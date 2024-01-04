#pragma once
#include <string>
#include "world.hpp"

using namespace std;

class Building
{
  uint id;
  string name;
  type_good* types_alowed;
  uint size_workers;
public:
  void (*func) (World*, uint, uint8_t);
  ~Building() {};
  Building() {};
  Building(uint id, string name, void (*func) (World*, uint, uint8_t)) {
    this->id = id;
    this->name = name;
    this->func = func;

  }
  uint get_id() { return this->id; };
  string get_name() { return this->name; };
  uint get_size_workers() { return this->size_workers; };
  void setup_buildings(World* w);
};