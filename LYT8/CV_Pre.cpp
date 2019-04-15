//==============================================================================
// CV_Pre.cpp (User function)
// 
//    void CV_Pre_user_init(test_function& func)
//    void CV_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "CV_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CV_Pre_user_init(test_function& func)
{
	CV_Pre_params *ours;
    ours = (CV_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CV_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    CV_Pre_params *ours;
    ours = (CV_Pre_params *)func.params;

	// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CV_Pre, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	if (g_Burn_Enable_S == 0 && g_GRR_Enable == 0)
		return;


	if (g_OPCODE==4250 || g_OPCODE==4300 || g_OPCODE==4500)
		return;

	//if (g_Fn_CV_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables
	float vFB_Start      = 0.0;
	float vStep          = 0.0;
	g_CV_Prg             = 0.0;
	float VcvPFOff_Pt    = 0.0;
	float VcvPFOff_Pst   = 0.0;
	float VcvBOff_Pt     = 0.0;
	float VcvBOff_Pst    = 0.0;
	float i_HSG          = 0.0;
	int   i              = 0;
	int   input_direct   = 1;
	int   loop_1         = 0;
	int   loop_2         = 0;
	int   exit_loop      = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	//int fNum_CV_Pre = 0;
	float CV_pt_S  =0;
	float CV_prg_S =0;
	float CV_Target_S = g_CV_Target_S_Trimops;//1.25; //gCV_Vout_TARGET_Trimops;
	int CV_TrCode_S = 0;
	int CV_BitCode_S = 0;
	int EEtr_Vref0_S = 0;
	int EEtr_Vref1_S = 0;
	int EEtr_Vref2_S = 0;
	int EEtr_Vref3_S = 0;
	float CV_Sim_S = 0;
	float CV_Sim_Chg_S = 0;
	float CV_ExpChg   = 0;
	float CV_PrgChg   = 0;
	float CV_pst_S =0;
	float CV_Pre_TT =0;

Pulse pulse;

	//Trimcode & bit weights.
	float	CV_S_TrimWt[16]   = {0.0};
	float	CV_S_code[16]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	int     startbit          = 32;

	i = 0;
	CV_S_code[i] =  0; CV_S_TrimWt[i] =  0;      i++;     //0 (0 link trimmed)
	CV_S_code[i] =  1; CV_S_TrimWt[i] = -0.5;    i++;    //0 (1 link trimmed--> -0.5%)
	CV_S_code[i] =  2; CV_S_TrimWt[i] = -1.0;    i++;    //0 (1 link trimmed--> -1.0%)
	CV_S_code[i] =  3; CV_S_TrimWt[i] = -1.5;    i++;    //0 (2 link trimmed--> -1.5%)
	CV_S_code[i] =  4; CV_S_TrimWt[i] = -1.5;    i++;    //0 (1 link trimmed--> -1.5%)
	CV_S_code[i] =  5; CV_S_TrimWt[i] = -2.0;    i++;    //0 (2 link trimmed--> -1.5%)
	CV_S_code[i] =  6; CV_S_TrimWt[i] = -2.5;    i++;    //0 (2 link trimmed--> -2.5%)
	CV_S_code[i] =  7; CV_S_TrimWt[i] = -3.0;    i++;    //0 (3 link trimmed--> -3.0%)
	CV_S_code[i] =  8; CV_S_TrimWt[i] =  0.5;    i++;    //0 (1 link trimmed-->  0.5%)
	CV_S_code[i] =  9; CV_S_TrimWt[i] =  1.0;    i++;    //0 (2 link trimmed-->  1.0%)
	CV_S_code[i] = 10; CV_S_TrimWt[i] =  1.5;    i++;    //0 (2 link trimmed-->  1.5%)
	CV_S_code[i] = 11; CV_S_TrimWt[i] =  2.0;    i++;    //0 (3 link trimmed-->  2.0%)
	CV_S_code[i] = 12; CV_S_TrimWt[i] =  2.5;    i++;    //0 (2 link trimmed-->  2.5%)
	CV_S_code[i] = 13; CV_S_TrimWt[i] =  3.0;    i++;    //0 (3 link trimmed-->  3.0%)
	CV_S_code[i] = 14; CV_S_TrimWt[i] =  3.5;    i++;    //0 (3 link trimmed-->  3.5%)
	CV_S_code[i] = 15; CV_S_TrimWt[i] =  4.0;    i++;    //0 (4 link trimmed-->  4.0%)

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
	Close_relay(K3_B_SPI_TB);		//Connect 2nF to B
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
	

	if(input_direct)
	{
		//Direct measuring at the input of the opamp (excluding the opamp offset)
		//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
		//											  (This Test Mode disable 
		//0x00 0x62 write 0x88 0x00
		DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

		//ZTMC_ana_EN and Core_en
		//0x00 0x40 write 0x06 0x00
		DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

		//0x00 0x44 write 0x10 0x00  ==> ZTMC_Avref_1p25V
		DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0010);

		if (g_Burn_Enable_S != 0)
		{
			Program_All_TrimRegister();
		}
	 
		FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
		FB_ovi3->set_current(FB_ch, 0.0e-6, RANGE_3_UA);
		FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
		wait.delay_10_us(100);
		
		CV_pt_S = FB_ovi3->measure_average(25);	
		g_CV_Pre = CV_pt_S;
		
	}

	else
	{
			//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
			//											  (This Test Mode disable 
			//0x00 0x62 write 0x88 0x00
			DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

			//ZTMC_ana_EN and Core_en ==> Avoid enable B due to noise.
			//0x00 0x40 write 0x06 0x00
			DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

			//0x00 0x60 write 0x00 0xC0  ==> Open Drain on HSG & B.
			//DSM_I2C_Write('w', g_TEST_CTRL1, 0xC000);
			//ZOpenDrain<0>,ZOpenDrain<1> 
			//0x00 0x60 write 0x02 0xC0 ==> To reduce noise.
			DSM_I2C_Write('w', g_TEST_CTRL1, 0xE020);
			DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

			//This method is to include the voffset of the opamp.
			//0x00 0x46 write 0x00 0xF0  ==> enable Dcv_comps_out to HSG
			DSM_I2C_Write('w', g_ANA_CTRL_1, 0xF000); 

			if (g_Burn_Enable_S != 0)
			{
				Program_All_TrimRegister();
			}

			//Set pullup voltage on HSG to 2V to minimize noise when HG switches.
			HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_CURRENT);
			HSG_ovi->set_voltage(HSG_ch, 2, VOLT_5_RANGE); 
			wait.delay_10_us(200);

			//Ramp FB and record CV-1.6%, CV & CV+1.6%
			vFB_Start = 1.1;
			vStep = 2e-3;

			CV_Search(VcvPFOff_Pt, CV_pt_S, VcvBOff_Pt, vFB_Start, vStep);

			g_CV_Pre = CV_pt_S;
	}

	// CV_S_Code //
	// Find which trim code will make CV_Pre closest to target //


	if (g_Burn_Enable_S)
	{
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<16; i++)
		{
			temp_1 = (CV_pt_S * (1 + (CV_S_TrimWt[i]/100)) -  CV_Target_S);
			if (temp_1 < 0)	// Get rid of negatives //
				temp_1 *= -1.0;
			if (temp_1 < smallest_diff_val)
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		//Manual Forcing
		//smallest_diff_idx = 0;

		CV_TrCode_S = CV_S_code[smallest_diff_idx];
		CV_ExpChg   = CV_S_TrimWt[smallest_diff_idx];
		TrimCode_To_TrimBit(CV_TrCode_S, "CV_S", 's');

		if(CV_TrCode_S >=0 && CV_TrCode_S <=7)
		{
			CV_BitCode_S = -1*CV_TrCode_S;
		}
		else
		{
			CV_BitCode_S = CV_TrCode_S - 7;
		}

		EEpr_Bank_S[E4] = EEpr_Bank_S[E4] | (CV_TrCode_S<<(38-startbit));

		Program_Single_TrimRegister(g_EEP_W_E4);
	}
	if(input_direct)
	{
		wait.delay_10_us(100);	
		CV_prg_S = FB_ovi3->measure_average(25);	
	}
	else
	{
			//Ramp FB and record CV-1.6%, CV & CV+1.6%
			vFB_Start = 1.0;
			vStep = 2e-3;
			CV_Search(VcvPFOff_Pst, CV_prg_S, VcvBOff_Pst, vFB_Start, vStep);
	}


	g_CV_Prg = CV_prg_S;
	if(CV_pt_S != 0)
	{
		CV_PrgChg = 100*(CV_prg_S - CV_pt_S) / CV_pt_S;
	}
	//-----------------------------------------------------------------------------------------------------
	//Powerdown sequence.
	//Disable I2C after programming.
	//------------------------------------------------------------------------------------------------------

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_5_RANGE); 
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
	//PiDatalog(func, A_Func_Num_CV_Pre, fNum_CV_Pre, 26, POWER_UNIT);
	PiDatalog(func, A_CV_pt_S,      CV_pt_S,              26, POWER_UNIT);
	if(!input_direct)
	{
		PiDatalog(func, A_cVPFOff_pt_S, VcvPFOff_Pt,          26, POWER_UNIT);
		PiDatalog(func, A_cvBOff_pt_S,  VcvBOff_Pt,           26, POWER_UNIT);
	}
	
	
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_CV_target_S,  CV_Target_S,          26, POWER_UNIT);
		PiDatalog(func, A_CV_TrCode_S,  CV_TrCode_S,          26, POWER_UNIT);
		PiDatalog(func, A_CV_BitCode_S, CV_BitCode_S,         26, POWER_UNIT);
		PiDatalog(func, A_CV_ExpChg_S,  CV_ExpChg,         26, POWER_UNIT);
		PiDatalog(func, A_Iztr_Vref0_S, g_S_TrimRegisterTemp[38], 26, POWER_UNIT);
		PiDatalog(func, A_Iztr_Vref1_S, g_S_TrimRegisterTemp[39], 26, POWER_UNIT);
		PiDatalog(func, A_Iztr_Vref2_S, g_S_TrimRegisterTemp[40], 26, POWER_UNIT);
		PiDatalog(func, A_Iztr_Vref3_S, g_S_TrimRegisterTemp[41], 26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,   EEpr_Bank_S[E4],        26, POWER_UNIT);
		PiDatalog(func, A_CV_prg_S,     CV_prg_S,             26, POWER_UNIT);
		PiDatalog(func, A_CV_prgchg_S,  CV_PrgChg,         26, POWER_UNIT);
	}
	else
	{
		
		PiDatalog(func, A_CV_Pst,     CV_prg_S,             26, POWER_UNIT);
	}

	if(!input_direct)
	{
		PiDatalog(func, A_cVPFOff_pst_S, VcvPFOff_Pst,        26, POWER_UNIT);
		PiDatalog(func, A_cvBOff_pst_S,  VcvBOff_Pst,         26, POWER_UNIT);
	}
	if (0)//g_Char_Enable_P) // Characterization only //
	{
		PiDatalog(func, A_CV_Sim_S, CV_Sim_S, 26, POWER_UNIT);
		PiDatalog(func, A_CV_Sim_Chg_S, CV_Sim_Chg_S, 26, POWER_UNIT);
	}
	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		CV_Pre_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_CV_Pre_TT, CV_Pre_TT, 26, POWER_MILLI);
	}



}
