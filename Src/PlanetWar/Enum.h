#ifndef __ENUM_H__
#define __ENUM_H__

#include "Utils.h"

class Enum
{
	protected:
		typedef std::map<int, String> EnumMap;
		typedef std::pair<int, String> EnumPair;	public:

	public:
		Enum() : m_iId(0) {}
		Enum(int id) : m_iId(id) {}

		int GetInt() const { return m_iId; }
		virtual const EnumMap& GetMap() const = 0;

		operator int() { return m_iId; }
		operator const String&() { return GetString(); }
		operator const char*() { return GetString().c_str(); }

		// operator =
		// operator ++ (les deux)
		// operator -- (les deux)
		// operator +=
		// operator -=
		// operator ==
		// operator !=
		// operator <
		// operator >

		const String& GetString() const
		{
			EnumMap::const_iterator it = GetMap().find(m_iId);
			ASSERT(it != GetMap().end());
			return it->second;
		}

	protected:
		int m_iId;
};

#define BEGIN_CREATE_ENUM(EnumName)										\
class EnumName : public Enum											\
{																		\
	public:																\
		EnumName()														\
			: Enum()													\
		{																\
			m_iId = GetMap().begin()->first;							\
		}																\
																		\
		EnumName(int id)												\
			: Enum(id)													\
		{																\
			if (GetMap().find(m_iId) == GetMap().end())					\
				m_iId = GetMap().begin()->first;						\
		}																\
																		\
	private:															\
		void BuildMap(Enum::EnumMap& Map) const							\
		{																\
			int id = 0;													\

#define ADD_ENUM(Value)													\
	ASSERT(Map.find(Value) == Map.end());								\
	id = Value;															\
	Map.insert(Enum::EnumPair(id++, #Value));							\

#define ADD_ENUM_EX(Value, ID)											\
	ASSERT(Map.find(ID) == Map.end());									\
	id = ID;															\
	Map.insert(Enum::EnumPair(id++, #Value));							\


#define END_CREATE_ENUM()												\
			ASSERT(Map.size() > 0);										\
		}																\
																		\
		const EnumMap& GetMap() const									\
		{																\
			static Enum::EnumMap s_Map;									\
																		\
			if (s_Map.size() == 0)										\
				BuildMap(s_Map);										\
																		\
			return s_Map;												\
		}																\
};																		\

enum ETest
{
	None,
	Value01,
	Value02,
	Value03
};

BEGIN_CREATE_ENUM(EnumTest)
ADD_ENUM(None);
ADD_ENUM(Value01);
ADD_ENUM(Value02);
ADD_ENUM(Value03);
END_CREATE_ENUM()

#endif
