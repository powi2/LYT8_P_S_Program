//==============================================================================
// ADC_Pt.cpp (User function)
// 
//    void ADC_Pt_user_init(test_function& func)
//    void ADC_Pt(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "ADC_Pt.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ADC_Pt_user_init(test_function& func)
{
	ADC_Pt_params *ours;
    ours = (ADC_Pt_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ADC_Pt(test_function& func)
{
    // The two lines below must be the first two in the function.
    ADC_Pt_params *ours;
    ours = (ADC_Pt_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_ADC_Pt, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	if (g_Trim_Enable_P == 0)
		return;

	if (g_Fn_ADC_Pt == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float VTOL_Vo3_VFB_p = 0;
	float VTOL_Vo3_20mV_p = 0;
	float VTOL_Vo4_VFB_p = 0;
	float VTOL_Vo4_20mV_p = 0;
	float VTOL_Vo5_VFB_p = 0;
	float VTOL_Vo5_20mV_p = 0;
	float VTOL_Vo6_VFB_p = 0;
	float VTOL_Vo6_20mV_p = 0;
	float VTOL_Vo7_VFB_p = 0;
	float VTOL_Vo7_20mV_p = 0;
	float ADC_Target_S = 1.40; // Trim Target //
	int ADC_TrCode_S = 0;
	int ADC_BitCode_S = 0;
	int EEtr_ADC1_S = 0;
	int EEtr_ADC2_S = 0;
	int EEtr_ADC3_S = 0;
	int EEtr_ADC4_S = 0;
	int EEtr_ADC5_S = 0;
	float ADC_Sim_S = 0;
	float ADC_Sim_Chg_S = 0;
	float ADC_Pt_TT = 0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray_A[16] = {0};
	int WordArray_B[16] = {0};
	int TempArray[30] = {0};
	float WordData = 0;
	float UpperLimit = 0;
	float LowerLimit = 0;
	float VoutForce = 0;
	int READ9_word[16] = {0};
	int READ8_word[16] = {0};
	int CV_Read = 0;
	float CV_Result = 0;
	float Delta = 0;
	float MinDelta = 0;
	float BestCV = 0;
	int Best_TrCode = 0;
	int Best_BitCode = 0;
	float Meas_uVCC = 0;
	float FB_measV = 0;
	Pulse pulse;

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

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

	// BPS //
//	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	//FB_ovi->disconnect(2); // Remove OVI from FB and use DVI2K instead for better accuracy. //
	Mux20_Close_relay(K46); // Connect DVI 2k to COMP pin intead of IS pin. //
	Mux20_Close_relay(K48); // Connect IS pin to ovi. //
	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_10_V); // OVI_3_4 //
	IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->disconnect(2); // Remove OVI from FB and use DVI2K instead for better accuracy. //
	Mux20_Close_relay(K55); // FB (COMP) pin to input of OP07 buffer.  Needed because the internal DAC 
							// ouput resistor is 80kohm, so the input impedance of the measure 
							// instrument needs to be 8Megohm just to get 1% accuracy. //
	Mux20_Close_relay(K56); // Output of OP07 buffer to DVI_13_0, dvi2k //
	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
	dvi_13->set_current(DVI_CHANNEL_0, 0.1e-9, RANGE_20_UA); // DVI_13_0, dvi2k, float //
	dvi_13->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_VOLTAGE); // DVI_13_0, dvi2k // 
	wait.delay_10_us(300); // Wait for relays //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
	uVCC_ovi->set_meas_mode(uVCC_ch, OVI_MEASURE_VOLTAGE); // OVI_3_2 //

	// DDD level //
//	g_DDD_Low = 0.0; // Save current value //
//	g_DDD_High = 3.3; // Save current value //
//	wait.delay_10_us(100);
//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//	wait.delay_10_us(100);

	// SDA //
	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
//	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
//	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup if EEPROM has not yet been written. //
	LoadShadowRegister();

	// Write byte to disable 10msec VI update lockout //
	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);

	// Disable TM_EN_SR_driver //
	Write_Word(g_TM_ANA, 0x0130, NObin, HEX);

	// Write 0x0020 to TM_CTRL.  This will force secondary in control.  Without this, the FB 
	// comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is 
	// the main cause of the FB comparator reference shift. //
	Write_Word(g_TM_CTRL, 0x0A22, NObin, HEX); // Per design (Johnny) 7/26/2017.


	if (g_Char_Enable_P) // Characterization only //
	{
		// Force 3V Vout, Read CV register //
		VoutForce = 3;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_5_RANGE); // DVI_9_0 //

		// uVCC //
		// Force uVCC (LDO) directly to improve measurement stability per design 7/26/2017. //
		// Force exactly uVCC if Vout < uVCC //
		wait.delay_10_us(150);
		Meas_uVCC = uVCC_ovi->measure_average(5);
		uVCC_ovi->set_voltage(uVCC_ch, Meas_uVCC, RANGE_5_V); // OVI_3_2 //
		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		wait.delay_10_us(100);

		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //

		VTOL_Vo3_20mV_p = VoutForce - CV_Result;
		wait.delay_10_us(20);
		VTOL_Vo3_VFB_p = dvi_13->measure_average(25);


		// Force 4V Vout, Read CV register //
		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
		wait.delay_10_us(10);
		VoutForce = 4;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_5_RANGE); // DVI_9_0 //
		
		// Force uVCC (LDO) directly to improve measurement stability per design 7/26/2017. //
		// Force 100mV above uVCC if Vout > uVCC //
		wait.delay_10_us(150);
		Meas_uVCC = uVCC_ovi->measure_average(5);
		uVCC_ovi->set_voltage(uVCC_ch, Meas_uVCC+0.1, RANGE_5_V); // OVI_3_2 //
		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		wait.delay_10_us(300);

		// Read Vout with I2C //
		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo4_20mV_p = VoutForce - CV_Result;
		wait.delay_10_us(20);
		VTOL_Vo4_VFB_p = dvi_13->measure_average(25);


		// Force 5V Vout, Read CV register //
		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
		wait.delay_10_us(10);
		VoutForce = 5;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
		
		// Force uVCC (LDO) directly to improve measurement stability per design 7/26/2017. //
		// Force 100mV above uVCC if Vout > uVCC //
		wait.delay_10_us(150);
		Meas_uVCC = uVCC_ovi->measure_average(5);
		uVCC_ovi->set_voltage(uVCC_ch, Meas_uVCC+0.1, RANGE_5_V); // OVI_3_2 //
		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		wait.delay_10_us(300);

		// Read Vout with I2C //
		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo5_20mV_p = VoutForce - CV_Result;
		wait.delay_10_us(20);
		VTOL_Vo5_VFB_p = dvi_13->measure_average(25);


		// Force 6V Vout, Read CV register //
		VoutForce = 6;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);

		// Read Vout with I2C //
		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo6_20mV_p = VoutForce - CV_Result;
		wait.delay_10_us(20);
		VTOL_Vo6_VFB_p = dvi_13->measure_average(25);

		
		// Force 7V Vout, Read CV register //
		VoutForce = 7;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);

		// Read Vout with I2C //
		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo7_20mV_p = VoutForce - CV_Result;
		wait.delay_10_us(20);
		VTOL_Vo7_VFB_p = dvi_13->measure_average(25);
	}


	// Force 5V Vout, Read CV register //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
	wait.delay_10_us(10);
	VoutForce = 5;
	VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
	
	// Force uVCC (LDO) directly to improve measurement stability per design 7/26/2017. //
	// Force 100mV above uVCC if Vout > uVCC //
	wait.delay_10_us(150);
	Meas_uVCC = uVCC_ovi->measure_average(5);
	uVCC_ovi->set_voltage(uVCC_ch, Meas_uVCC+0.1, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	wait.delay_10_us(600);

	// Measure FB pin voltage //
	g_ADC_Pt = dvi_13->measure_average(25);

	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	WordArray_A[0] = g_ShadowRegister[16];
	WordArray_A[1] = g_ShadowRegister[17];
	WordArray_A[2] = g_ShadowRegister[18];
	WordArray_A[3] = g_ShadowRegister[19];
	WordArray_A[4] = g_ShadowRegister[20];
	WordArray_A[5] = g_ShadowRegister[21];
	WordArray_A[6] = g_ShadowRegister[22];
	WordArray_A[7] = g_ShadowRegister[23];
	WordArray_A[8] = g_ShadowRegister[24];
	WordArray_A[9] = g_ShadowRegister[25];
	WordArray_A[10] = g_ShadowRegister[26];
	WordArray_A[11] = g_ShadowRegister[27];
	WordArray_A[12] = g_ShadowRegister[28];
	WordArray_A[13] = g_ShadowRegister[29];
	WordArray_A[14] = g_ShadowRegister[30];
	WordArray_A[15] = g_ShadowRegister[31]; // EEtr_ADC1_S //

	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	WordArray_B[0] = g_ShadowRegister[96];
	WordArray_B[1] = g_ShadowRegister[97];
	WordArray_B[2] = g_ShadowRegister[98];
	WordArray_B[3] = g_ShadowRegister[99];
	WordArray_B[4] = g_ShadowRegister[100]; // EEtr_ADC2_S //
	WordArray_B[5] = g_ShadowRegister[101]; // EEtr_ADC3_S //
	WordArray_B[6] = g_ShadowRegister[102]; // EEtr_ADC4_S //
	WordArray_B[7] = g_ShadowRegister[103]; // EEtr_ADC5_S //
	WordArray_B[8] = g_ShadowRegister[104];
	WordArray_B[9] = g_ShadowRegister[105];
	WordArray_B[10] = g_ShadowRegister[106];
	WordArray_B[11] = g_ShadowRegister[107];
	WordArray_B[12] = g_ShadowRegister[108];
	WordArray_B[13] = g_ShadowRegister[109];
	WordArray_B[14] = g_ShadowRegister[110];
	WordArray_B[15] = g_ShadowRegister[111];

	// Find trim code closest to target. //
	UpperLimit = 17;
	LowerLimit = -16; 	
	MinDelta = 99999;
	while ( (UpperLimit - LowerLimit) > 1)
	{
		ADC_BitCode_S = (UpperLimit + LowerLimit) / 2;
		
		// Convert BitCode to TrCode. Mapping between bit code and trim code. //
		if(ADC_BitCode_S == -15) ADC_TrCode_S = 15;
		if(ADC_BitCode_S == -14) ADC_TrCode_S = 14;
		if(ADC_BitCode_S == -13) ADC_TrCode_S = 13;
		if(ADC_BitCode_S == -12) ADC_TrCode_S = 12;
		if(ADC_BitCode_S == -11) ADC_TrCode_S = 11;
		if(ADC_BitCode_S == -10) ADC_TrCode_S = 10;
		if(ADC_BitCode_S == -9) ADC_TrCode_S = 9;
		if(ADC_BitCode_S == -8) ADC_TrCode_S = 8;
		if(ADC_BitCode_S == -7) ADC_TrCode_S = 7;
		if(ADC_BitCode_S == -6) ADC_TrCode_S = 6;
		if(ADC_BitCode_S == -5) ADC_TrCode_S = 5;
		if(ADC_BitCode_S == -4) ADC_TrCode_S = 4;
		if(ADC_BitCode_S == -3) ADC_TrCode_S = 3;
		if(ADC_BitCode_S == -2) ADC_TrCode_S = 2;
		if(ADC_BitCode_S == -1) ADC_TrCode_S = 1;
		if(ADC_BitCode_S == 0) ADC_TrCode_S = 0;
		if(ADC_BitCode_S == 1) ADC_TrCode_S = 31;
		if(ADC_BitCode_S == 2) ADC_TrCode_S = 30;
		if(ADC_BitCode_S == 3) ADC_TrCode_S = 29;
		if(ADC_BitCode_S == 4) ADC_TrCode_S = 28;
		if(ADC_BitCode_S == 5) ADC_TrCode_S = 27;
		if(ADC_BitCode_S == 6) ADC_TrCode_S = 26;
		if(ADC_BitCode_S == 7) ADC_TrCode_S = 25;
		if(ADC_BitCode_S == 8) ADC_TrCode_S = 24;
		if(ADC_BitCode_S == 9) ADC_TrCode_S = 23;
		if(ADC_BitCode_S == 10) ADC_TrCode_S = 22;
		if(ADC_BitCode_S == 11) ADC_TrCode_S = 21;
		if(ADC_BitCode_S == 12) ADC_TrCode_S = 20;
		if(ADC_BitCode_S == 13) ADC_TrCode_S = 19;
		if(ADC_BitCode_S == 14) ADC_TrCode_S = 18;
		if(ADC_BitCode_S == 15) ADC_TrCode_S = 17;
		if(ADC_BitCode_S == 16) ADC_TrCode_S = 16;

		// Convert decimal number 'ADC_TrCode_S' into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(ADC_TrCode_S, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray_A[15] = TempArray[0];
		WordArray_B[4] = TempArray[1]; 
		WordArray_B[5] = TempArray[2]; 
		WordArray_B[6] = TempArray[3]; 
		WordArray_B[7] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG1, NOhex, WordArray_A, BIN); // Load trim code to shadow register. //
		Write_Word(g_SREG6, NOhex, WordArray_B, BIN); // Load trim code to shadow register. //
		wait.delay_10_us(100);

		// Measure FB pin voltage //
		wait.delay_10_us(300);
		FB_measV = dvi_13->measure_average(25);

		// Compare //
		//Delta = CV_Result - ADC_Target_S;
		Delta = FB_measV - ADC_Target_S;
		if (Delta < 0) // Remove negative //
			Delta *= -1;
		if (Delta < MinDelta)
		{
			MinDelta = Delta;
			//BestCV = CV_Result;
			BestCV = FB_measV;
			Best_TrCode = ADC_TrCode_S;
			Best_BitCode = ADC_BitCode_S;
			if (FB_measV == ADC_Target_S) // Found best code, don't need to search anymore. //
				break;
		}
		if (FB_measV < ADC_Target_S) // Below target //
			LowerLimit = ADC_BitCode_S;
		else // Above target //
			UpperLimit = ADC_BitCode_S;
	}
	ADC_Sim_S = BestCV;
	ADC_TrCode_S = Best_TrCode;
	ADC_BitCode_S = Best_BitCode;
	ADC_Sim_Chg_S = ((ADC_Sim_S - g_ADC_Pt) / g_ADC_Pt)*100; // In percent //
	
	// Load the shadow register with the final trim code ADC_TrCode_S.  Must not overwrite any of the other shadow register bits! //	
	Convert_Decimal_To_Binary(ADC_TrCode_S, TempArray); // Convert decimal number 'ADC_TrCode_S' into binary number and store in TempArray[]. // 

	// Load TempArray[] to WordArray[] at correct bit locations. //
	WordArray_A[15] = TempArray[0];
	WordArray_B[4] = TempArray[1]; 
	WordArray_B[5] = TempArray[2]; 
	WordArray_B[6] = TempArray[3]; 
	WordArray_B[7] = TempArray[4]; 

	// Load final trim code to shadow register. //
	Write_Word(g_SREG1, NOhex, WordArray_A, BIN); // Load trim code to shadow register. //
	Write_Word(g_SREG6, NOhex, WordArray_B, BIN); // Load trim code to shadow register. //

	// Save the new values to the g_ShadowRegister[] array. //
	g_ShadowRegister[31] = WordArray_A[15];
	g_ShadowRegister[100] = WordArray_B[4];
	g_ShadowRegister[101] = WordArray_B[5];
	g_ShadowRegister[102] = WordArray_B[6];
	g_ShadowRegister[103] = WordArray_B[7];

	// Load individual bits for datalogging //
	EEtr_ADC1_S = WordArray_A[15];
	EEtr_ADC2_S = WordArray_B[4];
	EEtr_ADC3_S = WordArray_B[5];
	EEtr_ADC4_S = WordArray_B[6];
	EEtr_ADC5_S = WordArray_B[7];

	// Powerdown //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);
	wait.delay_10_us(5);
	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
	dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39);
	Mux20_Open_relay(K46);
	Mux20_Open_relay(K48);
	Mux20_Open_relay(K55);
	Mux20_Open_relay(K56);
	VO_dvi->set_voltage(VO_ch, 1, VOLT_5_RANGE); // DVI_9_0, prevent undershoot //
	wait.delay_10_us(20);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(1, 0, 0.1);
	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(45); // prevent SR undershoot //
	FB_ovi->connect(2);
	Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(5);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
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
	PiDatalog(func, A_ADC_Pt, g_ADC_Pt, 25, POWER_UNIT);
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo3_VFB_p, VTOL_Vo3_VFB_p, 25, POWER_UNIT);
		PiDatalog(func, A_VTOL_Vo3_20mV_p, VTOL_Vo3_20mV_p, 25, POWER_MILLI);
		PiDatalog(func, A_VTOL_Vo4_VFB_p, VTOL_Vo4_VFB_p, 25, POWER_UNIT);
		PiDatalog(func, A_VTOL_Vo4_20mV_p, VTOL_Vo4_20mV_p, 25, POWER_MILLI);
		PiDatalog(func, A_VTOL_Vo5_VFB_p, VTOL_Vo5_VFB_p, 25, POWER_UNIT);
		PiDatalog(func, A_VTOL_Vo5_20mV_p, VTOL_Vo5_20mV_p, 25, POWER_MILLI);
		PiDatalog(func, A_VTOL_Vo6_VFB_p, VTOL_Vo6_VFB_p, 25, POWER_UNIT);
		PiDatalog(func, A_VTOL_Vo6_20mV_p, VTOL_Vo6_20mV_p, 25, POWER_MILLI);
		PiDatalog(func, A_VTOL_Vo7_VFB_p, VTOL_Vo7_VFB_p, 25, POWER_UNIT);
		PiDatalog(func, A_VTOL_Vo7_20mV_p, VTOL_Vo7_20mV_p, 25, POWER_MILLI);
	}
	PiDatalog(func, A_ADC_Target_S, ADC_Target_S, 25, POWER_UNIT);
	PiDatalog(func, A_ADC_TrCode_S, ADC_TrCode_S, 25, POWER_UNIT);
	PiDatalog(func, A_ADC_BitCode_S, ADC_BitCode_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_ADC1_S, EEtr_ADC1_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_ADC2_S, EEtr_ADC2_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_ADC3_S, EEtr_ADC3_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_ADC4_S, EEtr_ADC4_S, 25, POWER_UNIT);
	PiDatalog(func, A_EEtr_ADC5_S, EEtr_ADC5_S, 25, POWER_UNIT);
	PiDatalog(func, A_ADC_Sim_S, ADC_Sim_S, 25, POWER_UNIT);
	PiDatalog(func, A_ADC_Sim_Chg_S, ADC_Sim_Chg_S, 25, POWER_UNIT);

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		ADC_Pt_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_ADC_Pt_TT, ADC_Pt_TT, 25, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
