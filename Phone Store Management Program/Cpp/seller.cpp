#include "..//Header//seller.h"
#include "..//Header//customer.h"

Seller::Seller() :Account()
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
	user_data << setfill('0') << setw(10) << phone << endl;
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

int Seller::Type()
{
	return 0;
}

string Seller::Name()
{
	return name;
}

string Seller::getAddress()
{
	return 0;
}

Date Seller::Dob()
{
	return dob;
}

int Seller::Phone()
{
	return phone;
}

void Seller::viewMenu(Database& list)
{
	int choice;
	do {
		cout << "1.Import list of product from csv file\n2.Create product\n3.Edit information of the product\n4.Search and view information of a product\n5.Create voucher\n6.Remove product\n7.Search and view profile of a customer\n8.Edit customer profile\n9.Export list of customer to a csv file\n10.View list of purchased in a month\n11.Edit order status\n0.Exit\nChoice :";
		cin >> choice;
		Store listProduct;
		Voucher voucher;
		Product method;
		switch (choice)
		{
		case 1: listProduct.importProductFromCSV(); break;
		case 2: method.createProduct(); break;
		case 3: method.editProduct();  break;
		case 4: break;
		case 5: voucher.createVoucher();   break;
		case 6: method.removeProduct(); break;
		case 7: list.searchviewProfilecustomer(); break;
		case 8: list.editProfilecustomer(); break;
		case 9: list.exportCustomerlist(); break;
		case 10: break;
		case 11: break;
		case 0: break;
		}
	} while (choice != 0);
}

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

void Database::searchviewProfilecustomer()
{
	int flag = 0;
	string searchname;
	cout << "Enter name of customer you want to search and view: ";
	getline(cin, searchname);
	getline(cin, searchname);
	for (int i = 0; i < num; i++)
	{
		if (data[i]->checkAccount() == 1)
		{
			if (data[i]->checkName(searchname))
			{
				data[i]->viewProfile();
				flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		cout << "Can't find customer" << endl;
	}
}

void Seller:: editProfile()
{
	cout << "Enter date of birth: ";
	cin >> dob.d >> dob.m >> dob.y;
	cout << "Enter phone: ";
	cin >> phone;
	cout << "Enter name: ";
	getline(cin, name);
	getline(cin, name);
	cout << "Enter title: ";
	getline(cin, title);
}

void Database::editProfilecustomer()
{
	int flag = 0;
	string searchname;
	cout << "Enter name of customer you want to edit: ";
	getline(cin, searchname);
	getline(cin, searchname);
	for (int i = 0; i < num; i++)
	{
		if (data[i]->checkAccount() == 1)
		{
			if (data[i]->checkName(searchname))
			{
				data[i]->editProfile();
				flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		cout << "Can't find customer" << endl;
	}
	else
	{
		cout << "Edit successfully" << endl;
	}
}

void Database::exportCustomerlist()
{
	int flag = 0;
	ofstream fo;
	fo.open("Data/Customerlist.csv");
	char s[] = "Name,Date of birth,Phone,Address\n";
	fo << s;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i]->Type() == 1)
		{
			flag = 1;
			fo << data[i]->Name() << ","<< data[i]->Dob().y << "/" << data[i]->Dob().m << "/" << data[i]->Dob().d << "," << data[i]->Phone() << "," << data[i]->getAddress() << endl;
		}
	}
	fo.close();
	if (flag == 1)
	{
		cout << "Export successfully" << endl;
	}
}


