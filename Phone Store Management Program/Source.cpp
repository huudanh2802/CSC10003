#include "Header/head.h"
#include "Header/seller.h"
#include "Header/customer.h"

int main()

{
	//SetConsoleTitle(TEXT("Store Management Program"));
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD sizeOfBuff;
	//sizeOfBuff.X = 120;
	//sizeOfBuff.Y = 40;
	//SetConsoleScreenBufferSize(buff, sizeOfBuff);
	//HWND hwnd = GetConsoleWindow();
	//if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 900, 700, SWP_SHOWWINDOW | SWP_NOMOVE); }
	//loadingScreen();
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
			//store_management_program();
			try {
				cout << "1.Login\n0.Exit\nEnter function :";
				cin >> func;
				if (func < 0 || func>1) throw "Invalid input";
			}
			catch (const char* invalid_argument) {
				cout << invalid_argument << endl;
				system("pause");
				continue;
			}
		}
		if (func == 0)
		{
			break;
		}
		else
		{
			system("cls");
			++time;
			cout << "1.Login\n2.Login as guest \nChoice :";
			cin >> choice;
			try {
				//store_management_program();
	
				if (choice < 1 || choice>2)throw "Invalid input";
			}
			catch (const char* invalid_argument) {
				cout << invalid_argument << endl;
				system("pause");
				continue;
			}
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
						//menu();
						try {
							cout << "1.Show menu\n2.View profile info\n3.Change password\n4.Logout" << endl;
							cout << "Choose function :";
							cin >> func;
							if (choice < 1 || choice>4)throw "Invalid input";
						}
						catch (const char* invalid_argument) {
							cout << invalid_argument << endl;
							system("pause");
							continue;
						}
						}
						switch (func)
						{
						case 1:
							system("cls");
							//menu();
							login->viewMenu(account_list,switchS);
							break;
						case 2:
						{
							system("cls");
							//menu();
							login->viewProfile();
							system("pause");
							break;
						}
						case 3:
						{
							system("cls");
							//menu();
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

