//==============================================================================
// Fosc_pt_S.cpp (User function)
// 
//    void Fosc_pt_S_user_init(test_function& func)
//    void Fosc_pt_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_pt_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_pt_S_user_init(test_function& func)
{
	Fosc_pt_S_params *ours;
    ours = (Fosc_pt_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_pt_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_pt_S_params *ours;
    ours = (Fosc_pt_S_params *)func.params;


		gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Pre_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Burn_Enable_P == 0)
//		return;


	if (g_Trim_Enable_S == 0 && g_GRR == 0)
		return;

	//if (g_Fn_CLK1M_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[32]  = {0};
	int   WordArray_E0[16] = {0};
	int   WordArray_E2[16] = {0};
	int   TrimRegisterTemp[80] = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float Fosc_pt_S      = 0;
	float Fosc_prg_S     = 0;
	float Fosc_Target_S1  = 100E3; 
	float Fosc_New_Target_S = 0;
	int   Fosc_TrCode_S  = 0;
	int   Fosc_BitCode_S1 = 0;
	int   EEtr64_VCO0_S     = 0;
	int   EEtr65_VCO1_S     = 0;
	int   EEtr66_VCO2_S     = 0;
	int   EEtr67_VCO3_S     = 0;
	int   EEtr68_VCO4_S     = 0;
	int   EEtr69_VCO5_S     = 0;
	int   startbit          = 0;

	float Fosc_Sim_S = 0;
	float Fosc_Sim_Chg_S = 0;
	float Fosc_ExpChg    = 0;
	float Fosc_ExpValue  = 0;
	float Fosc_PrgChg    = 0;
	float Fosc_pst_S     = 0;
	float Fosc_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	Fosc_S_TrimWt[32]   = {0.0};
	float	Fosc_S_code[32]     = {0.0};
	float   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;
	float   tmeas             = 0;

	
	i = 0;
	Fosc_S_code[i] =  0; Fosc_S_TrimWt[i] =   0.00;       i++;     //0 (0 link trimmed)
	Fosc_S_code[i] =  1; Fosc_S_TrimWt[i] =   1.50;     i++;     //0 (1 link trimmed--> 0.0%)
	Fosc_S_code[i] =  2; Fosc_S_TrimWt[i] =   3.00;    i++;     //0 (1 link trimmed--> 8.0%)
	Fosc_S_code[i] =  3; Fosc_S_TrimWt[i] =   4.65;    i++;     //0 (2 link trimmed--> 12.0%)
	Fosc_S_code[i] =  4; Fosc_S_TrimWt[i] =   6.00;   i++;     //0 (1 link trimmed--> 16.0%)
	Fosc_S_code[i] =  5; Fosc_S_TrimWt[i] =   7.50;  i++;     //0 (2 link trimmed--> 20.0%)
	Fosc_S_code[i] =  6; Fosc_S_TrimWt[i] =   9.20;  i++;     //0 (2 link trimmed--> 24.0%)
	Fosc_S_code[i] =  7; Fosc_S_TrimWt[i] =   10.6;   i++;     //0 (3 link trimmed--> 28.0%)
	Fosc_S_code[i] =  8; Fosc_S_TrimWt[i] =   12.0;   i++;     //0 (1 link trimmed-->  -32%)
	Fosc_S_code[i] =  9; Fosc_S_TrimWt[i] =   13.5;   i++;     //0 (2 link trimmed-->  -28%)
	Fosc_S_code[i] = 10; Fosc_S_TrimWt[i] =   15.0;   i++;     //0 (2 link trimmed-->  -24%)
	Fosc_S_code[i] = 11; Fosc_S_TrimWt[i] =   16.8;   i++;     //0 (3 link trimmed-->  -20%)
	Fosc_S_code[i] = 12; Fosc_S_TrimWt[i] =   18.0;   i++;     //0 (2 link trimmed-->  -16%)
	Fosc_S_code[i] = 13; Fosc_S_TrimWt[i] =   19.8;    i++;     //0 (3 link trimmed-->  -12%)
	Fosc_S_code[i] = 14; Fosc_S_TrimWt[i] =   21.1;    i++;     //0 (3 link trimmed-->  -8%)
	Fosc_S_code[i] = 15; Fosc_S_TrimWt[i] =   22.8;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 16; Fosc_S_TrimWt[i] =   23.9;       i++;     //0 (0 link trimmed)
	Fosc_S_code[i] = 17; Fosc_S_TrimWt[i] =   25.52;     i++;     //0 (1 link trimmed--> 0.0%)
	Fosc_S_code[i] = 18; Fosc_S_TrimWt[i] =   26.93;    i++;     //0 (1 link trimmed--> 8.0%)
	Fosc_S_code[i] = 19; Fosc_S_TrimWt[i] =   28.26;    i++;     //0 (2 link trimmed--> 12.0%)
	Fosc_S_code[i] = 20; Fosc_S_TrimWt[i] =   29.60;   i++;     //0 (1 link trimmed--> 16.0%)
	Fosc_S_code[i] = 21; Fosc_S_TrimWt[i] =   31.45;  i++;     //0 (2 link trimmed--> 20.0%)
	Fosc_S_code[i] = 22; Fosc_S_TrimWt[i] =   32.82;  i++;     //0 (2 link trimmed--> 24.0%)
	Fosc_S_code[i] = 23; Fosc_S_TrimWt[i] =   34.30;   i++;     //0 (3 link trimmed--> 28.0%)
	Fosc_S_code[i] = 24; Fosc_S_TrimWt[i] =   36.00;   i++;     //0 (1 link trimmed-->  -32%)
	Fosc_S_code[i] = 25; Fosc_S_TrimWt[i] =   37.10;   i++;     //0 (2 link trimmed-->  -28%)
	Fosc_S_code[i] = 26; Fosc_S_TrimWt[i] =   38.75;   i++;     //0 (2 link trimmed-->  -24%)
	Fosc_S_code[i] = 27; Fosc_S_TrimWt[i] =   40.20;   i++;     //0 (3 link trimmed-->  -20%)
	Fosc_S_code[i] = 28; Fosc_S_TrimWt[i] =   41.40;   i++;     //0 (2 link trimmed-->  -16%)
	Fosc_S_code[i] = 29; Fosc_S_TrimWt[i] =   43.00;    i++;     //0 (3 link trimmed-->  -12%)
	Fosc_S_code[i] = 30; Fosc_S_TrimWt[i] =   44.50;    i++;     //0 (3 link trimmed-->  -8%)
	Fosc_S_code[i] = 31; Fosc_S_TrimWt[i] =   46.00;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 32; Fosc_S_TrimWt[i] =  -1.150;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 33; Fosc_S_TrimWt[i] =  -2.600;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 34; Fosc_S_TrimWt[i] =  -4.200;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 35; Fosc_S_TrimWt[i] =  -5.700;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 36; Fosc_S_TrimWt[i] =  -7.150;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 37; Fosc_S_TrimWt[i] =  -8.800;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 38; Fosc_S_TrimWt[i] =  -10.40;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 39; Fosc_S_TrimWt[i] =  -11.80;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 40; Fosc_S_TrimWt[i] =  -13.44;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 41; Fosc_S_TrimWt[i] =  -15.00;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 42; Fosc_S_TrimWt[i] =  -16.50;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 43; Fosc_S_TrimWt[i] =  -18.20;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 44; Fosc_S_TrimWt[i] =  -19.60;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 45; Fosc_S_TrimWt[i] =  -21.15;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 46; Fosc_S_TrimWt[i] =  -22.62;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 47; Fosc_S_TrimWt[i] =  -24.30;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 48; Fosc_S_TrimWt[i] =  -25.42;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 49; Fosc_S_TrimWt[i] =  -27.00;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 50; Fosc_S_TrimWt[i] =  -28.50;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 51; Fosc_S_TrimWt[i] =  -30.00;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 52; Fosc_S_TrimWt[i] =  -31.60;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 53; Fosc_S_TrimWt[i] =  -33.22;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 54; Fosc_S_TrimWt[i] =  -34.80;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 55; Fosc_S_TrimWt[i] =  -36.40;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 56; Fosc_S_TrimWt[i] =  -37.85;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 57; Fosc_S_TrimWt[i] =  -39.55;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 58; Fosc_S_TrimWt[i] =  -41.20;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 59; Fosc_S_TrimWt[i] =  -42.78;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 60; Fosc_S_TrimWt[i] =  -43.78;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 61; Fosc_S_TrimWt[i] =  -45.30;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 62; Fosc_S_TrimWt[i] =  -47.00;    i++;     //0 (4 link trimmed-->  -4%)
	Fosc_S_code[i] = 63; Fosc_S_TrimWt[i] =  -48.85;    i++;     //0 (4 link trimmed-->  -4%)

	startbit = 64;
	
	Fosc_New_Target_S = 100000;
	Fosc_TrCode_S  = 0;
	Fosc_BitCode_S1 = 0;
	Fosc_ExpChg = 0;


	for(i=0;i<80;i++)
	{
		TrimRegisterTemp[i] = g_S_TrimRegister[i];
	}


	// Open all relays //
	Initialize_Relays();

	Load_100Khz_Pulses();

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
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_30_MA);
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

	//Setup TMU on Buffer of HSG pin.
	tmu_6->close_relay(TMU_HIZ_DUT4); 
	tmu_6->start_trigger_setup(8.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(8.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K7_IS_SPI_TB);       //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		 //Disconnect DVI_13_1 from IS.
	Close_relay(K2_HSG_SPI_TB);      //disconect OVI_1_0 from HSG.
	Open_relay(K1_HSG_SPI_RB);       //Keep Kelvin on HSG
	Close_relay(K5_HSG_SPI_TB);      //Connect HSG to buffer 
	Close_relay(K3_B_SPI_TB);		 //Connect 2nF to B
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Close_relay(K7_DDD_TB);          //Connect DDD_7_7 to FW.
	Close_relay(K1_FW_SPI_TB);       //Disconnect OVI from FW.
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 

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

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(10);

	//Clock FW with 10Khz pulses.
	Run_100Khz_Pulses();
	wait.delay_10_us(10);

	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1, VOLT_5_RANGE);
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

	//ZTMC_Driver_en & ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_sig_EN and Core_en.  Dont turn on B driver because of noise.
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZOpenDrain<1> & ZTMC_Dsbl_DaliCk2
	//0x00 0x60 write 0x02 0x40
	DSM_I2C_Write('w', g_TEST_CTRL1, 0x4002);

	//TEST_CTRL3[12]=1 && TEST_CTRL3[11:0] = 4095
	//0x00 0x64 write 0xFF 0x1F
	DSM_I2C_Write('w', 0x64, 0x1FFF);

	//TEST_CTRL4[5]=1 && TEST_CTRL4[4:0] = 16==> Jitter Average.
	//0x00 0x66 write 0x30 0x00
	DSM_I2C_Write('w', g_TEST_CTRL4, 0x0030);

	if(g_ZffOption_B19_20_S != 0)
	{
		//EEprom T[19]= 0, T[20] = 0 to turn off Feed Forward function.
		//Need to program these two bits back if FeedFoward option is needed.
		Set_EEprBit(EEpr_Array[1], 19-16, 0);
		Set_EEprBit(EEpr_Array[1], 20-16, 0);
	}

	
	//Set DL_on5D on HSG
	// 0x00 0x46 write 0x00 0x28
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2800);\
	//Loading previous trimming except T[19] & T[20] on E2 before performing the test.

	if (g_Trim_Enable_S != 0)
	{
		Program_All_TrimRegister();
	}

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

	//Monitor 100Khz switching on HSG pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(300e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		Fosc_pt_S = 1/tmeas;
	else
		Fosc_pt_S = 0.0;	

	g_Fosc_Pre = Fosc_pt_S;

