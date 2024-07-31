#pragma once

#include <iostream>
#include <raylib.h>
#include <chrono>
#include <thread>

#include "Game.h"

class HomeScreen
{
public:
	HomeScreen(Game& game);
	void Draw();
	bool ProcessInput();
	void Reset();

private:
	Game& game;
	bool isGameStarted;
};

