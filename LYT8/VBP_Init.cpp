//==============================================================================
// VBP_Init.cpp (User function)
// 
//    void VBP_Init_user_init(test_function& func)
//    void VBP_Init(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "VBP_Init.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VBP_Init_user_init(test_function& func)
{
	VBP_Init_params *ours;
    ours = (VBP_Init_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)fpid


// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VBP_Init(test_function& func)
{
    // The two lines below must be the first two in the function.
    VBP_Init_params *ours;
    ours = (VBP_Init_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VBP_init, gFuncNum, 12, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	//if (g_Fn_VBP_Init == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Declare Variables //
	double ID_1V_2V =0;
	float Vshunt_Init_Pr =0;
	float Vshunt_Init_Se =0;
	float VBPP_P_Init =0; 
	float VBPP_M_Init =0; 
	float VBPP_HYS_Init =0; 
	float VBPP_PV_Init =0;
	float VBPP_P_iHVoff =0; 
	float VBPP_Vshunt_PUseq =0;
	float VBPS_P_Init =0; 
	float VBPS_M_Init =0; 
	float VBPS_HYS_Init =0;
	int IS_Buff_Check = -99;
	float IS_Buff_Value = -99;
	float IS_buff_Mid = -99;
	float IS_buff_Low = -99;
	float IS_buff_ovi = -99;
	int VBP_Init_debug =0;
	float UpperLimit_BPP = 0;
	float UpperLimit_BPS = 0;
	float LowerLimit = 0;
	double V_hp_meter = 0;
	float IsCalVolt = 0;
	float ISvolt_ovi = 0;
	float VBP_Init_TT = 0;
	float UpperLimit_VBPP_s = 0;
	//int k=0;
	//float bpp_current[300] = {0};
	//float vstep=5e-3;
	//float vBPP_start=0;
	float VBPP_P_S_Init_S=0;
	char STRINGarray[1024] = {'\0'};//buffer to store formatted input.
	Pulse pulse;

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 							1V 2V tests										
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//Close_relay(K2); // Drain
	//Close_relay(K18); // FW

	// Disconnect UV(Itag) pin to stop it from pulling 0.5mA from device in normal mode. 
		UV_dvi->set_voltage(UV_ch, 0,		VOLT_10_RANGE);  
		UV_dvi->set_current(UV_ch, 10e-3,	RANGE_30_MA);		
		delay(2);
	//Drain 2V, BPP 1V, measure current from Drain to see how much current is traveling through from Drain to BPP.  Ideally 0A
		D_dvi->set_voltage(D_ch, 2.0, VOLT_2_RANGE);
		D_dvi->set_current(D_ch, 200e-3, RANGE_300_MA);		
		BPP_dvi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		BPP_dvi->set_voltage(BPP_ch, 1, VOLT_10_RANGE); // OVI_1_0
		D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
		wait.delay_10_us(500);
		D_dvi->set_current(D_ch, 29e-6, RANGE_30_UA);
		wait.delay_10_us(800);
		ID_1V_2V = D_dvi->measure_average(10);
	//Drain 0V, BPP 0V
		VBPP_ramp_down(1, 0.0, 0.05);
		D_dvi->set_current(D_ch, 30e-3, RANGE_300_MA);	
		D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);  
	//Datalog
		PiDatalog(func, A_ID_1V_2V, ID_1V_2V, 11, POWER_MICRO);	

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 	VShunt_2mA-P										
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//FW_dvi->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); //Redue noise for secondary
	//Open_relay(K2);
	Close_relay(K2_D_RB); // Drain to L1,R27 pullup from dvi-11-0
	delay(3);
	//BPP 
	BPP_dvi->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);  
	wait.delay_10_us(100);

	//Powerup BPP zigzag. I_BPP ~ 15mA
	VBPP_ramp_up(0, 5.5, 100e-3);
	VBPP_ramp_down(5.5, 4.3, 50e-3);
	BPP_dvi->set_current(BPP_ch, 2.0e-3, RANGE_30_MA);
	VBPP_ramp_up(4.3, 5.5, 50e-3);
	wait.delay_10_us(50);
	wait.delay_10_us(200);
	Vshunt_Init_Pr = BPP_dvi->measure_average(10);

	PiDatalog(func, A_Vshunt_Init_Pr, Vshunt_Init_Pr, 12, POWER_UNIT);	

	////// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////// 	VShunt_2mA-S									
	////// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	////UpperLimit_BPS = (func.dlog->tests[A_Vshunt_Init_Se].f_max_limit_val[0])*1.1;
	////BPS_dvi->set_current(BPS_ch, 2e-3, RANGE_3_MA);
	////VBPS_ramp_up(0, UpperLimit_BPS, 200e-3);
	////BPS_dvi->set_voltage(BPS_ch, UpperLimit_BPS, VOLT_10_RANGE);  
	////wait.delay_10_us(20);
	////BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); //Reduce noise for Primary
	////wait.delay_10_us(500);
	////Vshunt_Init_Se = BPS_dvi->measure_average(10);
	////gVshunt_Init_Pr = Vshunt_Init_Pr;
	////gVshunt_Init_Se = Vshunt_Init_Se;

	////// Powerdown BPS //
	////BPS_dvi->set_voltage(BPS_ch, 3.5, VOLT_10_RANGE); // Prevent undershoot //
	////wait.delay_10_us(100); // Must wait //
	////BPS_dvi->set_current(BPS_ch, 100e-3, RANGE_300_MA);
	////VBPS_ramp_down(3.5, 0, 100e-3);
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);  
	////wait.delay_10_us(10);

