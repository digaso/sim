#pragma once
#include <vector>
#include <string>
#include "population.hpp"
#include "configs.h"

using namespace std;


class CultureCustoms
{
private:
  /* data */
public:
  CultureCustoms(/* args */) {};
  ~CultureCustoms() {};
};

typedef struct PopConsumption {
  vector<pair<uint, float>> slaves_consumption;
  vector<pair<uint, float>> peasants_consumption;
  vector<pair<uint, float>> burghers_consumption;
  vector<pair<uint, float>> monks_consumption;
  vector<pair<uint, float>> nobles_consumption;
}PopConsumption;

class Culture
{
private:
  string name;
  uint id;
  vector<bool> customs;
  vector<uint> homelands; // provinces where this culture considers its homeland (for example, the province where the culture originated) and be more happy
  vector<uint> goods_obsession; // goods that this culture is obsessed with
  PopConsumption pop_consumption; // how much of each good each pop consumes
public:
  Culture(/* args */) {};
  ~Culture() {};
  Culture(string name, uint id);
  string get_name();
  uint getId();
  vector<uint> get_homelands();
  vector<uint> get_goods_obsession();
  PopConsumption get_pop_consumption();
  vector<pair<uint, float>> get_class_consumption(population_class pop_class);
  void set_homelands(vector<uint> homelands);
  void set_goods_obsession(vector<uint> goods_obsession);
  void set_pop_consumption(PopConsumption pop_consumption);
  PopConsumption generate_pop_consumption(World* w, uint country_id);
};

