#include "good.hpp"

Good::Good()
{
}

Good::Good(uint id, string name, float base_value)
{
  this->id = id;
  this->name = name;
  this->base_value = base_value;
}

Good::~Good()
{
}
