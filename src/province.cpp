#include "province.hpp"
#include "future"

using namespace std;

Province::Province(uint id, string name, uint population_size, int y, int x, float height, type_province type, float moisture, World* w)
{
  this->id = id;
  this->name = name;
  this->y = y;
  this->x = x;
  this->country_owner_id = -1;
  this->migration_atraction = 0;
  this->infrastructure = 10;
  this->height = height;
  this->type = type;
  this->moisture = moisture;
}

rank_province Province::upgrade_rank()
{
  if (this->rank == village)
  {
    this->rank = town;
  }
  else if (this->rank == town)
  {
    this->rank = city;
  }
  return this->rank;
}

rank_province Province::downgrade_rank()
{
  if (this->rank == city)
  {
    this->rank = town;
  }
  else if (this->rank == town)
  {
    this->rank = village;
  }
  return this->rank;
}

void Province::set_infrastructure(uint infrastructure)
{
  this->infrastructure = infrastructure;
}

vector<BuildingStats> Province::getBuildingStats()
{
  return this->buildings;
}

uint Province::get_infrastructure()
{
  return this->infrastructure;
}

string Province::get_name()
{
  return this->name;
}

void Province::set_country_owner_id(uint id)
{
  this->country_owner_id = id;
}

int Province::get_country_owner_id() const
{
  return this->country_owner_id;
}

void Province::set_region_id(int id)
{
  this->region_id = id;
}

int Province::get_region_id()
{
  return this->region_id;
}

bool Province::is_land()
{
  return this->type != deep_sea && this->type != sea && this->type != coastal_sea;
}

uint Province::get_population_size() const
{
  uint population_size = 0;
  for (auto& p : this->pops)
  {
    population_size += p.get_size();
  }
  return population_size;
}


uint Province::getId()
{
  return this->id;
}


int Province::get_y()
{
  return this->y;
}

type_province Province::get_type()
{
  return this->type;
}

int Province::get_x()
{
  return this->x;
}

float Province::get_height()
{
  return this->height;
}

float Province::get_moisture()
{
  return this->moisture;
}

vector<uint_fast8_t> Province::get_goods()
{
  return this->goods;
}

void Province::add_goods(uint_fast8_t good_id)
{
  this->goods.push_back(good_id);
}

float Province::get_migration_atraction()
{
  return this->migration_atraction;
}

void Province::set_migration_atraction(float migration_atraction)
{
  this->migration_atraction = migration_atraction;
}


void Province::add_population(Population pop)
{
  this->pops.push_back(pop);
}

vector<Population>* Province::get_pops()
{
  return &(this->pops);
}

void Province::add_building(uint_fast8_t building_id)
{
  for (auto& b : this->buildings)
  {
    if (b.id == building_id)
    {
      b.amount++;
      return;
    }
  }
  Ownership owner = { true, this->country_owner_id };
  this->buildings.push_back({ building_id, 1, owner });
}

void Province::set_type(type_province type)
{
  this->type = type;
}

uint Province::get_building_amount(uint_fast8_t building_id)
{
  for (auto& b : this->buildings)
  {
    if (b.id == building_id)
    {
      return b.amount;
    }
  }
  return 0;
}

Market* Province::get_market(World* w)
{
  Country* country = w->getCountryById(this->country_owner_id);
  vector<Market>* markets = country->get_markets();
  for (auto& m : *markets)
  {
    if (m.has_province(this->id))
    {
      return &m;
    }
  }
  return nullptr;
}

void Province::updatePopulation(World* w)
{
  for (auto& p : this->pops)
  {
    p.update(w);
  }
}

ostream& operator<<(ostream& os, const Province& p)
{
  os << "Province: " << p.name << " Population: " << p.get_population_size() << " Country: " << p.get_country_owner_id() << " Latitude: " << p.y << " Longitude: " << p.x;
  return os;
}
