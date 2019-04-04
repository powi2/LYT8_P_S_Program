//==============================================================================
// ADC_Final.cpp (User function)
// 
//    void ADC_Final_user_init(test_function& func)
//    void ADC_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "ADC_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ADC_Final_user_init(test_function& func)
{
	ADC_Final_params *ours;
    ours = (ADC_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ADC_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    ADC_Final_params *ours;
    ours = (ADC_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_ADC_Final, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_ADC_Final == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//float ADC_Final = 0;
	float ADC_Act_Chg = 0;
	float IIL_VO_final = 0;
	float IIH_COMP_final = 0;
	float IIH_FW_final = 0;
	float ADC_Final_TT = 0;

	// Declare Variables //
	Pulse pulse;

	if (g_Char_Enable_P) // Characterization only //
	{
		// Datalog //
		PiDatalog(func, A_ADC_Final, g_ADC_Final, 25, POWER_UNIT); // Measured in CV_nDAC_pDAC.cpp //
		if (g_Sim_Enable_P == 1)
		{
			ADC_Act_Chg = ((g_ADC_Final - g_ADC_Pt) / g_ADC_Pt)*100; // In percent //
			PiDatalog(func, A_ADC_Act_Chg, ADC_Act_Chg, 25, POWER_UNIT);
		}
	}


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Additonal leakage tests done here. Leakage currents change if EEPROM bit 63
	// is trimmed, so need to measure again here with different test limts. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	if (g_EE_ShadReg63 == 1)
	{
		// Open all relays //
//		Initialize_Relays();

		// Initialize Instruments //
//		Initialize_Instruments();

		// BPS //
		BPS_dvi->set_current(BPS_ch, 10.0e-3, RANGE_30_MA);

		// Prevent overshoot //
		BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
		BPS_dvi->set_voltage(BPS_ch, 2, VOLT_5_RANGE);
		wait.delay_10_us(20);
		BPS_dvi->set_voltage(BPS_ch, 3, VOLT_5_RANGE);
		wait.delay_10_us(20);
		BPS_dvi->set_voltage(BPS_ch, 4, VOLT_5_RANGE);
		wait.delay_10_us(20);
		BPS_dvi->set_voltage(BPS_ch, 4.5, VOLT_5_RANGE);
		wait.delay_10_us(100);
	
		// Measure leakage current on COMP and VO pins again because leakage changes 
		// if shadow register bit 63 is trimmed and need different test limits. //
		// FB(COMP) leakage
		FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);
		FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); 
		FB_ovi->set_current(FB_ch, 300.0e-6, RANGE_300_UA);
		wait.delay_10_us(50);
		FB_ovi->set_voltage(FB_ch, 5.5, RANGE_10_V); 
		wait.delay_10_us(100);
		IIH_COMP_final = FB_ovi->measure_average(5); 
		FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V);

		// Vout Leakage //
		VO_dvi->set_current(VO_ch, 300e-6, RANGE_300_UA);
		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);
		wait.delay_10_us(205);
		IIL_VO_final = VO_dvi->measure_average(5);

		// Datalog //
		PiDatalog(func, A_IIH_COMP_final, IIH_COMP_final, 11, POWER_MICRO);
		PiDatalog(func, A_IIL_VO_final, IIL_VO_final, 11, POWER_MICRO);
	}

	// Powerdown //
	VBPS_ramp_down(4.5, 0, 200e-3);


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// IIH_FW_final- FW pin leakage
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	//FW_dvi->set_current(FW_ch, 30e-6, RANGE_30_UA); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 200e-6, RANGE_300_UA);

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //

	// COMP //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// SDA //
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //

	// SCL //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //

	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(80);

	// Bring up FWpin, measure leakage. //
	FW_dvi->set_voltage(FW_ch, 5, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT); // DVI_11_1 //
	wait.delay_10_us(100);
	IIH_FW_final = FW_dvi->measure_average(5);

	// Powerdown //
	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1, prevent undershoot //
	SR_dvi2k->set_voltage(SR_ch, 0.5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	wait.delay_10_us(30); // prevent undershoot //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(5); // prevent undershoot //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	wait.delay_10_us(5); // prevent undershoot //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(1, 0, 0.1);
	VBPS_ramp_down(3, 0, 150e-3);
	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	Open_relay(K18);
	FB_ovi->connect(2);
	wait.delay_10_us(100); 


	// Datalog //
	PiDatalog(func, A_IIH_FW_final, IIH_FW_final, 11, POWER_MICRO);

	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		ADC_Final_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_ADC_Final_TT, ADC_Final_TT, 25, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
