//==============================================================================
// CLOCK1M_Pst_S.cpp (User function)
// 
//    void CLOCK1M_Pst_S_user_init(test_function& func)
//    void CLOCK1M_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "CLOCK1M_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CLOCK1M_Pst_S_user_init(test_function& func)
{
	CLOCK1M_Pst_S_params *ours;
    ours = (CLOCK1M_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CLOCK1M_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    CLOCK1M_Pst_S_params *ours;
    ours = (CLOCK1M_Pst_S_params *)func.params;
			// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CLK1M_Pst, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_Fn_CLK1M_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	

	// Test Names //
	float CLK1M_Pst_S     = 0;
	float CLK1M_Delta_S   = 0;
	float CLK1M_DCycle_S  = 0; 
	float CLK6M_S  = 0;
	float CLK6M_DCycle_S  = 0;
	float CLK1M_Pst_TT    = 0;

Pulse pulse;
	float   tmeas             = 0;
	
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	//Initialize_Instruments();   //No content for now.

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
	//HSG: disconnect and connect to 2nF
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  require open drain config and use pullup R.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = Hiz.
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	//IS = 0V/200mA...should it be a bit above ground?
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-6, RANGE_200_UA);//Keep 200UA range here to minimize range error.
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
	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Setup TMU on Buffer of B pin.
	tmu_6->close_relay(TMU_HIZ_DUT2); 
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(2.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K2_HSG_SPI_TB);      //Disconnect OVI_1_0 from HSG.
	Close_relay(K3_HSG_SPI_TB);      //Connect 2nF to HSG
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 connecting to B.
	Close_relay(K1_B_SPI_RB);       //Pullup R on B for Open Drain config later.
	Close_relay(K5_B_SPI_TB);       //Connect B to Buffer.

	
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

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE);
	//FB_ovi3->disconnect(FB_ch);  //Disconnect OVI from FB to keep it at Hiz.
	wait.delay_10_us(10);
	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	//HBP_dvi2k->set_voltage(HBP_ch, g_HBP_Pre_S, VOLT_20_RANGE);
	wait.delay_10_us(500);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

	//Setup IS for mesuring current.
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, 200e-6, RANGE_200_UA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);
	wait.delay_10_us(100);

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

	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.

	//ZTMC_Driver_en & ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_sig_EN and Core_en.  Dont turn on HSG driver because of noise.
	//0x00 0x40 write 0x05 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);

	//0x00 0x60 write 0x00 0xC0  ==> Open Drain on HSG & B.
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xC000);

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE);
	wait.delay_10_us(10);
	FB_ovi3->disconnect(FB_ch);  //Disconnect OVI from FB to keep it at Hiz.
	wait.delay_10_us(250);
	//Set pull V& I on B
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE);


	//DsysClk1Mhz on B.
	//0x00 0x42 write 0x0F 0x00
	DSM_I2C_Write('w', 0x42, 0x000F);

	//DsysClk6Mhz on B.
	//0x00 0x42 write 0x0F 0x00
	//DSM_I2C_Write('w', 0x42, 0x0018);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);


	//Monitor 1Mhz switching on Boost pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(150e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		CLK1M_Pst_S = 1/tmeas;
	else
		CLK1M_Pst_S = 0.0;	

	if (g_Trim_Enable_S && g_CLK1M_Pre != 0)
	{
	
		CLK1M_Delta_S = 100*(CLK1M_Pst_S - g_CLK1M_Pre) / g_CLK1M_Pre;
	}

	//DsysClk6Mhz on B.
	//0x00 0x42 write 0x0F 0x00
	DSM_I2C_Write('w', 0x42, 0x0018);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);


	//Monitor 1Mhz switching on Boost pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(150e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		CLK6M_S = 1/tmeas;
	else
		CLK6M_S = 0.0;	











	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);				
	wait.delay_10_us(10);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	HBP_dvi2k->close_relay(CONN_FORCE0);
	BPS_dvi->close_relay(CONN_FORCE0);
	Open_relay(K1_SDA_SPI_TB);       //Disconnect pullup R from SDA.
	Open_relay(K1_SCL_SPI_TB);       //Disconnect pullup R from SCL
	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	Open_relay(K4_DSM_TB);           //Disconnect DSM SCL from DUT SCL
	Open_relay(K2_HSG_SPI_TB);		 //Reconnect OVI_1_0 to HSG
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 connecting to B.
	Open_relay(K1_B_SPI_RB);        //Disconnect Pullup R on B 
	FB_ovi3->connect(FB_ch);			//Reconnect OVI to FB.
	Open_relay(K5_B_SPI_TB);       //Disconnect B from Buffer.
	tmu_6->open_relay(TMU_HIZ_DUT2); 
	wait.delay_10_us(250);


	PiDatalog(func, A_CLK1M_Pst_S,		  CLK1M_Pst_S,               26, POWER_MEGA);
	if (g_Trim_Enable_S)
	{
		PiDatalog(func, A_CLK1M_Delta_S,		  CLK1M_Delta_S,               26, POWER_UNIT);
	}
	PiDatalog(func, A_CLK6M_S,		  CLK6M_S,               26, POWER_MEGA);


	
}
