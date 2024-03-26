#pragma once
#include <string>
#include "world.hpp"
#include "culture.hpp"
#include "configs.h"


#define POPULATION_HAPPINESS  1.f
#define POPULATION_LOYALTY  1.f
#define POPULATION_MILITANCY 1.f


using namespace std;


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
  uint religion_id;
  float population_growth;
  float population_happiness;
  float population_loyalty;
  float population_militancy;

public:
  Population();
  Population(uint id, uint size, uint country_id, uint province_id, uint culture_id, population_class pop_class, uint religion_id, World* w);
  ~Population();
  string get_name();
  uint get_id();
  uint get_size() const;
  uint get_country_id();
  uint get_province_id();
  uint get_culture_id();
  float get_population_growth(World* world);
  void update(World* world);
  float get_population_happiness(World* world);
  float get_population_loyalty(World* world);
  float get_population_militancy(World* world);
  Population set_culture_id(uint culture_id, uint size);

};
