#ifndef _SELLER_H_
#define _SELLER_H_

#include "head.h"

class Seller :public Account {
private:int type;
	   string name;
	   Date dob;
	   int phone;
	   string title;
public:
	Seller();
	void inputData(ifstream &user_data);
	void outputData(ofstream& fin);
	void viewProfile();
	void viewMenu(Database& list);// Store and execute function, pass in Database for function edit, search account
	int checkAccount();
	int checkName(const string& searchname);
	void editProfile();
};

#endif