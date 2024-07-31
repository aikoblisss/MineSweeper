#include "Game.h"
#include "HomeScreen.h"
#include <raylib.h>

bool isGameStarted = false;

Game game;
HomeScreen homescreen(game);


int main()
{

	InitWindow(game.gridWidth, game.gridHeight + 100, "MineSweeper");

	game.Initialize();

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		

		if (homescreen.ProcessInput())
		{
			game.Run();
		}
		else
		{
			homescreen.Draw();
		}

		EndDrawing();
	}
	CloseWindow();
}