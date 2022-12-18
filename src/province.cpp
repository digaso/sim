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

vector<province*> province::get_neighbours()
{
  return this->neighbours;
}

void province::print_neighbours()
{
  cout << "Neighbours of " << this->get_name() << endl;
  for (province* p : this->neighbours) {
    cout << p->get_id() << " " << p->get_name() << endl;
  }
  cout << "End;" << endl;
}

void province::add_neighbour(province* p)
{

  for (province* neigh : this->neighbours) {
    if (neigh->get_id() == p->get_id()) {
      return;
    }
  }
  this->neighbours.push_back(p);
  p->add_neighbour(this);
}
