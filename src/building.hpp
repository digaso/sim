#pragma once
#include <string>
#include "world.hpp"
#include "configs.h"

using namespace std;



class Building
{
  uint id;
  uint price;
  string name;
  type_building type;
  uint size_workers; //per level
  Production production;
  float upkeep;
  uint build_time;
  uint build_cost;


public:
  void (*func) (World*, uint, uint8_t, Building);
  ~Building();
  Building();
  Building(uint id, string name, Production building_production, type_building building_type, void (*func) (World*, uint, uint8_t, Building));
  uint get_id() { return this->id; };
  Production get_production() { return this->production; };
  string get_name() { return this->name; };
  uint get_size_workers() { return this->size_workers; };
  void setup_buildings(World* w);
};