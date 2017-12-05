/**
 * @file arena_immobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_ARENA_IMMOBILE_ENTITY_H_
#define PROJECT_ITERATION2_SRC_ARENA_IMMOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an ArenaImmobileEntity with radius, position and color.
  * ArenaImmobileEntity is inherited from ArenaEntity.
  */
class ArenaImmobileEntity : public ArenaEntity {
 public:
   /**
    * @brief Create an ArenaImmobileEntity with radius, position and color.
    * ArenaImmobileEntity is inherited from ArenaEntity.
    */
  ArenaImmobileEntity(double radius, const Position& pos,
                    const Color& color, const enum entity_type type) :
      ArenaEntity(radius, pos, color, type) {}
  /**
  * @brief Shows that the ArenaImmobileEntity is not a mobile entity.
  */
  bool is_mobile(void) { return false; }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_ARENA_IMMOBILE_ENTITY_H_ */
