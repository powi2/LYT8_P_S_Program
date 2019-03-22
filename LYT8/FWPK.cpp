//==============================================================================
// FWPK.cpp (User function)
// 
//    void FWPK_user_init(test_function& func)
//    void FWPK(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "FWPK.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void FWPK_user_init(test_function& func)
{
	FWPK_params *ours;
    ours = (FWPK_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void FWPK(test_function& func)
{
    // The two lines below must be the first two in the function.
    FWPK_params *ours;
    ours = (FWPK_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_FWPK, gFuncNum, 28, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_FWPK == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	float tDableOn_300kHz =0.0;
	float tDableOn_1MHz =0.0;
	float FWPK_tDableOntime =0.0; 
	float FWPK_Timer =0.0; 
	float FWPK_4Ring =0.0; 
	float FWPK_DableOnHi4Ring =0.0;
	float FWPK_tVOxDble =0.0;
	float Dummy = 0;
	float Dummy2 = 0;
	float HS_Ring1V_FaultP =0.0;
	float MaxF_FaultP =0.0;
	float MinF_FaultP =0.0;
	float ChB_vrng=0.0;
	int vrng_b	=0.0;
	int TryNum = 0;
	int ValidResults = 0;
	float FWPK_TT = 0;
	float UpperLimit = 0;
	float LowerLimit = 0;
	int READ59_word[16] = {0};
	int WordArray[16] = {0};
	Pulse pulse; // External trigger pulse from dvi for debug //

	// Trimming DOPL bit will disable FWPK
	// FWPK disabled with DOPL bits trimmed //
	if(!g_EE_ShadReg22) // DOPL. bit[22]: trim_dopl //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// FWPK Switching START
		// FWPK with gage digitizer capture takes ~50ms test time.  PU + capture
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

		// ++++++++++++++++++++++++++++
		// 300kHz Half Ring Test
		// ++++++++++++++++++++++++++++
		g_SAMPLE_SIZE = GAGE_POST_8K;
	
		// Setup Digitizer //
		vrng_b = GAGE_PM_5_V;
		ChB_vrng = 5.0;

		// Channel B setup //
		Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,g_SAMPLE_SIZE); 
		gage_input_control_xp(GAGE_CHAN_B, // channel
							  GAGE_INPUT_ENABLE, // enable / disable
							  GAGE_DC, // coupling
							  vrng_b|GAGE_1_MOHM_INPUT); // range, impedance
		gage_trigger_control_xp(GAGE_CHAN_B, // trigger source
								GAGE_DC, // coupling for ext trig
								vrng_b, // range for CHA trigger
								GAGE_NEGATIVE, // slope
								1.0, // 1.0V trigger level 
	   							g_SAMPLE_SIZE); // 20ns * GAGE_WAVEFORM_BUFFER_SIZE


		// The FWPK tests are tricky since they are effectively done asynchronously without using the 
		// InvSyncCircuit. In test mode, the tDableON signal comes out on SR pin.  The required timing for 
		// the FW pin pulses can vary from part to part and therefore can occasionaly require more than one 
		// try to get the timing right.  Therefore, if it doesn't work the first time, then additional attempts 
		// are made using slighty modified FW pin pulse patterns. //

		// Negative cycle BPP pin //
		VBPP_Negative_Cycle();

		TryNum = 1;
		ValidResults = 0;
		while (ValidResults==0 && TryNum < 6) // Adjust FW peak pattern until correct pattern found //
		{
			// Negative cycle BPP pin //
//			VBPP_Negative_Cycle();

			// Open all relays //
//			Initialize_Relays();

			// Initialize Instruments //
//			Initialize_Instruments();

			// Set up Buffer Clamp
			BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA);
			BC_ovi->set_voltage(BC_ch, 5,VOLT_5_RANGE); // OVI_1_3 Account for one diode drop
				
			// Drain //
			//Close_relay(K3);
			D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
			D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //

			// BPP //
			BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

			// V pin //
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

			// FW //
			Close_relay(K18);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //

			// SR //
			// setup to measure signal come out of SR
			//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
			//SR_dvi2k->set_current(SR_ch, 2, RANGE_2_A); // DVI_13_1, dvi2k //
			SR_dvi2k->open_relay(CONN_SENSE1);
			SR_dvi2k->open_relay(CONN_FORCE1);
			Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
			//Close_relay(K26); // SR to Buffer for digitizer capture

			// BPS //
			BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
			BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

			// IS //
			IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

			// Vout //
			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //// Important to get correct FW pin time above Vout //
			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

			// FB (COMP) //
			FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //
			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

			// VBD //
			VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//			VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
			wait.delay_10_us(25); // Prevent glitch //
			VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

			// uVCC //
			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
			uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

			// DDD level //
			g_DDD_Low = 0.0; // Save current value //
			g_DDD_High = 3.3; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(g_DDDwait_b);

			// SDA //
			Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
			ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
			ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
			Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
			//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
			Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
			Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

			// SCL //
			Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
			//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
			ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

			// Set DDD for I2C. //
			ddd_7->ddd_set_clock_period(g_Dclk_I2C);
			ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
				
			// Wait for relays //
			wait.delay_10_us(200); 

			// Powerup secondary //
			BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
			wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

			// SR //
			SR_dvi2k->open_relay(CONN_SENSE1);
			SR_dvi2k->open_relay(CONN_FORCE1);
			//SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
			Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
			Close_relay(K26); // SR to Buffer for digitizer capture
			wait.delay_10_us(200); 

			// I2C secondary test mode //  
			Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
			Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

			// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
			// switching freqeuncy with FB pin //
			if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
			{
				// Read out contents of shadow register.  Can't overwrite shadow register. //
				//////
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

				// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
				WordArray[15] = 0;
				Write_Word(g_SREG3, NOhex, WordArray, BIN);
			}

			Write_Word(g_TM_ANA, 0x013C, NObin, HEX);

			Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
			
			Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
			//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

			// SR //
			//SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
			//Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
			//Close_relay(K26); // SR to Buffer for digitizer capture

			// Write the I2C command to connect the DableOn from FW pin Peak Switch to SR pin. //
			Write_Word(g_TM_SEL, 0x0004, NObin, HEX); // DableOn //  
			//Write_Word(g_TM_SEL, 0x0002, NObin, HEX); // SRO //
			//Write_Word(g_TM_SEL, 0x0006, NObin, HEX); // Pulse //

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

			// DDD setup //
			ddd_7->ddd_set_clock_period(Dclk_period);
			ddd_7->ddd_set_voltage_ref(DDD_Vref);

			// DDD level //
			g_DDD_Low = 0.5; // Save current value //
			g_DDD_High = 8; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(g_DDDwait_b);

			// Connect FW to DDD, but keep DDD HIZ for now, still let dvi control FW pin. //
			ddd_7->ddd_run_pattern(HIZallChannels_start, HIZallChannels_stop); // HIZ //
			wait.delay_10_us(10);
			Close_relay(K21); // FW to DDD-7-3 //
			wait.delay_10_us(300);

			// Gage_Start_Capture //
			Gage_Start_Capture(  );

			// Clock FW pin 3 times with dvi. 1st FW pulse to latch, then 2 pulses to handshake. //  		
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);

			// Float dvi on FW pin to let DDD control //
			FW_dvi->set_current(FW_ch, 0.1e-9, RANGE_3_MA); // DVI_11_1 //

			// 3 pulses on FW pin to simulate the ringing for FWPK programming.  Only one pulse is really 
			// needed to program, but use three to be sure.  Note the DDD high level goes above Vout and 
			// the DDD low level stays above ground.  The ring period should be 1/300kHz = 3.333us. So, 
			// the 1/2 ring period is 3.333/2 = 1.67us.  Therefore, the pulse widith of the ring at the 
			// Vout crossing should be 1.67us. //
			ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_start, FWPK_300kHz_Ring_stop);
			wait.delay_10_us(5);

			// Bring FB above CV to prevent secondary requests. //
			FB_ovi->set_voltage(FB_ch, 1.5, RANGE_5_V); // OVI_1_2 //

			// Get DDD ready for FW pulses below ground //
			ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

			// DDD level //
			g_DDD_Low = -1.0; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 		
			wait.delay_10_us(g_DDDwait_b);

			// Bring FB below CV to enable secondary requests //
			FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //

			// Send FW pin clocks and capture the FWPK waveforms //
			// DDD pattern chosen to avoid ToffMin violation //
			if (TryNum ==1)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start1_single, FWPK_test_pulses_stop1_single);
			}
			if (TryNum ==2)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start2_single, FWPK_test_pulses_stop2_single);
			}
			if (TryNum ==3)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start3_single, FWPK_test_pulses_stop3_single);
			}
			if (TryNum ==4)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start4_single, FWPK_test_pulses_stop4_single);
			}
			if (TryNum ==5)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start5_single, FWPK_test_pulses_stop5_single);
			}
			TryNum++;

			// Gage_End_Capture //
			Gage_Wait_For_Capture_Complete();

			g_Save_Awav_TextDebug_ALL = 0;
			Gage_Find_tDableOn(&tDableOn_300kHz, &FWPK_tVOxDble, &FWPK_Timer, 0);
			g_Save_Awav_TextDebug_ALL = 0;

			// Validate FW pin pattern //
			ValidResults = 1; // Initialize //
			//UpperLimit = (func.dlog->tests[A_tDableOn_300kHz_S].f_max_limit_val[0]);
			//LowerLimit = (func.dlog->tests[A_tDableOn_300kHz_S].f_min_limit_val[0]);
			UpperLimit = 435e-9;
			LowerLimit = 235e-9;
			if(tDableOn_300kHz < LowerLimit || tDableOn_300kHz > UpperLimit) // Value should be within reasonable range //
				ValidResults = 0;
			UpperLimit = (func.dlog->tests[A_FWPK_tVOxDble_S].f_max_limit_val[0]);
			LowerLimit = (func.dlog->tests[A_FWPK_tVOxDble_S].f_min_limit_val[0]);
			if(FWPK_tVOxDble < LowerLimit || FWPK_tVOxDble > UpperLimit)
				ValidResults = 0;
			UpperLimit = (func.dlog->tests[A_FWPK_Timer_S].f_max_limit_val[0]);
			LowerLimit = (func.dlog->tests[A_FWPK_Timer_S].f_min_limit_val[0]);
			if(FWPK_Timer < LowerLimit || FWPK_Timer > UpperLimit)
				ValidResults = 0;

			// Powerdown //
			SR_dvi2k->close_relay(CONN_SENSE1);
			SR_dvi2k->close_relay(CONN_FORCE1);
			tmu_6->open_relay(TMU_CHAN_B_DUT2); // Disconnect TMU CHB from SR
			//Open_relay(K3); // Drain //
			FW_dvi->set_voltage(FW_ch, 2, VOLT_2_RANGE); // DVI_11_1, prevent undershoot  //
			FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //
			Open_relay(K21); // FW DDD-7-3 
			Open_relay(K26);
			VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
			wait.delay_10_us(20);
