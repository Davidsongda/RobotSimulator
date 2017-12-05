/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <cstdlib>

#include "src/arena.h"
#include "src/robot.h"
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/event_proximity.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/event_debattery.h"
#include "src/event_despeed.h"
#include "src/event_transbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  player_(new Player(&params->player)),
  n_obstacles_(params->n_obstacles),
  n_observers_(params->n_observers),
  n_robots_(params->n_robots),
  observers_(),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color,
    params->recharge_station.type)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  // player_->set_heading_angle(37);
  entities_.push_back(player_);
  mobile_entities_.push_back(player_);
  observers_.push_back(player_);

  entities_.push_back(recharge_station_);
  // home_base_->set_heading_angle(37);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(home_base_);
  observers_.push_back(home_base_);
  for (int i=0; i < n_robots_; ++i) {
    Robot* r = new Robot(&params->robots[i]);
    entities_.push_back(r);
    mobile_entities_.push_back(r);
    observers_.push_back(r);
  }


  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color,
        params->obstacles[i].type));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::removeObserver(ArenaMobileEntity* a) {
  auto iterator = std::find(observers_.begin(), observers_.end(), a);
  if (iterator != observers_.end()) {
    observers_.erase(iterator);
  }
}

void Arena::notifyObserver(EventCollision * e) {
  for (ArenaMobileEntity * ame : observers_) {
    ame->Accept(e);
  }
}

void Arena::notifyObserver(EventProximity * e) {
  for (ArenaMobileEntity * ame : observers_) {
    ame->Accept(e);
  }
}

// void Arena::notifyObserver(EventTypeEmit * e) {
//   for(ArenaMobileEntity * ame : observers_) {
//     ame->Accept(e);
//   }
// }
//
// void Arena::notifyObserver(EventDistressCall * e) {
//   for(ArenaMobileEntity * ame : observers_) {
//     ame->Accept(e);
//   }
// }

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      res.push_back(r);
    }
  } /* for(ent..) */
  return res;
}

/*
 * @bag This function is supposed to use notifyObserver() to update Observers.
 * But when I use notifyObserver(), each events cannot be accept by sensors.
 * Entities would not collide with each other or do proximity.
 */
