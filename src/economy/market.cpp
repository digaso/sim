#include "market.hpp"
#include "../world.hpp"

Market::Market() {}

Market::Market(uint province_id, World* w) {
  this->province_id = province_id;
  for (uint16_t i = 0; i < w->getGoods().size(); i++) {
    this->goods_demands.push_back(0);
    this->goods_production.push_back(0);
  }
}
