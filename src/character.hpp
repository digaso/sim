#pragma once
#ifndef _PERSON_H_
#define _PERSON_H_
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

};
#endif
character::character(uint id, string name, string birth_date, country* country_living)
{
  this->id = id;
  this->name = name;
  this->birth_date = birth_date;
  this->country_living = country_living;
}

std::string character::get_name()
{
  return this->name;
}

string character::get_birth_date()
{
  return this->birth_date;
}

character::~character()
{
}

country* character::get_country_living()
{
  return this->country_living;
}