//==============================================================================
// IBP_Supply.cpp (User function)
// 
//    void IBP_Supply_user_init(test_function& func)
//    void IBP_Supply(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "IBP_Supply.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IBP_Supply_user_init(test_function& func)
{
	IBP_Supply_params *ours;
    ours = (IBP_Supply_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IBP_Supply(test_function& func)
{
    // The two lines below must be the first two in the function.
    IBP_Supply_params *ours;
    ours = (IBP_Supply_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IBP_Supply, gFuncNum, 12, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_IBP_Supply == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	float tmeas = 0;
	float BPP_ICH1_0V_p			=0, 
		  BPS_ICH1_3V_s			=0, 
		  BPP_ICH2_4V_p			=0, 
		  BPS_ICH2_4V_s			=0;
	float BPP_ICH3_CEN_p		=0,
		  BPS_ICH3_VO_s			=0, 
		  BPP_ICH4_D_p			=0,  
		  BPP_ICH5_CEN_p		=0;
	float BPS_IS1_nsw_s			=0, 
		  BPS_IS1_Diff			=0,
		  BPS_IS1_nswHF_s		=0,
		  BPS_IS2_sw_s			=0,
		  BPS_IS2_Diff			=0,
		  BPP_IS2_6p2_p			=0, 
		  BPP_IS2_VBPP_p		=0;
	float BPS_ICH3_VO_5v_S		=0, 
		  BPS_ICH3_4V_VO_5v_S	=0, 
		  BPS_ICH3_4V_VO20v_S	=0, 
		  BPS_ICH2_4V_FW11V_s	=0;
	float VO_S					=0, 
		  VBPS_S				=0;
	float Delta_VO_minus_VBPS_S	=0;
	float Vsr_clamp				=0.0,
		  Isr_clamp				=0.0,
		  Rsr_clamp				=0.0,
		  ISRclamp_S			=0.0;
	float LowerLimit = 0;
	float BP_supply_TT = 0;
	Pulse pulse;			//external trigger pulse from dvi for debug
	//

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//						BPP and BPS Charge Current
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Negative cycle BPP pin //
	VBPP_Negative_Cycle();
	VBPP_Negative_Cycle();

	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	Close_relay(K2);
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	
	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 190.0e-3, RANGE_300_MA); // Clamp to 190mA to reduce device damage

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
	wait.delay_10_us(250); 

	// Powerup //
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	//wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ICH1_3V_FW-S (FW=45V, BPS=3V, Drain=45V, BPP=0V)
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Because Secondary get damaged easily with high current coming from FW, Secondary 
	// is not testing at vBPS=0V. Temporary set vBPS=3V so the potential difference 
	// between FW and BPS is less and current would be less so device won't be damaged.
	// Current is also limited from FW source from 300mA to 190mA to prevent device damage. //
	// FW =45V
	// BPS =3V
	// Drain =45V 
	// BPP =0V
	// Vout = 0V/100mA, 10Vrange/300mARange

	// Drain set to 45V/300mA
	D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE); // DVI_11_0
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);	
	VBPS_ramp_up(0, 4.0, 0.05);
	wait.delay_10_us(100);


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ICH2_4V_FW-S,  ICH2_4V_FW11v-S
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// FW =45V
	// BPS =vPlus+150mV->4V "2ndary PU and back down to 4V"  (new)
	// Drain =45V 
	// BPP =4V
	// Vout = 0V/100mA, 10Vrange/300mARange
	VBPP_ramp_up(0, 4, 0.3); // vstart, vstop, vstep	
	wait.delay_10_us(50);

	// Set FW //
	FW_dvi->set_voltage(FW_ch, 11.0, VOLT_50_RANGE); // DVI
	wait.delay_10_us(120);

	// Powerup for next test //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(20);

	// ICH2_4V_FW11v-S //
	// Bring down BPS //
	BPS_dvi->set_voltage(BPS_ch, 4, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(50);
	BPS_ICH2_4V_FW11V_s = BPS_dvi->measure_average(25);

	// ICH2_4V_FW-S //
	FW_dvi->set_voltage(FW_ch, 45.0, VOLT_50_RANGE); // DVI_11_1
	wait.delay_10_us(120);
	BPS_ICH2_4V_s = BPS_dvi->measure_average(25);

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ICH3_4V_VO_5v-S
	// ICH3_3V_VO_5v-S
	// ICH3_4V_VO_20v-S
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// FW =0V
	// BPS =4V
	// Drain =45V 
	// BPP =4V
	// Vout = 5V/100mA, 10Vrange/300mARange	(measure current from Vout)
	FWrampDown(45, 0, 2); // Ramp down to prevent BPS pull down //
	VO_dvi->set_voltage(VO_ch, 5.0, VOLT_10_RANGE); // DVI_9_0
	wait.delay_10_us(20);
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	// From Inno3X //
	// DPG- leave for now and check if TMT43 is still a problem //
		//TMT43 require Secondary to bring BPS up to vPlus + 50mV because the first power-up has a big dip due to FW high.
		//Here is with FW at 0V and it's able to bring BPS high without dip so it's really PU.
	//	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 		VOLT_10_RANGE);	// DVI_9_1
	//	wait.delay_10_us(10);
	// From Inno3X //

	//BPS =4V
	BPS_dvi->set_voltage(BPS_ch, 4.0, VOLT_10_RANGE); // DVI_9_1
	wait.delay_10_us(100);
	BPS_ICH3_4V_VO_5v_S = VO_dvi->measure_average(25);

	//Vout = 20V
	VO_dvi->set_voltage(VO_ch, 20.0, VOLT_50_RANGE); // DVI_9_0
	wait.delay_10_us(300);
	BPS_ICH3_4V_VO20v_S = VO_dvi->measure_average(25);

	//Vout = 5V/100mA, 10Vrange/300mARange	(measure current from Vout)
	//BPS	=3V								(new)
	VOUTrampDown(20, 5, 2);
	wait.delay_10_us(20);
	VBPS_ramp_down(4, 3, 0.1);
	wait.delay_10_us(100);
	BPS_ICH3_VO_5v_S = VO_dvi->measure_average(25);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPP_ICH2_4V_D-P (FW=45V, BPS=3V, Drain=45V, BPP=4V)
	// BPP_ICH3_CEN-P  (FW=45V, BPS=3V, Drain=45V, BPP=(VBPP_P + VBPP_M)/2)
	// BPP_ICH4_4V_D-P (FW=45V, BPS=3V, Drain=45V, BPP=> PV_final then 4V)
	// BPP_ICH5_CEN-P  (FW=45V, BPS=3V, Drain=45V, BPP=(VBPP_P + VBPP_M)/2)
	//
	//								_______ BPP_PV_final
	//					   /\	   /
	//				  (3)_/  \_(4)/_(5)
	//					 /    \  /
	//					/	   \/__________ gVBPP_M_Init-0.2
	//			   (2)_/		
	//				  /
	//			 (1)_/
	//
	//			 (1) BPP_ICH1_0V_p
	//			 (2) BPP_ICH2_4V_D-P
	//			 (3) BPP_ICH3_CEN-P
	//			 (4) BPP_ICH4_4V_D-P
	//			 (5) BPP_ICH5_CEN-P
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	VOUTrampDown(5, 0, 0.5);
	VBPS_ramp_down(3, 0, 0.1);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE);
	VBPP_ramp_down(4, 0, 0.05);
	wait.delay_10_us(100);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ICH2_4V_D-P (FW=45V, BPS=3V, Drain=45V, BPP=4V)
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// FW =45V
	// BPS =3V
	// Drain =45V 
	// BPP =4V (new)
	// Vout = 0V/100mA, 10Vrange/300mARange

	D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE);
	wait.delay_10_us(100);
	BPP_ovi->set_voltage(BPP_ch, 4.0, RANGE_10_V);
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(200);
	BPP_ICH2_4V_p = BPP_ovi->measure_average(10);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ICH1_0V_D-P (Drain=45V, BPP=0V)
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //	
	// BPP set to 0V/30mA with current_meas_mode
	//BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0
	//BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	//wait.delay_10_us(500);
	//BPP_ICH1_0V_p = BPP_ovi->measure_average(10);	

	// BPP set to 0V/30mA with current_meas_mode
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE);
	wait.delay_10_us(100);
	VBPP_ramp_down(4, 0, 0.2);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE);
	wait.delay_10_us(500);
	BPP_ICH1_0V_p = BPP_ovi->measure_average(10);	

	// BPP_ICH3_CEN_p
	VBPP_ramp_up(0, 4, 0.3); // vstart, vstop, vstep	
	VBPP_ramp_up(gVBPP_VCEN-0.5, gVBPP_VCEN, 100e-3);
	wait.delay_10_us(10);
	BPP_ICH3_CEN_p = BPP_ovi->measure_average(10);	

	// BPP_ICH4_D_p
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_PV_final, RANGE_10_V); // OVI_1_0
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN, RANGE_10_V); // OVI_1_0
	wait.delay_10_us(100);
	BPP_ICH4_D_p = BPP_ovi->measure_average(10);	

	//  BPP_ICH5_CEN_p
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-0.2, RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN, RANGE_10_V); // OVI_1_0
	wait.delay_10_us(50);
	BPP_ICH5_CEN_p = BPP_ovi->measure_average(10);	


	// Powerdown //
	Open_relay(K2);
	Open_relay(K18);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0
	VBPP_ramp_down(4, 0, 0.3);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_20_RANGE); // DVI_9_0
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(0.5, 0, 0.1);
	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1
	FB_ovi->connect(2);
	wait.delay_10_us(100); // Waits for relays //


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//  R_SRclamp-S
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //	
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	//Close_relay(K2);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_5_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //

	// FB (COMP) //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
	//BPS_dvi->set_current(BPS_ch, 5.0e-3, RANGE_300_MA);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1
	SR_dvi2k->set_voltage(SR_ch, 5.0, VOLT_5_RANGE); // -.3 DVI_21_0
	SR_dvi2k->set_current(SR_ch, 10e-3,	RANGE_20_MA); // -1.0
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(25);
	Vsr_clamp = SR_dvi2k->measure_average(15);
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(25);
	Isr_clamp = SR_dvi2k->measure_average(25);
	Rsr_clamp = Vsr_clamp / Isr_clamp;

	// Powerdown //
	Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
