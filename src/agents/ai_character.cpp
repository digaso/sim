#include "ai_character.hpp"


AI_Character::AI_Character(uint id, Character* c)
{
  this->id = id;
  this->c = c;
}

AI_Character::AI_Character() {}

AI_Character::~AI_Character() {}



void AI_Character::makeCountryDecision(World* w) {
  Country* country = w->getCountryById(this->c->get_country_living());
  this->makeDiplomacyDecision(country, w);
  this->makeTradeDecision(country, w);
  this->makeMilitaryDecision(country, w);
}

void AI_Character::makeDiplomacyDecision(Country*, World* world) {

}
void AI_Character::makeMilitaryDecision(Country*, World* world) {}

void AI_Character::makeTradeDecision(Country* country, World* world) {
}

void AI_Character::makeSocialDecision(World* world) {};

void AI_Character::update(World* w) {
  if (this->c->get_country_living() != -1) {
    this->makeCountryDecision(w);
  }
  this->makeSocialDecision(w);
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