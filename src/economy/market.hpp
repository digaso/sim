#pragma once
#include <iostream>
#include <vector>
#include "good.hpp"


using namespace std;

class World;

class Market {
  vector<uint> provinces;
  vector<float> goods_prices;
  vector<uint> goods_demands;
  vector<uint> goods_production;
  vector<uint> goods_stocks;
public:
  vector<Good> goods;

  Market(World* w);
  Market() {};
  ~Market() {};
  vector<float> get_prices();
  vector<uint> get_demands();
  vector<uint> get_production();
  vector<uint> get_stocks();
  void updateMarketPrices();
  void updateDemand(uint good_id, uint amount);
  void updateProduction(uint good_id, uint amount);
  void cleanMarket();
  vector<uint> get_provinces();
  bool has_province(uint id);
  void add_province(uint id);
};