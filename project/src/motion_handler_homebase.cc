/**
 * @file motion_handler_homebase.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_homebase.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerHomeBase::MotionHandlerHomeBase() :
  heading_angle_(200.0),
  speed_(3),
  max_speed_(10) {}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerHomeBase::UpdateVelocity(SensorTouch st) {
  if (st.activated() == 1) {
    heading_angle_ = - st.angle_of_contact();
  }
}

void MotionHandlerHomeBase::HomeBaseChangeDirection(uint dt) {
  srand(time(NULL));
  double n = rand()% 360;
  int t = rand() % 2;
  if (t != 0) {
    set_heading_angle(heading_angle_);
  } else {
      set_heading_angle(n);
    }
}
NAMESPACE_END(csci3081);
