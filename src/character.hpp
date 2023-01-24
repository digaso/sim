#pragma once
#include <string>
#include "country.hpp"

using namespace std;

class country;

class character
{
protected:
  uint id;
  country* country_living;
  std::string name;
  string birth_date;
public:
  character(uint id, std::string name, string birth_date, country* country_living);
  ~character();
  string get_name();
  string get_birth_date();
  country* get_country_living();
  friend ostream& operator<<(ostream& os, const character& c);
};
