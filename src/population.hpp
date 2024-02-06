#pragma once
#include <string>
#include "world.hpp"
#include "culture.hpp"

#define POPULATION_HAPPINESS cap 1.f
#define POPULATION_LOYALTY cap 1.f
#define POPULATION_MILITANCY cap 1.f


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
  float population_growth;
  float population_happiness;
  float population_loyalty;
  float population_militancy;

public:
  Population();
  Population(uint id, uint size, uint country_id, uint province_id, uint culture_id, population_class pop_class);
  ~Population();
  string get_name();
  uint get_id();
  uint get_size() const;
  uint get_country_id();
  uint get_province_id();
  uint get_culture_id();
  float get_population_growth(World* world);
  float get_population_happiness(World* world);
  float get_population_loyalty(World* world);
  float get_population_militancy(World* world);
  Population set_culture_id(uint culture_id, uint size);

};
