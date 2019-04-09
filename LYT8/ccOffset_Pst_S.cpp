//==============================================================================
// ccOffset_Pst_S.cpp (User function)
// 
//    void ccOffset_Pst_S_user_init(test_function& func)
//    void ccOffset_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "ccOffset_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ccOffset_Pst_S_user_init(test_function& func)
{
	ccOffset_Pst_S_params *ours;
    ours = (ccOffset_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ccOffset_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    ccOffset_Pst_S_params *ours;
    ours = (ccOffset_Pst_S_params *)func.params;

				// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CCOffset_Pst, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	

	// Test Names //
	float CCOffset_Pst_S   = 0;
	float CCOffset_Detla_S = 0;
	float CCOffset_Test_S  = 0; 
	float   temp_1            = 0;
	float CCOffset_Pst_TT    = 0;

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
	//HSG: disconnect OVI and connect to 2nF to GND
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = Hiz.
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	//IS = 100mV/200mA
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);				
	IS_dvi2k->set_current(IS_ch, 20e-3, RANGE_20_MA);
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

	Close_relay(K2_HSG_SPI_TB);      //Disconect OVI_1_0 from HSG.
	Close_relay(K2_B_SPI_TB);        //Disconnect OVI_3_1 from B.
	Close_relay(K3_B_SPI_TB);		//Connect 2nF to B
	Close_relay(K3_HSG_SPI_TB);     //Connect 2nF to HSG
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

	//FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	//FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	//wait.delay_10_us(10);
	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	HBP_dvi2k->set_voltage(HBP_ch, g_HBP_Pre_S, VOLT_20_RANGE);
	wait.delay_10_us(500);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

	//IS = 100mV/20mA
	IS_dvi2k->set_current(IS_ch, 20e-3, RANGE_20_MA);
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

	//ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 0x62 write 0x80 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0080);

	//ZTMC_trimOffset, ZTMC_Frc_gain & ZTMC_AVIN
	//0x00 0x46 write 0xE0 0x00
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x00E0);

	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.1e-9, RANGE_3_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 	
	wait.delay_10_us(100);

	CCOffset_Pst_S = FB_ovi3->measure_average(25);
	
	if(g_Burn_Enable_S && g_CCOffset_Pre != 0)
	{
		CCOffset_Detla_S = 100*(CCOffset_Pst_S - g_CCOffset_Pre) / g_CCOffset_Pre;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-6, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-6, RANGE_30_MA);				
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
	Open_relay(K2_B_SPI_TB);         //Reconnect OVI_3_1 to B.
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	wait.delay_10_us(250);


	PiDatalog(func, A_CCOffset_Pst_S,		  CCOffset_Pst_S,               26, POWER_UNIT);
	if (g_Burn_Enable_S != 0)
	{
		PiDatalog(func, A_CCOffset_Delta_S,      CCOffset_Detla_S,           26, POWER_UNIT);
	}
	

}
