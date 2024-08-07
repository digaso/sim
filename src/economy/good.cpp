#include "good.hpp"
#include "../world.hpp"

Good::Good() {}

Good::Good(uint id, string name, float base_value, type_good type, class_good good_class) {
  this->id = id;
  this->name = name;
  this->base_value = base_value;
  this->type = type;
  this->good_class = good_class;
}

Good::~Good() {}

uint Good::getId() {
  return this->id;
}

float Good::get_base_value() {
  return this->base_value;
}

type_good Good::get_type() {
  return this->type;
}


void Good::set_goods(World* world) {
  world->addGood(Good(0, "Grain", 1.4, plantable, basic_need));
  world->addGood(Good(1, "Wine", 2.5, plantable, luxury));
  world->addGood(Good(2, "Salt", 2.3, mineral, basic_need));
  world->addGood(Good(3, "Fish", 1.4, catchable, basic_need));
  world->getGoodById(3)->set_maritime(true);
  world->addGood(Good(4, "Cotton", 2, plantable, raw_material));
  world->addGood(Good(5, "Clothes", 2.5, manufactured, basic_need));
  world->addGood(Good(6, "Iron", 2, mineral, raw_material));
  world->addGood(Good(7, "Timber", 1.5, plantable, raw_material));
  world->addGood(Good(8, "Dyes", 3.5, plantable, luxury));
  world->addGood(Good(9, "Silk", 4, plantable, luxury));
  world->addGood(Good(10, "Tea", 4, plantable, luxury));
  world->addGood(Good(11, "Coffee", 4, plantable, luxury));
  world->addGood(Good(12, "Cloves", 4.8, plantable, luxury));
  world->addGood(Good(13, "Sugar", 3, plantable, luxury));
  world->addGood(Good(14, "Horses", 2, catchable, military));
  world->addGood(Good(15, "Copper", 1.8, mineral, raw_material));
  world->addGood(Good(16, "Stone", 1.2, mineral, raw_material));
  world->addGood(Good(17, "Marble", 2.5, mineral, raw_material));
  world->addGood(Good(18, "Glass", 3.0, manufactured, raw_material));
  world->addGood(Good(19, "Paper", 3.0, manufactured, raw_material));
  world->addGood(Good(20, "Incense", 3.5, plantable, luxury));
  world->addGood(Good(21, "Gold", 9, mineral, luxury));
  world->addGood(Good(22, "Silver", 4, mineral, luxury));
  world->addGood(Good(23, "Spices", 4.8, plantable, luxury));
  world->addGood(Good(24, "Opioum", 4.5, plantable, luxury));
  world->addGood(Good(25, "Fruit", 1.6, plantable, basic_need));
  world->addGood(Good(26, "Tobacco", 3.5, plantable, luxury));
  world->addGood(Good(27, "Cocoa", 3.5, plantable, luxury));
  world->addGood(Good(28, "Ivory", 4.9, manufactured, luxury));
  world->addGood(Good(29, "Camels", 2, catchable, military));
  world->addGood(Good(30, "Meat", 1.7, manufactured, basic_need));
  world->addGood(Good(31, "Fur", 2, catchable, luxury));
  world->addGood(Good(32, "Leather", 1.7, catchable, raw_material));
  world->addGood(Good(33, "Gems", 5.5, mineral, luxury));
  world->addGood(Good(34, "Spears", 2, manufactured, military));
  world->addGood(Good(35, "Swords", 4, manufactured, military));
  world->addGood(Good(36, "Bows", 2, manufactured, military));
  world->addGood(Good(37, "Crossbows", 4, manufactured, military));
  world->addGood(Good(38, "Cannons", 7.5, manufactured, military));
  world->addGood(Good(39, "Muskets", 5.5, manufactured, military));
  world->addGood(Good(40, "Leather Armour", 2, manufactured, military));
  world->addGood(Good(41, "Plate Armour", 5.5, manufactured, military));
  world->addGood(Good(42, "Elephants", 3, catchable, military));
  world->addGood(Good(43, "Ale", 2, manufactured, basic_need));
  world->addGood(Good(44, "Rice", 1.4, plantable, raw_material));
  world->addGood(Good(45, "Vegetables", 1.4, plantable, raw_material));
  world->addGood(Good(46, "Tools", 3, manufactured, class_good::basic_need));
}

bool Good::is_maritime() {
  return this->maritime;
}

void Good::set_maritime(bool maritime) {
  this->maritime = maritime;
}


void Good::set_map(bool* map) {
  this->map = map;
}

bool* Good::get_map() {
  return this->map;
}

uint Good::get_initial_amount() {
  return this->initial_amoount;
}

void Good::set_initial_amount(uint initial_amount) {
  this->initial_amoount = initial_amount;
}

class_good Good::get_class() {
  return this->good_class;
}

string Good::get_name() {
  return this->name;
}

ostream& operator<<(ostream& os, const Good& g) {
  os << g.name;
  return os;
}
