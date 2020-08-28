#include "..//Header//head.h"
#include "..//Header//customer.h"
#include "..//Header//seller.h"
#include "..//Header//password.h"
Account::Account()
{
	user = "//";
	pass = "//";
}

Database::Database()
{
	num = 0;
}

void Date::input() {
	cout << "Day: ";
	cin >> d;
	cout << "Month: ";
	cin >> m;
	cout << "Year: ";
	cin >> y;
}

// PRODUCT
Product::Product() {
	ID = 0;
	price = 0;
	stock = 0;
	name = "";
	cpu = "";
	ram = 0;
	storage = 0;
}

bool Product::comparingID(const Product& a) {
	if (a.ID == this->ID) return true;
	return false;
}

void Product::loadFromCSV(ifstream& fin, string data) {
	stringstream ss(data);
	string tmp = "";

	getline(ss, tmp, ',');
	ID = stoi(tmp);

	getline(ss, tmp, ',');
	name = tmp;

	getline(ss, tmp, ',');
	price = stoi(tmp);

	getline(ss, tmp, ',');
	stock = stoi(tmp);

	getline(ss, tmp, ',');
	cpu = tmp;

	getline(ss, tmp, ',');
	ram = stoi(tmp);

	getline(ss, tmp, '\n');
	storage = stoi(tmp);
}

void Product::saveToTxt(ofstream& fout)
{
	fout << ID << endl;
	fout << name << endl;
	fout << price << endl;
	fout << stock << endl;
	fout << cpu << endl;
	fout << ram << endl;
	fout << storage << endl;
}

void Product::loadFromTxt(ifstream& fin) {
	fin >> ID;

	fin.ignore(1);
	getline(fin, name, '\n');

	fin >> price;
	fin >> stock;

	fin.ignore(1);
	getline(fin, cpu, '\n');

	fin >> ram;
	fin >> storage;
}

void Product::updateStock(const Product& temp) {
	this->stock += temp.stock;
}

void Order::loadFromCSV(ifstream& fin) {
	string s;
	fin.ignore(1);
	getline(fin, s);

	Product* p;

	while (getline(fin, s)) {
		p = NULL;
		p = new Product;
		p->loadFromCSV(fin, s);
		cart.push_back(p);
	}

	fin.close();
}

void Order::loadFromTxt() {
	ifstream fin;
	int n;
	fin.open(".//Data//product.txt");
	Product* p;

	fin >> n;
	for (int i = 0; i < n; i++)
	{
		p = NULL;
		p = new Product;
		p->loadFromTxt(fin);
		cart.push_back(p);
	}

	fin.close();
}

void Order::saveToTxt() {
	ofstream fout;
	fout.open(".//Data//product.txt");

	fout << cart.size() << endl;
	for (int i = 0; i < cart.size(); i++)
	{
		cart[i]->saveToTxt(fout);
	}
}

void Order::deleteListProduct() {
	for (int i = 0; i < cart.size(); i++)
	{
		delete cart[i];
	}
	cart.clear();
}

void Order::importProductFromCSV() {
	Date tempDate;

	cout << "Import date: " << endl;
	tempDate.input();

	string tempStr;
	tempStr = to_string(tempDate.y) + to_string(tempDate.m) + to_string(tempDate.d);
	tempStr = "product_" + tempStr + ".csv";
	ifstream fin;
	fin.open(tempStr);
	Order fromCsv;
	if (fin.is_open())
		fromCsv.loadFromCSV(fin);
	else {
		cout << "Can't open " << tempStr << " file" << endl;
		return;
	}
	loadFromTxt();

	Product* temp = NULL;
	for (int i = 0; i < fromCsv.cart.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < cart.size(); j++)
		{
			if (cart[j]->comparingID(*fromCsv.cart[i])) {
				cart[j]->updateStock(*fromCsv.cart[i]);
				flag = 1;
			}
		}
		if (flag == 0) {
			temp = fromCsv.cart[i];
			cart.push_back(temp);
		}
	}
	cout << "Import successfully" << endl;

	saveToTxt();
	deleteListProduct();
}

// <\PRODUCT>

