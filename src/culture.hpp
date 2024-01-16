#pragma once
#include <string>

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
  bool* customs;
  vector<uint> homelands; // provinces where this culture considers its homeland (for example, the province where the culture originated) and be more happy
  vector<uint> goods_obsession; // goods that this culture is obsessed with
  PopConsumption pop_consumption; // how much of each good each pop consumes
public:

  Culture(/* args */) {};
  Culture(string name, uint id, vector<uint> homelands, vector<uint> goods_obsession, PopConsumption pop_consumption) {
    this->name = name;
    this->id = id;
    this->homelands = homelands;
    this->goods_obsession = goods_obsession;
    this->pop_consumption = pop_consumption;
  };
  string get_name() {
    return this->name;
  }
  uint get_id() {
    return this->id;
  }
  ~Culture() {};
};

