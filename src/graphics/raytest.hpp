#include <raylib.h>
#include <rlgl.h>
#include "raygui.h"
#include <raymath.h>

#include "../world.hpp"
#include "../generation/generation.hpp"
#define TILESIZE 4
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

Color* colors = new Color[ 16 ]{
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

Image renderMap(World* w, province_properties* p) {
  byte* pixels = new byte[ w->get_num_rows() * w->get_num_cols() * 4 ];
  for (int i = 0; i < w->get_num_rows(); i++) {
    for (int j = 0; j < w->get_num_cols(); j++) {
      int index = i * w->get_num_cols() + j;
      int x = j * TILESIZE;
      int y = i * TILESIZE;
      Color c = colors[ p[ index ].color_id ];
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

  return img;
}




void run(World* w) {
  InitWindow(1200, 800, "raylib [core] example - basic window");
  SetTargetFPS(60);
  bool map_changed = false;
  Texture2D* textures = new Texture2D[ 16 ];
  Camera2D camera = { 0 };
  camera.target = { 0 };
  camera.offset = { 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;


  //  for (int i = 0; i < 16; i++) {
  //    Image img = GenImageColor(TILESIZE, TILESIZE, colors[ i ]);
  //    textures[ i ] = LoadTextureFromImage(img);
  //  }
  //
  //
  province_properties* p = generate_map(w);
  Image img = renderMap(w, p);
  Texture2D map = LoadTextureFromImage(img);
  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_W)) camera.target.y -= 2;
    if (IsKeyDown(KEY_S)) camera.target.y += 2;
    if (IsKeyDown(KEY_A)) camera.target.x -= 2;
    if (IsKeyDown(KEY_D)) camera.target.x += 2;

    if (IsKeyDown(KEY_R)) camera.rotation -= 1.0f;
    if (IsKeyDown(KEY_T)) camera.rotation += 1.0f;

    //mouse wheel to zoom
    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
    camera.zoom = Clamp(camera.zoom, 0.1f, 2.0f);



    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);
    //for (int i = 0; i < w->get_num_rows(); i++) {
    //  for (int j = 0; j < w->get_num_cols(); j++) {
    //    int index = i * w->get_num_cols() + j;
    //    int x = j * TILESIZE;
    //    int y = i * TILESIZE;
    //    DrawTexture(textures[ p[ index ].color_id ], x, y, WHITE);
    //  }
    //}


    DrawTexturePro(map, { 0, 0, (float)map.width, (float)map.height }, { 0, 0, map.width * camera.zoom, map.height * camera.zoom }, { 0, 0 }, camera.rotation, WHITE);
    DrawText("Move the camera with WASD keys and drag the mouse to look around", 10, 10, 20, DARKGRAY);
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}