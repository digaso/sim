#pragma once
#include <sstream>
#include <vector>
#include "utils/date.hpp"
#include <utility>
#include "country.hpp"
#include <queue>
#include <list>
#include "economy/trade_route.hpp"
#include "economy/good.hpp"

using namespace std;

struct graph_node {
  uint id;
  vector<pair<uint, Province*>> neighbours;
};

class Good;

class World
{
private:
  /* data */
  uint8_t num_rows;
  uint8_t num_cols;
  date world_date;
  vector<Province> provinces;
  vector<country> countries;
  vector<character> characters;
  vector<Good> goods;
public:
  World(int year, int month, int day);
  ~World();
  const date getDate() const;
  const string to_string() const;
  string getDateString();
  void setDate(date d);
  void addProvince(Province p);
  void addCountry(country c);
  void addCharacter(character c);
  void printCountries();
  void setupWorld();
  void addGood(Good g);
  Good* getGoodById(uint id);
  bool advanceDate();
  void printNeighbours(uint id);
  vector<int> getNeighbours(uint id);
  Province* getProvinceByCoords(uint8_t x, uint8_t y);
  country* getCountryById(uint id) {

    if (id < countries.size()) {
      return &countries.at(id);
    }

    return nullptr;
  }
  Province* getProvinceById(uint id) {
    if (id < provinces.size()) {
      return &provinces.at(id);
    }
    return nullptr;
  }
  const vector<Province> getProvinces() const;
  const vector<country> getCountries() const;
  void set_num_rows(uint8_t num_rows) {
    this->num_rows = num_rows;
  }
  void set_num_cols(uint8_t num_cols) {
    this->num_cols = num_cols;
  };
  vector<Good> getGoods() {
    return this->goods;
  }
  void printProvinces() {
    for (auto row : this->provinces) {
      cout << row.get_id() << " " << row.get_name() << " " << row.type_province_to_string(row.get_type()) << endl;
    }
  }
  vector<Province*> get_path_between_provinces(uint start, uint end);
};
