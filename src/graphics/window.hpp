#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../generation/generation.hpp"
#include "../world.hpp"


#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define TILE_SIZE 4

using namespace sf;
using namespace std;

enum mode {
  build,
  print,
  simulation
};
mode mod = print;

void setup_view(RenderWindow& window, View& view) {
  view.setSize(1200, 1200);
  window.setView(view);
}

void setup_window(RenderWindow& window) {
  window.create(VideoMode(1200, 1200), "Sim");
  window.setFramerateLimit(60);
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
        province_name.setOutlineThickness(1);
        province_name.setOutlineColor(Color::White);
        province_name.setCharacterSize(20);
        province_name.setStyle(sf::Text::Bold | sf::Text::Underlined);
        province_name.setPosition(worldPos.x, worldPos.y);
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

void draw_hud(RenderWindow& window, Text& province_name, Text& date_text) {

  window.draw(province_name);
  window.draw(date_text);
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

  int octaves = 5;

  RectangleShape** map = new RectangleShape * [ NUM_ROWS ];

  for (int i = 0; i < NUM_ROWS; i++) {
    map[ i ] = new RectangleShape[ NUM_COLS ];
  }
  Text province_name;
  Text date_text;
  date_text.setFont(font);
  date_text.setFillColor(Color::Red);
  date_text.setCharacterSize(20);
  date_text.setStyle(sf::Text::Bold);
  date_text.setPosition(10, 0);
  window.setView(view);
  while (window.isOpen()) {

    window.setView(view);
    Event event;
    while (window.pollEvent(event)) {
      check_scroll(event, window, view);
      check_close(event, window);
      check_key_pressed(event, window, view);
      check_mouse_pressed(event, province_name, window, view, font, map, w);
    }
    if (w->advanceDate()) cout << "Turn" << endl;
    date_text.setString(w->getDateString());
    window.clear();
    draw_window(window, map);
    window.setView(window.getDefaultView());
    draw_hud(window, province_name, date_text);
    window.display();
  }
}
