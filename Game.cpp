#include "Game.h"

Vector2 Game::GetScaledMousePosition(int mouseX, int mouseY)
{
	float scaledX = static_cast<float>(mouseX) / gridScale;
	float scaledY = static_cast<float>(mouseY) / gridScale;

	return { scaledX, scaledY };
}

void Game::DrawCenteredText(const char* text, int fontSize)
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	int textWidth = MeasureText(text, 100);
	int x = (screenWidth - textWidth) / 2;
	int y = (screenHeight - 100) / 2;

	DrawText(text, x, y, fontSize, RED);
}

void Game::PrintGrid()
{
	int numOfLines = 8;

	for (int i = 0; i < numOfLines; ++i)
	{
		int lineSpacing = i * 100;
		DrawLine(lineSpacing, 0, lineSpacing, 800, WHITE);
		DrawLine(0, lineSpacing, 800, lineSpacing, WHITE);
	}
}

struct Tile
{
	int x;
	int y;
	int width = 100;
	int height = 100;
};

void Game::InitializeTiles()
{
	if (gameIsRunning == true)
	{
		for (int i = 0; i < gridYScale; ++i)
		{
			for (int j = 0; j < gridXScale; ++j)
			{
				tile = { j, i };
				tiles.insert(tile);
			}
		}
	}
}

void Game::UpdateTiles()
{
	if (gameIsRunning == false) return;

	std::pair<int, int> mousePos = { -1, -1 };

	for (const auto& tile : tiles)
	{
		DrawRectangle(tile.first * gridScale, tile.second * gridScale, gridScale, gridScale, DARKGREEN);
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (!flagMode)
		{
			Vector2 scaledPos = GetScaledMousePosition(GetMouseX(), GetMouseY());
			int x = static_cast<int>(scaledPos.x);
			int y = static_cast<int>(scaledPos.y);
			std::cout << x << " " << y << std::endl;
			mousePos = { x, y };
		}
	}

	if (tiles.find(mousePos) != tiles.end() && !flagMode)
	{
		tiles.erase(mousePos);
	}
	if (flagPositions.find(mousePos) != flagPositions.end() && !flagMode)
	{
		tiles.erase(mousePos);
	}
	if (occupiedPositions.find(mousePos) != occupiedPositions.end())
	{
		gameIsRunning = false;
	}
}

void Game::HandleFlagModeToggle()
{
	if (IsKeyPressed(KEY_F)) {
		flagMode = !flagMode;
	}
}

void Game::PlaceFlags()
{
	if (!gameIsRunning) return;

	std::pair<int, int> mousePos = { -1, -1 };

	if (flagMode && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 scaledPos = GetScaledMousePosition(GetMouseX(), GetMouseY());
		std::pair<int, int> flag = { (int)scaledPos.x, (int)scaledPos.y };
		int x = (int)scaledPos.x;
		int y = (int)scaledPos.y;

		if (tiles.find(flag) != tiles.end() && flags > 0)
		{
			std::cout << "Flag Placed at: " << x << " " << y << std::endl;
			flagPositions.insert(flag);
			tiles.erase(flag);
			flags--;
		}
		else if (tiles.find(flag) == tiles.end())
		{
			flagPositions.erase(flag);
			tiles.insert(flag);
			std::cout << "Tile removed at: " << x << " " << y << std::endl;
			flags++;
		}
	}

	for (const auto& flag : flagPositions)
	{
		DrawRectangle(flag.first * gridScale, flag.second * gridScale, gridScale, gridScale, BLUE);
	}
}

void Game::printFlagCount()
{
	std::string flagText = "Flags: " + std::to_string(flags);
	DrawText(flagText.c_str(), 500, 830, 50, WHITE);
	DrawText("Press P to Reset", 10, 830, 30, WHITE);
	DrawText("Press F to Toggle Flags", 10, 870, 30, WHITE);
}

void Game::EndGame()
{
	if (!gameIsRunning && win == false)
	{
		DrawCenteredText("Game Over!!!", 100);
	}
}

void Game::CheckForWin()
{
	if (flagPositions == occupiedPositions)
	{
		DrawCenteredText("You Win!!!", 100);
		gameIsRunning = false;
		win = true;
	}
}

void Game::SpawnMines(int numMines)
{
	for (int i = 0; i < numMines; ++i)
	{
		Mine mine;
		std::pair<int, int> pos;

		do {
			mine.x = GetRandomValue(0, 7);
			mine.y = GetRandomValue(0, 7);
			pos = { mine.x, mine.y };
		} while (occupiedPositions.find(pos) != occupiedPositions.end());

		mine.color = WHITE;
		mines.push_back(mine);
		occupiedPositions.insert(pos);
	}

	for (const auto& pair : occupiedPositions)
	{
		std::cout << "(" << pair.first << ", " << pair.second << ") ";
		std::cout << std::endl;
	}
}

void Game::PrintBombs()
{
	for (const Mine& mine : mines)
	{
		DrawRectangle(mine.x * gridScale, mine.y * gridScale, gridScale, gridScale, WHITE);
	}
}

void Game::GenerateNumMap() 
{
	int bombCount = 0;

	for (int i = 0; i < gridYScale; ++i)
	{
		for (int j = 0; j < gridXScale; ++j)
		{
			std::pair<int, int> index = { j, i };
			if (occupiedPositions.find(index) != occupiedPositions.end())
			{
				continue;
			}
			else
			{
				if (occupiedPositions.find(std::make_pair(index.first - 1, index.second - 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first, index.second - 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first + 1, index.second - 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first - 1, index.second)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first + 1, index.second)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first - 1, index.second + 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first, index.second + 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				if (occupiedPositions.find(std::make_pair(index.first + 1, index.second + 1)) != occupiedPositions.end())
				{
					++bombCount;
				}
				std::string number = std::to_string(bombCount);
				DrawText(number.c_str(), j * gridScale + 40, i * gridScale + 25, 60, WHITE);
				bombCount = 0;
			}

		}
	}
}



void Game::Initialize()
{
	std::cout << "Initializing" << std::endl;
	flagPositions.clear();
	occupiedPositions.clear();
	tiles.clear();
	mines.clear();
	flags = bombs;
	gameIsRunning = true;
	flagMode = false;
	win = false;
	SpawnMines(10);
	InitializeTiles();
}

void Game::Run()
{
	PrintBombs();
	
	GenerateNumMap();
	UpdateTiles();
	HandleFlagModeToggle();
	PlaceFlags();
	PrintGrid();
	printFlagCount();
	CheckForWin();
	EndGame();
	
}