//if(1)
//{
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// 					Primary: VBPP_Init_P, VBPP_Init_M, VBPP_Init_HYS
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	VBPP_ramp_down(3, 0.0, 0.05);
//	BPP_dvi->set_current(BPP_ch, 30e-3, RANGE_30_MA);   
//	BPP_dvi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
//	wait.delay_10_us(30);
//	LowerLimit = (func.dlog->tests[A_VBPP_P_Init].f_min_limit_val[0]); // Get lower search limit //
//	search_VBPP_th(&VBPP_PV_Init, &VBPP_M_Init, &VBPP_P_Init, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq, LowerLimit);
//	
//	// Save global variables for later //
//	gVBPP_PV_Init = VBPP_PV_Init;
//	gVBPP_PV_final = VBPP_PV_Init + 0.05;
//	gVBPP_P_Init = VBPP_P_Init;
//	gVBPP_P_final = VBPP_P_Init + 0.05;
//	gVBPP_M_Init = VBPP_M_Init;
//	if (gVBPP_M_Init > 5.3) // Prevent setting BPP too high later in test program. //
//	{
//		gVBPP_M_Init = 0;
//		g_Error_Flag = -201;
//	}
//
//	// Power down VBPP test
//	VBPP_ramp_down(3, 0.0, 0.05);
//
//	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
//	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0	
//	wait.delay_10_us(5);
//	//Open_relay(K3);			   
//
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// 					Secondary: VBPS_Init_P, VBPS_Init_M, VBPS_Init_HYS				  
//	// VBPS_Init_P:																		  
//	//  Chip consumption is the same at different states for secondary when device is not  
//	//  switching. Power up FW pin to see state transition by checking charge current. 	  
//	//  NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  
//	//                            +200uA													  			
//	// 				 -20mA /----------------											  
//	// 					  /											            		  	
//	// 	BPS Pin			 /	                                                              
//	// 	FW =6V   	    /                                                                 
//	// 																				      
//	// VBPS_Init_M:																		  
//	// 	In order to find VBPS_Init_M, allow device to switch, chip consumption should drop
//	//   when VBPS_Init_M threshold is reached and switching is off.	Need two neg pulses on
//	//   to allow Secondary to switch													  
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// VBPS_P_Init & VBPS_M_Init
//	// K18 was closed above
//	BPS_dvi->set_current(BPS_ch, 100e-3, RANGE_300_MA);	 
//	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA);	 
//	FW_dvi->set_voltage(FW_ch, 6.0, VOLT_10_RANGE);	 
//	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
//	wait.delay_10_us(200);
//	search_VBPS_P_th(&VBPS_P_Init, 0);
//	gVBPS_P_Init = VBPS_P_Init;
//	gVBPS_final = VBPS_P_Init + 0.05;
//
//	search_VBPS_M_th_Inno4(&VBPS_M_Init);
//	gVBPS_M_Init = VBPS_M_Init;
//	VBPS_HYS_Init = VBPS_P_Init - VBPS_M_Init;
//
//	// Powerdown //
//	Open_relay(K18);
//	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // OVI_1_1 //
//	UV_dvi->set_current(UV_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//	uVCC_ovi->set_voltage(uVCC_ch, 1.0, RANGE_10_V); // OVI_3_2 //
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	wait.delay_10_us(30);
//	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
//	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	
//	VBPS_ramp_down(3, 0, 200e-3);	
//	uVCC_ramp_down(1, 0, .05);
//	uVCC_ovi->set_voltage(uVCC_ch, 0, RANGE_10_V); // OVI_3_2 //
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE);	
//	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA);	 
//	wait.delay_10_us(200);
//	 
//
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// VBPP_P_S_Init_S
//	// VBBP_P with secondary in control
//	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//
//	// Open all relays //
//	Initialize_Relays();
//
//	// Initialize Instruments //
//	Initialize_Instruments();
//
//	// Drain //
//	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
//	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
//	Close_relay(K3); // Drain to dvi through pullup resistor. //
//
//	// FW //
//	Close_relay(K18);
//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//	FW_dvi->set_current(FW_ch, 300e-3, RANGE_300_MA); // DVI_11_1 //
//	
//	// BPS //
//	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);
//
//	// IS //
//	IS_dvi2k->set_voltage(IS_ch, 0, VOLT_50_RANGE);
//	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);
//
//	// Setup Vpin for DDD clocking //
//	ovi_1->disconnect(OVI_CHANNEL_1);
//	
//	// Setup DDD //
//	// DDD level //
//	g_DDD_Low = 0.0; // Save current value //
//	g_DDD_High = 4.0; // Save current value //
//	wait.delay_10_us(g_DDDwait);
//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//	wait.delay_10_us(g_DDDwait);
//	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//	wait.delay_10_us(10);
//	Close_relay(K12); // Connect DDD7_1	to Vpin //
//	wait.delay_10_us(300); // Wait for all relays //
//
//	// Remove latchoff problem. //
//	VBPP_Negative_Cycle();
//	VBPP_Negative_Cycle();
//	wait.delay_10_us(10);
//	BPP_dvi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
//	wait.delay_10_us(10);
//
//	// Primary Power up with normal mode and TM6 //
//	VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep //	
//	wait.delay_10_us(2);
//
//	// Vpin pulse 6 times for test mode 6. //
//	// In test mode 6 the Vpin becomes the receiver input. //
//	ddd_7->ddd_run_pattern(Vpin_6clocks_start,Vpin_6clocks_stop);	
//	wait.delay_10_us(5);
//
//	// be able to see AF links properly
//	D_dvi->set_voltage(D_ch, 40.0, VOLT_50_RANGE); // DVI_11_0 //	
//	wait.delay_10_us(50);
//
//	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
//
//	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0	
//	wait.delay_10_us(5);
//	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
//	wait.delay_10_us(3); // 1.0 uF (ILIM) 30us for ILIM NORM
//
//	// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
//	BPP_dvi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
//	wait.delay_10_us(50);
//
//	BPP_dvi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//	wait.delay_10_us(1);
//	VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_Init + 0.05, 10e-3); // vstart, vstop, vstep //
//	wait.delay_10_us(10);
//	
//	// Two pulses 30usec apart to give control to secondary. //
//	D_dvi->set_voltage(D_ch, 25, VOLT_50_RANGE); // DVI_11_0
//	wait.delay_10_us(20);
//
//	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);
//	wait.delay_10_us(20);
//	ddd_7->ddd_end_pattern(Vpin_loop_pulse_stop);	//K12 needs to be closed for DDD connect to Vpin
//	wait.delay_10_us(20); 
//	ddd_7->ddd_run_pattern();
//	delay(5);
//
//	BPP_dvi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
//
//	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0
//	wait.delay_10_us(50);
//
//	k=0;
//	vstep = 5e-3;
//	vBPP_start = 5.4;
//	while(k<299)
//	{
//		k++;
//		BPP_dvi->set_voltage(BPP_ch, vBPP_start-k*vstep, RANGE_10_V); // Starting search point
//		wait.delay_10_us(5);
//		bpp_current[k] = BPP_dvi->measure_average(5);
//		if(bpp_current[k]<-0.6e-3)
//		{
//			VBPP_P_S_Init_S = vBPP_start-k*vstep;
//			break;
//		}
//	}
//	g_VBPP_P_S_Init_S = VBPP_P_S_Init_S;
//	VBPP_HYS_Init = VBPP_P_S_Init_S - VBPP_M_Init;
//
//	// Power down //
//	Open_relay(K18);
//	Open_relay(K3);
//	ddd_7->ddd_stop_pattern();
//	wait.delay_10_us(1);
//	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);	
//	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
//	VBPP_ramp_down(3, 0.0, 0.2);
//	BPP_dvi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//	ovi_1->connect(OVI_CHANNEL_1);
//	Open_relay(K12);
//
//	// DDD level //
//	//g_DDD_Low = 0.0; // Save current value //
//	//g_DDD_High = 4.0; // Save current value //
//	//wait.delay_10_us(100);
//	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//	wait.delay_10_us(200);
//
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// Check IS pin 20X buffer (OP27) //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// Use HP meter to calibrate IS pin buffer //
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	//HP 34401A internal meter setup
//	//---------------------------------------------------------------------------------
//	//Use left/right arrows < > to scroll through the menus and up/down (^ v) on the
//	//front panel to select the menu you want.
//	//
//	//step 1.	Enter into the menus (push SHIFT and ON/OFF)
//	//step 2.	Select "I/O" menu (there are 5 sub menus as next)
//	//step 3.	Select as follows;
//	//
//	//		GPIB_ADDR:		22
//	//		INTERFACE:		RS232
//	//		BAUD:			9600
//	//		PARITY:			8 Bits
//	//		LANGUAGE:		SCPI
//	//
//	//Step 4.	Exit the menu
//	//Step 5.	Press FRONT/REAR butTon to select "REAR"
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// First measure IS pin with HP meter.  Also, measure with ovi to double check. //
//	// Measure IS pin with ovi as a second check to be sure. //
//	// Must be powered up to measure the IS pin Op Amp 20X gain accurately.  I think the input impedance on 
//	// IS pin is different after powerup, which affects the gain measurement. //
//	// Open all relays //
////	Initialize_Relays();
//
//	// Initialize Instruments //
////	Initialize_Instruments();
//
//	// FW //
//	Close_relay(K18);
//	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//
//	// SR //
//	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
//
//	// BPS //
//	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//
//	// IS //
//	mux_14->close_relay(MUX_2_GND);
//	Close_relay(K24); // Connect IS pin to 20X buffer. //
//	wait.delay_10_us(300); 
//	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//	IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //
//	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_1_V); // OVI_3_4 //
//	IS_ovi->set_current(IS_ovi_ch, 0.1e-9, RANGE_30_UA); // OVI_3_4, float //
//	IS_ovi->set_meas_mode(IS_ovi_ch, OVI_MEASURE_VOLTAGE); // OVI_3_4 //
//	Mux20_Close_relay(K48); // Connect ovi to IS pin for measure. //
//	Close_relay(K71); // Connect HP meter. K71 with new hand wiring. //
//
//	// Vout //
//	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
//	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//
//	// FB (COMP) //
//	FB_ovi->disconnect(2);
//
//	// VBD //
//	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//	wait.delay_10_us(25); // Prevent glitch //
//	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//
//	// uVCC //
//	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//		
//	// Wait for relays //
//	wait.delay_10_us(300); 
//
//	// Powerup //
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//	wait.delay_10_us(100);
//	
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// IS_Buff_Value
//	// Get IS pin buffer gain at 32mV //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// IS pin //
//	IsCalVolt = 0.67783; // IS pin is connected to 21X buffer. (1000ohm + 49.9ohm) / 49.90hm = 21.04008.  From GRR data, mean = 21.1823. Dvi votlage = 0.032*21.1823 = 0.67783  //
//	IS_dvi2k->set_voltage(IS_ch, IsCalVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//	wait.delay_10_us(100);
//
//	// HP meter, measure IS pin voltage. //
//	// Only calibrate first passing part in lot. //
//	if (g_FirstPartPass == 0 && g_HP_meter_cal_done == 0)
//	{
//		//g_comm->set_meter_config(METER_VOLTS_DC, METER_1_V, METER_SLOW_RATE);
//		g_comm->set_meter_config(METER_VOLTS_DC, METER_100_MILLI_V, METER_SLOW_RATE);
//		//wait.delay_10_us(1000); //Fast CPU may need this delay
//		wait.delay_10_us(3000); //Fast CPU may need this delay
//		g_comm->stable_meter_reading(V_hp_meter, 0.5);	// 0.0005 accuracy settings for meter
//		g_ISbuff_Gain32 = IsCalVolt / V_hp_meter;
//	}
//	IS_Buff_Value = g_ISbuff_Gain32;
//
//	// Check results //
//	IS_Buff_Check = 1; // Default is pass //
//	if(g_ISbuff_Gain32 < 20.735 || g_ISbuff_Gain32 > 21.5895) // Limits based on GRR data (mean +/- 2*RR) //
//	{
//		IS_Buff_Check = -99;
//		g_Error_Flag = -190;
//		AbortTest = 1;
//		//MessageBox(NULL, "Be sure meter cable is connected.  IS pin buffer error.", "Error", MB_OK|MB_TOPMOST);
//		sprintf(STRINGarray,"Be sure meter cable is connected.  IS pin buffer error.  g_ISbuff_Gain32. \n\n%f\n", g_ISbuff_Gain32);
//		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
//	}
//
//	// Check IS pin voltage with ovi //
//	IS_ovi->set_meas_mode(IS_ovi_ch, OVI_MEASURE_VOLTAGE); // OVI_3_4 //
//	wait.delay_10_us(20);
//	IsCalVolt = .032*g_ISbuff_Gain32; // IS pin is connected to 21X buffer. (1000ohm + 49.9ohm) / 49.90hm = 21.04008.  From GRR data, mean = 21.1823. Dvi votlage = 0.032*21.1823 = 0.67783  //
//	IS_dvi2k->set_voltage(IS_ch, IsCalVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//	wait.delay_10_us(150);
//	ISvolt_ovi = IS_ovi->measure_average(50);
//	//if (ISvolt_ovi < 0.0313 || ISvolt_ovi > 0.0327)// Error //
//	if (ISvolt_ovi < 0.0295 || ISvolt_ovi > 0.033)// Error //
//	{
//		IS_Buff_Check = -99;
//		g_Error_Flag = -190;
//		AbortTest = 1;
//		//MessageBox(NULL, "Be sure meter cable is connected.  IS pin buffer error.", "Error", MB_OK|MB_TOPMOST);
//		sprintf(STRINGarray,"Be sure meter cable is connected.  IS pin buffer error.  ISvolt_ovi.\n\n%f\n", ISvolt_ovi);
//		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
//	}
//	IS_buff_ovi = ISvolt_ovi;
//
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// IS_buff_Mid
//	// Get IS pin buffer gain at 19mV //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// HP meter, measure IS pin voltage. //
//	// Only calibrate first passing part in lot. //
//	if (g_FirstPartPass == 0 && g_HP_meter_cal_done == 0)
//	{
//		// IS pin //
//		IsCalVolt = 0.40246; // IS pin is connected to 21X buffer. (1000ohm + 49.9ohm) / 49.90hm = 21.04008.  From GRR data, mean = 21.1823. Dvi votlage = 0.019*21.1823 = 0.40246  //
//		IS_dvi2k->set_voltage(IS_ch, IsCalVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//		wait.delay_10_us(100);
//		//g_comm->set_meter_config(METER_VOLTS_DC, METER_1_V, METER_SLOW_RATE);
//		g_comm->set_meter_config(METER_VOLTS_DC, METER_100_MILLI_V, METER_SLOW_RATE);
//		//wait.delay_10_us(1000); //Fast CPU may need this delay
//		wait.delay_10_us(3000); //Fast CPU may need this delay
//		g_comm->stable_meter_reading(V_hp_meter, 0.5);	// 0.0005 accuracy settings for meter
//		g_ISbuff_GainMid = IsCalVolt / V_hp_meter;
//	}
//	IS_buff_Mid = g_ISbuff_GainMid;
//
//	// Check results //
//	if(g_ISbuff_GainMid < 20.60 || g_ISbuff_GainMid > 21.5895) // Limits based on GRR data (mean +/- 2*RR) //
//	{
//		IS_Buff_Check = -99;
//		g_Error_Flag = -211;
//		AbortTest = 1;
//		//MessageBox(NULL, "Be sure meter cable is connected.  IS pin buffer error.", "Error", MB_OK|MB_TOPMOST);
//		sprintf(STRINGarray,"Be sure meter cable is connected.  IS pin buffer error.  g_ISbuff_GainMid.\n\n%f\n", g_ISbuff_GainMid);
//		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
//	}
//
//
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// IS_buff_Low
//	// Get IS pin buffer gain at 6.25mV //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// HP meter, measure IS pin voltage. //
//	// Only calibrate first passing part in lot. //
//	if (g_FirstPartPass == 0 && g_HP_meter_cal_done == 0)
//	{
//		// IS pin //
//		IsCalVolt = 0.13239; // IS pin is connected to 21X buffer. (1000ohm + 49.9ohm) / 49.90hm = 21.04008.  From GRR data, mean = 21.1823. Dvi votlage = 0.00625*21.1823 = 0.13239 //
//		IS_dvi2k->set_voltage(IS_ch, IsCalVolt, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//		wait.delay_10_us(100);
//		//g_comm->set_meter_config(METER_VOLTS_DC, METER_1_V, METER_SLOW_RATE);
//		g_comm->set_meter_config(METER_VOLTS_DC, METER_100_MILLI_V, METER_SLOW_RATE);
//		//wait.delay_10_us(1000); //Fast CPU may need this delay
//		wait.delay_10_us(3000); //Fast CPU may need this delay
//		g_comm->stable_meter_reading(V_hp_meter, 0.5);	// 0.0005 accuracy settings for meter
//		g_ISbuff_GainLow = IsCalVolt / V_hp_meter;
//	}
//	IS_buff_Low = g_ISbuff_GainLow;
//
//	// Check results //
//	if(g_ISbuff_GainLow < 20.185 || g_ISbuff_GainLow > 22) // Limits based on GRR data (mean +/- 2*RR) //
//	{
//		IS_Buff_Check = -99;
//		g_Error_Flag = -212;
//		AbortTest = 1;
//		//MessageBox(NULL, "Be sure meter cable is connected.  IS pin buffer error.", "Error", MB_OK|MB_TOPMOST);
//		sprintf(STRINGarray,"Be sure meter cable is connected.  IS pin buffer error.  g_ISbuff_GainLow.\n\n%f\n", g_ISbuff_GainLow);
//		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
//	}
//
//	// Powerdown //
//	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//	wait.delay_10_us(20);
//	Open_relay(K18);
//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//	mux_14->open_relay(MUX_2_GND);
//	Open_relay(K24); // Disconnect IS pin from 20X buffer. //
//	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_1_V); // OVI_3_4 //
//	IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //
//	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//	Mux20_Open_relay(K48); // Disconnect ovi from IS pin. //
//	Open_relay(K71); // Disconnect HP meter. K71 with new hand wiring. //
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	uVCCrampDown(1, 0, 0.1);
//	VBPS_ramp_down(4, 0.2, 200e-3);
//	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//	wait.delay_10_us(20);
//	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//	FB_ovi->connect(2);
//	wait.delay_10_us(200); // Wait for relays //
//
//	//Datalog
//	PiDatalog(func, A_Vshunt_Init_Se, Vshunt_Init_Se, 12, POWER_UNIT);
//	PiDatalog(func, A_VBPP_PV_Init, VBPP_PV_Init, 12, POWER_UNIT);	
//	PiDatalog(func, A_VBPP_M_Init, VBPP_M_Init, 12,	POWER_UNIT);	
//	PiDatalog(func, A_VBPP_P_Init, VBPP_P_Init, 12,	POWER_UNIT);	
//	PiDatalog(func, A_VBPP_P_S_Init_S, VBPP_P_S_Init_S, 12,	POWER_UNIT);
//	PiDatalog(func, A_VBPP_P_iHVoff, VBPP_P_iHVoff, 12, POWER_UNIT);	
//	PiDatalog(func, A_VBPP_HYS_Init, VBPP_HYS_Init, 12,	POWER_UNIT);
//	PiDatalog(func, A_VBPS_P_Init, VBPS_P_Init, 12,	POWER_UNIT);	
//	PiDatalog(func, A_VBPS_M_Init, VBPS_M_Init, 12,	POWER_UNIT);
//	PiDatalog(func, A_VBPS_HYS_Init, VBPS_HYS_Init, 12,	POWER_UNIT);
//	PiDatalog(func, A_IS_Buff_Check, IS_Buff_Check, 31, POWER_UNIT);
//	PiDatalog(func, A_IS_Buff_Value, IS_Buff_Value, 31, POWER_UNIT);
//	PiDatalog(func, A_IS_buff_Mid, IS_buff_Mid, 31, POWER_UNIT);
//	PiDatalog(func, A_IS_buff_Low, IS_buff_Low, 31, POWER_UNIT);
//	PiDatalog(func, A_IS_buff_ovi, IS_buff_ovi, 31, POWER_UNIT);
//
//	// DDD memory on TMT118 was getting erased periodically.  Suspect faulty DDD board.  Not a problem on any 
//	// other tester. When this occurs then every part afterward will start failing.  Only solution found is to 
//	// reload DDD memory. VBPP_P_S_Init-S test is the first failing test if this occurs so use this failure 
//	// as a flag to reload DDD memory. //
//	//UpperLimit_VBPP_s = (func.dlog->tests[A_VBPP_P_S_Init_S].f_max_limit_val[0]); // Get upper test limit. //
//	//if (VBPP_P_S_Init_S > UpperLimit_VBPP_s)
//	//	g_VBPP_P_S_FailFlag = 1;
//
//	if (VBPP_P_S_Init_S < 4.8)
//	{
//		VBPP_P_S_Init_S = 4.8;
//	}
//	g_VBPP_P_s_final = VBPP_P_S_Init_S + 0.05;
//
//	// Test Time End //
//	if (g_TstTime_Enble_P)
//	{
//		g_endtime = g_mytimer.GetElapsedTime();
//		VBP_Init_TT = (g_endtime - g_begintime)*1e-6;
//		PiDatalog(func, A_VBP_Init_TT, VBP_Init_TT, 12, POWER_MILLI);
//	}	
//
//	// Check any test failed //
//	if (PiGetAnyFailStatus())		
//	{
//		g_PartFailed = 1;
//	}
//}

	if(g_Char_vBPPth)
	{
		Characterize_vBPPth(); //
	}

}
