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

void World::addProvince(Province p)
{
  this->provinces.push_back(p);
}

void World::addCountry(country c)
{
  this->countries.push_back(c);
}

const vector<Province> World::getProvinces() const
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

vector<Province*> World::get_path_between_provinces(uint start, uint end) {
  vector<Province*> path;
  vector<uint> visited;
  queue<uint> q;
  q.push(start);
  visited.push_back(start);
  return path;
}

void World::printNeighbours(uint id) {
  Province* p = this->getProvinceById(id);
  int x = p->get_x();
  int y = p->get_y();
  for (Province& neighbor : this->provinces) {
    if (neighbor.get_x() >= x - 1 && neighbor.get_x() <= x + 1 &&
      neighbor.get_y() >= y - 1 && neighbor.get_y() <= y + 1 &&
      !(neighbor.get_x() == x && neighbor.get_y() == y)) {
      cout << neighbor.get_name() << endl;
    }
  }
}

vector<int> World::getNeighbours(uint id) {
  vector<int> neighbours;
  Province* p = this->getProvinceById(id);
  int x = p->get_x();
  int y = p->get_y();
  for (Province& neighbor : this->provinces) {
    if (neighbor.get_x() >= x - 1 && neighbor.get_x() <= x + 1 &&
      neighbor.get_y() >= y - 1 && neighbor.get_y() <= y + 1 &&
      !(neighbor.get_x() == x && neighbor.get_y() == y)) {
      neighbours.push_back(neighbor.get_id());
    }
  }
  return neighbours;
}
void World::advanceDate() {
  this->world_date++;
}