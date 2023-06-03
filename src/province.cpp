#include "province.hpp"

using namespace std;


string Province::get_name()
{
  return this->name;
}


country* Province::get_country()
{
  return this->country_owner;
}

void Province::set_country(country* country_owner)
{
  this->country_owner = country_owner;
}

uint Province::get_id()
{
  return this->id;
}

vector<pair<int, Province*>> Province::get_neighbours()
{
  return this->neighbours;
}

uint Province::get_population()
{
  return this->population_size;
}

float Province::get_latitude()
{
  return this->latitude;
}

type_province Province::get_type()
{
  return this->type;
}

float Province::get_longitude()
{
  return this->longitude;
}


float Province::get_migration_atraction()
{
  return this->migration_atraction;
}

float Province::get_tax_control()
{
  return this->tax_control;
}

void Province::set_migration_atraction(float migration_atraction)
{
  this->migration_atraction = migration_atraction;
}

void Province::set_tax_control(float tax_control)
{
  this->tax_control = tax_control;
}


void Province::print_neighbours()
{
  cout << "Neighbours of " << this->get_name() << endl;
  for (auto item : this->neighbours) {
    cout << item.second->get_name() << " " << item.first << " Days" << endl;
  }
  cout << "End;" << endl;
}
bool Province::is_neighbour(Province* p)
{
  for (auto item : this->neighbours) {
    if (item.second->get_id() == p->get_id())
      return true;
  }
  return false;
}
void Province::add_neighbour(uint16_t cost, Province* p)
{

  if (this->is_neighbour(p))
    return;
  pair<int, Province*> pair = make_pair(cost, p);
  this->neighbours.push_back(pair);
  p->add_neighbour(cost, this);
}

void find_path(Province* p)
{
  cout << "Finding path to " << p->get_name() << endl;
}

ostream& operator<<(ostream& os, const Province& p)
{
  os << "Province: " << p.name << " Population: " << p.population_size << " Country: " << p.country_owner->get_name() << " Latitude: " << p.latitude << " Longitude: " << p.longitude;
  return os;
}