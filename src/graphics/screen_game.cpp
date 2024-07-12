#pragma once
#include <chrono>
#include <filesystem>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "screens.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "render_maps.hpp"
#include "utils.hpp"
#include "../configs.h"


using namespace std;
static auto last_tick = chrono::steady_clock::now();
static int music_id = 0;
static int id_good = 0;
static bool show = false;
static bool goods_map = false;
static bool political_map = false;
static float vol = 0.009;
static Camera2D camera = { 0 };
static Texture2D* texgoods;
static Texture2D geomap;
static Texture2D map;
static Texture2D borders;
static Texture2D fog;
static vector<Music> musics;
static Province* prov;
static Vector2 prevMousePos;
static string province_name, good_name, CountryName, type_prov, coords, population, region_name, kingName, height;
static game_velocity velocity = PAUSED;
static province_properties* p;
static bool dragging = false;
static Vector2 dragStartPos = { 0 };
static Vector2 cameraStartTarget = { 0 };
static game_mode mode = DEBUG;
static int screen_width = 320;
static int screen_height = 240;
static bool country_chosen = false;
static Country* player_country = nullptr;

void drawDebugMode(World* w);
void drawGameMode(World* w);
void drawGUIGood(World* w);
void drawMusic();
void toggleButtons();
void drawProvinceGUI(World* w);
void cameraMoveLetters();
void cameraMove();
void drawPoliticalMap();

