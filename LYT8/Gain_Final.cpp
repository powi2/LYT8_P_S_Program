//==============================================================================
// Gain_Final.cpp (User function)
// 
//    void Gain_Final_user_init(test_function& func)
//    void Gain_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Gain_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Gain_Final_user_init(test_function& func)
{
	Gain_Final_params *ours;
    ours = (Gain_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Gain_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    Gain_Final_params *ours;
    ours = (Gain_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_Gain_Final, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_Gain_Final == 0 )  return;

	// Test Time Begin //
	// if (g_TstTime_Enble_P)
	// 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//float Gain_Final = 0;
	float Gain_IsPin_32mV = 0;
	float Gain_Act_Chg = 0;
	float Gain_Final_TT = 0; 

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //	
	int ReadWordData[16] = {0};
	int ReadByteData[8] = {0};
	float Volt1 = 0;
	float Volt2 = 0;
	int TempGain = 0;
	float IsPinVolt = 0;
	Pulse pulse;

	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	mux_14->close_relay(MUX_2_GND);
	Close_relay(K24); // Connect IS pin to 20X buffer. //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	//IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 3.3; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);

	// SDA //
	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //

	// SCL //
	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

	// Set DDD for I2C. //
	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
	
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Set DDD for I2C. //
	// fSCL- SCL Clock Frequency.  Set the I2C clock frequency to 800kHz to test the upper datasheet limit. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	ddd_7->ddd_set_clock_period(0.41e-6); // To get 800kHz I2C clocking frequency //
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
	
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//	Write_Word_Force_SCL(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word_Force_SCL(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //

	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //


	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		//Write I2C command to connect output of 40X gain amplifier to FB pin using TM_CTRL (tm_ctrl[12]:tm_isn_afe set to 1).
		//Write I2C command to set tm_ctrl[11:8] to '1000'  (design says this will provide cleanest signal on FB pin. )
		//Write_Word(g_TM_CTRL, 0x1800, NObin, HEX);
	//	Write_Word_Force_SCL(g_TM_CTRL, 0x1800, NObin, HEX);
	DSM_Write_Word(g_TM_CTRL, 0x1800); 
		
		// Input 8mV to IS pin and readout the ADC code through I2C;Data1 //
		//IS_dvi2k->set_voltage(IS_ch, 160e-3, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 160mV / 20 = 8mV. //
		//IsPinVolt = 0.008 * g_ISbuff_Gain32;
		IsPinVolt = 0.008 * g_ISbuff_GainLow;
		if(IsPinVolt > 0.9999 || IsPinVolt < -0.9999) // Check for out of range. //
		{
			IsPinVolt = 0.001;
			g_Error_Flag = -210; // Error.  Out of range. //
		}
		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 160mV / 20 = 8mV. //
		wait.delay_10_us(100);

		// Measure volt output on FB pin. //
		FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
		wait.delay_10_us(10);
		Volt1 = FB_ovi->measure();

		// Input 32mV to IS pin and readout the ADC code through I2C;Data2 //
		//IS_dvi2k->set_voltage(IS_ch, 640e-3, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
		IsPinVolt = 0.032 * g_ISbuff_Gain32;
		if(IsPinVolt > 0.9999 || IsPinVolt < -0.9999) // Check for out of range. //
		{
			IsPinVolt = 0.001;
			g_Error_Flag = -210; // Error.  Out of range. //
		}
		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
		wait.delay_10_us(100);

		// Measure volt output on FB pin. //
		Volt2 = FB_ovi->measure();

		if (g_Char_Enable_P) // Characterization only //
		{
			Gain_IsPin_32mV = Volt2;
		}

		// Gain_Final.  Calculate the Gain by (Volt2-Volt1)/0.024 //
		g_Gain_Final = (Volt2-Volt1)/0.024;
		if (g_Trim_Enable_P == 1)
			Gain_Act_Chg = ((g_Gain_Final - g_Gain_Pt_S) / g_Gain_Pt_S)*100; // In percent //

		// Reset test mode control register for next test. //
	//	Write_Word_Force_SCL(g_TM_CTRL, 0x0000, NObin, HEX);
	DSM_Write_Word(g_TM_CTRL, 0x0000);
	}

	// Powerdown //
	//Open_relay(K2);
	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	//Open_relay(K18);
	//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	//mux_14->open_relay(MUX_2_GND);
	//Open_relay(K24);
	//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	//VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	//Mux20_Open_relay(K64);
	//ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	//Mux20_Open_relay(K37);
	//Mux20_Open_relay(K38);
	//Mux20_Open_relay(K40);
	//Mux20_Open_relay(K39);  // Disconnect ovi from SCL. //
	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
	
	// DDD level //
//	g_DDD_Low = 0.0; // Save current value //
//	g_DDD_High = 4.0; // Save current value //
//	wait.delay_10_us(100);
//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		PiDatalog(func, A_Gain_Final, g_Gain_Final, 25, POWER_UNIT); // Note, measured using 800kHz I2C clock frequency. //
	}
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_Gain_IsPin_32mV, Gain_IsPin_32mV, 25, POWER_MILLI); // Note, measured using 800kHz I2C clock frequency. //
	}
	if (g_Trim_Enable_P == 1)
		PiDatalog(func, A_Gain_Act_Chg, Gain_Act_Chg, 25, POWER_UNIT);

	// Test Time End //
	//if (g_TstTime_Enble_P)
	//{
	//	g_endtime = g_mytimer.GetElapsedTime();
	//	Gain_Final_TT = (g_endtime - g_begintime)*1e-6;
	//	PiDatalog(func, A_Gain_Final_TT, Gain_Final_TT, 25, POWER_MILLI);
	//}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
