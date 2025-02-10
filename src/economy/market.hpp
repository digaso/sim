#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "good.hpp"


using namespace std;

class World;

class Market {
  vector<uint> provinces;
  float* goods_prices;
  float* goods_demands;
  float* goods_production;
  float* goods_stocks;
  queue<pair<uint, float>> demand_stack;
  queue<pair<uint, float>> production_stack;
public:
  vector<Good> goods;

  Market(World* w);
  Market() {};
  ~Market() {};
  float* get_prices();
  float* get_demands();
  float* get_production();
  float* get_stocks();
  void updateMarketPrices();
  void updateDemands();
  void updateProductions();
  void addDemand(uint good_id, float amount);
  void addProduction(uint good_id, float amount);
  void cleanMarket();
  vector<uint> getProvinces();
  bool has_province(uint id);
  void add_province(uint id);
  void clearStacks();
};