//			uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//			uVCCrampDown(0.5, 0, 0.1);
			SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
			SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
			wait.delay_10_us(45); // prevent SR undershoot //
			FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
			FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
			BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
			BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
			wait.delay_10_us(5);
			SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//			VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//			VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
			wait.delay_10_us(20);
//			VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
			ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
			FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
			BC_ovi->set_voltage(BC_ch, 0, VOLT_5_RANGE);

			// DDD level //
			//g_DDD_Low = 0.0; // Save current value //
			//g_DDD_High = 4.0; // Save current value //
			//wait.delay_10_us(100);
			//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(200); // Wait for relays //
		}

		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// 1MHz Half Ring Test (tDable_ON_1MHz)
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		
		// The FWPK tests are tricky since they are effectively done asynchronously without using the 
		// InvSyncCircuit. In test mode, the tDableON signal comes out on SR pin.  The required timing for 
		// the FW pin pulses can vary from part to part and therefore can occasionaly require more than one 
		// try to get the timing right.  Therefore, if it doesn't work the first time, then additional attempts 
		// are made using slighty modified FW pin pulse patterns. //
		TryNum = 1;
		ValidResults = 0;
		while (ValidResults==0 && TryNum < 6) // Adjust FW peak pattern until correct pattern found //
		{
			// Negative cycle BPP pin //
//			VBPP_Negative_Cycle();

			// Open all relays //
//			Initialize_Relays();

			// Initialize Instruments //
//			Initialize_Instruments();

			// Set up Buffer Clamp
			BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA);
			BC_ovi->set_voltage(BC_ch, 5,VOLT_5_RANGE); // OVI_1_3 Account for one diode drop
				
			// Drain //
			//Close_relay(K3);
			D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
			D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //

			// BPP //
			BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

			// V pin //
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

			// FW //
			Close_relay(K18);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //

			// SR //
			// setup to measure signal come out of SR
			//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
			//SR_dvi2k->set_current(SR_ch, 2, RANGE_2_A); // DVI_13_1, dvi2k //
			Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
			//Close_relay(K26); // SR to Buffer for digitizer capture

			// BPS //
			BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
			BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

			// IS //
			IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
			IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

			// Vout //
			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

			// FB (COMP) //
			FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //
			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

			// VBD //
			VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//			VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
			wait.delay_10_us(25); // Prevent glitch //
			VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

			// uVCC //
			uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
			uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

			// DDD level //
			g_DDD_Low = 0.0; // Save current value //
			g_DDD_High = 3.3; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(g_DDDwait_b);

			// SDA //
			Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
			ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
			ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
			Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
			//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
			Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
			Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

			// SCL //
			Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
			//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_UA); // OVI_3_1, float, let DDD control //
			ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

			// Set DDD for I2C. //
			ddd_7->ddd_set_clock_period(g_Dclk_I2C);
			ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
				
			// Wait for relays //
			wait.delay_10_us(200); 

			// Powerup secondary //
			BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
			wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

			// SR //
			SR_dvi2k->open_relay(CONN_SENSE1);
			SR_dvi2k->open_relay(CONN_FORCE1);
			//SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
			Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
			Close_relay(K26); // SR to Buffer for digitizer capture
			wait.delay_10_us(200); 

			// I2C secondary test mode // 
			Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
			Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
			
			// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
			// switching freqeuncy with FB pin //
			if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
			{
				// Read out contents of shadow register.  Can't overwrite shadow register. //
				//////
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

				// bit[63]: trim_no_fb_pin, set to zero to connect COMP(FB) //
				WordArray[15] = 0;
				Write_Word(g_SREG3, NOhex, WordArray, BIN);
			}
		
			Write_Word(g_TM_ANA, 0x013C, NObin, HEX);
			
			Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
			
			Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
			//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

			// Float SR dvi //
		//	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

			// Write the I2C command to connect the DableOn from FW pin Peak Switch to SR pin. //
			Write_Word(g_TM_SEL, 0x0004, NObin, HEX); // DableOn //  
			//Write_Word(g_TM_SEL, 0x0002, NObin, HEX); // SRO //
			//Write_Word(g_TM_SEL, 0x0006, NObin, HEX); // Pulse //

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

			// DDD setup //
			ddd_7->ddd_set_clock_period(Dclk_period);
			ddd_7->ddd_set_voltage_ref(DDD_Vref);

			// DDD level //
			g_DDD_Low = 0.5; // Save current value //
			g_DDD_High = 9; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(g_DDDwait_b);

			// Vout setup //
			VO_dvi->set_voltage(VO_ch, 2.7, VOLT_5_RANGE); // DVI_9_0 // // Important to get correct FW pin time above Vout //

			// Connect FW to DDD, but keep DDD HIZ for now, still let dvi control FW pin. //
			ddd_7->ddd_run_pattern(HIZallChannels_start, HIZallChannels_stop); // HIZ //
			wait.delay_10_us(10);
			Close_relay(K21); // FW to DDD-7-3 //
			wait.delay_10_us(300);

			// Gage_Start_Capture //
			Gage_Start_Capture(  );

			// Clock FW pin 3 times with dvi. 1st FW pulse to latch, then 2 pulses to handshake. //  		
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);
			FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
			wait.delay_10_us(1);

			// Float dvi on FW pin to let DDD control //
			FW_dvi->set_current(FW_ch, 0.1e-9, RANGE_3_MA); // DVI_11_1 //

			// 3 pulses on FW pin to simulate the ringing for FWPK programming.  Only one pulse is really 
			// needed to program, but use three to be sure.  Note the DDD high level goes above Vout and 
			// the DDD low level stays above ground.  The ring period should be 1/1MHz = 1us. So, 
			// the 1/2 ring period is 1us/2 = 0.5us.  Therefore, the pulse widith of the ring at the 
			// Vout crossing should be 0.5us. //
			ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_start, FWPK_1MHz_Ring_stop);
			wait.delay_10_us(5);

			// Bring FB above CV to prevent secondary requests. //
			FB_ovi->set_voltage(FB_ch, 1.5, RANGE_5_V); // OVI_1_2 //

			// Get DDD ready for FW pulses below ground //
			ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

			// DDD level //
			g_DDD_Low = -1.0; // Save current value //
			wait.delay_10_us(g_DDDwait_b);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 	
			wait.delay_10_us(g_DDDwait_b);

			// Bring FB below CV to enable secondary requests //
			FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //
			//wait.delay_10_us(1);

			// Send FW pin clocks and capture the FWPK waveforms //
			// DDD pattern chosen to avoid ToffMin violation //
			if (TryNum ==1)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start1_single, FWPK_test_pulses_stop1_single);
				//if(g_ToffMin_s > 2.5e-6 && g_ToffMin_s < 3e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start1, FWPK_test_pulses_stop1);
				//else if(g_ToffMin_s > 2.999e-6 && g_ToffMin_s < 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start2, FWPK_test_pulses_stop2);
				//else if(g_ToffMin_s > 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start3, FWPK_test_pulses_stop3);
			}
			if (TryNum ==2)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start2_single, FWPK_test_pulses_stop2_single);
				//if(g_ToffMin_s > 2.5e-6 && g_ToffMin_s < 3e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start4, FWPK_test_pulses_stop4);
				//else if(g_ToffMin_s > 2.999e-6 && g_ToffMin_s < 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start5, FWPK_test_pulses_stop5);
				//else if(g_ToffMin_s > 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start6, FWPK_test_pulses_stop6);
			}
			if (TryNum ==3)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start3_single, FWPK_test_pulses_stop3_single);
				//if(g_ToffMin_s > 2.5e-6 && g_ToffMin_s < 3e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start7, FWPK_test_pulses_stop7);
				//else if(g_ToffMin_s > 2.999e-6 && g_ToffMin_s < 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start8, FWPK_test_pulses_stop8);
				//else if(g_ToffMin_s > 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start9, FWPK_test_pulses_stop9);
			}
			if (TryNum ==4)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start4_single, FWPK_test_pulses_stop4_single);
				//if(g_ToffMin_s > 2.5e-6 && g_ToffMin_s < 3e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start10, FWPK_test_pulses_stop10);
				//else if(g_ToffMin_s > 2.999e-6 && g_ToffMin_s < 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start11, FWPK_test_pulses_stop11);
				//else if(g_ToffMin_s > 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start12, FWPK_test_pulses_stop12);
			}
			if (TryNum ==5)
			{
				ddd_7->ddd_run_pattern(FWPK_test_pulses_start5_single, FWPK_test_pulses_stop5_single);
				//if(g_ToffMin_s > 2.5e-6 && g_ToffMin_s < 3e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start13, FWPK_test_pulses_stop13);
				//else if(g_ToffMin_s > 2.999e-6 && g_ToffMin_s < 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start14, FWPK_test_pulses_stop14);
				//else if(g_ToffMin_s > 3.5e-6)
				//	ddd_7->ddd_run_pattern(FWPK_test_pulses_start15, FWPK_test_pulses_stop15);
			}
			TryNum++;
		
			// Gage_End_Capture //
			Gage_Wait_For_Capture_Complete();

			g_Save_Awav_TextDebug_ALL = 1;
			Gage_Find_tDableOn(&tDableOn_1MHz, &Dummy, &Dummy2, 1);
			g_Save_Awav_TextDebug_ALL = 0;

			// Validate FW pin pattern //
			ValidResults = 1; // Initialize //
			UpperLimit = (func.dlog->tests[A_tDableOn_1MHz_S].f_max_limit_val[0]);
			LowerLimit = (func.dlog->tests[A_tDableOn_1MHz_S].f_min_limit_val[0]);
			if(tDableOn_1MHz < LowerLimit || tDableOn_1MHz > UpperLimit)
				ValidResults = 0;
			
			// Powerdown //
			SR_dvi2k->close_relay(CONN_SENSE1);
			SR_dvi2k->close_relay(CONN_FORCE1);
			tmu_6->open_relay(TMU_CHAN_B_DUT2); // Disconnect TMU CHB from SR
			//Open_relay(K3); // Drain //
			FW_dvi->set_voltage(FW_ch, 2, VOLT_2_RANGE); // DVI_11_1, prevent undershoot  //
			FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //
			Open_relay(K21); // FW DDD-7-3 
			Open_relay(K26);
			VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
			wait.delay_10_us(20);
