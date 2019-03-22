//==============================================================================
// FOSC_Ton_ARST.cpp (User function)
// 
//    void FOSC_Ton_ARST_user_init(test_function& func)
//    void FOSC_Ton_ARST(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "FOSC_Ton_ARST.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void FOSC_Ton_ARST_user_init(test_function& func)
{
	FOSC_Ton_ARST_params *ours;
    ours = (FOSC_Ton_ARST_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void FOSC_Ton_ARST(test_function& func)
{
    // The two lines below must be the first two in the function.
    FOSC_Ton_ARST_params *ours;
    ours = (FOSC_Ton_ARST_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_FOSC_Ton_ARST, gFuncNum, 14, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_FOSC_Ton_ARST == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();
	
	// Declare Variables //
	//float FOSC_S = 0;
	float FOSC_Act_Chg_S = 0;
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //	
	//float iBPS =0.0;
	float tmeas =0.0; 
	float   ToffMin_s=0.0;	
	float	FOSC_P=0.0,
			FOSC_act_P=0.0,
			TonMax_P=0.0,
			DCmax_P=0,
			DCmax_S=0,
			tAR_On_NM_P=0.0,
			tAR_On_TM_P=0.0,
			tAR_Off_TM_P=0.0,
			fLB_audible_P=0.0, 
			fUB_audible_P=0.0,
			Result=0,
			TonMax1us_s	=0.0;

	int ILIM_Select = ILIM_NORM;

	float AR_disable_S=0;
	float TonMax_S=0;

	float tOVL_S=0,
		  fOVL=0,
		  tOVL_act=0,
		  //tOVL_Err_S=0,
		  tblock_S=0,
		  tOffmin_blk_dif=0;
	int	  Rep_cnt=0;
	float tmeas_Sum=0.0; 
	float Freq_at_TonMax_s = 0;
	int   lcnt =0, 
		  maxcnt =0, 
		  i=0;
	int	  Loff_aft_AR_P=0;
	int	  ARoff_P=0;
	int	  Loff_w_OT_P=0;
 
	float ARST_NM_starttime=0, 
		  ARST_NM_stoptime=0;
	float ARST_On_TM_starttime=0;
	float ARST_On_TM_stoptime=0;
	float ARST_Off_TM_starttime=0;
	float ARST_Off_TM_stoptime=0;
	float WAIT_n_LISTEN_NM_starttime=0, 
		  WAIT_n_LISTEN_NM_stoptime=0, 
		  tWL_NM_P=0, 
		  tElapse=0;
	float WAIT_n_LISTEN_TM_starttime=0, 
		  WAIT_n_LISTEN_TM_stoptime=0, 
		  tWL_TM_P=0;
	float tOV_filter_starttime=0, 
		  tOV_filter_stoptime=0, 
		  tOV_filter=0;
	float tDZwindow_90us=0, 
		  tDZwindow_55us=0,
		  tDZwindow_145us=0;
	float imeas=0;
	float TimeStart = 0;	
	float TimeStop = 0;
	float TimeDelta = 0;
	int FlagError = 0;
	int	count = 0;
	int MaxCount = 0;
	float	ChB_vrng=0.0;
	int		vrng_b	=0.0;
	float vstart = 0;
	float vstop = 0;
	float vstep = 0;
	int flagStartTimer = 0;
	int READ59_word[16] = {0};
	int WordArray[16] = {0};
	float tARskip_S = 0;
	float FOSC_TonARST_TT = 0;
	float BPS_curr = 0;
	//float Vmeas = 0;
	Pulse pulse;

	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);
	
	if (g_Char_Enable_P) // Characterization only.  Tested in test mode later for reduced test time in production. //
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		//		Wait and Listen Time (Primary)														
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		//Primary NM power-up (ON ~82ms, OFF ~2seconds)

		//Vpin set to 0V before PU (Low Jitter for ILIM_NORM if Primary in control)
		//VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);  
		//VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);

		//BPP set 0V
		//BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		//BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0
		//wait.delay_10_us(5);

		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(5);

		//Drain (>15V read anti-fuses)
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0	
		delay(3);

		VBPP_ramp_up(0.0, gVBPP_PV_final, 0.2);	// vstart, vstop, vstep	
		wait.delay_10_us(5);

		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
		wait.delay_10_us(1);

		VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.2, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(50);

		BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
		VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
		
		wait.delay_10_us(50);

		D_dvi->set_voltage(D_ch, 2.0, VOLT_10_RANGE); // DVI_11_0	(needed to reduce noise)
		wait.delay_10_us(10);

		WAIT_n_LISTEN_NM_starttime = mytimer.GetElapsedTime();
		tElapse = 0;
		tmeas	= 0;
		while(tElapse<120e-3 && tmeas < 1e-6)
		{
			tmu_6->arm();					
			wait.delay_10_us(10);			
			tmeas = tmu_6->read(30e-6);
			tElapse += 100e-6; // Estimated time per loop without the arm() and read() in account.
		}
		WAIT_n_LISTEN_NM_stoptime = mytimer.GetElapsedTime();
		tWL_NM_P = (WAIT_n_LISTEN_NM_stoptime - WAIT_n_LISTEN_NM_starttime)*1e-6;

		ARST_NM_starttime = WAIT_n_LISTEN_NM_stoptime;

		lcnt =0;
		maxcnt = 700;
		while (	tmeas > 1.0e-6 && lcnt < maxcnt )
		{
			tmu_6->arm(); // Device doing auto-restart
			wait.delay_10_us(15); // Wait for TMU
			tmeas = tmu_6->read(30e-6);	 
			lcnt ++;
		}
		ARST_NM_stoptime = mytimer.GetElapsedTime();

		if (ARST_NM_starttime <= 199 || ARST_NM_stoptime <= -199)
			tAR_On_NM_P =999.0 *1e-3;
		else
			tAR_On_NM_P = (ARST_NM_stoptime - ARST_NM_starttime) * 1e-6;

		// Powerdown
		D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0	
		wait.delay_10_us(20);
		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0
		wait.delay_10_us(20);
	}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Fosc_P: Primary Frequency Post Trim
	// Note: Primay frequency doesn't have Jitter
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	VBPP_Negative_Cycle();
	wait.delay_10_us(5);

	//update TMU setting to have better Freq measurement
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(128,TRUE);
	wait.delay_10_us(10);			

	//Setup Vpin for digital clocking
	ovi_1->disconnect(OVI_CHANNEL_1);

	// Initialize DDD
	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
	wait.delay_10_us(300);

	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

	tmu_6->arm();					
	delay(8); // Wait for TMU to trigger and to capture 128 cycles		
	tmeas = tmu_6->read(8e-3);	 
	tmeas/=128;
	if (tmeas>99)
		FOSC_P=999e3;
	else if (tmeas==0)	
		FOSC_P=-999e3;	
	else
		FOSC_P=1/tmeas;

	if( gFosc_pt_P !=0)
		FOSC_act_P = (FOSC_P/gFosc_pt_P -1)*100;
	else 
		FOSC_act_P = 999.0;

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// TonMax_P: Primary Control 							
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(1.8,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(5);
	tmeas =0.0;
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(5);				// Wait for TMU
	tmeas+= tmu_6->read();	
	TonMax_P = tmeas;

	DCmax_P = (TonMax_P / (1/FOSC_P))*100.0; //datalog in percentage

	// Power down primary switching
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0	
	VBPP_ramp_down(3, 0.0, 0.05);
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2 Stop device from switching	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE); // DVI_9_1
	Open_relay(K12);
	VPIN_ovi->connect(VPIN_ch);
	wait.delay_10_us(50);

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//				TonMax_1us with secondary in control															//
	//  - Devices with the FW_peak_20us_timer feature will require trimming DOPL bit.								//
	//  - If DOPL bit is not trimmed, Toff will be ~22us.															//
	//  - Modify Hardware to keep FW stay below GND so FW_Peak_20us_timer feature will not be triggered.			//
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//					Fosc_S: Secondary Frequency	Post Trim
	// Note: Secondary frequency has Jitter
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	VBPP_Negative_Cycle();

	// Drain //
	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(1.1, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
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
	//SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50);

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);

	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.15, VOLT_5_RANGE);

	// Adjust invSYNC reference at hot //
	if (g_OPCODE==4300 || g_OPCODE==4500)
	{
		if (!strnicmp(Part_ID_LimitSet, "INN3368", 7) ||
			!strnicmp(Part_ID_LimitSet, "SC1738", 6))
		{
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.7, VOLT_20_RANGE);	// OVI_1_4	
		}
	}

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

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

	Write_Word(g_TM_ANA, 0x0120, NObin, HEX);

	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
	wait.delay_10_us(100);

	// Powerup primary in test mode 1. //
	VBPP_Power_Up_w_Test_Mode(gTM1_p,ILIM_NORM);

	// Handshake will happen right after 'wait & listen' is done. //

	// Wait for 'wait & listen' to finish. // 
	wait.delay_10_us(350);

	// Bring FB pin or Vout voltage up to stop switching.  fOVL fault will occur if secondary 
	// switches above fOVL frequency for tAR- so, need to reset the tAR timer here 
	// to give enougn time to measure frequency. //
	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2	
	wait.delay_10_us(50);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// Drop FB to start switching. //
	FB_ovi->set_voltage(FB_ch, 1.0, RANGE_2_V); // OVI_1_2	
	wait.delay_10_us(10);
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(128,TRUE);
	tmu_6->arm();
	wait.delay_10_us(150); // Wait for TMU to trigger and to capture 128 cycles (need at least 1280us wait if 10us period)
	tmeas = tmu_6->read(1.5e-3);	 
	tmeas/=128;
	if (tmeas != 0)
			g_FOSC_S = 1/tmeas;
		else
			g_FOSC_S = 0.0;

	// Only calculate if preTrim was measured. //
	if (g_Trim_Enable_P == 1)
		FOSC_Act_Chg_S = ((g_FOSC_S - gFOSC_pt_S) / gFOSC_pt_S)*100; // In percent //

	//Ton setup for TMU
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->stop_trigger_setup(0.3,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(5); // Wait for TMU

	tmeas		= 0.0;
	tmeas_Sum	= 0.0;
	for(lcnt=0;lcnt<2;lcnt++)
	{
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(5);				// Wait for TMU
		tmeas = tmu_6->read(50e-6);
		tmeas_Sum += tmeas;
	}
	TonMax1us_s = tmeas_Sum/2.0;

	// Powerdown //
//	Mux20_Open_relay(K50);
//	Open_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39);
//	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain
	BPP_ovi->set_voltage(BPP_ch, 3, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(3);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(3, 0, 0.3);
	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	Disconnect_InvSyn_IM();
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
	wait.delay_10_us(140);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
//	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	//wait.delay_10_us(45); // prevent SR undershoot //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(5);
//	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	VBD_dvi->set_voltage(VBD_ch, 4, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	FB_ovi->connect(2);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_5_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//					TonMax: Secondary Control Post Trim
	//					DCMax : Secondary Control Maximum duty cycle
	//					ToffMax-S:	   Secondary Control Max off time
	//					tAR_On_NM_P: Secondary controlled 64ms ARST on time.
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPP cycle //
	VBPP_Negative_Cycle();

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

	// Drain //
	Close_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
	tmu_6->start_trigger_setup(2.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(3.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(10,TRUE);
	tmu_6->stop_holdoff(128,TRUE);

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	//VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
	//Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
	//wait.delay_10_us(300);
	//ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);

	// V pin //
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
	wait.delay_10_us(300);
	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //

	// FW //
	//Connect_InvSyn_IM(Low_Load_Vd_Input);

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
	
	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);
InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4

	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.2, VOLT_5_RANGE);
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.7, VOLT_5_RANGE);
	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);
	
	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	
	// FB (COMP) //
	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 3.3; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);

	// SDA //
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
	//Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	//ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	//ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	//Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	//Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	//ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// Primary TM5 bypass Wait and Listen power up //
