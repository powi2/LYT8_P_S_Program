//==============================================================================
// HBP_Pre_S.cpp (User function)
// 
//    void HBP_Pre_S_user_init(test_function& func)
//    void HBP_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "HBP_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void HBP_Pre_S_user_init(test_function& func)
{
	HBP_Pre_S_params *ours;
    ours = (HBP_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void HBP_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    HBP_Pre_S_params *ours;
    ours = (HBP_Pre_S_params *)func.params;

	//Variables
	
	// Increment function number //
	gFuncNum++;	

	Pulse pulse;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_HBP_Pre_S, gFuncNum, 15, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_Continuity == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

		PiDatalog(func, A_HBP_Pre_S, g_HBP_Pre_S, 20, POWER_UNIT);


}
