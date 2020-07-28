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
	user_data.open(((string)".//Data//user.txt").c_str(), ios::trunc);
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
	Account* account = nullptr;
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
		if (tempPass1.compare(tempPass2) != 0) cout << "\nNew Password and confirmed new password is different" << endl;
		else if (pass.compare(tempPass1) == 0) cout << "\nNew Password must different from old password" << endl;
		else break;
	};
	pass = tempPass1;
}

Product::Product()
{
	ID = 0;
	price = 0;
	stock = 0;
	name = "//";
}

Order::Order()
{
	ID = 0;
	num = 0;
}

Voucher::Voucher()
{
	stock = 0;
	discount = 0;
	expire.d = 0;
	expire.y = 0;
	expire.m = 0;
}

void Database::Searchname()
{
	string searchname;
	cout << "Enter name of customer you want to search: ";
	getline(cin, searchname);
	for (int i = 0; i < num; i++)
	{
		if (data[i]->checkAccount() == 1)
		{
			if (data[i]->checkName(searchname))
			{
				data[i]->viewProfile();
			}
		}
	}
}