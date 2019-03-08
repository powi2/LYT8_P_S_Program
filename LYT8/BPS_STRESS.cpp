//==============================================================================
// BPS_STRESS.cpp (User function)
// 
//    void BPS_STRESS_user_init(test_function& func)
//    void BPS_STRESS(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BPS_STRESS.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BPS_STRESS_user_init(test_function& func)
{
	BPS_STRESS_params *ours;
    ours = (BPS_STRESS_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BPS_STRESS(test_function& func)
{
    // The two lines below must be the first two in the function.
    BPS_STRESS_params *ours;
    ours = (BPS_STRESS_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_BPS_Stress, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	if (g_Trim_Enable_P == 0)
		return;

	if (g_Fn_BPS_STRESS == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float BPS_Stress_Volt = 0;
	float IIL_FW_Post = -999;
	float IIL_FW_Delta = -999;
	float IIL_VO_Post = -999;
	float IIL_VO_Delta = -999;
	float IIL_IS_Post = -999;
	float IIL_IS_Delta = -999;
	float IIL_VBD_Post = -999;
	float IIL_VBD_Delta = -999;
	float IIH_VBD_Post = -999;
	float IIH_VBD_Delta = -999;
	float IIL_SDA_Post = -999;
	float IIL_SDA_Delta = -999;
	float IIH_SDA_Post = -999;
	float IIH_SDA_Delta = -999;
	float IIL_SCL_Post = -999;
	float IIL_SCL_Delta = -999;
	float IIH_SCL_Post = -999;
	float IIH_SCL_Delta = -999;
	float IIL_COMP_Post = -999;
	float IIL_COMP_Delta = -999;
	float IIH_COMP_Post = -999;
	float IIH_COMP_Delta = -999;
	//float BPS_IS1_Pre = -999;
	float BPS_IS1_Post = -999;
	float BPS_IS1_Delta = -999;
	//float BPS_IS1hf_Pre = -999;
	//float BPS_IS1hf_Post = -999;
	//float BPS_IS1hf_Delta = -999;
	//float BPS_IS2_Pre = -999;
	float BPS_IS2_Post = -999;
	float BPS_IS2_Delta = -999;
	
	// Declare Variables //
	int i = 0;
	float UpperLimit = 0;
	float LowerLimit = 0;
	float CurrentClamp = 0;
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //	
	float WordData = 0;
	int READ59_word[16] = {0};
	int WordArray[16] = {0};
	float Force_IS_volt = 0;
	float Stress_Time = 0;
	float vset = 0;	
	Pulse pulse;



	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPS_IS1_Pre
	// BPS_IS2_Pre
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	// Negative cycle BPP pin //
	VBPP_Negative_Cycle();

	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	Close_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->disconnect(VPIN_ch);

	// Setup DDD //
	//ddd_7->ddd_set_clock_period(Dclk_period);
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
	wait.delay_10_us(200);

	// Powerup primary [most of the way].  Don't finish the primary powerup here.
	Power_Up_Primary_BypassWL_TM5_SoftStart(ILIM_NORM);

	// Reconnect ovi to Vpin //
	VPIN_ovi->connect(VPIN_ch);
	Open_relay(K12); // Disonnect DDD7_1 from Vpin(UV) pin

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);
	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4, VOLT_20_RANGE); // OVI_1_4
	// Adjust inv synce reference at hot. //
	//if (g_OPCODE==4300 || g_OPCODE==4500)
	//{
	//	if (!strnicmp(Part_ID_LimitSet, "SC1750", 6) ||!strnicmp(Part_ID_LimitSet, "SC1738", 6))
	//	{
	//		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.25, VOLT_20_RANGE); // OVI_1_4
	//	}
	//}

	// Do not have FW pin below ground during BPS powerup- causing I2C programming problem? Not well understood. //
	ovi_1->set_voltage(OVI_CHANNEL_6, 0, VOLT_5_RANGE);	// inv_syn_circuit //

	// SR //
	//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
	//Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
	
	// Connect 5nF cap //
	// Want the SR pin enabled and switching to get the worst case BPS pin 
	// current.  With 5nF cap connected, the SR pin will be enabled. //
	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
	Close_relay(K5); // Connect 5nF Cap to SR //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->disconnect(2);
	//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
	//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C secondary into test mode- because soft start is disabled in test mode. //  
	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup in case EEPROM has not yet been written. //
	LoadShadowRegister();
	wait.delay_10_us(100);

	//Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //

	Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Measure BPS supply current at no load with VBEN (aka VBUS) disabled. With VBUS 
	// disabled, internal system clock is only running ~300kHz, instead of ~3MHz. //
	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
	wait.delay_10_us(50);
	g_BPS_IS1_Pre = BPS_dvi->measure_average(25);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);

	// Hold SDA and SCL low before disconnecting DDD. //
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
	wait.delay_10_us(20);
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	wait.delay_10_us(30);
	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
	wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //

	// Setup inv_syn_circuit low output //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.3, VOLT_5_RANGE);	// revB inv_syn_circuit //
	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);	// revB inv_syn_circuit //
	wait.delay_10_us(200);

	// Finish primary powerup //	
	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);

	// Bring Vout above CV to abort soft start and go full frequency //
	VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(30);
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	//FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
	//wait.delay_10_us(20);
	//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(105);
	g_BPS_IS2_Pre = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.

	// Powerdown //
	pv3_4->drive_off();
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Open_relay(KIM1); // Disconnect Vind to CT2+ to CT2-
	Open_relay(K9); // Disconnect CT2- to Drain
	Open_relay(K1); // Disconnect Iped to CT2+ to CT2-
	Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1
	pv3_4->set_current(0);						
	pv3_4->set_voltage(0, RANGE_100_V);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_1);
	pv3_4->open_switch(PV3_HIGH_SENSE_1);
	Open_relay(K3); // Drain to RL pullup
	VBPP_ramp_down(3, 0.0, 0.05);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	FB_ovi->connect(2);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
	Disconnect_InvSyn_IM();
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	VBPS_ramp_down(3, 0, .05);
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(2, 0, 0.05);
	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 300e-3, RANGE_300_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	Mux20_Open_relay(K59); // SR pin DVI_13_1, dvi2k //
	Open_relay(K5); // Disconnect 5nF Cap from SR //
	wait.delay_10_us(200); // Wait for relays //



	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPP_IS2_Pre
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Open all relays //
	//Initialize_Relays();

	// Initialize Instruments //
	//Initialize_Instruments();

	// Drain //
	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->stop_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //	

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->connect(VPIN_ch);
	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	//Connect_InvSyn_IM(Low_Load_Vd_Input);

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);

	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.15, VOLT_5_RANGE);

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// FB (COMP) //
	if (g_ShadowRegister[63] == 1 || g_EEpt_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
		FB_ovi->disconnect(2);
	}
	else
	{
		FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
	}

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
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C secondary into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// The shadow register should only be loaded if this is a virgin part and EEPROM has not yet been written. //
	if (g_Trim_Enable_P == 0)
	{
		// Do not load shadow register because this is already a trimmed part and EEPROM has already been written. //
	}
	else
	{
		// Load the shadow register //
		LoadShadowRegister();
		wait.delay_10_us(100);
	}

	// Powerup primary in test mode 1. //
	VBPP_Power_Up_w_Test_Mode(gTM1_p,ILIM_NORM);

	// Handshake will happen right after 'wait & listen' is done. //

	// Wait for 'wait & listen' to finish. // 
	wait.delay_10_us(350);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// Bring FB pin or Vout voltage up to stop switching.  fOVL fault will occur if secondary 
	// switches above fOVL frequency for tAR- so, need to reset the tAR timer here 
	// to give enougn time to measure frequency. //
	if (g_ShadowRegister[63] == 1 || g_EEpt_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
		VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(50);

		// Drop Vout to start switching. //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	}
	else
	{
		FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2	
		wait.delay_10_us(50);

		// Drop FB to start switching. //
		FB_ovi->set_voltage(FB_ch, 1.0, RANGE_2_V); // OVI_1_2	
	}
	wait.delay_10_us(25);

	// Measure frequency //
	//	tmu_6->start_holdoff(5,TRUE);
	//	tmu_6->stop_holdoff(5,TRUE);
	//	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init+250e-3, VOLT_10_RANGE);	// DVI_9_1
	//	wait.delay_10_us(10);
	//	tmu_6->arm();						// Device doing auto-restart
	//	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	//	tmeas = tmu_6->read(150e-6);	 
	//	tmeas/=5;
	//	if (tmeas != 0)
	//		Fosc_WeakBPS = 1/tmeas;
	//	else
	//		Fosc_WeakBPS = 0.0;	


	// Make sure VBPP is below shunt otherwise current reading will be wrong. //
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init-0.100, RANGE_10_V); // Keep below shunt voltage //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_S_Init_S+0.100, RANGE_10_V); // Test condition per datasheet //
	//VBPP_ramp_down(gVBPP_P_final, g_VBPP_P_S_Init_S+0.100, 0.01);
	BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_3_MA);
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(120);
	g_BPP_IS2_Pre = BPP_ovi->measure_average(5);

	//	tmu_6->start_holdoff(0,FALSE);
	//	tmu_6->stop_holdoff(0,FALSE);

	// Go above secondary OVP, device should stop switching if it is secondary control
	if (g_ShadowRegister[63] == 1 || g_EEpt_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
		VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
	}
	else
	{
		FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V);	// OVI_1_2	
	}
	wait.delay_10_us(10);
	//	tmu_6->arm(); 
	wait.delay_10_us(10);
	//	toff = tmu_6->read(); 


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPP_IS1_Pre
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Make sure VBPP is below shunt otherwise current reading will be wrong //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_S_Init_S+0.100, RANGE_10_V); // Test condition per datasheet //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(175);
	g_BPP_IS1_Pre = BPP_ovi->measure_average(5);

	// Powerdown //
	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain
	SR_dvi2k->set_voltage(SR_ch, 0.5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	wait.delay_10_us(30); // prevent undershoot //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(5); // prevent undershoot //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	wait.delay_10_us(5); // prevent undershoot //
	Open_relay(K3); // Drain to RL pullup
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39); 
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.2);
	wait.delay_10_us(10);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(1, 0, 0.1);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	wait.delay_10_us(2);
	VBPS_ramp_down(3, 0, 150e-3);
	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
	FB_ovi->connect(2);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iLeak_V_Pre
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 						50V Device on Vpin						 
	//  Procedure:
	//  1) Set D = 40V
	//  2) Set Vpin = 0V.
	//  3) Ramp BPP from 0V to 5.5V
	//  4) Then raise Vpin to 50V and measure leakage current.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //	
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// DVI11_Ch1 used for Vpin //
	dvi_11->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 300e-3, RANGE_300_MA);

	// Disconnect ovi from Vpin //
	ovi_1->disconnect(1);

	// Connect DVI11_Ch1 to Vpin //
	// Need dvi to bring Vpin to 50V //
	mux_14->open_relay(MUX_BANK_8_1);
	mux_14->open_relay(MUX_BANK_3_4);
	mux_14->open_relay(MUX_2_GND);
	Close_relay(K1_DSM_TB);	
	Close_relay(K3_DSM_TB);
	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	dvi_11->close_relay(BUS_SENSE1);
	dvi_11->close_relay(BUS_FORCE1);
	wait.delay_10_us(300);
	
	// Set BPP 100mV to prevent BPP undershoot when drain comes up. //
	BPP_ovi->set_voltage(BPP_ch, 0.1, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	wait.delay_10_us(20);

	// Set D = 40V / 100mA
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0 //
	wait.delay_10_us(100);

	// Ramp VBPP from 0.1V to 5.5V (DVI_11_1)
	// Bpp set 5.5V for 100us
	VBPP_ramp_up(0.1, 5.5, 0.1); // vstart, vstop, vstep	//
	wait.delay_10_us(50);

	// Bring up Vpin voltage //
	// DVI11_Ch1 used for Vpin //
	vset = 50;
	dvi_11->set_voltage(DVI_CHANNEL_1, vset, VOLT_50_RANGE);
	wait.delay_10_us(5);
	dvi_11->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_CURRENT);
	wait.delay_10_us(500); // Wait for voltage to come up. //
	dvi_11->set_current(DVI_CHANNEL_1, 300e-6, RANGE_300_UA); // Change range for more accuracy //
	wait.delay_10_us(500); // Wait for voltage to come up. //
	g_iLeak_V_Pre = dvi_11->measure_average(25);

	// Powerdown //
	dvi_11->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 300e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	wait.delay_10_us(100);
	VBPP_ramp_down(5.5, 0, 0.1);
	wait.delay_10_us(50);
	mux_14->open_relay(MUX_BANK_2_3);
	mux_14->open_relay(MUX_3_BUS3);
	mux_14->open_relay(MUX_1_1);
	mux_14->open_relay(MUX_1_3);
	dvi_11->open_relay(BUS_SENSE1);
	dvi_11->open_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_BANK_3_4);
	ovi_1->connect(1);
		


	// Apply Stress //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Secondary Stress Conditions:
	// Use I2C to program Vout to be 24V before raising Vout to 29V otherwise device may be damaged.
	// VBPS=8V (30mA clamp)
	// VFW=44V
	// Vout=29V
	// VFB=0-8V, 100kHz (Using DDD clocks)
	// VIS=0-200mV, 8.7kHz (Using DVI, 50us Low, 50us High)
	// SR=0V
	// VBD = float
	// uVCC = 8V
	// SDA = 0V
	// SCL = 0V
	//
	// Primary Stress Conditions:
	// VPin = 0V 1mA
    // VBPP = 8V 50mA. If we use OVI we could use 30mA clamp here.
    // D = 50V 10mA
	//
	// Hold above stress conditions for 100msec.
	// Be sure Vout is brought up first before uVCC and then uVCC down first before Vout down.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //2
	Initialize_Instruments();

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA); // OVI_1_1 //
	//wait.delay_10_us(10);

	// Drain //
	Close_relay(K2);
	//wait.delay_10_us(250);
	D_dvi->set_current(D_ch, 10e-3,RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	//wait.delay_10_us(40);

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 1, VOLT_50_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 300e-3, RANGE_300_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 2, RANGE_2_A); // DVI_13_1, dvi2k //
	//Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
	VBPS_ramp_up(0, gVBPS_M_Init - 200e-3, 50e-3);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	//IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	//mux_14->close_relay(MUX_2_GND);
	//Close_relay(K24); // Connect IS pin to 20X buffer. //
	//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE); // DVI_13_0, dvi2k //
	//IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_50_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// COMP //
	Close_relay(K17); // Connect FB pin to DDD //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 1e-3, RANGE_30_MA); // OVI_3_2 //

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
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup in case EEPROM has not yet been written. //
	LoadShadowRegister();
	wait.delay_10_us(100);

	// Set CV with I2C //
	// MUST BE SET TO 24V BEFORE RAISING Vout to 30V OR DEVICE WILL BE DAMAGED!!! //
	WordData = 37600; // 24V //
	Write_Word(g_CV_reg, WordData, NObin, HEX); // Write CV register //

	// If the COMP(FB) was disconnected with trim, then reconnect. //
	if (g_ShadowRegister[63] == 1) // bit[63]: trim_no_fb_pin //
	{
		// Read out contents of shadow register.  Can't overwrite shadow register. //
		Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
		Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //

		WordArray[0] = READ59_word[0];
		WordArray[1] = READ59_word[1];
		WordArray[2] = READ59_word[2];
		WordArray[3] = READ59_word[3];
		WordArray[4] = READ59_word[4];
		WordArray[5] = READ59_word[5];
		WordArray[6] = READ59_word[6];
		WordArray[7] = READ59_word[7];
		WordArray[8] = READ59_word[8];
		WordArray[9] = READ59_word[9];
		WordArray[10] = READ59_word[10];
		WordArray[11] = READ59_word[11];
		WordArray[12] = READ59_word[12];
		WordArray[13] = READ59_word[13];
		WordArray[14] = READ59_word[14];
		WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //

		// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
		WordArray[15] = 0;
		Write_Word(g_SREG3, NOhex, WordArray, BIN);
	}

	// Hold SDA and SCL low before disconnecting DDD. //
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
	wait.delay_10_us(20);
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	wait.delay_10_us(30);
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
	Mux20_Open_relay(K39);
	wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //

	// Clamp current 30mA //
	// Bring up BPS to 8V //
	BPS_Stress_Volt = 8.0;
	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
	//BPS_dvi->set_voltage(BPS_ch, BPS_Stress_Volt, VOLT_10_RANGE); // DVI_9_1 //
	VBPS_ramp_up(gVBPS_final, BPS_Stress_Volt, 50e-3);

	// FW = 44V, Vout = 29V //
	VO_dvi->set_voltage(VO_ch, 29, VOLT_50_RANGE); // DVI_9_0 //
	FW_dvi->set_voltage(FW_ch, 44, VOLT_50_RANGE); // DVI_11_1 //
	wait.delay_10_us(30);

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 5, RANGE_10_V); // OVI_3_2, prevent overshoot //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_53_2 //
	uVCCrampUp(5, 7.5, 0.2); // OVI_3_2, prevent overshoot //
	wait.delay_10_us(10);
	uVCCrampUp(7.5, 8.0, 0.2);

	// FB pin clocing 0-8V at 100kHz //
	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 8.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);
	wait.delay_10_us(20);
	ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop); // Run a looping pattern. //
	ddd_7->ddd_run_pattern(); // Need to do a stop pattern to stop ddd looping //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA); // OVI_1_1 //

	// Drain //
	D_dvi->set_current(D_ch, 10e-3,RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, 50, VOLT_50_RANGE); // DVI_11_0 //
	wait.delay_10_us(40);

	// BPP //
	g_BPP_Stress_Volt = 8.0;
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_up(0.0, g_BPP_Stress_Volt, 0.3);

	// IS pin. 0-200mV, 8.7kHz (Using DVI, 50us Low, 50us High) //
	//Force_IS_volt = g_ISbuff_Gain32 * 0.200; // IS pin is connected to 20X buffer. //
	Force_IS_volt = 0.200;
	g_begintime = g_mytimer.GetElapsedTime();
	Stress_Time = 0;
	while (Stress_Time < 100e-3)
	{
		//IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_10_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_voltage(IS_ch, Force_IS_volt*0.8, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(1);
		for(i=0;i<3;i++) // Loop to add more delay.  Normal wait command does not has small enough resolution. //
		{
			IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		}
		wait.delay_10_us(3);
		//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_voltage(IS_ch, 10e-3, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		wait.delay_10_us(1);
		for(i=0;i<2;i++) // Loop to add more delay.  Normal wait command does not has small enough resolution. //
		{
			IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		}
		wait.delay_10_us(3);
		g_endtime = g_mytimer.GetElapsedTime();
		Stress_Time = (g_endtime - g_begintime)*1e-6;
	}

	// Powerdown //
	ddd_7->ddd_stop_pattern();
	VBPP_ramp_down(g_BPP_Stress_Volt, gVBPP_P_final, 0.3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //
	wait.delay_10_us(20);
	VBPP_ramp_down(gVBPP_P_final, 0, 0.3);
	Open_relay(K2);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
	wait.delay_10_us(2);
	Open_relay(K17);
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //;
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
	wait.delay_10_us(80);
	//VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	VBPS_ramp_down(3, 0, .05);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	Open_relay(K18);
	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 300e-3, RANGE_300_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iLeak_V_Post
	// iLeak_V_Delta
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 						50V Device on Vpin						 
	//  Procedure:
	//  1) Set D = 40V
	//  2) Set Vpin = 0V.
	//  3) Ramp BPP from 0V to 5.5V
	//  4) Then raise Vpin to 50V and measure leakage current.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //	
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// DVI11_Ch1 used for Vpin //
	dvi_11->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 300e-3, RANGE_300_MA);

	// Disconnect ovi from Vpin //
	ovi_1->disconnect(1);

	// Connect DVI11_Ch1 to Vpin //
	// Need dvi to bring Vpin to 50V //
	mux_14->open_relay(MUX_BANK_8_1);
	mux_14->open_relay(MUX_BANK_3_4);
	mux_14->open_relay(MUX_2_GND);
	Close_relay(K1_DSM_TB);	
	Close_relay(K3_DSM_TB);
	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	dvi_11->close_relay(BUS_SENSE1);
	dvi_11->close_relay(BUS_FORCE1);
	wait.delay_10_us(300);
	
	// Set BPP 100mV to prevent BPP undershoot when drain comes up. //
	BPP_ovi->set_voltage(BPP_ch, 0.1, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	wait.delay_10_us(20);

	// Set D = 40V / 100mA
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0 //
	wait.delay_10_us(100);

	// Ramp VBPP from 0.1V to 5.5V (DVI_11_1)
	// Bpp set 5.5V for 100us
	VBPP_ramp_up(0.1, 5.5, 0.1); // vstart, vstop, vstep	//
	wait.delay_10_us(50);

	// Bring up Vpin voltage //
	// DVI11_Ch1 used for Vpin //
	vset = 50;
	dvi_11->set_voltage(DVI_CHANNEL_1, vset, VOLT_50_RANGE);
	wait.delay_10_us(5);
	dvi_11->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_CURRENT);
	wait.delay_10_us(500); // Wait for voltage to come up. //
	dvi_11->set_current(DVI_CHANNEL_1, 300e-6, RANGE_300_UA); // Change range for more accuracy //
	wait.delay_10_us(500); // Wait for voltage to come up. //
	g_iLeak_V_Post  = dvi_11->measure_average(25);
	g_iLeak_V_Delta = g_iLeak_V_Post - g_iLeak_V_Pre;

	// Powerdown //
	dvi_11->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 300e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	wait.delay_10_us(100);
	VBPP_ramp_down(5.5, 0, 0.1);
	wait.delay_10_us(50);
	mux_14->open_relay(MUX_BANK_2_3);
	mux_14->open_relay(MUX_3_BUS3);
	mux_14->open_relay(MUX_1_1);
	mux_14->open_relay(MUX_1_3);
	dvi_11->open_relay(BUS_SENSE1);
	dvi_11->open_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_BANK_3_4);
	ovi_1->connect(1);
	wait.delay_10_us(200);



	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Post stress leakage.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Open all relays //
	//Initialize_Relays();

	// Connect Relays //
	Close_relay(K2); //Connects Drain to DVI_11_0
	Close_relay(K18); //Connects FW to DVI_11_1

	// Setup Instruments //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V); // OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 300.0e-6, RANGE_300_UA);	
	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_5_RANGE); // DVI_9_0
	VO_dvi->set_current(VO_ch, 300e-6, RANGE_300_UA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); // DVI_9_1
	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE); // DVI_21_0
	IS_dvi2k->set_current(IS_ch, 200.0e-6, RANGE_200_UA);
	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); // DVI_11_1
	FW_dvi->set_current(FW_ch, 20.0e-6, RANGE_30_UA);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	SR_dvi2k->set_current(SR_ch, 200.0e-6, RANGE_200_UA);
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2
	FB_ovi->set_current(FB_ch, 30.0e-6, RANGE_30_UA);
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V);
	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
	SCL_ovi->set_voltage(SCL_ch, 0, RANGE_5_V);	
	SCL_ovi->set_current(SCL_ch, 29e-6, RANGE_30_UA);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_50_RANGE);	
	VBD_dvi->set_current(VBD_ch, 1e-3, RANGE_3_MA);	

	//Drain Low Leakage test only (High leakage is already in BV_Drain function)
	//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
	//D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 
	//D_dvi->set_current(D_ch, 300.0e-6, RANGE_300_UA); // Use 3mA to bring it to GND faster then smaller Range to 
	wait.delay_10_us(150);	

	//ILL_D = D_dvi->measure_average(15);

	// Normal Power Up //
	//D_dvi->set_voltage(D_ch, 5.5, VOLT_10_RANGE); 
	//wait.delay_10_us(50);
	//If BPP is set to 5.5V, Vpin at 20V will fail (It has to go through the BPP power cycle)
	//VBPP_ramp_up(0, 5.5, 0.2); // Prevent overshoot //
	//wait.delay_10_us(50);
	//BPP_ovi->set_voltage(BPP_ch, 4.5, VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
	//wait.delay_10_us(100);
	//BPP_ovi->set_voltage(BPP_ch, 5.1, VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)


	// Vpin leakage //
	//VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	//VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V); 
	//wait.delay_10_us(10);
	//ILL_UV = VPIN_ovi->measure_average(5);		

	//Primary pins set to 0V
	//BPP_ovi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 
	//VBPP_ramp_down(5.1, 0, 0.2); // Prevent undershoot //
	//D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 

	BPS_dvi->set_current(BPS_ch, 10.0e-3, RANGE_30_MA);

	// Prevent overshoot //
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	BPS_dvi->set_voltage(BPS_ch, 2, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 3.5, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 4, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 4.25, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 4.375, VOLT_5_RANGE);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 4.5, VOLT_5_RANGE);
	wait.delay_10_us(100);


	//FW leakage (Make sure it's less than vBPS else it could provide charge to BPS easily)
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
	FW_dvi->set_current(FW_ch, 30.0e-6, RANGE_30_UA);
	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE);
	wait.delay_10_us(205);
	IIL_FW_Post  = FW_dvi->measure_average(5);
	IIL_FW_Delta = IIL_FW_Post - g_ILL_FW;

	// FB(COMP) leakage
	CurrentClamp = 29.991e-6;
	FB_ovi->set_current(FB_ch, CurrentClamp, RANGE_30_UA);
	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); 
	wait.delay_10_us(105);
	IIL_COMP_Post = FB_ovi->measure_average(5);
	IIL_COMP_Delta = IIL_COMP_Post - g_ILL_FB;

	// Make sure test limits are not wider than current clamp. //
	UpperLimit = (func.dlog->tests[A_IIL_COMP_Post].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_IIL_COMP_Post].f_min_limit_val[0]); // Get lower test limit //
	if (UpperLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -217;
			IIL_COMP_Post = -999;
		}
	}
	if (UpperLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = -217;
			IIL_COMP_Post = -999;
		}
	}
	if (LowerLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -217;
			IIL_COMP_Post = -999;
		}
	}
	if (LowerLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = -217;
			IIL_COMP_Post = -999;
		}
	}

	FB_ovi->set_current(FB_ch, 300.0e-6, RANGE_300_UA);//FB goes to resistor divider
	wait.delay_10_us(50);
	FB_ovi->set_voltage(FB_ch, 5.5, RANGE_10_V); 
	wait.delay_10_us(100);
	IIH_COMP_Post = FB_ovi->measure_average(5); 
	IIH_COMP_Delta = IIH_COMP_Post - g_ILH_FB;
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); 

	// Vout Leakage //
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(205);
	IIL_VO_Post = VO_dvi->measure_average(5);
	IIL_VO_Delta = IIL_VO_Post - g_ILL_VO;

	// IS Leakage //
	IS_dvi2k->set_current(IS_ch, 200.0e-6, RANGE_200_UA);
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);	// DVI_21_0
	wait.delay_10_us(205);
	IIL_IS_Post = IS_dvi2k->measure_average(5);
	IIL_IS_Delta = IIL_IS_Post - g_ILL_IS;

	
	//============================================Inno VI pins SDA/SCL/VB pin=====================================================//

	// When DOPL bits trimmed, the VBD pin goes high when BPS is powered up, 
	// causing leakage failure.  Need to reduce BPS to prevent VBD from going high. //
	//if(g_ShadowRegister[22]) // DOPL //
	//{
	//	VBPS_ramp_down(4.5, 3, 0.1);
	//	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_5_RANGE);
	//}

	// VB/D //
	Mux20_Open_relay(K36);//Make sure VB/D is connected to DVI17 Ch.0
	VO_dvi->set_voltage(VO_ch, 5.0, VOLT_5_RANGE); // DVI_9_0
	VO_dvi->set_current(VO_ch, 29.0e-3, RANGE_30_MA);//~needs 19mA
	VBD_dvi->set_voltage(VBD_ch, 30.0, VOLT_50_RANGE);	
	VBD_dvi->set_current(VBD_ch, 1e-3, RANGE_3_MA);	
	VBD_dvi->set_meas_mode(VBD_ch,DVI_MEASURE_CURRENT);
	wait.delay_10_us(100);
	IIH_VBD_Post = VBD_dvi->measure_average(5);
	IIH_VBD_Delta = IIH_VBD_Post - g_ILH_VBD;

	VBD_dvi->set_voltage(VBD_ch, 15.0, VOLT_50_RANGE);
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA);//Change ranges away from abs. max to avoid glitch
	
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(120);
	IIL_VBD_Post = VBD_dvi->measure_average(5);
	IIL_VBD_Delta = IIL_VBD_Post - g_ILL_VBD;

	// Return to previous //
	// When DOPL bits trimmed, the VBD pin goes high when BPS is powered up, 
	// causing leakage failure. //
	//if(g_ShadowRegister[22]) // DOPL //
	//{
	//	VBPS_ramp_up(3, 4.5, 0.1);
	//	BPS_dvi->set_voltage(BPS_ch, 4.5, VOLT_5_RANGE);
	//}

	Mux20_Open_relay(K37);//Make sure OVI3 CH.0 connected to SDA
	wait.delay_10_us(200);
	Mux20_Close_relay(K39);
	wait.delay_10_us(200);

	// IIH_SDA_Post  //
	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
	SDA_ovi->set_voltage(SDA_ch, 3.3, RANGE_5_V);	
	wait.delay_10_us(30);
	CurrentClamp = 28e-6;
	SDA_ovi->set_current(SDA_ch, CurrentClamp, RANGE_30_UA);
	SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(100);
	IIH_SDA_Post = SDA_ovi->measure_average(5);
	IIH_SDA_Delta = IIH_SDA_Post -g_ILH_SDA;
	
	// Make sure test limits are not wider than current clamp. //
	UpperLimit = (func.dlog->tests[A_IIH_SDA_Post].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_IIH_SDA_Post].f_min_limit_val[0]); // Get lower test limit //
	if (UpperLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -218;
			IIH_SDA_Post = -999;
		}
	}
	if (UpperLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = -218;
			IIH_SDA_Post = -999;
		}
	}
	if (LowerLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -218;
			IIH_SDA_Post = -999;
		}
	}
	if (LowerLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = -218;
			IIH_SDA_Post = -999;
		}
	}

	// IIL_SDA_Post //
	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
	SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V);//Change current ranges away from abs max to avoid glitch	
	wait.delay_10_us(50);
	CurrentClamp = 2.991e-6;
	SDA_ovi->set_current(SDA_ch, CurrentClamp, RANGE_3_UA);
	wait.delay_10_us(100);
	IIL_SDA_Post = SDA_ovi->measure_average(5);
	IIL_SDA_Delta = IIL_SDA_Post - g_ILL_SDA;

	// Make sure test limits are not wider than current clamp. //
	UpperLimit = (func.dlog->tests[A_IIL_SDA_Post].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_IIL_SDA_Post].f_min_limit_val[0]); // Get lower test limit //
	if (UpperLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -219;
			IIL_SDA_Post = -999;
		}
	}
	if (UpperLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = 219;
			IIL_SDA_Post = -999;
		}
	}
	if (LowerLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = 219;
			IIL_SDA_Post = -999;
		}
	}
	if (LowerLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = 219;
			IIL_SDA_Post = -999;
		}
	}

	Mux20_Open_relay(K39);
	Mux20_Close_relay(K37);
	delay(2);

	//SCL
	SCL_ovi->set_voltage(SCL_ch, 3.3, RANGE_5_V);	
	wait.delay_10_us(25);
	SCL_ovi->set_current(SCL_ch, 29e-6, RANGE_30_UA);
	SCL_ovi->set_meas_mode(SCL_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(150);
	IIH_SCL_Post = SCL_ovi->measure_average(5);
	IIH_SCL_Delta = IIH_SCL_Post - g_ILH_SCL;

	// Ramp down- prevent undershoot //
	SCL_ovi->set_voltage(SCL_ch, 1.5, RANGE_5_V);//Change current ranges away from abs max to avoid glitch	
	wait.delay_10_us(10);
	SCL_ovi->set_voltage(SCL_ch, 0.6, RANGE_5_V);
	wait.delay_10_us(10);
	SCL_ovi->set_voltage(SCL_ch, 0.3, RANGE_5_V);
	wait.delay_10_us(10);
	SCL_ovi->set_voltage(SCL_ch, 0.15, RANGE_5_V);
	wait.delay_10_us(10);
	SCL_ovi->set_voltage(SCL_ch, 0, RANGE_5_V);
	wait.delay_10_us(20);
	CurrentClamp = 2.991e-6;
	SCL_ovi->set_current(SCL_ch, CurrentClamp, RANGE_3_UA);
	wait.delay_10_us(100);
	IIL_SCL_Post = SCL_ovi->measure_average(5);
	IIL_SCL_Delta = IIL_SCL_Post - g_ILL_SCL;


	// Make sure test limits are not wider than current clamp. //
	UpperLimit = (func.dlog->tests[A_IIL_SCL_Post].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_IIL_SCL_Post].f_min_limit_val[0]); // Get lower test limit //
	if (UpperLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = -220;
			IIL_SCL_Post = -999;
		}
	}
	if (UpperLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = 220;
			IIL_SCL_Post = -999;
		}
	}
	if (LowerLimit < 0)
	{
		if((-1*CurrentClamp) > LowerLimit)
		{	
			g_Error_Flag = 220;
			IIL_SCL_Post = -999;
		}
	}
	if (LowerLimit > 0)
	{
		if(CurrentClamp < UpperLimit)
		{	
			g_Error_Flag = 220;
			IIL_SCL_Post = -999;
		}
	}

	// Powerdown //
	Open_relay(K2);
	Open_relay(K18);
	Mux20_Open_relay(K37);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1, prevent undershoot //
	wait.delay_10_us(4);
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
	wait.delay_10_us(4);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	uVCC_ovi->set_voltage(uVCC_ch, 1.0, RANGE_10_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	wait.delay_10_us(30);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	wait.delay_10_us(100);
	uVCC_ramp_down(1, 0, .05);
	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
	VBPS_ramp_down(3, 0, 200e-3);
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE);
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	wait.delay_10_us(200); // Wait for relays //

	
	// Datalog //
	PiDatalog(func, A_BPS_Stress_Volt, BPS_Stress_Volt, 27, POWER_UNIT);
	PiDatalog(func, A_IIL_FW_Post, IIL_FW_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_FW_Delta, IIL_FW_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_VO_Post, IIL_VO_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_VO_Delta, IIL_VO_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_IS_Post, IIL_IS_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_IS_Delta, IIL_IS_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_VBD_Post, IIL_VBD_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_VBD_Delta, IIL_VBD_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_VBD_Post, IIH_VBD_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_VBD_Delta, IIH_VBD_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_SDA_Post, IIL_SDA_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_SDA_Delta, IIL_SDA_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_SDA_Post, IIH_SDA_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_SDA_Delta, IIH_SDA_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_SCL_Post, IIL_SCL_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_SCL_Delta, IIL_SCL_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_SCL_Post, IIH_SCL_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_SCL_Delta, IIH_SCL_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_COMP_Post, IIL_COMP_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIL_COMP_Delta, IIL_COMP_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_COMP_Post, IIH_COMP_Post, 27, POWER_MICRO);
	PiDatalog(func, A_IIH_COMP_Delta, IIH_COMP_Delta, 27, POWER_MICRO);
	//PiDatalog(func, A_BPS_IS1_Pre, g_BPS_IS1_Pre, 27, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_BPS_IS1_Pre, g_BPS_IS1_Pre, 5, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	//PiDatalog(func, A_BPS_IS1_Post, BPS_IS1_Post, 27, POWER_MICRO);
	//PiDatalog(func, A_BPS_IS1_Delta, BPS_IS1_Delta, 27, POWER_MICRO);
	//PiDatalog(func, A_BPS_IS1hf_Pre, BPS_IS1hf_Pre, 27, POWER_MICRO);
	//PiDatalog(func, A_BPS_IS1hf_Post, BPS_IS1hf_Post, 27, POWER_MICRO);
	//PiDatalog(func, A_BPS_IS1hf_Delta, BPS_IS1hf_Delta, 27, POWER_MICRO);
	PiDatalog(func, A_BPS_IS2_Pre, g_BPS_IS2_Pre, 27, POWER_MILLI);
	//PiDatalog(func, A_BPS_IS2_Post, BPS_IS2_Post, 27, POWER_MILLI);
	//PiDatalog(func, A_BPS_IS2_Delta, BPS_IS2_Delta, 27, POWER_MILLI);

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
