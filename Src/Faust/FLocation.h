#ifndef FLOCATION_H
#define FLOCATION_H

#include "Config.h"
#include "Utils.h"
#include "libpq-fe.h"

enum ELocElem
{
	Loc_Country,
	Loc_City,
	Loc_District,
	Loc_Street,
	Loc_Address,

	ELocElem_MAX
};


class FLocation
{
	public:
		FLocation();
		FLocation(PGresult* pRes, int iTuple);

		int GetKey() const { return m_uID; }
		void SetKey(uint id) { m_uID = id; }

		const string& GetValue(uint id) const { return  m_sValue[id]; }
		void SetValue(uint id, const string& sValue) { m_sValue[id] = sValue; }

		bool IsNull() const { return m_sValue[0].length() == 0; }
		string GetJoinQuery() const;

	public:
		bool UpdateID();
		void Save();

		string GetFormated() const;

	public:
		static FLocation Parse(const char* str);

	private:
		uint			m_uID;

		string			m_sValue[ELocElem_MAX];

	public:
		static const char* s_scolName[ELocElem_MAX];
};

struct ltloc
{
	bool operator()(const FLocation& l1, const FLocation& l2) const
	{
		for (uint i=0 ; i<ELocElem_MAX ; ++i)
		{
			int res = strcmp(l1.GetValue(i).c_str(), l2.GetValue(i).c_str());

			if (res != 0)
				return (res < 0);
		}

		return false;
	}
};




#endif