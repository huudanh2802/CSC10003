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

void Store::loadFromCSV(ifstream& fin) {
	
	string s;
	fin.ignore(1);
	getline(fin, s);

	Product* p;

	while (getline(fin, s)) {
		p = NULL;
		p = new Product;
		p->loadFromCSV(fin, s);
		store.push_back(p);
	}

	fin.close();
}

void Store::loadFromTxt() {
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
		store.push_back(p);
	}

	fin.close();
}

void Store::saveToTxt() {
	ofstream fout;
	fout.open(".//Data//product.txt");

	fout << store.size() << endl;
	for (int i = 0; i < store.size(); i++)
	{
		store[i]->saveToTxt(fout);
	}
}

void Store::deleteListProduct() { 
	for (int i = 0; i < store.size(); i++)
	{
		delete store[i];
	}
	store.clear();
}

void Store::importProductFromCSV() {
	Date tempDate;
	cout << "Import date: " << endl;
	tempDate.input();

	string tempStr;
	tempStr = to_string(tempDate.y) + to_string(tempDate.m) + to_string(tempDate.d);
	tempStr = "product" + tempStr + ".csv";
	ifstream fin;
	fin.open(tempStr);
	Store fromCsv;
	if(fin.is_open())
		fromCsv.loadFromCSV(fin);
	else {
		cout << "Can not open " <<tempStr<<" file" << endl;
		return;
	}
	loadFromTxt();

	Product* temp = NULL;
	for (int i = 0; i < fromCsv.store.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < store.size(); j++)
		{
			if (store[j]->comparingID(*fromCsv.store[i])) {
				store[j]->updateStock(*fromCsv.store[i]);
				flag = 1;
			}
			
		}
		if (flag == 0) {
		temp = fromCsv.store[i];
		store.push_back(temp);
		}
	}

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
	user_data.open(((string)".//Data//user.txt").c_str(),ios::trunc);
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
	for (int i = 0; i < num; i++)
		delete data[i];
	user_data.close();
}

int Account::checkLogin(const string& input_username, const string& input_password)
{
	if (user.compare(input_username) == 0 && pass.compare(input_password) == 0) return 1;
	else return 0;
}

Account* Database::login()
{
	Account* account =nullptr;
	string input_username, input_password;
	while (true)
	{
		cout << "Username :";
		getline(cin, input_username);
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
			cout << "Invalid username/password" << endl;
		}
	}
	return account;
}

void Database::createAccount() {
	Customer* acc = new Customer;
	acc->createAccount();
	data.push_back(acc);
	num++;
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
		if (tempPass1.compare( tempPass2) != 0) cout << "\nNew Password and confirmed new password is different" << endl;
		else if (pass.compare( tempPass1) == 0) cout << "\nNew Password must different from old password" << endl;
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
}

void Product::viewProduct()
{
	system("cls");
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
}

void Product::editProduct()
{
	system("cls");
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
}

void Product::removeProduct()
{
	system("cls");
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
}

void Product::listProduct()
{
	system("cls");
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
		cout << i + 1 << ". " << p[i]->name << endl;
	}	
}

void Product::viewProductInf(vector <Product*> p, int no)
{

	if (no > p.size()) cout << "This product is unavailable!" << endl;
	else
	{
		system("cls");
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

void Product::setID(int &id)
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

void Product::setName(string &Name)
{
	name = Name;
}

void Product::setCpu(string& CPU)
{
	cpu = CPU;
}

void Product::loadProduct(vector <Product*> &p)
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

Order::Order()
{
	ID = 0;
	purchase.d = 0;
	purchase.m = 0;
	purchase.y = 0;
	status = 0;
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
	cout << "Expire date: "<<endl;
	expire.input();
	cout << "Discount (ex: 200.000 vnd) : ";
	cin >> discount;
	code = rand() % (RAND_MAX) + 1000;

	saveToTxt();
	cout << "Successfully!!!" << endl;
}

void Voucher::saveToTxt() {
	ofstream voucher_txt;
	voucher_txt.open("Data/Voucher.txt");
	if (!voucher_txt.is_open()) {
		cout << "Can't open Voucher.txt file" << endl;
		return;
	}
	else {
		voucher_txt << code << endl;
		voucher_txt << expire.y << " " << expire.m << " " << expire.d << endl;
		voucher_txt << discount << endl;
		voucher_txt << stock << endl;
	}
	
}

string Account::getUsername()
{
	return user;
}

