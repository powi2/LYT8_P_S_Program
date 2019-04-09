//==============================================================================
// BV_Drain.cpp (User function)
// 
//    void BV_Drain_user_init(test_function& func)
//    void BV_Drain(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_Drain.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_Drain_user_init(test_function& func)
{
	BV_Drain_params *ours;
    ours = (BV_Drain_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_Drain(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_Drain_params *ours;
    ours = (BV_Drain_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_BV_Drain, gFuncNum, 10, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_Fn_BV_Drain == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	Pulse pulse(PULSE_RISING_EDGE,10e-6); // external trigger pulse from dvi for debug

	double ifrc_str_init =0;
	double ifrc_str =0;
	double ifrc =0;
	int INIT_STRESS_FLAG =0;
	float vfrc_init =0;
	float vfrc =0;
	float BVDSS_STR1 =0;
	float BVDSS_STR2 =0;
	float BVDSS_ISTR =0;
	float BVDSS_WALK =0;
	float BVD_100UA =0;
	float IDS_BVD_10V =0;
	float IDS_80BVD =0;
	float IDS_325V =0;
	float IDS_150V =0;
	float IDS_30V =0;
	float Imeas =0.0;
	float ton =0.0;
	float toff =0.0;
	//int BVD_stress_time =0;
	bool LowBV_PowerDown =0;
	float DrainV = 0;
	int i_set = 0;
	float j = 0;
	float BV_Drain_TT = 0;

	// Instrument protection
	ovi_1->disconnect(1);
	ovi_1->disconnect(2);
	ovi_1->disconnect(3);
	ovi_1->disconnect(4);
	ovi_1->disconnect(5);
	ovi_1->disconnect(6);
	ovi_1->disconnect(7);
	ovi_3->disconnect(0);
	Mux20_Close_relay(K37);
	ovi_3->disconnect(1);
	Mux20_Close_relay(K39);
	ovi_3->disconnect(2);
	Mux20_Close_relay(K41);
	ovi_3->disconnect(3);
	ovi_3->disconnect(4);
	Mux20_Open_relay(K48);
	ovi_3->disconnect(5); // Already disconnected //
	Mux20_Open_relay(K45);
	ovi_3->disconnect(6);
	ovi_3->disconnect(7);
	Mux20_Open_relay(K64);
	Close_relay(K18);
	tmu_6->open_relay(TMU_HIZ_DUT1); // protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT2); // protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT3); // protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT4); // protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT1); // protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT2); // protect TMU
	tmu_6->open_relay(TMU_CHAN_B_DUT1); // protect TMU
	tmu_6->open_relay(TMU_CHAN_B_DUT2); // protect TMU
	//ddd_7->ddd_disconnect_drivers();

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// 						High Voltage MOSFET BVD								
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//Short UV pin to GND by MUX (UV PIN MUST BE GROUNDED IN ORDER FOR DEVICE TO POWER-UP PROPERLY)
	//We do not want to burn any OVI card so risk mux card here or connect the un-used relay of the K12B to GND for HW mod.
	mux_14->close_relay(MUX_BANK_8_1);	
	Close_relay(K1_DSM_TB);	
	Close_relay(K4); // Connect HVS to Drain

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Make sure HVS connects to drain- be sure the relay is working properly.  If HVS is 
	// NOT connected to drain, BVD test will datalog as passing even though the 
	// drain BVD was never actually tested. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Connect DVI to drain //
	Close_relay(K2);

	// Connect HVS to drain //
	hvs_15->init(); // Needed to prevent HVS glitch //
	wait.delay_10_us(300); // Don't remove delay.  Needed to prevent HVS glitch //
	hvs_15->set_current(1e-3, RANGE_1_MA);
	hvs_15->set_voltage(0.0, RANGE_100_V);
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	wait.delay_10_us(100);
	hvs_15->close_relay(HVS_NEG_FORCE); // NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->close_relay(HVS_SHORT_NEG_FS);	
	hvs_15->close_relay(HVS_GND_NEG_SENSE);	
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	hvs_15->close_relay(HVS_GND_POS_SENSE); // Needed to prevent HVS glitch //
	wait.delay_10_us(925); // Don't remove delay.  Needed to prevent HVS glitch //
	hvs_15->open_relay(HVS_GND_POS_SENSE); // Needed to prevent HVS glitch //
	hvs_15->close_relay(HVS_FORCE_POS); // POS_FORCE (J6,B9) to drain	
	wait.delay_10_us(250);

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// Be sure HVS is connected to drain.  Force 5V to drain with HVS and measure with dvi. //
	// Setup to measure drain voltage //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 1e-6, RANGE_30_UA); // DVI_11_0, float //

	// Power up from 0V 6.3V->4.4V->6.8V above Vshunt to stop device from switching
	BPP_ovi->set_current(BPP_ch, 5e-3, RANGE_30_MA); // OVI_1_0 //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(10);
	BPP_ovi->set_voltage(BPP_ch, 3.0, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(50);
//	BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP-50e-3, RANGE_10_V); // OVI_1_0 //
//	wait.delay_10_us(10);
//	BPP_ovi->set_voltage(BPP_ch, 4.4, RANGE_10_V); // OVI_1_0 //
//	wait.delay_10_us(10);
//	BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP, RANGE_10_V); // OVI_1_0 //
//	wait.delay_10_us(10);
	j = 3.0;
	while(j < gVshunt_BPP)
	{
		if(j > 5.4 && i_set < 1)
		{
			BPP_ovi->set_current(BPP_ch, 18e-3, RANGE_30_MA);  //used to be at 5mA
			i_set = 1;
		}
		BPP_ovi->set_voltage(BPP_ch, j, RANGE_10_V); // OVI_1_0 //
		wait.delay_10_us(10);
		j = j + 0.1;
	}
	BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP+100e-6, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(10);	

	//Randy's recommendation to use 18mA to prevent the DUT going into Shutdown mode.
	BPP_ovi->set_current(BPP_ch, 18e-3, RANGE_30_MA); // OVI_1_0 // // require > Ishunt to hit Vshunt_BPP  zcx 12/28/16
	wait.delay_10_us(50);	

	// Be sure HVS is connected to drain.  Force 30V to drain with HVS and measure with dvi. //
	hvs_15->set_current(1e-3, RANGE_1_MA);
	hvs_15->set_voltage(30, RANGE_1_KV);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE); // DVI_11_0 //
	wait.delay_10_us(1000);
	DrainV = D_dvi->measure(); // DVI_11_0 //
	if (DrainV < 27.5 )
	{
		g_Error_Flag = -197; // Error.  HVS not connected to drain //
	}

	// Powerdown //
	hvs_15->set_voltage(0.0, RANGE_1_KV);
	VBPP_ramp_down(4, 0, 0.05);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	Open_relay(K2); // Disconnect dvi from drain //
	ovi_1->disconnect(0);
	wait.delay_10_us(250);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// BVD test
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Close_relay(K11); // Connect BPP to DVI. Avoid using OVI, which can be damaged by 
					  // avalanche breakdown from bad units. 
	wait.delay_10_us(300);
	if (g_OPCODE==4300 || g_OPCODE==4500)
	{
		ifrc_str = 300e-6; // stress current clamp at hot
		ifrc = 100e-6; // current clamp at hot
		vfrc = gBVD_Hot_Trimops;			
	}
	else if (g_OPCODE==4400)
	{
		ifrc_str = g_scaled_ifrc; // stress current clamp at cold
		ifrc = 100e-6; // current clamp at cold	// Per Shreyas 11/21/16
		vfrc = 600;			
	}
	else
	{
		ifrc_str = g_scaled_ifrc; // stress current clamp at room per device
		ifrc = 100e-6; // current clamp at room
		vfrc = gBVD_Room_Trimops;			
	}
	//BVD_stress_time = ours->BVD_stress_time * 1000;	// In ms

	// Power up from 0V 6.3V->4.4V->6.8V above Vshunt to stop device from switching
	BPP_DVI->set_current(BPP_ch, 5e-3, RANGE_30_MA);
	BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(10); // DVI_11_0 
	BPP_DVI->set_voltage(BPP_ch, 3.0, VOLT_10_RANGE);
	wait.delay_10_us(50);
	j = 3.0;
	while(j < gVshunt_BPP)
	{
		if(j > 5.4 && i_set < 1)
		{
			BPP_DVI->set_current(BPP_ch, 18e-3, RANGE_30_MA);  //used to be at 5mA
			i_set = 1;
		}
		BPP_DVI->set_voltage(BPP_ch, j, VOLT_10_RANGE);
		wait.delay_10_us(10);
		j = j + 0.1;
	}
	BPP_DVI->set_voltage(BPP_ch, gVshunt_BPP+100e-6, VOLT_10_RANGE);
	wait.delay_10_us(10);	

	//Randy's recommendation to use 18mA to prevent the DUT going into Shutdown mode.
	BPP_DVI->set_current(BPP_ch, 18e-3, RANGE_30_MA); // require > Ishunt to hit Vshunt_BPP  zcx 12/28/16
	wait.delay_10_us(50);	
	hvs_15->set_current(100e-9,	RANGE_1_MA);
	hvs_15->set_voltage(0.0, RANGE_1_KV);
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);				
	wait.delay_10_us(250);	

	// +++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Production Stress the High Voltage MOSFET STARTS
	// +++++++++++++++++++++++++++++++++++++++++++++++++ //
	//hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);	
	hvs_15->set_current(ifrc_str, RANGE_1_MA);
	hvs_15->set_voltage(vfrc, RANGE_1_KV);	
	delay(15); // Give HVS time for the voltage to come up //

	// Measure ISTR
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);	
	wait.delay_10_us(200);

	BVDSS_ISTR = hvs_15->measure_average(5); // measure avalanche current

	// Measure BVDSS at ISTR before WALK
	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	wait.delay_10_us(200);
	BVDSS_STR1 = hvs_15->measure_average(5); // measure BVD @ stress				
	BVDSS_STR1 = BVDSS_STR1 - BVDSS_ISTR*47e3; // subtract 47k vdrop

	// Prevent bad device from damaging tester.  Go to LowBV Powerdown
	if(BVDSS_STR1 < 450)
	{
		LowBV_PowerDown = true;
		goto Run_LowBV_PowerDown;
	}
	delay(20); // Stress time //
	BVDSS_STR2 = hvs_15->measure_average(5);
	BVDSS_STR2 = BVDSS_STR2 - BVDSS_ISTR*47e3; // subtract 47k vdrop
	BVDSS_WALK = BVDSS_STR2 - BVDSS_STR1; // BVDSS:WALK
	// +++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Production Stress the High Voltage MOSFET ENDS
	// +++++++++++++++++++++++++++++++++++++++++++++++++ //

	// After stress reduce current or at hot leave it the same
	hvs_15->set_current(ifrc, RANGE_1_MA); // 100uA or 300uA at hot 			
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	wait.delay_10_us(750);
	Imeas = hvs_15->measure_average(5); // measure avalanche current
	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	wait.delay_10_us(750); //HL changed from 2ms to 5ms.

	// BVD_100UA
	BVD_100UA = hvs_15->measure_average(5);
	BVD_100UA -= Imeas * 47e3; // subtract 47k vdrop 
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	//wait.delay_10_us(500); //HL changed from 2ms to 5ms.
	
	// BVD-10V
	hvs_15->set_voltage(BVD_100UA - 10, RANGE_1_KV); 
	wait.delay_10_us(500); //HL changed from 2ms to 5ms
	IDS_BVD_10V = hvs_15->measure_average(5); // IDSS:BVD-10V

	// 80%BVD
	hvs_15->set_voltage(BVD_100UA * 0.8 ,RANGE_1_KV);
	//HVS_ramp_down(BVD_100UA - 10, BVD_100UA * 0.8, 75);
	wait.delay_10_us(500);
	//wait.delay_10_us(300);
	IDS_80BVD = hvs_15->measure_average(10); // IDSS:80%BVD 78.7ms

	// 325V BVD
	hvs_15->set_voltage(325 ,RANGE_1_KV);
	//HVS_ramp_down(BVD_100UA * 0.8, 325, 75);
	wait.delay_10_us(700);
	//wait.delay_10_us(400);
	IDS_325V = hvs_15->measure_average(10);	// IDSS:80%BVD 78.7ms

	// 150V
	hvs_15->set_voltage(150, RANGE_1_KV); 
	//HVS_ramp_down(325, 150, 75);
	wait.delay_10_us(700);
	//wait.delay_10_us(400);
	IDS_150V = hvs_15->measure_average(10); // IDSS:150V 88.5ms
	
	// 30V
	hvs_15->set_current(ifrc, RANGE_100_UA);
	hvs_15->set_voltage(30, RANGE_1_KV); 
	//HVS_ramp_down(150, 30, 25);
	delay(15);
	//delay(7);
	IDS_30V = hvs_15->measure_average(10); // IDSS:30V 98.7ms

	// Power down HVS before connecting it to FW pin
	hvs_15->set_voltage(0.0, RANGE_1_KV);	
	wait.delay_10_us(100);
	BPP_DVI->set_current(BPP_ch, 5e-3, RANGE_30_MA); //HL changed BPP current back to 5mA.
	VBPP_DVI_ramp_down(4, 0, 0.2);
	uVCC_ovi->set_voltage(uVCC_ch, 0.5, RANGE_10_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	wait.delay_10_us(30);
	Open_relay(K4); // Disconnect HVS from Drain
	Open_relay(K11); // Disconnect BPP from DVI
	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);
	ovi_1->connect(3);
	ovi_1->connect(4);
	ovi_1->connect(5);
	ovi_1->connect(6);
	ovi_1->connect(7);
	ovi_3->connect(0);
	Mux20_Open_relay(K37);
	ovi_3->connect(1);
	Mux20_Open_relay(K39);
	ovi_3->connect(2);
	Mux20_Open_relay(K41);
	ovi_3->connect(3);
	ovi_3->connect(4);
	//ovi_3->connect(5); // Keep disconnected //
	ovi_3->connect(6);
	ovi_3->connect(7);
	Open_relay(K18);
	//ddd_7->ddd_connect_drivers();
	hvs_15->open_relay(HVS_NEG_FORCE); // NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS); // POS_FORCE (J6,B9) to drain
	wait.delay_10_us(200);
hvs_15->init();
	uVCC_ramp_down(0.5, 0, .05);
	//wait.delay_10_us(200);
	if (BVD_100UA < 150.0)
	{
		AbortTest =true;		// Don't continue on if BVD is too low
		g_Error_Flag = -226;
	}

	Run_LowBV_PowerDown:

	if(LowBV_PowerDown == true)
	{
		hvs_15->set_voltage(0.0, RANGE_1_KV);
		wait.delay_10_us(200);

		// Power down HVS before connecting it to FW pin
		hvs_15->set_voltage(0.0, RANGE_1_KV);	
		wait.delay_10_us(200);
		VBPP_ramp_down(3, 0.0, 0.05);
		Open_relay(K4); // Disconnect HVS from Drain
		Open_relay(K11); // Disconnect BPP from DVI
		hvs_15->open_relay(HVS_NEG_FORCE); // NEG_FORCE (J6,B3)  hardwired to gnd 
		hvs_15->open_relay(HVS_SHORT_NEG_FS);	
		hvs_15->open_relay(HVS_GND_NEG_SENSE);	
		hvs_15->open_relay(HVS_SHORT_POS_FS);
		hvs_15->open_relay(HVS_FORCE_POS); // POS_FORCE (J6,B9) to drain	
		wait.delay_10_us(200);

		// Power down
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
		wait.delay_10_us(10);
		VBPP_ramp_down(3, 0.0, 0.05);
		Open_relay(K2);
		hvs_15->init();	
		wait.delay_10_us(100);
		ovi_1->connect(0);
		ovi_1->connect(1);
		ovi_1->connect(2);
		ovi_1->connect(3);
		ovi_1->connect(4);
		ovi_1->connect(5);
		ovi_1->connect(6);
		ovi_1->connect(7);
		ovi_3->connect(0);
		Mux20_Open_relay(K37);
		ovi_3->connect(1);
		Mux20_Open_relay(K39);
		ovi_3->connect(2);
		Mux20_Open_relay(K41);
		ovi_3->connect(3);
		ovi_3->connect(4);
		//ovi_3->connect(5); // Keep disconnected //
		ovi_3->connect(6);
		ovi_3->connect(7);
		//ddd_7->ddd_connect_drivers();
		wait.delay_10_us(100);
		AbortTest = true;
		g_Error_Flag = -227;
	}

	//Disconnect UV pin from GND by MUX
	mux_14->open_relay(MUX_BANK_8_1);	
	mux_14->open_relay(MUX_1_1);
	wait.delay_10_us(100);

	// Force failure if HVS was not connected to drain. //
	if (g_Error_Flag == -197) // Error.  HVS not connected to drain. //
	{
		BVDSS_ISTR = -99;
		BVDSS_STR1 = -99;
		BVDSS_STR2 = -99;
		BVDSS_WALK = -99;
		BVD_100UA = -99;
		IDS_BVD_10V = -99;
		IDS_80BVD = -99;
		IDS_325V = -99;
		IDS_150V = -99;
		IDS_30V = -99;
	}

	// Datalog
	PiDatalog(func, A_IDSS_StressCurr, ifrc_str, 10, POWER_MICRO);	
	PiDatalog(func, A_BVDSS_ISTR, BVDSS_ISTR, 10, POWER_MICRO);		
	PiDatalog(func, A_BVDSS_STR1, BVDSS_STR1, 10, POWER_UNIT);		
	PiDatalog(func, A_BVDSS_STR2, BVDSS_STR2, 10, POWER_UNIT);		
	PiDatalog(func, A_BVDSS_WALK, BVDSS_WALK, 10, POWER_UNIT);		
	PiDatalog(func, A_BVD_100UA, BVD_100UA, 10, POWER_UNIT);	
	PiDatalog(func, A_IDS_BVD_10V, IDS_BVD_10V, 10, POWER_MICRO);		
	PiDatalog(func, A_IDS_80BVD, IDS_80BVD, 10, POWER_MICRO);	
	PiDatalog(func, A_IDS_325V, IDS_325V, 10, POWER_MICRO);	
	PiDatalog(func, A_IDS_150V, IDS_150V, 10, POWER_MICRO);		
	PiDatalog(func, A_IDS_30V, IDS_30V, 10, POWER_MICRO);

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		BV_Drain_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_BV_Drain_TT, BV_Drain_TT, 10, POWER_MILLI);
	}	

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
