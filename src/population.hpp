#pragma once
#ifndef _POPULATION_H_
#define _POPULATION_H_
#include <string>
#include "culture.hpp"
using namespace std;
class population
{
private:
  uint id;
  string name;
  uint size;
  uint country_id;
  uint province_id;
  culture* cult;
public:
  population() {}
  population(uint id, string name, uint size, uint country_id, uint province_id)
  {
    this->id = id;
    this->name = name;
    this->size = size;
    this->country_id = country_id;
    this->province_id = province_id;
  }
  ~population() {}
  string get_name();
  uint get_id();
  uint get_size();
  uint get_country_id();
  uint get_province_id();
};
#endif

string population::get_name()
{
  return this->name;
}

uint population::get_id()
{
  return this->id;
}

uint population::get_size()
{
  return this->size;
}

uint population::get_country_id()
{
  return this->country_id;
}

uint population::get_province_id()
{
  return this->province_id;
}