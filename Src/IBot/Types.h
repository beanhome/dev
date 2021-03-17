#ifndef TYPES_H
#define TYPES_H

#include "Utils.h"

typedef set<class IBFact*>						FactSet;
typedef set<class IBAction*> 					ActionSet;
typedef set<class IBNode*>				NodeSet;
typedef map<string, class IBObject> 			VarMap;
typedef pair<string, class IBObject>			VarPair;
typedef map<string, vector<class IBObject>>		PotentialVarMap;
typedef pair<string, vector<class IBObject>>	PotentialVarPair;


enum IBF_Result
{
	IBF_OK,
	IBF_FAIL,
	IBF_UNKNOW,
	IBF_IMPOSSIBLE,
	IBF_RESOLVED,
	IBF_DELETE,

	IBF_Result_MAX
};

extern const char* IBF_ResultString[IBF_Result_MAX];


enum IBA_State
{
	IBA_Created,
	IBA_Unresolved,
	IBA_Resolved,
	IBA_Impossible,
	IBA_Active,
	IBA_Finish,
	IBA_Destroy,
	IBA_Destroyed,

	IBA_State_MAX
};

extern const char* IBA_StateString[IBA_State_MAX];


#endif