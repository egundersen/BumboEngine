/* BUMBO ENGINE vWIP: Credits: Erik, Amber, Jayden
 * MIT License (c) 2018
 *
 * How-To-Use For the most part, stay out of the Image class. You can call the class,
 * Just don't edit it. Everything in the Bumbo Engine is called from the Grid class.
 */

#include "MatrixManager.h"
#include <windows.h>

void setConsoleSize(int width, int height);
char GetKeyPressed(MatrixManager &grid);

int main()
{
	setConsoleSize(600, 600);
	double start_time = GetTickCount();
	char player_input = ' ';
	MatrixManager grid(79, 34, 10); //(37 or 79 , 34)

	// Checks if player presses ESCAPE to quit
	while (player_input != 'x')
	{
		double currentTime = GetTickCount() - start_time;

		if (currentTime >= 50) // 1000 = 1 second
		{
			player_input = GetKeyPressed(grid);
			start_time = GetTickCount(); // reset time
		}
	}

	grid.onShutdown();
	return 0;
}

//sets the console dimensions
void setConsoleSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE); // 800 width, 100 height
}

// Gets all keys currently being pressed
char GetKeyPressed(MatrixManager &grid)
{
	char input = 0;
	grid.evaluatePlayerInput();
	if (GetAsyncKeyState(0x49) & 0x8000)
		if(grid.getCurrentVectorSpace() == "MAP")
			grid.loadVectorSpace("INVENTORY");
	if (GetAsyncKeyState(VK_BACK) & 0x8000)
		if (grid.getCurrentVectorSpace() == "INVENTORY")
			grid.loadVectorSpace("MAP");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		input = 'x';
	return input;
}