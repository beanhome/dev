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
	"Created",
	"Unresolved",
	"Resolved",
	"Impossible",
	"Active",
	"Finish",
	"Destroy",
	"Destroyed",
};