//			uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//			uVCCrampDown(0.5, 0, 0.1);
			SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
			SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
			wait.delay_10_us(45); // prevent SR undershoot //
			FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
			FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
			BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
			BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
			wait.delay_10_us(5);
			SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//			VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//			VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
			wait.delay_10_us(20);
//			VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
			ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
			FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
			FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
			BC_ovi->set_voltage(BC_ch, 0, VOLT_5_RANGE);

			// DDD level //
			//g_DDD_Low = 0.0; // Save current value //
			//g_DDD_High = 4.0; // Save current value //
			//wait.delay_10_us(100);
			//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(200); // Wait for relays //
		}
		
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// HS_Ring1V_FaultP 
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Negative cycle BPP pin //
//		VBPP_Negative_Cycle();

		// Open all relays //
//		Initialize_Relays();

		// Initialize Instruments //
//		Initialize_Instruments();
			
		// Drain //
		D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
		D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA); // DVI_11_0 //

		// BPP //
		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

		// V pin //
		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

		// FW //
		Close_relay(K18);
		FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
		FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //

		// SR //
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
		SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

		// BPS //
		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

		// Vout //
		VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //// Important to get correct FW pin time above Vout //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

		// FB (COMP) //
		FB_ovi->disconnect(2);
		//FB_ovi->set_voltage(FB_ch, 1, RANGE_5_V); // OVI_1_2 //
		//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

		// VBD //
		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//		VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
		wait.delay_10_us(25); // Prevent glitch //
		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

		// uVCC //
		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

		// DDD level //
		g_DDD_Low = 0.0; // Save current value //
		g_DDD_High = 3.3; // Save current value //
		wait.delay_10_us(g_DDDwait_b);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait_b);

		// SDA //
		Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
		ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
		//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
		SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
		Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//		Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
	Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //

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

		// I2C secondary test mode //