//	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);

BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);

//	wait.delay_10_us(50);
wait.delay_10_us(70);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// Measure frequency //
	tmu_6->arm();		
	wait.delay_10_us(300);  // Wait for TMU to capture all 128 cycles
	tmeas = tmu_6->read();
	tmeas/=128;
	Freq_at_TonMax_s = 1/tmeas;

	// Measure maximum ontime //
	tmu_6->start_trigger_setup(3.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(1,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(5);

	tmeas_Sum = 0;
	for (i=0;i<5;i++)
	{

	tmu_6->arm();						
	wait.delay_10_us(10);				
	tmeas = tmu_6->read();
	tmeas_Sum += tmeas;
	}

	//TonMax_S = tmeas;
	TonMax_S = tmeas_Sum / 5;
	g_TonMax_S = TonMax_S;	// Save for later use
	ToffMin_s = 1/Freq_at_TonMax_s - TonMax_S;
	g_ToffMin_s = ToffMin_s; // Save for later //
	DCmax_S = 100 * TonMax_S/(1/Freq_at_TonMax_s);


	// Powerdown //
//	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//	Open_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//	Mux20_Open_relay(K50); // SR pin GND //
	Disconnect_InvSyn_IM();
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.3);
	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
	wait.delay_10_us(10);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(95);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
	VBPS_ramp_down(4, 0, 200e-3);
//	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
	wait.delay_10_us(200);

	// +++++++++++++++++++++++++ TESTMODE PRIMARY +++++++++++++++++++++++++++++++++ //
	//					ARST_On_Tmode:  Secondary controlled 2ms ARST on time.
	//					tAR_Off_TM_P: Secondary controlled 64ms ARST on time.	
	//  Timing: TM1 gives 32x faster									
	//			- Wait and Listen after power-up.	(~2.7ms)	
	//			- Switching On Time.				(~2.7ms)
	//			- Switching Off Time.				(~64.ms)
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(1.4,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	delay(3);
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	

	// Primary power up with TM1 
	
	// Drain = 0V
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(5);

	// UV pin (Vpin) set to 0V before PU
	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);  
	VPIN_ovi->set_current(VPIN_ch, 20e-3, RANGE_30_MA);	
	
	// BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(5);

	VBPP_ramp_up(0, gVBPP_PV_final, 0.2); // This ramp seems important to start from 0V, else not repeatable.
	
	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1); // vstart, vstop, vstep	
	wait.delay_10_us(3); // 1.0 uF (ILIM) 30us
	wait.delay_10_us(1); // Delay is critical for 1.8A device.  w/o 10us, ILIM read 70mA lower and not as repeatable.
	VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.25, 0.1); // vstart, vstop, vstep	
	wait.delay_10_us(10);

	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	//VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT); // OVI_1_0 //
	vstart = gVBPP_M_Init-200e-3;
	vstop = gVBPP_P_final;
	vstep = 10e-3;
	flagStartTimer = 0;

	//while( vstart < (vstop-vstep) ) // Ramp up VBPP to reduce overshoot
	while( vstart < vstop ) // Ramp up VBPP to reduce overshoot
	{	
		vstart +=vstep;
		BPP_ovi->set_voltage(BPP_ch, vstart, RANGE_10_V); // OVI_1_0
		wait.delay_10_us(7);
		imeas = BPP_ovi->measure();

		// Wait and listen time starts as soon as the BPP is powered up 
		// which is indicated by BPP current jumping above 1mA //
		if (imeas > 0.001 && flagStartTimer ==0)
		{
			WAIT_n_LISTEN_TM_starttime = mytimer.GetElapsedTime();
			flagStartTimer = 1;
		}
	}	
	BPP_ovi->set_voltage(BPP_ch, vstop,	RANGE_10_V);	
	wait.delay_10_us(5);	

	//wait.delay_10_us(50);
	//VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.1); // vstart, vstop, vstep	
	D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, VOLT_5_RANGE); // DVI_11_0	

