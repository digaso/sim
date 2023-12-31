#include "ai_character.hpp"


AI_Character::AI_Character(uint id, Character* c)
{
  this->id = id;
  this->c = c;
}

AI_Character::AI_Character() {}

AI_Character::~AI_Character() {}


void AI_Character::makeDiplomacyDecision(Country*, World* world) {
}

void AI_Character::makeTradeDecision(Country* country, World* world) {
}

void AI_Character::update(World* w) {

}

ostream& operator<<(ostream& os, const AI_Character& aic)
{
  os << aic.to_string();
  return os;
}

const std::string AI_Character::to_string() const
{
  return "AI_Character " + std::to_string(this->id) + " " + this->c->to_string();
}