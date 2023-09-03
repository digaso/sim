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
#include "religion.hpp"

using namespace std;

class Good;

class World
{
private:
  /* data */
  int num_rows;
  int num_cols;
  date world_date;
  Province* provinces;
  vector<Country> countries;
  vector<character> characters;
  vector<Religion> religions;
  vector<Good> goods;
public:
  World(uint8_t day, uint8_t month, uint8_t year, uint cols, uint rows);
  ~World();
  vector<Province*> getNeighbours(Province* p);
  const date getDate() const;
  const string to_string() const;
  string getDateString();
  void setDate(date d);
  void addProvince(Province p, uint x, uint y);
  void addCountry(Country c);
  void addCharacter(character c);
  void printCountries();
  void setupWorld();
  void addGood(Good g);
  Good* getGoodById(uint id);
  bool* getGoodMapById(uint id) {
    return this->goods.at(id).get_map();
  }
  void setGoodMapById(uint id, bool* map) {
    this->goods.at(id).set_map(map);
  }
  bool advanceDate();
  Province* getProvinceByCoords(uint8_t x, uint8_t y);
  Country* getCountryById(uint id) {
    if (id < countries.size()) {
      return &countries.at(id);
    }

    return nullptr;
  }
  Province* getProvinceById(uint id);
  Province* getProvinces();
  const vector<Country> getCountries() const;
  void set_num_rows(int num_rows) {
    this->num_rows = num_rows;
  }
  void set_num_cols(int num_cols) {
    this->num_cols = num_cols;
  };
  int get_num_rows() {
    return this->num_rows;
  }
  int get_num_cols() {
    return this->num_cols;
  }
  vector<Good> getGoods() {
    return this->goods;
  }
  void printProvinces();
  vector<Province*> get_path_between_provinces(uint start, uint end);
};