if (g_Trim_Enable_S)
{

	// Fosc_S_Code //
	// Find which trim code will make Fosc_Pre closest to target //
	smallest_diff_val = 999999.9;
	smallest_diff_idx = 0;
	for (i=0; i<64; i++)
	{
		temp_1 = (Fosc_pt_S * (1 + (Fosc_S_TrimWt[i]/100)) -  Fosc_New_Target_S);
		if (temp_1 < 0)	// Get rid of negatives //
			temp_1 *= -1.0;
		if (temp_1 < smallest_diff_val)
		{
			smallest_diff_val = temp_1;
			smallest_diff_idx = i;
		}
	}


	//Manual forcing:
	//smallest_diff_idx = 63;

	Fosc_TrCode_S = Fosc_S_code[smallest_diff_idx];
	Fosc_ExpChg   = Fosc_S_TrimWt[smallest_diff_idx];

	Fosc_ExpValue = (Fosc_pt_S * (1 + (Fosc_S_TrimWt[smallest_diff_idx]/100)));

	TrimCode_To_TrimBit(Fosc_TrCode_S, "Fosc_S", 's');


	//Convert Trimcode to readable datalog file.
	if(Fosc_S_code[smallest_diff_idx]>=32 && Fosc_S_code[smallest_diff_idx] <= 63)
	{
		Fosc_BitCode_S1 = -1*Fosc_TrCode_S + 31; 
	}

	EEpr_Array[4] = EEpr_Array[4] | (Fosc_TrCode_S<<(64-startbit));

	Program_Single_TrimRegister(g_EEP_W_E8);
	
	if(g_ZffOption_B19_20_S == 1)
	{
		//Need to program these two bits back if FeedFoward option is needed.
		Set_EEprBit(EEpr_Array[1], 19-16, 1);
		Set_EEprBit(EEpr_Array[1], 20-16, 0);
	}
	else if(g_ZffOption_B19_20_S == 2)
	{
		//Need to program these two bits back if FeedFoward option is needed.
		Set_EEprBit(EEpr_Array[1], 19-16, 0);
		Set_EEprBit(EEpr_Array[1], 20-16, 1);
	}
	else if(g_ZffOption_B19_20_S == 3)
	{
		//Need to program these two bits back if FeedFoward option is needed.
		Set_EEprBit(EEpr_Array[1], 19-16, 1);
		Set_EEprBit(EEpr_Array[1], 20-16, 1);
	}

}
	tmeas = 0.0;
