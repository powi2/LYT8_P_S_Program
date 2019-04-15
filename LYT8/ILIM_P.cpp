//==============================================================================
// ILIM_P.cpp (User function)
// 
//    void ILIM_P_user_init(test_function& func)
//    void ILIM_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "ILIM_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_P_user_init(test_function& func)
{
	ILIM_P_params *ours;
    ours = (ILIM_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_P_params *ours;
    ours = (ILIM_P_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_ILIM_P, gFuncNum, 9, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_Fn_ILIM == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//float	ILIM_P = 0;
	//float	ILIM_TT		=0;	
	//float	tmeas[20]					= {0};	
	//int		i=0, j=0;		
	//float ILIM_didt_P = 0;
	//float ILIM_ton_P = 0;

	float	ILIM_Tgt_P	=0;
	float	ILIM_P	=0;
	float	ILIM_Err_P	=0;
	float	ILIM_didt_P	=0;
	float	ILIM_Ton_P	=0;
	float	ILIM_Rdson_P	=0;
	float	ILIMp1_P	=0;
	float	ILIMp1_Err_P	=0;
	float	ILIMp1_didt_P	=0;
	float	ILIMp1_Ton_P	=0;
	float	ILIMp1_Rdson_P	=0;
	float	ILIM_P_TT	=0;
	int	i	=0;


	float Dummy_rdson_peak = 0.0;
	float Dummy_rdson_spec;


	Pulse pulse; // External trigger pulse from dvi for debug //


	//Decide what Inductor pullup voltage to use per FET SIZE
	gVind_RM = 42.5;	//size x8

	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	g_SAMPLE_SIZE = GAGE_POST_32K;
	BINNO_Gage_ChanAB_setup(0.15);	// Only do it if g_SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)
	//vrng_b = 0;
	//ChB_vrng = 0;
	
	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	DSM_I2C_Write('b', g_TM_CTRL, 0x06);		//0x40, 0x06 (enable analog mode + core_en)
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x2804
	DSM_I2C_Write('w', 0x44, 0x0402);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
	DSM_I2C_Write('b', 0x4C, 0x01);				//release TS pin

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

	
	//HL-Question: Should TS/UV pins be powered down before opening relays?
	//This can be hot-switching the DSM relays on the primary sides.
	//Disconnect DSM from Primary after releasing VPIN or TS pins
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(10);
	TS_ovi3->set_current(TSovi3_ch, 0.01e-3, RANGE_30_MA);
	UV_dvi->set_current(UV_ch, 0.01e-3, RANGE_300_MA);
	wait.delay_10_us(10);
	//--------------------------------------------------------------------------------------------
	//Setup for TS to run 100kHz
	//Disconnect DSM from Primary after releasing VPIN or TS pins
	Open_relay(K1_DSM_TB);	
	Open_relay(K3_DSM_TB);	
	delay(3);

	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	wait.delay_10_us(10);

	Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
	Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
	delay(4);

	TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
	wait.delay_10_us(10);

	if(0)	//Observe from RL pullup
	{
		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
		Close_relay(K2_D_RB);
		delay(4);
			D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
			delay(1);
			D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE); // DVI_11_0
			delay(1);
	}
	else	//Observe from Inductor pullup
	{
		//Connect Drain to IM with PV3
		Close_relay(K3_D_TB);	// disconnect	Drain from RL pullup 
		Close_relay(K9_D_TB);	// Connect		Drain to CT- to Pearson to CT+ & CT2+
				//Close_relay(K1_D_RB);	// Connect		Iped to CT2+ to CT2-
		Close_relay(K1_IM_TB);	// Connect		Vind to CT2+ to CT2-
		delay(5);
		PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
	}

	Load_100Khz_Pulses_TS();
	wait.delay_10_us(50);
	BPP_zigzag(gVBPP_PV_final, gVBPP_M_final, gVBPP_P_final, 2e-3);
	//BPP_zigzag(5.5, 4.3, 5.3, 2e-3);
	BPP_dvi->set_current(BPP_ch, 5.0e-3, RANGE_300_MA);
		
	Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
	//wait.delay_10_us(50);
	Gage_Start_Capture(0);
		
	Gage_Wait_For_Capture_Complete();
	pv3_4->drive_off();	
	Stop_100Khz_Pulses_TS();

DEBUG=0;
g_Debug=0;
	g_WAVE_NAME =  "ILIM";
	g_FIND_RDSON_Peak_FLAG = 0;
	Gage_Find_Ilim(&ILIM_P, &ILIM_didt_P, &ILIM_Ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);
DEBUG=0;
g_Debug=0;

	PiDatalog(func, A_ILIM_P,		ILIM_P,					ours->fail_bin, POWER_MILLI);
	PiDatalog(func, A_ILIM_didt_P,	ILIM_didt_P,			ours->fail_bin, POWER_MILLI);
	PiDatalog(func, A_ILIM_Ton_P,	ILIM_Ton_P,				ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_ILIM_Tgt_P,	gP_ILIM_TARGET_Trimops,	ours->fail_bin, POWER_MILLI);
	

	pv3_4->drive_off();	

	pv3_4->set_current(0.1e-9);						
	pv3_4->set_voltage(0, RANGE_100_V);
	wait.delay_10_us(10);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_1);
	pv3_4->open_switch(PV3_HIGH_SENSE_1);
	delay(1);
	pv3_4->charge_on();	

	Power_Down_I2C_P();
	Open_relay(K2_D_RB);				//D			to RB_82uH_50ohm to K2_D to DVI-11-0		Disconnect
	Open_relay(K2_TS_TB);				//TS		to OVI_3_0_TS_RB							Connect
	Open_relay(K3_TS_IB);				//DDD7_1	to Comparator LT1719 to COMP_OUT to TS		Disconnect

	//disconnect Drain from IM
	Open_relay(K3_D_TB);	// Connect			Drain to RL pullup 
	Open_relay(K9_D_TB);	// disConnect		Drain to CT2-
	//Open_relay(K1_D_RB);	// disConnect		Iped to CT2+ to CT2-
	Open_relay(K1_IM_TB);	// disConnect		Vind to CT2+ to CT2-
	delay(1);



/*
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		ILIM_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_ILIM_TT, ILIM_TT, 9, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/

}
