#include <raylib.h>
#include <rlgl.h>
#include "future"
#include <filesystem>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <raymath.h>
#include "rayutils.h"
#include "../generation/generation.hpp"

using namespace std;

Color DeepSea = { 0, 0, 175, 255 };
Color Sea = { 10, 10, 235, 255 };
Color CoastalSea = { 17, 173, 193, 255 };
Color Beach = { 247, 182, 158, 255 };
Color CoastalDesert = { 255, 170, 122, 255 };
Color Grassland = { 91, 179, 97, 255 };
Color Forest = { 30, 136, 117, 255 };
Color Tropical = { 30, 255, 30, 255 };
Color TropicalForest = { 0, 100, 0, 255 };
Color Desert = { 253, 253, 150, 255 };
Color TemperateDesert = { 220, 255, 130, 255 };
Color Hill = { 96, 108, 129, 255 };
Color Tundra = { 171, 219, 227, 255 };
Color Bare = { 234, 182, 118, 255 };
Color Taiga = { 109, 247, 146, 255 };
Color Mountain = { 255, 255, 255, 255 };

Color* terrain_colors = new Color[ 16 ]{
  DeepSea,
  Sea,
  CoastalSea,
  Beach,
  CoastalDesert,
  Grassland,
  Forest,
  Tropical,
  TropicalForest,
  Desert,
  TemperateDesert,
  Hill,
  Tundra,
  Bare,
  Taiga,
  Mountain
};

Color* colors = new Color[ 116 ]{
OLIVE,
SILVER,
TEAL,
NAVY,
DARKRED,
FIREBRICK,
CRIMSON,
TOMATO,
CORAL,
INDIANRED,
LIGHTCORAL,
DARKSALMON,
SALMON,
LIGHTSALMON,
ORANGERED,
DARKORANGE,
DARKGOLDENROD,
GOLDENROD,
PALEGOLDENROD,
DARKKHAKI,
KHAKI,
YELLOWGREEN,
DARKOLIVEGREEN,
OLIVEDRAB,
LAWNGREEN,
CHARTREUSE,
GREENYELLOW,
FORESTGREEN,
LIMEGREEN,
LIGHTGREEN,
PALEGREEN,
DARKSEAGREEN,
MEDIUMSPRINGGREEN,
SPRINGGREEN,
SEAGREEN,
MEDIUMAQUAMARINE,
MEDIUMSEAGREEN,
LIGHTSEAGREEN,
DARKSLATEGRAY,
DARKCYAN,
AQUA,
CYAN,
LIGHTCYAN,
DARKTURQUOISE,
TURQUOISE,
MEDIUMTURQUOISE,
PALETURQUOISE,
AQUAMARINE,
LIGHTBLUE,
POWDERBLUE,
CADETBLUE,
STEELBLUE,
CORNFLOWERBLUE,
DEEPSKYBLUE,
DODGERBLUE,
LIGHTSKYBLUE,
MIDNIGHTBLUE,
MEDIUMBLUE,
ROYALBLUE,
BLUEVIOLET,
INDIGO,
DARKSLATEBLUE,
SLATEBLUE,
MEDIUMSLATEBLUE,
MEDIUMPURPLE,
DARKMAGENTA,
DARKVIOLET,
DARKORCHID,
MEDIUMORCHID,
THISTLE,
PLUM,
FUSCHIA,
ORCHID,
MEDIUMVIOLETRED,
PALEVIOLETRED,
DEEPPINK,
HOTPINK,
ANTIQUEWHITE,
BISQUE,
BLANCHEDALMOND,
WHEAT,
CORNSILK,
LEMONSHIFFON,
LIGHTGOLDENRODYELLOW,
LIGHTYELLOW,
SADDLEBROWN,
SIENNA,
CHOCOLATE,
PERU,
SANDYBROWN,
BURLYWOOD,
TAN,
ROSYBROWN,
MOCCASIN,
NAVAJOWHITE,
PEACHPUFF,
MISTYROSE,
LAVENDERBLUSH,
LINEN,
OLDLACE,
PAPAYAWHIP,
SEASHELL,
MINTCREAM,
SLATEGRAY,
LIGHTSLATEGRAY,
LIGHTSTEELBLUE,
LAVENDER,
FLORALWHITE,
ALICEBLUE,
GHOSTWHITE,
HONEYDEW,
IVORY,
AZURE,
SNOW,
DIMGRAY,
GAINSBORO,
};

