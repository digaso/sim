#pragma once
#include "../world.hpp"

class Character;

class AI_Character
{
  int id;
public:
  AI_Character();
  ~AI_Character();
  const std::string to_string() const;
  void makeDiplomacyDecision(Country*, World* world);
  void makeTradeDecision(Country* country, World* world);
  void makeMilitaryDecision(Country* country, World* world);
  void makeSocialDecision(World* w);
  void makeCountryDecision(World* w);
  void update(World* world);
private:
  static uint id_counter;
  World* world;
};