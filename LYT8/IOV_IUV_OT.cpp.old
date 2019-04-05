//==============================================================================
// IOV_IUV_OT.cpp (User function)
// 
//    void IOV_IUV_OT_user_init(test_function& func)
//    void IOV_IUV_OT(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IOV_IUV_OT.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_IUV_OT_user_init(test_function& func)
{
	IOV_IUV_OT_params *ours;
    ours = (IOV_IUV_OT_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_IUV_OT(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_IUV_OT_params *ours;
    ours = (IOV_IUV_OT_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IOV_IUV_OT, gFuncNum, 24, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_IOV_IUV_OT == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	float iOVp = 0;
	float iOVm = 0; 
	float iUVp = 0; 
	float iUVm = 0;
	float iOV_plus =0; 
	float iOV_minus =0; 
	float iOVplus_start =0;
	float iOV_Hys =0;
	float tOV_P_S = 0;
	float iUV_minus =0;
	float iBPP_bled_S =0;
	float iBPP_bledOff_S =0;
	float iUV_plus =0;
	float iUV_Hys =0;
	float tUV_minus =0;
	float iOV_plus_err =0;
	float iOV_plus_exp =0;
	float iOV_plus_act =0;
	float i_start =0;
	float i_stop =0;
	float i_step =0;
	float i_VPIN =0;
	float i_Hys =0;
	float i_force =0;
	float tmeas =0;
	float LoopTime[100] ={0};
	float ifrc_UV[100] ={0};
	float ifrc_UVm_Time =0;
	float UVm_TimeTrack =0;
	float tUV_400ms_S =0;
	float tUV_M_counter_S = 0;
	bool SWITCHING =false;
	bool NO_SWITCHING =false;
	int count =0;
	int i =0;
	float TimeStart =0;	
	float TimeStop =0;
	float TimeDelta =0;
	float ExitTime =0;
	float stepDown =0;
	int loopCount =0;
	float BPPcurrent1 =0;
	float BPPcurrent2 =0;
	int ILIM_Select =ILIM_NORM;
	int WordArray[16] = {0};
	int READ59_word[16] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	float IOV_IUV_OT_TT = 0;
	float VcurrMeas = 0;
	Pulse pulse;
	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//					IUV, IOV test(s)																
	//																									
	//  Notes:  Both Testmode 1 & 2 enables "No Delay" response time for UV/OV test.					
	//          Since TM1 is 32x faster, we want to do this in TM2.									
	//																									
	//  Test Procedure:																				
	//  -	Primary TestMode2 power-up with VPIN set to 6V/80uA.										
	//		Expect Drain to be switching (Drain can set to 100mV like the PH device to lower the noise).
	//	 -	Ramp up iVPIN until Drain stop switching to find iOV-										
	//	 -  Ramp down iVPIN from iOV- until Drain start switching to find iOV+							
	//	 -  Ramp down further from iOV+ until Drain stop switching to find iUV-							
	//		Note: Require confirmation from design that TM2 did not disable UV delay (35ms)				
	//	 -  Ramp up from iUV- until Drain start switching to find iUV+									
	//																									
	//  Attention:																						
	//		If Primary in control, test has to be done within 64ms (switching ON time).					
	//		Otherwise, it will go into ARST.															
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	VBPP_Negative_Cycle();

	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

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
//Mux20_Close_relay(K66);
//mux_14->close_relay(MUX_2_GND);
//Close_relay(K74);

	// FW //
	// Only 1V on FW pin here to reduce current to BPS pin.  FW upto 4V after BPS brought up. //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// FW //
	wait.delay_10_us(5);
	FW_dvi->set_voltage(FW_ch, 4, VOLT_10_RANGE); // DVI_11_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// COMP //
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2 //
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
//	g_DDD_Low = 0.0; // Save current value //
//	g_DDD_High = 3.3; // Save current value //
//	wait.delay_10_us(100);
//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//	wait.delay_10_us(100);

	// SDA //
	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	SDA_ovi->set_current(SDA_ch, 0.1e-9, RANGE_30_UA); // OVI_3_0, float, let DDD control //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
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

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
//	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //

//	Write_Word(g_TM_ANA, 0x0138, NObin, HEX);
DSM_Write_Word(g_TM_ANA, 0x0138);
	
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

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
	wait.delay_10_us(200);

	FB_ovi->set_voltage(FB_ch, 1.0, RANGE_2_V);	// OVI_1_2 //

	// Powerup Primary //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	wait.delay_10_us(10);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	VBPP_Negative_Cycle();
	wait.delay_10_us(300);
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);

	// Power Up //
	gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	VBPP_Power_Up_w_Test_Mode(gTM2_UVOV_NoDelay, ILIM_NORM); // TM2 requires the normal wait and listen 85ms //
	D_dvi->set_voltage(D_ch, 5.0, VOLT_50_RANGE); // Bring Drain higher to TMU measurement during iVpin test //

	// Setup DDD //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Get ready for handshake to give control to secondary. //
	ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
	wait.delay_10_us(14);
	Close_relay(K21); // Connect FW pin to DDD_Ch3. //
	wait.delay_10_us(200);
	Open_relay(K18); // Disconnect FW pin from DVI-11-1 //
	wait.delay_10_us(200);
	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2
	wait.delay_10_us(50);

	// Provide 2 negative pulses on FW to give Secondary control.  (FW go below -100mV)
	Force_Neg_Pulses_FW_DDD(5, -0.5); //expect Drain to give acknowlege pulse after the 3rd FW pulse.
	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
	FW_dvi->set_voltage(FW_ch, 5, VOLT_10_RANGE); // DVI_11_1 //
	wait.delay_10_us(10);
	Close_relay(K18); // Connect FW pin to DVI-11-1 //
	delay(2);	
	Open_relay(K21); // Disconnect FW pin from DDD_Ch3. //
	delay(2);
	FW_dvi->set_voltage(FW_ch, 1.0, VOLT_50_RANGE);	// DVI_11_1
	wait.delay_10_us(200);
	gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	wait.delay_10_us(50);
	VPIN_ovi->set_voltage(VPIN_ch, 5.0, RANGE_5_V);	//Can't go down to 2V.  3V is about 0.3uA lower than original

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(20);

	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT); // OVI_1_1 //
	wait.delay_10_us(10);

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// IOV+
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if(!gTrim_iov_Off_P_Trimops)
	{
		UpperLimit = (func.dlog->tests[A_iOV_plus].f_max_limit_val[0])*1.2; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_iOV_plus].f_min_limit_val[0])*0.8; // Get lower search limit //
		search_IOVp_Binary(&iOV_plus, LowerLimit, UpperLimit);
	
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// IOV-
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		//Found IOV+ and step down 4uA to start searching for IOV-.
		if (fabs(iOV_plus) > 300e-6)		// to prevent range error when bad part encountered
		{
			i_VPIN	= giOV_plus_TARGET_Trimops;
		}
		else
		{
			i_VPIN	= iOV_plus;
		}

		//Make sure device stop switching
		i_force = 125e-6;
		VPIN_ovi->set_current(VPIN_ch, i_force, RANGE_300_UA);	//expect no switching
		wait.delay_10_us(20);

		//Ramp down iVpin to be closer to iOV- threshold
		while( i_force > (i_VPIN-3e-6) )
		{
			VPIN_ovi->set_current(VPIN_ch, i_force, RANGE_300_UA); //expect no switching
			wait.delay_10_us(5);
			i_force -= 0.5e-6;
		}
		
		//step down with i_step to roughly find IOV- threshold 
		i_step = 0.25e-6;
		for(i=1; i<=40; i++)
		{
			//i_VPIN = i_VPIN - i*i_step;
			i_VPIN = i_VPIN - i_step;
			VPIN_ovi->set_current(VPIN_ch, i_VPIN, RANGE_300_UA);	//expect no switching
			wait.delay_10_us(20);
			tmu_6->arm();						
			wait.delay_10_us(20);	//Need minimum 100us for device to react to new current from nsw to sw
			tmeas = tmu_6->read(200e-6);
			if(tmeas > 10e-6 && tmeas < 999)	//Device switching
				break;
		}
		iOV_minus = i_VPIN;
		//Fine tune with 0.1uA step (need this???)
		iOV_Hys = iOV_plus - iOV_minus;
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iUV+
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//Device is in non-switching state from tUV
	//Ramp up from 15uA to 40uA with i_step (Note that iUV+ might need to be found in less than 4ms else device stays OFF)
	//Note if above iUV+ is appllied you will see device switch for more than 100ms
	VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);	
	wait.delay_10_us(50);
	i_step	= 0.25e-6;
	i_start = 15e-6;
	for(i=1; i<=80; i++)
	{
		i_VPIN = i_start + i*i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN, RANGE_300_UA);	//require minimum 100us for device change from nsw to sw
		tmu_6->arm(); 
		wait.delay_10_us(20);		// ~100us needed for device to go from nsw to sw
		tmeas = tmu_6->read(100e-6); 
		if(tmeas > 10e-6 && tmeas < 999)
		{
			SWITCHING = true;
			break;
		}
		else
			SWITCHING = false;
	}
	iUV_plus = i_VPIN+i_step;

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iUV- 
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Device is in switching state from iUV+
	// Ramp down from IUV+ - 3uA with i_step down until device stop switching
	i_step = 0.25e-6;
	loopCount = 30;
	if(gTrim_iuvMinus_P_Trimops)
	{
		stepDown = 9e-6;
		loopCount = 48;
	}
	i_VPIN = iUV_plus;
	for(i=1; i<=loopCount; i++)
	{
		i_VPIN -= i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN, RANGE_300_UA);	
		wait.delay_10_us(20);
		tmu_6->arm(); 
		wait.delay_10_us(20);
		tmeas = tmu_6->read(100e-6); 

		if(tmeas > 10e-6 && tmeas < 999)
			SWITCHING = true;
		else
		{
			SWITCHING = false;
			break;
		}
	}
	iUV_minus = i_VPIN-i_step;
	iUV_Hys = iUV_plus - iUV_minus;

	// Powerdown //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain 
	Open_relay(K3); // Drain to RL pullup
	Open_relay(K18);
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39); 
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.3);
	wait.delay_10_us(10);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
