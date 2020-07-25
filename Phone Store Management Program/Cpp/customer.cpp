#include "..//Header//customer.h"

Customer::Customer():Account()
{
	name = "//";
	address = "//";
	type = 1;
	phone = 0000000000;
	dob.d = 0;
	dob.m = 0;
	dob.y = 0;
}

void Customer::inputData(ifstream& fin) //Get name, dob, phone, address from user.txt
{
	Account::inputData(fin);
	fin >> dob.y;
	fin >> dob.m;
	fin >> dob.d;
	getline(fin, name);
	getline(fin, name);
	fin >> phone;
	getline(fin, address);
	getline(fin, address);
}

void Customer::outputData(ofstream& user_data)
{
	user_data << type << endl;
	Account::outputData(user_data);
	user_data << dob.y << " " << setfill('0') << setw(2) << dob.m << " " << setfill('0') << setw(2) << dob.d << endl;
	user_data << name << endl;
	user_data << setfill('0') << setw(10) << phone << endl;
	user_data << address << endl;
}

void Customer::viewProfile()
{
	Account::viewProfile();
	cout << "Name :" << name << endl;
	cout << "DOB :" << dob.d << "/" << dob.m << "/" << dob.y << endl;
	cout << "Phone number:" << setfill('0') << setw(10) << phone << endl;
	cout << "Address :" << address << endl;
}

void Customer::viewMenu(Database& list)
{
	int choice;
	if (name.compare("//")==0)
	{
		do {
			cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Checkout\n0.Exit\nChoice :";
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
			case 0: break;
			}
		} while (choice != 0);
	}
	else
	{
		do {
			cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Uses voucher\n9.Checkout\n10.View order status\n11.View order status\n12.Cancel order\n13.Change profile information\n0.Exit\nChoice :";
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
			case 12: break;
			case 13: break;
			case 0: break;
			}
		} while (choice != 0);
	}
}