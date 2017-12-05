/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_
#define PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include "src/position.h"
#include "src/color.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 *
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Note that not all classes need to be able to do these two things.
 */
class ArenaEntity {
 public:
  /**
  * @brief Create an ArenaEnity object with radius, position and color. Then create a Destructor without and paraems.
  */
  ArenaEntity(double radius, const Position& pos,
              const Color& color, enum entity_type type) :
      radius_(radius), pos_(pos), color_(color), type_(type) {}
  virtual ~ArenaEntity(void) {}

  /**
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /**
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}

  /**
   * @brief Make an annoucment what's the name of this ArenaEntity. It's a pure virtual function.
   */
  virtual std::string name(void) const = 0;

  /**
   * @brief Set the arena entity's position
   */
  void set_pos(const Position& pos) { pos_ = pos; }

  /**
   * @brief Get the arena entity's position from Position& pos.
   */
  const Position& get_pos(void) const { return pos_; }

  /**
   * @brief Get the arena entity's color
   */
  const Color& get_color(void) const { return color_; }

  /**
   * @brief Set the arena entity's color by using Color& color
   */
  void set_color(const Color& color) { color_ = color; }

  /**
   * @brief Judge whether the entity is mobile or not. 1 means is mobile, 0 means is not mobile.
   */
  virtual bool is_mobile(void) = 0;

  /**
   * @brief Get the arena entity's radius
   */
  double get_radius(void) const { return radius_; }

  virtual int get_distress() {}

  enum entity_type get_type() {
    return type_;
  }

  void set_type(enum entity_type t) { type_ = t; }

 private:
  double radius_;
  Position pos_;
  Color color_;
  enum entity_type type_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_
