//==============================================================================
// CV_nDAC_pDAC.cpp (User function)
// 
//    void CV_nDAC_pDAC_user_init(test_function& func)
//    void CV_nDAC_pDAC(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "CV_nDAC_pDAC.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CV_nDAC_pDAC_user_init(test_function& func)
{
	CV_nDAC_pDAC_params *ours;
    ours = (CV_nDAC_pDAC_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CV_nDAC_pDAC(test_function& func)
{
    // The two lines below must be the first two in the function.
    CV_nDAC_pDAC_params *ours;
    ours = (CV_nDAC_pDAC_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_CVnDACpDAC, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_CV_nDAC_pDAC == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float pDAC_3V_S = 0;
	float pDAC_4p84V_S = 0;
	float pDAC_4p92V_S = 0;
	float pDAC_4p96V_S = 0;
	float pDAC_4p98V_S = 0;
	float pDAC_4p99V_S = 0;
	float pDAC_Final_S = 0;
	float pDAC_Final_dlta = 0;
	float pDAC_TrCode0 = 0;
	float pDAC_TrCode1 = 0;
	float pDAC_TrCode2 = 0;
	float pDAC_TrCode4 = 0;
	float pDAC_TrCode8 = 0;
	float pDAC_TrCode16 = 0;
	float pDAC_TrCode31 = 0;
	float pDAC_Act_Chg_S = 0;
	float nDAC_5p1V_S = 0;
	float nDAC_5p2V_S = 0;
	float nDAC_5p4V_S = 0;
	float nDAC_5p8V_S = 0;
	float nDAC_6p6V_S = 0;
	float nDAC_8p2V_S = 0;
	float nDAC_20V_S = 0;
	float nDAC_24V_S = 0;
	float nDAC_Final_S = 0;
	float nDAC_Final_dlta = 0;
	float nDAC_TrCode0 = 0;
	float nDAC_TrCode1 = 0;	
	float nDAC_TrCode2 = 0;	
	float nDAC_TrCode4 = 0;	
	float nDAC_TrCode8 = 0;	
	float nDAC_TrCode16 = 0;	
	float nDAC_TrCode31 = 0;
	float nDAC_Act_Chg_S = 0;
	//float CV_Final_S = 0;
	float CV_Act_Chg_S = 0;
	float DeltaVOUT_10mV = 0;
	float DeltaVOUT_100mV = 0;
	//float VOUT_T = 0;
	//float CVO_timer = 0;
	float VTOL_Vo3_VFB =0;
	float VTOL_Vo3_20mV =0;
	float VTOL_Vo3_Avg = 0;
	float VTOL_Vo4_VFB =0;
	float VTOL_Vo4_20mV =0;
	float VTOL_Vo4_Avg = 0;
	float VTOL_Vo5_VFB =0;
	float VTOL_Vo5_20mV =0;
	float VTOL_Vo5_Avg = 0;
	float VTOL_Vo6_VFB =0;
	float VTOL_Vo6_20mV =0;
	float VTOL_Vo6_Avg = 0;
	float VTOL_Vo7_VFB =0;
	float VTOL_Vo7_20mV =0;
	float VTOL_Vo7_Avg = 0;
	float VTOL_Vo9_VFB =0;
	float VTOL_Vo9_50mV =0;
	float VTOL_Vo9_Avg = 0;
	float VTOL_Vo12_VFB =0;
	float VTOL_Vo12_100mV =0;
	float VTOL_Vo12_Avg = 0;
	float VTOL_Vo21_VFB = -9999;
	float VTOL_Vo21_100mV = -9999;
	float VTOL_Vo21_Avg = -9999;
	float VTOL_Vo24_VFB =0;
	float VTOL_Vo24_100mV =0;
	float VTOL_Vo24_Avg = 0;
	float CV_nDAC_pDAC_TT = 0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	int READ59_word[16] = {0};
	int TempArray[30] = {0};
	float WordData = 0;
	float UpperLimit = 0;
	float LowerLimit = 0;
	float Vforce = 0;
	float SRpinVolt = 0;
	int READ14_word[16] = {0};
	int READ8_word[16] = {0};
	int READ41_word[16] = {0};
	int READ9_word[16] = {0};
	int CV_Read = 0;
	float CV_Result = 0;
	float VoutForce = 0;
	int READ1_word[16] = {0};
	float LowerResult = 0;
	float UpperResult = 0;
	float LowerValue= 0;
	float UpperValue= 0;
	int FoundThresh = 0;
	float stepSize = 0;
	int i = 0;
	float SumResult = 0;
	float Meas_uVCC = 0;
	int READ58_word[16] = {0};
	float CV_Ref = 0;
	Pulse pulse;

	// Measure pDAC_Final-S //

	// Open all relays //
	//Initialize_Relays();

	// Initialize Instruments //
	//Initialize_Instruments();

	// Drain //
	//Close_relay(K2);
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
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
	
	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// Connect Op Amp supply.  dvi used as OpAmp supply. //
	// Limit supply to 10V during connection to prevent Vout going to high- will damage part. //
	Mux20_Close_relay(K36);
	wait.delay_10_us(300);
	VBD_ramp_up(0, 1, 0.2);
	VBD_dvi->set_current(VBD_ch, 300e-3, RANGE_300_MA); // DVI_21_0, prevent glitch //
	VBD_ramp_up(1, 10, 0.2);

	// Vout //
	Mux20_Close_relay(K53); // Connect Vout pin to Op Amp output. //
	VO_dvi->set_current(VO_ch, 0.1e-9, RANGE_30_UA); // DVI_9_0, float //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //

	// COMP //
	FB_ovi->disconnect(2);
	Mux20_Close_relay(K54); // Connect FB pin to Op Amp negative input. //

	// Setup Op Amp positive input reference to 1.25V. //
	ovi_3->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_3_6 //
	ovi_3->set_voltage(OVI_CHANNEL_6, 1.25, RANGE_2_V); // OVI_3_6 //

	// VBD //
	//VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	//wait.delay_10_us(25); // Prevent glitch //
	//VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

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
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200);

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
	// stairsteps up slowly, with CV only mode it steps up in a single step. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
	}

	// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
	// switching freqeuncy with FB pin //
	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
	
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		WordArray[5] = g_EE_ShadReg53;
		WordArray[6] = g_EE_ShadReg54;
		WordArray[7] = g_EE_ShadReg55;
		WordArray[8] = g_EE_ShadReg56;
		WordArray[9] = g_EE_ShadReg57;
		WordArray[10] = g_EE_ShadReg58;
		WordArray[11] = g_EE_ShadReg59;
		WordArray[12] = g_EE_ShadReg60;
		WordArray[13] = g_EE_ShadReg61;
		WordArray[14] = g_EE_ShadReg62;
		WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //

		// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
		WordArray[15] = 0;
		Write_Word(g_SREG3, NOhex, WordArray, BIN);
	}

	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX);
	wait.delay_10_us(30);

	// More delay for Rev C //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
		wait.delay_10_us(100); // Needed //

	// Ramp Op Amp supply up to 24V to match previous test program conditions //
	VBD_ramp_up(10, 24, 0.2);
	wait.delay_10_us(100);


	// Measure Vout.  This with nDAC and pDAC pogrammed to zero by default at powerup. //
	CV_Ref = VO_dvi->measure_average(10);

	// Write the I2C command to set_CV //
	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
	// and [7] and [15] are odd parity bits.  
	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
	WordData = 756; 
	Write_Word(g_CV_reg, WordData, NObin, HEX);

	// Measure Vout //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
		wait.delay_10_us(1020); // Needed //
	else
		wait.delay_10_us(120); // Needed //
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		pDAC_Final_S = VO_dvi->measure_average(50);
		pDAC_Final_dlta = CV_Ref - pDAC_Final_S;
	}
	if (g_Trim_Enable_P == 1)
		pDAC_Act_Chg_S = ((pDAC_Final_S - g_pDAC_Pt_S) / g_pDAC_Pt_S)*100; // In percent //

	// Write byte to disable 10msec VI update lockout //
	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);

	if (g_Char_Enable_P) // Characterization only //
	{
		
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		WordArray[5] = g_EE_ShadReg53;
		WordArray[6] = g_EE_ShadReg54;
		WordArray[7] = g_EE_ShadReg55;
		WordArray[8] = g_EE_ShadReg56;
		WordArray[9] = g_EE_ShadReg57;
		WordArray[10] = g_EE_ShadReg58;
		WordArray[11] = g_EE_ShadReg59;
		WordArray[12] = g_EE_ShadReg60;
		WordArray[13] = g_EE_ShadReg61;
		WordArray[14] = g_EE_ShadReg62;
		WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //

		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
		{
			// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
			WordArray[15] = 0;
		}

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode0
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(0, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode0 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode1
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(1, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode1 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode2
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(2, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode2 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode4
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(4, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode4 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode8
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(8, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode8 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode16
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(16, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode16 = VO_dvi->measure_average(50);


		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// pDAC_TrCode31
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(31, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		pDAC_TrCode31 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Reload original trim code to shadow register //
		// Load READ59_word[] to WordArray[] at correct bit locations. //
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Load TempArray[] to WordArray[] at correct bit locations. //
	
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		Write_Word(g_SREG3, NOhex, WordArray, BIN); // Load trim code to shadow register. //
	}

	// pDAC_3V_S //
	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
	// and [7] and [15] are odd parity bits.  
	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
	WordData = 556; 
	Write_Word(g_CV_reg, WordData, NObin, HEX);

	if (g_SiliconRev_Sec == 5) // Rev C silicon //
		wait.delay_10_us(1000); // Needed //
	else
		wait.delay_10_us(80); // Needed //
	pDAC_3V_S = VO_dvi->measure_average(50);


	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// pDAC_4p84V_S //.
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33636; 
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		pDAC_4p84V_S = VO_dvi->measure_average(50);

		// pDAC_4p92V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33772; 
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1020); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		pDAC_4p92V_S = VO_dvi->measure_average(50);

		// pDAC_4p96V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33648; 
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		pDAC_4p96V_S = VO_dvi->measure_average(50);


		// DAC_4p98V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33778; 
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		pDAC_4p98V_S = VO_dvi->measure_average(100);

		// pDAC_4p99V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33651; 
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		pDAC_4p99V_S = VO_dvi->measure_average(100);

		if (g_Char_Enable_P) // Characterization only //
		{
			// DeltaVOUT_10mV //
			// Calculate difference between two adjacent 10mV steps //
			DeltaVOUT_10mV = pDAC_4p99V_S - pDAC_4p98V_S;
		}
	}

	// Reset CV back to 5V (default). //
	WordData = 33780;  // 5.0V //
	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //
	wait.delay_10_us(100); // Needed // 
		
	// Powerdown //
	//Open_relay(K2);
	//Open_relay(K18);
	//FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	//BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	//VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	//Mux20_Open_relay(K53); // Disconnect Vout pin from Op Amp output. //
	//VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
	//FB_ovi->connect(2);
	//Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
	//ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //
	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	//Mux20_Open_relay(K64);
	//ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	//Mux20_Open_relay(K37); 
	//Mux20_Open_relay(K38);
	//Mux20_Open_relay(K40);
	//Mux20_Open_relay(K39);
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
	
	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Measure nDAC_Final-S //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

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

	// BPS //
	//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// Vout //
	Mux20_Close_relay(K53); // Connect Vout pin to Op Amp output. //
	VO_dvi->set_current(VO_ch, 0.1e-9, RANGE_30_UA); // DVI_9_0, float //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_20_RANGE); // DVI_9_0 //
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //

	// COMP //
	FB_ovi->disconnect(2);
	Mux20_Close_relay(K54); // Connect FB pin to Op Amp negative input. //

	// Setup Op Amp positive input reference to 1.25V. //
	ovi_3->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_3_6 //
	ovi_3->set_voltage(OVI_CHANNEL_6, 1.25, RANGE_2_V); // OVI_3_6 //

	// VBD //
//	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//	wait.delay_10_us(25); // Prevent glitch //
//	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

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
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	//wait.delay_10_us(200); 

	// Powerup //
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	//wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
//	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //



	// Don't write to CV register.  Instead, using test mode, write directly to the nDAC register.  Writing to the 
	// CV register causes the pDAC to also be written when Vout is higher than 5V to get the 10mV steps, but want 
	// to isolate the nDAC trimming by writing to nDAC register only.
	// In TM_CTRL register, set bit tm_ctrl[3]: tm_fbdac100 to 1 to write directly to nDAC.
	// Then write code 64 (0x40) to TM_DAC register. Use 64 because we are trimming to 1/4 scale, so 256/4 = 64. //  

	// Also, need to prevent the FB comparator reference from shifting.
	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	
	// Both of the above need to be written at the same time, so the code is 0x0828.

	// Put seconary in control, disconnect Vout from ADC, program nDAC directly.//
	Write_Word(g_TM_CTRL, 0x0828, NObin, HEX); 
	wait.delay_10_us(30);

	// Measure Vout.  This with nDAC and pDAC pogrammed to zero by default at powerup. //
	CV_Ref = VO_dvi->measure_average(10);

// Ramp down op amp supply voltage to prevent initial overshoot on Vout. //
VBD_ramp_down(24, 11.5, 0.2);

	// Set nDAC to 1/4 scale. // 
	Write_Byte(g_TM_DAC, 0x40, NObin, HEX);

wait.delay_10_us(120); 
VBD_ramp_up(11.5, 24, 0.2);

	// Measure Vout //
	wait.delay_10_us(120); 
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		nDAC_Final_S = VO_dvi->measure_average(50);
		nDAC_Final_dlta = nDAC_Final_S - CV_Ref;
	}
	if (g_Trim_Enable_P == 1)
		nDAC_Act_Chg_S = ((nDAC_Final_S - g_nDAC_Pt_S) / g_nDAC_Pt_S)*100; // In percent //	


	if (g_Char_Enable_P) // Characterization only //
	{
		//
		// Load WordArray[] with contents of shadow register array!  Must not overwrite shadow register! //
		Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
		Read_Word(g_RDADDR, READ58_word);// SRE22G2.  Shadow register. //

		////// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
		////WordArray[0] = READ58_word[0];
		////WordArray[1] = READ58_word[1]; 
		////WordArray[2] = READ58_word[2]; 
		////WordArray[3] = READ58_word[3]; 
		////WordArray[4] = READ58_word[4]; 
		////WordArray[5] = READ58_word[5];
		////WordArray[6] = READ58_word[6];
		////WordArray[7] = READ58_word[7];
		////WordArray[8] = READ58_word[8]; // EEtr_nDAC1_S //
		////WordArray[9] = READ58_word[9]; // EEtr_nDAC2_S //
		////WordArray[10] = READ58_word[10]; // EEtr_nDAC3_S //
		////WordArray[11] = READ58_word[11]; // EEtr_nDAC4_S //
		////WordArray[12] = READ58_word[12]; // EEtr_nDAC5_S //
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
		WordArray[6] = g_EE_ShadReg38;
		WordArray[7] = g_EE_ShadReg39;
		WordArray[8] = g_EE_ShadReg40; // EEtr_nDAC1_S //
		WordArray[9] = g_EE_ShadReg41; // EEtr_nDAC2_S //
		WordArray[10] = g_EE_ShadReg42; // EEtr_nDAC3_S //
		WordArray[11] = g_EE_ShadReg43; // EEtr_nDAC4_S //
		WordArray[12] = g_EE_ShadReg44; // EEtr_nDAC5_S //
		WordArray[13] = g_EE_ShadReg45;
		WordArray[14] = g_EE_ShadReg46;
		WordArray[15] = g_EE_ShadReg47;

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode0
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(0, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode0 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode1
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(1, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode1 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode2
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(2, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode2 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode4
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(4, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode4 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode8
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(8, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode8 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode16
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(16, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode16 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// nDAC_TrCode31
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Convert decimal number into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(31, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[8] = TempArray[0];
		WordArray[9] = TempArray[1]; 
		WordArray[10] = TempArray[2]; 
		WordArray[11] = TempArray[3]; 
		WordArray[12] = TempArray[4]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //

		// Measure Vout //
		wait.delay_10_us(150); 
		nDAC_TrCode31 = VO_dvi->measure_average(50);

		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Reload original trim code to shadow register //
		// Load READ58_word[] to WordArray[] at correct bit locations. //
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		//////
		////WordArray[8] = READ58_word[8];
		////WordArray[9] = READ58_word[9]; 
		////WordArray[10] = READ58_word[10]; 
		////WordArray[11] = READ58_word[11]; 
		////WordArray[12] = READ58_word[12];
		//////
		WordArray[8] = g_EE_ShadReg40; // EEtr_nDAC1_S //
		WordArray[9] = g_EE_ShadReg41; // EEtr_nDAC2_S //
		WordArray[10] = g_EE_ShadReg42; // EEtr_nDAC3_S //
		WordArray[11] = g_EE_ShadReg43; // EEtr_nDAC4_S //
		WordArray[12] = g_EE_ShadReg44; // EEtr_nDAC5_S //
		Write_Word(g_SREG2, NOhex, WordArray, BIN); // Load trim code to shadow register. //
	}

	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX); 

	// Write byte to disable 10msec VI update lockout //
	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// VO change range //
		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //

		// nDAC_5p1V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 33790;  // 5.1V //
		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		nDAC_5p1V_S = VO_dvi->measure_average(100);

		// nDAC_5p2V_S //
		//WordData = 520; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit; therefore data bits 7,8,9,10,11 shift over by one.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 628)0000 0010 0111 0100. //
		WordData = 1032;  // 5.2V //
		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		nDAC_5p2V_S = VO_dvi->measure_average(100);
		
		if (g_Char_Enable_P) // Characterization only //
		{
			// DeltaVOUT_100mV //
			// Calculate difference between two adjacent 100mV steps //
			DeltaVOUT_100mV = nDAC_5p2V_S - nDAC_5p1V_S;
		}


		// nDAC_5p4V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 1052;  // 5.4V //
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed // 
		else
			wait.delay_10_us(80); // Needed //
		nDAC_5p4V_S = VO_dvi->measure_average(50);

		// nDAC_5p8V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 1220; // 5.8V //
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed // 
		nDAC_5p8V_S = VO_dvi->measure_average(50);

		// nDAC_6p6V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 34196; // 6.6V //
		Write_Word(g_CV_reg, WordData, NObin, HEX);

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //  
		nDAC_6p6V_S = VO_dvi->measure_average(50);

		// nDAC_8p2V_S //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 34356; // 8.2V //
		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(80); // Needed //
		nDAC_8p2V_S = VO_dvi->measure_average(50);

		// nDAC_20V_S //
		// Check secondary silicon revision //
		VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0, change range. //

		// Ramp down op amp supply voltage to prevent initial overshoot on Vout. //
		VBD_ramp_down(24, 20, 0.2);

		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 36816; // 20V //
		Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed // 
		else
			wait.delay_10_us(100); // Needed //

		VBD_ramp_up(20, 24, 0.2);
		wait.delay_10_us(120); 

		nDAC_20V_S = VO_dvi->measure_average(50);
	}


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// nDAC_24V_S 
	//
	// Opamp does not goes upto 24V (uses +24V Vcc), need to remove opamp and use binary
	// search for 24V level.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0, change range. //
	Mux20_Open_relay(K53); // Disonnect Vout pin from Op Amp output. //

	// COMP(FB)//
	Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
	wait.delay_10_us(250); // Waits for relays //

	// Remove Op Amp positive input reference. //
	ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //

	// Vout setup //
	VO_dvi->set_voltage(VO_ch, 5, VOLT_50_RANGE); // DVI_9_0, needed to prevent spike below ground // //
	wait.delay_10_us(150); // Delay needed to prevent spike below ground //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //

	// Set CV with I2C //
	//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
	// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
	// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
	// and [7] and [15] are odd parity bits.  
	// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
	WordData = 37600; // 24V //
	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

	// Do not program nDAC directly, nDAC no longer programmed to 1/4 scale. //
	Write_Byte(g_TM_DAC, 0x00, NObin, HEX);

	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //
	
	// Float SR dvi //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

	// Connect the FB comparator output to SR pin (CV comparator output). //
	Write_Word(g_TM_SEL, 0x0024, NObin, HEX);

	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX);

	// Extra wait for Rev C silicon //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
		wait.delay_10_us(300); // Needed //

	// Binary search CV [on Vout pin] //
	// Look for FB comparator output flip on SR pin. //
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
	UpperLimit = (func.dlog->tests[A_nDAC_24V_S].f_max_limit_val[0])*1.1; // Get upper search limit //
	LowerLimit = (func.dlog->tests[A_nDAC_24V_S].f_min_limit_val[0])*0.9; // Get lower search limit //
//	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//	{
//		UpperLimit = (func.dlog->tests[A_nDAC_24V_S].f_max_limit_val[0])*1.4; // Get upper search limit //
//		LowerLimit = (func.dlog->tests[A_nDAC_24V_S].f_min_limit_val[0])*0.6; // Get lower search limit //
//	}
	Vforce = (UpperLimit + LowerLimit) / 2;
	if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
	{
		Vforce = 0;
		g_Error_Flag = -186;
	}
	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
	wait.delay_10_us(100);
	while ( (UpperLimit - LowerLimit) > .010)
	{
		Vforce = (UpperLimit + LowerLimit) / 2; 
		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -186;
			break;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
		if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
			LowerLimit = Vforce;
		else // Above threshold.  CV comparator high. //
			UpperLimit = Vforce;		
	}
	nDAC_24V_S = Vforce;

	// Reset bit 63 if changed previously //
	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
		//////
		////// Read out contents of shadow register.  Can't overwrite shadow register. //
		////Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
		////Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //

		////WordArray[0] = READ59_word[0];
		////WordArray[1] = READ59_word[1];
		////WordArray[2] = READ59_word[2];
		////WordArray[3] = READ59_word[3];
		////WordArray[4] = READ59_word[4];
		////WordArray[5] = READ59_word[5];
		////WordArray[6] = READ59_word[6];
		////WordArray[7] = READ59_word[7];
		////WordArray[8] = READ59_word[8];
		////WordArray[9] = READ59_word[9];
		////WordArray[10] = READ59_word[10];
		////WordArray[11] = READ59_word[11];
		////WordArray[12] = READ59_word[12];
		////WordArray[13] = READ59_word[13];
		////WordArray[14] = READ59_word[14];
		////WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
		//////
		WordArray[0] = g_EE_ShadReg48;
		WordArray[1] = g_EE_ShadReg49;
		WordArray[2] = g_EE_ShadReg50;
		WordArray[3] = g_EE_ShadReg51;
		WordArray[4] = g_EE_ShadReg52;
		WordArray[5] = g_EE_ShadReg53;
		WordArray[6] = g_EE_ShadReg54;
		WordArray[7] = g_EE_ShadReg55;
		WordArray[8] = g_EE_ShadReg56;
		WordArray[9] = g_EE_ShadReg57;
		WordArray[10] = g_EE_ShadReg58;
		WordArray[11] = g_EE_ShadReg59;
		WordArray[12] = g_EE_ShadReg60;
		WordArray[13] = g_EE_ShadReg61;
		WordArray[14] = g_EE_ShadReg62;
		WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //

		// bit[63]: trim_no_fb_pin, set back to one to disconnect COMP(FB) //
		WordArray[15] = 1;
		Write_Word(g_SREG3, NOhex, WordArray, BIN);
	}

	// Powerdown //
//	Mux20_Open_relay(K64);
//	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//	Mux20_Open_relay(K37);
//	Mux20_Open_relay(K38);
//	Mux20_Open_relay(K40);
//	Mux20_Open_relay(K39);
//	FB_ovi->connect(2);
	//VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0, get ready for next test //
	wait.delay_10_us(20);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
//	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//	wait.delay_10_us(45); // prevent SR undershoot //
//	Open_relay(K18);
//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//	wait.delay_10_us(5);
//	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//	wait.delay_10_us(200); // Wait for relays //

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Measure CV_Final-S //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

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
//	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	SR_dvi2k->set_current(SR_ch, 200.0e-3, RANGE_200_MA); // DVI_13_1, dvi2k //

	// BPS //
//	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	
	// COMP //
	FB_ovi->disconnect(2);

	// VBD //
//	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//	wait.delay_10_us(25); // Prevent glitch //
//	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
	uVCC_ovi->set_meas_mode(uVCC_ch, OVI_MEASURE_VOLTAGE); // OVI_3_2 //

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

	// Write byte to disable 10msec VI update lockout //
//	Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);

//	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //

	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Float SR dvi //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

	// Connect the FB comparator output to SR pin (CV comparator output). //
//	Write_Word(g_TM_SEL, 0x0024, NObin, HEX); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //
	
	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
//	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX); 

	// Reset CV back to 5V (default). //
	WordData = 33780;  // 5.0V //
	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //


	if (g_SiliconRev_Sec == 5) // Rev C silicon //
		wait.delay_10_us(1000); // Needed //
	else
		wait.delay_10_us(100); // Needed //



	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// CV_Final_S //
	// To improve repeatability for characterziaton only FOR THE CDC TESTS WHICH ARE DONE LATER, 
	// a binary search is first done to get the approximate value.  Then, linear searching is 
	// done first starting below the threshold and increasing until SR pin flips.  Next, linear 
	// searching is done starting above the threshold and decreasing until SR pin flips.  Then 
	// the average of the two search values is taken.  The is done because noise on the input to 
	// the comparator causes the SR pin to flip when getting near the threshold and by searching 
	// linearly from below and above and then taking the average this error is minimized.  
	// Additional averaging is done by performing the whole test 5 times.  This 
	// adds quite a bit of test time, but is only done for characterization. 
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (g_Char_Enable_P) // Characterization only //
	{
		LowerResult = 0;
		UpperResult = 0;
		LowerValue= 0;
		UpperValue= 0;
		FoundThresh = 0;
		stepSize = 0;
		i = 0;
		SumResult = 0;
		for (i=0; i<5; i++)
		{
			// Binary search CV [on Vout pin] to get the g_CV_Final_S value, should be around CV_Target_S. //
			// Look for FB comparator output flip on SR pin. //
			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
			UpperLimit = (func.dlog->tests[A_CV_Final_S].f_max_limit_val[0])*1.1; // Get upper search limit //
			LowerLimit = (func.dlog->tests[A_CV_Final_S].f_min_limit_val[0])*0.9; // Get lower search limit //
			if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
			{
				UpperLimit = (func.dlog->tests[A_CV_Final_S].f_max_limit_val[0])*1.4; // Get upper search limit //
				LowerLimit = (func.dlog->tests[A_CV_Final_S].f_min_limit_val[0])*0.6; // Get lower search limit //
			}
			Vforce = (UpperLimit + LowerLimit) / 2;
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -172;
			}
			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(5);
			while ( (UpperLimit - LowerLimit) > .001)
			{
				Vforce = (UpperLimit + LowerLimit) / 2; 
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -173;
					break;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(5);
				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
				if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
					LowerLimit = Vforce;
				else // Above threshold.  CV comparator high. //
					UpperLimit = Vforce;		
			}
			g_CV_Final_S = Vforce;


			LowerResult = 0;
			UpperResult = 0;
			LowerValue= Vforce - .05;
			UpperValue= Vforce + .05;
			FoundThresh = 0;
			stepSize = 0.001;
			Vforce = LowerValue;
			while ( Vforce < UpperValue && FoundThresh == 0)
			{
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -174;
					break;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(5);
				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
				if (SRpinVolt > 1.5) // Threshold found //
				{
					FoundThresh = 1;
				}
				Vforce += stepSize;
			}
			Vforce -= stepSize;
			LowerResult = Vforce;

			FoundThresh = 0;
			Vforce = UpperValue;
			while ( Vforce > LowerValue && FoundThresh == 0)
			{
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -175;
					break;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(5);
				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
				if (SRpinVolt < 1.5) // Threshold found //
				{
					FoundThresh = 1;
				}
				Vforce -= stepSize;
			}
			Vforce += stepSize;
			UpperResult = Vforce;
			g_CV_Final_S = ((LowerResult + UpperResult) / 2);
			SumResult += g_CV_Final_S;
		}
		g_CV_Final_S = SumResult / 5;
		if (g_Trim_Enable_P == 1)
			CV_Act_Chg_S = ((g_CV_Final_S - g_CV_pt_S) / g_CV_pt_S)*100; // In percent //
	}
	else // Production //
	{
		// Binary search CV [on Vout pin] to get the g_CV_Final_S value, should be around CV_Target_S. //
		// Look for FB comparator output flip on SR pin. //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
		UpperLimit = (func.dlog->tests[A_CV_Final_S].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_CV_Final_S].f_min_limit_val[0])*0.9; // Get lower search limit //
		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		{
			UpperLimit = (func.dlog->tests[A_CV_Final_S].f_max_limit_val[0])*1.4; // Get upper search limit //
			LowerLimit = (func.dlog->tests[A_CV_Final_S].f_min_limit_val[0])*0.6; // Get lower search limit //
		}
		Vforce = (UpperLimit + LowerLimit) / 2;
		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -180;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		while ( (UpperLimit - LowerLimit) > .001)
		{
			Vforce = (UpperLimit + LowerLimit) / 2; 
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -181;
				break;
			}
			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
			if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
				LowerLimit = Vforce;
			else // Above threshold.  CV comparator high. //
				UpperLimit = Vforce;		
		}
		g_CV_Final_S = Vforce;
		if (g_Trim_Enable_P == 1)
			CV_Act_Chg_S = ((g_CV_Final_S - g_CV_pt_S) / g_CV_pt_S)*100; // In percent //	
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Test VOUT_T (Report-Back Output Voltage Tolerance) //
	//
	// VOUT				Resolution
	// 3.0 to 7.2V		20mV
	// 7.2 to 10V		50mV
	// >10V				100mV
	// Check the 20mV, 50mV and 100mV resolution.  
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Turn on VBD drive //
	Write_Byte(g_VBEN, 0x83, NObin, HEX); 

	// Disable SR driver //
	Write_Word(g_TM_ANA, 0x0130, NObin, HEX); // Disable TM_EN_SR_driver //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 200.0e-3, RANGE_200_MA); // DVI_13_1, dvi2k //

	// Disconnect the FB comparator output from SR pin (CV comparator output). //
	Write_Word(g_TM_SEL, 0x0000, NObin, HEX); //  Write the I2C command to disconnect the FB comparator output from SR pin (CV comparator output). //

	// Write 0x0020 to TM_CTRL.  This will force secondary in control.  Without this, the FB 
	// comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is 
	// the main cause of the FB comparator reference shift. //
//	Write_Word(g_TM_CTRL, 0x0020, NObin, HEX); 
	Write_Word(g_TM_CTRL, 0x0A22, NObin, HEX); // Per design (Johnny) 7/26/2017.

	// IS //
	FB_ovi->disconnect(2); // Remove OVI from FB and use DVI2K instead for better accuracy. //
	Mux20_Close_relay(K46); // Connect DVI 2k to COMP pin intead of IS pin. //
	Mux20_Close_relay(K48); // Connect IS pin to ovi. //
	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_10_V); // OVI_3_4 //
	IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //

	// FB //
	Mux20_Close_relay(K55); // FB (COMP) pin to input of OP07 buffer.  Needed because the internal DAC 
							// ouput resistor is 80kohm, so the input impedance of the measure 
							// instrument needs to be 8Megohm just to get 1% accuracy. //
	Mux20_Close_relay(K56); // Output of OP07 buffer to DVI_13_0, dvi2k //
	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
	dvi_13->set_current(DVI_CHANNEL_0, 0.1e-9, RANGE_20_UA); // DVI_13_0, dvi2k, float //
	dvi_13->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_VOLTAGE); // DVI_13_0, dvi2k // 
	wait.delay_10_us(300); // Wait for relays //

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

	// For Rev B3 silicon, no averaging register. //
	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	{
		Write_Word(g_RDADDR, g_READ9, NObin, HEX);
		Read_Word(g_RDADDR, READ9_word);
		READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		READ9_word[13] = 0;
		READ9_word[14] = 0;
		READ9_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo3_20mV = VoutForce - CV_Result;
	}

	// Test chip //
	// For Rev C silicon, use averaging register. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// VTOL_Vo3_Avg
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		wait.delay_10_us(1500);
		Write_Word(g_RDADDR, g_READ14, NObin, HEX);
		Read_Word(g_RDADDR, READ14_word);
		//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
		//READ14_word[13] = 0;
		//READ14_word[14] = 0;
		//READ14_word[15] = 0;
		Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
		CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
		VTOL_Vo3_Avg = VoutForce - CV_Result;
	}	
	wait.delay_10_us(20);
	if (g_Char_Enable_P) // Characterization only //
	{
		VTOL_Vo3_VFB = dvi_13->measure_average(25);
	}


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ADC_Final
	// Good place to measure ADC_Final
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Force Vout, Read CV register //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
	wait.delay_10_us(10);
	VoutForce = 5.0;
	VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //

	// uVCC //
	// Force uVCC (LDO) directly to improve measurement stability per design 7/26/2017. //
	// Force 100mV above uVCC if Vout > uVCC //
	wait.delay_10_us(150);
	Meas_uVCC = uVCC_ovi->measure_average(5);
	uVCC_ovi->set_voltage(uVCC_ch, Meas_uVCC+0.1, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	wait.delay_10_us(600);

	// Read using I2C //
//	Write_Word(g_RDADDR, g_READ9, NObin, HEX);
//	Read_Word(g_RDADDR, READ9_word);
//	READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
//	READ9_word[13] = 0;
//	READ9_word[14] = 0;
//	READ9_word[15] = 0;
//	Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
//	g_ADC_Final = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //

	if (g_Char_Enable_P) // Characterization only //
	{
		// Measure FB pin voltage //
		g_ADC_Final = dvi_13->measure_average(25);
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		// Force 4V Vout, Read CV register //
		VoutForce = 4;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_5_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			// Read Vout with I2C //
			Write_Word(g_RDADDR, g_READ9, NObin, HEX);
			Read_Word(g_RDADDR, READ9_word);
			READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			READ9_word[13] = 0;
			READ9_word[14] = 0;
			READ9_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo4_20mV = VoutForce - CV_Result;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// VTOL_Vo4_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ14, NObin, HEX);
			Read_Word(g_RDADDR, READ14_word);
			//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			//READ14_word[13] = 0;
			//READ14_word[14] = 0;
			//READ14_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo4_Avg = VoutForce - CV_Result;
		}
		wait.delay_10_us(20);
		VTOL_Vo4_VFB = dvi_13->measure_average(25);
	}
		
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// Force 5V Vout, Read CV register //
		VoutForce = 5;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			// Read Vout with I2C //
			Write_Word(g_RDADDR, g_READ9, NObin, HEX);
			Read_Word(g_RDADDR, READ9_word);
			READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			READ9_word[13] = 0;
			READ9_word[14] = 0;
			READ9_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo5_20mV = VoutForce - CV_Result;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// VTOL_Vo5_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ14, NObin, HEX);
			Read_Word(g_RDADDR, READ14_word);
			//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			//READ14_word[13] = 0;
			//READ14_word[14] = 0;
			//READ14_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo5_Avg = VoutForce - CV_Result;
		}
		wait.delay_10_us(20);
		if (g_Char_Enable_P) // Characterization only //
		{
			VTOL_Vo5_VFB = dvi_13->measure_average(25);
		}

		if (g_Char_Enable_P) // Characterization only //
		{
			// Force 6V Vout, Read CV register //
			VoutForce = 6;
			VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);

			// For Rev B3 silicon, no averaging register. //
			if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
			{
				// Read Vout with I2C //
				Write_Word(g_RDADDR, g_READ9, NObin, HEX);
				Read_Word(g_RDADDR, READ9_word);
				READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				READ9_word[13] = 0;
				READ9_word[14] = 0;
				READ9_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo6_20mV = VoutForce - CV_Result;
			}

			// Test chip //
			// For Rev C silicon, use averaging register. //
			if (g_SiliconRev_Sec == 5) // Rev C silicon //
			{
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				// VTOL_Vo6_Avg
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				wait.delay_10_us(1500);
				Write_Word(g_RDADDR, g_READ14, NObin, HEX);
				Read_Word(g_RDADDR, READ14_word);
				//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				//READ14_word[13] = 0;
				//READ14_word[14] = 0;
				//READ14_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo6_Avg = VoutForce - CV_Result;
			}
			wait.delay_10_us(20);
			VTOL_Vo6_VFB = dvi_13->measure_average(25);
			
			// Force 7V Vout, Read CV register //
			VoutForce = 7;
			VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);

			// For Rev B3 silicon, no averaging register. //
			if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
			{
				// Read Vout with I2C //
				Write_Word(g_RDADDR, g_READ9, NObin, HEX);
				Read_Word(g_RDADDR, READ9_word);
				READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				READ9_word[13] = 0;
				READ9_word[14] = 0;
				READ9_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo7_20mV = VoutForce - CV_Result;
			}

			// Test chip //
			// For Rev C silicon, use averaging register. //
			if (g_SiliconRev_Sec == 5) // Rev C silicon //
			{
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				// VTOL_Vo7_Avg
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				wait.delay_10_us(1500);
				Write_Word(g_RDADDR, g_READ14, NObin, HEX);
				Read_Word(g_RDADDR, READ14_word);
				//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				//READ14_word[13] = 0;
				//READ14_word[14] = 0;
				//READ14_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo7_Avg = VoutForce - CV_Result;
			}
			wait.delay_10_us(20);
			VTOL_Vo7_VFB = dvi_13->measure_average(25);
		}


		// Write the I2C command to set_CV.  Needed to change to higher readback range.  3 ranges 
		// total for Rev.2 silicon: 0-6, 6-10, and 10-24V.  Need to set CV using customer 
		// programmable register to force part to go into next range. //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 1796; // Set to 9V //
		Write_Word(g_CV_reg, WordData, NObin, HEX);
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(100); // Needed //


		// Force Vout, Read CV register //
		VoutForce = 9;
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(150);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			Write_Word(g_RDADDR, g_READ9, NObin, HEX);
			Read_Word(g_RDADDR, READ9_word);
			READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			READ9_word[13] = 0;
			READ9_word[14] = 0;
			READ9_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo9_50mV = VoutForce - CV_Result;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// VTOL_Vo9_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ14, NObin, HEX);
			Read_Word(g_RDADDR, READ14_word);
			//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			//READ14_word[13] = 0;
			//READ14_word[14] = 0;
			//READ14_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo9_Avg = VoutForce - CV_Result;
		}
		wait.delay_10_us(20);
		if (g_Char_Enable_P) // Characterization only //
		{
			VTOL_Vo9_VFB = dvi_13->measure_average(25);
		}

		// Write the I2C command to set_CV.  Needed to change to higher readback range.  3 ranges 
		// total for Rev.2 silicon: 0-6, 6-10, and 10-24V.  Need to set CV using customer 
		// programmable register to force part to go into next range. //
		//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
		// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
		// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
		// and [7] and [15] are odd parity bits.  
		// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
		WordData = 36816; // Set to 20V //
		Write_Word(g_CV_reg, WordData, NObin, HEX);
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
			wait.delay_10_us(1000); // Needed //
		else
			wait.delay_10_us(100); // Needed //


		if (g_Char_Enable_P) // Characterization only //
		{
			// Force Vout, Read CV register //
			VoutForce = 12;
			VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_20_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);

			// For Rev B3 silicon, no averaging register. //
			if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
			{
				Write_Word(g_RDADDR, g_READ9, NObin, HEX);
				Read_Word(g_RDADDR, READ9_word);
				READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				READ9_word[13] = 0;
				READ9_word[14] = 0;
				READ9_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo12_100mV = VoutForce - CV_Result;
			}

			// Test chip //
			// For Rev C silicon, use averaging register. //
			if (g_SiliconRev_Sec == 5) // Rev C silicon //
			{
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				// VTOL_Vo12_Avg
				// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
				wait.delay_10_us(1500);
				Write_Word(g_RDADDR, g_READ14, NObin, HEX);
				Read_Word(g_RDADDR, READ14_word);
				//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
				//READ14_word[13] = 0;
				//READ14_word[14] = 0;
				//READ14_word[15] = 0;
				Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
				CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
				VTOL_Vo12_Avg = VoutForce - CV_Result;
			}
			wait.delay_10_us(20);
			VTOL_Vo12_VFB = dvi_13->measure_average(25);
		}


		// Force Vout, Read CV register //
		VoutForce = 21;
		VO_dvi->set_voltage(VO_ch, 15, VOLT_50_RANGE); // DVI_9_0, prevent overshoot //
		wait.delay_10_us(22); // Prevent overshoot //
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_50_RANGE); // DVI_9_0 //
		wait.delay_10_us(150);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{	
			Write_Word(g_RDADDR, g_READ9, NObin, HEX);
			Read_Word(g_RDADDR, READ9_word);
			READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			READ9_word[13] = 0;
			READ9_word[14] = 0;
			READ9_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo21_100mV = VoutForce - CV_Result;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// VTOL_Vo21_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ14, NObin, HEX);
			Read_Word(g_RDADDR, READ14_word);
			//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			//READ14_word[13] = 0;
			//READ14_word[14] = 0;
			//READ14_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo21_Avg = VoutForce - CV_Result;
		}
		wait.delay_10_us(20);
		if (g_Char_Enable_P) // Characterization only //
		{
			VTOL_Vo21_VFB = dvi_13->measure_average(25);
		}


		// Force Vout, Read CV register //
		VoutForce = 24;
		//VO_dvi->set_voltage(VO_ch, 15, VOLT_50_RANGE); // DVI_9_0, prevent overshoot //
		//wait.delay_10_us(22); // Prevent overshoot //
		VO_dvi->set_voltage(VO_ch, VoutForce, VOLT_50_RANGE); // DVI_9_0 //
		wait.delay_10_us(150);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			Write_Word(g_RDADDR, g_READ9, NObin, HEX);
			Read_Word(g_RDADDR, READ9_word);
			READ9_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			READ9_word[13] = 0;
			READ9_word[14] = 0;
			READ9_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ9_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo24_100mV = VoutForce - CV_Result;
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// VTOL_Vo24_Avg
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			wait.delay_10_us(1500);
			Write_Word(g_RDADDR, g_READ14, NObin, HEX);
			Read_Word(g_RDADDR, READ14_word);
			//READ14_word[12] = 0; // Be sure bit 12 to 15 are all zero. They are not part of the CV register. //
			//READ14_word[13] = 0;
			//READ14_word[14] = 0;
			//READ14_word[15] = 0;
			Convert_16bitBinary_To_Decimal(READ14_word, CV_Read);
			CV_Result = (float)CV_Read / 100; // Value returned from CV read is in 10mV steps //
			VTOL_Vo24_Avg = VoutForce - CV_Result;
		}
		wait.delay_10_us(20);
		if (g_Char_Enable_P) // Characterization only //
		{
			VTOL_Vo24_VFB = dvi_13->measure_average(25);
		}
	}
	// Powerdown //
	Mux20_Open_relay(K46);
	Mux20_Open_relay(K48);
	Mux20_Open_relay(K55);
	Mux20_Open_relay(K56);
	dvi_13->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
	dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	//Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	//Mux20_Open_relay(K37);
	//Mux20_Open_relay(K38);
	//Mux20_Open_relay(K40);
	//Mux20_Open_relay(K39);
	VO_dvi->set_voltage(VO_ch, 1, VOLT_5_RANGE); // DVI_9_0, prevent undershoot //
	wait.delay_10_us(20);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(0.5, 0, 0.1);
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
	//VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//wait.delay_10_us(20);
	//VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);


