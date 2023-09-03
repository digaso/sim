#include <iostream>
#include <random>
#include <vector>
#include <list>
#include "FastNoiseLite.h"
#include "../utils/wgen.hpp"
#include "../world.hpp"



typedef struct province_properties {
  uint pop;
  string province_name;
  type_province type;
  int color_id;
} province_properties;


float** setup(int rows, int cols, float frequency, int seed, int octaves);
void populate_world(World* w);
void set_map_goods(World* w, float frequency, int seed, int octaves);

vector<float> _generate_noise(int rows, int cols, float frequency, int seed, int octaves) {
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
  noise.SetFractalType(FastNoiseLite::FractalType_FBm);
  noise.SetSeed(seed);
  noise.SetFrequency(frequency);
  noise.SetFractalOctaves(octaves);
  noise.SetFractalLacunarity(2.0f);
  noise.SetFractalGain(0.5f);
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
  uint pop = 500;
  string province_name;
  type_province type = sea;
  int color = 0;
  if (height < -0.15f) {
    color = 0;
    type = deep_sea;
    pop = 0;
  }
  else if (height < 0.05f) {
    color = 1;
    type = sea;
    pop = 0;
  }
  else if (height < 0.18f) {
    color = 2;
    type = coastal_sea;
    pop = 0;
  }
  else if (height < 0.19f) {
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
  else if (height < 0.45f) {
    if (moisture < -0.4) {
      color = 9;
      type = desert;
    }
    else if (moisture < 0.2) {
      color = 5;
      type = grassland;
    }
    else if (moisture < 0.4) {
      color = 6;
      type = forest;
    }
    else if (moisture < 0.55) {
      color = 7;
      type = tropical;
    }
    else if (moisture < 0.99) {
      color = 8;
      type = tropical_forest;
    }
    province_name = generateCityName();
  }
  else if (height < 0.8f) {
    if (moisture < -0.4) {
      color = 13;
      type = bare;
    }
    else if (moisture < 0.1) {
      color = 14;
      type = taiga;
    }
    else if (moisture < 0.4) {
      color = 12;
      type = tundra;
    }
    else {
      color = 11;
      type = hill;
    }
    province_name = generateCityName();
  }
  else {
    color = 15;
    type = mountain;
    province_name = generateCityName();
  }
  return { pop, province_name, type, color };

}


province_properties* generate_map(World* w) {
  srand((unsigned)time(NULL));
  int random = rand();
  int seed = random % 100000;
  float frequency = 0.011f;
  int octaves = 7;
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();

  province_properties* prov_props = new province_properties[ rows * cols ];

  float** tiles = setup(rows, cols, frequency, seed, octaves);
  seed = random % 1000000;
  float** moisture = setup(rows, cols, frequency / 3, seed, octaves);
  uint id_count = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      float height = tiles[ row ][ col ];
      float moisture_level = moisture[ row ][ col ];
      province_properties props = get_province_type(height, moisture_level);
      prov_props[ row * cols + col ] = props;
      Province p(id_count++, props.province_name, props.pop, col, row, height, props.type, moisture_level);
      w->addProvince(p, col, row);
    }
  }
  free(moisture);
  free(tiles);
  cout << "Map generated" << endl;
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
    float** map = setup(rows, cols, frequency / 2, seed, octaves);
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
          if (g.get_name() == "Salt" && (p->get_type() == coastal_desert || p->get_type() == coast)) {
            p->add_goods(g.get_id()); count++;
            bmap[ row * cols + col ] = true;
            continue;
          }
          if (g.get_type() == catchable && g.is_maritime() && (p->get_type() == sea || p->get_type() == coastal_sea || p->get_type() == deep_sea))
          {
            p->add_goods(g.get_id()); count++;

            bmap[ row * cols + col ] = true;
          }
          else if (map[ row ][ col ] > 0.5 - (1.0 / g.get_base_value()) && (p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)) {
            if (g.get_name() == "Ivory" && p->get_type() == type_province::temperate_desert || p->get_type() == type_province::coastal_desert || p->get_type() == type_province::tropical) {
              p->add_goods(g.get_id()); count++;
              bmap[ row * cols + col ] = true;
              continue;

            }
            if (g.get_type() == type_good::mineral && (p->get_type() == type_province::mountain || p->get_type() == type_province::hill || p->get_type() == bare || p->get_type() == tundra || p->get_type() == taiga) && p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)
            {
              p->add_goods(g.get_id()); count++;
              bmap[ row * cols + col ] = true;

            } if (g.get_type() == type_good::plantable && p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)
            {
              p->add_goods(g.get_id()); count++;

              bmap[ row * cols + col ] = true;
            }
            if (g.get_type() == catchable && !g.is_maritime()) {
              p->add_goods(g.get_id()); count++;
              bmap[ row * cols + col ] = true;
            }
          }
        }
      }
    }


    w->setGoodMapById(g.get_id(), bmap);
    //cout << g.get_name() << " " << count << endl;
  }

  maps.clear();
  //int count = 0;
  //for (int row = 0; row < rows; row++) {
  //  for (int col = 0; col < cols; col++) {
  //    Province* p = w->getProvinceById(row * cols + col);
  //    if (p->get_goods().size() == 0)
  //    {
  //      count++;
  //    }
//
  //  }
  //}
  //cout << "No goods: " << count << endl;
}


void generate_religions(World* w) {
  uint8_t num_religions = 10;
}

void generate_countries(World* w) {
  uint8_t num_countries = 50;
  uint8_t i = 0;
  while (i < num_countries) {
    uint x = GetRandomValue(0, w->get_num_cols());
    uint y = GetRandomValue(0, w->get_num_rows());
    Province* p = w->getProvinceByCoords(x, y);

    if (p->get_type() != type_province::sea && p->get_type() != type_province::coastal_sea && p->get_type() != type_province::deep_sea && p->get_country_owner_id() == -1) {
      cout << p->get_name() << endl;
      p->set_country_owner_id(i);
      Country c(i, generateCountryName());
      uint8_t color_id = GetRandomValue(0, 10);
      c.set_color_id(color_id);
      c.add_province(p);
      c.set_capital_id(p->get_id());
      w->addCountry(c);
      i++;
    }
  }

}


void populate_world(World* w) {

  generate_countries(w);
  generate_religions(w);
}
float** setup(int rows, int cols, float frequency, int seed, int octaves) {

  float** tiles = new float* [ rows ];
  for (int i = 0; i < rows; i++) {
    tiles[ i ] = new float[ cols ];
  }

  vector<float> noiseData = _generate_noise(rows, cols, frequency, seed, octaves);
  int index = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      tiles[ row ][ col ] = noiseData[ index++ ];
    }
  }

  return tiles;
}