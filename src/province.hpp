#pragma once
#ifndef _PROVINCE_H_
#define _PROVINCE_H_
#include "population.hpp"
#include "country.hpp"
#include <string>
#include <vector>

using namespace std;

enum types_of_province {
  meadows = 0,
  hills = 1,
  valley = 2,
  mountain = 3,
  desert = 4,
  jungle = 5,
  swamp = 6,
  forest = 7,
  tundra = 8,
  glacier = 9,
  ice = 10,
  ocean = 11,
  coast = 12,
  island = 13,
  archipelago = 14,
  river = 15
};

class country;
class province {
private:
  types_of_province type_of_province;
  uint id;
  string name;
  uint population_size;
  float latitude;
  float longitude;
  country* country_owner;
  float migration_atraction;
  float tax_control;
  vector<population> populations;
  vector<province*> neighbours;
  typedef struct {
    int k;
  } buildings;

public:
  province() {};
  province(uint id, string name, uint population_size, float latitude, float longitude, country* country_owner)
  {
    this->id = id;
    this->name = name;
    this->population_size = population_size;
    this->latitude = latitude;
    this->longitude = longitude;
    this->country_owner = country_owner;
    this->migration_atraction = 0;
    this->tax_control = 0;
  }
  ~province() {};
  string get_name();
  uint get_id();
  uint get_population();
  float get_latitude();
  float get_longitude();
  uint get_country_id();
  float get_migration_atraction();
  float get_tax_control();
  void set_migration_atraction(float migration_atraction);
  void set_tax_control(float tax_control);
  vector<province*> get_neighbours();


};
#endif



province _0_porto = {
  0,
  "Porto",
  20000,
  1.0,
  40.4,
  nullptr
};

province _1_lisboa = {
  1, "Lisboa", 31000, 45.1, 50.2, nullptr
};