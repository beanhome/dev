#include "StringUtils.h"

string FormatString(const char* format, ...)
{
	va_list arglist;
	va_start(arglist, format);

	int nb = _vscprintf(format, arglist);

	char* buff = new char[nb+2];

	_vsprintf_s_l(buff, nb+1, format, NULL, arglist);

	string output(buff);

	free(buff);

	return output;
}

void Tokenize(const string& s, const string& delimiters, vector<string>& tokens)
{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

vector<string> Tokenize(const string& s, const string& delimiters)
{
	vector<string> tokens;
	Tokenize(s, delimiters, tokens);
	return tokens;
}
