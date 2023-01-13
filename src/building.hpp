#pragma once
#include <string>

using namespace std;

class building
{
  uint id;
  string name;
  uint size_workers;
public:
  ~building() {};
  building() {};
  building(uint id, string name, uint size_workers) {
    this->id = id;
    this->name = name;
    this->size_workers = size_workers;
  }
};