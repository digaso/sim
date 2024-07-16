#pragma once
#include <string>
#include <vector>
// world variables
#define INITIAL_YEAR 822
#define INITIAL_MONTH 1
#define INITIAL_DAY 1
// graphics variables
#define NUM_CHUNKS 4
#define TILESIZE 2
#define CHUNKSIZE 64
// generation variables
#define MAXCOUNTRIES 140
#define MAXRELIGIONS MAXCOUNTRIES/4
#define MAXPROVINCES 90
#define MINPROVINCES 75



using namespace std;

static int window_width = 1920;
static int window_height = 1080;

enum rank_province {
  village,
  town,
  city
};

enum population_class {
  slaves,
  peasants,
  burghers,
  monks,
  nobles
};

enum type_building {
  agriculture,
  mineral_building,
  maritime,
  manufactury,
  military_building,
  infrastructure_building,
  commerce,
  culture,
  religion,
  administration,
  education,
  health,
  special
};


struct base_input {
  uint good_id;
  uint32_t amount;
};
struct base_output {
  uint good_id;
  uint32_t amount;
};
typedef struct production {
  vector<base_input> inputs = {};
  vector<base_output> outputs = {};
} Production;

enum game_mode {
  PLAY,
  DEBUG
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
  wasteland = 16,
};


enum game_velocity {
  PAUSED,
  SLOW,
  MEDIUM,
  FAST,
  SUPER_FAST
};

typedef enum {
  SCREEN_LOADING,
  SCREEN_MAIN_MENU,
  SCREEN_GAME,
  SCREEN_SETTINGS
} GameScreen;

typedef struct ownership {
  bool country; //true if country, false if character
  uint owner_id;
}Ownership;


typedef struct province_properties {
  uint pop;
  string province_name;
  type_province type;
  int color_id;
} province_properties;

typedef struct buildings_stats {
  uint_fast8_t id;
  uint_fast8_t amount;
  Ownership owner;
} BuildingStats;

