#pragma once
#include "province.hpp"

string province::get_name()
{
  return this->name;
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