void Account::inputData(ifstream& user_data) //Get username and password
{
	getline(user_data, user);
	getline(user_data, user);
	getline(user_data, pass);
}

void Database::loadData(ifstream& user_data) //Load user from user.txt
{
	Account* account;
	int tType;
	user_data >> num;
	for (int i = 0; i < num; i++)
	{
		user_data >> tType;
		if (tType == 0)
			account = new Seller;
		else
			account = new Customer;
		account->inputData(user_data);
		user_data.ignore(1, '\n');
		data.push_back(account);
	}
}

void Database::deleteData() //Deallocate vector data
{
	ofstream user_data;
	user_data.open(((string)".//Data//user.txt").c_str(), ios::trunc);
	if (!user_data.is_open()) {
		cout << "user.txt can't be opened" << endl;
		exit(0);
	}
	user_data << num << endl;
	for (int i = 0; i < num; i++)
	{
		data[i]->outputData(user_data);
		user_data << '\n';
	}
	for (int i = 0; i < data.size(); i++)
		delete data[i];
	data.clear();
	user_data.close();
}

int Account::checkLogin(const string& input_username, const string& input_password)
{
	if (user.compare(input_username) == 0 && pass.compare(input_password) == 0) return 1;
	else return 0;
}

Account* Database::login()
{
	Account* account = nullptr;
	string input_username, input_password;
	int i = 0;
	while (true)
	{
		system("cls");
		//store_management_program();
		cout << "Username :";
		if(i==0) getline(cin, input_username);
		getline(cin, input_username);
		cout << "Password :";
		enterPass(input_password);
		for (int i = 0; i < num; i++)
		{
			if (data[i]->checkLogin(input_username, input_password) == 1)
			{
				account = data[i];
				break;
			}
		}
		if (account != nullptr) break;
		else {
			i++;
			cout << "Invalid username/password" << endl;
		}
	}
	return account;
}

void Database::createAccount(Account* acc) {
	acc->createAccount();
	data.push_back(acc);
	num++;
}

void Database::changeProfileInformation(string user_name) {
	for (int i = 0; i < num; i++)
	{
		if (user_name == data[i]->getUsername()) {
			data[i]->changeProfileInformation();
		}
	}
}

int Database::Number()
{
	return num;
}

void Account::outputData(ofstream& user_data)
{
	user_data << user << endl;
	user_data << pass << endl;
}

void Account::viewProfile()
{
	cout << "Username :" << user << endl;
}

void Account::changePassword()
{
	string tempPass1, tempPass2;
	while (true)
	{
		cout << "Enter old password :";
		getline(cin, tempPass1);
		enterPass(tempPass1);
		if (tempPass1.compare(pass) != 0) cout << "\nOld password entered incorrectly" << endl;
		else break;
	};
	while (true) {
		cout << "\nEnter new password :";
		enterPass(tempPass1);
		cout << "\nConfirm new password:";
		enterPass(tempPass2);
		if (tempPass1.compare(tempPass2) != 0) cout << "\nNew Password and confirmed new password is different" << endl;
		else if (pass.compare(tempPass1) == 0) cout << "\nNew Password must different from old password" << endl;
		else break;
	};
	pass = tempPass1;
}

void Account::createAccount() {
	cout << "Enter user name: ";
	getline(cin, user);
	getline(cin, user);
	cout << "Enter password: ";
	enterPass(pass);
}

