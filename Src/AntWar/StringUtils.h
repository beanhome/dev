#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "Utils.h"

string FormatString(const char* format, ...);
void Tokenize(const string& s, const string& delimiters, vector<string>& tokens);
vector<string> Tokenize(const string& s, const string& delimiters = string(" "));

#endif
