//==============================================================================
// TonMin_Pre_P.cpp (User function)
// 
//    void TonMin_Pre_P_user_init(test_function& func)
//    void TonMin_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "TonMin_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TonMin_Pre_P_user_init(test_function& func)
{
	TonMin_Pre_P_params *ours;
    ours = (TonMin_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TonMin_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TonMin_Pre_P_params *ours;
    ours = (TonMin_Pre_P_params *)func.params;


	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_TMin_Tr_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	//// Skip trimming if g_Trim_Enable_P set //
	//if (g_Trim_Enable_P == 0)
	//	return;

	//if (g_Fn_TonMin_Pre_P == 0 )  return;

	float TonMin_pt_P     =0;
	float TonMin_prg_P    =0;
	float TonMin_Target_P = 5.25; 
	int TonMin_TrCode_P   = 0;
	int TonMin_BitCode_P  = 0;
	int EEtr27_ZTML0_P  = 0;
	int EEtr28_ZTML1_P  = 0;
	
	float TonMin_Sim_P = 0;
	float TonMin_Sim_Chg_P = 0;
	float TonMin_ExpChg   = 0;
	float TonMin_PrgChg   = 0;
	float TonMin_pst_P =0;
	float TonMin_Pre_P_TT =0;


	//Trimcode & bit weights.
	float	TonMin_P_TrimWt[32]   = {0.0};
	float	TonMin_P_code[32]     = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;

	float	tmeas[20]			= {0};


	i=0;
	TonMin_P_code[i] =  0	;	 TonMin_P_TrimWt[i] 	=	0.000	;	    i++	;
	TonMin_P_code[i] =  1	;	 TonMin_P_TrimWt[i] 	=	1.000	;	    i++	;
	TonMin_P_code[i] =  2	;	 TonMin_P_TrimWt[i] 	=	2.000	;	    i++	;
	TonMin_P_code[i] =  3	;	 TonMin_P_TrimWt[i] 	=	3.000	;	    i++	;
	TonMin_P_code[i] =  4	;	 TonMin_P_TrimWt[i] 	=	4.000	;	    i++	;
	TonMin_P_code[i] =  5	;	 TonMin_P_TrimWt[i] 	=	5.000	;	    i++	;
	TonMin_P_code[i] =  6	;	 TonMin_P_TrimWt[i] 	=	6.000	;	    i++	;
	TonMin_P_code[i] =  7	;	 TonMin_P_TrimWt[i] 	=	7.000	;	    i++	;
	TonMin_P_code[i] =  8	;	 TonMin_P_TrimWt[i] 	=	8.000	;	    i++	;
	TonMin_P_code[i] =  9	;	 TonMin_P_TrimWt[i] 	=	9.000	;	    i++	;
	TonMin_P_code[i] = 10	;	 TonMin_P_TrimWt[i] 	=	10.000	;	    i++	;
	TonMin_P_code[i] = 11	;	 TonMin_P_TrimWt[i] 	=	11.000	;	    i++	;
	TonMin_P_code[i] = 12	;	 TonMin_P_TrimWt[i] 	=	12.000	;	    i++	;
	TonMin_P_code[i] = 13	;	 TonMin_P_TrimWt[i] 	=	13.000	;	    i++	;
	TonMin_P_code[i] = 14	;	 TonMin_P_TrimWt[i] 	=	14.000	;	    i++	;
	TonMin_P_code[i] = 15	;	 TonMin_P_TrimWt[i] 	=	15.000	;	    i++	;

	//Pass Bank E0 trim registers data to the WordArray
	/*
		TonMin_3_P	bit 11
		TonMin_2_P	bit 10
		TonMin_1_P	bit 9
		TonMin_0_P	bit 8
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


	//Setup for Ton_Min measurement
	Close_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Connect
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(0.15,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);


	Pulse pulse;
	pulse.do_pulse();	

	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	DSM_I2C_Write('b', g_TM_CTRL, 0x02);	//0x40, 0x06 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x0024 (I2C password + observe drain 
	DSM_I2C_Write('w', 0x44, 0x0442);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
	DSM_I2C_Write('b', 0x4C, 0x01);				//release TS pin

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C


	//--------------------------------------------------------------------------------------------
	//Setup for TS to run 100kHz
		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	wait.delay_10_us(10);

	Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
	Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
	delay(4);

	TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
	wait.delay_10_us(10);

	//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
	Close_relay(K2_D_RB);
	delay(4);
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
		delay(1);
		D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
		delay(1);

	BPP_zigzag(5.5, 4.3, 5.4);
		////BPP zig zag (5V to 5.5V to 4.3V to 5.4V below OV threshold)
		//BPP_dvi->set_voltage(BPP_ch, 5.5, VOLT_10_RANGE); // DVI_11_1
		//delay(1);
		//BPP_dvi->set_voltage(BPP_ch, 4.3, VOLT_10_RANGE); // DVI_11_1
		//delay(1);
		//BPP_dvi->set_voltage(BPP_ch, 5.4, VOLT_10_RANGE); // DVI_11_1
		//delay(1);


	Load_100Khz_Pulses_TS();
	delay(1);
	Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
	delay(1);


	tmeas[1]=0;
	TonMin_pt_P=0;
	for(i=1; i<=10; i++)
	{
		tmu_6->arm();				
		wait.delay_10_us(10);
		tmeas[i] = tmu_6->read(100e-6);	
		TonMin_pt_P += tmeas[i];
	}
	TonMin_pt_P = TonMin_pt_P/10;

	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain									
	Open_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Disconnect
	delay(4);
	Stop_100Khz_Pulses_TS();
	Power_Down_I2C_P();
	Open_relay(K2_D_RB);				//D			to RB_82uH_50ohm to K2_D to DVI-11-0		Disconnect
	Open_relay(K2_TS_TB);				//TS		to OVI_3_0_TS_RB							Connect
	Open_relay(K3_TS_IB);				//DDD7_1	to Comparator LT1719 to COMP_OUT to TS		Disconnect

	//Datalog
	PiDatalog(func, A_TonMin_pt_P, TonMin_pt_P, 14,	POWER_MICRO);	


}
