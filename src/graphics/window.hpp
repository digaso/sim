#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../generation/generation.hpp"
#include "../utils/wgen.hpp"
#include "../province.hpp"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define TILE_SIZE 4
using namespace sf;
using namespace std;

int NUM_ROWS;
int NUM_COLS;


typedef struct {
  int r, g, b;
} pixel;

Color DeepSea(0, 0, 175);
Color Sea(10, 10, 235);
Color CoastalSea(17, 173, 193);
Color Beach(247, 182, 158);
Color Grassland(91, 179, 97);
Color Forest(30, 136, 117);
Color Tropical(30, 255, 30);
Color TropicalForest(0, 100, 0);
Color Desert(255, 255, 0);
Color TemperateDesert(200, 200, 0);
Color Hill(96, 108, 129);
Color Tundra(171, 219, 227);
Color Bare(234, 182, 118);
Color Taiga(109, 247, 146);
Color Mountain(255, 255, 255);

void setup_view(RenderWindow& window, View& view) {
  view.setSize(1200, 1200);
  window.setView(view);
}


void setup_window(RenderWindow& window) {
  window.create(VideoMode(1200, 1200), "Sim");
  window.setFramerateLimit(60);
}

typedef struct province_properties {
  int pop;
  string province_name;
  type_province type;
  Color color;

} province_properties;

province_properties get_province_type(float height, float moisture) {
  uint pop = 500;
  string province_name;
  type_province type;
  Color color;
  if (height < -0.12f) {
    color = DeepSea;
    type = deep_sea;
    pop = 0;
  }
  else if (height < -0.03f) {
    color = Sea;
    type = sea;
    pop = 0;
  }
  else if (height < 0.052f) {
    color = CoastalSea;
    type = coastal_sea;
    pop = 0;
  }
  else if (height < 0.059f) {
    color = Beach;
    type = coast;
    province_name = generateCityName();
  }
  else if (height < 0.35f) {
    if (moisture < -0.4) {
      color = Desert;
      type = desert;
    }
    else if (moisture < 0.2) {
      color = Grassland;
      type = grassland;
    }
    else if (moisture < 0.4) {
      color = Forest;
      type = forest;
    }
    else if (moisture < 0.7) {
      color = Tropical;
      type = tropical;
    }
    else if (moisture < 0.99) {
      color = TropicalForest;
      type = tropical_forest;
    }
    province_name = generateCityName();
  }
  else if (height < 0.7f) {
    if (moisture < -0.4) {
      color = Bare;
      type = bare;
    }
    else if (moisture < 0.1) {
      color = Taiga;
      type = taiga;
    }
    else if (moisture < 0.5) {
      color = Hill;
      type = hill;
    }
    else {
      color = Tundra;
      type = tundra;
    }
    province_name = generateCityName();
  }
  else {
    color = Mountain;
    type = mountain;
    province_name = generateCityName();
  }
  return { pop, province_name, type, color };

}

void generate_map(RectangleShape** map, uint tile_size, float frequency, int octaves, Province* provinces) {
  srand((unsigned)time(NULL));

  int random = rand();
  int seed = random % 100000;
  float** tiles = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
  seed = random % 1000000;
  float** moisture = setup(NUM_ROWS, NUM_COLS, frequency / 2, seed, octaves);
  uint id_count = 1;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      map[ row ][ col ].setSize(Vector2f(tile_size, tile_size));
      map[ row ][ col ].setPosition(tile_size * col, tile_size * row);
      string province_name;
      float height = tiles[ row ][ col ];
      float moisture_level = moisture[ row ][ col ];
      province_properties props = get_province_type(height, moisture_level);
      map[ row ][ col ].setFillColor(props.color);
      Province p(id_count++, props.province_name, props.pop, row, col, height, props.type, moisture_level);
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

void check_mouse_pressed(Event event, Province* provinces, Text& province_name, RenderWindow& window, View& view, Font& font, RectangleShape** map) {
  if (event.type == Event::MouseButtonPressed) {
    Vector2i position = sf::Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(position, view); // Convert mouse position to world coordinates
    for (int i = 0; i < NUM_ROWS; i++) {
      for (int j = 0; j < NUM_COLS; j++) {
        if (map[ i ][ j ].getGlobalBounds().contains(worldPos.x, worldPos.y)) {
          // If the mouse position is inside a RectangleShape, display the province name
          cout << provinces[ i * NUM_COLS + j ].get_name() << endl;
          province_name.setFont(font);
          province_name.setString(provinces[ i * NUM_COLS + j ].get_name() + "\n" + to_string(provinces[ i * NUM_COLS + j ].get_type()));
          province_name.setFillColor(Color::Black);
          province_name.setCharacterSize(20);
          province_name.setStyle(sf::Text::Bold | sf::Text::Underlined);
          province_name.setPosition(worldPos);
        }
      }
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

  if (!font.loadFromFile("arial_narrow_7.ttf")) {
    // Error handling
    return;
  }
  NUM_ROWS = window.getSize().y / TILE_SIZE;
  NUM_COLS = window.getSize().x / TILE_SIZE;

  float frequency = 0.01f;

  int octaves = 4;

  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];
  Province* provinces = new Province[ NUM_ROWS * NUM_COLS ];
  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  generate_map(map, TILE_SIZE, frequency, octaves, provinces);
  //print provinces
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      cout << provinces[ i * NUM_COLS + j ].get_name() << " " << provinces[ i * NUM_COLS + j ].get_type();
      cout << endl;
    }
  }
  Text province_name;
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      check_scroll(event, window, view);
      check_close(event, window);
      check_key_pressed(event, window, view);
      check_mouse_pressed(event, provinces, province_name, window, view, font, map);
    }
    window.clear();
    draw_window(window, map);
    window.draw(province_name);
    window.display();
  }
}
