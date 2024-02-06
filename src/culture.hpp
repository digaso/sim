#pragma once
#include "world.hpp"
#include <string>
#include <vector>

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
  vector<pair<uint, uint>> slaves_consumption;
  vector<pair<uint, uint>> peasants_consumption;
  vector<pair<uint, uint>> citizens_consumption;
  vector<pair<uint, uint>> elite_consumption;
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
  uint get_id();
  vector<uint> get_homelands();

  vector<uint> get_goods_obsession();

  PopConsumption get_pop_consumption();

  void set_homelands(vector<uint> homelands);

  void set_goods_obsession(vector<uint> goods_obsession);

  void set_pop_consumption(PopConsumption pop_consumption);

  PopConsumption generate_pop_consumption(World* w, uint country_id);
};

