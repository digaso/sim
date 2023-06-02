#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../generation/generation.hpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
using namespace sf;
using namespace std;

typedef struct {
  int r, g, b;
} pixel;

void setup_view(RenderWindow& window, View& view) {
  view.setSize(1200, 1200);
  window.setView(view);
}


void setup_window(RenderWindow& window) {
  window.create(VideoMode(1000, 800), "Sim");
  window.setFramerateLimit(60);
}

void make_map(RectangleShape** map, int NUM_ROWS, int NUM_COLS, uint tile_size, float frequency, int seed, int octaves) {
  float** tiles = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      map[ row ][ col ].setSize(Vector2f(tile_size, tile_size));
      map[ row ][ col ].setPosition(tile_size * col, tile_size * row);

      float height = tiles[ row ][ col ];
      if (height < -0.9f) map[ row ][ col ].setFillColor(Color(0, 0, 175));
      else if (height < 0.1f) map[ row ][ col ].setFillColor(Color(17, 173, 193));
      else if (height < 0.2f) map[ row ][ col ].setFillColor(Color(247, 182, 158));
      else if (height < 0.5f) map[ row ][ col ].setFillColor(Color(91, 179, 97));
      else if (height < 0.6f) map[ row ][ col ].setFillColor(Color(30, 136, 117));
      else if (height < 0.7f) map[ row ][ col ].setFillColor(Color(30, 136, 117));
      else if (height < 0.8f) map[ row ][ col ].setFillColor(Color(96, 108, 129));
      else if (height < 0.9f) map[ row ][ col ].setFillColor(Color(255, 255, 255));

      cout << tiles[ row ][ col ] << endl;
    }
  }
}

void run() {
  RenderWindow window;
  setup_window(window);
  View view;
  setup_view(window, view);
  uint tile_size = 8;

  const int NUM_ROWS = window.getSize().y / tile_size;
  const int NUM_COLS = window.getSize().x / tile_size;
  float frequency = 0.01f;
  int seed = 1;
  int octaves = 1;


  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];
  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  while (window.isOpen()) {
    make_map(map, NUM_ROWS, NUM_COLS, tile_size, frequency, seed, octaves);
    Event event;
    Vector2i position = sf::Mouse::getPosition();
    while (window.pollEvent(event)) {
      if (event.type == Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
          view.zoom(0.9);
        else
          view.zoom(1.1);
        window.setView(view);
      }

      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) view.move(0, -10);
        if (event.key.code == sf::Keyboard::Down) view.move(0, 10);
        if (event.key.code == sf::Keyboard::Left) view.move(-10, 0);
        if (event.key.code == sf::Keyboard::Right) view.move(10, 0);
        if (event.key.code == sf::Keyboard::Q) frequency += 0.01f;
        if (event.key.code == sf::Keyboard::A) frequency -= 0.01f;
        if (event.key.code == sf::Keyboard::W) seed += 1;
        if (event.key.code == sf::Keyboard::S) seed -= 1;
        if (event.key.code == sf::Keyboard::E) octaves += 1;
        if (event.key.code == sf::Keyboard::D) octaves -= 1;


        window.setView(view);
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }

    window.clear();

    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLS; col++) {
        window.draw(map[ row ][ col ]);
      }
    }
    window.display();
  }
}
