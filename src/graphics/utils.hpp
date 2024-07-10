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


string getLiteralTypeProv(type_province type)
{
  switch (type)
  {
  case deep_sea:
    return "Deep Sea";
    break;
  case sea:
    return "Sea";
    break;
  case coastal_sea:
    return "Coastal Sea";
    break;
  case coast:
    return "Coast";
    break;
  case grassland:
    return "Grassland";
    break;
  case desert:
    return "Desert";
    break;
  case tundra:
    return "Tundra";
    break;
  case taiga:
    return "Taiga";
    break;
  case bare:
    return "Bare";
    break;
  case mountain:
    return "Mountain";
    break;
  case hill:
    return "Hill";
    break;
  case tropical:
    return "Tropical";
    break;
  case tropical_forest:
    return "Tropical Forest";
    break;
  case temperate_desert:
    return "Temperate Desert";
    break;
  case forest:
    return "Forest";
    break;
  case coastal_desert:
    return "Coastal Desert";
    break;
  default:
    break;
  }
  return "None";
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

string getLiteralRank(rank_province r) {
  switch (r) {
  case village:
    return "Village";
  case town:
    return "Town";
  case city:
    return "City";
  default:
    return "Village";
  }
}