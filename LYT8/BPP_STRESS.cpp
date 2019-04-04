//==============================================================================
// BPP_STRESS.cpp (User function)
// 
//    void BPP_STRESS_user_init(test_function& func)
//    void BPP_STRESS(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BPP_STRESS.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BPP_STRESS_user_init(test_function& func)
{
	BPP_STRESS_params *ours;
    ours = (BPP_STRESS_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BPP_STRESS(test_function& func)
{
    // The two lines below must be the first two in the function.
    BPP_STRESS_params *ours;
    ours = (BPP_STRESS_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_BPP_Stress, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	if (g_Fn_BPP_STRESS == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//float BPP_Stress_Volt = -9999;
	//float BPP_IS1_Pre = -9999;
	//float BPP_IS2_Pre = -9999;
	//float iLeak_V_Pre = -9999;
	float BPP_IS1_Post = -9999;
	float BPP_IS1_Delta = -9999;
	float BPP_IS2_Post = -9999;
	float BPP_IS2_Delta = -9999;
	//float iLeak_V_Post = -9999;
	//float iLeak_V_Delta = -9999;
	
	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	float vset = 0;	
	Pulse pulse;



	// Datalog //
	PiDatalog(func, A_BPP_Stress_Volt, g_BPP_Stress_Volt, 27, POWER_UNIT);
	//PiDatalog(func, A_BPP_IS1_Pre, g_BPP_IS1_Pre, 27, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_BPP_IS1_Pre, g_BPP_IS1_Pre, 5, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_BPP_IS2_Pre, g_BPP_IS2_Pre, 27, POWER_MILLI);
	PiDatalog(func, A_iLeak_V_Pre, g_iLeak_V_Pre, 27, POWER_MICRO);
	//PiDatalog(func, A_BPP_IS1_Post, BPP_IS1_Post, 27, POWER_MICRO);
	//PiDatalog(func, A_BPP_IS1_Delta, BPP_IS1_Delta, 27, POWER_MICRO);
	//PiDatalog(func, A_BPP_IS2_Post, BPP_IS2_Post, 27, POWER_MILLI);
	//PiDatalog(func, A_BPP_IS2_Delta, BPP_IS2_Delta, 27, POWER_MILLI);
	PiDatalog(func, A_iLeak_V_Post, g_iLeak_V_Post, 27, POWER_MICRO);
	PiDatalog(func, A_iLeak_V_Delta, g_iLeak_V_Delta, 27, POWER_MICRO);

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
