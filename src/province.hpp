#pragma once
#ifndef _PROVINCE_H_
#define _PROVINCE_H_
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
  province(uint id, string name, uint population, float latitude, float longitude, uint country_id);
  ~province();
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
province::province(uint id, string name, uint population, float latitude, float longitude, uint country_id)
{
  this->id = id;
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
  return this->population;
}

float province::get_latitude()
{
  return this->latitude;
}

float province::get_longitude()
{
  return this->longitude;
}

uint province::get_country_id()
{
  return this->country_id;
}

uint province::get_migration_atraction()
{
  return this->migration_atraction;
}

float province::get_tax_control()
{
  return this->tax_control;
}
