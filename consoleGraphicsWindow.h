#pragma once

#include<Windows.h>

class consoleGraphicsWindow
{
private:
	int screenWidth = 160;
	int screenHeight = 50;

	wchar_t* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten = 0;

public:
	consoleGraphicsWindow(int wid, int height) : screenWidth(wid), screenHeight(height)
	{
		// Initializes screen with blank characters
		screen = new wchar_t[screenWidth * screenHeight];
		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				set_char(x, y, ' ');
			}
		}

		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
	}

	consoleGraphicsWindow()
	{
		// Initializes screen with blank characters
		screen = new wchar_t[screenWidth * screenHeight];
		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				set_char(x, y, ' ');
			}
		}

		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
	}

	~consoleGraphicsWindow()
	{
		delete[] screen;
	}

	bool set_char(int x, int y, wchar_t symbol)
	{
		// Returns true if the operation was sucessful.
		if (0 <= x < screenWidth && 0 <= y < screenHeight)
		{
			screen[x + screenWidth * y] = symbol;
			return true;
		}
		return false;
	}

	void clear_frame()
	{
		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				set_char(x, y, ' ');
			}
		}
	}

	void draw_frame()
	{
		screen[screenWidth * screenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}
};
