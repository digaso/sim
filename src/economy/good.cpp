#include "good.hpp"

Good::Good()
{
}

Good::Good(uint id, string name, float base_value, void (*func) (Province*))
{
  this->id = id;
  this->name = name;
  this->base_value = base_value;
  this->func = func;
}

Good::~Good()
{
}
