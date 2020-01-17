#include "Types.h"
#include "Action/IBAction.h"


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
	"Start",
	"Execute",
	"Finish",
	"Abort",
	"Destroy",
	"Destroyed",
};


