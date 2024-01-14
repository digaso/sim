#pragma once
#include <string>
#include "population.hpp"
#include "country.hpp"
#include "economy/good.hpp"
#include "economy/market.hpp"
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


typedef struct buildings_stats {
  uint_fast8_t id;
  uint_fast8_t amount;
} BuildingStats;

class Country;
class Province {
private:
  vector<Population> pops; //vector of populations
  uint id; //id of province
  string name; //name of province
  uint y;
  uint x;
  uint baron_id; //id of baron
  float height; //value between -1 and 1
  float moisture; //value between -1 and 1
  type_province type; //type of province
  int country_owner_id; //id to country that owns the province
  float migration_atraction; //value between 0 and 1
  float tax_control; //value between 0 and 1
  bool trade_route_candidate = false; //becomes true if province has a marketplace or a port
  vector<uint_fast8_t> goods; //id of goods
  vector<BuildingStats> buildings; //id of buildings
  Market market;


public:
  Province() {};
  Province(uint id, string name, uint population_size, int y, int x, float height, type_province type, float moisture)
  {
    this->id = id;
    this->name = name;
    this->y = y;
    this->x = x;
    this->country_owner_id = -1;
    this->migration_atraction = 0;
    this->tax_control = 0.5;
    this->height = height;
    this->type = type;
    this->moisture = moisture;
  }
  ~Province() {};
  string get_name();
  uint get_id();
  uint get_baron_id();
  void set_baron_id(uint id);
  int get_y();
  int get_x();
  type_province get_type();
  float get_moisture();
  uint get_population_size() const;
  int get_country_owner_id() const;
  void set_country_owner_id(uint id);
  float get_migration_atraction();
  float get_tax_control();
  float get_height();
  void set_migration_atraction(float migration_atraction);
  void set_tax_control(float tax_control);
  static string type_province_to_string(type_province type);
  void add_goods(uint_fast8_t good_id);
  vector<uint_fast8_t> get_goods();
  friend ostream& operator<<(ostream& os, const Province& p);
  void add_building(uint_fast8_t building_id);
  vector<uint_fast8_t> get_buildings();
  void add_population(Population pop);
  vector<Population>* get_pops();

};
