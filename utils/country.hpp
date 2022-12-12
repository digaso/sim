#pragma once
#include <string>
#include "province.hpp"
#include <vector>
using namespace std;

class Country
{
private:
  uint id;
  string name;
  uint population;
  float money;
  vector<Province> provinces;

public:
  Country(string name, uint population);
  ~Country();
};

Country::Country(string name, uint population)
{
  this->name = name;
  this->population = population;
}

Country::~Country()
{
}
