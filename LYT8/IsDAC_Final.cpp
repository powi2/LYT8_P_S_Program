//==============================================================================
// IsDAC_Final.cpp (User function)
// 
//    void IsDAC_Final_user_init(test_function& func)
//    void IsDAC_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IsDAC_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IsDAC_Final_user_init(test_function& func)
{
	IsDAC_Final_params *ours;
    ours = (IsDAC_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IsDAC_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    IsDAC_Final_params *ours;
    ours = (IsDAC_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	////// Datalog gFuncNum variable //
	////if(gDisplay_FuncNum)
	////	PiDatalog(func, A_fNum_IsDACfinal, gFuncNum, 25, POWER_UNIT);

	////// Skip Test if AbortTest set //
	////if (AbortTest)
	////	return;

	////if (g_Fn_IsDAC_Final == 0 )  return;

	////// Test Time Begin //
	////// if (g_TstTime_Enble_P)
	////// 	g_begintime = g_mytimer.GetElapsedTime();

	////// Test Names //
	//////float IsDAC_final = 0;
	////float IsDAC_TrCode0 = 0;
	////float IsDAC_TrCode1 = 0;
	////float IsDAC_TrCode2 = 0;
	////float IsDAC_TrCode4 = 0;
	////float IsDAC_TrCode8 = 0;
	////float IsDAC_TrCode16 = 0;
	////float IsDAC_TrCode31 = 0;
	////float IsDAC_Act_Chg = 0;
	////float IsDAC_final_TT =0;

	////// Declare Variables //
	////int NObin[1] = {0}; // Place holder //
	////int NOhex = 0; // Place holder //
	////int WordArray[16] = {0};
	////float UpperLimit = 0;
	////float LowerLimit = 0;
	////float COMPpinVolt = 0;
	////int READ60_word[16] = {0};
	////int TempArray[30] = {0};

	////if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	////{
	////	// Open all relays //
	////	//Initialize_Relays();

	////	// Initialize Instruments //
	////	//Initialize_Instruments();

	////	// Drain //
	////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	////	// BPP //
	////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	////	// V pin //
	////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	////	// FW //
	////	Close_relay(K18);
	////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	////	// SR //
	////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	////	// BPS //
	////	//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	////	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	////	// IS //
	////	FB_ovi->disconnect(2); // Remove OVI from FB and use DVI2K instead for better accuracy. //
	////	Mux20_Close_relay(K46); // Connect DVI 2k to COMP pin intead of IS pin. //
	////	Mux20_Close_relay(K48); // Connect IS pin to ovi. //
	////	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_10_V); // OVI_3_4 //
	////	IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //

	////	// Vout //
	////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //

	////	// FB (COMP) //
	////	Mux20_Close_relay(K55); // FB (COMP) pin to input of OP07 buffer.  Needed because the internal DAC 
	////							// ouput resistor is 80kohm, so the input impedance of the measure 
	////							// instrument needs to be 8Megohm just to get 1% accuracy. //
	////	Mux20_Close_relay(K56); // Output of OP07 buffer to DVI_13_0, dvi2k //
	////	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
	////	dvi_13->set_current(DVI_CHANNEL_0, 0.1e-9, RANGE_20_UA); // DVI_13_0, dvi2k, float //
	////	dvi_13->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_VOLTAGE); // DVI_13_0, dvi2k // 

	////	// VBD //
	////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	////	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	////	//wait.delay_10_us(25); // Prevent glitch //
	////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	////	// uVCC //
	////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	////	// DDD level //	
	////	//g_DDD_Low = 0.0; // Save current value //
	////	//g_DDD_High = 3.3; // Save current value //
	////	//wait.delay_10_us(100);
	////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	////	//wait.delay_10_us(100);

	////	// SDA //
	////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	////	// SCL //
	////	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
	////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	////	
	////	// Set DDD for I2C. //
	////	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	////	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
	////		
	////	// Wait for relays //
	////	wait.delay_10_us(300); 
	////	
	////	// Powerup //
	////	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	////	//wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	////	// I2C into test mode. //  
	////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	////	// Load the DUTs shadow register to the g_ShadowRegister[] array.  
	////	//ReadShadowRegister();

	////	// Disable the Cal Bit in shadow register (SREG3, bit[55]: trim_dis_cali, set to 1.
	////	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	////	/*
	////	WordArray[0] = g_ShadowRegister[48];
	////	WordArray[1] = g_ShadowRegister[49];
	////	WordArray[2] = g_ShadowRegister[50];
	////	WordArray[3] = g_ShadowRegister[51];
	////	WordArray[4] = g_ShadowRegister[52];
	////	WordArray[5] = g_ShadowRegister[53];
	////	WordArray[6] = g_ShadowRegister[54];
	////	WordArray[7] = g_ShadowRegister[55]; //  bit[55]: trim_dis_cali //
	////	WordArray[8] = g_ShadowRegister[56];
	////	WordArray[9] = g_ShadowRegister[57];
	////	WordArray[10] = g_ShadowRegister[58];
	////	WordArray[11] = g_ShadowRegister[59];
	////	WordArray[12] = g_ShadowRegister[60];
	////	WordArray[13] = g_ShadowRegister[61];
	////	WordArray[14] = g_ShadowRegister[62];
	////	WordArray[15] = g_ShadowRegister[63];
	////	*/
	////	WordArray[0] = g_EE_ShadReg48;
	////	WordArray[1] = g_EE_ShadReg49;
	////	WordArray[2] = g_EE_ShadReg50;
	////	WordArray[3] = g_EE_ShadReg51;
	////	WordArray[4] = g_EE_ShadReg52;
	////	WordArray[5] = g_EE_ShadReg53;
	////	WordArray[6] = g_EE_ShadReg54;
	////	WordArray[7] = g_EE_ShadReg55; //  bit[55]: trim_dis_cali //
	////	WordArray[8] = g_EE_ShadReg56;
	////	WordArray[9] = g_EE_ShadReg57;
	////	WordArray[10] = g_EE_ShadReg58;
	////	WordArray[11] = g_EE_ShadReg59;
	////	WordArray[12] = g_EE_ShadReg60;
	////	WordArray[13] = g_EE_ShadReg61;
	////	WordArray[14] = g_EE_ShadReg62;
	////	WordArray[15] = g_EE_ShadReg63;

	////	// (SREG3, bit[55]: trim_dis_cali, set to 1.) //
	////	WordArray[7] = 1; // bit[55]: trim_dis_cali, set to 1. //
	////	Write_Word(g_SREG3, NOhex, WordArray, BIN); // bit[55]: trim_dis_cali, set to 1. //

	////	// Disable CC comparator offset trim in shadow register (SREG4, bit[71:69]: trim_comp_cc , set to 0.)
	////	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	////	/*
	////	WordArray[0] = g_ShadowRegister[64];
	////	WordArray[1] = g_ShadowRegister[65];
	////	WordArray[2] = g_ShadowRegister[66];
	////	WordArray[3] = g_ShadowRegister[67];
	////	WordArray[4] = g_ShadowRegister[68];
	////	WordArray[5] = g_ShadowRegister[69];
	////	WordArray[6] = g_ShadowRegister[70];
	////	WordArray[7] = g_ShadowRegister[71];
	////	WordArray[8] = g_ShadowRegister[72];
	////	WordArray[9] = g_ShadowRegister[73];
	////	WordArray[10] = g_ShadowRegister[74];
	////	WordArray[11] = g_ShadowRegister[75];
	////	WordArray[12] = g_ShadowRegister[76];
	////	WordArray[13] = g_ShadowRegister[77];
	////	WordArray[14] = g_ShadowRegister[78];
	////	WordArray[15] = g_ShadowRegister[79];
	////	*/
	////	WordArray[0] = g_EE_ShadReg64;
	////	WordArray[1] = g_EE_ShadReg65;
	////	WordArray[2] = g_EE_ShadReg66;
	////	WordArray[3] = g_EE_ShadReg67;
	////	WordArray[4] = g_EE_ShadReg68;
	////	WordArray[5] = g_EE_ShadReg69;
	////	WordArray[6] = g_EE_ShadReg70;
	////	WordArray[7] = g_EE_ShadReg71;
	////	WordArray[8] = g_EE_ShadReg72;
	////	WordArray[9] = g_EE_ShadReg73;
	////	WordArray[10] = g_EE_ShadReg74;
	////	WordArray[11] = g_EE_ShadReg75;
	////	WordArray[12] = g_EE_ShadReg76;
	////	WordArray[13] = g_EE_ShadReg77;
	////	WordArray[14] = g_EE_ShadReg78;
	////	WordArray[15] = g_EE_ShadReg79;

	////	// (SREG4, bit[71:69]: trim_comp_cc , set to 0.)//
	////	WordArray[5] = 0;
	////	WordArray[6] = 0;
	////	WordArray[7] = 0;	
	////	Write_Word(g_SREG4, NOhex, WordArray, BIN); // SREG4, bit[71:69]: trim_comp_cc , set to 0.)//

	////	// Set the calibration bits to zero in shadow register (SREG5, trim_cali_ofst[5:0], set to all zeros)
	////	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	////	/*
	////	WordArray[0] = g_ShadowRegister[80];
	////	WordArray[1] = g_ShadowRegister[81];
	////	WordArray[2] = g_ShadowRegister[82];
	////	WordArray[3] = g_ShadowRegister[83];
	////	WordArray[4] = g_ShadowRegister[84];
	////	WordArray[5] = g_ShadowRegister[85];
	////	WordArray[6] = g_ShadowRegister[86];
	////	WordArray[7] = g_ShadowRegister[87];
	////	WordArray[8] = g_ShadowRegister[88];
	////	WordArray[9] = g_ShadowRegister[89];
	////	WordArray[10] = g_ShadowRegister[90]; // trim_cali_ofst[0] //
	////	WordArray[11] = g_ShadowRegister[91]; // trim_cali_ofst[1] //
	////	WordArray[12] = g_ShadowRegister[92]; // trim_cali_ofst[2] //
	////	WordArray[13] = g_ShadowRegister[93]; // trim_cali_ofst[3] //
	////	WordArray[14] = g_ShadowRegister[94]; // trim_cali_ofst[4] //
	////	WordArray[15] = g_ShadowRegister[95]; // trim_cali_ofst[5] //
	////	*/
	////	WordArray[0] = g_EE_ShadReg80;
	////	WordArray[1] = g_EE_ShadReg81;
	////	WordArray[2] = g_EE_ShadReg82;
	////	WordArray[3] = g_EE_ShadReg83;
	////	WordArray[4] = g_EE_ShadReg84;
	////	WordArray[5] = g_EE_ShadReg85;
	////	WordArray[6] = g_EE_ShadReg86;
	////	WordArray[7] = g_EE_ShadReg87;
	////	WordArray[8] = g_EE_ShadReg88;
	////	WordArray[9] = g_EE_ShadReg89;
	////	WordArray[10] = g_EE_ShadReg90; // trim_cali_ofst[0] //
	////	WordArray[11] = g_EE_ShadReg91; // trim_cali_ofst[1] //
	////	WordArray[12] = g_EE_ShadReg92; // trim_cali_ofst[2] //
	////	WordArray[13] = g_EE_ShadReg93; // trim_cali_ofst[3] //
	////	WordArray[14] = g_EE_ShadReg94; // trim_cali_ofst[4] //
	////	WordArray[15] = g_EE_ShadReg95; // trim_cali_ofst[5] //

	////	// (SREG5, trim_cali_ofst[5:0], set to all zeros) //
	////	WordArray[10] = 0; // trim_cali_ofst[0] //
	////	WordArray[11] = 0; // trim_cali_ofst[1] //
	////	WordArray[12] = 0; // trim_cali_ofst[2] //
	////	WordArray[13] = 0; // trim_cali_ofst[3] //
	////	WordArray[14] = 0; // trim_cali_ofst[4] //
	////	WordArray[15] = 0; // trim_cali_ofst[5] //
	////	Write_Word(g_SREG5, NOhex, WordArray, BIN); // trim_cali_ofst[5:0], set to all zeros) //

	////	// Write the I2C command to connect the output of the 8-Bit DAC to FB(COMP) pin. //
	////	Write_Word(g_TM_CTRL, 0x0004, NObin, HEX); //  Write the I2C command to connect the output of the 8-Bit DAC to FB(COMP) pin. //
	////	
	////	// Write the I2C command to set the DAC value to be 8'b10000000. //
	////	Write_Byte(g_TM_DAC, 0x80, NObin, HEX);

	////	// IsDAC_final.  Measure voltage on FB (COMP) pin. //
	////	wait.delay_10_us(100);
	////	g_IsDAC_final = dvi_13->measure_average(10); // DVI_13_0, dvi2k //
	////	if (g_Trim_Enable_P == 1)
	////		IsDAC_Act_Chg = ((g_IsDAC_final - g_IsDAC_Pt_S) / g_IsDAC_Pt_S)*100; // In percent //


	////	if (g_Char_Enable_P) // Characterization only //
	////	{
	////		/*
	////		// Load WordArray[] with contents of shadow register array!  Must not overwrite shadow register! //
	////		Write_Word(g_RDADDR, g_READ60, NObin, HEX); // SREG4.  Shadow register. //
	////		Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //

	////		// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	////		WordArray[0] = READ60_word[0]; // EEtr_IsDAC1_S //
	////		WordArray[1] = READ60_word[1]; // EEtr_IsDAC2_S //
	////		WordArray[2] = READ60_word[2]; // EEtr_IsDAC3_S //
	////		WordArray[3] = READ60_word[3]; // EEtr_IsDAC4_S //
	////		WordArray[4] = READ60_word[4]; // EEtr_IsDAC5_S //
	////		WordArray[5] = READ60_word[5];
	////		WordArray[6] = READ60_word[6];
	////		WordArray[7] = READ60_word[7];
	////		WordArray[8] = READ60_word[8];
	////		WordArray[9] = READ60_word[9];
	////		WordArray[10] = READ60_word[10];
	////		WordArray[11] = READ60_word[11];
	////		WordArray[12] = READ60_word[12];
	////		WordArray[13] = READ60_word[13];
	////		WordArray[14] = READ60_word[14];
	////		WordArray[15] = READ60_word[15];
	////		*/
	////		WordArray[0] = g_EE_ShadReg64; // EEtr_IsDAC1_S //
	////		WordArray[1] = g_EE_ShadReg65; // EEtr_IsDAC2_S //
	////		WordArray[2] = g_EE_ShadReg66; // EEtr_IsDAC3_S //
	////		WordArray[3] = g_EE_ShadReg67; // EEtr_IsDAC4_S //
	////		WordArray[4] = g_EE_ShadReg68; // EEtr_IsDAC5_S //
	////		WordArray[5] = g_EE_ShadReg69;
	////		WordArray[6] = g_EE_ShadReg70;
	////		WordArray[7] = g_EE_ShadReg71;
	////		WordArray[8] = g_EE_ShadReg72;
	////		WordArray[9] = g_EE_ShadReg73;
	////		WordArray[10] = g_EE_ShadReg74;
	////		WordArray[11] = g_EE_ShadReg75;
	////		WordArray[12] = g_EE_ShadReg76;
	////		WordArray[13] = g_EE_ShadReg77;
	////		WordArray[14] = g_EE_ShadReg78;
	////		WordArray[15] = g_EE_ShadReg79;

	////		// (SREG4, bit[71:69]: trim_comp_cc , set to 0.)//
	////		WordArray[5] = 0;
	////		WordArray[6] = 0;
	////		WordArray[7] = 0;	

	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode0
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(0, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode0 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode1
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(1, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode1 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //


	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode2
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(2, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode2 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //


	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode4
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(4, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode4 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //


	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode8
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(8, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode8 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //


	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode16
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(16, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode16 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //



	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// IsDAC_TrCode31
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Convert decimal number into binary number and store in TempArray[]. //		
	////		Convert_Decimal_To_Binary(31, TempArray);

	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		WordArray[0] = TempArray[0];
	////		WordArray[1] = TempArray[1]; 
	////		WordArray[2] = TempArray[2]; 
	////		WordArray[3] = TempArray[3]; 
	////		WordArray[4] = TempArray[4]; 

	////		// Load new trim code to shadow register. //
	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	////		// Measure voltage on FB (COMP) pin. //
	////		wait.delay_10_us(150);
	////		IsDAC_TrCode31 = dvi_13->measure_average(10); // DVI_13_0, dvi2k //

	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Reload original trim code to shadow register //
	////		// Load READ59_word[] to WordArray[] at correct bit locations. //
	////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////		// Load TempArray[] to WordArray[] at correct bit locations. //
	////		/*
	////		WordArray[0] = READ60_word[0];
	////		WordArray[1] = READ60_word[1]; 
	////		WordArray[2] = READ60_word[2]; 
	////		WordArray[3] = READ60_word[3]; 
	////		WordArray[4] = READ60_word[4];
	////		WordArray[5] = READ60_word[5]; 
	////		WordArray[6] = READ60_word[6]; 
	////		WordArray[7] = READ60_word[7];
	////		*/
	////		WordArray[0] = g_EE_ShadReg64; // EEtr_IsDAC1_S //
	////		WordArray[1] = g_EE_ShadReg65; // EEtr_IsDAC2_S //
	////		WordArray[2] = g_EE_ShadReg66; // EEtr_IsDAC3_S //
	////		WordArray[3] = g_EE_ShadReg67; // EEtr_IsDAC4_S //
	////		WordArray[4] = g_EE_ShadReg68; // EEtr_IsDAC5_S //
	////		WordArray[5] = g_EE_ShadReg69;
	////		WordArray[6] = g_EE_ShadReg70;
	////		WordArray[7] = g_EE_ShadReg71;

	////		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
	////	}

	////}

	////// Powerdown //
	//////Open_relay(K2);
	////SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	////Open_relay(K18);
	////FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	////BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	////Mux20_Open_relay(K55); // FB (COMP) pin to input of OP07 buffer. //
	////Mux20_Open_relay(K56); // FB (COMP) pin output of OP07 buffer. //
	////Mux20_Open_relay(K48); // Disconnect IS pin from ovi. //
	////Mux20_Open_relay(K46); // Connect DVI 2k to IS pin. //
	////FB_ovi->connect(2);
	////VO_dvi->set_voltage(VO_ch,0, VOLT_5_RANGE); // DVI_9_0 //
	////dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	////dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	////VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	////uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	////Mux20_Open_relay(K64);
	////ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	////Mux20_Open_relay(K37);
	////Mux20_Open_relay(K38);
	////Mux20_Open_relay(K40);
	////Mux20_Open_relay(K39);
	////Mux20_Open_relay(K50);
	////ddd_7->ddd_set_clock_period(Dclk_period);
	////ddd_7->ddd_set_voltage_ref(DDD_Vref);

	////// DDD level //
	//////g_DDD_Low = 0.0; // Save current value //
	//////g_DDD_High = 4.0; // Save current value //
	//////wait.delay_10_us(100);
	//////ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//////ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	////wait.delay_10_us(200); // Wait for relays //

	////// Datalog //
	////if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	////{
	////	PiDatalog(func, A_IsDAC_final, g_IsDAC_final, 25, POWER_UNIT);
	////}
	////if (g_Char_Enable_P) // Characterization only //
	////{
	////	PiDatalog(func, A_IsDAC_TrCode0, IsDAC_TrCode0, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode1, IsDAC_TrCode1, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode2, IsDAC_TrCode2, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode4, IsDAC_TrCode4, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode8, IsDAC_TrCode8, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode16, IsDAC_TrCode16, 25, POWER_UNIT);
	////	PiDatalog(func, A_IsDAC_TrCode31, IsDAC_TrCode31, 25, POWER_UNIT);
	////}
	////if (g_Trim_Enable_P == 1)
	////	PiDatalog(func, A_IsDAC_Act_Chg, IsDAC_Act_Chg, 25, POWER_UNIT);
	////
	////// Test Time End //
	//////if (g_TstTime_Enble_P)
	//////{
	//////	g_endtime = g_mytimer.GetElapsedTime();
	//////	IsDAC_final_TT = (g_endtime - g_begintime)*1e-6;
	//////	PiDatalog(func, A_IsDAC_final_TT, IsDAC_final_TT, 25, POWER_MILLI);
	//////}

	////// Check any test failed //
	////if (PiGetAnyFailStatus())		
	////{
	////	g_PartFailed = 1;
	////}
}
