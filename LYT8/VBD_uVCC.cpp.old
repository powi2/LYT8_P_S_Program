//==============================================================================
// VBD_uVCC.cpp (User function)
// 
//    void VBD_uVCC_user_init(test_function& func)
//    void VBD_uVCC(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "VBD_uVCC.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VBD_uVCC_user_init(test_function& func)
{
	VBD_uVCC_params *ours;
    ours = (VBD_uVCC_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VBD_uVCC(test_function& func)
{
    // The two lines below must be the first two in the function.
    VBD_uVCC_params *ours;
    ours = (VBD_uVCC_params *)func.params;

	// Increment function number //
	gFuncNum++;

////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_VBD_uVCC, gFuncNum, 21, POWER_UNIT);
////
////	// Skip Test if AbortTest set //
////	if (AbortTest)
////		return;
////
////	if (g_Fn_VBD_uVCC == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	float uVCC_Reset_Result = 0;
////	float V_VBD_Vout5V = 0;
////	float V_VBD_Vo5V_VBPp = 0;
////	//float V_VBD_Vout3V = 0; // Not needed //
////	float V_VBD_Vout24V = 0;
////	float Ruvcc = 0;
////	float tR_VBD = 0;
////	float tF_VBD = 0;
////	float VBD_RDSON = 0;
////	float VBD_OFF = 0;
////	float tWDT = 0;
////	float uVCC = 0;
////	float uVCC_10mA = 0;
////	float I_uVCC = 0;
////	float uVCC_VoutLow = 0;
////	float uVCC_VoutHigh = 0;
////	float uVCC_b = 0;
////	float uVCC_10mA_b = 0;
////	float I_uVCC_b = 0;
////	float uVCC_VoutLow_b = 0;
////	float uVCC_VoutHigh_b = 0;
////	float SCL_interrupt = 0;
////	float uVCC_VBD_short = 0;
////	int DisableVBEN = 0;
////	float VOL = 0;
////	float VBD_uVCC_TT = 0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	int WordArray[16] = {0};
////	int TempArray[30] = {0};
////	int READ6_word[16] = {0};
////	float WordData = 0;
////	//float UpperLimit = 0;
////	//float LowerLimit = 0;
////	float StartLevel = 0;
////	float StopLevel = 0;
////	float VBD_Curr = 0;
////	float StartTimer = 0;
////	float EndTimer = 0;
////	int LoopCnt = 0;
////	float SetVBD = 0.2;
////	float I1_VBD = 0;
////	float I2_VBD = 0;
////	float VBD_curr = 0;
////	float VBDvolt = 0;
////	float VBD_absolute = 0;
////	float uVCC_curr = 0;
////	float uVCC_volt = 0;
////	float uVCC_step = 0;
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	float IuVCC_SetV = 0;
////	float VoutVoltage = 0;
////	float uVCC_Current = 0;
////	float Vout_Current = 0;
////	float istep = 0;
////	int Bld_ON = 0;
////	int Vben_ON = 0;
////	float VBD_tempV = 0;
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
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////	// COMP //
////	FB_ovi->disconnect(2);
////
////	// VBD //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////	wait.delay_10_us(25); // Prevent glitch //
////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////	VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE); // DVI_21_0 //
////	
////	// Connect VBD to TMU_HIZ_4 through unity gain buffer for tR_VBD measurement.  Charge pump does not have enough 
////	// drive current and TMU HIZ alone does not have enough input resistance.  Without buffer, VBD 
////	// voltage will not come up quickly enough and will not rise up to its full value. //
////	tmu_6->close_relay(TMU_HIZ_DUT4); // Connect TMU HIZ //
////	Mux20_Close_relay(K42); // Connect TMU_HIZ_4 to VBD pin. //
////	Mux20_Close_relay(K52); // Connect TMU_HIZ_4 to VBD pin. //
////	Mux20_Close_relay(K45); // VBD to TMU HIZ 4 through unity gain buffer. //
////
////	// uVCC //
////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 3.3; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	//wait.delay_10_us(100);
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
////// Set DSM clock frequency //
////DSM_set_vector_clock_freq(DSM_CONTEXT, 1200); // Freq in kHZ, 1200/4 = 300kHz clock frequency //  // Add I2C DSM //
////		
////	// Wait for relays //
////	wait.delay_10_us(200); 
////
////	// Powerup //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////	// I2C into test mode. //  
////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
////
////	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////	{
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// V_VBD_Vout5V test //
////		// 
////		// VBEN Drive Voltage.  With respect to Vout pin at 5V.  VBPS = gVBPS_M_Init + 50e-3
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Lower VBPS per test plan. //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init + 50e-3, VOLT_10_RANGE); // DVI_9_1 //
////		Mux20_Close_relay(K60); // Connect cap to VBD pin. //
////		wait.delay_10_us(300);
////
////		// Wait upto 5msec for VBD cap to be discharged. //
////		VBD_tempV = 999;
////		LoopCnt = 0;
////		while(VBD_tempV > 0.05 && LoopCnt < 50)
////		{
////			VBD_tempV = VBD_dvi->measure();
////			wait.delay_10_us(10); // 100us //
////			LoopCnt++;
////		}
////		if (VBD_tempV > 0.2) // If VBD cap not discharged below 200mV fail error flag //
////		{
////			g_Error_Flag = -233;
////		}
////
////		// tR_VBD test //
////		StartLevel = 450e-3; // Test condition per design guys 5/1/2017 //
////		StopLevel = 5 + 5; // Test condition per design guys 5/1/2017.  5V above Vout. //
////		tmu_6->start_trigger_setup(StartLevel, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(StopLevel, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		wait.delay_10_us(10);
////		tmu_6->arm();	
////		wait.delay_10_us(10); 
////	//	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////		tR_VBD = tmu_6->read(30e-3);
////		wait.delay_10_us(2000); // Needed, make sure VBD cap is fully charged. //
////		VBD_absolute = VBD_dvi->measure();
////		V_VBD_Vout5V = VBD_absolute - 5; // VBEN Drive Voltage is with respect to Vout pin. //
////
////		// tF_VBD test //
////		// The buffer output does not have fast enough slew rate to test fall 
////		// time. Connect VBD to TMU with 330 resistor. //  
////		Mux20_Open_relay(K45); // VBD to TMU HIZ 4 through 330ohm resistor. //
////		wait.delay_10_us(2000); // Needed, make sure VBD cap is fully charged. //
////		VBDvolt = VBD_dvi->measure();
////
////		StartLevel = 0.9*VBDvolt; // Test condition per design guys 5/1/2017 //
////		StopLevel = 5; // Test condition per design guys 5/1/2017 //
////		tmu_6->start_trigger_setup(StartLevel, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(StopLevel, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
////		wait.delay_10_us(10);
////		tmu_6->arm();	
////		wait.delay_10_us(10); 
////	//	Write_Byte(g_VBEN, 0x80, NObin, HEX); // Turn off VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x80); // Turn off VBD drive //
////		wait.delay_10_us(50);
////		tF_VBD = tmu_6->read();	 
////
////		Mux20_Open_relay(K42); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K52); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K45); // Disconnect TMU_HIZ_4 from VBD pin. //
////		wait.delay_10_us(300);
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// V_VBD_Vo5V_VBPp test //
////		// 
////		// VBEN Drive Voltage.  With respect to Vout pin at 5V.  VBPS = gVBPS_P_Init + 0.05
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Disable watchdog timer //
////	//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////	DSM_Write_Byte(g_Watchdog_Timer, 0x00);
////
////		// Bring VBPS up. //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		
////	//	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////		
////		wait.delay_10_us(2000); // Needed, make sure VBD cap is fully charged. //
////		VBDvolt = VBD_dvi->measure();
////		V_VBD_Vo5V_VBPp = VBDvolt - 5; // VBEN Drive Voltage is with respect to Vout pin. //
////	}
////	else // 4300 //
////	{
////		Mux20_Close_relay(K60); // Connect cap to VBD pin. //
////		Mux20_Open_relay(K42); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K52); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K45); // Disconnect TMU_HIZ_4 from VBD pin. //
////		wait.delay_10_us(300);
////		DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////	}
////
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// V_VBD_Vout24V test //
////	// 
////	// VBEN Drive Voltage.  With respect to Vout pin at 24V.  VBPS = gVBPS_P_Init - 200e-3
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Set CV with I2C //
////	WordData = 37600; // 24V //
//////	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////	wait.delay_10_us(30);
////
////	// Lower VBPS per test plan. //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 // // Changed to VBPS+ -200mV per 10/26/2017 char review meeting per design (Yuri). //
////
////	// VBD dvi range change //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_50_RANGE); // DVI_21_0 //
////
////	// Vout to 24V //	
////	VO_dvi->set_voltage(VO_ch, 24, VOLT_50_RANGE); // DVI_9_0 //
////	wait.delay_10_us(3000); // Needed, make sure VBD cap is fully charged. //
////	VBDvolt = VBD_dvi->measure();
////	V_VBD_Vout24V = VBDvolt - 24; // VBEN Drive Voltage is with respect to Vout pin. //
////
////	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////	{
////		// Vout //
////		VO_dvi->set_voltage(VO_ch, 5, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(50);
////
////	//	Write_Byte(g_VBEN, 0x80, NObin, HEX); // Turn off VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x80); // Turn off VBD drive //
////
////		// Reset CV back to 5V (default). //
////		WordData = 33780;  // 5.0V //
////	//	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////	DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////		wait.delay_10_us(30);
////		
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// VBD_RDSON //
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Bring VBPS back up. //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100);
////
////		// Disable watchdog timer //
////	//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////	DSM_Write_Byte(g_Watchdog_Timer, 0x00);
////
////		// Setup instruments //
////		VBD_dvi->set_voltage(VBD_ch, 1, VOLT_1_RANGE); // DVI_21_0, prevent glitch //
////		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0 //
////		wait.delay_10_us(40); //prevent glitch //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_1_RANGE); // DVI_21_0 //
////		VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //
////		VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_CURRENT); // DVI_21_0 //
////		Mux20_Open_relay(K42); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K52); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K45); // Disconnect TMU_HIZ_4 from VBD pin. //
////		Mux20_Open_relay(K60); // Disconnect cap from VBD pin. //
////		Mux20_Open_relay(K36); // Connect dvi to VBD. //
////		tmu_6->open_relay(TMU_HIZ_DUT4); // Disconnect TMU HIZ //
////		wait.delay_10_us(250);
////		VBD_dvi->set_voltage(VBD_ch, SetVBD, VOLT_1_RANGE); // DVI_21_0 //
////		wait.delay_10_us(50);
////		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0 //
////		wait.delay_10_us(100);
////		VBD_Curr = VBD_dvi->measure_average(10); // Measure VBD current.  Should be no current, load discharge has not been enabled yet. //
////		I1_VBD = VBD_Curr;
////		VBD_OFF = SetVBD / I1_VBD; // Calculate resistance //
////		if (VBD_Curr > 100e-6) // Error.  Load Discharge should be off. //
////			g_Error_Flag = -164;
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////
////	//	Write_Byte(g_VDIS, 0x83, NObin, HEX); // Turn on Load Discharge //
////	DSM_Write_Byte(g_VDIS, 0x83); // Turn on Load Discharge //
////		
////	//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////	DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
////		wait.delay_10_us(50);
////		VBD_Curr = VBD_dvi->measure_average(10);
////		I2_VBD = VBD_Curr;
////		VBD_RDSON = SetVBD / (I2_VBD - I1_VBD); // Calculate rdson //
////		if (VBD_Curr < 0.001) // Error. Load Discharge should be on. //
////			g_Error_Flag = -165;
////
////	//	Write_Byte(g_VDIS, 0x8C, NObin, HEX); // Turn off Load Discharge //
////	DSM_Write_Byte(g_VDIS, 0x8C); // Turn off Load Discharge //
////		
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0 //
////
////		// Characterization only //
////		if (g_Char_Enable_P == 1)
////		{
////			// tWDT.  Test watchdog timer. //
////			// Test the 0.5 default watchdog timer.  First enable the watchdog timer.  
////			// Turn on the VBD drive through I2C (aka the VBUS switch).  Then, monitor how 
////			// long it takes for VBD drive to turn off.  If no I2C commands are sent for the 
////			// watchdog time, then the VBD drive will be disabled. //
////			VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE); // DVI_21_0 //
////	//		Write_Byte(g_Watchdog_Timer, 0x01, NObin, HEX); // Enable watchdog timer //
////		DSM_Write_Byte(g_Watchdog_Timer, 0x01); // Enable watchdog timer //
////
////	//		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////		DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////			
////			StartTimer = g_mytimer.GetElapsedTime();
////			wait.delay_10_us(10);
////			VBDvolt = VBD_dvi->measure();
////			LoopCnt = 0;
////			while(VBDvolt > 5 && LoopCnt < 200000)
////			{
////				VBDvolt = VBD_dvi->measure();
////				wait.delay_10_us(1);
////				LoopCnt++;
////			}
////			EndTimer = g_mytimer.GetElapsedTime();
////			tWDT = (EndTimer - StartTimer) / 1e6;
////		}
////
////		// Disable watchdog timer //
////	//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////	DSM_Write_Byte(g_Watchdog_Timer, 0x00);
////
////		if (g_EE_ShadReg104 == 0) // uVCC = 3.3V //
////		{
////			// uVCC, I_uVCC, uVCC_VoutLow //
////			// 1. Normal power VBPS to VBPS_P + 100mV, VFW = 1V and apply 3.6V on VOUT pin;
////			// 2. Measure the voltage on uVCC pin; (datalog as uVCC)
////			// 3. Draw 10mA out of uVCC pin and measure voltag one uVCC pin (datalog as uVCC_10mA)
////			// 4. Set Vout to 5V. Draw current out of the uVCC pin until the voltage drops to 100mV below uVCC, record the current; (datalog as I_uVCC)
////			// 5. Reduce the voltage on VOUT pin to 3V;
////			// 6. Draw 6mA current out of the uVCC pin, and measure the voltage on uVCC pin (datalog as uVCC_VoutLow)
////			//    With Vout at 3V and 6mA load, the uVCC pin should be greater than or equal to 2.8V.  
////			// 7. Increase the voltage on VOUT pin to 24V;
////			// 8. Draw 10mA current out of the uVCC pin, and measure the voltage on uVCC pin (datalog as uVCC_VoutHigh)
////			//    With Vout at 24V and 10mA load, the uVCC pin should be greater than or equal to 3.2V.  	
////			
////			// Need dvi to supply 50mA current //
////			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////			uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////			Mux20_Close_relay(K41); // Disconnect uVCC from ovi //
////			Close_relay(K22); // Connect uVCC to dvi17_CH1 //
////			wait.delay_10_us(250);
////			//dvi_17->set_voltage(DVI_CHANNEL_1, 0, VOLT_5_RANGE);
////			//dvi_17->set_current(DVI_CHANNEL_1, 0.1e-9, RANGE_30_UA); // Float //
////			//dvi_17->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////			dvi_21->set_voltage(DVI_CHANNEL_1, 0, VOLT_5_RANGE);
////			dvi_21->set_current(DVI_CHANNEL_1, 0.1e-9, RANGE_30_UA); // Float //
////			dvi_21->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////			FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////			VO_dvi->set_voltage(VO_ch, 3.6, VOLT_10_RANGE); // DVI_9_0.  Set to 3.6V per design. //
////			wait.delay_10_us(100);
////			//uVCC = dvi_17->measure();
////			uVCC = dvi_21->measure();
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// uVCC_10mA
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			//dvi_17->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA);
////			//wait.delay_10_us(100);
////			//uVCC_10mA = dvi_17->measure();
////			dvi_21->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA);
////			wait.delay_10_us(100);
////			uVCC_10mA = dvi_21->measure();
////
////			// Binary search for I_uVCC //
////			IuVCC_SetV = uVCC - 0.1; // Threshold is 100mV below uVCC //
////			VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0.  Set to 5V per design. //
////			UpperLimit = (func.dlog->tests[A_I_uVCC].f_max_limit_val[0])*1.2; // Get upper search limit //
////			//LowerLimit = (func.dlog->tests[A_I_uVCC].f_min_limit_val[0])*0.5; // Get lower search limit //
////			LowerLimit = 0; // Get lower search limit //
////			while ( (UpperLimit - LowerLimit) > 250e-6)
////			{
////				uVCC_curr = (UpperLimit + LowerLimit) / 2; 
////				if (uVCC_curr < -300e-3 || uVCC_curr > 300e-3) // Prevent out of range. //
////				{
////					uVCC_curr = 1e-6;
////					g_Error_Flag = -166;
////					break;
////				}
////				//dvi_17->set_current(DVI_CHANNEL_1, uVCC_curr, RANGE_300_MA); // uVCC //
////				//wait.delay_10_us(100);
////				//uVCC_volt = dvi_17->measure_average(5);
////				dvi_21->set_current(DVI_CHANNEL_1, uVCC_curr, RANGE_300_MA); // uVCC //
////				wait.delay_10_us(100);
////				uVCC_volt = dvi_21->measure_average(5);
////				if (uVCC_volt < IuVCC_SetV) // Below threshold //
////					UpperLimit = uVCC_curr;
////				else // Above threshold //
////					LowerLimit = uVCC_curr;		
////			}
////			I_uVCC = uVCC_curr;
////
////			// uVCC_VoutLow //
////			VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0.  Set to 3V. //
////			//dvi_17->set_current(DVI_CHANNEL_1, 6e-3, RANGE_30_MA); // uVCC //
////			//wait.delay_10_us(150);
////			//uVCC_VoutLow = dvi_17->measure_average(5);
////			dvi_21->set_current(DVI_CHANNEL_1, 6e-3, RANGE_30_MA); // uVCC //
////			wait.delay_10_us(150);
////			uVCC_VoutLow = dvi_21->measure_average(5);
////			if (uVCC_VoutLow < 2.8) // Must be higher than 2.8V per design //
////				g_Error_Flag = -154;
////
////			// Set CV with I2C //
////			WordData = 37600; // 24V //
////	//		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////		DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////			wait.delay_10_us(30);
////
////			// uVCC_VoutHigh //
////			VO_dvi->set_voltage(VO_ch, 24, VOLT_50_RANGE); // DVI_9_0.  Set to 24V. //
////			//dvi_17->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA); // uVCC //
////			//wait.delay_10_us(300);
////			//uVCC_VoutHigh = dvi_17->measure_average(5);
////			dvi_21->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA); // uVCC //
////			wait.delay_10_us(300);
////			uVCC_VoutHigh = dvi_21->measure_average(5);
////			if (uVCC_VoutHigh < 3.2) // Must be higher than 3.2V per design //
////				g_Error_Flag = -155;
////
////			// Reset CV back to 5V (default). //
////			WordData = 33780;  // 5.0V //
////	//		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////		DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////			wait.delay_10_us(30);
////		}
////
////		if (g_EE_ShadReg104 == 1) // uVCC = 3.6V //
////		{
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// If uVCC = 3.6V trimmed
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// uVCC, I_uVCC, uVCC_VoutLow //
////			// 1. Normal power VBPS to VBPS_P + 100mV, VFW = 1V and apply 3.9V on VOUT pin;
////			// 2. Measure the voltage on uVCC pin; (datalog as uVCC_b)
////			// 3. Draw 10mA out of uVCC pin and measure voltag one uVCC pin (datalog as uVCC_10mA_b)
////			// 4. Set Vout to 5V. Draw current out of the uVCC pin until the voltage drops to 3.3V, record the current; (datalog as I_uVCC_b)
////			// 5. Reduce the voltage on VOUT pin to 3V;
////			// 6. Draw 6mA current out of the uVCC pin, and measure the voltage on uVCC pin (datalog as uVCC_VoutLow_b)
////			//    With Vout at 3V and 6mA load, the uVCC pin should be greater than or equal to 2.8V.  
////			// 7. Increase the voltage on VOUT pin to 24V;
////			// 8. Draw 10mA current out of the uVCC pin, and measure the voltage on uVCC pin (datalog as uVCC_VoutHigh_b)
////			//    With Vout at 24V and 10mA load, the uVCC pin should be greater than or equal to 3.49V.  	
////			
////			// Need dvi to supply 50mA current //
////			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////			uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////			Mux20_Close_relay(K41); // Disconnect uVCC from ovi //
////			Close_relay(K22); // Connect uVCC to dvi17_CH1 //
////			wait.delay_10_us(250);
////			//dvi_17->set_voltage(DVI_CHANNEL_1, 0, VOLT_5_RANGE);
////			//dvi_17->set_current(DVI_CHANNEL_1, 0.1e-9, RANGE_30_UA); // Float //
////			//dvi_17->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////			dvi_21->set_voltage(DVI_CHANNEL_1, 0, VOLT_5_RANGE);
////			dvi_21->set_current(DVI_CHANNEL_1, 0.1e-9, RANGE_30_UA); // Float //
////			dvi_21->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////			FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////			VO_dvi->set_voltage(VO_ch, 3.9, VOLT_10_RANGE); // DVI_9_0.
////			wait.delay_10_us(100);
////			//uVCC_b = dvi_17->measure();
////			uVCC_b = dvi_21->measure();
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// uVCC_10mA_b
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			//dvi_17->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA);
////			//wait.delay_10_us(100);
////			//uVCC_10mA_b = dvi_17->measure();
////			dvi_21->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA);
////			wait.delay_10_us(100);
////			uVCC_10mA_b = dvi_21->measure();
////
////			// Set Vout //
////			VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //
////
////			// Binary search for I_uVCC //
////			if (uVCC_b < 3.3) // Must be above 3.3V for I_uVCC test. //
////			{
////				g_Error_Flag = -166;
////			}
////			UpperLimit = (func.dlog->tests[A_I_uVCC_b].f_max_limit_val[0])*1.2; // Get upper search limit //
////			LowerLimit = (func.dlog->tests[A_I_uVCC_b].f_min_limit_val[0])*0.8; // Get lower search limit //
////			while ( (UpperLimit - LowerLimit) > 10e-6)
////			{
////				uVCC_curr = (UpperLimit + LowerLimit) / 2; 
////				if (uVCC_curr < -300e-3 || uVCC_curr > 300e-3) // Prevent out of range. //
////				{
////					uVCC_curr = 1e-6;
////					g_Error_Flag = -166;
////					break;
////				}
////				//dvi_17->set_current(DVI_CHANNEL_1, uVCC_curr, RANGE_300_MA); // uVCC //
////				//wait.delay_10_us(100);
////				//uVCC_volt = dvi_17->measure_average(5);
////				dvi_21->set_current(DVI_CHANNEL_1, uVCC_curr, RANGE_300_MA); // uVCC //
////				wait.delay_10_us(150);
////				uVCC_volt = dvi_21->measure_average(5);
////				if (uVCC_volt < 3.3) // Below threshold //
////					UpperLimit = uVCC_curr;
////				else // Above threshold //
////					LowerLimit = uVCC_curr;
////			}
////			I_uVCC_b = uVCC_curr;
////
////			// uVCC_VoutLow //
////			VoutVoltage = 3;
////			uVCC_Current = 6e-3;
////			//dvi_17->set_current(DVI_CHANNEL_1, uVCC_Current, RANGE_300_MA); // uVCC, prevent undershoot //
////			dvi_21->set_current(DVI_CHANNEL_1, uVCC_Current, RANGE_300_MA); // uVCC, prevent undershoot //
////			VO_dvi->set_voltage(VO_ch, VoutVoltage, VOLT_10_RANGE); // DVI_9_0.  Set to 3.3V. //
////			//dvi_17->set_current(DVI_CHANNEL_1, uVCC_Current, RANGE_30_MA); // uVCC //
////			//wait.delay_10_us(150);
////			//uVCC_VoutLow_b = dvi_17->measure_average(5);
////			dvi_21->set_current(DVI_CHANNEL_1, uVCC_Current, RANGE_30_MA); // uVCC //
////			wait.delay_10_us(150);
////			uVCC_VoutLow_b = dvi_21->measure_average(5);
////			if (uVCC_VoutLow_b < 2.8) // Must be higher than 2.8V per design //
////				g_Error_Flag = -154;
////
////			// Ruvcc //
////			Ruvcc = (VoutVoltage - uVCC_VoutLow_b) / uVCC_Current;
////
////			// Set CV with I2C //
////			WordData = 37600; // 24V //
////	//		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////		DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////			wait.delay_10_us(30);
////
////			// uVCC_VoutHigh //
////			VO_dvi->set_voltage(VO_ch, 24, VOLT_50_RANGE); // DVI_9_0.  Set to 24V. //
////			//dvi_17->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA); // uVCC //
////			//wait.delay_10_us(300);
////			//uVCC_VoutHigh_b = dvi_17->measure_average(5);
////			dvi_21->set_current(DVI_CHANNEL_1, 10e-3, RANGE_30_MA); // uVCC //
////			wait.delay_10_us(300);
////			uVCC_VoutHigh_b = dvi_21->measure_average(5);
////			if (uVCC_VoutHigh_b < 3.49) // Must be higher than 3.49V per design //
////				g_Error_Flag = -155;
////
////			// Reset CV back to 5V (default). //
////			WordData = 33780;  // 5.0V //
////	//		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
////		DSM_Write_Word(g_CV_reg, WordData); // Write CV register //
////			wait.delay_10_us(30);
////		}
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// uVCC_Reset
////		// The value of uVCC reset depends on if uVCC is 3.3V or 3.6V for rev. C silicon.  uVCC 3.3V or 
////		// 3.6V is changed with shadow register bit 104.
////		//
////		// Reduce uVCC voltage until I2C disabled.
////		// Use I2C to turn on/off VBD drive voltage; when I2C is disabled VBD drive will no longer 
////		// respond to I2C commands.
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Vout //
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_50_RANGE); // DVI_9_0. //
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT); // DVI_9_0 //
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_50_RANGE); // DVI_21_0, range change //
////		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0 //
////		VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE); // DVI_21_0 //
////
////		// Get uVCC dvi ready, range change, prevent glitch undershoot below ground. //
////		if (g_EE_ShadReg104 == 0) // uVCC = 3.3V //
////		{
////			uVCC_volt = uVCC;
////		}
////		if (g_EE_ShadReg104 == 1) // uVCC = 3.6V //
////		{
////			uVCC_volt = uVCC_b;
////		}
////		uVCC_volt =  uVCC_volt - 0.1;
////		//dvi_17->set_voltage(DVI_CHANNEL_1, uVCC_volt, VOLT_5_RANGE); // uVCC //
////		//dvi_17->set_current(DVI_CHANNEL_1, 10e-3, RANGE_300_MA); // uVCC //
////		//wait.delay_10_us(50);
////		//dvi_17->set_current(DVI_CHANNEL_1, 200e-3, RANGE_300_MA); // uVCC //
////		//wait.delay_10_us(100);
////		dvi_21->set_voltage(DVI_CHANNEL_1, uVCC_volt, VOLT_5_RANGE); // uVCC //
////		dvi_21->set_current(DVI_CHANNEL_1, 10e-3, RANGE_300_MA); // uVCC //
////		wait.delay_10_us(50);
////		dvi_21->set_current(DVI_CHANNEL_1, 200e-3, RANGE_300_MA); // uVCC //
////		wait.delay_10_us(100);
////
////	// For Rev B3 silicon, the uVCC reset value is the same whether or not bit 104 is trimmed. //
////	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
////	{
////		// Get search limits //
////		LowerLimit = (func.dlog->tests[A_uVCC_Reset].f_min_limit_val[0])*0.9;
////		UpperLimit = (func.dlog->tests[A_uVCC_Reset].f_max_limit_val[0])*1.1;
////	}
////
////	// For Rev C silicon, the uVCC reset value is different if bit 104 is trimmed. //
////	if (g_SiliconRev_Sec == 5) // Rev C silicon //
////	{
////		if (g_EE_ShadReg104 == 0) // uVCC = 3.3V //
////		{
////			// Get search limits //
////			LowerLimit = (func.dlog->tests[A_uVCC_Reset].f_min_limit_val[0])*0.9;
////			UpperLimit = (func.dlog->tests[A_uVCC_Reset].f_max_limit_val[0])*1.1;
////		}
////		if (g_EE_ShadReg104 == 1) // uVCC = 3.6V //
////		{
////			// Get search limits //
////			LowerLimit = (func.dlog->tests[A_uVCC_Reset_b].f_min_limit_val[0])*0.9;
////			UpperLimit = (func.dlog->tests[A_uVCC_Reset_b].f_max_limit_val[0])*1.1;
////		}
////	}
////
////		// Reduce uVCC voltage until I2C disabled. //
////		// Use I2C to turn on/off VBD drive voltage; when I2C is disabled VBD drive will no longer respond to I2C commands. //
////		if (UpperLimit > uVCC_volt) // Prevent forcing high voltage to uVCC pin. //
////		{
////			g_Error_Flag = -203;
////			UpperLimit = uVCC_volt;
////		}
////		//dvi_17->set_voltage(DVI_CHANNEL_1, UpperLimit, VOLT_5_RANGE); // uVCC //
////		dvi_21->set_voltage(DVI_CHANNEL_1, UpperLimit, VOLT_5_RANGE); // uVCC //
////		wait.delay_10_us(50);
////		uVCC_step = 0.025;
////		uVCC_volt = UpperLimit + uVCC_step;
////		Vben_ON = 0;
////		while(uVCC_volt > LowerLimit)
////		{
////			uVCC_volt -= uVCC_step;
////			//dvi_17->set_voltage(DVI_CHANNEL_1, uVCC_volt, VOLT_5_RANGE); // uVCC //
////			dvi_21->set_voltage(DVI_CHANNEL_1, uVCC_volt, VOLT_5_RANGE); // uVCC //
////			wait.delay_10_us(20);
////			if(Vben_ON==0)
////			{
////				// Turn on VBD drive //
////	//			Write_Byte(g_VBEN, 0x83, NObin, HEX);
////			DSM_Write_Byte(g_VBEN, 0x83);
////				Vben_ON = 1;
////			}
////			else if(Vben_ON==1)
////			{
////				// Turn off VBD drive //
////	//			Write_Byte(g_VBEN, 0x80, NObin, HEX);
////	//			Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////			DSM_Write_Byte(g_VBEN, 0x80);
////			DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
////				Vben_ON = 0;
////			}
////			VBDvolt = VBD_dvi->measure();
////			if(Vben_ON==1 && VBDvolt < 3)
////				break;
////			if(Vben_ON==0 && VBDvolt > 3)
////				break;
////		}
////		uVCC_Reset_Result = uVCC_volt + (uVCC_step/2);
////
////		// Error //
////		if (g_Error_Flag == -203)
////			uVCC_Reset_Result = -999;
////
////		// Powerdown //
////		Open_relay(K18);
////		Mux20_Open_relay(K41); // Disconnect uVCC from ovi //
////		Open_relay(K22); // Connect uVCC to dvi17_CH1 //
////		FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE);
////		FB_ovi->connect(2);
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		//dvi_17->set_current(DVI_CHANNEL_1, 30e-3, RANGE_30_MA);
////		dvi_21->set_current(DVI_CHANNEL_1, 30e-3, RANGE_30_MA);
////		Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////		Mux20_Open_relay(K37);
////		Mux20_Open_relay(K38);
////		Mux20_Open_relay(K40);
////		Mux20_Open_relay(K39);
////		ddd_7->ddd_set_clock_period(Dclk_period);
////		ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(200); // Wait for relays //
////
////
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// SCL_interrupt and DisableVBEN tests 
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////		// Open all relays //
////		Initialize_Relays();
////
////		// Initialize Instruments //
////		Initialize_Instruments();
////
////		// Drain //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////
////		// BPP //
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////		// V pin //
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////
////		// FW //
////		Close_relay(K18);
////		FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////		FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////
////		// BPS //
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////		// IS //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////		// Vout //
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////		// COMP //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////		wait.delay_10_us(25); // Prevent glitch //
////		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////
////		// uVCC //
////		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 3.3; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(100);
////
////		// SDA //
////		Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////		ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////		Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////		Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////		Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////		Close_relay(K67); // Connect TMU HIZ3 to SCL //
////		tmu_6->close_relay(TMU_HIZ_DUT3); // Connect TMU HIZ //
////		tmu_6->start_trigger_setup(1.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////		tmu_6->stop_trigger_setup(2.0, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
////		tmu_6->start_holdoff(0,FALSE);
////		tmu_6->stop_holdoff(0,FALSE);
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// I2C into test mode. //  
////		//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////		//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// DisableVBEN
////		//
////		// Automatically disable Bus Switch (VBEN) charge pump with discharge command. Functional 
////		// check to make sure VBEN is turned off when discharge commard (VDIS) is enabled.
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////
////		// Make sure VBD drive is on //
////		DisableVBEN = 1; // Initialize //
////		VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE); // DVI_21_0 //
////		wait.delay_10_us(30);
////		VBDvolt = VBD_dvi->measure();
////		if (VBDvolt < 5) // Fail. VBD drive did not turn on. //
////			DisableVBEN = -99;
////
////		// Turn on Load Discharge and make sure VBD drive turns off. //
////		Write_Byte(g_VDIS, 0x83, NObin, HEX); // Turn on Load Discharge //
////		wait.delay_10_us(20);
////		VBDvolt = VBD_dvi->measure();
////		if (VBDvolt > 5) // Fail. VBD drive did not turn off. //
////			DisableVBEN = -99;
////		Write_Byte(g_VDIS, 0x8C, NObin, HEX); // Turn off Load Discharge //
////		wait.delay_10_us(45); // Needed //
////
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// SCL_interrupt
////			//
////			// Check 50usec interrupt fault on SCL pin //
////			// If enabled through customer programmable registerInterrupt_Mask, then fault will 
////			// cause SCL pulldown for 50usec. //
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Enable vout_ov interrupt //
////			Write_Byte(g_Interrupt_Mask, 0x01, NObin, HEX);
////			wait.delay_10_us(10);
////
////			// Disconnect SDA and SCL from DDD. //
////			Mux20_Open_relay(K38);
////			Mux20_Open_relay(K40);
////			wait.delay_10_us(300);
////
////			// Arm tmu //
////			tmu_6->arm();
////			wait.delay_10_us(10);
////
////			// Bring Vout above OVA (6.2V by default) //
////			// Measure SCL pulled down for interrupt time (~50usec). //
////			VO_dvi->set_voltage(VO_ch, 8, VOLT_10_RANGE); // DVI_9_0 //
////			wait.delay_10_us(160);
////			SCL_interrupt = tmu_6->read();
////		}
////
////		// Powerdown //
////		Open_relay(K67); // Disconnect TMU HIZ3 from SCL //
////		tmu_6->open_relay(TMU_HIZ_DUT3); // Disconnect TMU HIZ //
////		//Open_relay(K18);
////		//FB_ovi->connect(2);
////		//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////		//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		//VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE);
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0, get ready for next test. //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		//Mux20_Open_relay(K64);
////		//ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////		Mux20_Open_relay(K37);
////		//Mux20_Open_relay(K38);
////		//Mux20_Open_relay(K40);
////		Mux20_Open_relay(K39);
////		//ddd_7->ddd_set_clock_period(Dclk_period);
////		//ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(200); // Wait for relays //
////
////
////
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// uVCC_VBD_short
////		// uVCC to VBD short detection. If short occurs, should trigger a watchdog reset sequence. 
////		// The uVCC and VBD pins do not need to be shorted to test this fault.  An overvoltage 
////		// comparator was added to uVCC pin with a threshold around 4 or 5V per Johnny.  If 
////		// the uVCC pin is brought above the comparator threshold a watchdog reset will 
////		// occur.  Test by enabling the VBD bleeder then bring uVCC above comparator threshold 
////		// and make sure bleeder turns off due to watchdog reset. This is a go/no go test.
////		//
////		// VOL
////		// Use I2C to drive SDA low.  Force 3mA into SDA pin and measure SDA voltage.
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Open all relays //
////		//Initialize_Relays();
////
////		// Initialize Instruments //
////		//Initialize_Instruments();
////
////		// Drain //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////
////		// BPP //
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////		// V pin //
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////
////		// FW //
////		Close_relay(K18);
////		FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////		FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////
////		// BPS //
////		//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////		// IS //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////		// Vout //
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////		// FB (COMP) //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_CURRENT); // DVI_21_0 //
////
////		// uVCC //
////		uVCC_ovi->set_voltage(uVCC_ch, 2, RANGE_10_V); // OVI_3_2 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 3.3; // Save current value //
////		///wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(100);
////
////		// SDA //
////		SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_5_V); // OVI_3_0 //
////		SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////		Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////		ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////		//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////		SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
////		Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////		Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////		// SCL //
////		SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////		SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////		//Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
////		SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////		// Set DDD for I2C. //
////		//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup //
////		//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// uVCC //
////		uVCC_ovi->set_voltage(uVCC_ch, 3.3, RANGE_10_V); // OVI_3_2 //
////
////	// Disable interrupts [from previous test] //
////	Write_Byte(g_Interrupt_Mask, 0x00, NObin, HEX);
////	wait.delay_10_us(10);
////
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// uVCC_VBD_short
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		Write_Byte(g_VDIS, 131, NObin, HEX); // Turn on VBD bleeder //
////
////		// Make sure VBD bleeder was turned on //
////		VBD_curr = VBD_dvi->measure();
////		if (VBD_curr < 5e-3)
////			g_Error_Flag = -188;
////
////		// Bring up uVCC above comparator threshold //
////		uVCC_ovi->set_voltage(uVCC_ch, 4.6, RANGE_10_V); // OVI_3_2, prevent overshoot //
////		wait.delay_10_us(40);
////		uVCC_ovi->set_voltage(uVCC_ch, 5.1, RANGE_10_V); // OVI_3_2 //
////		wait.delay_10_us(50);
////
////		// Make sure reset occured by checking VBD bleeder turned off. //
////		uVCC_ovi->set_voltage(uVCC_ch, 3.3, RANGE_10_V); // OVI_3_2 //
////		wait.delay_10_us(50);
////		VBD_curr = VBD_dvi->measure();
////		if (VBD_curr < 0.5e-3)
////			uVCC_VBD_short = 1; // Pass //
////		else
////			uVCC_VBD_short = 0; // Fail
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////		wait.delay_10_us(25); // Prevent glitch //
////		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////
////		// uVCC //
////		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////		wait.delay_10_us(100);
////
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VOL
////			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Write a partial command to I2C so the SDA pin is pulled low by the part.
////			// This is not a full Watchdog_Timer command, but is just being used so the
////			// part will pull SDA low.  The I2C data stream is broken right at the point the part is 
////			// sending an ACK signal. //
////			Write_Byte_Part_Pulls_SDA_low(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////			// Hold SDA and SCL low before disconnecting DDD. //
////			SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_5_V); // OVI_3_0 //
////			//SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////			//SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////			//SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////			wait.delay_10_us(30);
////			//Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
////			//Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
////			Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
////			ovi_3->set_current(OVI_CHANNEL_7, 0.1e-9, RANGE_30_UA); // OVI_3_7 //
////			ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////			wait.delay_10_us(200);
////
////			// Force 3mA into SDA and measure SDA voltage //
////			SDA_ovi->set_current(SDA_ch, 3e-3, RANGE_30_MA); // OVI_3_0 //
////			SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_VOLTAGE); // OVI_3_0 //
////			wait.delay_10_us(60);
////			SDA_ovi->set_voltage(SDA_ch, 2, RANGE_5_V); // OVI_3_0 //
////			wait.delay_10_us(90);
////			VOL = SDA_ovi->measure_average(5);
////		}
////		else
////		{
////			SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_5_V); // OVI_3_0 //
////			wait.delay_10_us(30);
////			Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
////			ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////		}
////	}
////	else // 4300 only //
////	{
////		DSM_Write_Byte(g_VBEN, 0x80); // Turn off VBD drive //
////		wait.delay_10_us(30);
////		VO_dvi->set_voltage(VO_ch, 5, VOLT_5_RANGE); // DVI_9_0, reduce undershoot //
////		tmu_6->open_relay(TMU_HIZ_DUT4);
////		SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////		SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1 //
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////		Mux20_Close_relay(K40);
////		VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		wait.delay_10_us(20);
////		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////		SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_VOLTAGE); // OVI_3_0 //
////		Mux20_Open_relay(K64);
////		Mux20_Open_relay(K37);
////		Mux20_Open_relay(K39);
////		Mux20_Open_relay(K60);
////		wait.delay_10_us(200); // Wait for relays //
////	}
////
////	// Powerdown //
////	//Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
////	//Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////	SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V); // OVI_3_0 //
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////	wait.delay_10_us(20);
////	//Open_relay(K18);
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	//uVCCrampDown(0.5, 0, 0.1);
////	VBPS_ramp_down(4, 0, 200e-3);
////	//VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	//VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	//FB_ovi->connect(2);
////	//ddd_7->ddd_set_clock_period(Dclk_period);
////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
////	
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	//wait.delay_10_us(200); // Wait for relays //
////	wait.delay_10_us(100);
////
////	// Datalog //
////	if(!g_EE_ShadReg22) // VBD drive always on if DOPL bits trimmmed. DOPL. bit[22]: trim_dopl //
////	{
////		if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////		{
////			// For Rev B3 silicon, the uVCC reset value is the same whether or not bit 104 is trimmed. //
////			if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
////			{
////				PiDatalog(func, A_uVCC_Reset, uVCC_Reset_Result, 21, POWER_UNIT);
////			}
////
////			// For Rev C silicon, the uVCC reset value is different if bit 104 is trimmed. Use different test limits. //
////			if (g_SiliconRev_Sec == 5) // Rev C silicon //
////			{
////				if (g_EE_ShadReg104 == 0) // uVCC = 3.3V //
////				{
////					PiDatalog(func, A_uVCC_Reset, uVCC_Reset_Result, 21, POWER_UNIT);
////				}
////				if (g_EE_ShadReg104 == 1) // uVCC = 3.6V //
////				{
////					PiDatalog(func, A_uVCC_Reset_b, uVCC_Reset_Result, 21, POWER_UNIT);
////				}
////			}
////		}
////	}
////	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////	{
////		PiDatalog(func, A_V_VBD_Vout5V, V_VBD_Vout5V, 21, POWER_UNIT);
////		PiDatalog(func, A_V_VBD_Vo5V_VBPp, V_VBD_Vo5V_VBPp, 21, POWER_UNIT);
////	}
////	//PiDatalog(func, A_V_VBD_Vout3V, V_VBD_Vout3V, 21, POWER_UNIT); // Not needed //
////	PiDatalog(func, A_V_VBD_Vout24V, V_VBD_Vout24V, 21, POWER_UNIT); // Not needed //
////
////	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////	{
////		if (g_EE_ShadReg104 == 1) // uVCC = 3.6V //
////		{
////			PiDatalog(func, A_Ruvcc, Ruvcc, 21, POWER_UNIT);
////		}
////		if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
////		{
////			if(!g_EE_ShadReg22) // VBD drive always on if DOPL bits trimmmed. DOPL. bit[22]: trim_dopl //
////				PiDatalog(func, A_tR_VBD, tR_VBD, 21, POWER_MILLI);
////			PiDatalog(func, A_tF_VBD, tF_VBD, 21, POWER_MICRO);
////		}
////		PiDatalog(func, A_VBD_RDSON, VBD_RDSON, 21, POWER_UNIT);
////		if(!g_EE_ShadReg22) // VBD drive always on if DOPL bits trimmmed. DOPL. bit[22]: trim_dopl //
////			PiDatalog(func, A_VBD_OFF, VBD_OFF, 21, POWER_KILO);
////		if (g_Char_Enable_P == 1)
////		{
////			PiDatalog(func, A_tWDT, tWDT, 21, POWER_UNIT);
////		}
////		if (g_EE_ShadReg104 == 0)
////		{
////			PiDatalog(func, A_uVCC, uVCC, 21, POWER_UNIT);
////			PiDatalog(func, A_uVCC_10mA, uVCC_10mA, 21, POWER_UNIT);
////			PiDatalog(func, A_I_uVCC, I_uVCC, 21, POWER_MILLI);
////			PiDatalog(func, A_uVCC_VoutLow, uVCC_VoutLow, 21, POWER_UNIT);
////			PiDatalog(func, A_uVCC_VoutHigh, uVCC_VoutHigh, 21, POWER_UNIT);
////		}
////		if (g_EE_ShadReg104 == 1)
////		{
////			PiDatalog(func, A_uVCC_b, uVCC_b, 21, POWER_UNIT);
////			PiDatalog(func, A_uVCC_10mA_b, uVCC_10mA_b, 21, POWER_UNIT);
////			//PiDatalog(func, A_I_uVCC_b, I_uVCC_b, 21, POWER_MILLI); // DEBUG ONLY!!! Change to bin5 for engineering. //
////			PiDatalog(func, A_I_uVCC_b, I_uVCC_b, 5, POWER_MILLI); // DEBUG ONLY!!! Change to bin5 for engineering. //
////			PiDatalog(func, A_uVCC_VoutLow_b, uVCC_VoutLow_b, 21, POWER_UNIT);
////			PiDatalog(func, A_uVCC_VoutHigh_b, uVCC_VoutHigh_b, 21, POWER_UNIT);
////		}
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			PiDatalog(func, A_SCL_interrupt, SCL_interrupt, 21, POWER_MICRO);
////		}
////		PiDatalog(func, A_uVCC_VBD_short, uVCC_VBD_short, 21, POWER_UNIT);
////		PiDatalog(func, A_DisableVBEN, DisableVBEN, 21, POWER_UNIT);
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			PiDatalog(func, A_VOL, VOL, 21, POWER_UNIT);
////		}
////	}
////
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		VBD_uVCC_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_VBD_uVCC_TT, VBD_uVCC_TT, 21, POWER_MILLI);
////	}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
