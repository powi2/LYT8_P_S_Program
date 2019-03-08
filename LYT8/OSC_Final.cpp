//==============================================================================
// OSC_Final.cpp (User function)
// 
//    void OSC_Final_user_init(test_function& func)
//    void OSC_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "OSC_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void OSC_Final_user_init(test_function& func)
{
	OSC_Final_params *ours;
    ours = (OSC_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void OSC_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    OSC_Final_params *ours;
    ours = (OSC_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;

	//////// Datalog gFuncNum variable //
	//////if(gDisplay_FuncNum)
	//////	PiDatalog(func, A_fNum_OSC_Final, gFuncNum, 25, POWER_UNIT);

	//////// Skip Test if AbortTest set //
	//////if (AbortTest)
	//////	return;

	//////if (g_Fn_OSC_Final == 0 )  return;

	//////// Test Time Begin //
	//////// if (g_TstTime_Enble_P)
	//////// 	g_begintime = g_mytimer.GetElapsedTime();

	//////// Test Names //
	//////float OSC_Final = 0;
	//////float OSC_Act_Chg = 0;
	//////float OSC_Final_TT = 0;

	//////// Declare Variables //
	//////float Period = 0;
	//////int NObin[1] = {0}; // Place holder //
	//////int NOhex = 0; // Place holder //
	//////int WordArray[16] = {0};
	//////int TempArray[30] = {0};
	//////float Frequency = 0;
	//////int UpperLimit = 0;
	//////int LowerLimit = 0;
	//////Pulse pulse;
	//////
	//////if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	//////{
	//////	// Set DSM clock frequency //
	//////	DSM_set_vector_clock_freq(DSM_CONTEXT, 2400); // Freq in kHZ, 2400/4 = 600kHz clock frequency //  // Add I2C DSM //

	//////	// Open all relays //
	//////	//Initialize_Relays();

	//////	// Initialize Instruments //
	//////	//Initialize_Instruments();

	//////	// Drain //
	//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	//////	// BPP //
	//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	//////	// V pin //
	//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	//////	// FW //
	//////	Close_relay(K18);
	//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	//////	// SR //
	//////	Mux20_Close_relay(K42); // TMU_HIZ_4 to SR pin //
	//////	tmu_6->close_relay(TMU_HIZ_DUT4);
	//////	tmu_6->start_trigger_setup(1.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	//////	tmu_6->stop_trigger_setup(1.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

	//////	// BPS //
	//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	//////	// IS //
	//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	//////	// Vout //
	//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	//////	// COMP //
	//////	FB_ovi->disconnect(2);

	//////	// VBD //
	//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	//////	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	//////	//wait.delay_10_us(25); // Prevent glitch //
	//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	//////	// uVCC //
	//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	//////	// DDD level //
	//////	//g_DDD_Low = 0.0; // Save current value //
	//////	//g_DDD_High = 3.3; // Save current value //
	//////	//wait.delay_10_us(g_DDDwait);
	//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//////	//wait.delay_10_us(g_DDDwait);

	//////	// SDA //
	//////	Mux20_Close_relay(K64);  // SDA pullup to 3.3V through 1.5kohm resistor. //
	//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	//////	Mux20_Close_relay(K37);  // Disconnect ovi from SDA. //
	//////	Mux20_Close_relay(K38);  // Connect SDA and SCL to DDD. //
	////////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
	//////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //

	//////	// SCL //
	//////	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
	//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

	//////	// Set DDD for I2C. //
	//////	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//////	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
	//////		
	//////	// Wait for relays //
	//////	wait.delay_10_us(200); 

	//////	// Powerup //
	//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	//////	// I2C into test mode. //  
	////////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	//////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
	////////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C password for test mode. //
	//////	
	////////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //
	//////DSM_Write_Word(g_TM_ANA, 0x0134); // TM_EN_SR_driver //
	//////	
	//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	//////	// Float SR dvi //
	//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

	//////	// Output 375kHz OSC clock to SR pin. //
	////////	Write_Word(g_TM_SEL, 0x0001, NObin, HEX); // Write the I2C command to connect the 375KHZ signal to SR pin. //
	//////DSM_Write_Word(g_TM_SEL, 0x0001); // Write the I2C command to connect the 375KHZ signal to SR pin. //

	//////	// OSC_Final //
	//////	tmu_6->arm(); 
	//////	wait.delay_10_us(10);
	//////	Period = tmu_6->read();
	//////	OSC_Final = 1/Period;
	//////	if (g_Trim_Enable_P == 1)
	//////		OSC_Act_Chg = ((OSC_Final - g_OSC_Pt_S) / g_OSC_Pt_S)*100; // In percent //

	//////	// Reset test mode registers for next test. //
	////////	Write_Word(g_TM_ANA, 0x0000, NObin, HEX);
	//////DSM_Write_Word(g_TM_ANA, 0x0000);
	////////	Write_Word(g_TM_SEL, 0x0000, NObin, HEX);
	//////DSM_Write_Word(g_TM_SEL, 0x0000);

	//////	// Powerdown //
	//////	//Open_relay(K18);
	//////	//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	//////	Mux20_Open_relay(K42);
	//////	tmu_6->open_relay(TMU_HIZ_DUT4);
	//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	//////	//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	//////	//VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	//////	//FB_ovi->connect(2);
	//////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	//////	//Mux20_Open_relay(K64);
	//////	//ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	//////	//Mux20_Open_relay(K37);
	//////	//Mux20_Open_relay(K38);
	//////	//Mux20_Open_relay(K40);
	//////	//Mux20_Open_relay(K39);
	//////	//ddd_7->ddd_set_clock_period(Dclk_period);
	//////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);

	//////	// DDD level //
	//////	//g_DDD_Low = 0.0; // Save current value //
	//////	//g_DDD_High = 4.0; // Save current value //
	//////	//wait.delay_10_us(100);
	//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//////	//wait.delay_10_us(200); // Wait for relays //

	//////	// Set DSM clock frequency //
	//////	DSM_set_vector_clock_freq(DSM_CONTEXT, 1200); // Freq in kHZ, 1200/4 = 300kHz clock frequency //  // Add I2C DSM //

	//////	// Datalog //
	//////	PiDatalog(func, A_OSC_Final, OSC_Final, 14, POWER_KILO);
	//////	if (g_Trim_Enable_P == 1)
	//////		PiDatalog(func, A_OSC_Act_Chg, OSC_Act_Chg, 14, POWER_UNIT);
	//////	
	//////	// Test Time End //
	//////	//if (g_TstTime_Enble_P)
	//////	//{
	//////	//	g_endtime = g_mytimer.GetElapsedTime();
	//////	//	OSC_Final_TT = (g_endtime - g_begintime)*1e-6;
	//////	//	PiDatalog(func, A_OSC_Final_TT, OSC_Final_TT, 14, POWER_MILLI);
	//////	//}

	//////	// Check any test failed //
	//////	if (PiGetAnyFailStatus())		
	//////	{
	//////		g_PartFailed = 1;
	//////	}
	//////}
}
