#include "building.hpp"
#include "world.hpp"

#define UPKEEP_MANUFACTURY 0.20
#define UPKEEP_AGRICULTURE 0.10
#define UPKEEP_MINERAL 0.15
#define UPKEEP_MARITIME 0.20
#define UPKEEP_INFRASTRUCTURE 0.20
#define UPKEEP_COMMERCE 0.20
#define UPKEEP_CULTURE 0.20
#define UPKEEP_RELIGION 0.20
#define UPKEEP_MILITARY 0.20
#define UPKEEP_ADMINISTRATION 0.25
#define UPKEEP_EDUCATION 0.35
#define UPKEEP_HEALTH 0.35
#define UPKEEP_SPECIAL 0.8
#define INFRASTRUCTURE_COST 1
#define SIZE_PEASANTS 1000
#define SIZE_BURGHERS 250
#define SIZE_MONKS 250
#define SIZE_NOBLES 50

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
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 100,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber,1}},
  {}, {{grain,1}}
};

Production copper_mine_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MINERAL,
  base_time : 16,
  construction_goods : { { timber,1 } },
  {}, {{copper,1}}
};

Production iron_mine_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MINERAL,
  base_time : 16,
  construction_goods : {{timber,1}},
  {}, {{iron,1}}
};

Production salt_mine_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 180,
  upkeep : UPKEEP_MINERAL,
  base_time : 14,
  construction_goods : {{timber,1}},
  {}, {{salt,1}}
};

Production stone_quarry_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 180,
  upkeep : UPKEEP_MINERAL,
  base_time : 16,
  construction_goods : {{timber,1}},
  {}, {{stone,1}}
};

Production marble_quarry_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MINERAL,
  base_time : 18,
  construction_goods : {{timber,1}},
  {}, {{marble,1}}
};

Production gold_mine_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 5,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MINERAL,
  base_time : 18,
  construction_goods : { { timber,1 } },
  {}, {{gold,1}}
};

Production silver_mine_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 3,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MINERAL,
  base_time : 18,
  construction_goods : {{timber,1}},
  {}, {{silver,1}}
};

Production logging_camp_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {},
  {}, {{timber,1.5}}
};

Production fishery_production = {
  infrastructure_cost: INFRASTRUCTURE_COST - 0.5,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS - 200,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 1}, {cotton, 0.5}},
  {{cotton, 0.15}}, {{fish,1}}
};

Production furrier_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{fur,1}}
};

Production winery_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{wine,1}}
};

Production clothier_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 3,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 16,
  construction_goods : {{timber, 0.8}, {stone, 1}},
  {{cotton,0.25}}, {{clothes,1}}
};

Production port_production = {
  infrastructure_cost: 0,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 400,
  upkeep : UPKEEP_COMMERCE,
  base_time : 24,
  construction_goods : {{timber, 1.5}, {stone, 1.5}},
  {{timber,0.25}}, {{}}
};

Production dock_production = {
  infrastructure_cost: 0,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 300,
  upkeep : UPKEEP_MILITARY,
  base_time : 16,
  construction_goods : {{timber, 1.0}, {stone, 1.0}},
  {{timber,0.20}}, {{}}
};

Production shipyard_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MILITARY,
  base_time : 16,
  construction_goods : {{timber, 1.0}, {stone, 1.0}},
  {{timber,0.4},{cotton,0.2}}, {}
};

Production armourer_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 12,
  construction_goods : {{timber, 0.5},{iron, 0.5}},
  {{timber,0.1},{leather,0.33}, {iron,0.4}}, {{leather_armour,1}}
};

Production blacksmith_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 12,
  construction_goods : {{timber, 0.5},{iron, 0.5}},
  {{timber,0.15},{iron,0.4}},
  {{spears,1}, {swords,1}}
};

Production bowyer_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 12,
  construction_goods : {{timber, 0.5},{iron, 0.5}},
  {{timber,0.15}},
  {{bows,1}, {crossbows,1}}
};

Production cattle_farm_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {{grain, 0.3}},
  {{meat,0.8}, {leather,1.4}}
};

Production sheep_farm_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{leather,1}, {cotton,1}}
};

Production horse_breeders_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{horses,1}}
};

Production camel_breeders_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{camels,1}}
};

Production elephant_breeders_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{elephants,1}}
};

Production tobacco_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{tobacco,1}}
};

Production cocoa_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{cocoa,1}}
};

Production opium_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{opium,1}}
};

Production fruit_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 100,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 8,
  construction_goods : {{timber, 0.8}},
  {}, {{fruit,1}}
};

Production tea_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{tea,1}}
};

Production coffee_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 120,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{coffee,1}}
};

Production cloves_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{cloves,1}}
};

Production sugar_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{sugar,1}}
};

Production incense_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{incense,1}}
};

Production spices_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 170,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 10,
  construction_goods : {{timber, 0.8}},
  {}, {{spices,1}}
};

