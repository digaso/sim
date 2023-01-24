#include "province.hpp"

using namespace std;


string province::get_name()
{
  return this->name;
}


country* province::get_country()
{
  return this->country_owner;
}

void province::set_country(country* country_owner)
{
  this->country_owner = country_owner;
}

uint province::get_id()
{
  return this->id;
}

vector<pair<int, province*>> province::get_neighbours()
{
  return this->neighbours;
}

uint province::get_population()
{
  return this->population_size;
}

float province::get_latitude()
{
  return this->latitude;
}

float province::get_longitude()
{
  return this->longitude;
}


float province::get_migration_atraction()
{
  return this->migration_atraction;
}

float province::get_tax_control()
{
  return this->tax_control;
}

void province::set_migration_atraction(float migration_atraction)
{
  this->migration_atraction = migration_atraction;
}

void province::set_tax_control(float tax_control)
{
  this->tax_control = tax_control;
}


void province::print_neighbours()
{
  cout << "Neighbours of " << this->get_name() << endl;
  for (auto item : this->neighbours) {
    cout << item.second->get_name() << " " << item.first << " Days" << endl;
  }
  cout << "End;" << endl;
}
bool province::is_neighbour(province* p)
{
  for (auto item : this->neighbours) {
    if (item.second->get_id() == p->get_id())
      return true;
  }
  return false;
}
void province::add_neighbour(uint16_t cost, province* p)
{

  if (this->is_neighbour(p))
    return;
  pair<int, province*> pair = make_pair(cost, p);
  this->neighbours.push_back(pair);
  p->add_neighbour(cost, this);
}

void find_path(province* p)
{
  cout << "Finding path to " << p->get_name() << endl;
}

ostream& operator<<(ostream& os, const province& p)
{
  os << "Province: " << p.name << " Population: " << p.population_size << " Country: " << p.country_owner->get_name() << " Latitude: " << p.latitude << " Longitude: " << p.longitude;
  return os;
}