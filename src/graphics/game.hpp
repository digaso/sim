#pragma once
#include <raylib.h>
#include <rlgl.h>
#include "screens.hpp"
#include "future"
#include <filesystem>
#include "render_maps.hpp"
#include "../generation/generation.hpp"
#include "../configs.h"
#include "thread"
#include "mutex"
#include "chrono"

using namespace std;
static game_velocity velocity = PAUSED;
static GameScreen s = GameScreen::SCREEN_GAME;
static auto last_tick = chrono::steady_clock::now();

void updateWorld(World* w, game_velocity* velocity) {
  auto now = chrono::steady_clock::now();
  switch (*velocity)
  {
  case PAUSED:
    break;
  case SLOW:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 550) {
      w->updateWorld();
      last_tick = now;
    }
    break;

  case MEDIUM:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 250) {
      w->updateWorld();
      last_tick = now;
    }
    break;
  case FAST:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 80) {
      w->updateWorld();
      last_tick = now;
    }
    break;
  case SUPER_FAST:
    w->updateWorld();
    break;
  default:
    break;
  }
}



void run(World* w) {
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_width, window_height, "Winds of Gold");
  SetTargetFPS(60);
  drawLoadingScreen();
  province_properties* props = generate_map(w);
  w->updateCountries();
  initGameScreen(w, props);
  //create thread
  atomic_bool playing = true;
  thread t1([&]() {
    while (playing)
      updateWorld(w);

    });
  while (!WindowShouldClose()) {
    updateGameScreen(w);
    drawGameScreen(w);
  }
  playing = false;
  t1.join();

}