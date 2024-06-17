#pragma once
#include <iostream>
#include <vector>
#include "good.hpp"


using namespace std;

class World;

class Market {
  vector<uint> provinces;
  vector<float> goods_prices;
  vector<float> goods_demands;
  vector<float> goods_production;
  vector<float> goods_stocks;
public:
  vector<Good> goods;

  Market(World* w);
  Market() {};
  ~Market() {};
  vector<float> get_prices();
  vector<float> get_demands();
  vector<float> get_production();
  vector<float> get_stocks();
  void updateMarketPrices();
  void updateDemand(uint good_id, float amount);
  void updateProduction(uint good_id, float amount);
  void cleanMarket();
  vector<uint> getProvinces();
  bool has_province(uint id);
  void add_province(uint id);
};