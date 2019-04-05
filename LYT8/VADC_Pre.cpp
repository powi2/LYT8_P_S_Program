//==============================================================================
// VADC_Pre.cpp (User function)
// 
//    void VADC_Pre_user_init(test_function& func)
//    void VADC_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "VADC_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VADC_Pre_user_init(test_function& func)
{
	VADC_Pre_params *ours;
    ours = (VADC_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VADC_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    VADC_Pre_params *ours;
    ours = (VADC_Pre_params *)func.params;

			// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VADC_Pre, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_S is not set //
	if (g_Trim_Enable_S == 0 && g_GRR == 0)
		return;

	//if (g_Fn_VADC_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float VADC_pt_S      =0;
	float VADC_prg_S     =0;
	float VADC_Target_S  = 3.5; 
	int VADC_TrCode_S    = 0;
	int VADC_BitCode_S   = 0;
	int EEtr48_ZTMFS0_S  = 0;
	int EEtr49_ZTMFS1_S  = 0;
	int EEtr50_ZTMFS2_S  = 0;
	int EEtr51_ZTMFS3_S  = 0;
	
	float VADC_Sim_S = 0;
	float VADC_Sim_Chg_S = 0;
	float VADC_ExpChg    = 0;
	float VADC_ExpValue  = 0;
	float VADC_PrgChg    = 0;
	float VADC_pst_S     = 0;
	float VADC_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	VADC_S_TrimWt[16]   = {0.0};
	float	VADC_S_code[16]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	int     startbit          = 0;

	
	i = 0;
	VADC_S_code[i] =  0; VADC_S_TrimWt[i] =   0;    i++;     //0 (0 link trimmed)
	VADC_S_code[i] =  1; VADC_S_TrimWt[i] =  -1;    i++;     //0 (1 link trimmed--> -1.0%)
	VADC_S_code[i] =  2; VADC_S_TrimWt[i] =  -2;    i++;     //0 (1 link trimmed--> -2.0%)
	VADC_S_code[i] =  3; VADC_S_TrimWt[i] =  -3;    i++;     //0 (2 link trimmed--> -3.0%)
	VADC_S_code[i] =  4; VADC_S_TrimWt[i] =  -4;    i++;     //0 (1 link trimmed--> -4.0%)
	VADC_S_code[i] =  5; VADC_S_TrimWt[i] =  -5;    i++;     //0 (2 link trimmed--> -5.0%)
	VADC_S_code[i] =  6; VADC_S_TrimWt[i] =  -6;    i++;     //0 (2 link trimmed--> -6.0%)
	VADC_S_code[i] =  7; VADC_S_TrimWt[i] =  -7;    i++;     //0 (3 link trimmed--> -7.0%)
	VADC_S_code[i] =  8; VADC_S_TrimWt[i] =   0.9;    i++;     //0 (1 link trimmed-->  1%)
	VADC_S_code[i] =  9; VADC_S_TrimWt[i] =   1.8;    i++;     //0 (2 link trimmed-->  2%)
	VADC_S_code[i] = 10; VADC_S_TrimWt[i] =   2.7;    i++;     //0 (2 link trimmed-->  3%)
	VADC_S_code[i] = 11; VADC_S_TrimWt[i] =   3.6;    i++;     //0 (3 link trimmed-->  4%)
	VADC_S_code[i] = 12; VADC_S_TrimWt[i] =   4.7;    i++;     //0 (2 link trimmed-->  5%)
	VADC_S_code[i] = 13; VADC_S_TrimWt[i] =   5.52;    i++;     //0 (3 link trimmed-->  6%)
	VADC_S_code[i] = 14; VADC_S_TrimWt[i] =   6.53;    i++;     //0 (3 link trimmed-->  7%)
	VADC_S_code[i] = 15; VADC_S_TrimWt[i] =   7.52;    i++;     //0 (4 link trimmed-->  8%)

	startbit = 48;
	
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

	//ZTMC_ana_EN and Core_en
	//0x00 0x40 write 0x06 0x00
	//DSM_I2C_Write('w', g_S_TM_CTRL, 0x0006);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	if (g_Trim_Enable_S != 0)
	{
		//Loading previous trimming before performing the test.
		Program_All_TrimRegister();
	}

	//ZTMC_ADC_ref
	//0x00 0x44 write 0x20 0x00
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0020);

	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.0e-6, RANGE_3_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 	
	wait.delay_10_us(100);


	VADC_pt_S = FB_ovi3->measure_average(25);

	g_VADC_Pre = VADC_pt_S;

if (g_Trim_Enable_S != 0)
{
	// IRSET_S_Code //
	// Find which trim code will make IRSET_Pre closest to target //
	smallest_diff_val = 999999.9;
	smallest_diff_idx = 0;
	for (i=0; i<16; i++)
	{
		temp_1 = (VADC_pt_S * (1 + (VADC_S_TrimWt[i]/100)) -  VADC_Target_S);
		if (temp_1 < 0)	// Get rid of negatives //
			temp_1 *= -1.0;
		if (temp_1 < smallest_diff_val)
		{
			smallest_diff_val = temp_1;
			smallest_diff_idx = i;
		}
	}


	//Manual forcing:
//	smallest_diff_idx = 15;

	VADC_TrCode_S = VADC_S_code[smallest_diff_idx];
	VADC_ExpChg   = VADC_S_TrimWt[smallest_diff_idx];

	VADC_ExpValue = (VADC_pt_S * (1 + (VADC_S_TrimWt[smallest_diff_idx]/100)));

	TrimCode_To_TrimBit(VADC_TrCode_S, "VADC_S", 's');


	//Convert Trimcode to readable datalog file.
	if(VADC_S_code[smallest_diff_idx]>=0 && VADC_S_code[smallest_diff_idx] <= 7)
	{
		VADC_BitCode_S = -1*VADC_TrCode_S; 
	}
	else
	{
		VADC_BitCode_S = VADC_TrCode_S - 7;
	}

	EEpr_Array[3] = EEpr_Array[3] | (VADC_TrCode_S<<(48-startbit));

	Program_Single_TrimRegister(g_EEP_W_E6);


}
	wait.delay_10_us(100);

	VADC_prg_S = FB_ovi3->measure_average(25);

	if(VADC_pt_S != 0)
	{
		VADC_PrgChg = 100*(VADC_prg_S - VADC_pt_S) / VADC_pt_S;
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


	PiDatalog(func, A_VADC_pt_S,		  VADC_pt_S,               26, POWER_UNIT);
	
	if (g_Trim_Enable_S)
	{
		PiDatalog(func, A_VADC_target_S,      VADC_Target_S,           26, POWER_UNIT);
		PiDatalog(func, A_VADC_TrCode_S,      VADC_TrCode_S,           26, POWER_UNIT);
		PiDatalog(func, A_VADC_BitCode_S,     VADC_BitCode_S,           26, POWER_UNIT);
		PiDatalog(func, A_VADC_ExpChg_S,      VADC_ExpChg,             26, POWER_UNIT);
		PiDatalog(func, A_VADC_Exp_Value,     VADC_ExpValue,           26, POWER_UNIT);
		PiDatalog(func, A_Eetr48_ZTMFS0_S,    g_S_TrimRegisterTemp[48],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr49_ZTMFS1_S,    g_S_TrimRegisterTemp[49],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr50_ZTMFS2_S,    g_S_TrimRegisterTemp[50],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr51_ZTMFS3_S,    g_S_TrimRegisterTemp[51],    26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,         EEpr_Array[3],          26, POWER_UNIT);
		PiDatalog(func, A_VADC_prg_S,         VADC_prg_S,              26, POWER_UNIT);
		PiDatalog(func, A_VADC_prgchg_S,      VADC_PrgChg,             26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_VADC_Pst,         VADC_prg_S,              26, POWER_UNIT);

	}

}
