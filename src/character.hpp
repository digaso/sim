#pragma once
#include <string>
#include "country.hpp"
#include "utils/date.hpp"

using namespace std;

class Country;

class Character
{
protected:
  uint id;
  uint religion_id;
  uint culture_id;
  uint dynasty_id;
  uint father_id;
  uint mother_id;
  uint spouse_id;
  uint country_living_id;
  uint country_born_id;
  uint province_born_id;
  uint province_living_id;
  string name;
  vector<uint> children;
  date birth_date;
  date death_date;
public:
  Character(uint id, std::string name, date birth_date, uint country_living);
  ~Character();
  string get_name();
  uint get_id();
  date get_birth_date();
  date get_death_date();


  uint get_country_living();

  friend ostream& operator<<(ostream& os, const Character& c);
};
