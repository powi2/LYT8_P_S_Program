//==============================================================================
// HBP_S.cpp (User function)
// 
//    void HBP_S_user_init(test_function& func)
//    void HBP_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "HBP_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void HBP_S_user_init(test_function& func)
{
	HBP_S_params *ours;
    ours = (HBP_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void HBP_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    HBP_S_params *ours;
    ours = (HBP_S_params *)func.params;

	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_HBP_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	int   i                 = 0;
	
	// Test Names //
	int   HBP_M_L_PF_S      = 0;
	int   HBP_M_H_PF_S      = 0;
	int   HBP_Ext_L_S_PF    = 0;
	int   HBP_Ext_H_S_PF    = 0;
	int   Exit_loop         = 0;
	float HBP_P_S           = 0;
	
	float HBP_M_S_CHAR_S    = 0;
	float HBP_Shunt_S       = 0;
	float HBP_I_Shunt_S     = 0;
	float HBP_Ext_S_CHAR    = 0;
	float HBP_FB_Short_S    = 0;	
	float HBP_80us_Filter_S = 0;
	float HBP_Test1         = 0;	
	float HBP_Test2         = 0;
	float HBP_S_TT          = 0;
	float j                 = 0;
	float V_hsg             = 0;
	float V_b               = 0;
	float I_hbp             = 0;
	float I_tmp             = 0;
	float UpperLimit        = 0;
	float LowerLimit        = 0;
	float Start_time        = 0;
	float End_time          = 0;


Pulse pulse;

	// Open all relays //
	Initialize_Relays();

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
	tmu_6->open_relay(TMU_HIZ_DUT4); 
	tmu_6->close_relay(TMU_HIZ_DUT3); 
	tmu_6->close_relay(TMU_CHAN_B_DUT1); 

	//tmu_6->start_trigger_setup(8.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	//tmu_6->stop_trigger_setup(8.4, NEG_SLOPE, TMU_CHAN_B_DUT1, TMU_IN_20V);
	//tmu_6->start_holdoff(0,FALSE);
	//tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K3_TMU_TB);          //Connect TMU_HIZ3 to HBP.
	Close_relay(K7_IS_SPI_TB);       //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		 //Disconnect DVI_13_1 from IS.
	Close_relay(K2_HSG_SPI_TB);      //disconect OVI_1_0 from HSG.
	Close_relay(K2_B_SPI_TB);        //disconnect OVI_3_1 from B.
	Open_relay(K1_HSG_SPI_RB);       //Keep Kelvin on HSG
	Close_relay(K5_HSG_SPI_TB);      //Connect HSG to buffer 
	Close_relay(K5_B_SPI_TB);        //Connect B to buffer.
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF to B
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Close_relay(K7_DDD_TB);          //Connect DDD_7_7 to FW.
	Open_relay(K1_FW_SPI_TB);       //Disconnect OVI from FW.
	tmu_6->close_relay(TMU_CHAN_B_DUT1); 
	tmu_6->close_relay(TMU_HIZ_DUT3); 

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

	//Disconnect OVI from FB.
	FB_ovi3->disconnect(FB_ch);
	//Short HBP to FB
	Close_relay(K1_HBP_SPI_RB);
	wait.delay_10_us(250);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);

	///Power up VR to 20V to wake up 2ndary.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	HBP_dvi2k->set_meas_mode(HBP_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(500);

	HBP_FB_Short_S = HBP_dvi2k->measure_average(25);

	//VR back to 0V
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);
	VR_dvi->set_voltage(VR_ch, 0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	//Disconnect the short between HBP & FB, then reconnect OVI to FB
	Open_relay(K1_HBP_SPI_RB);  //Open relay between HBP & FB
	FB_ovi3->connect(FB_ch);   //connect OVI to FB
	HBP_dvi2k->open_relay(CONN_FORCE0);
	wait.delay_10_us(250);

	//VR back to 20V
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE);
	wait.delay_10_us(10);
	///Power up VR to 20V to wake up 2ndary.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

	HBP_P_S = HBP_dvi2k->measure_average(25);

	g_HBP_P_S = HBP_P_S;

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

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//ZTMC_Dsbl_sysRset	==> Prevent HBP_UV or losing control resetting digitial									 
	//0x00 0x62 write 0xA8 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);


	UpperLimit = (func.dlog->tests[A_HBP_Ext_S_CHAR].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_HBP_Ext_S_CHAR].f_min_limit_val[0]); // Get lower test limit //
	//Connect OVI3_2 to Boost buffer.
	Close_relay(K6_HSG_SPI_RB);
	HBP_dvi2k->set_current(HBP_ch, 5e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, LowerLimit, VOLT_20_RANGE);
	ovi_3->set_meas_mode(OVI_CHANNEL_2, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(250);

	V_b = ovi_3->measure();

	if(V_b < 3)
	{
		HBP_Ext_L_S_PF = 1;
	}

	//Program ZHBPext to Boost pin.
	//0x00 0x42 write 0x17 0x00
	DSM_I2C_Write('w', 0x42, 0x0017);

	if(g_Char_Enable_S)
	{

			j = HBP_P_S;
			while(j < 14 && Exit_loop < 1)
			{
				HBP_dvi2k->set_voltage(HBP_ch, j, VOLT_20_RANGE);
				wait.delay_10_us(10);
				V_b = ovi_3->measure();
				if(V_b > 3)
				{
					HBP_Ext_S_CHAR = j;
					Exit_loop = 1;
				}
				j = j + 0.01;
			}
	}

	HBP_dvi2k->set_voltage(HBP_ch, UpperLimit, VOLT_20_RANGE);
	wait.delay_10_us(50);

	V_b = ovi_3->measure();

	if(V_b > 3)
	{
		HBP_Ext_H_S_PF = 1;
	}

	//Reset HBP voltage.
	HBP_dvi2k->set_voltage(HBP_ch, HBP_P_S, VOLT_20_RANGE);
	wait.delay_10_us(50);

//
		
	Open_relay(K6_HSG_SPI_RB);
	wait.delay_10_us(150);//==> not hot switching due to another 1ms delay @ HBP_dvi setting below	

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);
	//Program DxHBP_UV to HSG
	//0x00 0x46 write 0x00 0x98
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x9800);

	ovi_3->set_meas_mode(OVI_CHANNEL_2, OVI_MEASURE_VOLTAGE);
	ovi_3->set_current(OVI_CHANNEL_2, 0.1e-6, RANGE_300_UA);
	ovi_3->set_voltage(OVI_CHANNEL_2, 0.0, VOLT_20_RANGE); 
	HBP_dvi2k->set_current(HBP_ch, 5e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, HBP_P_S+0.5, VOLT_20_RANGE);
	wait.delay_10_us(100);
	V_hsg = ovi_3->measure_average(5);

	UpperLimit = (func.dlog->tests[A_HBP_M_S_CHAR_S].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_HBP_M_S_CHAR_S].f_min_limit_val[0]); // Get lower test limit //

	
	//This voltage will be the upper limit of HBP_M from the search loop below.
	HBP_dvi2k->set_voltage(HBP_ch, UpperLimit, VOLT_20_RANGE);
	wait.delay_10_us(50);
	V_hsg = ovi_3->measure();
	if(V_hsg > 5)
	{
		HBP_M_H_PF_S = 1;
	}

	if(g_Char_Enable_S)
	{
		j =  HBP_P_S+0.5; 
		Exit_loop = 0;
		while(j > 7.7 && Exit_loop < 1)
		{
			HBP_dvi2k->set_voltage(HBP_ch, j, VOLT_20_RANGE);
			wait.delay_10_us(10);
			V_hsg = ovi_3->measure();
			if(V_hsg < 5)
			{
				HBP_M_S_CHAR_S = j;
				Exit_loop = 1;
			}
			else
			{
				j=j-0.1;
			}
		}
	}

	//This voltage will be the lower limit of HBP_M from the search loop below.
	HBP_dvi2k->set_voltage(HBP_ch, LowerLimit, VOLT_20_RANGE);
	wait.delay_10_us(100);
	V_hsg = ovi_3->measure_average(5);

	if(V_hsg < 5)
	{
		HBP_M_L_PF_S = 1;
	}

	//Drop VR to 5V to reset the part.
	//And to remove DVI from HBP or the test won't work.
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	HBP_dvi2k->open_relay(CONN_FORCE0);
	wait.delay_10_us(250);

	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(50);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Enter TM
	Analog_TM_Enable_Secondary();

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt
	//ZTMC_Dsbl_sysRset
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);
	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);
	//Program DxHBP_UV to HSG
	//0x00 0x46 write 0x00 0x98
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x9800);

	//Bring HBP back to HBP Plus.
	tmu_6->start_trigger_setup(HBP_M_S_CHAR_S, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->stop_trigger_setup(2, NEG_SLOPE, TMU_CHAN_B, TMU_IN_25V);
	
	ovi_3->set_meas_mode(OVI_CHANNEL_2, OVI_MEASURE_VOLTAGE);
	HBP_dvi2k->set_current(HBP_ch, 50e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, HBP_P_S+0.5, VOLT_20_RANGE);
	wait.delay_10_us(500);
	HBP_dvi2k->set_voltage(HBP_ch, 8, VOLT_20_RANGE);
	tmu_6->arm();
	wait.delay_10_us(50);
	HBP_80us_Filter_S = tmu_6->read(10e-3);


	HBP_dvi2k->set_voltage(HBP_ch, HBP_P_S+0.05, VOLT_20_RANGE);
	wait.delay_10_us(1000);

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt
	//Remove ZTMC_Dsbl_sysRset
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

//Reset
	//-------------------------

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);

	///Power up VR to 20V to wake up 2ndary.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(500);
	//----------------

	HBP_dvi2k->set_voltage(HBP_ch, 13, VOLT_20_RANGE);
	wait.delay_10_us(1000);
	//HBP_dvi2k->set_voltage(HBP_ch, 8, VOLT_20_RANGE);
	//wait.delay_10_us(1000);
	//Setting HBP back to 13V
	j = 13;
	HBP_dvi2k->set_meas_mode(HBP_ch, DVI_MEASURE_CURRENT);
	HBP_dvi2k->set_current(HBP_ch, 200e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, j, VOLT_20_RANGE);
	wait.delay_10_us(500); //Needed due to 1uF on HBP
	I_tmp = HBP_dvi2k->measure_average(10);

	Exit_loop = 0;
	while(j<19.8 && Exit_loop < 1)
	{
		HBP_dvi2k->set_voltage(HBP_ch, j, VOLT_20_RANGE);
		wait.delay_10_us(50);
		I_tmp = HBP_dvi2k->measure_average(10);
		if(I_tmp >= 2.0e-3)
		{
			HBP_Shunt_S = j;
			HBP_I_Shunt_S = I_tmp;
			Exit_loop = 1;
		}
		else
		{
			j=j+0.1;
		}

	}

	HBP_dvi2k->set_voltage(HBP_ch, 20, VOLT_20_RANGE);
	wait.delay_10_us(500);
	I_tmp = HBP_dvi2k->measure_average(10);

	HBP_dvi2k->set_voltage(HBP_ch, 10, VOLT_20_RANGE);
	wait.delay_10_us(100);

	//-------------------------------------------------------------------------------------
	//Power down.
	//-------------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	HBP_dvi2k->set_voltage(HBP_ch, 5.0, VOLT_20_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 5, VOLT_20_RANGE);
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE);
	wait.delay_10_us(10);
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);				
	wait.delay_10_us(10);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
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
	Open_relay(K2_B_SPI_TB);          //Connect OVI_3_1 to B.
	Open_relay(K1_HSG_SPI_RB);        //Disconnect pullup R from HSG. 
	Open_relay(K5_HSG_SPI_TB);        //Disconnect HSG from buffer 
	Open_relay(K3_B_SPI_TB);		  //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Open_relay(K7_DDD_TB);           //Disconnect DDD_7_7 from FW.
	Open_relay(K1_FW_SPI_TB);        //Reconnect OVI to FW.
	Open_relay(K3_TMU_TB);           //Disconnect TMU_HIZ3 from HBP.
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 
	tmu_6->open_relay(TMU_HIZ_DUT4); 
	wait.delay_10_us(250);

	PiDatalog(func, A_HBP_P_S,			HBP_P_S,			26, POWER_UNIT);
	PiDatalog(func, A_HBP_M_L_PF_S,     HBP_M_L_PF_S,    26, POWER_UNIT);
	if(g_Char_Enable_S)
	{
		PiDatalog(func, A_HBP_M_S_CHAR_S,   HBP_M_S_CHAR_S,    26, POWER_UNIT);
	}
	PiDatalog(func, A_HBP_M_H_PF_S,     HBP_M_H_PF_S,    26, POWER_UNIT);
	PiDatalog(func, A_HBP_Ext_L_S_PF,     HBP_Ext_L_S_PF,    26, POWER_UNIT);
	if(g_Char_Enable_S)
	{
		PiDatalog(	func, A_HBP_Ext_S_CHAR,   HBP_Ext_S_CHAR,    26, POWER_UNIT);
	}
	PiDatalog(func, A_HBP_Ext_H_S_PF,     HBP_Ext_H_S_PF,    26, POWER_UNIT);

	PiDatalog(func, A_HBP_Shunt_S,   HBP_Shunt_S,    26, POWER_UNIT);

	PiDatalog(func, A_HBP_80us_F_S,   HBP_80us_Filter_S,    26, POWER_MICRO);

	PiDatalog(func, A_HBP_FB_Short_S,   HBP_FB_Short_S,    26, POWER_UNIT);

	PiDatalog(func, A_HBP_Test1,   HBP_I_Shunt_S,    26, POWER_UNIT);
	PiDatalog(func, A_HBP_Test2,   I_tmp,    26, POWER_UNIT);


}
