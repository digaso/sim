#pragma once
#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "country.hpp"
using namespace std;
class character
{
protected:
  uint id;
  uint country_id;
  std::string name;
  string birth_date;
public:
  character(uint id, std::string name, string birth_date, uint country_id);
  ~character();
  std::string get_name();
  string get_birth_date();
};
#endif
character::character(uint id, std::string name, string birth_date, uint country_id)
{
  this->id = id;
  this->name = name;
  this->birth_date = birth_date;
  this->country_id = country_id;
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
