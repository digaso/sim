#include "market.hpp"
#include "../world.hpp"


Market::Market(World* w) {
  this->goods = w->getGoods();
  for (uint16_t i = 0; i < goods.size(); i++) {
    this->goods_prices.push_back(0);
    this->goods_demands.push_back(0);
    this->goods_production.push_back(0);
    this->goods_stocks.push_back(0);
  }
}

void Market::updateMarketPrices() {
  for (uint16_t i = 0; i < this->goods_prices.size(); i++) {
    this->goods_prices[ i ] = goods[ i ].get_base_value() + (this->goods_demands[ i ] - this->goods_production[ i ]) / 100;
  }
}

void Market::cleanMarket() {
  for (uint16_t i = 0; i < this->goods_prices.size(); i++) {
    this->goods_demands.at(i) = 0;
    this->goods_production.at(i) = 0;
  }
}

void Market::updateDemand(uint good_id, float amount) {
  this->goods_demands[ good_id ] += amount;
}

void Market::updateProduction(uint good_id, float amount) {
  this->goods_production[ good_id ] += amount;
}

vector<uint> Market::getProvinces() {
  return this->provinces;
}

void Market::add_province(uint id) {
  this->provinces.push_back(id);
}

vector<float> Market::get_prices() {
  return this->goods_prices;
}

vector<float> Market::get_demands() {
  return this->goods_demands;
}

vector<float> Market::get_production() {
  return this->goods_production;
}

vector<float> Market::get_stocks() {
  return this->goods_stocks;
}

bool Market::has_province(uint id) {
  for (uint i = 0; i < this->provinces.size(); i++) {
    if (this->provinces[ i ] == id) {
      return true;
    }
  }
  return false;
}



