#include "FFileParser.h"
#include "FApp.h"
#include "FSQLClient.h"
#include "FQuery.h"


FFileParser::FFileParser()
{

}

FFileParser::FFileParser(const FFileParser& src)
{
}

FFileParser::~FFileParser()
{
}

bool FFileParser::ParseName(FILE* pFile, string& sName) const
{
	char c;

	sName.clear();

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (!isspace(c))	break;
	}

	if (c != '[')
		sName += c;

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (c == ']')		break;

		sName += c;
	}

	return true;
}

bool FFileParser::ParseEvent(FILE* pFile, FEvent& oEvent) const
{
	bool res = true;
	string sName, sField;

	bool bEnd = false;
	while (!bEnd)
	{
		bEnd = !GetField(pFile, sName, sField);
		if (sName == "Ref")			oEvent.SetParent(sField);
		if (sName == "Start")		oEvent.GetDatation().GetStart().Parse(sField.c_str());
		if (sName == "End")			oEvent.GetDatation().GetEnd().Parse(sField.c_str());
		if (sName == "Desc")		oEvent.SetDescription(sField.c_str());
		if (sName == "Location")	oEvent.AddLocation(sField.c_str());
		if (sName == "Roles")		oEvent.AddRoles(sField);
		if (sName == "Tags")		oEvent.AddTags(sField);
	}

	oEvent.ForceComplete();
	return true;
}

bool FFileParser::GetField(FILE* pFile, string& sName, string& sField) const
{
	char c;

	sName.clear();
	sField.clear();

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (c == '[')		return false;
		if (c == '#')		break;
		if (!isspace(c))	{ sName+=c; break; }
	}

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (c == '[')		return false;
		if (isspace(c))		break;

		sName += c;
	}

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (c == '[')		return false;
		if (!isspace(c))	break;
	}

	sField += c;

	while(true)
	{
		c = fgetc(pFile);
		if (c == EOF)		return false;
		if (c == '[')		return false;
		if (c == '#')		break;

		sField += c;
	}

	return true;
}