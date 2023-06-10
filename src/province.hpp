#pragma once
#include <string>
#include "population.hpp"
#include "country.hpp"
#include "economy/good.hpp"
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
  coastal_desert = 15,
};

class country;
class Province {
private:
  vector<population> populations; //vector of populations
  uint id; //id of province
  string name; //name of province
  uint population_size; //population size
  float y;
  float x;
  float height; //value between -1 and 1
  float moisture; //value between -1 and 1
  type_province type; //type of province
  country* country_owner; //pointer to country that owns the province
  float migration_atraction; //value between 0 and 1
  float tax_control; //value between 0 and 1
  bool trade_route_candidate = false; //becomes true if province has a marketplace or a port
  vector<uint_fast8_t> goods; //id of goods
  vector<uint_fast8_t> buildings; //id of buildings


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
    this->tax_control = 0.5;
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
  float get_moisture();
  void set_country(country* country_owner);
  float get_migration_atraction();
  float get_tax_control();
  float get_height();
  void set_migration_atraction(float migration_atraction);
  void set_tax_control(float tax_control);
  static string type_province_to_string(type_province type);
  void add_goods(uint_fast8_t good_id);
  friend ostream& operator<<(ostream& os, const Province& p);

};
