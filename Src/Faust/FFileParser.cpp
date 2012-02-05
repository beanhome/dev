#include "FFileParser.h"
#include "FApp.h"
#include "FSQLClient.h"
#include "FQuery.h"


FFileParser::FFileParser(const char* path)
	: m_iLine(0)
	, m_sNameStart("[")
	, m_sNameEnd("]")
	, m_sInfoStart("#")
	, m_sInfoEnd("")
{
	FILE* pFile;
	fopen_s(&pFile, path, "rt");

	const int BUFFSIZE = 256;

	char buff[BUFFSIZE];

	bool eof = false;

	while (!eof)
	{
		string str;

		do		
		{
			eof = (fgets(buff, BUFFSIZE, pFile) == NULL);
			str += buff;
		} while (str[str.length()-1] != '\n' && buff[0] != 0);
		
		m_sData.push_back(str);
	}

	fclose(pFile);





	m_oInfo[EIT_Name].sName = "";
	m_oInfo[EIT_Name].sPrefix = "==";
	m_oInfo[EIT_Name].sSuffix = "";
	m_oInfo[EIT_Name].sEndLine = "==";

	m_oInfo[EIT_Ref].sName = "Ref";
	m_oInfo[EIT_Ref].sPrefix = "<!--";
	m_oInfo[EIT_Ref].sSuffix = ":";
	m_oInfo[EIT_Ref].sEndLine = "-->";

	m_oInfo[EIT_StartDate].sName = "Start";
	m_oInfo[EIT_StartDate].sPrefix = "";
	m_oInfo[EIT_StartDate].sSuffix = ":";

	m_oInfo[EIT_EndDate].sName = "End";
	m_oInfo[EIT_EndDate].sPrefix = "";
	m_oInfo[EIT_EndDate].sSuffix = ":";

	m_oInfo[EIT_Date].sName = "Date";
	m_oInfo[EIT_Date].sPrefix = "";
	m_oInfo[EIT_Date].sSuffix = ":";

	m_oInfo[EIT_Location].sName = "Location";
	m_oInfo[EIT_Location].sPrefix = "";
	m_oInfo[EIT_Location].sSuffix = ":";
	m_oInfo[EIT_Location].bList = true;

	m_oInfo[EIT_Desc].sName = "Desc";
	m_oInfo[EIT_Desc].sPrefix = "";
	m_oInfo[EIT_Desc].sSuffix = ":";

	m_oInfo[EIT_Role].sName = "Role";
	m_oInfo[EIT_Role].sPrefix = "";
	m_oInfo[EIT_Role].sSuffix = ":";
	m_oInfo[EIT_Role].bList = true;
	m_oInfo[EIT_Role].bWord = true;

	m_oInfo[EIT_Tag].sName = "Tag";
	m_oInfo[EIT_Tag].sPrefix = "";
	m_oInfo[EIT_Tag].sSuffix = ":";
	m_oInfo[EIT_Tag].bList = true;
	m_oInfo[EIT_Tag].bWord = true;

}


FFileParser::~FFileParser()
{
}

void FFileParser::ParseParam()
{
	const char* sNameStart = "#NameStart";
	const char* sNameEnd = "#NameEnd";
	const char* sInfoStart = "#InfoStart";
	const char* sInfoEnd = "#InfoEnd";

	while (m_iLine < m_sData.size() && m_sData[m_iLine].compare(0, m_sNameStart.length(), m_sNameStart))
	{
		const string& line = m_sData[m_iLine];

		if (line.compare(0, strlen(sNameStart), sNameStart) == 0)
			m_sNameStart = line.substr(strlen(sNameStart), line.length());

		if (line.compare(0, strlen(sNameEnd), sNameEnd) == 0)
			m_sNameEnd = line.substr(strlen(sNameEnd), line.length());

		if (line.compare(0, strlen(sInfoStart), sInfoStart) == 0)
			m_sInfoStart = line.substr(strlen(sInfoStart), line.length());

		if (line.compare(0, strlen(sInfoEnd), sInfoEnd) == 0)
			m_sInfoEnd = line.substr(strlen(sInfoEnd), line.length());

		m_iLine++;
	}

	int start = 0, end = 0;

	start = m_sNameStart.find_first_of("\"");
	end = m_sNameStart.find_last_of("\"");
	m_sNameStart = m_sNameStart.substr(start+1, end-start-1);

	start = m_sNameEnd.find_first_of("\"");
	end = m_sNameEnd.find_last_of("\"");
	m_sNameEnd = m_sNameEnd.substr(start+1, end-start-1);

	start = m_sInfoStart.find_first_of("\"");
	end = m_sInfoStart.find_last_of("\"");
	m_sInfoStart = m_sInfoStart.substr(start+1, end-start-1);

	start = m_sInfoEnd.find_first_of("\"");
	end = m_sInfoEnd.find_last_of("\"");
	m_sInfoEnd = m_sInfoEnd.substr(start+1, end-start-1);

}

bool FFileParser::ParseName(string& sName) const
{
	regexp

	//char c;

	//sName.clear();

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (!isspace(c))	break;
	//}

	//if (c != '[')
	//	sName += c;

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (c == ']')		break;

	//	sName += c;
	//}

	return true;
}

bool FFileParser::ParseEvent(FEvent& oEvent) const
{
	//bool res = true;
	//string sName, sField;

	//bool bEnd = false;
	//while (!bEnd)
	//{
	//	bEnd = !GetField(pFile, sName, sField);
	//	if (sName == "Ref")			oEvent.SetParent(sField);
	//	if (sName == "Start")		oEvent.GetDatation().GetStart().Parse(sField.c_str());
	//	if (sName == "End")			oEvent.GetDatation().GetEnd().Parse(sField.c_str());
	//	if (sName == "Desc")		oEvent.SetDescription(sField.c_str());
	//	if (sName == "Location")	oEvent.AddLocation(sField.c_str());
	//	if (sName == "Roles")		oEvent.AddRoles(sField);
	//	if (sName == "Tags")		oEvent.AddTags(sField);
	//}

	//oEvent.ForceComplete();
	return true;
}

bool FFileParser::GetField(string& sName, string& sField) const
{
	//char c;

	//sName.clear();
	//sField.clear();

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (c == '[')		return false;
	//	if (c == '#')		break;
	//	if (!isspace(c))	{ sName+=c; break; }
	//}

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (c == '[')		return false;
	//	if (isspace(c))		break;

	//	sName += c;
	//}

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (c == '[')		return false;
	//	if (!isspace(c))	break;
	//}

	//sField += c;

	//while(true)
	//{
	//	c = fgetc(pFile);
	//	if (c == EOF)		return false;
	//	if (c == '[')		return false;
	//	if (c == '#')		break;

	//	sField += c;
	//}

	return true;
}