//	mytimer.Start();
//	WAIT_n_LISTEN_TM_starttime = mytimer.GetElapsedTime();
	tElapse = 0;
	tmeas = 0;
	while(tElapse<5e-3 && tmeas < 4e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(8);			
		tmeas = tmu_6->read(80e-6);
		tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
	}
	WAIT_n_LISTEN_TM_stoptime = mytimer.GetElapsedTime();
	tWL_TM_P = (WAIT_n_LISTEN_TM_stoptime - WAIT_n_LISTEN_TM_starttime)*1e-6;

	ARST_On_TM_starttime = WAIT_n_LISTEN_TM_stoptime;
	tElapse = 0;
	while(tElapse<4e-3 && tmeas > 1e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(8);	//Require minimum 80us for SAM,DSOFT bits trimmed device else 40us wait is enough
		tmeas = tmu_6->read(80e-6);
		tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
	}
	ARST_On_TM_stoptime = mytimer.GetElapsedTime();
	tAR_On_TM_P = (ARST_On_TM_stoptime - ARST_On_TM_starttime)*1e-6;

	ARST_Off_TM_starttime = ARST_On_TM_stoptime;
	tElapse = 0;
	while(tElapse<80e-3 && tmeas < 1e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(8);			
		tmeas = tmu_6->read(80e-6);
		tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
	}
	ARST_Off_TM_stoptime = mytimer.GetElapsedTime();
	tAR_Off_TM_P = (ARST_Off_TM_stoptime - ARST_Off_TM_starttime)*1e-6;

	// Powerdown //
//	Open_relay(K3);
 	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0	
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.2); // vstart, vstop, vstep	


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//					tOVL or fOVL (Fosc_Overload)							 //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Setup Digitizer //
	//Gage_pretrig_samples=1024; // Set up the Pre_Trigger sample to be 1024 for better trigger point.
	//Gage_init();
	g_SAMPLE_SIZE = GAGE_POST_4K;
	vrng_b = GAGE_PM_10_V;
	ChB_vrng = 5.6;

	// Channel B setup //
	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,g_SAMPLE_SIZE); 
	gage_input_control_xp (GAGE_CHAN_B, // channel
						   GAGE_INPUT_ENABLE, // enable / disable
						   GAGE_DC, // coupling
						   vrng_b|GAGE_1_MOHM_INPUT); // range, impedance
	gage_trigger_control_xp (GAGE_CHAN_B, // trigger source
							 GAGE_DC, // coupling for ext trig
							 vrng_b, // range for CHA trigger
							 GAGE_NEGATIVE, // slope
							 4.5, // 1.0V trigger level 
	   						 g_SAMPLE_SIZE); // 20ns * GAGE_WAVEFORM_BUFFER_SIZE

	// tOVL or fOVL (Fosc_Overload) //
	Close_relay(K3);
	VBPP_Negative_Cycle();
	wait.delay_10_us(300);

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

	// Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_10_RANGE); // OVI_1_3 Account for one diode drop
	delay(1);

	// Drain //
	Close_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->connect(VPIN_ch);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);
InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
	
	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
	//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_MA); // OVI_3_0, float, let DDD control //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_MA); // OVI_3_1, float, let DDD control //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// If the COMP(FB) was disconnected with trim, need to reconnect here for controlling 
	// switching freqeuncy with FB pin //
	if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
	{
		////// Read out contents of shadow register.  Can't overwrite shadow register. //
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
	wait.delay_10_us(200);

	// Setup DDD //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);

	// Vpin to DDD //
	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
	wait.delay_10_us(200);
	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
	wait.delay_10_us(200);

	// Primary TM5 bypass Wait and Listen power up
	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//Power_Up_Primary_BypassWL_TM5_New(ILIM_NORM);

//BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);

//wait.delay_10_us(70);

	wait.delay_10_us(30);
	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
	wait.delay_10_us(30);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// FB setup //	
	// DDD level //
	g_DDD_High = 1.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
	wait.delay_10_us(10);
	Close_relay(K17); // Connect FB to DDD_2.  Disconnect FB from ovi. //
	wait.delay_10_us(200);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2

	// Connect Vpin back to OVI //
	VPIN_ovi->connect(VPIN_ch);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);  
	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA); 

	// Connect Vpin to RDSon buffer circuit. //
	Close_relay(K35);
	wait.delay_10_us(100);

	// Setup to measure tOVL from Vpin
	Open_relay(K12); // disconnect DDD7_1	from Vpin(UV)	pin
	Close_relay(KC5C); // VPIN_OVI to 15Kohm to UV pin
	Close_relay(KC6C); // UV pin to 330ohm to TMU_HIZ_DUT3
	wait.delay_10_us(300);
	VPIN_ovi->set_voltage(VPIN_ch, 5.0, RANGE_10_V);  
	wait.delay_10_us(10);

	// Setup FB High/Low switching thresholds
	// DDD level //
	g_DDD_Low = 1.0; // Save current value //
	g_DDD_High = 1.5; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
	wait.delay_10_us(50);
	Gage_Start_Capture(  );

	// Initiate the first pattern of tOVL to get rid of all of the noise before tmu arm()
	ddd_7->ddd_run_pattern(FB_tOVL_start,FB_tOVL_stop);
	wait.delay_10_us(25); // HOT debug
	Gage_Wait_For_Capture_Complete();

	// Disable Vpin
	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);  
	wait.delay_10_us(10);
	Open_relay(K17);
	Open_relay(KC5C); // VPIN_OVI to 15Kohm to UV pin
	Open_relay(KC6C); // UV pin to 330ohm to TMU_HIZ_DUT3
	tmu_6->open_relay(TMU_HIZ_DUT3);	
	Open_relay(K35);

	// Powerdown //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	BC_ovi->set_voltage(BC_ch, 0,VOLT_10_RANGE); // OVI_1_3
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Disconnect_InvSyn_IM();
//	Mux20_Open_relay(K50);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.5);
	wait.delay_10_us(10);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//	VBD_dvi->set_voltage(VBD_ch, 5, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Search result //
	g_Save_Awav_TextDebug_ALL = 0;
	Gage_Find_tOVL(&tOVL_S);
	g_Save_Awav_TextDebug_ALL = 0;
	fOVL = 1/tOVL_S;
	//tOVL_Err_S = ( (tOVL_S/g_tOVL_TARGET_Trimops) - 1 ) * 100.0;

	// tOVL_act
	//if(tOVL_S > 99.0)
	//	tOVL_S/=1e6;	
	if( g_tOVL_Pt !=0 )
		tOVL_act = (tOVL_S/g_tOVL_Pt -1)*100;
	else 
		tOVL_act = 999.0;

	//Gage_pretrig_samples=64; // Reset the Pre_Trigger Samples back to defaul at 64.
	//Gage_init() ;
	

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//					Audible Noise START
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Prevent switching at frequencies from 7khz to 11khz.  This is to suppress noise resulting from the cavity resonant frequency 
	// of the transformer.  If any switching request comes 90us to 145us after 1 switching request, all of these requests will be denied.
	// After this "deadzone" window has elapsed, pulses outside of this window will be honored, but RTM will be frozen (meaning ILIM fixed) 
	// until after 2 switching pulses.

	// The deadzone window has been brought out and observable on VPIN.  See ObserveMode for the addressing.  
	// A straight forward way to test this would be to also do this during the ILIM test, so we are in 2ndary control.  
	// Fire a pulse and keep quiet for about 200us to window on VPIN.

	// Simplified test procedure:
	// - Get into ObserveMode
	// - Get into 2ndary control
	// - fire a request pulse
	// - measure Dzwindow to be from 90us to 145us
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	// BPP cycle //
	VBPP_Negative_Cycle();

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

	// Drain //
	Close_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	tmu_6->close_relay(TMU_HIZ_DUT3);
	tmu_6->start_trigger_setup(4.6, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(4.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// Power up Primary //
	Close_relay(KC6C); // UV pin to 330ohm to TMU_HIZ_DUT3 //
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	VPIN_ovi->disconnect(VPIN_ch);	// Vpin disconnect OVI then below close K16 to connect to 5kohm to DDD-7-1
	Close_relay(K16);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
	wait.delay_10_us(300);
	Power_Up_Primary_Observe_Mode(gObserve_Mode_DZwindow);
	Open_relay(K16);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)

	// Setup Vpin //
	VPIN_ovi->connect(VPIN_ch);	
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_5_V);
	wait.delay_10_us(5);
	Close_relay(KC5C); // VPIN_OVI to 5Kohm to UV pin
	wait.delay_10_us(300);
	VPIN_ovi->set_voltage(VPIN_ch, 5.0, RANGE_5_V);
	wait.delay_10_us(20);

	// FW //
	Close_relay(K21); // FW to DDD-7-3 //
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
	
	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
	
	// FB (COMP) //
	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
	//SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_MA); // OVI_3_0, float, let DDD control //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	//SCL_ovi->set_current(SCL_ch, 0.1e-9, RANGE_30_MA); // OVI_3_1, float, let DDD control //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

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
	wait.delay_10_us(200);

	// Setup DDD //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// Setup DDD //
	// DDD level //
	g_DDD_Low = -0.5; // Save current value //
	g_DDD_High = 4.9; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	wait.delay_10_us(50);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
	wait.delay_10_us(10);

	// Three negative pulse on FW pin to give control to secondary //
	Force_Neg_Pulses_FW_DDD(4.9, -0.5);
	wait.delay_10_us(16);

	// Stop switching //
	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
	wait.delay_10_us(10);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// Connect InvSync Circuit //
	Connect_InvSyn_IM(Low_Vd_Input);
InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
	Open_relay(K21); // Disconnect FW from DDD-7-3 //
	wait.delay_10_us(200);

	// Bring up drain to observe switching //
	D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE); // DVI_11_0 //
	wait.delay_10_us(50);

	// Stop switching //
	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
	//wait.delay_10_us(50);

	// Setup for FB pin
	// DDD level //
	g_DDD_Low = 1.0; // Save current value //
	g_DDD_High = 1.5; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
	wait.delay_10_us(5);
	Close_relay(K17); // FB to DDD7_2
	wait.delay_10_us(300);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //

	// Require 11 pulses in order for dead zone signals to come up for revB2 and later silicons //
	for(i=1; i<=11; i++)
	{
		ddd_7->ddd_run_pattern(0, 40);
		wait.delay_10_us(30);	// Outside the 145us dead zone window //
	}

	// tmeas
	tmu_6->arm();			
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(0, 40);
	wait.delay_10_us(30); // Outside the 145us dead zone window
	tDZwindow_55us = tmu_6->read();

	// Setup to measure 90us, Time between device start switching (Drain High to Low) to Vpin toggle from Low to High (4V to 5V)
	tmu_6->close_relay(TMU_CHAN_A_DUT1); // Connect TMU CHA to FW
	tmu_6->start_trigger_setup(2.5, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// FW Channel_A_DUT1 to start trigger NEG
	tmu_6->stop_trigger_setup(4.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V); // Vpin HIZ-DUT-3 to stop trigger POS
	wait.delay_10_us(200);

	// tmeas
	tmu_6->arm();			
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(0, 40);
	wait.delay_10_us(50);
	tDZwindow_90us = tmu_6->read();
	if(tDZwindow_90us == 0)
		fLB_audible_P = 999e3;
	else
		fLB_audible_P = 1/tDZwindow_90us; // Audible noise frequency Lower Bound

	tDZwindow_145us = tDZwindow_90us + tDZwindow_55us;
	if(tDZwindow_145us == 0)
		fUB_audible_P = 999e3;
	else
		fUB_audible_P = 1/tDZwindow_145us; // Audible noise frequency Upper Bound

	// Powerdown //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	Open_relay(K3);
	Open_relay(KC6C);
	Open_relay(KC5C);
	Open_relay(K17); // FB, DDD7_2 //
	tmu_6->open_relay(TMU_HIZ_DUT3); // Vpin //
	tmu_6->open_relay(TMU_CHAN_A_DUT1); // TMU CHA, FW //
	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ, Drain //
	Mux20_Open_relay(K50); // SR pin GND//
	Disconnect_InvSyn_IM();
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.2);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
	wait.delay_10_us(5);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // Secondary vBPS_plus
	VBPS_ramp_down(3, 0, 200e-3);
//	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tblock-S //
	// After the drain turns off, secondary requests are ignored for tblock (~2usec).
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Drain //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Close_relay(K3); // Drain to dvi through pullup resistor. //
	
	// TMU setup //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	tmu_6->start_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->stop_trigger_setup(9.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// SR //
	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	dvi_13->close_relay(BUS_SENSE1);
	dvi_13->close_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_3_BUS3);

	// BPS //
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0, VOLT_50_RANGE);
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);

	// Setup Vpin for DDD clocking //
	ovi_1->disconnect(OVI_CHANNEL_1);
	
	// Setup DDD //
	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);
	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12); // Connect DDD7_1	to Vpin //
	wait.delay_10_us(300); // Wait for all relays //

	// Remove latchoff problem. //
	VBPP_Negative_Cycle();
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	wait.delay_10_us(10);

	// Primary Power up with normal mode and TM6 //
	VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep //	
	wait.delay_10_us(2);
	
	// Vpin pulse 6 times for test mode 6. //
	// In test mode 6 the Vpin becomes the receiver input. //
	ddd_7->ddd_run_pattern(Vpin_6clocks_start,Vpin_6clocks_stop);	
	wait.delay_10_us(5);

	// Drain to 40V, for normal mode. //	
	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE);
	wait.delay_10_us(60);

	// Set BPP //
	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
	wait.delay_10_us(5);

	// Set BPP //
	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	ILIM_Select = ILIM_NORM;
	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

	// Set BPP below VBP- //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(30);

	// Set BPP above VBP+ // 
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
	//wait.delay_10_us(30);

	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
	
	wait.delay_10_us(50);

	// Set drain to observe switching. //
	D_dvi->set_voltage(D_ch, 10, VOLT_10_RANGE);
	wait.delay_10_us(40);

	// Two pulses 30usec apart to give control to secondary. //
	ddd_7->ddd_run_pattern(Vpin_30usec_start,Vpin_30usec_stop);	
	wait.delay_10_us(10);
		
	// Setup TMU //
	tmu_6->arm();					
	wait.delay_10_us(10);	

	// One Vpin clock.  Drain turns on when Vpin goes high.  After 15usec tonMax, drain turns off, 
	// then turns on again after tblock has ended. //
	ddd_7->ddd_run_pattern(Vpin_one_30us_clock_start,Vpin_one_30us_clock_stop);
	wait.delay_10_us(10);
	tmeas = tmu_6->read();	
	tblock_S = tmeas;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tOffmin_blk_dif
	//
	// Go/NoGo test to make sure minimum offtime is greater than tblock time.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	tOffmin_blk_dif = ToffMin_s-tblock_S;
	if(tOffmin_blk_dif > 0)
		tOffmin_blk_dif = 1;
	else			
		tOffmin_blk_dif = 0;

	// Powerdown //
//	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain //
	Open_relay(K12);
