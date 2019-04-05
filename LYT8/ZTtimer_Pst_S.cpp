//==============================================================================
// ZTtimer_Pst_S.cpp (User function)
// 
//    void ZTtimer_Pst_S_user_init(test_function& func)
//    void ZTtimer_Pst_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "ZTtimer_Pst_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ZTtimer_Pst_S_user_init(test_function& func)
{
	ZTtimer_Pst_S_params *ours;
    ours = (ZTtimer_Pst_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ZTtimer_Pst_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    ZTtimer_Pst_S_params *ours;
    ours = (ZTtimer_Pst_S_params *)func.params;

				// Increment function number //
	gFuncNum++;	

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_ZTtimer_Pst, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Burn_Enable_P set //
	//if (g_Burn_Enable_P == 0)
//		return;

	///*if (g_Trim_Enable_S == 0)
	//	return;*/

	//if (g_Fn_ZTtimer_Pre == 0 )  return;

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	// Test variables

	int     i                       = 0;
	int     valid_count             = 0;
	int		array_index		        = 0;
	int		num_loop                = 15;
	float   temp_1                  = 0;
	float   Avg_temp                = 0;
	float   Avg_temp1               = 0;
	float   tmeas                   = 0;
	float   tmeas1					= 0;
	float   tmeas_array[50]         = {0};
	float   tmeas_array2[50]        = {0};
	float   FW_Pulse_Width[50]      = {0};
	float   DPulseTx_PulseWidth[50] = {0};
	float   Ztime_3us               = 0;
	float   DPulseTx_PW             = 0;
	

	// Test Names //
	
	float ZTtimer_Pst_S        =   0;
	float ZTtimer_pct_delta_S  =   0;
	float ZTtimer_DPulseWidth  =   0;
	float tMinOff_S            = 0;
	float tHS_Window_S         = 0;
	float Timer1_S             = 0;
	float Timer2_S             = 0;
	float ZTtimer_Pst_TT       = 0;

Pulse pulse;

	
	//Gage_ChanAB_Setup_S(0.18, GAGE_PM_5_V, GAGE_PM_20_V);

	
	// Open all relays //
	Initialize_Relays();

	//Loading 10Khz DDD pattern into memory.
	//Note:  DDD period is done at 1us, but it will be changed in the future to accomodate for both primary and 2ndary.
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
	//HSG needs to connect thru buffer then.
	HSG_ovi->set_current(HSG_ch, 3e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30UA==> Require to disconnect OVI from FW and clock pulses from DDD_7_7.
	FW_ovi3->set_current(FW_ch, 300e-6, RANGE_300_UA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB = 1.15V/30mA then sweep or binary search.
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	//IS = 0V/200mA...
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);				
	IS_dvi2k->set_current(IS_ch, 0.1e-6, RANGE_200_UA);
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
	HBP_dvi2k->set_current(HBP_ch, 20e-6, RANGE_2_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	
	BPS_dvi->open_relay(CONN_FORCE0);

	Close_relay(K7_IS_SPI_TB);      //Connect 1K from IS to GND
	Close_relay(K1_IS_SPI_TB);		  //Disconnect DVI_13_1 from IS.
	Close_relay(K2_HSG_SPI_TB);       //Disconnect OVI_1_0 from HSG.
	Open_relay(K1_HSG_SPI_RB);       //Keep Kelvin connection. 
	Close_relay(K5_HSG_SPI_TB);      //Connect HSG to buffer  ==> The buffer AD817 is too much for HSG/B.  Will need hardware fix.
	Close_relay(K3_B_SPI_TB);		 //Connect 2nF to B
	Close_relay(K5_TMU_TB);           //ConnectTMU_HIZ_3 to FW.
	Close_relay(K7_DDD_TB);          //Connect DDD_7_7 to FW.
	Close_relay(K1_FW_SPI_TB);       //Disconnect OVI from FW.
	tmu_6->open_relay(TMU_HIZ_DUT4);
	tmu_6->close_relay(TMU_CHAN_B_DUT1); 
	tmu_6->close_relay(TMU_HIZ_DUT3); 
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

	tmu_6->start_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	wait.delay_10_us(250);

	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	wait.delay_10_us(10);
	///Power up VR to 15V to wake up 2ndary.
	// If 15V doesn't work, will set to 20V.
	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	//HBP_dvi2k->set_voltage(HBP_ch, 12, VOLT_20_RANGE);
	wait.delay_10_us(500);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

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

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)

	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en.  Do not enable B signal!  Too much noise interference!
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//1p35us Timer ==> Works okay.  
	//0x00 0x46 write 0x00 0x08
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0800);
	Run_100Khz_Pulses();

	wait.delay_10_us(10);
	for (i=0; i<15; i++)
	{
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(10);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas_array[i] = tmu_6->read(100e-6);	
	}

	ZTtimer_Pst_S = Average_Value(tmeas_array, 1e-6, 2e-6);

	if (g_Trim_Enable_S && g_ZTtimer_Pre != 0)
	{
		ZTtimer_pct_delta_S = 100*(ZTtimer_Pst_S - g_ZTtimer_Pre) / g_ZTtimer_Pre;
	}

	//---------------------------------------------------------------------------------------
	//ZTimer Pulse width
	//-----------------------------------------------------------------------------------
	tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	tmu_6->stop_trigger_setup(10.0, NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	wait.delay_10_us(10);
	for (i=0; i<15; i++)
	{
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(10);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas_array[i] = tmu_6->read(100e-6);	
	}

	ZTtimer_DPulseWidth = Average_Value(tmeas_array, 200e-9, 500e-9);

	//----------------------------------------------------------------------------
	//DXControl_S. Expect ~= 30us or 60us.
	//Due to hardware design, will need to break the meas into 2 stages until hw rev 2.
	//------------------------------------------------------------------------------
	Stop_100Khz_Pulses();
	wait.delay_10_us(50);
	Load_10Khz_Pulses();
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 	
	wait.delay_10_us(500);
	
	//Measure time difference between HSG and FW first.
	tmu_6->open_relay(TMU_HIZ_DUT4);
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->close_relay(TMU_HIZ_DUT3);	   //FW
	tmu_6->close_relay(TMU_CHAN_A_DUT1);   //HSG 
	tmu_6->start_trigger_setup(5.0, NEG_SLOPE, TMU_CHAN_A, TMU_IN_25V);
	tmu_6->stop_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(50);

	Run_10Khz_Pulses();

	VR_dvi->set_voltage(VR_ch, 20, VOLT_50_RANGE); 
	wait.delay_10_us(500);
	DSM_set_I2C_timeout(0, 1);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter TM
	Analog_TM_Enable_Secondary();

	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)

	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en.  Do not enable B signal!  Too much noise interference!
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);
	//DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//DX Control S
	//0x00 0x46 write 0x00 0x00
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0000);
	Run_10Khz_Pulses();
	
	tmu_6->arm();
	wait.delay_10_us(900);
	tmeas = tmu_6->read(1e-3);

	tmu_6->start_trigger_setup(1.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	wait.delay_10_us(10);
	tmu_6->arm();
	wait.delay_10_us(15);
	tmeas1 = tmu_6->read(1e-3);

	tHS_Window_S = tmeas1 - tmeas;

	ddd_7->ddd_stop_pattern(); //Stop the 10Khz Pattern.
	wait.delay_10_us(50);
	//------------------------------------------------------------------------
	//DX_Starttimer. Expect ~= 3us.  Might be the trim parameter.
	//0x00 0x46 write 0x02 0x78
	//-------------------------------------------------------------------------
	tmu_6->start_trigger_setup(5.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_25V);
	tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	//Need to re-enter TM or the test won't work.
	//Enter TM
	Analog_TM_Enable_Secondary();
	TestMode_Check(0); //Set 1 to step into loop.  Set 0 to skip Test Mode check.

	//ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

	//ZTMC_ana_EN and Core_en.  Do not enable B signal!  Too much noise interference!
	//0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', g_TM_CTRL, 0x0006);
	//DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); 	
	wait.delay_10_us(10);

	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x7802);
	wait.delay_10_us(600);  //Do not change to less time.  Need at least 5ms delay to measure tMinOff 3us correctly.

	Run_10Khz_Pulses();
	tmu_6->arm();	
	wait.delay_10_us(490);

	array_index = 0;
	num_loop = 15;

	for (i=0; i<num_loop; i++)
	{
		wait.delay_10_us(5);				// Wait for TMU to trigger and to capture 10 cycles 
		tmeas_array2[i] = tmu_6->read(60e-6);
		tmu_6->arm();
	}
	
	//Eliminate 3 max values.  After that, pre trim = average of the remaining values.
	for(i=0;i<3;i++)
	{
		max_value(tmeas_array2, array_index, num_loop); tmeas_array2[array_index] = 0;array_index = 0;
	}

	valid_count = 0;
	for(i=0;i<num_loop;i++)
	{
		if(tmeas_array2[i] > 0 && tmeas_array2[i] < 1)
		{
			Avg_temp = Avg_temp + tmeas_array2[i];
			valid_count++;
		}
	}
	if(valid_count != 0)
	{
		Avg_temp = Avg_temp /  valid_count;
	}
	//--------------------------------------------------------------------------------------
	
	tmu_6->start_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->stop_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	for (i=0; i<15; i++)
	{
		tmu_6->arm();
		wait.delay_10_us(10);				// Wait for TMU to trigger and to capture 10 cycles 
		FW_Pulse_Width[i] = tmu_6->read(60e-6);
		
	}

	valid_count = 0;
	for(i=0;i<num_loop;i++)
	{
		if(FW_Pulse_Width[i] > 0 && FW_Pulse_Width[i] < 1)
		{
			Avg_temp1 = Avg_temp1 + FW_Pulse_Width[i];
			valid_count++;
		}
	}
	if(valid_count != 0)
	{
		Avg_temp1 = Avg_temp1 /  valid_count;
	}

	Ztime_3us = Avg_temp1 - Avg_temp;


	tmu_6->start_trigger_setup(5.0, NEG_SLOPE, TMU_CHAN_A, TMU_IN_25V);
	tmu_6->stop_trigger_setup(4.2, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	for (i=0; i<15; i++)
	{
		tmu_6->arm();
		wait.delay_10_us(10);				// Wait for TMU to trigger and to capture 10 cycles 
		DPulseTx_PulseWidth[i] = tmu_6->read(60e-6);
		
	}

	valid_count = 0;
	for(i=0;i<num_loop;i++)
	{
		if(DPulseTx_PulseWidth[i] > 0 && FW_Pulse_Width[i] < 1)
		{
			DPulseTx_PW = DPulseTx_PW + DPulseTx_PulseWidth[i];
			valid_count++;
		}
	}
	if(valid_count != 0)
	{
		DPulseTx_PW = DPulseTx_PW /  valid_count;
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


	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	wait.delay_10_us(50);
	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	wait.delay_10_us(200);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);				
	wait.delay_10_us(10);
	IS_dvi2k->set_current(IS_ch, 0.01e-3, RANGE_2_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	HBP_dvi2k->close_relay(CONN_FORCE0);
	BPS_dvi->close_relay(CONN_FORCE0);
	Open_relay(K7_IS_SPI_TB);      //Connect 1K from IS to GND
	Open_relay(K1_SDA_SPI_TB);       //Disconnect pullup R from SDA.
	Open_relay(K1_SCL_SPI_TB);       //Disconnect pullup R from SCL
	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	Open_relay(K4_DSM_TB);           //Disconnect DSM SCL from DUT SCL
	Open_relay(K2_HSG_SPI_TB);		 //Reconnect OVI_1_0 to HSG
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF from B
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K5_HSG_SPI_TB);       //Disconnect HSG from buffer  
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	Open_relay(K5_TMU_TB);           //Disconnect TMU_HIZ_3 to FW.
	Open_relay(K7_DDD_TB);           //Disconnect DDD_7_7 to FW.
	Open_relay(K1_FW_SPI_TB);        //Reconnect OVI to FW.
	Open_relay(K1_IS_SPI_TB);	     //Reconnect DVI_13_1 to IS
	tmu_6->open_relay(TMU_HIZ_DUT4);
	tmu_6->open_relay(TMU_CHAN_B_DUT1); 
	tmu_6->open_relay(TMU_HIZ_DUT3); 
	tmu_6->open_relay(TMU_CHAN_A_DUT1); 
	Open_relay(K1_DigA_TB);         //Disconnect digitizer CHANA to FW
	Open_relay(K2_DigA_TB);

	wait.delay_10_us(250);


	PiDatalog(func, A_ZTtimer_pst_S, ZTtimer_Pst_S,              26, POWER_MICRO);
	if (g_Trim_Enable_S)
	{
		PiDatalog(func, A_ZTtimer_Pct_Delta_S, ZTtimer_pct_delta_S, 26, POWER_UNIT);

	}
	PiDatalog(func, A_ZTimer_DPTx_S, ZTtimer_DPulseWidth,              26, POWER_NANO);

	if(g_ZEE_50KStr_B63_S == 1)
	{
		PiDatalog(func, A_tHS_Window2_S, tHS_Window_S,              26, POWER_MICRO);
	}
	else
	{
		PiDatalog(func, A_tHS_Window1_S, tHS_Window_S,              26, POWER_MICRO);

	}
	
	PiDatalog(func, A_tMinOff_S,      Ztime_3us,              26, POWER_MICRO);
	PiDatalog(func, A_tMinOff_DPTx_S, DPulseTx_PW,              26, POWER_MICRO);

}