Texture2D renderGeographicalMap(World* w, province_properties* p) {
  byte* pixels = new byte[ w->get_num_rows() * w->get_num_cols() * 4 ];
  for (int i = 0; i < w->get_num_rows(); i++) {
    for (int j = 0; j < w->get_num_cols(); j++) {
      int index = (i * w->get_num_cols() + j);
      //int x = j * TILESIZE;
      //int y = i * TILESIZE;
      Color c = terrain_colors[ p[ index ].color_id ];
      pixels[ (index * 4) + 0 ] = (byte)c.r;
      pixels[ (index * 4) + 1 ] = (byte)c.g;
      pixels[ (index * 4) + 2 ] = (byte)c.b;
      pixels[ (index * 4) + 3 ] = (byte)c.a;
    }
  }
  Image img = {
    .data = pixels,
    .width = int(w->get_num_cols()),
    .height = int(w->get_num_rows()),
    .mipmaps = 1,
    .format = 7
  };
  ImageResizeNN(&img, w->get_num_cols() * TILESIZE, w->get_num_rows() * TILESIZE);
  Texture2D tex = LoadTextureFromImage(img);
  delete[] img.data;
  return tex;
}

void renderGoodMap(World* w, Texture2D* tex) {
  vector<Good> g = w->getGoods();
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();

  for (uint i = 0; i < g.size(); i++) {
    byte* pixels = new byte[ rows * cols * 4 ];
    bool* map = w->getGoodMapById(i);
    for (int j = 0; j < rows * cols; j++) {
      int index = j * 4;
      if (map[ j ]) {
        pixels[ index + 0 ] = (byte)255;
        pixels[ index + 1 ] = (byte)0;
        pixels[ index + 2 ] = (byte)0;
        pixels[ index + 3 ] = (byte)150;
      }
      else {
        pixels[ index + 0 ] = (byte)255;
        pixels[ index + 1 ] = (byte)255;
        pixels[ index + 2 ] = (byte)255;
        pixels[ index + 3 ] = (byte)100;
      }
    }
    Image img = {
      .data = pixels,
      .width = cols,
      .height = rows,
      .mipmaps = 1,
      .format = 7
    };
    ImageResizeNN(&img, cols * TILESIZE, rows * TILESIZE);
    tex[ i ] = LoadTextureFromImage(img);
    delete[] img.data;
  }
  //delete pixels;
}

Texture2D renderPoliticalMap(World* w) {
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();

  byte* pixels = new byte[ rows * cols * 4 ];
  for (int i = 0; i < rows * cols; i++) {
    int index = i * 4;
    Province* prov = w->getProvinceById(i);
    if (prov->get_country_owner_id() != -1)
    {
      uint8_t color_id = w->getCountryById(prov->get_country_owner_id())->get_color_id();
      Color c = colors[ color_id ];
      pixels[ index + 0 ] = (byte)c.r;
      pixels[ index + 1 ] = (byte)c.g;
      pixels[ index + 2 ] = (byte)c.b;
      pixels[ index + 3 ] = (byte)255;
    }
    else
    {
      pixels[ index + 0 ] = (byte)255;
      pixels[ index + 1 ] = (byte)255;
      pixels[ index + 2 ] = (byte)255;
      pixels[ index + 3 ] = (byte)100;
    }
  }
  Image img = {
    .data = pixels,
    .width = cols,
    .height = rows,
    .mipmaps = 1,
    .format = 7
  };
  ImageResizeNN(&img, cols * TILESIZE, rows * TILESIZE);
  Texture2D tex = LoadTextureFromImage(img);
  delete[] img.data;
  return tex;
}

