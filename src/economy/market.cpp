#include "market.hpp"
#include "../world.hpp"


Market::Market(World* w) {
  vector<Good> goods = w->getGoods();
  for (uint16_t i = 0; i < w->getGoods().size(); i++) {
    this->goods_prices.push_back(goods[ i ].get_base_value());
    this->goods_demands.push_back(0);
    this->goods_production.push_back(0);
    this->goods_stocks.push_back(0);
  }
}

void Market::updateMarket() {
  for (uint16_t i = 0; i < this->goods_prices.size(); i++) {
    this->goods_prices[ i ] += (this->goods_demands[ i ] - this->goods_production[ i ]) / 100;
  }
}

void Market::updateDemand(uint good_id, uint amount) {
  this->goods_demands[ good_id ] += amount;
}

void Market::updateProduction(uint good_id, uint amount) {
  this->goods_production[ good_id ] += amount;
}

vector<uint> Market::get_provinces() {
  return this->provinces;
}

void Market::add_province(uint id) {
  this->provinces.push_back(id);
}

bool Market::has_province(uint id) {
  for (uint i = 0; i < this->provinces.size(); i++) {
    if (this->provinces[ i ] == id) {
      return true;
    }
  }
  return false;
}



