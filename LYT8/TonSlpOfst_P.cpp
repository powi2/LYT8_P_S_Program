//==============================================================================
// TonSlpOfst_P.cpp (User function)
// 
//    void TonSlpOfst_P_user_init(test_function& func)
//    void TonSlpOfst_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "TonSlpOfst_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TonSlpOfst_P_user_init(test_function& func)
{
	TonSlpOfst_P_params *ours;
    ours = (TonSlpOfst_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TonSlpOfst_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TonSlpOfst_P_params *ours;
    ours = (TonSlpOfst_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_SlpOfst_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	//if (g_Fn_Ton_Pre_P == 0 )  return;

	float	Ton_30kHz_P	=0;
	float	Ton_80kHz_P	=0;
	float	Ton_30kHz_Sim_P	=0;
	float	Ton_80kHz_Sim_P	=0;
	float	dx	=99;
	float	dy	=0;
	float	Slope_P	=0;


	float	tmeas[20]					= {0};	
	int		i=0, j=0;		

	float	Offset_P			=0;	
	float	Offset1_P			=0;	
	float	Offset_pst1_P		=0;
	float	Offset_Pre_TT		=0;	

	int		pE0_data[33] = {0};
	int		pE2_data[33] = {0};
	int		pE4_data[33] = {0};
	int		pE6_data[33] = {0};
	int		pE8_data[33] = {0};

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	//Setup for Ton_Min measurement
	Close_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Connect
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);


	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	DSM_I2C_Write('b', g_TM_CTRL, 0x02);	//0x40, 0x06 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x0024 (I2C password + observe drain 
	DSM_I2C_Write('w', 0x44, 0x0402);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
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
	
	BPP_zigzag(5.5, 4.3, 5.3);

		Load_30Khz_Pulses_TS();
		delay(1);
		Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		delay(1);
		//Observe 1.44us Ton_min at 30kHz TS request
		tmeas[1]=0;
		Ton_30kHz_P=0;
		for(i=1; i<=10; i++)
		{
			tmeas[i]=0;		//reset array values before use again.
			tmu_6->arm();				
			wait.delay_10_us(10);
			tmeas[i] = tmu_6->read(100e-6);	
			Ton_30kHz_P += tmeas[i];
		}
		Ton_30kHz_P = Ton_30kHz_P/10;


		tmu_6->stop_trigger_setup(0.3,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope

		Load_80Khz_Pulses_TS();
		delay(1);
		Run_80Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		delay(1);
		//Observe that the part react to faster freq request and adjust Ton accordingly
		//The first two Ton is due to transient behavior.  We want to ignore them.
		//We need to observe from the 4th pulse and expect all Ton stays the same after the 4th pulse.
		//Observe 5.64us Ton_min at 80kHz TS request.
		Ton_80kHz_P=0;
		for(i=1; i<=10; i++)
		{
			tmeas[i]=0;		//reset array values before use again.
			tmu_6->arm();				
			wait.delay_10_us(10);
			tmeas[i] = tmu_6->read(100e-6);	
			Ton_80kHz_P += tmeas[i];
		}
		Ton_80kHz_P = Ton_80kHz_P/10;

		dy = Ton_80kHz_P - Ton_30kHz_P;
		dx = 80 - 30;
		Slope_P = dy/dx;	//us/kHz

	//Datalog
	PiDatalog(func, A_Slope_P,		Slope_P,					14,	POWER_MICRO);	
	PiDatalog(func, A_Slope_Tgt_P,	gP_Slope_TARGET_Trimops,	14,	POWER_MICRO);	

	//---------------------------------------------------------------------------------
	//------- Offset Start ---------------------------
	//---------------------------------------------------------------------------------
	if(1)
	{
		//Find offset using formula y = mx + b where m = slope, x = known frequency in kHz, y = TonMin @ x 
		////Offset_P = Ton_80kHz_P - (Slope_P * 80);
		//	Designer is using y = mx - b instead of y = mx + b.  Hence b = mx - y ==> Offset = (Slope * 80) - Ton_80k
		Offset_P = (Slope_P * 80) - Ton_80kHz_P;
		Offset_P = Offset_P + Ton_30kHz_P - 1.08666666667e-6;

		PiDatalog(func, A_Offset_P,			Offset_P,				14,	POWER_MICRO);	
		PiDatalog(func, A_Offset_Tgt_P,		gP_Offset_TARGET_Trimops,	14,	POWER_MICRO);	
	}
	//---------------------------------------------------------------------------------
	//------- Offset Stop ---------------------------
	//---------------------------------------------------------------------------------

	delay(4);
	Stop_100Khz_Pulses_TS();
	Power_Down_I2C_P();
	Open_relay(K2_D_RB);
	Open_relay(K2_TS_TB); //TS to OVI_3_0_TS_RB								Connect
	Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS	Disconnect


}
