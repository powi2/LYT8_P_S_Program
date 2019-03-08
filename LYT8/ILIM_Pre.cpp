//==============================================================================
// ILIM_Pre.cpp (User function)
// 
//    void ILIM_Pre_user_init(test_function& func)
//    void ILIM_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "ILIM_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_Pre_user_init(test_function& func)
{
	ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_ILIM_Pre, gFuncNum, 9, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	if (g_Trim_Enable_P == 0)
		return;

	if (g_Fn_ILIM_Pre == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float ILIM_pt_P = 0;
	float ILIM_pt_didt_P = 0;
	float ILIM_pt_ton_P = 0;
	float ILIM_Pre_TT = 0;

	// Declare Variables //
	//int NObin[1] = {0}; // Place holder //
	//int NOhex = 0; // Place holder //
	float Dummy_rdson_peak = 0.0;
	float Dummy_rdson_spec;
	float PV3_Charge =0.0;
	float Vped_meas  =0.0;
	float Vpv3_meas  =0.0;
	int lcnt=0;
	float ChB_vrng=0.0;
	int vrng_b	=0.0;
	Pulse pulse; // External trigger pulse from dvi for debug //


	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	SAMPLE_SIZE = GAGE_POST_32K;
	vrng_b = 0;
	ChB_vrng = 0;
	INNO_Gage_ChanAB_setup(0.1);	// Only do it if SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)
/*
	// Connect Inductor to Drain
	Open_relay(K3); // Drain to RL pullup
	Close_relay(KIM1); // Connect Vind to CT2+ to CT2-
	Close_relay(K9); // Connect CT2- to Drain
	Close_relay(K1); // Connect Iped to CT2+ to CT2-
	

	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
	{
		Close_relay(KIM3); // ILIM Pedestal Use resistor Rpd2
	}
	else
		Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1

	wait.delay_10_us(300);

	// Setup Pedestal
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, g_Vpedestal, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);

	PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage

	// Two pulses 30usec apart to give control to secondary. //
	ddd_7->ddd_run_pattern(Vpin_30usec_start,Vpin_30usec_stop);	
	wait.delay_10_us(10);

	// Enable RTM by switch >110kHz for >200usec. //
	ddd_7->ddd_run_pattern(Vpin_125kHz_pulse_start_X,Vpin_125kHz_pulse_stop_X);	
	wait.delay_10_us(100);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(20);

	// Start capturing data //
	Gage_Start_Capture();

	// Setup to have ILIM switch for 18pulses, then OFF 30us, ON 10us, OFF 200us and ON for 3 pulses of 100kHz
	ddd_7->ddd_run_pattern(Vpin_100kHz_ILIM_pulse_start,Vpin_100kHz_ILIM_pulse_stop);
	wait.delay_10_us(100);	

	// Finish capturing data //
	Gage_Wait_For_Capture_Complete();
	pv3_4->drive_off();	

	// Process data
	WAVE_NAME =  "ILIM_Pre";
	FIND_RDSON_Peak_FLAG = 0;
	Gage_Find_Ilim(&ILIM_pt_P, &ILIM_pt_didt_P, &ILIM_pt_ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);
	gILIM_I2f_pt_S = ILIM_pt_P *ILIM_pt_P * 100e3 * 1e-3; // Pass to global variable
	gILIM_pt_P = ILIM_pt_P;										 // Pass to global variable
	if(ILIM_pt_P > 99)
		gILIM_I2f_pt_S = 999;

	// Powerdown //
	pv3_4->set_current(0.1e-9);						
	pv3_4->set_voltage(0, RANGE_100_V);
	wait.delay_10_us(10);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_1);
	pv3_4->open_switch(PV3_HIGH_SENSE_1);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	wait.delay_10_us(10);
	Open_relay(K12);
	Open_relay(KIM1);
	Open_relay(K9); // Disconnect CT2 from Drain
	Open_relay(KIM3); // Disconnect Pedestal circuit
	Open_relay(K1); // Disconnect Pedestal circuit
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	VBPP_ramp_down(3, 0.0, 0.05);	
	wait.delay_10_us(10);
	VPIN_ovi->connect(VPIN_ch);

	// DDD level //
	wait.delay_10_us(200);
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);	

	// Datalog
	PiDatalog(func, A_ILIM_pt_P, ILIM_pt_P, 9, POWER_MILLI);
	PiDatalog(func, A_ILIM_pt_didt_P, ILIM_pt_didt_P, 9, POWER_MILLI);
	PiDatalog(func, A_ILIM_pt_ton_P, ILIM_pt_ton_P, 9, POWER_MICRO);
	PiDatalog(func, A_ILIM_I2f_pt_P, gILIM_I2f_pt_S, 9, POWER_UNIT);

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		ILIM_Pre_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_ILIM_Pre_TT, ILIM_Pre_TT, 9, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
