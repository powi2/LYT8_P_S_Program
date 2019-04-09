//==============================================================================
// Fosc_Pst_S.cpp (User function)
// 
//    void Fosc_Pst_S_user_init(test_function& func)
//    void Fosc_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Pst_S_user_init(test_function& func)
{
	Fosc_Pst_S_params *ours;
    ours = (Fosc_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Pst_S_params *ours;
    ours = (Fosc_Pst_S_params *)func.params;

			gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Pst_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_Fn_CLK1M_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	float Fosc_Pst_S    = 0;
	float Fosc_FF_00_S  = 0;
	float Fosc_FF_01_S  = 0;
	float Fosc_FF_10_S  = 0;
	float Fosc_FF_11_S  = 0;
	float Fosc_Delta_S  = 0;
	float Fosc_TonMax_S = 0;
	float Fosc_DCMax_S  = 0;
	float Fosc_Jit_p5pct_S = 0;
	float Fosc_Jit_n5pct_S = 0;
	float Fosc_Jitter_S = 0;
	float Fosc_Pst_TT   = 0;
	float temp_1        = 0;
	float ton           = 0;
	float toff          = 0;
	float period        = 0;
	float Duty_Cycle    = 0;
	float tmeas         = 0;
	int   i             = 0;
	int   Skip_Test0    = 0;
	int   Skip_Test1    = 0;
	int   Skip_Test2    = 0;
	int   Skip_Test3    = 0;


Pulse pulse;

	// Open all relays //
	Initialize_Relays();

	Load_100Khz_Pulses();

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
	//HSG: disconnect and connect to 2nF
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_30_MA);
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

	//Setup TMU on Buffer of HSG pin.
	tmu_6->close_relay(TMU_HIZ_DUT4); 
	tmu_6->start_trigger_setup(8.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(8.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K7_IS_SPI_TB);       //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		 //Disconnect DVI_13_1 from IS.
	Close_relay(K2_HSG_SPI_TB);      //disconect OVI_1_0 from HSG.
	Open_relay(K1_HSG_SPI_RB);       //Keep Kelvin on HSG
	Close_relay(K5_HSG_SPI_TB);      //Connect HSG to buffer 
	Close_relay(K3_B_SPI_TB);		 //Connect 2nF to B
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Close_relay(K7_DDD_TB);          //Connect DDD_7_7 to FW.
	Close_relay(K1_FW_SPI_TB);       //Disconnect OVI from FW.
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 

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

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);

	//Clock FW with 10Khz pulses.
	Run_100Khz_Pulses();
	wait.delay_10_us(10);

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1, VOLT_5_RANGE);
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

	//ZTMC_sig_EN and Core_en.  Dont turn on B driver because of noise.
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZOpenDrain<1> & ZTMC_Dsbl_DaliCk2
	//0x00 0x60 write 0x02 0x40
	DSM_I2C_Write('w', g_TEST_CTRL1, 0x4002);

	//TEST_CTRL3[12]=1 && TEST_CTRL3[11:0] = 4095
	//0x00 0x64 write 0xFF 0x1F
	DSM_I2C_Write('w', 0x64, 0x1FFF);

	//TEST_CTRL4[5]=1 && TEST_CTRL4[4:0] = 16==> Jitter Average.
	//0x00 0x66 write 0x30 0x00
	DSM_I2C_Write('w', g_TEST_CTRL4, 0x0030);


	//Set DL_on5D on HSG
	// 0x00 0x46 write 0x00 0x28
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2800);

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

	//Monitor 100Khz switching on HSG pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(300e-6);	 
	tmeas/=15;
	period = tmeas;
	if (tmeas != 0)
		Fosc_Pst_S = 1/tmeas;
	else
		Fosc_Pst_S = 0.0;	

	if (g_Burn_Enable_S && g_Fosc_Pre != 0)
	{
		Fosc_Delta_S = 100*(Fosc_Pst_S - g_Fosc_Pre) / g_Fosc_Pre;

	}

	//--------------------------------------------------------------------------------
	//---------------TonMax--------------------------------------------------------
	//---------------------------------------------------------------------------------
	tmu_6->start_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->stop_trigger_setup(11.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	Fosc_TonMax_S = tmu_6->read(300e-6);

	toff = Fosc_TonMax_S;
	ton  = period - toff;

	if(period != 0)
	{
		Duty_Cycle = 100*ton / period;
	}

	if(g_Trim_ZffOption_B19_20_S_Trimops == 0)
	{
		 Fosc_FF_00_S  = Fosc_Pst_S;
		 Skip_Test0     = 1;
		
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 1)
	{
		
		 Fosc_FF_01_S  = Fosc_Pst_S;
		 Skip_Test1     = 1;
		 
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 2)
	{
		
		 Fosc_FF_10_S  = Fosc_Pst_S;
		 Skip_Test2    = 1;
		
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 3)
	{
		 Fosc_FF_11_S  = Fosc_Pst_S;
		 Skip_Test3    = 1;
	}
	else //Not doing anything. something is wrong and datalog as 0 to fail the tests.
	{
		 Fosc_FF_00_S  = 0;
		 Fosc_FF_01_S  = 0;
		 Fosc_FF_10_S  = 0;
		 Fosc_FF_11_S  = 0;
	}

	//Reset TMU Settings.
	tmu_6->start_trigger_setup(8.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(8.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	
	if(Skip_Test0 == 0)
	{
		////////////FeedFWD Option = 0 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 0);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 0);
		Program_Single_TrimRegister(g_EEP_W_E2);


		//Monitor freq switching on HSG pin.	
		tmu_6->start_holdoff(15,TRUE);
		tmu_6->stop_holdoff(15,TRUE);
		wait.delay_10_us(10);
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas = tmu_6->read(300e-6);	 
		tmeas/=15;
		period = tmeas;
		if (tmeas != 0)
			Fosc_FF_00_S = 1/tmeas;
		else
			Fosc_FF_00_S = 0.0;	

	}
	
	if(Skip_Test1 == 0)
	{
		////////////FeedFWD Option = 1 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 0);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 1);
		Program_Single_TrimRegister(g_EEP_W_E2);


		//Monitor 100Khz switching on HSG pin.	
		tmu_6->start_holdoff(15,TRUE);
		tmu_6->stop_holdoff(15,TRUE);
		wait.delay_10_us(10);
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas = tmu_6->read(300e-6);	 
		tmeas/=15;
		period = tmeas;
		if (tmeas != 0)
			Fosc_FF_01_S = 1/tmeas;
		else
			Fosc_FF_01_S = 0.0;	

	}

	if(Skip_Test2 == 0)
	{
		////////////FeedFWD Option = 2 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 1);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 0);
		Program_Single_TrimRegister(g_EEP_W_E2);


		//Monitor 100Khz switching on HSG pin.	
		tmu_6->start_holdoff(15,TRUE);
		tmu_6->stop_holdoff(15,TRUE);
		wait.delay_10_us(10);
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas = tmu_6->read(300e-6);	 
		tmeas/=15;
		period = tmeas;
		if (tmeas != 0)
			Fosc_FF_10_S = 1/tmeas;
		else
			Fosc_FF_10_S = 0.0;	

	}

	if(Skip_Test3 == 0)
	{
		////////////FeedFWD Option = 1 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 1);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 1);
		Program_Single_TrimRegister(g_EEP_W_E2);


		//Monitor 100Khz switching on HSG pin.	
		tmu_6->start_holdoff(15,TRUE);
		tmu_6->stop_holdoff(15,TRUE);
		wait.delay_10_us(10);
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas = tmu_6->read(300e-6);	 
		tmeas/=15;
		period = tmeas;
		if (tmeas != 0)
			Fosc_FF_11_S = 1/tmeas;
		else
			Fosc_FF_11_S = 0.0;	

	}

	//Reset EEpr[2] to original settings.

	if(g_Trim_ZffOption_B19_20_S_Trimops == 0)
	{
		////////////FeedFWD Option = 0 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 0);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 0);
		Program_Single_TrimRegister(g_EEP_W_E2);
		
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 1)
	{
		////////////FeedFWD Option = 1 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 0);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 1);
		Program_Single_TrimRegister(g_EEP_W_E2);
		 
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 2)
	{
		
	////////////FeedFWD Option = 2 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 1);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 0);
		Program_Single_TrimRegister(g_EEP_W_E2);		 
		
	}
	else if(g_Trim_ZffOption_B19_20_S_Trimops == 3)
	{
	////////////FeedFWD Option = 3 //////////////
		Set_EEprBit(EEpr_Bank_S[E2], 19-16, 1);
		Set_EEprBit(EEpr_Bank_S[E2], 20-16, 1);
		Program_Single_TrimRegister(g_EEP_W_E2);		
	}


	//-------------------------------------------------------------------------------------------
	//Measure Jitter Frequency here.
	//--------------------------------------------------------------------------------------------
	//Set TEST_CTRL4[5] = 1 & TEST_CTRL4[4:0] = 0 to meas freq with +5% jitter.
	//0x00 0x66 write 0x20 0x00
	DSM_I2C_Write('w', g_TEST_CTRL4, 0x0020);

	
	//Monitor freq with +5% jitter switching on HSG pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(300e-6);	 
	tmeas/=15;
	period = tmeas;
	if (tmeas != 0)
		Fosc_Jit_p5pct_S = 1/tmeas;
	else
		Fosc_Jit_p5pct_S = 0.0;	


	//Set TEST_CTRL4[5] = 1 & TEST_CTRL4[4:0] = 26 to meas freq with -5% jitter.
	//0x00 0x66 write 0x3A 0x00
	DSM_I2C_Write('w', g_TEST_CTRL4, 0x003A);

	//Monitor freq with -5% jitter switching on HSG pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(300e-6);	 
	tmeas/=15;
	period = tmeas;
	if (tmeas != 0)
		Fosc_Jit_n5pct_S = 1/tmeas;
	else
		Fosc_Jit_n5pct_S = 0.0;	


	Fosc_Jitter_S = Fosc_Jit_p5pct_S - Fosc_Jit_n5pct_S;

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

	Open_relay(K7_IS_SPI_TB);         //Disconnect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		  //Reconnect DVI_13_1 to IS.
	Open_relay(K2_HSG_SPI_TB);        //Keep OVI_1_0 on HSG.
	Open_relay(K1_HSG_SPI_RB);        //Disconnect pullup R from HSG. 
	Open_relay(K5_HSG_SPI_TB);        //Disconnect HSG from buffer 
	Open_relay(K3_B_SPI_TB);		  //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Open_relay(K7_DDD_TB);           //Disconnect DDD_7_7 from FW.
	Open_relay(K1_FW_SPI_TB);        //Reconnect OVI to FW.
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 
	tmu_6->open_relay(TMU_HIZ_DUT4); 
	wait.delay_10_us(250);

	


	PiDatalog(func, A_Fosc_Pst_S,		    Fosc_Pst_S,               26, POWER_KILO);
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_Fosc_Delta_S,     Fosc_Delta_S,           26, POWER_UNIT);
	}
	PiDatalog(func, A_Fosc_TonMax_S,        ton,           26, POWER_MICRO);
	PiDatalog(func, A_Fosc_DCMax_S,         Duty_Cycle,       26, POWER_UNIT);

	PiDatalog(func, A_Fosc_FF_00_S,		    Fosc_FF_00_S,               26, POWER_KILO);
	PiDatalog(func, A_Fosc_FF_01_S,		    Fosc_FF_01_S,               26, POWER_KILO);
	PiDatalog(func, A_Fosc_FF_10_S,		    Fosc_FF_10_S,               26, POWER_KILO);
	PiDatalog(func, A_Fosc_FF_11_S,		    Fosc_FF_11_S,               26, POWER_KILO);

	PiDatalog(func, A_Fosc_Jit_Max_S,		Fosc_Jit_p5pct_S,               26, POWER_KILO);
	PiDatalog(func, A_Fosc_Jit_Min_S,		Fosc_Jit_n5pct_S,               26, POWER_KILO);
	PiDatalog(func, A_Fosc_Jitter_S,		Fosc_Jitter_S,               26, POWER_KILO);


}
