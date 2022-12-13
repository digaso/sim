#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "src/world.hpp"
#include "src/character.hpp"
#include "src/utils/read_csv.hpp"

using namespace std;
using namespace sf;

Font createFont() {
  Font font;
  if (!font.loadFromFile("font/arial.ttf"))
    cout << "Error loading font" << endl;
  return font;
}

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
  }
  cout << "Provinces loaded" << endl;

}

void load_characters(World* world_sim) {
  hashMap characters = read_csv("data/characters.csv");
  int i = 0;
  for (auto row : characters) {
    string country_abrev = row[ "country" ];
    int country_id = get_countryId_byAbrev(country_abrev, world_sim->getCountries());
    character c(i++, row[ "name" ], row[ "birthdate" ], country_id);
  }
  cout << "Characters loaded" << endl;
}

void  load_files(World* world_sim) {
  hashMap characters = read_csv("data/characters.csv");
  load_countries(world_sim);
  load_provinces(world_sim);

}

int main() {
  //RenderWindow window(VideoMode(800, 800), "SFML works!");

  World world_sim(1, 1, 1268);
  load_files(&world_sim);
  cout << world_sim.to_string() << endl;

  //CircleShape shape[ 2 ];
  //Font font = createFont();
  //Text text[ 2 ];
  //
  //Clock clock;
  //while (window.isOpen())
  //{
  //  Vector2i mousePos = Mouse::getPosition(window);
  //
  //  Event event;
  //
  //  if (clock.getElapsedTime().asMilliseconds() > 10)
  //  {
  //    printf("1/2 second passed\n");
  //    simulate();
  //    clock.restart();
  //  }
  //  while (window.pollEvent(event))
  //  {
  //    if (event.type == Event::Closed)
  //      window.close();
  //  }
  //
  //  window.clear();
  //  declareCities(font, size, text, shape);
  //  for (int i = 0; i < size; i++)
  //  {
  //    window.draw(shape[ i ]);
  //    window.draw(text[ i ]);
  //  }
  //  window.display();
  //}
  //
  //
  return EXIT_SUCCESS;
}