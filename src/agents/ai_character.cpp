#include "ai_character.hpp"


AI_Character::AI_Character(uint id, Character* c)
{
  this->id = id;
  this->c = c;
}

AI_Character::AI_Character() {}

AI_Character::~AI_Character()
{
}

void AI_Character::update(World* w)
{


}

const std::string AI_Character::to_string() const
{
  return "AI_Character";
}