//Mux20_Open_relay(K66);
//Open_relay(K74);
//mux_14->open_relay(MUX_2_GND);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	wait.delay_10_us(2);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
	FB_ovi->connect(2);
	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
	SR_dvi2k->set_voltage(SR_ch, 0.5, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	wait.delay_10_us(30);
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(5);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tOV_P-S
	//
	// There are two different tOV features per Lance (designer):
	// 1) tOV+ from datasheet.  Should be around 3 usec.  This is tested by getting the part 
	// in secondary control so drain on-time will be 15us.  Apply IOV condition to Vpin prior 
	// to drain turn-on and measure how long for drain to turn off.  The Vpin FET OV/UV 
	// functionality will be off if more than 50us has elapsed since the last drain turn on, 
	// and the Vpin FET OV/UV functionality will be on again the next time the drain turns on.
	// 
	// 2) The other tOV test is as follows:  with the part switching in secondary control 
	// if a IOV condition exists for less than 100usec then the part will continue switching 
	// in secondary control.  If the IOV condition exists for >100usec then the primary will 
	// take over control and a handshake would be required to give control back to secondary.
	// This is checked as a functional test.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if(!gTrim_iov_Off_P_Trimops)
	{
		VBPP_Negative_Cycle();

		// Open all relays //
	//	Initialize_Relays();

		// Initialize Instruments //
	//	Initialize_Instruments();

		// Drain //
		Close_relay(K3);
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
		tmu_6->start_trigger_setup(1.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(2.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);

		// BPP //
		BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

		// V pin //
		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

		// FW //
		Close_relay(K21); // Connect FW pin to DDD_Ch3. //
			
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
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

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

		// Set DDD for I2C. //
		//ddd_7->ddd_set_clock_period(g_Dclk_I2C);
		//ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
			
		// Wait for relays //
		wait.delay_10_us(200); 

		// FW high //
		ddd_7->ddd_set_clock_period(Dclk_period);
		ddd_7->ddd_set_voltage_ref(DDD_Vref);
		wait.delay_10_us(20); 
		ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
		wait.delay_10_us(20);

		// Powerup //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
		//wait.delay_10_us(100);wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

		// I2C into test mode. //  
		//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
		//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
		//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

		//Power up Primary with Vpin OV/UV functionality enabled //
		gIOV = 1;
		Power_Up_Primary_Normal_Mode(ILIM_NORM);
		gIOV = 0;
		wait.delay_10_us(25);

		// Provide negative pulses on FW to give Secondary control //
		Force_Neg_Pulses_FW_DDD(4, -0.5);
		wait.delay_10_us(16);

		// Vout high to stop switching //
		VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(20);

		// VBP_P drops when secondary has control //
		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
		wait.delay_10_us(8);
		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(20);

		// Apply IOV conditon to Vpin //
		tmu_6->arm();
		VPIN_ovi->set_current(VPIN_ch, 200e-6, RANGE_300_UA); // OVI_1_1 //
		wait.delay_10_us(10);

		// Turn on drain, and measure drain on-time //
		VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(30);
		tOV_P_S = tmu_6->read(); 

		// Functional check //
		// Remove IOV condition.  If the IOV condition exists for more than 100us the primary 
		// should take back control and handshake required to give control back to secondary.  
		// This is a functional check to make sure the primary has take back control (will go 
		// to wait-and-listen with no switching) //
		// Remove IOV and make sure drain is not switching //
		VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA); // OVI_1_1 //
		wait.delay_10_us(10);
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read();
		if (tmeas > 1e-9) // Should not be switching. Error if still switching. //
		{
			g_Error_Flag = -205;
		}

		// Powerdown //
		Open_relay(K3);
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
		tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
		Mux20_Open_relay(K50);
		Open_relay(K21);
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		VBPP_ramp_down(4, 0, 0.2);
		VPIN_ovi->set_voltage(VPIN_ch, 0.5, RANGE_10_V); // OVI_1_1 //
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
		wait.delay_10_us(10);
		VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V); // OVI_1_1 //
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
		FB_ovi->connect(2);
	//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

		// DDD level //
		//g_DDD_Low = 0.0; // Save current value //
		//g_DDD_High = 4.0; // Save current value //
		//wait.delay_10_us(100);
		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(200);
	}

	if(!gTrim_uvDelay_P_Trimops)
	{
		if (g_Char_Enable_P) // Characterization only //
		{
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// tUV
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// BPP cycle //
			VBPP_Negative_Cycle();

			// Open all relays //
//			Initialize_Relays();

			// Initialize Instruments //
//			Initialize_Instruments();

			// Drain //
			Close_relay(K3);
			D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
			tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
			tmu_6->start_trigger_setup(1.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			tmu_6->stop_trigger_setup(2.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);

			// BPP //
			BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

			// V pin //
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

			// FW //
			Close_relay(K21); // FW to DDD-7-3 //
			ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
	
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
			VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
			VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

			// FB (COMP) //
			FB_ovi->disconnect(2);
			//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
			//FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

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
			SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
			SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //

			// SCL //
			SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
			SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	
			// Setup DDD //
			ddd_7->ddd_set_clock_period(Dclk_period);
			ddd_7->ddd_set_voltage_ref(DDD_Vref);

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

			// Powerup secondary //
			BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
			wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
	
			//Power up Primary
			gIOV = 1;
			Power_Up_Primary_Normal_Mode(ILIM_NORM);
			gIOV = 0;
			wait.delay_10_us(25);

			// Keep drain low while connecting InvSync circuit to prevent glitches on FW pin //
			D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
			//wait.delay_10_us(30);
		
			// Three negative pulse on FW pin to give control to secondary //
			Force_Neg_Pulses_FW_DDD(4.9, -0.5); //Expect Drain to give acknowlege pulse after the 3rd FW pulse //
			wait.delay_10_us(16);

			// Stop switching //
			VO_dvi->set_voltage(VO_ch, 5.5, VOLT_10_RANGE); // DVI_9_0 //
			//FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
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

			// Start switching //
			VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
			//FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
			wait.delay_10_us(20);
			SWITCHING = true;
			VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA); // Expect switching for 35ms then OFF // 

			//wait.delay_10_us(100);
			if(gTrim_iuvMinus_P_Trimops)
				VPIN_ovi->set_current(VPIN_ch, 1e-6, RANGE_300_UA);
			starttime = mytimer.GetElapsedTime();
			count = 0;
			while(SWITCHING == true && count < 1500)
			{
				tmu_6->arm(); 
				wait.delay_10_us(10);
				tmeas = tmu_6->read(50e-6); 
				if(tmeas > 10e-6 && tmeas < 999)
				{
					SWITCHING = true;
				}
				else
				{
					SWITCHING = false;
					break;
				}
				count++;
			}
			stoptime = mytimer.GetElapsedTime();
			tUV_minus = (stoptime - starttime)/1e6;

			// Powerdown //
			D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
			tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
			Mux20_Open_relay(K50); // SR pin GND//
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
			VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
			VBPP_ramp_down(4, 0, 0.2);
			Disconnect_InvSyn_IM();
			VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
			//wait.delay_10_us(20);
		//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
		//	uVCCrampDown(0.5, 0, 0.1);
			wait.delay_10_us(170);
			BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE);
			wait.delay_10_us(5);
			BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // Secondary vBPS_plus
			VBPS_ramp_down(3, 0, 200e-3);
		//	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
		//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
			wait.delay_10_us(20);
		//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
			FB_ovi->connect(2);
			FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
		//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

			// DDD level //
			g_DDD_Low = 0.0; // Save current value //
			g_DDD_High = 4.0; // Save current value //
			wait.delay_10_us(g_DDDwait);
			ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
			wait.delay_10_us(200); // Wait for relays //
		}
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tUV_M_counter-S
	// The tUV time measured in test mode 1. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	VBPP_Negative_Cycle();

	// Open all relays //
	//Initialize_Relays();

	// Initialize Instruments //
	//Initialize_Instruments();

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
	//Close_relay(K18);
	//FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	//FW_dvi->set_current(FW_ch, 3e-3, RANGE_3_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// FW //
	Connect_InvSyn_IM(Low_Vd_Input);

	// Lower the inv sync output GND to get a faster falling edge to make sure secondary request comes before the end of the primary window (tblock = 2us) //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.5, VOLT_5_RANGE);
	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);

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
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	//IS_dvi2k->set_current(IS_ch, 200.0e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50);

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// COMP //
	FB_ovi->set_voltage(FB_ch, 1, RANGE_10_V); // OVI_1_2 //
	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //

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
//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
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

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
//	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Password); // Write I2C password for test mode. //
DSM_Write_Word(g_TM_EN, g_TestMode_Enter); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

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
	wait.delay_10_us(250);

	// TMU setup //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// Set DDD //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	//Negative pulses on FW
