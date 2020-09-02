#ifndef _PASSWORD_H
#define _PASSWORD_H_

#define ENTER 13
#define TAB 9
#define BKSP 8

#include "../Crypto++/sha.h"
#include "../Crypto++/filters.h"
#include "../Crypto++/base64.h"
#include "head.h"

string SHA256HashString(string aString);
void enterPass(string& pass);
#endif