//	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	FB_ovi->connect(2);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	SR_dvi2k->set_voltage(SR_ch, 0, VOLT_5_RANGE); // -.3 DVI_21_0
	SR_dvi2k->set_current(SR_ch, 20e-3,	RANGE_20_MA); // -1.0
	wait.delay_10_us(200); // Wait for relays //

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPS_IS1_nsw-S, BPS Pin Current at No-Load
	// Measure BPS supply current at no load with VBEN (aka VBUS) disabled. With VBUS 
	// disabled, internal system clock is only running ~300kHz, instead of ~3MHz. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPS_IS1_nsw_s = gIBPS_nsw;	//This test is done in the VBP_Supply.cpp function //
	BPS_IS1_Diff = BPS_IS1_nsw_s - g_BPS_IS1_Pre;

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BPS_IS1_nswHF-S, BPS Pin Current at No-Load
	// Measure BPS supply current at no load with VBEN (aka VBUS) enabled. With VBUS 
	// enabled, internal system clock increases to ~3MHz from ~300kHz. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPS_IS1_nswHF_s = gIBPS_nswHF;	//This test is done in the VBP_Supply.cpp function //

	//************************************************************
	//** IS2_S (Switching and should be done with SR switching) **
	//************************************************************
	// Note: This test couldn't be done from Fosc-S because SR pin has to be shorted to see 132kHz.  If SR not shorted, it's 126kHz

	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	// Negative cycle BPP pin //
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
//	if (g_OPCODE==4300 || g_OPCODE==4500)
//	{
//		if (!strnicmp(Part_ID_LimitSet, "SC1750", 6) ||!strnicmp(Part_ID_LimitSet, "SC1738", 6))
//		{
//			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.25, VOLT_20_RANGE); // OVI_1_4
//		}
//	}

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

	// Powerup secondary //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C secondary into test mode- because soft start is disabled in test mode. //  