void Arena::AdvanceTime(void) {
  std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */
  if (player_->get_battery_level() <=0) {
    printf("YOU LOSE ! ");
    assert(0); /* not implemented yet */
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;

  EventProximity ep;

  EventTypeEmit et;

  EventDistressCall ed;

  CheckForEntityCollision(player_, recharge_station_,
    &ec, player_->get_collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    player_->Accept(&er);
  }

  std::vector<Obstacle*> obstacles_ = obstacles();
  for (size_t i = 1; i < obstacles_.size(); i++) {
    CheckForEntityCollision(player_, obstacles_[i], &ec,
      player_->get_collision_delta());
    if (ec.collided()) {
      EventDespeed eds;
      EventDebattery edb;
      player_ -> Accept(&eds);
      player_ -> Accept(&edb);
    }
  } /* for(i..) */


  // Player freeze robots or SuperBot freeze Player
  std::vector<Robot*> robots_ = robots();
  for (size_t i = 0; i < robots_.size(); i++) {
    CheckForEntityCollision(player_, robots_[i],
        &ec, player_->get_collision_delta());
    if (ec.collided()) {
      if (robots_[i]->isRobot()) {
        robots_[i]->set_speed(0);
      } else {
        player_->isFreeze(true);
      }
    }

  }

  // Win
  // bool winflag = false;
  // for (auto robot : robots_) {
  //   if (robot->get_type() == kRobot && robot->get_speed() != 0) {
  //     winflag = false;
  //   }
  // }
  // winflag = true;
  // if (winflag) {
  //   std::cout << "YOU WIN !!!" << '\n';
  //   assert(0);
  // }



  // Robots unfreeze robots
  for (size_t i = 1; i < robots_.size(); i++) {
    for (size_t j=0; j < robots_.size(); j++) {
      if (i != j) {
        CheckForEntityCollision(robots_[i], robots_[j],
            &ec, player_->get_collision_delta());
        if (ec.collided()) {
          robots_[j]->set_speed(3);
        }
      }
    }
  }

  // Robots hit homebase become Superbot
  for (size_t i = 0; i < robots_.size(); i++) {
    CheckForEntityCollision(robots_[i], home_base_,
        &ec, player_->get_collision_delta());
    if (ec.collided()) {
      EventTrans et;
      robots_[i]->Accept(&et);
    }
  }
  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->get_collision_delta());
        if (ec.collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */

  for (auto ent : robots_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    CheckForEntityOutOfBounds(ent, &ec);
    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec,
        	ent->get_collision_delta());
        if (ec.collided()) {
        	et.SensorPos(ent->get_pos());
          et.SensedPos(entities_[i]->get_pos());
          et.SensedRad(entities_[i]->get_radius());
          et.set_entity(ent->get_type());
          ent->Accept(&et);
          break;
      } else { // without collision
      	  ep.SensorPos(ent->get_pos());
          ep.SensedPos(entities_[i]->get_pos());
          ep.SensedRad(entities_[i]->get_radius());
          ep.SensorHd(ent->get_heading_angle());
          ent->Accept(&ep);
          std::cout << "Proximity" << ep.SensorHd() << '\n';
          if (ent->get_sp()) {
            et.SensorPos(ent->get_pos());
         	  et.SensedPos(entities_[i]->get_pos());
         	  et.SensedRad(entities_[i]->get_radius());
            et.set_entity(ent->get_type());
            ent->Accept(&et);

            if (ent->get_et() == kRobot) {
            	ed.SensorPos(ent->get_pos());
          	  ed.SensedPos(entities_[i]->get_pos());
          	  ed.SensedRad(entities_[i]->get_radius());
          	  ed.IsDistress(entities_[i]->get_distress());
              ent->Accept(&ed);

              if(ent->get_distress() == 1) {
                ent->closeSensors();
                continue;
              }
            } else if (ent->get_et() == kHomeBase) {
              ent->closeSensors();
              std::cout << "touch homebase" << '\n';
              continue;
            } else if (ent->get_et() == kPlayer) {
              continue;
            }
            break;
          }
        }
      }
    } else {
      ent->closeSensors();
    }
    ent->Accept(&ec);
  }
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x+ ent->get_radius() >= x_dim_) {
    // Right Wall
    event->collided(true);
    event->point_of_contact(Position(x_dim_, ent->get_pos().y));
    event->angle_of_contact(-180 + ent->get_heading_angle());
  } else if (ent->get_pos().x- ent->get_radius() <= 0) {
    event->collided(true);
    event->point_of_contact(Position(0, ent->get_pos().y));
    event->angle_of_contact(-180 + ent->get_heading_angle());
  } else if (ent->get_pos().y+ ent->get_radius() >= y_dim_) {
    // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->angle_of_contact(ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->get_radius() <= 0) {
    // Top Wall
    event->collided(true);
    event->point_of_contact(Position(0, y_dim_));
    event->angle_of_contact(ent->get_heading_angle());
  } else {
    event->collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaEntity *const ent1,
                                    const ArenaEntity *const ent2,
                                    EventCollision *const event,
                                    double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x;
  double ent1_y = ent1->get_pos().y;
  double ent2_x = ent2->get_pos().x;
  double ent2_y = ent2->get_pos().y;
  double dist = std::sqrt(
      std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->collided(false);
  } else {
    event->collided(true);

    double angle = std::asin(std::abs(ent2_x - ent1_x) / dist);

    if ((ent2_x - ent1_x) > 0) {
      if ((ent2_y - ent1_y) > 0) {
        // lower right
        event->point_of_contact(
            {
                ent1_x + std::sin(angle) * ent1->get_radius(),
                ent1_y + std::cos(angle) * ent1->get_radius()
            });
        angle = M_PI_2 - angle;
      } else if ((ent2_y - ent1_y) < 0) {
        // upper right
        event->point_of_contact(
            {
                ent1_x + std::sin(angle) * ent1->get_radius(),
                ent1_y - std::cos(angle) * ent1->get_radius()
            });
        angle += (3 * M_PI_2);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // 0 or 360 deg
        event->point_of_contact(
            {
                ent1_x + ent1->get_radius(),
                ent1_y
            });
        angle = 0;
      }
    } else if ((ent2_x - ent1_x) < 0)  {
      if ((ent2_y - ent1_y) > 0) {
        // lower left
        event->point_of_contact(
            {
                ent1_x - std::sin(angle) * ent1->get_radius(),
                ent1_y + std::cos(angle) * ent1->get_radius()
            });
        angle += M_PI_2;
      } else if ((ent2_y - ent1_y) < 0) {
        // upper left
        event->point_of_contact(
            {
                ent1_x - std::sin(angle) * ent1->get_radius(),
                ent1_y - std::cos(angle) * ent1->get_radius()
            });
        angle = (M_PI_2 * 2) + (M_PI_2 - angle);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // 180 deg
        event->point_of_contact(
            {
                ent1_x - ent1->get_radius(),
                ent1_y
            });
        angle = M_PI;
      }
    } else {  // if ((ent2_x - ent1_x) == 0)
      if ((ent2_y - ent1_y) > 0) {
        // 90 deg
        event->point_of_contact(
            {
                ent1_x,
                ent1_y + ent1->get_radius()
            });
        angle = M_PI_2;
      } else if ((ent2_y - ent1_y) < 0) {
        // 270 deg
        event->point_of_contact(
            {
                ent1_x,
                ent1_y - ent1->get_radius()
            });
        angle = (3 * M_PI_2);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // completely overlap, which is theoretically impossible...
        std::cerr << ent1->name() << " is in complete overlap with "
                  << ent2->name() << ".\n";
        // assert(false);
      }
    }

    event->angle_of_contact((M_PI - angle) / M_PI * 180);
  }
} /* entities_have_collided() */

