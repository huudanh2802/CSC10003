#include "../Header/window.h"

 void gotoxy(int x, int y)
{
	COORD d;
	d.X = x;
	d.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
}

void loadingScreen()
{
	char a = 219;
	gotoxy(36, 14);
	cout << "Loading." << endl;
	gotoxy(30, 16);
	for (int r = 1; r <= 20; r++)
	{
		for (int q = 0; q <= 100000; q++);
		cout << a;
	}

}


void store_management_program()
{
	cout << flush;
	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"░█▀▀▀█ ▀▀█▀▀ █▀▀█ █▀▀█ █▀▀ ░█▀▄▀█ █▀▀█ █▀▀▄ █▀▀█ █▀▀▀ █▀▀ █▀▄▀█ █▀▀ █▀▀▄ ▀▀█▀▀ ░█▀▀█ █▀▀█ █▀▀█ █▀▀▀ █▀▀█ █▀▀█ █▀▄▀█\n─▀▀▀▄▄ ──█── █──█ █▄▄▀ █▀▀ ░█░█░█ █▄▄█ █──█ █▄▄█ █─▀█ █▀▀ █─▀─█ █▀▀ █──█ ──█── ░█▄▄█ █▄▄▀ █──█ █─▀█ █▄▄▀ █▄▄█ █─▀─█\n░█▄▄▄█ ──▀── ▀▀▀▀ ▀─▀▀ ▀▀▀ ░█──░█ ▀──▀ ▀──▀ ▀──▀ ▀▀▀▀ ▀▀▀ ▀───▀ ▀▀▀ ▀──▀ ──▀── ░█─── ▀─▀▀ ▀▀▀▀ ▀▀▀▀ ▀─▀▀ ▀──▀ ▀───▀";
	wcout << flush;
	fflush(stdout);
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "\n";
	for (int i = 0; i < 134; i++) cout << "_";
	cout << "\n";

}

void menu_main()
{
	cout << flush;
	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"█▄─▀█▀─▄█▄─▄▄─█▄─▀█▄─▄█▄─██─▄█\n██─█▄█─███─▄█▀██─█▄▀─███─██─██\n▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▄▀▀";
	wcout << flush;
	fflush(stdout);
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "\n";
	cout << "\n";

}

int gety()
{
	HANDLE hConsoleOutput;
	CONSOLE_SCREEN_BUFFER_INFO info;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &info);
	return info.dwCursorPosition.Y;
}

void turnCursor(bool on)
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = on;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor);
}

void textColor(int x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}

int print(const char* s, int choose)
{
	char* yourChoose, * ntok = 0, * str = new char[strlen(s) + 1];
	strcpy_s(str, strlen(s) + 1, s);
	yourChoose = strtok_s(str, "\n", &ntok);
	int i = 1;
	while (yourChoose)
	{
		if (i == choose)
		{
			textColor(12);
			cout << yourChoose << endl;
		}
		else
		{
			textColor(15);
			cout << yourChoose << "   " << endl;
		}
		yourChoose = strtok_s(0, "\n", &ntok);
		i++;
	}
	delete[] str;
	return i - 1;
}

