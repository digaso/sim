#include "character.hpp"

Character::Character(uint id, string first_name, string last_name, date birth_date, uint country_living)
{
  this->id = id;
  this->first_name = first_name;
  this->last_name = last_name;
  this->birth_date = birth_date;
  this->country_living_id = country_living;
}

string Character::get_name()
{
  return this->first_name + " " + this->last_name;
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

uint Character::get_id()
{
  return this->id;
}

uint Character::get_religion()
{
  return this->religion_id;
}

uint Character::get_culture()
{
  return this->culture_id;
}

uint Character::get_father()
{
  return this->father_id;
}

uint Character::get_mother()
{
  return this->mother_id;
}

uint Character::get_spouse()
{
  return this->spouse_id;
}

uint Character::get_province_living()
{
  return this->province_living_id;
}

uint Character::get_province_born()
{
  return this->province_born_id;
}

uint8_t Character::get_military_skill()
{
  return this->military_skill;
}

uint8_t Character::get_diplomacy_skill()
{
  return this->diplomacy_skill;
}

uint8_t Character::get_economy_skill()
{
  return this->economy_skill;
}

vector <CharacterTrait> Character::get_traits()
{
  return this->traits;
}

vector <uint> Character::get_children()
{
  return this->children;
}

date Character::get_death_date()
{
  return this->death_date;
}


ostream& operator<<(ostream& os, const Character& c)
{
  os << c.first_name << " " << c.last_name << " (" << c.birth_date << ")";
  return os;
}