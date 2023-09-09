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
  uint num_rows;
  uint num_cols;
  date world_date;
  Province* provinces;
  vector<Country> countries;
  vector<Character> characters;
  vector<Religion> religions;
  vector<Good> goods;
public:
  World(uint8_t day, uint8_t month, uint year, uint cols, uint rows);
  ~World();
  vector<Province*> getLandNeighbours(Province* p);
  const date getDate() const;
  const string to_string() const;
  string getDateString();
  void setDate(date d);
  void addProvince(Province p, uint x, uint y);
  void addCountry(Country c);
  void addCharacter(Character c);
  void printCountries();
  void setupWorld();
  void addGood(Good g);
  void addReligion(Religion r);
  Good* getGoodById(uint id);
  bool* getGoodMapById(uint id) {
    return this->goods.at(id).get_map();
  }
  void setGoodMapById(uint id, bool* map) {
    this->goods.at(id).set_map(map);
  }
  bool advanceDate();
  Province* getProvinceByCoords(uint x, uint y);
  Country* getCountryById(uint id) {
    if (id < countries.size()) {
      return &countries.at(id);
    }

    return nullptr;
  }
  Province* getProvinceById(uint id);
  Province* getProvinces();
  const vector<Country> getCountries() const;
  void set_num_rows(uint num_rows) {
    this->num_rows = num_rows;
  }
  void set_num_cols(uint num_cols) {
    this->num_cols = num_cols;
  };
  uint get_num_rows() {
    return this->num_rows;
  }
  uint get_num_cols() {
    return this->num_cols;
  }
  vector<Good> getGoods() {
    return this->goods;
  }
  void printProvinces();
  void printCharacters();
  void printReligions();
  Religion* getReligionById(uint id);
  vector<Province*> get_path_between_provinces(uint start_id, uint end_id);
};