void Product::createProduct()
{
	vector <Product*> p;
	loadProduct(p);
	Product* tmp = nullptr;
	tmp = new Product;
	int check = 1;
	while (check == 1)
	{
		check = 2;
		cout << "Enter product information:\n";
		cout << "ID: ";
		cin >> tmp->ID;
		for (int i = 0; i < p.size(); i++)
		{
			if (tmp->ID == p[i]->ID)
			{
				cout << "ID existed! Try again? (1.Yes/ 2.No)\n";
				cin >> check;
				if (check == 2) return;
			}
			if (check == 1) break;
		}
	}
	cout << "Name: ";
	getline(cin, tmp->name);
	getline(cin, tmp->name);
	cout << "Price: ";
	cin >> tmp->price;
	cout << "Stock: ";
	cin >> tmp->stock;
	cout << "CPU: ";
	getline(cin, tmp->cpu);
	getline(cin, tmp->cpu);
	cout << "Ram (GB): ";
	cin >> tmp->ram;
	cout << "Storage (GB): ";
	cin >> tmp->storage;
	p.push_back(tmp);
	cout << "Create successfully!" << endl;
	saveProduct(p);

	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::viewProduct()
{
	system("cls");
	//menu();
	int choose = 0;
	vector <Product*> p;
	loadProduct(p);
	listProduct();
	if (p.size() == 0) return;
	cout << "Would you like to see product information? (1: Yes/ 2. No)" << endl;
	cin >> choose;
	if (choose == 1)
	{
		int no;
		cout << "Enter numerical order to view product information: ";
		cin >> no;
		viewProductInf(p, no);
	}
	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::viewProductBaseOnCategories()
{
	vector <Product*> p;
	loadProduct(p);
	int retry = 0, flag = 0, no = 1, choose, sprice = 0, bprice = 100000000, sram = 0, bram = 16, sstorage = 0, bstorage = 1028;
	string cpu;
	while (retry != 1)
	{
		cout << "Filter:\n1.Price\n2.CPU\n3.Storage\n4.Ram\n5.View list product base on categories\n";
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << "Enter price range (Smaller price < Your phone price < Bigger price)\n";
			cout << "Smaller price: ";
			cin >> sprice;
			cout << "Bigger price: ";
			cin >> bprice;
			break;
		case 2:
			cout << "Enter memory range (Smaller memory < Your phone memory < Bigger memory)\n";
			cout << "Smaller memory: ";
			cin >> sram;
			cout << "Bigger memory: ";
			cin >> bram;
			break;
		case 3:
			cout << "Enter storage range (Smaller storage < Your phone storage < Bigger storage)\n";
			cout << "Smaller storage: ";
			cin >> sstorage;
			cout << "Bigger storage: ";
			cin >> bstorage;
			break;
		case 4:
			cout << "Enter name of cpu: ";
			getline(cin, cpu);
			getline(cin, cpu);
			flag = 1;
			break;
		case 5:
			retry = 1;
			break;
		}
	}
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i]->price > sprice && p[i]->price < bprice
			&& p[i]->ram > sram && p[i]->ram < bram
			&& p[i]->storage > sstorage && p[i]->storage < bstorage)
		{
			if (flag == 0)
			{
				cout << no << "." << p[i]->name << endl;
				no++;
			}
			if (flag == 1 && p[i]->cpu == cpu)
			{
				cout << no << "." << p[i]->name << endl;
				no++;
			}
		}
	}

	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::editProduct()
{
	system("cls");
	//menu();
	int no, choose;
	vector <Product*> p;
	loadProduct(p);
	listProduct();
	if (p.size() == 0) return;
	cout << "Enter numerical order to edit product information:  ";
	cin >> no;
	viewProductInf(p, no);
	int retry = 1, check = 1, flag = 0;
	while (retry == 1) {
		flag = 1;
		cout << "Select the information to edit\n1. ID\n2. Name\n3. Price\n4. Stock\n5. CPU\n6. Ram\n7. Storage\n0. Exit\n";
		cin >> choose;
		switch (choose)
		{
		case 0:
			flag = 0;
			retry = 2;
			break;
		case 1:
			while (check == 1) {
				flag = 1;
				check = 2;
				cout << "Enter new ID: ";
				cin >> p[no - 1]->ID;
				for (int i = 0; i < p.size(); i++)
				{
					if ((p[no - 1]->ID == p[i]->ID) && (i != no - 1))
					{
						flag = 0;
						cout << "ID existed! Try again? (1.Yes/ 2.No)\n";
						cin >> check;
					}
					if (check == 1) break;
				}
			}
			break;
		case 2:
			cout << "Enter new name: ";
			getline(cin, p[no - 1]->name);
			getline(cin, p[no - 1]->name);
			break;
		case 3:
			cout << "Enter new price: ";
			cin >> p[no - 1]->price;
			break;
		case 4:
			cout << "Enter new stock: ";
			cin >> p[no - 1]->stock;
			break;
		case 5:
			cout << "Enter new cpu: ";
			getline(cin, p[no - 1]->cpu);
			getline(cin, p[no - 1]->cpu);
			break;
		case 6:
			cout << "Enter new ram: ";
			cin >> p[no - 1]->ram;
			break;
		case 7:
			cout << "Enter new storage: ";
			cin >> p[no - 1]->storage;
			break;
		default:
			cout << "There is no option for this. Try again? (1. Yes/ 2.No)\n";
			cin >> retry;
			if (retry == 2) flag = 2;
			break;
		}
		if (choose <= 7 && choose > 0)
		{
			cout << "Edit more information? (1. Yes/ 2.No)\n";
			cin >> retry;
		}
	}
	if (flag == 1)
	{
		cout << "Edit successfully!\n";
		saveProduct(p);
	}
	else
	{
		cout << "Edit failed!\n";
	}

	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::removeProduct()
{
	vector <Product*> p;
	loadProduct(p);
	listProduct();
	int retry = 1, no;
	while (retry == 1) {
		retry = 2;
		cout << "Enter numerical order to remove product: ";
		cin >> no;
		if (no >= p.size())
		{
			cout << "This product is unavailable! Retry? (1.Yes/ 2.No)\n";
			cin >> retry;
			if (retry == 0) return;
		}
	}
	for (int i = no - 1; i < p.size() - 1; i++)
	{
		p[i] = p[i + 1];
	}
	p.resize(p.size() - 1);
	saveProduct(p);
	cout << "Remove successfully!" << endl;
	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::listProduct()
{
	system("cls");
	//menu();
	vector <Product*> p;
	loadProduct(p);
	cout << "List of product:\n";
	if (p.size() == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}
	for (int i = 0; i < p.size(); i++)
	{
		cout << i + 1 << ". " << p[i]->name <<"      ( Stock:"<<p[i]->stock<<")"<< endl;
	}
	for (int i = 0; i < p.size(); i++) delete p[i]; //fix memory leak
}

void Product::viewProductInf(vector <Product*> p, int no)
{
	if (no > p.size()) cout << "This product is unavailable!" << endl;
	else
	{
		cout << "Product Information" << endl;
		cout << "ID: " << p[no - 1]->ID << endl;
		cout << "Name: " << p[no - 1]->name << endl;
		cout << "Price: " << p[no - 1]->price << endl;
		cout << "Stock: " << p[no - 1]->stock << endl;
		cout << "CPU: " << p[no - 1]->cpu << endl;
		cout << "Ram: " << p[no - 1]->ram << endl;
		cout << "Storage: " << p[no - 1]->storage << endl;
	}
}

void Product::compareProduct()
{
	system("cls");
	vector <Product*> p;
	loadProduct(p);
	int retry = 1, p1, p2;
	while (retry == 1)
	{
		retry = 2;
		system("cls");
		listProduct();
		cout << "Please choose 2 products to compare: ";
		cin >> p1 >> p2;
		if (p1 > p.size() || p2 > p.size())
		{
			cout << "Product unavailable! Try again?\n1.Yes\n2.No\n";
			cin >> retry;
		}
		else
		{
			system("cls");
			cout << "Compare"; gotoxy(25, 0); cout << "Product"; gotoxy(50, 0); cout << "Product 2" << endl;
			cout << "Name"; gotoxy(25, 1); cout << p[p1 - 1]->name; gotoxy(50, 1); cout << p[p2 - 1]->name << endl;
			cout << "Price"; gotoxy(25, 2); cout << p[p1 - 1]->price; gotoxy(50, 2); cout << p[p2 - 1]->price << endl;
			cout << "CPU"; gotoxy(25, 3); cout << p[p1 - 1]->cpu; gotoxy(50, 3); cout << p[p2 - 1]->cpu << endl;
			cout << "Ram"; gotoxy(25, 4); cout << p[p1 - 1]->ram; gotoxy(50, 4); cout << p[p2 - 1]->ram << endl;
			cout << "Storage"; gotoxy(25, 5); cout << p[p1 - 1]->storage; gotoxy(50, 5); cout << p[p2 - 1]->storage << endl;
		}
	}
	for (int i = 0; i < p.size(); i++) delete p[i];
}



int Product::getID()
{
	return ID;
}

int Product::getPrice()
{
	return price;
}

int Product::getStock()
{
	return stock;
}

int Product::getRam()
{
	return ram;
}

int Product::getStorage()
{
	return storage;
}

string Product::getName()
{
	return name;
}

string Product::getCpu()
{
	return cpu;
}

void Product::setID(int& id)
{
	ID = id;
}

void Product::setPrice(int& Price)
{
	price = Price;
}

void Product::setStock(int& Stock)
{
	stock = Stock;
}

void Product::setRam(int& Ram)
{
	ram = Ram;
}

void Product::setStorage(int& Storage)
{
	storage = Storage;
}

void Product::setName(string& Name)
{
	name = Name;
}

void Product::setCpu(string& CPU)
{
	cpu = CPU;
}

void Product::loadProduct(vector <Product*>& p)
{
	int n;
	Product* pd;
	ifstream fin;
	fin.open("Data/product.txt");
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

void Product::saveProduct(vector<Product*> p)
{
	ofstream fout;
	fout.open("Data/product.txt");
	fout << p.size() << endl;
	for (int i = 0; i < p.size(); i++)
	{
		fout << p[i]->ID << endl;
		fout << p[i]->name << endl;
		fout << p[i]->price << endl;
		fout << p[i]->stock << endl;
		fout << p[i]->cpu << endl;
		fout << p[i]->ram << endl;
		fout << p[i]->storage << endl;
	}
	fout.close();
}

void Product::output() {
	cout << endl << name << endl;
	cout << "Chip: " << cpu << endl;
	cout << "Ram: " << ram << endl;
	cout << "Storage: " << storage << endl;
	cout << "Price: " << price << endl;
}

void Order::searchProduct() {
	string name;
	cout << "Searching (Enter name): " << endl;
	getline(cin, name, '\n');
	getline(cin, name, '\n');

	char* tmpName = new char[name.length() + 1];
	strcpy(tmpName, name.c_str());

	//chuan hoa ten nhap vao
	for (int i = 0; i < strlen(tmpName); i++)
	{
		if (tmpName[i] >= 65 && tmpName[i] <= 90) {
			tmpName[i] += 32;
		}
	}
	string strName(tmpName);
	loadFromTxt();
	//chuan hoa ten tu file, sau do so sanh
	for (int i = 0; i < cart.size(); i++)
	{
		char* tmpProductName = new char[cart[i]->getName().length() + 1];
		strcpy(tmpProductName, cart[i]->getName().c_str());

		for (int i = 0; i < strlen(tmpProductName); i++)
		{
			if (tmpProductName[i] >= 65 && tmpProductName[i] <= 90) {
				tmpProductName[i] += 32;
			}
		}
		string strProductName(tmpProductName);

		int flag = 0;
		for (int i = 0; i < strlen(tmpName); i++)
		{
			if (tmpName[i] == tmpProductName[i])
				flag++;
		}
		if (flag == strlen(tmpName))cart[i]->output();

		delete[]tmpProductName;
	}

	delete[]tmpName;
}

Order::Order()
{
	srand(unsigned(time(NULL)));
	ID = 0;
	purchaser = "//";
	purchase.d = 0;
	purchase.m = 0;
	purchase.y = 0;
	status = 0;
	voucher_ID = 0;
	total = 0;
}

// VOUCHER
Voucher::Voucher()
{
	srand(unsigned(time(NULL)));
	code = 0;
	stock = 0;
	discount = 0;
	expire.d = 0;
	expire.y = 0;
	expire.m = 0;
}

void Voucher::createVoucher() {
	cout << "The number of voucher you want to create: ";
	cin >> stock;
	cout << "Expire date: " << endl;
	expire.input();
	cout << "Discount (ex: 200.000 vnd) : ";
	cin >> discount;
	code = rand() % (RAND_MAX)+1000;
	saveToTxt();
	cout << "Successfully!!!" << endl;
}

void Voucher::saveToTxt() {
	int flag = 1;
	ifstream temp;
	ofstream voucher_txt;
	temp.open("Data/Voucher.txt");
	if (!temp.is_open()) {
		cout << "Can't open Voucher.txt file" << endl;
		flag = 0;
	}
	if (temp.peek() == ifstream::traits_type::eof()) {
		flag = 0;
		temp.close();
	}
	if (flag == 0) voucher_txt.open("Data/Voucher.txt");
	else voucher_txt.open("Data/Voucher.txt", ios_base::app);
	voucher_txt << code << endl;
	voucher_txt << expire.y << " " << expire.m << " " << expire.d << endl;
	voucher_txt << discount << endl;
	voucher_txt << stock << endl;
	voucher_txt.close();
}

void Voucher::loadFromTxt() {
	ifstream voucher_txt;
	voucher_txt.open("Data/Voucher.txt");
	if (!voucher_txt.is_open()) {
		cout << "Can't open file Data/Voucher.txt" << endl;
	}
	else {
		int n;
		voucher_txt >> n;
		Voucher* v = NULL;
		for (int i = 0; i < n; i++)
		{
			v = new Voucher;
			voucher_txt >> v->code;
			voucher_txt >> v->expire.y >> v->expire.m >> v->expire.d;
			voucher_txt >> v->discount;
			voucher_txt >> v->stock;
			list.push_back(v);
		}
	}
	voucher_txt.close();
}

void Voucher::saveListToTxt() {
	ofstream fout;
	fout.open("Data/Voucher.txt");
	if (!fout.is_open()) {
		cout << "Can't open file Data/Voucher.txt" << endl;
	}
	else {
		fout << list.size() << endl;
		for (int i = 0; i < list.size(); i++)
		{
			fout << list[i]->code << endl;
			fout << list[i]->expire.y<<" " << list[i]->expire.m<<" " << list[i]->expire.d << endl;
			fout << list[i]->discount << endl;
			fout << list[i]->stock << endl;
		}
	}
	fout.close();
}

Voucher::~Voucher() {
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
	list.clear();
}

string Account::getUsername()
{
	return user;
}

void Account::changeProfileInformation()
{
	return;
}

void Product::inputData(ifstream& fin)
{
	fin >> ID;
	getline(fin, name);
	getline(fin, name);
	fin >> price;
	getline(fin, cpu);
	getline(fin, cpu);
	fin >> ram;
	fin >> storage;
}

void Order::inputData(ifstream& fin)
{
	Product* product;
	fin >> ID;
	getline(fin, purchaser);
	getline(fin, purchaser);
	fin >> purchase.y;
	fin >> purchase.m;
	fin >> purchase.d;
	fin >> status;
	fin >> voucher_ID;
	fin >> total;
	int n_products;
	fin >> n_products;
	for (int i = 0; i < n_products; i++)
	{
		product = new Product;
		product->inputData(fin);
		cart.push_back(product);
	}
}

vector<Order*> Order::loadListOfOrder()
{
	vector<Order*> list;
	Order* order;
	ifstream fin;
	fin.open("Data/Orders.txt");
	if (!fin.is_open())
	{
		fin.close();
		return list;
	}
	int n_orders;
	fin >> n_orders;
	for (int i = 0; i < n_orders; i++)
	{
		order = new Order;
		order->inputData(fin);
		list.push_back(order);
	}
	return list;
	fin.close();
}

void Order::saveOrder(vector<Order*>& list)
{
	ofstream list_orders;
	list_orders.open(((string)".//Data//Orders.txt").c_str(), ios::trunc);
	if (!list_orders.is_open()) {
		cout << "Orders.txt can't be opened" << endl;
		exit(0);
	}
	list_orders << list.size() << endl;
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->outputData(list_orders);
	}

	list_orders.close();
}

void Product::outputData(ofstream& fout)
{
	fout << ID << endl;
	fout << name << endl;
	fout << price << endl;
	fout << cpu << endl;
	fout << ram << endl;
	fout << storage << endl;
}

void Order::outputData(ofstream& fout)
{
	fout << ID << endl;
	fout << purchaser << endl;
	fout << purchase.y << " " << setfill('0') << setw(2) << purchase.m << " " << setfill('0') << setw(2) << purchase.d << endl;
	fout << status << endl;
	fout << voucher_ID << endl;
	fout << total << endl;
	fout << cart.size() << endl;
	for (int i = 0; i < cart.size(); i++)
	{
		cart[i]->outputData(fout);
	}
}
void Order::calCart()
{
	for (int i = 0; i < cart.size(); i++) total += cart[i]->getPrice();
}

bool Order::checkCart()
{
	if (cart.size() == 0)
	{
		cout << "Cart is empty" << endl;
		return false;
	}
	else return true;
}

int Date::compareDate(int day, int month, int year)
{
	if (this->y < year)
	{
		return 0;
	}
	else if (this->y == year && this->m < month)
	{
		return 0;
	}
	else if (this->m == month && this->d < day)
	{
		return 0;
	}
	return 1;
}
void Voucher::usesVoucher(vector<Order*>& order,string username)
{
	int id,flag1 = 0,flag2 = 0;
	Order o;
	time_t now = time(0);
	struct tm newtime;
	localtime_s(&newtime, &now);
	int yearnow = 1900 + newtime.tm_year;
	int monthnow = 1 + newtime.tm_mon;
	int daynow = newtime.tm_mday;
	loadFromTxt();
	if (list.size() == 0)
	{
		cout << "Don't have any voucher to use" << endl;
	}
	else
	{
		for (int i = 0; i < order.size(); i++)
		{
			if (strcmp(order[i]->getPurchaser().c_str(), username.c_str()) == 0)
			{
				flag1 = 1;
				for (int j = 0; j < list.size(); j++)
				{
					if (order[i]->getVoucherID() == list[j]->code&& list[j]->stock!=0)
					{
						flag2 = 1;
						int temp = order[i]->getTotal();
						temp = temp - list[j]->discount;
						order[i]->setTotal(temp);
						list[j]->stock = list[j]->stock - 1;
						o.saveOrder(order);
						saveListToTxt();
						break;
					}
				}
			}
		}
		if (flag1 != 1) cout << "Doesn't have order to use voucher" << endl;
		else if (flag2 != 1) cout << "ID voucher is valid or voucher out of stock" << endl;
		else cout << "Uses voucher succesfully" << endl;
	}
}

int getMonth(char* pch)
{
	if (strcmp(pch, "Jan") == 0) return 1;
	if (strcmp(pch, "Feb") == 0) return 2;
	if (strcmp(pch, "Mar") == 0) return 3;
	if (strcmp(pch, "Apr") == 0) return 4;
	if (strcmp(pch, "May") == 0) return 5;
	if (strcmp(pch, "Jun") == 0) return 6;
	if (strcmp(pch, "Jul") == 0) return 7;
	if (strcmp(pch, "Aug") == 0) return 8;
	if (strcmp(pch, "Sep") == 0) return 9;
	if (strcmp(pch, "Oct") == 0) return 10;
	if (strcmp(pch, "Nov") == 0) return 11;
	if (strcmp(pch, "Dec") == 0) return  12;
}

void getCurrentDate(Date& dCur)
{
	time_t tt;
	struct tm* ti;
	time(&tt);
	ti = localtime(&tt);
	ti->tm_year;
	char temp[MAX];
	strcpy(temp, asctime(ti));
	char* pch;
	pch = strtok(temp, " ");
	pch = strtok(NULL, " ");
	dCur.m = getMonth(pch);
	pch = strtok(NULL, " ");
	dCur.d = atoi(pch);
	pch = strtok(NULL, " ");
	strcpy(temp, pch);
	pch = strtok(NULL, " ");
	dCur.y = atoi(pch);
	cout << dCur.d << " " << dCur.m << " " << dCur.y << endl;
}


Product& Product::operator=(const Product& copy)
{
	this->ID = copy.ID;
	this->price = copy.price;
	this->stock = copy.stock;
	this->ram = copy.ram;
	this->storage = copy.storage;
	this->name = copy.name;
	this->cpu = copy.cpu;

	return *this;
}
