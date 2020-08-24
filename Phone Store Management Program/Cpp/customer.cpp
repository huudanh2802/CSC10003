#include "..//Header//customer.h"
#include "..//Header//password.h"

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

void Customer::viewMenu(Database& account_list)
{
	vector<Order*>order_list;
	Order temp;
	Voucher voucher;
	order_list = temp.loadListOfOrder();
	int choice = -1;

	if (name.compare("//") == 0)
	{
		Order cart;
		Product method;
		Order listProduct;
		int checkOut = -1;
		do {
			system("cls");
			//menu();
			try {
				if (choice == 0) break;
				cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Checkout\n9.Create account\n0.Exit\nChoice :";
				cin >> choice;
				if (choice < 0 || choice>9) throw "Invalid input";
			}
			catch (const char* invalid_argument) {
				cout << invalid_argument << endl;
				system("pause");
				continue;
			}
			switch (choice)
			{
			case 1: {
				system("cls");
				//menu();
				method.viewProduct();
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				//menu();
				cart.addProduct();
				cart.calCart();
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				//menu();
				listProduct.searchProduct();
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				//menu();
				cart.viewCart();
				system("pause");

				break;
			}
			case 5: {
				system("cls");
				//menu();
				cart.removeProduct();
				cart.calCart();
				system("pause");
				break;
			}
			case 6: {
				system("cls");
				//menu();
				method.viewProductBaseOnCategories();
				system("pause");
				break;
			}
			case 7: {
				system("cls");
				//menu();
				break;
			}
			case 8: {
				if (cart.viewCart())
				{
					system("cls");
					//menu();
					cout << "Create an account then log back in" << endl;
					account_list.createAccount(this);
					cart.saveCartTxt(this->getUsername(), name);
					choice = 0;
					system("pause");
				}
				break;
			}
			case 9: {
				system("cls");
				//menu();
				account_list.createAccount(this);
				choice = 0;
				system("pause");
				break;
			}
			case 0: break;
			}
		} while (choice != 0);
	}
	else
	{
		Product method;
		Order listProduct;
		Order cart;
		cart.loadCartTxt(this->getUsername(), name);
		int checkOut = -1;
		do {
			system("cls");
			//menu();
			try {
				cout << "1.View all product\n2.Add product to cart\n3.Search product\n4.View cart\n5.Remove product from cart\n6.View list of products based on categories\n7.Compare 2 products\n8.Uses voucher\n9.Checkout\n10.View order status\n11.Cancel order\n12.Change profile information\n0.Exit\nChoice :";
				cin >> choice;
				if(choice<0||choice>12)throw "Invalid input";
			}
			catch (const char* invalid_argument) {
				cout << invalid_argument << endl;
				system("pause");
				continue;
			}
			switch (choice)
			{
			case 1: {
				system("cls");
				//menu();
				method.viewProduct();
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				//menu();
				cart.addProduct();
				cart.saveCartTxt(this->getUsername(), name);
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				//menu();
				listProduct.searchProduct();
				system("pause");
				break; }
			case 4: {
				system("cls");
				//menu();
				cart.viewCart();
				system("pause");
				break; }
			case 5: {
				system("cls");
				//menu();
				cart.removeProduct();
				cart.saveCartTxt(this->getUsername(), name);
				system("pause");
				break; }
			case 6: {
				system("cls");
				//menu();
				method.viewProductBaseOnCategories();
				system("pause");
				break; }
			case 7: {
				system("cls");
				//menu();
				system("pause");
				break; }
			case 8: {
				system("cls");
				//menu();
				voucher.usesVoucher(order_list, this->getUsername());
				system("pause");
				break; }
			case 9: {
				system("cls");
				//menu();
				if (cart.viewCart())
				{
					cart.checkOut(this->getUsername(), name, order_list, checkOut);
				}
				system("pause");
				break; }
			case 10: {
				system("cls");
				//menu();
				cart.viewOrderStatus(order_list, this->getUsername());
				system("pause");
				break;
			}
			case 11: {
				system("cls");
				//menu();
				cart.cancelOrder(this->getUsername(), order_list);
				system("pause");
				break;
			}
			case 12: {
				system("cls");
				//menu();
				this->changeProfileInformation();
				system("pause");
				break;
			}
			case 0: break;
			}
		} while (choice != 0);
		for (int i = 0; i < order_list.size(); i++)
		{
			if (i == order_list.size() - 1)
			{
				if (checkOut == 1)
				{
					checkOut = -1;
					break;
				}
			}
			order_list[i]->deleteListProduct();
			delete order_list[i];
		}
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

void Order::loadCartTxt(string user, string& name)
{
	char s[60], cart1[60] = "Data/Cart_";
	strcpy_s(s, strlen(name.c_str()) + 1, name.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, "_");
	strcpy_s(s, strlen(user.c_str()) + 1, user.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, ".txt");
	int n;
	Product* pd;
	ifstream fin;
	fin.open(cart1);
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		pd = nullptr;
		pd = new Product;
		int ID, Stock, Price, Ram, Storage;
		string Name, CPU;
		fin >> ID;
		pd->setID(ID);
		getline(fin, Name);
		getline(fin, Name);
		pd->setName(Name);
		fin >> Price;
		pd->setPrice(Price);
		fin >> Stock;
		pd->setStock(Stock);
		getline(fin, CPU);
		getline(fin, CPU);
		pd->setCpu(CPU);
		fin >> Ram;
		pd->setRam(Ram);
		fin >> Storage;
		pd->setStorage(Storage);
		cart.push_back(pd);
	}
	fin.close();
}

void Order::saveCartTxt(string user, string& name)
{
	ofstream fo;
	char s[60], cart1[60] = "Data/Cart_";
	strcpy_s(s, strlen(name.c_str()) + 1, name.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, "_");
	strcpy_s(s, strlen(user.c_str()) + 1, user.c_str());
	strcat_s(cart1, s);
	strcat_s(cart1, ".txt");
	fo.open(cart1);
	fo << cart.size() << endl;
	if (cart.size() != 0)
	{
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

	fo.close(); //add close file
}

void Order::addProduct()
{
	Product* temp = nullptr;
	int flag = 0;
	vector<Product*> list;
	Product* p;
	p = new Product;
	p->loadProduct(list);
	p->listProduct();
	int num;
	cout << "Enter number of product you want to add to cart: ";
	cin >> num;
	for (int i = 0; i < list.size(); i++)
	{
		if (num - 1 == i && list[i]->getStock() > 0)
		{
			flag = 1;
			temp = new Product;
			*temp = *list[i];
			cart.push_back(temp);
			break;
		}
		if (list[i]->getStock() == 0)
		{
			flag = 2;
			break;
		}
	}
	if (flag == 1)
	{
		cout << "Add product to cart successfully" << endl;
	}
	else if (flag == 2)
	{
		cout << "Item out of stock" << endl;
	}
	else
	{
		cout << "Can't find product to add" << endl;
	}

	for (int i = 0; i < list.size(); i++)
	{
			delete list[i];
	}
	list.clear();
	delete p;
}

void Order::removeProduct()
{
	int flag = 0;
	int id, temp;
	if (viewCart() == true)
	{
		cout << "Enter id of product you want to remove from cart: ";
		cin >> id;
		for (int i = 0; i < cart.size(); i++)
		{
			if (cart[i]->getID() == id)
			{
				flag = 1;
				delete cart[i];
				for (int j = i; j < cart.size() - 1; j++)
				{
					cart[j] = cart[j + 1];
				}
				cart.resize(cart.size() - 1);
			}
		}
		if (flag == 1)
		{
			cout << "Remove product from cart successfully" << endl;
		}
		else
		{
			cout << "Can't find product to remove" << endl;
		}
	}
}

bool Order::viewCart()
{
	 if (cart.size() == 0)
	{
		cout << "Cart is empty" << endl;
		return false;
	}
	else
	{
		int S = 0;
		for (int i = 0; i < cart.size(); i++)
		{
			cout << "Product " << i + 1 << " :" << endl;
			cart[i]->outputInfProduct();
			S = S + cart[i]->getPrice();
		}
		cout << "Total :" << S << "$" << endl;
		return true;
	}
}

void Product::outputInfProduct()
{
	cout << "ID: " << ID << endl;
	cout << "Name: " << name << endl;
	cout << "Price: " << price << endl;
	cout << "Stock: " << stock << endl;
	cout << "CPU: " << cpu << endl;
	cout << "Ram: " << ram << endl;
	cout << "Storage: " << storage << endl;
}

void Customer::changeProfileInformation() {
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

void Order::checkOut(string user, string& name, vector<Order*>& list, int& flag)
{
	flag = 1;
	char s[60], remove_file[60] = "Data/Cart_";
	strcpy_s(s, strlen(name.c_str()) + 1, name.c_str());
	strcat_s(remove_file, s);
	strcat_s(remove_file, "_");
	strcpy_s(s, strlen(user.c_str()) + 1, user.c_str());
	strcat_s(remove_file, s);
	strcat_s(remove_file, ".txt");

	try {
		if (remove(remove_file) != 0)
			throw "Cart file invalid! Please check cart data file";
	}
	catch (const char* invalid_argument) {
		cout << invalid_argument << endl;
		exit(0);
	}

	for (int i = 0; i < cart.size(); i++)
		cart[i]->resizeStock();
	this->ID = rand() % 900000 + 100000;
	this->purchaser = user;
	getCurrentDate(this->purchase);
	Order* temp = new Order;
	temp = this;
	list.push_back(temp);
	temp->saveOrder(list);
	cout << "Check out successfully" << endl;
}

void Order::cancelOrder(string user_name, vector<Order*>& list) {
	int flag = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (user_name == list[i]->purchaser && list[i]->status != 2) {
			int total = 0;
			flag = 1;
			cout << "ID of order: " << list[i]->ID << endl;
			for (int i = 0; i < list[i]->cart.size(); i++)
			{
				cout << list[i]->cart[i]->getName() << endl;
				cout << list[i]->cart[i]->getPrice() << endl;
				total += list[i]->cart[i]->getPrice();
			}
			cout << "Total: " << total << endl;
		}
	}
	if (flag == 0) {
		cout << "Your order is empty" << endl;
		return;
	}
	else {
		int id;
		cout << "Enter the order's ID (enter 0 to exit ): ";
		cin >> id;
		if (id == 0) return;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->ID == id) {
				delete list[i];
				list.erase(list.begin() + i);
			}
		}
		cout << "Your order has been cancelled " << endl;
	}

	this->saveOrder(list);
}

void Order::viewOrderStatus(vector<Order*>& list, string name)
{
	int flag = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (strcmp(name.c_str(), list[i]->purchaser.c_str()) == 0)
		{
			flag = 1;
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
		}
	}
	if (flag != 1)
	{
		cout << "Can't view order status" << endl;
	}
}

int Order::getTotal()
{
	return total;
}

void Order::setTotal(int x)
{
	total = x;
}

int Order::getVoucherID()
{
	return voucher_ID;
}

string Order::getPurchaser()
{
	return purchaser;
}


void Product::resizeStock()
{
	vector <Product*> p;
	loadProduct(p);
	for (int i = 0; i < p.size(); i++)
	{
		if (name == p[i]->name)
		{
			p[i]->stock--;
			break;
		}
	}
	saveProduct(p);

	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak

}