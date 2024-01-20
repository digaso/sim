#pragma once
#include <sstream>
#include <vector>
#include "utils/date.hpp"
#include <utility>
#include <queue>
#include <list>
#include "country.hpp"
#include "economy/trade_route.hpp"
#include "economy/good.hpp"
#include "religion.hpp"
#include "building.hpp"
#include "culture.hpp"
#include "character.hpp"
#include "agents/ai_character.hpp"

using namespace std;

class Building;
class Good;
class AI_Character;
class Character;
class Country;


class World
{
private:
  /* data */
  uint num_rows;
  uint num_cols;
  date world_date;
  Province* provinces;
  vector<Country> countries;
  vector<Character> characters;
  vector<Religion> religions;
  vector<Culture> cultures;
  vector<Good> goods;
  vector<Building> buildings;
  vector<AI_Character> agents;

public:
  World(uint8_t day, uint8_t month, uint year, uint cols, uint rows);
  ~World();
  vector<Province*> get_land_neighbours(Province* p);
  const date getDate() const;
  const string to_string() const;
  string getDateString();
  void setDate(date d);
  void addProvince(Province p, uint x, uint y);
  void addCountry(Country c);
  void addCharacter(Character c);
  void printCountries();
  void setupWorld();
  void addGood(Good g);
  void addReligion(Religion r);
  void addCulture(Culture c);
  void addBuilding(Building b);
  void addAIAgent(AI_Character aic);
  uint get_characters_size();
  Good* getGoodById(uint id);
  bool* getGoodMapById(uint id) { return this->goods.at(id).get_map(); }
  void setGoodMapById(uint id, bool* map) { this->goods.at(id).set_map(map); }
  bool advanceDate();
  Province* getProvinceByCoords(uint x, uint y);
  Country* getCountryById(uint id) {
    if (id < countries.size()) {
      return &countries.at(id);
    }
    return nullptr;
  };
  Province* getProvinceById(uint id);
  Province* getProvinces();
  vector<Religion> getReligions() { return this->religions; }
  vector<Culture> getCultures() { return this->cultures; }
  vector<Character> getCharacters() { return this->characters; }
  vector<AI_Character> getAgents() { return this->agents; }
  Character* getCharacter(uint id) {
    if (id < characters.size()) {
      return &characters.at(id);
    }
    return nullptr;
  }
  const vector<Country> getCountries() const;
  void set_num_rows(uint num_rows) { this->num_rows = num_rows; }
  void set_num_cols(uint num_cols) { this->num_cols = num_cols; }
  uint get_num_rows() { return this->num_rows; }
  uint get_num_cols() { return this->num_cols; }
  vector<Good> getGoods() { return this->goods; }
  void printProvinces();
  void printCharacters();
  void printReligions();
  Religion* getReligionById(uint id);
  vector<Province*> get_path_between_provinces(uint start_id, uint end_id);
  const AI_Character& getAgentById(uint id) const;
  vector<Province*> get_neighbours(Province* p);
  vector<Province*> get_neighbours_without_diagonal(Province* p);
  void updateAgents();
  void updateCharacters();
  void updateCountries();
  void updateProvinces();
  void updateReligions();
  void updateWorld();
};