//	Open_relay(K3);
	dvi_13->open_relay(BUS_SENSE1);
	dvi_13->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);
	ovi_1->connect(OVI_CHANNEL_1);
	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.2);
	SR_dvi2k->set_voltage(SR_ch, 1.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	wait.delay_10_us(5);
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(45);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //



	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tARskip_S
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPP cycle //
	VBPP_Negative_Cycle();

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

	// Drain //
	Close_relay(K3);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(0.7, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Connect_InvSyn_IM(Low_Load_Vd_Input);

	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.15, VOLT_5_RANGE);

	// Adjust invSYNC reference at hot //
	if (g_OPCODE==4300 || g_OPCODE==4500)
	{
		if (!strnicmp(Part_ID_LimitSet, "INN3368", 7) ||
			!strnicmp(Part_ID_LimitSet, "SC1738", 6))
		{
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.7, VOLT_20_RANGE);	// OVI_1_4	
		}
	}

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
	
	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	
	// FB (COMP) //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 3.3; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//wait.delay_10_us(100);

	// SDA //
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //

	// SCL //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //

	// Wait for relays //
	wait.delay_10_us(200);

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Turn on VBD drive //
	//Write_Byte(g_VBEN, 0x83, NObin, HEX); 

	// Powerup primary in test mode 1. //
	VBPP_Power_Up_w_Test_Mode(gTM1_p,ILIM_NORM);

	// Wait for 'wait & listen' to finish. // 
	wait.delay_10_us(350);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(10);

	// Stop switching //
	VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(5);
	TimeStart = mytimer.GetElapsedTime();
	count = 0;
	while (count < 500)
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read();
		if (tmeas > 0.1e-9) // Part started switching. //
			break;
		count++;
	}
	TimeStop = mytimer.GetElapsedTime();
	tARskip_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //

	// Powerdown //
	Open_relay(K3);
	tmu_6->open_relay(TMU_HIZ_DUT1);
	D_dvi->set_voltage(D_ch, 0, VOLT_5_RANGE); // DVI_11_0 //
	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	Mux20_Open_relay(K50); // SR pin GND//
	Disconnect_InvSyn_IM();
	FB_ovi->connect(2);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.2);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
	wait.delay_10_us(5);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // Secondary vBPS_plus
	VBPS_ramp_down(3, 0, 200e-3);
