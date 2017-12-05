
/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
#include "src/robot.h"
#include "src/player_motion_behavior.h"

NAMESPACE_BEGIN(csci3081);

uint Robot::next_id_ = 1;

Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color, params->type),
  angle_delta_(params->angle_delta),
  resetPos(params->pos),
  motion_behavior_(),
  resetHd(),
  motion_handler_(new MotionHandlerRobot()),
  sensor_touch_(),
  sensor_proximity_(),
  sensor_entity_type_(),
  sensor_distress_(),
  id_(0) {
  motion_handler_->set_heading_angle(30);
  motion_handler_->set_speed(3);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_->UpdateVelocity(sensor_touch_, sensor_proximity_, sensor_entity_type_);

    // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);

  // Random change the direction of robot
  // motion_handler_.HomeBaseChangeDirection(dt);


  // Deplete battery as appropriate given distance and speed of movement
  // battery_.Deplete(old_pos, get_pos(), dt);
  // std::cout << "Reach baterry deplete"<< std::endl;
} /* TimestepUpdate() */

bool Robot::isRobot() {
  return (motion_handler_->isRobot());
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}


void Robot::Accept(EventProximity * e) {
  sensor_proximity_.Accept(e);
}

void Robot::Accept(EventTrans * e) {
  if ( e->Trans() ) {
    motion_handler_ = new MotionHandlerSuperBot();
    set_color(csci3081::Color(0, 0, 0, 255));
    set_speed(3);
  }
}

void Robot::Accept(EventDistressCall * e) {
  sensor_distress_.Accept(e);
}
void Robot::Accept(EventTypeEmit * e) {
  sensor_entity_type_.Accept(e);
}



void Robot::Reset(void) {
  set_pos(resetPos);
  set_heading_angle(resetHd);
  motion_handler_ = new MotionHandlerRobot();
  motion_handler_->Reset();
  sensor_touch_.Reset();
  Color r = csci3081::Color(0, 255, 0, 255);
  set_color(r);
} /* Reset() */



NAMESPACE_END(csci3081);
