//==============================================================================
// CP_Pre_S.cpp (User function)
// 
//    void CP_Pre_S_user_init(test_function& func)
//    void CP_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "CP_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CP_Pre_S_user_init(test_function& func)
{
	CP_Pre_S_params *ours;
    ours = (CP_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CP_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    CP_Pre_S_params *ours;
    ours = (CP_Pre_S_params *)func.params;

	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_CP_Pre_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_S is not set //
	if (g_Burn_Enable_S == 0 && g_GRR_Enable == 0)
		return;

	if (g_OPCODE==4250 || g_OPCODE==4300 || g_OPCODE==4500)
		return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i              = 0;
	int   WordArray[16]  = {0};
	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	// Test Names //
	float CP_IS_pt_S     = 0;
	float CP_IS_prg_S    = 0;
	float CP_IS_Target_S = g_CP_IS_Target_S_Trimops;
	if(g_Device_ID_S == 6160||g_Device_ID_S == 6159||g_Device_ID_S==6155)
	{
		//CP_IS_Target_S = 201e-3; 
	}
	else
	{
		//CP_IS_Target_S = 120e-3; 
	}
	int CP_IS_TrCode_S   = 0;
	int CP_IS_BitCode_S  = 0;
	int Eetr23_Tcp0_S    = 0;
	int Eetr24_Tcp1_S    = 0;
	int Eetr25_Tcp2_S    = 0;
	int Eetr26_Tcp3_S    = 0;
	
	
	float CP_IS_Sim_S     = 0;
	float CP_IS_Sim_Chg_S = 0;
	float CP_IS_ExpChg    = 0;
	float CP_IS_ExpValue  = 0;
	float CP_IS_PrgChg    = 0;
	float CP_IS_pst_S     = 0;
	float CP_IS_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	CP_IS_S_TrimWt[16]   = {0.0};
	float	CP_IS_S_code[16]     = {0.0};
	double   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;

	double CP_IS_TH = 0;
	double CP_BOFF_TH     = 0;
	double CP_PFOFF_TH    = 0;
	float j = 0;
	float delta = 0;
	int   startbit = 0;

	//The trim weight will be updated soon.
	i = 0;
	CP_IS_S_code[i] =  0;  CP_IS_S_TrimWt[i] =      0;   i++;     
	CP_IS_S_code[i] =  1;  CP_IS_S_TrimWt[i]  =  -2.80;  i++;     
	CP_IS_S_code[i] =  2;  CP_IS_S_TrimWt[i]  =  -5.60;  i++;    
	CP_IS_S_code[i] =  3;  CP_IS_S_TrimWt[i]  =  -8.10;  i++;    
	CP_IS_S_code[i] =  4;  CP_IS_S_TrimWt[i]  =  -10.46;  i++;     
	CP_IS_S_code[i] =  5;  CP_IS_S_TrimWt[i]  =  -12.70;  i++;     
	CP_IS_S_code[i] =  6;  CP_IS_S_TrimWt[i]  =  -14.70;  i++;     
	CP_IS_S_code[i] =  7;  CP_IS_S_TrimWt[i]  =  -16.70; i++;     
	CP_IS_S_code[i] =  8;  CP_IS_S_TrimWt[i]  =   2.80;   i++;     
	CP_IS_S_code[i] =  9;  CP_IS_S_TrimWt[i]  =   6.00;  i++;     
	CP_IS_S_code[i] =  10; CP_IS_S_TrimWt[i]  =   9.60;  i++;    
	CP_IS_S_code[i] =  11; CP_IS_S_TrimWt[i]  =   13.00;  i++;    
	CP_IS_S_code[i] =  12; CP_IS_S_TrimWt[i]  =   17.10;  i++;     
	CP_IS_S_code[i] =  13; CP_IS_S_TrimWt[i]  =   21.60;  i++;     
	//CP_IS_S_code[i] =  14; CP_IS_S_TrimWt[i]  =   21.60;  i++;     
	//CP_IS_S_code[i] =  15; CP_IS_S_TrimWt[i]  =   21.60; i++;  

	startbit = 16;

	// Open all relays //
	Initialize_Relays();

	Gage_ChanAB_Setup_S(0.17, GAGE_PM_500_MV, GAGE_PM_20_V);

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
	//HSG:==> 5V/30mA since it needs to be in open drain mode.
	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = 0V/30mA
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 
	//IS = 100mV/200mA
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);				
	IS_dvi2k->set_current(IS_ch, 2e-6, RANGE_20_MA);
	//SDA will be at 3.3V/30mA for I2C
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_5_RANGE); 
	//SCL will be at 3.3V/30mA for I2C
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_5_RANGE); 
	//BPS will be Hiz
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	//HBP will be Hiz.
	HBP_dvi2k->set_current(HBP_ch, 200e-6, RANGE_20_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);


	//Switch GNDs on TMT LB not TB
	mux_20->close_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->close_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	//Disable DSM I2C before connecting any relays.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K7_IS_SPI_TB);      //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		//Connect DVI to divider (1/3)
	Close_relay(K3_IS_SPI_IB);      //Connect Resistor divider on IS buffer Module.
	Open_relay(K2_IS_SPI_IB);      //Connect Resistor divider on IS buffer Module.
	Open_relay(K5_IS_SPI_IB);       //Do not connect IS buffer output to IS pin yet.
	Close_relay(K2_HSG_SPI_TB);     //Disconnect OVI_1_0 from HSG
	Open_relay(K3_HSG_SPI_TB);      //Disconnect 2nF from HSG
	Open_relay(K1_HSG_SPI_RB);      //Use pullup on HSG for open drain config.
	Close_relay(K2_B_SPI_TB);       //Disconnect OVI_3_1 from B.
	Close_relay(K3_B_SPI_TB);		//Connect 2nF to B
	Close_relay(K1_FW_SPI_TB);      //Disconnect OVI from FW pin.
	Close_relay(K7_DDD_TB);         //connect DDD to FW
	
	
	//Disconnect Pullup R from TS and UV pins
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

	FB_ovi3->set_current(FB_ch, 2e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	wait.delay_10_us(10);

	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_5_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_5_RANGE); 
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


	//ZTMC_driver_EN & ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)								  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);
	
	//Disable AutoRestart
	//0x00 0x44 write 0x00 0x01
	DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0100);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//ZTMC_ana_EN and Core_en==> Boost driver isn't turned on.
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZOpenDrain<0>,ZOpenDrain<1> 
	//0x00 0x60 write 0x02 0xC0 
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xE020);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//CORE_CTRL1
	//0x00 0x12 write 0x00
	//DSM_I2C_Write('b', g_CORE_CTRL1, 0x00); //CP @ 100%
	//DSM_I2C_Write('b', g_CORE_CTRL1, 0x01); //CP @ 85%
	//DSM_I2C_Write('b', g_CORE_CTRL1, 0x02); //CP @ 75%==> Not working on scoop & goop parts.
	DSM_I2C_Write('b', g_CORE_CTRL1, 0x03); //CP @ 60%



	//Dcp_comps_out
	//0x00 0x46 write 0x00 0xE8
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0xE800);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	Open_relay(K2_HSG_SPI_TB);      //Connect OVI_1_0 to HSG
	Close_relay(K1_HSG_SPI_RB);      //Use pullup on HSG for open drain config.
	wait.delay_10_us(250);



	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.5, VOLT_1_RANGE); 

	IS_dvi2k->set_current(IS_ch, 2e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);
	wait.delay_10_us(10);

	//Note:  Connecting K1_IS_Buffer/K2_IS_Buffer causes glitches on IS pin.
	//       Unable to find a better place to place these two relays to avoid the glitches.
	//       Fortunately, the test is still working even with glitches due to the bounce of the relay pins.

	Close_relay(K5_IS_SPI_IB);       //Connect IS buffer output to IS pin.
	Close_relay(K7_IS_SPI_TB);        //Disconnect 1K from IS to GND
	Close_relay(K2_IS_BUFF_TB);      //Connect IS to K1_IS_BuffA
	Close_relay(K1_IS_BUFF_TB);      //Connect IS to Digitizer A buffer
	Close_relay(K1_DigA_TB);        //Connect digitizer A to IS buffer
	Close_relay(K5_HSG_SPI_TB);      //Connect Buffer/HSG.
	Close_relay(K_CHANB_TB);         //Connect Buffer Output HSG to digitizer B.
	Open_relay(K4_IS_SPI_IB);       //Remove GND from GND_ANA on IS buffer.
	wait.delay_10_us(250);

	if (g_Burn_Enable_S)
	{
		Program_All_TrimRegister();
	}
	CP_IS_TH = 0;

	g_Debug = 0;
		Gage_Find_CP(&CP_IS_TH, &CP_BOFF_TH, &CP_PFOFF_TH);
	g_Debug = 0;

	CP_IS_pt_S = CP_IS_TH;

	g_CP_IS_Pre = CP_IS_pt_S;

	if (g_Burn_Enable_S)
	{

		// CP_Pre can be either trimmed up or down only.  
		// CP_S_Code //
		// Find which trim code will make CP_Pre closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<13; i++)
		{
			temp_1 = (CP_IS_pt_S * (1 + (CP_IS_S_TrimWt[i]/100)) -  CP_IS_Target_S);
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

		CP_IS_TrCode_S   = CP_IS_S_code[smallest_diff_idx];
		CP_IS_ExpChg     = CP_IS_S_TrimWt[smallest_diff_idx];

		CP_IS_ExpValue = (CP_IS_pt_S * (1 + (CP_IS_S_TrimWt[smallest_diff_idx]/100)));

		TrimCode_To_TrimBit(CP_IS_TrCode_S, "CP_S", 's');


		//Convert Trimcode to readable datalog file.
		if(CP_IS_S_code[smallest_diff_idx]>=0 && CP_IS_S_code[smallest_diff_idx] <= 7)
		{
			CP_IS_BitCode_S = -1*CP_IS_TrCode_S; 
		}
		else
		{
			CP_IS_BitCode_S = CP_IS_BitCode_S - 7;
		}

		EEpr_Bank_S[E2] = EEpr_Bank_S[E2] | (CP_IS_TrCode_S<<(23-startbit));

		Program_Single_TrimRegister(g_EEP_W_E2);

	}
	wait.delay_10_us(500);
	CP_IS_TH = 0;

	Gage_Find_CP(&CP_IS_TH, &CP_BOFF_TH, &CP_PFOFF_TH);

	CP_IS_prg_S = CP_IS_TH;

	if(CP_IS_pt_S != 0)
	{
		CP_IS_PrgChg = 100*(CP_IS_prg_S - CP_IS_pt_S) / CP_IS_pt_S;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	//Disable DSM I2C before powerdown.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

	//Reset DDD low level to 0V.
	ddd_7->ddd_set_lo_level(0.0);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);

	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_10_RANGE); 

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
	Open_relay(K1_FW_SPI_TB);        //Reconnect OVI to FW pin.
	Open_relay(K7_DDD_TB);           //Disconnect DDD from FW
	Open_relay(K1_IS_SPI_TB);
	Open_relay(K7_IS_SPI_TB);        //Disconnect 1K from IS to GND
	Open_relay(K3_IS_SPI_IB);        //Disconnect Resistor divider on IS buffer Module.
	Open_relay(K5_IS_SPI_IB);        //Disconnect IS buffer output from IS pin.
	Open_relay(K2_IS_BUFF_TB);      // Disconnect IS to K1_IS_BuffA
	Open_relay(K1_IS_BUFF_TB);       //Disconnect Digitizer A from U21/ IS buffer to Digitizer A
	Open_relay(K1_DigA_TB);          //Disconnect digitizer A to IS buffer
	Open_relay(K5_HSG_SPI_TB);       //Disconnect Buffer/HSG.
	Open_relay(K_CHANB_TB);           //Disconnect HSG from digitizer B.
	Open_relay(K4_IS_SPI_IB);        //Reconnect GND to GND_ANA on IS buffer.

