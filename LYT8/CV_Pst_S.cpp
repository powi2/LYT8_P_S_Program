//==============================================================================
// CV_Pst_S.cpp (User function)
// 
//    void CV_Pst_S_user_init(test_function& func)
//    void CV_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "CV_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CV_Pst_S_user_init(test_function& func)
{
	CV_Pst_S_params *ours;
    ours = (CV_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CV_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    CV_Pst_S_params *ours;
    ours = (CV_Pst_S_params *)func.params;

		// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CV_Post, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_Fn_CV_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables
	float vFB_Start        = 0;
	float vStep            = 0;
	int   CV_pst_L_S_PF    = 0;
	float CV_pst_S         = 0;
	int   CV_pst_H_S_PF    = 0;
	float CV_pct_Detla_S   = 0;
	int   VcvPFOFF_L_S_PF  = 0;
	float VcvPFOFF_S	   = 0;
	int   VcvPFOFF_H_S_PF  = 0;
	int   Vref1p25V_L_S_PF = 0;
	float Vref1p25V_S	   = 0;
	int   Vref1p25V_H_S_PF = 0;
	int   VcvBoost_L_S_PF  = 0;
	float VcvBoost_S       = 0;
	int   VcvBoost_H_S_PF  = 0;
	int   VcvLowFB_L_S_PF  = 0;
	float VcvLowFB_S       = 0;
	int   VcvLowFB_H_S_PF  = 0;
	int   VcvSkip5A_L_S_PF = 0;
	float VcvSkip5A_S      = 0;
	int   VcvSkip5A_H_S_PF = 0;
	int   VcvOVP5A_L_S_PF  = 0;
	float VcvOVP5A_S       = 0;
	int   VcvOVP5A_H_S_PF  = 0;
	float IFB_Pullup_S     = 0;
	float FB_Test1         = 0;
	float FB_Test2		   = 0;
	int   CV_Pst_TT        = 0;
	float i_HSG            = 0;
	float v_Boost          = 0;
	float i_Boost          = 0;
	float j                = 0;
	float UpperLimit       = 0;
	float LowerLimit       = 0;
	int   i                = 0;
	int   loop_1           = 0;
	int   loop_2           = 0;
	int   exit_loop        = 0;
	

Pulse pulse;

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
	//HSG needs to connect thru buffer then.
	HSG_ovi->set_current(HSG_ch, 3e-3, RANGE_3_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = 1.15V/30mA then sweep or binary search.
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	//IS = 0V/200mA...should it be a bit above ground?
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);//Keep 200mA range here or IS will drop below ground.
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

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	
	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG.
	Close_relay(K1_HSG_SPI_RB);     //Connect pullup R on HSG.
	//Close_relay(K5_HSG_SPI_TB);   //Connect HSG to buffer==> No need.  Monitor current directly on OVI_1_0
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
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

	//Step 1.	vFB = 1.15V
	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);
	FB_ovi3->set_current(FB_ch, 30e-6, RANGE_30_UA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	wait.delay_10_us(10);
	
	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	//HBP_dvi2k->set_voltage(HBP_ch, g_HBP_Pre_S, VOLT_20_RANGE);
	wait.delay_10_us(500);

	IFB_Pullup_S = FB_ovi3->measure_average(25);


	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

	//////////IS leakage can be measured here??
	//IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, 2e-3, RANGE_200_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(100);

	
	//-----------------------------------------------------------------------------------
	//I2C command and sweep FB here.
	//------------------------------------------------------------------------------------
	
	//Sometimes, DSM I2C can't be written correctly the first time.
	//Change the DSM timeout to 1ms since the default timeout is approximately 35ms.
	//g_Debug = 1;
	DSM_set_I2C_timeout(0, 1);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter TM
	Analog_TM_Enable_Secondary();

	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.
	
	//Direct measuring at the input of the opamp (excluding the opamp offset)
	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)										 
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00  => Boost driver isn't on to avoid noise.
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZTMC_Avref_1p25
	//0x00 0x44 write 0x10 0x00  
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0010);

	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.0e-6, RANGE_3_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(100);
	
	CV_pst_S = FB_ovi3->measure_average(25);

	if (g_Trim_Enable_S&& g_CV_Pre != 0.0)
	{
		CV_pct_Detla_S =  100*(CV_pst_S - g_CV_Pre) / g_CV_Pre;		
	}




	//-------------------------------------------------------------------
	//Measure @ output of comparator to include the input voffset voltage.
	//Will need to cycle VR in order to get the test to work.  
	//--------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Reset FB = 1.25V
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	wait.delay_10_us(10);
	//Cycle VR from 20V -> 5V -> 20V.  
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(100);
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(100);
	
	//Enter TM
	Analog_TM_Enable_Secondary();
	
	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en ==> Avoid enable B due to noise.
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZOpenDrain<0>,ZOpenDrain<1> 
	//0x00 0x60 write 0x02 0xC0 ==> To reduce noise.
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xE020);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//This method is to include the voffset of the opamp.
	//0x00 0x46 write 0x00 0xF0  ==> enable Dcv_comps_out to HSG
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0xF000); 

	//Set pullup voltage on HSG to 2V to minimize noise when HG switches.
	HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_CURRENT);
	HSG_ovi->set_voltage(HSG_ch, 2, VOLT_5_RANGE); 
	wait.delay_10_us(200);

	//Ramp FB and record CV-1.6%, CV & CV+1.6%
	vFB_Start = 1.1;
	vStep = 2e-3;
	CV_Search(VcvPFOFF_S, Vref1p25V_S, VcvBoost_S, vFB_Start, vStep);



	//Need to disable HSG & Enable Boost.

	//ZTMC_ana_EN and Core_en ==> Avoid enable HSG due to noise.
	//0x00 0x40 write 0x05 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);

	FB_ovi3->set_voltage(FB_ch, 0.00, VOLT_5_RANGE); 
	wait.delay_10_us(10);
	//Change to 1V range to improve accuracy & repeatability.
	FB_ovi3->set_voltage(FB_ch, 0.00, VOLT_1_RANGE); 
	wait.delay_10_us(10);

	//0x00 0x42 write 0x14 0x00  ==> enable Dfb_comps_out to Boost
	DSM_I2C_Write('w', 0x42, 0x0014); 
	
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_VOLTAGE);
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE);

	
	UpperLimit = (func.dlog->tests[A_VcvLowFB_S].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_VcvLowFB_S].f_min_limit_val[0]); // Get lower test limit /

	//Voltage divider @ FB can be used to improve accuracy.  Need to change to 0.1% resistor or calibrate the offset.
	//HW modification is needed.
	FB_ovi3->set_voltage(FB_ch, LowerLimit, VOLT_1_RANGE); // DVI_11_0
	wait.delay_10_us(100);
	v_Boost = B_ovi3->measure();

	if(v_Boost <3)
	{
		VcvLowFB_L_S_PF = 1;
	}

	if(g_Char_Enable_S)
	{
		j = 0.08;
		exit_loop = 0;
		while(j< 0.12&&exit_loop <1)
		{
			FB_ovi3->set_voltage(FB_ch, j, VOLT_1_RANGE); // DVI_11_0
			wait.delay_10_us(10);
			v_Boost = B_ovi3->measure();
			if(v_Boost > 3)
			{
				VcvLowFB_S = j;
				exit_loop = 1;
			}
			j=j+0.001;
		}
	}

	FB_ovi3->set_voltage(FB_ch, UpperLimit, VOLT_1_RANGE); // DVI_11_0
	wait.delay_10_us(100);
	v_Boost = B_ovi3->measure();

	if(v_Boost >3)
	{
		VcvLowFB_H_S_PF = 1;
	}

	//--------------------------------------------------------------------------------
	//VcvSkip5A test
	//--------------------------------------------------------------------------------
	FB_ovi3->set_voltage(FB_ch, 0, VOLT_1_RANGE); // DVI_11_0
	wait.delay_10_us(10);
	FB_ovi3->set_voltage(FB_ch, 0, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	j = 0;
	while(j<=1.3)
	{
		FB_ovi3->set_voltage(FB_ch, j, VOLT_2_RANGE); // DVI_11_0
		wait.delay_10_us(10);
		j = j + 0.1;
	}

	FB_ovi3->set_voltage(FB_ch, 1.31, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	UpperLimit = (func.dlog->tests[A_VcvSkip5A_S].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_VcvSkip5A_S].f_min_limit_val[0]); // Get lower test limit /

	FB_ovi3->set_voltage(FB_ch, LowerLimit, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	v_Boost = B_ovi3->measure();

	if(v_Boost < 3)
	{
		VcvSkip5A_L_S_PF = 1;
	}



	if(g_Char_Enable_S)
	{
		j = 1.3;
		exit_loop = 0;
		while(j < 1.4 && exit_loop < 1)
		{
			FB_ovi3->set_voltage(FB_ch, j, VOLT_2_RANGE); // DVI_11_0
			wait.delay_10_us(10);
			v_Boost = B_ovi3->measure();
			if(v_Boost > 3)
			{
				VcvSkip5A_S = j;
				exit_loop = 1;
			}
			j = j + 0.010;

		}

	}
	else
	{
		VcvSkip5A_S = 0;
	}

	FB_ovi3->set_voltage(FB_ch, UpperLimit, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	v_Boost = B_ovi3->measure();

	if(v_Boost > 3)
	{
		VcvSkip5A_H_S_PF = 1;
	}

	//-------------------------------------------------------------------------------------
	//VcvOVP5A test
	//--------------------------------------------------------------------------------
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	FB_ovi3->set_voltage(FB_ch, 0, VOLT_1_RANGE); // DVI_11_0
	wait.delay_10_us(10);
	FB_ovi3->set_voltage(FB_ch, 0, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	j = 1.4;
	while(j<=1.53)
	{
		FB_ovi3->set_voltage(FB_ch, j, VOLT_2_RANGE); // DVI_11_0
		wait.delay_10_us(10);
		j = j + 0.1;
	}

	FB_ovi3->set_voltage(FB_ch, 1.53, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	UpperLimit = (func.dlog->tests[A_VcvOVP5A_S].f_max_limit_val[0]); // Get upper test limit //
	LowerLimit = (func.dlog->tests[A_VcvOVP5A_S].f_min_limit_val[0]); // Get lower test limit /

	FB_ovi3->set_voltage(FB_ch, LowerLimit, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	i_Boost = B_ovi3->measure();

	if(i_Boost < 1e-3)
	{
		VcvOVP5A_L_S_PF = 1;
	}



	if(g_Char_Enable_S)
	{
		j = 1.53;
		exit_loop = 0;
		while(j < 1.60 && exit_loop < 1)
		{
			FB_ovi3->set_voltage(FB_ch, j, VOLT_2_RANGE); // DVI_11_0
			wait.delay_10_us(10);
			i_Boost = B_ovi3->measure();
			if(i_Boost > 1e-3)
			{
				VcvOVP5A_S = j;
				exit_loop = 1;
			}
			j = j + 0.010;

		}

	}
	else
	{
		VcvOVP5A_S = 0;
	}

	FB_ovi3->set_voltage(FB_ch, UpperLimit, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	i_Boost = B_ovi3->measure();

	if(i_Boost > 1e-3)
	{
		VcvOVP5A_H_S_PF = 1;
	}










	//-----------------------------------------------------------------------------------------------------
	//Powerdown sequence.
	//Disable I2C after programming.
	//------------------------------------------------------------------------------------------------------

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_5_RANGE); 
	wait.delay_10_us(10);
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
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
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	wait.delay_10_us(250);

	// Datalog //
	
	PiDatalog(func, A_CV_pst_S,     CV_pst_S,             26, POWER_UNIT);
	PiDatalog(func, A_VcvPFOFF_S,   VcvPFOFF_S,           26, POWER_UNIT);
	PiDatalog(func, A_Vref1p25_S,   Vref1p25V_S,          26, POWER_UNIT);
	PiDatalog(func, A_VcvBoost_S,   VcvBoost_S,           26, POWER_UNIT);
	PiDatalog(func, A_VcvLowFB_L_S_PF,   VcvLowFB_L_S_PF, 26, POWER_UNIT);
	if(g_Char_Enable_S)
	{
		PiDatalog(func, A_VcvLowFB_S,   VcvLowFB_S,           26, POWER_MILLI);
	}
	PiDatalog(func, A_VcvLowFB_H_S_PF,   VcvLowFB_H_S_PF, 26, POWER_UNIT);
	PiDatalog(func, A_VcvSkip5A_L_S_PF,   VcvSkip5A_L_S_PF, 26, POWER_UNIT);
	if(g_Char_Enable_S)
	{
		PiDatalog(func, A_VcvSkip5A_S,   VcvSkip5A_S,           26, POWER_UNIT);
	}	
	PiDatalog(func, A_VcvSkip5A_H_S_PF,   VcvSkip5A_H_S_PF, 26, POWER_UNIT);
	PiDatalog(func, A_VcvOVP5A_L_S_PF,   VcvOVP5A_L_S_PF, 26, POWER_UNIT);
	if(g_Char_Enable_S)
	{
		PiDatalog(func, A_VcvOVP5A_S,   VcvOVP5A_S,           26, POWER_UNIT);
	}	
	PiDatalog(func, A_VcvOVP5A_H_S_PF,   VcvOVP5A_H_S_PF, 26, POWER_UNIT);
	if (g_Trim_Enable_S)
	{
		PiDatalog(func, A_CV_pct_Detla_S, CV_pct_Detla_S,  26, POWER_UNIT);
	}

	PiDatalog(func, A_IFB_Pullup_S,   IFB_Pullup_S, 26, POWER_MICRO);


	//// Test Time End //
	//if (g_TstTime_Enble_P)
	//{
	//	g_endtime = g_mytimer.GetElapsedTime();
	//	CV_Pst_TT = (g_endtime - g_begintime)*1e-6;
	//	PiDatalog(func, A_CV_Pst_TT, CV_Pst_TT, 26, POWER_MILLI);
	//}

}
