#pragma once
#include <chrono>
#include <filesystem>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "screens.hpp"
#include "thread"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "render_maps.hpp"
#include "utils.hpp"
#include "../configs.h"


using namespace std;
static auto last_tick = chrono::steady_clock::now();
static int music_id = 0;
static int id_good = 0;
static bool show = false, showMarket = false;
static bool goods_map = false;
static bool political_map = false;
static float vol = 0.009;
static Camera2D camera2D = { 0 };
static Camera3D camera3D = { 0 };
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
static bool is3DView = false;

static game_mode mode = DEBUG;
static bool country_chosen = false;
static Country* player_country = nullptr;

void drawDebugMode(World* w);
void drawGameMode(World* w);
void drawGUIGood(World* w);
void drawCountryMarketGUI(World* w);
void drawMusic();
void toggleButtons();
void drawProvinceGUI(World* w);
void cameraMoveLetters();
void cameraMove();
void drawPoliticalMap();
void init_camera3D(int mapWidth, int mapHeight);

void drawPoliticalMap() {
  DrawTexturePro(geomap, { 0, 0, (float)geomap.width, (float)geomap.height }, { 0, 0, geomap.width * camera2D.zoom, geomap.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
  DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera2D.zoom, map.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
  DrawTexturePro(borders, { 0, 0, (float)borders.width, (float)borders.height }, { 0, 0, borders.width * camera2D.zoom, borders.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
  DrawTexturePro(fog, { 0, 0, (float)fog.width, (float)fog.height }, { 0, 0, fog.width * camera2D.zoom, fog.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
}


void init_camera3D(int mapWidth, int mapHeight) {
  camera3D.position = (Vector3){ mapWidth / 2.0f, 100.0f, mapHeight / 2.0f };
  camera3D.target = (Vector3){ mapWidth / 2.0f, 0.0f, mapHeight / 2.0f };
  camera3D.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera3D.fovy = 45.0f;
  camera3D.projection = CAMERA_PERSPECTIVE;
}

void initGameScreen(World* w, province_properties* props) {
  camera2D.target = { 0 };
  camera2D.offset = { 0 };
  camera2D.zoom = 1.8f;
  camera2D.rotation = 0.0f;
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


void render_map_3d(World* w, province_properties* props) {
  static Model terrainModel;
  static Texture2D heightmapTex;
  static bool initialized = false;

  if (!initialized) {
    int rows = w->get_num_rows();
    int cols = w->get_num_cols();
    Image heightmap = GenImageColor(cols, rows, BLACK);
    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols; x++) {
        Province* p = w->getProvinceByCoords(x, y);
        float val = (p->get_height() + 1.0f) / 2.0f; // normalizar de [-1,1] para [0,1]
        Vector4 colorVal = (Vector4){ val, val, val, 1.0f };
        Color c = ColorFromNormalized(colorVal);
        ImageDrawPixel(&heightmap, x, y, c);
      }
    }
    heightmapTex = LoadTextureFromImage(heightmap);
    UnloadImage(heightmap);
    Mesh mesh = GenMeshHeightmap(heightmap, (Vector3) { (float)cols, 40.0f, (float)rows });
    terrainModel = LoadModelFromMesh(mesh);
    terrainModel.materials[ 0 ].maps[ MATERIAL_MAP_DIFFUSE ].texture = heightmapTex;
    initialized = true;
  }

  BeginMode3D(camera3D);
  DrawModel(terrainModel, (Vector3) { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
  EndMode3D();
}


void drawGameMode(World* w) {
  BeginMode2D(camera2D);
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
  drawCountryMarketGUI(w);
  DrawFPS(100, 100);
}

void drawDebugMode(World* w) {
  BeginMode2D(camera2D);
  ClearBackground(RAYWHITE);
  DrawTexturePro(geomap, { 0, 0, (float)geomap.width, (float)geomap.height }, { 0, 0, geomap.width * camera2D.zoom , geomap.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
  if (political_map) {
    goods_map = false;
    DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera2D.zoom, map.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
    DrawTexturePro(borders, { 0, 0, (float)borders.width, (float)borders.height }, { 0, 0, borders.width * camera2D.zoom, borders.height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
  }
  else if (goods_map) {
    political_map = false;
    DrawTexturePro(texgoods[ id_good ], { 0, 0, (float)texgoods[ id_good ].width, (float)texgoods[ id_good ].height }, { 0, 0, texgoods[ id_good ].width * camera2D.zoom, texgoods[ id_good ].height * camera2D.zoom }, { 0, 0 }, camera2D.rotation, WHITE);
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
      if (is3DView) {
        render_map_3d(w, p);
      }
      else {
        drawGameMode(w);
      }
    }
    else if (mode == DEBUG) {
      if (is3DView) {
        render_map_3d(w, p);
      }
      else {
        drawDebugMode(w);
      }
    }
  }
  EndDrawing();
}

void updateWorld(World* w) {
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
    if (chrono::duration_cast<chrono::milliseconds>(now - last_tick).count() > 1) {
      w->updateWorld();
      last_tick = now;
    }
    break;


  default:
    break;
  }
}

void updateGameScreen(World* w) {
  prevMousePos = GetMousePosition();
  if (IsKeyPressed(KEY_TAB)) {
    cout << "Toggling 3D view" << endl;
    is3DView = !is3DView;
  }

  //asdasdas
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
  UnloadTexture(fog);
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

void drawCountryMarketGUI(World* w) {
  if (showMarket) {
    GuiPanel(Rectangle{ 400, 10, 310, 700 }, "Market");
    Market* m = w->getCountryById(prov->get_country_owner_id())->getMarket(0);
    int i = 0;
    for (auto& g : w->getGoods()) {
      GuiLabel(Rectangle{ 410, 40.0f + i * 20, 310, 20 }, g.get_name().c_str());
      GuiLabel(Rectangle{ 475, 40.0f + i * 20, 310, 20 }, TextFormat("Demand: %.2f", m->get_demands()[ g.getId() ]));
      GuiLabel(Rectangle{ 575, 40.0f + i * 20, 310, 20 }, TextFormat("Supply: %.2f", m->get_production()[ g.getId() ]));
      i++;
    }

    if (GuiButton(Rectangle{ 400, 350, 100, 20 }, "Close")) {
      showMarket = false;
    }
  }
}

void drawProvinceGUI(World* w) {
  Vector2 coordinates = getCoordinatesByMouse(camera2D);
  int x = (int)coordinates.x;
  int y = (int)coordinates.y;
  Rectangle guiRec = { 10, 160, 310, 300 };
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
    GuiLabel(Rectangle{ 15, 180, 310, 20 }, good_name.c_str());
    GuiLabel(Rectangle{ 15, 200, 310, 20 }, CountryName.c_str());
    GuiLabel(Rectangle{ 15, 220, 310, 20 }, type_prov.c_str());
    GuiLabel(Rectangle{ 15, 240, 310, 20 }, coords.c_str());
    GuiLabel(Rectangle{ 15, 260, 310, 20 }, population.c_str());
    GuiLabel(Rectangle{ 15, 280, 310, 20 }, region_name.c_str());
    GuiLabel(Rectangle{ 15, 300, 310, 20 }, kingName.c_str());
    GuiLabel(Rectangle{ 15, 320, 310, 20 }, height.c_str());
    if (GuiButton(Rectangle{ 10, 350, 100, 20 }, "Close")) {
      show = false;
    }
    if (prov->get_country_owner_id() != -1 && GuiButton(Rectangle{ 10,380, 100, 20 }, "Choose country")) {
      country_chosen = true;
      player_country = w->getCountryById(prov->get_country_owner_id());
      mode = PLAY;
      fog = renderFogOfWarMap(w, prov->get_country_owner_id());
      cout << "Fog of war loaded" << endl;
    }
    if (prov->get_country_owner_id() != -1) {

      if (GuiButton(Rectangle{ 10, 410, 100, 20 }, "Market")) showMarket = true;
    }
    else showMarket = false;
  }

}

void cameraMoveLetters() {
  float speed = 10.0f;

  if (!is3DView) {
    if (IsKeyDown(KEY_W)) camera2D.offset.y += speed / camera2D.zoom;
    if (IsKeyDown(KEY_S)) camera2D.offset.y -= speed / camera2D.zoom;
    if (IsKeyDown(KEY_A)) camera2D.offset.x += speed / camera2D.zoom;
    if (IsKeyDown(KEY_D)) camera2D.offset.x -= speed / camera2D.zoom;
  }
  else {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera3D.target, camera3D.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera3D.up));
    Vector3 move = { 0 };

    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_Q)) {
      camera3D.position.y += speed * GetFrameTime();
      camera3D.target.y += speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_E)) {
      camera3D.position.y -= speed * GetFrameTime();
      camera3D.target.y -= speed * GetFrameTime();
    }

    camera3D.position = Vector3Add(camera3D.position, Vector3Scale(move, speed * GetFrameTime()));
    camera3D.target = Vector3Add(camera3D.target, Vector3Scale(move, speed * GetFrameTime()));
  }
}

void cameraMove() {
  if (!is3DView) {
    // ----------- 2D CAMERA CONTROLS -----------
    // Zoom handling
    float mouseDelta = GetMouseWheelMove();
    float newZoom = camera2D.zoom + mouseDelta * 0.02f;
    if (newZoom <= 0.01f) newZoom = 0.01f;
    camera2D.zoom = newZoom;

    // Mouse dragging
    Vector2 thisPos = GetMousePosition();
    Vector2 delta = Vector2Subtract(thisPos, prevMousePos);
    prevMousePos = thisPos;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 worldDelta = Vector2Scale(delta, -1.0f / camera2D.zoom);
      camera2D.target = Vector2Add(camera2D.target, worldDelta);
    }

    cameraMoveLetters();

  }
  else {
    // ----------- 3D CAMERA CONTROLS -----------
    cameraMoveLetters();

    // Optional mouse look
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 mouseDelta = GetMouseDelta();
      float rotSpeed = 0.003f;

      Vector3 forward = Vector3Normalize(Vector3Subtract(camera3D.target, camera3D.position));
      Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera3D.up));

      // Rotate horizontally
      Matrix rotY = MatrixRotateY(-mouseDelta.x * rotSpeed);
      forward = Vector3Transform(forward, rotY);

      // Rotate vertically
      Matrix rotX = MatrixRotate(Vector3CrossProduct(forward, camera3D.up), -mouseDelta.y * rotSpeed);
      forward = Vector3Transform(forward, rotX);

      camera3D.target = Vector3Add(camera3D.position, forward);
    }

    // Optional zoom (scroll = move forward/backward)
    float scroll = GetMouseWheelMove();
    if (scroll != 0.0f) {
      Vector3 direction = Vector3Normalize(Vector3Subtract(camera3D.target, camera3D.position));
      Vector3 zoom = Vector3Scale(direction, scroll * 4.0f);
      camera3D.position = Vector3Add(camera3D.position, zoom);
      camera3D.target = Vector3Add(camera3D.target, zoom);
    }
  }
}
