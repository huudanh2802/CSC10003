#include "Header/head.h"
#include "Header/seller.h"
#include "Header/customer.h"

int main()

{
	SetConsoleTitle(TEXT("Store Management Program"));
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
	Account* login;

	ifstream data_file;
	data_file.open("Data/user.txt");
	try {
		if (!data_file.is_open())
		{
			throw "Can't open data file (user.txt)!";
		}
	}
	catch (const char* invalid_argument) {
		cout << invalid_argument << endl;
		exit(0);
	}
	account_list.loadData(data_file);
	int time = 0, choice;
	int func;
	do {
		system("cls");
		int status = 0;
		func = 1;
		if (time != 0) {
			system("cls");
			////store_management_program();
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
			account_list.deleteData();
			data_file.close();
			return 0;
		}
		else
		{
			system("cls");
			++time;
			try {
				////store_management_program();
				cout << "1.Login\n2.Login as guest \nChoice :";
				cin >> choice;
				if (choice < 1 || choice>2)throw "Invalid input";
			}
			catch (const char* invalid_argument) {
				cout << invalid_argument << endl;
				system("pause");
				continue;
			}
			system("cls");
			switch (choice)
			{
			case 1:
			{
				login = account_list.login();
				do {
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
					switch (func)
					{
					case 1:
						system("cls");
						//menu();
						login->viewMenu(account_list);
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
				login->viewMenu(account_list);
				break;
			}
		}
	} while (func != 0);
}