Texture2D renderBordersMap(World* w) {
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();
  byte* pixels = new byte[ rows * cols * 4 ]();
  Color borderColor = { 0, 0, 0, 60 };

  vector<Country> countries = w->getCountries();
  // Iterate over each country
  for (Country country : countries) {
    for (int i : country.get_provinces()) {

      Province* prov = w->getProvinceById(i);
      for (Province* p : w->get_neighbours(prov)) {

        if (p->get_country_owner_id() != prov->get_country_owner_id())
        {
          // Calculate the position of the border
          int index = (prov->get_y() * cols + prov->get_x()) * 4;
          pixels[ index + 0 ] = (byte)borderColor.r;
          pixels[ index + 1 ] = (byte)borderColor.g;
          pixels[ index + 2 ] = (byte)borderColor.b;
          pixels[ index + 3 ] = (byte)borderColor.a;
        }
      }
    }
  }

  Image img = {
    .data = pixels,
    .width = cols , // Unadjusted width for borders
    .height = rows , // Unadjusted height for borders
    .mipmaps = 1,
    .format = 7
  };
  ImageResizeNN(&img, cols * TILESIZE, rows * TILESIZE);
  Texture2D tex = LoadTextureFromImage(img);
  delete[] img.data;
  return tex;
}

enum screen {
  STARTING_LOAD,
  MENU,
  GAME
};

enum game_mode {
  NORMAL,
  DEBUG
};

enum game_velocity {
  PAUSED,
  SLOW,
  MEDIUM,
  FAST
};

void draw_loading_screen() {
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);
    DrawText("Loading...", GetRenderWidth() / 2, GetRenderHeight() / 2, 20, GRAY);
  }
  EndDrawing();
}

void change_game_mode(game_mode* mode) {
  if (IsKeyPressed(KEY_F1))
    *mode = NORMAL;
  if (IsKeyPressed(KEY_F2))
    *mode = DEBUG;
}

void draw_path(World* w, vector<Province*> path) {
  for (uint i = 0; i < path.size() - 1; i++) {
    Vector2 p1 = { (float)path[ i ]->get_x() * TILESIZE, (float)path[ i ]->get_y() * TILESIZE };
    Vector2 p2 = { (float)path[ i + 1 ]->get_x() * TILESIZE, (float)path[ i + 1 ]->get_y() * TILESIZE };
    DrawLineEx(p1, p2, 2, RED);
  }
}

void draw_textbox(World* w) {
  char* start_id = new char[ 100 ]();
  char* end_id = new char[ 100 ]();
  GuiTextBox(Rectangle{ 10, 10, 100, 20 }, start_id, 100, true);
  GuiTextBox(Rectangle{ 10, 40, 100, 20 }, end_id, 100, true);
}

void draw_gui_good(uint* id_good, World* w) {
  DrawText(TextFormat("Good: %s", w->getGoodById(*id_good)->get_name().c_str()), 120, 10, 20, BLACK);
  if (GuiButton(Rectangle{ 10, 10, 100, 20 }, "Change good")) {
    *id_good += 1;
    if (*id_good >= w->getGoods().size())
      *id_good = 0;
  }

}

void draw_music(vector<Music> musics, int& music_id, float& vol) {
  if (GuiButton(Rectangle{ 10, 40, 100, 20 }, "Change music")) {
    StopMusicStream(musics[ music_id ]);
    music_id += 1;
    if (music_id >= musics.size())
      music_id = 0;
    SetMusicVolume(musics[ music_id ], vol);
    PlayMusicStream(musics[ music_id ]);
  }
}

