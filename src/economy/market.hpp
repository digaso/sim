#pragma once
#include <iostream>
#include <vector>


using namespace std;

class World;

class Market {
  vector<uint> provinces;
  vector<float> goods_prices;
  vector<uint> goods_demands;
  vector<uint> goods_production;
  vector<uint> goods_stocks;
public:

  Market(World* w);
  Market() {};
  ~Market() {};
  void updateMarket();
  void updateDemand(uint good_id, uint amount);
  void updateProduction(uint good_id, uint amount);
  vector<uint> get_provinces();
  bool has_province(uint id);
  void add_province(uint id);
};