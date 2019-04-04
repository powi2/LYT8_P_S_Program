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

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Trim_Enable_S == 0)
		return;

	//if (g_Fn_CV_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables
	float vFB_Start      = 0.0;
	float vStep          = 0.0;
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
	float CV_Target_S = 1.25; //gCV_Vout_TARGET_Trimops;
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


	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //
	// E4 Trim register.
	WordArray[0]  = g_S_TrimRegister[32];
	WordArray[1]  = g_S_TrimRegister[33];
	WordArray[2]  = g_S_TrimRegister[34];
	WordArray[3]  = g_S_TrimRegister[35];
	WordArray[4]  = g_S_TrimRegister[36];
	WordArray[5]  = g_S_TrimRegister[37];
	WordArray[6]  = g_S_TrimRegister[38]; //EEtr38_Vref1_S
	WordArray[7]  = g_S_TrimRegister[39]; //EEtr39_Vref2_s
	WordArray[8]  = g_S_TrimRegister[40]; //EEtr40_Vref3_S
	WordArray[9]  = g_S_TrimRegister[41]; //EEtr41_Vref4_S
	WordArray[10] = g_S_TrimRegister[42];
	WordArray[11] = g_S_TrimRegister[43];
	WordArray[12] = g_S_TrimRegister[44]; 
	WordArray[13] = g_S_TrimRegister[45]; 
	WordArray[14] = g_S_TrimRegister[46]; 
	WordArray[15] = g_S_TrimRegister[47];

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
	 
		FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
		FB_ovi3->set_current(FB_ch, 0.0e-6, RANGE_3_UA);
		FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
		wait.delay_10_us(100);
		
		CV_pt_S = FB_ovi3->measure_average(25);	
	}

	else
	{
			//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
			//											  (This Test Mode disable 
			//0x00 0x62 write 0x88 0x00
			DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

			//ZTMC_ana_EN and Core_en
			//0x00 0x40 write 0x06 0x00
			DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

			//0x00 0x60 write 0x00 0xC0  ==> Open Drain on HSG & B.
			DSM_I2C_Write('w', g_TEST_CTRL1, 0xC000);

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

			CV_Search(VcvPFOff_Pt, CV_pt_S, VcvBOff_Pt, vFB_Start, vStep);
	}

	// CV_S_Code //
	// Find which trim code will make CV_Pre closest to target //
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

	CV_TrCode_S = smallest_diff_idx;
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

	//Update WordArray.
	WordArray[6]        = g_S_TrimRegisterTemp[38]; //EEtr38_Vref1_S
	WordArray[7]        = g_S_TrimRegisterTemp[39]; //EEtr39_Vref2_s
	WordArray[8]        = g_S_TrimRegisterTemp[40]; //EEtr40_Vref3_S
	WordArray[9]        = g_S_TrimRegisterTemp[41]; //EEtr41_Vref4_S

	//Update secondary trim register array for programming later.
	g_S_TrimRegister[38] = g_S_TrimRegisterTemp[38]; //EEtr38_Vref1_S
	g_S_TrimRegister[39] = g_S_TrimRegisterTemp[39]; //EEtr39_Vref2_s
	g_S_TrimRegister[40] = g_S_TrimRegisterTemp[40]; //EEtr40_Vref3_S
	g_S_TrimRegister[41] = g_S_TrimRegisterTemp[41]; //EEtr41_Vref4_S

	//Convert from binary to decimal.
	converted_dec1 = Convert_BIN_2_Dec(WordArray);
	converted_dec2 = Convert_BIN_2_Dec(WordArray);


	//Program Trim Register with new calculated bit combination.
	Program_Trim_Register(g_S_TrimRegister);

	//int TrimBank[5];

	//Read_Trim_Register(TrimBank);
//DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
//		TrimBank[0] = DSM_I2C_Read(0xC0);	//Read back data of Register addr 0xE0 from 0xC0 register address through READ_ADDR 0x00
//		TrimBank[1] = DSM_I2C_Read(0xC2);	//Read back data of Register addr 0xE2 from 0xC2 register address through READ_ADDR 0x00
//		TrimBank[2] = DSM_I2C_Read(0xC4);	//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
//		TrimBank[3] = DSM_I2C_Read(0xC6);	//Read back data of Register addr 0xE6 from 0xC6 register address through READ_ADDR 0x00
//		TrimBank[4] = DSM_I2C_Read(0xC8);

	if(input_direct)
	{
		wait.delay_10_us(500);	
		CV_prg_S = FB_ovi3->measure_average(25);	
	}
	else
	{
			//Ramp FB and record CV-1.6%, CV & CV+1.6%
			vFB_Start = 1.0;
			vStep = 2e-3;
			CV_Search(VcvPFOff_Pst, CV_prg_S, VcvBOff_Pst, vFB_Start, vStep);
	}

	if(CV_pt_S != 0)
	{
		CV_PrgChg = 100*(CV_prg_S - CV_pt_S) / CV_pt_S;
	}
	//-----------------------------------------------------------------------------------------------------
	//Powerdown sequence.
	//Disable I2C after programming.
	//------------------------------------------------------------------------------------------------------

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
	PiDatalog(func, A_CV_target_S,  CV_Target_S,          26, POWER_UNIT);
	PiDatalog(func, A_CV_TrCode_S,  CV_TrCode_S,          26, POWER_UNIT);
	PiDatalog(func, A_CV_BitCode_S, CV_BitCode_S,         26, POWER_UNIT);
	PiDatalog(func, A_CV_ExpChg_S,  CV_ExpChg,         26, POWER_UNIT);
	PiDatalog(func, A_Iztr_Vref0_S, g_S_TrimRegister[38], 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_Vref1_S, g_S_TrimRegister[39], 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_Vref2_S, g_S_TrimRegister[40], 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_Vref3_S, g_S_TrimRegister[41], 26, POWER_UNIT);
	PiDatalog(func, A_Bin2Dec1_S,   converted_dec1,        26, POWER_UNIT);
	PiDatalog(func, A_CV_prg_S,     CV_prg_S,             26, POWER_UNIT);
	PiDatalog(func, A_CV_prgchg_S,  CV_PrgChg,         26, POWER_UNIT);

	if(!input_direct)
	{
		PiDatalog(func, A_cVPFOff_pst_S, VcvPFOff_Pst,        26, POWER_UNIT);
		PiDatalog(func, A_cvBOff_pst_S,  VcvBOff_Pst,         26, POWER_UNIT);
	}
	if (g_Char_Enable_P) // Characterization only //
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


