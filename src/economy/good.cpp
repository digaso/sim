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

void Good::set_goods(World* world)
{
  world->addGood(Good(0, "Grain", 1.0, plantable));
  world->addGood(Good(1, "Wine", 1.5, plantable));
  world->addGood(Good(2, "Salt", 1.2, mineral));
  world->addGood(Good(3, "Fish", 1.0, catchable));
  world->addGood(Good(4, "Wool", 1.0, catchable));
  world->addGood(Good(5, "Cloth", 1.9, manufactured));
  world->addGood(Good(6, "Iron", 2.0, mineral));
  world->addGood(Good(7, "Timber", 1.0, plantable));
  world->addGood(Good(8, "Dyes", 2.0, plantable));
  world->addGood(Good(9, "Silk", 2.5, plantable));
  world->addGood(Good(10, "Tea", 1.9, plantable));
  world->addGood(Good(11, "Coffee", 1.9, plantable));
  world->addGood(Good(12, "Cloves", 3.0, plantable));
  world->addGood(Good(13, "Sugar", 1.3, plantable));
  world->addGood(Good(14, "Horses", 1.0, catchable));
  world->addGood(Good(15, "Copper", 1.0, mineral));
  world->addGood(Good(16, "Fur", 1.0, catchable));
  world->addGood(Good(17, "Stone", 1.0, mineral));
  world->addGood(Good(18, "Marble", 1.0, mineral));
  world->addGood(Good(19, "Glass", 1.0, manufactured));
  world->addGood(Good(20, "Paper", 1.0, manufactured));
  world->addGood(Good(21, "Incense", 1.0, plantable));
  world->addGood(Good(22, "Gold", 0.0, mineral));
  world->addGood(Good(23, "Silver", 3.0, mineral));
  world->addGood(Good(24, "Pearls", 1.0, catchable));
  world->addGood(Good(25, "Spices", 1.0, plantable));
}


ostream& operator<<(ostream& os, const Good& g)
{
  os << g.name;
  return os;
}
