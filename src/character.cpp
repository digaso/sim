#include "character.hpp"

Character::Character(uint id, string name, date birth_date, uint country_living)
{
  this->id = id;
  this->name = name;
  this->birth_date = birth_date;
  this->country_living_id = country_living;
}

string Character::get_name()
{
  return this->name;
}

date Character::get_birth_date()
{
  return this->birth_date;
}

Character::~Character()
{
}

uint Character::get_country_living()
{
  return this->country_living_id;
}

ostream& operator<<(ostream& os, const Character& c)
{
  os << c.name << " (" << c.birth_date << ")";
  return os;
}