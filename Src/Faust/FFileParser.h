#ifndef FFILE_PARSER_H
#define FFILE_PARSER_H

#include "Utils.h"

#include "FEvent.h"

struct EventInfo
{
	string sName;
	string sPrefix;
	string sSuffix;
	string sEndLine;

	bool bList;
	bool bWord;

	EventInfo() : sName(""), sPrefix(""), sSuffix(""), sEndLine(""), bList(false), bWord(false)
};

enum EventInfoType
{
	EIT_Name,
	EIT_Ref,
	EIT_StartDate,
	EIT_EndDate,
	EIT_Date,
	EIT_Location,
	EIT_Desc,
	EIT_Role,
	EIT_Tag,

	EventInfoType_MAX
};

class FFileParser
{
	public:
		FFileParser(const char* path);
		~FFileParser();

		bool IsEOF() const { return (m_iLine >= m_sData.size()); }

		void ParseParam();
		bool ParseName(string& sName) const;
		bool ParseEvent(FEvent& oEvent) const;

	private:
		bool GetField(string& sName, string& sField) const;


	private:
		vector<string>		m_sData;
		uint				m_iLine;

		EventInfo			m_oInfo[EventInfoType_MAX];

		string				m_sNameStart, m_sNameEnd;
		string				m_sInfoStart, m_sInfoEnd;
};

#endif