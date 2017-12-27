/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "src/sensor_entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorEntityType::SensorEntityType() :
    Sensor(),
    range_(60.0),
    sensor_pos(0.0, 0.0),
    sensed_pos(0.0, 0.0),
    sensed_radius(0.0),
    s_entity_(kRobot) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


void SensorEntityType::Reset() {
  activated(0);
} /* reset() */

bool SensorEntityType::InRange(EventTypeEmit * e) {
  // double e1x = e->SensorPos().x;
  // double e1y = e->SensorPos().y;
  // double e2x = e->SensedPos().x;
  // double e2y = e->SensedPos().y;
  // double dist = std::sqrt(
  //   std::pow(e2x - e1x, 2) + std::pow(e2y - e1y, 2));
  if (calcu_Dis(e->SensorPos().x, e->SensorPos().y,
    e->SensedPos().x, e->SensedPos().y) > range_ + e->SensedRad()) {
    return false;
  } else {
    return true;
  }
}

void SensorEntityType::Accept(EventTypeEmit *const e) {
  if (InRange(e)) {
    activated(1);
    sensor_pos = e->SensorPos();
    sensed_pos = e->SensedPos();
    sensed_radius = e->SensedRad();
    s_entity_ = e->get_entity();
    std::cout << "event entity" << " " << s_entity_ << '\n';
  } else {
    activated(0);
  }
}

NAMESPACE_END(csci3081);
