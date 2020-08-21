#include "../Header/head.h"

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

void menu()
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