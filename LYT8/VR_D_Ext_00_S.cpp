//==============================================================================
// VR_D_Ext_00_S.cpp (User function)
// 
//    void VR_D_Ext_00_S_user_init(test_function& func)
//    void VR_D_Ext_00_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "VR_D_Ext_00_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VR_D_Ext_00_S_user_init(test_function& func)
{
	VR_D_Ext_00_S_params *ours;
    ours = (VR_D_Ext_00_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VR_D_Ext_00_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VR_D_Ext_00_S_params *ours;
    ours = (VR_D_Ext_00_S_params *)func.params;

			gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VR_DE_00_S, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;


	if(g_TvrOption_B16_17_S != 0)
		return;

	//if (g_Fn_VADC_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int   i                 = 0;
	int   HBP_Internal      = 0;
	float j                 = 0.0;
	float temp              = 0.0;
	float VFB               = 0.0;
	float V_DDD_5K          = 0;
	float VA0_Dali254_5K    = 0;
	float VA1_Dali254_5K    = 0;
	float VA2_Dali254_5K    = 0;
	float VA3_Dali254_5K    = 0;
	float VA0_Dali35_5K     = 0;
	float VA1_Dali35_5K     = 0;
	float VA2_Dali35_5K     = 0;
	float VA3_Dali35_5K     = 0;
	float VA0_Dali0_5K      = 0;
	float VA1_Dali0_5K      = 0;
	float VA2_Dali0_5K      = 0;
	float VA3_Dali0_5K      = 0;
	float VA0_Dali254_7K    = 0;
	float VA1_Dali254_7K    = 0;
	float VA2_Dali254_7K    = 0;
	float VA3_Dali254_7K    = 0;
	float VA0_Dali35_7K     = 0;
	float VA1_Dali35_7K     = 0;
	float VA2_Dali35_7K     = 0;
	float VA3_Dali35_7K     = 0;
	float VA0_Dali0_7K      = 0;
	float VA1_Dali0_7K      = 0;
	float VA2_Dali0_7K      = 0;
	float VA3_Dali0_7K      = 0;
	float VA0_Dali254_9K    = 0;
	float VA1_Dali254_9K    = 0;
	float VA2_Dali254_9K    = 0;
	float VA3_Dali254_9K    = 0;
	float VA0_Dali35_9K     = 0;
	float VA1_Dali35_9K     = 0;
	float VA2_Dali35_9K     = 0;
	float VA3_Dali35_9K     = 0;
	float VA0_Dali0_9K      = 0;
	float VA1_Dali0_9K      = 0;
	float VA2_Dali0_9K      = 0;
	float VA3_Dali0_9K      = 0;
	float VA0_Dali254_13p5K = 0;
	float VA1_Dali254_13p5K = 0;
	float VA2_Dali254_13p5K = 0;
	float VA3_Dali254_13p5K = 0;
	float VA0_Dali35_13p5K  = 0;
	float VA1_Dali35_13p5K  = 0;
	float VA2_Dali35_13p5K  = 0;
	float VA3_Dali35_13p5K  = 0;
	float VA0_Dali0_13p5K   = 0;
	float VA1_Dali0_13p5K   = 0;
	float VA2_Dali0_13p5K   = 0;
	float VA3_Dali0_13p5K   = 0;
	float VR_Detect_S_TT    = 0;

	float VFB_Meas[5] = {0};


	
Pulse pulse;

	// Open all relays //
	Initialize_Relays();
	int StartAddr = 500;
	Load_FW_DDD_1_Pulse(StartAddr);

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
	//Do not Use DVI_9_1 on VR for this test.  Use DVI_9_0 instead.  
	VR_dvi->open_relay(CONN_FORCE1);
	VR_dvi->close_relay(CONN_SENSE1);
	wait.delay_10_us(250);
	//HSG needs to connect thru buffer then.
	HSG_ovi->set_current(HSG_ch, 3e-3, RANGE_3_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 0.1e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = 1.15V/30mA then sweep or binary search.
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
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
	HBP_dvi2k->set_current(HBP_ch, 0.0001e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VRstep_ch, 0.1e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//Switch GNDs on TMT LB not TB
	mux_20->close_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->close_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Secondary I2C to ready Secondary Die ID.
	BPS_dvi->open_relay(CONN_FORCE0);

	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG for Open Drain config later.
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 on B for Open Drain config later.
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Open_relay(K3_B_SPI_TB);		//Do not connect 2nF to B!
	Open_relay(K3_HSG_SPI_TB);      //Do not connect 2nF to HSG!
	Open_relay(K7_IS_SPI_TB);      //Connect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		//Disconnect DVI_13_1 from IS.
	Close_relay(K5_B_SPI_TB);       //Connect B to Buffer.
	Close_relay(K5_HSG_SPI_TB);     //Connect Buffer/HSG.
	Close_relay(K1_FW_SPI_TB);      //Disconnect OVI from FW pin.
	Close_relay(K7_DDD_TB);         //connect DDD to FW
	Close_relay(K6_VR_SPI_RB);      //Connect DVI_9_0 to VR thru Diode.  Prevent VR from drawing current from HBP


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

	//Keep FW @ 0V.
	ddd_7->ddd_run_pattern(510,540);  
	delay(1);


	//Tips.------------------------------------------------------------------------------------------
	//Power-up HBP with external voltage has different procedure from bench.
	//If directly setting HBP = 8V, VR = 8V and then HBP = HBP_P + 100mV, TM can't be accessed.
	//One get-around method is to power up VR = 15V first and wait until HBP regulates to HBP_P.
	//Then apply external voltage on HBP pin to HBP_P + 100mV. Next is to drop VR from 15V to 10V
	//-----------------------------------------------------------------------------------------------
	VR_dvi->set_current(VRstep_ch, 10e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_50_RANGE); 

	FB_ovi3->set_voltage(FB_ch, 1.0, VOLT_2_RANGE); 	
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VRstep_ch, 16, VOLT_50_RANGE);
	wait.delay_10_us(200);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);
	
	//Apply External HBP voltage: 13V/10mA
	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 13.0, VOLT_20_RANGE);
	delay(2);


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

	//ZTMC_Driver_En & ZTMC_Dsbl_FBshrt							  
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en (HSG is enabled)
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

	//ZTMC_AVR_tap
	//0x00 0x46 write 0x10 0x00
	DSM_I2C_Write('w', 0x46, 0x0010);

	//-------------------------------------------------------------------------------------------------------
	//Clock 1 pulse to FW and monitor FB voltage.  VFB indicates the 4 VR option settings.
	//Need to create datalog for these 4 FB measurements.
	//-------------------------------------------------------------------------------------------------------
	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	FB_ovi3->set_current(FB_ch, 0.0001e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(50);

	VFB_Meas[0] = FB_ovi3->measure_average(5);

	for(i=1;i<5;i++)
	{
		Run_FW_DDD_1_Pulse(StartAddr);
		wait.delay_10_us(50);
		VFB_Meas[i] = FB_ovi3->measure_average(5);
	}

	delay(1);

	//0x00 0x60 write 0x00 0xE0  ==> Open Drain on HSG & B & disable communication to reduce noise.
	DSM_I2C_Write('w', g_TEST_CTRL1, 0xC000);

	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_CURRENT);
	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 5.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	//DVR_dim_comps_out to HSG
	//0x00 0x46 write 0x00 0xd0
	DSM_I2C_Write('w', 0x46, 0xD000);

	//----------------------------------------------------------------------------------------------------------------
	//LightOff Mode
	//0x00 0x64 write 0x00 0x30
	DSM_I2C_Write('w', 0x64, 0x3000);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Ramp VR and observe output on Boost pin.
	VR_dvi->set_meas_mode(VR_ch, DVI_MEASURE_VOLTAGE);
	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);


	float VStart_BLO = 10.0;
	float VSet_BLO   = 20.0;
	float Vstep      = 50e-3;	
	float BLO_5K        = 0.0;
	float BLO_Skip_5K   = 0.0;
	
	//VR_Detect_B_Search(float &VB, float &VBSkip, float &VStart, float &Vstop, float &Vstep, char B_or_HSG, char Up_or_Dn)
	VR_Detect_B_Search(BLO_5K, BLO_Skip_5K, VStart_BLO, VSet_BLO, Vstep, 'H', 'U');
	delay(1);

	//-----------------------------------------------------------------------------------------------------------------------------
	//Deep Dim Mode
	//-----------------------------------------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Deep Dim Mode
	//0x00 0x64 write 0x00 0x50
	DSM_I2C_Write('w', 0x64, 0x5000);

	//Ramp VR and observe output on Boost pin.
	//VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);
	VR_dvi->set_voltage(VRstep_ch, 32, VOLT_50_RANGE);
	delay(10);

	float VStart_B   = 35.0;
	float VSet_B     = 20.0;
		  Vstep      = 50e-3;
	float B_5K       = 0.0;
	float B_Skip_5K  = 0.0;


	//VR_Detect_B_Search(float &VB, float &VBSkip, float &VStart, float &Vstop, float &Vstep, char B_or_HSG, char Up_or_Dn)
	VR_Detect_B_Search(B_5K, B_Skip_5K, VStart_B, VSet_B, Vstep, 'H', 'D');

	
	//------------------------------------------------------------------------------------------------------------
	//Measure A parameters --------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	// Disable FB short, enable driver and ZTMC_VR_Target
	//0x00 0x62 write 0x88 0x10
	DSM_I2C_Write('w', 0x62, 0x1088);
	// Enable HSG and B out and core_en
	//0x00 0x40 write 0x07 00
	DSM_I2C_Write('w', 0x40, 0x0007);

	// Bring out DVR_comps_out to B
	//0x00 0x42 write 0x06 0x00
	DSM_I2C_Write('w', 0x42, 0x0006);

	////This is to get out of Deep Dimming mode.
	DSM_I2C_Write('w', 0x64, 0x1FFF);

	//Enable ZTMC_VR_comps_link 
	//0x00 0x46 write 0x08 0x00
	DSM_I2C_Write('w', 0x46, 0x0008);

	//0x00 0x60 write 0x00 0xE0  ==> Open Drain on HSG & B to reduce noise.
	DSM_I2C_Write('w', 0x60, 0xC000);

	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	
	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 5.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	//Need to slowly ramp VR down to 10V. Else, VR causes glitch on HBP to get kicked out of TM.
	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);
	VR_dvi->set_voltage(VRstep_ch, 20, VOLT_50_RANGE);
	wait.delay_10_us(100);
	j = 20;
	while(j >= 10)
	{
		VR_dvi->set_voltage(VRstep_ch, j, VOLT_50_RANGE);
		wait.delay_10_us(2);
		j = j - 0.1;
	}
	VR_dvi->set_voltage(VRstep_ch, 10, VOLT_50_RANGE);	
	wait.delay_10_us(100);

	//Need to reduce FB voltage for option 44 due to VR threshold can be up to 60V.
	if(VFB_Meas[4] >= 0.2 && VFB_Meas[4] <= 0.5)
	{
		FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
		FB_ovi3->set_voltage(FB_ch, 0.8, VOLT_2_RANGE); 
		wait.delay_10_us(50);
		VFB = FB_ovi3->measure_average(5);
	}
	else
	{
		FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
		FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_2_RANGE); 
		wait.delay_10_us(50);
		VFB = FB_ovi3->measure_average(5);
	}

	//------------------------------------------------------------------
	//Search for B3_UVLO Threshold
	//------------------------------------------------------------------

	//Ramp VR and observe output on Boost pin.
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);
	VR_dvi->set_voltage(VRstep_ch,12, VOLT_50_RANGE);
	delay(100);
