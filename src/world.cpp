#include "world.hpp"

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
    cout << row.print() << endl;
  }
}

void World::addCharacter(character* c) {
  for (auto row : this->countries) {
    if (row.get_id() == c->get_country_living()->get_id()) {
      row.add_character(c);
    }
  }
}
