#include "population.hpp"

Population::Population() {}

Population::Population(uint id, uint size, uint country_id, uint province_id, uint culture_id, population_class pop_class)
{
  this->id = id;
  this->size = size;
  this->country_id = country_id;
  this->province_id = province_id;
  this->culture_id = culture_id;
  this->pop_class = pop_class;
}

Population::~Population() {}

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

uint Population::get_culture_id()
{
  return this->culture_id;
}

float Population::get_population_growth(World* world)
{
  Province* province = world->getProvinceById(this->province_id);
  Culture culture = world->getCultures().at(this->culture_id);
  float growth = 0.0f;
  if (this->pop_class == population_class::slaves) {
    growth = 0.0f;
  }
  else if (this->pop_class == population_class::peasants) {
    growth = 0.01f;
  }
  else if (this->pop_class == population_class::citizens) {
    growth = 0.02f;
  }
  else if (this->pop_class == population_class::elite) {
    growth = 0.03f;
  }

}

float Population::get_population_happiness(World* world)
{
  Province* province = world->getProvinceById(this->province_id);
  Culture culture = world->getCultures().at(this->culture_id);
  float happiness = 0.0f;
  if (this->pop_class == population_class::slaves) {
    happiness = 0.0f;
  }
  else if (this->pop_class == population_class::peasants) {
    happiness = 0.01f;
  }
  else if (this->pop_class == population_class::citizens) {
    happiness = 0.02f;
  }
  else if (this->pop_class == population_class::elite) {
    happiness = 0.03f;
  }

}

float Population::get_population_loyalty(World* world)
{
  Province* province = world->getProvinceById(this->province_id);
  Culture culture = world->getCultures().at(this->culture_id);
  float loyalty = 0.0f;
  if (this->pop_class == population_class::slaves) {
    loyalty = 0.0f;
  }
  else if (this->pop_class == population_class::peasants) {
    loyalty = 0.01f;
  }
  else if (this->pop_class == population_class::citizens) {
    loyalty = 0.02f;
  }
  else if (this->pop_class == population_class::elite) {
    loyalty = 0.03f;
  }

}