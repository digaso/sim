#pragma once
#include "raylib.h"
#include "rlgl.h"
#include <raymath.h>
#include "rayutils.h"
#include "../world.hpp"



//loading screen functions
void initLoadingScreen();
void updateLoadingScreen();
void drawLoadingScreen();
void destroyLoadingScreen();

//main menu screen functions

void initMainMenuScreen();
void updateMainMenuScreen();
void drawMainMenuScreen();
void destroyMainMenuScreen();

//game screen functions
void initGameScreen(World* w, province_properties* props);
void updateGameScreen(World* w);
void drawGameScreen(World* w);
void updateWorld(World* w);
void destroyGameScreen();

//settings screen functions
void initSettingsScreen();
void updateSettingsScreen();
void drawSettingsScreen();
void destroySettingsScreen();

