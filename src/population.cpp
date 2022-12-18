#include "population.hpp"

string population::get_name()
{
  return this->name;
}

uint population::get_id()
{
  return this->id;
}

uint population::get_size()
{
  return this->size;
}

uint population::get_country_id()
{
  return this->country_id;
}

uint population::get_province_id()
{
  return this->province_id;
}