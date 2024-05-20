#pragma once
#include "raylib.h"
#include "screens.hpp"

void initLoadingScreen() {
  // Initialization
}

void updateLoadingScreen() {
  // Update
}

void drawLoadingScreen() {
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);
    DrawText("Loading...", GetRenderWidth() / 2, GetRenderHeight() / 2, 20, GRAY);
  }
  EndDrawing();
}