//Switch GNDs on TMT LB not TB
	mux_20->open_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->open_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	PiDatalog(func, A_CP_pt_S,			CP_IS_pt_S,			  26, POWER_MILLI);
	
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_CP_target_S,      CP_IS_Target_S,       26, POWER_MILLI);
		PiDatalog(func, A_CP_TrCode_S,      CP_IS_TrCode_S,       26, POWER_UNIT);
		PiDatalog(func, A_CP_BitCode_S,     CP_IS_BitCode_S,      26, POWER_UNIT);
		PiDatalog(func, A_CP_ExpChg_S,      CP_IS_ExpChg,         26, POWER_UNIT);
		PiDatalog(func, A_CP_Exp_Value,     CP_IS_ExpValue,       26, POWER_MILLI);
		PiDatalog(func, A_Eetr23_Tcp0_S,    g_S_TrimRegisterTemp[23], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr24_Tcp1_S,    g_S_TrimRegisterTemp[24], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr25_Tcp2_S,    g_S_TrimRegisterTemp[25], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr26_Tcp3_S,    g_S_TrimRegisterTemp[26], 26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,		EEpr_Bank_S[E2],		  26, POWER_UNIT);
		PiDatalog(func, A_CP_prg_S,         CP_IS_prg_S,          26, POWER_MILLI);
		PiDatalog(func, A_CP_prgchg_S,      CP_IS_PrgChg,         26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_CP_Pst,         CP_IS_prg_S,          26, POWER_MILLI);

	}


}
