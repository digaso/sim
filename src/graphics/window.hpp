#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../generation/generation.hpp"
#include "../utils/wgen.hpp"
#include "../province.hpp"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
using namespace sf;
using namespace std;

int NUM_ROWS;
int NUM_COLS;


typedef struct {
  int r, g, b;
} pixel;

Color Blue(0, 0, 175);
Color Blue2(10, 10, 235);
Color LightBlue(17, 173, 193);
Color Yellow(247, 182, 158);
Color Grass(91, 179, 97);
Color DarkGrass(30, 136, 117);
Color Mountain(96, 108, 129);
Color Snow(255, 255, 255);

void setup_view(RenderWindow& window, View& view) {
  view.setSize(1200, 1200);
  window.setView(view);
}


void setup_window(RenderWindow& window) {
  window.create(VideoMode(800, 1200), "Sim");
  window.setFramerateLimit(30);
}

void generate_map(RectangleShape** map, uint tile_size, float frequency, int seed, int octaves, province* provinces) {
  float** tiles = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
  uint id_count = 1;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      map[ row ][ col ].setSize(Vector2f(tile_size, tile_size));
      map[ row ][ col ].setPosition(tile_size * col, tile_size * row);
      string province_name;
      float height = tiles[ row ][ col ];
      type_province type;
      uint pop = 500;
      if (height < -0.12f) {
        map[ row ][ col ].setFillColor(Blue);
        type = deep_sea;
        pop = 0;
      }
      else if (height < -0.05f) {
        map[ row ][ col ].setFillColor(Blue2);
        type = sea;
        pop = 0;
      }
      else if (height < 0.052f) {
        map[ row ][ col ].setFillColor(LightBlue);
        type = coastal_sea;
        pop = 0;
      }
      else if (height < 0.059f) {
        map[ row ][ col ].setFillColor(Yellow);
        type = coast;
        province_name = generateCityName();
      }
      else if (height < 0.3f) {
        map[ row ][ col ].setFillColor(Grass);
        type = grassland;
        province_name = generateCityName();
      }
      else if (height < 0.55f) {
        map[ row ][ col ].setFillColor(DarkGrass);
        type = forest;
        province_name = generateCityName();
      }
      else if (height < 0.7f) {
        map[ row ][ col ].setFillColor(Mountain);
        type = hill;
        province_name = generateCityName();
      }
      else {
        map[ row ][ col ].setFillColor(Snow);
        type = mountain;
        province_name = generateCityName();
      };

      province p(id_count++, province_name, pop, row, col, height, type);
      provinces[ row * NUM_COLS + col ] = p;
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

void draw_window(RenderWindow& window, RectangleShape** map) {
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      window.draw(map[ row ][ col ]);
    }
  }
}


void run(World* w) {
  RenderWindow window;
  setup_window(window);
  View view;
  setup_view(window, view);
  sf::Font font;

  uint tile_size = 8;

  NUM_ROWS = window.getSize().y / tile_size;
  NUM_COLS = window.getSize().x / tile_size;

  float frequency = 0.01f;
  srand((unsigned)time(NULL));

  int random = rand();
  int seed = random % 100000;
  int octaves = 4;

  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];
  province* provinces = new province[ NUM_ROWS * NUM_COLS ];
  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  generate_map(map, tile_size, frequency, seed, octaves, provinces);
  //print provinces
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      cout << provinces[ i * NUM_COLS + j ].get_name() << " " << provinces[ i * NUM_COLS + j ].get_type();
      cout << endl;
    }
  }
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      check_scroll(event, window, view);
      check_close(event, window);
      check_key_pressed(event, window, view);

      if (event.type == Event::MouseButtonPressed) {
        Vector2i position = sf::Mouse::getPosition();
        for (int i = 0; i < NUM_ROWS; i++) {
          for (int j = 0; j < NUM_COLS; j++) {
            if (map[ i ][ j ].getGlobalBounds().contains(position.x, position.y)) {
              // If the mouse position is inside a RectangleShape, display the province name
              Text province_name(provinces[ i * NUM_COLS + j ].get_name(), font, 40);
              province_name.setFillColor(Color::Black);
              province_name.setPosition(Mouse::getPosition().x + 5, Mouse::getPosition().y + 5);
              window.draw(province_name);
            }
          }
        }
      }

    }
    window.clear();
    draw_window(window, map);
    window.display();
  }
}
