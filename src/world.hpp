#pragma once
#include "country.hpp"
#include "province.hpp"
#include "date.hpp"
#include <vector>
#include <sstream>
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
  void printCountries();
  country* getCountryById(uint id) {

    if (id < countries.size()) {
      return &countries.at(id);
    }

    return nullptr;
  }
  country* getCountryByAbrev(string abrev) {
    for (auto row : countries) {
      if (row.get_abrev() == abrev) {
        country* c = &row;
        return c;
      }
    }
    return nullptr;
  }
  const vector<province> getProvinces() const;
  const vector<country> getCountries() const;
};

World::World(int day, int month, int year)
{
  this->world_date = date(day, month, year);
}

World::~World()
{
}
const string World::to_string() const
{
  ostringstream os;
  os << "World date: " << this->world_date.day() << "-" << world_date.month() << "-" << world_date.year();
  return os.str();
}
const date World::getDate() const
{
  return this->world_date;
}

void World::setDate(date d)
{
  this->world_date = d;
}

void World::addProvince(province p)
{
  this->provinces.push_back(p);
}

void World::addCountry(country c)
{
  this->countries.push_back(c);
}

const vector<province> World::getProvinces() const
{
  return this->provinces;
}

const vector<country> World::getCountries() const
{
  return this->countries;
}


void World::printCountries() {
  for (auto row : this->countries) {
    cout << row.get_name() << endl;
  }
}