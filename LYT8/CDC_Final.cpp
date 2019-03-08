//==============================================================================
// CDC_Final.cpp (User function)
// 
//    void CDC_Final_user_init(test_function& func)
//    void CDC_Final(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "CDC_Final.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void CDC_Final_user_init(test_function& func)
{
	CDC_Final_params *ours;
    ours = (CDC_Final_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void CDC_Final(test_function& func)
{
    // The two lines below must be the first two in the function.
    CDC_Final_params *ours;
    ours = (CDC_Final_params *)func.params;

	// Increment function number //
	gFuncNum++;	
/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_CDC_Final, gFuncNum, 26, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;
	
	if (g_Fn_CDC_Final == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float CDC_0mV_S = -999;
	float CDC_50mV_S = 0;
	float CDC_100mV_S = 0;
	float CDC_200mV_S = 0;
	float CDC_400mV_S = 0;
	float CDC_550mV_S = 0;
	float CDC_Final_S = 0;
	float CDC_Act_Chg_S = 0;
	float Delta_CDC = 0;
	float CDC_Final_TT = 0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int WordArray[16] = {0};
	int TempArray[30] = {0};
	float UpperLimit = 0;
	float LowerLimit = 0;
	float Vforce = 0;
	float SRpinVolt = 0;
	float TempValue = 0;
	float Force_IS_volt = 0;
	float LowerResult = 0;
	float UpperResult = 0;
	float LowerValue= 0;
	float UpperValue= 0;
	int FoundThresh = 0;
	float stepSize = 0;
	int i = 0;
	float SumResult = 0;
	Pulse pulse;

	if ( g_OPCODE != 4300 || g_Char_Enable_P) // Skip at 4300. Test if characterization enabled. //
	{
		// Open all relays //
		//Initialize_Relays();

		// Initialize Instruments //
		//Initialize_Instruments();

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
		//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 

		// BPS //
		//BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

		// IS //
		//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
		IS_dvi2k->set_current(IS_ch, 2, RANGE_2_A); // DVI_13_0, dvi2k //

		// Vout //
		VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
		VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //

		// FB (COMP) //
		FB_ovi->disconnect(2);

		// VBD //
		VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
		//VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
		//wait.delay_10_us(25); // Prevent glitch //
		VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

		// uVCC //
		uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
		uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

		// DDD level //
		//g_DDD_Low = 0.0; // Save current value //
		//g_DDD_High = 3.3; // Save current value //
		//wait.delay_10_us(100);
		//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
		//wait.delay_10_us(100);

		// SDA //
		Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
		ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
		ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
		Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
		Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
		//	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. // // Add I2C DSM //
	Mux20_Open_relay(K40);  // Connect SDA and SCL to DSM. // // Add I2C DSM //

		// SCL //
		Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
		ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //

		// Set DDD for I2C. //
		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
			
		// Wait for relays //
		wait.delay_10_us(200);

		// Powerup //
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

		// I2C into test mode. //  
		//Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
		//Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
		
	//	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
	DSM_Write_Word(g_TM_ANA, 0x0134);

	//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
	DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //

		// SR //
		SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k, Float. //

		// Connect the FB comparator output to SR pin (CV comparator output). //
	//	Write_Word(g_TM_SEL, 0x0024, NObin, HEX); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //
	DSM_Write_Word(g_TM_SEL, 0x0024); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //

		// Write 0x0820 to TM_CTRL.  This will force secondary in control and disconnect Vout from ADC.  Without this, the FB comparator reference is shifted causing a measuremnt error. //
		// Putting secondary in control prevents the FB comparator reference from shifting- this is the main cause of the FB comparator reference shift. //
		// Disconnecting Vout from ADC also prevents FB comparator reference from shifting, but not as much as putting secondary in control. //
	//	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX);
	DSM_Write_Word(g_TM_CTRL, 0x0820); 

		// Get IS pin ready. //
		//Force_IS_volt = g_IsDAC_final; // Saved from IsDAC_Final.cpp function. //
		//Force_IS_volt = Force_IS_volt / g_Gain_Final; // Reduce by 40X for op amp gain. The target is ~32mV. //
		//Force_IS_volt = g_ISVTH; // Change to ISVTH per design(Johnny) 10/23/2017. //
		//Force_IS_volt = 20.0 * Force_IS_volt; // IS pin is connected to 20X buffer. //
		Force_IS_volt = 0.032; // Change to force fixed 32mV per design (Johnny and Yuri) 11/29/2017. //
		Force_IS_volt = g_ISbuff_Gain32 * Force_IS_volt; // IS pin is connected to 20X buffer. //
		mux_14->close_relay(MUX_2_GND);
		Close_relay(K24); // Connect IS pin to 20X buffer. //
		wait.delay_10_us(200); // Wait for relay //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 

		// Force ~32mV to IS pin to get full CDC. //
		if (Force_IS_volt > 0.999 || Force_IS_volt < 0) // Prevent out of range. //
		{
			Force_IS_volt = 0;
			g_Error_Flag = -131;
		}
		IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k.  Remember, IS pin attached to 20X gain buffer, 640mV / 20 = 32mV. //
		wait.delay_10_us(100);

		// Program the CDC with I2C to g_CDC_Target_S. //
		TempValue = (g_CDC_Target_S*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//	Write_Byte(g_CDC, TempValue, NObin, HEX);
	DSM_Write_Byte(g_CDC, TempValue);

		// Binary search CV [on Vout pin] to get CV plus CDC. //
		// Look for FB comparator output flip on SR pin. //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
		UpperLimit = (func.dlog->tests[A_CDC_Final_S].f_max_limit_val[0])*1.1; // Get upper search limit //
		UpperLimit = UpperLimit + g_CV_Final_S;
		LowerLimit = (func.dlog->tests[A_CDC_Final_S].f_min_limit_val[0])*0.9; // Get lower search limit //
		LowerLimit = LowerLimit + g_CV_Final_S;
		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		{
			UpperLimit = (func.dlog->tests[A_CDC_Final_S].f_max_limit_val[0])*1.5; // Get upper search limit //
			UpperLimit = UpperLimit + g_CV_Final_S;
			LowerLimit = (func.dlog->tests[A_CDC_Final_S].f_min_limit_val[0])*0.5; // Get lower search limit //
			LowerLimit = LowerLimit + g_CV_Final_S;
		}
		Vforce = (UpperLimit + LowerLimit) / 2;
		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -121;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		while ( (UpperLimit - LowerLimit) > .001)
		{
			Vforce = (UpperLimit + LowerLimit) / 2; 
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -122;
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
		CDC_Final_S = Vforce - g_CV_Final_S;
		CDC_Act_Chg_S = ((CDC_Final_S - g_CDC_Pt_S) / g_CDC_Pt_S)*100; // In percent //		


		if (g_Char_Enable_P) // Characterization only //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// CDC_0mV_S //
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Program the CDC with I2C //
			TempValue = (0*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//		Write_Byte(g_CDC, TempValue, NObin, HEX);
		DSM_Write_Byte(g_CDC, TempValue);

			// Binary search CV [on Vout pin] to get CV plus CDC. //
			// Look for FB comparator output flip on SR pin. //
			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
			UpperLimit = (func.dlog->tests[A_CDC_0mV_S].f_max_limit_val[0])*1.1; // Get upper search limit //
			UpperLimit = UpperLimit + g_CV_Final_S;
			LowerLimit = (func.dlog->tests[A_CDC_0mV_S].f_min_limit_val[0])*0.9; // Get lower search limit //
			LowerLimit = LowerLimit + g_CV_Final_S;
			if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
			{
				UpperLimit = (func.dlog->tests[A_CDC_0mV_S].f_max_limit_val[0])*1.5; // Get upper search limit //
				UpperLimit = UpperLimit + g_CV_Final_S;
				LowerLimit = (func.dlog->tests[A_CDC_0mV_S].f_min_limit_val[0])*0.5; // Get lower search limit //
				LowerLimit = LowerLimit + g_CV_Final_S;
			}
			Vforce = (UpperLimit + LowerLimit) / 2;
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -121;
			}
			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);
			while ( (UpperLimit - LowerLimit) > .0005)
			{
				Vforce = (UpperLimit + LowerLimit) / 2; 
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -122;
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
			CDC_0mV_S = Vforce - g_CV_Final_S;

		
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// CDC_50mV_S //
			// To improve repeatability, a binary search is first done to get the approximate 
			// value.  Then, linear searching is done first starting below the threshold and 
			// increasing until SR pin flips.  Next, linear searching is done starting above 
			// the threshold and decreasing until SR pin flips.  Then the average of the two 
			// search values is taken.  The is done because noise on the input to the comparator 
			// causes the SR pin to flip when getting near the threshold and by searching linearly 
			// from below and above and then taking the average this error is minimized.  
			// Additional averaging is done by performing the whole test 5 times.  This 
			// adds quite a bit of test time, but is only done for characterization. 
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Program the CDC with I2C //
			TempValue = (0.050*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//		Write_Byte(g_CDC, TempValue, NObin, HEX);
		DSM_Write_Byte(g_CDC, TempValue);
			SumResult = 0;
			for (i=0; i<5; i++)
			{
				// Binary search CV [on Vout pin] to get CV plus CDC. //
				// Look for FB comparator output flip on SR pin. //
				SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
				UpperLimit = (func.dlog->tests[A_CDC_50mV_S].f_max_limit_val[0])*1.1; // Get upper search limit //
				UpperLimit = UpperLimit + g_CV_Final_S;
				LowerLimit = (func.dlog->tests[A_CDC_50mV_S].f_min_limit_val[0])*0.9; // Get lower search limit //
				LowerLimit = LowerLimit + g_CV_Final_S;
				if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
				{
					UpperLimit = (func.dlog->tests[A_CDC_50mV_S].f_max_limit_val[0])*1.5; // Get upper search limit //
					UpperLimit = UpperLimit + g_CV_Final_S;
					LowerLimit = (func.dlog->tests[A_CDC_50mV_S].f_min_limit_val[0])*0.5; // Get lower search limit //
					LowerLimit = LowerLimit + g_CV_Final_S;
				}
				Vforce = (UpperLimit + LowerLimit) / 2;
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -176;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(50);
				while ( (UpperLimit - LowerLimit) > .0005)
				{
					Vforce = (UpperLimit + LowerLimit) / 2; 
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -177;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
						LowerLimit = Vforce;
					else // Above threshold.  CV comparator high. //
						UpperLimit = Vforce;		
				}
				CDC_50mV_S = Vforce - g_CV_Final_S;

				// Linear search from below and above threshold //
				LowerResult = 0;
				UpperResult = 0;
				LowerValue= Vforce - .03;
				UpperValue= Vforce + .03;
				FoundThresh = 0;
				stepSize = 0.001;

				// Linear search from below threshold //
				Vforce = LowerValue;
				while ( Vforce < UpperValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -178;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt > 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce += stepSize;
				}
				Vforce -= stepSize;
				LowerResult = Vforce;

				// Linear search from above threshold //
				FoundThresh = 0;
				Vforce = UpperValue;
				while ( Vforce > LowerValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -179;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce -= stepSize;
				}
				Vforce += stepSize;
				UpperResult = Vforce;
				CDC_50mV_S = ((LowerResult + UpperResult) / 2) - g_CV_Final_S;
				SumResult += CDC_50mV_S;
			}
			CDC_50mV_S = SumResult / 5;

			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// CDC_100mV_S //
			// To improve repeatability, a binary search is first done to get the approximate 
			// value.  Then, linear searching is done first starting below the threshold and 
			// increasing until SR pin flips.  Next, linear searching is done starting above 
			// the threshold and decreasing until SR pin flips.  Then the average of the two 
			// search values is taken.  The is done because noise on the input to the comparator 
			// causes the SR pin to flip when getting near the threshold and by searching linearly 
			// from below and above and then taking the average this error is minimized.  
			// Additional averaging is done by performing the whole test 5 times.  This 
			// adds quite a bit of test time, but is only done for characterization. 
			//
			// Add 45kHz I2C frequency communication test.  The CDC_100mV_S test will be done use the I2C 
			// running at 45kHz.  This is to ensure the parts meet the lower spec limit of 50kHz. This
			// is done for characterization only.
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

			// Set DDD clock frequency to 45kHz.  This is to ensure the parts meet the lower spec limit 
			// of 50kHz. This is done for characterization only.
			// Set DDD for I2C. //
			ddd_7->ddd_set_clock_period(3.75e-6); // 45kHz I2C clock frequency. //


		// Set DSM clock frequency //
		DSM_set_vector_clock_freq(DSM_CONTEXT, 180); // Freq in kHZ, 180/4 = 45kHz clock frequency //  // Add I2C DSM //

			// Program the CDC with I2C //
			TempValue = (0.100*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
			//Write_Byte(g_CDC, TempValue, NObin, HEX);
	//		Write_Byte_45kHz(g_CDC, TempValue, NObin, HEX);
		DSM_Write_Byte(g_CDC, TempValue);
			SumResult = 0;
			for (i=0; i<5; i++)
			{
				// Binary search CV [on Vout pin] to get CV plus CDC. //
				// Look for FB comparator output flip on SR pin. //
				SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
				UpperLimit = (func.dlog->tests[A_CDC_100mV_S].f_max_limit_val[0])*1.1; // Get upper search limit //
				UpperLimit = UpperLimit + g_CV_Final_S;
				LowerLimit = (func.dlog->tests[A_CDC_100mV_S].f_min_limit_val[0])*0.9; // Get lower search limit //
				LowerLimit = LowerLimit + g_CV_Final_S;
				if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
				{
					UpperLimit = (func.dlog->tests[A_CDC_100mV_S].f_max_limit_val[0])*1.5; // Get upper search limit //
					UpperLimit = UpperLimit + g_CV_Final_S;
					LowerLimit = (func.dlog->tests[A_CDC_100mV_S].f_min_limit_val[0])*0.5; // Get lower search limit //
					LowerLimit = LowerLimit + g_CV_Final_S;
				}
				Vforce = (UpperLimit + LowerLimit) / 2;
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -176;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(50);
				while ( (UpperLimit - LowerLimit) > .0005)
				{
					Vforce = (UpperLimit + LowerLimit) / 2; 
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -177;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
						LowerLimit = Vforce;
					else // Above threshold.  CV comparator high. //
						UpperLimit = Vforce;		
				}
				CDC_100mV_S = Vforce - g_CV_Final_S;

				// Linear search from below and above threshold //
				LowerResult = 0;
				UpperResult = 0;
				LowerValue= Vforce - .04;
				UpperValue= Vforce + .04;
				FoundThresh = 0;
				stepSize = 0.001;

				// Linear search from below threshold //
				Vforce = LowerValue;
				while ( Vforce < UpperValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -178;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt > 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce += stepSize;
				}
				Vforce -= stepSize;
				LowerResult = Vforce;

				// Linear search from above threshold //
				FoundThresh = 0;
				Vforce = UpperValue;
				while ( Vforce > LowerValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -179;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce -= stepSize;
				}
				Vforce += stepSize;
				UpperResult = Vforce;
				CDC_100mV_S = ((LowerResult + UpperResult) / 2) - g_CV_Final_S;
				SumResult += CDC_100mV_S;
			}
			CDC_100mV_S = SumResult / 5;

			// Return to full speed. //
			// Set DDD for I2C. //
			ddd_7->ddd_set_clock_period(g_Dclk_I2C);
			wait.delay_10_us(50);
		// Set DSM clock frequency //
		DSM_set_vector_clock_freq(DSM_CONTEXT, 1200); // Freq in kHZ, 1200/4 = 300kHz clock frequency //  // Add I2C DSM //


				
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// CDC_200mV_S //
			// To improve repeatability, a binary search is first done to get the approximate 
			// value.  Then, linear searching is done first starting below the threshold and 
			// increasing until SR pin flips.  Next, linear searching is done starting above 
			// the threshold and decreasing until SR pin flips.  Then the average of the two 
			// search values is taken.  The is done because noise on the input to the comparator 
			// causes the SR pin to flip when getting near the threshold and by searching linearly 
			// from below and above and then taking the average this error is minimized.  
			// Additional averaging is done by performing the whole test 5 times.  This 
			// adds quite a bit of test time, but is only done for characterization. 
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Program the CDC with I2C //
			TempValue = (0.200*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//		Write_Byte(g_CDC, TempValue, NObin, HEX);
		DSM_Write_Byte(g_CDC, TempValue);
			SumResult = 0;
			for (i=0; i<5; i++)
			{
				// Binary search CV [on Vout pin] to get CV plus CDC. //
				// Look for FB comparator output flip on SR pin. //
				SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
				UpperLimit = (func.dlog->tests[A_CDC_200mV_S].f_max_limit_val[0])*1.1; // Get upper search limit //
				UpperLimit = UpperLimit + g_CV_Final_S;
				LowerLimit = (func.dlog->tests[A_CDC_200mV_S].f_min_limit_val[0])*0.9; // Get lower search limit //
				LowerLimit = LowerLimit + g_CV_Final_S;
				if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
				{
					UpperLimit = (func.dlog->tests[A_CDC_200mV_S].f_max_limit_val[0])*1.5; // Get upper search limit //
					UpperLimit = UpperLimit + g_CV_Final_S;
					LowerLimit = (func.dlog->tests[A_CDC_200mV_S].f_min_limit_val[0])*0.5; // Get lower search limit //
					LowerLimit = LowerLimit + g_CV_Final_S;
				}
				Vforce = (UpperLimit + LowerLimit) / 2;
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -176;
				}
				VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
				wait.delay_10_us(50);
				while ( (UpperLimit - LowerLimit) > .0005)
				{
					Vforce = (UpperLimit + LowerLimit) / 2; 
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -177;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Below threshold.  CV comparator low. //
						LowerLimit = Vforce;
					else // Above threshold.  CV comparator high. //
						UpperLimit = Vforce;		
				}
				CDC_200mV_S = Vforce - g_CV_Final_S;

				// Linear search from below and above threshold //
				LowerResult = 0;
				UpperResult = 0;
				LowerValue= Vforce - .04;
				UpperValue= Vforce + .04;
				FoundThresh = 0;
				stepSize = 0.001;

				// Linear search from below threshold //
				Vforce = LowerValue;
				while ( Vforce < UpperValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -178;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt > 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce += stepSize;
				}
				Vforce -= stepSize;
				LowerResult = Vforce;

				// Linear search from above threshold //
				FoundThresh = 0;
				Vforce = UpperValue;
				while ( Vforce > LowerValue && FoundThresh == 0)
				{
					if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
					{
						Vforce = 0;
						g_Error_Flag = -179;
						break;
					}
					VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
					wait.delay_10_us(50);
					SRpinVolt = SR_dvi2k->measure(); // DVI_13_1, dvi2k, check for CV comparator output flip. // 
					if (SRpinVolt < 1.5) // Threshold found //
					{
						FoundThresh = 1;
					}
					Vforce -= stepSize;
				}
				Vforce += stepSize;
				UpperResult = Vforce;
				CDC_200mV_S = ((LowerResult + UpperResult) / 2) - g_CV_Final_S;
				SumResult += CDC_200mV_S;
			}
			CDC_200mV_S = SumResult / 5;
		}		
			
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// CDC_400mV_S //
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
		// Program the CDC with I2C //
		TempValue = (0.400*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//	Write_Byte(g_CDC, TempValue, NObin, HEX);
	DSM_Write_Byte(g_CDC, TempValue);

		// Binary search CV [on Vout pin] to get CV plus CDC. //
		// Look for FB comparator output flip on SR pin. //
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
		UpperLimit = (func.dlog->tests[A_CDC_400mV_S].f_max_limit_val[0])*1.1; // Get upper search limit //
		UpperLimit = UpperLimit + g_CV_Final_S;
		LowerLimit = (func.dlog->tests[A_CDC_400mV_S].f_min_limit_val[0])*0.9; // Get lower search limit //
		LowerLimit = LowerLimit + g_CV_Final_S;
		if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
		{
			UpperLimit = (func.dlog->tests[A_CDC_400mV_S].f_max_limit_val[0])*1.5; // Get upper search limit //
			UpperLimit = UpperLimit + g_CV_Final_S;
			LowerLimit = (func.dlog->tests[A_CDC_400mV_S].f_min_limit_val[0])*0.5; // Get lower search limit //
			LowerLimit = LowerLimit + g_CV_Final_S;
		}
		Vforce = (UpperLimit + LowerLimit) / 2;
		if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
		{
			Vforce = 0;
			g_Error_Flag = -121;
		}
		VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
		wait.delay_10_us(100);
		while ( (UpperLimit - LowerLimit) > .0005)
		{
			Vforce = (UpperLimit + LowerLimit) / 2; 
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -122;
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
		CDC_400mV_S = Vforce - g_CV_Final_S;

		if (g_Char_Enable_P) // Characterization only //
		{
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// CDC_550mV_S //
			// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
			// Program the CDC with I2C //
			TempValue = (0.55*1000) / 50; // The g_CDC register is a 4bit with 50mV per step. //
	//		Write_Byte(g_CDC, TempValue, NObin, HEX);
		DSM_Write_Byte(g_CDC, TempValue);

			// Binary search CV [on Vout pin] to get CV plus CDC. //
			// Look for FB comparator output flip on SR pin. //
			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
			UpperLimit = ((func.dlog->tests[A_CDC_400mV_S].f_max_limit_val[0]) + .15)*1.1; // Get upper search limit //
			UpperLimit = UpperLimit + g_CV_Final_S;
			LowerLimit = ((func.dlog->tests[A_CDC_400mV_S].f_min_limit_val[0]) + .15)*0.9; // Get lower search limit //
			LowerLimit = LowerLimit + g_CV_Final_S;
			if (g_Char_Enable_P == 1) // Widen the search limit for characterization. //
			{
				UpperLimit = ((func.dlog->tests[A_CDC_400mV_S].f_max_limit_val[0]) + .15)*1.5; // Get upper search limit //
				UpperLimit = UpperLimit + g_CV_Final_S;
				LowerLimit = ((func.dlog->tests[A_CDC_400mV_S].f_min_limit_val[0]) + .15)*0.5; // Get lower search limit //
				LowerLimit = LowerLimit + g_CV_Final_S;
			}
			Vforce = (UpperLimit + LowerLimit) / 2;
			if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
			{
				Vforce = 0;
				g_Error_Flag = -121;
			}
			VO_dvi->set_voltage(VO_ch, Vforce, VOLT_10_RANGE); // DVI_9_0 //
			wait.delay_10_us(100);
			while ( (UpperLimit - LowerLimit) > .0005)
			{
				Vforce = (UpperLimit + LowerLimit) / 2; 
				if (Vforce < -9.99 || Vforce > 9.99) // Prevent out of range. //
				{
					Vforce = 0;
					g_Error_Flag = -122;
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
			CDC_550mV_S = Vforce - g_CV_Final_S;
			Delta_CDC = CDC_Final_S - CDC_550mV_S;
		}

		// Powerdown //
	//	mux_14->open_relay(MUX_2_GND);
	//	Open_relay(K24);
	//	Open_relay(K18);
	//	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	//	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	//	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	//	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE); // DVI_13_0, dvi2k //
	//	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
		FB_ovi->connect(2);
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
	//	wait.delay_10_us(g_DDDwait);
	//	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	//	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	//	wait.delay_10_us(g_DDDwait);

		// Datalog //
		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_CDC_0mV_S, CDC_0mV_S, 26, POWER_MILLI);
			PiDatalog(func, A_CDC_50mV_S, CDC_50mV_S, 26, POWER_MILLI);
			PiDatalog(func, A_CDC_100mV_S, CDC_100mV_S, 26, POWER_MILLI);
			PiDatalog(func, A_CDC_200mV_S, CDC_200mV_S, 26, POWER_MILLI);
		}
		PiDatalog(func, A_CDC_400mV_S, CDC_400mV_S, 26, POWER_MILLI);
		PiDatalog(func, A_CDC_Final_S, CDC_Final_S, 26, POWER_MILLI);
		if(g_Trim_Enable_P)
		{
			PiDatalog(func, A_CDC_Act_Chg_S, CDC_Act_Chg_S, 26, POWER_UNIT);
		}

		if (g_Char_Enable_P) // Characterization only //
		{
			PiDatalog(func, A_Delta_CDC, Delta_CDC, 26, POWER_MILLI);
		}
		
		// Test Time End //
		if (g_TstTime_Enble_P)
		{
			g_endtime = g_mytimer.GetElapsedTime();
			CDC_Final_TT = (g_endtime - g_begintime)*1e-6;
			PiDatalog(func, A_CDC_Final_TT, CDC_Final_TT, 26, POWER_MILLI);
		}

		// Check any test failed //
		if (PiGetAnyFailStatus())		
		{
			g_PartFailed = 1;
		}
	}
	else // Skip at 4300. Test if characterization enabled. //
	{
		ddd_7->ddd_set_clock_period(g_Dclk_I2C);
		ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
		wait.delay_10_us(200);

		//	Write_Word(g_TM_ANA, 0x0134, NObin, HEX);
		DSM_Write_Word(g_TM_ANA, 0x0134);

		//	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
		DSM_Write_Byte(g_Watchdog_Timer, 0x00); // Disable watchdog timer //

		//	Write_Word(g_TM_SEL, 0x0024, NObin, HEX); //  Write the I2C command to connect the FB comparator output to SR pin (CV comparator output). //
		DSM_Write_Word(g_TM_SEL, 0x0024); 

		//	Write_Word(g_TM_CTRL, 0x0820, NObin, HEX);
		DSM_Write_Word(g_TM_CTRL, 0x0820); 

		Force_IS_volt = 0.032; // Change to force fixed 32mV per design (Johnny and Yuri) 11/29/2017. //
		Force_IS_volt = g_ISbuff_Gain32 * Force_IS_volt; // IS pin is connected to 20X buffer. //
		IS_dvi2k->set_voltage(IS_ch, Force_IS_volt, VOLT_1_RANGE); // DVI_13_0, dvi2k. 

		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k // 
		FB_ovi->connect(2);
	}
*/
}
