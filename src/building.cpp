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

void Building::setup_buildings(World* w) {
  w->addBuilding(Building(0, "Farm", farm));
  w->addBuilding(Building(1, "Mine", mine));
  w->addBuilding(Building(2, "Logging Camps", logging_camp));
  w->addBuilding(Building(3, "Fishery", fishery));
  w->addBuilding(Building(4, "Furrier", furrier));
  w->addBuilding(Building(5, "Port", port));
  w->addBuilding(Building(6, "Dock", dock));
  w->addBuilding(Building(7, "Shipyard", shipyard));
}