#include "..//Header//password.h"

string SHA256HashString(string aString) {
	std::string digest;
	CryptoPP::SHA256 hash;

	CryptoPP::StringSource foo(aString, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::Base64Encoder(
				new CryptoPP::StringSink(digest), false)));

	return digest;
}

void enterPass(string& pass)
{
	int p = 0;
	char ch, tPass[MAX];
	while (true)
	{
		ch = _getch();
		if (ch == ENTER || ch == TAB)
		{
			tPass[p] = '\0';
			break;;
		}
		else if (ch == BKSP)
		{
			if (p > 0)
			{
				p--;
				cout << "\b \b";
			}
		}
		else
		{
			tPass[p++] = ch;
			cout << "* \b";
		}
	}
	pass = tPass;
	pass = SHA256HashString(pass);
}