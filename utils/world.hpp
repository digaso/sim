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
  vector<Province> provinces;
  vector<Country> countries;
public:
  World(int year, int month, int day);
  ~World();
  const date getDate() const;
  const string to_string() const;
  void setDate(date d);
  void addProvince(Province p);
  void addCountry(Country c);
  const vector<Province> getProvinces() const;
};
ostream& operator << (ostream& os, const World& w);

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

void World::addProvince(Province p)
{
  this->provinces.push_back(p);
}

void World::addCountry(Country c)
{
  this->countries.push_back(c);
}

const vector<Province> World::getProvinces() const
{
  return this->provinces;
}