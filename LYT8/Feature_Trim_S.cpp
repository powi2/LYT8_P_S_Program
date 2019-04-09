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
#pragma warning (disable : 4305)

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
	//if (g_Burn_Enable_S == 0)
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

	EEpr_Bank_S[E0] = EEpr_E0;
	EEpr_Bank_S[E2] = EEpr_E2;
	EEpr_Bank_S[E4] = EEpr_E4;
	EEpr_Bank_S[E6] = EEpr_E6;
	EEpr_Bank_S[E8] = EEpr_E8;


////extern int g_Trim_tsstart_B8_9_S_Trimops;			//Softstart time    
////extern int g_Trim_tfbOption_B10_11_S_Trimops;		//Boost Frequency Options
////extern int g_Trim_DOPL_B15_S_Trimops;				//DOPL Option Bit
////extern int g_Trim_TvrOption_B16_17_S_Trimops;		//VR Option Selection.
////extern int g_Trim_TenCP_B18_S_Trimops;				//Enable CP in Non I2C Mode
////extern int g_Trim_ZffOption_B19_20_S_Trimops;		//Feedforward Option.
////extern int g_Trim_DsblJitDim_B21_S_Trimops;			//Disable Jitter in Dimming.
////extern int g_Trim_JitterOff_B22_S_Trimops;			//Turn off Jitter.
////extern int g_Trim_ZTMBStr_B29_30_S_Trimops;			//Enable 1 segment Boost Driver.
////extern int g_Trim_DsblFlBck_B31_S_Trimops;			//Disable Foldback.
////extern int g_Trim_Dimth_B47_S_Trimops;				//Select Deep Dim Threshold
////extern int g_Trim_tHrtBtOpt_B61_S_Trimops;			//Heat beat time option.
////extern int g_Trim_CPNonI2C_B62_S_Trimops;			//Disable CP
////extern int g_Trim_ZEE_50KStr_B63_S_Trimops;			//Set softstart start up freq
////extern int g_Trim_FlBck_Ccopt_B74_S_Trimops;			//To change rate of change in CC reference.
////extern int g_Trim_FlBck_Sel_B75_S_Trimops;			//Trim to disable thermal foldback and line induced foldback.


	if(ours->Manual_Prog)
	{
		//Manual set option bit.
		//-----------------------------------------------------------------------
		//ZEE_tsstart
		if(ours->tsstart_B_8_9_S == 0)
		{
			Eetr8_tsstart0_S     = 0;
			g_Trim_tsstart_B8_9_S_Trimops     = 0;
			Set_EEprBit(EEpr_Bank_S[E0],8, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 0); 
		}
		else if(ours->tsstart_B_8_9_S == 1)
		{
			Eetr8_tsstart0_S     = 1;
			g_Trim_tsstart_B8_9_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E0],8, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 0); 
		}
		else if(ours->tsstart_B_8_9_S == 2)
		{
			Eetr8_tsstart0_S     = 0;
			Eetr9_tsstart1_S     = 1;
			g_Trim_tsstart_B8_9_S_Trimops = 2;
			Set_EEprBit(EEpr_Bank_S[E0],8, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 1);
		}
		else if(ours->tsstart_B_8_9_S == 3)
		{
			Eetr8_tsstart0_S     = 1;
			Eetr9_tsstart1_S     = 1;
			g_Trim_tsstart_B8_9_S_Trimops     = 3;
			Set_EEprBit(EEpr_Bank_S[E0],8, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 1);
		}
		else
		{
			//Not doing anything.
		}
		//----------------------------------------------------------------------------------

	
		//tfbOption
		if(ours->tfbOption_B_10_11_S== 0)
		{
			Eetr10_tfbOption0_S  = 0;
			Eetr11_tfbOption1_S  = 0;
			g_Trim_tfbOption_B10_11_S_Trimops = 0;
			Set_EEprBit(EEpr_Bank_S[E0],10, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 0); 
		}
		else if(ours->tfbOption_B_10_11_S== 1)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 0;
			g_Trim_tfbOption_B10_11_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E0],10, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 0); 
		}
		else if(ours->tfbOption_B_10_11_S == 2)
		{
			Eetr10_tfbOption0_S  = 0;
			Eetr11_tfbOption1_S  = 1;
			g_Trim_tfbOption_B10_11_S_Trimops = 2;
			Set_EEprBit(EEpr_Bank_S[E0],10, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 1); 
		}
		else if(ours->tfbOption_B_10_11_S == 3)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 1;
			g_Trim_tfbOption_B10_11_S_Trimops = 3;
			Set_EEprBit(EEpr_Bank_S[E0],10, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 1); 
		}
		else
		{
			//Not doing anything.
		}
		//----------------------------------------------------------------------------------
		//DOPL
		if(ours->DOPL_B_15_S == 1)
		{
			Eetr15_DOPL_S = 1;
			g_Trim_DOPL_B15_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E0],15, 1);
		}
		//----------------------------------------------------------------------------------
		//TvrOption
		if(ours->TvrOption_B_16_17_S == 0) 
		{
			Eetr16_TvrOption0_S  = 0;
			Eetr17_TvrOption1_S  = 0;
			g_Trim_TvrOption_B16_17_S_Trimops = 0;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 0); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 0); //TvrOption
		}
		else if(ours->TvrOption_B_16_17_S == 1) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 0;
			g_Trim_TvrOption_B16_17_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 0); //TvrOption
		}
		else if(ours->TvrOption_B_16_17_S == 2) 
		{
			Eetr16_TvrOption0_S  = 0;
			Eetr17_TvrOption1_S  = 1;
			g_Trim_TvrOption_B16_17_S_Trimops = 2;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 0); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 1); //TvrOption
		}
		else if(ours->TvrOption_B_16_17_S == 3) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 1;
			g_Trim_TvrOption_B16_17_S_Trimops = 3;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 1); //TvrOption
		}
		else
		{
			//Not doing anything.
		}
		//----------------------------------------------------------------------

		if(ours->tenCP_B_18_S == 1) 
		{
			Eetr18_TenCP_S = 1;
			g_Trim_TenCP_B18_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],18-16, 1); //Dim Set Freq
		}
		//------------------------------------------------------------------------------

		
		if(ours->zffOption_B_19_20_S == 0) 
		{
			Eetr19_ZffOption0_S  = 0;
			Eetr20_ZffOption1_S  = 0;
			g_Trim_ZffOption_B19_20_S_Trimops = 0;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 0); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 0); //FeedForward Option.
		}
		else if(ours->zffOption_B_19_20_S == 1) 
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 0;
			g_Trim_ZffOption_B19_20_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 0); //FeedForward Option.
		}
		else if(ours->zffOption_B_19_20_S==2)
		{
				Eetr19_ZffOption0_S  = 0;
				Eetr20_ZffOption1_S  = 1;
				g_Trim_ZffOption_B19_20_S_Trimops = 2;
				Set_EEprBit(EEpr_Bank_S[E2],19-16, 0); //FeedForward Option.
				Set_EEprBit(EEpr_Bank_S[E2],20-16, 1); //FeedForward Option.
		}
		else if(ours->zffOption_B_19_20_S == 3)
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 1;
			g_Trim_ZffOption_B19_20_S_Trimops = 3;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 1); //FeedForward Option.
		}
		else
		{
			//Not doing anything.
		}
		//--------------------------------------------------------
		if(ours->DsblJitDim_B_21_S == 1) 
		{
			Eetr21_DsblJitDim_S = 1;
			g_Trim_DsblJitDim_B21_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],21-16, 1); //Dsbl_JitterDim
		}
		//------------------------------------------------------------------------------
		//Zjitter_Off
		if(ours->JitterOff_B_22_S == 1)
		{
			Eetr22_JitterOff_S = 1;
			g_Trim_JitterOff_B22_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],22-16, 1);

		}
		//-------------------------------------------------------------------------------
		//ZTMBoostStre0
		if(ours->ZTMBStr_B_29_30_S == 0)
		{
			Eetr29_ZTMBStr0_S    = 0;
			Eetr30_ZTMBStr1_S    = 0;
			g_Trim_ZTMBStr_B29_30_S_Trimops   = 0;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 0);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 0);
		}
		else if(ours->ZTMBStr_B_29_30_S == 1)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 0;
			g_Trim_ZTMBStr_B29_30_S_Trimops   = 1;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 1);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 0);
		}
		else if(ours->ZTMBStr_B_29_30_S == 2)
		{
			Eetr29_ZTMBStr0_S    = 0;
			Eetr30_ZTMBStr1_S    = 1;
			g_Trim_ZTMBStr_B29_30_S_Trimops   = 2;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 0);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 1);
		}
		else if(ours->ZTMBStr_B_29_30_S == 3)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 1;
			g_Trim_ZTMBStr_B29_30_S_Trimops   = 3;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 1);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 1);
		}
		else
		{
			//Not doing anythng.
		}
		//------------------------------------------------------------------------------
		//ZEE_Dsbl_Foldback
		if(ours->DsblFlBck_B_31_S == 1)
		{
			Eetr31_DsblFolBack_S = 1;
			g_Trim_DsblFlBck_B31_S_Trimops    = 1;
			Set_EEprBit(EEpr_Bank_S[E2],31-16, 1);
		}
		//-------------------------------------------------------------------------------
		//Dim_th
		if(ours->DimTh_B_47_S == 1)
		{
			Eetr47_DimTh_S = 1;
			g_Trim_Dimth_B47_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E4],47-32, 1);
		}
		//---------------------------------------------------------------------------
		//Zee_tHrtBtOpt
		if(ours->tHrtBtOpt_B_61_S == 1)
		{
			Eetr61_tHrtBtOpt_S = 1;
			g_Trim_tHrtBtOpt_B61_S_Trimops  = 1;
			Set_EEprBit(EEpr_Bank_S[E6],61-48, 1);

		}
		//------------------------------------------------------------------------------
		//Disable CP
		if(ours->CPNonI2C_B_62_S == 1) 
		{
			Eetr62_CPNI2C_S  = 1;
			g_Trim_CPNonI2C_B62_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E6], 62-48, 1); //Enable CP in Non-I2C
		}
		//-------------------------------------------------------------------------------
		//Set softstart Freq
		if(ours->Zee_50KStr_B_63_S == 1) 
		{
			Eetr63_50KStart_S  = 1;
			g_Trim_ZEE_50KStr_B63_S_Trimops = 1;
			Set_EEprBit(EEpr_Bank_S[E6], 63-48, 1); //Set Softstart Start up freq
		}
		//--------------------------------------------------------------------------------
		//Zee_FldBck_CCopt
		if(ours->FlBck_Ccopt_B_74_S == 1)
		{
			Eetr74_FldBck_CCopt_S = 1;
			g_Trim_FlBck_Ccopt_B74_S_Trimops   = 1;
			Set_EEprBit(EEpr_Bank_S[E8], 74-64, 1); 

		}
		//Zee_FldBck_Sel
		if(ours->FlBck_Sel_B_75_S == 1)
		{
			Eetr75_FldBck_Sel_S = 1;
			g_Trim_FlBck_Sel_B75_S_Trimops   = 1;
			Set_EEprBit(EEpr_Bank_S[E8], 75-64, 1); 

		}
	}
	else
	{
		//Based on Trimops Table.
		//-----------------------------------------------------------------------
		//ZEE_tsstart
		if(g_Trim_tsstart_B8_9_S_Trimops == 0)
		{
			Eetr8_tsstart0_S     = 0;
			Set_EEprBit(EEpr_Bank_S[E0],8, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 0); 
		}
		else if(g_Trim_tsstart_B8_9_S_Trimops == 1)
		{
			Eetr8_tsstart0_S     = 1;
			Set_EEprBit(EEpr_Bank_S[E0],8, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 0); 
		}
		else if(g_Trim_tsstart_B8_9_S_Trimops  == 2)
		{
			Eetr8_tsstart0_S     = 0;
			Eetr9_tsstart1_S     = 1;
			Set_EEprBit(EEpr_Bank_S[E0],8, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 1);
		}
		else if(g_Trim_tsstart_B8_9_S_Trimops == 3)
		{
			Eetr8_tsstart0_S     = 1;
			Eetr9_tsstart1_S     = 1;
			Set_EEprBit(EEpr_Bank_S[E0],8, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],9, 1);
		}
		else
		{
			//Not doing anything.
		}
		//----------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------

	
		//tfbOption
		if(g_Trim_tfbOption_B10_11_S_Trimops == 0)
		{
			Eetr10_tfbOption0_S  = 0;
			Eetr11_tfbOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E0],10, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 0); 
		}
		else if(g_Trim_tfbOption_B10_11_S_Trimops == 1)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E0],10, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 0); 
		}
		else if(g_Trim_tfbOption_B10_11_S_Trimops == 2)
		{
			Eetr10_tfbOption0_S  = 0;
			Eetr11_tfbOption1_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E0],10, 0); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 1); 
		}
		else if(g_Trim_tfbOption_B10_11_S_Trimops == 3)
		{
			Eetr10_tfbOption0_S  = 1;
			Eetr11_tfbOption1_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E0],10, 1); 
			Set_EEprBit(EEpr_Bank_S[E0],11, 1); 
		}
		else
		{
			//Not doing anything.
		}
		//----------------------------------------------------------------------------------
		//DOPL
		if(g_Trim_DOPL_B15_S_Trimops == 1)
		{
			Eetr15_DOPL_S = 1;
			Set_EEprBit(EEpr_Bank_S[E0],15, 1);
		}
		//----------------------------------------------------------------------------------
		//TvrOption
		if(g_Trim_TvrOption_B16_17_S_Trimops == 0) 
		{
			Eetr16_TvrOption0_S  = 0;
			Eetr17_TvrOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 0); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 0); //TvrOption
		}
		else if(g_Trim_TvrOption_B16_17_S_Trimops == 1) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 0); //TvrOption
		}
		else if(g_Trim_TvrOption_B16_17_S_Trimops== 2) 
		{
			Eetr16_TvrOption0_S  = 0;
			Eetr17_TvrOption1_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 0); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 1); //TvrOption
		}
		else if(g_Trim_TvrOption_B16_17_S_Trimops == 3) 
		{
			Eetr16_TvrOption0_S  = 1;
			Eetr17_TvrOption1_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],16-16, 1); //TvrOption
			Set_EEprBit(EEpr_Bank_S[E2],17-16, 1); //TvrOption
		}
		else
		{
			//Not doing anything
		}
		//----------------------------------------------------------------------

		if(g_Trim_TenCP_B18_S_Trimops == 1) 
		{
			Eetr18_TenCP_S = 1;
			Set_EEprBit(EEpr_Bank_S[E2],18-16, 1); //Dim Set Freq
		}
		//------------------------------------------------------------------------------

		
		if(g_Trim_ZffOption_B19_20_S_Trimops == 0) 
		{
			Eetr19_ZffOption0_S  = 0;
			Eetr20_ZffOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 0); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 0); //FeedForward Option.
		}
		else if(g_Trim_ZffOption_B19_20_S_Trimops == 1) 
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 0;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 0); //FeedForward Option.
		}
		else if(g_Trim_ZffOption_B19_20_S_Trimops==2)
		{
				Eetr19_ZffOption0_S  = 0;
				Eetr20_ZffOption1_S  = 1;
				Set_EEprBit(EEpr_Bank_S[E2],19-16, 0); //FeedForward Option.
				Set_EEprBit(EEpr_Bank_S[E2],20-16, 1); //FeedForward Option.
		}
		else if(g_Trim_ZffOption_B19_20_S_Trimops == 3)
		{
			Eetr19_ZffOption0_S  = 1;
			Eetr20_ZffOption1_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E2],19-16, 1); //FeedForward Option.
			Set_EEprBit(EEpr_Bank_S[E2],20-16, 1); //FeedForward Option.
		}
		else
		{
			//Not doing anything.
		}
		//--------------------------------------------------------
		if(g_Trim_DsblJitDim_B21_S_Trimops == 1) 
		{
			Eetr21_DsblJitDim_S = 1;
			Set_EEprBit(EEpr_Bank_S[E2],21-16, 1); //Dsbl_JitterDim
		}
		//------------------------------------------------------------------------------
		//Zjitter_Off
		if(g_Trim_JitterOff_B22_S_Trimops == 1)
		{
			Eetr22_JitterOff_S = 1;
			Set_EEprBit(EEpr_Bank_S[E2],22-16, 1);

		}
		//-------------------------------------------------------------------------------
		//ZTMBoostStre0
		if(g_Trim_ZTMBStr_B29_30_S_Trimops == 0)
		{
			Eetr29_ZTMBStr0_S    = 0;
			Eetr30_ZTMBStr1_S    = 0;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 0);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 0);
		}
		else if(g_Trim_ZTMBStr_B29_30_S_Trimops == 1)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 0;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 1);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 0);
		}
		else if(g_Trim_ZTMBStr_B29_30_S_Trimops == 2)
		{
			Eetr29_ZTMBStr0_S    = 0;
			Eetr30_ZTMBStr1_S    = 1;
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 0);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 1);
		}
		else if(g_Trim_ZTMBStr_B29_30_S_Trimops == 3)
		{
			Eetr29_ZTMBStr0_S    = 1;
			Eetr30_ZTMBStr1_S    = 1;			
			Set_EEprBit(EEpr_Bank_S[E2],29-16, 1);
			Set_EEprBit(EEpr_Bank_S[E2],30-16, 1);
		}
		else
		{
			//Not doing anything.
		}
		//------------------------------------------------------------------------------
		//ZEE_Dsbl_Foldback
		if(g_Trim_DsblFlBck_B31_S_Trimops == 1)
		{
			Eetr31_DsblFolBack_S = 1;
			Set_EEprBit(EEpr_Bank_S[E2],31-16, 1);
		}
		//-------------------------------------------------------------------------------
		//Dim_th
		if(g_Trim_Dimth_B47_S_Trimops == 1)
		{
			Eetr47_DimTh_S = 1;
			Set_EEprBit(EEpr_Bank_S[E4],47-32, 1);
		}
		//---------------------------------------------------------------------------
		//Zee_tHrtBtOpt
		if(g_Trim_tHrtBtOpt_B61_S_Trimops == 1)
		{
			Eetr61_tHrtBtOpt_S = 1;
			Set_EEprBit(EEpr_Bank_S[E6],61-48, 1);

		}
		//------------------------------------------------------------------------------
		//Disable CP
		if(g_Trim_CPNonI2C_B62_S_Trimops == 1) 
		{
			Eetr62_CPNI2C_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E6], 62-48, 1); //Enable CP in Non-I2C
		}
		//-------------------------------------------------------------------------------
		//Set softstart Freq
		if(g_Trim_ZEE_50KStr_B63_S_Trimops == 1) 
		{
			Eetr63_50KStart_S  = 1;
			Set_EEprBit(EEpr_Bank_S[E6], 63-48, 1); //Set Softstart Start up freq
		}
		//--------------------------------------------------------------------------------
		//Zee_FldBck_CCopt
		if(g_Trim_FlBck_Ccopt_B74_S_Trimops == 1)
		{
			Eetr74_FldBck_CCopt_S = 1;
			Set_EEprBit(EEpr_Bank_S[E8], 74-64, 1); 

		}
		//Zee_FldBck_Sel
		if(g_Trim_FlBck_Sel_B75_S_Trimops == 1)
		{
			Eetr75_FldBck_Sel_S = 1;
			Set_EEprBit(EEpr_Bank_S[E8], 75-64, 1); 

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
