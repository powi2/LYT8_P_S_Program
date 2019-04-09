//==============================================================================
// VccRef_Pre_S.cpp (User function)
// 
//    void VccRef_Pre_S_user_init(test_function& func)
//    void VccRef_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "VccRef_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VccRef_Pre_S_user_init(test_function& func)
{
	VccRef_Pre_S_params *ours;
    ours = (VccRef_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VccRef_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VccRef_Pre_S_params *ours;
    ours = (VccRef_Pre_S_params *)func.params;

					// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VccRef_Pre, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_S is not set //
	if (g_Burn_Enable_S == 0 && g_GRR_Enable == 0)
		return;

	//if (g_Fn_VccRef_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float VccRef_pt_S     =0;
	float VccRef_prg_S    = 0;
	float VccRef_Target_S = g_VccRef_Target_S_Trimops;
	if(g_Device_ID_S == 6160||g_Device_ID_S == 6159||g_Device_ID_S==6155)
	{
		VccRef_Target_S = 335e-3; //Taken care by Trimops.
	}
	else
	{
		VccRef_Target_S = 200e-3; //Taken care by Trimops.
	}
	
	int VccRef_TrCode_S   = 0;
	int VccRef_BitCode_S  = 0;
	int Eetr52_DacTr0_S   = 0;
	int Eetr53_DacTr1_S   = 0;
	int Eetr54_DacTr2_S   = 0;
	int Eetr55_DacTr3_S   = 0;
	int Eetr56_DacTr4_S   = 0;
	
	
	float VccRef_Sim_S     = 0;
	float VccRef_Sim_Chg_S = 0;
	float VccRef_ExpChg    = 0;
	float VccRef_ExpValue  = 0;
	float VccRef_PrgChg    = 0;
	float VccRef_pst_S     = 0;
	float VccRef_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	VccRef_S_TrimWt[32]   = {0.0};
	float	VccRef_S_code[32]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	int     startbit          = 0;

	
	i = 0;
	VccRef_S_code[i] =  0; VccRef_S_TrimWt[i] =   0;     i++;     
	VccRef_S_code[i] =  1; VccRef_S_TrimWt[i]  =  0.75;  i++;     
	VccRef_S_code[i] =  2; VccRef_S_TrimWt[i]  =  1.50;  i++;    
	VccRef_S_code[i] =  3; VccRef_S_TrimWt[i]  =  2.25;  i++;    
	VccRef_S_code[i] =  4; VccRef_S_TrimWt[i]  =  3.00;  i++;     
	VccRef_S_code[i] =  5; VccRef_S_TrimWt[i]  =  3.75;  i++;     
	VccRef_S_code[i] =  6; VccRef_S_TrimWt[i]  =  4.50;  i++;     
	VccRef_S_code[i] =  7; VccRef_S_TrimWt[i]  =  5.25;  i++;     
	VccRef_S_code[i] =  8; VccRef_S_TrimWt[i] =   6.00;  i++;     
	VccRef_S_code[i] =  9; VccRef_S_TrimWt[i] =   6.75;  i++;     
	VccRef_S_code[i] = 10; VccRef_S_TrimWt[i] =   7.50;  i++;     
	VccRef_S_code[i] = 11; VccRef_S_TrimWt[i] =   8.25;  i++;     
	VccRef_S_code[i] = 12; VccRef_S_TrimWt[i] =   9.00;  i++;    
	VccRef_S_code[i] = 13; VccRef_S_TrimWt[i] =   9.75;  i++;     
	VccRef_S_code[i] = 14; VccRef_S_TrimWt[i] =  10.50;  i++;     
	VccRef_S_code[i] = 15; VccRef_S_TrimWt[i] =  11.25;  i++;    
	VccRef_S_code[i] = 16; VccRef_S_TrimWt[i] =   0.10;  i++;     
	VccRef_S_code[i] = 17; VccRef_S_TrimWt[i]  = -0.75;  i++;     
	VccRef_S_code[i] = 18; VccRef_S_TrimWt[i]  = -1.50;  i++;    
	VccRef_S_code[i] = 19; VccRef_S_TrimWt[i]  = -2.50;  i++;    
	VccRef_S_code[i] = 20; VccRef_S_TrimWt[i]  = -3.50;  i++;     
	VccRef_S_code[i] = 21; VccRef_S_TrimWt[i]  = -4.10;  i++;     
	VccRef_S_code[i] = 22; VccRef_S_TrimWt[i]  = -5.00;  i++;     
	VccRef_S_code[i] = 23; VccRef_S_TrimWt[i]  = -5.80;  i++;     
	VccRef_S_code[i] = 24; VccRef_S_TrimWt[i] =  -6.55;  i++;     
	VccRef_S_code[i] = 25; VccRef_S_TrimWt[i] =  -7.30;  i++;     
	VccRef_S_code[i] = 26; VccRef_S_TrimWt[i] =  -8.00;  i++;     
	VccRef_S_code[i] = 27; VccRef_S_TrimWt[i] =  -8.90;  i++;     
	VccRef_S_code[i] = 28; VccRef_S_TrimWt[i] =  -9.70;  i++;    
	VccRef_S_code[i] = 29; VccRef_S_TrimWt[i] =  -10.50; i++;     
	VccRef_S_code[i] = 30; VccRef_S_TrimWt[i] =  -11.50; i++;     
	VccRef_S_code[i] = 31; VccRef_S_TrimWt[i] =  -12.20; i++;    

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

	//Disable DSM I2C before connecting any relays.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K2_HSG_SPI_TB);      //Disconect OVI_1_0 from HSG.
	Close_relay(K2_B_SPI_TB);        //Disconnect OVI_3_1 from B.
	Close_relay(K3_B_SPI_TB);		//Connect 2nF to B
	Close_relay(K3_HSG_SPI_TB);     //Connect 2nF to HSG
	//Close_relay(K1_IS_SPI_TB);		//Disconnect DVI from IS
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

	//IS = 100mV/20mA
	IS_dvi2k->set_current(IS_ch, 20e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, 1, VOLT_1_RANGE);
	//wait.delay_10_us(100);

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

	//ZTMC_CC_Ref
	//0x00 0x46 write 0x00 0x01
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0100);

	//ZTMC_Dsbl_DaliCK2
	//0x00 0x60 write 0x00 0x01
	//DSM_I2C_Write('w', g_S_TEST_CTRL1, 0x0002);

	

	//CORE_CTRL0 
	//0x00 0x10 write FF
	DSM_I2C_Write('w', 0x64, 0x1FFF);

	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.1e-9, RANGE_3_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_1_RANGE); 	
	wait.delay_10_us(500);

	if (g_Burn_Enable_S)
	{	
		Program_All_TrimRegister();
	}

	VccRef_pt_S = FB_ovi3->measure_average(100);

	g_VccRef_Pre = VccRef_pt_S;
	

	if (g_Burn_Enable_S && g_OPCODE==4200)
	{
		// VccRef can be either trimmed up or down only.  
		// VccRef_S_Code //
		// Find which trim code will make VccRef_Pre closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<32; i++)
		{
			temp_1 = (VccRef_pt_S * (1 + (VccRef_S_TrimWt[i]/100)) -  VccRef_Target_S);
			if (temp_1 < 0)	// Get rid of negatives //
				temp_1 *= -1.0;
			if (temp_1 < smallest_diff_val)
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}


		//if(smallest_diff_idx == 3) smallest_diff_idx = 0;
		//Manual forcing:
		//smallest_diff_idx = 17;

		VccRef_TrCode_S = VccRef_S_code[smallest_diff_idx];
		VccRef_ExpChg   = VccRef_S_TrimWt[smallest_diff_idx];

		VccRef_ExpValue = (VccRef_pt_S * (1 + (VccRef_S_TrimWt[smallest_diff_idx]/100)));

		TrimCode_To_TrimBit(VccRef_TrCode_S, "VccRef_S", 's');

		//Convert Trimcode to readable datalog file.
		///*if(VccRef_S_code[smallest_diff_idx]>=0 && VccRef_S_code[smallest_diff_idx] <= 2)
		//{
		//	CCOffset_BitCode_S = -1*CCOffset_TrCode_S; 
		//}*/

		EEpr_Bank_S[E6] = EEpr_Bank_S[E6] | (VccRef_TrCode_S<<(52-startbit));
		Program_Single_TrimRegister(g_EEP_W_E6);
	}
	wait.delay_10_us(500);

	VccRef_prg_S = FB_ovi3->measure_average(25);

	if(VccRef_pt_S != 0)
	{
		VccRef_PrgChg = 100*(VccRef_prg_S - VccRef_pt_S) / VccRef_pt_S;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	//Disable DSM I2C before powerdown.
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
	Open_relay(K1_IS_SPI_TB);		 //Reconnect DVI to IS
	wait.delay_10_us(250);


	PiDatalog(func, A_VccRef_pt_S,			VccRef_pt_S,            26, POWER_MILLI);
	
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_VccRef_target_S,      VccRef_Target_S,        26, POWER_MILLI);
		PiDatalog(func, A_VccRef_TrCode_S,      VccRef_TrCode_S,        26, POWER_UNIT);
		PiDatalog(func, A_VccRef_BitCode_S,     VccRef_BitCode_S,       26, POWER_UNIT);
		PiDatalog(func, A_VccRef_ExpChg_S,      VccRef_ExpChg,          26, POWER_UNIT);
		PiDatalog(func, A_VccRef_Exp_Value,     VccRef_ExpValue,        26, POWER_MILLI);
		PiDatalog(func, A_Eetr52_DacTr0_S,      g_S_TrimRegisterTemp[52],	26, POWER_UNIT);
		PiDatalog(func, A_Eetr53_DacTr1_S,      g_S_TrimRegisterTemp[53],	26, POWER_UNIT);
		PiDatalog(func, A_Eetr54_DacTr2_S,      g_S_TrimRegisterTemp[54],	26, POWER_UNIT);
		PiDatalog(func, A_Eetr55_DacTr3_S,      g_S_TrimRegisterTemp[55],	26, POWER_UNIT);
		PiDatalog(func, A_Eetr56_DacTr4_S,      g_S_TrimRegisterTemp[56],	26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,			  EEpr_Bank_S[E6],				26, POWER_UNIT);
		PiDatalog(func, A_VccRef_prg_S,          VccRef_prg_S,              26, POWER_MILLI);
		PiDatalog(func, A_VccRef_prgchg_S,       VccRef_PrgChg,             26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_VccRef_Pst,          VccRef_prg_S,              26, POWER_MILLI);

	}


}
