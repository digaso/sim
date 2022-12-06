#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


typedef struct {
  uint id;
  string name;
}Good;

typedef struct {
  uint id;
  string name;
  float population;
  Good goods[ 10 ];
  Vector2i pos;
} City;

City cities[] = {
   { 1, "Lisboa", 6.5, {}, Vector2i(115, 320) },
   { 2, "Porto", 3.9,{} , Vector2i(170, 130) },
   { 3, "Braga", 2.7, {}, Vector2i(265, 70) },
   { 4, "Chaves", 1.7, {}, Vector2i(585, 25) },
   { 5, "Faro", 1.5,{} , Vector2i(405, 550) }
};

void simulate() {

  uint ch = rand() % 5;
  cities[ ch ].population += 0.8;
  ch = rand() % 5;
  cities[ ch ].population -= 0.8;

  return;
}

Font createFont() {
  Font font;
  if (!font.loadFromFile("font/arial.ttf"))
    cout << "Error loading font" << endl;
  return font;
}

void declareCities(Font& font, int size, Text text[], CircleShape shape[]) {
  for (int i = 0; i < size; i++)
  {

    shape[ i ].setRadius(2 * cities[ i ].population);
    shape[ i ].setFillColor(Color::Green);
    shape[ i ].setPosition(cities[ i ].pos.x, cities[ i ].pos.y);
    text[ i ].setFont(font);
    text[ i ].setCharacterSize(24);
    text[ i ].setStyle(Text::Bold);
    text[ i ].setFillColor(Color::White);
    text[ i ].setString(cities[ i ].name + " " + to_string(cities[ i ].population));
    text[ i ].setPosition(cities[ i ].pos.x - 5, cities[ i ].pos.y + 20);
  }
}

int main() {
  RenderWindow window(VideoMode(1200, 1200), "SFML works!");


  int size = sizeof(cities) / sizeof(cities[ 0 ]);


  CircleShape shape[ size ];
  Font font = createFont();
  Text text[ size ];
  declareCities(font, size, text, shape);

  Clock clock;
  while (window.isOpen())
  {
    Vector2i mousePos = Mouse::getPosition(window);

    Event event;

    if (clock.getElapsedTime().asMilliseconds() > 10)
    {
      printf("1/2 second passed\n");
      simulate();
      clock.restart();
    }
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
        window.close();
    }

    window.clear();
    declareCities(font, size, text, shape);
    for (int i = 0; i < size; i++)
    {
      window.draw(shape[ i ]);
      window.draw(text[ i ]);
    }
    window.display();
  }


  return 0;
}