void toggle_buttons(bool* goods_map, bool* political_map) {

  if (GuiButton(Rectangle{ 10, 70, 100, 20 }, "Toggle goods map")) {
    *goods_map = !*goods_map;
  }

  if (GuiButton(Rectangle{ 10, 100, 100, 20 }, "Toggle political map")) {
    *political_map = !*political_map;
  }

}

void draw_province_GUI(Camera2D camera, World* w, bool* show) {
  Vector2 mousePos = GetMousePosition();
  mousePos = GetScreenToWorld2D(mousePos, camera);
  int x = (int)mousePos.x / (TILESIZE * camera.zoom);
  int y = (int)mousePos.y / (TILESIZE * camera.zoom);
  Province* prov;
  string s, s2, CountryName, s3, s4;
  if (IsMouseButtonPressed(0) || *show == true) {
    if (x >= 0 && x < w->get_num_cols() && y >= 0 && y < w->get_num_rows()) {
      *show = true;
      prov = w->getProvinceByCoords(x, y);
      s = prov->get_name();
      s2 = "Goods: ";
      for (auto& g : prov->get_goods()) {
        s2 += w->getGoodById(g)->get_name() + ", ";
      }
      string CountryName = "Country: ";
      string kingName = "King Name:";
      if (prov->get_country_owner_id() != -1) {
        Country* c = w->getCountryById(prov->get_country_owner_id());
        CountryName += c->get_name();
        kingName += w->getCharacterById(c->get_king_id())->get_name();
      }
      else {
        CountryName += "No owner";
      }

      string s3 = "Type: " + Province::type_province_to_string(prov->get_type());
      string s4 = "Position x: " + to_string(prov->get_x()) + " y: " + to_string(prov->get_y());
      string s5 = "Population: " + to_string(prov->get_population_size());
      string s6 = "Region: " + w->getRegionById(prov->get_region_id()).name;
      GuiPanel(Rectangle{ 10, 130, 310, 300 }, s.c_str());
      GuiLabel(Rectangle{ 15, 150, 310, 20 }, s2.c_str());
      GuiLabel(Rectangle{ 15, 170, 310, 20 }, CountryName.c_str());
      GuiLabel(Rectangle{ 15, 190, 310, 20 }, s3.c_str());
      GuiLabel(Rectangle{ 15, 210, 310, 20 }, s4.c_str());
      GuiLabel(Rectangle{ 15, 230, 310, 20 }, s5.c_str());
      GuiLabel(Rectangle{ 15, 250, 310, 20 }, s6.c_str());
      GuiLabel(Rectangle{ 15, 270, 310, 20 }, kingName.c_str());
    }
    else {
      *show = false;
    }
  }
}

