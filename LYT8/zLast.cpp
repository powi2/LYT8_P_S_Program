//==============================================================================
// zLast.cpp (User function)
// 
//    void zLast_user_init(test_function& func)
//    void zLast(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "zLast.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void zLast_user_init(test_function& func)
{
	zLast_params *ours;
    ours = (zLast_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void zLast(test_function& func)
{
    // The two lines below must be the first two in the function.
    zLast_params *ours;
    ours = (zLast_params *)func.params;

	// Increment function number //
	gFuncNum++;
////
////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_Last, gFuncNum, 31, POWER_UNIT);
////
////	// Skip Test if AbortTest set 
//////	if (AbortTest)
//////		return;
////
////	if (g_Fn_zLast == 0 )  return;
////
////	// Test Time Begin //
////	// if (g_TstTime_Enble_P)
////	// 	g_begintime = g_mytimer.GetElapsedTime();
//// 
////	// Test Names //
////	float Last_TT = 0;
////
////	// QC sample //
//////	if ((g_OPCODE == 4200||g_OPCODE == 4300) && !Golden_Unit_Prg)
//////			PiQcSampleSelect( );
////
////	// Check for golden unit program //
////	if (!strnicmp( g_PrgName, "INN3375GoldenUnit", 17 ) || 
////		!strnicmp( g_PrgName, "INN3376GoldenUnit", 17 ) || 
////		!strnicmp( g_PrgName, "INN3377GoldenUnit", 17 ) || 
////		!strnicmp( g_PrgName, "INN3368GoldenUnit", 17 ))
////	{
////		// No QC sample for golden units. //
////	}
////	else if (g_OPCODE==4200 || g_OPCODE==4250 || g_OPCODE==4300)
////	{
////		PiQcSampleSelect( ); // Perform QC sampling //
////	}
////
////	// Datalog //
////	//PiDatalog(func, A_Num_Functions, gFuncNum, 31, POWER_UNIT);
////	PiDatalog(func, A_Error_Flag, g_Error_Flag, 31, POWER_UNIT);
////	PiDatalog(func, A_TestTime, PiGetTestTime(), 31, POWER_UNIT);
////	PiDatalog(func, A_TestTime_PP, PiGetPart2PartTime(), 31, POWER_UNIT);
////	if(gLoadBoardRev > 24)
////	{
////		PiDatalog(func, A_ENG1, g_R1_ohms, 31, POWER_UNIT);
////	}
////	if(gLoadBoardRev > 24 && gContactorRev > 20)
////	{
////		PiDatalog(func, A_ENG2, g_Site, 31, POWER_UNIT);
////	}
////	PiDatalog(func, A_ENG3, g_InvSyn_Fall, 31, POWER_UNIT);
////	PiDatalog(func, A_ENG4, g_DSM_Library_Version/10000, 31, POWER_UNIT);
////	PiDatalog(func, A_ENG5, g_DSM_Firmware_Version/10000, 31, POWER_UNIT);
////	PiDatalog(func, A_ENG6, g_GNDRes_Se, 31, POWER_UNIT);
////	PiDatalog(func, A_ENG7, g_GNDRes_Pri, 31, POWER_UNIT);
////	PiDatalog(func, A_ENG8, g_FWmeasV, 31, POWER_UNIT); 
////	//PiDatalog(func, A_ENG9, g_Vshunt_2mA_P_Final, 31, POWER_UNIT);
////	//PiDatalog(func, A_ENG10, g_ENG10, 31, POWER_UNIT);
////	
////
////
////	// Test Time End //
////	//if (g_TstTime_Enble_P)
////	//{
////	//	g_endtime = g_mytimer.GetElapsedTime();
////	//	Last_TT = (g_endtime - g_begintime)*1e-6;
////	//	PiDatalog(func, A_Last_TT, Last_TT, 25, POWER_MILLI);
////	//}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
