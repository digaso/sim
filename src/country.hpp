#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "character.hpp"
#include "province.hpp"
#include "diplomacy.hpp"
#include "agents/ai_character.hpp"
#include "economy/market.hpp"

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
  bool* provinces_known;
  uint king_id;
  uint id;
  string name;
  CountryDiplomacy diplomacy;
  uint color_id;
  uint culture_id;
  uint religion_id;
  vector<Market> markets;
  vector<uint> cultures_accepted;
  bool is_player = false;
  float money = 0.00f;
  float income;
  float expenses;
  float tax_income;
  float trade_income;
  float production_income;
  float army_maintenance;
  float navy_maintenance;
  float fort_maintenance;

public:
  Country() {};
  Country(uint id, string name, uint8_t religion_id, World* w);
  ~Country() {};
  uint getId();
  string get_name();
  void set_name(string name);
  string print();
  void knowProvince(uint id);
  void knowMultipleProvinces(vector<uint> ids);
  void add_province(Province* p);
  void remove_province(Province* p);
  void add_character(Character c);
  void remove_character(uint id);
  void print_characters();
  void print_provinces();
  void print_provinces_known();
  void add_province_known(uint id);
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
  void set_cultures_accepted(vector<uint> cultures_accepted);
  vector<uint> get_cultures_accepted();
  bool add_culture_accepted(uint culture_id);
  bool remove_culture_accepted(uint culture_id);
  bool player();
  vector<Market>* get_markets();
  void add_market(Market m);
  void cleanMarkets();

  vector<uint> getProvinces();
  bool* getProvincesKnown();
  vector<uint> getProvinceTypesCount();
  vector<uint> getCharacters();
  friend ostream& operator<<(ostream& os, const Country& c);
};