//pulse.do_pulse();
	j = 10.0;
	i = 0;
	float B3_UVLO_5K = 0.0;
	float V_Set =18;
	int Exit_loop = 0;
	float i_meas[1000] = {0.0};
	float v_step[1000] = {0.0};
	while(j < V_Set && Exit_loop < 1)
	{	
		VR_dvi->set_voltage(VRstep_ch, j+0.1, VOLT_50_RANGE);
		wait.delay_10_us(5);
		temp = B_ovi3->measure_average(5);
		i_meas[i] = temp;
		if(temp > 5e-3)
		{
				B3_UVLO_5K = VR_dvi->measure_average(5);
				Exit_loop = 1;
		}
		j=j+0.1;
		i++;
	}

	//-------------------------------------------------------------
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);
	VR_dvi->set_voltage(VRstep_ch, 15, VOLT_50_RANGE);
	delay(5);

////////////	/////*float VStart_B2         = 15.0;
////////////	////float VSet_B2           = 30.0;
////////////	////	  Vstep             = 50e-3;
////////////	////float B2_MaxState5K     = 0.0;
////////////	////float B1_FastUpdate_5K  = 0.0;*/
////////////
	//-------------------------------------------------------------------------------------------------------------
	//Searching for A parameters
	//--------------------------------------------------------------------------------------------------------------
	VR_dvi->set_current(VRstep_ch, 300e-3, RANGE_300_MA);
	VR_dvi->set_voltage(VRstep_ch, 13, VOLT_50_RANGE);
	delay(100);


	j = 15.0;

	float I_B[1000] = {0.0};
	float V_VR[1000] = {0.0};
	float VStart = 13;
	float Vstop = 49.8;
	float VstepSize  = 50.0e-3;
	float B2_MaxSate = 0.0;
	float B1_FastUpdate = 0.0;
	float A3_Target_VR = 0.0;
	float A2_FastUpdate = 0.0;
	float A1_MinState   = 0.0;
	float A_Skipping    = 0.0;

	

