#pragma once
#include <iostream>
#include <vector>



using namespace std;

class World;

class Market {
  uint province_id;
  vector<uint> goods_demands;
  vector<uint> goods_production;
public:

  Market(uint province_id, World* w);
  Market();
  ~Market() {};
};