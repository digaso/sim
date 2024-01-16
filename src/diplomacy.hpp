#pragma once
#include "world.hpp"

typedef struct Allie {
  Country* country;
  date start_date;
  uint cost = 20;
} Allie;

enum type_subject {
  PERSONAL_UNION,
  VASSAL,
  PROTECTORATE,
  TRIBUTARY,
  COLONY,
  TRADING_COMPANY,
  CLIENT_STATE,
  DOMINION
};

typedef struct Subject {
  Country* country;
  date start_date;
  type_subject type;
  uint cost = 10;
}Subject;



typedef struct Truce {
  Country* country;
  date start_date;
  date end_date;
} Truce;

typedef struct MilitaryAccess {
  Country* country_to;
  Country* country_from;
  date start_date;
  uint cost = 2;
} MilitaryAccess;

typedef struct Guarantee {
  Country* country;
  date start_date;
  uint cost = 5;
} Guarantee;

typedef struct TradePartner {
  Country* country;
  date start_date;
  uint cost = 5;
} TradePartner;

