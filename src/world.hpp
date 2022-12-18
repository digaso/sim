#pragma once
#include <sstream>
#include <vector>
#include "country.hpp"
#include "utils/date.hpp"

class World
{
private:
  /* data */
  date world_date;
  vector<province> provinces;
  vector<country> countries;
public:
  World(int year, int month, int day);
  ~World();
  const date getDate() const;
  const string to_string() const;
  void setDate(date d);
  void addProvince(province p);
  void addCountry(country c);
  void addCharacter(character c);
  void printCountries();
  void setupWorld();
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
  province* getProvinceById(uint id) {
    if (id < provinces.size()) {
      return &provinces.at(id);
    }
    return nullptr;
  }
  const vector<province> getProvinces() const;
  const vector<country> getCountries() const;
  void printProvinces() {
    for (auto row : this->provinces) {
      cout << row.get_name() << endl;
    }
  }

};
