//==============================================================================
// SOA_SDS_TW50.cpp (User function)
// 
//    void SOA_SDS_TW50_user_init(test_function& func)
//    void SOA_SDS_TW50(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SOA_SDS_TW50.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SOA_SDS_TW50_user_init(test_function& func)
{
	SOA_SDS_TW50_params *ours;
    ours = (SOA_SDS_TW50_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SOA_SDS_TW50(test_function& func)
{
    // The two lines below must be the first two in the function.
    SOA_SDS_TW50_params *ours;
    ours = (SOA_SDS_TW50_params *)func.params;

	// Increment function number //
	gFuncNum++;
//////
//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_Func_Num_SOA_SDS_TW50, gFuncNum, 19, POWER_UNIT);
//////
//////	// Skip Test if AbortTest set //
//////	if (AbortTest)
//////		return;
//////
//////	if (g_Fn_SOA_SDS_TW50 == 0 )  return;
//////
//////	// Test Time Begin //
//////	if (g_TstTime_Enble_P)
//////		g_begintime = g_mytimer.GetElapsedTime();
//////
//////	// Declare Variables //
//////	Pulse pulse(PULSE_RISING_EDGE,10e-6); // External trigger pulse from dvi for debug
//////	Pulse pulse2(PULSE_RISING_EDGE,50e-6); // External trigger pulse from dvi for debug
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //	
//////	float SOA_S =0.0;
//////	float TW50_S =0.0;
//////	float SOA_P =0.0;
//////	float TW50_P =0.0;
//////	float SDS_P =0.0;
//////	float TW50_SDS_P =0.0;
//////	float SDS_S =0.0;
//////	float TW50_SDS_S =0.0;
//////	float SDS_P_nsw =0.0;
//////	float SDS_S_nsw =0.0;
//////	float tARoffShort_P =0;
//////	float PV3_Charge =0.0;
//////	int lcnt =0;
//////	int Rep_cnt =0;
//////	float Vpv3_meas =0.0;
//////	float vSOA =0.0;
//////	float vSOA_P =0.0;
//////	float vSDS =0.0;
//////	float vSDS_P =0.0;
//////	float Vref_cmp=0.0;
//////	float tmu_trig;
//////	float tmeas=0.0;
//////	float vsync_set = 0.0;
//////	int count = 0;
//////	int MaxCount = 0;
//////	int FlagError = 0;
//////	float vTrig_Start =0.0;
//////	float vTrig_Stop =0.0;
//////	float vfrc =0.0;
//////	float vstep =0.0;
//////	int SR_AF_temp[100]= {0};
//////	float previous_tmu_trig = 0;
//////	int READ59_word[16] = {0};
//////	int WordArray[16] = {0};
//////	float SOA_SDS_TW50_TT = 0;
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SDS test: (diode short) 
//////	//	Resistive/inductive pull-up provided by wire-wound resistor
//////	//	Higher pull-up voltage will cause drain pulse width to be very small (<180ns)
//////	//	DUT will detect short pulse width and enter SDS mode
//////	//	Test is done twice, once with primary in control, once with secondary in control
//////	//	Primary in control, SOA mode puts out two pulses approx. 115us apart
//////	//	Secondary in control, 	SDS mode is two pulses, short gap, one pulse, 200ms gap
//////	//
//////	// SOA test: (safe operating area)
//////	//	Resistive/inductive pull-up provided by wire-wound resistor
//////	//	Slightly lower pull-up voltage will cause drain pulse width to be short (<320ns) but longer 
//////	//	than SDS pulse (>180ns)
//////	//	DUT will detect intermediate short pulse width and enter SOA mode
//////	//	Test is done twice, once with primary in control, once with secondary in control
//////	//	Primary in control, SOA mode puts out a single pulse approx. every 115us
//////	//	Secondary in control, SOA mode repeats this sequence: pulse, 8us gap, pulse, 35us gap
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
////////	Initialize_Instruments();
//////	
//////	if (gMOSFET_SIZE_Trimops == 5)
//////	{
//////		if (!strnicmp(Part_ID_LimitSet, "INN3365", 7))
//////		{
//////			vSOA = 14.4; // 7/22/17 //
//////		}
//////		if (!strnicmp(Part_ID_LimitSet, "INN3375", 7))
//////		{
//////			vSOA = 13.6; // 7/22/17 //
//////		}
//////	}
//////	if (gMOSFET_SIZE_Trimops == 6)
//////	{
//////		if (!strnicmp(Part_ID_LimitSet, "INN3366", 7))
//////		{
//////			vSOA = 17.0; ; // 7/22/17 //
//////		}
//////		if (!strnicmp(Part_ID_LimitSet, "INN3376", 7))
//////		{
//////			vSOA = 17.2; // 7/22/17 //
//////		}
//////	}
//////	if (gMOSFET_SIZE_Trimops == 7)
//////	{
//////		if (!strnicmp(Part_ID_LimitSet, "INN3367", 7))
//////		{
//////			vSOA = 19.2; // 7/22/17 //
//////		}
//////		if (!strnicmp(Part_ID_LimitSet, "INN3377", 7))
//////		{
//////			vSOA = 18.4; // 7/22/17 //
//////		}
//////		if (!strnicmp(Part_ID_LimitSet, "SC1750", 6))
//////		{
//////			vSOA = 19.067; // 5/21/18 //
//////		}
//////	}
//////	if (gMOSFET_SIZE_Trimops == 8)
//////	{
//////		if (!strnicmp(Part_ID_LimitSet, "INN3368", 7))
//////		{
//////			vSOA = 19.4; // 7/22/17 //
//////		}
//////		if (!strnicmp(Part_ID_LimitSet, "SC1738", 6))
//////		{
//////			vSOA = 19.975; // 5/21/18 //
//////		}
//////	}
//////
//////	// Gage Setup //
//////	//Gage_pretrig_samples=256;
//////	//Gage_init();
//////	SAMPLE_SIZE = GAGE_POST_64K;
//////	INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 
//////
//////	// PVI setup //
//////	PV3_CHARGE_ON(RANGE_100_V); // Prepare PV3 before power-up
//////	PV3_Check_Charge(RANGE_100_V); // Note: Once Charge Off, V start dropping due to discharge over time
//////	pv3_4->close_switch(PV3_LOW_FORCE_2);
//////	pv3_4->close_switch(PV3_LOW_SENSE_2);
//////	pv3_4->close_switch(PV3_HIGH_FORCE_3);
//////	pv3_4->close_switch(PV3_HIGH_SENSE_3);
//////	pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
//////
//////	// Force 5V below normal VSOA and search up for the right VSOA. Some devices require lower VSOA while some require higher.
//////	if (vSOA>8)		
//////		pv3_4->set_voltage(vSOA-5, RANGE_100_V);
//////	else	
//////		pv3_4->set_voltage(vSOA-2, RANGE_100_V);	
//////	pv3_4->set_current(10.0);
//////	wait.delay_10_us(20);
//////	pv3_4->charge_off();
//////
//////	//  TMU setup //
//////	tmu_trig = 6;
//////	tmu_6->close_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup( tmu_trig, POS_SLOPE, TMU_HIZ, TMU_IN_100V);
//////	tmu_6->stop_trigger_setup( tmu_trig-0.5, POS_SLOPE, TMU_HIZ, TMU_IN_100V);
//////	tmu_6->start_holdoff(0,FALSE);  
//////	tmu_6->stop_holdoff(0,FALSE);
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// SOA-P & SDS-P
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Information:
//////	//	- SOA pullup resistance
//////	//		-5ohm (Require hardware modification)
//////	Close_relay(K3); // Drain to L1 to 50ohm.
//////
//////	// Setting up Vpin for TM5 power up.
//////	VPIN_ovi->disconnect(VPIN_ch);
//////	
//////	// Initialize DDD
//////	g_DDD_Low = 0.1; // Save current value //
//////	g_DDD_High = 4.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////	
//////	//Strange, same pattern at different location, causing FW to drop below GND.
//////	//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
//////	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);
//////	wait.delay_10_us(10);
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	wait.delay_10_us(300);
//////
//////	// BPP //
//////	VBPP_Negative_Cycle();
//////	wait.delay_10_us(200);
//////
//////	// Powerup primary //
//////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////	wait.delay_10_us(50);
//////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
//////	wait.delay_10_us(100);
//////	Open_relay(K3); // Disconnect Drain from DVI
//////	wait.delay_10_us(300);
//////
//////	// Turn off the switching of device before connecting PV3 to drain to avoid hot switching.
//////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-50e-3, RANGE_10_V); // OVI_1_0 //
//////	wait.delay_10_us(20);
//////	BPP_ovi->set_current(BPP_ch, 10e-3,	RANGE_30_MA); // This current clamp is needed to avoid Drain charging BPP which could cause the BPP/Drain to switch. //
//////	wait.delay_10_us(10);
//////	
//////	// Drain to PVI //
//////	Close_relay(K9); // Drain to CT2+ //
//////	Close_relay(K7); // CT2+ to 2ohm pull-up by PVI
//////	wait.delay_10_us(300);
//////
//////	// BPP //
//////	BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_30_MA); // B3 material. HL changed from 2mA to 3mA
//////	VBPP_ramp_up(gVBPP_M_Init-50e-3, gVBPP_P_final, 10e-3);// B3 material
//////	wait.delay_10_us(10);
//////	wait.delay_10_us(10);
//////	
//////	// Force 5V below normal VSOA and search up for the right VSOA. 
//////	// Some devices require lower VSOA while some require higher.
//////	if (vSOA>8)
//////		vfrc = vSOA-5;
//////	else
//////		vfrc = vSOA-2;
//////
//////	// Turn on PV3
//////	pv3_4->drive_on(); 
//////	pv3_4->set_voltage(vfrc, RANGE_100_V);
//////	wait.delay_10_us(50);
//////
//////	// Search for SOA pull-up voltage //
//////	vstep = 0.2; 
//////	tmeas = 0.0;
//////	previous_tmu_trig = tmu_trig;
//////	while (vfrc < 25 && tmeas < 90e-6)
//////	{
//////		vfrc += vstep;
//////
//////		// Need to adjust TMU trigger levels as drain voltage is increased otherwise won't trigger. //
//////		tmu_trig = vfrc + 2.3;
//////		tmu_6->start_trigger_setup( tmu_trig, POS_SLOPE, TMU_HIZ, TMU_IN_100V);
//////		tmu_6->stop_trigger_setup( tmu_trig-0.5, POS_SLOPE, TMU_HIZ, TMU_IN_100V);
//////		pv3_4->set_voltage(vfrc, RANGE_100_V);
//////		wait.delay_10_us(6);
//////		tmu_6->arm();	
//////		wait.delay_10_us(30);
//////		tmeas = tmu_6->read(100e-9);
//////		if(tmeas > 90e-6) // Add a little extra voltage to be sure above threshold. //
//////		{
//////			if(g_OPCODE==4300 || g_OPCODE==4500)
//////			{
//////				pv3_4->set_voltage((vfrc+3*vstep), RANGE_100_V);
//////			}
//////			else
//////			{
//////				vfrc = vfrc + 3*vstep;
//////				pv3_4->set_voltage(vfrc, RANGE_100_V);
//////			}
//////			wait.delay_10_us(10);
//////		}
//////	}
//////
//////	vSOA = vfrc;
//////	if (gMOSFET_SIZE_Trimops == 5)
//////	{
//////		vSDS = vSOA+10;
//////	}
//////	else
//////	{
//////		vSDS = vSOA+17;
//////	}
//////
//////	// SOA_P //
//////	// device switching, 
//////	// start SOA_P capture //
//////	Gage_Start_Capture( );	
//////	Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
//////
//////	// Turn off switching before PV3 drive-off.
//////	// Turn off the switching of device before SDS test
//////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-50e-3, RANGE_10_V); // OVI_1_0 //
//////	
//////	// Turn off gage
//////	pv3_4->drive_off(); 
//////	wait.delay_10_us(100);
//////	pv3_4->set_voltage(0.0, RANGE_100_V);
//////	pv3_4->set_current(0.0);
//////	pv3_4->charge_on();
//////	wait.delay_10_us(500);
//////
//////	// HL changed from 10mA to 5mA due to a SDS-P repeatability failure seen on TMT92. 06/13/17
//////	BPP_ovi->set_current(BPP_ch, 10e-3,	RANGE_30_MA); // This current clamp is needed to avoid Drain charging BPP which could cause the BPP/Drain is switching.	
//////	wait.delay_10_us(50);
//////
//////	// Process capture
//////	g_SaveAwav = 0;
//////	Gage_Find_SOA(&SOA_P, &TW50_P);
//////	g_SaveAwav = 0;
//////
//////	// Set voltage for SDS test
//////	pv3_4->charge_off();
//////	delay(5);
//////	pv3_4->set_voltage(vSDS, RANGE_100_V);
//////	pv3_4->set_current(10.0);
//////	pv3_4->drive_on();	
//////	delay(5);
//////
//////	// start SDS_P capture
//////	Gage_Start_Capture( );	
//////
//////	BPP_ovi->set_current(BPP_ch, 12e-3, RANGE_30_MA); // HL changed from 2mA to 3mA
//////	VBPP_ramp_up(gVBPP_M_Init-50e-3, gVBPP_P_final, 10e-3);
//////	wait.delay_10_us(20);
//////	
//////	Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
//////	
//////	// Turn off gage
//////	pv3_4->drive_off();	
//////	wait.delay_10_us(100);
//////	pv3_4->set_voltage(0.0, RANGE_100_V);
//////	pv3_4->set_current(0.0);
//////	pv3_4->charge_on();
//////	wait.delay_10_us(500);
//////
//////	// Process capture
//////	g_SaveAwav = 0;
//////	Gage_Find_SDS(&SDS_P, &TW50_SDS_P, &SDS_P_nsw);
//////	g_SaveAwav = 0;
//////
//////	if (gTrim_SDSoff_P_Trimops)
//////	{
//////		if (SDS_P_nsw > 0)
//////			SDS_P_nsw = 0; // Pass //
//////	}
//////
//////	// Powerdown //
//////	tmu_6->open_relay(TMU_HIZ_DUT2); // Disonnect TMU HIZ from Drain //
//////	VPIN_ovi->connect(VPIN_ch);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	Open_relay(K9); // Drain, CT2+ //
//////	Open_relay(K7); // CT2+ 2ohm pull-up by PVI
//////	VBPP_ramp_down(4, 0, 0.1);
//////	
//////	// DDD //
//////	g_DDD_Low = 0.1; // Save current value //
//////	g_DDD_High = 0.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// For datalog units purpose //
//////	if(SOA_P > 990.0)
//////		SOA_P/=1e6;
//////	if(TW50_P > 990.0)
//////		TW50_P/=1e6;
//////	if(SDS_P > 990.0)
//////		SDS_P/=1e6;
//////	if(TW50_SDS_P > 990.0)
//////		TW50_SDS_P/=1e6;
//////
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Secondary: SOA-S & SDS-S
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
////////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
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
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2 //
//////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
//////	// Setup DDD //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 4.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
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
//////	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
////////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
////////	{
////////		BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_30_MA);
////////	}
//////	wait.delay_10_us(30);
//////	FB_ovi->set_voltage(FB_ch, 1.5, RANGE_2_V); // OVI_1_2 //
//////	wait.delay_10_us(30);
//////
//////	// VBP_P drops when secondary has control //
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
//////	wait.delay_10_us(8);
//////	BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
//////	wait.delay_10_us(20);
//////
//////	// Connect Vpin back to OVI //
//////	VPIN_ovi->connect(VPIN_ch);
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);  
//////	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA); 
//////	Open_relay(K12); // disconnect DDD7_1 from Vpin(UV) pin
//////
//////	if(g_OPCODE==4300 || g_OPCODE==4500) 
//////	{
//////		if(gMOSFET_SIZE_Trimops == 5) //HL Inv requires 3.75V at hot.  
//////			vsync_set = 3.0;
//////		if(gMOSFET_SIZE_Trimops == 6)
//////			vsync_set = 5.5;
//////		if(gMOSFET_SIZE_Trimops == 7)
//////			vsync_set = 6.5;
//////		if(gMOSFET_SIZE_Trimops == 8)
//////			vsync_set = 6.5;
//////	}
//////	else 
//////	{
//////		if(gMOSFET_SIZE_Trimops == 5) //HL Inv requires 3.75V at hot.  
//////			vsync_set = 3.0;
//////		if(gMOSFET_SIZE_Trimops == 6)
//////			vsync_set = 6.0;
//////		if(gMOSFET_SIZE_Trimops == 7)
//////			vsync_set = 6.5;
//////		if(gMOSFET_SIZE_Trimops == 8)
//////			vsync_set = 6.5;
//////	}
//////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, vsync_set, VOLT_20_RANGE); // OVI_1_4
//////
//////	// Adding extra VBPP voltage improves repeatability (on TMT91, not sure about other TMTs). //
////////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
////////	{
//////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.35, RANGE_10_V);
////////	}
////////	else
////////	{
////////		BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.2, RANGE_10_V);
////////	}
//////	wait.delay_10_us(10);
//////	wait.delay_10_us(50);
//////	Open_relay(K3); // Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0
//////
//////	// Adding extra capacitance to drain pin improves repeatability (on TMT91, not sure about other TMTs). //
////////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
////////	{
//////		Close_relay(K2);
//////		D_dvi->open_relay(CONN_FORCE0);
//////		D_dvi->open_relay(CONN_SENSE0);
////////	}
//////
//////	wait.delay_10_us(300);
//////	Close_relay(K7); // CT2+ to 2ohm pull-up by PVI
//////	Close_relay(K9); // Drain to CT2+
//////	wait.delay_10_us(300);
//////
//////	// Only test tARoffShort-P for characterizaton.  200 msec duration. //
//////	if(g_Char_Enable_P)
//////	{
//////		vTrig_Start = 14.0;	
//////		vTrig_Stop  = 15.0;
//////		tmu_6->close_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain // 
//////		//tmu_6->start_trigger_setup( vTrig_Start, NEG_SLOPE, TMU_HIZ, TMU_IN_100V); // cx 11/10/16
//////		//tmu_6->stop_trigger_setup(vTrig_Stop,  POS_SLOPE, TMU_HIZ, TMU_IN_100V); // cx 11/10/16
//////		tmu_6->start_trigger_setup( vTrig_Start, NEG_SLOPE, TMU_HIZ, TMU_IN_250V);
//////		tmu_6->stop_trigger_setup(vTrig_Stop,  POS_SLOPE, TMU_HIZ, TMU_IN_250V);
//////		tmu_6->start_holdoff(0,FALSE); // remove the 1ms  cx 1/30/2017
//////		tmu_6->stop_holdoff(0,FALSE);
//////		wait.delay_10_us(200);
//////	}
//////	pv3_4->charge_off();
//////	wait.delay_10_us(500);
//////
//////
//////	// SDS_S //
//////	Gage_Start_Capture( );	// start SDS_S capture //
//////
//////	//pull-up voltage
//////	pv3_4->set_voltage(vSDS+1, RANGE_100_V); // voltage found in search above
//////	pv3_4->set_current(10.0);
//////	pv3_4->drive_on();
//////	wait.delay_10_us(300);
//////
//////	// Turn device back on...	
//////	FB_ovi->set_voltage(FB_ch, 1, RANGE_2_V); // OVI_1_2
//////	wait.delay_10_us(4); // Approximate time for second pulse to happen //
//////
//////	// Only test tARoffShort-P for characterizaton.  200 msec duration. //
//////	if(g_Char_Enable_P)
//////	{
//////		starttime = mytimer.GetElapsedTime();
//////	}	
//////	Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
//////
//////	// Process capture
//////	g_SaveAwav = 0;
//////	Gage_Find_SDS(&SDS_S, &TW50_SDS_S, &SDS_S_nsw);
//////	g_SaveAwav = 0;
//////
//////	if (gTrim_SDSoff_P_Trimops)
//////	{
//////		if (SDS_S_nsw > 0)
//////			SDS_S_nsw = 0; // Pass //
//////	}
//////
//////	// Only test tARoffShort-P for characterizaton.  200 msec duration. //
//////	if(g_Char_Enable_P && !gTrim_Loff_AR_P_Trimops && !gTrim_SDSoff_P_Trimops)
//////	{
//////		tmu_6->arm();	//only need to arm once.  If the trigger is used, then we shall exit the while loop.  cx.  1/30/2017
//////		
//////		// Wait for next SDS pulse (approx 200msec). //
//////		count = 0;
//////		MaxCount = 3500;
//////		FlagError = 0;
//////		while (count < MaxCount) // About 100usec per loop //
//////		{
//////			wait.delay_10_us(10);
//////			tmeas = tmu_6->read(100e-6);
//////			if (tmeas > 0.1e-9)
//////				break;
//////			count++;
//////		}
//////		if(count > (MaxCount-1))
//////			FlagError = 1; // Part did not start switching. //
//////
//////		stoptime = mytimer.GetElapsedTime();
//////
//////		if(FlagError)
//////			tARoffShort_P = -99999;
//////		else
//////			tARoffShort_P = (stoptime - starttime) / 1e6;
//////	}
//////
//////	// Powerdown //
//////	pv3_4->drive_off();	
//////	pv3_4->set_voltage(0.0, RANGE_100_V);
//////	pv3_4->set_current(0.0);
//////	pv3_4->open_switch(PV3_LOW_FORCE_2);
//////	pv3_4->open_switch(PV3_LOW_SENSE_2);
//////	pv3_4->open_switch(PV3_HIGH_FORCE_3);
//////	pv3_4->open_switch(PV3_HIGH_SENSE_3);
//////	pv3_4->charge_on();
//////	D_dvi->close_relay(CONN_SENSE0);
//////	D_dvi->close_relay(CONN_FORCE0);
//////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
//////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
//////	Disconnect_InvSyn_IM();
//////	tmu_6->open_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain //
//////	Open_relay(K2);
//////	Open_relay(K7); // CT2+ to 2ohm pull-up by PVI
//////	Open_relay(K9); // Drain to CT2+
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	Mux20_Open_relay(K50);
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(0.5, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
////////	ddd_7->ddd_set_clock_period(Dclk_period);
////////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////
//////	// DDD level //
////////	g_DDD_Low = 0.0; // Save current value //
////////	g_DDD_High = 4.0; // Save current value //
////////	wait.delay_10_us(100);
////////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////	// Back to previous //
//////	//Gage_pretrig_samples=64;
//////	//Gage_init();
//////
//////	// For datalog units purpose //
//////	if(SOA_S > 990.0)
//////		SOA_S/=1e6;
//////	if(TW50_S > 990.0)
//////		TW50_S/=1e6;
//////	if(SDS_S > 990.0)
//////		SDS_S/=1e6;
//////	if(TW50_SDS_S > 990.0)
//////		TW50_SDS_S/=1e6;
//////
//////	// Datalog//
//////	PiDatalog(func, A_TW50_P, TW50_P, 19,POWER_NANO);
//////	PiDatalog(func, A_SOA_P, SOA_P, 19, POWER_MICRO);
//////	//PiDatalog(func, A_SOA_S, SOA_S, 19, POWER_MICRO); // Not needed per design, covered by SDS-S, TW50_SDS-S, SOA-P, TW50-P, SDS-P, TW50_SDS-P. //
//////	//PiDatalog(func, A_TW50_S, TW50_S, 19, POWER_NANO); // Not needed per design, covered by SDS-S, TW50_SDS-S, SOA-P, TW50-P, SDS-P, TW50_SDS-P. //
//////	if (!gTrim_SDSoff_P_Trimops)
//////	{
//////		PiDatalog(func, A_SDS_TW50_P, TW50_SDS_P, 19, POWER_NANO);
//////		PiDatalog(func, A_SDS_P, SDS_P, 19, POWER_MICRO);
//////		PiDatalog(func, A_SDS_S, SDS_S, 19, POWER_MICRO);
//////		PiDatalog(func, A_SDS_TW50_S, TW50_SDS_S, 19, POWER_NANO);
//////	}
//////	PiDatalog(func, A_SDS_P_nsw, SDS_P_nsw, 19, POWER_MICRO);	
//////	PiDatalog(func, A_SDS_S_nsw, SDS_S_nsw, 19, POWER_MICRO);	
//////	if(g_Char_Enable_P && !gTrim_Loff_AR_P_Trimops && !gTrim_SDSoff_P_Trimops)
//////		PiDatalog(func, A_tARoffShort_P, tARoffShort_P, 19, POWER_MILLI);	
//////
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		SOA_SDS_TW50_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_SOA_SDS_TW50_TT, SOA_SDS_TW50_TT, 19, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
