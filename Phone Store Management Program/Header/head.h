#ifndef _HEAD_H_
#define _HEAD_H_
#define MAX 1000
#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <conio.h>
#include<sstream>
#include<time.h>
#include<stdlib.h>


using namespace std;

struct Date {
	int d, m, y;
	void input();
};

class Database;

class Account {
private: string user, pass;
public:
	Account();
	virtual void inputData(ifstream& fin);
	virtual void outputData(ofstream& fin);
	virtual void viewProfile();
	virtual void viewMenu(Database& list) = 0;
	int checkLogin(const string& input_username, const string& input_password);
	Account* login(const string& input_username, const string& input_pass);
	void changePassword();
	virtual void createAccount();
	virtual int checkName(const string& searchname) = 0;
	virtual int checkAccount() = 0;
	virtual void editProfile() = 0;
	virtual int Type() = 0;
	virtual string Name() = 0;
	virtual string getAddress() = 0;
	virtual Date Dob() = 0;
	virtual int Phone() = 0;
};

class Database {
private:int num;
	   vector<Account*>data;
public:
	Database();
	void deleteData();
	void loadData(ifstream& user_data);
	Account* login();
	int Number();
	void searchviewProfilecustomer();
	void editProfilecustomer();
	void exportCustomerlist();
	void createAccount();
};


/// <PRODUCT>
class Product {
private:
	int ID, price, stock;
	string name;
public:
	Product();
	void loadFromCSV(ifstream& fin, string data);
	void saveToTxt(ofstream& fout);
	void loadFromTxt(ifstream& fin);
	bool comparingID (const Product&);
	void updateStock(const Product&);
	void createProduct();
	void loadProduct(vector <Product*> &p);
	void saveProduct(vector <Product*> p);

};

class Store {
private:
	string name;
	vector<Product*> store;
public:
	void loadFromCSV(ifstream& fin);
	void saveToTxt();
	void loadFromTxt();
	void importProductFromCSV();
	void deleteListProduct();
};


/// </PRODUCT>

class Order {
private:int ID, num;
	   vector<Product*>cart;
public:
	Order();
};

class Voucher {
private:Date expire;
	   int code;
	   int stock, discount;
public:Voucher();
	  void createVoucher();
	  void loadFromTxt();
	  void saveToTxt();
};
#endif