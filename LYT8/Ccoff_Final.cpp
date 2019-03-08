//==============================================================================
// Ccoff_Final.cpp (User function)
// 
//    void Ccoff_Final_user_init(test_function& func)
//    void Ccoff_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Ccoff_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Ccoff_Final_user_init(test_function& func)
{
	Ccoff_Final_params *ours;
    ours = (Ccoff_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Ccoff_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    Ccoff_Final_params *ours;
    ours = (Ccoff_Final_params *)func.params;
	
	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_Ccoff_Fin, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_Ccoff_Final == 0 )	return;

	// Test Time Begin //
	// if (g_TstTime_Enble_P)
	// 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//int CCoff_final =0;
	int CCoff_TrCode_S =0;
	int CCoff_BitCode_S =0;
	float CCoff_Exp_Chg_S =0;
	int EEtr_CCoff1_S =0;
	int EEtr_CCoff2_S =0;
	int EEtr_CCoff3_S =0;
	int CCoff_Sim_S =0;
	float CCoff_Act_Chg =0;
	float CCoff_final_TT =0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	int reg_CC_Data = 0;
	float SRpinVolt = 0;

	if (g_Char_Enable_P) // Characterization only //
	{
		// Datalog //
		PiDatalog(func, A_CCoff_final, g_CCoff_final, 25, POWER_MILLI); // Measured in Iout.cpp function //
	}

	//PiDatalog(func, A_CCoff_Act_Chg, CCoff_Act_Chg, 25, POWER_UNIT);
	
	// Test Time End //
	//if (g_TstTime_Enble_P)
	//{
	//	g_endtime = g_mytimer.GetElapsedTime();
	//	CCoff_final_TT = (g_endtime - g_begintime)*1e-6;
	//	PiDatalog(func, A_CCoff_final_TT, CCoff_final_TT, 25, POWER_MILLI);
	//}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;

	}
*/
}
