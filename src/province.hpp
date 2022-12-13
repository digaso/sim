#pragma once
#include "country.hpp"
#include <string>
using namespace std;

class province {
private:
  static uint id_counter;
  uint id;
  string name;
  uint population;
  float latitude;
  float longitude;
  //country* country_owner;
  int country_id;
  uint migration_atraction;
  float tax_control;

public:
  province(string name, uint population, float latitude, float longitude, uint country_id);
  ~province();
};

province::province(string name, uint population, float latitude, float longitude, uint country_id)
{
  this->name = name;
  this->population = population;
  this->latitude = latitude;
  this->longitude = longitude;
  this->country_id = country_id;
  this->id = 0;
}

province::~province()
{
}
