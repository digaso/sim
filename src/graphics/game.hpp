#pragma once
#include <raylib.h>
#include <rlgl.h>
#include "screens.hpp"
#include "future"
#include <filesystem>
#include "render_maps.hpp"
#include "../generation/generation.hpp"



using namespace std;

static int window_width = 1920;
static int window_height = 1080;

static GameScreen s = GameScreen::SCREEN_GAME;

void run(World* w) {
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_width, window_height, "Winds of Gold");
  SetTargetFPS(60);
  drawLoadingScreen();
  province_properties* props = generate_map(w);
  initGameScreen(w, props);
  while (!WindowShouldClose()) {
    updateGameScreen(w);
    drawGameScreen(w);
  }
}