/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CV_Pre, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	if (g_Fn_CV_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//int fNum_CV_Pre = 0;
	//float CV_pt_S =0;
	float CV_Target_S = gCV_Vout_TARGET_Trimops;
	int CV_TrCode_S = 0;
	int CV_BitCode_S = 0;
	int EEtr_CV1_S = 0;
	int EEtr_CV2_S = 0;
	int EEtr_CV3_S = 0;
	int EEtr_CV4_S = 0;
	int EEtr_CV5_S = 0;
	int EEtr_CV6_S = 0;
	float CV_Sim_S = 0;
	float CV_Sim_Chg_S = 0;
	float CV_Pre_TT =0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	int TempArray[30] = {0};
	float WordData = 0;
	float UpperLimit = 0;
	float LowerLimit = 0;
	float Vforce = 0;
	float SRpinVolt = 0;
	Pulse pulse;

	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Close_relay(K18);
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

	// COMP //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 3.3; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

	// SDA //
	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		
	// Wait for relays //
	wait.delay_10_us(200); 

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //

	Write_Word(g_TM_ANA, 0x0134, NObin, HEX); // TM_EN_SR_driver //

	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Always load g_ShadowRegister[] array to shadow register of DUT after powerup if EEPROM has not yet been written. //
	LoadShadowRegister();

	// Float SR dvi //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

	// Connect the FB comparator output to SR pin (CV comparator output). //
	Write_Word(g_TM_SEL, 0x0024, NObin, HEX);
	
	// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
	// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
	// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX);

	// CV regisiter is programmed to 5V by default on powerup. //

	// Binary search CV [on Vout pin] to get the CV_pt_S value, should be around CV_Target_S. //
	// Look for FB comparator output flip on SR pin. //
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
	UpperLimit = (func.dlog->tests[A_CV_pt_S].f_max_limit_val[0])*1.1; // Get upper search limit //
	LowerLimit = (func.dlog->tests[A_CV_pt_S].f_min_limit_val[0])*0.9; // Get lower search limit //
//	if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//	{
//		UpperLimit = (func.dlog->tests[A_CV_pt_S].f_max_limit_val[0])*1.4; // Get upper search limit //
//		LowerLimit = (func.dlog->tests[A_CV_pt_S].f_min_limit_val[0])*0.6; // Get lower search limit //
//	}
	Vforce = (UpperLimit + LowerLimit) / 2;
	if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
	{
		Vforce = 0;
		g_Error_Flag = -111;
	}
	VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
	wait.delay_10_us(100);
	while ( (UpperLimit - LowerLimit) > .001)
	{
		Vforce = (UpperLimit + LowerLimit) / 2; 
		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -112;
			break;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
		if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
			LowerLimit = Vforce;
		else // Above threshold.  CV comparator high. //
			UpperLimit = Vforce;		
	}
	g_CV_pt_S = Vforce;

	// Load WordArray[] with contents of g_ShadowRegister[] array!  Must not overwrite shadow register!  This is important for proper trimming! //
	WordArray[0] = g_ShadowRegister[16]; // EEtr_CV1_S //
	WordArray[1] = g_ShadowRegister[17]; // EEtr_CV2_S // 
	WordArray[2] = g_ShadowRegister[18]; // EEtr_CV3_S //
	WordArray[3] = g_ShadowRegister[19]; // EEtr_CV4_S //
	WordArray[4] = g_ShadowRegister[20]; // EEtr_CV5_S //
	WordArray[5] = g_ShadowRegister[21]; // EEtr_CV6_S //
	WordArray[6] = g_ShadowRegister[22];
	WordArray[7] = g_ShadowRegister[23];
	WordArray[8] = g_ShadowRegister[24];
	WordArray[9] = g_ShadowRegister[25];
	WordArray[10] = g_ShadowRegister[26];
	WordArray[11] = g_ShadowRegister[27];
	WordArray[12] = g_ShadowRegister[28];
	WordArray[13] = g_ShadowRegister[29];
	WordArray[14] = g_ShadowRegister[30];
	WordArray[15] = g_ShadowRegister[31];

	// Find trim code closest to target. //
	// Apply CV_Target_S at VOUT pin, write the I2C command to set_CV to be CV_Target_S; adjust the trim code through I2C until the comparator triggered. //
	VO_dvi->set_voltage(VO_ch, CV_Target_S, VOLT_10_RANGE); // DVI_9_0 //

	// CV regisiter is programmed to 5V by default on powerup. //

	// Find trim code closest to target. //
	UpperLimit = 33;
	LowerLimit = -32; 
	while ( (UpperLimit - LowerLimit) > 1)
	{
		CV_BitCode_S = (UpperLimit + LowerLimit) / 2;
		
		// Convert BitCode to TrCode. Mapping between bit code and trim code. //
		if(CV_BitCode_S == -31) CV_TrCode_S = 31;
		if(CV_BitCode_S == -30) CV_TrCode_S = 30;
		if(CV_BitCode_S == -29) CV_TrCode_S = 29;
		if(CV_BitCode_S == -28) CV_TrCode_S = 28;
		if(CV_BitCode_S == -27) CV_TrCode_S = 27;
		if(CV_BitCode_S == -26) CV_TrCode_S = 26;
		if(CV_BitCode_S == -25) CV_TrCode_S = 25;
		if(CV_BitCode_S == -24) CV_TrCode_S = 24;
		if(CV_BitCode_S == -23) CV_TrCode_S = 23;
		if(CV_BitCode_S == -22) CV_TrCode_S = 22;
		if(CV_BitCode_S == -21) CV_TrCode_S = 21;
		if(CV_BitCode_S == -20) CV_TrCode_S = 20;
		if(CV_BitCode_S == -19) CV_TrCode_S = 19;
		if(CV_BitCode_S == -18) CV_TrCode_S = 18;
		if(CV_BitCode_S == -17) CV_TrCode_S = 17;
		if(CV_BitCode_S == -16) CV_TrCode_S = 16;
		if(CV_BitCode_S == -15) CV_TrCode_S = 15;
		if(CV_BitCode_S == -14) CV_TrCode_S = 14;
		if(CV_BitCode_S == -13) CV_TrCode_S = 13;
		if(CV_BitCode_S == -12) CV_TrCode_S = 12;
		if(CV_BitCode_S == -11) CV_TrCode_S = 11;
		if(CV_BitCode_S == -10) CV_TrCode_S = 10;
		if(CV_BitCode_S == -9) CV_TrCode_S = 9;
		if(CV_BitCode_S == -8) CV_TrCode_S = 8;
		if(CV_BitCode_S == -7) CV_TrCode_S = 7;
		if(CV_BitCode_S == -6) CV_TrCode_S = 6;
		if(CV_BitCode_S == -5) CV_TrCode_S = 5;
		if(CV_BitCode_S == -4) CV_TrCode_S = 4;
		if(CV_BitCode_S == -3) CV_TrCode_S = 3;
		if(CV_BitCode_S == -2) CV_TrCode_S = 2;
		if(CV_BitCode_S == -1) CV_TrCode_S = 1;
		if(CV_BitCode_S == 0) CV_TrCode_S = 0;
		if(CV_BitCode_S == 1) CV_TrCode_S = 32;
		if(CV_BitCode_S == 2) CV_TrCode_S = 33;
		if(CV_BitCode_S == 3) CV_TrCode_S = 34;
		if(CV_BitCode_S == 4) CV_TrCode_S = 35;
		if(CV_BitCode_S == 5) CV_TrCode_S = 36;
		if(CV_BitCode_S == 6) CV_TrCode_S = 37;
		if(CV_BitCode_S == 7) CV_TrCode_S = 38;
		if(CV_BitCode_S == 8) CV_TrCode_S = 39;
		if(CV_BitCode_S == 9) CV_TrCode_S = 40;
		if(CV_BitCode_S == 10) CV_TrCode_S = 41;
		if(CV_BitCode_S == 11) CV_TrCode_S = 42;
		if(CV_BitCode_S == 12) CV_TrCode_S = 43;
		if(CV_BitCode_S == 13) CV_TrCode_S = 44;
		if(CV_BitCode_S == 14) CV_TrCode_S = 45;
		if(CV_BitCode_S == 15) CV_TrCode_S = 46;
		if(CV_BitCode_S == 16) CV_TrCode_S = 47;
		if(CV_BitCode_S == 17) CV_TrCode_S = 48;
		if(CV_BitCode_S == 18) CV_TrCode_S = 49;
		if(CV_BitCode_S == 19) CV_TrCode_S = 50;
		if(CV_BitCode_S == 20) CV_TrCode_S = 51;
		if(CV_BitCode_S == 21) CV_TrCode_S = 52;
		if(CV_BitCode_S == 22) CV_TrCode_S = 53;
		if(CV_BitCode_S == 23) CV_TrCode_S = 54;
		if(CV_BitCode_S == 24) CV_TrCode_S = 55;
		if(CV_BitCode_S == 25) CV_TrCode_S = 56;
		if(CV_BitCode_S == 26) CV_TrCode_S = 57;
		if(CV_BitCode_S == 27) CV_TrCode_S = 58;
		if(CV_BitCode_S == 28) CV_TrCode_S = 59;
		if(CV_BitCode_S == 29) CV_TrCode_S = 60;
		if(CV_BitCode_S == 30) CV_TrCode_S = 61;
		if(CV_BitCode_S == 31) CV_TrCode_S = 62;
		if(CV_BitCode_S == 32) CV_TrCode_S = 63;

		// Convert decimal number 'CV_TrCode_S' into binary number and store in TempArray[]. //		
		Convert_Decimal_To_Binary(CV_TrCode_S, TempArray);

		// Load TempArray[] to WordArray[] at correct bit locations. //
		WordArray[0] = TempArray[0];
		WordArray[1] = TempArray[1]; 
		WordArray[2] = TempArray[2]; 
		WordArray[3] = TempArray[3]; 
		WordArray[4] = TempArray[4]; 
		WordArray[5] = TempArray[5]; 

		// Load new trim code to shadow register. //
		Write_Word(g_SREG1, NOhex, WordArray, BIN); // Load trim code to shadow register. //
		wait.delay_10_us(100);

		// Check if CV comparator output has flipped. //
		SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
		if (SRpinVolt > 1.5) // Below target //
			LowerLimit = CV_BitCode_S;
		else // Above target //
			UpperLimit = CV_BitCode_S;		
	}

	// Load the shadow register with the final trim code CV_TrCode_S.  Must not overwrite any of the other shadow register bits! //	
	Convert_Decimal_To_Binary(CV_TrCode_S, TempArray); // Convert decimal number 'CV_TrCode_S' into binary number and store in TempArray[]. // 

	// Load TempArray[] to WordArray[] at correct bit locations. //
	WordArray[0] = TempArray[0];
	WordArray[1] = TempArray[1]; 
	WordArray[2] = TempArray[2]; 
	WordArray[3] = TempArray[3]; 
	WordArray[4] = TempArray[4]; 
	WordArray[5] = TempArray[5]; 

	// Load final trim code to shadow register. //
	Write_Word(g_SREG1, NOhex, WordArray, BIN); // Load trim code to shadow register. //

	// Save the new values to the g_ShadowRegister[] array. //
	g_ShadowRegister[16] = WordArray[0];
	g_ShadowRegister[17] = WordArray[1];
	g_ShadowRegister[18] = WordArray[2];
	g_ShadowRegister[19] = WordArray[3];
	g_ShadowRegister[20] = WordArray[4];
	g_ShadowRegister[21] = WordArray[5];

	// Load individual bits for datalogging //
	EEtr_CV1_S = WordArray[0];
	EEtr_CV2_S = WordArray[1];
	EEtr_CV3_S = WordArray[2];
	EEtr_CV4_S = WordArray[3];
	EEtr_CV5_S = WordArray[4];
	EEtr_CV6_S = WordArray[5];

	if (g_Char_Enable_P) // Characterization only //
	{
		// CV_Sim_S. Measure the final value after shadow register is loaded with final trim code. //
		// Binary search CV [on Vout pin] to get the CV_Sim_S value, should be around CV_Target_S. //
		// Look for FB comparator output flip on SR pin. //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
		UpperLimit = (func.dlog->tests[A_CV_Sim_S].f_max_limit_val[0])*1.1; // Get upper search limit //
		LowerLimit = (func.dlog->tests[A_CV_Sim_S].f_min_limit_val[0])*0.9; // Get lower search limit //
//		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
//		{
//			UpperLimit = (func.dlog->tests[A_CV_Sim_S].f_max_limit_val[0])*1.5; // Get upper search limit //
//			LowerLimit = (func.dlog->tests[A_CV_Sim_S].f_min_limit_val[0])*0.5; // Get lower search limit //
//		}
		Vforce = (UpperLimit + LowerLimit) / 2;
		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -113;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		while ( (UpperLimit - LowerLimit) > .001)
		{
			Vforce = (UpperLimit + LowerLimit) / 2; 
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -114;
				break;
			}
			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(30);
			SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
			if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
				LowerLimit = Vforce;
			else // Above threshold.  CV comparator high. //
				UpperLimit = Vforce;		
		}
		CV_Sim_S = Vforce;
		CV_Sim_Chg_S = ((CV_Sim_S - g_CV_pt_S) / g_CV_pt_S)*100; // In percent //
	}

	// Reset test mode control register for next test. //
	Write_Word(g_TM_CTRL, 0x0000, NObin, HEX);

	// Powerdown //
