#ifndef FFILE_PARSER_H
#define FFILE_PARSER_H

#include "Utils.h"

#include "FEvent.h"

class FFileParser
{
	public:
		FFileParser();
		FFileParser(const FFileParser& src);
		~FFileParser();

		bool ParseName(FILE* pFile, string& sName) const;
		bool ParseEvent(FILE* pFile, FEvent& oEvent) const;

	private:
		bool GetField(FILE* pFile, string& sName, string& sField) const;


	private:
};

#endif