void drawPoliticalMap() {
  DrawTexturePro(geomap, { 0, 0, (float)geomap.width, (float)geomap.height }, { 0, 0, geomap.width * camera.zoom, geomap.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera.zoom, map.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  DrawTexturePro(borders, { 0, 0, (float)borders.width, (float)borders.height }, { 0, 0, borders.width * camera.zoom, borders.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  DrawTexturePro(fog, { 0, 0, (float)fog.width, (float)fog.height }, { 0, 0, fog.width * camera.zoom, fog.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
}


void initGameScreen(World* w, province_properties* props) {
  camera.target = { 0 };
  camera.offset = { 0 };
  camera.zoom = 1.8f;
  camera.rotation = 0.0f;
  texgoods = new Texture2D[ w->getGoods().size() ];
  p = props;
  geomap = renderGeographicalMap(w, p);
  cout << "Geographical map loaded" << endl;
  map = renderPoliticalMap(w);
  cout << "Political map loaded" << endl;
  borders = renderBordersMap(w);
  cout << "Borders map loaded" << endl;
  renderGoodMap(w, texgoods);
  string path = "assets/songs";
  for (const auto& entry : filesystem::directory_iterator(path)) {
    string s = entry.path().string();
    musics.push_back(LoadMusicStream(s.c_str()));
  }
  InitAudioDevice();
  SetMusicVolume(musics[ music_id ], vol);
  PlayMusicStream(musics[ music_id ]);
  last_tick = chrono::steady_clock::now();

}

void drawGameMode(World* w) {
  BeginMode2D(camera);
  ClearBackground(RAYWHITE);
  drawPoliticalMap();
  EndMode2D();
  //draw navbar
  DrawRectangle(0, 0, window_width, 50, BLUEVIOLET);
  DrawText(TextFormat("Date: %d-%d-%d", w->getDate().day(), w->getDate().month(), w->getDate().year()), 10, 10, 20, BLACK);
  DrawText(TextFormat("Velocity: %s", getLiteralVelocity(velocity).c_str()), 160, 10, 20, BLACK);
  DrawText(TextFormat("Country: %s", player_country->get_name().c_str()), 410, 10, 20, BLACK);
  DrawText(TextFormat("Money: %.2f", player_country->get_money()), 660, 10, 20, BLACK);
  drawProvinceGUI(w);
  DrawFPS(100, 100);
}

void drawDebugMode(World* w) {
  BeginMode2D(camera);
  ClearBackground(RAYWHITE);
  DrawTexturePro(geomap, { 0, 0, (float)geomap.width, (float)geomap.height }, { 0, 0, geomap.width * camera.zoom , geomap.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  if (political_map) {
    goods_map = false;
    DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera.zoom, map.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    DrawTexturePro(borders, { 0, 0, (float)borders.width, (float)borders.height }, { 0, 0, borders.width * camera.zoom, borders.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  }
  else if (goods_map) {
    political_map = false;
    DrawTexturePro(texgoods[ id_good ], { 0, 0, (float)texgoods[ id_good ].width, (float)texgoods[ id_good ].height }, { 0, 0, texgoods[ id_good ].width * camera.zoom, texgoods[ id_good ].height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
  }
  EndMode2D();
  DrawFPS(130, 100);
  drawGUIGood(w);
  drawMusic();
  toggleButtons();
  //draw velocity
  DrawText(TextFormat("Velocity: %s", getLiteralVelocity(velocity).c_str()), 10, 170, 20, BLACK);
  //draw world date
  DrawText(TextFormat("Date: %d-%d-%d", w->getDate().day(), w->getDate().month(), w->getDate().year()), 10, 130, 20, BLACK);
  //mouse click over provinces with tilesize and show text, but caring about zoom
  drawProvinceGUI(w);

}

void drawGameScreen(World* w) {
  BeginDrawing(); {

    if (mode == PLAY) {
      drawGameMode(w);
    }
    else if (mode == DEBUG) {
      drawDebugMode(w);
    }
  }
  EndDrawing();
}

void updateGameScreen(World* w) {
  prevMousePos = GetMousePosition();
  auto now = chrono::steady_clock::now();
  switch (velocity)
  {
  case PAUSED:
    break;
  case SLOW:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 550) {
      w->updateWorld();
      last_tick = now;
    }
    break;

  case MEDIUM:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 250) {
      w->updateWorld();
      last_tick = now;
    }
    break;
  case FAST:
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 80) {
      w->updateWorld();
      last_tick = now;
    }
    break;
  case SUPER_FAST:
    w->updateWorld();
    break;


  default:
    break;
  }
  UpdateMusicStream(musics[ music_id ]);
  cameraMove();
  if (IsKeyPressed(KEY_SPACE)) velocity = velocity == PAUSED ? SLOW : PAUSED;
  if (IsKeyPressed(KEY_ONE)) velocity = SLOW;
  if (IsKeyPressed(KEY_TWO)) velocity = MEDIUM;
  if (IsKeyPressed(KEY_THREE)) velocity = FAST;
  if (IsKeyPressed(KEY_FOUR)) velocity = SUPER_FAST;
  if (IsKeyPressed(KEY_TAB)) mode = DEBUG;
}

void destroyGameScreen(World* w) {
  UnloadTexture(geomap);
  UnloadTexture(map);
  UnloadTexture(borders);
  for (uint i = 0; i < w->getGoods().size(); i++) {
    UnloadTexture(texgoods[ i ]);
  }
  CloseAudioDevice();
  CloseWindow();
}

void drawTextBox(World* w) {
  char* start_id = new char[ 100 ]();
  char* end_id = new char[ 100 ]();
  GuiTextBox(Rectangle{ 10, 10, 100, 20 }, start_id, 100, true);
  GuiTextBox(Rectangle{ 10, 40, 100, 20 }, end_id, 100, true);
}

void drawGUIGood(World* w) {
  DrawText(TextFormat("Good: %s", w->getGoodById(id_good)->get_name().c_str()), 120, 10, 20, BLACK);
  if (GuiButton(Rectangle{ 10, 10, 100, 20 }, "Change good")) {
    id_good += 1;
    if (id_good >= w->getGoods().size()) id_good = 0;
  }
}

void drawMusic() {
  if (GuiButton(Rectangle{ 10, 40, 100, 20 }, "Change music")) {
    StopMusicStream(musics[ music_id ]);
    music_id += 1;
    if (music_id >= musics.size())
      music_id = 0;
    SetMusicVolume(musics[ music_id ], vol);
    PlayMusicStream(musics[ music_id ]);
  }
}

void toggleButtons() {
  if (GuiButton(Rectangle{ 10, 70, 100, 20 }, "Toggle goods map")) {
    political_map = false;
    goods_map = !goods_map;
  }
  if (GuiButton(Rectangle{ 10, 100, 100, 20 }, "Toggle political map")) {
    goods_map = false;
    political_map = !political_map;
  }
}

void drawProvinceGUI(World* w) {
  Vector2 coordinates = getCoordinatesByMouse(camera);
  int x = (int)coordinates.x;
  int y = (int)coordinates.y;
  Rectangle guiRec = { 10, 130, 310, 300 };
  if (x >= 0 && x < w->get_num_cols() && y >= 0 && y < w->get_num_rows() && IsMouseButtonDown(0) && !CheckCollisionPointRec(GetMousePosition(), guiRec)) {
    prov = w->getProvinceByCoords(x, y);
    province_name = prov->get_name();
    good_name = "Goods: ";
    for (auto& g : prov->get_goods()) {
      good_name += w->getGoodById(g)->get_name() + ", ";
    }
    CountryName = "Country: ";
    kingName = "King Name:";
    if (prov->get_country_owner_id() != -1) {
      Country* country = w->getCountryById(prov->get_country_owner_id());
      CountryName += country->get_name();
      kingName += w->getCharacterById(country->get_king_id())->get_name();
    }
    else {
      CountryName += "No owner";
    }

    type_prov = "Type: " + getLiteralTypeProv(prov->get_type());
    coords = "Position x: " + to_string(prov->get_x()) + " y: " + to_string(prov->get_y());
    population = "Population: " + to_string(prov->get_population_size());
    region_name = "Region: " + w->getRegionById(prov->get_region_id()).name;
    height = "Height: " + to_string(prov->get_height());
    show = true;

  }
  if (show) {
    GuiPanel(guiRec, province_name.c_str());
    GuiLabel(Rectangle{ 15, 150, 310, 20 }, good_name.c_str());
    GuiLabel(Rectangle{ 15, 170, 310, 20 }, CountryName.c_str());
    GuiLabel(Rectangle{ 15, 190, 310, 20 }, type_prov.c_str());
    GuiLabel(Rectangle{ 15, 210, 310, 20 }, coords.c_str());
    GuiLabel(Rectangle{ 15, 230, 310, 20 }, population.c_str());
    GuiLabel(Rectangle{ 15, 250, 310, 20 }, region_name.c_str());
    GuiLabel(Rectangle{ 15, 270, 310, 20 }, kingName.c_str());
    GuiLabel(Rectangle{ 15, 290, 310, 20 }, height.c_str());
    if (GuiButton(Rectangle{ 10, 320, 100, 20 }, "Close")) {
      show = false;
    }
    if (prov->get_country_owner_id() != -1 && GuiButton(Rectangle{ 10,350, 100, 20 }, "Choose country")) {
      country_chosen = true;
      player_country = w->getCountryById(prov->get_country_owner_id());
      mode = PLAY;
      fog = renderFogOfWarMap(w, prov->get_country_owner_id());
      cout << "Fog of war loaded" << endl;
    }
  }

}

void cameraMoveLetters() {
  if (IsKeyDown(KEY_W))
    camera.offset.y += 10 / camera.zoom;
  if (IsKeyDown(KEY_S))
    camera.offset.y -= 10 / camera.zoom;
  if (IsKeyDown(KEY_A))
    camera.offset.x += 10 / camera.zoom;
  if (IsKeyDown(KEY_D))
    camera.offset.x -= 10 / camera.zoom;
}

void cameraMove() {
  // Zoom handling
  float mouseDelta = GetMouseWheelMove();
  float newZoom = camera.zoom + mouseDelta * 0.02f;
  if (newZoom <= 0) newZoom = 0.01f;
  camera.zoom = newZoom;

  // Get the current mouse position
  Vector2 thisPos = GetMousePosition();
  // Calculate the delta from the previous mouse position
  Vector2 delta = Vector2Subtract(thisPos, prevMousePos);
  // Update the previous mouse position
  prevMousePos = thisPos;

  // Handle dragging (panning)
  if (IsMouseButtonDown(0)) {
    Vector2 worldDelta = Vector2Scale(delta, -1.0f / camera.zoom);
    camera.target = Vector2Add(camera.target, worldDelta);
  }
  // Additional panning using keyboard input
  cameraMoveLetters();
}
