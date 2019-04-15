//==============================================================================
// Feature_Trim_P.cpp (User function)
// 
//    void Feature_Trim_P_user_init(test_function& func)
//    void Feature_Trim_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Feature_Trim_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Feature_Trim_P_user_init(test_function& func)
{
	Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Feature_Trim_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_FetrTrim_P, gFuncNum, ours->fail_bin, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	int shift_n_bits = 0;
	int pE0_data=0,
		pE2_data=0,
		pE4_data=0,
		pE6_data=0,
		pE8_data=0;

	if(g_Sim_Enable_P)
	{
		//E2 bank register bits for feature trim
		if(gP_Trim_AR_SKIP_time_Trimops > 0)					//bit 21
		{
			shift_n_bits = gP_Reg_Start_Bit_ArSkip - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( gP_Trim_AR_SKIP_time_Trimops << shift_n_bits );
			//PiDatalog(func, A_AR_SkipT_P, gP_Trim_AR_SKIP_time_Trimops, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Disable_TON_foldback_Trimops > 0)			//bit 22
		{
			shift_n_bits = gP_Reg_Start_Bit_ArOnT - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( gP_Trim_Disable_TON_foldback_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_AR_OnT_P	,	gP_Trim_Disable_TON_foldback_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_AR_OFF_TIME_Trimops > 0)						//bit 23,24
		{
			shift_n_bits = gP_Reg_Start_Bit_ArOffT - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( gP_Trim_AR_OFF_TIME_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_AR_OFFT_P	,	gP_Trim_AR_OFF_TIME_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_START_UP_FREQ_Trimops > 0) 					//bit 25
		{
			shift_n_bits = gP_Reg_Start_Bit_StrFREQ - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( gP_Trim_START_UP_FREQ_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_StartFreq_P	,	gP_Trim_START_UP_FREQ_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Enable_Shunt_during_Cap_Select_Trimops > 0)	//bit31
		{
			shift_n_bits = gP_Reg_Start_Bit_ShuntEn - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( gP_Trim_Enable_Shunt_during_Cap_Select_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_EnShuntCapSel_P	,	gP_Trim_Enable_Shunt_during_Cap_Select_Trimops	, ours->fail_bin, POWER_UNIT);
		}

		//E4 bank register bits for feature trim
		if(gP_Trim_RCV_threshold_Trimops > 0)					//bit 32,33,34
		{
			shift_n_bits = gP_Reg_Start_Bit_RcvTH - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_RCV_threshold_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_Rcv_TH_P	,	gP_Trim_RCV_threshold_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_GaN_Mode_Trimops > 0)						//bit 35
		{
			shift_n_bits = gP_Reg_Start_Bit_GanMode - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_GaN_Mode_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_GanMode_P	,	gP_Trim_GaN_Mode_Trimops	, ours->fail_bin, POWER_UNIT);
		}		
		if(gP_Trim_Sense_Voltage_ILIM_Trimops > 0)				//bit 36,37,38,39,40
		{
			shift_n_bits = gP_Reg_Start_Bit_VxTrim - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_Sense_Voltage_ILIM_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_Vx_Trim_P	,	gP_Trim_Sense_Voltage_ILIM_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Driver_Size_Trimops > 0)						//bit 41,42,43,44
		{
			shift_n_bits = gP_Reg_Start_Bit_DrSize - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_Driver_Size_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_DriverSize_P	,	gP_Trim_Driver_Size_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_AR_ON_time_Trimops > 0)						//bit 45
		{
			shift_n_bits = gP_Reg_Start_Bit_AROn512 - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_AR_ON_time_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_ARON_512ms_P	,	gP_Trim_AR_ON_time_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_GaN_On_Delay_Trimops > 0)					//bit 46,47
		{
			shift_n_bits = gP_Reg_Start_Bit_GanDLy1 - g_E4_start_bit;
			EEpr_Bank_P[E4] = EEpr_Bank_P[E4] | ( gP_Trim_GaN_On_Delay_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_GanDelay_P	,	gP_Trim_GaN_On_Delay_Trimops	, ours->fail_bin, POWER_UNIT);
		}


		//E6 bank register bits for feature trim
		if(gP_Trim_ILIMTC_Trimops > 0)							//bit 48,49,50,51
		{
			shift_n_bits = gP_Reg_Start_Bit_IlimTc - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_ILIMTC_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_ILIMTC_P	,	gP_Trim_ILIMTC_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Bandgap_TSD_Trimops > 0)						//bit 52,53
		{
			shift_n_bits = gP_Reg_Start_Bit_SDTemp - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_Bandgap_TSD_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_SDTemp_P	,	gP_Trim_Bandgap_TSD_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_DOPL_mode_Trimops > 0)						//bit 54
		{
			shift_n_bits = gP_Reg_Start_Bit_DOPL - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_DOPL_mode_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_DOPL_P	,	gP_Trim_DOPL_mode_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Disable_ILIM_cap_Select_Trimops > 0)			//bit 55
		{
			shift_n_bits = gP_Reg_Start_Bit_DisIlimCap - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_Disable_ILIM_cap_Select_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_Dsb_IlimCap_P	,	gP_Trim_Disable_ILIM_cap_Select_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Set_ILIMP_Trimops > 0)						//bit 56
		{
			shift_n_bits = gP_Reg_Start_Bit_ILIMP - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_Set_ILIMP_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_IlimPlus_P	,	gP_Trim_Set_ILIMP_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_Junction_Start_Temp_Trimops > 0)				//bit 61,62,63
		{
			shift_n_bits = gP_Reg_Start_Bit_StrTTFB - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( gP_Trim_Junction_Start_Temp_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_StrTherTemp_P	,	gP_Trim_Junction_Start_Temp_Trimops	, ours->fail_bin, POWER_UNIT);
		}



		//E8 bank register bits for feature trim
		if(gP_Trim_Junction_TSD_Trimops > 0)					//bit 64,65,66
		{
			shift_n_bits = gP_Reg_Start_Bit_EndTTFB - g_E8_start_bit;
			EEpr_Bank_P[E8] = EEpr_Bank_P[E8] | ( gP_Trim_Junction_TSD_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_EndTherTemp_P	,	gP_Trim_Junction_TSD_Trimops	, ours->fail_bin, POWER_UNIT);
		}
		if(gP_Trim_iUV_10pct_Trimops > 0)						//bit 71
		{
			shift_n_bits = gP_Reg_Start_Bit_UV10pct - g_E8_start_bit;
			EEpr_Bank_P[E8] = EEpr_Bank_P[E8] | ( gP_Trim_iUV_10pct_Trimops << shift_n_bits );
			//PiDatalog(func, 	A_UV_10pct_P	,	gP_Trim_iUV_10pct_Trimops	, ours->fail_bin, POWER_UNIT);
		}

		//HL moved it down to the if function below.
		//Setup_Resources_for_I2C_P();
		//PowerUp_I2C_P();

		//************************************************************************************
		//** Burn_P Features Start ***********************************************************
		//************************************************************************************
		if(0) //HL disabled.  This is for manually trimming only.  Feature trim will be done in the EEprom Burn function.
		{
			Setup_Resources_for_I2C_P();
			PowerUp_I2C_P();
			EEPROM_Write_Enable_P();

			//issue write command per Reg_Addr (0xE0,2,4,6,8) for data to write into
			DSM_I2C_Write('w', 0xE0, EEpr_Bank_P[E0]);
			DSM_I2C_Write('w', 0xE2, EEpr_Bank_P[E2]);
			DSM_I2C_Write('w', 0xE4, EEpr_Bank_P[E4]); //(VX=10110 + DriverSize=0010)
			DSM_I2C_Write('w', 0xE6, EEpr_Bank_P[E6]);
			DSM_I2C_Write('w', 0xE8, EEpr_Bank_P[E8]); 

			EEPROM_BURN_P(&g_vDrain_Burn_th_P);

			Power_Down_I2C_P();

		}
		//************************************************************************************
		//** Burn_P Features End *************************************************************
		//************************************************************************************

		//read E0 to E8 register data
		if(0)
		{
			EEPROM_Read_Enable_P();
			//Read data out from EEPROM registers 0xC0
			pE0_data = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
			pE2_data = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
			pE4_data = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
			pE6_data = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
			pE8_data = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		}
		Power_Down_I2C_P();


	}

	PiDatalog(func,		A_AR_SkipT_P,		gP_Trim_AR_SKIP_time_Trimops, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_AR_OnT_P	,		gP_Trim_Disable_TON_foldback_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_AR_OFFT_P	,		gP_Trim_AR_OFF_TIME_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_StartFreq_P,		gP_Trim_START_UP_FREQ_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_EnShuntCapSel_P,	gP_Trim_Enable_Shunt_during_Cap_Select_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_Rcv_TH_P	,		gP_Trim_RCV_threshold_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_GanMode_P	,		gP_Trim_GaN_Mode_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_Vx_Trim_P	,		gP_Trim_Sense_Voltage_ILIM_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_DriverSize_P	,	gP_Trim_Driver_Size_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_ARON_512ms_P	,	gP_Trim_AR_ON_time_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_GanDelay_P	,	gP_Trim_GaN_On_Delay_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_ILIMTC_P	,		gP_Trim_ILIMTC_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_SDTemp_P	,		gP_Trim_Bandgap_TSD_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_DOPL_P	,		gP_Trim_DOPL_mode_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_Dsb_IlimCap_P	,	gP_Trim_Disable_ILIM_cap_Select_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_IlimPlus_P	,	gP_Trim_Set_ILIMP_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_StrTherTemp_P	,	gP_Trim_Junction_Start_Temp_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_EndTherTemp_P	,	gP_Trim_Junction_TSD_Trimops	, ours->fail_bin, POWER_UNIT);
	PiDatalog(func, 	A_UV_10pct_P	,	gP_Trim_iUV_10pct_Trimops	, ours->fail_bin, POWER_UNIT);



}
