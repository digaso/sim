#include <raylib.h>
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <raymath.h>
#include "../world.hpp"
#include "../generation/generation.hpp"
#include <filesystem>

#define TILESIZE 8
#define CHUNKSIZE 64

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
Color TemperateDesert = { 200, 200, 0, 255 };
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

Color* colors = new Color[ 11 ]{
  { 255, 0, 0, 255 },
  { 0, 255, 0, 255 },
  { 0, 0, 255, 255 },
  { 255, 255, 0, 255 },
  { 255, 0, 255, 255 },
  { 0, 255, 255, 255},
  { 123, 22,233, 255},
  {234,120,22,255},
  {22,234,120,255},
  {120,22,234,255},
  { 20, 255, 25, 255 }
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
    .width = w->get_num_cols(),
    .height = w->get_num_rows(),
    .mipmaps = 1,
    .format = 7
  };
  ImageResizeNN(&img, w->get_num_cols() * TILESIZE, w->get_num_rows() * TILESIZE);
  return LoadTextureFromImage(img);
}

Texture2D* renderGoodMap(World* w) {
  vector<Good> g = w->getGoods();
  int cols = w->get_num_cols();
  int rows = w->get_num_rows();
  Texture2D* tex = new Texture2D[ g.size() ]; //one image for each good

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
        pixels[ index + 3 ] = (byte)150;
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

  }
  return tex;
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
      pixels[ index + 3 ] = (byte)200;
    }
    else
    {
      pixels[ index + 0 ] = (byte)255;
      pixels[ index + 1 ] = (byte)255;
      pixels[ index + 2 ] = (byte)255;
      pixels[ index + 3 ] = (byte)80;
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
  return LoadTextureFromImage(img);
}

void run(World* w) {
  InitWindow(1200, 800, "SIM");
  SetTargetFPS(60);
  bool map_changed = false;
  bool goods_map = false;
  bool political_map = false;
  uint id_good = 0;
  Camera2D camera = { 0 };
  camera.target = { 0 };
  camera.offset = { 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  province_properties* p = generate_map(w);
  //Texture2D* texgoods = renderGoodMap(w);

  Texture2D Geomap = renderGeographicalMap(w, p);
  Texture2D map = renderPoliticalMap(w);
  Vector2 prevMousePos = GetMousePosition();
  string path = "assets/songs";
  vector<Music> musics;
  InitAudioDevice();
  for (const auto& entry : filesystem::directory_iterator(path)) {
    string s = entry.path().string();
    musics.push_back(LoadMusicStream(s.c_str()));
  }
  int music_id = GetRandomValue(0, musics.size() - 1);
  float vol = 0.001;
  SetMusicVolume(musics[ music_id ], vol);
  PlayMusicStream(musics[ music_id ]);
  while (!WindowShouldClose()) {
    float mouseDelta = GetMouseWheelMove();
    UpdateMusicStream(musics[ music_id ]);
    float newZoom = camera.zoom + mouseDelta * 0.01f;
    if (newZoom <= 0)
      newZoom = 0.01f;

    camera.zoom = newZoom;

    Vector2 thisPos = GetMousePosition();

    Vector2 delta = Vector2Subtract(prevMousePos, thisPos);
    prevMousePos = thisPos;

    if (IsMouseButtonDown(0))
      camera.target = GetScreenToWorld2D(Vector2Add(camera.offset, delta), camera);

    if (IsKeyDown(KEY_W))
      camera.offset.y += 10 / camera.zoom;
    if (IsKeyDown(KEY_S))
      camera.offset.y -= 10 / camera.zoom;
    if (IsKeyDown(KEY_A))
      camera.offset.x += 10 / camera.zoom;
    if (IsKeyDown(KEY_D))
      camera.offset.x -= 10 / camera.zoom;


    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);
    DrawTexturePro(Geomap, { 0, 0, (float)Geomap.width, (float)Geomap.height }, { 0, 0, Geomap.width * camera.zoom, Geomap.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    //if (goods_map) {
    //  DrawTexturePro(texgoods[ id_good ], { 0, 0, (float)texgoods[ id_good ].width, (float)texgoods[ id_good ].height }, { 0, 0, texgoods[ id_good ].width * camera.zoom, texgoods[ id_good ].height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    //}
    if (political_map)
      DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera.zoom, map.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);

    EndMode2D();
    DrawText(TextFormat("Good: %s", w->getGoodById(id_good)->get_name().c_str()), 120, 10, 20, BLACK);
    if (GuiButton(Rectangle{ 10, 10, 100, 20 }, "Change good")) {
      id_good += 1;
      if (id_good >= w->getGoods().size())
        id_good = 0;
    }

    if (GuiButton(Rectangle{ 10, 40, 100, 20 }, "Change music")) {
      StopMusicStream(musics[ music_id ]);
      music_id += 1;
      if (music_id >= musics.size())
        music_id = 0;
      SetMusicVolume(musics[ music_id ], vol);
      PlayMusicStream(musics[ music_id ]);
    }

    if (GuiButton(Rectangle{ 10, 70, 100, 20 }, "Toggle goods map")) {
      goods_map = !goods_map;
    }

    if (GuiButton(Rectangle{ 10, 100, 100, 20 }, "Toggle political map")) {
      political_map = !political_map;
    }

    //slider to music volume

    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();
}