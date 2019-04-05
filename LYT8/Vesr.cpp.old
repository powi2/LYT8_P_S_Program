//==============================================================================
// Vesr.cpp (User function)
// 
//    void Vesr_user_init(test_function& func)
//    void Vesr(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "Vesr.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Vesr_user_init(test_function& func)
{
	Vesr_params *ours;
    ours = (Vesr_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Vesr(test_function& func)
{
    // The two lines below must be the first two in the function.
    Vesr_params *ours;
    ours = (Vesr_params *)func.params;

	// Increment function number //
	gFuncNum++;

////	// Datalog gFuncNum variable //
////	if(gDisplay_FuncNum)
////		PiDatalog(func, A_Func_Num_Vesr, gFuncNum, 26, POWER_UNIT);
////
////	// Skip Test if AbortTest set // 
////	if (AbortTest)
////		return;
////
////	if (g_Fn_Vesr == 0 )  return;
////
////	// Test Time Begin //
////	if (g_TstTime_Enble_P)
////		g_begintime = g_mytimer.GetElapsedTime();
////
////	// Test Names //
////	float Vesr_Vfb1_S = 0;
////	float Vesr_DeltaT1_S = 0;
////	float Vesr_Vfb2_S = 0;
////	float Vesr_DeltaT2_S = 0;
////	float Vesr_Vfb3_S = 0;
////	float Vesr_DeltaT3_S = 0;
////	float Vesr_Vfb4_S = 0;
////	float Vesr_DeltaT4_S = 0;
////	float Vesr_slope1_S = 0;
////	float Vesr_intcp1_S = 0;
////	float Vesr_slope2_S = 0;
////	float Vesr_intcp2_S = 0;
////	float Vesr_Knee1_S = 0;
////	float Vesr_Knee2_S = 0;
////	//float Vesr_Knee_S = 0;
////	float Vesr_Peak_S = 0;
////	float Vesr_TT = 0;
////
////	// Declare Variables //
////	int NObin[1] = {0}; // Place holder //
////	int NOhex = 0; // Place holder //
////	float VFB0 = 0;
////	float VFBX = 0;
////	float period = 0;
////	float toff = 0;
////	int count=0;
////	float CV=0;
////	float LargeStep = 0;
////	float SmallStep = 0;
////	int i = 0;
////	int READ59_word[16] = {0};
////	int WordArray[16] = {0};
////	float VFB_force = 0;
////	float FBcv = 0;
////	float StepValue = 0;
////	float toff_Threshold = 0;
////	float toff_Delta = 0;
////	float toff_initial = 0;
////	int MedianIndex = 0;
////	float TempValue = 0;
////	float SortDone = 0;
////	int NumSlope = 0;
////	int OrigIndexLoc[50] = {0};
////	float Vesr_Vfb_temp[15] = {0};
////	float Vesr_DeltaT_temp[15] = {0};
////	float Vesr_slope_temp[50] = {0};
////	float Vesr_Vfb1_Initial = 0;
////	int j = 0;
////	int NumPoints = 7;
////	float FB_start_thresh = 0;
////	float UpperLimitSlope1 = 0;
////	float LowerLimitSlope1 = 0;
////	float UpperLimitPeakS = 0;
////	float LowerLimitPeakS = 0;
////	int StepCount = 0;
////	Pulse pulse(PULSE_RISING_EDGE,10e-6); // external trigger pulse from dvi for debug
////
////
////	// BPP cycle //
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
////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(2.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(3.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////tmu_6->start_trigger_setup(2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////tmu_6->stop_trigger_setup(3, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
////	//tmu_6->start_holdoff(20,true); // Use holdoff to average 128 cycles, remove jitter 
////	//tmu_6->stop_holdoff(128,true);
////	tmu_6->start_holdoff(0,FALSE);
////	tmu_6->stop_holdoff(0,FALSE);
////
////	// BPP //
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////
////	// V pin //
////	//VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
////	//Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
////	//wait.delay_10_us(300);
////	//ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////
////	// V pin //
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(10);
////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
////	wait.delay_10_us(300);
////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
////
////	// FW //
////	Connect_InvSyn_IM(Low_Load_Vd_Input);
////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4
////
////	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
////	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.7, VOLT_5_RANGE);
////
////	// SR //
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////	
////	// BPS //
////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
////	
////	// IS //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////
////	// Vout //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
////	
////	// FB (COMP) //
////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
////	FB_ovi->set_current(FB_ch, 0.1e-9, RANGE_30_UA); // OVI_1_2, float //
////	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
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
////	wait.delay_10_us(200);
////
////	// Setup DDD //
////	ddd_7->ddd_set_clock_period(Dclk_period);
////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
////
////	// DDD level //
////	g_DDD_Low = 0.0; // Save current value //
////	g_DDD_High = 4.0; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(10);
////
////	// Vpin to DDD //
////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
////	wait.delay_10_us(200);
////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
////	wait.delay_10_us(200);
////
////	// Primary TM5 bypass Wait and Listen power up //
//////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);
////	
////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////
//////	wait.delay_10_us(50);
////wait.delay_10_us(70);
////
////	// VBP_P drops when secondary has control //
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
////	wait.delay_10_us(8);
////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
////	wait.delay_10_us(10);
////
////	// Measure the Vref on FB pin with Vout set to CV_final. //
////	VO_dvi->set_voltage(VO_ch, g_CV_Final_S, VOLT_10_RANGE); // DVI_9_0 //
////	wait.delay_10_us(50);
////	FBcv = FB_ovi->measure_average(10); // OVI_1_2 //
////
////	// Adaptive VESR //
////	if(gTrim_SdwReg27_Trimops)	
////	{
////		while(StepCount < 2)
////		{
////			tmu_6->start_holdoff(0,FALSE);
////			tmu_6->stop_holdoff(0,FALSE);
////
////			// Large steps //
////			// Loop until switching starts //
////			LargeStep = 0.5e-3; // Large step //
////			VFB_force = FBcv + LargeStep + 40e-3; // Start above //
////			FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////			wait.delay_10_us(10);
////			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////			wait.delay_10_us(100);
////			period = 0;
////			while (period < 1e-9 && VFB_force > (FBcv - 40e-3) )
////			{
////				VFB_force -= LargeStep;
////				FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////				wait.delay_10_us(50);
////				tmu_6->arm(); 
////				wait.delay_10_us(50);
////				period = tmu_6->read();
////				if(period > 1e-9) // Check again to make sure //
////				{
////					tmu_6->arm(); 
////					wait.delay_10_us(50);
////					period = tmu_6->read();
////				}
////			}
////			VFB0 = VFB_force + 0.5*LargeStep; // FB pin voltage at first turn-on. //
////
////			// Small steps //
////			// Search for first point of slope 2 //
////			SmallStep = 0.1e-3; // Small step //
////			VFB_force = VFB_force + 1.5*LargeStep; // Start above //
////			FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////			wait.delay_10_us(50);
////			period = 0;
////			toff = 0;
////			while (VFB_force > (FBcv - 40e-3) )
////			{
////				VFB_force -= SmallStep;
////				FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////				wait.delay_10_us(50);
////				tmu_6->arm(); 
////				wait.delay_10_us(50);
////				period = tmu_6->read();
////				toff = period - g_TonMax_S;
////				if (toff > 0 && toff < 140e-6) // Check again to make sure //
////				{
////					tmu_6->arm(); 
////					wait.delay_10_us(50);
////					period = tmu_6->read();
////					toff = period - g_TonMax_S;
////				}
////				if (toff > 0 && toff < 140e-6)
////					break;
////			}
////			Vesr_Vfb4_S = VFB_force + 0.5*SmallStep;
////			Vesr_DeltaT4_S = toff;
////
////			// Small steps //
////			// Search for 2nd point of slope 2 //
////			SmallStep = 0.1e-3; // Small step //
////			VFB_force = Vesr_Vfb4_S + SmallStep; // Start above //
////			FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////			wait.delay_10_us(50);
////			period = 0;
////			toff = 0;
////			while (VFB_force > (FBcv - 40e-3) )
////			{
////				VFB_force -= SmallStep;
////				FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////				wait.delay_10_us(50);
////				tmu_6->arm(); 
////				wait.delay_10_us(50);
////				period = tmu_6->read();
////				toff = period - g_TonMax_S;
////				if (toff > 0 && toff < 20e-6)
////					break;
////			}
////			Vesr_Vfb3_S = VFB_force + 0.5*SmallStep;
////			Vesr_DeltaT3_S = toff;
////
////			// Calculate slope 2 //
////			Vesr_slope2_S = ( (Vesr_Vfb4_S - Vesr_Vfb3_S)/ (Vesr_DeltaT4_S - Vesr_DeltaT3_S) ) *1e-6; // V/us //
////
////
////			// Vout //
////			VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
////			//VO_dvi->set_current(VO_ch, 3e-3, RANGE_300_MA); // DVI_9_0 //
////
////			// Search for slope 1 //
////			// Find the starting point for slope.  Starting point is VFB where toffMin starts to change. //
////			tmu_6->start_holdoff(20,true); // Use holdoff to average 128 cycles, remove jitter 
////			tmu_6->stop_holdoff(128,true);
////			wait.delay_10_us(50);
////			period = 0;
////			toff = 0;
////			toff_initial = 0;
////			VFB_force = FBcv - 100e-3; // Start below //
////			FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2
////			wait.delay_10_us(100);
////			tmu_6->arm(); 
////			wait.delay_10_us(330); // Wait for 128 cycles //
////			period = tmu_6->read();
////			period = period/128; // Use holdoff to average 128 cycles, remove jitter //
////			toff_initial = period - g_TonMax_S;
////
////			// Search for starting point //
////			toff_Delta = -9999; // Initialize //
////			StepValue = 3e-3;
////			//toff_Threshold = 0.04e-6;
////			toff_Threshold = 0.25e-6;
////			//while(toff_Delta < toff_Threshold && VFB_force < 1.5)
////			//while( toff_Delta < toff_Threshold && VFB_force < 1.5 )
////			//while( toff < g_ToffMin_s )
////			while( VFB_force < 1.5 )
////			{
////				VFB_force = VFB_force + StepValue;
////				FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2
////				wait.delay_10_us(50);
////				tmu_6->arm(); 
////				wait.delay_10_us(330); // Wait for 128 cycles //
////				period = tmu_6->read();
////				period = period/128; // Use holdoff to average 128 cycles, remove jitter //
////				toff = period - g_TonMax_S;
////				toff_Delta = toff - toff_initial;
////				//if(VFB_force > 1.2 && toff_Delta > toff_Threshold) // Check again to make sure //
////				//if(toff_Delta > toff_Threshold) // Check again to make sure //
////				if(toff_Delta > toff_Threshold && VFB_force > FB_start_thresh) // Check again to make sure //
////				{
////					tmu_6->arm(); 
////					wait.delay_10_us(330); // Wait for 128 cycles //
////					period = tmu_6->read();
////					period = period/128; // Use holdoff to average 128 cycles, remove jitter //
////					toff = period - g_TonMax_S;
////					toff_Delta = toff - toff_initial;
////					//if(VFB_force > 1.2 && toff_Delta > toff_Threshold)
////					//if(toff_Delta > toff_Threshold)
////					if(toff_Delta > toff_Threshold && VFB_force > FB_start_thresh)
////						break;
////				}
////			}
////		
////			// Get all the VFB and toff points //
////			Vesr_Vfb1_Initial = 0;
////			for (i=0;i<15;i++)
////			{
////				Vesr_Vfb_temp[i] = 0;
////				Vesr_DeltaT_temp[i] = 0;
////			}
////			for (i=0;i<50;i++)
////			{
////				Vesr_slope_temp[i] = 0;
////			}
////			j = 0;
////			NumPoints = 7;
////			Vesr_Vfb1_Initial = VFB_force;
////			tmu_6->start_holdoff(20,true); // Use holdoff to average 128 cycles, remove jitter 
////			tmu_6->stop_holdoff(128,true);
////			wait.delay_10_us(50);
////			for (i=1;i<(NumPoints+1);i++)
////			{
////				/*
////				if (i==1)
////					VFB_force = Vesr_Vfb1_Initial * 1.002;
////				if (i==2)
////					VFB_force = Vesr_Vfb1_Initial * 1.004286;
////				if (i==3)
////					VFB_force = Vesr_Vfb1_Initial * 1.006571;
////				if (i==4)
////					VFB_force = Vesr_Vfb1_Initial * 1.008857;
////				if (i==5)
////					VFB_force = Vesr_Vfb1_Initial * 1.011143;
////				if (i==6)
////					VFB_force = Vesr_Vfb1_Initial * 1.013429;
////				if (i==7)
////					VFB_force = Vesr_Vfb1_Initial * 1.015714;
////				if (i==8)
////					VFB_force = Vesr_Vfb1_Initial * 1.018;
////				*/
////
////				/*
////				if (i==1)	
////					VFB_force = Vesr_Vfb1_Initial * 1;
////				if (i==2)	
////					VFB_force = Vesr_Vfb1_Initial * 1.002571;
////				if (i==3)	
////					VFB_force = Vesr_Vfb1_Initial * 1.005142;
////				if (i==4)	
////					VFB_force = Vesr_Vfb1_Initial * 1.007714;
////				if (i==5)	
////					VFB_force = Vesr_Vfb1_Initial * 1.010285;
////				if (i==6)	
////					VFB_force = Vesr_Vfb1_Initial * 1.012857;
////				if (i==7)	
////					VFB_force = Vesr_Vfb1_Initial * 1.015428;
////				if (i==8)	
////					VFB_force = Vesr_Vfb1_Initial * 1.018;
////				*/
////
////				if (i==1)	
////					VFB_force = Vesr_Vfb1_Initial * 1;
////				if (i==2)	
////					VFB_force = Vesr_Vfb1_Initial * 1.003;
////				if (i==3)	
////					VFB_force = Vesr_Vfb1_Initial * 1.006;
////				if (i==4)	
////					VFB_force = Vesr_Vfb1_Initial * 1.009;
////				if (i==5)	
////					VFB_force = Vesr_Vfb1_Initial * 1.012;
////				if (i==6)	
////					VFB_force = Vesr_Vfb1_Initial * 1.015;
////				if (i==7)	
////					VFB_force = Vesr_Vfb1_Initial * 1.018;
////
////				FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2
////				wait.delay_10_us(50);
////				tmu_6->arm(); 
////				wait.delay_10_us(330); // Wait for 128 cycles //
////				period = tmu_6->read();
////				period = period/128; // Use holdoff to average 128 cycles, remove jitter //
////				toff = period - g_TonMax_S;
////				Vesr_Vfb_temp[i] = VFB_force;
////				Vesr_DeltaT_temp[i] = toff;
////			}
////
////			// Calculate the slope for each VFB,toff pair. //
////			// Find the max and min slope VFB,toff pairs //
////			for (i=0;i<50;i++)
////			{
////				OrigIndexLoc[i] = 0;
////			}
////			NumSlope = 0;
////			for(j=NumPoints;j>1;j--)
////			{
////				for (i=1;i<j;i++)
////				{
////					NumSlope++;
////					Vesr_slope_temp[NumSlope] = ( (Vesr_Vfb_temp[j] - Vesr_Vfb_temp[j-i])/ (Vesr_DeltaT_temp[j] - Vesr_DeltaT_temp[j-i]) ) *1e-6; // V/us //
////					OrigIndexLoc[NumSlope] = NumSlope; // Save index locations for later. //
////				}
////			}
////
////			// Put the slopes in ascending order. //
////			TempValue = 0;
////			SortDone = 0;
////			while (SortDone == 0)
////			{
////				SortDone = 1;
////				for(i=1;i<NumSlope;i++)
////				{
////					if (Vesr_slope_temp[i] > Vesr_slope_temp[i+1])
////					{
////						// Swap values //
////						TempValue = Vesr_slope_temp[i+1];
////						Vesr_slope_temp[i+1] = Vesr_slope_temp[i];
////						Vesr_slope_temp[i] = TempValue;
////
////						// Keep track of original index locations.  Needed later. //
////						TempValue = OrigIndexLoc[i+1];
////						OrigIndexLoc[i+1] = OrigIndexLoc[i];
////						OrigIndexLoc[i] = TempValue;
////						
////						// Flag of swap occured. //
////						SortDone = 0;
////					}
////				}
////			}
////
////			// Find the median slope, and corresponding VFB,toff pairs //
////			MedianIndex = NumSlope / 2;
////			//MedianIndex = NumSlope * 0.85;
////			Vesr_slope1_S = Vesr_slope_temp[MedianIndex];
////			NumSlope = 0;
////			for(j=NumPoints;j>1;j--)
////			{
////				for (i=1;i<j;i++)
////				{
////					NumSlope++;
////					if (NumSlope == OrigIndexLoc[MedianIndex])
////					{
////						Vesr_slope_temp[NumSlope] = ( (Vesr_Vfb_temp[j] - Vesr_Vfb_temp[j-i])/ (Vesr_DeltaT_temp[j] - Vesr_DeltaT_temp[j-i]) ) *1e-6; // V/us //
////						Vesr_Vfb2_S = Vesr_Vfb_temp[j];
////						Vesr_DeltaT2_S = Vesr_DeltaT_temp[j];
////						Vesr_Vfb1_S = Vesr_Vfb_temp[j-i];
////						Vesr_DeltaT1_S = Vesr_DeltaT_temp[j-i];
////					}
////					//Vesr_slope_temp[NumSlope] = ( (Vesr_Vfb_temp[j] - Vesr_Vfb_temp[j-i])/ (Vesr_DeltaT_temp[j] - Vesr_DeltaT_temp[j-i]) ) *1e-6; // V/us //
////				}
////			}
////
////			// Vesr_intcp1_S //
////			Vesr_intcp1_S = Vesr_Vfb2_S - (Vesr_slope1_S*Vesr_DeltaT2_S*1e6);
////
////			// Vesr_Peak_S //
////			//Vesr_Peak_S = VFB0 - (Vesr_Vfb2_S - (Vesr_slope1_S*Vesr_DeltaT2_S*1e6));
////			Vesr_Peak_S = FBcv - Vesr_intcp1_S;
////
////			// Vesr_intcp2_S //
////			Vesr_intcp2_S = Vesr_Vfb4_S - (Vesr_slope2_S*Vesr_DeltaT4_S);
////
////			// Vesr_Knee1_S //
////			// Finding knee point using with 2 equations and two unknowns using Vesr_slope1_S and Vesr_slope2_S. //
////			VFBX = ((Vesr_slope1_S*Vesr_slope2_S*(Vesr_DeltaT1_S-Vesr_DeltaT4_S)*1e6) + (Vesr_slope1_S*Vesr_Vfb4_S) - (Vesr_slope2_S*Vesr_Vfb1_S)) / (Vesr_slope1_S-Vesr_slope2_S);
////			Vesr_Knee1_S = VFB0 - VFBX;
////			//Vesr_Knee1_S = FBcv - VFBX;
////
////			// Vesr_Knee2_S //
////			// Finding knee point using just using VFB3. //
////			Vesr_Knee2_S = VFB0 - Vesr_Vfb3_S;
////			//Vesr_Knee2_S = FBcv - Vesr_Vfb3_S;
////
////			if (StepCount < 1)
////			{
////				// Check result then try higher on the curve if needed. //
////				UpperLimitSlope1 = (func.dlog->tests[A_Vesr_slope1_S].f_max_limit_val[0]);
////				LowerLimitSlope1 = (func.dlog->tests[A_Vesr_slope1_S].f_min_limit_val[0]);
////				UpperLimitPeakS = (func.dlog->tests[A_Vesr_Peak_S].f_max_limit_val[0]);
////				LowerLimitPeakS = (func.dlog->tests[A_Vesr_Peak_S].f_min_limit_val[0]);
////				if (Vesr_slope1_S < LowerLimitSlope1 || Vesr_slope1_S > UpperLimitSlope1 ||
////					Vesr_Peak_S < LowerLimitPeakS || Vesr_Peak_S > UpperLimitPeakS)
////				{
////					FB_start_thresh = 1.2;
////				}
////				else
////				{
////					StepCount = 99;
////				}
////			}
////			StepCount++;
////		}
////	}
////	
/////*
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Characterize Vesr adaptive: BEGIN //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	if(gTrim_SdwReg27_Trimops)	//Adaptive VESR
////	{
////		float VFB_thrsh = 0; 
////		int data_cnt=0;
////		double fb_val[1500]={0.0};
////		double Toff_val[1500]={0.0};
////		double t_meas = 0;
////		double avg_per = 0;
////
////		VFB_thrsh = FBcv;
////		data_cnt=0; 
////		t_meas=0;
////
////		//small step loop
////		for ( VFB_force = VFB_thrsh-40e-3;(t_meas < 50e-3) && (VFB_force < VFB_thrsh+0.2) && (data_cnt<1500); data_cnt++)
////		{
////			FB_ovi->set_voltage(FB_ch, VFB_force, RANGE_2_V); // OVI_1_2	
////
////			//Use hold off feature to average jitter out
////			tmu_6->arm(); 
////			wait.delay_10_us(2000);	//time to count cycles
////			t_meas = tmu_6->read();
////			//calculate average period
////			avg_per = t_meas/128;
////			Toff_val[data_cnt] = avg_per - g_TonMax_S; // FW Ton = Drain Toff
////			fb_val[data_cnt] = VFB_force;
////			VFB_force += 0.1e-3;
////		}
////		// Engineering sweep DAC.  Output to .txt file. //
////		float Arr1[1500] = {0};
////		float Arr2[1500] = {0};
////		float Arr3[1500] = {0}; // Not used //
////		float Arr4[1500] = {0}; // Not used //
////		float Arr5[1500] = {0}; // Not used //
////		for (i=0; i < data_cnt; i++)
////		{
////			Arr1[i] = fb_val[i];
////			Arr2[i] = Toff_val[i];
////		}
////		Data_To_Text_File(1500,"VesrAdaptive", "Vfb", Arr1, "Toff", Arr2, "NotUsed", Arr3, "NotUsed", Arr4, "NotUsed", Arr5);
////	}
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Characterize Vesr adaptive: END //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////*/
////
////	// Powerdown //
////	Mux20_Open_relay(K50); // Remove SR pin hard short to GND with relay //
////	Open_relay(K3);
////	tmu_6->start_holdoff(0,FALSE);
////	tmu_6->stop_holdoff(0,FALSE);
////	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain //
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
////	VPIN_ovi->connect(VPIN_ch);
////	Disconnect_InvSyn_IM();
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	wait.delay_10_us(20);
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	uVCCrampDown(0.5, 0, 0.1);
////	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	wait.delay_10_us(45); // prevent SR undershoot //
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
////	wait.delay_10_us(5);
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	wait.delay_10_us(20);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////	Open_relay(K12); 
////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2
////	//ddd_7->ddd_set_clock_period(Dclk_period);
////	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
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
////	PiDatalog(func, A_Vesr_Vfb1_S, Vesr_Vfb1_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_DeltaT1_S, Vesr_DeltaT1_S, 26, POWER_MICRO);
////	PiDatalog(func, A_Vesr_Vfb2_S, Vesr_Vfb2_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_DeltaT2_S, Vesr_DeltaT2_S, 26, POWER_MICRO);
////	PiDatalog(func, A_Vesr_Vfb3_S, Vesr_Vfb3_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_DeltaT3_S, Vesr_DeltaT3_S, 26, POWER_MICRO);
////	PiDatalog(func, A_Vesr_Vfb4_S, Vesr_Vfb4_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_DeltaT4_S, Vesr_DeltaT4_S, 26, POWER_MICRO);
////	PiDatalog(func, A_Vesr_slope1_S, Vesr_slope1_S, 26, POWER_MILLI);
////	PiDatalog(func, A_Vesr_intcp1_S, Vesr_intcp1_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_slope2_S, Vesr_slope2_S, 26, POWER_MILLI);
////	PiDatalog(func, A_Vesr_intcp2_S, Vesr_intcp2_S, 26, POWER_UNIT);
////	PiDatalog(func, A_Vesr_Knee1_S, Vesr_Knee1_S, 26, POWER_MILLI);
////	PiDatalog(func, A_Vesr_Knee2_S, Vesr_Knee2_S, 26, POWER_MILLI);
////	//PiDatalog(func, A_Vesr_Knee_S, Vesr_Knee_S, 26, POWER_MILLI);
////	PiDatalog(func, A_Vesr_Peak_S, Vesr_Peak_S, 26, POWER_MILLI);
////	
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		Vesr_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_Vesr_TT, Vesr_TT, 26, POWER_MILLI);
////	}
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
