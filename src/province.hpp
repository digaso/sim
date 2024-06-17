#pragma once
#include <string>
#include "population.hpp"
#include "economy/good.hpp"
#include "economy/market.hpp"
#include "configs.h"
#include <vector>

using namespace std;

class Population;

typedef struct buildings_stats {
  uint_fast8_t id;
  uint_fast8_t amount;
  Ownership owner;
} BuildingStats;

class Country;
class Province {
private:
  vector<Population> pops; //vector of populations
  uint id; //id of province
  string name; //name of province
  uint y;
  uint x;
  int region_id = -1; //id of region
  uint baron_id; //id of baron
  float height; //value between -1 and 1
  float moisture; //value between -1 and 1
  type_province type; //type of province
  int country_owner_id; //id to country that owns the province
  float migration_atraction; //value between 0 and 1
  uint infrastructure;
  vector<uint_fast8_t> goods; //id of goods
  vector<BuildingStats> buildings; //id of buildings


public:
  Province() {};
  Province(uint id, string name, uint population_size, int y, int x, float height, type_province type, float moisture, World* w);
  ~Province() {};
  string get_name();
  uint getId();
  uint get_baron_id();
  void set_baron_id(uint id);
  int get_y();
  int get_x();
  type_province get_type();
  void set_region_id(int id);
  int get_region_id();
  float get_moisture();
  uint get_population_size() const;
  int get_country_owner_id() const;
  void set_country_owner_id(uint id);
  float get_migration_atraction();
  float get_tax_control();
  float get_height();
  void set_type(type_province type);
  void set_migration_atraction(float migration_atraction);
  static string type_province_to_string(type_province type);
  void add_goods(uint_fast8_t good_id);
  vector<uint_fast8_t> get_goods();
  friend ostream& operator<<(ostream& os, const Province& p);
  void add_building(uint_fast8_t building_id);
  vector<BuildingStats> getBuildingStats();
  void add_population(Population pop);
  float get_populations_growth();
  float get_populations_happiness();
  bool is_land();
  Market* get_market(World* w);
  void set_infrastructure(uint infrastructure);
  uint get_infrastructure();
  uint get_building_amount(uint_fast8_t building_id);
  vector<Population>* get_pops();
  void updatePopulation(World* w);

};