//		Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//		Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
	DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //

//		Write_Word(g_TM_ANA, 0x013C, NObin, HEX);
	DSM_Write_Word(g_TM_ANA, 0x013C);
		
//		Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //
	DSM_Write_Byte(g_VBEN, 0x83); // Turn on VBD drive //
		
//		Write_Byte(g_FWPK_reg, 0x01, NObin, HEX); // Enable FW peak peak switch function. //
	DSM_Write_Byte(g_FWPK_reg, 0x01); // Enable FW peak peak switch function. //
		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

		// Float SR dvi, measure voltage //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k //

		// Write the I2C command to connect the DfuncOff FW pin Peak Switch Fault to SR pin. //
//		Write_Word(g_TM_SEL, 0x0008, NObin, HEX); // DfuncOff //  
	DSM_Write_Word(g_TM_SEL, 0x0008); // DfuncOff //  
		//Write_Word(g_TM_SEL, 0x0004, NObin, HEX); // DableOn // 
		//Write_Word(g_TM_SEL, 0x0002, NObin, HEX); // SRO //
		//Write_Word(g_TM_SEL, 0x0006, NObin, HEX); // Pulse //

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

		// DDD setup //
		ddd_7->ddd_set_clock_period(Dclk_period);
		ddd_7->ddd_set_voltage_ref(DDD_Vref);

		// DDD level //
		g_DDD_Low = 0.5; // Save current value //
		g_DDD_High = 3; // Save current value //
		wait.delay_10_us(g_DDDwait_b);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait_b);

		// Connect FW to DDD, but keep DDD HIZ for now, still let dvi control FW pin. //
		ddd_7->ddd_run_pattern(HIZallChannels_start, HIZallChannels_stop); // HIZ //
		wait.delay_10_us(10);
		Close_relay(K21); // FW to DDD-7-3 //
		wait.delay_10_us(300);

		// Clock FW pin 3 times with dvi. 1st FW pulse to latch, then 2 pulses to handshake. //  		
		FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		FW_dvi->set_voltage(FW_ch, 0.2, VOLT_2_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		FW_dvi->set_voltage(FW_ch, -0.7, VOLT_2_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);

		// Float dvi on FW pin to let DDD control //
		FW_dvi->set_current(FW_ch, 0.1e-9, RANGE_3_MA); // DVI_11_1 //

		// 3 pulses on FW pin to simulate the ringing for FWPK programming.  The pulses 
		// are set to be less than 1V above Vout and check if the fault triggers. //
		ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_start, FWPK_300kHz_Ring_stop);
		wait.delay_10_us(15);

		// Vout high to prevent switching, otherwise SR pin has glitches that can cause repeatability error. //
		//FB_ovi->set_voltage(FB_ch, 1.5, RANGE_5_V); // OVI_1_2 //
		VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(15);

		// If SR pin output is high, datalog HS_Ring1V_FaultP to be 1 //
		HS_Ring1V_FaultP = SR_dvi2k->measure();
		if(HS_Ring1V_FaultP > 2)
			HS_Ring1V_FaultP = 1; // Pass //
		else
			HS_Ring1V_FaultP = 0; // Fail //

		// Powerdown //
		tmu_6->open_relay(TMU_CHAN_B_DUT2); // Disconnect TMU CHB from SR
		FW_dvi->set_voltage(FW_ch, 2, VOLT_2_RANGE); // DVI_11_1, prevent undershoot  //
		FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //
		Open_relay(K21); // FW DDD-7-3 
		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(20);
		//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		//uVCCrampDown(0.5, 0, 0.1);
		SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
		SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		wait.delay_10_us(45); // prevent SR undershoot //
		FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
		FW_dvi->set_voltage(FW_ch, 0, VOLT_2_RANGE); // DVI_11_1 //
		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(5);
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
		//VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
		//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
		wait.delay_10_us(20);
		//VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
		ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
		FB_ovi->connect(2);
		FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

		// DDD level //
		//g_DDD_Low = 0.0; // Save current value //
		//g_DDD_High = 4.0; // Save current value //
		//wait.delay_10_us(100);
		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(200); // Wait for relays //


		// Datalog //
		PiDatalog(func, A_tDableOn_300kHz_S, tDableOn_300kHz, 28, POWER_NANO);
		PiDatalog(func, A_tDableOn_1MHz_S, tDableOn_1MHz, 28, POWER_NANO);
		PiDatalog(func, A_FWPK_Timer_S, FWPK_Timer, 28, POWER_MICRO);
		//PiDatalog(func, A_FWPK_4Rings_S, FWPK_4Ring, 28, POWER_UNIT);
		//PiDatalog(func, A_DableOnHi4Ring_S, FWPK_DableOnHi4Ring, 28, POWER_UNIT);
		PiDatalog(func, A_FWPK_tVOxDble_S, FWPK_tVOxDble, 28, POWER_MICRO);
		PiDatalog(func, A_HS_Ring1V_FaultP_S, HS_Ring1V_FaultP, 28, POWER_UNIT);
		//PiDatalog(func, A_MaxF_FaultP_S, MaxF_FaultP, 28, POWER_UNIT); // Disable MaxF_FaultP and MinF_FaultP per discussion with Qing. //
		//PiDatalog(func, A_MinF_FaultP_S, MinF_FaultP, 28, POWER_UNIT); // Disable MaxF_FaultP and MinF_FaultP per discussion with Qing. //
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		FWPK_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_FWPK_TT, FWPK_TT, 28, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}

*/
}
