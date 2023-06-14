#include <iostream>
#include <random>
#include <vector>
#include <list>
#include "FastNoiseLite.h"
#include "../utils/wgen.hpp"

using namespace sf;


int NUM_ROWS;
int NUM_COLS;


Color DeepSea(0, 0, 175);
Color Sea(10, 10, 235);
Color CoastalSea(17, 173, 193);
Color Beach(247, 182, 158);
Color CoastalDesert(255, 170, 122);
Color Grassland(91, 179, 97);
Color Forest(30, 136, 117);
Color Tropical(30, 255, 30);
Color TropicalForest(0, 100, 0);
Color Desert(253, 253, 150);
Color TemperateDesert(200, 200, 0);
Color Hill(96, 108, 129);
Color Tundra(171, 219, 227);
Color Bare(234, 182, 118);
Color Taiga(109, 247, 146);
Color Mountain(255, 255, 255);

typedef struct province_properties {
  uint pop;
  string province_name;
  type_province type;
  Color color;

} province_properties;


float** setup(int rows, int cols, float frequency, int seed, int octaves);
void set_map_goods(World* w, float frequency, int seed, int octaves);

vector<float> generate_noise(int rows, int cols, float frequency, int seed, int octaves) {
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
  Color color;
  if (height < -0.17f) {
    color = DeepSea;
    type = deep_sea;
    pop = 0;
  }
  else if (height < 0.05f) {
    color = Sea;
    type = sea;
    pop = 0;
  }
  else if (height < 0.18f) {
    color = CoastalSea;
    type = coastal_sea;
    pop = 0;
  }
  else if (height < 0.19f) {
    if (moisture < -0.4)
    {
      color = CoastalDesert;
      type = coastal_desert;
    }
    else {

      color = Beach;
      type = coast;
    }
    province_name = generateCityName();
  }
  else if (height < 0.45f) {
    if (moisture < -0.4) {
      color = Desert;
      type = desert;
    }
    else if (moisture < 0.2) {
      color = Grassland;
      type = grassland;
    }
    else if (moisture < 0.4) {
      color = Forest;
      type = forest;
    }
    else if (moisture < 0.55) {
      color = Tropical;
      type = tropical;
    }
    else if (moisture < 0.99) {
      color = TropicalForest;
      type = tropical_forest;
    }
    province_name = generateCityName();
  }
  else if (height < 0.8f) {
    if (moisture < -0.4) {
      color = Bare;
      type = bare;
    }
    else if (moisture < 0.1) {
      color = Taiga;
      type = taiga;
    }
    else if (moisture < 0.4) {
      color = Tundra;
      type = tundra;
    }
    else {
      color = Hill;
      type = hill;
    }
    province_name = generateCityName();
  }
  else {
    color = Mountain;
    type = mountain;
    province_name = generateCityName();
  }
  return { pop, province_name, type, color };

}


void generate_map(RectangleShape** map, uint tile_size, float frequency, int octaves, World* w) {
  srand((unsigned)time(NULL));
  int random = rand();
  int seed = random % 100000;
  float** tiles = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
  seed = random % 1000000;
  float** moisture = setup(NUM_ROWS, NUM_COLS, frequency / 3, seed, octaves);
  uint id_count = 0;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      map[ row ][ col ].setSize(Vector2f(tile_size, tile_size));
      map[ row ][ col ].setPosition(tile_size * col, tile_size * row);
      float height = tiles[ row ][ col ];
      float moisture_level = moisture[ row ][ col ];
      province_properties props = get_province_type(height, moisture_level);
      map[ row ][ col ].setFillColor(props.color);
      Province p(id_count++, props.province_name, props.pop, row, col, height, props.type, moisture_level);
      w->addProvince(p);
    }
  }
  free(tiles);
  free(moisture);
  set_map_goods(w, frequency / 3, seed, octaves);
}

void set_map_goods(World* w, float frequency, int seed, int octaves) {
  vector<Good> goods = w->getGoods();
  vector<float**> maps;
  for (uint i = 0; i < goods.size(); i++) {
    Good g = goods[ i ];
    float** map = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
    seed += 50;
    maps.push_back(map);
  }
  for (uint i = 0; i < goods.size(); i++) {
    Good g = goods[ i ];
    int count = 0;
    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLS; col++) {
        float** map = maps[ i ];
        Province* p = w->getProvinceById(row * NUM_COLS + col);
        if (g.get_type() == catchable && g.is_maritime() && (p->get_type() == sea || p->get_type() == coastal_sea || p->get_type() == deep_sea))
        {
          p->add_goods(g.get_id()); count++;
        }
        if (map[ row ][ col ] > 0.5 - (0.5 / g.get_base_value())) {
          if (g.get_type() == type_good::mineral && (p->get_type() == type_province::mountain || p->get_type() == type_province::hill || p->get_type() == bare || p->get_type() == tundra || p->get_type() == taiga) && p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)
          {
            p->add_goods(g.get_id()); count++;
          } if (g.get_type() == type_good::plantable && p->get_type() != type_province::sea && p->get_type() != type_province::deep_sea && p->get_type() != type_province::coastal_sea)
          {
            p->add_goods(g.get_id()); count++;
          }
        }
      }
    }
    cout << g.get_name() << " " << count << endl;
  }




}

float** setup(int rows, int cols, float frequency, int seed, int octaves) {

  float** tiles = new float* [ rows ];
  for (int i = 0; i < rows; i++) {
    tiles[ i ] = new float[ cols ];
  }

  vector<float> noiseData = generate_noise(rows, cols, frequency, seed, octaves);
  int index = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      tiles[ row ][ col ] = noiseData[ index++ ];
    }
  }

  return tiles;
}