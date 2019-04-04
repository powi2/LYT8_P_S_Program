//==============================================================================
// DofA_Final.cpp (User function)
// 
//    void DofA_Final_user_init(test_function& func)
//    void DofA_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "DofA_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void DofA_Final_user_init(test_function& func)
{
	DofA_Final_params *ours;
    ours = (DofA_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void DofA_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    DofA_Final_params *ours;
    ours = (DofA_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_DofA_Final, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_DofA_Final == 0 )  return;

	// Test Time Begin //
	// if (g_TstTime_Enble_P)
	// 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float DofA_final = 0;
	float DofA_TrCode0 = 0;
	float DofA_TrCode1 = 0;
	float DofA_TrCode2 = 0;
	float DofA_TrCode4 = 0;
	float DofA_TrCode8 = 0;
	float DofA_TrCode16 = 0;
	float DofA_TrCode31 = 0;
	float DofA_Act_Chg = 0;
	float DofA_final_TT = 0;
	
	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	float COMPpinVolt = 0;
	int READ59_word[16] = {0};
	int TempArray[30] = {0};

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// Open all relays //
		//Initialize_Relays();

		// Initialize Instruments //
		//Initialize_Instruments();

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
		SR_dvi2k->set_current(SR_ch, 200.0e-3, RANGE_200_MA); // DVI_13_1, dvi2k //

		// BPS //
		//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

		// IS //
		FB_ovi->disconnect(2); // Remove OVI from FB and use DVI2K instead for better accuracy. //
		Mux20_Close_relay(K46); // Connect DVI 2k to COMP pin intead of IS pin. //
		Mux20_Close_relay(K48); // Connect IS pin to ovi. //
		IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_10_V); // OVI_3_4 //
		IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //

		// Vout //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //

		// COMP //
		Mux20_Close_relay(K55); // FB (COMP) pin to input of OP07 buffer.  Needed because the internal DAC 
								// ouput resistor is 80kohm, so the input impedance of the measure 
								// instrument needs to be 8Megohm just to get 1% accuracy. //
		Mux20_Close_relay(K56); // Output of OP07 buffer to DVI_13_0, dvi2k //
		dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		dvi_13->set_current(DVI_CHANNEL_0, 0.1e-9, RANGE_20_UA); // DVI_13_0, dvi2k, float //
		dvi_13->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_VOLTAGE); // DVI_13_0, dvi2k // 

		// VBD //
		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
		//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
		//wait.delay_10_us(25); // Prevent glitch //
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
		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

		// Set DDD for I2C. //
		//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
		//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
			
		// Wait for relays //
		wait.delay_10_us(200); 

		// Powerup //
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

		// I2C into test mode. //  
		//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
		//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

		// Write the I2C command to connect the 8-Bit DAC output voltage of the ADC to FB (COMP) pin. //
	//	Write_Word(g_TM_CTRL, 0x0001, NObin, HEX); //  Write the I2C command to connect the 8-Bit DAC output voltage of the ADC to FB (COMP) pin. //
	DSM_Write_Word(g_TM_CTRL, 0x0001); //  Write the I2C command to connect the 8-Bit DAC output voltage of the ADC to FB (COMP) pin. //	


		// Write the I2C command to set the DAC value to be 8'b10000000. //
	//	Write_Byte(g_TM_DAC, 0x80, NObin, HEX);
	DSM_Write_Byte(g_TM_DAC, 0x80);

		// DofA_Final.  Measure voltage on FB (COMP) pin. //
		wait.delay_10_us(100);	
		DofA_final = dvi_13->measure_average(10); // DVI_13_0, dvi2k //
		if (g_Sim_Enable_P == 1)
			DofA_Act_Chg = ((DofA_final - g_DofA_Pt_S) / g_DofA_Pt_S)*100; // In percent //

		if (g_Char_Enable_P) // Characterization only //
		{
	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
	wait.delay_10_us(300); // Add I2C DSM //		
			
			// Load WordArray[] with contents of shadow register array!  Must not overwrite shadow register! //
			Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
			Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
			
			// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
			WordArray[0] = READ59_word[0];
			WordArray[1] = READ59_word[1];
			WordArray[2] = READ59_word[2];
			WordArray[3] = READ59_word[3];
			WordArray[4] = READ59_word[4];
			WordArray[5] = READ59_word[5];
			WordArray[6] = READ59_word[6];
			WordArray[7] = READ59_word[7];
			WordArray[8] = READ59_word[8]; // EEtr_DofA1_S //
			WordArray[9] = READ59_word[9]; // EEtr_DofA2_S //
			WordArray[10] = READ59_word[10]; // EEtr_DofA3_S //
			WordArray[11] = READ59_word[11]; // EEtr_DofA4_S //
			WordArray[12] = READ59_word[12]; // EEtr_DofA5_S //
			WordArray[13] = READ59_word[13];
			WordArray[14] = READ59_word[14];
			WordArray[15] = READ59_word[15];

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode0
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(0, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode0 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode1
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(1, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode1 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode2
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(2, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode2 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode4
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(4, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode4 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode8
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(8, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode8 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode16
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(16, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode16 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// DofA_TrCode31
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Convert decimal number 'DofA_TrCode_S' into binary number and store in TempArray[]. //		
			Convert_Decimal_To_Binary(31, TempArray);

			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = TempArray[0];
			WordArray[9] = TempArray[1]; 
			WordArray[10] = TempArray[2]; 
			WordArray[11] = TempArray[3]; 
			WordArray[12] = TempArray[4]; 

			// Load new trim code to shadow register. //
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

			// Measure voltage on FB (COMP) pin. //
			wait.delay_10_us(150);	
			DofA_TrCode31 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Reload original trim code to shadow register //
			// Load READ59_word[] to WordArray[] at correct bit locations. //
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Load TempArray[] to WordArray[] at correct bit locations. //
			WordArray[8] = READ59_word[8];
			WordArray[9] = READ59_word[9]; 
			WordArray[10] = READ59_word[10]; 
			WordArray[11] = READ59_word[11]; 
			WordArray[12] = READ59_word[12]; 
			Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //
		}

		// Powerdown //
		//Open_relay(K2);
		//Mux20_Open_relay(K55);
		//Mux20_Open_relay(K56);
		//dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		//dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k, float //
		//Open_relay(K18);
		//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
		//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
		//Mux20_Open_relay(K48); // Disconnect IS pin from ovi. //
		//Mux20_Open_relay(K46); // Connect DVI 2k to IS pin. //
		//FB_ovi->connect(2);
		//VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
		//dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		//dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
		//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
		//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		//Mux20_Open_relay(K64);
		//ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
		//Mux20_Open_relay(K37);
		//Mux20_Open_relay(K38);
		//Mux20_Open_relay(K40);
		//Mux20_Open_relay(K39);
		//Mux20_Open_relay(K50);
		//ddd_7->ddd_set_clock_period(Dclk_period);
		//ddd_7->ddd_set_voltage_ref(DDD_Vref);

		// DDD level //
		//g_DDD_Low = 0.0; // Save current value //
		//g_DDD_High = 4.0; // Save current value //
		//wait.delay_10_us(100);
		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		//wait.delay_10_us(200); // Wait for relays //

		// Datalog //
		PiDatalog(func, A_DofA_final, DofA_final, 25, POWER_UNIT);
		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_DofA_TrCode0, DofA_TrCode0, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode1, DofA_TrCode1, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode2, DofA_TrCode2, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode4, DofA_TrCode4, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode8, DofA_TrCode8, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode16, DofA_TrCode16, 25, POWER_UNIT);
			PiDatalog(func, A_DofA_TrCode31, DofA_TrCode31, 25, POWER_UNIT);
		}
		if (g_Sim_Enable_P == 1)
			PiDatalog(func, A_DofA_Act_Chg, DofA_Act_Chg, 25, POWER_UNIT);

		// Test Time End //
		//if (g_TstTime_Enble_P)
		//{
		//	g_endtime = g_mytimer.GetElapsedTime();
		//	DofA_Pt_TT = (g_endtime - g_begintime)*1e-6;
		//	PiDatalog(func, A_DofA_final_TT, DofA_final_TT, 25, POWER_MILLI);
		//}

		// Check any test failed //
		if (PiGetAnyFailStatus())		
		{
			g_PartFailed = 1;
		}
	}
*/
}
