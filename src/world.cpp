#include "world.hpp"
#include "economy/good.hpp"



World::World(uint8_t day, uint8_t month, uint8_t year, uint cols, uint rows)
{
  this->world_date = date(day, month, year);
  provinces = new Province[ cols * rows ];
  this->num_cols = cols;
  this->num_rows = rows;
  Good good;
  good.set_goods(this);
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

Good* World::getGoodById(uint id)
{
  if (id < goods.size()) {
    return &goods.at(id);
  }
  return nullptr;
}

Province* World::getProvinceByCoords(uint8_t x, uint8_t y)
{

  return &provinces[ (y * this->num_cols) + x ];
}

Province* World::getProvinceById(uint id)
{

  return &provinces[ id ];
}

string World::getDateString()
{
  ostringstream os;
  os << this->world_date.day() << "-" << world_date.month() << "-" << world_date.year();
  return os.str();
}

void World::setDate(date d)
{
  this->world_date = d;
}

void World::addProvince(Province p, uint x, uint y)
{
  this->provinces[ (y * this->num_cols) + x ] = p;
}

void World::addCountry(Country c)
{
  this->countries.push_back(c);
}

Province* World::getProvinces()
{
  return this->provinces;
}



const vector<Country> World::getCountries() const
{
  return this->countries;
}

void World::printCountries() {
  for (auto row : this->countries) {
    cout << row.print() << endl;
  }
}

void World::addCharacter(character c) {
  Country* ctry = c.get_country_living();
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




void World::addGood(Good g) {
  this->goods.push_back(g);
}

bool World::advanceDate() {
  int month = this->world_date.month();
  this->world_date++;
  if (month != this->world_date.month()) {
    return true;
  }
  return false;
}

