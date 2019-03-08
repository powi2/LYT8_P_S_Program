//==============================================================================
// BV_Vpin.cpp (User function)
// 
//    void BV_Vpin_user_init(test_function& func)
//    void BV_Vpin(test_function&	 func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_Vpin.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_Vpin_user_init(test_function& func)
{
	BV_Vpin_params *ours;
    ours = (BV_Vpin_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_Vpin(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_Vpin_params *ours;
    ours = (BV_Vpin_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BV_Vpin, gFuncNum, 10, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Disable the this Vpin BV test at HOT per PE and DE
	if (g_OPCODE==4300 ||g_OPCODE==4500)
		return;

	if (g_Fn_BV_Vpin == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	float ifrc_Vpin_str =0;
	float ifrc_Vpin =0;
	float vfrc_Vpin =0;
	float vfrc_Vpin_REL =0;
	float bvdss_Vpin_str1 =0;
	float bvdss_Vpin_str2 =0;
	float vset = 200;		
	float BVD_Vpin =0;
	float IDS_Vpin =0;
	float Imeas_750V = 0.0; 
	float Imeas_700V =0.0;
	float Imeas_650V =0.0;
	float Imeas_500V =0.0;
	float Temp_MeasI = 0;
	float BV_Vpin_TT = 0;
	float Vcheck = 0;
	float vset2 = 0;
	float vset3 = 0;
	float vset4 = 0;
	Pulse pulse;

	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

		// Instrument protection
		ovi_1->disconnect(0);
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
		tmu_6->open_relay(TMU_HIZ_DUT1); // protect TMU
		tmu_6->open_relay(TMU_HIZ_DUT2); // protect TMU
		tmu_6->open_relay(TMU_HIZ_DUT3); // protect TMU
		tmu_6->open_relay(TMU_HIZ_DUT4); // protect TMU
		tmu_6->open_relay(TMU_CHAN_A_DUT1); // protect TMU
		tmu_6->open_relay(TMU_CHAN_A_DUT2); // protect TMU
		tmu_6->open_relay(TMU_CHAN_B_DUT1); // protect TMU
		tmu_6->open_relay(TMU_CHAN_B_DUT2); // protect TMU
		Open_relay(K4); // Disconnect HVS from 47k resistor
		Open_relay(K1); // Disconnect DVI_11_0 from Drain directly (Kelvin connection)
		Open_relay(K2);
		Open_relay(K18);
		Open_relay(K5);
		Open_relay(K4); // Disconnect HVS from Drain
		Open_relay(K11); // Disconnect BPP from DVI
		Open_relay(K5); // Disconnect HVS from FW pin
		Open_relay(K18); // Disconnect FW  from DVI-11-1
		mux_14->open_relay(MUX_BANK_8_1);	
		mux_14->open_relay(MUX_1_1);
		Open_relay(K28_K29_K34_K69); // Controls relays K28, K29, K34 on loadboar and K69 on contactor board. // 
		wait.delay_10_us(300);
		//ddd_7->ddd_disconnect_drivers();
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// 						700V Device on Vpin pin BVD							 
		//  Procedure:
		//  1) Set D = 40V
		//  2) Set Vpin = 0V.
		//  3) Ramp BPP from 0V to 5.5V
		//  4) Then raise Vpin to 500V, 650V & 700V and measure leakage currents.
		//  5) Then clamp Vpin to 750V, force 100uA into Vpin and ensure voltage can clamp
		//     to 750V to ensure BV > 750V
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			
		// Power down HVS before connecting it to UV pin
		hvs_15->set_meas_mode(HVS_MEASURE_CURRENT); // HVS commands takes about 1ms per instruction.
		hvs_15->set_current(10e-6, RANGE_1_MA);							
		hvs_15->set_voltage(0.0, RANGE_1_KV);	
		wait.delay_10_us(50);

		//Close relay K5 & K18 is needed to avoid the large glitch caused by closing HVS relays to get to D, UV or FW pins.
		Close_relay(K5);
		Close_relay(K18);
		wait.delay_10_us(500);

		//Connect HVS relays.
		hvs_15->close_relay(HVS_NEG_FORCE); // NEG_FORCE (J6,B3)  hardwired to gnd 
		hvs_15->close_relay(HVS_SHORT_NEG_FS);	
		hvs_15->close_relay(HVS_GND_NEG_SENSE);	
		hvs_15->close_relay(HVS_SHORT_POS_FS);
		hvs_15->close_relay(HVS_FORCE_POS); // POS_FORCE (J6,B9) to drain	
		wait.delay_10_us(500);
		BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_0 
		dvi_11->set_current(DVI_CHANNEL_1, 100e-3, RANGE_300_MA);
		dvi_11->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE);
		wait.delay_10_us(50);
		Open_relay(K11); // Use DVI_11_0 to power up D = 40V during BV test.
		Close_relay(K28_K29_K34_K69); // Controls relays K28, K29, K34 on loadboar and K69 on contactor board. // 
									  //K34 connects HVS to UV pin
									  //K69 shorts UV F/S on CB	
		wait.delay_10_us(250); 
		Close_relay(K4); // Connect HVS to 47k resistor
		wait.delay_10_us(250); // Disconnect HVS from FW & D
		Open_relay(K1); // Connect DVI_11_0 to Drain directly (Kelvin connection)
		Close_relay(K2);
		Open_relay(K18); // Disconnect DVI_11_1 from Fw pin.
		Open_relay(K5);
		wait.delay_10_us(500);

		// Set BPP 100mV to prevent BPP undershoot when drain comes up. //
		dvi_11->set_voltage(DVI_CHANNEL_1, 0.1, VOLT_10_RANGE);
		wait.delay_10_us(20);

		// Set D = 40V / 100mA
		dvi_11->set_current(DVI_CHANNEL_0, 100e-3, RANGE_300_MA);
		dvi_11->set_voltage(DVI_CHANNEL_0, 40, VOLT_50_RANGE);
		wait.delay_10_us(100);

		// Ramp VBPP from 0.1V to 5.5V (DVI_11_1)
		// Bpp set 5.5V for 100us
		float j = 0.1;
		while(j<=5.5)
		{
			dvi_11->set_voltage(DVI_CHANNEL_1, j, VOLT_10_RANGE);
			j=j+0.1;
			wait.delay_10_us(5);
		}
		wait.delay_10_us(50);

		// Set Vpin per device type. //
		if (!strnicmp(Part_ID_LimitSet, "INN3365", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 645;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 650;
			}
			Vcheck = 595;
			vset2 = 640;
			vset3 = 595;
			vset4 = 455;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3375", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 700;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 710;
			}
			Vcheck = 650;
			vset2 = 700;
			vset3 = 650;
			vset4 = 500;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3366", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 645;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 650;
			}
			Vcheck = 595;
			vset2 = 640;
			vset3 = 595;
			vset4 = 455;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3376", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 700;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 710;
			}
			Vcheck = 650;
			vset2 = 700;
			vset3 = 650;
			vset4 = 500;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3367", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 645;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 650;
			}
			Vcheck = 595;
			vset2 = 640;
			vset3 = 595;
			vset4 = 455;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3377", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 700;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 710;
			}
			Vcheck = 650;
			vset2 = 700;
			vset3 = 650;
			vset4 = 500;
		}
		if (!strnicmp(Part_ID_LimitSet, "SC1750", 6))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 700;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 710;
			}
			Vcheck = 650;
			vset2 = 700;
			vset3 = 650;
			vset4 = 500;
		}
		if (!strnicmp(Part_ID_LimitSet, "INN3368", 7))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 645;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 650;
			}
			Vcheck = 595;
			vset2 = 640;
			vset3 = 595;
			vset4 = 455;
		}
		if (!strnicmp(Part_ID_LimitSet, "SC1738", 6))
		{
			// Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
			if (g_OPCODE==4300 || g_OPCODE==4500)
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 645;
			}
			else
			{
				ifrc_Vpin = 100.0e-6;		
				vset = 650;
			}
			Vcheck = 595;
			vset2 = 640;
			vset3 = 595;
			vset4 = 455;
		}



		// Bring up Vpin voltage //
		hvs_15->set_current(ifrc_Vpin, RANGE_1_MA);
		hvs_15->set_voltage(vset, RANGE_1_KV); 
		wait.delay_10_us(1500); // NEED 15MS 
		Imeas_750V = hvs_15->measure_average(25);
		hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
		wait.delay_10_us(500);	

		// BVD_100UA
		BVD_Vpin = hvs_15->measure_average(25);
		BVD_Vpin -= Imeas_750V * 47e3; // subtract 47k vdrop 
		if(BVD_Vpin >= Vcheck)
		{
				// HL made changes to keep Vpin testing at 700V, 650V & 500V as DE requested in the beginning.
				hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
				hvs_15->set_current(ifrc_Vpin, RANGE_1_MA);
				//hvs_15->set_voltage(700, RANGE_1_KV);
				hvs_15->set_voltage(vset2, RANGE_1_KV);
				wait.delay_10_us(500);
				Imeas_700V = hvs_15->measure_average(25);		

				hvs_15->set_current(ifrc_Vpin, RANGE_1_MA);
				//hvs_15->set_voltage(650, RANGE_1_KV); 
				hvs_15->set_voltage(vset3, RANGE_1_KV); 
				wait.delay_10_us(500);
				Imeas_650V = hvs_15->measure_average(25);		

				hvs_15->set_current(ifrc_Vpin, RANGE_1_MA);
				//hvs_15->set_voltage(500, RANGE_1_KV); 	
				HVS_ramp_down(vset3, vset4, 50);
				wait.delay_10_us(600);
				Imeas_500V = hvs_15->measure_average(25);
		}


		// Check to make sure HVS is connected to Vpin //
		// Connect RDSON buffer input to Vpin and bring up Vpin to 5V. Should 
		// measure leakage current into RDSON buffer. //
		hvs_15->set_voltage(10, RANGE_1_KV);
		wait.delay_10_us(50);
		hvs_15->set_voltage(5, RANGE_1_KV);
		wait.delay_10_us(200);
		Close_relay(KC6C); // Connect Vpin to Rdson buffer input //
		Close_relay(K35); // Connect Vpin to Rdson buffer input //
		BC_ovi->connect(BC_ch);
		BC_ovi->set_voltage(BC_ch, 0, VOLT_5_RANGE); // OVI_1_3 //
		BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA); // OVI_1_3 //
		wait.delay_10_us(300);
		hvs_15->set_current(1e-3, RANGE_1_MA);
		hvs_15->set_voltage(5, RANGE_1_KV);
		hvs_15->set_meas_mode(HVS_MEASURE_CURRENT); 
		//wait.delay_10_us(4500);
		wait.delay_10_us(100);
		Temp_MeasI = hvs_15->measure();
		hvs_15->set_voltage(0, RANGE_1_KV);
		Open_relay(KC6C); // Disconnect Vpin from Rdson buffer input //
		Open_relay(K35); // Disconnect Vpin from Rdson buffer input //
		wait.delay_10_us(300);
		if (Temp_MeasI < 40e-6)
		{
			g_Error_Flag = -215; // Error.  HVS not connected to Vpin. //
		}

