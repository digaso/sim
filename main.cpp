#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "utils/world.hpp"
using namespace std;
using namespace sf;

Font createFont() {
  Font font;
  if (!font.loadFromFile("font/arial.ttf"))
    cout << "Error loading font" << endl;
  return font;
}


int main() {
  //RenderWindow window(VideoMode(800, 800), "SFML works!");

  World world_sim(1268, 1, 1);

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
  return 0;
}