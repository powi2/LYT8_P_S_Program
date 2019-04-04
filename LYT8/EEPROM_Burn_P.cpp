//==============================================================================
// EEPROM_Burn_P.cpp (User function)
// 
//    void EEPROM_Burn_P_user_init(test_function& func)
//    void EEPROM_Burn_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "EEPROM_Burn_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_Burn_P_user_init(test_function& func)
{
	EEPROM_Burn_P_params *ours;
    ours = (EEPROM_Burn_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_Burn_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_Burn_P_params *ours;
    ours = (EEPROM_Burn_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, 	A_fNum_EEprP_Burn	,	gFuncNum	, 26, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	int		EEpr_P_Burn=0;

	float	vBurn_P_Tr=0,
			EEprP_Burn_TT=0;

	int pE0_data=0,
		pE2_data=0,
		pE4_data=0,
		pE6_data=0,
		pE8_data=0;

	if(g_Trim_Enable_P)
	{
		Setup_Resources_for_I2C_P();
		PowerUp_I2C_P();

		//************************************************************************************
		//** Burn Primary Trimming parameters Start ******************************************
		//************************************************************************************
		if(1)
		{
			EEPROM_Write_Enable_P();

			//issue write command per Reg_Addr (0xE0,2,4,6,8) for data to write into
			DSM_I2C_Write('w', 0xE0, EEpr_Bank_P[E0]);
			DSM_I2C_Write('w', 0xE2, EEpr_Bank_P[E2]);
			DSM_I2C_Write('w', 0xE4, EEpr_Bank_P[E4]); 
			DSM_I2C_Write('w', 0xE6, EEpr_Bank_P[E6]);
			DSM_I2C_Write('w', 0xE8, EEpr_Bank_P[E8]); 

			EEPROM_BURN_P(&vBurn_P_Tr);

			if(vBurn_P_Tr > 16)			EEpr_P_Burn = 1;
			else						EEpr_P_Burn = 0;

			PiDatalog(func, 	A_vBurn_P_Tr	,	vBurn_P_Tr	, 26, POWER_UNIT);
			PiDatalog(func, 	A_EEpr_P_Burn	,	EEpr_P_Burn	, 26, POWER_UNIT);
			PiDatalog(func, 	A_EEprP_Burn_TT	,	EEprP_Burn_TT	, 26, POWER_UNIT);

		}
		//************************************************************************************
		//** Burn Primary Trimming parameters End ********************************************
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

}
