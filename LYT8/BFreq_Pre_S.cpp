//==============================================================================
// BFreq_Pre_S.cpp (User function)
// 
//    void BFreq_Pre_S_user_init(test_function& func)
//    void BFreq_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BFreq_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BFreq_Pre_S_user_init(test_function& func)
{
	BFreq_Pre_S_params *ours;
    ours = (BFreq_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BFreq_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    BFreq_Pre_S_params *ours;
    ours = (BFreq_Pre_S_params *)func.params;


		gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BFreq_Pre_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Burn_Enable_P == 0)
//		return;

	// Skip trimming if g_Burn_Enable_S is not set //
	if (g_Burn_Enable_S == 0 && g_GRR_Enable == 0)
		return;

	//if (g_Fn_BFreq_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	int   WordArray_E0[16] = {0};
	int   WordArray_E2[16] = {0};
	int	  BIN_2_Dec_Num = 0;
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float BFreq_pt_S      =0;
	float BFreq_prg_S     =0;
	float BFreq_Target_S  = g_BFreq_Target_S_Trimops;//225E3; 
	int   BFreq_TrCode_S  = 0;
	int   BFreq_BitCode_S = 0;
	int   EEtr12_tfb0_S   = 0;
	int   EEtr13_tfb1_S   = 0;
	int   EEtr14_tfb2_S   = 0;
	
	
	float BFreq_Sim_S = 0;
	float BFreq_Sim_Chg_S = 0;
	float BFreq_ExpChg    = 0;
	float BFreq_ExpValue  = 0;
	float BFreq_PrgChg    = 0;
	float BFreq_pst_S     = 0;
	float BFreq_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	BFreq_S_TrimWt[8]   = {0.0};
	float	BFreq_S_code[8]     = {0.0};
	float   meas_value[100]     = {0.0};
	int     TrimRegister[80]    = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	float   tmeas             = 0;
	int     startbit          = 0;
	int     num_loop          = 0;
	
	i = 0;
	BFreq_S_code[i] =  0; BFreq_S_TrimWt[i] =  0;       i++;     //0 (0 link trimmed)
	BFreq_S_code[i] =  1; BFreq_S_TrimWt[i] =  -3.0;    i++;     //0 (1 link trimmed--> 0.0%)
	BFreq_S_code[i] =  2; BFreq_S_TrimWt[i] =  -6.0;    i++;     //0 (1 link trimmed--> 8.0%)
	BFreq_S_code[i] =  3; BFreq_S_TrimWt[i] =  -9.0;    i++;     //0 (2 link trimmed--> 12.0%)
	BFreq_S_code[i] =  4; BFreq_S_TrimWt[i] =  +12.0;   i++;     //0 (1 link trimmed--> 16.0%)
	BFreq_S_code[i] =  5; BFreq_S_TrimWt[i] =  +11.22;  i++;     //0 (2 link trimmed--> 20.0%)
	BFreq_S_code[i] =  6; BFreq_S_TrimWt[i] =  +14.62;  i++;     //0 (2 link trimmed--> 24.0%)
	BFreq_S_code[i] =  7; BFreq_S_TrimWt[i] =  +18.0;   i++;     //0 (3 link trimmed--> 28.0%)

	startbit = 0;
	
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
	//FB = CV-5%
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
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
	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Setup TMU on Buffer of B pin.
	tmu_6->close_relay(TMU_HIZ_DUT2); 
	tmu_6->start_trigger_setup(3.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(3.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);


	Close_relay(K7_IS_SPI_TB);       //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		 //Disconnect DVI_13_1 from IS.
	Close_relay(K2_HSG_SPI_TB);      //Disconnect OVI_1_0 from HSG.
	Close_relay(K3_HSG_SPI_TB);      //Connect 2nF to HSG
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF from B
	Close_relay(K2_B_SPI_TB);        //Keep OVI_3_1 connecting to B.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Close_relay(K5_B_SPI_TB);        //Connect B to Buffer.

	
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
	FB_ovi3->set_voltage(FB_ch, 1, VOLT_5_RANGE);
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

	//0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_D//Enter TM
	Analog_TM_Enable_Secondary();

	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.

	//ZTMC_Driver_en & ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 control_S & ZTMC_Dsbl_AR
	//0x00 0x44 write 0x80 0x10
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x1080);

	// ZTMC_Dsbl_CConB (disable ccBoostOff) & HSG Open Drain to reduce noise & ZTMC_TX
     //0x00 0x60 write 0x20 0x00
	DSM_I2C_Write('w', 0x60, 0xA020);
	

	//Program T[10] & T[11] to select boost freq option.
	//It's done in the First function for the scoop and goop parts.


	if(g_Trim_DsblFlBck_B31_S_Trimops == 0) //If Disable Foldback is not set, then set T[31] = 1 to disable foldback.
	{                          //Need to enable foldback at the end of the test program.
		//Set T[31]=1 to disable foldback .
		Set_EEprBit(EEpr_Bank_S[E2], 15, 1);
	}
	if (g_Burn_Enable_S)
	{
		Program_All_TrimRegister();
	}

	////Dali State to 254
	DSM_I2C_Write('b', 0x10, 0xFF);
	

	num_loop = 20;
	BFreq_pt_S = BFreq_Meas(num_loop);

	g_BFreq_Pre  = BFreq_pt_S;

	//Need to turn off switching on Boost pin.
	FB_ovi3->set_voltage(FB_ch, 2, VOLT_5_RANGE); // DVI_11_0

	if (g_Burn_Enable_S)
	{
		// BFreq_S_Code //
		// Find which trim code will make BFreq_Pre closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<8; i++)
		{
			temp_1 = (BFreq_pt_S * (1 + (BFreq_S_TrimWt[i]/100)) -  BFreq_Target_S);
			if (temp_1 < 0)	// Get rid of negatives //
				temp_1 *= -1.0;
			if (temp_1 < smallest_diff_val)
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}


		//Manual forcing:
		//smallest_diff_idx = 0;

		BFreq_TrCode_S = BFreq_S_code[smallest_diff_idx];
		BFreq_ExpChg   = BFreq_S_TrimWt[smallest_diff_idx];

		BFreq_ExpValue = (BFreq_pt_S * (1 + (BFreq_S_TrimWt[smallest_diff_idx]/100)));

		TrimCode_To_TrimBit(BFreq_TrCode_S, "Bfreq_S", 's');


	////////	//Convert Trimcode to readable datalog file.
	////////	///*if(CLK1M_S_code[smallest_diff_idx]>=0 && CLK1M_S_code[smallest_diff_idx] <= 7)
	////////	//{
	////////	//	CLK1M_BitCode_S = -1*VADC_TrCode_S; 
	////////	//}
	////////	//else
	////////	//{
	////////	//	VADC_BitCode_S = VADC_TrCode_S - 7;
	////////	//}*/
	////////

		EEpr_Bank_S[E0] = EEpr_Bank_S[E0] | (BFreq_TrCode_S<<(12-startbit));

		Program_Single_TrimRegister(g_EEP_W_E0);


	}

//////	int TrimBank[5];
//////
//////	Read_Trim_Register(TrimBank);
//////DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	
	//Enable switching on Boost pin again.
	FB_ovi3->set_voltage(FB_ch, 1, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(10);
	
	num_loop = 20;
	BFreq_prg_S = BFreq_Meas(num_loop);


	if(BFreq_pt_S != 0)
	{
		BFreq_PrgChg = 100*(BFreq_prg_S - BFreq_pt_S) / BFreq_pt_S;
	}

	if(g_Trim_DsblFlBck_B31_S_Trimops == 0)
	{
		//ReSet T[31]=0 to enable foldback .
		Set_EEprBit(EEpr_Bank_S[E2], 15, 0);
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 

	B_ovi3->set_current(B_ch1, 300e-6, RANGE_30_MA);
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
	Open_relay(K7_IS_SPI_TB);        //Disconnect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		 //Reconnect DVI_13_1 to IS.
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
	Open_relay(K5_B_SPI_TB);       //Disconnect B from Buffer.
	tmu_6->open_relay(TMU_HIZ_DUT2); 
	wait.delay_10_us(250);


	PiDatalog(func, A_BFreq_pt_S,		  BFreq_pt_S,               26, POWER_KILO);
	
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_BFreq_target_S,     BFreq_Target_S,           26, POWER_KILO);
		PiDatalog(func, A_BFreq_TrCode_S,     BFreq_TrCode_S,           26, POWER_UNIT);
		PiDatalog(func, A_BFreq_BitCode_S,    BFreq_BitCode_S,          26, POWER_UNIT);
		PiDatalog(func, A_BFreq_ExpChg_S,     BFreq_ExpChg,             26, POWER_UNIT);
		PiDatalog(func, A_BFreq_Exp_Value,    BFreq_ExpValue,           26, POWER_KILO);
		PiDatalog(func, A_Eetr12_tfb0_S,      g_S_TrimRegisterTemp[12],     26, POWER_UNIT);
		PiDatalog(func, A_Eetr13_tfb1_S,      g_S_TrimRegisterTemp[13],     26, POWER_UNIT);
		PiDatalog(func, A_Eetr14_tfb2_S,      g_S_TrimRegisterTemp[14],     26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,         EEpr_Bank_S[E0],           26, POWER_UNIT);
		PiDatalog(func, A_BFreq_prg_S,         BFreq_prg_S,             26, POWER_KILO);
		PiDatalog(func, A_BFreq_prgchg_S,      BFreq_PrgChg,            26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_BFreq_Pst,         BFreq_prg_S,             26, POWER_KILO);

	}

}
	
