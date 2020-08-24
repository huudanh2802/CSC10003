#ifndef _HEAD_H_
#define _HEAD_H_
#define MAX 1000
#define WINWIDTH 113
#define WINHEIGHT 1000
#define _WIN32_WINNT 0x0502
#define MAINICON 101   
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
#include <crtdbg.h>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
using namespace std;

struct Date {
	int d, m, y;
	void input();
	int compareDate(int day, int month, int year);
};

class Database;
class Order;

class Account {
private: string user, pass;
public:
	Account();
	virtual void inputData(ifstream& fin);
	virtual void outputData(ofstream& fin);
	virtual void viewProfile();
	virtual void viewMenu(Database& account_listt) = 0;
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
	void createAccount(Account* acc);
	void changeProfileInformation(string user_name);
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
	void loadProduct(vector <Product*>& p);
	void saveProduct(vector <Product*> p);
	int getID();
	int getPrice();
	int getStock();
	int getRam();
	int getStorage();
	string getName();
	string getCpu();
	void setID(int& id);
	void setPrice(int& Price);
	void setStock(int& Stock);
	void setRam(int& Ram);
	void setStorage(int& Storage);
	void setName(string& Name);
	void setCpu(string& CPU);
	void outputInfProduct();
	void inputData(ifstream& user_data);
	void output(); //for customer( without stock )
	void outputData(ofstream& fout);
	void resizeStock();
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
	void cancelOrder(string user_name, vector<Order*>& list);
	int getTotal();
	void setTotal(int x);
	int getVoucherID();
	string getPurchaser();
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

void getCurrentDate(Date& dCur);
void gotoxy(int x, int y);
void loadingScreen();
void store_management_program();
void menu();


#endif