#include "..//Header//customer.h"
#include "..//Header//password.h"
#include <string>

Customer::Customer() :Account()
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

int Customer::Type()
{
	return 1;
}

string Customer::Name()
{
	return name;
}

string Customer::getAddress()
{
	return address;
}

Date Customer::Dob()
{
	return dob;
}

int Customer::Phone()
{
	return phone;
}

void Customer::viewMenu(Database& list)
{
	int choice;
	Account* p;
	p = new Customer;
	p = this;
	string username;
	username = p->getUsername();
	if (name.compare("//") == 0)
	{
		Order cart;
		do {
			cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Checkout\n9.Create account\n0.Exit\nChoice :";
			cin >> choice;
			Product method;
			switch (choice)
			{
			case 1: method.viewProduct(); break;
			case 2: cart.addProduct(); break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			case 8: break;
			case 9: list.createAccount(); break;
			case 0: break;
			}
		} while (choice != 0);
	}
	else
	{
		do {
			cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Uses voucher\n9.Checkout\n10.View order status\n11.View order status\n12.Cancel order\n13.Change profile information\n0.Exit\nChoice :";
			cin >> choice;
			Order cart;
			switch (choice)
			{
			case 1: break;
			case 2: cart.addProduct(); cart.saveCartTxt(username,name); break;
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

int Customer::checkName(const string& searchname)
{
	if (name.compare(searchname) == 0)
	{
		return 1;
	}
	return 0;
}

int Customer::checkAccount()
{
	return 1;
}

void Customer::editProfile()
{
	cout << "Enter date of birth: ";
	cin >> dob.d >> dob.m >> dob.y;
	cout << "Enter phone: ";
	cin >> phone;
	cout << "Enter name: ";
	getline(cin, name);
	getline(cin, name);
	cout << "Enter address: ";
	getline(cin, address);
}

void Customer::createAccount() {

	Account::createAccount();
	cout << endl;
	cout << "Enter date of birth: ";
	cin >> dob.d >> dob.m >> dob.y;
	cout << "Enter phone: ";
	cin >> phone;
	cout << "Enter name: ";
	getline(cin, name);
	getline(cin, name);
	cout << "Enter address: ";
	getline(cin, address);
	
}

void Product::loadCartTxt(vector <Product*>& p,char* data)
{
	int n;
	Product* pd;
	ifstream fin;
	fin.open(data);
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		pd = nullptr;
		pd = new Product;
		fin >> pd->ID;
		getline(fin, pd->name);
		getline(fin, pd->name);
		fin >> pd->price;
		fin >> pd->stock;
		getline(fin, pd->cpu);
		getline(fin, pd->cpu);
		fin >> pd->ram;
		fin >> pd->storage;
		p.push_back(pd);
	}
	fin.close();
}

void Order::saveCartTxt(string &user,string &name)
{
	Product *p;
	p = new Product;
	ofstream fo;
	char s[60], cart1[60] = "Data/Cart_";
	strcpy_s(s, strlen(name.c_str()) + 1, name.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, "_");
	strcpy_s(s, strlen(user.c_str()) + 1, user.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, ".txt");
	ifstream fi;
	int n;
	fi.open(cart1);
	if (fi.is_open())
	{
		fi >> n;
		p->loadCartTxt(cart,cart1);
	}
	fo.open(cart1);
	fo << cart.size()<<endl;
	for (int i = 0; i < cart.size(); i++)
	{
		fo << cart[i]->getID() << endl;
		fo << cart[i]->getName() << endl;
		fo << cart[i]->getPrice() << endl;
		fo << cart[i]->getStock() << endl;
		fo << cart[i]->getCpu() << endl;
		fo << cart[i]->getRam() << endl;
		fo << cart[i]->getStorage() << endl;
	}
}

void Order::addProduct()
{
	vector<Product*> list;
	Product *p;
	p = new Product;
	p->loadProduct(list);
	p->listProduct();
	int num;
	cout << "Enter number of product you want to add to cart: ";
	cin >> num;
	for (int i = 0; i < list.size(); i++)
	{
		if (num-1 == i)
		{
			cart.push_back(list[i]);
		}
	}
}
	
