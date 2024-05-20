#include "building.hpp"
#include "world.hpp"

using namespace std;

Building::Building() {}

Building::~Building() {}

Building::Building(uint id, string name, Production building_production, type_building building_type, void (*func) (World*, uint, uint8_t, Building))
{
  this->id = id;
  this->name = name;
  this->func = func;
  this->production = building_production;
}


Production farm_production = {
  {}, {{0,2}}
};

Production copper_mine_production = {
  {}, {{15,2}}
};

Production iron_mine_production = {
  {}, {{6,2}}
};

Production salt_mine_production = {
  {}, {{2,2}}
};

Production stone_quarry_production = {
  {}, {{16,2}}
};

Production marble_quarry_production = {
  {}, {{17,2}}
};

Production gold_mine_production = {
  {}, {{21,2}}
};

Production silver_mine_production = {
  {}, {{22,2}}
};

Production logging_camp_production = {
  {}, {{7,2}}
};

Production fishery_production = {
  {}, {{3,1}}
};

Production furrier_production = {
  {}, {{4,1}}
};

Production winery_production = {
  {}, {{1,2}}
};

Production clothier_production = {
  {{4,1}}, {{5,2}}
};

Production port_production = {
  {{46,2}}, {{}}
};

Production dock_production = {
  {{46,2}}, {{}}
};


Production shipyard_production = {
  {{7,2},{4,2}}, {{46,1}, {47,1}, {48,1},{49,1}, {50,1}}
};

Production armourer_production = {
  {{7,1},{33,3}, {6,2}}, {{42,1}, {43,1}, {44,1}}
};

Production blacksmith_production = {
  {{7,1},{6,3}},
  {{35,2}, {38,2}, {40,2}, {41,2}}
};

Production bowyer_production = {
  {{7,1}},
  {{36,2}, {37,2}}
};

Production cattle_farm_production = {
  {},
  {{30,3}, {32,3}}
};

Production sheep_farm_production = {
  {}, {{32,3}, {4,3}}
};

Production horse_breeders_production = {
  {}, {{14,3}}
};

Production camel_breeders_production = {
  {}, {{29,3}}
};

Production elephant_breeders_production = {
  {}, {{44,3}}
};

Production tobacco_plantation_production = {
  {}, {{26,2}}
};

Production cocoa_plantation_production = {
  {}, {{27,2}}
};

Production opium_plantation_production = {
  {}, {{24,2}}
};

Production fruit_plantation_production = {
  {}, {{25,1}}
};

Production tea_plantation_production = {
  {}, {{10,1}}
};

Production coffee_plantation_production = {
  {}, {{11,2}}
};

Production cloves_plantation_production = {
  {}, {{12,2}}
};

Production sugar_plantation_production = {
  {}, {{13,2}}
};

Production incense_plantation_production = {
  {}, {{20,2}}
};

Production spices_plantation_production = {
  {}, {{23,2}}
};

Production dye_plantation_production = {
  {}, {{8,2}}
};

Production silk_plantation_production = {
  {}, {{9,2}}
};

Production cotton_plantation_production = {
  {}, {{4,2}}
};

Production ivory_hunters_production = {
  {{44,1}}, {{28,2}}
};


Production libary_production = {
  {}, {{19,2}}
};

Production no_production = {
  {}, {}
};



