#pragma once
#include <string>
#include "population.hpp"
#include "country.hpp"
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
  vector<population> populations;
  types_of_province type_of_province;
  uint id;
  string name;
  uint population_size;
  float latitude;
  float longitude;
  country* country_owner;
  float migration_atraction;
  float tax_control;
  vector<pair<int, province*>> neighbours;
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
  country* get_country();
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

};
