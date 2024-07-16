#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "random"
#include <list>
#include "../world.hpp"
#include <raylib.h>
#include "FastNoiseLite.h"
#include "../utils/wgen.hpp"
#include "../configs.h"

#define INITIAL_RADIUS 15

float** setup(int rows, int cols, float frequency, int seed, int octaves, bool _gradient);
void populate_world(World* w);
void set_map_goods(World* w, float frequency, int seed, int octaves);
province_properties* generate_map(World* w);
vector<uint> getProvinceRadius(uint province_id, int radius, World* w);

vector<float> _generate_noise(int rows, int cols, float frequency, int seed, int octaves) {
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
  noise.SetFractalType(FastNoiseLite::FractalType_FBm);
  noise.SetSeed(seed);
  noise.SetFrequency(frequency);
  noise.SetFractalOctaves(octaves);
  noise.SetFractalLacunarity(2.0f);
  noise.SetFractalGain(0.48f);
  noise.SetFractalWeightedStrength(0.0f);

  vector<float> noiseData(rows * cols);
  int index = 0;
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      noiseData[ index++ ] = noise.GetNoise((float)x, (float)y);
    }
  }
  return noiseData;
}

province_properties get_province_type(float height, float moisture) {
  uint pop = 0;
  string province_name;
  type_province type = sea;
  int color = 0;
  if (height < -0.22f) {
    color = 0;
    type = deep_sea;
    pop = 0;
  }
  else if (height < 0.02f) {
    color = 1;
    type = sea;
    pop = 0;
  }
  else if (height < 0.175f) {
    color = 2;
    type = coastal_sea;
    pop = 0;
  }
  else if (height < 0.192f) {
    if (moisture < -0.4)
    {
      color = 4;
      type = coastal_desert;
    }
    else {

      color = 3;
      type = coast;
    }
    province_name = generateCityName();
  }
  else if (height < 0.68f) {
    if (moisture < -0.35) {
      color = 9;
      type = desert;
    }
    else if (moisture < -0.12) {
      color = 10;
      type = temperate_desert;
    }
    else if (moisture < 0.2) {
      color = 5;
      type = grassland;
    }
    else if (moisture < 0.35) {
      color = 6;
      type = forest;
    }
    else if (moisture < 0.55) {
      color = 7;
      type = tropical;
    }
    else {
      color = 8;
      type = tropical_forest;
    }

    province_name = generateCityName();
  }
  else if (height < 0.80f) {
    if (GetRandomValue(0, 100) < 5) {
      color = 16;
      type = wasteland;
    }
    else {

      type = hill;
      color = 11;
      province_name = generateCityName();
    }
  }
  else if (height < 1.29f) {
    if (GetRandomValue(0, 100) < 15) {
      color = 16;
      type = wasteland;
    }
    else if (moisture < -0.4) {
      color = 13;
      type = bare;
    }
    else if (moisture < 0.0) {
      color = 14;
      type = taiga;
    }
    else if (moisture < 0.38) {
      color = 12;
      type = tundra;
    }
    else {
      color = 15;
      type = mountain;
    }
    province_name = generateCityName();
  }
  else {
    if (GetRandomValue(0, 100) < 22) {
      type = wasteland;
      color = 16;
    }
    else {

      color = 15;
      type = mountain;
      province_name = generateCityName();
    }
  }
  return { pop, province_name, type, color };
}

void fix_mistakes(World* w, province_properties* prov_props) {
  uint cols = w->get_num_cols();
  uint rows = w->get_num_rows();
  for (uint row = 0; row < rows; row++) {
    for (uint col = 0; col < cols; col++) {
      Province* p = w->getProvinceById(row * cols + col);
      type_province type = p->get_type();
      if (type == coastal_desert || type == coast) {
        vector<Province*> neighbours = w->get_neighbours_without_diagonal(p);
        bool flag = false;
        for (auto n : neighbours) {
          if (n->get_type() == type_province::sea || n->get_type() == type_province::coastal_sea) {
            flag = true;
            break;
          }
        }
        if (type == coastal_desert && !flag) {
          p->set_type(type_province::desert);
          prov_props[ row * cols + col ].type = type_province::desert;
          prov_props[ row * cols + col ].color_id = 9;
        }
        else if (type == coast && !flag) {
          p->set_type(type_province::grassland);
          prov_props[ row * cols + col ].type = type_province::grassland;
          prov_props[ row * cols + col ].color_id = 5;
        }
      }
    }
  }
}

