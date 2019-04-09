//==============================================================================
// IRSET_Pst_S.cpp (User function)
// 
//    void IRSET_Pst_S_user_init(test_function& func)
//    void IRSET_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IRSET_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IRSET_Pst_S_user_init(test_function& func)
{
	IRSET_Pst_S_params *ours;
    ours = (IRSET_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IRSET_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    IRSET_Pst_S_params *ours;
    ours = (IRSET_Pst_S_params *)func.params;

	
		// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IRSET_Pst, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Burn_Enable_P == 0)
//		return;
////if (g_Burn_Enable_S == 0)
////		return;
	//if (g_Fn_IRSET_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;

	// Test Names //
	//int fNum_CV_Pre = 0;
	float IRSET_Pst_S        = 0;
	float IRSET_Pct_Delta_S  = 0;
	float v_Boost1           = 0;
	float v_Boost2           = 0;
	float v_Boost3           = 0;
	int I2C_RSET_Chk_S      = 0;
	int I2C_RSET_Chk_S_H      = 0;
	int I2C_RSET_Chk_S_L      = 0;
	
	
	
	float IRSET_Pst_S_TT =0;

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

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG.
	Close_relay(K1_HSG_SPI_RB);     //Connect pullup R on HSG.
	Open_relay(K3_B_SPI_TB);		//Connect 2nF to B
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

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
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

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//											  (This Test Mode disable 
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x05 0x00 ==> B driver is enable, but not HSG.
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);

	//ZTMC_IRset_Trim
	//0x00 0x60 write 0x00 0x04
	DSM_I2C_Write('w', g_TEST_CTRL1, 0x0400);

	wait.delay_10_us(100);

	IRSET_Pst_S = -1*(IS_dvi2k->measure_average(25));

	if (g_Burn_Enable_S && g_IRSET_Pre != 0.0)
	{
		IRSET_Pct_Delta_S = 100*(IRSET_Pst_S - g_IRSET_Pre) / g_IRSET_Pre;
	}

	//-------------------------------------------------------------------------------
	//I2C Check.
	//--------------------------------------------------------------------------------

	//ZTMC_Frc_I2Cchk.
	//0x00 0x60 write 0x00 0x02
	DSM_I2C_Write('w', g_TEST_CTRL1, 0x0200);

	//ZI2C
	//0x00 0x42 write 0x05 0x00
	DSM_I2C_Write('w', 0x42, 0x0005);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300); //Need to disable DSM before disconnect DSM from SDA pin.

	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_VOLTAGE);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE);
	SDA_ovi3->set_current(SDA_ch, 0.0e-3, RANGE_30_MA);
	wait.delay_10_us(100);

	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	wait.delay_10_us(250);

	v_Boost1 = B_ovi3->measure();

	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE);
	SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
	wait.delay_10_us(100);

	v_Boost2 = B_ovi3->measure();

	if(v_Boost1 < 2 && v_Boost2 > 2)
	{
		I2C_RSET_Chk_S_H = 1;
	}

	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE);
	SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
	wait.delay_10_us(100);

	v_Boost3 = B_ovi3->measure();

	if(v_Boost3 < 2)
	{
		I2C_RSET_Chk_S_L = 1;
	}

	if(I2C_RSET_Chk_S_H == 1 && I2C_RSET_Chk_S_L == 1)
	{
		I2C_RSET_Chk_S = 1;
	}
//////	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

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
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	wait.delay_10_us(250);


	PiDatalog(func, A_IRSET_Pst_S,		 IRSET_Pst_S,              26, POWER_MICRO);
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_IRSET_Pct_Delta_S, IRSET_Pct_Delta_S,        26, POWER_UNIT);
	}
	PiDatalog(func, A_I2C_RSET_Chk_S,		 I2C_RSET_Chk_S,              26, POWER_UNIT);
	

}
