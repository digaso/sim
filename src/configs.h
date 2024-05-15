#pragma once
#include <string>
// world variables
#define INITIAL_YEAR 822
#define INITIAL_MONTH 1
#define INITIAL_DAY 1
// graphics variables
#define NUM_CHUNKS 3
#define TILESIZE 2
#define CHUNKSIZE 64
// generation variables
#define MAXCOUNTRIES 75
#define MAXRELIGIONS MAXCOUNTRIES/3
#define MAXPROVINCES 55
#define MINPROVINCES 40

using namespace std;

enum population_class {
  slaves,
  peasants,
  burghers,
  nobles
};

enum type_province {
  deep_sea = 0,
  sea = 1,
  coastal_sea = 2,
  coast = 3,
  grassland = 4,
  forest = 5,
  tropical_forest = 6,
  desert = 7,
  temperate_desert = 8,
  hill = 9,
  tropical = 10,
  mountain = 11,
  bare = 12,
  taiga = 13,
  tundra = 14,
  coastal_desert = 15,
};

enum game_mode {
  NORMAL,
  DEBUG
};

enum game_velocity {
  PAUSED,
  SLOW,
  MEDIUM,
  FAST
};

typedef enum {
  SCREEN_LOADING,
  SCREEN_MAIN_MENU,
  SCREEN_GAME,
  SCREEN_SETTINGS
} GameScreen;

typedef struct province_properties {
  uint pop;
  string province_name;
  type_province type;
  int color_id;
} province_properties;