//==============================================================================
// VDDA_Pst_S.cpp (User function)
// 
//    void VDDA_Pst_S_user_init(test_function& func)
//    void VDDA_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "VDDA_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VDDA_Pst_S_user_init(test_function& func)
{
	VDDA_Pst_S_params *ours;
    ours = (VDDA_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VDDA_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VDDA_Pst_S_params *ours;
    ours = (VDDA_Pst_S_params *)func.params;

		// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VDDA_Post, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Burn_Enable_P == 0)
//		return;

	///*if (g_Burn_Enable_S == 0)
	//	return;*/

	//if (g_Fn_CV_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;


	// Test Names //
	
	float VDDA_pst_S       = 0;
	float VDDA_Pct_Delta_S = 0;
	float VDDA_7V_S        = 0;
	float VDDA_8V_S        = 0; 
	float VBPS_S           = 0;
	float IBPS_LReg_S      = 0;
	float VBPS_ILoad_S     = 0;
	float VDDA_Post_TT =0;

Pulse pulse;

	float   temp_1            = 0;

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
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);//Keep 200mA range here or IS will drop below ground.
	//SDA will be at 3.3V/30mA for I2C
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	//SCL will be at 3.3V/30mA for I2C
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	//BPS 
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
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
	HBP_dvi2k->open_relay(CONN_FORCE0);
	
	Close_relay(K2_HSG_SPI_TB);      //Disconnect OVI_1_0 from HSG.
	Close_relay(K3_HSG_SPI_TB);      //Connect 2nF to HSG
	Close_relay(K2_B_SPI_TB);        //Disconnect OVI_3_1 from B.
	Close_relay(K3_B_SPI_TB);		 //Connect 2nF to B

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

	//////////IS leakage can be measured here??
	//IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, 2e-3, RANGE_200_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(100);

	//LDO Regulation Voltage
	BPS_dvi->set_voltage(BPS_ch, 2.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 1.0e-3, RANGE_300_MA);
	wait.delay_10_us(500);
	VBPS_S = BPS_dvi->measure_average(25);

	//VBPS @ 50mA
	BPS_dvi->set_voltage(BPS_ch, 2.5, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 50.0e-3, RANGE_300_MA);
	wait.delay_10_us(1500);

//
	VBPS_ILoad_S = BPS_dvi->measure_average(25);



	//BPS Current @ VBPS - 100mV
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	BPS_dvi->set_voltage(BPS_ch, VBPS_S-0.1, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 100.0e-3, RANGE_300_MA);
	wait.delay_10_us(500);
	IBPS_LReg_S = BPS_dvi->measure_average(25);

	//Reset BPS voltage & current
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0, RANGE_300_MA);
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
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	// ZTMC_VDDA_en
	//0x00 0x44 write 0x08 0x00 
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0008);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//---------------------------------------------------------------------------------
	//VDDA Post trim.
	//-------------------------------------------------------------------------------------
	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.0e-6, RANGE_3_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(500);
	
	VDDA_pst_S = FB_ovi3->measure_average(25);

	if (g_Burn_Enable_S && g_VDDA_Pre != 0.0)
	{
		VDDA_Pct_Delta_S =  100*(VDDA_pst_S - g_VDDA_Pre) / g_VDDA_Pre;		
	}


	//-----------------------------------------------------------------------------------------
	//VDDA @ 7V
	//------------------------------------------------------------------------------------------
	// ZTMC_trim_EW_VDDA
	//0x00 0x44 write 0x04 0x00 
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0004);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Take time for VDDA to rise up to 7V
	wait.delay_10_us(500);
	VDDA_7V_S = FB_ovi3->measure_average(25);

	//----------------------------------------------------------------------------------------------------
	//VDDA @ 8V
	//----------------------------------------------------------------------------------------------------
	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//ZTMC_MV_Stress											  
	//0x00 0x62 write 0xC8 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x00C8);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Take time for VDDA to rise up to 8V
	wait.delay_10_us(500);
	VDDA_8V_S = FB_ovi3->measure_average(25);


	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
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
	Open_relay(K2_HSG_SPI_TB);      //Reconnect OVI_1_0 to HSG.
	Open_relay(K3_HSG_SPI_TB);      //Disconnect 2nF from HSG
	Open_relay(K2_B_SPI_TB);        //Reconnect OVI_3_1 from B.
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
	wait.delay_10_us(250);

// Datalog //
	PiDatalog(func, A_VDDA_Post_S, VDDA_pst_S,         26, POWER_UNIT);
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_VDDA_Pct_Del_S,   VDDA_Pct_Delta_S,          26, POWER_UNIT);
	}

	PiDatalog(func, A_VDDA_7V_S,   VDDA_7V_S,          26, POWER_UNIT);
	PiDatalog(func, A_VDDA_8V_S,   VDDA_8V_S,          26, POWER_UNIT);


	PiDatalog(func, A_VBPS_S,      VBPS_S,              26, POWER_UNIT);
	PiDatalog(func, A_IBPS_LReg,   IBPS_LReg_S,         26, POWER_MILLI);
	PiDatalog(func, A_VBPS_ILoad,  VBPS_ILoad_S,        26, POWER_UNIT);





}
