/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double RobotBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
    double ox = old_pos.x;
    double oy = old_pos.y;
    double nx = new_pos.x;
    double ny = new_pos.y;
    double livel = std::sqrt(
      std::pow(nx - ox, 2) + std::pow(ny - oy, 2)) / dt;
    double anvel = (2*3.1415926)/dt;
    // charge_ = charge_ - ((kBASE_DEPLETION * dt) +
    // (kLINEAR_SCALE_FACTOR * livel) +
    // (kANGULAR_SCALE_FACTOR * anvel));
    if (ox == nx && oy == ny) {
      return charge_;
    } else {
      charge_ = charge_ - ((kBASE_DEPLETION * dt) +
      (kLINEAR_SCALE_FACTOR * livel) + (kANGULAR_SCALE_FACTOR * anvel));
      if (charge_ < 0) {
        charge_ = 0;
        return charge_;
      } else {
          return charge_;
        }
    }
} /* deplete() */

void Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
}

NAMESPACE_END(csci3081);
