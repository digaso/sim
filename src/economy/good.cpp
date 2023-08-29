#include "good.hpp"
#include "../world.hpp"

Good::Good()
{
}

Good::Good(uint id, string name, float base_value, type_good type)
{
  this->id = id;
  this->name = name;
  this->base_value = base_value;
  this->type = type;
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
  world->addGood(Good(0, "Grain", 1.5, plantable));
  world->addGood(Good(1, "Wine", 1.5, plantable));
  world->addGood(Good(2, "Salt", 2.0, mineral));
  world->addGood(Good(3, "Fish", 1.0, catchable));
  world->getGoodById(3)->set_maritime(true);
  world->addGood(Good(4, "Wool", 1.4, catchable));
  world->addGood(Good(5, "Cloth", 1.9, manufactured));
  world->addGood(Good(6, "Iron", 1.5, mineral));
  world->addGood(Good(7, "Timber", 1.0, plantable));
  world->addGood(Good(8, "Dyes", 2.9, plantable));
  world->addGood(Good(9, "Silk", 2.9, plantable));
  world->addGood(Good(10, "Tea", 3.0, plantable));
  world->addGood(Good(11, "Coffee", 3.2, plantable));
  world->addGood(Good(12, "Cloves", 3.9, plantable));
  world->addGood(Good(13, "Sugar", 1.9, plantable));
  world->addGood(Good(14, "Horses", 1.8, catchable));
  world->addGood(Good(15, "Copper", 1.4, mineral));
  world->addGood(Good(16, "Stone", 1.0, mineral));
  world->addGood(Good(17, "Marble", 2.0, mineral));
  world->addGood(Good(18, "Glass", 2.5, manufactured));
  world->addGood(Good(19, "Paper", 3.0, manufactured));
  world->addGood(Good(20, "Incense", 3.0, plantable));
  world->addGood(Good(21, "Gold", 7.0, mineral));
  world->addGood(Good(22, "Silver", 3.0, mineral));
  world->addGood(Good(23, "Spices", 4.0, plantable));
}


ostream& operator<<(ostream& os, const Good& g)
{
  os << g.name;
  return os;
}