Production dye_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 12,
  construction_goods : {{timber, 0.8}},
  {}, {{dyes,1}}
};

Production silk_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 12,
  construction_goods : {{timber, 0.8}},
  {}, {{silk,1}}
};

Production cotton_plantation_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 150,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 12,
  construction_goods : {{timber, 0.8}},
  {}, {{cotton,1.2}}
};

Production ivory_hunters_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS - 300,
  base_cost : 200,
  upkeep : UPKEEP_AGRICULTURE,
  base_time : 12,
  construction_goods : {{timber, 0.8}},
  {{elephants,0.15}}, {{ivory,1.2}}
};

Production libary_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 3,
  worker_class : monks,
  size_workers : SIZE_MONKS,
  base_cost : 250,
  upkeep : UPKEEP_EDUCATION,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 1.0}},
  {{paper, 0.2}}, {}
};

Production university_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 10,
  worker_class : monks,
  size_workers : SIZE_MONKS * 2,
  base_cost : 400,
  upkeep : UPKEEP_EDUCATION + 0.15,
  base_time : 12,
  construction_goods : {{timber, 2.5}, {stone, 2.0}},
  {{paper, 0.5}}, {}
};

Production toolsmith_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 250,
  upkeep : UPKEEP_MANUFACTURY,
  base_time : 12,
  construction_goods : {{timber, 0.8}},
  {{timber, 0.45},{iron, 0.3}}, {{tools,1.3}}
};

Production tax_office_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : nobles,
  size_workers : SIZE_NOBLES,
  base_cost : 250,
  upkeep : UPKEEP_ADMINISTRATION,
  base_time : 12,
  construction_goods : {{timber, 0.8}, {stone, 1.5}},
  {{paper, 0.15}}, {}
};

Production barracks_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : nobles,
  size_workers : SIZE_NOBLES,
  base_cost : 300,
  upkeep : UPKEEP_MILITARY,
  base_time : 12,
  construction_goods : {{timber, 1},{stone, 1}},
  {{leather_armour, 0.2},{swords, 0.2}}, {}
};

Production customs_house_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_NOBLES,
  base_cost : 300,
  upkeep : UPKEEP_ADMINISTRATION,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 1}},
  {{paper, 0.15}}, {}
};

Production town_hall_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : nobles,
  size_workers : SIZE_NOBLES,
  base_cost : 300,
  upkeep : UPKEEP_ADMINISTRATION,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 2}},
  {{paper, 0.15}}, {}
};

Production bathhouse_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 300,
  upkeep : UPKEEP_HEALTH,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 1}},
  {{timber, 0.25}}, {}
};

Production warehouse_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 5,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 500,
  upkeep : UPKEEP_COMMERCE,
  base_time : 12,
  construction_goods : {{timber, 2}, {stone, 2}},
  {{timber, 0.25}, {paper, 0.1}, }, {}
};

Production hospital_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 3,
  worker_class : monks,
  size_workers : SIZE_MONKS,
  base_cost : 300,
  upkeep : UPKEEP_HEALTH,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 1}},
  {{cotton, 0.25}, {opium, 0.2} }, {}
};

Production smallTemple_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : monks,
  size_workers : SIZE_MONKS,
  base_cost : 300,
  upkeep : UPKEEP_RELIGION,
  base_time : 12,
  construction_goods : { { timber, 1.0 }, { stone, 1 } },
  {{wine, 0.2}, {paper, 0.1}, }, {}
};

Production temple_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 5,
  worker_class : monks,
  size_workers : SIZE_MONKS * 2,
  base_cost : 400,
  upkeep : UPKEEP_RELIGION + 0.15,
  base_time : 18,
  {{wine, 0.3}, {paper, 0.5}, }, {}
};

Production wooden_castle_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 5,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 500,
  upkeep : UPKEEP_MILITARY + 0.1,
  base_time : 24,
  construction_goods : {{timber, 2}, {stone, 0.5}},
  {{leather_armour, 0.1}, {spears, 0.1}}, {}
};

Production pallisade_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 2,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 200,
  upkeep : UPKEEP_MILITARY,
  base_time : 12,
  construction_goods : {{timber, 1.5}, {stone, 0.5}},
  {{leather_armour, 0.1}, {spears, 0.1}}, {}
};

Production stone_castle_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 10,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS * 2,
  base_cost : 800,
  upkeep : UPKEEP_MILITARY + 0.35,
  base_time : 36,
  construction_goods : {{timber, 0.5}, {stone, 3.5}},
  {{leather_armour, 0.2}, {spears, 0.4}}, {}
};

Production stone_walls_production = {
  infrastructure_cost: INFRASTRUCTURE_COST * 5,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS,
  base_cost : 400,
  upkeep : UPKEEP_MILITARY + 0.10,
  base_time : 24,
  construction_goods : {{timber, 0.5}, {stone, 2.5}},
  {{leather_armour, 0.1}, {spears, 0.2}}, {}
};

