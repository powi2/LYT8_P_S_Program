//==============================================================================
// IsCal_Final.cpp (User function)
// 
//    void IsCal_Final_user_init(test_function& func)
//    void IsCal_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IsCal_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IsCal_Final_user_init(test_function& func)
{
	IsCal_Final_params *ours;
    ours = (IsCal_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IsCal_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    IsCal_Final_params *ours;
    ours = (IsCal_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;	
////
////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_IsCalFinal, gFuncNum, 25, POWER_UNIT);
////
////	// Skip Test if AbortTest set 
////	if (AbortTest)
////		return;
////
////	if (g_Fn_IsCal_Final == 0 )  return;
////
////	// Test Time Begin //
////	// if (g_TstTime_Enble_P)
////	// 	g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	//float IsCal_final =0;	
////	float IsCal_Act_Chg =0;
////	float IsCal_final_TT =0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	int WordArray[16] = {0};
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	int ReadWordData[16] = {0};
////	int ReadByteData[8] = {0};
////	int CalCode = 0;
////	Pulse pulse;
////
////	// Open all relays //
////	Initialize_Relays();
////
////	// Initialize Instruments //
////	Initialize_Instruments();
////
////	// Drain //
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////
////	// BPP //
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////	// V pin //
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////
////	// FW //
////	Close_relay(K18);
////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////
////	// SR //
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////	//IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
////
////	// FB (COMP) //
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_1_V); // OVI_1_2 //
////	FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
////	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////	// VBD //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////	wait.delay_10_us(25); // Prevent glitch //
////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////
////	// uVCC //
////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////	// DDD level //
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 3.3; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////
////	// SDA //
////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////	// SCL //
////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////	// Set DDD for I2C. //
////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////	
////	// Wait for relays //
////	wait.delay_10_us(200); 
////
////	// Powerup //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////	// I2C into test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////	//Write I2C command to connect output of 40X gain amplifier to FB pin using TM_CTRL (tm_ctrl[12]:tm_isn_afe set to 1).
////	//Write I2C command to set tm_ctrl[11:8] to '1000'  (design says this will provide cleanest signal on FB pin. )
//////	Write_Word(g_TM_CTRL, 0x1800, NObin, HEX);
////DSM_Write_Word(g_TM_CTRL, 0x1800);
////
////	if (g_Char_Enable_P) // Characterization only //
////	{
////		// Measure output of 40X gain amplifier.  Value should be around 400mV.  10mV offset source x 10 = 400mV. //
////		wait.delay_10_us(100);
////		g_IsCal_final = FB_ovi->measure_average(50);
////		if (g_Trim_Enable_P == 1)
////			IsCal_Act_Chg = ((g_IsCal_final - g_IsCal_Pt_S) / g_IsCal_Pt_S)*100; // In percent //
////	}
////
////	// Powerdown //
////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	//Open_relay(K18);
////	//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	//VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////	//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	//Mux20_Open_relay(K64);
////	//ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////	//Mux20_Open_relay(K37);
////	//Mux20_Open_relay(K38);
////	//Mux20_Open_relay(K40);
////	//Mux20_Open_relay(K39);  // Disconnect ovi from SCL. //
////	//Mux20_Open_relay(K50); // Open SR pin hard short to GND with relay //
////	//ddd_7->ddd_set_clock_period(Dclk_period);
////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////
////	// Datalog //
////	if (g_Char_Enable_P) // Characterization only //
////	{
////		PiDatalog(func, A_IsCal_final, g_IsCal_final, 25, POWER_MILLI);
////		if (g_Trim_Enable_P == 1)
////			PiDatalog(func, A_IsCal_Act_Chg, IsCal_Act_Chg, 25, POWER_UNIT);
////	}
////
////	// Test Time End //
////	//if (g_TstTime_Enble_P)
////	//{
////	//	g_endtime = g_mytimer.GetElapsedTime();
////	//	IsCal_final_TT = (g_endtime - g_begintime)*1e-6;
////	//	PiDatalog(func, A_IsCal_final_TT, IsCal_final_TT, 25, POWER_MILLI);
////	//}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
