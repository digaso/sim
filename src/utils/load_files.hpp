#pragma once
#include "read_csv.hpp"
#include "../world.hpp"

void load_countries(World* world_sim) {
  hashMap countries = read_csv("data/countries.csv");
  int i = 0;
  for (auto row : countries) {
    country c(i++, row[ "name" ], row[ "abrev" ]);
    world_sim->addCountry(c);
  }
  cout << "Countries loaded" << endl;
}

void load_provinces(World* world_sim) {
  hashMap provinces = read_csv("data/provinces.csv");
  int i = 0;
  for (auto row : provinces) {
    string country_abrev = row[ "country" ];
    country* c = world_sim->getCountryByAbrev(country_abrev);
    province p(i++, row[ "name" ], stoi(row[ "population" ]), stof(row[ "latitude" ]), stof(row[ "longitude" ]), c);
    world_sim->addProvince(p);
    if (c != nullptr) {
      province* np = world_sim->getProvinceById(i - 1);
      c->add_province(np);
    }
  }
  cout << "Provinces loaded" << endl;

}

void load_characters(World* world_sim) {
  hashMap characters = read_csv("data/characters.csv");
  int i = 0;
  for (auto row : characters) {
    string country_abrev = row[ "country" ];
    country* country_living = world_sim->getCountryByAbrev(country_abrev);
    character c(i++, row[ "name" ], row[ "birthdate" ], country_living);
    world_sim->addCharacter(&c);
  }
  cout << "Characters loaded" << endl;
}

void  load_files(World* world_sim) {
  load_countries(world_sim);
  load_provinces(world_sim);

  load_characters(world_sim);

}