#pragma once
#include <filesystem>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "screens.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "render_maps.hpp"
#include "../configs.h"

using namespace std;

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
static vector<Music> musics;
static Province* prov;
static string province_name, good_name, CountryName, type_prov, coords, population, region_name, kingName;
static game_velocity velocity = PAUSED;
static province_properties* p;


void drawGUIGood(World* w);
void drawMusic();
void toggleButtons();
void drawProvinceGUI(World* w);
void cameraMoveLetters(Camera2D* camera);
void cameraMove(Vector2* prevMousePos);


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

}

void drawGameScreen(World* w) {
  BeginDrawing();
  {
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
    //draw world date
    DrawText(TextFormat("Date: %d-%d-%d", w->getDate().day(), w->getDate().month(), w->getDate().year()), 10, 130, 20, BLACK);
    //mouse click over provinces with tilesize and show text, but caring about zoom
    drawProvinceGUI(w);

  }
  EndDrawing();
}

void updateGameScreen(World* w) {
  if (velocity != PAUSED) {
    w->updateWorld();
  }
  Vector2 prevMousePos = GetMousePosition();
  UpdateMusicStream(musics[ music_id ]);
  cameraMove(&prevMousePos);
  if (IsKeyPressed(KEY_SPACE)) velocity = velocity == PAUSED ? SLOW : PAUSED;
  if (velocity != PAUSED) w->updateWorld();
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
    goods_map = !goods_map;
  }
  if (GuiButton(Rectangle{ 10, 100, 100, 20 }, "Toggle political map")) {
    political_map = !political_map;
  }
}

void drawProvinceGUI(World* w) {
  Vector2 mousePos = GetMousePosition();
  mousePos = GetScreenToWorld2D(mousePos, camera);
  int x = (int)mousePos.x / (TILESIZE * camera.zoom);
  int y = (int)mousePos.y / (TILESIZE * camera.zoom);
  if (IsMouseButtonPressed(0) || show == true) {
    if (x >= 0 && x < w->get_num_cols() && y >= 0 && y < w->get_num_rows()) {
      show = true;
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

      type_prov = "Type: " + Province::type_province_to_string(prov->get_type());
      coords = "Position x: " + to_string(prov->get_x()) + " y: " + to_string(prov->get_y());
      population = "Population: " + to_string(prov->get_population_size());
      region_name = "Region: " + w->getRegionById(prov->get_region_id()).name;
      GuiPanel(Rectangle{ 10, 130, 310, 300 }, province_name.c_str());
      GuiLabel(Rectangle{ 15, 150, 310, 20 }, good_name.c_str());
      GuiLabel(Rectangle{ 15, 170, 310, 20 }, CountryName.c_str());
      GuiLabel(Rectangle{ 15, 190, 310, 20 }, type_prov.c_str());
      GuiLabel(Rectangle{ 15, 210, 310, 20 }, coords.c_str());
      GuiLabel(Rectangle{ 15, 230, 310, 20 }, population.c_str());
      GuiLabel(Rectangle{ 15, 250, 310, 20 }, region_name.c_str());
      GuiLabel(Rectangle{ 15, 270, 310, 20 }, kingName.c_str());
    }
    else {
      show = false;
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

void cameraMove(Vector2* prevMousePos) {

  float mouseDelta = GetMouseWheelMove();
  float newZoom = camera.zoom + mouseDelta * 0.02f;
  if (newZoom <= 0)
    newZoom = 0.01f;

  camera.zoom = newZoom;
  Vector2 thisPos = GetMousePosition();

  Vector2 delta = Vector2Subtract(*prevMousePos, thisPos);
  *prevMousePos = thisPos;

  if (IsMouseButtonDown(0))
    camera.target = GetScreenToWorld2D(Vector2Add(camera.offset, delta), camera);

  cameraMoveLetters();
}