//	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

//	Write_Byte(g_VBEN, 0x83, NObin, HEX); // Turn on VBD drive //

//	Write_Byte(g_FWPK_reg, 0x00, NObin, HEX); // Disable FW peak peak switch function. //
DSM_Write_Byte(g_FWPK_reg, 0x00); // Disable FW peak peak switch function. //
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

	// Setup inv_syn_circuit low output //
	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.3, VOLT_5_RANGE);	// inv_syn_circuit //
	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);
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
	BPS_IS2_sw_s = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
	BPS_IS2_Diff = BPS_IS2_sw_s - g_BPS_IS2_Pre;

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
//	pv3_4->drive_off();	
	Open_relay(K3); // Drain to RL pullup
	VBPP_ramp_down(3, 0.0, 0.05);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//	FB_ovi->connect(2);
//	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
	Open_relay(K17); 
	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
	Disconnect_InvSyn_IM();
	Mux20_Open_relay(K38); // Disconnect SDA and SCL from DDD. //
	Mux20_Open_relay(K40); // Disconnect SDA and SCL from DDD. //
	Mux20_Open_relay(K64); // Disconnect SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, 0, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	Mux20_Open_relay(K50);
	Mux20_Open_relay(K59); // SR pin DVI_13_1, dvi2k //
	Open_relay(K5); // Disconnect 5nF Cap from SR //
	//Open_relay(K12); 
	//VPIN_ovi->connect(VPIN_ch);
		

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Open all relays //
//	Initialize_Relays();

	// Initialize Instruments //
//	Initialize_Instruments();

	// Drain //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
