//==============================================================================
// IRSET_Pre.cpp (User function)
// 
//    void IRSET_Pre_user_init(test_function& func)
//    void IRSET_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "IRSET_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IRSET_Pre_user_init(test_function& func)
{
	IRSET_Pre_params *ours;
    ours = (IRSET_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IRSET_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    IRSET_Pre_params *ours;
    ours = (IRSET_Pre_params *)func.params;

		// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IRSET_Pre, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	//if (g_Sim_Enable_P == 0)
//		return;

	//if (g_Fn_IRSET_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	//int fNum_CV_Pre = 0;
	float IRSET_pt_S     =0;
	float IRSET_prg_S    =0;
	float IRSET_Target_S = 160e-6; 
	int IRSET_TrCode_S   = 0;
	int IRSET_BitCode_S  = 0;
	int EEtr76_ZTLnt0_S  = 0;
	int EEtr77_ZTLnt1_S  = 0;
	int EEtr78_ZTLnt2_S  = 0;
	int EEtr79_ZTLnt3_S  = 0;
	
	float IRSET_Sim_S = 0;
	float IRSET_Sim_Chg_S = 0;
	float IRSET_ExpChg   = 0;
	float IRSET_PrgChg   = 0;
	float IRSET_pst_S =0;
	float IRSET_Pre_TT =0;

Pulse pulse;

	//Trimcode & bit weights.
	float	IRSET_S_TrimWt[16]   = {0.0};
	float	IRSET_S_code[16]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;

	i = 0;
	IRSET_S_code[i] =  0; IRSET_S_TrimWt[i] =    0;    i++;     //0 (0 link trimmed)
	IRSET_S_code[i] =  1; IRSET_S_TrimWt[i] = -2.2;    i++;     //0 (1 link trimmed--> -2.2%)
	IRSET_S_code[i] =  2; IRSET_S_TrimWt[i] = -4.4;    i++;     //0 (1 link trimmed--> -4.4%)
	IRSET_S_code[i] =  3; IRSET_S_TrimWt[i] = -6.6;    i++;     //0 (2 link trimmed--> -6.6%)
	IRSET_S_code[i] =  4; IRSET_S_TrimWt[i] = -8.8;    i++;     //0 (1 link trimmed--> -8.8%)
	IRSET_S_code[i] =  5; IRSET_S_TrimWt[i] = -11;     i++;     //0 (2 link trimmed--> -11%)
	IRSET_S_code[i] =  6; IRSET_S_TrimWt[i] = -13.2;   i++;     //0 (2 link trimmed--> -2.5%)
	IRSET_S_code[i] =  7; IRSET_S_TrimWt[i] = -15.4;   i++;     //0 (3 link trimmed--> -15.4%)
	IRSET_S_code[i] =  8; IRSET_S_TrimWt[i] =  18;     i++;     //0 (1 link trimmed-->  18%)
	IRSET_S_code[i] =  9; IRSET_S_TrimWt[i] =  15.3;   i++;     //0 (2 link trimmed-->  15.3%)
	IRSET_S_code[i] = 10; IRSET_S_TrimWt[i] =  12.96;  i++;     //0 (2 link trimmed-->  12.96%)
	IRSET_S_code[i] = 11; IRSET_S_TrimWt[i] =  10.6;   i++;     //0 (3 link trimmed-->  10.6%)
	IRSET_S_code[i] = 12; IRSET_S_TrimWt[i] =  8.3;    i++;     //0 (2 link trimmed-->  8.3%)
	IRSET_S_code[i] = 13; IRSET_S_TrimWt[i] =  6.1;    i++;     //0 (3 link trimmed-->  6.1%)
	IRSET_S_code[i] = 14; IRSET_S_TrimWt[i] =  4.0;    i++;     //0 (3 link trimmed-->  4.0%)
	IRSET_S_code[i] = 15; IRSET_S_TrimWt[i] =  2.02;   i++;     //0 (4 link trimmed-->  2.02%)

	
	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //
	// E2 Trim register.
	WordArray[0]  = g_S_TrimRegister[64];
	WordArray[1]  = g_S_TrimRegister[65];
	WordArray[2]  = g_S_TrimRegister[66];
	WordArray[3]  = g_S_TrimRegister[67];
	WordArray[4]  = g_S_TrimRegister[68];
	WordArray[5]  = g_S_TrimRegister[69];
	WordArray[6]  = g_S_TrimRegister[70]; 
	WordArray[7]  = g_S_TrimRegister[71]; 
	WordArray[8]  = g_S_TrimRegister[72]; 
	WordArray[9]  = g_S_TrimRegister[73]; 
	WordArray[10] = g_S_TrimRegister[74];
	WordArray[11] = g_S_TrimRegister[75];
	WordArray[12] = g_S_TrimRegister[76];//EEtr76_ZTLnt0_S
	WordArray[13] = g_S_TrimRegister[77];//EEtr77_ZTLnt1_S
	WordArray[14] = g_S_TrimRegister[78];//EEtr78_ZTLnt2_S
	WordArray[15] = g_S_TrimRegister[79];//EEtr79_ZTLnt3_S

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
	//For TEST only..  Manually raise vFB above 2.5V or 3V here to observe HBP will go low and then lower to 1.25V for HSG to go High
	//Below to to make sure the FB controlling HBP is working properly before Disabling it.
	if(0)
	{
		FB_ovi3->set_voltage(FB_ch, 2.00, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.25, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.50, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.75, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 3.00, VOLT_5_RANGE); // DVI_11_0	//1uF on HBP.  The drop is slow if it's only 3ms.  Manual observe drop to ~1.7V
		delay(3);              
		FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
		delay(1);
	}

//pulse.do_pulse();

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//											  (This Test Mode disable 
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);


	//Loading previous trimming before performing the test.

	//Program Trim Register with new calculated bit combination.
	Program_Trim_Register(g_S_TrimRegister);


	//ZTMC_IRset_Trim
	//0x00 0x60 write 0x00 0x04
	DSM_I2C_Write('w', g_TEST_CTRL1, 0x0004);

	wait.delay_10_us(100);

	IRSET_pt_S = -1*(IS_dvi2k->measure_average(25));


	// IRSET_S_Code //
	// Find which trim code will make IRSET_Pre closest to target //
	smallest_diff_val = 999999.9;
	smallest_diff_idx = 0;
	for (i=0; i<16; i++)
	{
		temp_1 = (IRSET_pt_S * (1 + (IRSET_S_TrimWt[i]/100)) -  IRSET_Target_S);
		if (temp_1 < 0)	// Get rid of negatives //
			temp_1 *= -1.0;
		if (temp_1 < smallest_diff_val)
		{
			smallest_diff_val = temp_1;
			smallest_diff_idx = i;
		}
	}


	//Manual forcing:
	//smallest_diff_idx = 14;

	IRSET_TrCode_S = smallest_diff_idx;
	IRSET_TrCode_S = IRSET_S_code[smallest_diff_idx];
	IRSET_ExpChg   = IRSET_S_TrimWt[smallest_diff_idx];

	TrimCode_To_TrimBit(IRSET_TrCode_S, "IRSET_S", 's');

	if(IRSET_TrCode_S >=0 && IRSET_TrCode_S <= 7)
	{
		IRSET_BitCode_S = -1*IRSET_TrCode_S; 
	}
	else if(IRSET_TrCode_S == 15) IRSET_BitCode_S = 1;
	else if(IRSET_TrCode_S == 14) IRSET_BitCode_S = 2;
	else if(IRSET_TrCode_S == 13) IRSET_BitCode_S = 3;
	else if(IRSET_TrCode_S == 12) IRSET_BitCode_S = 4;
	else if(IRSET_TrCode_S == 11) IRSET_BitCode_S = 5;
	else if(IRSET_TrCode_S == 10) IRSET_BitCode_S = 6;
	else if(IRSET_TrCode_S == 9)  IRSET_BitCode_S = 7;
	else if(IRSET_TrCode_S == 8)  IRSET_BitCode_S = 8;

	//Update WordArray.
	WordArray[12]        = g_S_TrimRegisterTemp[76]; //EEtr76_ZTLnt0_S
	WordArray[13]        = g_S_TrimRegisterTemp[77]; //EEtr77_ZTLnt1_S
	WordArray[14]        = g_S_TrimRegisterTemp[78]; //EEtr78_ZTLnt2_S
	WordArray[15]        = g_S_TrimRegisterTemp[79]; //EEtr79_ZTLnt3_S

	//Update secondary trim register array for programming later.
	g_S_TrimRegister[76] = g_S_TrimRegisterTemp[76]; //EEtr76_ZTLnt0_S
	g_S_TrimRegister[77] = g_S_TrimRegisterTemp[77]; //EEtr77_ZTLnt1_S
	g_S_TrimRegister[78] = g_S_TrimRegisterTemp[78]; //EEtr78_ZTLnt2_S
	g_S_TrimRegister[79] = g_S_TrimRegisterTemp[79]; //EEtr79_ZTLnt3_S

	//Convert from binary to decimal.
	converted_dec1 = Convert_BIN_2_Dec(WordArray);
	converted_dec2 = Convert_BIN_2_Dec(WordArray);


	//Program Trim Register with new calculated bit combination.
	Program_Trim_Register(g_S_TrimRegister);

	int TrimBank[5];

	Read_Trim_Register(TrimBank);


	wait.delay_10_us(100);

	IRSET_prg_S = -1*(IS_dvi2k->measure_average(25));

	if(IRSET_pt_S != 0)
	{
		IRSET_PrgChg = 100*(IRSET_prg_S - IRSET_pt_S) / IRSET_pt_S;
	}
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


	PiDatalog(func, A_IRSET_pt_S, IRSET_pt_S,              26, POWER_MICRO);
	PiDatalog(func, A_IRSET_target_S,     IRSET_Target_S,          26, POWER_MICRO);
	PiDatalog(func, A_IRSET_TrCode_S,     IRSET_TrCode_S,          26, POWER_UNIT);
	PiDatalog(func, A_IRSET_BitCode_S,  IRSET_BitCode_S,         26, POWER_UNIT);
	PiDatalog(func, A_IRSET_ExpChg_S,     IRSET_ExpChg,            26, POWER_UNIT);
	PiDatalog(func, A_Eetr76_ZTLnt0_S,    g_S_TrimRegister[76],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr77_ZTLnt1_S,    g_S_TrimRegister[77],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr78_ZTLnt2_S,    g_S_TrimRegister[78],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr79_ZTLnt3_S,    g_S_TrimRegister[79],    26, POWER_UNIT);
	PiDatalog(func, A_Bin2Dec1_S,         converted_dec1,          26, POWER_UNIT);
	PiDatalog(func, A_IRSET_prg_S,        IRSET_prg_S,             26, POWER_MICRO);
	PiDatalog(func, A_IRSET_prgchg_S,     IRSET_PrgChg,            26, POWER_UNIT);




}
