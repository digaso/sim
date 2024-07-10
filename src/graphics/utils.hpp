#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "../configs.h"

using namespace std;

Vector2 getCoordinatesByMouse(Camera2D camera) {
  Vector2 mousePos = GetMousePosition();
  mousePos = GetScreenToWorld2D(mousePos, camera);
  int x = (int)mousePos.x / (TILESIZE * camera.zoom);
  int y = (int)mousePos.y / (TILESIZE * camera.zoom);

  return { (float)x, (float)y };
}

string getLiteralVelocity(game_velocity v) {
  switch (v) {
  case PAUSED:
    return "Paused";
  case SLOW:
    return "Slow";
  case MEDIUM:
    return "Normal";
  case FAST:
    return "Fast";
  case SUPER_FAST:
    return "Super Fast";
  default:
    return "Paused";
  }
}