/**
 * @file motion_handler_player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_player.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerPlayer::MotionHandlerPlayer() :
    heading_angle_(30.0),
    speed_(5.0),
    max_speed_(10.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerPlayer::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: set_heading_angle(heading_angle_ - 10); break;
  case COM_TURN_RIGHT: set_heading_angle(heading_angle_ + 10); break;
  case COM_SPEED_UP: set_speed(speed_ + 1); break;
  case COM_SLOW_DOWN: set_speed(speed_ - 1); break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void MotionHandlerPlayer::UpdateVelocity(SensorTouch st) {
  if (st.activated() == 1) {
    heading_angle_ = - st.angle_of_contact();
  }
}

NAMESPACE_END(csci3081);
