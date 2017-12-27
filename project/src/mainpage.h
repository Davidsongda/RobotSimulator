/**
 * @file mainpage.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
#ifndef PROJECT_ITERATION3_SRC_MAINPAGE_H_
#define PROJECT_ITERATION3_SRC_MAINPAGE_H_
/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * This project is a robot simulation program acting like a video game.
 * There are many different components (player, robot, superbot, homebase,
 * recharge station, obstacle) in a visible graphic window. Player, robot, superbot
 * and homebase are moving in this visible field while other objects keep stationary.
 * The player is manipulated by users and all the other mobile entities are moving under
 * the control of themselves. A moving robot will be frozen when it collides with the player
 * and will turn to a superbot when it collides with the homebase. The user needs to control the
 * player to make all the robots frozen at the same time to win the game. Lose the game when the battery of
 * the player dies or all robots collide with the home base and become superbot.
 * Based on the iteration one code, we already implemented the basic interaction functionality
 * between objects in the arena like collision and bounce, recharging the battery, depleting the battery,
 * controlling the robot and decreasing the robot’s speed when hitting the obstacles. In iteration two,
 * we need to refactor the code structure and implement a few more features. The primary addition
 * in this iteration is that the robot is autonomous with four different sensors having different
 * functionalities. The implementation of these four sensors is the most important part. Besides,
 * in this iteration, we are supposed to use observer pattern to deal with the relationship between arena
 * and the robots in it. The goal of this iteration and a general description are given as follows.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#endif  // PROJECT_ITERATION3_SRC_MAINPAGE_H_
