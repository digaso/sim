#pragma once
#ifndef _COUNTRY_H_
#define _COUNTRY_H_
#include <string>
#include <vector>
#include "province.hpp"
#include "character.hpp"
using namespace std;

class province;
class country
{
private:
  vector<province> provinces;
  vector<character> characters;
  uint id;
  string name;
  string abrev;
  float money;

public:
  country() {};
  country(uint id, string name, string abrev)
  {
    this->id = id;
    this->name = name;
    this->abrev = abrev;
  }
  ~country() {};
  uint get_id();
  string get_name();
  string get_abrev();
  string print();
  void add_province(province p);
  void remove_province(province p);
  void add_character(character* c);
  void remove_character(character c);
  static const int get_countryId_byAbrev(uint id, vector<country> countries);
};
#endif

void country::add_province(province p) {
  this->provinces.push_back(p);
}


void country::add_character(character* c) {
  this->characters.push_back(*c);
}



const int get_countryId_byAbrev(string abrev, vector<country> countries)
{
  for (int i = 0; i < countries.size(); i++)
  {
    if (countries.at(i).get_abrev() == abrev)
      return i;
  }
  return -1;
}

string country::get_name() {
  return this->name;
}
string country::get_abrev() {
  return this->abrev;
}

string country::print() {
  return this->name + " (" + this->abrev + ")";
}

uint country::get_id() {
  return this->id;
}
