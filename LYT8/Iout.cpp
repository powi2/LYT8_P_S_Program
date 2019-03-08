//==============================================================================
// Iout.cpp (User function)
// 
//    void Iout_user_init(test_function& func)
//    void Iout(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Iout.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Iout_user_init(test_function& func)
{
	Iout_params *ours;
    ours = (Iout_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Iout(test_function& func)
{
    // The two lines below must be the first two in the function.
    Iout_params *ours;
    ours = (Iout_params *)func.params;

	// Increment function number //
	gFuncNum++;
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_Iout, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_Iout == 0 )  
		return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float ISVTH = 0;
	float ISVTH_NOS = 0;
	float ISVTH_NoCal = 0;
	float ISVTH_NoCal_NOS = 0;
	float Delta_IOUT = 0;
	float AvgReg_LFdly = 0;
	float AvgReg_HFdly = 0;
	float iTOL_6p25_mV = 0;
	float iTOL_6p25_Avg = 0;
	float iTOL_19_mV = 0;
	float iTOL_19_mV_Avg = 0;
	float iTOL_32_mV = 0;
	float iTOL_32_mV_Avg = 0;
	float Iout_TT =0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	int READ15_word[16] = {0};
	int READ58_word[16] = {0};
	int READ59_word[16] = {0};
	int READ60_word[16] = {0};
	int READ61_word[16] = {0};
	int TempArray[30] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	float Vforce = 0;
	float SRpinVolt = 0;
	float Iout1 = 0;
	float Iout2 = 0;
	int ReadWordData[16] = {0};
	int ReadByteData[8] = {0};
	int ResultValue = 0;
	int Result1 = 0;
	int Result2 = 0;
	float WordData = 0;
	int LoopCnt = 0;
	float V_Step = 0;
	float ISVTH_FromAbove = 0;
	float ISVTH_FromBelow = 0;
	float TempV1 = 0;
	float Force_IS_volt = 0;
	float MeasResult[100] = {0};
	int MeasDelta = 0;
	int i = 0;
	int j = 0;
	float sum = 0;
	int NumPoints = 16;
	float Volt_IsDAC = 0;
	float Volt_40X = 0;
	float ISVTH_low = 0;
	float IsCal_Value = 0;
	float BeginCheckTime = 0; 
	float EndCheckTime = 0;
	int ReadoutResult[1000] = {0};
	float DelayTime[1000] = {0};
	Pulse pulse;

	if (g_Char_Enable_P) // Characterization only //
	{
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Measure the CC comparator offset //
		// -First measure output voltage from IsDAC (Volt_IsDAC).
		// -Search for ISVTH_low value on IS pin watching CC comparator output flip on SR pin
		//		(note, we are forcing IsDAC directly with calibration disabled so ISVTH will be 
		//		lower than normal; (1.28-0.4)/40 = .022 instead of (1.68-0.4)/40 = .032.
		// -Force the found ISVTH_low to IS pin.
		// -Measure output voltage from 40X gain comparator (Volt_40X);
		// -Calculate CC comparator offset:  g_CCoff_final = Volt_40X - Volt_IsDAC;
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
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
		//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
		Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

		// BPS //
		//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

		// Vout //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //

		// FB (COMP) //
		Mux20_Close_relay(K55); // FB (COMP) pin to input of OP07 buffer.  Needed because the internal DAC 
								// ouput resistor is 80kohm, so the input impedance of the measure 
								// instrument needs to be 8Megohm just to get 1% accuracy. //
		Mux20_Close_relay(K56); // Output of OP07 buffer to DVI_13_0, dvi2k //
		FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
		FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2 //
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
		Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

		// SCL //
		Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
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
		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

		// Enable CC comparator for Rev C silicon.  CC comparator is disabled by default for Rev C silicon 
		// and can be enabled through customer addressable registers. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			Write_Byte(g_fast_cc_offset, 0x80, NObin, HEX);
		}

		// Load the DUTs shadow register to the g_ShadowRegister[] array.  
		//ReadShadowRegister();

		////// Disable the Cal Bit in shadow register (SREG3, bit[55]: trim_dis_cali, set to 1.
		////// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register! //
		/////
		////WordArray[0] = g_ShadowRegister[48];
		////WordArray[1] = g_ShadowRegister[49];
		////WordArray[2] = g_ShadowRegister[50];
		////WordArray[3] = g_ShadowRegister[51];
		////WordArray[4] = g_ShadowRegister[52];
		////WordArray[5] = g_ShadowRegister[53];
		////WordArray[6] = g_ShadowRegister[54];
		////WordArray[7] = g_ShadowRegister[55]; //  bit[55]: trim_dis_cali //
		////WordArray[8] = g_ShadowRegister[56];
		////WordArray[9] = g_ShadowRegister[57];
		////WordArray[10] = g_ShadowRegister[58];
		////WordArray[11] = g_ShadowRegister[59];
		////WordArray[12] = g_ShadowRegister[60];
		////WordArray[13] = g_ShadowRegister[61];
		////WordArray[14] = g_ShadowRegister[62];
		////WordArray[15] = g_ShadowRegister[63];
		/////
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		WordArray[5] = g_EE_ShadReg53;
		WordArray[6] = g_EE_ShadReg54;
		WordArray[7] = g_EE_ShadReg55; //  bit[55]: trim_dis_cali //
		WordArray[8] = g_EE_ShadReg56;
		WordArray[9] = g_EE_ShadReg57;
		WordArray[10] = g_EE_ShadReg58;
		WordArray[11] = g_EE_ShadReg59;
		WordArray[12] = g_EE_ShadReg60;
		WordArray[13] = g_EE_ShadReg61;
		WordArray[14] = g_EE_ShadReg62;
		WordArray[15] = g_EE_ShadReg63;

		// (SREG3, bit[55]: trim_dis_cali, set to 1.) //
		WordArray[7] = 1; // bit[55]: trim_dis_cali, set to 1. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // bit[55]: trim_dis_cali, set to 1. //

		// Disable CC comparator offset trim in shadow register (SREG4, bit[71:69]: trim_comp_cc , set to 0.)
		// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register! //
		/////
		////WordArray[0] = g_ShadowRegister[64];
		////WordArray[1] = g_ShadowRegister[65];
		////WordArray[2] = g_ShadowRegister[66];
		////WordArray[3] = g_ShadowRegister[67];
		////WordArray[4] = g_ShadowRegister[68];
		////WordArray[5] = g_ShadowRegister[69];
		////WordArray[6] = g_ShadowRegister[70];
		////WordArray[7] = g_ShadowRegister[71];
		////WordArray[8] = g_ShadowRegister[72];
		////WordArray[9] = g_ShadowRegister[73];
		////WordArray[10] = g_ShadowRegister[74];
		////WordArray[11] = g_ShadowRegister[75];
		////WordArray[12] = g_ShadowRegister[76];
		////WordArray[13] = g_ShadowRegister[77];
		////WordArray[14] = g_ShadowRegister[78];
		////WordArray[15] = g_ShadowRegister[79];
		////
		WordArray[0] = g_EE_ShadReg64;
		WordArray[1] = g_EE_ShadReg65;
		WordArray[2] = g_EE_ShadReg66;
		WordArray[3] = g_EE_ShadReg67;
		WordArray[4] = g_EE_ShadReg68;
		WordArray[5] = g_EE_ShadReg69;
		WordArray[6] = g_EE_ShadReg70;
		WordArray[7] = g_EE_ShadReg71;
		WordArray[8] = g_EE_ShadReg72;
		WordArray[9] = g_EE_ShadReg73;
		WordArray[10] = g_EE_ShadReg74;
		WordArray[11] = g_EE_ShadReg75;
		WordArray[12] = g_EE_ShadReg76;
		WordArray[13] = g_EE_ShadReg77;
		WordArray[14] = g_EE_ShadReg78;
		WordArray[15] = g_EE_ShadReg79;

		// (SREG4, bit[71:69]: trim_comp_cc , set to 0.)//
		WordArray[5] = 0;
		WordArray[6] = 0;
		WordArray[7] = 0;	
		Write_Word(g_SREG4, NOhex, WordArray, BIN); // SREG4, bit[71:69]: trim_comp_cc , set to 0.)//

		// Set the calibration bits to zero in shadow register (SREG5, trim_cali_ofst[5:0], set to all zeros)
		// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register! //
		/////
		////WordArray[0] = g_ShadowRegister[80];
		////WordArray[1] = g_ShadowRegister[81];
		////WordArray[2] = g_ShadowRegister[82];
		////WordArray[3] = g_ShadowRegister[83];
		////WordArray[4] = g_ShadowRegister[84];
		////WordArray[5] = g_ShadowRegister[85];
		////WordArray[6] = g_ShadowRegister[86];
		////WordArray[7] = g_ShadowRegister[87];
		////WordArray[8] = g_ShadowRegister[88];
		////WordArray[9] = g_ShadowRegister[89];
		////WordArray[10] = g_ShadowRegister[90]; // trim_cali_ofst[0] //
		////WordArray[11] = g_ShadowRegister[91]; // trim_cali_ofst[1] //
		////WordArray[12] = g_ShadowRegister[92]; // trim_cali_ofst[2] //
		////WordArray[13] = g_ShadowRegister[93]; // trim_cali_ofst[3] //
		////WordArray[14] = g_ShadowRegister[94]; // trim_cali_ofst[4] //
		////WordArray[15] = g_ShadowRegister[95]; // trim_cali_ofst[5] //
		////
		WordArray[0] = g_EE_ShadReg80;
		WordArray[1] = g_EE_ShadReg81;
		WordArray[2] = g_EE_ShadReg82;
		WordArray[3] = g_EE_ShadReg83;
		WordArray[4] = g_EE_ShadReg84;
		WordArray[5] = g_EE_ShadReg85;
		WordArray[6] = g_EE_ShadReg86;
		WordArray[7] = g_EE_ShadReg87;
		WordArray[8] = g_EE_ShadReg88;
		WordArray[9] = g_EE_ShadReg89;
		WordArray[10] = g_EE_ShadReg90; // trim_cali_ofst[0] //
		WordArray[11] = g_EE_ShadReg91; // trim_cali_ofst[1] //
		WordArray[12] = g_EE_ShadReg92; // trim_cali_ofst[2] //
		WordArray[13] = g_EE_ShadReg93; // trim_cali_ofst[3] //
		WordArray[14] = g_EE_ShadReg94; // trim_cali_ofst[4] //
		WordArray[15] = g_EE_ShadReg95; // trim_cali_ofst[5] //

		// (SREG5, trim_cali_ofst[5:0], set to all zeros) //
		WordArray[10] = 0; // trim_cali_ofst[0] //
		WordArray[11] = 0; // trim_cali_ofst[1] //
		WordArray[12] = 0; // trim_cali_ofst[2] //
		WordArray[13] = 0; // trim_cali_ofst[3] //
		WordArray[14] = 0; // trim_cali_ofst[4] //
		WordArray[15] = 0; // trim_cali_ofst[5] //
		Write_Word(g_SREG5, NOhex, WordArray, BIN); // trim_cali_ofst[5:0], set to all zeros) //

		// Write the I2C command to connect the output of the 8-Bit DAC to FB(COMP) pin. //
		Write_Word(g_TM_CTRL, 0x0004, NObin, HEX); //  Write the I2C command to connect the output of the 8-Bit DAC to FB(COMP) pin. //

		// Write the I2C command to set the DAC value to be 8'b10000000. //
		Write_Byte(g_TM_DAC, 0x80, NObin, HEX);

		// Measure voltage on FB (COMP) pin. //
		wait.delay_10_us(100);
		Volt_IsDAC = FB_ovi->measure_average(10); // Measure output voltage from IsDAC //

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Search for ISVTH_low
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// SR //
		Mux20_Open_relay(K50);
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 

		// IS //
		mux_14->close_relay(MUX_2_GND);
		Close_relay(K24); // Connect IS pin to 20X buffer. //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

		// Wait for relays //
		wait.delay_10_us(200); 

		// SR //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, float //

		Write_Word(g_TM_ANA, 0x0934, NObin, HEX);

		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
		Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX); // Write byte to disable 10msec VI update lockout //

		//Write I2C command to connect output of CC comparator to FB pin //
		Write_Word(g_TM_SEL, 0x0026, NObin, HEX); // Write the I2C command to connect the output of the CC comparator to SR pin. //

		// If bit[38]: assign trim_CCesr was trimmed (set to 1), need to set back to 0 to disable Vesr CC for these tests. //
		if (g_EE_ShadReg38 == 1) // bit[38]: assign trim_CCesr //
		{
			///////
			//////// Read out contents of shadow register.  Can't overwrite shadow register. //
			//////Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
			//////Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //

			//////WordArray[0] = READ58_word[0];
			//////WordArray[1] = READ58_word[1];
			//////WordArray[2] = READ58_word[2];
			//////WordArray[3] = READ58_word[3];
			//////WordArray[4] = READ58_word[4];
			//////WordArray[5] = READ58_word[5];
			//////WordArray[6] = READ58_word[6]; // bit[38]: assign trim_CCesr //
			//////WordArray[7] = READ58_word[7];
			//////WordArray[8] = READ58_word[8];
			//////WordArray[9] = READ58_word[9];
			//////WordArray[10] = READ58_word[10];
			//////WordArray[11] = READ58_word[11];
			//////WordArray[12] = READ58_word[12];
			//////WordArray[13] = READ58_word[13];
			//////WordArray[14] = READ58_word[14];
			//////WordArray[15] = READ58_word[15];
			//////
			WordArray[0] = g_EE_ShadReg32;
			WordArray[1] = g_EE_ShadReg33;
			WordArray[2] = g_EE_ShadReg34;
			WordArray[3] = g_EE_ShadReg35;
			WordArray[4] = g_EE_ShadReg36;
			WordArray[5] = g_EE_ShadReg37;
			WordArray[6] = g_EE_ShadReg38; // bit[38]: assign trim_CCesr //
			WordArray[7] = g_EE_ShadReg39;
			WordArray[8] = g_EE_ShadReg40;
			WordArray[9] = g_EE_ShadReg41;
			WordArray[10] = g_EE_ShadReg42;
			WordArray[11] = g_EE_ShadReg43;
			WordArray[12] = g_EE_ShadReg44;
			WordArray[13] = g_EE_ShadReg45;
			WordArray[14] = g_EE_ShadReg46;
			WordArray[15] = g_EE_ShadReg47;

			// bit[38]: assign trim_CCesr set to 0 to disable Vesr CC. //
			WordArray[6] = 0;
			Write_Word(g_SREG2, NOhex, WordArray, BIN);
		}

		// Linear search steps from above //
		//UpperLimit = (func.dlog->tests[A_ISVTH].f_max_limit_val[0])*1.1; // Get upper search limit //
		//LowerLimit = (func.dlog->tests[A_ISVTH].f_min_limit_val[0])*0.9; // Get lower search limit //
		UpperLimit = .032; // Get upper search limit //
		LowerLimit = .015; // Get lower search limit //
		//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		//{
		//	UpperLimit = (func.dlog->tests[A_ISVTH].f_max_limit_val[0])*1.5; // Get upper search limit //
		//	LowerLimit = (func.dlog->tests[A_ISVTH].f_min_limit_val[0])*0.5; // Get lower search limit //
		//}
		//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = UpperLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		V_Step = 2.5e-3;
		LoopCnt = 0;
		Vforce += V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce > LowerLimit && LoopCnt < 400)
		{
			Vforce -= V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(25);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt < 1.5) // Below threshold //
			{
				break;
			}
			LoopCnt++;
		}
		ISVTH_FromAbove = Vforce + (V_Step/2);

		// Linear search steps from below //
		Vforce = LowerLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		LoopCnt = 0;
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce < UpperLimit && LoopCnt < 400)
		{
			Vforce += V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(25);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt > 1.5) // Above threshold //
			{
				break;
			}
			LoopCnt++;
		}
		ISVTH_FromBelow = Vforce - (V_Step/2);

		// Average two searches //
		ISVTH_low = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

		// IS pin connected to 20X buffer. //
		//ISVTH_low /= 20;
		ISVTH_low /= g_ISbuff_Gain32;

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Measure output voltage from 40X gain comparator (Volt_40X);
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		//Vforce = ISVTH_low*20; // IS pin connected to 20X buffer. //
		Vforce = ISVTH_low*g_ISbuff_Gain32; // IS pin connected to 20X buffer. //
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);

		// Disable TM_EN_SR_driver //
		Write_Word(g_TM_ANA, 0x0130, NObin, HEX);

		// SR //
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
		//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
		Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
		wait.delay_10_us(300);

		//Write I2C command to connect output of 40X gain amplifier to FB pin using TM_CTRL (tm_ctrl[12]:tm_isn_afe set to 1).
		//Write I2C command to set tm_ctrl[11:8] to '1000'  (design says this will provide cleanest signal on FB pin. )
		Write_Word(g_TM_CTRL, 0x1800, NObin, HEX); 

		// Measure volt output on FB pin. //
		FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
		wait.delay_10_us(1000);
		Volt_40X = FB_ovi->measure_average(10);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Calculate CC comparator offset
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		g_CCoff_final = Volt_40X - Volt_IsDAC;
	}

	// Powerdown //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	//Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	Mux20_Open_relay(K55); // FB (COMP) pin to input of OP07 buffer. //
	Mux20_Open_relay(K56); // FB (COMP) pin output of OP07 buffer. //
