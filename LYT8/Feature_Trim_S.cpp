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

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_S, gFuncNum, 26, POWER_UNIT);
	
	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Trim_Enable_S == 0)
	//	return;

	//if (g_Fn_Feature_Trim_S == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //

	int	Eetr8_tsstart0_S     = 0;
	int	Eetr9_tsstart1_S     = 0;
	int Eetr10_tfbOption0_S  = 0;
	int Eetr11_tfbOption1_S  = 0;
	int Eetr15_DOPL_S        = 0;
	int Eetr16_TvrOption0_S  = 0;
	int Eetr17_TvrOption1_S  = 0;
	int Eetr18_TenCP_S       = 0;
	int Eetr19_ZffOption0_S  = 0;
	int Eetr20_ZffOption1_S  = 0;
	int Eetr21_DsblJitDim_S  = 0;
	int Eetr22_JitterOff_S   = 0;
	int Eetr29_ZTMBStr0_S    = 0;
	int Eetr30_ZTMBStr1_S    = 0;
	int Eetr31_DsblFolBack_S = 0;
	int Eetr47_DimTh_S       = 0;
	int Eetr61_tHrtBtOpt_S   = 0;
	int Eetr62_CPNI2C_S      = 0;
	int Eetr63_50KStart_S    = 0;
	int Eetr74_FldBck_CCopt_S= 0;
	int Eetr75_FldBck_Sel_S  = 0;
	int Ftr_Trim_S_TT        = 0;

	EEpr_E0 = 0x0000;
	EEpr_E2 = 0x0000;
	EEpr_E4 = 0x0000;
	EEpr_E6 = 0x0000;
	EEpr_E8 = 0x0000;

	EEpr_Array[0] = EEpr_E0;
	EEpr_Array[1] = EEpr_E2;
	EEpr_Array[2] = EEpr_E4;
	EEpr_Array[3] = EEpr_E6;
	EEpr_Array[4] = EEpr_E8;