void find_regions(World* w) {
  bool* visited = new bool[ w->get_num_rows() * w->get_num_cols() ];
  for (uint i = 0; i < w->get_num_rows() * w->get_num_cols(); i++) {
    visited[ i ] = false;
  }
  uint id = 0;
  for (uint row = 0; row < w->get_num_rows(); row++) {
    for (uint col = 0; col < w->get_num_cols(); col++) {
      Province* p = w->getProvinceById(row * w->get_num_cols() + col);
      if (!visited[ row * w->get_num_cols() + col ] && p->get_type() != type_province::sea && p->get_type() != type_province::coastal_sea && p->get_type() != type_province::deep_sea) {
        Region r;
        r.id = id++;
        r.name = generateWord(2, 5);
        r.color_id = GetRandomValue(0, 25);
        queue<Province*> q;
        q.push(p);
        visited[ row * w->get_num_cols() + col ] = true;
        while (!q.empty()) {
          Province* p = q.front();
          q.pop();
          r.provinces.push_back(p);
          p->set_region_id(r.id);
          vector<Province*> neighbours = w->get_land_neighbours_diagonal(p);
          for (auto n : neighbours) {
            if (!visited[ n->get_y() * w->get_num_cols() + n->get_x() ]) {
              q.push(n);
              visited[ n->get_y() * w->get_num_cols() + n->get_x() ] = true;
            }
          }
        }
        w->addRegion(r);
      }
    }
  }

}

province_properties* generate_map(World* w) {
  srand((unsigned)time(NULL));
  int random = rand();
  int seed = random % 100000;
  float frequency = 0.015f;
  int octaves = 10;
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();

  province_properties* prov_props = new province_properties[ rows * cols ];

  float** tiles = setup(rows, cols, frequency, seed, octaves, true);
  seed = random % 1000000;
  float** moisture = setup(rows, cols, frequency / 3, seed, octaves, true);
  uint id_count = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      float height = tiles[ row ][ col ];
      float moisture_level = moisture[ row ][ col ];
      province_properties props = get_province_type(height, moisture_level);
      prov_props[ id_count ] = props;
      Province p(id_count++, props.province_name, props.pop, row, col, height, props.type, moisture_level, w);
      w->addProvince(p, col, row);
    }
  }
  delete[] tiles;
  delete[] moisture;

  cout << "Map generated" << endl;
  find_regions(w);
  cout << "Regions found" << endl;
  fix_mistakes(w, prov_props);
  cout << "Mistakes fixed" << endl;
  set_map_goods(w, frequency / 3, seed, octaves);
  cout << "Goods generated" << endl;
  populate_world(w);
  cout << "World populated" << endl;
  return prov_props;
}

