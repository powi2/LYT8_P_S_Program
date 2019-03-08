//==============================================================================
// Vovp.cpp (User function)
// 
//    void Vovp_user_init(test_function& func)
//    void Vovp(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Vovp.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Vovp_user_init(test_function& func)
{
	Vovp_params *ours;
    ours = (Vovp_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Vovp(test_function& func)
{
    // The two lines below must be the first two in the function.
    Vovp_params *ours;
    ours = (Vovp_params *)func.params;

	// Increment function number //
	gFuncNum++;

//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_fNum_Vovp, gFuncNum, 25, POWER_UNIT);
//////
//////	if (!g_Char_Enable_P) // Characterization only //
//////		return;
//////
//////	// Skip Test if AbortTest set //
//////	if (AbortTest)
//////		return;
//////
//////	if (g_Fn_Vovp == 0 )  return;
//////
//////	// Test Time Begin //
//////	if (g_TstTime_Enble_P)
//////		g_begintime = g_mytimer.GetElapsedTime();
//////
//////	// Test Names //
//////	float V_OVP_6_2 = 0;
//////	float V_OVP_10 = 0;
//////	float V_OVP_15 = 0;
//////	float V_OVP_20 = 0;
//////	float V_OVP_24 = 0;
//////	float Delta_V_OVP = 0;
//////	float Vovp_TT = 0;
//////
//////	// Declare Variables //
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //
//////	int WordArray[16] = {0};
//////	int ReadWordData[16] = {0};
//////	int TempArray[30] = {0};
//////	float UpperLimit = 0;
//////	float LowerLimit = 0;
//////	float Vforce = 0;
//////	float SRpinVolt = 0;
//////	Pulse pulse;
//////	float V_OVP_6_3 = 0;
//////	float WordData = 0;
//////	float Imeas = 0;
//////	int LoopCount = 0; 
//////
//////	// Open all relays //
//////	//Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	//Initialize_Instruments();
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
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	//Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// COMP //
//////	FB_ovi->disconnect(2);
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 3.3; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	//wait.delay_10_us(100);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
//////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////
//////// Set DSM clock frequency //
//////DSM_set_vector_clock_freq(DSM_CONTEXT, 1200); // Freq in kHZ, 1200/4 = 300kHz clock frequency //  // Add I2C DSM //
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
////////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
//////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
//////	// stairsteps up slowly, with CV only mode it steps up in a single step. //
//////	if (g_SiliconRev_Sec == 5) // Rev C silicon //
//////	{
////////		Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
//////	DSM_Write_Byte(g_CVO_mode, 0x01); // Enable CV only mode //
//////	}
//////
//////	// Write byte to disable 10msec VI update lockout //
////////	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
//////DSM_Write_Byte(g_Fast_VI_Command, 0x01);
//////
////////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
//////DSM_Write_Word(g_TM_ANA, 0x0134);
//////	
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Float SR dvi //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
//////
//////	// Connect the "VOUT_OV_latch_chy" comparator output to SR pin. Test mode 29. //
//////	// To observe Vout over voltage fault when SR pin flips. //
////////	Write_Word(g_TM_SEL, 29, NObin, HEX);
//////DSM_Write_Word(g_TM_SEL, 29);
//////
//////	// Write register to put seconary in control //
////////	Write_Word(g_TM_CTRL, 0x0020, NObin, HEX); 
//////DSM_Write_Word(g_TM_CTRL, 0x0020); 
//////
//////	// Enable latch-off fault if Over-voltage theshold is tripped. //
////////	Write_Byte(g_OVL, 0x01, NObin, HEX);
//////DSM_Write_Byte(g_OVL, 0x01);
//////
//////	// V_OVP_6_2 test.  Program OVA to 6.2V, search for threshold. //
//////	// Program Output Over-voltage Threshold to 6.2V //
//////
//////	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////	// and [7] and [15] are odd parity bits.  
//////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////	WordData = 32830; // 6.2V //
////////	Write_Word(g_OVA, WordData, NObin, HEX);
//////DSM_Write_Word(g_OVA, WordData);
//////
//////	// Binary search for over-voltage threshold. //
//////	// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
//////	UpperLimit = (func.dlog->tests[A_V_OVP_6_2].f_max_limit_val[0])*1.1; // Get upper search limit //
//////	LowerLimit = 5;
////////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////////	{
////////		UpperLimit = (func.dlog->tests[A_V_OVP_6_2].f_max_limit_val[0])*1.4; // Get upper search limit //
////////		LowerLimit = 5;
////////	}
//////	Vforce = (UpperLimit + LowerLimit) / 2;
//////	if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
//////	{
//////		Vforce = 0;
//////		g_Error_Flag = -132;
//////	}
//////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(50);
//////	while ( (UpperLimit - LowerLimit) > .001)
//////	{
//////		Vforce = (UpperLimit + LowerLimit) / 2; 
//////		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -132;
//////			break;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(255); // Needed //
//////		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////		if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////			LowerLimit = Vforce;
//////		else // Above threshold.  Comparator high. //
//////			UpperLimit = Vforce;		
//////	}
//////	V_OVP_6_2 = Vforce;
//////
//////
//////	//  Program OVA to 6.3V, search for threshold. //
//////	// Program Output Over-voltage Threshold to 6.3V //
//////	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////	// and [7] and [15] are odd parity bits.  
//////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////	WordData = 32959; // 6.3V //
////////	Write_Word(g_OVA, WordData, NObin, HEX);
//////DSM_Write_Word(g_OVA, WordData);
//////
//////	// Binary search for over-voltage threshold. //
//////	// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////	UpperLimit = 8;
//////	LowerLimit = 5;
//////	Vforce = (UpperLimit + LowerLimit) / 2;
//////	if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
//////	{
//////		Vforce = 0;
//////		g_Error_Flag = -135;
//////	}
//////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(50);
//////	while ( (UpperLimit - LowerLimit) > .001)
//////	{
//////		Vforce = (UpperLimit + LowerLimit) / 2; 
//////		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -135;
//////			break;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(255); // Needed //
//////		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////		if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////			LowerLimit = Vforce;
//////		else // Above threshold.  Comparator high. //
//////			UpperLimit = Vforce;		
//////	}
//////	V_OVP_6_3 = Vforce;
//////
//////	// Calculate difference between two adjacent steps. //
//////	Delta_V_OVP = V_OVP_6_3 - V_OVP_6_2;
//////
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		// Write the I2C command to set_CV.  Needed to change to higher readback range.  3 ranges 
//////		// total for Rev.2 silicon: 0-6, 6-10, and 10-24V.  Need to set CV using customer 
//////		// programmable register to force part to go into next range. //
//////		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////		// and [7] and [15] are odd parity bits.  
//////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////		WordData = 1896; // Set to 10V //
////////		Write_Word(g_CV_reg, WordData, NObin, HEX);
//////	DSM_Write_Word(g_CV_reg, WordData);
//////		wait.delay_10_us(100); // Needed //
//////	
//////		// V_OVP_10 test.  Program OVA to 10V, search for threshold. //
//////		// Program Output Over-voltage Threshold to 10V //
//////		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////		// and [7] and [15] are odd parity bits.  
//////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////		WordData = 32868; // 10V //
////////		Write_Word(g_OVA, WordData, NObin, HEX);
//////	DSM_Write_Word(g_OVA, WordData);
//////	
//////		// Binary search for over-voltage threshold. //
//////		// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////		UpperLimit = (func.dlog->tests[A_V_OVP_10].f_max_limit_val[0])*1.1; // Get upper search limit //
//////		LowerLimit = 5;
////////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////////		{
////////			UpperLimit = (func.dlog->tests[A_V_OVP_10].f_max_limit_val[0])*1.4; // Get upper search limit //
////////			LowerLimit = 5;
////////		}
//////		Vforce = (UpperLimit + LowerLimit) / 2;
//////		if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -133;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(50);
//////		while ( (UpperLimit - LowerLimit) > .001)
//////		{
//////			Vforce = (UpperLimit + LowerLimit) / 2; 
//////			if (Vforce < -19.99 || Vforce > 19.99) // Prevent out of range. //
//////			{
//////				Vforce = 0;
//////				g_Error_Flag = -133;
//////				break;
//////			}
//////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_20_RANGE); // DVI_9_0 //
//////			wait.delay_10_us(255); // Needed //
//////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////			if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////				LowerLimit = Vforce;
//////			else // Above threshold.  Comparator high. //
//////				UpperLimit = Vforce;		
//////		}
//////		V_OVP_10 = Vforce;
//////	}
//////
//////	// Write the I2C command to set_CV.  Needed to change to higher readback range.  3 ranges 
//////	// total for Rev.2 silicon: 0-6, 6-10, and 10-24V (only two ranges for Rev.1 silicon.  Need 
//////	// to set CV using customer programmable register to force part to go into next range. //
//////	// Check secondary silicon revision //
//////	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////	// and [7] and [15] are odd parity bits.  
//////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////	WordData = 2124; // Set to 11V //
////////	Write_Word(g_CV_reg, WordData, NObin, HEX);
//////DSM_Write_Word(g_CV_reg, WordData);
//////	wait.delay_10_us(100); // Needed //
//////
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		// V_OVP_15 test.  Program OVA to 15V, search for threshold. //
//////		// Program Output Over-voltage Threshold to 15V //
//////		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////		// and [7] and [15] are odd parity bits.  
//////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////		WordData = 278; // 15V //
////////		Write_Word(g_OVA, WordData, NObin, HEX);
//////	DSM_Write_Word(g_OVA, WordData);
//////	
//////		// Binary search for over-voltage threshold. //
//////		// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////		UpperLimit = (func.dlog->tests[A_V_OVP_15].f_max_limit_val[0])*1.1; // Get upper search limit //
//////		LowerLimit = (func.dlog->tests[A_V_OVP_15].f_min_limit_val[0])*0.9; // Get lower search limit //
////////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////////		{
////////			UpperLimit = (func.dlog->tests[A_V_OVP_15].f_max_limit_val[0])*1.4; // Get upper search limit //
////////			LowerLimit = (func.dlog->tests[A_V_OVP_15].f_min_limit_val[0])*0.5; // Get lower search limit //
////////		}
//////		Vforce = (UpperLimit + LowerLimit) / 2;
//////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -134;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(50);
//////		while ( (UpperLimit - LowerLimit) > .001)
//////		{
//////			Vforce = (UpperLimit + LowerLimit) / 2; 
//////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////			{
//////				Vforce = 0;
//////				g_Error_Flag = -134;
//////				break;
//////			}
//////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////			wait.delay_10_us(255); // Needed //
//////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////			if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////				LowerLimit = Vforce;
//////			else // Above threshold.  Comparator high. //
//////				UpperLimit = Vforce;		
//////		}
//////		V_OVP_15 = Vforce;
//////
//////
//////
//////		// V_OVP_20 test.  Program OVA to 20V, search for threshold. //
//////		// Program Output Over-voltage Threshold to 20V //
//////		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////		// and [7] and [15] are odd parity bits.  
//////		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////		WordData = 456; // 20V //
////////		Write_Word(g_OVA, WordData, NObin, HEX);
//////	DSM_Write_Word(g_OVA, WordData);
//////	
//////		// Binary search for over-voltage threshold. //
//////		// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////		UpperLimit = (func.dlog->tests[A_V_OVP_20].f_max_limit_val[0])*1.1; // Get upper search limit //
//////		LowerLimit = (func.dlog->tests[A_V_OVP_20].f_min_limit_val[0])*0.9; // Get lower search limit //
////////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////////		{
////////			UpperLimit = (func.dlog->tests[A_V_OVP_20].f_max_limit_val[0])*1.4; // Get upper search limit //
////////			LowerLimit = (func.dlog->tests[A_V_OVP_20].f_min_limit_val[0])*0.5; // Get lower search limit //
////////		}
//////		Vforce = (UpperLimit + LowerLimit) / 2;
//////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -138;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(50);
//////		while ( (UpperLimit - LowerLimit) > .001)
//////		{
//////			Vforce = (UpperLimit + LowerLimit) / 2; 
//////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////			{
//////				Vforce = 0;
//////				g_Error_Flag = -138;
//////				break;
//////			}
//////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////			wait.delay_10_us(255); // Needed //
//////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////			if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////				LowerLimit = Vforce;
//////			else // Above threshold.  Comparator high. //
//////				UpperLimit = Vforce;		
//////		}
//////		V_OVP_20 = Vforce;
//////	}
//////
//////	// V_OVP_24 test.  Program OVA to 24V, search for threshold. //
//////	// Program Output Over-voltage Threshold to 24V //
//////	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
//////	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
//////	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
//////	// and [7] and [15] are odd parity bits.  
//////	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
//////	WordData = 368; // 24V //
////////	Write_Word(g_OVA, WordData, NObin, HEX);
//////DSM_Write_Word(g_OVA, WordData);
//////
//////	// Binary search for over-voltage threshold. //
//////	// Look at "VOUT_OV_latch_chy" comparator output on SR pin. //
//////	UpperLimit = (func.dlog->tests[A_V_OVP_24].f_max_limit_val[0])*1.1; // Get upper search limit //
//////	LowerLimit = (func.dlog->tests[A_V_OVP_24].f_min_limit_val[0])*0.9; // Get lower search limit //
////////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////////	{
////////		UpperLimit = (func.dlog->tests[A_V_OVP_24].f_max_limit_val[0])*1.4; // Get upper search limit //
////////		LowerLimit = (func.dlog->tests[A_V_OVP_24].f_min_limit_val[0])*0.5; // Get lower search limit //
////////	}
//////	Vforce = (UpperLimit + LowerLimit) / 2;
//////	if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////	{
//////		Vforce = 0;
//////		g_Error_Flag = -139;
//////	}
//////	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(50);
//////	while ( (UpperLimit - LowerLimit) > .001)
//////	{
//////		Vforce = (UpperLimit + LowerLimit) / 2; 
//////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
//////		{
//////			Vforce = 0;
//////			g_Error_Flag = -139;
//////			break;
//////		}
//////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
//////		wait.delay_10_us(255); // Needed //
//////		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for comparator output flip. // 
//////		if (SRpinVolt < 1.5) // Below threshold.  Comparator low. //
//////			LowerLimit = Vforce;
//////		else // Above threshold.  Comparator high. //
//////			UpperLimit = Vforce;		
//////	}
//////	V_OVP_24 = Vforce;
//////
//////
//////// Reset registers for next tests. //
////////Write_Word(g_TM_ANA, 0x0000, NObin, HEX);
////////Write_Byte(g_OVL, 0x02, NObin, HEX);
//////
////////WordData = 33780; // Set to 5V //
////////Write_Word(g_CV_reg, WordData, NObin, HEX);
//////
////////WordData = 32830; // 6.2V //
////////Write_Word(g_OVA, WordData, NObin, HEX);
//////
//////	// Powerdown //
//////	//Open_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE);
//////	//FB_ovi->connect(2);
//////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	//Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	//Mux20_Open_relay(K37);
//////	//Mux20_Open_relay(K38);
//////	//Mux20_Open_relay(K40);
//////	//Mux20_Open_relay(K39);
//////	//ddd_7->ddd_set_clock_period(Dclk_period);
//////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	//wait.delay_10_us(200); // Wait for relays //
//////
//////	// Datalogs //
//////	PiDatalog(func, A_V_OVP_6_2, V_OVP_6_2, 25, POWER_UNIT);
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		PiDatalog(func, A_V_OVP_10, V_OVP_10, 25, POWER_UNIT);
//////		PiDatalog(func, A_V_OVP_15, V_OVP_15, 25, POWER_UNIT);
//////		PiDatalog(func, A_V_OVP_20, V_OVP_20, 25, POWER_UNIT);
//////	}
//////	PiDatalog(func, A_V_OVP_24, V_OVP_24, 25, POWER_UNIT);
//////	PiDatalog(func, A_Delta_V_OVP, Delta_V_OVP, 25, POWER_MILLI);
//////
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		Vovp_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_Vovp_TT, Vovp_TT, 25, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