//void VR_Detect_A_Search(float &VB1, float &VB2, float &VA0, float &VA1, float &VA2, float &VA3, float &VStart, float &Vstop, float &Vstep);
VR_Detect_A_Search(B1_FastUpdate, B2_MaxSate, A_Skipping, A1_MinState, A2_FastUpdate, A3_Target_VR, VStart, Vstop, VstepSize);

////////////	////////V_Set = 49.8;
////////////	////////i = 0;
////////////	////////Exit_loop  = 0;
////////////	////////int Exit_loop1 = 0;  //for B2 MaxState
////////////	////////int Exit_loop2 = 0;  //for B1 fast Update.
////////////	////////int Exit_loop3 = 0;  //for A3 target VR
////////////	////////int Exit_loop4 = 0;  //for A2 fast update.
////////////	////////int Exit_loop5 = 0;  //for A1 min state
////////////	////////int Exit_loop6 = 0;  //for skipping
////////////	////////while(j < V_Set && Exit_loop < 1)
////////////	////////{	
////////////	////////		VR_dvi->set_voltage(VRstep_ch, j+VstepSize, VOLT_50_RANGE);
////////////	////////		wait.delay_10_us(20);	
////////////	////////		temp = B_ovi3->measure_average(5);	
////////////	////////		I_B[i] = temp;
////////////	////////		V_VR[i] = j+VstepSize;
////////////	////////		if(temp < 1e-3 && Exit_loop1<1)
////////////	////////		{		
////////////	////////			B2_MaxSate = VR_dvi->measure_average(25);
////////////	////////			Exit_loop1 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////	////////		}
////////////	////////		else if(temp > 1e-3 && Exit_loop1 > 0 && Exit_loop2 < 1)
////////////	////////		{
////////////	////////			B1_FastUpdate = VR_dvi->measure_average(25);
////////////	////////			Exit_loop2 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////
////////////	////////			//if(Exit_loop1 == 1 && Exit_loop2 == 1) Exit_loop = 1;
////////////	////////		}
////////////	////////		if(temp < 1e-3 && Exit_loop1 > 0 && Exit_loop2 > 0&& Exit_loop3 < 1)
////////////	////////		{		
////////////	////////			A3_Target_VR = VR_dvi->measure_average(25);
////////////	////////			Exit_loop3 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////	////////		}
////////////	////////		if(temp > 1e-3 && Exit_loop1 > 0 && Exit_loop2 >0 && Exit_loop3 > 0 && Exit_loop4 < 1)
////////////	////////		{		
////////////	////////			A2_FastUpdate = VR_dvi->measure_average(25);
////////////	////////			Exit_loop4 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////	////////		}
////////////	////////		if(temp < 1e-3 && Exit_loop1 > 0 && Exit_loop2 >0 && Exit_loop3 > 0 && Exit_loop4 > 0 && Exit_loop5 < 1)
////////////	////////		{		
////////////	////////			A1_MinState = VR_dvi->measure_average(25);
////////////	////////			Exit_loop5 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////	////////		}
////////////	////////		if(temp > 1e-3 && Exit_loop1 > 0 && Exit_loop2 >0 && Exit_loop3 > 0 && Exit_loop4 > 0 && Exit_loop5 > 0 && Exit_loop6 < 1)
////////////	////////		{		
////////////	////////			A_Skipping = VR_dvi->measure_average(25);
////////////	////////			Exit_loop6 = 1;
////////////	////////			j = j + 0.5; //Skip 0.5V ahead to reduce test time.
////////////
////////////	////////			if(Exit_loop1==1&&Exit_loop2==1&&Exit_loop3==1&&Exit_loop4==1&&Exit_loop5==1&&Exit_loop5==1) Exit_loop = 1;
////////////	////////		}
////////////	////////		else
////////////	////////		{
////////////	////////			j=j+VstepSize;
////////////	////////			i = i+1;
////////////	////////		}
////////////	////////}
	VR_dvi->set_voltage(VRstep_ch, 10, VOLT_50_RANGE);
	delay(5);




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

	VR_dvi->set_voltage(VRstep_ch, 10, VOLT_50_RANGE); 
	wait.delay_10_us(200);

	B_ovi3->set_current(B_ch1, 0.1e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);

	HSG_ovi->set_current(HSG_ch, 0.1e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(50);

	HBP_dvi2k->set_voltage(HBP_ch, 5, VOLT_20_RANGE);
	VR_dvi->set_voltage(VRstep_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);				
	wait.delay_10_us(10);

	HBP_dvi2k->set_voltage(HBP_ch, 0, VOLT_20_RANGE);
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	FB_ovi3->connect(FB_ch);
	Open_relay(K6_DDD_TB);

	HBP_dvi2k->close_relay(CONN_FORCE0);
	BPS_dvi->close_relay(CONN_FORCE0);
	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG for Open Drain config later.
	Open_relay(K2_B_SPI_TB);        //Keep OVI_3_1 on B for Open Drain config later.
	Open_relay(K3_B_SPI_TB);		//Do not connect 2nF to B!
	Open_relay(K3_HSG_SPI_TB);      //Do not connect 2nF to HSG!
	Open_relay(K7_IS_SPI_TB);       //Connect 1K from IS to GND
	Open_relay(K1_IS_SPI_TB);		//Disconnect DVI_13_1 from IS.
	Open_relay(K5_B_SPI_TB);        //Connect B to Buffer.
	Open_relay(K5_HSG_SPI_TB);      //Connect Buffer/HSG.
	Open_relay(K1_FW_SPI_TB);       //Disconnect OVI from FW pin.
	Open_relay(K7_DDD_TB);          //connect DDD to FW
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	Open_relay(K1_SDA_SPI_TB);
	Open_relay(K1_SCL_SPI_TB);
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	Open_relay(K6_VR_SPI_RB);      //Disconnect DVI_9_0 from VR thru Diode.  
	VR_dvi->close_relay(CONN_FORCE1);
	VR_dvi->close_relay(CONN_SENSE1);
	mux_20->open_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->open_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.

	Open_relay(K5_B_SPI_TB);       //Connect B to Buffer.
	Open_relay(K5_HSG_SPI_TB);     //Connect Buffer/HSG.
	Open_relay(K1_HSG_SPI_RB);      //Pullup R on HSG for Open Drain config later.
	Open_relay(K1_B_SPI_RB);        //Pullup R on B for Open Drain config later.
	
	Open_relay(K1_FW_SPI_TB);      //Disconnect OVI from FW pin.
	Open_relay(K7_DDD_TB);         //connect DDD to FW
	Open_relay(K6_VR_SPI_RB);      //Connect DVI_9_0 to VR thru Diode.  Prevent VR from drawing current from HBP

	//Connect Pullup R to SCL & SDA
	Open_relay(K1_SDA_SPI_TB);
	Open_relay(K1_SCL_SPI_TB);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	wait.delay_10_us(250);
	
	PiDatalog(func, A_VR_DE00_Opt,		  g_TvrOption_B16_17_S,      26, POWER_UNIT);
	PiDatalog(func, A_AVR_DE00_Tap1,		  VFB_Meas[4],               26, POWER_UNIT);
	PiDatalog(func, A_AVR_DE00_Tap2,		  VFB_Meas[1],               26, POWER_UNIT);
	PiDatalog(func, A_AVR_DE00_Tap3,		  VFB_Meas[2],               26, POWER_UNIT);
	PiDatalog(func, A_AVR_DE00_Tap4,		  VFB_Meas[3],               26, POWER_UNIT);

	PiDatalog(func, A_VFB_ExHBP_44_00,		  VFB,               26, POWER_UNIT);


	if(VFB != 0.0)
	{
		if(1)//Set 0 to get Raw data for debugging.
		{
			A_Skipping    = A_Skipping*1.25/VFB;
			A1_MinState   = A1_MinState*1.25/VFB;
			A2_FastUpdate = A2_FastUpdate*1.25/VFB;
			A3_Target_VR  = A3_Target_VR*1.25/VFB;
		}
	}
	else
	{
		A_Skipping    = 0;
		A1_MinState   = 0;
		A2_FastUpdate = 0;
		A3_Target_VR  = 0;
	}
		
	PiDatalog(func, A_A0_ExHBP_44_00, A_Skipping,				 26, POWER_UNIT);
	PiDatalog(func, A_A1_ExHBP_44_00, A1_MinState,				 26, POWER_UNIT);
	PiDatalog(func, A_A2_ExHBP_44_00, A2_FastUpdate,			 26, POWER_UNIT);
	PiDatalog(func, A_A3_ExHBP_44_00, A3_Target_VR,				 26, POWER_UNIT);


	PiDatalog(func, A_B1_ExHBP_44_00,	  B1_FastUpdate,		 26, POWER_UNIT);
	PiDatalog(func, A_B2_ExHBP_44_00,	  B2_MaxSate,			 26, POWER_UNIT);

	PiDatalog(func, A_BSk_ExHBP_44_00,  B_Skip_5K,				 26, POWER_UNIT);
	PiDatalog(func, A_BD_ExHBP_44_00,	  B_5K,				     26, POWER_UNIT);
	PiDatalog(func, A_BLOSkExHBP44_00,BLO_Skip_5K,				 26, POWER_UNIT);

	PiDatalog(func, A_BLO_ExHBP44_00,	  BLO_5K,				     26, POWER_UNIT);
	PiDatalog(func, A_B3_ExHBP_44_00,	  B3_UVLO_5K,				 26, POWER_UNIT);
	

	
	
	
	


	////////if (g_Trim_Enable_S)
	////////{
	////////	PiDatalog(func, A_VADC_Delta_S,      VADC_Delta_S,           26, POWER_UNIT);
	////////}
	////////

}