////extern int g_tsstart_B8_9_S;			//Softstart time    
////extern int g_tfbOption_B10_11_S;		//Boost Frequency Options
////extern int g_DOPL_B15_S;				//DOPL Option Bit
////extern int g_TvrOption_B16_17_S;		//VR Option Selection.
////extern int g_TenCP_B18_S;				//Enable CP in Non I2C Mode
////extern int g_ZffOption_B19_20_S;		//Feedforward Option.
////extern int g_DsblJitDim_B21_S;			//Disable Jitter in Dimming.
////extern int g_JitterOff_B22_S;			//Turn off Jitter.
////extern int g_ZTMBStr_B29_30_S;			//Enable 1 segment Boost Driver.
////extern int g_DsblFlBck_B31_S;			//Disable Foldback.
////extern int g_Dimth_B47_S;				//Select Deep Dim Threshold
////extern int g_tHrtBtOpt_B61_S;			//Heat beat time option.
////extern int g_CPNonI2C_B62_S;			//Disable CP
////extern int g_ZEE_50KStr_B63_S;			//Set softstart start up freq
////extern int g_FlBck_Ccopt_B74_S;			//To change rate of change in CC reference.
////extern int g_FlBck_Sel_B75_S;			//Trim to disable thermal foldback and line induced foldback.


	if(ours->Manual_Prog)
	{
		//-----------------------------------------------------------------------
		//ZEE_tsstart
		if(ours->tsstart_B_8_9_S == 1)
		{
			Eetr8_tsstart0_S     = 1;
			g_tsstart_B8_9_S     = 1;
			Set_EEprBit(EEpr_Array[0],8, 1); 
			Set_EEprBit(EEpr_Array[0],9, 1); 
		}
		if(ours->tsstart_B_8_9_S == 2)
		{
			Eetr8_tsstart0_S     = 0;
			Eetr9_tsstart1_S     = 1;
			g_tsstart_B8_9_S     = 2;
			Set_EEprBit(EEpr_Array[0],8, 0); 
			Set_EEprBit(EEpr_Array[0],9, 1);
		}
		if(ours->tsstart_B_8_9_S == 3)
		{
			Eetr8_tsstart0_S     = 1;
			Eetr9_tsstart1_S     = 1;
			g_tsstart_B8_9_S     = 3;
			Set_EEprBit(EEpr_Array[0],8, 1); 
			Set_EEprBit(EEpr_Array[0],9, 1);
		}
		//----------------------------------------------------------------------------------

	
		//tfbOption
		if(ours->tfbOption_B_10_11_S== 1)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 0;
			g_tfbOption_B10_11_S = 1;
			Set_EEprBit(EEpr_Array[0],10, 1); 
			Set_EEprBit(EEpr_Array[0],11, 0); 
		}
		if(ours->tfbOption_B_10_11_S == 2)
		{
			Eetr10_tfbOption0_S  = 0;
			Eetr11_tfbOption1_S  = 1;
			g_tfbOption_B10_11_S = 2;
			Set_EEprBit(EEpr_Array[0],10, 0); 
			Set_EEprBit(EEpr_Array[0],11, 1); 
		}
		if(ours->tfbOption_B_10_11_S == 3)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 1;
			g_tfbOption_B10_11_S = 3;
			Set_EEprBit(EEpr_Array[0],10, 1); 
			Set_EEprBit(EEpr_Array[0],11, 1); 
		}
		//----------------------------------------------------------------------------------
		//DOPL
		if(ours->DOPL_B_15_S == 1)
		{
			Eetr15_DOPL_S = 1;
			g_DOPL_B15_S  = 1;
			Set_EEprBit(EEpr_Array[0],15, 1);
		}
		//----------------------------------------------------------------------------------
		//TvrOption
		if(ours->TvrOption_B_16_17_S == 1) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 0;
			g_TvrOption_B16_17_S = 1;
			Set_EEprBit(EEpr_Array[1],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Array[1],17-16, 0); //TvrOption
		}
		if(ours->TvrOption_B_16_17_S == 2) 
		{
			Eetr16_TvrOption0_S  = 0;
			Eetr17_TvrOption1_S  = 1;
			g_TvrOption_B16_17_S = 2;
			Set_EEprBit(EEpr_Array[1],16-16, 0); //TvrOption
			Set_EEprBit(EEpr_Array[1],17-16, 1); //TvrOption
		}
		if(ours->TvrOption_B_16_17_S == 3) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 1;
			g_TvrOption_B16_17_S = 3;
			Set_EEprBit(EEpr_Array[1],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Array[1],17-16, 1); //TvrOption
		}
		//----------------------------------------------------------------------

		if(ours->tenCP_B_18_S == 1) 
		{
			Eetr18_TenCP_S = 1;
			g_TenCP_B18_S  = 1;
			Set_EEprBit(EEpr_Array[1],18-16, 1); //Dim Set Freq
		}
		//------------------------------------------------------------------------------

		
		if(ours->zffOption_B_19_20_S == 0) 
		{
			Eetr19_ZffOption0_S  = 0;
			Eetr20_ZffOption1_S  = 0;
			g_ZffOption_B19_20_S = 0;
			Set_EEprBit(EEpr_Array[1],19-16, 0); //FeedForward Option.
			Set_EEprBit(EEpr_Array[1],20-16, 0); //FeedForward Option.
		}
		if(ours->zffOption_B_19_20_S == 1) 
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 0;
			g_ZffOption_B19_20_S = 1;
			Set_EEprBit(EEpr_Array[1],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Array[1],20-16, 0); //FeedForward Option.
		}
		else if(ours->zffOption_B_19_20_S==2)
		{
				Eetr19_ZffOption0_S  = 0;
				Eetr20_ZffOption1_S  = 1;
				g_ZffOption_B19_20_S = 2;
				Set_EEprBit(EEpr_Array[1],19-16, 0); //FeedForward Option.
				Set_EEprBit(EEpr_Array[1],20-16, 1); //FeedForward Option.
		}
		else if(ours->zffOption_B_19_20_S == 3)
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 1;
			g_ZffOption_B19_20_S = 3;
			Set_EEprBit(EEpr_Array[1],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Array[1],20-16, 1); //FeedForward Option.
		}
		//--------------------------------------------------------
		if(ours->DsblJitDim_B_21_S == 1) 
		{
			Eetr21_DsblJitDim_S = 1;
			g_DsblJitDim_B21_S  = 1;
			Set_EEprBit(EEpr_Array[1],21-16, 1); //Dsbl_JitterDim
		}
		//------------------------------------------------------------------------------
		//Zjitter_Off
		if(ours->JitterOff_B_22_S == 1)
		{
			Eetr22_JitterOff_S = 1;
			g_JitterOff_B22_S  = 1;
			Set_EEprBit(EEpr_Array[1],22-16, 1);

		}
		//-------------------------------------------------------------------------------
		//ZTMBoostStre0
		if(ours->ZTMBStr_B_29_30_S == 1)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 0;
			g_ZTMBStr_B29_30_S   = 1;
			Set_EEprBit(EEpr_Array[1],29-16, 1);
			Set_EEprBit(EEpr_Array[1],30-16, 0);
		}
		//ZTMBoostStre1
		if(ours->ZTMBStr_B_29_30_S == 2)
		{
			Eetr29_ZTMBStr0_S    = 0;
			Eetr30_ZTMBStr1_S    = 1;
			g_ZTMBStr_B29_30_S   = 2;
			Set_EEprBit(EEpr_Array[1],29-16, 0);
			Set_EEprBit(EEpr_Array[1],30-16, 1);
		}
		//ZTMBoostStre0&1
		if(ours->ZTMBStr_B_29_30_S == 2)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 1;
			g_ZTMBStr_B29_30_S   = 3;
			Set_EEprBit(EEpr_Array[1],29-16, 1);
			Set_EEprBit(EEpr_Array[1],30-16, 1);
		}
		//------------------------------------------------------------------------------
		//ZEE_Dsbl_Foldback
		if(ours->DsblFlBck_B_31_S == 1)
		{
			Eetr31_DsblFolBack_S = 1;
			g_DsblFlBck_B31_S    = 1;
			Set_EEprBit(EEpr_Array[1],31-16, 1);
		}
		//-------------------------------------------------------------------------------
		//Dim_th
		if(ours->DimTh_B_47_S == 1)
		{
			Eetr47_DimTh_S = 1;
			g_Dimth_B47_S  = 1;
			Set_EEprBit(EEpr_Array[2],47-32, 1);
		}
		//---------------------------------------------------------------------------
		//Zee_tHrtBtOpt
		if(ours->tHrtBtOpt_B_61_S == 1)
		{
			Eetr61_tHrtBtOpt_S = 1;
			g_tHrtBtOpt_B61_S  = 1;
			Set_EEprBit(EEpr_Array[3],61-48, 1);

		}
		//------------------------------------------------------------------------------
		//Disable CP
		if(ours->CPNonI2C_B_62_S == 1) 
		{
			Eetr62_CPNI2C_S  = 1;
			g_CPNonI2C_B62_S = 1;
			Set_EEprBit(EEpr_Array[3], 62-48, 1); //Enable CP in Non-I2C
		}
		//-------------------------------------------------------------------------------
		//Set softstart Freq
		if(ours->Zee_50KStr_B_63_S == 1) 
		{
			Eetr63_50KStart_S  = 1;
			g_ZEE_50KStr_B63_S = 1;
			Set_EEprBit(EEpr_Array[3], 63-48, 1); //Set Softstart Start up freq
		}
		//--------------------------------------------------------------------------------
		//Zee_FldBck_CCopt
		if(ours->FlBck_Ccopt_B_74_S == 1)
		{
			Eetr74_FldBck_CCopt_S = 1;
			g_FlBck_Ccopt_B74_S   = 1;
			Set_EEprBit(EEpr_Array[4], 74-64, 1); 

		}
		//Zee_FldBck_Sel
		if(ours->FlBck_Sel_B_75_S == 1)
		{
			Eetr75_FldBck_Sel_S = 1;
			g_FlBck_Sel_B75_S   = 1;
			Set_EEprBit(EEpr_Array[4], 75-64, 1); 

		}
	}
	
	
	
	

	// Datalog //
	PiDatalog(func, A_Eetr8_tsstart0_S,		Eetr8_tsstart0_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr9_tsstart1_S,		Eetr9_tsstart1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr10_tfbOption0_S,  Eetr10_tfbOption0_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr11_tfbOption1_S,	Eetr11_tfbOption1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr15_DOPL_S,		Eetr15_DOPL_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr16_TvrOption0_S,	Eetr16_TvrOption0_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr17_TvrOption1_S,	Eetr17_TvrOption1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr18_TenCP_S,		Eetr18_TenCP_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr19_ZffOption0_S,	Eetr19_ZffOption0_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr20_ZffOption1_S,	Eetr20_ZffOption1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr21_DsblJitDim_S,  Eetr21_DsblJitDim_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr22_JitterOff_S,	Eetr22_JitterOff_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr29_ZTMBStr0_S,	Eetr29_ZTMBStr0_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr30_ZTMBStr1_S,	Eetr30_ZTMBStr1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr31_DsblFolBack_S,	Eetr31_DsblFolBack_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr47_DimTh_S,		Eetr47_DimTh_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr61_tHrtBtOpt_S,	Eetr61_tHrtBtOpt_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr62_CPNI2C_S,		Eetr62_CPNI2C_S, 26, POWER_UNIT);	
	PiDatalog(func, A_Eetr63_50KStart_S,	Eetr63_50KStart_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr74_FldBck_CCopt_S,Eetr74_FldBck_CCopt_S, 26, POWER_UNIT);
	PiDatalog(func, A_Eetr75_FldBck_Sel_S,	Eetr75_FldBck_Sel_S, 26, POWER_UNIT);









/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_S, gFuncNum, 26, POWER_UNIT);
	
	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	if (g_Burn_Enable_P == 0)
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
