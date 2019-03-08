//==============================================================================
// VPK.cpp (User function)
// 
//    void VPK_user_init(test_function& func)
//    void VPK(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "VPK.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VPK_user_init(test_function& func)
{
	VPK_params *ours;
    ours = (VPK_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VPK(test_function& func)
{
    // The two lines below must be the first two in the function.
    VPK_params *ours;
    ours = (VPK_params *)func.params;

	// Increment function number //
	gFuncNum++;

////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_VPK, gFuncNum, 26, POWER_UNIT);
////
////	// Skip Test if AbortTest set //
////	if (AbortTest)
////		return;
////
////	if (g_Fn_VPK == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	float VPK_5_3_A = 0;
////	float VPK_5_3_B = 0;
////	float Pvpk_5_3_isvth = 0;
////	float Pvpk_5_3_imid = 0;
////	float VPK_10 = 0;
////	float VPK_15 = 0;
////	float VPK_20_A = 0;
////	float VPK_20_B = 0;
////	float VPK_23_5_A = 0;
////	float TOLP_OUT_ilow1 = 0;
////	float TOLP_OUT_ilow2 = 0;
////	float TOLP_OUT_imid1 = 0;
////	float TOLP_OUT_imid2 = 0;
////	float TOLP_OUT_ihigh1 = 0;
////	float TOLP_OUT_ihigh2 = 0;
////	float t_VI = 0;
////	float VPK_TT = 0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	int WordArray[16] = {0};
////	int READ59_word[16] = {0};
////	int TempArray[30] = {0};
////	float WordData = 0;
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	float IsPinVolt = 0;
////	float Vforce = 0;
////	float SRpinVolt = 0;
////	float VPK_5_4 = 0;
////	int ReadTotal = 0;
////	float SetCV = 0;
////	float TimeStop = 0;
////	float TimeStart = 0;
////	int Counter = 0;
////	float Is = 0;
////	float TempValue = 0;
////	float TempValue2 = 0;
////	float DeltaV = 0;
////	float CC_100_pct = 0;
////	float I_mid = 0.019;
////	float VoutMeas = 0;
////	float PctBelow = 0;
////	//float I_low = 0;
////	float IsForce = 0;
////	Pulse pulse;
////
////	// Rev B3 silicon //
////	if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
////	{
////		// Set full CC //
////		CC_100_pct = g_ISVTH; // Change to ISVTH per design(Johnny) 10/23/2017. //
////	
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			// Open all relays //
////			//Initialize_Relays();
////
////			// Initialize Instruments //
////			//Initialize_Instruments();
////
////			// Drain //
////			D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////			D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////
////			// BPP //
////			BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////			// V pin //
////			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////
////			// FW //
////			Close_relay(K18);
////			FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////			FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////
////			// SR //
////			SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////			//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////
////			// BPS //
////			//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////			//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////			// IS //
////			mux_14->close_relay(MUX_2_GND);
////			Close_relay(K24); // Connect IS pin to 20X buffer. //
////			//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////			//IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////			// Vout //
////			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
////			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////			// FB (COMP) //
////			FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
////			FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
////			FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////			// VBD //
////			VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////			//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////			//wait.delay_10_us(25); // Prevent glitch //
////			VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////
////			// uVCC //
////			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////			uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////			// DDD level //
////			//g_DDD_Low = 0.0; // Save current value //
////			//g_DDD_High = 3.3; // Save current value //
////			//wait.delay_10_us(100);
////			//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////			//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////			//wait.delay_10_us(100);
////
////			// SDA //
////			Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////			ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////			ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////			Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////			Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////			Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////			// SCL //
////			Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
////			ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////			// Set DDD for I2C. //
////			//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////			//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////				
////			// Wait for relays //
////			wait.delay_10_us(200); 
////
////			// Powerup //
////			//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////			//wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////			// I2C into test mode. //  
////			//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////			//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////			//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////			//	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //
////
////			// Float SR dvi //
////			SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////
////			// Connect the FB comparator output to SR pin (CV comparator output). //
////			//Write_Word(g_TM_SEL, 0x0024, NObin, HEX);
////
////			// Program the CDC with I2C to 0V. //
////			TempValue = (0*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
////			Write_Byte(g_CDC, TempValue, NObin, HEX);
////
////			// Write 0x0020 to TM_CTRL.  This will force secondary in control. 
////			// Without this, the FB comparator reference is shifted causing a measurement error. //
////			Write_Word(g_TM_CTRL, 0x0020, NObin, HEX);
////
////			// Write byte to disable 10msec VI update lockout //
////			//Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////
////			// Program Output Over-voltage Threshold to 25V, to prevent hitting OVA. //
////			//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
////			// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////			// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////			// and [7] and [15] are odd parity bits.  
////			// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////			WordData = 378;  // 25V //
////			Write_Word(g_OVA, WordData, NObin, HEX);
////
////			// Setup IS pin voltage. //
////			IsPinVolt = CC_100_pct;
////			IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////			{
////				IsPinVolt =0;
////				g_Error_Flag = -140;
////			}
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(100);
////
////			// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enabled the 
////			// timer is 8X longer and it takes much longer for CV to come down to VPK. //
////			Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////			
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// t_VI
////			// Maximum V/I Update Rate
////			// Program CV with I2C until SR pin flips- CV will not change until the timer has expired.
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set Vout to 5V //
////			VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //
////			wait.delay_10_us(20);
////			
////			// Set CV to 6V with I2C //
////			WordData = 1112; // 6V //
////			Write_Word(g_CV_reg, WordData, NObin, HEX);
////			TimeStart = mytimer.GetElapsedTime();
////
////			// Make sure SR pin is low //
////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. //
////			if (SRpinVolt > 2.5) // Error //
////			{
////				g_Error_Flag = -192;
////			}
////			
////			// Keep setting CV with I2C until SR pin flips.  CV will not change until lockout timer has expired. //
////			Counter = 0;
////			while (SRpinVolt < 2.5 && Counter < 1000)
////			{
////				// Set CV to 4V with I2C //
////				WordData = 33552; // 4V //
////				Write_Word(g_CV_reg, WordData, NObin, HEX);
////				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. //
////				Counter++;
////			}
////			TimeStop = mytimer.GetElapsedTime();
////			t_VI = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
////
////			// Error.  Force failure. //
////			if (g_Error_Flag == -192 )
////				t_VI = -99;
////
////			// Write byte to disable 10msec VI update lockout //
////			Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////
////			// Power Down //
////			//Open_relay(K18);
////			FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////			SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////			Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
////			BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////			//mux_14->open_relay(MUX_2_GND);
////			//Open_relay(K24);
////			IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////			VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////			VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////			uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////			//Mux20_Open_relay(K64);
////			ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////			//Mux20_Open_relay(K37);
////			//Mux20_Open_relay(K38);
////			//Mux20_Open_relay(K40);
////			//Mux20_Open_relay(K39);
////			//ddd_7->ddd_set_clock_period(Dclk_period);
////			//ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////			// DDD level //
////			//g_DDD_Low = 0.0; // Save current value //
////			//g_DDD_High = 4.0; // Save current value //
////			//wait.delay_10_us(100);
////			//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////			//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////			wait.delay_10_us(200); // Wait for relays //
////		}
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Constant power ouput (CP) tests. 
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
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
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////		
////		// IS //
////		mux_14->close_relay(MUX_2_GND);
////		Close_relay(K24); // Connect IS pin to 20X buffer. //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
////
////		// uVCC //
////		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////		// Vout //
////		Mux20_Close_relay(K53); // Connect Vout pin to Op Amp output. //
////		VO_dvi->set_current(VO_ch, 0.1e-9, RANGE_30_UA); // DVI_9_0, float //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////
////		// COMP //
////		FB_ovi->disconnect(2);
////		Mux20_Close_relay(K54); // Connect FB pin to Op Amp negative input. //
////
////		// Setup Op Amp positive input reference to 1.25V. //
////		ovi_3->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_3_6 //
////		ovi_3->set_voltage(OVI_CHANNEL_6, 1.25, RANGE_2_V); // OVI_3_6 //
////
////		// VBD //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////		wait.delay_10_us(25); // Prevent glitch //
////		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
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
////		Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
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
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// I2C into test mode. //  
////		Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////		Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////		// Program the CDC with I2C to 0V. //
////		TempValue = (0*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
////		Write_Byte(g_CDC, TempValue, NObin, HEX);
////
////		// Write 0x0020 to TM_CTRL.  This will force secondary in control. 
////		// Without this, the FB comparator reference is shifted causing a measurement error. //
////		Write_Word(g_TM_CTRL, 0x0020, NObin, HEX);
////
////		// Program Output Over-voltage Threshold to 25V, to prevent hitting OVA. //
////		WordData = 378;  // 25V //
////		Write_Word(g_OVA, WordData, NObin, HEX);
////
////		// Setup IS pin voltage. //
////		IsPinVolt = 0;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enabled the 
////		// timer is 8X longer and it takes much longer for CV to come down to VPK. //
////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////
////		// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
////		// switching freqeuncy with FB pin //
////		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////		{
////			/*
////			// Read out contents of shadow register.  Can't overwrite shadow register. //
////			Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
////			Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
////
////			WordArray[0] = READ59_word[0];
////			WordArray[1] = READ59_word[1];
////			WordArray[2] = READ59_word[2];
////			WordArray[3] = READ59_word[3];
////			WordArray[4] = READ59_word[4];
////			WordArray[5] = READ59_word[5];
////			WordArray[6] = READ59_word[6];
////			WordArray[7] = READ59_word[7];
////			WordArray[8] = READ59_word[8];
////			WordArray[9] = READ59_word[9];
////			WordArray[10] = READ59_word[10];
////			WordArray[11] = READ59_word[11];
////			WordArray[12] = READ59_word[12];
////			WordArray[13] = READ59_word[13];
////			WordArray[14] = READ59_word[14];
////			WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
////			*/
////			WordArray[0] = g_EE_ShadReg48;
////			WordArray[1] = g_EE_ShadReg49;
////			WordArray[2] = g_EE_ShadReg50;
////			WordArray[3] = g_EE_ShadReg51;
////			WordArray[4] = g_EE_ShadReg52;
////			WordArray[5] = g_EE_ShadReg53;
////			WordArray[6] = g_EE_ShadReg54;
////			WordArray[7] = g_EE_ShadReg55;
////			WordArray[8] = g_EE_ShadReg56;
////			WordArray[9] = g_EE_ShadReg57;
////			WordArray[10] = g_EE_ShadReg58;
////			WordArray[11] = g_EE_ShadReg59;
////			WordArray[12] = g_EE_ShadReg60;
////			WordArray[13] = g_EE_ShadReg61;
////			WordArray[14] = g_EE_ShadReg62;
////			WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
////
////			// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
////			WordArray[15] = 0;
////			Write_Word(g_SREG3, NOhex, WordArray, BIN);
////		}
////		
////		
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// VPK_5_3_A
////		// Pvpk_5_3_isvth
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	
////		// Setup IS pin voltage. //
////		IsPinVolt = CC_100_pct;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////
////		// Set CV to 21V and VPK to 5.3V. This is the worst case (i.e. most error) for measuring output power per design. //
////		// Set CV to 21V.
////		WordData = 4148; // 21V //
////		Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////	
////		// Set VPK to 5.3V //
////		WordData = 32949; // 5.3V //
////		Write_Word(g_VPK_reg, WordData, NObin, HEX);
////		wait.delay_10_us(50);
////
////		// Wait for Vout to settle. //
////		Counter = 0;
////		DeltaV = 99; // Initialize //
////		while ( DeltaV > .005 && Counter < 40 )
////		{
////			TempValue = VO_dvi->measure_average(5);
////			wait.delay_10_us(500); // Needed //
////			TempValue2 = VO_dvi->measure_average(5);
////			DeltaV = TempValue - TempValue2;
////			if(DeltaV<0) // Remove negative //
////				DeltaV *= -1;
////			Counter++;
////		}
////
////		
////		// Measure Vout, output of op amp //
////	
////		VPK_5_3_A = VO_dvi->measure_average(5);
////		Pvpk_5_3_isvth = VPK_5_3_A * CC_100_pct; // Power at 100%CC //
////	
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Pvpk_5_3_imid
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Setup IS pin voltage. //
////		IsPinVolt = I_mid;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////
////		// Wait for Vout to settle. //
////		Counter = 0;
////		DeltaV = 99; // Initialize //
////		while ( DeltaV > .005 && Counter < 40 )
////		{
////			TempValue = VO_dvi->measure_average(5);
////			wait.delay_10_us(500); // Needed //
////			TempValue2 = VO_dvi->measure_average(5);
////			DeltaV = TempValue - TempValue2;
////			if(DeltaV<0) // Remove negative //
////				DeltaV *= -1;
////			Counter++;
////		}
////		
////		// Measure Vout, output of op amp //
////		TempValue = VO_dvi->measure_average(5);
////		Pvpk_5_3_imid = TempValue * I_mid; // Power at middle of Cp curve. //
////	
////
////		// Setup IS pin voltage. //
////		IsPinVolt = CC_100_pct;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////
////		if (g_Char_Enable_P == 1)
////		{
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VPK_10
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set VPK to 10V //
////			WordData = 32868;
////			Write_Word(g_VPK_reg, WordData, NObin, HEX);
////			//wait.delay_10_us(1000);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .005 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(500); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			VPK_10 = VO_dvi->measure_average(5);
////
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VPK_15
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set VPK to 15V //
////			WordData = 278;
////			Write_Word(g_VPK_reg, WordData, NObin, HEX);
////			//wait.delay_10_us(1000);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .005 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(500); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			VPK_15 = VO_dvi->measure_average(5);
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VPK_20_A
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// CV reg to 24V to be sure CV is above 20 for VPK_20_A test //
////			WordData = 37600; // 24 //
////			Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////			// Set VPK to 20V //
////			WordData = 456;
////			Write_Word(g_VPK_reg, WordData, NObin, HEX);
////			//wait.delay_10_us(1000);
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .005 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(500); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			VPK_20_A = VO_dvi->measure_average(5);
////		}	
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// VPK_23_5_A
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Set VPK to 20V //
////		// Needed to set VPK to 20V first for repeatability problem for VPK_23_5_A test.  Not sure why. Can
////		// go back and debug later. //
////		WordData = 456;
////		Write_Word(g_VPK_reg, WordData, NObin, HEX);
////
////		// Setup test mode //
////		Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////		Write_Word(g_TM_SEL, 0x0024, NObin, HEX); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////		Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////		{
////			/*
////			// Read out contents of shadow register.  Can't overwrite shadow register. //
////			Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
////			Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
////
////			WordArray[0] = READ59_word[0];
////			WordArray[1] = READ59_word[1];
////			WordArray[2] = READ59_word[2];
////			WordArray[3] = READ59_word[3];
////			WordArray[4] = READ59_word[4];
////			WordArray[5] = READ59_word[5];
////			WordArray[6] = READ59_word[6];
////			WordArray[7] = READ59_word[7];
////			WordArray[8] = READ59_word[8];
////			WordArray[9] = READ59_word[9];
////			WordArray[10] = READ59_word[10];
////			WordArray[11] = READ59_word[11];
////			WordArray[12] = READ59_word[12];
////			WordArray[13] = READ59_word[13];
////			WordArray[14] = READ59_word[14];
////			WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
////			*/
////
////			WordArray[0] = g_EE_ShadReg48;
////			WordArray[1] = g_EE_ShadReg49;
////			WordArray[2] = g_EE_ShadReg50;
////			WordArray[3] = g_EE_ShadReg51;
////			WordArray[4] = g_EE_ShadReg52;
////			WordArray[5] = g_EE_ShadReg53;
////			WordArray[6] = g_EE_ShadReg54;
////			WordArray[7] = g_EE_ShadReg55;
////			WordArray[8] = g_EE_ShadReg56;
////			WordArray[9] = g_EE_ShadReg57;
////			WordArray[10] = g_EE_ShadReg58;
////			WordArray[11] = g_EE_ShadReg59;
////			WordArray[12] = g_EE_ShadReg60;
////			WordArray[13] = g_EE_ShadReg61;
////			WordArray[14] = g_EE_ShadReg62;
////			WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
////
////			// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
////			WordArray[15] = 1;
////			Write_Word(g_SREG3, NOhex, WordArray, BIN);
////		}
////		Mux20_Open_relay(K53); // Disconnect Vout pin from Op Amp output. //
////		wait.delay_10_us(250);
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_50_RANGE); // DVI_9_0, prevent undershoot //
////		Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
////		wait.delay_10_us(10);
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////		FB_ovi->connect(2);
////		FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
////		FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
////		FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////		// Disconnect Op Amp positive input reference. //
////		ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //
////
////		// 100% CC //
////		IS_dvi2k->set_voltage(IS_ch, CC_100_pct, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(250); // Wait for relays //
////
////		// CV reg to 24V to be sure CV is above 20 for VPK_20_A test //
////		WordData = 37600; // 24 //
////		Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////		// Set VPK to 23.5V //
////		WordData = 363; // 23.5V //
////		Write_Word(g_VPK_reg, WordData, NObin, HEX);
////		wait.delay_10_us(1000); // Needed //
////
////		// Binary search VPK [on Vout pin]. //
////		// Look for FB comparator output flip on SR pin. //
////		//SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
////		UpperLimit = (func.dlog->tests[A_VPK_23_5_A].f_max_limit_val[0])*1.1; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_VPK_23_5_A].f_min_limit_val[0])*0.9; // Get lower search limit //
//////		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//////		{
//////			UpperLimit = (func.dlog->tests[A_VPK_23_5_A].f_max_limit_val[0])*1.4; // Get upper search limit //
//////			LowerLimit = (func.dlog->tests[A_VPK_23_5_A].f_min_limit_val[0])*0.6; // Get lower search limit //
//////		}
////		Vforce = (UpperLimit + LowerLimit) / 2;
////		if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -151;
////		}
////		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(100);
////		while ( (UpperLimit - LowerLimit) > .001)
////		{
////			Vforce = (UpperLimit + LowerLimit) / 2; 
////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////			{
////				Vforce = 0;
////				g_Error_Flag = -152;
////				break;
////			}
////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////			wait.delay_10_us(100);
////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
////			if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
////				LowerLimit = Vforce;
////			else // Above threshold.  CV comparator high. //
////				UpperLimit = Vforce;		
////		}
////		VPK_23_5_A = Vforce;
////
////		// Set VPK to 23.5V //
////		//WordData = 363;
////		//Write_Word(g_VPK_reg, WordData, NObin, HEX);
////		//wait.delay_10_us(1000);
////		//VPK_23_5_A = VO_dvi->measure_average(5);
////
////		// Power Down //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
////		FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////		Open_relay(K18);
////		mux_14->open_relay(MUX_2_GND);
////		Open_relay(K24);
////		//Mux20_Open_relay(K53); // Disconnect Vout pin from Op Amp output. //
////		//wait.delay_10_us(250);
////		//VO_dvi->set_voltage(VO_ch, 5, VOLT_50_RANGE); // DVI_9_0, prevent undershoot //
////		//Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
////		//wait.delay_10_us(10);
////		//VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////		wait.delay_10_us(20);
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		uVCCrampDown(0.5, 0, 0.1);
////		SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		wait.delay_10_us(45); // prevent SR undershoot //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		wait.delay_10_us(5);
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		wait.delay_10_us(20);
////		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////		ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////		FB_ovi->connect(2);
////		FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
////		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////		ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //
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
////		// Datalog //
////		PiDatalog(func, A_VPK_5_3_A, VPK_5_3_A, 26, POWER_UNIT);
////		PiDatalog(func, A_Pvpk_5_3_isvth, Pvpk_5_3_isvth, 26, POWER_UNIT);
////		PiDatalog(func, A_Pvpk_5_3_imid, Pvpk_5_3_imid, 26, POWER_UNIT);
////		
////		if (g_Char_Enable_P == 1)
////		{
////			PiDatalog(func, A_VPK_10, VPK_10, 26, POWER_UNIT);
////			PiDatalog(func, A_VPK_15, VPK_15, 26, POWER_UNIT);
////			PiDatalog(func, A_VPK_20_A, VPK_20_A, 26, POWER_UNIT);
////		}
////		PiDatalog(func, A_VPK_23_5_A, VPK_23_5_A, 26, POWER_UNIT);
////
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			PiDatalog(func, A_t_VI, t_VI, 26, POWER_MILLI);
////		}
////		
////		// Test Time End //
////		if (g_TstTime_Enble_P)
////		{
////			g_endtime = g_mytimer.GetElapsedTime();
////			VPK_TT = (g_endtime - g_begintime)*1e-6;
////			PiDatalog(func, A_VPK_TT, VPK_TT, 26, POWER_MILLI);
////		}
////	}
////
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////
////	// Rev C silicon //
////	if (g_SiliconRev_Sec == 5) // Rev C silicon //
////	{
////		CC_100_pct = 0.032;
////		PctBelow = 0.95;
////
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			// Open all relays //
////			//Initialize_Relays();
////
////			// Initialize Instruments //
////			//Initialize_Instruments();
////
////			// Drain //
////			D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////			D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////
////			// BPP //
////			BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////			// V pin //
////			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////
////			// FW //
////			Close_relay(K18);
////			FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
////			FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////
////			// SR //
////			SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////			//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////
////			// BPS //
////			//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////			//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////			// IS //
////			mux_14->close_relay(MUX_2_GND);
////			Close_relay(K24); // Connect IS pin to 20X buffer. //
////			//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////			//IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////			// Vout //
////			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
////			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////			// FB (COMP) //
////			FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
////			FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
////			FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////			// VBD //
////			VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////			//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////			//wait.delay_10_us(25); // Prevent glitch //
////			VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
////
////			// uVCC //
////			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////			uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////			// DDD level //
////			//g_DDD_Low = 0.0; // Save current value //
////			//g_DDD_High = 3.3; // Save current value //
////			//wait.delay_10_us(100);
////			//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////			//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////			//wait.delay_10_us(100);
////
////			// SDA //
////			Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////			ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////			ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////			Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////			Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////			Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////			// SCL //
////			Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
////			ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////			// Set DDD for I2C. //
////			//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////			//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////				
////			// Wait for relays //
////			wait.delay_10_us(200); 
////
////			// Powerup //
////			//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////			//wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////			// I2C into test mode. //  
////			//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////			//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////			//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////			//	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //
////
////			// Float SR dvi //
////			SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////
////			// Connect the FB comparator output to SR pin (CV comparator output). //
////			//Write_Word(g_TM_SEL, 0x0024, NObin, HEX);
////
////			// Program the CDC with I2C to 0V. //
////			TempValue = (0*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
////			Write_Byte(g_CDC, TempValue, NObin, HEX);
////
////			// Write 0x0020 to TM_CTRL.  This will force secondary in control. 
////			// Without this, the FB comparator reference is shifted causing a measurement error. //
////			Write_Word(g_TM_CTRL, 0x0020, NObin, HEX);
////
////			// Write byte to disable 10msec VI update lockout //
////			//Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////
////			// Program Output Over-voltage Threshold to 25V, to prevent hitting OVA. //
////			//WordData = 372; // 10mV per LSB.  For example, to set 3.72V,  WordData = 3.72/0.01 = 372. //
////			// For Rev.2 silicon bit[7] is odd parity bit for bits 0 to 6, and bit[15] is odd parity 
////			// bit for bits 7 through 11. Therefore, data bits 7,8,9,10,11 shift to left by one, 
////			// and [7] and [15] are odd parity bits.  
////			// For example, (decimal 372)0000 0001 0111 0100 becomes (decimal 756)0000 0010 1111 0100. //
////			WordData = 378;  // 25V //
////			Write_Word(g_OVA, WordData, NObin, HEX);
////
////			// Setup IS pin voltage. //
////			IsPinVolt = CC_100_pct;
////			IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////			{
////				IsPinVolt =0;
////				g_Error_Flag = -140;
////			}
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(100);
////
////			// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enabled the 
////			// timer is 8X longer and it takes much longer for CV to come down to VPK. //
////			Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////			
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// t_VI
////			// Maximum V/I Update Rate
////			// Program CV with I2C until SR pin flips- CV will not change until the timer has expired.
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set Vout to 5V //
////			VO_dvi->set_voltage(VO_ch, 5, VOLT_10_RANGE); // DVI_9_0 //
////			wait.delay_10_us(20);
////			
////			// Set CV to 6V with I2C //
////			WordData = 1112; // 6V //
////			Write_Word(g_CV_reg, WordData, NObin, HEX);
////			TimeStart = mytimer.GetElapsedTime();
////
////			wait.delay_10_us(150); // Needed //
////			
////			// Make sure SR pin is low //
////			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. //
////			if (SRpinVolt > 2.5) // Error //
////			{
////				g_Error_Flag = -192;
////			}
////			
////			// Keep setting CV with I2C until SR pin flips.  CV will not change until lockout timer has expired. //
////			Counter = 0;
////			while (SRpinVolt < 2.5 && Counter < 1000)
////			{
////				// Set CV to 4V with I2C //
////				WordData = 33552; // 4V //
////				Write_Word(g_CV_reg, WordData, NObin, HEX);
////				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. //
////				Counter++;
////			}
////			TimeStop = mytimer.GetElapsedTime();
////			t_VI = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
////
////			// Error.  Force failure. //
////			if (g_Error_Flag == -192 )
////				t_VI = -99;
////
////			// Write byte to disable 10msec VI update lockout //
////			Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////		}
////
////		// Power Down //
////		//Open_relay(K18);
////		FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		//mux_14->open_relay(MUX_2_GND);
////		//Open_relay(K24);
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////		FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
////		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////		//FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		//Mux20_Open_relay(K64);
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////		//Mux20_Open_relay(K37);
////		//Mux20_Open_relay(K38);
////		//Mux20_Open_relay(K40);
////		//Mux20_Open_relay(K39);
////		//ddd_7->ddd_set_clock_period(Dclk_period);
////		//ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////		// DDD level //
////		//g_DDD_Low = 0.0; // Save current value //
////		//g_DDD_High = 4.0; // Save current value //
////		//wait.delay_10_us(100);
////		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(300); // Wait for relays //
////	
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// VPK
////		// Constant Output Power Onset Threshold Programming Range
////		//
////		// TOLP_OUT
////		// Constant Output Power Tolerance
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
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
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////		
////		// IS //
////		mux_14->close_relay(MUX_2_GND);
////		Close_relay(K24); // Connect IS pin to 20X buffer. //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
////
////		// uVCC //
////		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
////		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
////
////		// Connect Op Amp supply.  dvi used as OpAmp supply. //
////		// Limit supply to 10V during connection to prevent Vout going to high- will damage part. //
////		Mux20_Close_relay(K36);
////		wait.delay_10_us(300);
////		VBD_ramp_up(0, 1, 0.2);
////		VBD_dvi->set_current(VBD_ch, 300e-3, RANGE_300_MA); // DVI_21_0, prevent glitch //
////		VBD_ramp_up(1, 10, 0.2);
////
////		// Vout //
////		Mux20_Close_relay(K53); // Connect Vout pin to Op Amp output. //
////		VO_dvi->set_current(VO_ch, 0.1e-9, RANGE_30_UA); // DVI_9_0, float //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////		VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////
////		// COMP //
////		FB_ovi->disconnect(2);
////		Mux20_Close_relay(K54); // Connect FB pin to Op Amp negative input. //
////
////		// Setup Op Amp positive input reference to 1.25V. //
////		ovi_3->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_3_6 //
////		ovi_3->set_voltage(OVI_CHANNEL_6, 1.25, RANGE_2_V); // OVI_3_6 //
////
////		// VBD //
////		//VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////		//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
////		//wait.delay_10_us(25); // Prevent glitch //
////		//VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
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
////		Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////		// SCL //
////		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
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
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// I2C into test mode. //  
////		Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////		Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////		// Program the CDC with I2C to 0V. //
////		TempValue = (0*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
////		Write_Byte(g_CDC, TempValue, NObin, HEX);
////
////		// Write 0x0020 to TM_CTRL.  This will force secondary in control. 
////		// Without this, the FB comparator reference is shifted causing a measurement error. //
////		Write_Word(g_TM_CTRL, 0x0020, NObin, HEX);
////
////		// Program Output Over-voltage Threshold to 25V, to prevent hitting OVA. //
////		WordData = 378;  // 25V //
////		Write_Word(g_OVA, WordData, NObin, HEX);
////
////		// Setup IS pin voltage. //
////		IsPinVolt = 0;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////	
////		// Enable the bus switch (VBD) to speed up the timer.  If VBD is not enabled the 
////		// timer is 8X longer and it takes much longer for CV to come down to VPK. //
////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////
////		// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
////		// switching freqeuncy with FB pin //
////		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////		{
////			/*
////			// Read out contents of shadow register.  Can't overwrite shadow register. //
////			Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
////			Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
////
////			WordArray[0] = READ59_word[0];
////			WordArray[1] = READ59_word[1];
////			WordArray[2] = READ59_word[2];
////			WordArray[3] = READ59_word[3];
////			WordArray[4] = READ59_word[4];
////			WordArray[5] = READ59_word[5];
////			WordArray[6] = READ59_word[6];
////			WordArray[7] = READ59_word[7];
////			WordArray[8] = READ59_word[8];
////			WordArray[9] = READ59_word[9];
////			WordArray[10] = READ59_word[10];
////			WordArray[11] = READ59_word[11];
////			WordArray[12] = READ59_word[12];
////			WordArray[13] = READ59_word[13];
////			WordArray[14] = READ59_word[14];
////			WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
////			*/
////
////			WordArray[0] = g_EE_ShadReg48;
////			WordArray[1] = g_EE_ShadReg49;
////			WordArray[2] = g_EE_ShadReg50;
////			WordArray[3] = g_EE_ShadReg51;
////			WordArray[4] = g_EE_ShadReg52;
////			WordArray[5] = g_EE_ShadReg53;
////			WordArray[6] = g_EE_ShadReg54;
////			WordArray[7] = g_EE_ShadReg55;
////			WordArray[8] = g_EE_ShadReg56;
////			WordArray[9] = g_EE_ShadReg57;
////			WordArray[10] = g_EE_ShadReg58;
////			WordArray[11] = g_EE_ShadReg59;
////			WordArray[12] = g_EE_ShadReg60;
////			WordArray[13] = g_EE_ShadReg61;
////			WordArray[14] = g_EE_ShadReg62;
////			WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
////
////			// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
////			WordArray[15] = 0;
////			Write_Word(g_SREG3, NOhex, WordArray, BIN);
////		}
////	
////		// Set IS pin to 0V to start (THIS IS IMPORTANT because there are two different CP curves, one 
////		// curve when IS pin is ramping up and another when IS pin is ramping down, setting IS pin to 
////		// 0V ensures we are starting on the ramp up).//
////		IsPinVolt = 0;
////		IsPinVolt = IsPinVolt * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		if (IsPinVolt > 0.99999 || IsPinVolt < -0.99999)
////		{
////			IsPinVolt =0;
////			g_Error_Flag = -140;
////		}
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(100);
////
////		// Set CV to 21V and VPK to 5.3V. This is the worst case (i.e. most error) for measuring output power per design. //
////		// Set CV to 21V.
////		WordData = 4148; // 21V //
////		Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////		// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
////		// stairsteps up slowly, with CV only mode it steps up in a single step. //
////		Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
////		wait.delay_10_us(50);  // Wait for CV to come up //
////
////		// Disable CV only mode //
////		Write_Byte(g_CVO_mode, 0x00, NObin, HEX); // Disable CV only mode //
////		wait.delay_10_us(50);
////
////		// Set VPK to 5.3V //
////		WordData = 32949; // 5.3V //
////		Write_Word(g_VPK_reg, WordData, NObin, HEX);
////		wait.delay_10_us(50);
////
////		// Ramp Op Amp supply up to 24V to match previous test program conditions //
////		VBD_ramp_up(10, 24, 0.2);
////		wait.delay_10_us(100);
////
////		// Characterization only //
////		if (g_Char_Enable_P)
////		{
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// TOLP_OUT_ilow1
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			IsForce = 0.0095;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(1000);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .020 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(1000); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			wait.delay_10_us(2000);
////			VoutMeas = VO_dvi->measure_average(5);
////			TOLP_OUT_ilow1 = VoutMeas * IsForce;
////
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// TOLP_OUT_imid1
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			IsForce = 0.020;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(700);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .020 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(1000); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			VoutMeas = VO_dvi->measure_average(5);
////			TOLP_OUT_imid1 = VoutMeas * IsForce;
////		}	
////
////		// If characterization tests (TOLP_OUT_ilow1 and TOLP_OUT_imid1) disabled. //
////		if (!g_Char_Enable_P)
////		{
////			// Bring IS pin voltage up more slowly if TOLP_OUT_ilow1 and TOLP_OUT_imid1 tests are not done
////			// to prevent IS pin overshoot. //
////			IsForce = 0.0095;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(500);
////
////			IsForce = 0.020;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(500);
////		}
////
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// TOLP_OUT_ihigh1
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		IsForce = CC_100_pct*PctBelow; // Just below CC threshold- don't get too close to CC threshold or will hit maxCC and Vout will drop. //
////		IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		//wait.delay_10_us(700);
////
////		// Wait for Vout to settle. //
////		Counter = 0;
////		DeltaV = 99; // Initialize //
////		while ( DeltaV > .020 && Counter < 40 )
////		{
////			TempValue = VO_dvi->measure_average(5);
////			wait.delay_10_us(1000); // Needed //
////			TempValue2 = VO_dvi->measure_average(5);
////			DeltaV = TempValue - TempValue2;
////			if(DeltaV<0) // Remove negative //
////				DeltaV *= -1;
////			Counter++;
////		}
////		VoutMeas = VO_dvi->measure_average(5);
////		TOLP_OUT_ihigh1 = VoutMeas * IsForce;
////		//VPK_5_3_A = VoutMeas*(IsForce/CC_100_pct);
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// TOLP_OUT_ihigh2
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Set IS pin to 40mV to start (THIS IS IMPORTANT because there are two different CP curves, one 
////		// curve when IS pin is ramping up and another when IS pin is ramping down, setting IS pin to 
////		// 40mV ensures we are starting on the ramp down).//
////		// Bring current above CC before starting the ramp back down. //
////		IsForce = 0.040;
////		IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		wait.delay_10_us(700);
////		
////		IsForce = CC_100_pct*PctBelow; // Just below CC threshold- don't get too close to CC threshold or will hit maxCC and Vout will drop. //
////		IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////		IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////		//wait.delay_10_us(700);
////
////		// Wait for Vout to settle. //
////		Counter = 0;
////		DeltaV = 99; // Initialize //
////		while ( DeltaV > .020 && Counter < 40 )
////		{
////			TempValue = VO_dvi->measure_average(5);
////			wait.delay_10_us(1000); // Needed //
////			TempValue2 = VO_dvi->measure_average(5);
////			DeltaV = TempValue - TempValue2;
////			if(DeltaV<0) // Remove negative //
////				DeltaV *= -1;
////			Counter++;
////		}
////		VoutMeas = VO_dvi->measure_average(5);
////		TOLP_OUT_ihigh2 = VoutMeas * IsForce;
////		//VPK_5_3_B = VoutMeas*(IsForce/CC_100_pct);
////
////		// Characterization only //
////		if (g_Char_Enable_P)
////		{
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// TOLP_OUT_imid2
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			IsForce = 0.020;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(700);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .020 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(1000); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			VoutMeas = VO_dvi->measure_average(5);
////			TOLP_OUT_imid2 = VoutMeas * IsForce;
////
////	
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// TOLP_OUT_ilow2
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			IsForce = 0.0095;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(1000);
////
////			// Wait for Vout to settle. //
////			Counter = 0;
////			DeltaV = 99; // Initialize //
////			while ( DeltaV > .020 && Counter < 40 )
////			{
////				TempValue = VO_dvi->measure_average(5);
////				wait.delay_10_us(1000); // Needed //
////				TempValue2 = VO_dvi->measure_average(5);
////				DeltaV = TempValue - TempValue2;
////				if(DeltaV<0) // Remove negative //
////					DeltaV *= -1;
////				Counter++;
////			}
////			wait.delay_10_us(2000);
////			VoutMeas = VO_dvi->measure_average(5);
////			TOLP_OUT_ilow2 = VoutMeas * IsForce;
////
////	
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VPK_20_A
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set IS pin to 0V to start (THIS IS IMPORTANT because there are two different CP curves, one 
////			// curve when IS pin is ramping up and another when IS pin is ramping down, setting IS pin to 
////			// 0V ensures we are starting on the ramp up).//
////			IsForce = 0;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(1000);
////
////			// Set VPK to 20V //
////			WordData = 456;
////			Write_Word(g_VPK_reg, WordData, NObin, HEX);
////
////			// Setup test mode //
////			Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////			Write_Word(g_TM_SEL, 0x0024, NObin, HEX); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //
////			SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////			Write_Byte(g_Fast_VI_Command, 0x01, NObin, HEX);
////			if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////			{
////				/*
////				// Read out contents of shadow register.  Can't overwrite shadow register. //
////				Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
////				Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
////
////				WordArray[0] = READ59_word[0];
////				WordArray[1] = READ59_word[1];
////				WordArray[2] = READ59_word[2];
////				WordArray[3] = READ59_word[3];
////				WordArray[4] = READ59_word[4];
////				WordArray[5] = READ59_word[5];
////				WordArray[6] = READ59_word[6];
////				WordArray[7] = READ59_word[7];
////				WordArray[8] = READ59_word[8];
////				WordArray[9] = READ59_word[9];
////				WordArray[10] = READ59_word[10];
////				WordArray[11] = READ59_word[11];
////				WordArray[12] = READ59_word[12];
////				WordArray[13] = READ59_word[13];
////				WordArray[14] = READ59_word[14];
////				WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
////				*/
////				WordArray[0] = g_EE_ShadReg48;
////				WordArray[1] = g_EE_ShadReg49;
////				WordArray[2] = g_EE_ShadReg50;
////				WordArray[3] = g_EE_ShadReg51;
////				WordArray[4] = g_EE_ShadReg52;
////				WordArray[5] = g_EE_ShadReg53;
////				WordArray[6] = g_EE_ShadReg54;
////				WordArray[7] = g_EE_ShadReg55;
////				WordArray[8] = g_EE_ShadReg56;
////				WordArray[9] = g_EE_ShadReg57;
////				WordArray[10] = g_EE_ShadReg58;
////				WordArray[11] = g_EE_ShadReg59;
////				WordArray[12] = g_EE_ShadReg60;
////				WordArray[13] = g_EE_ShadReg61;
////				WordArray[14] = g_EE_ShadReg62;
////				WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
////
////				// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
////				WordArray[15] = 0;
////				Write_Word(g_SREG3, NOhex, WordArray, BIN);
////			}
////			Mux20_Open_relay(K53); // Disconnect Vout pin from Op Amp output. //
////			wait.delay_10_us(250);
////			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_50_RANGE); // DVI_9_0, prevent undershoot //
////			Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
////			wait.delay_10_us(250);
////			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////			FB_ovi->connect(2);
////			FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 //
////			FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, Float //
////			FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////			// Disconnect Op Amp positive input reference. //
////			ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //
////
////			// Bring up IS pin //
////			IsForce = CC_100_pct*PctBelow;  // Just below CC threshold- don't get too close to CC threshold or will hit maxCC and Vout will drop. //
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(250); // Wait for relays //
////
////			// CV reg to 24V to be sure CV is above 20 for VPK_20_A test //
////			WordData = 37600; // 24 //
////			Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////			// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
////			// stairsteps slowly, with CV only mode it steps up in a single step. //
////			Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
////			wait.delay_10_us(50);
////
////			// Disable CV only mode //
////			//Write_Byte(g_CVO_mode, 0x00, NObin, HEX); // Disable CV only mode //
////			//wait.delay_10_us(50);
////
////			// Set VPK to 20V //
////			//WordData = 363; // 23.5V //
////			//WordData = 456; // 20V //
////			//Write_Word(g_VPK_reg, WordData, NObin, HEX);
////			//wait.delay_10_us(13500);
////			//wait.delay_10_us(100);
////
////			// Disable CV only mode //
////			Write_Byte(g_CVO_mode, 0x00, NObin, HEX); // Disable CV only mode //
////			wait.delay_10_us(50);
////
////			// Binary search VPK [on Vout pin]. //
////			// Look for FB comparator output flip on SR pin. //
////			UpperLimit = (func.dlog->tests[A_VPK_20_A].f_max_limit_val[0])*1.1; // Get upper search limit //
////			LowerLimit = (func.dlog->tests[A_VPK_20_A].f_min_limit_val[0])*0.9; // Get lower search limit //
////			//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////			//{
////			//	UpperLimit = (func.dlog->tests[A_VPK_20_A].f_max_limit_val[0])*1.4; // Get upper search limit //
////			//	LowerLimit = (func.dlog->tests[A_VPK_20_A].f_min_limit_val[0])*0.6; // Get lower search limit //
////			//}
////			Vforce = (UpperLimit + LowerLimit) / 2;
////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////			{
////				Vforce = 0;
////				g_Error_Flag = -151;
////			}
////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////			wait.delay_10_us(100);
////			while ( (UpperLimit - LowerLimit) > .001)
////			{
////				Vforce = (UpperLimit + LowerLimit) / 2; 
////				if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////				{
////					Vforce = 0;
////					g_Error_Flag = -152;
////					break;
////				}
////				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////				wait.delay_10_us(100);
////				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
////				if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
////					LowerLimit = Vforce;
////				else // Above threshold.  CV comparator high. //
////					UpperLimit = Vforce;		
////			}
////			VPK_20_A = Vforce*(IsForce/CC_100_pct);
////
////
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// VPK_20_B
////			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////			// Set IS pin to 40mV to start (THIS IS IMPORTANT because there are two different CP curves, one 
////			// curve when IS pin is ramping up and another when IS pin is ramping down, setting IS pin to 
////			// 40mV ensures we are starting on the ramp down).//
////			// Bring current above CC before starting the ramp back down. //
////			IsForce = 0.040;
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			wait.delay_10_us(700);
////
////			// Bring down IS pin //
////			IsForce = CC_100_pct*PctBelow;  // Just below CC threshold- don't get too close to CC threshold or will hit maxCC and Vout will drop. //
////			IsPinVolt = IsForce * g_ISbuff_Gain32; // IS pin attached to 20X gain buffer //
////			IS_dvi2k->set_voltage(IS_ch, IsPinVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  IS pin attached to 20X gain buffer. //
////			//wait.delay_10_us(30000);
////			wait.delay_10_us(100);
////
////			// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
////			// stairsteps slowly, with CV only mode it steps up in a single step. //
////			Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
////			wait.delay_10_us(50);
////
////			// Disable CV only mode //
////			Write_Byte(g_CVO_mode, 0x00, NObin, HEX); // Disable CV only mode //
////			wait.delay_10_us(50);
////
////			// CV reg to 24V to be sure CV is above 20 for VPK_20_A test //
////			//WordData = 37600; // 24 //
////			//Write_Word(g_CV_reg, WordData, NObin, HEX);
////
////			// Enable CV only mode to speed up PDAC and NDAC (CV register) output.  Without CV only mode it 
////			// stairsteps slowly, with CV only mode it steps up in a single step. //
////			//Write_Byte(g_CVO_mode, 0x01, NObin, HEX); // Enable CV only mode //
////			//wait.delay_10_us(50);  // Wait for CV to come up //
////
////			// Disable CV only mode //
////			//Write_Byte(g_CVO_mode, 0x00, NObin, HEX); // Disable CV only mode //
////			//wait.delay_10_us(50);
////
////			// Set VPK to 23.5V //
////			//WordData = 363; // 23.5V //
////			//Write_Word(g_VPK_reg, WordData, NObin, HEX);
////			//wait.delay_10_us(13500); // Needed //
////
////
////			wait.delay_10_us(5000); // Extra delay OK, test is for characterization only. //
////
////
////			// Binary search VPK [on Vout pin]. //
////			// Look for FB comparator output flip on SR pin. //
////			UpperLimit = (func.dlog->tests[A_VPK_20_B].f_max_limit_val[0])*1.1; // Get upper search limit //
////			LowerLimit = (func.dlog->tests[A_VPK_20_B].f_min_limit_val[0])*0.9; // Get lower search limit //
////			//if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////			//{
////			//	UpperLimit = (func.dlog->tests[A_VPK_20_B].f_max_limit_val[0])*1.4; // Get upper search limit //
////			//	LowerLimit = (func.dlog->tests[A_VPK_20_B].f_min_limit_val[0])*0.6; // Get lower search limit //
////			//}
////			Vforce = (UpperLimit + LowerLimit) / 2;
////			if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////			{
////				Vforce = 0;
////				g_Error_Flag = -151;
////			}
////			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////			wait.delay_10_us(100);
////			while ( (UpperLimit - LowerLimit) > .001)
////			{
////				Vforce = (UpperLimit + LowerLimit) / 2; 
////				if (Vforce < -49.99 || Vforce > 49.99) // Prevent out of range. //
////				{
////					Vforce = 0;
////					g_Error_Flag = -152;
////					break;
////				}
////				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_50_RANGE); // DVI_9_0 //
////				wait.delay_10_us(100);
////				SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
////				if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
////					LowerLimit = Vforce;
////				else // Above threshold.  CV comparator high. //
////					UpperLimit = Vforce;		
////			}
////			VPK_20_B = Vforce*(IsForce/CC_100_pct);
////		}		
////
////		// Power Down //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////		FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
////		FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////		Open_relay(K18);
////		mux_14->open_relay(MUX_2_GND);
////		Open_relay(K24);
////		Mux20_Open_relay(K53); // Disconnect Vout pin from Op Amp output. //
////		wait.delay_10_us(250);
////		VO_dvi->set_voltage(VO_ch, 5, VOLT_50_RANGE); // DVI_9_0, prevent undershoot //
////		Mux20_Open_relay(K54); // Disconnect FB pin from Op Amp negative input. //
////		wait.delay_10_us(10);
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////		VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
////		wait.delay_10_us(20);
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		uVCCrampDown(0.5, 0, 0.1);
////		SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
////		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////		wait.delay_10_us(45); // prevent SR undershoot //
////		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////		wait.delay_10_us(5);
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		wait.delay_10_us(20);
////		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////		ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////		FB_ovi->connect(2);
////		FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
////		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////		ovi_3->set_voltage(OVI_CHANNEL_6, 0, RANGE_2_V); // OVI_3_6 //
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
////		// Disconnect Op Amp supply.  dvi used as OpAmp supply. //
////		VBD_ramp_down(24, 0, 0.2);
////		Mux20_Open_relay(K36);
////		wait.delay_10_us(300);
////
////		// Datalog //
////		//PiDatalog(func, A_VPK_5_3_A, VPK_5_3_A, 26, POWER_UNIT);
////		//PiDatalog(func, A_VPK_5_3_B, VPK_5_3_B, 26, POWER_UNIT);
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			PiDatalog(func, A_VPK_20_A, VPK_20_A, 26, POWER_UNIT);
////			PiDatalog(func, A_VPK_20_B, VPK_20_B, 26, POWER_UNIT);
////			//PiDatalog(func, A_VPK_23_5_A, VPK_23_5_A, 26, POWER_UNIT);
////			PiDatalog(func, A_TOLP_OUT_ilow1, TOLP_OUT_ilow1, 26, POWER_UNIT);
////			PiDatalog(func, A_TOLP_OUT_ilow2, TOLP_OUT_ilow2, 26, POWER_UNIT);
////			PiDatalog(func, A_TOLP_OUT_imid1, TOLP_OUT_imid1, 26, POWER_UNIT);
////			PiDatalog(func, A_TOLP_OUT_imid2, TOLP_OUT_imid2, 26, POWER_UNIT);
////		}
////		PiDatalog(func, A_TOLP_OUT_ihigh1, TOLP_OUT_ihigh1, 26, POWER_UNIT);
////		PiDatalog(func, A_TOLP_OUT_ihigh2, TOLP_OUT_ihigh2, 26, POWER_UNIT);
////
////		if (g_Char_Enable_P) // Characterization only //
////		{
////			PiDatalog(func, A_t_VI, t_VI, 26, POWER_MILLI);
////		}
////		
////		// Test Time End //
////		if (g_TstTime_Enble_P)
////		{
////			g_endtime = g_mytimer.GetElapsedTime();
////			VPK_TT = (g_endtime - g_begintime)*1e-6;
////			PiDatalog(func, A_VPK_TT, VPK_TT, 26, POWER_MILLI);
////		}
////	}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
