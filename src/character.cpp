
<<<<<<< HEAD
#include "character.hpp"
#include "agents/ai_character.hpp"

Character::Character(uint id, string first_name, string last_name, date birth_date, uint country_living, uint military_skill, uint diplomacy_skill, uint economy_skill, uint religion_id, uint culture_id, int father_id, int mother_id, int spouse_id, uint province_born_id, uint province_living_id, bool ruling, bool man, World* w, int country_ruling)
=======
Character::Character(uint id, string name, date birth_date, uint country_living)
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)
{
  this->id = id;
  this->name = name;
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
  this->man = man;
  this->country_ruling = country_ruling;
  this->ai_agent = id;
  AI_Character aic(id, this);
  w->addAIAgent(aic);
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

<<<<<<< HEAD
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

=======
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)
ostream& operator<<(ostream& os, const Character& c)
{
  os << c.name << " (" << c.birth_date << ")";
  return os;
}