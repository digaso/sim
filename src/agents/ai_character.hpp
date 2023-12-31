#pragma once
#include "../world.hpp"

class Character;
class World;
class Country;

class AI_Character
{
protected:
  int id;
public:
  AI_Character(uint id, Character* c);
  AI_Character();
  ~AI_Character();
  const std::string to_string() const;
  void makeDiplomacyDecision(Country*, World* world);
  void makeTradeDecision(Country* country, World* world);
  void makeMilitaryDecision(Country* country, World* world);
  void makeSocialDecision(World* w);
  void makeCountryDecision(World* w);
  void update(World* w);
  friend ostream& operator<<(ostream& os, const AI_Character& aic);

private:
  Character* c;
};