Production market_production = {
  infrastructure_cost: INFRASTRUCTURE_COST,
  worker_class : burghers,
  size_workers : SIZE_BURGHERS,
  base_cost : 200,
  upkeep : UPKEEP_COMMERCE,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 0.5}, {cotton, 0.5}},
  {{cotton, 0.15}}, {}
};

Production road_production = {
  infrastructure_cost: 0,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS / 10,
  base_cost : 100,
  upkeep : UPKEEP_INFRASTRUCTURE,
  base_time : 12,
  construction_goods : {{timber, 0.5}, {stone, 1.0}},
  {}, {}
};

Production wells_production = {
  infrastructure_cost: 0,
  worker_class : peasants,
  size_workers : SIZE_PEASANTS / 10,
  base_cost : 100,
  upkeep : UPKEEP_INFRASTRUCTURE,
  base_time : 12,
  construction_goods : {{timber, 1.0}, {stone, 1.0}},
  {}, {}
};




void farm(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void mine(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void logging_camp(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void fishery(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void furrier(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void port(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();

  Province* prov = w->getProvinceById(province_id);
  Market* market = prov->get_market(w);
  uint8_t infr_per_level = 5;
  for (auto& good : production.inputs) {
    auto amount = good.amount;
    auto good_id = good.good_id;
    market->addDemand(good_id, amount * level);
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
    market->addDemand(good_id, amount * level);
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
    market->addDemand(good_id, amount * level);
  }

  //TODO: change later based on tecnology

  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  market->addProduction(good_id, amount * level);



}

void winery(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void clothier(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount_out = production.outputs.at(0).amount;
  auto good_id_out = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id_out, amount_out * level);

  auto amount_in = production.inputs.at(0).amount;
  auto good_id_in = production.inputs.at(0).good_id;
  market->addDemand(good_id_in, amount_in * level);
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

void pallisade(World* w, uint province_id, uint8_t level, Building b) {}

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

void university(World* w, uint province_id, uint8_t level, Building b) {
}

void toolsmith(World* w, uint province_id, uint8_t level, Building b) {
  auto production = b.get_production();
  auto amount = production.outputs.at(0).amount;
  auto good_id = production.outputs.at(0).good_id;
  Market* market = w->getProvinceById(province_id)->get_market(w);
  market->addProduction(good_id, amount * level);
}

void tax_office(World* w, uint province_id, uint8_t level, Building b) {
}

void barracks(World* w, uint province_id, uint8_t level, Building b) {
}

void customs_house(World* w, uint province_id, uint8_t level, Building b) {
}

void town_hall(World* w, uint province_id, uint8_t level, Building b) {
}

void bathhouse(World* w, uint province_id, uint8_t level, Building b) {
}

void warehouse(World* w, uint province_id, uint8_t level, Building b) {
}

void hospital(World* w, uint province_id, uint8_t level, Building b) {
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
  w->addBuilding(Building(17, "Small Temple", smallTemple_production, religion, small_temple));
  w->addBuilding(Building(18, "Temple", temple_production, religion, temple));
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
  w->addBuilding(Building(39, "Wells", wells_production, infrastructure_building, well));
  w->addBuilding(Building(40, "Bowyer", bowyer_production, manufactury, bowyer));
  w->addBuilding(Building(41, "Pallisade", pallisade_production, military_building, pallisade));
  w->addBuilding(Building(42, "Wooden Castle", wooden_castle_production, military_building, wooden_castle));
  w->addBuilding(Building(43, "Stone Castle", stone_castle_production, military_building, stone_castle));
  w->addBuilding(Building(44, "Stone City Walls", stone_walls_production, military_building, stone_city_walls));
  w->addBuilding(Building(45, "Market", market_production, commerce, market));
  w->addBuilding(Building(46, "Roads", road_production, infrastructure_building, road));
  w->addBuilding(Building(47, "Library", libary_production, type_building::education, library));
  w->addBuilding(Building(48, "University", university_production, type_building::education, university));
  w->addBuilding(Building(49, "Toolsmith", toolsmith_production, type_building::manufactury, toolsmith));
  w->addBuilding(Building(50, "Tax Office", tax_office_production, type_building::administration, tax_office));
  w->addBuilding(Building(51, "Barracks", barracks_production, type_building::military_building, barracks));
  w->addBuilding(Building(52, "Customs House", customs_house_production, type_building::administration, customs_house));
  w->addBuilding(Building(53, "Town Hall", town_hall_production, type_building::administration, town_hall));
  w->addBuilding(Building(54, "Bathhouse", bathhouse_production, type_building::infrastructure_building, bathhouse));
  w->addBuilding(Building(55, "Warehouse", warehouse_production, type_building::infrastructure_building, warehouse));
  w->addBuilding(Building(56, "Hospital", hospital_production, type_building::administration, hospital));
}