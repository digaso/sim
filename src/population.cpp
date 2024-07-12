#include "population.hpp"

Population::Population() {}

string get_class_string(population_class clss) {
  if (clss == population_class::slaves) return "slaves";
  if (clss == population_class::burghers) return "burghers";
  if (clss == population_class::peasants) return "peasants";
  if (clss == population_class::monks) return "monks";
  if (clss == population_class::nobles) return "nobles";
  return "no_class";
}

Population::Population(uint id, uint size, uint country_id, uint province_id, uint culture_id, population_class pop_class, uint religion_id, World* w)
{
  this->id = id;
  this->size = size;
  this->country_id = country_id;
  this->province_id = province_id;
  this->culture_id = culture_id;
  this->pop_class = pop_class;
  this->religion_id = religion_id;
  string class_name = get_class_string(pop_class);
  string culture_name = w->getCultureById(culture_id)->get_name();
  string religion_name = w->getReligionById(religion_id)->get_name();
  this->name = class_name + " " + culture_name + " " + religion_name;

}

Population::~Population() {}

string Population::get_name()
{
  return this->name;
}

uint Population::getId()
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

void Population::update(World* w)
{
  //handle consumption
  Province* province = w->getProvinceById(this->province_id);
  Culture culture = w->getCultures().at(this->culture_id);
  vector<pair<uint, float>> consumption = culture.get_class_consumption(this->pop_class);

  float temp_happiness = this->population_happiness;
  float temp_loyalty = this->population_loyalty;
  float temp_militancy = this->population_militancy;
  float temp_growth = this->population_growth;
  //TODO: implement market
  //Market* market = province->get_market(w);
  //for (uint i = 0; i < consumption.size(); i++) {
  //  uint good_id = consumption[ i ].first;
  //  cout << "olá" << endl;
  //  uint amount = consumption[ i ].second;
  //  cout << "olá" << endl;
  //  market->updateDemand(good_id, amount);
  //  cout << "olá" << endl;
  //}

  //handle growth
  this->population_happiness = this->get_population_happiness(w);
  this->population_growth = this->get_population_growth(w);
  this->population_loyalty = this->get_population_loyalty(w);


  if (population_loyalty < 0.4f) {
    this->population_militancy += 0.05f;
  }
  else if (population_loyalty > 0.6f) {
    this->population_militancy -= 0.05;
    this->population_militancy = population_militancy < 0.0f ? 0.0f : population_militancy;
  }
  else {
    this->population_militancy += 0.0f;
  }
  this->size += this->size * this->population_growth;
  this->size = this->size < 0 ? 0 : this->size;


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
  else if (this->pop_class == population_class::burghers) {
    growth = 0.02f;
  }
  else if (this->pop_class == population_class::nobles) {
    growth = 0.03f;
  }
  return growth + 1;

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
  else if (this->pop_class == population_class::burghers) {
    happiness = 0.02f;
  }
  else if (this->pop_class == population_class::nobles or this->pop_class == population_class::monks) {
    happiness = 0.03f;
  }
  return happiness;

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
  else if (this->pop_class == population_class::burghers) {
    loyalty = 0.02f;
  }
  else if (this->pop_class == population_class::nobles) {
    loyalty = 0.03f;
  }
  return loyalty;
}