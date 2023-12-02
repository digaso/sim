#pragma once
#include <string>
#include "country.hpp"
#include "utils/date.hpp"
#include "agents/ai_character.hpp"

using namespace std;

class Country;
<<<<<<< HEAD
class World;
class AI_Character;
=======
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)

class Character
{
protected:
  bool man;
  uint id;
  uint religion_id;
  uint culture_id;
<<<<<<< HEAD
  int father_id;
  int mother_id;
  int spouse_id;
  int country_ruling;
=======
  uint dynasty_id;
  uint father_id;
  uint mother_id;
  uint spouse_id;
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)
  uint country_living_id;
  uint country_born_id;
  uint province_born_id;
  uint province_living_id;
<<<<<<< HEAD
  uint8_t military_skill;
  uint8_t diplomacy_skill;
  uint8_t economy_skill;
  string first_name;
  string last_name;
=======
  string name;
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)
  vector<uint> children;
  date birth_date;
  date death_date;
  uint ai_agent;
public:
<<<<<<< HEAD
  Character(uint id, string first_name, string last_name, date birth_date, uint country_living, uint military_skill, uint diplomacy_skill, uint economy_skill, uint religion_id, uint culture_id, int father_id, int mother_id, int spouse_id, uint province_born_id, uint province_living_id, bool ruling, bool man, World* w, int country_ruling);
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
=======
  Character(uint id, std::string name, date birth_date, uint country_living);
  ~Character();
  string get_name();
  uint get_id();
>>>>>>> parent of 8bb1725 (added UI to see info and started character generation)
  date get_birth_date();
  date get_death_date();

  uint get_country_living();

  friend ostream& operator<<(ostream& os, const Character& c);
};