void farm(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void mine(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void logging_camp(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void fishery(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void furrier(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void port(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  Province* prov = w->getProvinceById(province_id);
  Market* market = prov->get_market(w);
  uint8_t infr_per_level = 2;
  for (auto& good : production.inputs) {
    auto amount = good.amount;
    auto good_id = good.good_id;
    market->updateDemand(good_id, amount * level);
  }
  prov->set_infrastructure(prov->get_infrastructure() + infr_per_level * level);

}

void dock(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  Province* prov = w->getProvinceById(province_id);
  Market* market = prov->get_market(w);
  uint8_t infr_per_level = 4;
  for (auto& good : production.inputs) {
    auto amount = good.amount;
    auto good_id = good.good_id;
    market->updateDemand(good_id, amount * level);
  }
  prov->set_infrastructure(prov->get_infrastructure() + infr_per_level * level);
}

void shipyard(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  Province* prov = w->getProvinceById(province_id);
  Market* market = prov->get_market(w);
  for (auto& good : production.inputs) {
    auto amount = good.amount;
    auto good_id = good.good_id;
    market->updateDemand(good_id, amount * level);
  }

  //TODO: change later based on tecnology

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  market->updateProduction(good_id, amount * level);



}

void winery(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id, amount * level);
}

void clothier(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount_out = production.outputs.at(0).amount;
  auto good_id_out = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->updateProduction(good_id_out, amount_out * level);

  auto amount_in = production.inputs.at(0).amount;
  auto good_id_in = production.inputs.at(0).good_id;
  market->updateDemand(good_id_in, amount_in * level);
}

void armourer(World* w, uint province_id, uint8_t level, Building b) {}

void small_temple(World* w, uint province_id, uint8_t level, Building b) {}

void temple(World* w, uint province_id, uint8_t level, Building b) {}

void blacksmith(World* w, uint province_id, uint8_t level, Building b) {}

void cattle_farm(World* w, uint province_id, uint8_t level, Building b) {}

void sheep_farm(World* w, uint province_id, uint8_t level, Building b) {}

void camel_breeder(World* w, uint province_id, uint8_t level, Building b) {}

void horse_breeder(World* w, uint province_id, uint8_t level, Building b) {}

void elephant_breeder(World* w, uint province_id, uint8_t level, Building b) {}

void well(World* w, uint province_id, uint8_t level, Building b) {
  Province* prov = w->getProvinceById(province_id);
  prov->set_infrastructure(prov->get_infrastructure() + 2 * level);
}

void bowyer(World* w, uint province_id, uint8_t level, Building b) {}

void wooden_city_walls(World* w, uint province_id, uint8_t level, Building b) {}

void stone_city_walls(World* w, uint province_id, uint8_t level, Building b) {}

void wooden_fort(World* w, uint province_id, uint8_t level, Building b) {}

void wooden_castle(World* w, uint province_id, uint8_t level, Building b) {}

void stone_castle(World* w, uint province_id, uint8_t level, Building b) {}

void stone_fort(World* w, uint province_id, uint8_t level, Building b) {}

void market(World* w, uint province_id, uint8_t level, Building b) {}

void road(World* w, uint province_id, uint8_t level, Building b) {
  Province* prov = w->getProvinceById(province_id);
  prov->set_infrastructure(prov->get_infrastructure() + 5 * level);
}

void library(World* w, uint province_id, uint8_t level, Building b) {
}




void Building::setup_buildings(World* w) {
  w->addBuilding(Building(0, "Grain Farm", farm_production, agriculture, farm));
  w->addBuilding(Building(1, "Copper Mine", copper_mine_production, mineral_building, mine));
  w->addBuilding(Building(2, "Iron Mine", iron_mine_production, mineral_building, mine));
  w->addBuilding(Building(3, "Salt Mine", salt_mine_production, mineral_building, mine));
  w->addBuilding(Building(4, "Stone Quarry", stone_quarry_production, mineral_building, mine));
  w->addBuilding(Building(5, "Marble Quarry", marble_quarry_production, mineral_building, mine));
  w->addBuilding(Building(6, "Gold Mine", gold_mine_production, mineral_building, mine));
  w->addBuilding(Building(7, "Silver Mine", silver_mine_production, agriculture, mine));
  w->addBuilding(Building(8, "Logging Camps", logging_camp_production, agriculture, logging_camp));
  w->addBuilding(Building(9, "Fishery", fishery_production, maritime, fishery));
  w->addBuilding(Building(10, "Furrier", furrier_production, manufactury, furrier));
  w->addBuilding(Building(11, "Port", port_production, maritime, port));
  w->addBuilding(Building(12, "Dock", dock_production, maritime, dock));
  w->addBuilding(Building(13, "Shipyard", shipyard_production, maritime, shipyard));
  w->addBuilding(Building(14, "Winery", winery_production, agriculture, winery));
  w->addBuilding(Building(15, "Clothier", clothier_production, manufactury, clothier));
  w->addBuilding(Building(16, "Armourer", armourer_production, manufactury, armourer));
  w->addBuilding(Building(17, "Small Temple", no_production, religion, small_temple));
  w->addBuilding(Building(18, "Temple", no_production, religion, temple));
  w->addBuilding(Building(19, "Blacksmith", blacksmith_production, manufactury, blacksmith));
  w->addBuilding(Building(20, "Cattle Farm", cattle_farm_production, agriculture, farm));
  w->addBuilding(Building(21, "Sheep Farm", cattle_farm_production, agriculture, farm));
  w->addBuilding(Building(22, "Camel Breeders", camel_breeders_production, agriculture, camel_breeder));
  w->addBuilding(Building(23, "Horse Breeders", horse_breeders_production, agriculture, horse_breeder));
  w->addBuilding(Building(24, "Elephant Breeders", elephant_breeders_production, agriculture, elephant_breeder));
  w->addBuilding(Building(25, "Tobacco Plantation", tobacco_plantation_production, agriculture, farm));
  w->addBuilding(Building(26, "Cocoa Plantation", cocoa_plantation_production, agriculture, farm));
  w->addBuilding(Building(27, "Opium Plantation", opium_plantation_production, agriculture, farm));
  w->addBuilding(Building(28, "Fruit Plantation", fruit_plantation_production, agriculture, farm));
  w->addBuilding(Building(29, "Tea Plantation", tea_plantation_production, agriculture, farm));
  w->addBuilding(Building(30, "Coffee Plantation", coffee_plantation_production, agriculture, farm));
  w->addBuilding(Building(31, "Cloves Plantation", cloves_plantation_production, agriculture, farm));
  w->addBuilding(Building(32, "Sugar Plantation", sugar_plantation_production, agriculture, farm));
  w->addBuilding(Building(33, "Incense Plantation", incense_plantation_production, agriculture, farm));
  w->addBuilding(Building(34, "Spices Plantation", spices_plantation_production, agriculture, farm));
  w->addBuilding(Building(35, "Dye Plantation", dye_plantation_production, agriculture, farm));
  w->addBuilding(Building(36, "Silk Farms", silk_plantation_production, agriculture, farm));
  w->addBuilding(Building(37, "Cotton Plantation", cotton_plantation_production, agriculture, farm));
  w->addBuilding(Building(38, "Ivory Hunters", ivory_hunters_production, manufactury, farm));
  w->addBuilding(Building(39, "Wells", no_production, infrastructure_building, well));
  w->addBuilding(Building(40, "Bowyer", bowyer_production, manufactury, bowyer));
  w->addBuilding(Building(41, "Wooden City Walls", no_production, military_building, wooden_city_walls));
  w->addBuilding(Building(42, "Wooden Fort", no_production, military_building, wooden_fort));
  w->addBuilding(Building(43, "Wooden Castle", no_production, military_building, wooden_castle));
  w->addBuilding(Building(44, "Stone Castle", no_production, military_building, stone_castle));
  w->addBuilding(Building(45, "Stone Fort", no_production, military_building, stone_fort));
  w->addBuilding(Building(46, "Stone City Walls", no_production, military_building, stone_city_walls));
  w->addBuilding(Building(47, "Market", no_production, commerce, market));
  w->addBuilding(Building(48, "Roads", no_production, infrastructure_building, road));
  w->addBuilding(Building(49, "Library", libary_production, type_building::education, library));
}