//	Open_relay(K18);
//	Close_relay(K21);
//	wait.delay_10_us(300);
//	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
//	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
//	Open_relay(K21);
//	Close_relay(K18);
//	wait.delay_10_us(300);
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE);	// DVI_9_0
	wait.delay_10_us(50);
//	Connect_InvSyn_IM(Low_Vd_Input);
//	Open_relay(K18); // Disconnect dvi from FW //
	wait.delay_10_us(100);
	VBPP_Power_Up_w_Test_Mode(gTM1_UVOV_NoDelay, ILIM_NORM);	// TM2 requires the normal wait and listen 85ms
	wait.delay_10_us(500);

	// VBP_P drops when secondary has control //
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	wait.delay_10_us(8);
	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(20);

	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //  Reset the dvi //


// Setup dvi to measure current //
//BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
//wait.delay_10_us(20);
//LowerLimit = (func.dlog->tests[A_iBPP_bled].f_min_limit_val[0]); // Get lower search limit //

	// Force IUV fault //
	VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);
	wait.delay_10_us(1);

	// Wait for drain to stop switching //
	TimeStart = mytimer.GetElapsedTime();
	count = 0;
	while (count < 10000)
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(60e-6);
		if (tmeas < 0.1e-9)
			break;
		count++;
	}
	TimeStop = mytimer.GetElapsedTime();
	tUV_M_counter_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //



	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iBPP_bled-S //
	// iBPP_bledOff-S //
	// When Vpin current falls below IUV-, the 1mA BPP bleeder current turns on.  
	// When Vpin is brought back above IUV+, the BPP bleeder current should turn off again.  
	// Without the bleeder on, the BPP current should be about 200uA. Be sure to subtract 
	// the 200uA from the bleeder current measurement. 
	// iBPP_bled-S is the bleeder current.
	// iBPP_bledOff-S is a functional go/no test to make sure the bleeder turns off.
	// Test with primary in TM1 to reduce the amount of time it takes bleeder to turn on.
	// Seconary does not need to be powered up. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Make sure VBPP is below shunt otherwise current reading will be wrong //
