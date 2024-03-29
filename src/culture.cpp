#include "culture.hpp"

Culture::Culture(string name, uint id) {
  this->name = name;
  this->id = id;
}

string Culture::get_name() {
  return this->name;
}

uint Culture::get_id() {
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

vector<pair<uint, uint>> Culture::get_class_consumption(population_class pop_class) {
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
  //left good id and right consumption
  pop_consumption.slaves_consumption = { {0,2} ,{3, 2},  {5, 1} };
  pop_consumption.peasants_consumption = { {0,2}, {2, 1}, {3, 2},  {5, 1} , {10,1} };
  pop_consumption.citizens_consumption = { {0,1}, {1, 1}, {2, 1}, {3, 2},  {5, 1}, {10,1}, {24,1} };
  pop_consumption.elite_consumption = { {0,1}, {1, 1}, {2, 1}, {3, 2},  {5, 1} , {10,2}, {24,2} };

  return pop_consumption;
}