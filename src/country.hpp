#pragma once
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

public:
  country(string name, string abrev);
  ~country();
  int get_id();
  string get_name();
  string get_abrev();
  string print();
  static country* get_country_byId(uint id, vector<country> countries);
  static const int get_countryId_byAbrev(uint id, vector<country> countries);
};

country::country(string name, string abrev)
{
  this->name = name;
  this->abrev = abrev;
}

country::~country() {}


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
