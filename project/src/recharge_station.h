/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_
#define PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an RechargeStation.
  * Obstacle is inherited from Obstacle.
  * @params obstacles' params.
  */
class RechargeStation: public Obstacle {
 public:
/**
  * @brief Create the RechargeStation object
  */
  RechargeStation(double radius, const Position& pos,
                  const Color& color, enum entity_type type) :
      Obstacle(radius, pos, color, type) {}
  std::string name(void) const {
    return "Recharge Station";
  }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_ */
