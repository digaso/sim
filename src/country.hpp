#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "character.hpp"
#include "province.hpp"
#include "diplomacy.hpp"
#include "agents/ai_character.hpp"

using namespace std;


typedef struct CountryDiplomacy {
  vector<Allie> allies;
  vector<Subject> subjects;
  vector<Truce> truces;
  vector<MilitaryAccess> military_access;
  vector<TradePartner> trade_partners;
  vector<Guarantee> guarantees;
  //vector<War> wars;
  int diplo_points_produced = 0;
  int diplo_points_spent = 0;
  int diplo_points = diplo_points_produced - diplo_points_spent;
} CountryDiplomacy;

class Character;
class Province;

class Country
{
  uint num_provinces = 0;
  uint capital_id;
  vector<uint> provinces;
  vector<uint> characters;
  vector<uint> provinces_known;
  uint king_id;
  uint id;
  string name;
  CountryDiplomacy diplomacy;
  uint color_id;
  uint culture_id;
  uint religion_id;
  bool is_player = false;
  float money;
public:
  Country() {};
  Country(uint id, string name, uint8_t religion_id)
  {
    this->id = id;
    this->name = name;
    this->religion_id = religion_id;
  };
  ~Country() {};
  uint get_id();
  string get_name();
  void set_name(string name);
  string print();
  void add_province(Province* p);
  void remove_province(Province* p);
  void add_character(Character c);
  void remove_character(Character c);
  void print_characters();
  void print_provinces();
  void set_capital_id(uint id);
  uint get_capital_id();
  uint get_num_provinces();
  void set_king_id(uint id);
  uint get_king_id();
  void set_money(float money);
  float get_money();
  void set_color_id(uint id);
  uint get_color_id();
  uint get_religion_id();
  uint get_culture_id();
  void set_culture_id(uint id);
  void set_player(bool is_player);
  bool player();
  vector<uint> get_provinces();
  vector<uint> get_characters();
  friend ostream& operator<<(ostream& os, const Country& c);
};