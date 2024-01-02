#include "good.hpp"
#include "../world.hpp"

Good::Good()
{
}

Good::Good(uint id, string name, float base_value, type_good type, class_good good_class)
{
  this->id = id;
  this->name = name;
  this->base_value = base_value;
  this->type = type;
  this->good_class = good_class;
}

Good::~Good()
{
}

uint Good::get_id()
{
  return this->id;
}

float Good::get_base_value()
{
  return this->base_value;
}

type_good Good::get_type()
{
  return this->type;
}
void Good::set_goods(World* world)
{
  world->addGood(Good(0, "Grain", 1.5, plantable, basic_need));
  world->addGood(Good(1, "Wine", 2.0, plantable, luxury));
  world->addGood(Good(2, "Salt", 2.0, mineral, basic_need));
  world->addGood(Good(3, "Fish", 1.0, catchable, basic_need));
  world->getGoodById(3)->set_maritime(true);
  world->addGood(Good(4, "Cotton", 1.6, plantable, raw_material));
  world->addGood(Good(5, "Clothes", 2.0, manufactured, basic_need));
  world->addGood(Good(6, "Iron", 1.8, mineral, raw_material));
  world->addGood(Good(7, "Timber", 1.2, plantable, raw_material));
  world->addGood(Good(8, "Dyes", 3.3, plantable, luxury));
  world->addGood(Good(9, "Silk", 3.7, plantable, luxury));
  world->addGood(Good(10, "Tea", 3.5, plantable, luxury));
  world->addGood(Good(11, "Coffee", 3.5, plantable, luxury));
  world->addGood(Good(12, "Cloves", 4.5, plantable, luxury));
  world->addGood(Good(13, "Sugar", 2.5, plantable, luxury));
  world->addGood(Good(14, "Horses", 1.8, catchable, military));
  world->addGood(Good(15, "Copper", 1.4, mineral, raw_material));
  world->addGood(Good(16, "Stone", 1.0, mineral, raw_material));
  world->addGood(Good(17, "Marble", 2.0, mineral, raw_material));
  world->addGood(Good(18, "Glass", 3.0, manufactured, raw_material));
  world->addGood(Good(19, "Paper", 3.0, manufactured, raw_material));
  world->addGood(Good(20, "Incense", 3.0, plantable, luxury));
  world->addGood(Good(21, "Gold", 7.0, mineral, luxury));
  world->addGood(Good(22, "Silver", 3.5, mineral, luxury));
  world->addGood(Good(23, "Spices", 4.5, plantable, luxury));
  world->addGood(Good(24, "Opioum", 3.9, plantable, luxury));
  world->addGood(Good(25, "Fruit", 1.9, plantable, basic_need));
  world->addGood(Good(26, "Tobacco", 3.5, plantable, luxury));
  world->addGood(Good(27, "Cocoa", 3.5, plantable, luxury));
  world->addGood(Good(28, "Ivory", 4.9, catchable, luxury));
  world->addGood(Good(29, "Camels", 1.5, catchable, military));
  world->addGood(Good(30, "Cattle", 1.5, catchable, basic_need));
  world->addGood(Good(31, "Meat", 1.5, manufactured, basic_need));
  world->addGood(Good(32, "Fur", 1.5, catchable, luxury));
  world->addGood(Good(33, "Leather", 1.5, catchable, raw_material));
  world->addGood(Good(38, "Gems", 5.5, mineral, luxury));

}


ostream& operator<<(ostream& os, const Good& g)
{
  os << g.name;
  return os;
}
