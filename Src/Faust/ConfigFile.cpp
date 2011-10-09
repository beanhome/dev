#include "ConfigFile.h"
#include "Utils.h"
#include "Config.h"


ConfigFile::ConfigFile(const string& sPath)
	: m_sPath(sPath)
{
}

bool ConfigFile::Read()
{
	FILE* pFile = NULL;
	
	fopen_s(&pFile, m_sPath.c_str(), "rt");

	if (pFile != NULL)
	{
		const int iBuffSize = 128;
		char pBuff[iBuffSize];

		while (fgets(pBuff, iBuffSize, pFile) != NULL)
		{
			int i = 0;
			while (isspace(pBuff[i])) i++;

			if (pBuff[i] == 0 || pBuff[i] == '#')
				continue;
			
			int j=i;

			while (!isspace(pBuff[j])) j++;
			if (pBuff[j] == 0)
			{
				Log("Error Read Config File : %s", pBuff);
				continue;
			}

			string sName(pBuff+i, j-i);

			while (pBuff[j] != '=' || pBuff[j] == 0) j++;
			if (pBuff[j] == 0)
			{
				Log("Error Read Config File : %s", pBuff);
				continue;
			}
			
			i = j+1;

			while (isspace(pBuff[i])) i++;
			if (pBuff[i] == 0)
			{
				Log("Error Read Config File : %s", pBuff);
				continue;
			}

			j = i;
			
			while (!isspace(pBuff[j])) j++;
			if (pBuff[j] == 0)
			{
				Log("Error Read Config File : %s", pBuff);
				continue;
			}

			string sValue(pBuff+i, j-i);

			m_aList.insert(ConfigPair(sName, sValue));
		}

		fclose(pFile);
		return true;
	}

	return false;
}
void ConfigFile::Write()
{
	FILE* pFile = NULL;

	fopen_s(&pFile, m_sPath.c_str(), "wt");

	if (pFile != NULL)
	{
		ConfigMap::iterator begin = m_aList.begin();
		ConfigMap::iterator end = m_aList.end();
		ConfigMap::iterator it;
		for (it = begin ; it != end ; ++it)
		{
			fprintf_s(pFile, "%s = %s\n", it->first.c_str(), it->second.c_str());
		}

		fclose(pFile);
	}
}


string ConfigFile::GetOption(const string& sName) const
{
	ConfigMap::const_iterator it = m_aList.find(sName);

	if (it != m_aList.end())
		return it->second;

	return string();
}

void ConfigFile::SetOption(const string& sName, const string& sValue)
{
	ConfigMap::iterator it = m_aList.find(sName);

	if (it != m_aList.end())
		it->second = sValue;
	else
		m_aList.insert(ConfigPair(sName, sValue));
}
