#pragma once
#include <string>
#include "country.hpp"
#include "utils/date.hpp"

using namespace std;

class Country;

class Character
{
protected:
  bool ruling = false;
  uint id;
  uint religion_id;
  uint culture_id;
  uint father_id;
  uint mother_id;
  uint spouse_id;
  uint country_living_id;
  uint country_born_id;
  uint province_born_id;
  uint province_living_id;
  uint8_t military_skill;
  uint8_t diplomacy_skill;
  uint8_t economy_skill;
  string first_name;
  string last_name;
  vector<uint> children;
  date birth_date;
  date death_date;
public:
  Character(uint id, string first_name, string last_name, date birth_date, uint country_living, uint military_skill, uint diplomacy_skill, uint economy_skill, uint religion_id, uint culture_id, uint father_id, uint mother_id, uint spouse_id, uint province_born_id, uint province_living_id);
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

  uint get_country_living();

  friend ostream& operator<<(ostream& os, const Character& c);
};
