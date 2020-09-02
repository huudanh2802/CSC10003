#ifndef _WINDOW_H_
#define _WINDOW_H_
#define WINWIDTH 113
#define WINHEIGHT 1000
#define _WIN32_WINNT 0x0502
#define MAINICON 101   

#include "head.h"

void gotoxy(int x, int y);
void loadingScreen();
void store_management_program();
void menu_main();
int gety();
void turnCursor(bool on);
void gotoXY(int x, int y);
void textColor(int x);
int print(const char* s, int choose);

#endif