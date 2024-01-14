#pragma once
#include <string>
#include "culture.hpp"

using namespace std;

enum population_class {
  slaves,
  peasants,
  citizens,
  elite
};


class Population
{
private:
  uint id;
  string name;
  uint size;
  population_class pop_class;
  uint country_id;
  uint province_id;
  uint culture_id;
public:
  Population() {}
  Population(uint id, uint size, uint country_id, uint province_id, uint culture_id, population_class pop_class)
  {
    this->id = id;
    this->size = size;
    this->country_id = country_id;
    this->province_id = province_id;
    this->culture_id = culture_id;
    this->pop_class = pop_class;
  }
  ~Population() {}
  string get_name();
  uint get_id();
  uint get_size() const;
  uint get_country_id();
  uint get_province_id();
  uint get_culture_id();
  Population set_culture_id(uint culture_id, uint size);

};
