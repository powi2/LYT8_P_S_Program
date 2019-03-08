//==============================================================================
// Fosc_Pre_P.cpp (User function)
// 
//    void Fosc_Pre_P_user_init(test_function& func)
//    void Fosc_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Pre_P_user_init(test_function& func)
{
	Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_Fosc_Pre_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	//if (g_Trim_Enable_P == 0)
	//	return;

	//if (g_Fn_Fosc_Pre_P == 0 )  return;

	float Fosc_pt_P     =0;
	float Fosc_prg_P    =0;
	float Fosc_Target_P = 5.25; 
	int Fosc_TrCode_P   = 0;
	int Fosc_BitCode_P  = 0;
	int EEtr27_ZTML0_P  = 0;
	int EEtr28_ZTML1_P  = 0;
	
	float Fosc_Sim_P = 0;
	float Fosc_Sim_Chg_P = 0;
	float Fosc_ExpChg   = 0;
	float Fosc_PrgChg   = 0;
	float Fosc_pst_P =0;
	float Fosc_Pre_P_TT =0;


	//Trimcode & bit weights.
	float	Fosc_P_TrimWt[32]   = {0.0};
	float	Fosc_P_code[32]     = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;

	float	tmeas=0;


	i=0;
	Fosc_P_code[i] =  0	;	 Fosc_P_TrimWt[i] 	=	0.000	;	    i++	;
	Fosc_P_code[i] =  1	;	 Fosc_P_TrimWt[i] 	=	1.000	;	    i++	;
	Fosc_P_code[i] =  2	;	 Fosc_P_TrimWt[i] 	=	2.000	;	    i++	;
	Fosc_P_code[i] =  3	;	 Fosc_P_TrimWt[i] 	=	3.000	;	    i++	;
	Fosc_P_code[i] =  4	;	 Fosc_P_TrimWt[i] 	=	4.000	;	    i++	;
	Fosc_P_code[i] =  5	;	 Fosc_P_TrimWt[i] 	=	5.000	;	    i++	;
	Fosc_P_code[i] =  6	;	 Fosc_P_TrimWt[i] 	=	6.000	;	    i++	;
	Fosc_P_code[i] =  7	;	 Fosc_P_TrimWt[i] 	=	7.000	;	    i++	;
	Fosc_P_code[i] =  8	;	 Fosc_P_TrimWt[i] 	=	8.000	;	    i++	;
	Fosc_P_code[i] =  9	;	 Fosc_P_TrimWt[i] 	=	9.000	;	    i++	;
	Fosc_P_code[i] = 10	;	 Fosc_P_TrimWt[i] 	=	10.000	;	    i++	;
	Fosc_P_code[i] = 11	;	 Fosc_P_TrimWt[i] 	=	11.000	;	    i++	;
	Fosc_P_code[i] = 12	;	 Fosc_P_TrimWt[i] 	=	12.000	;	    i++	;
	Fosc_P_code[i] = 13	;	 Fosc_P_TrimWt[i] 	=	13.000	;	    i++	;
	Fosc_P_code[i] = 14	;	 Fosc_P_TrimWt[i] 	=	14.000	;	    i++	;
	Fosc_P_code[i] = 15	;	 Fosc_P_TrimWt[i] 	=	15.000	;	    i++	;

	//Pass Bank E0 trim registers data to the WordArray
	/*
		fOSC_3_P	bit 11
		fOSC_2_P	bit 10
		fOSC_1_P	bit 9
		fOSC_0_P	bit 8
	*/

	WordArray[0]  	=	 g_S_TrimRegister[0];	//E0 bit 0
	WordArray[1]  	=	 g_S_TrimRegister[1];	//E0 bit 1
	WordArray[2]  	=	 g_S_TrimRegister[2];	//E0 bit 2
	WordArray[3]  	=	 g_S_TrimRegister[3];	//E0 bit 3
	WordArray[4]  	=	 g_S_TrimRegister[4];	//E0 bit 4
	WordArray[5]  	=	 g_S_TrimRegister[5];	//E0 bit 5
	WordArray[6]  	=	 g_S_TrimRegister[6];	//E0 bit 6
	WordArray[7]  	=	 g_S_TrimRegister[7];	//E0 bit 7
	WordArray[8]  	=	 g_S_TrimRegister[8];	//E0 bit 8	fosc_0
	WordArray[9]  	=	 g_S_TrimRegister[9];	//E0 bit 9	fosc_1
	WordArray[10] 	=	 g_S_TrimRegister[10];	//E0 bit 10	fosc_2
	WordArray[11] 	=	 g_S_TrimRegister[11];	//E0 bit 11	fosc_3
	WordArray[12] 	=	 g_S_TrimRegister[12];	//E0 bit 12
	WordArray[13] 	=	 g_S_TrimRegister[13];	//E0 bit 13
	WordArray[14] 	=	 g_S_TrimRegister[14];	//E0 bit 14
	WordArray[15] 	=	 g_S_TrimRegister[15];	//E0 bit 15


	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	DSM_I2C_Write('b', g_TM_CTRL, 0x06);	//0x40, 0x06 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2824);	//0x46, 0x0024 (I2C password + observe drain 

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

	Close_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	Close_relay(K1_TMU_TB);	//D  to TMU_HIZ1
		delay(4);

	//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
		delay(1);
		D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
		delay(1);

	//Drain signal shows sharper rising edge, hence use START/STOP POSITIVE/POSITIVE
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		
	tmu_6->stop_trigger_setup(1.7,  NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	//tmu_6->start_trigger_setup(2.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		
	//tmu_6->stop_trigger_setup(2.7,  NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	//tmu_6->start_trigger_setup(-0.25, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		//noise level only
	//tmu_6->stop_trigger_setup(-0.15,  NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		//noise level only
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(10,TRUE);
	wait.delay_10_us(100);
	delay(4);

	tmu_6->arm();				
	delay(1);					
	tmeas = tmu_6->read(1e-3);	
	tmeas/=10;	
	Fosc_pt_P = 1/tmeas;


	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain 
	Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	Open_relay(K1_TMU_TB);	//D  to TMU_HIZ1
	delay(4);
	Power_Down_I2C_P();

	//Datalog
	PiDatalog(func, A_Fosc_pt_P, Fosc_pt_P, 14,	POWER_KILO);	


	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Fosc_Pre_P_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Fosc_Pre_P_TT, Fosc_Pre_P_TT, 14, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}











}
