//==============================================================================
// UVP.cpp (User function)
// 
//    void UVP_user_init(test_function& func)
//    void UVP(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "UVP.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void UVP_user_init(test_function& func)
{
	UVP_params *ours;
    ours = (UVP_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void UVP(test_function& func)
{
    // The two lines below must be the first two in the function.
    UVP_params *ours;
    ours = (UVP_params *)func.params;

	// Increment function number //
	gFuncNum++;
////
////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_UVP, gFuncNum, 25, POWER_UNIT);
////
////	if (!g_Char_Enable_P) // Characterization only //
////		return;
////
////	// Skip Test if AbortTest set //
////	if (AbortTest)
////		return;
////
////	if (g_Fn_UVP == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	float V_UVP_3 = 0;
////	float V_UVP_8 = 0;
////	float V_UVP_14 = 0;
////	float V_UVP_19 = 0;
////	float V_UVP_24 = 0;
////	float Delta_V_UVP = 0;
////	float t_UVP_8 = 0;
////	float t_UVP_16 = 0;
////	float t_UVP_32 = 0;
////	float t_UVP_64 = 0;
////	float UVP_TT = 0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	int READ59_word[16] = {0};
////	int READ62_word[16] = {0};
////	int WordArray[16] = {0};
////	int TempArray[30] = {0};
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	float Vforce = 0;
////	float SRpinVolt = 0;
////	Pulse pulse;
////	float WordData = 0;
////	int READ20_word[16] = {0};
////	int READ10_word[16] = {0};
////	//float V_UVP_7_9 = 0;
////	float V_UVP_7 = 0;
////	int Loop_Count = 0;
////	float VoutV = 0;
////	int ReadTotal = 0;
////	float TMUmeas = 0;	
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
////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////	// COMP //
////	FB_ovi->disconnect(2);
////
////	// VBD //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////	wait.delay_10_us(25); // Prevent glitch //
////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
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
////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////	// SCL //
////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////	
////	// Set DDD for I2C. //
////	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		
////	// Wait for relays //
////	wait.delay_10_us(200); 
////
////	// Powerup //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////	// I2C into test mode. //  
////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////	// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
////	// stairsteps up slowly, with CV only mode it steps up in a single step. //
////	if (g_SiliconRev_Sec == 5) // Rev C silicon //
////	{
////		Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
////	}
////
////	// Shadow register bits 63 and 104 need to be set to 0. //
////	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////	{
////		/*
////		// Read out contents of shadow register.  Can't overwrite shadow register. //
////		Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
////		Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
////
////		WordArray[0] = READ59_word[0];
////		WordArray[1] = READ59_word[1];
////		WordArray[2] = READ59_word[2];
////		WordArray[3] = READ59_word[3];
////		WordArray[4] = READ59_word[4];
////		WordArray[5] = READ59_word[5];
////		WordArray[6] = READ59_word[6];
////		WordArray[7] = READ59_word[7];
////		WordArray[8] = READ59_word[8];
////		WordArray[9] = READ59_word[9];
////		WordArray[10] = READ59_word[10];
////		WordArray[11] = READ59_word[11];
////		WordArray[12] = READ59_word[12];
////		WordArray[13] = READ59_word[13];
////		WordArray[14] = READ59_word[14];
////		WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
////		*/
////		WordArray[0] = g_EE_ShadReg48;
////		WordArray[1] = g_EE_ShadReg49;
////		WordArray[2] = g_EE_ShadReg50;
////		WordArray[3] = g_EE_ShadReg51;
////		WordArray[4] = g_EE_ShadReg52;
////		WordArray[5] = g_EE_ShadReg53;
////		WordArray[6] = g_EE_ShadReg54;
////		WordArray[7] = g_EE_ShadReg55;
////		WordArray[8] = g_EE_ShadReg56;
////		WordArray[9] = g_EE_ShadReg57;
////		WordArray[10] = g_EE_ShadReg58;
////		WordArray[11] = g_EE_ShadReg59;
////		WordArray[12] = g_EE_ShadReg60;
////		WordArray[13] = g_EE_ShadReg61;
////		WordArray[14] = g_EE_ShadReg62;
////		WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
////
////		// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
////		WordArray[15] = 0;
////		Write_Word(g_SREG3, NOhex, WordArray, BIN);
////
////		// Read out contents of shadow register.  Can't overwrite shadow register. //
////		/*
////		Write_Word(g_RDADDR, g_READ62, NObin, HEX); // SREG6.  Shadow register. //
////		Read_Word(g_RDADDR, READ62_word); // SREG6.  Shadow register. //
////
////		WordArray[0] = READ62_word[0];
////		WordArray[1] = READ62_word[1];
////		WordArray[2] = READ62_word[2];
////		WordArray[3] = READ62_word[3];
////		WordArray[4] = READ62_word[4];
////		WordArray[5] = READ62_word[5];
////		WordArray[6] = READ62_word[6];
////		WordArray[7] = READ62_word[7];
////		WordArray[8] = READ62_word[8]; // eep_sreg[104]: trim_ldo_3p6v //
////		WordArray[9] = READ62_word[9];
////		WordArray[10] = READ62_word[10];
////		WordArray[11] = READ62_word[11];
////		WordArray[12] = READ62_word[12];
////		WordArray[13] = READ62_word[13];
////		WordArray[14] = READ62_word[14];
////		WordArray[15] = READ62_word[15];
////		*/
////		WordArray[0] = g_EE_ShadReg96;
////		WordArray[1] = g_EE_ShadReg97;
////		WordArray[2] = g_EE_ShadReg98;
////		WordArray[3] = g_EE_ShadReg99;
////		WordArray[4] = g_EE_ShadReg100;
////		WordArray[5] = g_EE_ShadReg101;
////		WordArray[6] = g_EE_ShadReg102;
////		WordArray[7] = g_EE_ShadReg103;
////		WordArray[8] = g_EE_ShadReg104; // eep_sreg[104]: trim_ldo_3p6v //
////		WordArray[9] = g_EE_ShadReg105;
////		WordArray[10] = g_EE_ShadReg106;
////		WordArray[11] = g_EE_ShadReg107;
////		WordArray[12] = g_EE_ShadReg108;
////		WordArray[13] = g_EE_ShadReg109;
////		WordArray[14] = g_EE_ShadReg110;
////		WordArray[15] = g_EE_ShadReg111;
////
////		// eep_sreg[104]: trim_ldo_3p6v //
////		WordArray[8] = 0;
////		Write_Word(g_SREG6, NOhex, WordArray, BIN);
////	}
////
////	// Write byte to disable 10msec VI update lockout //
////	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////
////	// Float SR dvi //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////
////	// Connect the "VOUT_UV_AR_chy" comparator output to SR pin. Test mode 27. //
////	// To observe Vout under voltage fault when SR pin flips. //
////	Write_Word(g_TM_SEL, 26, NObin, HEX);
////	
////	// Write register to put secondary in control //
////	Write_Word(g_TM_CTRL, 0x0020, NObin, HEX); 
////
////	// Reduce UVL timer to minimum //
////	//Write_Byte(g_UVL_Timer, 0x00, NObin, HEX);
////
////	// V_UVP_3 test.  Program UVA to 3.0V, search for threshold. //
////	// Check secondary silicon revision //
////	// WordData = 30; // 100mV per LSB.  For example, to set 3.0V,  WordData = 3.0/0.1 = 30. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	WordData = 32926; 
////	Write_Word(g_UVA, WordData, NObin, HEX);
////
////	// Binary search for under-voltage threshold. //
////	// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
////	UpperLimit = (func.dlog->tests[A_V_UVP_3].f_max_limit_val[0])*1.1; // Get upper search limit //
////	LowerLimit = (func.dlog->tests[A_V_UVP_3].f_min_limit_val[0])*0.9; // Get lower search limit //	
////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////	{
////		UpperLimit = (func.dlog->tests[A_V_UVP_3].f_max_limit_val[0])*1.4; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_V_UVP_3].f_min_limit_val[0])*0.5; // Get lower search limit //	
////	}
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -137;
////	}
////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
////	wait.delay_10_us(50);
////	while ( (UpperLimit - LowerLimit) > .005)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -137;
////			break;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
////		wait.delay_10_us(100);
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1) // Check bit "vout_uv_comp" in READ10 register. //
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;	
////	}
////	V_UVP_3 = Vforce;
////
////	// Write the I2C command to set_CV.  Needed to change to higher readback range.  3 ranges 
////	// total for Rev.2 silicon: 0-6, 6-10, and 10-24V.  Need to set CV using customer 
////	// programmable register to force part to go into next range. //
////	// WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	WordData = 34336; // 8V //
////	Write_Word(g_CV_reg, WordData, NObin, HEX);
////	wait.delay_10_us(100); // Needed //
////
////	// V_UVP_7 test.  Program UVA to 7V, search for threshold. //
////	// WordData = 70; // 100mV per LSB.  For example, to set 7.0V,  WordData = 7.0/0.1 = 70. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	WordData = 32838; // 7V //
////	Write_Word(g_UVA, WordData, NObin, HEX);
////
////	// Binary search for under-voltage threshold. //
////	// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////	UpperLimit = 8.5;
////	LowerLimit = 5.5;
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -137;
////	}
////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
////	wait.delay_10_us(50);
////	while ( (UpperLimit - LowerLimit) > .005)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -137;
////			break;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
////		wait.delay_10_us(100);
////
////		/*
////		ReadTotal = 0;
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////			
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		if ( ReadTotal > 2)
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;
////		*/
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1)
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;		
////	}
////	V_UVP_7 = Vforce;
////
////
////	// V_UVP_8 test.  Program UVA to 8V, search for threshold. //
////	// WordData = 79; // 100mV per LSB.  For example, to set 7.9V,  WordData = 7.9/0.1 = 79. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	WordData = 32976; // 8V //
////	Write_Word(g_UVA, WordData, NObin, HEX);
////
////	// Binary search for under-voltage threshold. //
////	// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////	UpperLimit = (func.dlog->tests[A_V_UVP_8].f_max_limit_val[0])*1.1; // Get upper search limit //
////	LowerLimit = (func.dlog->tests[A_V_UVP_8].f_min_limit_val[0])*0.9; // Get lower search limit //	
////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////	{
////		UpperLimit = (func.dlog->tests[A_V_UVP_8].f_max_limit_val[0])*1.4; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_V_UVP_8].f_min_limit_val[0])*0.5; // Get lower search limit //	
////	}
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -137;
////	}
////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
////	wait.delay_10_us(50);
////	while ( (UpperLimit - LowerLimit) > .005)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -137;
////			break;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
////		wait.delay_10_us(100);
////
////		/*
////		ReadTotal = 0;
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //	
////		if ( READ10_word[1] == 1)
////			ReadTotal++;
////	
////		if ( ReadTotal > 2)
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;
////		*/
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1)
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;		
////	}
////	V_UVP_8 = Vforce;
////
////	// Calculate difference between two adjacent steps. //
////	Delta_V_UVP = (V_UVP_8 - V_UVP_7) / 10;
////
////	// Write the I2C command to set_CV //
////	// WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	WordData = 2124; // 11V //
////	Write_Word(g_CV_reg, WordData, NObin, HEX);
////	wait.delay_10_us(100); // Needed //
////
////	if (g_Char_Enable_P) // Characterization only //
////	{
////
////		// V_UVP_14 test.  Program UVA to 14V, search for threshold. //
////		// WordData = 79; // 100mV per LSB.  For example, to set 7.9V,  WordData = 7.9/0.1 = 79. //
////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////		// and [7] and [15] are odd parity bits.  
////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////		WordData = 396; // 14V //
////		Write_Word(g_UVA, WordData, NObin, HEX);
////	
////		// Binary search for under-voltage threshold. //
////		// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////		UpperLimit = (func.dlog->tests[A_V_UVP_14].f_max_limit_val[0])*1.1; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_V_UVP_14].f_min_limit_val[0])*0.9; // Get lower search limit //	
//////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//////		{
//////			UpperLimit = (func.dlog->tests[A_V_UVP_14].f_max_limit_val[0])*1.4; // Get upper search limit //
//////			LowerLimit = (func.dlog->tests[A_V_UVP_14].f_min_limit_val[0])*0.5; // Get lower search limit //	
//////		}
////		Vforce = (UpperLimit + LowerLimit) / 2;
////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -137;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(50);
////		while ( (UpperLimit - LowerLimit) > .005)
////		{
////			Vforce = (UpperLimit + LowerLimit) / 2; 
////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////			{
////				Vforce = 0;
////				g_Error_Flag = -137;
////				break;
////			}
////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////			wait.delay_10_us(100);
////
////			// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////			Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////			Read_Word(g_RDADDR, READ10_word); // READ10 //		
////			if ( READ10_word[1] == 1) // Check bit "vout_uv_comp" in READ10 register. //
////				LowerLimit = Vforce;
////			else
////				UpperLimit = Vforce;		
////		}
////		V_UVP_14 = Vforce;
////
////		// V_UVP_19 test.  Program UVA to 19V, search for threshold. //
////		// Program Output Under-voltage Threshold to 19V //
////		// WordData = 79; // 100mV per LSB.  For example, to set 7.9V,  WordData = 7.9/0.1 = 79. //
////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////		// and [7] and [15] are odd parity bits.  
////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////		WordData = 318; // 19V //
////		Write_Word(g_UVA, WordData, NObin, HEX);
////	
////		// Binary search for over-voltage threshold. //
////		// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////		UpperLimit = (func.dlog->tests[A_V_UVP_19].f_max_limit_val[0])*1.1; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_V_UVP_19].f_min_limit_val[0])*0.9; // Get lower search limit //	
//////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//////		{
//////			UpperLimit = (func.dlog->tests[A_V_UVP_19].f_max_limit_val[0])*1.4; // Get upper search limit //
//////			LowerLimit = (func.dlog->tests[A_V_UVP_19].f_min_limit_val[0])*0.5; // Get lower search limit //	
//////		}
////		Vforce = (UpperLimit + LowerLimit) / 2;
////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -137;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(50);
////		while ( (UpperLimit - LowerLimit) > .005)
////		{
////			Vforce = (UpperLimit + LowerLimit) / 2; 
////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////			{
////				Vforce = 0;
////				g_Error_Flag = -137;
////				break;
////			}
////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////			wait.delay_10_us(100);
////
////			// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////			Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////			Read_Word(g_RDADDR, READ10_word); // READ10 //		
////			if ( READ10_word[1] == 1) // Check bit "vout_uv_comp" in READ10 register. //
////				LowerLimit = Vforce;
////			else
////				UpperLimit = Vforce;
////		}
////		V_UVP_19 = Vforce;
////	}
////
////	// V_UVP_24 test.  Program UVA to 24V, search for threshold. //
////	// Program Output Under-voltage Threshold to 19V //
////	// WordData = 79; // 100mV per LSB.  For example, to set 7.9V,  WordData = 7.9/0.1 = 79. //
////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////	// and [7] and [15] are odd parity bits.  
////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////	//WordData = 486; // 23V //
////	WordData = 368; // 24V //
////	Write_Word(g_UVA, WordData, NObin, HEX);
////
////	// Binary search for over-voltage threshold. //
////	// Look at "VOUT_UV_AR_chy" comparator output on SR pin. //
////	UpperLimit = (func.dlog->tests[A_V_UVP_24].f_max_limit_val[0])*1.1; // Get upper search limit //
////	LowerLimit = (func.dlog->tests[A_V_UVP_24].f_min_limit_val[0])*0.9; // Get lower search limit //	
//////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//////	{
//////		UpperLimit = (func.dlog->tests[A_V_UVP_24].f_max_limit_val[0])*1.4; // Get upper search limit //
//////		LowerLimit = (func.dlog->tests[A_V_UVP_24].f_min_limit_val[0])*0.5; // Get lower search limit //	
//////	}
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -187;
////	}
////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////	wait.delay_10_us(50);
////	while ( (UpperLimit - LowerLimit) > .005)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -187;
////			break;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(100);
////
////		// Check bit "vout_uv_comp" in READ10 register to see if UVA has been triggered. //
////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
////		Read_Word(g_RDADDR, READ10_word); // READ10 //		
////		if ( READ10_word[1] == 1) // Check bit "vout_uv_comp" in READ10 register. //
////			LowerLimit = Vforce;
////		else
////			UpperLimit = Vforce;	
////	}
////	V_UVP_24 = Vforce;
////
////	// Power down //
////	//Open_relay(K2);
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	Open_relay(K18);
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	FB_ovi->connect(2);
////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCCrampDown(0.5, 0, 0.1);
////	wait.delay_10_us(45); // prevent SR undershoot //
////	VBPS_ramp_down(4, 0.2, 200e-3);
////	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	Mux20_Open_relay(K64);
////	Mux20_Open_relay(K38);
////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////	wait.delay_10_us(200); // Prevent SDA undershoot below GND //
////	Mux20_Open_relay(K37);
////	Mux20_Open_relay(K40);
////	Mux20_Open_relay(K39);
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////
////	if (g_Char_Enable_P) // Characterization only //
////	{
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// t_UVP tests
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		
////		// t_UVP_8 test //	
////		
////		// Open all relays //
////		Initialize_Relays();
////
////		// Initialize Instruments //
////		Initialize_Instruments();
////
////		// Drain //
////		Close_relay(K3);
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
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
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
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////		
////		// COMP //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
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
//////		Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////		
////		// Set DDD for I2C. //
////	//	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////	//	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////
////// Set DSM clock frequency //
////DSM_set_vector_clock_freq(DSM_CONTEXT, 1200); // Freq in kHZ, 1200/4 = 300kHz clock frequency //  // Add I2C DSM //
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup Secondary //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// Disable watchdog timer //
//////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////
////
//////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////wait.delay_10_us(10);
////
////		//Setup Vpin for digital clocking
////		VPIN_ovi->disconnect(OVI_CHANNEL_1);	
////
////		// Initialize DDD
////		ddd_7->ddd_set_clock_period(Dclk_period);
//////		wait.delay_10_us(100);
////		ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////		wait.delay_10_us(100);
////
////		// DDD level //
//////		g_DDD_Low = 0.0; // Save current value //
//////		g_DDD_High = 4.0; // Save current value //
//////		wait.delay_10_us(100);
//////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////		wait.delay_10_us(100);
////
//////		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////		wait.delay_10_us(10);
////		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////		wait.delay_10_us(300);
//////		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////	Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
////	//	wait.delay_10_us(50);
////	wait.delay_10_us(70);
////
////		// DDD level //
////		g_DDD_Low = 0.0; // Save current value //
////		g_DDD_High = 3.3; // Save current value //
////		wait.delay_10_us(g_DDDwait);
////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(g_DDDwait);
////
////		// VBP_P drops when secondary has control //
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////		wait.delay_10_us(8);
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////		wait.delay_10_us(10);
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		wait.delay_10_us(20);
////
////		// Setup TMU //
////		tmu_6->init();
////		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
////		tmu_6->start_trigger_setup(1, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->start_holdoff(0,FALSE);
////		tmu_6->stop_holdoff(0,FALSE);
////		wait.delay_10_us(200);
////
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enable the timer is 8X longer. //
//////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////
////		// Set UVL timer to 8msec //
//////		Write_Byte(g_UVL_Timer, 0x00, NObin, HEX); // 8ms //
////	DSM_Write_Byte(g_UVL_Timer, 0x00); // 8ms //
////
////		// Device should be switching //
////		//tmu_6->arm();					
////		//wait.delay_10_us(20);
////		//TMUmeas = tmu_6->read();
////		//if (TMUmeas < 0.1e-9) // Not switching //
////		//	g_Error_Flag = -144;
////
////		// Pull Vout below UVA.  UVA is 3.6V by default at powerup. //
////		VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0 //
////		VoutV = VO_dvi->measure();
////		Loop_Count = 0;
////		while(VoutV > 3.2 && Loop_Count < 10000)
////		{
////			VoutV = VO_dvi->measure();
////			wait.delay_10_us(1);
////			Loop_Count++;
////		}
////		starttime = g_mytimer.GetElapsedTime();	
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////		Loop_Count = 0;
////		TMUmeas = 99; // Start //
////		while (TMUmeas > 0 && Loop_Count < 10000)
////		{
////			tmu_6->arm();					
////			wait.delay_10_us(20);
////			TMUmeas = tmu_6->read();
////			Loop_Count++;
////		}
////		stoptime = g_mytimer.GetElapsedTime();
////		t_UVP_8 = (stoptime - starttime) / 1e6;
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////
////		// Power down //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////		Open_relay(K3);
////		tmu_6->open_relay(TMU_HIZ_DUT1);
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////		VPIN_ovi->connect(OVI_CHANNEL_1);
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////		Disconnect_InvSyn_IM();
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////		Open_relay(K12); 
////		FB_ovi->connect(2);
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
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
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// t_UVP_16 test //
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Open all relays //
////		Initialize_Relays();
////
////		// Initialize Instruments //
////		Initialize_Instruments();
////
////		// Drain //
////		Close_relay(K3);
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
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
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
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////		
////		// COMP //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
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
////	//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////		
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup Secondary //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// Disable watchdog timer //
//////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////
////		//Setup Vpin for digital clocking
////		VPIN_ovi->disconnect(OVI_CHANNEL_1);	
////
////		// Initialize DDD
////		ddd_7->ddd_set_clock_period(Dclk_period);
////		ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(100);
//////		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////		wait.delay_10_us(10);
////		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////		wait.delay_10_us(300);
////	//	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////	Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
////	//	wait.delay_10_us(50);
////	wait.delay_10_us(70);
////
////		// DDD level //
////		g_DDD_Low = 0.0; // Save current value //
////		g_DDD_High = 3.3; // Save current value //
////		wait.delay_10_us(g_DDDwait);
////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(g_DDDwait);
////
////		// VBP_P drops when secondary has control //
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////		wait.delay_10_us(8);
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////		wait.delay_10_us(10);
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		wait.delay_10_us(20);
////		
////		// Setup TMU //
////		tmu_6->init();
////		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
////		tmu_6->start_trigger_setup(1, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->start_holdoff(0,FALSE);
////		tmu_6->stop_holdoff(0,FALSE);
////		wait.delay_10_us(200);
////
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enable the timer is 8X longer. //
//////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////	
////		// Set UVL timer to 16msec //
//////		Write_Byte(g_UVL_Timer, 0x01, NObin, HEX); // 16ms //
////	DSM_Write_Byte(g_UVL_Timer, 0x01); // 16ms //
////
////		// Pull Vout below UVA.  UVA is 3.6V by default at powerup. //
////		VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0 //
////		VoutV = VO_dvi->measure();
////		Loop_Count = 0;
////		while(VoutV > 3.2 && Loop_Count < 10000)
////		{
////			VoutV = VO_dvi->measure();
////			wait.delay_10_us(1);
////			Loop_Count++;
////		}
////		starttime = g_mytimer.GetElapsedTime();	
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////		Loop_Count = 0;
////		TMUmeas = 99; // Start //
////		while (TMUmeas > 0 && Loop_Count < 10000)
////		{
////			tmu_6->arm();					
////			wait.delay_10_us(20);
////			TMUmeas = tmu_6->read();
////			Loop_Count++;
////		}
////		stoptime = g_mytimer.GetElapsedTime();
////		t_UVP_16 = (stoptime - starttime) / 1e6;
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////
////		// Power down //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////		Open_relay(K3);
////		tmu_6->open_relay(TMU_HIZ_DUT1);
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////		VPIN_ovi->connect(OVI_CHANNEL_1);
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////		Disconnect_InvSyn_IM();
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////		Open_relay(K12); 
////		FB_ovi->connect(2);
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
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
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// t_UVP_32 test //
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////		// Open all relays //
////		Initialize_Relays();
////
////		// Initialize Instruments //
////		Initialize_Instruments();
////
////		// Drain //
////		Close_relay(K3);
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
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
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
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////		
////		// COMP //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
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
////	//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////		
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup Secondary //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// Disable watchdog timer //
//////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////
////		//Setup Vpin for digital clocking
////		VPIN_ovi->disconnect(OVI_CHANNEL_1);	
////
////		// Initialize DDD
////		ddd_7->ddd_set_clock_period(Dclk_period);
////		ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(100);
//////		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////		wait.delay_10_us(10);
////		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////		wait.delay_10_us(300);
////	//	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////	Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
////	//	wait.delay_10_us(50);
////	wait.delay_10_us(70);
////
////		// DDD level //
////		g_DDD_Low = 0.0; // Save current value //
////		g_DDD_High = 3.3; // Save current value //
////		wait.delay_10_us(g_DDDwait);
////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(g_DDDwait);
////
////		// VBP_P drops when secondary has control //
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////		wait.delay_10_us(8);
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////		wait.delay_10_us(10);
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		wait.delay_10_us(20);
////
////		// Setup TMU //
////		tmu_6->init();
////		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
////		tmu_6->start_trigger_setup(1, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->start_holdoff(0,FALSE);
////		tmu_6->stop_holdoff(0,FALSE);
////		wait.delay_10_us(200);
////
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enable the timer is 8X longer. //
//////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////	
////		// Set UVL timer to 32msec //
//////		Write_Byte(g_UVL_Timer, 0x02, NObin, HEX); // 32ms //
////	DSM_Write_Byte(g_UVL_Timer, 0x02); // 32ms //
////
////		// Pull Vout below UVA.  UVA is 3.6V by default at powerup. //
////		VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0 //
////		VoutV = VO_dvi->measure();
////		Loop_Count = 0;
////		while(VoutV > 3.2 && Loop_Count < 10000)
////		{
////			VoutV = VO_dvi->measure();
////			wait.delay_10_us(1);
////			Loop_Count++;
////		}
////		starttime = g_mytimer.GetElapsedTime();	
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////		Loop_Count = 0;
////		TMUmeas = 99; // Start //
////		while (TMUmeas > 0 && Loop_Count < 10000)
////		{
////			tmu_6->arm();					
////			wait.delay_10_us(20);
////			TMUmeas = tmu_6->read();
////			Loop_Count++;
////		}
////		stoptime = g_mytimer.GetElapsedTime();
////		t_UVP_32 = (stoptime - starttime) / 1e6;
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////
////
////		// Power down //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////		Open_relay(K3);
////		tmu_6->open_relay(TMU_HIZ_DUT1);
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////		VPIN_ovi->connect(OVI_CHANNEL_1);
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////		Disconnect_InvSyn_IM();
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////		Open_relay(K12); 
////		FB_ovi->connect(2);
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
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
////		// t_UVP_64 test //
////		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////		// Open all relays //
////		Initialize_Relays();
////
////		// Initialize Instruments //
////		Initialize_Instruments();
////
////		// Drain //
////		Close_relay(K3);
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
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
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
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////		
////		// COMP //
////		FB_ovi->disconnect(2);
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
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
////		//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////		
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////			
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup Secondary //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// Disable watchdog timer //
//////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX);
////
////		//Setup Vpin for digital clocking
////		VPIN_ovi->disconnect(OVI_CHANNEL_1);	
////
////		// Initialize DDD
////		ddd_7->ddd_set_clock_period(Dclk_period);
////		ddd_7->ddd_set_voltage_ref(DDD_Vref);
////			
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		//wait.delay_10_us(100);
//////		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////		wait.delay_10_us(10);
////		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////		wait.delay_10_us(300);
////	//	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////	Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
////	//	wait.delay_10_us(50);
////	wait.delay_10_us(70);
////
////		// DDD level //
////		g_DDD_Low = 0.0; // Save current value //
////		g_DDD_High = 3.3; // Save current value //
////		wait.delay_10_us(g_DDDwait);
////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(g_DDDwait);
////
////		// VBP_P drops when secondary has control //
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////		wait.delay_10_us(8);
////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////		wait.delay_10_us(10);
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		wait.delay_10_us(20);
////
////		// Setup TMU //
////		tmu_6->init();
////		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
////		tmu_6->start_trigger_setup(1, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
////		tmu_6->start_holdoff(0,FALSE);
////		tmu_6->stop_holdoff(0,FALSE);
////		wait.delay_10_us(200);
////
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enable the timer is 8X longer. //
//////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////	
////		// Set UVL timer to 64msec //
//////		Write_Byte(g_UVL_Timer, 0x03, NObin, HEX); // 64ms //
////	DSM_Write_Byte(g_UVL_Timer, 0x03); // 64ms //
////
////		// Pull Vout below UVA.  UVA is 3.6V by default at powerup. //
////		VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0 //
////		VoutV = VO_dvi->measure();
////		Loop_Count = 0;
////		while(VoutV > 3.2 && Loop_Count < 10000)
////		{
////			VoutV = VO_dvi->measure();
////			wait.delay_10_us(1);
////			Loop_Count++;
////		}
////		starttime = g_mytimer.GetElapsedTime();	
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////		Loop_Count = 0;
////		TMUmeas = 99; // Start //
////		while (TMUmeas > 0 && Loop_Count < 10000)
////		{
////			tmu_6->arm();					
////			wait.delay_10_us(20);
////			TMUmeas = tmu_6->read();
////			Loop_Count++;
////		}
////		stoptime = g_mytimer.GetElapsedTime();
////		t_UVP_64 = (stoptime - starttime) / 1e6;
////		if (Loop_Count > 9990)
////			g_Error_Flag = -144;
////
////		// Error check //
////		if (g_Error_Flag == -137 ||g_Error_Flag == -144 )
////		{
////			V_UVP_3 = -999;
////			V_UVP_8 = -999;
////			V_UVP_14 = -999;
////			V_UVP_19 = -999;
////			V_UVP_24 = -999;
////			Delta_V_UVP = -999;
////			t_UVP_8 = -999;
////			t_UVP_16 = -999;
////			t_UVP_32 = -999;
////			t_UVP_64 = -999;
////		}
////
////
////		// Power down //
////		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////		D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////		Open_relay(K3);
////		tmu_6->open_relay(TMU_HIZ_DUT1);
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////		VPIN_ovi->connect(OVI_CHANNEL_1);
////		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////		Disconnect_InvSyn_IM();
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////		Open_relay(K12); 
////		FB_ovi->connect(2);
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
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
////	}
////
////	// Datalog //
////	PiDatalog(func, A_V_UVP_3, V_UVP_3, 25, POWER_UNIT);
////	PiDatalog(func, A_V_UVP_8, V_UVP_8, 25, POWER_UNIT);
////	if (g_Char_Enable_P) // Characterization only //
////	{
////		PiDatalog(func, A_V_UVP_14, V_UVP_14, 25, POWER_UNIT);
////		PiDatalog(func, A_V_UVP_19, V_UVP_19, 25, POWER_UNIT);
////	}
////	PiDatalog(func, A_V_UVP_24, V_UVP_24, 25, POWER_UNIT);
////	PiDatalog(func, A_Delta_V_UVP, Delta_V_UVP, 25, POWER_MILLI);
////
////	if (g_Char_Enable_P) // Characterization only //
////	{
////		PiDatalog(func, A_t_UVP_8, t_UVP_8, 25, POWER_MILLI);
////		PiDatalog(func, A_t_UVP_16, t_UVP_16, 25, POWER_MILLI);
////		PiDatalog(func, A_t_UVP_32, t_UVP_32, 25, POWER_MILLI);
////		PiDatalog(func, A_t_UVP_64, t_UVP_64, 25, POWER_MILLI);
////	}
////	
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		UVP_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_UVP_TT, UVP_TT, 25, POWER_MILLI);
////	}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}