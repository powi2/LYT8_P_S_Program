//==============================================================================
// Feature_Trim_S.cpp (User function)
// 
//    void Feature_Trim_S_user_init(test_function& func)
//    void Feature_Trim_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Feature_Trim_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Feature_Trim_S_user_init(test_function& func)
{
	Feature_Trim_S_params *ours;
    ours = (Feature_Trim_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Feature_Trim_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Feature_Trim_S_params *ours;
    ours = (Feature_Trim_S_params *)func.params;

	// Increment function number //
	gFuncNum++;
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_S, gFuncNum, 26, POWER_UNIT);
	
	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	if (g_Fn_Feature_Trim_S == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	int EEtr_PK_SpdLd_S = 0;
	int EEtr_VesrAdp_S = 0;
	//int EEtr_AR1_S = 0;
	//int EEtr_AR2_S = 0;
	//int EEtr_CBEN_S = 0;
	int EEtr_DsoftEn_S = 0;
	int EEtr_DOPL_S = 0;
	//int EEtr_OVLO_S = 0;
	//int EEtr_VR1_S = 0;
	//int EEtr_VR2_S = 0;
	//int EEtr_XFWPK_S = 0;
	//int EEtr_SCEN_S = 0;
	//int EEtr_CR_S = 0;
	int EEtr_CCAR_S = 0;
	int EEtr_DoplEnCp_S = 0;
	int EEtr_ESRsel_S = 0;
	int EEtr_DdampEn_S = 0;
	float Fetur_Trim_S_TT = 0;

	// Declare Variables //
	int i = 0;

	// Load the g_ShadowRegister[] array with the InnoVI-TrimOptions.csv file data. //
	g_ShadowRegister[0] = gTrim_SdwReg0_Trimops;
	g_ShadowRegister[1] = gTrim_SdwReg1_Trimops;
	g_ShadowRegister[2] = gTrim_SdwReg2_Trimops;
	g_ShadowRegister[3] = gTrim_SdwReg3_Trimops;
	g_ShadowRegister[4] = gTrim_SdwReg4_Trimops;
	g_ShadowRegister[5] = gTrim_SdwReg5_Trimops;
	g_ShadowRegister[6] = gTrim_SdwReg6_Trimops;
	g_ShadowRegister[7] = gTrim_SdwReg7_Trimops;
	g_ShadowRegister[8] = gTrim_SdwReg8_Trimops;
	g_ShadowRegister[9] = gTrim_SdwReg9_Trimops;
	g_ShadowRegister[10] = gTrim_SdwReg10_Trimops;
	g_ShadowRegister[11] = gTrim_SdwReg11_Trimops;
	g_ShadowRegister[12] = gTrim_SdwReg12_Trimops;
	g_ShadowRegister[13] = gTrim_SdwReg13_Trimops;
	g_ShadowRegister[14] = gTrim_SdwReg14_Trimops;
	g_ShadowRegister[15] = gTrim_SdwReg15_Trimops;
	g_ShadowRegister[16] = gTrim_SdwReg16_Trimops;
	g_ShadowRegister[17] = gTrim_SdwReg17_Trimops;
	g_ShadowRegister[18] = gTrim_SdwReg18_Trimops;
	g_ShadowRegister[19] = gTrim_SdwReg19_Trimops;
	g_ShadowRegister[20] = gTrim_SdwReg20_Trimops;
	g_ShadowRegister[21] = gTrim_SdwReg21_Trimops;
	g_ShadowRegister[22] = gTrim_SdwReg22_Trimops;
	g_ShadowRegister[23] = gTrim_SdwReg23_Trimops;
	g_ShadowRegister[24] = gTrim_SdwReg24_Trimops;
	g_ShadowRegister[25] = gTrim_SdwReg25_Trimops;
	g_ShadowRegister[26] = gTrim_SdwReg26_Trimops;
	g_ShadowRegister[27] = gTrim_SdwReg27_Trimops;
	g_ShadowRegister[28] = gTrim_SdwReg28_Trimops;
	g_ShadowRegister[29] = gTrim_SdwReg29_Trimops;
	g_ShadowRegister[30] = gTrim_SdwReg30_Trimops;
	g_ShadowRegister[31] = gTrim_SdwReg31_Trimops;
	g_ShadowRegister[32] = gTrim_SdwReg32_Trimops;
	g_ShadowRegister[33] = gTrim_SdwReg33_Trimops;
	g_ShadowRegister[34] = gTrim_SdwReg34_Trimops;
	g_ShadowRegister[35] = gTrim_SdwReg35_Trimops;
	g_ShadowRegister[36] = gTrim_SdwReg36_Trimops;
	g_ShadowRegister[37] = gTrim_SdwReg37_Trimops;
	g_ShadowRegister[38] = gTrim_SdwReg38_Trimops;
	g_ShadowRegister[39] = gTrim_SdwReg39_Trimops;
	g_ShadowRegister[40] = gTrim_SdwReg40_Trimops;
	g_ShadowRegister[41] = gTrim_SdwReg41_Trimops;
	g_ShadowRegister[42] = gTrim_SdwReg42_Trimops;
	g_ShadowRegister[43] = gTrim_SdwReg43_Trimops;
	g_ShadowRegister[44] = gTrim_SdwReg44_Trimops;
	g_ShadowRegister[45] = gTrim_SdwReg45_Trimops;
	g_ShadowRegister[46] = gTrim_SdwReg46_Trimops;
	g_ShadowRegister[47] = gTrim_SdwReg47_Trimops;
	g_ShadowRegister[48] = gTrim_SdwReg48_Trimops;
	g_ShadowRegister[49] = gTrim_SdwReg49_Trimops;
	g_ShadowRegister[50] = gTrim_SdwReg50_Trimops;
	g_ShadowRegister[51] = gTrim_SdwReg51_Trimops;
	g_ShadowRegister[52] = gTrim_SdwReg52_Trimops;
	g_ShadowRegister[53] = gTrim_SdwReg53_Trimops;
	g_ShadowRegister[54] = gTrim_SdwReg54_Trimops;
	g_ShadowRegister[55] = gTrim_SdwReg55_Trimops;
	g_ShadowRegister[56] = gTrim_SdwReg56_Trimops;
	g_ShadowRegister[57] = gTrim_SdwReg57_Trimops;
	g_ShadowRegister[58] = gTrim_SdwReg58_Trimops;
	g_ShadowRegister[59] = gTrim_SdwReg59_Trimops;
	g_ShadowRegister[60] = gTrim_SdwReg60_Trimops;
	g_ShadowRegister[61] = gTrim_SdwReg61_Trimops;
	g_ShadowRegister[62] = gTrim_SdwReg62_Trimops;
	g_ShadowRegister[63] = gTrim_SdwReg63_Trimops;
	g_ShadowRegister[64] = gTrim_SdwReg64_Trimops;
	g_ShadowRegister[65] = gTrim_SdwReg65_Trimops;
	g_ShadowRegister[66] = gTrim_SdwReg66_Trimops;
	g_ShadowRegister[67] = gTrim_SdwReg67_Trimops;
	g_ShadowRegister[68] = gTrim_SdwReg68_Trimops;
	g_ShadowRegister[69] = gTrim_SdwReg69_Trimops;
	g_ShadowRegister[70] = gTrim_SdwReg70_Trimops;
	g_ShadowRegister[71] = gTrim_SdwReg71_Trimops;
	g_ShadowRegister[72] = gTrim_SdwReg72_Trimops;
	g_ShadowRegister[73] = gTrim_SdwReg73_Trimops;
	g_ShadowRegister[74] = gTrim_SdwReg74_Trimops;
	g_ShadowRegister[75] = gTrim_SdwReg75_Trimops;
	g_ShadowRegister[76] = gTrim_SdwReg76_Trimops;
	g_ShadowRegister[77] = gTrim_SdwReg77_Trimops;
	g_ShadowRegister[78] = gTrim_SdwReg78_Trimops;
	g_ShadowRegister[79] = gTrim_SdwReg79_Trimops;
	g_ShadowRegister[80] = gTrim_SdwReg80_Trimops;
	g_ShadowRegister[81] = gTrim_SdwReg81_Trimops;
	g_ShadowRegister[82] = gTrim_SdwReg82_Trimops;
	g_ShadowRegister[83] = gTrim_SdwReg83_Trimops;
	g_ShadowRegister[84] = gTrim_SdwReg84_Trimops;
	g_ShadowRegister[85] = gTrim_SdwReg85_Trimops;
	g_ShadowRegister[86] = gTrim_SdwReg86_Trimops;
	g_ShadowRegister[87] = gTrim_SdwReg87_Trimops;
	g_ShadowRegister[88] = gTrim_SdwReg88_Trimops;
	g_ShadowRegister[89] = gTrim_SdwReg89_Trimops;
	g_ShadowRegister[90] = gTrim_SdwReg90_Trimops;
	g_ShadowRegister[91] = gTrim_SdwReg91_Trimops;
	g_ShadowRegister[92] = gTrim_SdwReg92_Trimops;
	g_ShadowRegister[93] = gTrim_SdwReg93_Trimops;
	g_ShadowRegister[94] = gTrim_SdwReg94_Trimops;
	g_ShadowRegister[95] = gTrim_SdwReg95_Trimops;
	g_ShadowRegister[96] = gTrim_SdwReg96_Trimops;
	g_ShadowRegister[97] = gTrim_SdwReg97_Trimops;
	g_ShadowRegister[98] = gTrim_SdwReg98_Trimops;
	g_ShadowRegister[99] = gTrim_SdwReg99_Trimops;
	g_ShadowRegister[100] = gTrim_SdwReg100_Trimops;
	g_ShadowRegister[101] = gTrim_SdwReg101_Trimops;
	g_ShadowRegister[102] = gTrim_SdwReg102_Trimops;
	g_ShadowRegister[103] = gTrim_SdwReg103_Trimops;
	g_ShadowRegister[104] = gTrim_SdwReg104_Trimops;
	g_ShadowRegister[105] = gTrim_SdwReg105_Trimops;
	g_ShadowRegister[106] = gTrim_SdwReg106_Trimops;
	g_ShadowRegister[107] = gTrim_SdwReg107_Trimops;
	g_ShadowRegister[108] = gTrim_SdwReg108_Trimops;
	g_ShadowRegister[109] = gTrim_SdwReg109_Trimops;
	g_ShadowRegister[110] = gTrim_SdwReg110_Trimops;
	g_ShadowRegister[111] = gTrim_SdwReg111_Trimops;

	// Load test variables //
	EEtr_PK_SpdLd_S = g_ShadowRegister[45]; // PKssLd. (1 bit) //
	EEtr_VesrAdp_S = g_ShadowRegister[27]; // VesrAdp. //
	//EEtr_AR1_S = 0;
	//EEtr_AR2_S = 0;
	//EEtr_CBEN_S = 0;
	EEtr_DsoftEn_S = g_ShadowRegister[23]; // DsoftEn. //
	EEtr_DOPL_S = g_ShadowRegister[22]; // DOPL. //
	//EEtr_OVLO_S = 0;
	//EEtr_VR1_S = 0;
	//EEtr_VR2_S = 0;
	//EEtr_XFWPK_S = 0;
	//EEtr_SCEN_S = 0;
	//EEtr_CR_S = 0;

	EEtr_DoplEnCp_S = g_ShadowRegister[15]; // trim_dopl_en_cp //
	
	EEtr_ESRsel_S = g_ShadowRegister[29]; // ESRsel. //
	EEtr_DdampEn_S = g_ShadowRegister[28]; // DdampEn. //

	// Datalog //
	PiDatalog(func, A_IZtr_PK1_S, EEtr_PK_SpdLd_S, 26, POWER_UNIT);
	PiDatalog(func, A_IZtr_DVesrSlpAdj, EEtr_VesrAdp_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_AR1_S, EEtr_AR1_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_AR2_S, EEtr_AR2_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_CBEN_S, EEtr_CBEN_S, 26, POWER_UNIT);
	PiDatalog(func, A_IZtr_DsoftEn_S, EEtr_DsoftEn_S, 26, POWER_UNIT);
	PiDatalog(func, A_IZtr_DOPL_S, EEtr_DOPL_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_OVLO_S, EEtr_OVLO_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_VR1_S, EEtr_VR1_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_VR2_S, EEtr_VR2_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_XFWPK_S, EEtr_XFWPK_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_SCEN_S, EEtr_SCEN_S, 26, POWER_UNIT);
	//PiDatalog(func, A_IZtr_CR_S, EEtr_CR_S, 26, POWER_UNIT);
	PiDatalog(func, A_EEtr_DoplEnCp_S, EEtr_DoplEnCp_S, 26, POWER_UNIT);
	PiDatalog(func, A_IZtr_ESRsel_S, EEtr_ESRsel_S, 26, POWER_UNIT);
	PiDatalog(func, A_IZtr_DdampEn_S, EEtr_DdampEn_S, 26, POWER_UNIT);
	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Fetur_Trim_S_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Fetur_Trim_S_TT, Fetur_Trim_S_TT, 26, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
