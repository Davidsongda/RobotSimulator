/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>
#include "src/player.h"
#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "player Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                       "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    last_dt += dt;
    while (last_dt > 0.05) {
      arena_->AdvanceTime();
      last_dt -= 0.05;
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  std::cout << "Left mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  std::cout << "Right mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  std::cout << "Special Key UP key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawPlayer(NVGcontext *ctx,
    const Player* const player) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this player
  nvgSave(ctx);
  nvgTranslate(ctx, player->get_pos().x, player->get_pos().y);
  nvgRotate(ctx, player->get_heading_angle());

  // player's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, player->get_radius());
  nvgFillColor(ctx, nvgRGBA(player->get_color().r,
                            player->get_color().g,
                            player->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // player id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, player->name().c_str(), NULL);
  double visbattery = player->get_battery_level();
  // make battery visualized
  int visb = (int)visbattery;
  std::string b = std::to_string(visb);
  nvgText(ctx, 0.0, 0.0, b.c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);
  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
    obstacle->get_radius());
  nvgFillColor(ctx, nvgRGBA(obstacle->get_color().r,
                            obstacle->get_color().g,
                            obstacle->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
          obstacle->name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x, home->get_pos().y, home->get_radius());
  nvgFillColor(ctx, nvgRGBA(home->get_color().r,
                            home->get_color().g,
                            home->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x, home->get_pos().y, home->name().c_str(),
    NULL);
}

void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                               const Robot* const robot) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, robot->get_pos().x, robot->get_pos().y, robot->get_radius());
  nvgFillColor(ctx, nvgRGBA(robot->get_color().r,
                            robot->get_color().g,
                            robot->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, robot->get_pos().x, robot->get_pos().y, robot->name().c_str(),
    NULL);

  // translate and rotate all graphics calls that follow so that they are
  // centered at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x, robot->get_pos().y);
  double angle = (robot->get_heading_angle() * 3.1415 / 180);
  nvgRotate(ctx, angle);
  double sensor_angle = (robot->get_proximity().filed_of_view() * 3.1415 / 180);
  double sensor_dist = robot->get_proximity().distance();
  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -(sensor_angle), NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 100, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);
  nvgRestore(ctx);
}
// This is the primary driver for drawing all entities in the arena.
// It is called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  std::vector<Robot*> robots = arena_->robots();
  for (size_t i = 0; i < robots.size(); i++) {
    DrawRobot(ctx, robots[i]);
  }

  DrawPlayer(ctx, arena_->player());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
