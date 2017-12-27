/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_superbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerSuperBot::MotionHandlerSuperBot() :
  heading_angle_(200.0),
  speed_(3),
  max_speed_(10) {}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerSuperBot::UpdateVelocity(SensorTouch st, SensorProximity sp,
      SensorEntityType se, SensorDistress sd) {
    if (st.activated() == 1 && se.activated() == 1) {
      heading_angle_ = - st.angle_of_contact();
    } else if (st.activated() == 1 && se.activated() == 0) {
      heading_angle_ = - st.angle_of_contact();
    } else if (sp.activated() == 1) {
      heading_angle_ += 180;
      set_speed(speed_ - 0.2);
    }
}

NAMESPACE_END(csci3081);