//		HVS_ramp_down(vset4, 0, 50);

		// Ramp VBPP from 5.5V to 0V
		j=5.5;
		while(j>=0)
		{
			dvi_11->set_voltage(DVI_CHANNEL_1, j, VOLT_10_RANGE);
			j=j-0.1;	
		}
		wait.delay_10_us(50);

		// Set D = 00V / 100mA
		dvi_11->set_voltage(DVI_CHANNEL_0, 0, VOLT_50_RANGE);
		wait.delay_10_us(50);
		Open_relay(K28_K29_K34_K69); // Controls relays K28, K29, K34 on loadboar and K69 on contactor board. // 
									 // Turn relay off on contactor board to reconnect OVI to UV pin & disconnect HVS from UV pin.
									 // Disconnect DVI_11_1 from BPP.
									 // Reconnect HVS to either D or FWf.
		Open_relay(K4); // Disconnect HVS from 47k resistor
		Open_relay(K1); // Disconnect DVI_11_0 from Drain directly (Kelvin connection)
		Open_relay(K2);
		Open_relay(K18);
		Open_relay(K5);
		ovi_1->connect(0);
		ovi_1->connect(1);
		ovi_1->connect(2);
		ovi_1->connect(3);
		ovi_1->connect(4);
		ovi_1->connect(5);
		ovi_1->connect(6);
		ovi_1->connect(7);
		ovi_3->connect(0);
		ovi_3->connect(1);
		ovi_3->connect(2);
		ovi_3->connect(3);
		ovi_3->connect(4);
		//ovi_3->connect(5); // Keep disconnected //
		ovi_3->connect(6);
		ovi_3->connect(7);
		Open_relay(K4); // Disconnect HVS from Drain
		Open_relay(K11); // Disconnect BPP from DVI
		Open_relay(K5); // Disconnect HVS from FW pin
		Open_relay(K18); // Disconnect FW from DVI-11-1
		hvs_15->open_relay(HVS_NEG_FORCE); // NEG_FORCE (J6,B3)  hardwired to gnd 
		hvs_15->open_relay(HVS_SHORT_NEG_FS);	
		hvs_15->open_relay(HVS_GND_NEG_SENSE);	
		hvs_15->open_relay(HVS_SHORT_POS_FS);
		hvs_15->open_relay(HVS_FORCE_POS); // POS_FORCE (J6,B9) to drain	
		delay(2);
		hvs_15->init();
		//ddd_7->ddd_connect_drivers();

		// Force failure if HVS was not connected to Vpin. //
		if (g_Error_Flag == -215) // Error.  HVS not connected to Vpin. //
		{
			BVD_Vpin = -99;
			Imeas_750V = -99;
			Imeas_700V = -99;
			Imeas_650V = -99;
			Imeas_500V = -99;
		}

		// Datalog
		PiDatalog(func, A_BVD_Vpin, BVD_Vpin, 10, POWER_UNIT);		
		PiDatalog(func, A_IDS_750V_Vpin, Imeas_750V, 10, POWER_MICRO);		
		PiDatalog(func, A_IDS_700V_Vpin, Imeas_700V, 10, POWER_MICRO);		
		PiDatalog(func, A_IDS_650V_Vpin, Imeas_650V, 10, POWER_MICRO);		
		PiDatalog(func, A_IDS_500V_Vpin, Imeas_500V, 10, POWER_MICRO);	


	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		BV_Vpin_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_BV_Vpin_TT, BV_Vpin_TT, 10, POWER_MILLI);
	}	

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;

	}
*/
}
