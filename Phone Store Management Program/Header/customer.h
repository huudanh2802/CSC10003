#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "head.h"

class Customer :public Account {
private:int type;
	   string name;
	   Date dob;
	   int phone;
	   string address;
public:
	Customer();
	void inputData(ifstream& user_data);
	void outputData(ofstream& fin);
	void viewProfile();
	void viewMenu(Database& list);// Store and execute function, pass in Database for function create, change profile information
	int checkName(const string& searchname);
	int checkAccount();
	void editProfile();
	int Type();
	string Name();
	string getAddress();
	Date Dob();
	int Phone();
	void createAccount();
	void changeProfileInformation();
};

#endif