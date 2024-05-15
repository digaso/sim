#pragma once
#include "raylib.h"
#include "colors.hpp"
#include "../configs.h"
#include "../world.hpp"


Texture2D renderGeographicalMap(World* w, province_properties* p);

void renderGoodMap(World* w, Texture2D* tex);

Texture2D renderPoliticalMap(World* w);

Texture2D renderBordersMap(World* w);
