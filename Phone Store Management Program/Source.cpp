#include "Header/head.h"
#include "Header/seller.h"
#include "Header/customer.h"

int main()
{
	Database list;
	Account* login;
	ifstream data_file;
	data_file.open("Data/user.txt");
	if (!data_file.is_open())
	{
		throw invalid_argument("Can't open data file (user.txt)");
		exit(0);
	}
	list.loadData(data_file);
	int time = 0,choice;
	int func;
	do {
		int status = 0;
		func = 1;
		if (time != 0) {
			system("cls");
			cout << "1.Login\n0.Exit\nEnter function :";
			cin >> func;
		}
		if (func == 0)
		{
			data_file.close();
			list.deleteData();
			return 0;
		}
		else 
		{
			system("cls");
			++time;
			cout << "1.Login\n2.Login as guest \nChoice :";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1:
			{
				login = list.login();
				do {
					system("cls");
					cout << "1.Show menu\n2.View profile info\n3.Change password\n4.Logout" << endl;
					cout << "Choose function :";
					cin >> func;
					switch (func)
					{
					case 1:
						system("cls");
						login->viewMenu(list);
						break;
					case 2:
					{
						system("cls");
						login->viewProfile();
						system("pause");
						break;
					}
					case 3:
					{
						system("cls");
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
				do {
					system("cls");
					cout << "1.Show menu\n2.Create Account\n3.Logout" << endl;
					cout << "Choose function :";
					cin >> func;
					switch (func)
					{
					case 1:
						login->viewMenu(list);
						break;
					case 2:
					{
						system("pause");
						system("cls");
						break;
					}
					case 3:
					{
						system("cls");
						break;
					}
					}
				} while (func != 3);
				break;
			}
		}
	} while (func != 0);
}