void draw_game_screen(Camera2D camera, World* w, Texture2D Geomap, Texture2D* texgoods, Texture2D map, Texture2D borders, bool* goods_map, bool* political_map, uint* id_good, bool* show, int music_id, vector<Music> musics, float vol) {
  BeginDrawing();
  {
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);
    DrawTexturePro(Geomap, { 0, 0, (float)Geomap.width, (float)Geomap.height }, { 0, 0, Geomap.width * camera.zoom, Geomap.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    if (*political_map) {
      *goods_map = false;
      DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera.zoom, map.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
      DrawTexturePro(borders, { 0, 0, (float)borders.width, (float)borders.height }, { 0, 0, borders.width * camera.zoom, borders.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    }
    else if (*goods_map) {
      *political_map = false;
      DrawTexturePro(texgoods[ *id_good ], { 0, 0, (float)texgoods[ *id_good ].width, (float)texgoods[ *id_good ].height }, { 0, 0, texgoods[ *id_good ].width * camera.zoom, texgoods[ *id_good ].height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    }
    EndMode2D();
    DrawFPS(130, 100);
    draw_gui_good(id_good, w);
    draw_music(musics, music_id, vol);
    toggle_buttons(goods_map, political_map);
    //draw world date
    DrawText(TextFormat("Date: %d-%d-%d", w->getDate().day(), w->getDate().month(), w->getDate().year()), 10, 130, 20, BLACK);
    //mouse click over provinces with tilesize and show text, but caring about zoom
    draw_province_GUI(camera, w, show);

  }
  EndDrawing();
}

void camera_move_wasd(Camera2D* camera) {
  if (IsKeyDown(KEY_W))
    camera->offset.y += 10 / camera->zoom;
  if (IsKeyDown(KEY_S))
    camera->offset.y -= 10 / camera->zoom;
  if (IsKeyDown(KEY_A))
    camera->offset.x += 10 / camera->zoom;
  if (IsKeyDown(KEY_D))
    camera->offset.x -= 10 / camera->zoom;
}

void camera_move(Camera2D* camera, Vector2* prevMousePos, int music_id, vector<Music> musics) {

  float mouseDelta = GetMouseWheelMove();
  UpdateMusicStream(musics[ music_id ]);
  float newZoom = camera->zoom + mouseDelta * 0.02f;
  if (newZoom <= 0)
    newZoom = 0.01f;

  camera->zoom = newZoom;


  Vector2 thisPos = GetMousePosition();

  Vector2 delta = Vector2Subtract(*prevMousePos, thisPos);
  *prevMousePos = thisPos;

  if (IsMouseButtonDown(0))
    camera->target = GetScreenToWorld2D(Vector2Add(camera->offset, delta), *camera);

  camera_move_wasd(camera);
}

void run(World* w) {
  InitWindow(1200, 800, "SIM");
  SetTargetFPS(60);
  draw_loading_screen();
  SetTraceLogLevel(LOG_ERROR);
  game_velocity velocity = SLOW;
  bool show = false;
  bool goods_map = false;
  bool political_map = false;
  float vol = 0.009;
  uint id_good = 0;
  Camera2D camera = { 0 };
  camera.target = { 0 };
  camera.offset = { 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.85f;
  screen s = STARTING_LOAD;
  game_mode mode = DEBUG;
  province_properties* p = generate_map(w);
  Texture2D* texgoods = new Texture2D[ w->getGoods().size() ];
  renderGoodMap(w, texgoods);
  Texture2D Geomap;
  Texture2D map;
  Texture2D borders;
  Vector2 prevMousePos = GetMousePosition();
  string path = "assets/songs";
  vector<Music> musics;
  InitAudioDevice();
  for (const auto& entry : filesystem::directory_iterator(path)) {
    string s = entry.path().string();
    musics.push_back(LoadMusicStream(s.c_str()));
  }
  int music_id = GetRandomValue(0, musics.size() - 1);
  SetMusicVolume(musics[ music_id ], vol);
  PlayMusicStream(musics[ music_id ]);
  future<void> fut;
  while (!WindowShouldClose()) {
    camera_move(&camera, &prevMousePos, music_id, musics);

    if (IsKeyPressed(KEY_SPACE)) velocity = velocity == PAUSED ? SLOW : PAUSED;

    if (velocity != PAUSED) fut = async(launch::async, &World::updateWorld, w);
    switch (s) {
    case STARTING_LOAD:
      draw_loading_screen();
      renderGoodMap(w, texgoods);
      Geomap = renderGeographicalMap(w, p);
      map = renderPoliticalMap(w);
      borders = renderBordersMap(w);
      s = GAME;
      break;
    default:
      change_game_mode(&mode);
      draw_game_screen(camera, w, Geomap, texgoods, map, borders, &goods_map, &political_map, &id_good, &show, music_id, musics, vol);
      break;
    }

  }
  UnloadTexture(Geomap);
  UnloadTexture(map);
  UnloadTexture(borders);
  for (uint i = 0; i < w->getGoods().size(); i++) {
    UnloadTexture(texgoods[ i ]);
  }
  CloseAudioDevice();
  CloseWindow();

}