// void Arena::CheckForRobotProximity(const Robot *const r1,
//                                     const ArenaEntity *const ent,
//                                     EventProximity * event) {
//   /* Note: this assumes circular entities */
//   SensorProximity s = r1->get_sp();
//   double sr = s.SensorReading(r1->get_pos(),
//               ent->get_pos(), r1->get_heading_angle(), ent->get_radius());
//
//   bool isPlayer = (typeid(*ent) == typeid(Player));
//   std::cout << sr << '\n';
//   if (sr != -1 && !isPlayer) {
//     event->Proximitied(true);
//     event->SensorPos(r1->get_pos());
//     event->SensedPos(ent->get_pos());
//     event->SensorHd(r1->get_heading_angle());
//   } else {
//     event->Proximitied(false);
//   }
// } /* entities_have_proximitied() */
//
// void Arena::CheckForRobotDistress(const Robot *const r1,
//                                     const ArenaEntity *const ent,
//                                     EventDistressCall * event) {
//   /* Note: this assumes circular entities */
//   SensorDistress s = r1->get_sd();
//   int id = s.IsDistress();
//
//   bool isR = (typeid(*ent) == typeid(Robot));
//   std::cout << id << '\n';
//   if (id == 1 && isR) {
//     event->Distressed(true);
//     event->SensorPos(r1->get_pos());
//     event->SensedPos(ent->get_pos());
//     event->SensedRad(r1->get_radius());
//   } else {
//     event->Distressed(false);
//   }
// } /* entities_have_proximitied() */

void Arena::Accept(__unused EventKeypress * e) {
  player_->EventCmd(e->get_key_cmd());
}

NAMESPACE_END(csci3081);
