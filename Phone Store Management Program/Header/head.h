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

using namespace std;

struct Date {
	int d, m, y;
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
	virtual int checkName(const string& searchname) = 0;
	virtual int checkAccount() = 0;
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
	void Searchname();
};

class Product {
private:int ID, price, stock;
	   string name;
public:
	Product();
};

class Order {
private:int ID, num;
	   vector<Product*>cart;
public:
	Order();
};

class Voucher {
private:Date expire;
	   int stock, discount;
public:Voucher();
};
#endif