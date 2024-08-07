#include "culture.hpp"

Culture::Culture(string name, uint id) {
  this->name = name;
  this->id = id;
}

string Culture::get_name() {
  return this->name;
}

uint Culture::getId() {
  return this->id;
}

vector<uint> Culture::get_homelands() {
  return this->homelands;
}

vector<uint> Culture::get_goods_obsession() {
  return this->goods_obsession;
}

PopConsumption Culture::get_pop_consumption() {
  return this->pop_consumption;
}

void Culture::set_homelands(vector<uint> homelands) {
  this->homelands = homelands;
}

void Culture::set_goods_obsession(vector<uint> goods_obsession) {
  this->goods_obsession = goods_obsession;
}

void Culture::set_pop_consumption(PopConsumption pop_consumption) {
  this->pop_consumption = pop_consumption;
}

vector<pair<uint, float>> Culture::get_class_consumption(population_class pop_class) {
  switch (pop_class) {
  case slaves:
    return this->pop_consumption.slaves_consumption;
  case peasants:
    return this->pop_consumption.peasants_consumption;
  case burghers:
    return this->pop_consumption.burghers_consumption;
  case monks:
    return this->pop_consumption.monks_consumption;
  case nobles:
    return this->pop_consumption.nobles_consumption;
  }
}


PopConsumption Culture::generate_pop_consumption(World* w, uint country_id) {
  PopConsumption pop_consumption;
  Country* country = w->getCountryById(country_id);



  //left: good id, right:consumption
  pop_consumption.slaves_consumption = { {grain,0.15} ,{fish, 0.2},  {clothes, 0.2} };
  pop_consumption.peasants_consumption = { {grain,0.22}, {salt, 0.2}, {fish, 0.25},  {clothes, 0.3} , {tea,0.2}, {tobacco, 0.15} };
  pop_consumption.burghers_consumption = { {grain,0.4}, {wine, 0.5}, {salt, 0.4}, {fish, 0.7},  {clothes, 0.4}, {tea,0.4}, {spices,0.55} };
  pop_consumption.monks_consumption = { {grain,0.8}, {wine, 0.7}, {salt, 0.5}, {fish, 0.8},  {clothes, 0.4}, {tea,0.4}, {spices,0.45} };
  pop_consumption.nobles_consumption = { {grain,1.0}, {wine, 0.9}, {salt, 0.9}, {fish, 0.9},  {clothes, 0.9} , {tea,0.65}, {spices,0.85}, {gems, 0.5} };

  return pop_consumption;
}