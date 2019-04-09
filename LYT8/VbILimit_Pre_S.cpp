//==============================================================================
// VbILimit_Pre_S.cpp (User function)
// 
//    void VbILimit_Pre_S_user_init(test_function& func)
//    void VbILimit_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "VbILimit_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VbILimit_Pre_S_user_init(test_function& func)
{
	VbILimit_Pre_S_params *ours;
    ours = (VbILimit_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VbILimit_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VbILimit_Pre_S_params *ours;
    ours = (VbILimit_Pre_S_params *)func.params;

		gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VbIlim_Pre_S, gFuncNum, 27, POWER_UNIT);

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
	float VbIlim_pt_S     = 0;
	float VbIlim_prg_S    = 0;
	float VbIlim_Target_S = g_VbIlim_Target_S_Trimops;//82e-3; 
	if(g_Device_ID_S == 6154)
	{
		//VbIlim_Target_S = 160e-3; //Taken care by trimops.
	}
	int VbIlim_TrCode_S   = 0;
	int VbIlim_BitCode_S  = 0;
	int Eetr42_BILIM0_S    = 0;
	int Eetr43_BILIM1_S    = 0;
	int Eetr44_BILIM2_S    = 0;
	int Eetr45_BILIM3_S    = 0;
	int Eetr46_BILIM4_S    = 0;
	
	
	float VbIlim_Sim_S     = 0;
	float VbIlim_Sim_Chg_S = 0;
	float VbIlim_ExpChg    = 0;
	float VbIlim_ExpValue  = 0;
	float VbIlim_PrgChg    = 0;
	float VbIlim_pst_S     = 0;
	float VbIlim_Pre_TT    = 0;

Pulse pulse;

	//Trimcode & bit weights.
	float	VbIlim_S_TrimWt[32]   = {0.0};
	float	VbIlim_S_code[32]     = {0.0};
	double   smallest_diff_val = 999999.9;
	int     smallest_diff_idx = 0;
	float   temp_1            = 0;

	double VbIlim_TH = 0;
	float j = 0;
	float delta = 0;
	int   startbit = 32;

	//The trim weight will be updated soon.
	i = 0;
	VbIlim_S_code[i] =  0;  VbIlim_S_TrimWt[i] =      0;   i++;     
	VbIlim_S_code[i] =  1;  VbIlim_S_TrimWt[i]  =  -1.60;  i++;     
	VbIlim_S_code[i] =  2;  VbIlim_S_TrimWt[i]  =  -3.20;  i++;    
	VbIlim_S_code[i] =  3;  VbIlim_S_TrimWt[i]  =  -4.80;  i++;    
	VbIlim_S_code[i] =  4;  VbIlim_S_TrimWt[i]  =  -6.40;  i++;     
	VbIlim_S_code[i] =  5;  VbIlim_S_TrimWt[i]  =  -7.60;  i++;     
	VbIlim_S_code[i] =  6;  VbIlim_S_TrimWt[i]  =  -8.20;  i++;     
	VbIlim_S_code[i] =  7;  VbIlim_S_TrimWt[i]  =  -9.80; i++;     
	VbIlim_S_code[i] =  8;  VbIlim_S_TrimWt[i]  =  -11.40;   i++;     
	VbIlim_S_code[i] =  9;  VbIlim_S_TrimWt[i]  =  -13.00;  i++;     
	VbIlim_S_code[i] =  10; VbIlim_S_TrimWt[i]  =  -14.60;  i++;    
	VbIlim_S_code[i] =  11; VbIlim_S_TrimWt[i]  =  -16.20;  i++;    
	VbIlim_S_code[i] =  12; VbIlim_S_TrimWt[i]  =  -17.80;  i++;     
	VbIlim_S_code[i] =  13; VbIlim_S_TrimWt[i]  =  -19.40;  i++;     
	VbIlim_S_code[i] =  14; VbIlim_S_TrimWt[i]  =  -21.00;  i++;     
	VbIlim_S_code[i] =  15; VbIlim_S_TrimWt[i]  =  -22.60; i++;  
	VbIlim_S_code[i] =  16;  VbIlim_S_TrimWt[i] =    1.60;   i++;     
	VbIlim_S_code[i] =  17;  VbIlim_S_TrimWt[i]  =   3.20;  i++;     
	VbIlim_S_code[i] =  18;  VbIlim_S_TrimWt[i]  =   4.80;  i++;    
	VbIlim_S_code[i] =  19;  VbIlim_S_TrimWt[i]  =   6.40;  i++;    
	VbIlim_S_code[i] =  20;  VbIlim_S_TrimWt[i]  =   7.64;  i++;     
	VbIlim_S_code[i] =  21;  VbIlim_S_TrimWt[i]  =   8.20;  i++;     
	VbIlim_S_code[i] =  22;  VbIlim_S_TrimWt[i]  =   11.40;  i++;     
	VbIlim_S_code[i] =  23;  VbIlim_S_TrimWt[i]  =   13.00; i++;     
	VbIlim_S_code[i] =  24;  VbIlim_S_TrimWt[i]  =   14.60;   i++;     
	VbIlim_S_code[i] =  25;  VbIlim_S_TrimWt[i]  =   16.20;  i++;     
	VbIlim_S_code[i] =  26; VbIlim_S_TrimWt[i]  =   17.80;  i++;    
	VbIlim_S_code[i] =  27; VbIlim_S_TrimWt[i]  =   19.40;  i++;    
	VbIlim_S_code[i] =  28; VbIlim_S_TrimWt[i]  =   21.10;  i++;     
	VbIlim_S_code[i] =  29; VbIlim_S_TrimWt[i]  =   22.60;  i++;     
	VbIlim_S_code[i] =  30; VbIlim_S_TrimWt[i]  =   24.60;  i++;     
	VbIlim_S_code[i] =  31; VbIlim_S_TrimWt[i]  =   25.60; i++;  

	startbit = 32;
	
	// Open all relays //
	Initialize_Relays();

	Load_VbIlim_Pattern();

	Gage_ChanAB_Setup_S2(0.05, GAGE_PM_1_V, GAGE_PM_10_V, 200e6);

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
	Open_relay(K2_DDD_TB);          //K2_DDD is connected to IS by default.
	Open_relay(K6_IS_SPI_IB);       //Use DDD_7_2 to connect to Mosfet Gate to control the IS ramp.
	Close_relay(K1_IS_SPI_TB);      //Disconnect DVI_13_1 from IS pin.
	Open_relay(K5_IS_SPI_IB);       //Make sure IS buffer output not connecting to IS pin.
	Open_relay(K2_IS_BUFF_TB);      //Do not connect IS_Boost_Comp_Out to IS pin yet.
	Close_relay(K2_HSG_SPI_TB);     //Disconnect OVI_1_0 from HSG
	Close_relay(K3_HSG_SPI_TB);     //Connect 2nF to HSG

	Close_relay(K2_B_SPI_TB);       //Disconnect OVI_3_1 from B.
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
	Close_relay(K1_FW_SPI_TB);      //Disconnect OVI from FW pin.
	Close_relay(K7_DDD_TB);         //connect DDD to FW
	Close_relay(K1_DDD_TB);         //connect DDD_7_1 to Boost Current Limit IB

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

	FB_ovi3->set_current(FB_ch, 10e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 	
	wait.delay_10_us(10);

	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_5_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_5_RANGE); 
	wait.delay_10_us(200);

	//Set OVI1_2 to 0V (POS IN OF boost current limit integrator in the IB)
	ovi_1->set_current(OVI_CHANNEL_2, 10E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_2, 0, VOLT_1_RANGE);

	//Set OVI1_4 to 0V (OVI_1_4-->1K->Mosfet--> IN- of boost current limit integrator in the IB)
	ovi_1->set_current(OVI_CHANNEL_4, 10E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_4, 0, VOLT_5_RANGE);



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
	
	//ZTMC_ana_EN and Core_en==> HSG driver is not ON.
	//0x00 0x40 write 0x05 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0005);


	//DbILimit5D
	//0x00 0x42 write 0x1D
	DSM_I2C_Write('b', g_SIG_CTRL, 0x1D);

	//ZTMC_Bon_FBin
	//0x00 0x60 write 0x18 0xb0  
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xb018);

	if (g_Burn_Enable_S)
	{
		Program_All_TrimRegister();
	}

	Open_relay(K1_IS_BUFF_TB);      //Connect IS to Digitizer A buffer
	Close_relay(K2_IS_BUFF_TB);      //Connect IS to K1_IS_BuffA
	delay(3);

	FB_ovi3->set_voltage(FB_ch, 3, VOLT_5_RANGE); // DVI_11_0
	delay(1);

	ovi_1->set_current(OVI_CHANNEL_4, 0.5E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_4, -1, VOLT_20_RANGE);
	delay(5);

	//Need some offset so the Ramp starts at 0V.
	ovi_1->set_current(OVI_CHANNEL_2, 10E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_2, 0.00, VOLT_1_RANGE);
	delay(2);

	//Note:  Connecting K1_IS_Buffer/K2_IS_Buffer causes glitches on IS pin.
	//       Unable to find a better place to place these two relays to avoid the glitches.
	//       Fortunately, the test is still working even with glitches due to the bounce of the relay pins.

	//Do not connect any relay yet.  Need to verify the Boost Current Limit IB first.


	Close_relay(K2_IS_BUFF_TB);      //Connect IS to K1_IS_BuffA
	Close_relay(K1_IS_BUFF_TB);      //Connect IS to Digitizer A buffer
	Close_relay(K1_DigA_TB);        //Connect digitizer A to IS buffer
	Close_relay(K5_B_SPI_TB);        //connect B to Buffer.
	wait.delay_10_us(250);

	FB_ovi3->set_voltage(FB_ch, 3, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(50);
	
	VbIlim_TH = 0;
	float vbilim_pre_array[30] = {0};


	for(i=0;i<5;i++)
	{
		FB_ovi3->set_voltage(FB_ch, 0, VOLT_5_RANGE); // DVI_11_0
		wait.delay_10_us(50);
		Gage_Find_VbIlim_TH(&VbIlim_TH);
		//wait.delay_10_us(20);
		VbIlim_pt_S = VbIlim_TH;
		vbilim_pre_array[i] = VbIlim_TH;
		FB_ovi3->set_voltage(FB_ch, 3, VOLT_5_RANGE); // DVI_11_0
		wait.delay_10_us(50);
	}

	int array_index = 0;
	int num_loop = 5;
	//Eliminate 2 min and 2 max values.  After that, pre trim = average of the remaining values.
	for(i=0;i<2;i++)
	{
		min_value(vbilim_pre_array, array_index, num_loop); vbilim_pre_array[array_index] = 0;array_index = 0;
		max_value(vbilim_pre_array, array_index, num_loop); vbilim_pre_array[array_index] = 0;array_index = 0;
	}

	for(i=0;i<5;i++)
	{
		if(vbilim_pre_array[i] > 0) VbIlim_pt_S = vbilim_pre_array[i];
	}

	g_VbIlim_Pre = VbIlim_pt_S;

	if (g_Burn_Enable_S && g_OPCODE==4200)
	{

		// VbIlim_Pre can be either trimmed up or down only.  
		// VbIlim_TrCode_S //
		// Find which trim code will make VbIlim_Pre closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<32; i++)
		{
			temp_1 = (VbIlim_pt_S * (1 + (VbIlim_S_TrimWt[i]/100)) -  VbIlim_Target_S);
			if (temp_1 < 0)	// Get rid of negatives //
				temp_1 *= -1.0;
			if (temp_1 < smallest_diff_val)
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}


		//Manual forcing:
		//smallest_diff_idx = 1;

		VbIlim_TrCode_S   = VbIlim_S_code[smallest_diff_idx];
		VbIlim_ExpChg     = VbIlim_S_TrimWt[smallest_diff_idx];

		VbIlim_ExpValue = (VbIlim_pt_S * (1 + (VbIlim_S_TrimWt[smallest_diff_idx]/100)));

		TrimCode_To_TrimBit(VbIlim_TrCode_S, "VbILimit_S", 's');


		//////Convert Trimcode to readable datalog file.
		////if(VbIlim_S_code[smallest_diff_idx]>=0 && VbIlim_S_code[smallest_diff_idx] <= 15)
		////{
		////	VbIlim_BitCode_S = -1*VbIlim_TrCode_S; 
		////}
		////else
		////{
		////	VbIlim_BitCode_S = VbIlim_BitCode_S - 7;
		////}

		EEpr_Bank_S[E4] = EEpr_Bank_S[E4] | (VbIlim_TrCode_S<<(42-startbit));

		Program_Single_TrimRegister(g_EEP_W_E4);

		
	}
	wait.delay_10_us(500);

	FB_ovi3->set_voltage(FB_ch, 3, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(50);
	

	//Program Trim Register with new calculated bit combination.
	//Program_Trim_Register(g_S_TrimRegister);
	VbIlim_TH = 0;
	float vbilim_prg_array[30] = {0};



	g_Debug = 0;
	for(i=0;i<5;i++)
	{
		FB_ovi3->set_voltage(FB_ch, 0, VOLT_5_RANGE); // DVI_11_0
		wait.delay_10_us(50);
		Gage_Find_VbIlim_TH(&VbIlim_TH);
		g_Debug = 0;
		//wait.delay_10_us(20);
		VbIlim_prg_S = VbIlim_TH;
		vbilim_prg_array[i] = VbIlim_TH;
		FB_ovi3->set_voltage(FB_ch, 3, VOLT_5_RANGE); // DVI_11_0
		wait.delay_10_us(50);
	}

	array_index = 0;
	num_loop = 5;
	//Eliminate 2 min and 2 max values.  After that, pre trim = average of the remaining values.
	for(i=0;i<2;i++)
	{
		min_value(vbilim_prg_array, array_index, num_loop); vbilim_prg_array[array_index] = 0;array_index = 0;
		max_value(vbilim_prg_array, array_index, num_loop); vbilim_prg_array[array_index] = 0;array_index = 0;
	}

	for(i=0;i<5;i++)
	{
		if(vbilim_prg_array[i] > 0) VbIlim_prg_S = vbilim_prg_array[i];
	}


	if(VbIlim_pt_S != 0)
	{
		VbIlim_PrgChg = 100*(VbIlim_prg_S - VbIlim_pt_S) / VbIlim_pt_S;
	}
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	//Disable DSM I2C before powerdown.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	Stop_VbIlim_Pattern();

	//ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.

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

	ovi_1->set_current(OVI_CHANNEL_4, 15E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_4, 0, VOLT_20_RANGE);
	delay(5);

	ovi_1->set_current(OVI_CHANNEL_2, 10E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_2, 0.0, VOLT_1_RANGE);
	delay(2);


	//Set OVI1_2 to 0V (POS IN OF boost current limit integrator in the IB)
	ovi_1->set_current(OVI_CHANNEL_2, 0.1E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_2, 0, VOLT_1_RANGE);

	//Set OVI1_4 to 0V (OVI_1_4-->1K->Mosfet--> IN- of boost current limit integrator in the IB)
	ovi_1->set_current(OVI_CHANNEL_4, 0.1E-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_4, 0, VOLT_20_RANGE);

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
	Open_relay(K1_DDD_TB);           //Disconnect DDD_7_1 from Boost Current Limit IB
	Open_relay(K1_IS_SPI_TB);		 //Reconnect DVI to IS pin.
	Open_relay(K7_IS_SPI_TB);        //Disconnect 1K from IS to GND
	Open_relay(K3_IS_SPI_IB);        //Disconnect Resistor divider on IS buffer Module.
	Open_relay(K5_IS_SPI_IB);        //Disconnect IS buffer output from IS pin.
	Open_relay(K2_IS_BUFF_TB);      // Disconnect IS to K1_IS_BuffA
	Open_relay(K1_IS_BUFF_TB);       //Disconnect Digitizer A from U21/ IS buffer to Digitizer A
	Open_relay(K1_DigA_TB);          //Disconnect digitizer A to IS buffer
	Open_relay(K5_HSG_SPI_TB);       //Disconnect Buffer/HSG.
	Open_relay(K_CHANB_TB);           //Disconnect HSG from digitizer B.
	Open_relay(K4_IS_SPI_IB);        //Reconnect GND to GND_ANA on IS buffer.

	Open_relay(K2_DDD_TB);          //K2_DDD is connected to IS by default.
	Open_relay(K6_IS_SPI_IB);       //Disconnect Mosfet Gate from B on Boost Current Limit IB. 
	Open_relay(K5_IS_SPI_IB);       //Make sure IS buffer output not connecting to IS pin.
	Open_relay(K2_IS_BUFF_TB);      //Disconnect IS_Boost_Comp_Out to IS pin.
	Open_relay(K2_HSG_SPI_TB);     //Reconnect OVI_1_0 from HSG
	Open_relay(K3_HSG_SPI_TB);      //Disconnect 2nF from HSG
	Open_relay(K5_IS_SPI_IB);
	Open_relay(K2_B_SPI_TB);       //Reconnect OVI_3_1 to B.
	Open_relay(K3_B_SPI_TB);		//Disconnect 2nF from B
	Open_relay(K1_FW_SPI_TB);      //Reconnect OVI to FW pin.
	Open_relay(K7_DDD_TB);         //Disconnect DDD from FW
	Open_relay(K5_B_SPI_TB);        //Disconnect B from Buffer.
//Switch GNDs on TMT LB not TB
	mux_20->open_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->open_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	PiDatalog(func, A_VbIlim_pt_S,			VbIlim_pt_S,			  26, POWER_MILLI);
	
	if (g_Burn_Enable_S)
	{
		PiDatalog(func, A_VbIlim_target_S,      VbIlim_Target_S,       26, POWER_MILLI);
		PiDatalog(func, A_VbIlim_TrCode_S,      VbIlim_TrCode_S,       26, POWER_UNIT);
		PiDatalog(func, A_VbIlim_BitCode_S,     VbIlim_BitCode_S,      26, POWER_UNIT);
		PiDatalog(func, A_VbIlim_ExpChg_S,      VbIlim_ExpChg,         26, POWER_UNIT);
		PiDatalog(func, A_VbIlim_Exp_Value,     VbIlim_ExpValue,       26, POWER_MILLI);
		PiDatalog(func, A_Eetr42_BILIM0_S,    g_S_TrimRegisterTemp[42], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr43_BILIM1_S,    g_S_TrimRegisterTemp[43], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr44_BILIM2_S,    g_S_TrimRegisterTemp[44], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr45_BILIM3_S,    g_S_TrimRegisterTemp[45], 26, POWER_UNIT);
		PiDatalog(func, A_Eetr46_BILIM4_S,    g_S_TrimRegisterTemp[46], 26, POWER_UNIT);
		PiDatalog(func, A_Bin2Dec1_S,		EEpr_Bank_S[E4],		  26, POWER_UNIT);	
		PiDatalog(func, A_VbIlim_prg_S,         VbIlim_prg_S,          26, POWER_MILLI);
		PiDatalog(func, A_VbIlim_prgchg_S,      VbIlim_PrgChg,         26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_VbIlim_Pst,         VbIlim_prg_S,          26, POWER_MILLI);

	}

}
