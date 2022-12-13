#pragma once
#ifndef _PROVINCE_H_
#define _PROVINCE_H_
#include "population.hpp"
#include "country.hpp"
#include <string>
#include <vector>

using namespace std;

class country;

class province {
private:
  uint id;
  string name;
  uint population_size;
  float latitude;
  float longitude;
  country* country_owner;
  uint migration_atraction;
  float tax_control;
  vector<population> populations;
  typedef struct {
    int k;
  } buildings;

public:
  province();
  province(uint id, string name, uint population_size, float latitude, float longitude, country* country_owner)
  {
    this->id = id;
    this->name = name;
    this->population_size = population_size;
    this->latitude = latitude;
    this->longitude = longitude;
    this->country_owner = country_owner;
    this->id = 0;
  }
  ~province() {};
  string get_name();
  uint get_id();
  uint get_population();
  float get_latitude();
  float get_longitude();
  uint get_country_id();
  uint get_migration_atraction();
  float get_tax_control();

};
#endif

string province::get_name()
{
  return this->name;
}

uint province::get_id()
{
  return this->id;
}

uint province::get_population()
{
  return this->population_size;
}

float province::get_latitude()
{
  return this->latitude;
}

float province::get_longitude()
{
  return this->longitude;
}


uint province::get_migration_atraction()
{
  return this->migration_atraction;
}

float province::get_tax_control()
{
  return this->tax_control;
}
