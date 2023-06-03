#pragma once
#include <sstream>
#include <vector>
#include "utils/date.hpp"
#include <utility>
#include "country.hpp"
#include <queue>
#include <list>

using namespace std;
struct graph_node {
  uint id;
  vector<pair<uint, Province*>> neighbours;
};

class World
{
private:
  /* data */
  date world_date;
  typedef list<graph_node> Map;
  Map map;
  vector<Province> provinces;
  vector<country> countries;
public:
  World(int year, int month, int day);
  ~World();
  const date getDate() const;
  const string to_string() const;
  void setDate(date d);
  void addProvince(Province p);
  void addCountry(country c);
  void addCharacter(character c);
  void printCountries();
  void setupWorld();
  void advanceDate();
  country* getCountryById(uint id) {

    if (id < countries.size()) {
      return &countries.at(id);
    }

    return nullptr;
  }

  country* getCountryByAbrev(string abrev) {
    uint i = 0;
    for (auto row : countries) {

      if (row.get_abrev() == abrev) {
        return &countries.at(i);
      }
      i++;
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
  void printProvinces() {
    for (auto row : this->provinces) {
      cout << row.get_name() << endl;
    }
  }
  vector<Province*> get_path_between_provinces(uint start, uint end);
};