//	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final-.175, RANGE_10_V); // OVI_1_0, Keep below shunt voltage // //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(20);

	iBPP_bled_S = BPP_ovi->measure_average(25);
	// Raise Vpin current above IUV+ and make sure bleeder turns back off. //
	VPIN_ovi->set_current(VPIN_ch, 60e-6, RANGE_300_UA);
	wait.delay_10_us(50);
	BPPcurrent2 = BPP_ovi->measure_average(5); // Measure BPP current to make sure bleeder turns off. //
	if(iBPP_bled_S > 0.5e-3 && BPPcurrent2 < 0.75e-3) // Functional check, make sure bleeder turns on, then back off. //
//if(iBPP_bled_S > LowerLimit && BPPcurrent2 < LowerLimit) // Functional check, make sure bleeder turns on, then back off. //
		iBPP_bledOff_S = 1e-6; // Pass //
	else
		iBPP_bledOff_S = -999; // Fail //

	// Powerdown //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain
	Open_relay(K3); // Drain to RL pullup
	Mux20_Open_relay(K50);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	VBPP_ramp_down(4, 0, 0.3);
	wait.delay_10_us(10);
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(20);
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(1, 0, 0.1);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	wait.delay_10_us(2);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
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

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tUV_400ms-S
	// When bit#18 (UV 400ms delay) is trimmed the tUV time increaes to 400msec. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_uvDelay_P_Trimops)
	{
		if(g_Char_Enable_P == false)
			ExitTime = .05; // If production test, only wait 50msec max. //
		else
			ExitTime = 0.6; // If characterization, expect longest UV timer ~600ms //

		// Drain to 40V, for normal mode. //
		D_dvi->set_voltage(D_ch, 40.0, VOLT_50_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(1.9, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
		tmu_6->stop_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		// Vpin high to enable OV/UV //
		VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);  // Do not exceed IOV. //	
		VPIN_ovi->set_voltage(VPIN_ch, 6, RANGE_10_V); 

		// FW //
		Close_relay(K21); // Connect FW to DDD Ch3 // 

		// SR //
		SR_dvi2k->set_current(SR_ch, 0, RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);

		// BPS //
		BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

		// IS //
		IS_dvi2k->set_voltage(IS_ch, 0, VOLT_50_RANGE);
		IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);

		// Vout //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA);	
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE);
		
		// FB //
		FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA);
		FB_ovi->set_voltage(FB_ch, gCV_FB_S*1.1, RANGE_2_V);
		
		// Setup DDD //
		// DDD level //
		g_DDD_Low = 0.0; // Save current value //
		g_DDD_High = 5.0; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
		delay(2);; // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up with normal mode //
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

		// Set drain //
		D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
		wait.delay_10_us(40);

		// BPS powerup //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
		wait.delay_10_us(50);

		// FW pin //
		ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

		// Secondary send 3 negative FW pulses. //
		Force_Neg_Pulses_FW_DDD(5, -0.5);
		wait.delay_10_us(30);
		// Secondary now has control. //
		
		// Set drain to 0V to connnect InvSync circuit //
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
		wait.delay_10_us(20);

		// FW pin //
		// DDD level //
		g_DDD_Low = 0.0; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);

		// Connect InvSync circuit //
		Connect_InvSyn_IM(Low_Vd_Input);
		Open_relay(K21); // Disconnect FW from DDD Ch3 //
		wait.delay_10_us(200);

		// FB pin //
		// DDD level //
		g_DDD_High = gCV_FB_S*1.1; // Save current value //
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		wait.delay_10_us(g_DDDwait);
		ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
		wait.delay_10_us(50);
		Close_relay(K17); // Connect DDD Ch2 to FB pin //
		delay(4);
		//wait.delay_10_us(200);
		FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V);

		// Set drain //
		D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
		wait.delay_10_us(50);
		
		// Start drain switching //
		ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop);
		ddd_7->ddd_run_pattern(); // Need to do a stop pattern when you don't want ddd looping //
		wait.delay_10_us(50);

		// Force IUV fault //
		VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);
		wait.delay_10_us(50);
		
		// Wait for drain to stop switching //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(20);
			tmeas = tmu_6->read(200e-6);

			TimeStop = mytimer.GetElapsedTime();
			TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
			if (tmeas < 0.1e-9 || (TimeDelta > ExitTime))
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		tUV_400ms_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
		ddd_7->ddd_stop_pattern();

		// Power Down //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();
		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain //
	}

	// Datalog
	if(!gTrim_iov_Off_P_Trimops)
	{
		PiDatalog(func, A_iOV_plus, iOV_plus, 24, POWER_MICRO);	
		PiDatalog(func, A_iOV_minus, iOV_minus, 24, POWER_MICRO);	
		PiDatalog(func, A_iOV_Hys, iOV_Hys, 24, POWER_MICRO);
		PiDatalog(func, A_tOV_P_S, tOV_P_S, 24, POWER_MICRO);

		if(g_Sim_Enable_P)
		{
			// iOV_plus_act
			if( giOV_plus_Pt_P !=0)		
				iOV_plus_act = ((giOV_plus_Pt_P/iOV_plus -1)*100) * -1;
			else 						
				iOV_plus_act = 999.0;
			PiDatalog(func, A_iOV_plus_exp, giOV_plus_exp, 24, POWER_UNIT);	
			PiDatalog(func, A_iOV_plus_act, iOV_plus_act, 24, POWER_UNIT);	
		}		
	}
	PiDatalog(func, A_iUV_minus, iUV_minus, 24, POWER_MICRO);
	PiDatalog(func, A_iUV_plus, iUV_plus, 24, POWER_MICRO);
	PiDatalog(func, A_iUV_Hys, iUV_Hys, 24,	POWER_MICRO);

	PiDatalog(func, A_iBPP_bled, iBPP_bled_S, 24, POWER_MICRO);
	PiDatalog(func, A_iBPP_bledOff, iBPP_bledOff_S, 24, POWER_MICRO);
	if(!gTrim_uvDelay_P_Trimops)
	{
		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_tUV_minus, tUV_minus, 24, POWER_MILLI);	
		}
	}
//	PiDatalog(func, A_OT_Vpin6V,	OT_Vpin6V,		24,	POWER_UNIT);	
//	PiDatalog(func, A_OT_Vpin0V,	OT_Vpin0V,		24,	POWER_UNIT);	
	PiDatalog(func, A_tUV_M_counter, tUV_M_counter_S, 24, POWER_MILLI);
	if (gTrim_uvDelay_P_Trimops)
		PiDatalog(func, A_tUV_400ms, tUV_400ms_S, 24, POWER_MILLI);	

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		IOV_IUV_OT_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_IOV_IUV_OT_TT, IOV_IUV_OT_TT, 24, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
