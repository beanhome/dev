#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "Utils.h"

class ConfigFile
{
	public:
		ConfigFile(const string& sPath);

		typedef map<string, string> ConfigMap;
		typedef pair<string, string> ConfigPair;

		bool Read();
		void Write();

		string GetOption(const string& sName) const;
		void SetOption(const string& sName, const string& sValue);

	private:
		string m_sPath;

		ConfigMap m_aList;
};

#endif