void set_map_goods(World* w, float frequency, int seed, int octaves) {
  vector<Good> goods = w->getGoods();
  uint cols = w->get_num_cols();
  uint rows = w->get_num_rows();
  vector<float**> maps;
  //fill bmap with 0s
  for (uint i = 0; i < goods.size(); i++) {
    float** map = setup(rows, cols, frequency / 2, seed, octaves, false);
    seed += 50;
    maps.push_back(map);
  }
  for (uint i = 0; i < goods.size(); i++) {
    Good g = goods[ i ];
    bool* bmap = new bool[ rows * cols ];
    for (uint i = 0; i < rows * cols; i++) {
      bmap[ i ] = false;
    }
    int count = 0;
    if (g.get_type() != manufactured) {

      for (uint row = 0; row < rows; row++) {
        for (uint col = 0; col < cols; col++) {
          float** map = maps[ i ];
          Province* p = w->getProvinceById(row * cols + col);
          if (p->get_type() == type_province::wasteland) continue;
          if (g.get_name() == "Salt" && (p->get_type() == coastal_desert || p->get_type() == coast)) {
            p->add_goods(g.getId()); count++;
            bmap[ row * cols + col ] = true;
            continue;
          }
          if (g.get_name() == "Timber" && (p->get_type() == forest || p->get_type() == tropical_forest || p->get_type() == tropical || p->get_type() == grassland || p->get_type() == taiga) && GetRandomValue(0, 100) < 90) {
            p->add_goods(g.getId()); count++;
            bmap[ row * cols + col ] = true;
            continue;
          }
          if (g.get_name() == "Timber" && (p->get_type() == coastal_desert || p->get_type() == desert || p->get_type() == bare)) {
            if (GetRandomValue(0, 100) < 20) {
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
            }
            continue;
          }
          if (g.get_name() == "Gold" && p->is_land()) {
            uint8_t chance = GetRandomValue(0, 240);
            if (chance < 233) {
              continue;
            }
            p->add_goods(g.getId()); count++;
            bmap[ row * cols + col ] = true;
            continue;
          }
          if (g.get_type() == catchable && g.is_maritime() && (p->get_type() == coast || p->get_type() == coastal_desert))
          {
            p->add_goods(g.getId()); count++;
            bmap[ row * cols + col ] = true;
          }
          else if (map[ row ][ col ] > 0.5 - (1.0 / g.get_base_value()) && (p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)) {
            if (g.get_name() == "Camels" && (p->get_type() == desert || p->get_type() == coastal_desert || p->get_type() == temperate_desert || p->get_type() == bare)) {
              uint chance = GetRandomValue(0, 100);
              if (chance < 20) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_name() == "Cattle" && (p->get_type() == grassland || p->get_type() == forest || p->get_type() == tropical || p->get_type() == tropical_forest || p->get_type() == temperate_desert)) {
              uint chance = GetRandomValue(0, 100);
              if (chance < 10) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_name() == "Horses" && (p->get_type() == grassland || p->get_type() == forest || p->get_type() == tropical || p->get_type() == tropical_forest || p->get_type() == temperate_desert)) {
              uint chance = GetRandomValue(0, 100);
              if (chance < 10) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }

            if (g.get_name() == "Elephants" && (p->get_type() == type_province::temperate_desert || p->get_type() == type_province::coastal_desert || p->get_type() == type_province::tropical || p->get_type() == type_province::tropical_forest)) {
              if (GetRandomValue(0, 100) < 10) continue;
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_type() == plantable && (p->get_type() == type_province::desert || p->get_type() == type_province::bare))
            {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 30) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_type() == plantable && (p->get_type() == mountain || p->get_type() == coastal_desert || p->get_type() == taiga || p->get_type() == tundra))
            {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 30) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_type() == plantable && (p->get_type() == grassland || p->get_type() == forest || p->get_type() == tropical || p->get_type() == tropical_forest || p->get_type() == temperate_desert))
            {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 20) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_name() == "Stone" && (p->get_type() == grassland || p->get_type() == forest || p->get_type() == tropical || p->get_type() == tropical_forest))
            {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 30) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_name() == "Gems" && (type_province::mountain || p->get_type() == type_province::hill || p->get_type() == type_province::bare || p->get_type() == type_province::tundra || p->get_type() == type_province::taiga)) {
              uint8_t chance = GetRandomValue(0, 10);
              if (chance < 8) {
                continue;
              }
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;
              continue;
            }
            if (g.get_type() == type_good::mineral && (p->get_type() == type_province::mountain || p->get_type() == type_province::hill || p->get_type() == bare || p->get_type() == tundra || p->get_type() == taiga) && p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)
            {
              p->add_goods(g.getId()); count++;
              bmap[ row * cols + col ] = true;

            }
            if (g.get_type() == type_good::plantable)
            {
              p->add_goods(g.getId()); count++;

              bmap[ row * cols + col ] = true;
            }
          }
        }
      }
    }
    //if (count == 0)cout << g.get_name() << " " << count << endl;
    w->getGoodById(g.getId())->set_initial_amount(count);
    w->setGoodMapById(g.getId(), bmap);
  }
  maps.clear();
}

void generate_religions(World* w) {
  uint num_religions = MAXRELIGIONS;
  uint8_t i = 0;
  while (i < num_religions) {
    uint8_t color_id = GetRandomValue(0, 10);
    //chance to be polytheistic
    uint8_t chance = GetRandomValue(0, 100);
    if (chance < 80) {
      Religion r(i, generateReligionName(), color_id, true);
      uint8_t num_gods = GetRandomValue(4, 10);
      uint8_t j = 0;
      while (j < num_gods) {
        God g(j, generateGodName(), i);
        r.add_god(g);
        j++;
      }
      w->addReligion(r);
      i++;
      continue;
    }
    Religion r(i, generateReligionName(), color_id, false);
    God g(0, generateGodName(), i);
    r.add_god(g);
    w->addReligion(r);
    i++;
  }
}

