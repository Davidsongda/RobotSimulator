/**
 * @file robot_arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_ARENA_H_
#define PROJECT_ITERATION3_SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/event_distress.h"
#include "src/event_proximity.h"
#include "src/robot.h"
#include "src/player.h"
#include "src/home_base.h"
#include "src/recharge_station.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * RobotViewer or Tests call \ref set_time and \ref advance_time to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of robots and
 * obstacles).
 *
 *  For now, RobotArena is hard coded to run a simulation of two robots running
 *  around in a circle.  You can see their sensors, but they don't yet respond
 *  to each other or to obstacles.
 */
class Arena {
 public:
   /**
   * @brief Create the Arena
   * parameter's type is struct named arena_params.
   */
  explicit Arena(const struct arena_params * const params);

  /**
  * @brief Desructor of Arena
  */
  ~Arena(void);

  /**
   * @brief Advance the simulation by a single step.
   */
  void AdvanceTime(void);

  /**
  * @brief Handle the key press passed along by the viewer.
  *
  * @param[in] an event holding the key press.
  *
  */
  void Accept(EventKeypress * e);

  /**
   * @brief Get a list of all robots (i.e. mobile entities in the arena).
   */
  std::vector<class Robot*> robots(void);


  /*
   * @brief Add observer.
   */
  void registerObserver(ArenaMobileEntity* ame) {
    observers_.push_back(ame);
  }

  /*
   * @brief remove observer.
   */
  void removeObserver(ArenaMobileEntity* ame);

  /*
   * @brief notify observer.
   */
  void notifyObserver(EventCollision * e);

  /*
   * @brief notify observer.
   */
  void notifyObserver(EventProximity * e);

  /*
   * @brief notify observer.
   */
  void notifyObserver(EventDistressCall * e) {}

  /*
   * @brief notify observer.
   */
  void notifyObserver(EventTypeEmit * e) {}

  // Reset all in the arena
  void Reset(void);

  /*
   * @brief Get the # of robots in the arena.
   */
  unsigned int n_robots(void) { return n_robots_; }

  /*
   * @brief Get # of obstacles in the arena.
   */
  unsigned int n_obstacles(void) { return n_obstacles_; }

  /**
   * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
   */
  std::vector<class Obstacle*> obstacles(void);



  /**
   * @brief Get the list of all mobile entities in the arena.
   */
  std::vector<class ArenaMobileEntity*> mobile_entities(void)
    { return mobile_entities_; }

 /**
  * @brief Get the robot
  */
  Player* player(void) const { return player_; }

  /**
   * @brief Get the homebase
   */
  HomeBase* home_base(void) const { return home_base_; }

  /**
   * @brief Get the recharge_station
   */
  RechargeStation* recharge_station(void) const { return recharge_station_; }

  /**
   * @brief Get the obstacles
   */
  Obstacle* obstacles(void) const { return obstacles_; }


  /**
   * @brief Get the robots
   */
  Robot* robots(void) const { return robots_; }

  /**
    * @brief Win condition
    */
  bool Win();
  /**
    * @brief Lose condition
    */
  bool Lose();

  /**
    * @brief Refactor3 update event
    */
  void LoadtoProximityEvent(Robot * r, ArenaEntity * a, EventProximity * p);

  /**
    * @brief Refactor3 update event
    */
  void LoadtoDistressEvent(Robot * r, ArenaEntity * a, EventDistressCall * d);

  /**
    * @brief Refactor3 update event
    */
  void LoadtoTypeEmitEvent(Robot * r, ArenaEntity * a, EventTypeEmit * t);

 private:
  /**
   * @brief Determine if two entities have collided in the arena. Collision is
   * defined as the difference between the extents of the two entities being less
   * than a run-time parameter.
   *
   * @param ent1 Entity #1.
   * @param ent2 Entity #2.
   * @param pointer to a collision event
   *
   * Collision Event is populated appropriately.
   */
  void CheckForEntityCollision(const class ArenaEntity* const ent1,
    const class ArenaEntity* const ent2,
    EventCollision * ec,
    double collision_delta);

    /**
     * @brief Determine if two entities have Proximitied in the arena. Proximity is
     * defined as the difference between the extents of the two entities being less
     * than a run-time parameter.
     *
     * @param ent1 Entity #1.
     * @param ent2 Entity #2.
     * @param pointer to a Proximity event
     *
     */
  void CheckForRobotProximity(const class Robot* const r1,
    const class ArenaEntity* const ent,
    EventProximity * ep);

    /**
     * @brief Determine if two entities have Distressed in the arena. Distress is
     * defined as the difference between the extents of the two entities being less
     * than a run-time parameter.
     *
     * @param ent1 Entity #1.
     * @param ent2 Entity #2.
     * @param pointer to a Distress event
     *
     */
  void CheckForRobotDistress(const class Robot* const r1,
    const class ArenaEntity* const ent,
    EventDistressCall * ed);


  /**
   * @brief Determine if a particular entity is gone out of the boundaries of
   * the simulation.
   *
   * @param ent The entity to check.
   * @param pointer to a collision event.
   *
   * Collision event is populated appropriately.
   */
  void CheckForEntityOutOfBounds(const class ArenaMobileEntity* const ent,
    EventCollision * ec);

  /**
   * @brief Update all entities for a single timestep
   */
  void UpdateEntitiesTimestep(void);

  // Under certain circumstance, the compiler requires that the copy
  // constructor is not defined. This is deleting the default copy const.
  Arena& operator=(const Arena& other) = delete;
  Arena(const Arena& other) = delete;

  // Dimensions of graphics window inside which robots must operate
  double x_dim_;
  double y_dim_;
  unsigned int n_robots_;
  unsigned int n_observers_;
  unsigned int n_obstacles_;
  unsigned int n_player;

  // Entities populating the arena
  Player* player_;
  Robot* robots_;
  RechargeStation * recharge_station_;
  HomeBase * home_base_;
  Obstacle * obstacles_;
  std::vector<class ArenaEntity*> entities_;
  std::vector<class ArenaMobileEntity*> mobile_entities_;
  std::vector<class ArenaMobileEntity*> observers_;
  std::vector<class Robot*> r;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_ARENA_H_
