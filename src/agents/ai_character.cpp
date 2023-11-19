#include "ai_character.hpp"
#include "../world.hpp"

uint AI_Character::id_counter = 0;

AI_Character::AI_Character()
{
  id = id_counter++;
}
AI_Character::~AI_Character()
{
}

void AI_Character::update(World* world)
{
  this->world = world;

}

const std::string AI_Character::to_string() const
{
  return "AI_Character";
}