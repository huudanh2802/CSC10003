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
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

using namespace std;

struct Date {
	int d, m, y;
	void input();
	int compareDate(int day, int month, int year);
	void getCurrentDate();
};

class Database;
class Order;

class Account {
protected: string user, pass;
public:
	Account();
	virtual void inputData(fstream& fin);
	virtual void outputData(fstream& fin);
	virtual void viewProfile();
	virtual void viewMenu(Database& account_listt,int &switchS) = 0;
	int checkLogin(const string& input_username, const string& input_password);
	Account* login(const string& input_username, const string& input_pass);
	void changePassword();
	virtual void createAccount( Database& list);
	virtual int checkName(const string& searchname) = 0;
	virtual int checkAccount() = 0;
	virtual bool checkUser(const string&user);
	virtual void editProfile() = 0;
	virtual int Type() = 0;
	virtual void changeProfileInformation();
	void changeProfileInData(const string& user_name);
};

class Database {
private:int num;
	   vector<Account*>data;
	   fstream data_file;
public:
	Database();
	~Database();
	Account* login();
	int Number();
	void searchviewProfilecustomer();
	void editProfilecustomer();
	void exportCustomerlist();
	void createAccount(Account* acc);
	void changeProfileInformation(const string& user_name);
	bool checkUser(const string& name);
};

/// <PRODUCT>
class Product {
private:
	int ID, price, stock, ram, storage;
	string name, cpu;

public:
	Product();
	Product& operator=(const Product& copy);
	void loadFromCSV(ifstream& fin, string data);
	void saveToTxt(ofstream& fout);
	void loadFromTxt(ifstream& fin);
	bool comparingID(const Product&);
	void updateStock(const Product&);
	void createProduct();
	void viewProduct();
	void viewProductBaseOnCategories();
	void editProduct();
	void removeProduct();
	void listProduct();
	void viewProductInf(vector <Product*> p, int no);
	void compareProduct();
	void loadProduct(vector <Product*>& p);
	void saveProduct(vector <Product*> p);
	void outputInfProduct();
	void inputData(ifstream& user_data);
	void output(); //for customer( without stock )
	void outputData(ofstream& fout);
	void resizeStock();
	bool checkStock();
	int getPrice();
	bool checkID(const int& id);
	string getName();
};

/// </PRODUCT>

class Order {
private:int ID;
	   string purchaser;
	   vector<Product*>cart;
	   int status;
	   Date purchase;
	   int voucher_ID;
	   int total;
public:
	Order();
	void addProduct();
	void loadCartTxt(string user, string& name);
	void saveCartTxt(string user, string& name);
	void removeProduct();
	bool viewCart();
	void loadFromCSV(ifstream& fin);
	void saveToTxt();
	void loadFromTxt();
	void importProductFromCSV();
	void deleteListProduct();
	void searchProduct();
	void inputData(ifstream& user_data);
	vector<Order*> loadListOfOrder();
	void saveOrder(vector<Order*>& list);
	void outputData(ofstream& fout);
	void calCart();
	void checkOut(string user, string& name, vector<Order*>& list, int& flag);
	bool checkCart();
	void viewOrderStatus(vector<Order*>& list, string name);
	void editOrderStatus();
	void cancelOrder(string user_name, vector<Order*>& list);
	int getTotal();
	void setTotal(int x);
	int getVoucherID();
	string getPurchaser();
	void purchasedProductInAMonth( vector<Order*>& list);
};

class Voucher {
private:Date expire;
	   int code;
	   int stock, discount;
	   vector<Voucher*> list;
public:Voucher();
	  void createVoucher();
	  void loadFromTxt();
	  void saveToTxt();
	  void saveListToTxt();
	  ~Voucher();
	  void usesVoucher(vector<Order*>& Order,string username);
};
int menu(const char* s);

#endif