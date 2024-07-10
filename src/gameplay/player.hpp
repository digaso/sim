#pragma once
#include "../world.hpp"

class Player {
public:
  Player(World* w, uint country_id);
private:
  World* w;
  Country* country_player;
};