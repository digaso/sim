#pragma once
#include <string>
#include "population.hpp"
#include "country.hpp"
#include <vector>


using namespace std;

enum type_province {
  deep_sea,
  sea,
  coastal_sea,
  coast,
  grassland,
  forest,
  tropical_forest,
  desert,
  temperate_desert,
  hill,
  tropical,
  mountain,
  tundra,
};

class country;
class province {
private:
  vector<population> populations;
  uint id;
  string name;
  uint population_size;
  float latitude;
  float longitude;
  float height;
  type_province type;
  country* country_owner;
  float migration_atraction;
  float tax_control;
  vector<pair<int, province*>> neighbours;
  typedef struct {
    int k;
  } buildings;

public:
  province() {};
  province(uint id, string name, uint population_size, float latitude, float longitude, float height, type_province type)
  {
    this->id = id;
    this->name = name;
    this->population_size = population_size;
    this->latitude = latitude;
    this->longitude = longitude;
    this->country_owner = country_owner;
    this->migration_atraction = 0;
    this->tax_control = 0;
    this->height = height;
    this->type = type;

  }
  ~province() {};
  string get_name();
  uint get_id();
  uint get_population();
  float get_latitude();
  float get_longitude();
  country* get_country();
  type_province get_type();
  void set_country(country* country_owner);
  void add_neighbour(uint16_t cost, province* p);
  float get_migration_atraction();
  float get_tax_control();
  void print_neighbours();
  bool is_neighbour(province* p);
  void set_migration_atraction(float migration_atraction);
  void set_tax_control(float tax_control);
  vector<pair<int, province*>> get_neighbours();
  void find_path(province* p);
  friend ostream& operator<<(ostream& os, const province& p);

};
