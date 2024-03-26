#pragma once
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


enum population_class {
  slaves,
  peasants,
  burghers,
  nobles
};