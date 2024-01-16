#pragma once
#include <iostream>
#include <vector>


using namespace std;

class World;

class Market {
  uint province_id;
  vector<float> goods_prices;
  vector<uint> goods_demands;
  vector<uint> goods_production;
  vector<uint> goods_stocks;
public:

  Market(uint province_id, World* w);
  Market() {};
  ~Market() {};
  void updateMarket();
};