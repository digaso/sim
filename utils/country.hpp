#pragma once
#include <string>
#include <vector>
#include "province.hpp"
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
  static Country* getCountryById(uint id, vector<Country> countries);
};

Country::Country(string name, uint population)
{
  this->name = name;
  this->population = population;
}

Country::~Country()
{
}

Country* Country::getCountryById(uint id, vector<Country> countries)
{
  if (id < countries.size())
    return &countries.at(id);
  return NULL;
}