void generate_royalty(World* w, Country* c, Province* p) {
  //generate king
  uint conscientiousness = GetRandomValue(0, 100);
  uint agreeableness = GetRandomValue(0, 100);
  uint neuroticism = GetRandomValue(0, 100);
  uint openness = GetRandomValue(0, 100);
  uint extraversion = GetRandomValue(0, 100);
  uint religion_id = c->get_religion_id();
  string firstName = generateWord(1, 3);
  string lastName = generateWord(2, 4);
  uint age = GetRandomValue(25, 40);
  uint year = 822 - age;
  uint month = GetRandomValue(1, 12);
  uint day = GetRandomValue(1, 28);
  date birth_date = date(day, month, year);
  uint country_living = c->getId();
  uint culture_id = c->get_culture_id();
  uint father_id = -1;
  uint mother_id = -1;
  uint spouse_id;
  uint country_ruling = c->getId();
  bool man = true;
  uint province_born = p->getId();
  uint province_living = p->getId();
  uint id = w->get_characters_size();

  //generate queen
  uint wife_conscientiousness = GetRandomValue(0, 100);
  uint wife_agreeableness = GetRandomValue(0, 100);
  uint wife_neuroticism = GetRandomValue(0, 100);
  uint wife_openness = GetRandomValue(0, 100);
  uint wife_extraversion = GetRandomValue(0, 100);
  string wife_firstName = generateWord(1, 3);
  string wife_lastName = generateWord(2, 4);
  uint wife_age = GetRandomValue(25, 40);
  uint wife_year = 822 - wife_age;
  uint wife_month = GetRandomValue(1, 12);
  uint wife_day = GetRandomValue(1, 28);
  date wife_birth_date = date(wife_day, wife_month, wife_year);
  uint wife_spouse_id = id;
  uint wife_id = id + 1;
  spouse_id = wife_id;
  uint wife_country_ruling = -1;
  bool wife_man = false;

  Character king(id, firstName, lastName, birth_date, country_living, conscientiousness, agreeableness, neuroticism, openness, extraversion, religion_id, culture_id, father_id, mother_id, spouse_id, province_born, province_living, true, man, w, country_ruling);
  Character queen(wife_id, wife_firstName, wife_lastName, wife_birth_date, country_living, wife_conscientiousness, wife_agreeableness, wife_neuroticism, wife_openness, wife_extraversion, religion_id, culture_id, father_id, mother_id, wife_spouse_id, province_born, province_living, false, wife_man, w, wife_country_ruling);
  w->addCharacter(king);
  w->addCharacter(queen);
  c->set_king_id(id);

}

void generate_culture(World* w, Country* c, uint* cultures_count) {

  Culture culture(generateCultureName(c->get_name()), *cultures_count);
  *cultures_count += 1;
  c->set_culture_id(culture.getId());
  culture.set_pop_consumption(culture.generate_pop_consumption(w, c->getId()));
  w->addCulture(culture);
}

