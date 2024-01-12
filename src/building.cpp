#include "building.hpp"
#include "world.hpp"

using namespace std;

void farm(World* w, uint province_id, uint8_t level) {}

void mine(World* w, uint province_id, uint8_t level) {}

void logging_camp(World* w, uint province_id, uint8_t level) {}

void fishery(World* w, uint province_id, uint8_t level) {}

void furrier(World* w, uint province_id, uint8_t level) {}

void port(World* w, uint province_id, uint8_t level) {}

void dock(World* w, uint province_id, uint8_t level) {}

void shipyard(World* w, uint province_id, uint8_t level) {}


Production farm_production = {
  {}, {{0,1}}
};

Production copper_mine_production = {
  {}, {{15,1}}
};

Production iron_mine_production = {
  {}, {{6,1}}
};

Production salt_mine_production = {
  {}, {{2,1}}
};

Production stone_quarry_production = {
  {}, {{16,1}}
};

Production marble_quarry_production = {
  {}, {{17,1}}
};

Production gold_mine_production = {
  {}, {{21,1}}
};

Production silver_mine_production = {
  {}, {{22,1}}
};

Production logging_camp_production = {
  {}, {{7,1}}
};

Production fishery_production = {
  {}, {{3,1}}
};

Production furrier_production = {
  {}, {{4,1}}
};



void Building::setup_buildings(World* w) {
  w->addBuilding(Building(0, "Farm", farm_production, agriculture, farm));
  w->addBuilding(Building(1, "Copper Mine", copper_mine_production, type_building::mineral_building, mine));
  w->addBuilding(Building(2, "Iron Mine", mine));
  w->addBuilding(Building(3, "Salt Mine", mine));
  w->addBuilding(Building(4, "Stone Quarry", mine));
  w->addBuilding(Building(5, "Marble Quarry", mine));
  w->addBuilding(Building(6, "Gold Mine", mine));
  w->addBuilding(Building(7, "Silver Mine", mine));
  w->addBuilding(Building(8, "Logging Camps", logging_camp));
  w->addBuilding(Building(9, "Fishery", fishery));
  w->addBuilding(Building(10, "Furrier", furrier));
  w->addBuilding(Building(11, "Port", port));
  w->addBuilding(Building(12, "Dock", dock));
  w->addBuilding(Building(13, "Shipyard", shipyard));
  w->addBuilding(Building(14, "Wine Cellar", manufactury));
  w->addBuilding(Building(15, "Saltworks", manufactury));
  w->addBuilding(Building(16, "Clothier", manufactury));
  w->addBuilding(Building(17, "Cotton Mill", manufactury));
  w->addBuilding(Building(18, "Ironworks", manufactury));
  //TODO: Add temples and production buildings and fix the rest of the buildings
}