//==============================================================================
// VBP_Supply.cpp (User function)
// 
//    void VBP_Supply_user_init(test_function& func)
//    void VBP_Supply(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "VBP_Supply.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VBP_Supply_user_init(test_function& func)
{
	VBP_Supply_params *ours;
    ours = (VBP_Supply_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VBP_Supply(test_function& func)
{
    // The two lines below must be the first two in the function.
    VBP_Supply_params *ours;
    ours = (VBP_Supply_params *)func.params;

	// Increment function number //
	gFuncNum++;

//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_Func_Num_VBP_Supply, gFuncNum, 12, POWER_UNIT);
//////
//////	// Skip Test if AbortTest set //
//////	if (AbortTest)
//////		return;
//////
//////	if (g_Fn_VBP_Supply == 0 )  return;
//////
//////	// Test Time Begin //
//////	 if (g_TstTime_Enble_P)
//////	 	g_begintime = g_mytimer.GetElapsedTime();
//////	
//////	// Declare Variables //
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //
//////	float Ishunt_p =0.0;	
//////	float Ishunt_s =0.0; 
//////	float VBPP_P =0;			 
//////	float VBPP_M =0.0;		
//////	float VBPP_HYS =0.0;		
//////	float VBPP_PV =0.0;
//////	float VBPS_P =0.0; 		 
//////	float VBPS_M =0.0;		
//////	float VBPS_HYS =0.0;		
//////	float VBPP_P_iHVoff =0.0;	
//////	float VBPP_Vshunt_PUseq =0.0;
//////	float VBPP_Reset_p =0.0;  
//////	float VBPS_Reset_s =0.0; 
//////	float VBPS_Reset_Delta_s =0.0;
//////	float tLOff_Filter_S =0.0;
//////	float vfrc =0.0; 
//////	float ifrc =0.0; 
//////	float vstep =0.0; 
//////	float istep =0.0; 
//////	float iforce = 0;
//////	float tmeas =0.0;
//////	float ISD_s =0; 
//////	float VBPS_OV =0;
//////	int ISD_func_p =false;
//////	float LO_Expect_Time =0;
//////	float HI_Expect_Time =0;
//////	float VBP_Supply_TT =0;
//////	float vforce =0;
//////	int start =0; 
//////	int stop =0;
//////	//float tOVP_S =0.0;
//////	float ISD_p =0;
//////	float VSD_p = 0;
//////	float ChargePumpBPS = 0;
//////	float BPScurrent = 0;
//////	float Imeas = 0;
//////	float IdrainON = 0;
//////	int LoopCount = 0;
//////	float VBDmeasV = 0;
//////	int READ5_word[16] = {0};
//////	float MaxSearch = 0;
//////	float UpperLimit = 0;
//////	float LowerLimit = 0;
//////	float BPS_forceI = 0;
//////	float BPS_measV = 0;
//////	Pulse pulse;// External trigger pulse from dvi for debug //
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	//									ISD-P									    //
//////	// Ramp IBPP until device latches off (stops switching).					    //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	//								ISD:func-P										//
//////	// Go/No go functional test.  Make sure device can be brought out of			//
//////	// latchoff after ISD has occured.												//
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->init();
////// 	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(1.8,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(2.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->start_holdoff(0,FALSE);
//////	tmu_6->stop_holdoff(0,FALSE);
//////	wait.delay_10_us(10);
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
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
//////	// V pin //
//////	Close_relay(K12); // Connect DDD7_1 to Vpin(UV) pin
//////	VPIN_ovi->disconnect(VPIN_ch); // Disconnect ovi from Vpin, let DDD control Vpin. //
//////	wait.delay_10_us(200);
//////
//////	if (gTrim_AR_req_Trimops)
//////	{
//////		// Get search limit //
//////		UpperLimit = (func.dlog->tests[A_ISD_p].f_max_limit_val[0])*1.2; // Get upper search limit //
//////
//////		// Primary TM5 bypass Wait and Listen power up
//////		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////		wait.delay_10_us(50);
//////
//////		// Get ready for search. //
//////		// Check to make sure drain is initially switching. //
//////		vfrc = gVshunt_Init_Pr + .1;
//////		if (vfrc > 5.65) 
//////		{
//////			vfrc = 5.65; // OK to increase clamp to 5.75V per design (Lance) 10/19/2017 email.  Try 5.65V for now, goto 5.75V later if needed. //
//////		}
//////		ifrc = 3.0e-3;
//////		BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V); 
//////		BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////		wait.delay_10_us(10);
//////		VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep //
//////		wait.delay_10_us(10);
//////		tmu_6->arm();
//////		wait.delay_10_us(15);	
//////		tmeas = tmu_6->read(1e-3);
//////		istep = 0.5e-3;
//////		LO_Expect_Time = 1.0e-6;
//////		HI_Expect_Time = 100e-6;
//////		if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
//////		{
//////			// Rough search for ISD-P threshold. //
//////			while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < UpperLimit)
//////			{
//////					ifrc +=istep;
//////					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////					wait.delay_10_us(10);	// Provide enough time for device to stop switching
//////					tmu_6->arm();	
//////					wait.delay_10_us(10);				
//////					tmeas = tmu_6->read(1e-3);
//////			}
//////			
//////			// Fine search for ISD-P threshold. //
//////			VBPP_ramp_down(vfrc, gVBPP_M_Init-200e-3, 0.05); // Bring below VBP- to reset latch-off. //
//////			wait.delay_10_us(50); // Wait for BPP voltage to come down. //
//////			BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//////			VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_Init+50e-3, 0.05); // Bring back up to make sure part switches //
//////			tmu_6->arm();	
//////			wait.delay_10_us(10);				
//////			tmeas = tmu_6->read(100e-6);
//////			if ( (tmeas < LO_Expect_Time) || (tmeas > HI_Expect_Time) )
//////				g_Error_Flag = -216; // Fail.  Device is not switching correctly. //
//////			ifrc -= 1e-3;
//////			istep = 0.02e-3;	
//////			BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V);
//////			BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////			wait.delay_10_us(10);
//////			VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep - To reduce overshoot //
//////			wait.delay_10_us(10);
//////			tmu_6->arm();
//////			wait.delay_10_us(15);				
//////			tmeas = tmu_6->read(1e-3);
//////			if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
//////			{
//////				while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < UpperLimit)
//////				{
//////					ifrc +=istep;
//////					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////					wait.delay_10_us(15);	// Provide enough time for device to stop switching
//////					tmu_6->arm();	
//////					wait.delay_10_us(15);				
//////					tmeas = tmu_6->read(200e-6);
//////				}
//////			}
//////			else
//////			{		
//////				ISD_p = -999; // Device not switching. FAIL. //
//////			}
//////			ISD_p = ifrc;
//////
//////			// Check for error //
//////			if (g_Error_Flag == -216)
//////			{
//////				ISD_p = -999;
//////			}
//////
//////			// Measure the voltage at ISD_p //
//////			BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE); // OVI_1_0 //
//////			wait.delay_10_us(5);
//////			VSD_p = BPP_ovi->measure_average(5);
//////		}
//////		else
//////			ISD_p = -999; // Device not switching. FAIL. //
//////
//////		gISD_P = ISD_p;	// Save for later SR tests
//////	}
//////	else
//////	{
//////		// Get search limit //
//////		UpperLimit = (func.dlog->tests[A_ISD_p].f_max_limit_val[0])*1.2; // Get upper search limit //
//////
//////		// Primary TM5 bypass Wait and Listen power up
//////		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
//////		wait.delay_10_us(50);
//////
//////		// Get ready for search. //
//////		// Check to make sure drain is initially switching. //
//////		vfrc = gVshunt_Init_Pr + 0.1;
//////		if (vfrc > 5.65) 
//////		{
//////			vfrc = 5.65; // OK to increase clamp to 5.75V per design (Lance) 10/19/2017 email.  Try 5.65V for now, goto 5.75V later if needed. //
//////		}
//////		ifrc = 3.0e-3;
//////		BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V);
//////		BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////		wait.delay_10_us(10);
//////
//////		VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep //
//////		wait.delay_10_us(10);
//////		tmu_6->arm();
//////		wait.delay_10_us(15);				
//////		tmeas = tmu_6->read(1e-3);
//////		istep = 0.5e-3;
//////		LO_Expect_Time = 1.0e-6;
//////		HI_Expect_Time = 100e-6;
//////		if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
//////		{
//////			// Rough search for ISD-P threshold. //
//////			while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < UpperLimit)
//////			{
//////					ifrc +=istep;
//////					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////					wait.delay_10_us(10);	// Provide enough time for device to stop switching
//////					tmu_6->arm();	
//////					wait.delay_10_us(10);				
//////					tmeas = tmu_6->read();
//////			}
//////
//////			// Functional check.  Make sure latchoff can be removed by bring BP below VBP-. // 
//////			VBPP_ramp_down(vfrc, gVBPP_M_Init-200e-3, 0.05); // Bring below VBP- to reset latch-off. //
//////			wait.delay_10_us(50); // Wait for BPP voltage to come down. //
//////			//BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
//////			BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//////			VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_Init+50e-3, 0.05); // Bring back up to make sure part switches (i.e. make sure latchoff is removed). //
//////			tmu_6->arm();	
//////			wait.delay_10_us(10);				
//////			tmeas = tmu_6->read(100e-6);
//////			if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) )
//////				ISD_func_p = true; // Pass.  Latchoff is removed- drain switching. //
//////			else
//////				ISD_func_p = -999.0; // Fail.  Latchoff not removed- drain not switching. //
//////
//////			// Fine search for ISD-P threshold. //
//////			ifrc -= 1e-3;
//////			istep = 0.02e-3;	
//////			BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V);
//////			BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////			wait.delay_10_us(10);
//////			VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep - To reduce overshoot //
//////			wait.delay_10_us(10);
//////			tmu_6->arm();
//////			wait.delay_10_us(15);				
//////			tmeas = tmu_6->read(1e-3);
//////			if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
//////			{
//////				while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < UpperLimit)
//////				{
//////					ifrc +=istep;
//////					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
//////					wait.delay_10_us(15);	// Provide enough time for device to stop switching
//////					tmu_6->arm();	
//////					wait.delay_10_us(15);				
//////					tmeas = tmu_6->read(200e-6);
//////				}
//////			}
//////			else
//////			{		
//////				ISD_p = -999; // Device not switching. FAIL. //
//////			}
//////			ISD_p = ifrc;
//////			
//////			// Measure the voltage at ISD_p //
//////			BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE); // OVI_1_0 //
//////			wait.delay_10_us(5);
//////			VSD_p = BPP_ovi->measure_average(5);
//////		}
//////		else
//////			ISD_p = -999; // Device not switching. FAIL. //
//////
//////		gISD_P = ISD_p; // Save for later SR tests
//////	}
//////
//////	// IShunt_5p5V-P //
//////	// Per Lance on 7/1/2017, change the measure voltage to 5.6V instead of 5.5V. Otherwise, 
//////	// Ishunt_p is coming is low on some parts, but these parts are still good according to 
//////	// Lance, he tested on the bench. //
//////	// Measure BPP current with 5.6V //
//////	//BPP_ovi->set_voltage(BPP_ch, 5.5, RANGE_10_V);
//////	BPP_ovi->set_voltage(BPP_ch, 5.6, RANGE_10_V); 
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
//////	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
//////	wait.delay_10_us(250); // Must wait //
//////	Ishunt_p = BPP_ovi->measure_average(5);
//////
//////	// Powerdown //
//////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
//////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain
//////	Open_relay(K3); // Drain to RL pullup
//////	Open_relay(K12);
//////	VPIN_ovi->connect(VPIN_ch);
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(g_DDDwait);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	//wait.delay_10_us(200); // Wait for relays //
//////	wait.delay_10_us(300); // Wait for relays //
//////
//////	// IShunt_5p5V-S //
//////	// Measure BPS current with 5.5V //
//////	BPS_dvi->set_current(BPS_ch, 30e-3,RANGE_30_MA);	
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		VBPS_ramp_up(0, 5.5, 100e-3);
//////		BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
//////		wait.delay_10_us(250); // Must wait //
//////		Ishunt_s = BPS_dvi->measure_average(5);
//////		VBPS_ramp_down(5.0, 0, 100e-3);	//Needs to ramp down to prevent undershoot
//////		wait.delay_10_us(250);
//////	}
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	//					Primary: VBPP_Init_P, VBPP_Init_M, VBPP_Init_HYS				    //
//////	//																					    //
//////	// Src VBPP threshold by checking chip consumption at different state without involving //
//////	// Drain pin.																		    //
//////	//             /\    /\																    //
//////	//       0.3 /  3 0.3 0.8 mA														    //	
//////	//	BPP Pin	 /	  \/    \                                                               //
//////	//	   	    /                                                                           //
//////	// CAUTION: "OVI" has major overshoot when forcing voltage on BPP pin                   //
//////	//          (0-5V signal, 20% overshoot - 1V). DVI doesn't have a problem.              //
//////	//			Without parts, OVI doesn't have overshoot.                                  //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// UV pin has to be grounded.  Otherwise, BPP will not operate.
//////	Close_relay(K3);
//////	wait.delay_10_us(200);
//////	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_2_V);  
//////	VPIN_ovi->set_current(VPIN_ch, 10e-3, RANGE_30_MA);		
//////	wait.delay_10_us(30);
//////	VBPP_P = 0.0;
//////	VBPP_M = 0.0;
//////	LowerLimit = (func.dlog->tests[A_VBPP_P].f_min_limit_val[0]); // Get lower search limit //
//////	wait.delay_10_us(330);
//////	search_VBPP_th(&VBPP_PV, &VBPP_M, &VBPP_P, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq, LowerLimit);
//////
//////	//VBPP_HYS = VBPP_P - VBPP_M;
//////	VBPP_HYS = g_VBPP_P_S_Init_S - VBPP_M;  // VBPP_P_S_Init_S not test again, same as Inno3X. //
//////	gVBPP_VCEN = (VBPP_P + VBPP_M)/2;	
//////
//////	// Power down VBPP test
//////	//BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE);
//////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
//////	VBPP_ramp_down(4, 0, 0.3);
//////	Open_relay(K3);		
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	//					Secondary: VBPS_Init_P, VBPS_Init_M, VBPS_Init_HYS				  //
//////	//VBPS_Init_P:																		  //
//////	// Chip consumption is the same at different states for secondary when device is not  //
//////	// switching. Power up FW pin to see state transition by checking charge current. 	  //
//////	// NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  //
//////	//                           +200uA													  //			
//////	//				 -20mA /----------------											  //
//////	//					  /											            		  //	
//////	//	BPS Pin			 /	                                                              //
//////	//	FW =9.5V   	    /                                                                 //
//////	//																				      //
//////	//VBPS_Init_M:																		  //
//////	//	In order to find VBPS_Init_M, allow device to switch, chip consumption should drop//
//////	//  when VBPS_Init_M threshold is reached and switching is off.						  //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////
//////	// Setting to be the same as VBP_Init function
//////	mux_14->open_relay(MUX_4_4);	//InvSync forgot somewhere before this func
//////	mux_14->open_relay(MUX_7_3);	//InvSync forgot somewhere before this func
//////
//////	// VBPS_Init_P
//////	Close_relay(K18); // FW to dvi-11-1
//////	wait.delay_10_us(200);
//////	BPS_dvi->set_current(BPS_ch, 100e-3, RANGE_300_MA);	 
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA);	 
//////	FW_ramp_up(0,6.0,0.1);
////////	FW_dvi->set_voltage(FW_ch, 6.0, VOLT_10_RANGE);	 
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(200);
//////
//////	VBPS_P = 0.0;
//////	VBPS_M = 0.0;
//////	search_VBPS_P_th(&VBPS_P, 1);
//////
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		search_VBPS_M_th_Inno4(&VBPS_M);
//////		VBPS_HYS = VBPS_P - VBPS_M;
//////	}
//////
//////	gVBPS_P = VBPS_P; // Save for later //
//////
//////	// Power down
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE);	 
//////	Open_relay(K18); // FW to dvi-11-1
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(1, 0, 0.1);
//////	VBPS_ramp_down(3, 0, 200e-3);	//Needs to ramp down to prevent undershoot
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// VBPS:Reset-S
//////	// Measures the secondary BPS reset voltage.											//
//////	// After secondary is powered up and in control, VBPS is ramped down toward VBPS:Reset.	//
//////	// After each ramp down step, two negative pulses are applied on the FW pin.             //
//////	// If VBPS:Reset hasn't been reached, secondary will come back switching. Vice versa,   //
//////	// if VBPS:Reset is reached, secondary would not come back switching with 2 negative    //
//////	// pulses. 3 negative pulses on FW pin is required to switch secondary. This difference //
//////	// is used as a criteria to search VBPS:Reset.										    //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1);// Connect TMU HIZ to Drain 
//////	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
//////	tmu_6->start_holdoff(0,FALSE);
//////	tmu_6->stop_holdoff(0,FALSE);
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
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT); // DVI_9_1 //
//////
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////	
//////	// COMP //
//////	FB_ovi->disconnect(2);
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_20_RANGE); // DVI_21_0 //
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
////////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
//////Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //
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
//////	// Powerup //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. //  
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// ChargePumpBPS
//////	//
//////	// Charge pump starts when VBPS < VBPS_P and VOUT < 5V
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Measure BPS supply current at no load with VBEN (aka VBUS) disabled. With VBUS 
//////	// disabled, internal system clock is only running ~300kHz, instead of ~3MHz. //
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
//////	wait.delay_10_us(100);
//////	gIBPS_nsw = 0.0; // Always reset global variable here //
//////	gIBPS_nsw = BPS_dvi->measure_average(25); //gIBPS_nsw datalogged IBP_Supply.cpp //
//////
//////	// BPS //
//////	// Enable VBUS switch with I2C to speed up the internal system clock to
//////	// get maximum internal system clock frequency //
////////	Write_Byte(g_VBEN, 0x83, NObin, HEX);
//////DSM_Write_Byte(g_VBEN, 0x83);
//////
//////	// Measure BPS supply current at no load with VBEN (aka VBUS) enabled. With VBUS 
//////	// enabled, internal system clock increases to ~3MHz from ~300kHz. //
//////	wait.delay_10_us(150);
//////	gIBPS_nswHF = 0; // Always reset global variable here //
//////	gIBPS_nswHF = BPS_dvi->measure_average(25);
//////
//////	// Bring BPS below VBP+ to turn on charge pump //
//////	VBPS_ramp_up(gVBPS_final, VBPS_P-0.1, 0.01);
//////
//////	// Set Vout to 3V for worst case charge pump current //
//////	VO_dvi->set_voltage(VO_ch, 3, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(100);
//////	BPScurrent = BPS_dvi->measure_average(25);
//////
//////	// Subtract supply current to get charge pump current //
//////	ChargePumpBPS = BPScurrent - gIBPS_nswHF;
//////	ChargePumpBPS *= -1; // Datalog as positive //
//////
//////	// BPS, Vout powerdown //
//////	// Get ready for next test //
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	BPS_dvi->set_voltage(BPS_ch, 2, VOLT_10_RANGE); // DVI_9_1, prevent glitch //
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
//////	VBPS_ramp_down(2, 1, .05); // prevent glitch //
//////	wait.delay_10_us(40);
//////	VBPS_ramp_down(1, 0, .05); // prevent glitch //
//////	wait.delay_10_us(10);
//////
//////	// FW //
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//////	VBPS_ramp_up(0, gVBPS_M_Init - 200e-3, .2);	
//////
//////	// Vout //
//////	// Get ready for next test //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////	wait.delay_10_us(50); 
//////
//////	// Powerup Secondary //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// I2C into test mode. // 
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
////////	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //
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
//////	wait.delay_10_us(250);
//////
//////	// DDD level //
//////	g_DDD_High = 5.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// Connect FW to DDD //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
//////	wait.delay_10_us(14);
//////	FW_dvi->set_voltage(FW_ch, 5, VOLT_10_RANGE); // DVI_11_1 //
//////	wait.delay_10_us(20);
//////	Close_relay(K21); // Connect FW to DDD
//////	wait.delay_10_us(200);
//////
//////	// Disconnect dvi from FW //
//////	Open_relay(K18);
//////	wait.delay_10_us(200);
//////
//////	// Powerup primary //
//////	Power_Up_Primary_Normal_Mode(ILIM_NORM) ;
//////
//////	// DDD level //
//////	wait.delay_10_us(30);
//////	g_DDD_Low = -0.5; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// 3 pulses to FW pin //
//////	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);
//////	wait.delay_10_us(100);
//////
//////	// Search //
//////	search_VBPS_Reset (&VBPS_Reset_s);
//////	VBPS_Reset_Delta_s = gVBPS_M_Init - VBPS_Reset_s;
//////
//////	// Powerdown //
//////	tmu_6->open_relay(TMU_HIZ_DUT1);// Connect TMU HIZ to Drain 
//////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.5);
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	Open_relay(K21); // FW DDD //
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0.2, 200e-3);
//////	VBD_dvi->set_voltage(VBD_ch, 2, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//////	FB_ovi->connect(2);
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// ISD-S and VSD-S
//////	//	
//////	// ISD-S is the BPS shutdown current and VSD-S is the voltage at ISD-S.  
//////	// Increase the current into BPS pin until part stops switching.
//////	//
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	tmu_6->stop_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	tmu_6->start_holdoff(0,FALSE);
//////	tmu_6->stop_holdoff(0,FALSE);
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
//////	//Connect_InvSyn_IM(Low_Load_Vd_Input);
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
//////	// FW //
//////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
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
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////	//Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	//ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	//ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	//Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	//Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
//////	//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	//ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
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
//////
//////	// Make sure drain is switching //
//////	tmu_6->arm();
//////	wait.delay_10_us(10);
//////	tmeas = tmu_6->read();
//////
//////	// Error //
//////	if (tmeas < 1e-9)
//////		g_Error_Flag = -183;
//////
//////	// Measure the supply current
//////	//BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(60);
//////	BPScurrent = BPS_dvi->measure_average(15);
//////
//////	// Force current instead of voltage, set current and voltage clamp //
//////	iforce = BPScurrent+0.5e-3;
//////	if (iforce > 29.999e-3 || iforce < -29.999e-3) // Prevent out of range //
//////	{
//////		iforce = 3e-3;
//////		g_Error_Flag = -200;
//////	}
//////	BPS_dvi->set_current(BPS_ch, iforce, RANGE_300_MA); // DVI_9_1 //
//////	//BPS_dvi->set_current(BPS_ch, iforce, RANGE_30_MA); // DVI_9_1 //
//////	wait.delay_10_us(10);
//////	VBPS_ramp_up(gVBPS_final, gVBPS_final+1, .05);	
//////	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final+1, VOLT_10_RANGE); // DVI_9_1, raise voltage clamp so dvi is in current force mode. //
//////
//////	// Increase current into BPS until switching stops //
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
//////	istep = 100e-6;
//////	iforce = iforce - istep;
//////	MaxSearch = 20e-3;
//////	while( (iforce < MaxSearch) && (tmeas > 1e-9) )	
//////	{
//////		iforce += istep;
//////		VBPS_OV = BPS_dvi->measure(); // Voltage at shutdown //
//////		start = mytimer.GetElapsedTime();
//////		BPS_dvi->set_current(BPS_ch, iforce, RANGE_300_MA); // DVI_9_1 //
//////		//BPS_dvi->set_current(BPS_ch, iforce, RANGE_30_MA); // DVI_9_1 //
//////		wait.delay_10_us(10); // > 120us timer on BPS latchoff, per DE
//////		tmu_6->arm();
////////		wait.delay_10_us(11);
////////		tmeas = tmu_6->read();
//////wait.delay_10_us(12);
//////tmeas = tmu_6->read(1e-3);
//////		stop = mytimer.GetElapsedTime();
//////	}
//////	Imeas = iforce-istep;	// Measure current just before threshold
//////	ISD_s = Imeas - BPScurrent; // Subtract the supply current to get the shutdown current //
//////	gISD_S = ISD_s; // Save for later //
//////
//////	// Error check //
//////	if (g_Error_Flag == -183)
//////	{
//////		VBPS_OV = -99;
//////		ISD_s = -99;
//////	}
//////
//////	// Powerdown //
//////	BPS_dvi->set_current(BPS_ch, 7e-3, RANGE_300_MA); // DVI_9_1 //
//////	//BPS_dvi->set_current(BPS_ch, 7e-3, RANGE_30_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//////	tmu_6->open_relay(TMU_CHAN_A_DUT2); // TMU_CHAN_A2 SR pin //
//////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	Mux20_Open_relay(K50);
//////	//Mux20_Open_relay(K64);
//////	//ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	//Mux20_Open_relay(K37);
//////	//Mux20_Open_relay(K38);
//////	//Mux20_Open_relay(K40);
//////	//Mux20_Open_relay(K39);
//////	Disconnect_InvSyn_IM();
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.3);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(1, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(10);
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_300_MA); // DVI_9_1 //
//////	//BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
//////	VBPS_ramp_down(3, 0, 200e-3);
//////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	Open_relay(K17); 
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  //
//////	//							VBPP_Reset_p								     //
//////	//		Ramp down VBPP pin and monitor Vpin current to find the threshold.	 //
//////	//		When Vbp rest is reached, POR will change currents on feature pins.	 //
//////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// Vpin (300uA)
//////
//////	VPIN_ovi->set_voltage(VPIN_ch, 6.0, RANGE_10_V);
//////	VPIN_ovi->set_current(VPIN_ch, 300e-6, RANGE_300_UA);
//////	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
//////	wait.delay_10_us(30);
//////	VBPP_Power_Up_w_Test_Mode(gTM1_UVOV_NoDelay, ILIM_NORM);
//////	search_VBPP_Reset (&VBPP_Reset_p);
//////
//////	// Powerdown //
//////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);
//////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);	
//////	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
//////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
//////	VBPP_ramp_down(2, 0, 0.5);
//////
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// tLOff_Filter-S
//////	// 
//////	// Latch-off filter.  Amount of time for device to latchoff after shutdown 
//////	// current (ISD-S) applied.
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	Close_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain //
//////	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	tmu_6->stop_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
//////	tmu_6->start_holdoff(0,FALSE);
//////	tmu_6->stop_holdoff(0,FALSE);
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
//////	//Connect_InvSyn_IM(Low_Load_Vd_Input);
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
//////	// FW //
//////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4	
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
//////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
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
//////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
//////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
//////	//Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	//ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	//ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	//Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
//////	//Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
//////	//Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
//////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
//////	//Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
//////	//ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
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
//////	// I2C into test mode. //  
//////	//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
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
//////
//////	// Make sure drain is switching //
//////	tmu_6->arm();
//////	wait.delay_10_us(10);
//////	tmeas = tmu_6->read();
//////
//////	// Error //
//////	if (tmeas < 1e-9)
//////		g_Error_Flag = -195;
//////
//////	// Measure the supply current
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA);	 // DVI_9_1 //
//////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(60);
//////	BPScurrent = BPS_dvi->measure_average(15);
//////
//////	// Force current instead of voltage, set current and voltage clamp //
//////	iforce = BPScurrent + 0.5e-3;
//////	if (iforce > 29.999e-3 || iforce < -29.999e-3) // Prevent out of range //
//////	{
//////		iforce = 3e-3;
//////		g_Error_Flag = -200;
//////	}
//////	BPS_dvi->set_current(BPS_ch, iforce, RANGE_30_MA); // DVI_9_1 //
//////	wait.delay_10_us(10);
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final+1, VOLT_10_RANGE); // DVI_9_1, raise voltage clamp so dvi is in current force mode. //
//////
//////	// Measure drain current while device switching //
//////	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT); // DVI_11_0 //
//////	wait.delay_10_us(20);
//////	IdrainON = D_dvi->measure_average(15);
//////
//////	//int i = 0;
//////	//float MyCurrentMeas[20000] = {0};
//////	//for (i=0;i<20000;i++)
//////	//{
//////	//	MyCurrentMeas[i] = D_dvi->measure();
//////	//}
//////
//////	// Increase current above ISD into BPS and check how long until switching stops. //
//////	// Drain current drops when device stops switching. //
//////	iforce = BPScurrent + ISD_s + 2e-3;
//////	LoopCount = 0;
//////	Imeas = 99; // Initialize //
//////	if (iforce > 29.999e-3 || iforce < -29.999e-3)
//////	{
//////		iforce = 30e-3;
//////		g_Error_Flag = -200;
//////	}
//////	BPS_dvi->set_current(BPS_ch, iforce, RANGE_30_MA); // DVI_9_1 //
//////	wait.delay_10_us(5);
//////	start = mytimer.GetElapsedTime();
//////	while( Imeas > 0.5*IdrainON && LoopCount < 300)
//////	{
//////		Imeas = D_dvi->measure();
//////		LoopCount++;
//////	}
//////	stop = mytimer.GetElapsedTime();
//////	tLOff_Filter_S = (stop - start)/1e6;
//////
//////	// Error check //
//////	if (g_Error_Flag == -195)
//////	{
//////		tLOff_Filter_S = -99;
//////	}
//////
//////	// Powerdown //
//////	BPS_dvi->set_current(BPS_ch, 7e-3, RANGE_30_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	tmu_6->open_relay(TMU_HIZ_DUT1); // TMU HIZ Drain //
//////	tmu_6->open_relay(TMU_CHAN_A_DUT2); // TMU_CHAN_A2 SR pin //
//////	Open_relay(K3);
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	Mux20_Open_relay(K50);
//////	//Mux20_Open_relay(K64);
//////	//ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	//Mux20_Open_relay(K37);
//////	//Mux20_Open_relay(K38);
//////	//Mux20_Open_relay(K40);
//////	//Mux20_Open_relay(K39);
//////	Disconnect_InvSyn_IM();
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////	VBPP_ramp_down(4, 0, 0.3);
//////	Open_relay(K12); // Disconnect DDD7_1 from Vpin(UV) pin
//////	VPIN_ovi->connect(VPIN_ch); // Connect ovi to Vpin //
//////	wait.delay_10_us(10);
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(1, 0, 0.1);
//////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(10);
//////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
//////	VBPS_ramp_down(3, 0, 200e-3);
//////	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	ddd_7->ddd_run_pattern(Low_pat_start, Low_pat_stop);
//////	FB_ovi->set_voltage(FB_ch, 0, RANGE_2_V); // OVI_1_2 //
//////	Open_relay(K17); 
//////
//////	// Datalog //
//////	//PiDatalog(func, A_Vshunt_2mA_p, Vshunt_2mA_p, 12, POWER_UNIT);	//Done in VBP_Init func
//////	//PiDatalog(func, A_Vshunt_2mA_s, Vshunt_2mA_s, 12, POWER_UNIT);	//Done in VBP_Init func	
//////	PiDatalog(func, A_Ishunt_p, Ishunt_p, 12, POWER_MILLI);	
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		PiDatalog(func, A_Ishunt_s, Ishunt_s, 12, POWER_MILLI);	
//////	}
//////	PiDatalog(func, A_VBPP_P, VBPP_P, 12, POWER_UNIT);	
//////	PiDatalog(func, A_VBPP_M, VBPP_M, 12, POWER_UNIT);	
//////	PiDatalog(func, A_VBPP_HYS, VBPP_HYS, 12, POWER_UNIT);
//////	PiDatalog(func, A_VBPS_P, VBPS_P, 12, POWER_UNIT);	
//////	if (g_Char_Enable_P) // Characterization only //
//////	{
//////		PiDatalog(func, A_VBPS_M, VBPS_M, 12, POWER_UNIT);	
//////		PiDatalog(func, A_VBPS_HYS, VBPS_HYS, 12, POWER_UNIT);
//////	}
//////	PiDatalog(func, A_VBPS_Reset_s, VBPS_Reset_s, 12, POWER_UNIT);
//////	PiDatalog(func, A_VBPS_Res_Delta, VBPS_Reset_Delta_s, 12, POWER_UNIT);
//////	PiDatalog(func, A_ISD_S, ISD_s, 12,	POWER_MILLI);
//////	PiDatalog(func, A_VSD_S, VBPS_OV, 12, POWER_UNIT);
//////	PiDatalog(func, A_tLOff_Filter_S, tLOff_Filter_S, 12, POWER_MICRO);
//////	PiDatalog(func, A_VBPP_Reset_p, VBPP_Reset_p, 12, POWER_UNIT);
//////	PiDatalog(func, A_ISD_p, ISD_p, 12,	POWER_MILLI);
//////	PiDatalog(func, A_VSD_p, VSD_p, 12,	POWER_UNIT); 
//////	PiDatalog(func, A_ChargePumpBPS, ChargePumpBPS, 12, POWER_MICRO);
//////	if (!gTrim_AR_req_Trimops)
//////	{
//////		PiDatalog(func, A_ISD_func_p, ISD_func_p, 12, POWER_UNIT);
//////	}
//////
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		VBP_Supply_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_VBP_Supply_TT, VBP_Supply_TT, 12, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
