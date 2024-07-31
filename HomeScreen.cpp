#include "HomeScreen.h"

HomeScreen::HomeScreen(Game& game) 
	: game(game), isGameStarted(false)
{
}

void HomeScreen::Draw()
{
	DrawText("MINESWEEPER", 20, 300, 100, GREEN);
	DrawText("Press G to Play", 200, 600, 50, RED);
}

bool HomeScreen::ProcessInput()
{
	if (!isGameStarted)
	{
		if (IsKeyPressed(KEY_G))
		{
				std::cout << "G is pressed" << std::endl;
				game.Initialize();
				isGameStarted = true;
				ClearBackground(BLACK);
		}
	}
	if (IsKeyPressed(KEY_P))
	{
		Reset();
	}
	return isGameStarted;
}

void HomeScreen::Reset()
{
	isGameStarted = false;
	game.Initialize();
}
