//==============================================================================
// IsCal_Pt.cpp (User function)
// 
//    void IsCal_Pt_user_init(test_function& func)
//    void IsCal_Pt(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IsCal_Pt.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IsCal_Pt_user_init(test_function& func)
{
	IsCal_Pt_params *ours;
    ours = (IsCal_Pt_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IsCal_Pt(test_function& func)
{
    // The two lines below must be the first two in the function.
    IsCal_Pt_params *ours;
    ours = (IsCal_Pt_params *)func.params;

	// Increment function number //
	gFuncNum++;	

//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_fNum_IsCal_Pt, gFuncNum, 25, POWER_UNIT);
//////
//////	// Skip Test if AbortTest set //
//////	if (AbortTest)
//////		return;
//////
//////	// Skip trimming if g_Sim_Enable_P set //
//////	if (g_Sim_Enable_P == 0)
//////		return;
//////
//////	if (g_Fn_IsCal_Pt == 0 )  return;
//////
//////	// Test Time Begin //
//////	 if (g_TstTime_Enble_P)
//////	 	g_begintime = g_mytimer.GetElapsedTime();
//////
//////	// Test Names //
//////	float IsCal_Target_S = 0.4; // Target range is 300mV to 500mV. //
//////	int IsCal_TrCode_S =0;
//////	int IsCal_BitCode_S =0;
//////	int EEtr_IsCal1_S =0;
//////	int EEtr_IsCal2_S =0;
//////	int EEtr_IsCal3_S =0;
//////	float IsCal_Sim_S =0;
//////	float IsCal_Sim_Chg_S =0;
//////	float IsCal_Pt_TT =0;
//////
//////	// Declare Variables //
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //
//////	int WordArray[16] = {0};
//////	int TempArray[30] = {0};
//////	float UpperLimit = 0;
//////	float LowerLimit = 0;
//////	int ReadWordData[16] = {0};
//////	int ReadByteData[8] = {0};
//////	int CalCode = 0;
//////	float TempVolt = 0;
//////	float TempVoltX[20] = {0};
//////	float TempNum[20] = {0};
//////	float BaseLow[20] = {0};
//////	float BaseHigh[20] = {0};
//////	int Best_TrCode = 0;
//////	int Best_BitCode = 0;
//////	float Best_IsCal = 0;
//////	float Vdelta_High = 0;
//////	float Vdelta_Low = 0;
//////	float MinDiff = 0;
//////	float CalValue = 0;
//////	int High_or_Low = 0;
//////	Pulse pulse;
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////	// Drain //
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////
//////	// FW //
//////	Close_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// BPS //
////////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_1_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
//////	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
////////	g_DDD_Low = 0.0; // Save current value //
////////	g_DDD_High = 3.3; // Save current value //
////////	wait.delay_10_us(100);
////////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////////	wait.delay_10_us(100);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////
//////	// Set DDD for I2C. //
////////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup //
////////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
////////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup if EEPROM has not yet been written. //
//////	LoadShadowRegister();
//////
//////	//Write I2C command to connect output of 40X gain amplifier to FB pin using TM_CTRL (tm_ctrl[12]:tm_isn_afe set to 1).
//////	//Write I2C command to set tm_ctrl[11:8] to '1000'  (design says this will provide cleanest signal on FB pin. )
//////	Write_Word(g_TM_CTRL, 0x1800, NObin, HEX);
//////
//////	// Measure output of 40X gain amplifier.  Value should be around 400mV.  10mV offset source x 10 = 400mV. //
//////	wait.delay_10_us(100);
//////	g_IsCal_Pt_S = FB_ovi->measure_average(50);
//////
//////	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
//////	WordArray[0] = g_ShadowRegister[64];
//////	WordArray[1] = g_ShadowRegister[65];
//////	WordArray[2] = g_ShadowRegister[66];
//////	WordArray[3] = g_ShadowRegister[67];
//////	WordArray[4] = g_ShadowRegister[68];
//////	WordArray[5] = g_ShadowRegister[69];
//////	WordArray[6] = g_ShadowRegister[70];
//////	WordArray[7] = g_ShadowRegister[71];
//////	WordArray[8] = g_ShadowRegister[72];
//////	WordArray[9] = g_ShadowRegister[73];
//////	WordArray[10] = g_ShadowRegister[74];
//////	WordArray[11] = g_ShadowRegister[75];
//////	WordArray[12] = g_ShadowRegister[76];
//////	WordArray[13] = g_ShadowRegister[77]; // EEtr_IsCal1_S //
//////	WordArray[14] = g_ShadowRegister[78]; // EEtr_IsCal2_S //
//////	WordArray[15] = g_ShadowRegister[79]; // EEtr_IsCal3_S //
//////
//////	// If calibration is disabled (SREG3, bit[55]: trim_dis_cali, set to 1) //
//////	if (g_ShadowRegister[55] == 1)
//////	{
//////		// Per design engineering 3/22/2018.  There are two criteria for trimming:
//////		// 1. IsCal final trimmed value must be between 300mV and 500mV.
//////		// 2. IsCal final trimmed value should be as close to a 10mV analog step as possible. For example, trimming to 379mV is 
//////		//     better than trimming to 404mV because 379mV is only 1mV away from 380mV, but 404mV is 4mV away 
//////		//     from 400mV. 
//////		//
//////		// Step through all 8 trim codes to find to best one. //
//////		for (IsCal_TrCode_S = 0; IsCal_TrCode_S < 8; IsCal_TrCode_S++)
//////		{	
//////			// Convert decimal number 'IsCal_TrCode_S' into binary number and store in TempArray[]. //		
//////			Convert_Decimal_To_Binary(IsCal_TrCode_S, TempArray);
//////
//////			// Load TempArray[] to WordArray[] at correct bit locations. //
//////			WordArray[13] = TempArray[0];
//////			WordArray[14] = TempArray[1];
//////			WordArray[15] = TempArray[2]; 
//////
//////			// Load new trim code to shadow register. //
//////			Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
//////			wait.delay_10_us(150);
//////
//////			// Measure output of 40X gain amplifier //
//////			TempVoltX[IsCal_TrCode_S] = FB_ovi->measure_average(10);
//////			TempVoltX[IsCal_TrCode_S] *= 1000; // Change scale //
//////		}
//////		
//////		// Find best code //
//////		Best_TrCode = 999;
//////		Vdelta_High = 0;
//////		Vdelta_Low = 0;
//////		MinDiff = 999;
//////		for (IsCal_TrCode_S = 0; IsCal_TrCode_S < 8; IsCal_TrCode_S++)
//////		{
//////			// Convert BitCode to TrCode. Mapping between bit code and trim code. //
//////			if(IsCal_TrCode_S == 3) IsCal_BitCode_S = -3;
//////			if(IsCal_TrCode_S == 2) IsCal_BitCode_S = -2;
//////			if(IsCal_TrCode_S == 1) IsCal_BitCode_S = -1;
//////			if(IsCal_TrCode_S == 0) IsCal_BitCode_S = 0;
//////			if(IsCal_TrCode_S == 7) IsCal_BitCode_S = 1;
//////			if(IsCal_TrCode_S == 6) IsCal_BitCode_S = 2;
//////			if(IsCal_TrCode_S == 5) IsCal_BitCode_S = 3;
//////			if(IsCal_TrCode_S == 4) IsCal_BitCode_S = 4;
//////
//////			// IsCal must be between 300mV and 500mV per design. //
//////			if(TempVoltX[IsCal_TrCode_S] > 300 && TempVoltX[IsCal_TrCode_S] < 500)
//////			{
//////				TempNum[IsCal_TrCode_S] = (int)TempVoltX[IsCal_TrCode_S] / 10;
//////				BaseLow[IsCal_TrCode_S] = TempNum[IsCal_TrCode_S] * 10;
//////				BaseHigh[IsCal_TrCode_S] = (TempNum[IsCal_TrCode_S] * 10) + 10;
//////				Vdelta_High = BaseHigh[IsCal_TrCode_S] - TempVoltX[IsCal_TrCode_S];
//////				Vdelta_Low = TempVoltX[IsCal_TrCode_S] - BaseLow[IsCal_TrCode_S];
//////				if(Vdelta_High < MinDiff)
//////				{
//////					MinDiff = Vdelta_High;
//////					Best_TrCode = IsCal_TrCode_S;
//////					Best_BitCode = IsCal_BitCode_S;
//////					Best_IsCal = TempVoltX[IsCal_TrCode_S] / 1000;
//////					High_or_Low = 1;
//////				}
//////				if(Vdelta_Low < MinDiff)
//////				{
//////					MinDiff = Vdelta_Low;
//////					Best_TrCode = IsCal_TrCode_S;
//////					Best_BitCode = IsCal_BitCode_S;
//////					Best_IsCal = TempVoltX[IsCal_TrCode_S] / 1000;
//////					High_or_Low = 0;
//////				}
//////			}
//////		}
//////		IsCal_TrCode_S = Best_TrCode;
//////		IsCal_BitCode_S = Best_BitCode;
//////		IsCal_Sim_S = Best_IsCal;
//////		IsCal_Sim_Chg_S = IsCal_Sim_S - g_IsCal_Pt_S;
//////
//////		// Be sure can trim IsCal between 300mV and 500mV. //
//////		if (Best_TrCode == 999)
//////		{
//////			g_IsCal_Pt_S = -999;
//////			IsCal_Sim_S = -999;
//////			g_Error_Flag = -214; // Error //
//////			AbortTest = true;
//////		}
//////
//////		// Load the shadow register with the final trim code IsCal_TrCode_S.  Must not overwrite any of the other shadow register bits! //	
//////		Convert_Decimal_To_Binary(IsCal_TrCode_S, TempArray); // Convert decimal number 'IsCal_TrCode_S' into binary number and store in TempArray[]. // 
//////		
//////		// Load TempArray[] to WordArray[] at correct bit locations. //
//////		WordArray[13] = TempArray[0]; 
//////		WordArray[14] = TempArray[1]; 
//////		WordArray[15] = TempArray[2]; 
//////
//////		// Load final trim code to shadow register. //
//////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
//////
//////		// Save the new values to the g_ShadowRegister[] array. //
//////		g_ShadowRegister[77] = WordArray[13];
//////		g_ShadowRegister[78] = WordArray[14];
//////		g_ShadowRegister[79] = WordArray[15];
//////
//////		// Load individual bits for datalogging //
//////		EEtr_IsCal1_S = WordArray[13];
//////		EEtr_IsCal2_S = WordArray[14];
//////		EEtr_IsCal3_S = WordArray[15];
//////
//////		// Set the calibration bits in shadow register (SREG5, trim_cali_ofst[5:0]) //
//////		if (High_or_Low == 1) // Use the nearest high DAC value //
//////		{
//////			CalValue = BaseHigh[IsCal_TrCode_S];
//////		}
//////		if (High_or_Low == 0) // Use the nearest low DAC value //
//////		{
//////			CalValue = BaseLow[IsCal_TrCode_S];
//////		}
//////		CalValue /= 10;
//////		Convert_Decimal_To_Binary(CalValue, TempArray); // Convert decimal number 'IsCal_TrCode_S' into binary number and store in TempArray[]. //
//////		g_ShadowRegister[90] = TempArray[0]; // trim_cali_ofst[0] //
//////		g_ShadowRegister[91] = TempArray[1]; // trim_cali_ofst[1] //
//////		g_ShadowRegister[92] = TempArray[2]; // trim_cali_ofst[2] //
//////		g_ShadowRegister[93] = TempArray[3]; // trim_cali_ofst[3] //
//////		g_ShadowRegister[94] = TempArray[4]; // trim_cali_ofst[4] //
//////		g_ShadowRegister[95] = TempArray[5]; // trim_cali_ofst[5] //
//////	}
//////
//////	// If calibration is enabled (SREG3, bit[55]: trim_dis_cali, set to 0) //
//////	if (g_ShadowRegister[55] == 0)
//////	{
//////		// Per design engineering.  IsCal only needs to be within the target range. The target range is 300mV to 500mV.  
//////		// Only need to trim if g_IsCal_Pt_S is less than 300mV or greater than 500mV.  //
//////		if (g_IsCal_Pt_S < 0.300 || g_IsCal_Pt_S > 0.495)  // Trim if outside range. //
//////		{
//////			// Find trim code closest to target. //
//////			UpperLimit = 5;
//////			LowerLimit = -4; 	
//////			while ( (UpperLimit - LowerLimit) > 1)
//////			{
//////				IsCal_BitCode_S = (UpperLimit + LowerLimit) / 2;
//////
//////				// Convert BitCode to TrCode. Mapping between bit code and trim code. //
//////				if(IsCal_BitCode_S == -3) IsCal_TrCode_S = 3;
//////				if(IsCal_BitCode_S == -2) IsCal_TrCode_S = 2;
//////				if(IsCal_BitCode_S == -1) IsCal_TrCode_S = 1;
//////				if(IsCal_BitCode_S == 0) IsCal_TrCode_S = 0;
//////				if(IsCal_BitCode_S == 1) IsCal_TrCode_S = 7;
//////				if(IsCal_BitCode_S == 2) IsCal_TrCode_S = 6;
//////				if(IsCal_BitCode_S == 3) IsCal_TrCode_S = 5;
//////				if(IsCal_BitCode_S == 4) IsCal_TrCode_S = 4;
//////			
//////				// Convert decimal number 'IsCal_TrCode_S' into binary number and store in TempArray[]. //		
//////				Convert_Decimal_To_Binary(IsCal_TrCode_S, TempArray);
//////
//////				// Load TempArray[] to WordArray[] at correct bit locations. //
//////				WordArray[13] = TempArray[0];
//////				WordArray[14] = TempArray[1];
//////				WordArray[15] = TempArray[2]; 
//////
//////				// Load new trim code to shadow register. //
//////				Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
//////				wait.delay_10_us(100);
//////
//////				// Check if the ISNS calibration is above or below the target. //
//////				// Measure output of 40X gain amplifier //
//////				TempVolt = FB_ovi->measure();
//////
//////				// Check if TempVolt is above or below the target. //
//////				if (TempVolt > IsCal_Target_S) // Below target //
//////					LowerLimit = IsCal_BitCode_S;
//////				else // Above target //
//////					UpperLimit = IsCal_BitCode_S;		
//////			}
//////
//////			// Load the shadow register with the final trim code IsCal_TrCode_S.  Must not overwrite any of the other shadow register bits! //	
//////			Convert_Decimal_To_Binary(IsCal_TrCode_S, TempArray); // Convert decimal number 'IsCal_TrCode_S' into binary number and store in TempArray[]. // 
//////			
//////			// Load TempArray[] to WordArray[] at correct bit locations. //
//////			WordArray[13] = TempArray[0]; 
//////			WordArray[14] = TempArray[1]; 
//////			WordArray[15] = TempArray[2]; 
//////
//////			// Load final trim code to shadow register. //
//////			Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
//////
//////			// Save the new values to the g_ShadowRegister[] array. //
//////			g_ShadowRegister[77] = WordArray[13];
//////			g_ShadowRegister[78] = WordArray[14];
//////			g_ShadowRegister[79] = WordArray[15];
//////
//////			// Load individual bits for datalogging //
//////			EEtr_IsCal1_S = WordArray[13];
//////			EEtr_IsCal2_S = WordArray[14];
//////			EEtr_IsCal3_S = WordArray[15];
//////
//////			// Measure the final value after shadow register is loaded with final trim code. //
//////			wait.delay_10_us(100);
//////			IsCal_Sim_S = FB_ovi->measure();
//////			IsCal_Sim_Chg_S = IsCal_Sim_S - g_IsCal_Pt_S;
//////		}
//////	}
//////
//////	// Powerdown //
//////	//Open_relay(K2);
////////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_voltage(SR_ch, 1, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	wait.delay_10_us(45); // prevent SR undershoot //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////////	Open_relay(K18);
////////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	Mux20_Open_relay(K64);
////////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////////	Mux20_Open_relay(K37);
////////	Mux20_Open_relay(K38);
////////	Mux20_Open_relay(K40);
////////	Mux20_Open_relay(K39);  // Disconnect ovi from SCL. //
//////	Mux20_Open_relay(K50); // Open SR pin hard short to GND with relay //
////////	ddd_7->ddd_set_clock_period(Dclk_period);
////////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
////////	g_DDD_Low = 0.0; // Save current value //
////////	g_DDD_High = 4.0; // Save current value //
////////	wait.delay_10_us(100);
////////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////	// Datalog //
//////	PiDatalog(func, A_IsCal_Pt_S, g_IsCal_Pt_S, 25, POWER_MILLI);
//////	
//////	// Per design engineering.  IsCal only needs to be within the target range. The target range is 30 to 50.  
//////	// Only need to trim if g_IsCal_Pt_S is less than 300mV or greater than 500mV.  //
//////	if (g_IsCal_Pt_S < 0.300 || g_IsCal_Pt_S > 0.500)  // Trim if outside range. //
//////	{
//////		PiDatalog(func, A_IsCal_Target_S, IsCal_Target_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_IsCal_TrCode_S, IsCal_TrCode_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_IsCal_BitCode_S, IsCal_BitCode_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_EEtr_IsCal1_S, EEtr_IsCal1_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_EEtr_IsCal2_S, EEtr_IsCal2_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_EEtr_IsCal3_S, EEtr_IsCal3_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_IsCal_Sim_S, IsCal_Sim_S, 25, POWER_UNIT);
//////		PiDatalog(func, A_IsCal_Sim_Chg_S, IsCal_Sim_Chg_S, 25, POWER_UNIT);
//////	}
//////
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		IsCal_Pt_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_IsCal_Pt_TT, IsCal_Pt_TT, 25, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
