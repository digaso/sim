#pragma once
#include <string>

using namespace std;

class Province
{
private:
  static uint id_counter;
  uint id;
  string name;
  uint population;
  float latitude;
  float longitude;
  uint country_id;
  uint migration_atraction;
  float tax_control;

public:
  Province(string name, uint population, float latitude, float longitude, uint country_id);
  ~Province();
};

Province::Province(string name, uint population, float latitude, float longitude, uint country_id)
{
  this->name = name;
  this->population = population;
  this->latitude = latitude;
  this->longitude = longitude;
  this->country_id = country_id;
  this->id = 0;
}

Province::~Province()
{
}
