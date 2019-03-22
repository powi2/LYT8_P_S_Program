//==============================================================================
// SR_Delay_tREQinh.cpp (User function)
// 
//    void SR_Delay_tREQinh_user_init(test_function& func)
//    void SR_Delay_tREQinh(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SR_Delay_tREQinh.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SR_Delay_tREQinh_user_init(test_function& func)
{
	SR_Delay_tREQinh_params *ours;
    ours = (SR_Delay_tREQinh_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SR_Delay_tREQinh(test_function& func)
{
    // The two lines below must be the first two in the function.
    SR_Delay_tREQinh_params *ours;
    ours = (SR_Delay_tREQinh_params *)func.params;

	// Increment function number //
	gFuncNum++;

//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_Func_Num_SR_Delay, gFuncNum, 28, POWER_UNIT);
//////
//////	// Skip Test if AbortTest set //
//////	if (AbortTest)
//////		return;
//////
//////	if (g_Fn_SR_Delay_tREQinh == 0 )  return;
//////
//////	// Test Time Begin //
//////	if (g_TstTime_Enble_P)
//////		g_begintime = g_mytimer.GetElapsedTime();
//////
//////	// Declare Variables //
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //
//////	float ISR_Pulldown=0.0;
//////	float VSR_Pulldown = 0.0;
//////	float SR_delay=0.0;
//////	float isr_Pullup=0;
//////	float VSR_Pullup = 0.0;
//////	float Rpd = 0.0;
//////	float Rpu = 0.0;
//////	float SR_threshold=0.0;
//////	float vSR_high=0.0;
//////	float tmeas =0.0;
//////	float iBPS=0.0;
//////	float vset=0.0;
//////	float TREQ_INH=0.0;
//////	int NTC_HighByte = 0;
//////	float TON_P=0.0;
//////	float TOFF_P=0.0;
//////	float tHS=0.0;
//////	float Freq_P_tHS=0.0;
//////	float Freq_S_tHS=0.0;
//////	float Soft_time_S=0.0;
//////	float Soft_FrqStart_S=0.0;
//////	float ISR_Pullup[50]={0};
//////	int i=0;
//////	int Unwanted_pulses=0;
//////	int j=0;
//////	float SR_freq[20]={0};
//////	float SR_Ton[20]={0};
//////	bool Switching = false;
//////	float SRfrequency = 0; 
//////	float SRCkOpen=0;
//////	float SRCkCap=0;
//////	float SRGdFrequency=0;
//////	int num_pulse = 0; 
//////	int Cknum_pulse=0; 
//////	int Gdnum_pulse=0;
//////	float Pulse_dly_HS = 0; 
//////	float Pulse_dly_0V = 0;
//////	float FWFlate_filter_NM = 0; 
//////	float FWFlate_dly_0V = 0;
//////	float Delta_dly_0V = 0;
//////	float vbps = 0;
//////	float isr = 0;
//////	float ISR_clamp = 0;
//////	float LowerLimit = 0;
//////	int READ59_word[16] = {0};
//////	int WordArray[16] = {0};
//////	float SR_Delay_TT = 0;
//////	int LoopCount = 0;
//////	int READ10_word[16] = {0};
//////	Pulse pulse; // External trigger pulse from dvi for debug
//////
//////	// Charge up PV3 for SOA test
//////	pv3_4->normal_comp();
//////	pv3_4->set_voltage(0, RANGE_3_V);
//////	pv3_4->set_current(0);
//////	pv3_4->set_meas_mode(PV3_CHARGE_S);			// Monitor storage cap DEBUG_MODEge_mode
//////	pv3_4->drive_off();
//////	pv3_4->charge_on();							// Requires a 15ms wait
//////	// Charge up PV3 for SOA test
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// ISR_Pulldown-S, ISR_Pullup-S: Only power up Secondary
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Negative cycle BPP pin //
////////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////ddd_7->ddd_connect_drivers(); // Fix for repeatability, suspect DDD8. //
//////		
//////	// Drain //
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //
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
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_5_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////
//////	// SR //
//////	// setup to measure signal come out of SR
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_1_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 200e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_5_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C secondary test mode //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////////DSM_Write_Word(g_TM_ANA, 0x0134);
//////	
//////	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////////DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
//////	
//////	//Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	SDA_ovi->set_current(SDA_ch, 30e-6, RANGE_30_UA); // OVI_3_0 //
//////	SCL_ovi->set_current(SCL_ch, 30e-6, RANGE_30_UA); // OVI_3_1 //
//////	wait.delay_10_us(5);
//////	ddd_7->ddd_run_pattern(HIZ_SDA_SCL_start, HIZ_SDA_SCL_stop);	// HIZ SDA and SCL //
//////
//////	// Set FW switching, for worst case SR driver strength? //
//////	FW_dvi->set_voltage(FW_ch, 5, VOLT_5_RANGE); // DVI_11_1 //
//////
//////	// DDD level //
//////	g_DDD_Low = -0.5; // Save current value //
//////	g_DDD_High = 1.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	wait.delay_10_us(5);
//////	ddd_7->ddd_run_pattern(SDA_SCL_HIZ_FW_High_start, SDA_SCL_HIZ_FW_High_stop); // FW will start with High //
//////	wait.delay_10_us(10);
//////	Close_relay(K21); // Connect FW pin to DDD //
//////	wait.delay_10_us(200);
//////	Open_relay(K18); // Disconnect FW pin from DVI //
//////	wait.delay_10_us(200);
//////	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
//////	ddd_7->ddd_run_pattern();
//////	wait.delay_10_us(10);
//////
//////	// Set VO and FW to zero to limit influence on BPS //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_5_RANGE); // DVI_11_1 //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR pulldown //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// First do Rpd measurement at 30mA to avoid device heating //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init + 0.2, VOLT_10_RANGE); // DVI_9_1 //
//////	SR_dvi2k->set_voltage(SR_ch, 1.0, VOLT_1_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 30e-3, RANGE_200_MA);
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE);
//////	wait.delay_10_us(50);	
//////
//////	VSR_Pulldown = SR_dvi2k->measure_average(8);
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(50);
//////	ISR_Pulldown = SR_dvi2k->measure_average(8);
//////	Rpd = VSR_Pulldown / ISR_Pulldown;
//////
//////	// Now measure full pulldown current //
//////	SR_dvi2k->set_current(SR_ch, 2,	RANGE_2_A);
//////	SR_dvi2k->set_voltage(SR_ch, gVBPS_P_Init + 0.2, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(50);	
//////	ISR_Pulldown = SR_dvi2k->measure_average(8);
//////
//////	// Back to previous //
//////	SR_dvi2k->set_voltage(SR_ch, 1.0, VOLT_1_RANGE); // DVI_13_1, dvi2k //
//////
//////	// Stop FW negative pulses so SR stays low //
//////	ddd_7->ddd_stop_pattern();
//////	wait.delay_10_us(5);
//////
//////	// FB high to prevent switching //
//////	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_5_V); // OVI_1_2 //
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR pullup //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	wait.delay_10_us(5);
//////
//////	SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
//////	SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
//////	wait.delay_10_us(5);
//////
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////
//////	// SR to 0V //
//////	SR_dvi2k->set_voltage(SR_ch, 0, VOLT_5_RANGE); // DVI_13_1, dvi2k //
//////	wait.delay_10_us(50);
//////
//////	// VO back up to charge uVCC for I2C interface //
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_5_RANGE); // DVI_11_1 //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(100);
//////
//////	// Write the I2C command to connect the Vp SR pullup to SR pin. //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // Let SR come up //
//////	Write_Word(g_TM_SEL, 0x000A, NObin, HEX); // DableOn //
////////DSM_Write_Word(g_TM_SEL, 0x000A); // DableOn //
//////
//////	// Set VO and FW to zero to limit influence on BPS //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_5_RANGE); // DVI_11_1 //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(50);
//////
//////	// Meaure BPS voltage //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final+100e-3, VOLT_10_RANGE);
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
//////	wait.delay_10_us(50);
//////	vbps = BPS_dvi->measure_average(10);
//////
//////	// First measure Rpu at 30mA forcing current to limit heating. //
//////	SR_dvi2k->set_voltage(SR_ch, 4.3, VOLT_5_RANGE);
//////	SR_dvi2k->set_current(SR_ch, -30e-3, RANGE_200_MA);
//////	wait.delay_10_us(50);
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(20);
//////
//////	isr = SR_dvi2k->measure_average(20);	
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE);
//////	wait.delay_10_us(50);	
//////	VSR_Pullup = SR_dvi2k->measure_average(20);
//////
//////	// Calculate Rpu //
//////	Rpu = -(vbps - VSR_Pullup) / isr;
//////
//////	// Now measure full pullup current //
//////	ISR_clamp = -190e-3;
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(20);
//////	SR_dvi2k->set_current(SR_ch, ISR_clamp, RANGE_200_MA);
//////	wait.delay_10_us(2);
//////	SR_dvi2k->set_voltage(SR_ch, 2, VOLT_5_RANGE);
//////	wait.delay_10_us(50);
//////	isr_Pullup = SR_dvi2k->measure_average(5);
//////
//////	// Be sure lower test limit is not below ISR_clamp or test can never fail. //
//////	LowerLimit = (func.dlog->tests[A_ISR_Pullup].f_min_limit_val[0]); // Get lower limit //
//////	if ( (LowerLimit-2e-3) < ISR_clamp)
//////	{
//////		isr_Pullup = 999;
//////		g_Error_Flag = -153;
//////	}
//////	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // Limit the currrent as soon as possible to avoid heating. //
//////	
//////	// Powerdown //
//////	ddd_7->ddd_run_pattern(HIZ_SDA_SCL_start, HIZ_SDA_SCL_stop);	// HIZ SDA and SCL //
//////	wait.delay_10_us(2);
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////////	Mux20_Open_relay(K38);
////////	Mux20_Open_relay(K40);
//////	FW_dvi->set_voltage(FW_ch, 2, VOLT_5_RANGE); // DVI_11_1, prevent undershoot  //
//////	FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //
//////	Open_relay(K21); // FW DDD-7-3 
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	wait.delay_10_us(45); // prevent SR undershoot //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_5_RANGE); // DVI_11_1 //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(5);
//////	SR_dvi2k->set_voltage(SR_ch, 3, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	wait.delay_10_us(3);
//////	SR_dvi2k->set_voltage(SR_ch, 2, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	wait.delay_10_us(3);
//////	SR_dvi2k->set_voltage(SR_ch, 1, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	wait.delay_10_us(3);
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////////	VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR_delay: Secondary controlled primary Switching
//////	//
//////	// Measure delay time from the falling edge of SR to the falling edge of Drain
//////	// SR_delay is the delay measured from SR drive turning off (SR low) to drain 
//////	// turning on.  The actual delay is from the secondary request pulse to drain turn 
//////	// on.  The actual secondary request pulse signal can be seen on BPS pin as a glitch 
//////	// and can also be observed in test mode looking at secondary request pulse on SR pin.
//////	// This test is done in test mode looking at secondary request pulse on SR pin.
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	VPIN_ovi->connect(VPIN_ch);
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////
//////	// FW //
//////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	//SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////	tmu_6->close_relay(TMU_CHAN_A_DUT2); // Connect TMU_CHAN_A2 to SR pin //
//////	
//////	// TMU trigger setup //
//////	tmu_6->start_trigger_setup(1.5, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(4.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	Write_Word(g_TM_ANA, 0x013C, NObin, HEX);
////////DSM_Write_Word(g_TM_ANA, 0x013C);
//////
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////	
//////	// Goto test mode to look at secondary request pulse on SR pin //
//////	Write_Word(g_TM_SEL, 0x0006, NObin, HEX); // Pulse //
////////DSM_Write_Word(g_TM_SEL, 0x0006); // Pulse //
//////
//////	// Setup SR //
//////	Mux20_Open_relay(K50); // Remove SR pin connection to GND //
//////	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
//////
//////	// Setup DDD //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	//wait.delay_10_us(100);
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	wait.delay_10_us(10);
//////
//////	// Vpin to DDD //
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	wait.delay_10_us(200);
//////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////	wait.delay_10_us(200);
//////
//////	// Primary TM5 bypass Wait and Listen power up
////////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
//////
//////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
//////
////////	wait.delay_10_us(50);
//////wait.delay_10_us(70);
//////
//////	// VBP_P drops when secondary has control //
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
//////	wait.delay_10_us(8);
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
//////	wait.delay_10_us(10);
//////	SR_delay = 0;
//////	for (i=0; i<10; i++)
//////	{
//////		// SR to Drain prop delay //
//////		tmu_6->arm(); 
//////		wait.delay_10_us(10);
//////		SR_delay += tmu_6->read();	//See ~100ns from scope for INNO 3x
//////	}
//////	SR_delay /= 10;
//////
//////	// Powerdown //
//////	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
////////	tmu_6->open_relay(TMU_CHAN_A_DUT2); // TMU_CHAN_A2 SR pin //
////////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	Mux20_Open_relay(K59); // SR pin to DVI_13_1, dvi2k //
////////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////////	Mux20_Open_relay(K37);
////////	Mux20_Open_relay(K38);
////////	Mux20_Open_relay(K40);
////////	Mux20_Open_relay(K39);
////////	Disconnect_InvSyn_IM();
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0, 200e-3);
////////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	Open_relay(K17); 
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// tREQ_INH-S: the maximum amount of time the seconary will wait for an FW pin
//////	//             falling edge after is sends a switching request.
//////	// INH_Cycles-S: Eight cycles. Also known as "no response" cycles.  If the secondary 
//////	//               does not see an FW falling edge for 8 consecutive switching requests 
//////	//               then it goes to auto-restart.
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Gage sample setup //
//////	g_SAMPLE_SIZE = GAGE_POST_32K;
//////
//////	// Channel B setup //
//////	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,g_SAMPLE_SIZE); 
//////
//////	gage_input_control_xp (GAGE_CHAN_B, // channel
//////			GAGE_INPUT_ENABLE, // enable / disable
//////			GAGE_DC, // coupling
//////			GAGE_PM_5_V|GAGE_1_MOHM_INPUT); // range, impedance
//////	
//////	gage_trigger_control_xp (GAGE_CHAN_B, // trigger source
//////			GAGE_DC, // coupling for ext trig
//////			GAGE_PM_5_V, // range for CHA trigger
//////			GAGE_POSITIVE, // slope
//////			0.15, // 1.0V trigger level 
//////	   		g_SAMPLE_SIZE); // 20ns * GAGE_WAVEFORM_BUFFER_SIZE
//////
//////	// Set up Buffer Clamp //
//////	BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA);
//////	BC_ovi->set_voltage(BC_ch, 4.4, VOLT_10_RANGE);	// OVI_1_3 Account for one diode drop
//////
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	VPIN_ovi->connect(VPIN_ch);
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////
//////	// FW //
//////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	//SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////	tmu_6->close_relay(TMU_CHAN_A_DUT2); // Connect TMU_CHAN_A2 to SR pin //
//////	
//////	// TMU trigger setup //
//////	tmu_6->start_trigger_setup(1.5, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(4.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
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
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
//////	// switching freqeuncy with FB pin //
//////	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
//////	{
//////		// Read out contents of shadow register.  Can't overwrite shadow register. //
//////		/*
//////		Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
//////		Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
//////
//////		WordArray[0] = READ59_word[0];
//////		WordArray[1] = READ59_word[1];
//////		WordArray[2] = READ59_word[2];
//////		WordArray[3] = READ59_word[3];
//////		WordArray[4] = READ59_word[4];
//////		WordArray[5] = READ59_word[5];
//////		WordArray[6] = READ59_word[6];
//////		WordArray[7] = READ59_word[7];
//////		WordArray[8] = READ59_word[8];
//////		WordArray[9] = READ59_word[9];
//////		WordArray[10] = READ59_word[10];
//////		WordArray[11] = READ59_word[11];
//////		WordArray[12] = READ59_word[12];
//////		WordArray[13] = READ59_word[13];
//////		WordArray[14] = READ59_word[14];
//////		WordArray[15] = READ59_word[15]; // bit[63]: trim_no_fb_pin //
//////		*/
//////		WordArray[0] = g_EE_ShadReg48;
//////		WordArray[1] = g_EE_ShadReg49;
//////		WordArray[2] = g_EE_ShadReg50;
//////		WordArray[3] = g_EE_ShadReg51;
//////		WordArray[4] = g_EE_ShadReg52;
//////		WordArray[5] = g_EE_ShadReg53;
//////		WordArray[6] = g_EE_ShadReg54;
//////		WordArray[7] = g_EE_ShadReg55;
//////		WordArray[8] = g_EE_ShadReg56;
//////		WordArray[9] = g_EE_ShadReg57;
//////		WordArray[10] = g_EE_ShadReg58;
//////		WordArray[11] = g_EE_ShadReg59;
//////		WordArray[12] = g_EE_ShadReg60;
//////		WordArray[13] = g_EE_ShadReg61;
//////		WordArray[14] = g_EE_ShadReg62;
//////		WordArray[15] = g_EE_ShadReg63; // bit[63]: trim_no_fb_pin //
//////
//////		// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
//////		WordArray[15] = 0;
//////		Write_Word(g_SREG3, NOhex, WordArray, BIN);
//////	}
//////
//////	// Setup SR //
//////	Mux20_Open_relay(K50); // Remove SR pin connection to GND //
//////	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
//////
//////	// Setup DDD //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	//wait.delay_10_us(100);
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	wait.delay_10_us(10);
//////
//////	// Vpin to DDD //
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	wait.delay_10_us(200);
//////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////	wait.delay_10_us(200);
//////
//////	// Primary TM5 bypass Wait and Listen power up //
//////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////////Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
//////
////////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
//////
//////	wait.delay_10_us(50);
////////wait.delay_10_us(70);
//////
//////	// VBP_P drops when secondary has control //
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
//////	wait.delay_10_us(8);
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
//////	wait.delay_10_us(10);
//////
//////	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2	
//////	wait.delay_10_us(20);
//////	Disconnect_InvSyn_IM();	// Disconnect FW pin
//////	Close_relay(K10); //Drain to RDS_BUF_IN //
//////	wait.delay_10_us(200);
//////	Close_relay(K18);
//////	wait.delay_10_us(200);
//////	FW_dvi->set_voltage(FW_ch, 3, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	wait.delay_10_us(20);
//////
//////	Gage_Start_Capture();
//////	wait.delay_10_us(1);
//////	FB_ovi->set_voltage(FB_ch, 1.0, RANGE_2_V); // OVI_1_2	
//////	wait.delay_10_us(20);
//////
//////	Gage_Wait_For_Capture_Complete();
//////
//////	g_Save_Awav_TextDebug_ALL = 0;
//////	Gage_Find_NTCcode(&TREQ_INH, &NTC_HighByte);
//////	g_Save_Awav_TextDebug_ALL = 0;
//////
//////	// Powerdown //
//////	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	BC_ovi->set_voltage(BC_ch, 0, VOLT_10_RANGE);	// OVI_1_3 Account for one diode drop
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//////	tmu_6->open_relay(TMU_CHAN_A_DUT2); // TMU_CHAN_A2 SR pin //
//////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	Mux20_Open_relay(K59); // SR pin to DVI_13_1, dvi2k //
////////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////////	Mux20_Open_relay(K37);
////////	Mux20_Open_relay(K38);
////////	Mux20_Open_relay(K40);
////////	Mux20_Open_relay(K39);
//////	Open_relay(K10); //Drain RDS_BUF_IN //
////////	Open_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0, 200e-3);
////////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	Open_relay(K17); 
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR:Threshold 
//////	//
//////	// Powerup in testmode to bring SR comparator output to SR pin (DFWh signal).  Sweep 
//////	// FW pin and look for SR pin votlage change.
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
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
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 300e-3, RANGE_300_MA); // DVI_11_1 //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////////DSM_Write_Word(g_TM_ANA, 0x0134);
//////	
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////	
//////	// Goto test mode to look at SR comparator output (DFWh signal) on SR pin //
//////	Write_Word(g_TM_SEL, 0x0016, NObin, HEX); // DFWh //
////////DSM_Write_Word(g_TM_SEL, 0x0016); // DFWh //
//////
//////	// Float SR //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k //
//////
//////	// FB high to prevent switching noise //
//////	// Not really needed if EEPROM bit63 is '1', but doesn't hurt to have it.  Doesn't look like there's any switching noise anyway per scope. //
//////	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
//////	wait.delay_10_us(5);
//////
//////	//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
//////	//FW_dvi->set_current(FW_ch, 1e-3, RANGE_30_MA);
//////	FW_dvi->set_voltage(FW_ch, gVshunt_BPS+0.2,	VOLT_10_RANGE);
//////	wait.delay_10_us(100); //needed 1ms here 
//////
//////	// Ramp up FW so SR will toggle from low to high //
//////	LowerLimit = (func.dlog->tests[A_SR_threshold].f_min_limit_val[0])*1.2; // Get lower search limit //
//////	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//////	{
//////		LowerLimit = (func.dlog->tests[A_SR_threshold].f_min_limit_val[0])*1.5; // Get lower search limit //
//////	}
//////
//////	search_SR_th(&SR_threshold, LowerLimit);
//////
//////	// Powerdown //
//////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	Mux20_Open_relay(K37);
//////	Mux20_Open_relay(K38);
//////	Mux20_Open_relay(K40);
//////	Mux20_Open_relay(K39);
//////	Open_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	wait.delay_10_us(45); // prevent SR undershoot //
//////	VBPS_ramp_down(4, 0, 200e-3);
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR_Chk_Open-S
//////	// Keep SR pin floating during powerup and make sure device does not switch 
//////	// after secondary handshake - go/no go test.  
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
////////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(1.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	//Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	//VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////	//wait.delay_10_us(300);
//////	//ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////
//////	// V pin //
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	wait.delay_10_us(10);
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	wait.delay_10_us(300);
//////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////
//////	// FW //
//////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2, VOLT_20_RANGE); // OVI_1_4	
//////
//////	// SR //
//////	// Floating SR pin on the contactor board //
//////	tmu_6->close_relay(TMU_EXT_DRV3); // Relay K68, SR pin //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// SDA //
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////
//////	// SCL //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
//////
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Primary TM5 bypass Wait and Listen power up //
////////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
//////
//////
//////
//////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
//////
////////	wait.delay_10_us(50);
//////wait.delay_10_us(70);
//////
//////	// VBP_P drops when secondary has control //
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
//////	wait.delay_10_us(8);
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
//////	wait.delay_10_us(10);
//////
//////	tmu_6->arm();
//////	wait.delay_10_us(10);
//////	tmeas = tmu_6->read();
//////
//////	if(tmeas < 1e-9) // No Switching //
//////		SRCkOpen = 1;
//////	else
//////		SRCkOpen = 0;
//////
//////	// Powerdown //
//////	tmu_6->open_relay(TMU_EXT_DRV3); // Relay K68, SR pin //
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////////	Disconnect_InvSyn_IM();
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0, 200e-3);
////////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	wait.delay_10_us(200);
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SR_Chk_5nF-S
//////	// Connect 5nF cap to SR pin during powerup and make sure part still switches after 
//////	// secondary handshake- go/no go test.
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	//Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	//Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	//tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	//tmu_6->start_trigger_setup(3, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	//tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////
//////	// V pin //
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	wait.delay_10_us(10);
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	wait.delay_10_us(300);
//////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////	//wait.delay_10_us(200);
//////	
//////	// FW //
//////	//Connect_InvSyn_IM(Low_Load_Vd_Input);
//////
//////	// SR //
//////	// Connect 5nF cap //
//////	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
//////	Close_relay(K5); // Connect 5nF Cap to SR //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//////	//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////
//////	// Set DDD for I2C. //
//////	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////
//////	// I2C into test mode. //  
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Primary TM5 bypass Wait and Listen power up //
//////	//ddd_7->ddd_set_clock_period(Dclk_period);
//////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////	wait.delay_10_us(50);
//////
//////	// VBP_P drops when secondary has control //
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
//////	wait.delay_10_us(8);
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
//////	wait.delay_10_us(10);
//////
//////	tmu_6->init();
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(3, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	tmu_6->stop_trigger_setup(2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	wait.delay_10_us(200);
//////
//////	wait.delay_10_us(50);
//////	tmu_6->arm();
//////	wait.delay_10_us(10);
//////	tmeas = tmu_6->read();
//////	if(tmeas > 0)	// Switching //
//////		SRCkCap = 1;
//////	else
//////		SRCkCap = 0;
//////
//////	// Powerdown //
//////	IS_dvi2k->set_voltage(IS_ch, 0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//////	Open_relay(K3);
//////	//Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	//Mux20_Open_relay(K37);
//////	//Mux20_Open_relay(K38);
//////	//Mux20_Open_relay(K40);
//////	//Mux20_Open_relay(K39);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	Mux20_Open_relay(K59); // SR pin to DVI_13_1, dvi2k //
//////	Open_relay(K5); // Disconnect 5nF Cap from SR //
//////	Disconnect_InvSyn_IM();
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	//uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0, 200e-3);
//////	//VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	//VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	wait.delay_10_us(200);
//////
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Pulse_dly_HS-S, Pulse_dly_OV-S, FWFlate, FWFlate_OV, Delta_dly_OV-S
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
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
//////	// Only 1V on FW pin here to reduce current to BPS pin.  FW upto 3V after BPS brought up. //
//////	Close_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	tmu_6->close_relay(TMU_CHAN_A_DUT1); // Connect TMU chA to FW //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////	tmu_6->close_relay(TMU_CHAN_B_DUT2); // TMU chB to SR pin //
//////	tmu_6->start_trigger_setup(0.55, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(0.3, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// FW //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, 3, VOLT_10_RANGE); // DVI_11_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->disconnect(2);
//////	//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C secondary //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////////DSM_Write_Word(g_TM_ANA, 0x0134);
//////	
//////	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////////DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
//////	
////////	Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Float SR dvi //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
//////	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
//////	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// Goto test mode to look at secondary request pulse on SR pin //
//////	Write_Word(g_TM_SEL, 0x0006, NObin, HEX); // Pulse //
////////DSM_Write_Word(g_TM_SEL, 0x0006); // Pulse //
//////
//////	// Hold SDA and SCL low before disconnecting DDD. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
//////	wait.delay_10_us(20);
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
//////	wait.delay_10_us(30);
//////	Mux20_Open_relay(K37);
//////	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
//////	Mux20_Open_relay(K39);
//////	wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
//////	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
//////	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
//////	wait.delay_10_us(200);
//////
//////	// BPS setup //
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	wait.delay_10_us(2);
//////	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS+0.2, VOLT_10_RANGE);			
//////	//wait.delay_10_us(50);
//////
//////	// Force FW DDD pulses continuously //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	
//////	// DDD level //
//////	g_DDD_Low = -0.5; // Save current value //
//////	g_DDD_High = 3.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
//////	wait.delay_10_us(10);
//////	Close_relay(K21); // Connect FW pin to DDD //
//////	wait.delay_10_us(200);
//////	Open_relay(K18); // Disconnect FW pin from DVI //
//////	wait.delay_10_us(200);
//////	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
//////	ddd_7->ddd_run_pattern();
//////	wait.delay_10_us(150);
//////	
//////	//for (i=0; i<50; i++)	// SR pin cannot drive stray capacitance
//////	//{
//////		// measure time
//////		tmu_6->arm(); 
//////		//wait.delay_10_us(40);
//////		wait.delay_10_us(10);
//////		tmeas = tmu_6->read(100e-6);
//////		//wait.delay_10_us(5);
//////		//if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
//////	//}
//////	Pulse_dly_HS = tmeas;
//////
//////	//Pulse_dly_0V
//////	VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 // // Above CV threshold //
//////	//FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // Above CV threshold
//////	wait.delay_10_us(10);
//////	if ((gISD_S+2e-3) > 29.999e-3 || (gISD_S+2e-3) < -29.999e-3) // Prevent out of range //
//////	{
//////		BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // Secondary vBPS_plus
//////	}
//////	else
//////		BPS_dvi->set_current(BPS_ch, gISD_S+2e-3, RANGE_30_MA);
//////	wait.delay_10_us(40);
//////
////////	for (i=0; i<10; i++)	// SR pin cannot drive stray capacitance
////////	{
//////		// measure time
//////		tmu_6->arm(); 
////////		wait.delay_10_us(14);
//////		wait.delay_10_us(10);
//////		tmeas = tmu_6->read(100e-6);
////////		wait.delay_10_us(5);
////////		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
////////	}
//////	Pulse_dly_0V = tmeas;
//////	
//////	// Powerdown //
//////	ddd_7->ddd_stop_pattern();
//////	SR_dvi2k->set_voltage(SR_ch, 0, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //	
//////	Mux20_Open_relay(K59); // SR pin DVI_13_1, dvi2k //
//////	tmu_6->open_relay(TMU_CHAN_A_DUT1); // Connect TMU HIZ to FW //
//////	tmu_6->open_relay(TMU_CHAN_B_DUT2); // tmu to SR pin //
//////	Open_relay(K21); // Disconnect FW pin from DDD //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
//////	wait.delay_10_us(5);
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // Secondary vBPS_plus
//////	VBPS_ramp_down(3, 0, 200e-3);
////////	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->connect(2);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// FWFlate //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	ddd_7->ddd_connect_drivers(); // Fix for repeatability, suspect DDD8. //
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
//////	// Only 1V on FW pin here to reduce current to BPS pin.  FW upto 4V after BPS brought up. //
//////	Close_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	tmu_6->close_relay(TMU_CHAN_A_DUT1); // Connect TMU CHA to FW //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////	tmu_6->close_relay(TMU_CHAN_B_DUT2); // tmu to SR pin //
//////	tmu_6->start_trigger_setup(0.55, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V); // FW //
//////	tmu_6->stop_trigger_setup(0.3, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V); // SR //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// FW //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, 3, VOLT_10_RANGE); // DVI_11_1 //
//////	
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// FB (COMP) //
//////	FB_ovi->disconnect(2);
//////	//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
//////	//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
////////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C secondary, do not put into test mode- because soft start is disabled in test mode. //  
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
////////DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
//////
//////	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
////////DSM_Write_Word(g_TM_ANA, 0x0134);
//////
//////	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
////////DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
//////	
////////	Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Float SR dvi //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
//////	Mux20_Close_relay(K59); // Disconnect SR pin from DVI_13_1, dvi2k //
//////	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// Goto test mode to look at FWFlate FW min 1us negative pulse indication on SR pin //
//////	Write_Word(g_TM_SEL, 0x0018, NObin, HEX); // FWFlate //
////////DSM_Write_Word(g_TM_SEL, 0x0018); // FWFlate //
//////
//////	// Hold SDA and SCL low before disconnecting DDD. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop); 
//////	wait.delay_10_us(20);
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
//////	wait.delay_10_us(30);
//////	Mux20_Open_relay(K37);
//////	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
//////	Mux20_Open_relay(K39);
//////	wait.delay_10_us(300); // Needed to prevent noise on SDA and SCL lines. //
//////	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
//////	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
//////	wait.delay_10_us(200);
//////
//////	// BPS setup //
////////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_300_MA);	 // DVI_9_1 //
//////	wait.delay_10_us(2);
//////	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS+0.2, VOLT_10_RANGE);			
//////
//////	// Force FW DDD pulses continuously //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	g_DDD_Low = -0.5; // Save current value //
//////	g_DDD_High = 3.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
//////	wait.delay_10_us(10);
//////	Close_relay(K21); // Connect FW pin to DDD //
//////	wait.delay_10_us(200);
//////	Open_relay(K18); // Disconnect FW pin from DVI //
//////	wait.delay_10_us(200);
//////
//////	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
//////	ddd_7->ddd_run_pattern();
//////	//wait.delay_10_us(6);
//////	wait.delay_10_us(150);
//////
////////	for (i=0; i<10; i++)	// SR pin cannot drive stray capacitance
////////	{
//////		// measure time
//////		tmu_6->arm(); 
//////		//wait.delay_10_us(14);
//////		wait.delay_10_us(10);
//////		tmeas = tmu_6->read(100e-6);
////////		wait.delay_10_us(5);
////////		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
////////	}
//////	FWFlate_filter_NM = tmeas;
//////
//////	//FWFlate_dly_OV
//////	VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 // // Above CV threshold //
//////	//FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // Above CV threshold
//////	wait.delay_10_us(10);
//////	if ((gISD_S+2e-3) > 29.999e-3 || (gISD_S+2e-3) < -29.999e-3) // Prevent out of range //
//////	{
//////		BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // Secondary vBPS_plus
//////	}
//////	else
//////		BPS_dvi->set_current(BPS_ch, gISD_S+2e-3, RANGE_30_MA);
//////	wait.delay_10_us(40);
//////
////////	for (i=0; i<10; i++)
////////	{
////////		// measure time
//////		tmu_6->arm(); 
////////		wait.delay_10_us(14);
//////		wait.delay_10_us(10);
//////		tmeas = tmu_6->read(100e-6);
////////		wait.delay_10_us(5);
////////		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
////////	}
//////	FWFlate_dly_0V = tmeas;
//////
//////	// Delta_dly_OV //
//////	Delta_dly_0V = Pulse_dly_0V - FWFlate_dly_0V;
//////
//////	// Powerdown //
//////	ddd_7->ddd_stop_pattern();
//////	SR_dvi2k->set_voltage(SR_ch, 0, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //	
//////	Mux20_Open_relay(K59); // SR pin DVI_13_1, dvi2k //
//////	tmu_6->open_relay(TMU_CHAN_A_DUT1); // Connect TMU HIZ to FW //
//////	tmu_6->open_relay(TMU_CHAN_B_DUT2); // tmu to SR pin //
//////	Open_relay(K21); // Disconnect FW pin from DDD //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
////////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////////	uVCCrampDown(0.5, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
//////	wait.delay_10_us(5);
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // Secondary vBPS_plus
//////	VBPS_ramp_down(3, 0, 200e-3);
////////	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
////////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->connect(2);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Unwanted_pulses
//////	//
//////	// If secondary sees 4 FW pin falling edges without sending any switching 
//////	// requests, the secondary goes to auto-restart.
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BPP cycle //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////
//////	// Drain //
//////	//D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
//////	//D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
//////
//////	// BPP //
//////	//BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	//BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	//VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	//VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////
//////	// FW //
//////	//Close_relay(K21); // FW to DDD-7-3 //
//////	//ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
//////	Close_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 300e-3, RANGE_300_MA); // DVI_11_1 //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
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
//////	// FB (COMP) //
//////	FB_ovi->disconnect(2);
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
////////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Prevent secondary requests //
//////	VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(10);
//////
//////	// Check bit "control_s" in READ10 register to confirm secondary does not have control. //
//////	Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
//////	Read_Word(g_RDADDR, READ10_word); // READ10 //
//////	if ( READ10_word[14] == 1) // Error. Secondary already has control. //
//////		g_Error_Flag = -193;
//////
//////	// Three negative pulse on FW pin to give control to secondary //
//////	//Force_Neg_Pulses_FW_DDD(4.9, -0.5);
//////	//wait.delay_10_us(16);
//////	FW_dvi->set_voltage(FW_ch, -0.4, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, -0.4, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, -0.4, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(5);
//////
//////	// Check bit "control_s" in READ10 register to confirm secondary now has control. //
//////	Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
//////	Read_Word(g_RDADDR, READ10_word); // READ10 //
//////	if ( READ10_word[14] == 0) // Error. Secondary does not have control. //
//////		g_Error_Flag = -193;
//////
//////	// Apply unwanted pulses until secondary gives up control //
//////	for (i=1; i<10; i++)
//////	{
//////		Unwanted_pulses = i;
//////		FW_dvi->set_voltage(FW_ch, -0.4, VOLT_1_RANGE); // DVI_11_1 //
//////		wait.delay_10_us(5);
//////		FW_dvi->set_voltage(FW_ch, 1, VOLT_1_RANGE); // DVI_11_1 //
//////		wait.delay_10_us(5);
//////		Write_Word(g_RDADDR, g_READ10, NObin, HEX); // READ10 //
//////		Read_Word(g_RDADDR, READ10_word); // READ10 //
//////		if ( READ10_word[14] == 0) // Seconday gave up control, exit loop //
//////			break;	
//////	}
//////
//////	// Powerdown //
////////	Mux20_Open_relay(K50); // SR pin GND//
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	Open_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_1_RANGE); // DVI_11_1 //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(0.5, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
//////	wait.delay_10_us(5);
//////	VBPS_ramp_down(3, 0, 200e-3);
//////	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->connect(2);
////////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
////////	Mux20_Open_relay(K37);
////////	Mux20_Open_relay(K38);
////////	Mux20_Open_relay(K40);
////////	Mux20_Open_relay(K39);
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////	// Datalog
//////	if (gSiOption_s == 2304 || gSiOption_s == 6400) // 2304: SET Rev C silicon, 6400: JSC Rev C silicon //
//////	{
//////		PiDatalog(func, A_ISR_Pulldown, ISR_Pulldown, 18, POWER_MILLI);
//////		PiDatalog(func, A_Rpd, Rpd, 18,	POWER_UNIT);
//////	}
//////	else if (gSiOption_s == 2305 || gSiOption_s == 6401) // 2305: SET Rev C1 silicon, 6401: JSC Rev C1 silicon //
//////	{
//////		PiDatalog(func, A_ISR_Pulldown_C1, ISR_Pulldown, 18, POWER_MILLI);
//////		PiDatalog(func, A_Rpd_SR_C1, Rpd, 18, POWER_UNIT);
//////	}
//////	else
//////	{
//////		PiDatalog(func, A_ISR_Pulldown_C1, -999, 18, POWER_MILLI);
//////		PiDatalog(func, A_Rpd_SR_C1, -999, 18, POWER_UNIT);
//////	}
//////	PiDatalog(func, A_SR_delay, SR_delay, 18, POWER_NANO);
//////	PiDatalog(func, A_ISR_Pullup, isr_Pullup, 18, POWER_MILLI);
//////	PiDatalog(func, A_Rpu, Rpu, 18, POWER_UNIT);
//////	PiDatalog(func, A_SR_threshold, SR_threshold, 18, POWER_MILLI);
//////	PiDatalog(func, A_SR_chk_Open, SRCkOpen, 18, POWER_UNIT);
//////	PiDatalog(func, A_SR_chk_5nF, SRCkCap, 18, POWER_UNIT);
//////	PiDatalog(func, A_tLong_NTC, TREQ_INH, 28, POWER_MICRO);
//////	PiDatalog(func, A_nCycles_Inhibit, NTC_HighByte, 28, POWER_UNIT);
//////	PiDatalog(func, A_Unwanted_pulses, Unwanted_pulses, 28, POWER_UNIT);
//////	PiDatalog(func, A_Pulse_dly_HS, Pulse_dly_HS, 28, POWER_MICRO);
//////	PiDatalog(func, A_Pulse_dly_0V, Pulse_dly_0V, 28, POWER_MICRO);
//////	PiDatalog(func, A_FWFlate_filter_NM, FWFlate_filter_NM,	28, POWER_MICRO);
//////	PiDatalog(func, A_FWFlate_dly_0V, FWFlate_dly_0V, 28, POWER_MICRO);
//////	PiDatalog(func, A_Delta_dly_0V, Delta_dly_0V, 28, POWER_NANO);
//////	
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		SR_Delay_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_SR_Delay_TT, SR_Delay_TT, 28, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
