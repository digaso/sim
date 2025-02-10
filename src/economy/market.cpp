#include "market.hpp"
#include "../world.hpp"

Market::Market(World* w) {
  this->goods = w->getGoods();
  this->goods_prices = new float[ this->goods.size() ];
  this->goods_demands = new float[ this->goods.size() ];
  this->goods_production = new float[ this->goods.size() ];
  this->goods_stocks = new float[ this->goods.size() ];
  for (uint16_t i = 0; i < this->goods.size(); i++) {
    this->goods_prices[ i ] = this->goods[ i ].get_base_value();
    this->goods_demands[ i ] = 0;
    this->goods_production[ i ] = 0;
    this->goods_stocks[ i ] = 0;
  }
}
void Market::updateMarketPrices() {
  cout << "Production Start: " << this->production_stack.size() << endl;
  cout << "Demand Start: " << this->demand_stack.size() << endl;
  this->updateDemands();
  this->updateProductions();
  cout << "Production End: " << this->production_stack.size() << endl;
  cout << "Demand End: " << this->demand_stack.size() << endl;
  for (uint16_t i = 0; i < this->goods.size(); i++) {
    this->goods_prices[ i ] = goods[ i ].get_base_value() + (this->goods_demands[ i ] - this->goods_production[ i ]) / 100;
  }
}

void Market::cleanMarket() {
  for (uint16_t i = 0; i < this->goods.size(); i++) {
    this->goods_demands[ i ] = 0;
    this->goods_production[ i ] = 0;
  }
}

void Market::updateDemands() {
  while (!this->demand_stack.empty()) {
    pair<uint, float> demand = this->demand_stack.front();
    this->goods_demands[ demand.first ] += demand.second;
    this->demand_stack.pop();
  }
}

void Market::updateProductions() {
  while (!this->production_stack.empty()) {
    pair<uint, float> production = this->production_stack.front();
    this->goods_production[ production.first ] += production.second;
    this->production_stack.pop();
  }
}


void Market::addDemand(uint good_id, float amount) {
  this->demand_stack.push(make_pair(good_id, amount));
}

void Market::addProduction(uint good_id, float amount) {
  this->production_stack.push(make_pair(good_id, amount));
  cout << "stack size: " << this->demand_stack.size() << endl;

}

vector<uint> Market::getProvinces() {
  return this->provinces;
}

void Market::add_province(uint id) {
  this->provinces.push_back(id);
}

float* Market::get_prices() {
  return this->goods_prices;
}

float* Market::get_demands() {
  return this->goods_demands;
}

float* Market::get_production() {
  return this->goods_production;
}

float* Market::get_stocks() {
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
