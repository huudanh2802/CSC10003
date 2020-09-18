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
	void inputData(fstream& user_data);
	void outputData(fstream& fin);
	void viewProfile();
	void viewMenu(Database& account_list,int &switchS);// Store and execute function, pass in Database for function create, change profile information
	int checkName(const string& searchname);
	int checkAccount();
	void editProfile();
	int Type();
	string Name();
	string getAddress();
	Date Dob();
	int Phone();
	void createAccount( Database& list);
	void changeProfileInformation();
	void export_file(ofstream& fout);
};

#endif