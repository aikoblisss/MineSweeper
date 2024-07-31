#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <set>
#include <string>

class Game
{

public:
		struct Mine
		{
			int x;
			int y;
			Color color;
		};

	std::set<std::pair<int, int>> occupiedPositions;
	std::set<std::pair<int, int>> tiles;
	std::set<std::pair<int, int>> flagPositions;

	std::pair<int, int> tile;

	std::vector<Mine> mines;

	const int gridHeight = 800;
	const int gridWidth = 800;
	const int gridScale = 100;
	const int bombs = 10;

	int flags = bombs;
	int gridXScale = gridWidth / gridScale;
	int gridYScale = gridHeight / gridScale;

	bool flagMode = false;
	bool gameIsRunning = true;
	bool win = false;

	Vector2 GetScaledMousePosition(int mouseX, int mouseY);


	void InitializeTiles();
	void UpdateTiles();
	void SpawnMines(int numMines);
	void PrintBombs();
	void DrawCenteredText(const char* text, int fontSize);
	void PrintGrid();
	void HandleFlagModeToggle();
	void PlaceFlags();
	void printFlagCount();
	void EndGame();
	void CheckForWin();
	void GenerateNumMap();
	void Initialize();
	void Run();

};

