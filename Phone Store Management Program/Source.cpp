#include "Header/head.h"
#include "Header/seller.h"
#include "Header/customer.h"
#include "Header/window.h"

int main()

{
	SetConsoleTitle(TEXT("Store Management Program"));
	textColor(15);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 120;
	sizeOfBuff.Y = 40;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 900, 700, SWP_SHOWWINDOW | SWP_NOMOVE); }
	loadingScreen();
	Database account_list;
	Account* login=nullptr;
	int switchS = 0;
	int time = 0, choice;
	int func;
	do {
		system("cls");
		int status = 0;
		func = 1;
		if (time != 0) {
			system("cls");
			store_management_program();
			do {
				try {
					func = menu("1.Login\n2.Exit");
					if (func < 0 || func>2) throw "Invalid input";
				}
				catch (const char* invalid_argument) {
					cout << invalid_argument << endl;
					system("pause");
					continue;
				}
				break;
			} while (true);
		}
		if (func == 2)
		{
			break;
		}
		else
		{
			++time;
			do {
				system("cls");
				try {

					store_management_program();
					choice = menu("1.Login\n2.Login as guest ");
					if (choice < 1 || choice>2)throw "Invalid input";
				}
				catch (const char* invalid_argument) {
					cout << invalid_argument << endl;
					system("pause");
					continue;
				}
				break;
			} while (true);
			system("cls");
			do {
				if (switchS !=0) choice = 1;
				switch (choice)
				{
				case 1:
				{
					if (switchS == 0) {
						login = account_list.login();
					}
					do {
						if (switchS == 2) choice = 1;
						else {
						switchS = 0;
						system("cls");
						menu_main();
						do {
							try {
								func = menu("1.Show menu\n2.View profile info\n3.Change password\n4.Logout");
								if (choice < 1 || choice>4)throw "Invalid input";
							}
							catch (const char* invalid_argument) {
								cout << invalid_argument << endl;
								system("pause");
								continue;
							}
							break;
						} while (true);
						}
						switch (func)
						{
						case 1:
							system("cls");
							menu_main();
							login->viewMenu(account_list,switchS);
							break;
						case 2:
						{
							system("cls");
							menu_main();
							login->viewProfile();
							system("pause");
							break;
						}
						case 3:
						{
							system("cls");
							menu_main();
							login->changePassword();
							system("pause");
							break;
						}
						case 4:
						{
							system("cls");
							break;
						}
						}
					} while (func != 4);
					break;
				}
				case 2:
					login = new Customer;
					login->viewMenu(account_list,switchS);
					if (switchS == 0) delete login;
					if (switchS !=0) continue;
					break;
				}
			} while (switchS!=0);
		}
	} while (func != 0);
	return 0;
}

