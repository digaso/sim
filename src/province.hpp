#pragma once
#include <string>
#include "population.hpp"
#include "country.hpp"
#include <vector>


using namespace std;


enum type_province {
  deep_sea = 0,
  sea = 1,
  coastal_sea = 2,
  coast = 3,
  grassland = 4,
  forest = 5,
  tropical_forest = 6,
  desert = 7,
  temperate_desert = 8,
  hill = 9,
  tropical = 10,
  mountain = 11,
  bare = 12,
  taiga = 13,
  tundra = 14,
};

class country;
class Province {
private:
  vector<population> populations;
  uint id;
  string name;
  uint population_size;
  float y;
  float x;
  float height;
  float moisture;
  type_province type;
  country* country_owner;
  float migration_atraction;
  float tax_control;
  typedef struct {
    int k;
  } buildings;

public:
  Province() {};
  Province(uint id, string name, uint population_size, float y, float x, float height, type_province type, float moisture)
  {
    this->id = id;
    this->name = name;
    this->population_size = population_size;
    this->y = y;
    this->x = x;
    this->migration_atraction = 0;
    this->tax_control = 0;
    this->height = height;
    this->type = type;
    this->moisture = moisture;
  }
  ~Province() {};
  string get_name();
  uint get_id();
  uint get_population();
  float get_y();
  float get_x();
  country* get_country();
  type_province get_type();
  void set_country(country* country_owner);
  float get_migration_atraction();
  float get_tax_control();
  float get_height();
  void set_migration_atraction(float migration_atraction);
  void set_tax_control(float tax_control);
  static string type_province_to_string(type_province type);
  friend ostream& operator<<(ostream& os, const Province& p);

};
