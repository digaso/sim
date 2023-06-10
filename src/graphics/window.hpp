#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../generation/generation.hpp"
#include "../utils/wgen.hpp"
#include "../world.hpp"


#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define TILE_SIZE 4

using namespace sf;
using namespace std;

int NUM_ROWS;
int NUM_COLS;

enum mode {
  build,
  print,
  simulation
};
mode mod = print;


Color DeepSea(0, 0, 175);
Color Sea(10, 10, 235);
Color CoastalSea(17, 173, 193);
Color Beach(247, 182, 158);
Color CoastalDesert(255, 170, 122);
Color Grassland(91, 179, 97);
Color Forest(30, 136, 117);
Color Tropical(30, 255, 30);
Color TropicalForest(0, 100, 0);
Color Desert(253, 253, 150);
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
  uint pop;
  string province_name;
  type_province type;
  Color color;

} province_properties;

province_properties get_province_type(float height, float moisture) {
  uint pop = 500;
  string province_name;
  type_province type = sea;
  Color color;
  if (height < -0.17f) {
    color = DeepSea;
    type = deep_sea;
    pop = 0;
  }
  else if (height < 0.05f) {
    color = Sea;
    type = sea;
    pop = 0;
  }
  else if (height < 0.18f) {
    color = CoastalSea;
    type = coastal_sea;
    pop = 0;
  }
  else if (height < 0.19f) {
    if (moisture < -0.4)
    {
      color = CoastalDesert;
      type = coastal_desert;
    }
    else {

      color = Beach;
      type = coast;
    }
    province_name = generateCityName();
  }
  else if (height < 0.45f) {
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
    else if (moisture < 0.55) {
      color = Tropical;
      type = tropical;
    }
    else if (moisture < 0.99) {
      color = TropicalForest;
      type = tropical_forest;
    }
    province_name = generateCityName();
  }
  else if (height < 0.8f) {
    if (moisture < -0.4) {
      color = Bare;
      type = bare;
    }
    else if (moisture < 0.1) {
      color = Taiga;
      type = taiga;
    }
    else if (moisture < 0.4) {
      color = Tundra;
      type = tundra;
    }
    else {
      color = Hill;
      type = hill;
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

void generate_map(RectangleShape** map, uint tile_size, float frequency, int octaves, World* w) {
  srand((unsigned)time(NULL));

  int random = rand();
  int seed = random % 100000;
  float** tiles = setup(NUM_ROWS, NUM_COLS, frequency, seed, octaves);
  seed = random % 1000000;
  float** moisture = setup(NUM_ROWS, NUM_COLS, frequency / 3, seed, octaves);
  uint id_count = 0;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      map[ row ][ col ].setSize(Vector2f(tile_size, tile_size));
      map[ row ][ col ].setPosition(tile_size * col, tile_size * row);
      float height = tiles[ row ][ col ];
      float moisture_level = moisture[ row ][ col ];
      province_properties props = get_province_type(height, moisture_level);
      map[ row ][ col ].setFillColor(props.color);
      Province p(id_count++, props.province_name, props.pop, row, col, height, props.type, moisture_level);
      w->addProvince(p);
    }
  }
  free(tiles);
  free(moisture);
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
    if (event.key.code == sf::Keyboard::W) view.move(0, -10);
    if (event.key.code == sf::Keyboard::S) view.move(0, 10);
    if (event.key.code == sf::Keyboard::A) view.move(-10, 0);
    if (event.key.code == sf::Keyboard::D) view.move(10, 0);
    window.setView(view);
    if (event.key.code == sf::Keyboard::Escape) {
      window.close();
    }
    if (event.key.code == sf::Keyboard::Num1) {
      mod = build;
    }
    if (event.key.code == sf::Keyboard::Num2) {
      mod = print;
    }
    if (event.key.code == sf::Keyboard::Num3) {
      mod = simulation;
    }
  }
  if (event.type == sf::Event::Resized) {
    view.setSize(event.size.width, event.size.height);
    window.setView(view);
  }
}


void print_city_neighbours(Text& province_name, World* w, Font& font, Vector2f worldPos, RectangleShape** map) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      if (map[ i ][ j ].getGlobalBounds().contains(worldPos.x, worldPos.y)) {
        Province* province = w->getProvinceById(i * NUM_COLS + j);
        province_name.setFont(font);
        province_name.setString(province->get_name() + "\n" + province->type_province_to_string(province->get_type()));
        province_name.setFillColor(Color::Black);
        province_name.setCharacterSize(20);
        province_name.setStyle(sf::Text::Bold | sf::Text::Underlined);
        province_name.setPosition(worldPos);
        w->printNeighbours(i * NUM_COLS + j);
      }
    }
  }
}


void check_mouse_pressed(Event event, Text& province_name, RenderWindow& window, View& view, Font& font, RectangleShape** map, World* w) {
  if (event.type == Event::MouseButtonPressed) {
    Vector2i position = sf::Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(position, view);
    switch (mod)
    {
    case print:
      print_city_neighbours(province_name, w, font, worldPos, map);
      break;
    default:
      break;

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

void asd(Province* p) {
  cout << p->get_name() << endl;
}

void run(World* w) {
  RenderWindow window;
  setup_window(window);
  View view;
  setup_view(window, view);
  sf::Font font;

  if (!font.loadFromFile("arial_narrow_7.ttf")) {
    cout << "erro ao carregar fonte" << endl;
    return;
  }

  NUM_ROWS = window.getSize().y / TILE_SIZE;
  NUM_COLS = window.getSize().x / TILE_SIZE;
  w->set_num_rows(NUM_ROWS);
  w->set_num_cols(NUM_COLS);
  float frequency = 0.011f;

  int octaves = 4;

  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];

  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  generate_map(map, TILE_SIZE, frequency, octaves, w);
  Text province_name;
  Good g(0, "Twi", 3.5, &asd);
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      check_scroll(event, window, view);
      check_close(event, window);
      check_key_pressed(event, window, view);
      check_mouse_pressed(event, province_name, window, view, font, map, w);
    }
    window.clear();
    draw_window(window, map);
    window.draw(province_name);
    window.display();
  }
}