//	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //

	// DDD level //
	//g_DDD_Low = 0.0; // Save current value //
	//g_DDD_High = 4.0; // Save current value //
	//wait.delay_10_us(100);
	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Loff_aft_AR-P //
	// Feature Trim#19: Latch off after any AR.
	//
	// When this bit trimmed, any fault that causes AR will cause latchoff.  
	// Powerup in TM1 for faster test time.  Prevent secondary from taking control by keeping BPS < 4.4V.
	// After wait&listen (2.56ms), there will be switching for tAR (another 2.56msec).  
	// Without bit#19 trimmed, the part will then stop switching for tAROff (62msec) and then will start 
	// switching in tAR again.  But, with bit#19 trimmed, the part will stop switching and stay latched 
	// off and should never switch again.  So, in this test we just need to monitor switching to ensure 
	// that after the 62msec of tARoff, that switching does not start again. Check all the way out to 
	// 100msec.  The is a functional test.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_Loff_AR_P_Trimops)
	{
		// Initialize //
		Loff_aft_AR_P = -999;
		FlagError = 0;
		
		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();

		// Drain to 0V, for test mode 1. //
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		// SR //
		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0, VOLT_50_RANGE);
		IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up test mode 1. //
		VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep //	
		wait.delay_10_us(7);

		// Set BPP //
		VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
		wait.delay_10_us(5);

		// Set BPP //
		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// Set BPP below VBP- //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(30);

		// Set BPP above VBP+ // 
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);

		// Set Drain //
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE); // Keep below 3V to stay in test mode 1. //
		wait.delay_10_us(20);

		// Wait for wait&isten to expire and drain will start switching (~2.5msec). //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
		if(TimeDelta > .005) // Wait&Listen was too long. //
			FlagError = 1;

		// Wait for tAR to expire and drain will stop switching (~2.5msec). //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas < 0.1e-9) // Part stopped switching. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
		if(TimeDelta > .005) // tAR was too long. //
			FlagError = 1;

		// Make sure drain has latched off. Check for 100msec to make sure it does not start switching again. //
		// 100msec is a long test time.  Maybe for characterizaiton only. //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			TimeStop = mytimer.GetElapsedTime();
			TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
			if (tmeas > 0.1e-9) // Error. Part started switching.  Should have stayed latched off. //
			{
				FlagError = 1;
				break;
			}
			if (TimeDelta > 0.1) // Wait for 100msec. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //

		// Final result //
		if (FlagError)
			Loff_aft_AR_P = -999; // Fail. //
		else
			Loff_aft_AR_P = 1; // Pass. //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// AR_disable-S //
	// Feature Trim#20: Disable AR if not switching. //
	//
	// Bit#20 disables the AR function that transfers control to primary when secondary stops requesting 
	// for > tARSK (1.3s).  Note, secondary can still give up control with latchoff request.  
	// Powerup in TM1 to save test time.  With seconary control, stop making requests for more than 
	// tARSK (tARST = 1.3/32 = 40.6ms).  Use 62msec.  After waiting for 62msec, make sure the primary 
	// still responds to secondary requests (making sure secondary still has control).  This 
	// is a functional test.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_DisablAR_P_Trimops)
	{
		// Initialize //
		AR_disable_S = -999;
		FlagError = 0;
		
		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();	

		// Drain //
		D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		// SR //
		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0, VOLT_50_RANGE);
		IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);

		//Setup Vpin for digital clocking
		ovi_1->disconnect(OVI_CHANNEL_1);
		
		// Initialize DDD
		// DDD level //
		g_DDD_Low = 0.0; // Save current value //
		g_DDD_High = 4.0; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
		
		//Setup FB to connect to DDD //
		Close_relay(K17); // Connect FB to DD //	

		//Have InvSync circuit ready for communication
		Connect_InvSyn_IM(Low_Vd_Input);
		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1, VOLT_20_RANGE);	// OVI_1_4	
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up with TM1 and TM5 in same power up //
		VBPP_ramp_up(0.0, 5.0, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(20);
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(10);
		VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
		wait.delay_10_us(5);
		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// Set BPP below VBP- //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);

		// Reconnect Vpin OVI //
		VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA);
		ovi_1->connect(OVI_CHANNEL_1);
		Open_relay(K12);
		delay(2);
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
		wait.delay_10_us(50);

		// Drain set to 1.5V for switching.  Do not exceed 3V or will exit TM1. //
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE);
		wait.delay_10_us(30);

		// Set BPP above VBP+ // 
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);
		// Wait and listen should be skipped, and device should switching immediatly under primary control. //

		// Get FB ready for clocking. //
		// DDD level //
		g_DDD_Low = 0.8; // Save current value //
		g_DDD_High = gCV_FB_S*1.1; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
		wait.delay_10_us(5);		

		// Vout at 5V. // 	
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE);
		wait.delay_10_us(50);

		// BPS powerup //
		// When BPS is powered up, secondary will immediately handshake and take control. //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
		wait.delay_10_us(100);
		// Secondary should now have control. //

		// Issue FB pulses.  Make sure secondary has control. //
		wait.delay_10_us(350); // Must wait to make sure tAR time is finished, in case secondary failed to take control. //
		tmu_6->arm();
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(FB_100kHz_pulse_start_5X, FB_100kHz_pulse_stop_5X);
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if (tmeas < 0.1e-9) // No switching detected, secondary does not have control. //
			FlagError  = 1; // Error. //

		// Wait for longer than tARSK (wait for 62msec).
		TimeStart = mytimer.GetElapsedTime();
		wait.delay_10_us(6200);
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-3;

		// Issue FB pulses.  Make sure secondary still has control. //
		tmu_6->arm();
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(FB_100kHz_pulse_start_5X, FB_100kHz_pulse_stop_5X);
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if (tmeas < 0.1e-9) // No switching detected, secondary does not have control. //
			FlagError  = 1; // Error. //

		// Final result //
		if (FlagError)
			AR_disable_S = -999; // Fail //
		else
			AR_disable_S = TimeDelta; // Pass.  Datalog the wait time. //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Loff_w_OT-P //
	// Feature Trim#23: Latch off with OT. //
	//
	// Normally, when a part heat ups above the thermal shutdown threshold it stops switching, 
	// and it will start switching again when the temperature falls below the thermal shutdown 
	// threshold.  However, with bit#23 trimmed, when a part heats up above the thermal shutdown 
	// threshold it latches off and does not start switching again when the temperature falls 
	// below the thermal shutdown threshold.  To test this, go into OT (i.e.OVT) test mode and 
	// when Vpin is brought up to 5V (i.e. thermal shutdown is reduced to 19C) the part should 
	// latch off and stop switching, then when Vpin is set to 0V (i.e. thermal shutdown set to 
	// 60C) it should stay latched off.  Then, can make sure the latch off can be removed by 
	// either pulling VBPP below undervoltage then back above VBP+.  This is a functional test.
	//
	// OT test mode will only work at room temp. Cannot test this at hot.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_LoffwOT_P_Trimops)
	{
		// Initialize //
		Loff_w_OT_P = -999;
		FlagError = 0;

		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();	

		// Drain low for test mode 1. //
		D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		//Setup Vpin for digital clocking
		ovi_1->disconnect(OVI_CHANNEL_1);
		
		// Initialize DDD
		// DDD level //
		g_DDD_Low = 0.0; // Save current value //
		g_DDD_High = 4.0; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up with OT test mode and test mode 1. //
		VBPP_ramp_up(0.0, 5.0, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(2);
		
		// Vpin pulse 4 times for OT test mode. //
		ddd_7->ddd_run_pattern(Vpin_4clocks_start,Vpin_4clocks_stop);	
		wait.delay_10_us(5);

		// BP //
		VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
		wait.delay_10_us(5);
		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// Set BPP below VBP- //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);

		// Reconnect Vpin OVI //
		VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA);
		ovi_1->connect(OVI_CHANNEL_1);
		Open_relay(K12);
		delay(2);
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
		wait.delay_10_us(50);

		// Drain set to 1.5V for switching.  Do not exceed 3V or will exit test mode 1. //
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE);
		wait.delay_10_us(30);

		// Set BPP above VBP+ // 
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);

		// Wait for wait&listen to finish and drain will start switching (~2.5msec). //
		count = 0;
		MaxCount = 50;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Raise Vpin to 5V to reduce OT threshold to 19C. //
		VPIN_ovi->set_voltage(VPIN_ch, 5, RANGE_10_V);
		wait.delay_10_us(15);

		// Make sure part stopped switching //
		count = 0;
		MaxCount = 10;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Error. Part still switching. //
			{
				FlagError = 1;
				break;
			}
			count++;
		}
		
		// Bring Vpin back to 0V to increase OT theshold back to 60C. //
		VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);
		wait.delay_10_us(20);

		// Make sure part is still NOT switching //
		count = 0;
		MaxCount = 10;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Error. Part still switching. //
			{
				FlagError = 1;
				break;
			}
			count++;
		}

		// Reset latch-off condition to make sure part start switching again. //
		VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init - 0.200, 0.1);
		VBPP_ramp_up(gVBPP_M_Init - 0.200, gVBPP_P_final, 0.1);

		// Make sure part is now switching //
		// After part comes out of latch-off, it goes into wait&listen for ~2.5msec and then starts switching. //
		count = 0;
		MaxCount = 50;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Final result //
		if (FlagError)
			Loff_w_OT_P = -999; // Fail //
		else
			Loff_w_OT_P = 1; // Pass //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ARoff-P //
	// Feature Trim#54: request AR //
	//
	// Bit#54 changes secondary triggered primary latchoff into auto-restart instead.  The part
	// should go into auto-restart instead of latchoff. 
	// Powerup in test mode 1.  Create an ISD BPS fault.  Make sure device starts switching again 
	// after auto-restart time (2s/32 = 62msec in test mode 1) making sure the part 
	// goes into auto-restart instead of staying in latchoff.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_AR_req_Trimops)
	{
		// Initialize //
		ARoff_P = -999;
		FlagError = 0;

		// Open all relays //
		Initialize_Relays();

		// Initialize Instruments //
		Initialize_Instruments();

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

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

		// Vout //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

		// FB (COMP) //
		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
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
//		Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
	Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //

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
//		Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//		Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//		Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //

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
		if (g_EE_ShadReg63 == 1) // bit[63]: trim_no_fb_pin //
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

		// Make sure drain starts switching. //
		count = 0;
		MaxCount = 10;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Force BPS ISD fault to trigger primary latchoff. //
		BPS_curr = gISD_S + 1.5e-3;
		if (BPS_curr > 15e-3)
			BPS_dvi->set_current(BPS_ch, 15e-3, RANGE_300_MA);
		else
			BPS_dvi->set_current(BPS_ch, BPS_curr, RANGE_300_MA);
		BPS_dvi->set_voltage(BPS_ch, 5.5, VOLT_10_RANGE);  // abs max 5.5V //

		// Wait until drain stops switching //
		count = 0;
		MaxCount = 100;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas < 0.1e-9) // Part stopped switching. //
			{
				break;
			}
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not stop switching. //

		// DDD level //
