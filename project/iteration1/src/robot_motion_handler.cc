/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(25) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: heading_angle(heading_angle_ - 10); break;
  case COM_TURN_RIGHT: heading_angle(heading_angle_ + 10); break;
  case COM_SPEED_UP: speed(speed_ + 1); break;
  case COM_SLOW_DOWN: speed(speed_ - 1); break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

void RobotMotionHandler::HomeBaseChangeDirection(uint dt) {
  srand(time(NULL));
  double n = rand()% 360;
  int t = rand()% 2;
  if (t != 0) {
    heading_angle(heading_angle_);
  } else {
      heading_angle(n);
    }
}
NAMESPACE_END(csci3081);
