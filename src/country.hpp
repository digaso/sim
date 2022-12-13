#pragma once
#ifndef _COUNTRY_H_
#define _COUNTRY_H_
#include <string>
#include <vector>
#include "province.hpp"
using namespace std;

class country
{
private:
  uint id;
  string name;
  string abrev;
  float money;
  vector<province> provinces;
  //vector<character> characters;

public:
  country(uint id, string name, string abrev);
  ~country();
  int get_id();
  string get_name();
  string get_abrev();
  string print();
  void add_province(province p);
  void remove_province(province p);
  //void add_character(character c);
  //void remove_character(character c);
  static country* get_country_byId(uint id, vector<country> countries);
  static const int get_countryId_byAbrev(uint id, vector<country> countries);
};
#endif
country::country(uint id, string name, string abrev)
{
  this->id = id;
  this->name = name;
  this->abrev = abrev;
}

country::~country() {}

void country::add_province(province p) {
  this->provinces.push_back(p);
}


//void country::add_character(character c) {
//  this->characters.push_back(c);
//}

const int get_countryId_byAbrev(string abrev, vector<country> countries)
{
  for (int i = 0; i < countries.size(); i++)
  {
    if (countries.at(i).get_abrev() == abrev)
      return i;
  }
  return -1;
}

country* country::get_country_byId(uint id, vector<country> countries)
{
  if (id < countries.size())
    return &countries.at(id);
  return NULL;
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

int country::get_id() {
  return this->id;
}