//		g_DDD_Low = 0.0; // Save current value //
//		wait.delay_10_us(100);
//		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution
//		wait.delay_10_us(100);
		VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE);

		// Power down BPS //
		VBPS_ramp_down(3, 0, 200e-3);

		// Make sure drain starts switching again after auto-restart offtime (~62msec). //
		count = 0;
		MaxCount = 1000;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Final result //
		if (FlagError)
			ARoff_P = -999; // Fail //
		else
			ARoff_P = 1; // Pass //

		// Powerdown //
		Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
		D_dvi->set_voltage(D_ch, 0.0, VOLT_5_RANGE); // DVI_11_0
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
//		FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
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
		//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		wait.delay_10_us(2);
		VBPS_ramp_down(3, 0, 150e-3);
		BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
		VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
		wait.delay_10_us(20);
		VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//		ddd_7->ddd_set_clock_period(Dclk_period);
//		ddd_7->ddd_set_voltage_ref(DDD_Vref);
		ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
		FB_ovi->connect(2);
		FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

		// DDD level //
//		g_DDD_Low = 0.0; // Save current value //
//		g_DDD_High = 4.0; // Save current value //
//		wait.delay_10_us(100);
//		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(200); // Wait for relays //
	}

	//Datalog
	PiDatalog(func, A_FOSC_P, FOSC_P, 14, POWER_KILO);
	if(g_Trim_Enable_P)
	{
		PiDatalog(func, A_FOSC_exp_P, gFOSC_exp_P, 14, POWER_UNIT);	
		PiDatalog(func, A_FOSC_act_P, FOSC_act_P, 14, POWER_UNIT);
	}
	PiDatalog(func, A_TonMax_P, TonMax_P, 22, POWER_MICRO);	
	PiDatalog(func, A_DCmax_P, DCmax_P, 22, POWER_UNIT);
	if (gTrim_Loff_AR_P_Trimops)
	{
		PiDatalog(func, A_Loff_aft_AR_P, Loff_aft_AR_P, 17, POWER_UNIT);
	}
	if (gTrim_AR_req_Trimops)
	{
		PiDatalog(func, A_ARoff_P, ARoff_P, 17, POWER_UNIT);
	}
	if (gTrim_LoffwOT_P_Trimops)
	{
		PiDatalog(func, A_Loff_w_OT_P, Loff_w_OT_P, 30, POWER_UNIT);
	}
	PiDatalog(func, A_FOSC_S, g_FOSC_S, 14, POWER_KILO);
	if (g_Trim_Enable_P == 1)
	{
		PiDatalog(func, A_FOSC_Act_Chg_S, FOSC_Act_Chg_S, 14, POWER_UNIT);	
	}
	//PiDatalog(func, A_DCmax_S, DCmax_S, 22, POWER_UNIT); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_DCmax_S, DCmax_S, 5, POWER_UNIT); // DEBUG ONLY!!! Change to bin5 for engineering. //
	if (gTrim_DisablAR_P_Trimops)
	{
		PiDatalog(func, A_AR_disable_S, AR_disable_S, 21, POWER_UNIT);
	}
	PiDatalog(func, A_TonMax_S, TonMax_S, 22, POWER_MICRO);	
	//PiDatalog(func, A_ToffMin_s, ToffMin_s, 22, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_ToffMin_s, ToffMin_s, 5, POWER_MICRO); // DEBUG ONLY!!! Change to bin5 for engineering. //
	PiDatalog(func, A_TonMax1us_s, TonMax1us_s, 22, POWER_MICRO);
	if (g_Char_Enable_P) // Characterization only.  Tested in test mode for reduced test time in production. //
	{
		PiDatalog(func, A_tAR_On_NM_P, tAR_On_NM_P, 21, POWER_MILLI);
	}
	PiDatalog(func, A_tAR_On_TM_P, tAR_On_TM_P, 21, POWER_MILLI);
	PiDatalog(func, A_tAR_Off_TM_P, tAR_Off_TM_P, 21, POWER_MILLI);
	PiDatalog(func, A_tOVL_S, tOVL_S, 14, POWER_MICRO);
	//PiDatalog(func, A_tOVL_Err_S, tOVL_Err_S, 14, POWER_UNIT);	
	if(g_Trim_Enable_P)
	{
		PiDatalog(func, A_tOVL_exp, g_tOVL_exp, 14, POWER_UNIT);
		PiDatalog(func, A_tOVL_act, tOVL_act, 14, POWER_UNIT);
	}
	PiDatalog(func, A_fOVL, fOVL, 14, POWER_KILO);
	if (g_Char_Enable_P) // Characterization only.  Tested in test mode for reduced test time in production. //
	{
		PiDatalog(func, A_tWL_NM_P, tWL_NM_P, 21, POWER_MILLI);
	}
	PiDatalog(func, A_tWL_TM_P, tWL_TM_P, 21, POWER_MILLI);
	PiDatalog(func, A_fLB_audible_P, fLB_audible_P, 14, POWER_KILO);
	PiDatalog(func, A_fUB_audible_P, fUB_audible_P, 14, POWER_KILO);
	PiDatalog(func, A_tblock_S, tblock_S, 28, POWER_MICRO);
	PiDatalog(func, A_tOffmin_blk_dif, tOffmin_blk_dif, 28, POWER_UNIT);	
	PiDatalog(func, A_tARskip_S, tARskip_S, 21, POWER_MILLI);
	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		FOSC_TonARST_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_FOSC_TonARST_TT, FOSC_TonARST_TT, 14, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;

	}
*/
}