//	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 0.1e-9, RANGE_30_UA); // DVI_9_1, float //
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// COMP //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// SDA //
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //

	// SCL //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //

	// Wait for relays //
	//wait.delay_10_us(200); 

	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
	wait.delay_10_us(1000);
	VO_S = VO_dvi->measure_average(5);
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE); // DVI_9_1 //
	wait.delay_10_us(20);
	VBPS_S = BPS_dvi->measure_average(5);
	Delta_VO_minus_VBPS_S = (VO_S - VBPS_S);

	// Powerdown //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(10);
	BPS_dvi->set_voltage(BPS_ch, 2.5, VOLT_10_RANGE); // DVI_9_1, prevent undershoot //
	BPS_dvi->set_current(BPS_ch, 3e-3, RANGE_3_MA); // DVI_9_1, prevent undershoot //
	wait.delay_10_us(270);
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	FB_ovi->connect(2);
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(0.5, 0, 0.1);
//	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	wait.delay_10_us(100);

	// Datalog //
	PiDatalog(func, A_BPP_ICH1_0V_p, BPP_ICH1_0V_p, 12, POWER_MILLI);	
//	PiDatalog(func, A_BPS_ICH1_3V_s, BPS_ICH1_3V_s, 12, POWER_MILLI);	
	PiDatalog(func, A_BPP_ICH2_4V_p, BPP_ICH2_4V_p, 12, POWER_MILLI);	
	PiDatalog(func, A_BPS_ICH2_4V_s, BPS_ICH2_4V_s, 12, POWER_MILLI);	
	PiDatalog(func, A_BPS_ICH2_4V_FW11V_s, BPS_ICH2_4V_FW11V_s, 12, POWER_MILLI);
	if (gSiOption_s == 2304 || gSiOption_s == 6400) // 2304: SET Rev C silicon, 6400: JSC Rev C silicon //
	{
		PiDatalog(func, A_R_SRclamp_S, Rsr_clamp, 17, POWER_UNIT);
	}
	else if (gSiOption_s == 2305 || gSiOption_s == 6401) // 2305: SET Rev C1 silicon, 6401: JSC Rev C1 silicon //
	{
		PiDatalog(func, A_R_SRclamp_C1, Rsr_clamp, 17, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_R_SRclamp_C1, -999, 17, POWER_UNIT);
	}
	PiDatalog(func, A_BPP_ICH3_CEN_p, BPP_ICH3_CEN_p, 12, POWER_MILLI);	
	PiDatalog(func, A_BPS_ICH3_VO_5v_S, BPS_ICH3_VO_5v_S, 12, POWER_MILLI); // Added per Sheng 05/16/14  HQL
	PiDatalog(func, A_BPS_ICH3_4V_VO_5v_S, BPS_ICH3_4V_VO_5v_S, 12, POWER_MILLI);
	PiDatalog(func, A_BPS_ICH3_4V_VO20v_S, BPS_ICH3_4V_VO20v_S, 12, POWER_MILLI);
	PiDatalog(func, A_Delta_VO_minus_VBPS_S, Delta_VO_minus_VBPS_S, 12, POWER_MILLI);
	PiDatalog(func, A_BPP_ICH4_D_p, BPP_ICH4_D_p, 12, POWER_MILLI);	
	PiDatalog(func, A_BPP_ICH5_CEN_p, BPP_ICH5_CEN_p, 12, POWER_MILLI);	
	PiDatalog(func, A_BPS_IS1_nsw_s, BPS_IS1_nsw_s, 12, POWER_MICRO);
	if (g_Trim_Enable_P == 1) // Only tested for virgin part. //
	{
		PiDatalog(func, A_BPS_IS1_Diff, BPS_IS1_Diff, 12, POWER_MICRO);
	}
	PiDatalog(func, A_BPS_IS1_nswHF_s, BPS_IS1_nswHF_s, 12, POWER_MICRO);
	PiDatalog(func, A_BPS_IS2_sw_s, BPS_IS2_sw_s, 12, POWER_MILLI);	
	if (g_Trim_Enable_P == 1) // Only tested for virgin part. //
	{
		PiDatalog(func, A_BPS_IS2_Diff, BPS_IS2_Diff, 12, POWER_MILLI);	
	}
	PiDatalog(func, A_BPP_IS1_nsw_P, g_BPP_IS1_nsw_P, 12, POWER_MICRO); // Measured in Fosc_post_S.cpp //
	if (g_Trim_Enable_P == 1) // Only tested for virgin part. //
	{
		PiDatalog(func, A_BPP_IS1_Diff, g_BPP_IS1_Diff, 12, POWER_MICRO); // Measured in Fosc_post_S.cpp // 
	}
	PiDatalog(func, A_BPP_IS2_sw_P, g_BPP_IS2_sw_P, 12, POWER_MILLI); // Measured in Fosc_post_S.cpp //
	if (g_Trim_Enable_P == 1) // Only tested for virgin part. //
	{
		PiDatalog(func, A_BPP_IS2_Diff, g_BPP_IS2_Diff, 12, POWER_MILLI); // Measured in Fosc_post_S.cpp //
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		BP_supply_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, IBP_Supply_TT, BP_supply_TT, 12, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
