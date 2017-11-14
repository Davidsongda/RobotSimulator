
/**
 * @file home_base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
#include "src/home_base.h"
#include "src/robot_motion_behavior.h"

NAMESPACE_BEGIN(csci3081);

uint HomeBase::next_id_ = -99;

HomeBase::HomeBase(const struct home_base_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  id_(-100) {
  motion_handler_.heading_angle(0);
  motion_handler_.speed(7);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void HomeBase::TimestepUpdate(uint dt) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
    // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Random change the direction of home_base
  motion_handler_.HomeBaseChangeDirection(dt);


  // Deplete battery as appropriate given distance and speed of movement
  // battery_.Deplete(old_pos, get_pos(), dt);
  // std::cout << "Reach baterry deplete"<< std::endl;
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void HomeBase::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void HomeBase::Accept(EventRecharge * e) {
}

void HomeBase::Accept(EventDespeed * e) {
}

void HomeBase::Accept(EventDebattery * e) {
}

// User input commands to change heading or speed
void HomeBase::EventCmd(enum event_commands cmd) {
} /* event_cmd() */

void HomeBase::Reset(void) {
  set_pos(Position(400, 400));
  motion_handler_.Reset();
  sensor_touch_.Reset();
} /* Reset() */



NAMESPACE_END(csci3081);