// Disconnect Op Amp supply.  dvi used as OpAmp supply. //
VBD_ramp_down(24, 0, 0.2);
Mux20_Open_relay(K36);
wait.delay_10_us(300);




	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	PiDatalog(func, A_pDAC_3V_S, pDAC_3V_S, 26, POWER_UNIT);
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_pDAC_4p84V_S, pDAC_4p84V_S, 26, POWER_UNIT);
		}
		PiDatalog(func, A_pDAC_4p92V_S, pDAC_4p92V_S, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_4p96V_S, pDAC_4p96V_S, 26, POWER_UNIT);	
		PiDatalog(func, A_pDAC_4p98V_S, pDAC_4p98V_S, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_4p99V_S, pDAC_4p99V_S, 26, POWER_UNIT);
	}
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_DeltaVOUT_10mV, DeltaVOUT_10mV, 26, POWER_MILLI);
	}
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		PiDatalog(func, A_pDAC_Final_S, pDAC_Final_S, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_Final_dlta, pDAC_Final_dlta, 26, POWER_UNIT);
	}
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_pDAC_TrCode0, pDAC_TrCode0, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode1, pDAC_TrCode1, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode2, pDAC_TrCode2, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode4, pDAC_TrCode4, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode8, pDAC_TrCode8, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode16, pDAC_TrCode16, 26, POWER_UNIT);
		PiDatalog(func, A_pDAC_TrCode31, pDAC_TrCode31, 26, POWER_UNIT);
	}
	if (g_Trim_Enable_P == 1)
		PiDatalog(func, A_pDAC_Act_Chg_S, pDAC_Act_Chg_S, 26, POWER_UNIT);
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		PiDatalog(func, A_nDAC_5p1V_S, nDAC_5p1V_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_5p2V_S, nDAC_5p2V_S, 26, POWER_UNIT);
		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_DeltaVOUT_100mV, DeltaVOUT_100mV, 26, POWER_MILLI);
		}
		PiDatalog(func, A_nDAC_5p4V_S, nDAC_5p4V_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_5p8V_S, nDAC_5p8V_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_6p6V_S, nDAC_6p6V_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_8p2V_S, nDAC_8p2V_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_20V_S, nDAC_20V_S, 26, POWER_UNIT);
	}
	PiDatalog(func, A_nDAC_24V_S, nDAC_24V_S, 26, POWER_UNIT);
	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		PiDatalog(func, A_nDAC_Final_S, nDAC_Final_S, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_Final_dlta, nDAC_Final_dlta, 26, POWER_UNIT);
	}
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_nDAC_TrCode0, nDAC_TrCode0, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode1, nDAC_TrCode1, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode2, nDAC_TrCode2, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode4, nDAC_TrCode4, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode8, nDAC_TrCode8, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode16, nDAC_TrCode16, 26, POWER_UNIT);
		PiDatalog(func, A_nDAC_TrCode31, nDAC_TrCode31, 26, POWER_UNIT);
	}
	if (g_Trim_Enable_P == 1)
		PiDatalog(func, A_nDAC_Act_Chg_S, nDAC_Act_Chg_S, 26, POWER_UNIT);
	PiDatalog(func, A_CV_Final_S, g_CV_Final_S, 26, POWER_UNIT);
	if (g_Trim_Enable_P == 1)
		PiDatalog(func, A_CV_Act_Chg_S, CV_Act_Chg_S, 26, POWER_UNIT);
	//PiDatalog(func, A_VOUT_T, VOUT_T, 25, POWER_MILLI); // No longer needed //

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo3_VFB, VTOL_Vo3_VFB, 25, POWER_UNIT);
	}

	// For Rev B3 silicon, no averaging register. //
	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	{
		PiDatalog(func, A_VTOL_Vo3_20mV, VTOL_Vo3_20mV, 25, POWER_MILLI);
	}
	
	// Test chip //
	// For Rev C silicon, use averaging register. //
	if (g_SiliconRev_Sec == 5) // Rev C silicon //
	{
		PiDatalog(func, A_VTOL_Vo3_Avg, VTOL_Vo3_Avg, 25, POWER_MILLI);
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo4_VFB, VTOL_Vo4_VFB, 25, POWER_UNIT);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo4_20mV, VTOL_Vo4_20mV, 25, POWER_MILLI);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo4_Avg, VTOL_Vo4_Avg, 25, POWER_MILLI);
		}
	}	

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo5_VFB, VTOL_Vo5_VFB, 25, POWER_UNIT);
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo5_20mV, VTOL_Vo5_20mV, 25, POWER_MILLI);
		}
		
		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo5_Avg, VTOL_Vo5_Avg, 25, POWER_MILLI);
		}
	}
	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo6_VFB, VTOL_Vo6_VFB, 25, POWER_UNIT);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo6_20mV, VTOL_Vo6_20mV, 25, POWER_MILLI);
		}
		
		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo6_Avg, VTOL_Vo6_Avg, 25, POWER_MILLI);
		}

		PiDatalog(func, A_VTOL_Vo7_VFB, VTOL_Vo7_VFB, 25, POWER_UNIT);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo7_20mV, VTOL_Vo7_20mV, 25, POWER_MILLI);
		}
		
		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo7_Avg, VTOL_Vo7_Avg, 25, POWER_MILLI);
		}
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo9_VFB, VTOL_Vo9_VFB, 25, POWER_UNIT);
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo9_50mV, VTOL_Vo9_50mV, 25, POWER_MILLI);
		}
		
		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo9_Avg, VTOL_Vo9_Avg, 25, POWER_MILLI);
		}
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo12_VFB, VTOL_Vo12_VFB, 25, POWER_UNIT);

		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo12_100mV, VTOL_Vo12_100mV, 25, POWER_MILLI);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo12_Avg, VTOL_Vo12_Avg, 25, POWER_MILLI);
		}
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo21_VFB, VTOL_Vo21_VFB, 25, POWER_UNIT);
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo21_100mV, VTOL_Vo21_100mV, 25, POWER_MILLI);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo21_Avg, VTOL_Vo21_Avg, 25, POWER_MILLI);
		}
	}

	if (g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_VTOL_Vo24_VFB, VTOL_Vo24_VFB, 25, POWER_UNIT);
	}

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// For Rev B3 silicon, no averaging register. //
		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
		{
			PiDatalog(func, A_VTOL_Vo24_100mV, VTOL_Vo24_100mV, 25, POWER_MILLI);
		}

		// Test chip //
		// For Rev C silicon, use averaging register. //
		if (g_SiliconRev_Sec == 5) // Rev C silicon //
		{
			PiDatalog(func, A_VTOL_Vo24_Avg, VTOL_Vo24_Avg, 25, POWER_MILLI);
		}
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		CV_nDAC_pDAC_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_CV_nDAC_pDAC_TT, CV_nDAC_pDAC_TT, 26, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
