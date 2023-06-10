#pragma once
#include <string>
#include "world.hpp"

using namespace std;

class building
{
  uint id;
  string name;
  uint size_workers;
public:
  ~building() {};
  building() {};
  building(uint id, string name, void (*func) (World*)) {
    this->id = id;
    this->name = name;
  }
  uint get_id() { return this->id; };
};