#include "Types.h"
#include "Action/IBAction.h"

bool EvalSort::operator()(const IBAction* a1, const IBAction* a2) const
{
	float e1 = a1->GetCost();
	float e2 = a2->GetCost();

	return (e1 == e2 ? a1->GetState() < a2->GetState() : e1 < e2);
}

const char* IBF_ResultString[IBF_Result_MAX] =
{
	"Ok",
	"Fail",
	"Unknow",
	"Impossible",
	"Resolved",
	"Delete",
};


const char*	IBA_StateString[IBA_State_MAX] =
{
	"Init",
	"Unresolved",
	"Resolved",
	"Impossible",
	"Ready",
	"Start",
	"Execute",
	"Finish",
	"Abort",
	"Destroy",
	"Destroyed",
};


