#pragma once
#include "raylib.h"
#include "colors.hpp"
#include "../configs.h"
#include "../world.hpp"
#include "render_maps.hpp"


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
