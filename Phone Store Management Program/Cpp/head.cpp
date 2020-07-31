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

	getline(ss, tmp, '\n');
	stock = stoi(tmp);

}

void Product::saveToTxt(ofstream& fout)
{
	fout << ID << endl;
	fout << name << endl;
	fout << price << endl;
	fout << stock << endl;
}

void Product::loadFromTxt(ifstream& fin) {
	fin >> ID;

	fin.ignore(1);
	getline(fin, name, '\n');

	fin >> price;
	fin >> stock;

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
	fin.open(".//Data//Product.txt");
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
	fout.open(".//Data//Product.txt");

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
	tempStr = "Product" + tempStr + ".csv";
	ifstream fin;
	fin.open(tempStr);
	Store fromCsv;
	if(fin.is_open())
		fromCsv.loadFromCSV(fin);
	else {
		cout << "Can not open this file" << endl;
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

Order::Order()
{
	ID = 0;
	num = 0;
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
}

void Voucher::saveToTxt() {
	ofstream voucher_txt;
	voucher_txt.open("Voucher.txt");
	voucher_txt << code<<endl;
	voucher_txt << expire.y<<" " << expire.m<<" "<<expire.d<<endl ;
	voucher_txt << stock;
}

