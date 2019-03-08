//==============================================================================
// CCoff_Pt.cpp (User function)
// 
//    void CCoff_Pt_user_init(test_function& func)
//    void CCoff_Pt(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "CCoff_Pt.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CCoff_Pt_user_init(test_function& func)
{
	CCoff_Pt_params *ours;
    ours = (CCoff_Pt_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CCoff_Pt(test_function& func)
{
    // The two lines below must be the first two in the function.
    CCoff_Pt_params *ours;
    ours = (CCoff_Pt_params *)func.params;
	
	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_CCoff_Pt, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;	

	// Skip trimming if g_Trim_Enable_P set //
	if (g_Trim_Enable_P == 0)
		return;

	if (g_Fn_CCoff_Pt == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//int CCoff_Pt_S =0;
	//g_CCoff_Target_S = 128;
	g_CCoff_Target_S = gISvth_TARGET_Trimops;
	int CCoff_TrCode_S =0;
	int CCoff_BitCode_S =0;
	int EEtr_CCoff1_S =0;
	int EEtr_CCoff2_S =0;
	int EEtr_CCoff3_S =0;
	float CCoff_Sim_S =0;
	float CCoff_Sim_Chg_S =0;
	float CCoff_Pt_TT =0;
	int HighCount = 0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	int READ58_word[16] = {0};
	int TempArray[30] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	int reg_CC_Data = 0;
	float SRpinVolt = 0;
	float WordData = 0;
	float Vforce = 0;
	float V_Step = 0;
	int LoopCnt = 0;
	float ISVTH_FromAbove = 0;
	float ISVTH_FromBelow = 0;
	float MinDelta = 0;
	float Delta = 0;
	float ISVTH_Temp = 0;
	float Best_ISVTH = 0;
	float Best_TrCode = 0;
	float Best_BitCode = 0;
	float UpperSearchLimit = 0;
	float LowerSearchLimit = 0;
	int i =0;
*/
	// Test not needed.  May add again later if needed per design. //
/*	
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
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 3.3; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

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
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
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

	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup if EEPROM has not yet been written. //
	LoadShadowRegister();

	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);

	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX); // Write byte to disable 10msec VI update lockout //

	//Write I2C command to connect output of CC comparator to FB pin //
	Write_Word(g_TM_SEL, 0x0026, NObin, HEX); // Write the I2C command to connect the output of the CC comparator to SR pin. //

	// If bit[38]: assign trim_CCesr was trimmed (set to 1), need to set back to 0 to disable Vesr CC for these tests. //
	if (g_ShadowRegister[38] == 1) // bit[38]: assign trim_CCesr //
	{
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
		Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //

		WordArray[0] = READ58_word[0];
		WordArray[1] = READ58_word[1];
		WordArray[2] = READ58_word[2];
		WordArray[3] = READ58_word[3];
		WordArray[4] = READ58_word[4];
		WordArray[5] = READ58_word[5];
		WordArray[6] = READ58_word[6]; // bit[38]: assign trim_CCesr //
		WordArray[7] = READ58_word[7];
		WordArray[8] = READ58_word[8];
		WordArray[9] = READ58_word[9];
		WordArray[10] = READ58_word[10];
		WordArray[11] = READ58_word[11];
		WordArray[12] = READ58_word[12];
		WordArray[13] = READ58_word[13];
		WordArray[14] = READ58_word[14];
		WordArray[15] = READ58_word[15];

		// bit[38]: assign trim_CCesr set to 0 to disable Vesr CC. //
		WordArray[6] = 0;
		Write_Word(g_SREG2, NOhex, WordArray, BIN);
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ISVTH //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
	// and [7] and [15] are odd parity bits.  
	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
	// Write maximum CC 128 (100%) with I2C //
	WordData = 384; // With parity //
	Write_Word(g_CC_reg, WordData, NObin, HEX); // CC register //

	// Linear search steps from above //
	UpperSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_max_limit_val[0])*1.1; // Get upper search limit //
	LowerSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_min_limit_val[0])*0.9; // Get lower search limit //
	//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
	//{
	//	UpperSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_max_limit_val[0])*1.5; // Get upper search limit //
	//	LowerSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_min_limit_val[0])*0.5; // Get lower search limit //
	//}
	//UpperSearchLimit *= 20; // IS pin is connected to 20X buffer. //
	//LowerSearchLimit *= 20; // IS pin is connected to 20X buffer. //
	UpperSearchLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
	LowerSearchLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
	Vforce = UpperSearchLimit;
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
	while (Vforce > LowerSearchLimit && LoopCnt < 400)
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
	Vforce = LowerSearchLimit;
	if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
	{
		Vforce = 0;
		g_Error_Flag = -158;
	}
	LoopCnt = 0;
	Vforce -= V_Step;
	IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(100);
	while (Vforce < UpperSearchLimit && LoopCnt < 400)
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
	g_CCoff_Pt_S = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

	// IS pin connected to 20X buffer. //
	//g_CCoff_Pt_S /= 20;
	g_CCoff_Pt_S /= g_ISbuff_Gain32;

	// Get ready for searching trim codes //
	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	WordArray[0] = g_ShadowRegister[64];
	WordArray[1] = g_ShadowRegister[65];
	WordArray[2] = g_ShadowRegister[66];
	WordArray[3] = g_ShadowRegister[67];
	WordArray[4] = g_ShadowRegister[68];
	WordArray[5] = g_ShadowRegister[69]; // EEtr_CCoff1_S //
	WordArray[6] = g_ShadowRegister[70]; // EEtr_CCoff2_S //
	WordArray[7] = g_ShadowRegister[71]; // EEtr_CCoff3_S //
	WordArray[8] = g_ShadowRegister[72];
	WordArray[9] = g_ShadowRegister[73];
	WordArray[10] = g_ShadowRegister[74];
	WordArray[11] = g_ShadowRegister[75];
	WordArray[12] = g_ShadowRegister[76];
	WordArray[13] = g_ShadowRegister[77];
	WordArray[14] = g_ShadowRegister[78];
	WordArray[15] = g_ShadowRegister[79];

	// Find trim code closest to target. //
	//Write_Byte(g_CC_reg, g_CCoff_Target_S, NObin, HEX); // CC register must be set to CCoff_Target_S. //
	//Write_Byte(g_CC_reg, 128, NObin, HEX); // CC register must be set to CCoff_Target_S. //
	UpperLimit = 4;
	LowerLimit = -5;
	MinDelta = 99999;
	while ( (UpperLimit - LowerLimit) > 1)
	{
		CCoff_BitCode_S = (UpperLimit + LowerLimit) / 2;
		
		// Convert BitCode to TrCode. Mapping between bit code and trim code. //
		if(CCoff_BitCode_S == -4) CCoff_TrCode_S = 4;
		if(CCoff_BitCode_S == -3) CCoff_TrCode_S = 5;
		if(CCoff_BitCode_S == -2) CCoff_TrCode_S = 6;
		if(CCoff_BitCode_S == -1) CCoff_TrCode_S = 7;
		if(CCoff_BitCode_S == 0) CCoff_TrCode_S = 0;
		if(CCoff_BitCode_S == 1) CCoff_TrCode_S = 1;
		if(CCoff_BitCode_S == 2) CCoff_TrCode_S = 2;
		if(CCoff_BitCode_S == 3) CCoff_TrCode_S = 3;


		// Convert decimal number 'CCoff_TrCode_S' into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(CCoff_TrCode_S, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[5] = TempArray[0];
		WordArray[6] = TempArray[1];
		WordArray[7] = TempArray[2];

		// Load new trim code to shadow register. //
		Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
		wait.delay_10_us(100);
	
		// Linear search steps from above //
		UpperSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_min_limit_val[0])*0.9; // Get lower search limit //
		//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		//{
		//	UpperSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_max_limit_val[0])*1.5; // Get upper search limit //
		//	LowerSearchLimit = (func.dlog->tests[A_CCoff_Pt_S].f_min_limit_val[0])*0.5; // Get lower search limit //
		//}
		//UpperSearchLimit *= 20; // IS pin is connected to 20X buffer. //
		//LowerSearchLimit *= 20; // IS pin is connected to 20X buffer. //
		UpperSearchLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		LowerSearchLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
		Vforce = UpperSearchLimit;
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
		while (Vforce > LowerSearchLimit && LoopCnt < 400)
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
		Vforce = LowerSearchLimit;
		if (Vforce < -1.999 || Vforce > 1.999) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -158;
		}
		LoopCnt = 0;
		Vforce -= V_Step;
		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(100);
		while (Vforce < UpperSearchLimit && LoopCnt < 400)
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
		ISVTH_Temp = (ISVTH_FromAbove + ISVTH_FromBelow) / 2;

		// IS pin connected to 20X buffer. //
		//ISVTH_Temp /= 20;
		ISVTH_Temp /= g_ISbuff_Gain32;

		// Check if ISVTH_Temp is above or below the target. //
		Delta = ISVTH_Temp - g_CCoff_Target_S;
		if (Delta < 0) // Remove negative //
			Delta *= -1;
		if (Delta < MinDelta)
		{
			MinDelta = Delta;
			Best_ISVTH = ISVTH_Temp;
			Best_TrCode = CCoff_TrCode_S;
			Best_BitCode = CCoff_BitCode_S;
		}
		if (ISVTH_Temp < g_CCoff_Target_S) // Below target //
			LowerLimit = CCoff_BitCode_S;
		else // Above target //
			UpperLimit = CCoff_BitCode_S;		
	}
	CCoff_Sim_S = Best_ISVTH;
	CCoff_TrCode_S = Best_TrCode;
	CCoff_BitCode_S = Best_BitCode;
	CCoff_Sim_Chg_S = ((CCoff_Sim_S - g_CCoff_Pt_S) / g_CCoff_Pt_S)*100; // In percent //

	// Load the shadow register with the final trim code CCoff_TrCode_S.  Must not overwrite any of the other shadow register bits! //	
	Convert_Decimal_To_Binary(CCoff_TrCode_S, TempArray); // Convert decimal number 'CCoff_TrCode_S' into binary number and store in TempArray[]. // 

	// Load TempArray[] to WordArray[] at correct bit locations. //
	WordArray[5] = TempArray[0];
	WordArray[6] = TempArray[1];
	WordArray[7] = TempArray[2];

	// Load final trim code to shadow register. //
	Write_Word(g_SREG4, NOhex, WordArray, BIN); // Load trim code to shadow register. //
	wait.delay_10_us(100);

	// Save the new values to the g_ShadowRegister[] array. //
	g_ShadowRegister[69] = WordArray[5];
	g_ShadowRegister[70] = WordArray[6];
	g_ShadowRegister[71] = WordArray[7];

	// Load individual bits for datalogging //
	EEtr_CCoff1_S = WordArray[5];
	EEtr_CCoff2_S = WordArray[6];
	EEtr_CCoff3_S = WordArray[7];

	// Powerdown //
	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
	Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	mux_14->open_relay(MUX_2_GND);
	Open_relay(K24); // Disconnect IS pin from 20X buffer. //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(0.5, 0, 0.1);
	wait.delay_10_us(45); // prevent SR undershoot //
	VBPS_ramp_down(4, 0.2, 200e-3);
	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	FB_ovi->connect(2);
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	PiDatalog(func, A_CCoff_Pt_S, g_CCoff_Pt_S, 25, POWER_UNIT);
	PiDatalog(func, A_CCoff_Target_S, g_CCoff_Target_S, 25, POWER_UNIT);
	PiDatalog(func, A_CCoff_TrCode_S, CCoff_TrCode_S, 25, POWER_UNIT);
	PiDatalog(func, A_CCoff_BitCode_S, CCoff_BitCode_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_CCoff1_S, EEtr_CCoff1_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_CCoff2_S, EEtr_CCoff2_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_CCoff3_S, EEtr_CCoff3_S, 25, POWER_UNIT);
	PiDatalog(func, A_CCoff_Sim_S, CCoff_Sim_S, 25, POWER_UNIT);
	PiDatalog(func, A_CCoff_Sim_Chg_S, CCoff_Sim_Chg_S, 25, POWER_UNIT);
	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		CCoff_Pt_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_CCoff_Pt_TT, CCoff_Pt_TT, 25, POWER_MILLI);
	}
	

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
	
}
