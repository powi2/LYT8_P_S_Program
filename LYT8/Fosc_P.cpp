//==============================================================================
// Fosc_P.cpp (User function)
// 
//    void Fosc_P_user_init(test_function& func)
//    void Fosc_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_P_user_init(test_function& func)
{
	Fosc_P_params *ours;
    ours = (Fosc_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_P_params *ours;
    ours = (Fosc_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_Fosc_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	//if (g_Sim_Enable_P == 0)
	//	return;

	//if (g_Fn_Fosc_Pre_P == 0 )  return;

	float	Fosc_P		=0,
			Fosc_Err_P	=0,
			TonMax_P	=0,
			DCMax_P		=0,
			Fosc_P_TT	=0;


	float	tmeas=0;


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
	Fosc_P = 1/tmeas;

	//
	//Datalog
	PiDatalog(func, A_Fosc_P,		Fosc_P,					14,	POWER_MEGA);	
	PiDatalog(func, A_Fosc_Tgt_P,	gP_Fosc_TARGET_Trimops,	14,	POWER_MEGA);	


	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain 
	Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	Open_relay(K1_TMU_TB);	//D  to TMU_HIZ1
	delay(4);
	Power_Down_I2C_P();



	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Fosc_P_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Fosc_P_TT, Fosc_P_TT, 14, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}

}
