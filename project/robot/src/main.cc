/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/robot.h"
#include "src/player.h"
#include "src/home_base.h"
#include "src/recharge_station.h"
#include "src/entity_type.h"
#include "fstream"

using namespace std;
using namespace csci3081;

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char * argv[]) {
  csci3081::arena_params aparams;
  csci3081::robot_params rparams;
  csci3081::home_base_params hparams;
  csci3081::player_params pparams;
  ifstream configfile;
  argc = 2;
  argv[0] = "iteration2";
  argv[1] = "config.txt";
  argc--;
  argv++;

  configfile.open(* argv);
  assert(configfile.is_open());  // make sure file opened
  string line;
  char command[100];
  int countO = 0;
  int countR = 0;
  while (getline(configfile, line)) {
    if (line[0] == '#') continue;  // jump line comments
    sscanf(line.c_str(), "%s ", command);
    string cmd = command;
    if (cmd == "Obstacle") {
      float x, y, rod;
      int t, r, g, b, a;
      sscanf(line.c_str(), "Obstacle %f %f %f %d %d %d %d %d",
        &x, &y, &rod, &t, &r, &g, &b, &a);
      // Obstacle* o = new Obstacle(rod, pos, col);
      aparams.obstacles[countO].radius = rod;
      aparams.obstacles[countO].pos = {x, y};
      aparams.obstacles[countO].type = (enum csci3081::entity_type)t;
      aparams.obstacles[countO].color = csci3081::Color(r, g, b, a);
      countO += 1;
      cout <<countO <<endl;
    } else if (cmd == "Player") {
      float x, y, rod, bmc, ad;
      int cd, t, r, g, b, a;
      sscanf(line.c_str(), "Player %f %f %f %f %f %d %d %d %d %d %d", &x, &y, &rod,
            &bmc, &ad, &cd, &t, &r, &g, &b, &a);
      pparams.battery_max_charge = bmc;
      pparams.angle_delta = ad;
      pparams.collision_delta = cd;
      pparams.radius = rod;
      pparams.pos = {x, y};
      pparams.type = (enum csci3081::entity_type)t;
      pparams.color = csci3081::Color(r, g, b, a);
      aparams.player = pparams;
    } else if (cmd == "HomeBase") {
      float x, y, rod, ad, cd;
      int t, r, g, b, a;
      sscanf(line.c_str(), "HomeBase %f %f %f %f %f %d %d %d %d %d", &x, &y, &rod,
            &ad, &cd, &t, &r, &g, &b, &a);
      hparams.angle_delta = ad;
      hparams.collision_delta = cd;
      hparams.radius = rod;
      hparams.pos = {x, y};
      hparams.type = (enum csci3081::entity_type)t;
      hparams.color = csci3081::Color(r, g, b, a);
      aparams.home_base = hparams;

    } else if (cmd == "RechargeStation") {
      float x, y, rod;
      int t, r, g, b, a;
      sscanf(line.c_str(), "RechargeStation %f %f %f %d %d %d %d %d", &x, &y, &rod, &t,
            &r, &g, &b, &a);
      aparams.recharge_station.radius = rod;
      aparams.recharge_station.pos = {x, y};
      aparams.recharge_station.type = (enum csci3081::entity_type)t;
      aparams.recharge_station.color =
        csci3081::Color(r, g, b, a);
    } else if (cmd == "Robot") {
      float x, y, rod, ad, cd;
      int t, r, g, b, a;
      sscanf(line.c_str(), "Robot %f %f %f %f %f %d %d %d %d %d", &x, &y, &rod,
            &ad, &cd, &t, &r, &g, &b, &a);
      aparams.robots[countR].angle_delta = ad;
      aparams.robots[countR].collision_delta = cd;
      aparams.robots[countR].radius = rod;
      aparams.robots[countR].pos = {x, y};
      aparams.robots[countR].type = (enum csci3081::entity_type)t;
      aparams.robots[countR].color = csci3081::Color(r, g, b, a);
      countR += 1;
    } else if (cmd == "robotnum") {
      int num;
      sscanf(line.c_str(), "robotnum %d", &num);
      aparams.n_robots = num;
    }
  }

  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities

  // csci3081::home_base_params hparams;

  aparams.n_obstacles = countO;

  aparams.y_dim = 768;
  aparams.x_dim = 1024;

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
