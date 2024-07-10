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
    return this->pop_consumption.citizens_consumption;
  case nobles:
    return this->pop_consumption.elite_consumption;
  }
}


PopConsumption Culture::generate_pop_consumption(World* w, uint country_id) {
  PopConsumption pop_consumption;
  Country* country = w->getCountryById(country_id);



  //left good id and right consumption
  pop_consumption.slaves_consumption = { {0,0.3} ,{3, 0.5},  {5, 0.3} };
  pop_consumption.peasants_consumption = { {0,0.6}, {2, 0.7}, {3, 0.4},  {5, 0.6} , {10,0.4} };
  pop_consumption.citizens_consumption = { {0,0.6}, {1, 0.5}, {2, 0.5}, {3, 0.9},  {5, 0.4}, {10,0.3}, {24,0.4} };
  pop_consumption.elite_consumption = { {0,0.8}, {1, 0.5}, {2, 0.6}, {3, 0.6},  {5, 0.4} , {10,0.95}, {24,0.74} };

  return pop_consumption;
}