
#include "character.hpp"

Character::Character(uint id, string first_name, string last_name, date birth_date, uint country_living, uint military_skill, uint diplomacy_skill, uint economy_skill, uint religion_id, uint culture_id, uint father_id, uint mother_id, uint spouse_id, uint province_born_id, uint province_living_id)
{
  this->id = id;
  this->first_name = first_name;
  this->last_name = last_name;
  this->birth_date = birth_date;
  this->country_living_id = country_living;
  this->military_skill = military_skill;
  this->diplomacy_skill = diplomacy_skill;
  this->economy_skill = economy_skill;
  this->religion_id = religion_id;
  this->culture_id = culture_id;
  this->father_id = father_id;
  this->mother_id = mother_id;
  this->spouse_id = spouse_id;
  this->province_born_id = province_born_id;
  this->province_living_id = province_living_id;
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