//	Mux20_Open_relay(K48); // Disconnect IS pin from ovi. //
//	Mux20_Open_relay(K46); // Connect DVI 2k to IS pin. //
	FB_ovi->connect(2);

	VO_dvi->set_voltage(VO_ch,0, VOLT_5_RANGE); // DVI_9_0 //
	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	//Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	//Mux20_Open_relay(K37);
	//Mux20_Open_relay(K38);
	//Mux20_Open_relay(K40);
	//Mux20_Open_relay(K39);
	Mux20_Open_relay(K50);

	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	if (g_Char_Enable_P) // Characterization only //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// ISVTH_NoCal //
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
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
		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 

		// BPS //
		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

		// IS //
		mux_14->close_relay(MUX_2_GND);
		Close_relay(K24); // Connect IS pin to 20X buffer. //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

		// Vout //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

		// FB (COMP) //
		FB_ovi->disconnect(2);

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
		Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

		// SCL //
		Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

		// Set DDD for I2C. //
		//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
		//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
			
		// Wait for relays //
		wait.delay_10_us(200); 

		// Powerup //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

		// SR //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, float //

		// I2C into test mode. //  
		Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
		Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

		// Enable CC comparator for Rev C silicon.  CC comparator is disabled by default for Rev C silicon 
		// and can be enabled through customer addressable registers. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			Write_Byte(g_fast_cc_offset, 0x80, NObin, HEX);
		}

		// Disable calibration //
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		////
		////Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
		////Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //

		////WordArray[0] = READ59_word[0];
		////WordArray[1] = READ59_word[1];
		////WordArray[2] = READ59_word[2];
		////WordArray[3] = READ59_word[3];
		////WordArray[4] = READ59_word[4];
		////WordArray[5] = READ59_word[5];
		////WordArray[6] = READ59_word[6];
		////WordArray[7] = READ59_word[7]; // bit[55]: trim_dis_cali //
		////WordArray[8] = READ59_word[8];
		////WordArray[9] = READ59_word[9];
		////WordArray[10] = READ59_word[10];
		////WordArray[11] = READ59_word[11];
		////WordArray[12] = READ59_word[12];
		////WordArray[13] = READ59_word[13];
		////WordArray[14] = READ59_word[14];
		////WordArray[15] = READ59_word[15];
		////
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		WordArray[5] = g_EE_ShadReg53;
		WordArray[6] = g_EE_ShadReg54;
		WordArray[7] = g_EE_ShadReg55; // bit[55]: trim_dis_cali //
		WordArray[8] = g_EE_ShadReg56;
		WordArray[9] = g_EE_ShadReg57;
		WordArray[10] = g_EE_ShadReg58;
		WordArray[11] = g_EE_ShadReg59;
		WordArray[12] = g_EE_ShadReg60;
		WordArray[13] = g_EE_ShadReg61;
		WordArray[14] = g_EE_ShadReg62;
		WordArray[15] = g_EE_ShadReg63;

		// bit[55]: trim_dis_cali, set to 1 to disable calibration //
		WordArray[7] = 1;
		Write_Word(g_SREG3, NOhex, WordArray, BIN);

		// Load calibration factor, using the IsCal_Final measurement //
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		////
		////Write_Word(g_RDADDR, g_READ61, NObin, HEX); // SREG5.  Shadow register. //
		////Read_Word(g_RDADDR, READ61_word); // SREG5.  Shadow register. //

		////WordArray[0] = READ61_word[0];
		////WordArray[1] = READ61_word[1];
		////WordArray[2] = READ61_word[2];
		////WordArray[3] = READ61_word[3];
		////WordArray[4] = READ61_word[4];
		////WordArray[5] = READ61_word[5];
		////WordArray[6] = READ61_word[6];
		////WordArray[7] = READ61_word[7];
		////WordArray[8] = READ61_word[8];
		////WordArray[9] = READ61_word[9];
		////WordArray[10] = READ61_word[10]; // eep_sreg[90]: trim_cali_ofst[0] //
		////WordArray[11] = READ61_word[11]; // eep_sreg[91]: trim_cali_ofst[1] //
		////WordArray[12] = READ61_word[12]; // eep_sreg[92]: trim_cali_ofst[2] //
		////WordArray[13] = READ61_word[13]; // eep_sreg[93]: trim_cali_ofst[3] //
		////WordArray[14] = READ61_word[14]; // eep_sreg[94]: trim_cali_ofst[4] //
		////WordArray[15] = READ61_word[15]; // eep_sreg[95]: trim_cali_ofst[5] //
		////
		WordArray[0] = g_EE_ShadReg80;
		WordArray[1] = g_EE_ShadReg81;
		WordArray[2] = g_EE_ShadReg82;
		WordArray[3] = g_EE_ShadReg83;
		WordArray[4] = g_EE_ShadReg84;
		WordArray[5] = g_EE_ShadReg85;
		WordArray[6] = g_EE_ShadReg86;
		WordArray[7] = g_EE_ShadReg87;
		WordArray[8] = g_EE_ShadReg88;
		WordArray[9] = g_EE_ShadReg89;
		WordArray[10] = g_EE_ShadReg90; // eep_sreg[90]: trim_cali_ofst[0] //
		WordArray[11] = g_EE_ShadReg91; // eep_sreg[91]: trim_cali_ofst[1] //
		WordArray[12] = g_EE_ShadReg92; // eep_sreg[92]: trim_cali_ofst[2] //
		WordArray[13] = g_EE_ShadReg93; // eep_sreg[93]: trim_cali_ofst[3] //
		WordArray[14] = g_EE_ShadReg94; // eep_sreg[94]: trim_cali_ofst[4] //
		WordArray[15] = g_EE_ShadReg95; // eep_sreg[95]: trim_cali_ofst[5] //

		// Load the calibration code //
		// eep_sreg[95:90]: trim_cali_ofst[5:0] //
		// Convert decimal number into binary number and store in TempArray[]. //
		IsCal_Value = g_IsCal_final/.010; // 10mV per DAC step. //
		Convert_Decimal_To_Binary(IsCal_Value, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[10] = TempArray[0];
		WordArray[11] = TempArray[1];
		WordArray[12] = TempArray[2];
		WordArray[13] = TempArray[3];
		WordArray[14] = TempArray[4];
		WordArray[15] = TempArray[5];

		// Load new calibration code to shadow register. //
		Write_Word(g_SREG5, NOhex, WordArray, BIN);

		Write_Word(g_TM_ANA, 0x0134, NObin, HEX);

		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
		Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX); // Write byte to disable 10msec VI update lockout //

		//Write I2C command to connect output of CC comparator to FB pin //
		Write_Word(g_TM_SEL, 0x0026, NObin, HEX); // Write the I2C command to connect the output of the CC comparator to SR pin. //

		// If bit[38]: assign trim_CCesr was trimmed (set to 1), need to set back to 0 to disable Vesr CC for these tests. //
		if (g_EE_ShadReg38 == 1) // bit[38]: assign trim_CCesr //
		{
			////// Read out contents of shadow register.  Can't overwrite shadow register. //
			//////
			////Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
			////Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //

			////WordArray[0] = READ58_word[0];
			////WordArray[1] = READ58_word[1];
			////WordArray[2] = READ58_word[2];
			////WordArray[3] = READ58_word[3];
			////WordArray[4] = READ58_word[4];
			////WordArray[5] = READ58_word[5];
			////WordArray[6] = READ58_word[6]; // bit[38]: assign trim_CCesr //
			////WordArray[7] = READ58_word[7];
			////WordArray[8] = READ58_word[8];
			////WordArray[9] = READ58_word[9];
			////WordArray[10] = READ58_word[10];
			////WordArray[11] = READ58_word[11];
			////WordArray[12] = READ58_word[12];
			////WordArray[13] = READ58_word[13];
			////WordArray[14] = READ58_word[14];
			////WordArray[15] = READ58_word[15];
			//////
			WordArray[0] = g_EE_ShadReg32;
			WordArray[1] = g_EE_ShadReg33;
			WordArray[2] = g_EE_ShadReg34;
			WordArray[3] = g_EE_ShadReg35;
			WordArray[4] = g_EE_ShadReg36;
			WordArray[5] = g_EE_ShadReg37;
			WordArray[6] = g_EE_ShadReg38; // bit[38]: assign trim_CCesr //
			WordArray[7] = g_EE_ShadReg39;
			WordArray[8] = g_EE_ShadReg40;
			WordArray[9] = g_EE_ShadReg41;
			WordArray[10] = g_EE_ShadReg42;
			WordArray[11] = g_EE_ShadReg43;
			WordArray[12] = g_EE_ShadReg44;
			WordArray[13] = g_EE_ShadReg45;
			WordArray[14] = g_EE_ShadReg46;
			WordArray[15] = g_EE_ShadReg47;

			// bit[38]: assign trim_CCesr set to 0 to disable Vesr CC. //
			WordArray[6] = 0;
			Write_Word(g_SREG2, NOhex, WordArray, BIN);
		}

		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //

		// Write maximum CC 128 (100%) with I2C //
		WordData = 384; // With parity //
		Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //
	
		// Linear search steps from above //
		UpperLimit = (func.dlog->tests[A_ISVTH_NoCal].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_ISVTH_NoCal].f_min_limit_val[0])*0.9; // Get lower search limit //
		//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		//{
		//	UpperLimit = (func.dlog->tests[A_ISVTH_NoCal].f_max_limit_val[0])*1.5; // Get upper search limit //
		//	LowerLimit = (func.dlog->tests[A_ISVTH_NoCal].f_min_limit_val[0])*0.5; // Get lower search limit //
		//}
		//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = UpperLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		V_Step = 2.5e-3;
		LoopCnt = 0;
		Vforce += V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce > LowerLimit && LoopCnt < 400)
		{
			Vforce -= V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt < 1.5) // Below threshold //
			{
				break;
			}
			LoopCnt++;
		}
		ISVTH_FromAbove = Vforce + (V_Step/2);

		// Linear search steps from below //
		Vforce = LowerLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		LoopCnt = 0;
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce < UpperLimit && LoopCnt < 400)
		{
			Vforce += V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt > 1.5) // Above threshold //
			{
				break;
			}
			LoopCnt++;
		}
		//TempV1 = Vforce + (V_Step*1.5);
		ISVTH_FromBelow = Vforce - (V_Step/2);

		// Average two searches //
		ISVTH_NoCal = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

		// IS pin connected to 20X buffer. //
		ISVTH_NoCal /= g_ISbuff_Gain32;



		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// ISVTH_NoCal_NOS //
		//
		// Measure ISVTH with no calibration and no CC comparator offset (EEPROM bits 69, 70, and 71 all zero)
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Set CC comparator offset to zero. //
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		///////
		//////Write_Word(g_RDADDR, g_READ60, NObin, HEX);// SREG4.  Shadow register. //
		//////Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //

		//////WordArray[0] = READ60_word[0];
		//////WordArray[1] = READ60_word[1];
		//////WordArray[2] = READ60_word[2];
		//////WordArray[3] = READ60_word[3];
		//////WordArray[4] = READ60_word[4];
		//////WordArray[5] = READ60_word[5]; // bit[69]: trim_comp_cc  //
		//////WordArray[6] = READ60_word[6]; // bit[70]: trim_comp_cc  //
		//////WordArray[7] = READ60_word[7]; // bit[71]: trim_comp_cc  //
		//////WordArray[8] = READ60_word[8];
		//////WordArray[9] = READ60_word[9];
		//////WordArray[10] = READ60_word[10];
		//////WordArray[11] = READ60_word[11];
		//////WordArray[12] = READ60_word[12];
		//////WordArray[13] = READ60_word[13];
		//////WordArray[14] = READ60_word[14];
		//////WordArray[15] = READ60_word[15];
		//////
		WordArray[0] = g_EE_ShadReg64;
		WordArray[1] = g_EE_ShadReg65;
		WordArray[2] = g_EE_ShadReg66;
		WordArray[3] = g_EE_ShadReg67;
		WordArray[4] = g_EE_ShadReg68;
		WordArray[5] = g_EE_ShadReg69; // bit[69]: trim_comp_cc  //
		WordArray[6] = g_EE_ShadReg70; // bit[70]: trim_comp_cc  //
		WordArray[7] = g_EE_ShadReg71; // bit[71]: trim_comp_cc  //
		WordArray[8] = g_EE_ShadReg72;
		WordArray[9] = g_EE_ShadReg73;
		WordArray[10] = g_EE_ShadReg74;
		WordArray[11] = g_EE_ShadReg75;
		WordArray[12] = g_EE_ShadReg76;
		WordArray[13] = g_EE_ShadReg77;
		WordArray[14] = g_EE_ShadReg78;
		WordArray[15] = g_EE_ShadReg79;

		// bits 69, 70, 71 set to 0 to set CC comparator offset to zero. //
		WordArray[5] = 0; // bit[69]: trim_comp_cc  //
		WordArray[6] = 0; // bit[70]: trim_comp_cc  //
		WordArray[7] = 0; // bit[71]: trim_comp_cc  //
		Write_Word(g_SREG4, NOhex, WordArray, BIN);

		// Write maximum CC 128 (100%) with I2C //
		WordData = 384; // With parity //
		Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //
	
		// Linear search steps from above //
		UpperLimit = (func.dlog->tests[A_ISVTH_NoCal_NOS].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_ISVTH_NoCal_NOS].f_min_limit_val[0])*0.9; // Get lower search limit //
		//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		//{
		//	UpperLimit = (func.dlog->tests[A_ISVTH_NoCal_NOS].f_max_limit_val[0])*1.5; // Get upper search limit //
		//	LowerLimit = (func.dlog->tests[A_ISVTH_NoCal_NOS].f_min_limit_val[0])*0.5; // Get lower search limit //
		//}
		//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = UpperLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		V_Step = 2.5e-3;
		LoopCnt = 0;
		Vforce += V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce > LowerLimit && LoopCnt < 400)
		{
			Vforce -= V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt < 1.5) // Below threshold //
			{
				break;
			}
			LoopCnt++;
		}
		ISVTH_FromAbove = Vforce + (V_Step/2);

		// Linear search steps from below //
		Vforce = LowerLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		LoopCnt = 0;
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce < UpperLimit && LoopCnt < 400)
		{
			Vforce += V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt > 1.5) // Above threshold //
			{
				break;
			}
			LoopCnt++;
		}
		//TempV1 = Vforce + (V_Step*1.5);
		ISVTH_FromBelow = Vforce - (V_Step/2);

		// Average two searches //
		ISVTH_NoCal_NOS = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

		// IS pin connected to 20X buffer. //
		ISVTH_NoCal_NOS /= g_ISbuff_Gain32;

		// Powerdown //
		SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
		//Mux20_Open_relay(K64);
		ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
		//Mux20_Open_relay(K37);
		//Mux20_Open_relay(K38);
		//Mux20_Open_relay(K40);
		//Mux20_Open_relay(K39);
		VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
		wait.delay_10_us(20);
		//Open_relay(K18);
		FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
		//mux_14->open_relay(MUX_2_GND);
		//Open_relay(K24); // Disconnect IS pin from 20X buffer. //
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		//uVCCrampDown(0.5, 0, 0.1);
		wait.delay_10_us(45); // prevent SR undershoot //
		VBPS_ramp_down(4, 0.2, 200e-3);
		//VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
		//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
		wait.delay_10_us(20);
		//VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
		//FB_ovi->connect(2);
		//ddd_7->ddd_set_clock_period(Dclk_period);
		//ddd_7->ddd_set_voltage_ref(DDD_Vref);

		// DDD level //
		//g_DDD_Low = 0.0; // Save current value //
		//g_DDD_High = 4.0; // Save current value //
		//wait.delay_10_us(100);
		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(200); // Wait for relays //
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ISVTH //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
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
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	mux_14->close_relay(MUX_2_GND);
	Close_relay(K24); // Connect IS pin to 20X buffer. //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->disconnect(2);

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
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

	// Set DDD for I2C. //
	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// SR //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, float //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

	// Enable CC comparator for Rev C silicon.  CC comparator is disabled by default for Rev C silicon 
	// and can be enabled through customer addressable registers. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		Write_Byte(g_fast_cc_offset, 0x80, NObin, HEX);
	}

	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
	
	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX); // Write byte to disable 10msec VI update lockout //

	//Write I2C command to connect output of CC comparator to SR pin //
	Write_Word(g_TM_SEL, 0x0026, NObin, HEX); // Write the I2C command to connect the output of the CC comparator to SR pin. //

	// If bit[38]: assign trim_CCesr was trimmed (set to 1), need to set back to 0 to disable Vesr CC for these tests. //
	if (g_EE_ShadReg38 == 1) // bit[38]: assign trim_CCesr //
	{
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		/////
		////Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
		////Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //

		////WordArray[0] = READ58_word[0];
		////WordArray[1] = READ58_word[1];
		////WordArray[2] = READ58_word[2];
		////WordArray[3] = READ58_word[3];
		////WordArray[4] = READ58_word[4];
		////WordArray[5] = READ58_word[5];
		////WordArray[6] = READ58_word[6]; // bit[38]: assign trim_CCesr //
		////WordArray[7] = READ58_word[7];
		////WordArray[8] = READ58_word[8];
		////WordArray[9] = READ58_word[9];
		////WordArray[10] = READ58_word[10];
		////WordArray[11] = READ58_word[11];
		////WordArray[12] = READ58_word[12];
		////WordArray[13] = READ58_word[13];
		////WordArray[14] = READ58_word[14];
		////WordArray[15] = READ58_word[15];
		////
		WordArray[0] = g_EE_ShadReg32;
		WordArray[1] = g_EE_ShadReg33;
		WordArray[2] = g_EE_ShadReg34;
		WordArray[3] = g_EE_ShadReg35;
		WordArray[4] = g_EE_ShadReg36;
		WordArray[5] = g_EE_ShadReg37;
		WordArray[6] = g_EE_ShadReg38; // bit[38]: assign trim_CCesr //
		WordArray[7] = g_EE_ShadReg39;
		WordArray[8] = g_EE_ShadReg40;
		WordArray[9] = g_EE_ShadReg41;
		WordArray[10] = g_EE_ShadReg42;
		WordArray[11] = g_EE_ShadReg43;
		WordArray[12] = g_EE_ShadReg44;
		WordArray[13] = g_EE_ShadReg45;
		WordArray[14] = g_EE_ShadReg46;
		WordArray[15] = g_EE_ShadReg47;

		// bit[38]: assign trim_CCesr set to 0 to disable Vesr CC. //
		WordArray[6] = 0;
		Write_Word(g_SREG2, NOhex, WordArray, BIN);
	}

	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
	// and [7] and [15] are odd parity bits.  
	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //

	// Write maximum CC 128 (100%) with I2C //
	WordData = 384; // With parity //
	Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //

	// Linear search steps from above //
	UpperLimit = (func.dlog->tests[A_ISVTH].f_max_limit_val[0])*1.1; // Get upper search limit //
	LowerLimit = (func.dlog->tests[A_ISVTH].f_min_limit_val[0])*0.9; // Get lower search limit //
	//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
	//{
	//	UpperLimit = (func.dlog->tests[A_ISVTH].f_max_limit_val[0])*1.5; // Get upper search limit //
	//	LowerLimit = (func.dlog->tests[A_ISVTH].f_min_limit_val[0])*0.5; // Get lower search limit //
	//}
	//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
	//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
	UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
	LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
	Vforce = UpperLimit;
	if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
	{
		Vforce = 0;
		g_Error_Flag = -158;
	}
	V_Step = 2.5e-3;
	LoopCnt = 0;
	Vforce += V_Step;
	IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(100);
	while (Vforce > LowerLimit && LoopCnt < 400)
	{
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(30);
		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
		if (SRpinVolt < 1.5) // Below threshold //
		{
			break;
		}
		LoopCnt++;
	}
	ISVTH_FromAbove = Vforce + (V_Step/2);

	// Linear search steps from below //
	Vforce = LowerLimit;
	if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
	{
		Vforce = 0;
		g_Error_Flag = -158;
	}
	LoopCnt = 0;
	Vforce -= V_Step;
	IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(100);
	while (Vforce < UpperLimit && LoopCnt < 400)
	{
		Vforce += V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(30);
		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
		if (SRpinVolt > 1.5) // Above threshold //
		{
			break;
		}
		LoopCnt++;
	}
	//TempV1 = Vforce + (V_Step*1.5);
	ISVTH_FromBelow = Vforce - (V_Step/2);

	// Average two searches //
	ISVTH = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

	// IS pin connected to 20X buffer. //
	//ISVTH /= 20;
	ISVTH /= g_ISbuff_Gain32;
	g_ISVTH = ISVTH;


	if (g_Char_Enable_P) // Characterization only //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// ISVTH_NOS //
		//
		// Measure ISVTH with no calibration and no CC comparator offset (EEPROM bits 69, 70, and 71 all zero)
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Set CC comparator offset to zero. //
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		/////
		////Write_Word(g_RDADDR, g_READ60, NObin, HEX);// SREG4.  Shadow register. //
		////Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //

		////WordArray[0] = READ60_word[0];
		////WordArray[1] = READ60_word[1];
		////WordArray[2] = READ60_word[2];
		////WordArray[3] = READ60_word[3];
		////WordArray[4] = READ60_word[4];
		////WordArray[5] = READ60_word[5]; // bit[69]: trim_comp_cc //
		////WordArray[6] = READ60_word[6]; // bit[70]: trim_comp_cc //
		////WordArray[7] = READ60_word[7]; // bit[71]: trim_comp_cc //
		////WordArray[8] = READ60_word[8];
		////WordArray[9] = READ60_word[9];
		////WordArray[10] = READ60_word[10];
		////WordArray[11] = READ60_word[11];
		////WordArray[12] = READ60_word[12];
		////WordArray[13] = READ60_word[13];
		////WordArray[14] = READ60_word[14];
		////WordArray[15] = READ60_word[15];
		////
		WordArray[0] = g_EE_ShadReg64;
		WordArray[1] = g_EE_ShadReg65;
		WordArray[2] = g_EE_ShadReg66;
		WordArray[3] = g_EE_ShadReg67;
		WordArray[4] = g_EE_ShadReg68;
		WordArray[5] = g_EE_ShadReg69; // bit[69]: trim_comp_cc  //
		WordArray[6] = g_EE_ShadReg70; // bit[70]: trim_comp_cc  //
		WordArray[7] = g_EE_ShadReg71; // bit[71]: trim_comp_cc  //
		WordArray[8] = g_EE_ShadReg72;
		WordArray[9] = g_EE_ShadReg73;
		WordArray[10] = g_EE_ShadReg74;
		WordArray[11] = g_EE_ShadReg75;
		WordArray[12] = g_EE_ShadReg76;
		WordArray[13] = g_EE_ShadReg77;
		WordArray[14] = g_EE_ShadReg78;
		WordArray[15] = g_EE_ShadReg79;

		// bits 69, 70, 71 set to 0 to set CC comparator offset to zero. //
		WordArray[5] = 0; // bit[69]: trim_comp_cc  //
		WordArray[6] = 0; // bit[70]: trim_comp_cc  //
		WordArray[7] = 0; // bit[71]: trim_comp_cc  //
		Write_Word(g_SREG4, NOhex, WordArray, BIN);

		// Write maximum CC 128 (100%) with I2C //
		WordData = 384; // With parity //
		Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //

		// Linear search steps from above //
		UpperLimit = (func.dlog->tests[A_ISVTH_NOS].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_ISVTH_NOS].f_min_limit_val[0])*0.9; // Get lower search limit //
		//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		//{
		//	UpperLimit = (func.dlog->tests[A_ISVTH_NOS].f_max_limit_val[0])*1.5; // Get upper search limit //
		//	LowerLimit = (func.dlog->tests[A_ISVTH_NOS].f_min_limit_val[0])*0.5; // Get lower search limit //
		//}
		//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = UpperLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		V_Step = 2.5e-3;
		LoopCnt = 0;
		Vforce += V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce > LowerLimit && LoopCnt < 400)
		{
			Vforce -= V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt < 1.5) // Below threshold //
			{
				break;
			}
			LoopCnt++;
		}
		ISVTH_FromAbove = Vforce + (V_Step/2);

		// Linear search steps from below //
		Vforce = LowerLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		LoopCnt = 0;
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce < UpperLimit && LoopCnt < 400)
		{
			Vforce += V_Step;
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt > 1.5) // Above threshold //
			{
				break;
			}
			LoopCnt++;
		}
		//TempV1 = Vforce + (V_Step*1.5);
		ISVTH_FromBelow = Vforce - (V_Step/2);

		// Average two searches //
		ISVTH_NOS = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

		// IS pin connected to 20X buffer. //
		ISVTH_NOS /= g_ISbuff_Gain32;

		// Set bits 69, 70, 71 back to original value. //
		WordArray[5] = g_EE_ShadReg69; // bit[69]: trim_comp_cc  //
		WordArray[6] = g_EE_ShadReg70; // bit[70]: trim_comp_cc  //
		WordArray[7] = g_EE_ShadReg71; // bit[71]: trim_comp_cc  //
		Write_Word(g_SREG4, NOhex, WordArray, BIN);
	}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Delta_IOUT //
	// Looking for difference between two adjacent CC steps. Program the CC register with 
	// two values that are 50 steps apart (use 45 and 128), measure the Is pin voltage 
	// were CC comparator ouput on SR pin flips for each one, then take the difference 
	// and divide by 83 to get the average for a single step. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Write CC 45 with I2C //
	WordData = 32941; 
	Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //

	if (g_Char_Enable_P) // Characterization only //
	{
		// More delay for Rev C //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(450); // Needed //

		// Binary search on IS pin looking at SR pin flip state //
		UpperLimit = 0.032; // Get upper search limit //
		LowerLimit = 0; // Get lower search limit //
		//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = (UpperLimit + LowerLimit) / 2;
		if (Vforce < -0.999 || Vforce > 0.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -160;
		}
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while ( (UpperLimit - LowerLimit) > .001)
		{
			Vforce = (UpperLimit + LowerLimit) / 2; 
			if (Vforce < -0.999 || Vforce > 0.999) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -161;
				break;
			}
			IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_1_RANGE); // DVI_13_0, dvi2k //
			wait.delay_10_us(100);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
			if (SRpinVolt < 1.5) // Below threshold //
				LowerLimit = Vforce;
			else // Above threshold //
				UpperLimit = Vforce;		
		}
		//Iout2 = Vforce / 20; // IS pin is connected to 20X buffer. //
		Iout2 = Vforce / g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Delta_IOUT = (ISVTH - Iout2)/83;
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// IOUT_T //
	// Report-Back Output Current Tolerance //
	// Set IS pin voltage and readout CC with I2C.
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Turn on VBD drive //
	Write_Byte(g_VBEN, 0x83, NObin, HEX);

	// I2C exit test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Exit, NObin, HEX); // Write I2C key to exit test mode. //
	
	// Set fast CC comparator back to default value (disabled, 32). //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		Write_Byte(g_fast_cc_offset, 32, NObin, HEX);
	}

	// Rev C silicon //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		if (g_Char_Enable_P == 1)
		{
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// AvgReg_LFdly
			// AvgReg_HFdly
			//
			// It takes about 60msec for averaging registers to stabilize when controller reset 
			// occurs per design.  A reset occurs at powerup and when opening the BUS 
			// switch (VBD drive off).  The instantaneous register only takes around 1.3msec.  
			// 60msec is worst case because when BUS switch is open the system clock frequency is reduced by 8X. 
			// When BUS switch gets closed (VBD drive on) the system clock frequency inscreases to 
			// full 375kHz and stabilization time only take around 60/8 = 7.5msec.
			//
			// AvgReg_LFdly test measures the 60msec time.
			// AvgReg_HFdly test measures the 7.5msec time.
			//
			// These tests are for characterization only.
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		
			
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// AvgReg_LFdly
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //		
			wait.delay_10_us(20);

			// 100% CC ---> 1.0 * 32 = 32mV //
			Force_IS_volt = g_ISbuff_Gain32 * 0.032; // IS pin is connected to 20X buffer. //
			if (Force_IS_volt > 0.999 || Force_IS_volt < 0) // Prevent out of range. //
			{
				Force_IS_volt = 0;
				g_Error_Flag = -202;
			}
			IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
			wait.delay_10_us(100);

			// Turn off VBD drive to cause reset //
			Write_Byte(g_VBEN, 0x80, NObin, HEX); 

			BeginCheckTime = g_mytimer.GetElapsedTime();
			i = 0;
			DelayTime[i] = 0;
			while (DelayTime[i] < 0.300 && i < 1000) // Timeout after 300msec or exceed array index. //
			{
				i++;

				// Averaging register readout CC with I2C //
				Write_Word(g_RDADDR, g_READ13, NObin, HEX);
				Read_Word(g_RDADDR, ReadWordData);

				// Convert binary to decimal. //
				Convert_16bitBinary_To_Decimal(ReadWordData, ResultValue);

				// Save result //
				ReadoutResult[i] = ResultValue; // 128 expected //

				// Measure time //
				EndCheckTime = g_mytimer.GetElapsedTime();
				DelayTime[i] = (EndCheckTime - BeginCheckTime)*1e-6;

				// If result changes less than 3 bits after 15 measurements 
				//then averaging register has stabilized.  Get out of loop. // 
				if (i>14)
				{
					MeasDelta = ReadoutResult[i] - ReadoutResult[i-14];
					if (MeasDelta<0) // Remove negative //
						MeasDelta *= -1;
					if (MeasDelta < 3)
						break;
				}
				
			}
			AvgReg_LFdly = DelayTime[i-14];


			
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// AvgReg_HFdly
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

			// Initialize variables //
			for (i=0; i<1000; i++)
			{
				ReadoutResult[i] = 0;
				DelayTime[i] = 0;
			}
			
			// Reset //
			Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
			Write_Byte(g_VBEN, 0x80, NObin, HEX); // Turn off VBD drive to cause reset //

			// Turn on VBD drive to go to full system clock frequency. //
			Write_Byte(g_VBEN, 0x83, NObin, HEX);

			BeginCheckTime = g_mytimer.GetElapsedTime();
			i = 0;
			DelayTime[i] = 0;
			while (DelayTime[i] < 0.300 && i < 1000) // Timeout after 300msec or exceed array index. //
			{
				i++;

				// Averaging register readout CC with I2C //
				Write_Word(g_RDADDR, g_READ13, NObin, HEX);
				Read_Word(g_RDADDR, ReadWordData);

				// Convert binary to decimal. //
				Convert_16bitBinary_To_Decimal(ReadWordData, ResultValue);

				// Save result //
				ReadoutResult[i] = ResultValue; // 128 expected //

				// Measure time //
				EndCheckTime = g_mytimer.GetElapsedTime();
				DelayTime[i] = (EndCheckTime - BeginCheckTime)*1e-6;

				// If result changes less than 3 bits after 15 measurements 
				//then averaging register has stabilized.  Get out of loop. // 
				if (i>14)
				{
					MeasDelta = ReadoutResult[i] - ReadoutResult[i-14];
					if (MeasDelta<0) // Remove negative //
						MeasDelta *= -1;
					if (MeasDelta < 3)
						break;
				}
				
			}
			AvgReg_HFdly = DelayTime[i-14];

			Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
			Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX); // Write byte to disable 10msec VI update lockout //
		}
	}


	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// iTOL_32_mV //
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// 100% CC ---> 1.0 * 32 = 32mV //
		// Force 32mV to Is pin.  Is pin connected to 20X buffer (32mV x 20 = 640mV) //
		//Force_IS_volt = g_ISbuff_Gain32 * g_ISVTH; // IS pin is connected to 20X buffer. //
		Force_IS_volt = g_ISbuff_Gain32 * 0.032; // IS pin is connected to 20X buffer. //
		if (Force_IS_volt > 0.999 || Force_IS_volt < 0) // Prevent out of range. //
		{
			Force_IS_volt = 0;
			g_Error_Flag = -202;
		}
		IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
		wait.delay_10_us(100);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			// Take several readings to remove noise //
			for (i=0;i<NumPoints;i++)
			{
				// Readout CC with I2C //
				Write_Word(g_RDADDR, g_READ7, NObin, HEX);
				Read_Word(g_RDADDR, ReadWordData);

				// Select the correct readout bits. //
				ReadByteData[0] = ReadWordData[0];
				ReadByteData[1] = ReadWordData[1];
				ReadByteData[2] = ReadWordData[2];
				ReadByteData[3] = ReadWordData[3];
				ReadByteData[4] = ReadWordData[4];
				ReadByteData[5] = ReadWordData[5];
				ReadByteData[6] = ReadWordData[6];
				//ReadByteData[7] = ReadWordData[7];
				ReadByteData[7] = ReadWordData[8]; // Bit 7 is parity bit.  Bit 8 is data bit //

				// Convert binary to decimal. //
				Convert_8bitBinary_To_Decimal(ReadByteData, ResultValue);

				// Save result //
				MeasResult[i] = ResultValue; // 128 expected //
			}
			sum = 0;
			for (i=0;i<NumPoints;i++)
			{
				sum += MeasResult[i];
			}
			iTOL_32_mV = sum / NumPoints;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// iTOL_32_mV_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Readout CC with I2C //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ13, NObin, HEX);
			Read_Word(g_RDADDR, ReadWordData);

			// Convert binary to decimal. //
			Convert_16bitBinary_To_Decimal(ReadWordData, ResultValue);

			// Save result //
			iTOL_32_mV_Avg = ResultValue; // 128 expected //	
		}
	}
	
	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iTOL_19_mV //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 50% CC ---> 0.59375 * 32 = 19mV//
	// Force 19mV to Is pin.  Is pin connected to 20X buffer (19mV x 20 = 380mV) //
	//Force_IS_volt = (g_ISbuff_Gain32 * g_ISVTH) / 1.6842; // IS pin is connected to 20X buffer. //
	//Force_IS_volt = g_ISbuff_Gain32 * 0.019; // IS pin is connected to 20X buffer. //
	Force_IS_volt = g_ISbuff_GainMid * 0.019; // IS pin is connected to 20X buffer. //
	if (Force_IS_volt > 0.999 || Force_IS_volt < 0) // Prevent out of range. //
	{
		Force_IS_volt = 0;
		g_Error_Flag = -202;
	}
	IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
	wait.delay_10_us(100);

	// For Rev B3 silicon, no averaging register. //
	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	{
		// Take several readings to remove noise //
		for (i=0;i<NumPoints;i++)
		{
			// Readout CC with I2C //
			Write_Word(g_RDADDR, g_READ7, NObin, HEX);
			wait.delay_10_us(100); // Improve repeatability //
			Read_Word(g_RDADDR, ReadWordData);

			// Select the correct readout bits. //
			ReadByteData[0] = ReadWordData[0];
			ReadByteData[1] = ReadWordData[1];
			ReadByteData[2] = ReadWordData[2];
			ReadByteData[3] = ReadWordData[3];
			ReadByteData[4] = ReadWordData[4];
			ReadByteData[5] = ReadWordData[5];
			ReadByteData[6] = ReadWordData[6];
			//ReadByteData[7] = ReadWordData[7];
			ReadByteData[7] = ReadWordData[8]; // Bit 7 is parity bit.  Bit 8 is data bit //

			// Convert binary to decimal. //
			Convert_8bitBinary_To_Decimal(ReadByteData, ResultValue);

			// Save result //
			MeasResult[i] = ResultValue; // 76 expected //
		}
		sum = 0;
		for (i=0;i<NumPoints;i++)
		{
			sum += MeasResult[i];
		}
		iTOL_19_mV = sum / NumPoints;
	}

	// Test chip //
	// For Rev C silicon, use averaging register. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// iTOL_19_mV_Avg
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Readout CC with I2C //
		wait.delay_10_us(1500);
		Write_Word(g_RDADDR, g_READ13, NObin, HEX);
		Read_Word(g_RDADDR, ReadWordData);

		// Convert binary to decimal. //
		Convert_16bitBinary_To_Decimal(ReadWordData, ResultValue);

		// Save result //
		iTOL_19_mV_Avg = ResultValue; // 76 expected //
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// iTOL_6p25_mV //
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// 20% CC ---> 0.20 * 32 = 6.4mV //
		// Force voltage should be 6.25mV per design (Yuri/Johnny 9/19/2017 charactization review meeting)
		// Force 6.25mV to Is pin.  Is pin connected to 20X buffer (6.25mV x 20 = 125mV) //
		//IS_dvi2k->set_voltage(IS_ch, 125e-3, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		//wait.delay_10_us(100);
		//Force_IS_volt = (20.0 * g_ISVTH) / 5.12; // IS pin is connected to 20X buffer. //
		//Force_IS_volt = (g_ISbuff_Gain32 * g_ISVTH) / 5.12; // IS pin is connected to 20X buffer. //
		//Force_IS_volt = g_ISbuff_Gain32 * 0.00625; // IS pin is connected to 20X buffer. //
		Force_IS_volt = g_ISbuff_GainLow * 0.00625; // IS pin is connected to 20X buffer. //
		if (Force_IS_volt > 0.999 || Force_IS_volt < 0) // Prevent out of range. //
		{
			Force_IS_volt = 0;
			g_Error_Flag = -202;
		}
		IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
		wait.delay_10_us(100);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			// Take several readings to remove noise //
			for (i=0;i<NumPoints;i++)
			{
				// Readout CC with I2C //
				Write_Word(g_RDADDR, g_READ7, NObin, HEX);
				wait.delay_10_us(100); // Improve repeatability //
				Read_Word(g_RDADDR, ReadWordData);

				// Select the correct readout bits. //
				ReadByteData[0] = ReadWordData[0];
				ReadByteData[1] = ReadWordData[1];
				ReadByteData[2] = ReadWordData[2];
				ReadByteData[3] = ReadWordData[3];
				ReadByteData[4] = ReadWordData[4];
				ReadByteData[5] = ReadWordData[5];
				ReadByteData[6] = ReadWordData[6];
				//ReadByteData[7] = ReadWordData[7];
				ReadByteData[7] = ReadWordData[8]; // Bit 7 is parity bit.  Bit 8 is data bit //

				// Convert binary to decimal. //
				Convert_8bitBinary_To_Decimal(ReadByteData, ResultValue);

				// Save result //
				MeasResult[i] = ResultValue; // 25 expected //
			}
			sum = 0;
			for (i=0;i<NumPoints;i++)
			{
				sum += MeasResult[i];
			}
			iTOL_6p25_mV = sum / NumPoints;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// iTOL_6p25_Avg
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Readout CC with I2C //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ13, NObin, HEX);
			Read_Word(g_RDADDR, ReadWordData);

			// Convert binary to decimal. //
			Convert_16bitBinary_To_Decimal(ReadWordData, ResultValue);

			// Save result //
			iTOL_6p25_Avg = ResultValue; // 25 expected //
		}
	}
	
	// Powerdown //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // SDA and SCL low with DDD. //
	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	//Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	//Mux20_Open_relay(K37);
	//Mux20_Open_relay(K38);
	//Mux20_Open_relay(K40);
	//Mux20_Open_relay(K39);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
	Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	mux_14->open_relay(MUX_2_GND);
	Open_relay(K24); // Disconnect IS pin from 20X buffer. //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//	IS_dvi2k->set_current(IS_ch, 200.0e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(0.5, 0, 0.1);
	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(45); // prevent SR undershoot //
	VBPS_ramp_down(4, 0.2, 200e-3);
	//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	//FB_ovi->connect(2);
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	PiDatalog(func, A_ISVTH, ISVTH, 25, POWER_MILLI);
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_ISVTH_NoCal, ISVTH_NoCal, 25, POWER_MILLI);
		PiDatalog(func, A_ISVTH_NOS, ISVTH_NOS, 25, POWER_MILLI);
		PiDatalog(func, A_ISVTH_NoCal_NOS, ISVTH_NoCal_NOS, 25, POWER_MILLI);
		PiDatalog(func, A_Delta_IOUT, Delta_IOUT, 25, POWER_MILLI);
	}
	
	// Rev C silicon //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		if (g_Char_Enable_P == 1)
		{
			PiDatalog(func, A_AvgReg_LFdly, AvgReg_LFdly, 25, POWER_MILLI);
			PiDatalog(func, A_AvgReg_HFdly, AvgReg_HFdly, 25, POWER_MILLI);
		}
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_iTOL_6p25_mV, iTOL_6p25_mV, 25, POWER_UNIT);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_iTOL_6p25_Avg, iTOL_6p25_Avg, 25, POWER_UNIT);
		}
	}

	// For Rev B3 silicon, no averaging register. //
	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	{
		PiDatalog(func, A_iTOL_19_mV, iTOL_19_mV, 25, POWER_UNIT);
	}

	// Test chip //
	// For Rev C silicon, use averaging register. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		PiDatalog(func, A_iTOL_19_mV_Avg, iTOL_19_mV_Avg, 25, POWER_UNIT);
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_iTOL_32_mV, iTOL_32_mV, 25, POWER_UNIT);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_iTOL_32_mV_Avg, iTOL_32_mV_Avg, 25, POWER_UNIT);
		}
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Iout_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Iout_TT, Iout_TT, 25, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}