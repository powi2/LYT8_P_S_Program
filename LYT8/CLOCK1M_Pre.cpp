//==============================================================================
// CLOCK1M_Pre.cpp (User function)
// 
//    void CLOCK1M_Pre_user_init(test_function& func)
//    void CLOCK1M_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)


#include "CLOCK1M_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CLOCK1M_Pre_user_init(test_function& func)
{
	CLOCK1M_Pre_params *ours;
    ours = (CLOCK1M_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CLOCK1M_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    CLOCK1M_Pre_params *ours;
    ours = (CLOCK1M_Pre_params *)func.params;

			// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CLK1M_Pre, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	//if (g_Trim_Enable_P == 0)
//		return;

	//if (g_Fn_CLK1M_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float CLK1M_pt_S      =0;
	float CLK1M_prg_S     =0;
	float CLK1M_Target_S  = 1E6; 
	int   CLK1M_TrCode_S  = 0;
	int   CLK1M_BitCode_S = 0;
	int   EEtr70_B0_S     = 0;
	int   EEtr71_B1_S     = 0;
	int   EEtr72_B2_S     = 0;
	int   EEtr73_B3_S     = 0;
	
	float CLK1M_Sim_S = 0;
	float CLK1M_Sim_Chg_S = 0;
	float CLK1M_ExpChg    = 0;
	float CLK1M_ExpValue  = 0;
	float CLK1M_PrgChg    = 0;
	float CLK1M_pst_S     = 0;
	float CLK1M_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	CLK1M_S_TrimWt[16]   = {0.0};
	float	CLK1M_S_code[16]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	float   tmeas             = 0;

	
	i = 0;
	CLK1M_S_code[i] =  0; CLK1M_S_TrimWt[i] =  0;       i++;     //0 (0 link trimmed)
	CLK1M_S_code[i] =  1; CLK1M_S_TrimWt[i] =  0;       i++;     //0 (1 link trimmed--> 0.0%)
	CLK1M_S_code[i] =  2; CLK1M_S_TrimWt[i] =  -2.6;    i++;     //0 (1 link trimmed--> 8.0%)
	CLK1M_S_code[i] =  3; CLK1M_S_TrimWt[i] =  -5.5;    i++;     //0 (2 link trimmed--> 12.0%)
	CLK1M_S_code[i] =  4; CLK1M_S_TrimWt[i] =  -8.22;   i++;     //0 (1 link trimmed--> 16.0%)
	CLK1M_S_code[i] =  5; CLK1M_S_TrimWt[i] =  -11.22;  i++;     //0 (2 link trimmed--> 20.0%)
	CLK1M_S_code[i] =  6; CLK1M_S_TrimWt[i] =  -14.62;  i++;     //0 (2 link trimmed--> 24.0%)
	CLK1M_S_code[i] =  7; CLK1M_S_TrimWt[i] =  -18.0;   i++;     //0 (3 link trimmed--> 28.0%)
	CLK1M_S_code[i] =  8; CLK1M_S_TrimWt[i] =  19.90;   i++;     //0 (1 link trimmed-->  -32%)
	CLK1M_S_code[i] =  9; CLK1M_S_TrimWt[i] =  17.91;   i++;     //0 (2 link trimmed-->  -28%)
	CLK1M_S_code[i] = 10; CLK1M_S_TrimWt[i] =  16.91;   i++;     //0 (2 link trimmed-->  -24%)
	CLK1M_S_code[i] = 11; CLK1M_S_TrimWt[i] =  13.73;   i++;     //0 (3 link trimmed-->  -20%)
	CLK1M_S_code[i] = 12; CLK1M_S_TrimWt[i] =  11.73;   i++;     //0 (2 link trimmed-->  -16%)
	CLK1M_S_code[i] = 13; CLK1M_S_TrimWt[i] =  9.51;    i++;     //0 (3 link trimmed-->  -12%)
	CLK1M_S_code[i] = 14; CLK1M_S_TrimWt[i] =  7.17;    i++;     //0 (3 link trimmed-->  -8%)
	CLK1M_S_code[i] = 15; CLK1M_S_TrimWt[i] =  4.84;    i++;     //0 (4 link trimmed-->  -4%)

	
	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //
	// E8 Trim register.
	WordArray[0]  = g_S_TrimRegister[64]; 
	WordArray[1]  = g_S_TrimRegister[65]; 
	WordArray[2]  = g_S_TrimRegister[66]; 
	WordArray[3]  = g_S_TrimRegister[67]; 
	WordArray[4]  = g_S_TrimRegister[68];
	WordArray[5]  = g_S_TrimRegister[69];
	WordArray[6]  = g_S_TrimRegister[70]; //EEtr70_B0_S
	WordArray[7]  = g_S_TrimRegister[71]; //EEtr71_B1_S
	WordArray[8]  = g_S_TrimRegister[72]; //EEtr72_B2_S
	WordArray[9]  = g_S_TrimRegister[73]; //EEtr73_B3_S
	WordArray[10] = g_S_TrimRegister[74];
	WordArray[11] = g_S_TrimRegister[75];
	WordArray[12] = g_S_TrimRegister[76];
	WordArray[13] = g_S_TrimRegister[77];
	WordArray[14] = g_S_TrimRegister[78];
	WordArray[15] = g_S_TrimRegister[79];

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
	//FB = Hiz.
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

	//Setup TMU on Buffer of B pin.
	tmu_6->close_relay(TMU_HIZ_DUT2); 
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(2.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K2_HSG_SPI_TB);      //Disconnect OVI_1_0 from HSG.
	Close_relay(K3_HSG_SPI_TB);      //Connect 2nF to HSG
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 connecting to B.
	Close_relay(K1_B_SPI_RB);       //Pullup R on B for Open Drain config later.
	Close_relay(K5_B_SPI_TB);       //Connect B to Buffer.

	
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
	//FB_ovi3->disconnect(FB_ch);  //Disconnect OVI from FB to keep it at Hiz.
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

////////////pulse.do_pulse();

	//ZTMC_Driver_en & ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_sig_EN and Core_en.  Dont turn on HSG driver because of noise.
	//0x00 0x40 write 0x05 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);

	//0x00 0x60 write 0x00 0xC0  ==> Open Drain on HSG & B.
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xC000);

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE);
	wait.delay_10_us(10);
	FB_ovi3->disconnect(FB_ch);  //Disconnect OVI from FB to keep it at Hiz.
	wait.delay_10_us(250);
	//Set pull V& I on B
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE);


	//Loading previous trimming before performing the test.
	Program_Trim_Register(g_S_TrimRegister);


	//DsysClk1Mhz on B.
	//0x00 0x42 write 0x0F 0x00
	DSM_I2C_Write('w', 0x42, 0x000F);

	//DsysClk6Mhz on B.
	//0x00 0x42 write 0x0F 0x00
	//DSM_I2C_Write('w', 0x42, 0x0018);
DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
pulse.do_pulse();

	//Monitor 1Mhz switching on Boost pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(150e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		CLK1M_pt_S = 1/tmeas;
	else
		CLK1M_pt_S = 0.0;	




	// CLK1M_S_Code //
	// Find which trim code will make CLK1M_Pre closest to target //
	smallest_diff_val = 999999.9;
	smallest_diff_idx = 0;
	for (i=0; i<16; i++)
	{
		temp_1 = (CLK1M_pt_S * (1 + (CLK1M_S_TrimWt[i]/100)) -  CLK1M_Target_S);
		if (temp_1 < 0)	// Get rid of negatives //
			temp_1 *= -1.0;
		if (temp_1 < smallest_diff_val)
		{
			smallest_diff_val = temp_1;
			smallest_diff_idx = i;
		}
	}


	//Manual forcing:
	//smallest_diff_idx = 15;

	CLK1M_TrCode_S = smallest_diff_idx;
	CLK1M_TrCode_S = CLK1M_S_code[smallest_diff_idx];
	CLK1M_ExpChg   = CLK1M_S_TrimWt[smallest_diff_idx];

	CLK1M_ExpValue = (CLK1M_pt_S * (1 + (CLK1M_S_TrimWt[smallest_diff_idx]/100)));

	TrimCode_To_TrimBit(CLK1M_TrCode_S, "Clock1M_S", 's');


	//Convert Trimcode to readable datalog file.
	///*if(CLK1M_S_code[smallest_diff_idx]>=0 && CLK1M_S_code[smallest_diff_idx] <= 7)
	//{
	//	CLK1M_BitCode_S = -1*VADC_TrCode_S; 
	//}
	//else
	//{
	//	VADC_BitCode_S = VADC_TrCode_S - 7;
	//}*/

	//Update WordArray.
	WordArray[6]        = g_S_TrimRegisterTemp[70]; //EEtr70_B0_S
	WordArray[7]        = g_S_TrimRegisterTemp[71]; //EEtr71_B1_S
	WordArray[8]        = g_S_TrimRegisterTemp[72]; //EEtr72_B2_S
	WordArray[9]        = g_S_TrimRegisterTemp[73]; //EEtr73_B3_S

	//Update secondary trim register array for programming later.
	g_S_TrimRegister[70] = g_S_TrimRegisterTemp[70]; //EEtr76_ZTLnt0_S
	g_S_TrimRegister[71] = g_S_TrimRegisterTemp[71]; //EEtr77_ZTLnt1_S
	g_S_TrimRegister[72] = g_S_TrimRegisterTemp[72]; //EEtr78_ZTLnt2_S
	g_S_TrimRegister[73] = g_S_TrimRegisterTemp[73]; //EEtr79_ZTLnt3_S

	//Convert from binary to decimal.
	converted_dec1 = Convert_BIN_2_Dec(WordArray);
	converted_dec2 = Convert_BIN_2_Dec(WordArray);

DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Program Trim Register with new calculated bit combination.
	Program_Trim_Register(g_S_TrimRegister);
DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	int TrimBank[5];

	Read_Trim_Register(TrimBank);
DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	tmeas = 0.0;

	//Monitor 1Mhz switching on Boost pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(150e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		CLK1M_prg_S = 1/tmeas;
	else
		CLK1M_prg_S = 0.0;	




	if(CLK1M_pt_S != 0)
	{
		CLK1M_PrgChg = 100*(CLK1M_prg_S - CLK1M_pt_S) / CLK1M_pt_S;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
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
	FB_ovi3->connect(FB_ch);			//Reconnect OVI to FB.
	Open_relay(K5_B_SPI_TB);       //Disconnect B from Buffer.
	tmu_6->open_relay(TMU_HIZ_DUT2); 
	wait.delay_10_us(250);


	PiDatalog(func, A_CLK1M_pt_S,		  CLK1M_pt_S,               26, POWER_MEGA);
	PiDatalog(func, A_CLK1M_target_S,     CLK1M_Target_S,           26, POWER_MEGA);
	PiDatalog(func, A_CLK1M_TrCode_S,     CLK1M_TrCode_S,           26, POWER_UNIT);
	PiDatalog(func, A_CLK1M_BitCode_S,    CLK1M_BitCode_S,           26, POWER_UNIT);
	PiDatalog(func, A_CLK1M_ExpChg_S,     CLK1M_ExpChg,             26, POWER_UNIT);
	PiDatalog(func, A_CLK1M_Exp_Value,    CLK1M_ExpValue,           26, POWER_MEGA);
	PiDatalog(func, A_Eetr70_B0_S,    g_S_TrimRegister[70],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr71_B1_S,    g_S_TrimRegister[71],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr72_B2_S,    g_S_TrimRegister[72],    26, POWER_UNIT);
	PiDatalog(func, A_Eetr73_B3_S,    g_S_TrimRegister[73],    26, POWER_UNIT);
	PiDatalog(func, A_Bin2Dec1_S,         converted_dec1,          26, POWER_UNIT);
	PiDatalog(func, A_CLK1M_prg_S,         CLK1M_prg_S,              26, POWER_MEGA);
	PiDatalog(func, A_CLK1M_prgchg_S,      CLK1M_PrgChg,             26, POWER_UNIT);


}
