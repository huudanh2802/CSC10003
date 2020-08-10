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
	string getUsername();
	virtual void changeProfileInformation();
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
	void changeProfileInformation(string user_name);
};


/// <PRODUCT>
class Product {
private:
	int ID, price, stock, ram, storage;
	string name, cpu;

public:
	Product();
	void loadFromCSV(ifstream& fin, string data);
	void saveToTxt(ofstream& fout);
	void loadFromTxt(ifstream& fin);
	bool comparingID (const Product&);
	void updateStock(const Product&);
	void createProduct();
	void viewProduct();
	void editProduct();
	void removeProduct();
	void listProduct();
	void viewProductInf(vector <Product*> p, int no);
	void loadProduct(vector <Product*> &p);
	void saveProduct(vector <Product*> p);
	int getID();
	int getPrice();
	int getStock();
	int getRam();
	int getStorage();
	string getName();
	string getCpu();
	void setID(int &id);
	void setPrice(int &Price);
	void setStock(int &Stock);
	void setRam(int &Ram);
	void setStorage(int&Storage);
	void setName(string &Name);
	void setCpu(string& CPU);
	void outputInfProduct();
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
private:int ID;
	   vector<Product*>cart;
	   int status;
	   Date purchase;
public:
	Order();
	void addProduct();
	void loadCartTxt(string user, string& name);
	void saveCartTxt(string user,string&name);
	void removeProduct();
	bool viewCart();
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