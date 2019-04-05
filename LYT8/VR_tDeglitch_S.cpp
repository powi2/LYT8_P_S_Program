//==============================================================================
// VR_tDeglitch_S.cpp (User function)
// 
//    void VR_tDeglitch_S_user_init(test_function& func)
//    void VR_tDeglitch_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "VR_tDeglitch_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VR_tDeglitch_S_user_init(test_function& func)
{
	VR_tDeglitch_S_params *ours;
    ours = (VR_tDeglitch_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VR_tDeglitch_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VR_tDeglitch_S_params *ours;
    ours = (VR_tDeglitch_S_params *)func.params;

			gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VR_tDeglitch_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_Fn_VADC_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i                  = 0;
	float j                  = 0.0;
	float temp               = 0.0;
	float tmeas              = 0.0;
	float VFB                = 0.0;
	float t_VRB_10V15V       = 0.0;
	float t_VRB_15V20V       = 0.0;
	float t_VRB_20V25V       = 0.0;
	float t_VRB_25V30V       = 0.0;
	float t_VRB_30V35V       = 0.0;
	float t_VRB_35V40V       = 0.0;
	float t_VRB_40V45V       = 0.0;
	float t_VRB_45V50V       = 0.0;
	float VRB_tDeglitch_S_TT = 0.0;


	float VFB_Meas[5] = {0};
	
Pulse pulse;

	// Open all relays //
	Initialize_Relays();


	int StartAddr = 1000;
	Load_VR_DDD_Step_Pulse(StartAddr);

	// Initialize Instruments //
	Initialize_Instruments();   //No content for now.

	// Setup Instruments //
	// Primary
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);                  // DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);     
	UV_dvi->set_voltage(UV_ch, 0.0, RANGE_10_V);                   // DVI_21_1
	UV_dvi->set_current(UV_ch, 30e-3, RANGE_300_MA);	
	BPP_dvi->set_voltage(BPP_ch, 0.0, RANGE_10_V);				   // DVI_11_1
	BPP_dvi->set_current(BPP_ch, 200e-3, RANGE_300_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE);            // OVI_3_0
	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);

	//Secondary.
	//HSG needs to connect thru buffer then.
	HSG_ovi->set_current(HSG_ch, 3e-3, RANGE_3_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 10e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = 1.15V/30mA then sweep or binary search.
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
	//IS = 0V/200mA...should it be a bit above ground?
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-6, RANGE_200_UA);
	//SDA will be at 3.3V/30mA for I2C
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	//SCL will be at 3.3V/30mA for I2C
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	//BPS will be Hiz
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	//HBP will be Hiz.
	HBP_dvi2k->set_current(HBP_ch, 0.0001e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  
	VR_dvi->set_current(VR_ch, 0.1e-3, RANGE_300_MA);	     //DVI_9_1
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	VR_dvi->set_current(VRstep_ch, 0.1e-3, RANGE_300_MA);	 //DVI_9_0
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//Switch GNDs on TMT LB not TB
	mux_20->close_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->close_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Secondary I2C to ready Secondary Die ID.
	BPS_dvi->open_relay(CONN_FORCE0);
	HBP_dvi2k->open_relay(CONN_FORCE0);

	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG for Open Drain config later.
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 on B for Open Drain config later.
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Open_relay(K3_B_SPI_TB);		//Do not connect 2nF to B!
	Open_relay(K3_HSG_SPI_TB);      //Do not connect 2nF to HSG!
	Open_relay(K7_IS_SPI_TB);      //Connect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		//Disconnect DVI_13_1 from IS.
	Close_relay(K5_B_SPI_TB);       //Connect B to Buffer.
	Close_relay(K5_HSG_SPI_TB);     //Connect Buffer/HSG.
	Open_relay(K1_FW_SPI_TB);      //Disconnect OVI from FW pin.
	Close_relay(K3_DDD_TB);         //connect DDD to VR Step Insert Module (to base of Q1)
	Close_relay(K3_VR_SPI_RB);      //Connect DVI_9_0 to DVI_VR_H high voltage setting of VR Step Insert Module.
	Close_relay(K5_VR_SPI_RB);      //Connect DVI_9_1 to DVI_VR_L low voltage setting of VR Step Insert Module.
	Close_relay(K4_TMU_TB);         //Connect TMU_Hiz3 to VR pin.
	tmu_6->close_relay(TMU_HIZ_DUT3);    // Close TMU_Hiz3 Relay on VR pin.
	tmu_6->close_relay(TMU_CHAN_B_DUT2); // Connect TMU CHb to B pin.
	tmu_6->open_relay(TMU_HIZ_DUT2);     // disconnect TMU_Hiz_dut2 from B pin.



	//Disonnect Pullup R from TS and UV pins
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	//Connect Pullup R to SCL & SDA
	Close_relay(K1_SDA_SPI_TB);
	Close_relay(K1_SCL_SPI_TB);
	//Disconnect DSM CLK & Data from primary pins: TS & UV
	//Connect DSM CLK & Data to secondary:         SCL & SDA
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Close_relay(K2_DSM_TB);
	Close_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	//Keep FW @ 0V.
	ddd_7->ddd_run_pattern(StartAddr,StartAddr+2);  
	delay(1);

	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);	     //DVI_9_1
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 

	FB_ovi3->set_voltage(FB_ch, 0.8, VOLT_2_RANGE); 	
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VR_ch, 16, VOLT_50_RANGE);   //DVI_9_1 Low
	VR_dvi->set_voltage(VRstep_ch, 16, VOLT_50_RANGE);//DVI_9_0 High.
	wait.delay_10_us(200);

	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 13, VOLT_20_RANGE);
	wait.delay_10_us(200);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);


	//-----------------------------------------------------------------------------------
	//I2C command.
	//------------------------------------------------------------------------------------
	
	//Sometimes, DSM I2C can't be written correctly the first time.
	//Change the DSM timeout to 1ms since the default timeout is approximately 35ms.
	//g_Debug = 1;
	DSM_set_I2C_timeout(0, 1);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter TM
	Analog_TM_Enable_Secondary();

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.

	//ZTMC_Driver_En & ZTMC_Dsbl_FBshrt							  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en (HSG is enabled)
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	if(1)
	{
	

		// Disable FB short, enable driver and ZTMC_VR_Target
		//0x00 0x62 write 0x88 0x10
		DSM_I2C_Write('w', 0x62, 0x1088);

		// Enable HSG and B out and core_en
		//0x00 0x40 write 0x07 00
		DSM_I2C_Write('w', 0x40, 0x0007);

		// Bring out DVR_comps_out to B
		//0x00 0x42 write 0x06 0x00
		DSM_I2C_Write('w', 0x42, 0x0006);

		////This is to get out of Deep Dimming mode.
		DSM_I2C_Write('w', 0x64, 0x1FFF);

		//Enable ZTMC_VR_comps_link 
		//0x00 0x46 write 0x08 0x00
		DSM_I2C_Write('w', 0x46, 0x0008);

		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

		//Reset VR to 10V
		VR_dvi->set_meas_mode(VR_ch, DVI_MEASURE_VOLTAGE);    //Need to measure VR low in order to set TMT threshold properly.
		VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
		//VR_dvi->set_voltage(VRstep_ch, 17, VOLT_50_RANGE);//DVI_9_0 High.
		//VR_dvi->set_voltage(VR_ch, 10, VOLT_50_RANGE);	  //DVI_9_1 Low.
		VR_dvi->set_voltage(VRstep_ch, g_B2_MaxSate+1, VOLT_50_RANGE);//DVI_9_0 High.
		VR_dvi->set_voltage(VR_ch, g_B2_MaxSate-5, VOLT_50_RANGE);	  //DVI_9_1 Low.
		delay(2);

		//temp = VR_dvi->measure_average(25);

		//tmu_6->start_trigger_setup(14.2, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
		tmu_6->start_trigger_setup(g_B2_MaxSate-1.5, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
		tmu_6->stop_trigger_setup(3.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		wait.delay_10_us(200);
		tmu_6->arm();
		wait.delay_10_us(30);

		Run_VR_DDD_Step_Pulse(StartAddr);	
		wait.delay_10_us(10);
		t_VRB_10V15V = tmu_6->read(2e-3);

		//----------------------------------------------------------------------------------------------------------
		
		//VR_dvi->set_voltage(VRstep_ch, 20, VOLT_50_RANGE);//DVI_9_0 High.
		//VR_dvi->set_voltage(VR_ch, 13, VOLT_50_RANGE);	  //DVI_9_1 Low.

		VR_dvi->set_voltage(VRstep_ch, g_B1_FastUpdate+1, VOLT_50_RANGE);//DVI_9_0 High.
		VR_dvi->set_voltage(VR_ch, g_B1_FastUpdate-4, VOLT_50_RANGE);	  //DVI_9_1 Low.
		delay(5);

		//temp = VR_dvi->measure_average(25);

		//tmu_6->start_trigger_setup(17.4, POS_SLOPE, TMU_HIZ, TMU_IN_25V);	
		tmu_6->start_trigger_setup(g_B1_FastUpdate, POS_SLOPE, TMU_HIZ, TMU_IN_25V);	
		tmu_6->stop_trigger_setup(3.0, NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		wait.delay_10_us(200);
		tmu_6->arm();
		wait.delay_10_us(30);

		Run_VR_DDD_Step_Pulse(StartAddr);	
		wait.delay_10_us(10);
		t_VRB_15V20V = tmu_6->read(2e-3);

		//--------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------------
		//float delta = 7.0;
		//float v_start = 21.5;
		//VR_dvi->set_voltage(VRstep_ch, v_start + delta, VOLT_50_RANGE);//DVI_9_0 High.
		//VR_dvi->set_voltage(VR_ch, v_start, VOLT_50_RANGE);	  //DVI_9_1 Low.

		VR_dvi->set_voltage(VRstep_ch, g_A3_Target_VR+1, VOLT_50_RANGE);//DVI_9_0 High.
		VR_dvi->set_voltage(VR_ch, g_A3_Target_VR-8, VOLT_50_RANGE);	  //DVI_9_1 Low.
		delay(5);

	//temp = VR_dvi->measure_average(25);	

		//tmu_6->start_trigger_setup(25.5, POS_SLOPE, TMU_HIZ, TMU_IN_25V);	
		tmu_6->start_trigger_setup(g_A3_Target_VR-2.5, POS_SLOPE, TMU_HIZ, TMU_IN_50V);	
		tmu_6->stop_trigger_setup(3.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		wait.delay_10_us(200);
		tmu_6->arm();
		wait.delay_10_us(30);


		Run_VR_DDD_Step_Pulse(StartAddr);	
		wait.delay_10_us(10);
		t_VRB_20V25V = tmu_6->read(2e-3);


	}


	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

	//Reset DDD low level to 0V.
	ddd_7->ddd_set_lo_level(0.0);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VR_ch, 10.0, VOLT_50_RANGE); 
	delay(5);
	VR_dvi->set_voltage(VRstep_ch, 10, VOLT_50_RANGE); 
	wait.delay_10_us(200);

	B_ovi3->set_current(B_ch1, 0.1e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);

	HSG_ovi->set_current(HSG_ch, 0.1e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	HBP_dvi2k->set_voltage(HBP_ch, 5, VOLT_20_RANGE);
	VR_dvi->set_voltage(VR_ch, 5.0, VOLT_50_RANGE); 
	VR_dvi->set_voltage(VRstep_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);				
	wait.delay_10_us(10);

	HBP_dvi2k->set_voltage(HBP_ch, 0, VOLT_20_RANGE);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	delay(5);
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	FB_ovi3->connect(FB_ch);
	Open_relay(K6_DDD_TB);

	HBP_dvi2k->close_relay(CONN_FORCE0);
	BPS_dvi->close_relay(CONN_FORCE0);
	Open_relay(K2_HSG_SPI_TB);      //Keep Kelvin connection of OVI_1_0 on HSG 
	Open_relay(K2_B_SPI_TB);        //Keep Kelvin connection of OVI_3_1 on B
	Open_relay(K3_B_SPI_TB);		//Do not connect 2nF to B!
	Open_relay(K3_HSG_SPI_TB);      //Do not connect 2nF to HSG!
	Open_relay(K7_IS_SPI_TB);       //Disconnect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		//Reconnect DVI_13_1 from IS.
	Open_relay(K5_B_SPI_TB);        //Disconnect B from Buffer.
	Open_relay(K5_HSG_SPI_TB);      //Disconnect Buffer/HSG.
	Open_relay(K1_FW_SPI_TB);       //Reconnect OVI to FW pin.
	Open_relay(K3_DDD_TB);          //Disconnect DDD from VR Insert Module
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	Open_relay(K1_SDA_SPI_TB);
	Open_relay(K1_SCL_SPI_TB);
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Open_relay(K6_VR_SPI_RB);      //Disconnect DVI_9_0 from VR thru Diode.  
	VR_dvi->close_relay(CONN_FORCE1);
	VR_dvi->close_relay(CONN_SENSE1);
	mux_20->open_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->open_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Open_relay(K3_VR_SPI_RB);      //Connect DVI_9_0 to DVI_VR_H high voltage setting of VR Step Insert Module.
	Open_relay(K5_VR_SPI_RB);      //Connect DVI_9_1 to DVI_VR_L low voltage setting of VR Step Insert Module.
	Open_relay(K4_TMU_TB);         //Connect TMU_Hiz3 to VR pin.
	tmu_6->open_relay(TMU_HIZ_DUT3);    // Close TMU_Hiz3 Relay on VR pin.
	tmu_6->open_relay(TMU_CHAN_B_DUT2); // Connect TMU CHA to B pin.
	tmu_6->open_relay(TMU_HIZ_DUT2);     // disconnect TMU_Hiz_dut2 from B pin.
	wait.delay_10_us(250);
	
	PiDatalog(func, A_t_VRB_10V15V,		  t_VRB_10V15V,      26, POWER_MICRO);
	PiDatalog(func, A_t_VRB_15V20V,		  t_VRB_15V20V,      26, POWER_MICRO);
	PiDatalog(func, A_t_VRB_20V25V,		  t_VRB_20V25V,      26, POWER_MICRO);


	
	
	
	


	////////if (g_Trim_Enable_S)
	////////{
	////////	PiDatalog(func, A_VADC_Delta_S,      VADC_Delta_S,           26, POWER_UNIT);
	////////}
	////////

}