void generate_countries(World* w) {
  uint i = 0;
  uint cultures_count = 0;
  while (i < MAXCOUNTRIES) {
    //get random number between 0 and num_cols
    uint x = GetRandomValue(40, w->get_num_cols() - 1 - ((NUM_CHUNKS * 0.25) * CHUNKSIZE));
    //get random number between 0 and num_rows
    uint y = GetRandomValue(40, w->get_num_rows() - 1 - ((NUM_CHUNKS * 0.25) * CHUNKSIZE));
    Province* p = w->getProvinceByCoords(x, y);
    uint num_provinces = GetRandomValue(MINPROVINCES, MAXPROVINCES);
    uint8_t color_id = GetRandomValue(0, 116);
    vector<uint> provinces;

    if (p->get_type() != type_province::sea && p->get_type() != type_province::coastal_sea && p->get_type() != type_province::deep_sea && p->get_type() != wasteland && p->get_country_owner_id() == -1) {
      uint religion_id = GetRandomValue(0, MAXRELIGIONS - 1);
      Country c(i, generateCountryName(), religion_id, w);
      Market market(w);

      generate_culture(w, &c, &cultures_count);
      p->set_country_owner_id(i);
      p->add_population(Population(0, GetRandomValue(8000, 10000), i, p->getId(), c.get_culture_id(), population_class::peasants, religion_id, w));
      p->add_population(Population(1, GetRandomValue(200, 450), i, p->getId(), c.get_culture_id(), population_class::burghers, religion_id, w));
      p->add_population(Population(2, GetRandomValue(50, 150), i, p->getId(), c.get_culture_id(), population_class::monks, religion_id, w));
      p->add_population(Population(3, GetRandomValue(10, 25), i, p->getId(), c.get_culture_id(), population_class::nobles, religion_id, w));
      c.knowMultipleProvinces(getProvinceRadius(p->getId(), INITIAL_RADIUS, w));
      c.set_color_id(color_id);
      c.add_province(p);
      p->upgrade_rank();
      w->addPopulatedLandProvince(p->getId());
      c.set_capital_id(p->getId());
      provinces.push_back(p->getId());
      market.add_province(p->getId());
      generate_royalty(w, &c, p);
      for (uint j = 0; j < num_provinces - 1; j++) {
        p = w->getProvinceById(provinces.at(GetRandomValue(0, provinces.size() - 1)));
        vector<Province*> neighbours = w->get_land_neighbours(p);
        for (auto n : neighbours) {
          if (n->get_country_owner_id() == -1 && n->get_type() != type_province::sea && n->get_type() != type_province::coastal_sea && n->get_type() != type_province::deep_sea) {
            if (n->get_type() == grassland || n->get_type() == forest || n->get_type() == tropical || n->get_type() == tropical_forest) {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 2) continue;
            }
            if (n->get_type() == hill || n->get_type() == mountain || n->get_type() == taiga || n->get_type() == tundra) {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 5) continue;
            }
            if (n->get_type() == desert || n->get_type() == bare) {
              uint8_t chance = GetRandomValue(0, 100);
              if (chance < 10) continue;
            }
            n->add_building(0);
            n->set_country_owner_id(i);
            c.knowMultipleProvinces(getProvinceRadius(n->getId(), INITIAL_RADIUS, w));
            market.add_province(n->getId());
            n->add_population(Population(0, GetRandomValue(4000, 7000), i, n->getId(), c.get_culture_id(), population_class::peasants, religion_id, w));
            n->add_population(Population(1, GetRandomValue(80, 200), i, n->getId(), c.get_culture_id(), population_class::burghers, religion_id, w));
            n->add_population(Population(2, GetRandomValue(50, 100), i, n->getId(), c.get_culture_id(), population_class::monks, religion_id, w));
            n->add_population(Population(3, GetRandomValue(2, 20), i, n->getId(), c.get_culture_id(), population_class::nobles, religion_id, w));
            c.add_province(n);
            w->addPopulatedLandProvince(n->getId());
            provinces.push_back(n->getId());
            j++;
          }

        }
      }
      c.add_market(market);
      w->getCultureById(c.get_culture_id())->set_homelands(provinces);
      w->addCountry(c);
      i++;
    }

  }
}

void populate_world(World* w) {
  generate_religions(w);
  cout << "Religions generated" << endl;
  generate_countries(w);
  cout << "Countries generated" << endl;
}

float getDistanceFromEdge(int x, int y, int rows, int cols) {
  int dist_left = x;
  int dist_right = cols - 1 - x;
  int dist_top = y;
  int dist_bottom = rows - 1 - y;
  return min(min(dist_left, dist_right), min(dist_top, dist_bottom));
}

vector<uint> getProvinceRadius(uint province_id, int radius, World* w) {
  vector<uint> provinces;
  Province* p = w->getProvinceById(province_id);
  uint cols = w->get_num_cols();
  uint rows = w->get_num_rows();

  for (int row = p->get_y() - radius; row <= p->get_y() + radius; row++) {
    for (int col = p->get_x() - radius; col <= p->get_x() + radius; col++) {
      if (row >= 0 && row < rows && col >= 0 && col < cols) {
        Province* n = w->getProvinceByCoords(col, row);
        provinces.push_back(n->getId());

      }
    }
  }

  return provinces;
}

float** setup(int rows, int cols, float frequency, int seed, int octaves, bool _gradient = false) {
  float** tiles = new float* [ rows ];
  for (int i = 0; i < rows; i++) {
    tiles[ i ] = new float[ cols ];
  }

  vector<float> noiseData = _generate_noise(rows, cols, frequency, seed, octaves);
  int index = 0;

  float max_distance_from_edge = min(rows, cols) / 2.0f;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      float distance_from_edge = getDistanceFromEdge(col, row, rows, cols);

      // Normalize distance to the range [0, 1]
      float normalized_distance = distance_from_edge / max_distance_from_edge;

      // Apply the gradient based on the distance from the edge
      float gradient = normalized_distance * 1.9; // Adjust this factor to control the transition smoothness
      float noise_value = noiseData[ index++ ];

      // Modify the noise value based on the gradient
      if (noise_value > 0.0f && _gradient) {
        tiles[ row ][ col ] = noise_value * gradient;
      }
      else
      {
        tiles[ row ][ col ] = noise_value;
      }

    }
  }

  return tiles;
}