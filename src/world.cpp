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
  this->map.push_back(graph_node{ p.get_id(),vector<pair<uint, province*>>() });
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

void World::addCharacter(character c) {
  country* ctry = c.get_country_living();
  if (ctry != nullptr) {
    ctry->add_character(c);
  }
}

vector<province*> World::get_path_between_provinces(uint start, uint end) {
  vector<province*> path;
  vector<uint> visited;
  queue<uint> q;
  q.push(start);
  visited.push_back(start);
  return path;
}

void World::advanceDate() {
  this->world_date++;
}