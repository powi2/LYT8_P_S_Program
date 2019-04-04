//==============================================================================
// Isvth3X_AR_ISSC.cpp (User function)
// 
//    void Isvth3X_AR_ISSC_user_init(test_function& func)
//    void Isvth3X_AR_ISSC(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Isvth3X_AR_ISSC.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Isvth3X_AR_ISSC_user_init(test_function& func)
{
	Isvth3X_AR_ISSC_params *ours;
    ours = (Isvth3X_AR_ISSC_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Isvth3X_AR_ISSC(test_function& func)
{
    // The two lines below must be the first two in the function.
    Isvth3X_AR_ISSC_params *ours;
    ours = (Isvth3X_AR_ISSC_params *)func.params;

	// Increment function number //
	gFuncNum++;

////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_Func_Num_Isvth3X, gFuncNum, 25, POWER_UNIT);
////
////	// Skip Test if AbortTest set //
////	if (AbortTest)
////		return;
////
////	if (g_Fn_Isvth3X_AR_ISSC == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////	
////	// Test Names //
////	float ISvth3X_S = 0;
////	float ISvth3X_act_S = 0;
////	float Isvth3X_ISSC_TT = 0;
////	float vFB_SC_OFF_S=0.0;
////	float AR_tISvth_S_TM=0.0;
////	float ISsc_vth_TM=0.0;
////	//float CV_S =0.0;
////	//float CV_S_Err =0.0;
////	float CV_exp_S=0.0;
////	float CV_act_S=0.0;
////	//float CV_TM_S=0.0;
////	float ARSTth_S=0.0;
////	//float Vclamp_20pct_S_QC3=0.0;
////	//float Vclamp_20pct_Ratio_S_QC3=0.0;
////	//float ISSC_LatchOff_S=0.0;
////	float ISvth_S=0.0;
////	float ISvth_Hot_S=0.0;
////	//float Vout_th_9V_TM =0.0;
////	float CC_exp_S=0.0;	
////	//float vCB_NM_9V_S=0.0;
////	//float vCB_NM_12V_S=0.0;
////	//float vCB_NM_20V_S=0.0;
////	//float CB_exp_S=0.0;
////	float CS_result_S=0.0;
////	float CB_0pct_S=0.0;
////	float CB_9pct_S=0.0;
////	float VoutKP_th_Start=0.0; 
////	float Vknee_actual_S=0.0;
////	//float ISSC_ISvth_NM_S=0;
////	//float ISSC_ISvth_TM_S=0;
////	float CV_FB_exp_S=0;
////	float ARth_FB_TM_S=0;
////	float ARth_FB_S=0;
////	float ARth_FB_pct_S=0;
////	float ARth_VO_S=0;
////	float VVO_2pct_BLD=0;
////	float VVO_2pct_BLDrat=0;
////	float IVO_2pct_BLD=0;
////	float IVO_BLD_Off = 0;
////	float VVO_BLD=0;
////	float VVO_BLD_ratio=0;
////	float IVO_BLD=0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	int READ59_word[16] = {0};
////	int WordArray[16] = {0};
////	int TempArray[30] = {0};
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	float Vforce = 0;
////	float SRpinVolt = 0;
////	float imeas = 0;
////	float imeas2 = 0;
////	float tmeas = 0;
////	float vstep =0;
////	float PV3_Charge =0.0;
////	float CC_factor =0.0;
////	float iPV3_frc =0.0; 
////	float vPV3_frc=0.0;
////	float iDVI2K_frc=0.0;
////	int lcnt =0;
////	int lcnt2 =0;
////	int Rep_cnt=0;
////	float MeasCount = 0;
////	int Flag = 0;
////	int i = 0;
////	float Initial_time = 0;
////	float Final_time = 0;
////	float Period = 0;
////	float WordData = 0;
////	int READ10_word[16] = {0};
////	int READ1_word[16] = {0};
////	int READ56_word[16] = {0};
////	int READ57_word[16] = {0};
////	Pulse pulse; // External trigger pulse from dvi for debug
////
////	// Open all relays //
////	//Initialize_Relays();
////
////	// Initialize Instruments //
////	//Initialize_Instruments();
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
////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
////
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////	// IS //
////	mux_14->close_relay(MUX_2_GND);
////	Close_relay(K24); // Connect IS pin to 20X buffer. //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
////
////	// FB (COMP) //
////	FB_ovi->disconnect(2);
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
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 3.3; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////
////	// SDA //
////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
////
////	// SCL //
////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
////	
////	// Set DDD for I2C. //
////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
////		
////	// Wait for relays //
////	wait.delay_10_us(200); 
////		
////	// Powerup //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
////
////	// I2C into test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
////
//////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //
////DSM_Write_Word(g_TM_ANA, 0x0134); // TM_EN_SR_driver //
////	
////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
//////	Write_Byte(g_CCSCL, 0x00, NObin, HEX); // Disable CCSCL //
////DSM_Write_Byte(g_CCSCL, 0x00); // Disable CCSCL //
////	
////	// SR //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
////
////	// Write the I2C command to connect the HC_ signal to SR pin. //
//////	Write_Word(g_TM_SEL, 0x0020, NObin, HEX); // Write the I2C command to connect the HC_ signal to SR pin. //
////DSM_Write_Word(g_TM_SEL, 0x0020); // Write the I2C command to connect the HC_ signal to SR pin. //
////
////	// ISvth3X_S //
////	// Binary search on IS pin looking at SR pin flip state //
////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
////	UpperLimit = (func.dlog->tests[A_ISvth3X_S].f_max_limit_val[0])*1.1; // Get upper search limit //
////	LowerLimit = (func.dlog->tests[A_ISvth3X_S].f_min_limit_val[0])*0.9; // Get lower search limit //
////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////	{
////		UpperLimit = (func.dlog->tests[A_ISvth3X_S].f_max_limit_val[0])*1.5; // Get upper search limit //
////		LowerLimit = (func.dlog->tests[A_ISvth3X_S].f_min_limit_val[0])*0.5; // Get lower search limit //
////	}
////	//UpperLimit *= 20; // IS pin is connected to 20X buffer. //
////	//LowerLimit *= 20; // IS pin is connected to 20X buffer. //
////	UpperLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
////	LowerLimit *= g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -4.99 || Vforce > 4.99) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -115;
////	}
////	IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_5_RANGE); // DVI_13_0, dvi2k //
////	wait.delay_10_us(100);
////	while ( (UpperLimit - LowerLimit) > .001)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -4.99 || Vforce > 4.99) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -116;
////			break;
////		}
////		IS_dvi2k->set_voltage(IS_ch, Vforce, VOLT_5_RANGE); // DVI_13_0, dvi2k //
////		wait.delay_10_us(100);
////		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k // 
////		if (SRpinVolt < 1.5) // Below threshold //
////			LowerLimit = Vforce;
////		else // Above threshold //
////			UpperLimit = Vforce;		
////	}
////	ISvth3X_S = Vforce;
////	//ISvth3X_S = ISvth3X_S/20.0; // IS pin is connected to 20X buffer. //
////	ISvth3X_S = ISvth3X_S/g_ISbuff_Gain32; // IS pin is connected to 20X buffer. //
////	ISvth3X_act_S = ((ISvth3X_S - g_ISvth3X_pt_S) / g_ISvth3X_pt_S)*100; // In percent //
////
////	// Powerdown //
////	//Open_relay(K2);
////	Open_relay(K18);
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	mux_14->open_relay(MUX_2_GND);
////	Open_relay(K24); // Connect IS pin to 20X buffer. //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE); // DVI_13_0, dvi2k //
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
////	FB_ovi->connect(2);
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	Mux20_Open_relay(K64);
////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////	Mux20_Open_relay(K37);
////	Mux20_Open_relay(K38);
////	Mux20_Open_relay(K40);
////	Mux20_Open_relay(K39);
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////
////	// Datalog //
////	PiDatalog(func, A_ISvth3X_S, ISvth3X_S, 26, POWER_MILLI);
////	if(g_Sim_Enable_P)
////	{
////		PiDatalog(func, A_ISvth3X_act_S, ISvth3X_act_S, 26, POWER_UNIT);
////	}
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//// 	//							 vFB_SC_OFF-S (aka VFB(OFF))					   
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	//  vFB_SC_OFF-S ( aka VFB(OFF) )
////	//	After handshake, VFB(OFF) will be initially disabled and after 
////	//  soft start ramp and hold time are finished (around 12 msec), then VFB(OFF) 
////	//	becomes enabled; then perform binary search. //  	
////					  
////	// Negative cycle BPP pin //
////	VBPP_Negative_Cycle();
////
////	// Open all relays //
////	//Initialize_Relays();
////
////	// Initialize Instruments //
////	//Initialize_Instruments();
////
////	// Drain //
////	Close_relay(K3);
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //
////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
////	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////	tmu_6->stop_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////	tmu_6->start_holdoff(0,FALSE);
////	tmu_6->stop_holdoff(0,FALSE);
////
////	// BPP //
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////	// V pin //
////	VPIN_ovi->disconnect(VPIN_ch); // Setup Vpin for DDD //
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
////	// Powerup primary [most of the way].  Don't finish the primary powerup here.
////	Power_Up_Primary_BypassWL_TM5_Partial(ILIM_NORM);
////
////	// FW //
////	Connect_InvSyn_IM(Low_Load_Vd_Input);
////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4
////
////	// Do not have FW pin below ground during BPS powerup- causing I2C programming problem? Not well understood. //
////	ovi_1->set_voltage(OVI_CHANNEL_6, 0, VOLT_5_RANGE);	// inv_syn_circuit //
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
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////	// FB (COMP) //
////	FB_ovi->set_voltage(FB_ch, 1, RANGE_1_V); // OVI_1_2 //
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
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 3.3; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
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
////	// I2C into test mode. //  
////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////	// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
////	// switching freqeuncy with FB pin //
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
////	}
////
////	Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
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
////	// Setup inv_syn_circuit low output //
////	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.3, VOLT_5_RANGE);	// revB inv_syn_circuit //
////	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);
////	wait.delay_10_us(200);
////
////	// Bring up drain to observe switching //
////	D_dvi->set_voltage(D_ch, 5, VOLT_50_RANGE); // DVI_11_0 //.
////
////	// Finish primary powerup //
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////	
////	// Wait for BPP to come up and part starts switching //
////	tmeas = 0;
////	lcnt = 0;
////	while (tmeas < 1e-6 && lcnt<2000) // While not switching //
////	{
////		tmu_6->arm();
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read();	
////		lcnt++;
////	}
////
////	// VBP_P drops when secondary has control //
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////	wait.delay_10_us(8);
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////	wait.delay_10_us(20);
////
////	// Wait for part to stop switching.  After handshake, VFB(OFF) will be initially disabled and after 
////	// soft start ramp and hold time are finished (around 12 msec), then VFB(OFF) 
////	// becomes enabled. // 
////	wait.delay_10_us(100);
////	tmeas = 99;
////	lcnt = 0;
////	while (tmeas > 1e-6 && lcnt<2000) // While switching //
////	{
////		tmu_6->arm();
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read();	
////		lcnt++;
////	}
////
////	//	FB_ovi->set_voltage(FB_ch, 0, RANGE_1_V); // OVI_1_2 //
////	//	wait.delay_10_us(20);
////
////	// Binary search for VFB(OFF) //
////	UpperLimit = (func.dlog->tests[A_vFB_SC_OFF_S].f_max_limit_val[0])*1.1; // Get upper search limit //
////	LowerLimit = 0; // Get lower search limit //
////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
////	{
////		UpperLimit = (func.dlog->tests[A_vFB_SC_OFF_S].f_max_limit_val[0])*1.5; // Get upper search limit //
////	}
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -0.9999 || Vforce > 0.9999) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -141;
////	}
////	while ( (UpperLimit - LowerLimit) > .001)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -0.9999 || Vforce > 0.9999) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -141;
////			break;
////		}
////		FB_ovi->set_voltage(FB_ch, Vforce, RANGE_1_V); // OVI_1_2 //
////		wait.delay_10_us(5);
////		tmu_6->arm();
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read();	 
////		if (tmeas < 1e-6) // Not switching //
////			LowerLimit = Vforce;
////		else // Switching //
////			UpperLimit = Vforce;		
////	}
////	vFB_SC_OFF_S = Vforce;
////
////	// Stop switching //
////	FB_ovi->set_voltage(FB_ch, 0, RANGE_1_V); // OVI_1_2 //
////
////	// Datalog
////	PiDatalog(func, A_vFB_SC_OFF_S, vFB_SC_OFF_S, 17, POWER_UNIT);
////
////	// Powerdown //
////	SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
////	Disconnect_InvSyn_IM();
////	Open_relay(K3); // Drain to RL pullup
////	Mux20_Open_relay(K50);
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////	VBPP_ramp_down(4, 0, 0.5);
////	VPIN_ovi->connect(VPIN_ch); // Setup Vpin for DDD //
////	wait.delay_10_us(10);
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	wait.delay_10_us(20);
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCCrampDown(0.5, 0, 0.1);
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	VBD_dvi->set_voltage(VBD_ch, 5, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// VVO_2pct_BLD
////	// Test measures the 2% weak bleed voltage on Vout //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Negative cycle BPP pin //
////	VBPP_Negative_Cycle();
////
////	// Open all relays //
////	Initialize_Relays();
////
////	// Initialize Instruments //
////	Initialize_Instruments();
////
////	// Drain //
////	Close_relay(K3);
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //
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
////	Mux20_Close_relay(K43); // Connect dvi9_ch0 to SR instead of Vout //
////	dvi_9->set_voltage(0, 0, VOLT_10_RANGE); // DVI_9_0 //
////	dvi_9->set_current(0, 0.1e-9, RANGE_30_UA); // DVI_9_0 //
////	//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	//SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	Mux20_Close_relay(K44); // Connect DVI_13_1, dvi2k to Vout instead of SR //
////	dvi_13->set_voltage(DVI_CHANNEL_1, 4, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	dvi_13->set_current(DVI_CHANNEL_1, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	//VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
////	//VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////
////	// FB (COMP) //
////	FB_ovi->disconnect(2);
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
////	Mux20_Close_relay(K64);  // SDA pullup to 3.3V through 1.5kohm resistor. //
////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////	Mux20_Close_relay(K37);  // Disconnect ovi from SDA. //
////	Mux20_Close_relay(K38);  // Connect SDA and SCL to DDD. //
////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. //
////
////	// SCL //
////	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
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
////	// I2C secondary, do not put into test mode- because soft start is disabled in test mode. //  
////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////
////	// Disable OTP because OTP kicks in around 125C and causes strong bleeder to be disabled //
////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); //
////
////	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////	
////	//Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
////
////	// When DOPL bits are trimmed the weak and strong bleed are disabled. Need to disable the DOPL bits 
////	// so weak and strong bleeder can be tester in reliability. Shadow register bits 15 and 22. //
////	if(g_EE_ShadReg22) // DOPL. bit[22]: trim_dopl //
////	{
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// bit[15]: trim_dopl_en_cp // 
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		/*
////		Write_Word(g_RDADDR, g_READ56, NObin, HEX);// SREG0.  Shadow register. //
////		Read_Word(g_RDADDR, READ56_word);// SREG0.  Shadow register. //
////
////		WordArray[0] = READ56_word[0];
////		WordArray[1] = READ56_word[1];
////		WordArray[2] = READ56_word[2];
////		WordArray[3] = READ56_word[3];
////		WordArray[4] = READ56_word[4];
////		WordArray[5] = READ56_word[5];
////		WordArray[6] = READ56_word[6];
////		WordArray[7] = READ56_word[7];
////		WordArray[8] = READ56_word[8];
////		WordArray[9] = READ56_word[9];
////		WordArray[10] = READ56_word[10];
////		WordArray[11] = READ56_word[11];
////		WordArray[12] = READ56_word[12];
////		WordArray[13] = READ56_word[13];
////		WordArray[14] = READ56_word[14];
////		WordArray[15] = READ56_word[15]; // bit[15]: trim_dopl_en_cp //
////		*/
////		WordArray[0] = g_EE_ShadReg0;
////		WordArray[1] = g_EE_ShadReg1;
////		WordArray[2] = g_EE_ShadReg2;
////		WordArray[3] = g_EE_ShadReg3;
////		WordArray[4] = g_EE_ShadReg4;
////		WordArray[5] = g_EE_ShadReg5;
////		WordArray[6] = g_EE_ShadReg6;
////		WordArray[7] = g_EE_ShadReg7;
////		WordArray[8] = g_EE_ShadReg8;
////		WordArray[9] = g_EE_ShadReg9;
////		WordArray[10] = g_EE_ShadReg10;
////		WordArray[11] = g_EE_ShadReg11;
////		WordArray[12] = g_EE_ShadReg12;
////		WordArray[13] = g_EE_ShadReg13;
////		WordArray[14] = g_EE_ShadReg14;
////		WordArray[15] = g_EE_ShadReg15; // bit[15]: trim_dopl_en_cp //
////
////		// bit[15]: trim_dopl_en_cp, set to zero to remove DOPL trim. //
////		WordArray[15] = 0;
////		Write_Word(g_SREG0, NOhex, WordArray, BIN);
////
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		// bit[22]: trim_dopl //
////		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////		/*
////		Write_Word(g_RDADDR, g_READ57, NObin, HEX);// SREG1.  Shadow register. //
////		Read_Word(g_RDADDR, READ57_word);// SREG1.  Shadow register. //
////
////		WordArray[0] = READ57_word[0];
////		WordArray[1] = READ57_word[1];
////		WordArray[2] = READ57_word[2];
////		WordArray[3] = READ57_word[3];
////		WordArray[4] = READ57_word[4];
////		WordArray[5] = READ57_word[5];
////		WordArray[6] = READ57_word[6]; // bit[22]: trim_dopl // 
////		WordArray[7] = READ57_word[7];
////		WordArray[8] = READ57_word[8];
////		WordArray[9] = READ57_word[9];
////		WordArray[10] = READ57_word[10];
////		WordArray[11] = READ57_word[11];
////		WordArray[12] = READ57_word[12];
////		WordArray[13] = READ57_word[13];
////		WordArray[14] = READ57_word[14];
////		WordArray[15] = READ57_word[15];
////		*/
////		WordArray[0] = g_EE_ShadReg16;
////		WordArray[1] = g_EE_ShadReg17;
////		WordArray[2] = g_EE_ShadReg18;
////		WordArray[3] = g_EE_ShadReg19;
////		WordArray[4] = g_EE_ShadReg20;
////		WordArray[5] = g_EE_ShadReg21;
////		WordArray[6] = g_EE_ShadReg22; // bit[22]: trim_dopl // 
////		WordArray[7] = g_EE_ShadReg23;
////		WordArray[8] = g_EE_ShadReg24;
////		WordArray[9] = g_EE_ShadReg25;
////		WordArray[10] = g_EE_ShadReg26;
////		WordArray[11] = g_EE_ShadReg27;
////		WordArray[12] = g_EE_ShadReg28;
////		WordArray[13] = g_EE_ShadReg29;
////		WordArray[14] = g_EE_ShadReg30;
////		WordArray[15] = g_EE_ShadReg31;
////
////		// bit[22]: trim_dopl, set to zero to remove DOPL trim. //
////		WordArray[6] = 0;
////		Write_Word(g_SREG1, NOhex, WordArray, BIN);
////		wait.delay_10_us(200); 
////	}
////
////
//////dvi_13->set_voltage(DVI_CHANNEL_1, 25, VOLT_50_RANGE); // DVI_13_1, dvi2k //
////
////	// Binary Search Vout. Looking for 2.5mA weak bleed current on Vout. //
////	//VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);
////	dvi_13->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_CURRENT); // DVI_13_1, dvi2k //
////	UpperLimit = g_CV_Final_S*1.10; // Get upper search limit //
////	LowerLimit = g_CV_Final_S; // Get lower search limit //
////	Vforce = (UpperLimit + LowerLimit) / 2;
////	if (Vforce < -10 || Vforce > 10) // Prevent out of range. //
////	{
////		Vforce = 0;
////		g_Error_Flag = -142;
////	}
////	//VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE);
////	dvi_13->set_voltage(DVI_CHANNEL_1, Vforce, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	wait.delay_10_us(100);
////	while ( (UpperLimit - LowerLimit) > .005)
////	{
////		Vforce = (UpperLimit + LowerLimit) / 2; 
////		if (Vforce < -10 || Vforce > 10) // Prevent out of range. //
////		{
////			Vforce = 0;
////			g_Error_Flag = -142;
////			break;
////		}
////		//VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE);
////		dvi_13->set_voltage(DVI_CHANNEL_1, Vforce, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////		wait.delay_10_us(50);
////		MeasCount = 0;
////		Flag = 0;
////		for (i=0;i<30;i++) // Take thirty measurements to improve repeatability. //
////		{
////			//imeas = VO_dvi->measure();
////			imeas = dvi_13->measure(); // DVI_13_1, dvi2k //
////			wait.delay_10_us(1);
////			if (imeas > 0.001) // 1mA //
////				MeasCount++;
////		}
////		if (MeasCount > 29)
////			Flag = 1;
////		if (Flag == 0) // Below threshold //
////			LowerLimit = Vforce;
////		else // Above threshold //
////			UpperLimit = Vforce;		
////	}
////	VVO_2pct_BLD = Vforce;
////	VVO_2pct_BLDrat = ( (VVO_2pct_BLD / g_CV_Final_S) - 1) * 100; // Datalog in percentage above CV. //
////	gVclamp_2pct_S = VVO_2pct_BLD; // Pass to global variable for Vclamp_10pct threshold search
////
////	// Measure 2% weak bleed current //
////	// Meaure Vout current without bleeder on first, then measure with weak bleed on and take the differnce. //
////	//VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
////	dvi_13->set_current(DVI_CHANNEL_1, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	wait.delay_10_us(10);
////	//VO_dvi->set_voltage(VO_ch, Vforce-0.1, VOLT_10_RANGE); // Turn off weak bleed. //
////	dvi_13->set_voltage(DVI_CHANNEL_1, Vforce-0.1, VOLT_10_RANGE); // DVI_13_1, dvi2k // // Turn off weak bleed. //
////	wait.delay_10_us(50);
////	//imeas = VO_dvi->measure_average(5); // Measure vout current //
////	imeas = dvi_13->measure_average(5); // Measure vout current //
////	//VO_dvi->set_voltage(VO_ch, Vforce+0.1, VOLT_10_RANGE); // Turn on weak bleed //
////	dvi_13->set_voltage(DVI_CHANNEL_1, Vforce+0.1, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	wait.delay_10_us(50);
////	//imeas2 = VO_dvi->measure_average(5); // Measure vout current //
////	imeas2 = dvi_13->measure_average(5); // Measure vout current //
////	IVO_2pct_BLD = imeas2 - imeas; // Calculate 2% weak bleed current. //
////	IVO_BLD_Off = imeas;
////	//VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	dvi_13->set_current(DVI_CHANNEL_1, 2, RANGE_2_A); // DVI_13_1, dvi2k //
////
////	// Datalog //
////	PiDatalog(func, A_VVO_2pct_BLD, VVO_2pct_BLD, 17, POWER_UNIT);
////	PiDatalog(func, A_VVO_2pct_BLDrat, VVO_2pct_BLDrat, 17, POWER_UNIT);	
////	PiDatalog(func, A_IVO_2pct_BLD, IVO_2pct_BLD, 17, POWER_MILLI);
////	PiDatalog(func, A_IVO_BLD_Off, IVO_BLD_Off, 17, POWER_MICRO);
////
////
////	//int READ4_word[16] = {0};
////	//int READ10_word[16] = {0};
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Stong bleeder current
////	// Test measures the strong bleed current on Vout //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Measure strong bleed current //
////	// Meaure Vout current with bleeder off first, then measure with strong bleed on and take the differnce. //
////	//VO_dvi->set_voltage(VO_ch, g_CV_Final_S, VOLT_10_RANGE);
////	dvi_13->set_voltage(DVI_CHANNEL_1, g_CV_Final_S, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	wait.delay_10_us(50);
////
////	//Write_Word(g_RDADDR, g_READ4, NObin, HEX);
////	//Read_Word(g_RDADDR, READ4_word);
////
////	//Write_Word(g_RDADDR, g_READ10, NObin, HEX);
////	//Read_Word(g_RDADDR, READ10_word);
////
////	//imeas = VO_dvi->measure_average(5); // Measure vout current //
////	imeas = dvi_13->measure_average(5); // Measure vout current //
////	Write_Byte(g_MINLD, 0x01, NObin, HEX); // Enable the strong bleeder with I2C. //
////	wait.delay_10_us(1);
////
////	//Write_Word(g_RDADDR, g_READ4, NObin, HEX);
////	//Read_Word(g_RDADDR, READ4_word);
////
////	//Write_Word(g_RDADDR, g_READ10, NObin, HEX);
////	//Read_Word(g_RDADDR, READ10_word);
////
////	//imeas2 = VO_dvi->measure(); // Measure vout current //
////	imeas2 = dvi_13->measure(); // Measure vout current //
////	//VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	dvi_13->set_voltage(DVI_CHANNEL_1, 0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	Write_Byte(g_MINLD, 0x00, NObin, HEX); // Disable the strong bleeder with I2C. //
////	IVO_BLD = imeas2 - imeas; // Calculate strong bleed current. //
////
////	// Datalog //
////	//PiDatalog(func, A_VVO_BLD, VVO_BLD, 17, POWER_UNIT); // Not needed //
////	//PiDatalog(func, A_VVO_BLD_ratio, VVO_BLD_ratio, 17, POWER_UNIT); // Not needed //
////	PiDatalog(func, A_IVO_BLD, IVO_BLD, 17, POWER_MILLI);
////
////	// Powerdown //
////	Mux20_Open_relay(K43);
////	Mux20_Open_relay(K44);
////	//Open_relay(K18);
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	Open_relay(K3); // Drain to RL pullup
////	Mux20_Open_relay(K50);
////	//Mux20_Open_relay(K64);
////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////	//Mux20_Open_relay(K37);
////	//Mux20_Open_relay(K38);
////	//Mux20_Open_relay(K40);
////	//Mux20_Open_relay(K39); 
////	wait.delay_10_us(10);
////	//VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	dvi_9->set_current(0, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	dvi_13->set_voltage(DVI_CHANNEL_1, 0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	wait.delay_10_us(20);
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCCrampDown(0.5, 0, 0.1);
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	VBD_dvi->set_voltage(VBD_ch, 5, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
////	//FB_ovi->connect(2);
////	//FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
////
////	// DDD level //
////	//g_DDD_Low = 0.0; // Save current value //
////	//g_DDD_High = 4.0; // Save current value //
////	//wait.delay_10_us(100);
////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(200); // Wait for relays //
////
////
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		Isvth3X_ISSC_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_Isvth3X_ISSC_TT, Isvth3X_ISSC_TT, 16, POWER_MILLI);
////	}	
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
