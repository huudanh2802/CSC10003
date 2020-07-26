#include "..//Header//seller.h"
#include "..//Header//customer.h"

Seller::Seller():Account()
{
	name = "//";
	title = "//";
	type = 0;
	phone = 0000000000;
	dob.d = 0;
	dob.m = 0;
	dob.y = 0;
}

void Seller::inputData(ifstream& fin) //Get name, dob, phone, title from user.txt
{
	Account::inputData(fin);
	fin >> dob.y;
	fin >> dob.m;
	fin >> dob.d;
	getline(fin, name);
	getline(fin, name);
	fin >> phone;
	getline(fin, title);
	getline(fin, title);
}

void Seller::outputData(ofstream& user_data)
{
	user_data << type << endl;
	Account::outputData(user_data);
	user_data << dob.y << " " << setfill('0') << setw(2) << dob.m << " " << setfill('0') << setw(2) << dob.d << endl;
	user_data << name << endl;
	user_data << setfill('0') << setw(10)<< phone << endl;
	user_data << title << endl;
}

void Seller::viewProfile()
{
	Account::viewProfile();
	cout << "Name :" << name << endl;
	cout << "DOB :" << dob.d << "/" << dob.m << "/" << dob.y << endl;
	cout << "Phone number:" << setfill('0') << setw(10) << phone << endl;
	cout << "Title :" << title << endl;
}

void Seller::viewMenu(Database& list)
{
	int choice;
	do {
		cout << "1.Import list of product from csv file\n2.Create product\n3.Edit information of the product\n4.Search and view information of a product\n5.Create voucher\n6.Remove product\n7.Search and view profile of a customer\n8.Edit customer profile\n9.Export list of customer to a csv file\n10.View list of purchased in a month\n11.Edit order status\n0.Exit\nChoice :";
		cin >> choice;
		switch (choice)
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;
		case 10: break;
		case 11: break;
		case 0: break;
		}
	} while (choice != 0);
}

/*void Seller::serchviewProfilecustomer(Database&list)
{
	string s;
	cout << "Enter name of customer you want to search: ";
	getline(cin, s);
	for (int i = 0; i < list.Number(); i++)
	{
		if(strcmp(s,list.))
	}
}*/

int Seller::checkAccount()
{
	return 0;
}

int Seller::checkName(const string& searchname)
{
	if (name.compare(searchname) == 0)
	{
		return 1;
	}
	return 0;
}