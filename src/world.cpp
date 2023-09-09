#include "world.hpp"
#include "economy/good.hpp"



World::World(uint8_t day, uint8_t month, uint year, uint cols, uint rows)
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

Province* World::getProvinceByCoords(uint x, uint y)
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

void World::addReligion(Religion r)
{
  this->religions.push_back(r);
}

vector<Province*> World::getLandNeighbours(Province* p)
{
  vector<Province*> neighbours;
  int x = p->get_x();
  int y = p->get_y();
  //check cardinal directions
  if (x < this->num_cols - 1 && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y));
  }
  if (y > 0 && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y - 1));
  }
  if (x > 0 && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y));
  }
  if (y < this->num_rows - 1 && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y + 1));
  }
  //check diagonals
  //if (x > 0 && y > 0 && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::deep_sea) {
  //  neighbours.push_back(this->getProvinceByCoords(x - 1, y - 1));
  //}
  //if (x < this->num_cols - 1 && y > 0 && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::deep_sea) {
  //  neighbours.push_back(this->getProvinceByCoords(x + 1, y - 1));
  //}
  //if (x > 0 && y < this->num_rows - 1 && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::deep_sea) {
  //  neighbours.push_back(this->getProvinceByCoords(x - 1, y + 1));
  //}
  //if (x < this->num_cols - 1 && y < this->num_rows - 1 && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::deep_sea) {
  //  neighbours.push_back(this->getProvinceByCoords(x + 1, y + 1));
  //}
  return neighbours;
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

vector<Province*> World::get_path_between_provinces(uint start_id, uint end_id) {
  vector<Province*> path;
  vector<uint> visited;
  queue<uint> q;
  q.push(start_id);
  visited.push_back(start_id);
  return path;
}

Religion* World::getReligionById(uint id) {
  if (id < religions.size()) {
    return &religions.at(id);
  }
  return nullptr;
}

void World::printReligions() {
  for (auto row : this->religions) {
    cout << row.print() << endl;
  }
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

