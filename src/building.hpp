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
  population_class worker_class; //class of worker that works in the building
  Production production;
  float upkeep;
  uint build_time; //in months
  float infrastructure_cost;
  float build_cost;
  uint8_t max_levels;
  vector<rank_province> rank_provinces_allowed;
  vector<uint> required_buildings;
  vector<uint> required_techs;
  vector<uint> required_goods;


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