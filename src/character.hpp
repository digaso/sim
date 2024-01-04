#pragma once
#include <string>
#include "country.hpp"
#include "utils/date.hpp"
#include "agents/ai_character.hpp"

using namespace std;

class Country;
class World;
class AI_Character;

struct military_skill {
  uint8_t tradition;
  uint8_t organization;
  uint8_t discipline;
};


class Character
{
protected:
  bool man;
  uint id;
  uint religion_id;
  uint culture_id;
  int father_id;
  int mother_id;
  int spouse_id;
  int country_ruling;
  uint country_living_id;
  uint country_born_id;
  uint province_born_id;
  uint province_living_id;
  uint8_t conscientiousness; // high means eficient and organized, low means careless and only cares about himself in a scale of 0 to 100
  uint8_t agreeableness; // low means its very critical and rational and low means friendly and compassionate in a scale of 0 to 100
  uint8_t neuroticism; // how much confident and resilient about his capabilities it is in a scale of 0 to 100
  uint8_t openness; // low means not open to new things like cultures or new ways of doings stuff in a scale of 0 to 100
  uint8_t extraversion; // high means outgoing and energetic  and low means solitary and reserved in a scale of 0 to 100

  string first_name;
  string last_name;
  vector<uint> opinions; // opinions about other characters in a scale from -100 to 100
  vector<uint> children;
  date birth_date;
  date death_date;
  uint ai_agent;
public:
  Character(uint id, string first_name, string last_name, date birth_date, uint country_living, uint8_t conscientiousness, uint8_t agreeableness, uint8_t neuroticism, uint8_t openness, uint8_t extraversion, uint religion_id, uint culture_id, int father_id, int mother_id, int spouse_id, uint province_born_id, uint province_living_id, bool ruling, bool man, World* w, int country_ruling);
  ~Character();
  string get_name();
  uint get_id();
  uint get_religion();
  uint get_culture();
  uint get_father();
  uint get_mother();
  uint get_spouse();
  uint get_province_living();
  uint get_province_born();
  uint8_t get_military_skill();
  uint8_t get_diplomacy_skill();
  uint8_t get_economy_skill();
  vector <uint> get_children();
  date get_birth_date();
  date get_death_date();
  string to_string();
  uint get_country_ruling();
  uint get_country_living();

  friend ostream& operator<<(ostream& os, const Character& c);
};
