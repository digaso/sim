#include "population.hpp"

string Population::get_name()
{
  return this->name;
}

uint Population::get_id()
{
  return this->id;
}

uint Population::get_size()const
{
  return this->size;
}

uint Population::get_country_id()
{
  return this->country_id;
}

uint Population::get_province_id()
{
  return this->province_id;
}