//	Open_relay(K18);
//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	SR_dvi2k->set_voltage(SR_ch, 5, VOLT_10_RANGE); // DVI_13_1, dvi2k, prevent undershoot //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	wait.delay_10_us(45); // prevent SR undershoot //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
//	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
//	VO_dvi->set_voltage(VO_ch, 4.7, VOLT_10_RANGE);
//	wait.delay_10_us(5);
//	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE);
//	FB_ovi->connect(2);
//	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//	Mux20_Open_relay(K64);
//	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//	Mux20_Open_relay(K37);
//	Mux20_Open_relay(K38);
//	Mux20_Open_relay(K40);
//	Mux20_Open_relay(K39);
//	ddd_7->ddd_set_clock_period(Dclk_period);
//	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
//	g_DDD_Low = 0.0; // Save current value //
//	g_DDD_High = 4.0; // Save current value //
//	wait.delay_10_us(100);
//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	//PiDatalog(func, A_Func_Num_CV_Pre, fNum_CV_Pre, 26, POWER_UNIT);
	PiDatalog(func, A_CV_pt_S, g_CV_pt_S, 26, POWER_UNIT);
	PiDatalog(func, A_CV_target_S, CV_Target_S, 26, POWER_UNIT);
	PiDatalog(func, A_CV_TrCode_S, CV_TrCode_S, 26, POWER_UNIT);
	PiDatalog(func, A_CV_BitCode_S, CV_BitCode_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV1_S, EEtr_CV1_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV2_S, EEtr_CV2_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV3_S, EEtr_CV3_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV4_S, EEtr_CV4_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV5_S, EEtr_CV5_S, 26, POWER_UNIT);
	PiDatalog(func, A_Iztr_CV6_S, EEtr_CV6_S, 26, POWER_UNIT);
	if (g_Char_Enable_P) // Characterization only //
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

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
