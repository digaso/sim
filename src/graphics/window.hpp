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
      Color Blue(0, 0, 175);
      Color LightBlue(17, 173, 193);
      Color Yellow(247, 182, 158);
      Color Grass(91, 179, 97);
      Color DarkGrass(30, 136, 117);
      Color Mountain(96, 108, 129);
      Color Snow(255, 255, 255);
      if (height < -0.2f) map[ row ][ col ].setFillColor(Blue);
      else if (height < 0.1f) map[ row ][ col ].setFillColor(LightBlue);
      else if (height < 0.2f) map[ row ][ col ].setFillColor(Yellow);
      else if (height < 0.5f) map[ row ][ col ].setFillColor(Grass);
      else if (height < 0.6f) map[ row ][ col ].setFillColor(DarkGrass);
      else if (height < 0.8f) map[ row ][ col ].setFillColor(Mountain);
      else if (height < 0.9f) map[ row ][ col ].setFillColor(Snow);

    }
  }
}


void check_scroll(Event event, RenderWindow& window, View& view) {
  if (event.type == Event::MouseWheelScrolled) {
    if (event.mouseWheelScroll.delta > 0)
      view.zoom(0.9);
    else
      view.zoom(1.1);
    window.setView(view);
  }
}

void check_close(Event event, RenderWindow& window) {
  if (event.type == Event::Closed)
    window.close();
}


void check_key_pressed(Event event, RenderWindow& window, View& view) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up) view.move(0, -10);
    if (event.key.code == sf::Keyboard::Down) view.move(0, 10);
    if (event.key.code == sf::Keyboard::Left) view.move(-10, 0);
    if (event.key.code == sf::Keyboard::Right) view.move(10, 0);
    window.setView(view);
    if (event.key.code == sf::Keyboard::Escape) {
      window.close();
    }
  }
}

void run() {
  RenderWindow window;
  setup_window(window);
  View view;
  setup_view(window, view);
  uint tile_size = 6;

  const int NUM_ROWS = window.getSize().y / tile_size;
  const int NUM_COLS = window.getSize().x / tile_size;

  float frequency = 0.013f;
  srand((unsigned)time(NULL));

  int random = rand();
  int seed = random % 100000;
  int octaves = 4;

  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];
  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  make_map(map, NUM_ROWS, NUM_COLS, tile_size, frequency, seed, octaves);
  while (window.isOpen()) {
    Event event;
    Vector2i position = sf::Mouse::getPosition();
    while (window.pollEvent(event)) {
      check_scroll(event, window, view);

      check_close(event, window);
      check_key_pressed(event, window, view);
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
