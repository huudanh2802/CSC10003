#include "..//Header//seller.h"
#include "..//Header//customer.h"
#include "..//Header//window.h"

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

void Seller::inputData(fstream& fin) //Get name, dob, phone, title from user.txt
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

void Seller::outputData(fstream& user_data)
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

void Seller::export_file(ofstream& fout)
{
	return;
}

void Seller::viewMenu(Database& account_list, int& switchS)
{
	vector<Order*>order_list;
	Order temp;
	order_list = temp.loadListOfOrder();
	int choice;
	do {
		system("cls");
		menu_main();
		try {
			choice = menu("1.Import list of product from csv file\n2.Create product\n3.Edit information of the product\n4.Search and view information of a product\n5.Create voucher\n6.Remove product\n7.Search and view profile of a customer\n8.Edit customer profile\n9.Export list of customer to a csv file\n10.View list of purchased in a month\n11.Edit order status\n12.Exit");
			if (choice < 0 || choice>12)throw "Invalid input";
		}
		catch (const char* invalid_argument) {
			cout << invalid_argument << endl;
			system("pause");
			continue;
		}
		Order listProduct;
		Voucher voucher;
		Product method;
		switch (choice)
		{
		case 1: {
			system("cls"); 
			menu_main();
			listProduct.importProductFromCSV(); 
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			menu_main();
			method.createProduct(); 
			system("pause"); 
			break; 
		}
		case 3: {
			system("cls");
			menu_main();
			method.editProduct();
			system("pause");
			break; 
		}
		case 4: {
			system("cls"); 
			menu_main();
			listProduct.searchProduct(); 
			system("pause");
			break; 
		}
		case 5: {
			system("cls");
			menu_main();
			voucher.createVoucher();
			system("pause");
			break;
		}
		case 6: {
			system("cls"); 
			menu_main();
			method.removeProduct(); 
			system("pause");
			break; 
		}
		case 7: {
			system("cls");	
			menu_main();
			account_list.searchviewProfilecustomer();
			system("pause");
			break; 
		}
		case 8: {
			system("cls"); 
			menu_main();
			account_list.editProfilecustomer(); 
			system("pause");
			break; 
		}
		case 9: {
			system("cls"); 
			menu_main();
			account_list.exportCustomerlist(); 
			system("pause");
			break; 
		}
		case 10: {
			system("cls"); 
			menu_main();
			listProduct.purchasedProductInAMonth(order_list);
			system("pause"); 
			break;
		}
		case 11: {
			system("cls"); 
			menu_main();
			listProduct.editOrderStatus();
			system("pause"); 
			break; 
		}
		case 12: break;
		}
	} while (choice != 12);
	temp.saveOrder(order_list);
	for (int i = 0; i < order_list.size(); i++)
	{
		order_list[i]->deleteListProduct();
		delete order_list[i];
	}
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

void Seller::editProfile()
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

void Customer::export_file(ofstream& fout)
{
	fout << name << "," << dob.y << "/" << dob.m << "/" <<dob.d << "," << phone << "," << address << endl;

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
			data[i]->export_file(fo);
			flag = 1;
		}
	}
	fo.close();
	if (flag == 1)
	{
		cout << "Export successfully" << endl;
	}
}

void Order::editOrderStatus()
{
	system("cls");
	menu_main();
	vector <Order*> order_list;
	Order tmp;
	order_list = tmp.loadListOfOrder();
	string name;
	cout << "Input name of customer you want to edit order status: ";
	getline(cin, name);
	getline(cin, name);
	viewOrderStatus(order_list, name);
	for (int i = 0; i < order_list.size(); i++)
	{
		int tmp, retry = 1;
		while (retry == 1)
		{
			if (strcmp(name.c_str(), order_list[i]->purchaser.c_str()) == 0)
			{
				retry = 2;
				cout << "Choose a transition status:\n";
				tmp = menu("1.Confirmed\n2.Pending\n3.Finished");
				if (tmp < 1 || tmp > 3)
				{
					cout << "You entered incorrectly. Try again?\n";
					retry = menu("1.Yes\n2.No");
				}
				else
				{
					order_list[i]->status = tmp - 1;
					cout << "Edit successfully!\n";
				}
			}
		}
		if (retry == 2) break;
	}
	saveOrder(order_list);
	for (int i = 0; i < order_list.size(); i++) delete order_list[i];
}

void Order::purchasedProductInAMonth( vector<Order*>& list) {
	int month;
	int flag = 0;
	cout << "Enter the month you want to see: ";
	cin >> month;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->purchase.m == month && list[i]->status == 2) {
			cout << "Purchaser: " << list[i]->purchaser << endl;
			cout << "ID: " << list[i]->ID << endl;
			cout << "Purchase: " << list[i]->purchase.d << "/" << list[i]->purchase.m << "/" << list[i]->purchase.y << endl;
			switch (list[i]->status)
			{
			case 0: cout << "Status: Confirmed" << endl; break;
			case 1: cout << "Status: Pending" << endl; break;
			case 2: cout << "Status: Finished" << endl; break;
			}
			cout << "Voucher ID: " << list[i]->voucher_ID << endl;
			list[i]->viewCart();
			flag = 1;
		}
	}
	if (flag == 0) {
		cout << "No order in this month" << endl;
	}
}