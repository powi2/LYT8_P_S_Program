//==============================================================================
// TonMin_P.cpp (User function)
// 
//    void TonMin_P_user_init(test_function& func)
//    void TonMin_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "TonMin_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TonMin_P_user_init(test_function& func)
{
	TonMin_P_params *ours;
    ours = (TonMin_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TonMin_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TonMin_P_params *ours;
    ours = (TonMin_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_TonMin_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	//if (g_Fn_TonMin_P == 0 )  return;

	float	TonMin_P		=0;
	float	TonMin_Err_P	=0;
	float	TonMin_P_TT		=0;

	float	tmeas[20]		={0};
	int		i				=0;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	//Setup for Ton_Min measurement
	Close_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Connect
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(0.02,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);


	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C
	DSM_I2C_Write('b', g_TM_CTRL, 0x02);	//0x40, 0x02 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x0024 (I2C password + observe drain 
	DSM_I2C_Write('w', 0x44, 0x0442);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
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

	BPP_zigzag(gVBPP_PV_final, gVBPP_M_final, gVBPP_P_final, 2.0e-3);
	//BPP_zigzag(5.5, 4.3, 5.35, 2.0e-3);

	Load_100Khz_Pulses_TS();
	delay(1);
	Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
	delay(1);


	tmeas[1]=0;
	TonMin_P=0;
	for(i=1; i<=10; i++)
	{
		tmu_6->arm();				
		wait.delay_10_us(10);
		tmeas[i] = tmu_6->read(100e-6);	
		TonMin_P += tmeas[i];
	}
	TonMin_P = TonMin_P/10;

	//Datalog
	PiDatalog(func, A_TonMin_P,		TonMin_P,					14,	POWER_MICRO);	
	PiDatalog(func, A_TonMin_Tgt_P,	gP_TonMin_TARGET_Trimops,	14,	POWER_MICRO);	


	//HL added.  Power down Drain first before disconnecting TMU
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);
	D_dvi->set_current(D_ch, 0.1e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);

	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain									
	Open_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Disconnect
	delay(4);
	Stop_100Khz_Pulses_TS();
	Power_Down_I2C_P();
	Open_relay(K2_D_RB);				//D			to RB_82uH_50ohm to K2_D to DVI-11-0		Disconnect
	Open_relay(K2_TS_TB);				//TS		to OVI_3_0_TS_RB							Connect
	Open_relay(K3_TS_IB);				//DDD7_1	to Comparator LT1719 to COMP_OUT to TS		Disconnect
	delay(3);

}
