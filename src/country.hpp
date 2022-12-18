#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "character.hpp"
#include "province.hpp"

using namespace std;

class character;
class province;
class country
{
  vector<province*> provinces;
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
  void set_name(string name);
  string get_abrev();
  string print();
  void add_province(province* p);
  void remove_province(province* p);
  void add_character(character c);
  void remove_character(character c);
  void print_characters();
  void print_provinces();
  //static void setup_countries(World* w);
  vector<province*> get_provinces();
  vector<character> get_characters();
};

country _0_POR = country(0, "Portugal", "POR");


