//==============================================================================
// SoftStart.cpp (User function)
// 
//    void SoftStart_user_init(test_function& func)
//    void SoftStart(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SoftStart.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SoftStart_user_init(test_function& func)
{
	SoftStart_params *ours;
    ours = (SoftStart_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SoftStart(test_function& func)
{
    // The two lines below must be the first two in the function.
    SoftStart_params *ours;
    ours = (SoftStart_params *)func.params;

	// Increment function number //
	gFuncNum++;
////
////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_fNum_SoftStart, gFuncNum, 20, POWER_UNIT);
////
////	// Skip Test if AbortTest set //
////	if (AbortTest)
////		return;
////
////	if (g_SoftStart == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	float ILIM_70pct_mA_P = 0; // ILIM_70pct_mA-P //
////	float ILIM_70pct_P = 0; // ILIM_70pct-P //
////	float tsoft_SSS = 0; // tSoft_ss-S //
////	float tHandshake_SSS = 0; // tHandShake_ss-S //
////	float Fosc_min_SSS = 0; // Fosc_min_ss-S //
////	float Fosc_max_SSS = 0; // Fosc_max_ss-S //
////	float fModulation_P = 0; // Fosc_Mod-S //
////	float gIdmin_Jitter_132kHz = 0; // ILIM ILIMLo_JitHi-S //
////	float gIdmax_Jitter_132kHz = 0; // ILIM ILIMhi_JitLo-S //
////	float ILIM_Reduce_w_Jitter_132kHz = 0; // ILIM ILIM_Jit132K-S //
////	float Fosc_Sss_P = 0; // Fosc_ss-P //
////	float ILIM_Jit18K_S = 0; // ILIM_Jit18K-S //
////	float ILIMLo_Jit18K_S = 0; // ILIM ILIMLo_Jit18K-S //
////	float ILIMhi_Jit18K_S = 0; // ILIMhi_Jit18K-S //
////	float Fosc_Mod_18K_S = 0; // ILIM Fosc_Mod_18K-S //	
////	float tChUp_RTM_P = 0; // tChUp_RTM-P //
////	float SoftStart_TT = 0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	float ChB_vrng =0.0;
////	int vrng_b =0.0;
////	int READ59_word[16] = {0};
////	int WordArray[16] = {0};
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	Pulse pulse;
////
////	//Gage_pretrig_samples=1024;
////	//Gage_init();
////
////	// Samsung bit trimmed
////	if(gTrim_SAM_P_Trimops)
////	{
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// ILIM - 70% - Samsung Soft Start
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// Samsung Soft Start - Tsoft
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
////		PV3_Check_Charge(RANGE_100_V);
////		pv3_4->charge_off();
////
////		SAMPLE_SIZE = GAGE_POST_1M;
////
////		vrng_b = 0;
////		ChB_vrng = 0;
////		INNO_Gage_ChanAB_setup(0.1);	// Only do it if SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)
////
////		// Negative cycle BPP pin //
////		VBPP_Negative_Cycle();
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
////		D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //	
////
////		// BPP //
////		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////		// V pin //
////		VPIN_ovi->disconnect(VPIN_ch); // Setup Vpin for DDD //
////
////		// Setup DDD //
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
////		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////		wait.delay_10_us(10);
////		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////		wait.delay_10_us(200);
////
////		// Powerup primary [most of the way].  Don't finish the primary powerup here.
////		Power_Up_Primary_BypassWL_TM5_SoftStart(ILIM_NORM);
////
////		// FW //
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4, VOLT_20_RANGE); // OVI_1_4
////
////		// Adjust inv synce reference at hot. //
//////		if (g_OPCODE==4300 || g_OPCODE==4500)
//////		{
//////			if (!strnicmp(Part_ID_LimitSet, "SC1750", 6) ||!strnicmp(Part_ID_LimitSet, "SC1738", 6))
//////			{
//////				InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.25, VOLT_20_RANGE); // OVI_1_4
//////			}
//////		}
////
////		// Do not have FW pin below ground during BPS powerup- causing I2C programming problem? Not well understood. //
////		ovi_1->set_voltage(OVI_CHANNEL_6, 0, VOLT_5_RANGE);	// inv_syn_circuit //
////
////		// SR //
////		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		//SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
////		Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////
////		// BPS //
////		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////		// IS //
////		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////		// Vout //
////		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
////		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////		// FB (COMP) //
////		FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
////		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
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
////		g_DDD_Low = 0.0; // Save current value //
////		g_DDD_High = 3.3; // Save current value //
////		wait.delay_10_us(g_DDDwait);
////		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////		wait.delay_10_us(g_DDDwait);
////
////		// SDA //
////		Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////		ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////		//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////		SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
////		Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////	//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////	Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////		// SCL //
////		//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////		SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////		// Set DDD for I2C. //
////		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////				
////		// Wait for relays //
////		wait.delay_10_us(200); 
////
////		// Powerup secondary //
////		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////		// I2C secondary, do not put into test mode- because soft start is disabled in test mode. //  
////		//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////		//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////
//////		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
////		
//////		Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
////	DSM_Write_Byte(g_FWPK_reg, 0x00); // Disable FW peak peak switch function. //
//////		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////	DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
////
////		// Hold SDA and SCL low before disconnecting DDD. //
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
////		wait.delay_10_us(20);
////		SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
////		SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////		SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////		SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////		wait.delay_10_us(30);
////		Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
////		wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
////		Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
////		Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
////
////		// Setup inv_syn_circuit low output //
////		//ovi_1->set_voltage(OVI_CHANNEL_6, -2.3, VOLT_5_RANGE);	// revB inv_syn_circuit //
////		ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);
////		wait.delay_10_us(200);
////
////		// Start capturing data //
////		Gage_Start_Capture();
////
////		// Finish primary powerup //
////		BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////		VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////		
////		// Finish capturing data //
////		Gage_Wait_For_Capture_Complete();
////		pv3_4->drive_off();	
////
////		// Powerdown //
////		D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////		Open_relay(KIM1); // Disconnect Vind to CT2+ to CT2-
////		Open_relay(K9); // Disconnect CT2- to Drain
////		Open_relay(K1); // Disconnect Iped to CT2+ to CT2-
////		Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1
////		pv3_4->set_current(0);						
////		pv3_4->set_voltage(0, RANGE_100_V);
////		pv3_4->drive_off();
////		pv3_4->open_switch(PV3_LOW_FORCE_2);
////		pv3_4->open_switch(PV3_LOW_SENSE_2);
////		pv3_4->open_switch(PV3_HIGH_FORCE_1);
////		pv3_4->open_switch(PV3_HIGH_SENSE_1);
////		SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////		Open_relay(K3); // Drain to RL pullup
////		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////		VBPP_ramp_down(3, 0.0, 0.05);
////		Open_relay(K12); 
////		VPIN_ovi->connect(VPIN_ch);
////		FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
////		Open_relay(K17); 
////		ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////		Disconnect_InvSyn_IM();
////		Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
////		Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
////		Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
////		ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////		SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
////		SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////		SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////		SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////		VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////		uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////		uVCCrampDown(1, 0, 0.1);
////		VBPS_ramp_down(3, 0, 100e-3);
////		VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////		wait.delay_10_us(20);
////		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////		Mux20_Open_relay(K50);
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
////		
////		// Process SoftStart data:  Find all parameters //
////		UpperLimit = (func.dlog->tests[A_Fosc_min_SSS].f_max_limit_val[0]); // Get upper limit //
////		LowerLimit = (func.dlog->tests[A_Fosc_min_SSS].f_min_limit_val[0]); // Get lower limit //
////		g_SaveAwav = 0;
////		//Gage_Find_Ilim_SSS(&ILIM_70pct_mA_P, &tsoft_SSS, &tHandshake_SSS, &Fosc_min_SSS, &Fosc_max_SSS, &gIdmin_Jitter_132kHz, &gIdmax_Jitter_132kHz, &fModulation_P, &Fosc_Sss_P);
////		Gage_Find_Ilim_SSS(&ILIM_70pct_mA_P, &tsoft_SSS, &tHandshake_SSS, &Fosc_min_SSS, &Fosc_max_SSS, &gIdmin_Jitter_132kHz, &gIdmax_Jitter_132kHz, &fModulation_P, &Fosc_Sss_P, UpperLimit, LowerLimit);
////		g_SaveAwav = 0;
////		ILIM_Reduce_w_Jitter_132kHz = (1 - gIdmin_Jitter_132kHz / gIdmax_Jitter_132kHz) * 100;
////		ILIM_70pct_P = (ILIM_70pct_mA_P / g_ILIM_S)*100.0;
////		g_tHandshake_SSS = int(tHandshake_SSS*1e6/10);
////		//g_SoftStartTime = tsoft_SSS; // Save for later //
////
////		// Back to previous //
////		//Gage_pretrig_samples=64;
////		//Gage_init();
////	}
////
////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// 18kHz jitter tests //
////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
////	PV3_Check_Charge(RANGE_100_V);
////	pv3_4->charge_off();
////
////	// Negative cycle BPP pin //
////	VBPP_Negative_Cycle();
////
////
////	// Open all relays //
//////	Initialize_Relays();
////
////	// Initialize Instruments //
//////	Initialize_Instruments();
////
////		// Drain //
////	Close_relay(K3);
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //	
////
////	// BPP //
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////	// V pin //
////	VPIN_ovi->disconnect(VPIN_ch); // Setup Vpin for DDD //
////
////	/*
////	// FW //
////	if(g_OPCODE==4300 || g_OPCODE==4500)
////	{
////		Connect_InvSyn_IM(High_Temp_Vd_Input);
////	}
////	else
////	{
////		Connect_InvSyn_IM(Low_Load_Vd_Input);
////	}
////	*/
////
////	// SR //
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	//SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////	// FW //
//////	if(g_OPCODE==4300 || g_OPCODE==4500)
//////	{
//////		Connect_InvSyn_IM(High_Temp_Vd_Input);
//////	}
//////	else
//////	{
//////		Connect_InvSyn_IM(Low_Load_Vd_Input);
//////	}
////
////Connect_InvSyn_IM(Low_Load_Vd_Input);	
////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4, VOLT_20_RANGE); // OVI_1_4
////
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////	// FB (COMP) //
////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////
////	// VBD //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
////	//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
////
////	// SCL //
////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////	//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////
////	// Set DDD for I2C. //
////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		
////	// Wait for relays //
////	wait.delay_10_us(200); 
////
////	// Powerup secondary //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////	// I2C secondary into test mode. //  
////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////
////	// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
////	// switching freqeuncy with FB pin //
////	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
////	{
////		// Read out contents of shadow register.  Can't overwrite shadow register. //
////		/*
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
////	}
////
////	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	
////	Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////	// Hold SDA and SCL low before disconnecting DDD. //
////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
////	wait.delay_10_us(20);
////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////	wait.delay_10_us(30);
////	Mux20_Open_relay(K37);
////	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
////	Mux20_Open_relay(K39);
////	wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
////	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
////	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
////
////	// Setup DDD //
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	//wait.delay_10_us(100);
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(10);
////	Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
////	wait.delay_10_us(200);
////
////	// Powerup primary in test mode 5- skip wait&listen //
////	Power_Up_Primary_BypassWL_TM5_18kHz(ILIM_NORM);
////
////	// Setup FB //
////	// DDD level //
////	g_DDD_Low = 0.8; // Save current value //
////	g_DDD_High = 1.5; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(5);
////	FB_ovi->set_voltage(FB_ch, 0.8, RANGE_2_V); // OVI_1_2 //
////	wait.delay_10_us(20);
////	Close_relay(K17); // Connect FB to DDD ch2 //
////	wait.delay_10_us(250);
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
////	// Stop switching //
////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
////	wait.delay_10_us(30);
////
////	// VBP_P drops when secondary has control //
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////	wait.delay_10_us(8);
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////	wait.delay_10_us(20);
////
////	// Enable RTM by switch >110kHz for >200usec. //
////	ddd_7->ddd_run_pattern(FB_125kHz_pulse_start,FB_125kHz_pulse_stop);	
////	wait.delay_10_us(250);
////
////	// 18kHz jitter tests //
////	// Start Capture
////	Gage_Start_Capture(  );
////
////	// Run 18kHz pattern
////	ddd_7->ddd_run_pattern(FB_18kHz_pulse_start,FB_18kHz_pulse_stop);	
////
////	// Finish capture
////	Gage_Wait_For_Capture_Complete();
////	pv3_4->drive_off();	
////
////	// Process data
////	g_SaveAwav = 0;
////	Gage_Find_Ilim_18kHz(&ILIM_Jit18K_S, &ILIMhi_Jit18K_S, &ILIMLo_Jit18K_S, &Fosc_Mod_18K_S);
////	g_SaveAwav = 0;
////
////	// Powerdown //
////	SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////	pv3_4->set_current(0);						
////	pv3_4->set_voltage(0, RANGE_100_V);
////	pv3_4->open_switch(PV3_LOW_FORCE_2);
////	pv3_4->open_switch(PV3_LOW_SENSE_2);
////	pv3_4->open_switch(PV3_HIGH_FORCE_1);
////	pv3_4->open_switch(PV3_HIGH_SENSE_1);
////	Disconnect_InvSyn_IM();
////	Open_relay(K3); // Drain to RL pullup
////	Open_relay(KIM1); // Disconnect Vind to CT2+ to CT2-
////	Open_relay(K9); // Disconnect CT2- to Drain
////	Open_relay(K1); // Disconnect Iped to CT2+ to CT2-
////	Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1
////	Mux20_Open_relay(K50);
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////	VBPP_ramp_down(4, 0, 0.2);
////	VPIN_ovi->connect(VPIN_ch); // Setup Vpin for DDD //
////	wait.delay_10_us(10);
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
////	Open_relay(K17); 
////	wait.delay_10_us(20);
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCCrampDown(0.5, 0, 0.1);
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	Open_relay(K17); 
////
////	// DDD level //
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 4.0; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////	
////	// Back to previous //
////	//Gage_pretrig_samples=64;
////	//Gage_init();
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// END:18kHz jitter tests //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// tChUp_RTM-P //
////	// Measures how accurate the 1us RTM charge up time is.  Goto observe mode address 3 (DchUp).  
////	// 1usec pulse should show up on Vpin when gate turns off. 
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////
////	// Open all relays //
////	Initialize_Relays();
////
////	// Initialize Instruments //
////	Initialize_Instruments();
////
////	// Setup Digitizer //
////	SAMPLE_SIZE = GAGE_POST_32K;
////	vrng_b = GAGE_PM_5_V;
////	ChB_vrng = 5.0;
////
////	// Channel B setup //
////	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 
////	gage_input_control_xp(GAGE_CHAN_B, // channel
////						  GAGE_INPUT_ENABLE, // enable / disable
////						  GAGE_DC, // coupling
////						  vrng_b|GAGE_1_MOHM_INPUT); // range, impedance
////	gage_trigger_control_xp(GAGE_CHAN_B, // trigger source
////							GAGE_DC, // coupling for ext trig
////							vrng_b, // range for CHA trigger
////							GAGE_POSITIVE, // slope
////							3.25, // 1.0V trigger level 
////	   						SAMPLE_SIZE); // 20ns * GAGE_WAVEFORM_BUFFER_SIZE
////
////	// Set up Buffer Clamp
////	BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA);
////	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE); // OVI_1_3 Account for one diode drop
////
////	// Remove latchoff problem. //
////	VBPP_Negative_Cycle();
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
////
////	// Drain //
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////	Close_relay(K3); // Drain to dvi through pullup resistor. //
////
////	// Setup Vpin for digital clocking //
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(10);
////	Close_relay(K12); // Connect Vpin to DDD. //
////
////	// DDD level //
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 5.0; // Save current value //
////	wait.delay_10_us(250); // Wait for relays //
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////	
////	// Primary Power up with test mode 1 and Observe mode in same power up //
////	VBPP_ramp_up(0.0, 5.0, 0.1);	// vstart, vstop, vstep	
////	wait.delay_10_us(20);
////
////	VPIN_ovi->disconnect(1);
////	wait.delay_10_us(10);
////
////	// Vpin pulse 2 times for Program mode. Then wiggle BPP pin to get into Observe mode. //
////	ddd_7->ddd_run_pattern(Vpin_2clocks_start, Vpin_2clocks_stop);	
////
////	// Set BPP //
////	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
////	wait.delay_10_us(5);
////	VBPP_ramp_down(gVBPP_PV_final, 5.0, 50e-3);	// vstart, vstop, vstep
////	wait.delay_10_us(20);
////	VBPP_ramp_down(5.0, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep
////
////	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
////	int ILIM_Select=0;
////	ILIM_Select = ILIM_NORM;
////	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
////	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //
////
////	// Set BPP below VBP- //
////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
////	wait.delay_10_us(50);
////
////	// Lower Vpin voltage because max RDSon buffer input is clamped to 4.4V. //
////	// DDD level //
////	g_DDD_High = 4.0; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////
////	// Connect Vpin to 5kohm pullup resistor. //
////	Open_relay(K12);
////	Close_relay(K16);
////	Close_relay(KC6C);
////	Open_relay(KC5C);
////
////	// Connect Vpin to RDSon buffer circuit. //
////	Close_relay(K35);
////	delay(2);
////
////	// Vpin //
////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
////	wait.delay_10_us(20);
////
////	// Set BPP above VBP+ // 
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////	wait.delay_10_us(30);
////	// Part should now be in Observe mode. //	
////
////	// Clock Vpin three times to look at DChUp observe signal. //
////	ddd_7->ddd_run_pattern(Vpin_3NegClocks_start, Vpin_3NegClocks_stop);
////	wait.delay_10_us(350);
////	Gage_Start_Capture(  );
////	CsDo(hSystem, ACTION_FORCE); // Force capture. //
////	Gage_Wait_For_Capture_Complete();
////
////	// Search result //
////	g_SaveAwav = 0;
////	DChUp_Gage_Find(&tChUp_RTM_P);
////	g_SaveAwav = 0;
////
////	// Power down //
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////	VBPP_ramp_down(3, 0.0, 0.4);
////	//BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);	
////	BC_ovi->set_voltage(BC_ch, 0,VOLT_5_RANGE); // OVI_1_3
////	Open_relay(K3);
////	VPIN_ovi->connect(1);
////	Open_relay(K12);
////	Open_relay(K35);
////	Open_relay(K16);
////	Open_relay(KC6C);
////	Open_relay(KC5C);
////	wait.delay_10_us(200);
////
////	// Datalog //
////
////	// ILIM_70pct_mA-P //
////	PiDatalog(func, A_ILIM_70pct_mA_P, ILIM_70pct_mA_P, 20, POWER_MILLI);
////
////	// ILIM_70pct-P //
////	PiDatalog(func, A_ILIM_70pct_P, ILIM_70pct_P, 20, POWER_UNIT);
////
////	// tSoft_ss-S //
////	PiDatalog(func, A_tsoft_SSS, tsoft_SSS, 20, POWER_MILLI);
////
////	// tHandShake_ss-S //
////	PiDatalog(func, A_tHandshake_SSS, tHandshake_SSS, 20, POWER_MICRO);
////
////	// Fosc_min_ss-S //
////	PiDatalog(func, A_Fosc_min_SSS, Fosc_min_SSS, 20, POWER_KILO);
////
////	// Fosc_max_ss-S //
////	PiDatalog(func, A_Fosc_max_SSS, Fosc_max_SSS, 20, POWER_KILO);
////	
////	// Fosc_Mod-S //
////	PiDatalog(func, A_Fosc_Mod_S, fModulation_P, 20, POWER_KILO);
////
////	// ILIM ILIMhi_JitLo-S //
////	PiDatalog(func, A_IlimHigh_JitterLow_S, gIdmax_Jitter_132kHz, 20, POWER_MILLI);
////
////	// ILIM ILIMLo_JitHi-S // 
////	PiDatalog(func, A_IlimLow_JitterHigh_S, gIdmin_Jitter_132kHz, 20, POWER_MILLI);
////
////	// ILIM ILIM_Jit132K-S //
////	PiDatalog(func, A_ILIM_Jit132K_S, ILIM_Reduce_w_Jitter_132kHz, 20, POWER_UNIT);
////	 
////	// Fosc_ss-P //
////	PiDatalog(func, A_Fosc_Sss_P, Fosc_Sss_P, 20, POWER_KILO);
////
////	// ILIM_Jit18K-S //
////	PiDatalog(func, A_ILIM_Jit18K_S, ILIM_Jit18K_S, 20, POWER_UNIT);
////
////	// ILIMhi_Jit18K-S //
////	PiDatalog(func, A_IlimHigh_JitterLow_18kHz_S, ILIMhi_Jit18K_S, 20, POWER_MILLI);
////
////	// ILIM ILIMLo_Jit18K-S //
////	PiDatalog(func, A_IlimLow_JitterHigh_18kHz_S, ILIMLo_Jit18K_S, 20, POWER_MILLI);
////
////	// ILIM Fosc_Mod_18K-S //
////	PiDatalog(func, A_Fosc_Mod_18kHz_S, Fosc_Mod_18K_S, 20, POWER_KILO);
////
////	// tChUp_RTM-P //
////	PiDatalog(func, A_tChUp_RTM_P, tChUp_RTM_P, 9, POWER_MICRO);
////	     
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		SoftStart_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_SoftStart_TT, SoftStart_TT, 14, POWER_MILLI);
////	}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
