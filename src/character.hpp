#pragma once
#include <string>
#include "country.hpp"

using namespace std;

class Country;

class character
{
protected:
  uint id;
  Country* country_living;
  std::string name;
  string birth_date;
public:
  character(uint id, std::string name, string birth_date, Country* country_living);
  ~character();
  string get_name();
  string get_birth_date();
  Country* get_country_living();
  friend ostream& operator<<(ostream& os, const character& c);
};