//Monitor 100Khz switching on HSG pin.	
	tmu_6->start_holdoff(15,TRUE);
	tmu_6->stop_holdoff(15,TRUE);
	wait.delay_10_us(10);
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(30);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(300e-6);	 
	tmeas/=15;
	if (tmeas != 0)
		Fosc_prg_S = 1/tmeas;
	else
		Fosc_prg_S = 0.0;	
	if(Fosc_pt_S != 0)
	{
		Fosc_PrgChg = 100*(Fosc_prg_S - Fosc_pt_S) / Fosc_pt_S;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

	//Reset DDD low level to 0V.
	ddd_7->ddd_set_lo_level(0.0);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(10);

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

	Open_relay(K7_IS_SPI_TB);         //Disconnect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		  //Reconnect DVI_13_1 to IS.
	Open_relay(K2_HSG_SPI_TB);        //Keep OVI_1_0 on HSG.
	Open_relay(K1_HSG_SPI_RB);        //Disconnect pullup R from HSG. 
	Open_relay(K5_HSG_SPI_TB);        //Disconnect HSG from buffer 
	Open_relay(K3_B_SPI_TB);		  //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K5_TMU_TB);           //DisconnectTMU_HIZ_3 from FW.
	Open_relay(K7_DDD_TB);           //Disconnect DDD_7_7 from FW.
	Open_relay(K1_FW_SPI_TB);        //Reconnect OVI to FW.
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 
	tmu_6->open_relay(TMU_HIZ_DUT4); 
	wait.delay_10_us(250);

	PiDatalog(func, A_Fosc_pt_S,		  Fosc_pt_S,               26, POWER_KILO);
	
	if (g_Trim_Enable_S)
	{
		PiDatalog(func, A_Fosc_target_S,     Fosc_New_Target_S,           26, POWER_KILO);
		PiDatalog(func, A_Fosc_TrCode_S,     Fosc_TrCode_S,           26, POWER_UNIT);
		PiDatalog(func, A_Fosc_BitCode_S,    Fosc_BitCode_S1,           26, POWER_UNIT);
		PiDatalog(func, A_Fosc_ExpChg_S,     Fosc_ExpChg,             26, POWER_UNIT);
		PiDatalog(func, A_Fosc_Exp_Value,    Fosc_ExpValue,           26, POWER_KILO);
		PiDatalog(func, A_Eetr64_VCO0_S,    g_S_TrimRegisterTemp[64],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr65_VCO1_S,    g_S_TrimRegisterTemp[65],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr66_VCO2_S,    g_S_TrimRegisterTemp[66],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr67_VCO3_S,    g_S_TrimRegisterTemp[67],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr68_VCO4_S,    g_S_TrimRegisterTemp[68],    26, POWER_UNIT);
		PiDatalog(func, A_Eetr69_VCO5_S,    g_S_TrimRegisterTemp[69],    26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,         EEpr_Array[4],          26, POWER_UNIT);
		PiDatalog(func, A_Fosc_prg_S,         Fosc_prg_S,              26, POWER_KILO);
		PiDatalog(func, A_Fosc_prgchg_S,      Fosc_PrgChg,             26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_Fosc_Pst,         Fosc_prg_S,              26, POWER_KILO);

	}


}
