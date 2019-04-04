//==============================================================================
// NTC_P.cpp (User function)
// 
//    void NTC_P_user_init(test_function& func)
//    void NTC_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "NTC_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void NTC_P_user_init(test_function& func)
{
	NTC_P_params *ours;
    ours = (NTC_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void NTC_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    NTC_P_params *ours;
    ours = (NTC_P_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_NTC_P, gFuncNum, 9, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	//if (g_Sim_Enable_P == 0)	return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	//int	Dbus1_12to9_P	=0;
	float	tLong_Dtemp	=0;
	float	tShort_Dtemp	=0;
	int		Dtemp_Tgt_P	=0;
	int		Dtemp_P	=0;
	float	Dtemp_Err_P	=0;
	float	ITS_P	=0;
	float	ITS_Err_P	=0;
	int		VTSstart_code	=0;
	//int		VTSstop_code	=0;
	float	NTC_P_TT	=0;
	int		dbus1_HighByte		=999, 
			dbus1_LowByte		=999, 
			dbus1_bit12_to_9	=0;

	//int		Dtemp_P		= 0;
	//float	ITS_P			= 0;
	//float	iUVm_P		= 0;
	//int		Dtemp_Target_P	= 256; 
	//int		EEtr27_ZTML0_P  = 0;
	//int		EEtr28_ZTML1_P  = 0;
	//
	//int		Dtemp_Sim_P = 0;
	//float	Dtemp_Sim_Chg_P = 0;
	//float	Dtemp_ExpChg   = 0;
	//int		Dtemp_SimChg   = 0;
	//int		Dtemp_pst_P =0;
	//float	Dtemp_TT =0;


	////Trimcode & bit weights.
	//int		Dtemp_TrCode_P		= 0;
	//int		Dtemp_BitCode_P		= 0;
	//float	Dtemp_TrimCode[32] = {0.0};
	//float	Dtemp_SignCode[32] = {0.0};
	//float	Dtemp_TrimWt[32]   = {0.0};
	//float   smallest_diff_val  = 999999.9;
	//float   temp_1             = 0;
	//int     smallest_diff_idx  = 0;
	//int		WordArray[16]	   = {0};
	//int		i;

	//float	tLong_Dtemp, 
	//		tShort_Dtemp;
	//float	tLong_Dtemp_Sim, 
	//		tShort_Dtemp_Sim;
	float	tLong_Dtemp_VTSstop, 
			tShort_Dtemp_VTSstop;
	//int		dbus1_HighByte, 
	//		dbus1_LowByte, 
	//		dbus1_bit12_to_9, 
	//		TS_Mode_NTC;
	//int		dbus1_HighByte_Sim, 
	//		dbus1_LowByte_Sim, 
	//		dbus1_bit12_to_9_Sim, 
	//		TS_Mode_NTC_Sim;
	int		Dtemp_VTSstop_P			=0,
			dbus1_HighByte_VTSstop		=0, 
			dbus1_LowByte_VTSstop		=0, 
			dbus1_bit12_to_9_VTSstop	=0, 
			TS_Mode_NTC_VTSstop		=0;

	//int		TrCode_shift_n_bits	=0,
	//		code_diff			=0;

	//float	VTS_start	=0,
	//		VTS_stop	=0,
	//		Dtemp_LSBmV	=0;


	//uint16_t converted_dec1 = 0;
	//uint16_t converted_dec2 = 0;


	Pulse pulse; // External trigger pulse from dvi for debug //

	/*
	--------------------------------------------------------------------------------------------------------
	Measurement	Target		Notes 
	ITS						~50uA
	VTSstart	
	VTSstop		

	Procedure from Design:
		At the end of TSpinModeDetect (before undoing CFG11, 26), ground TS pin so the mode detected goes into 
		NTC mode.  Then  go back into I2C, now bring Dtemp<8:0> out from dbus1 onto drain, make sure to 
		disable flux link clocking thru Tspin, undo CFG11,26 and then release TS pin (SCL) apply 2.5V on 
		TSPIN and TRIM to get code 256 from Dtemp<8:0>
		When you are applying the 2.5V, there should be a 50uA current being pushed into your 2.5V source, 
		record this as ITS for the datasheet.  The code comes from sigma delta, so 9-bit code updates every 
		512us.	After trimming, find the actual voltage around 2.5V that gives a code of 256, record this 
		voltage as VTSstart.  As the voltage goes down from 2.5V, the code should increase toward 511, 
		find the 1st voltage (close to 1V) that results in code 511, and record this voltage as VTSstop

	Trimming:
		At 2.5V, internally scaled to half of fullscale
		ZTM<70:67>

	Procedure in Program:		
		1.  Power up into I2C mode
		2.  have BPP just go from 0 to 5V stay there don't complete zig-zag, 
		3.  0x40, 0x07			enable sig mode, core en
		4.  0x46, 0x0424		Set 133C and I2C password  16'b0000_0100_0000_0100
		5.  0x42, 0x02			look at TSMODE<2:0> first 3 bits
		6.  0x44, 0x0800		<11> for loop detect 16'b0000_1000_0000_0000
		7.  0x4C, 0x01			release TSPIN
		8.  Drain (50ohm pullup to 1V) on bench setup
		9.  BPP zig zag
		10. Initial observation: Drain output --> expect 101 on TSMODE<2:0> bits using negative duty cycle 
			to determine if it's 1 (2us width) or 0 (1us width).

			Drain __________    _    _    _    _    _    _    _    _    ________   ..............
					tLong	|  | |  | |  | |  | |  | |  | |  | |  | |  | tShort |  ..............
					~11us	|__| |__| |__| |__| |__| |__| |__| |__| |__| ~5us	|__..............
				TSMODE bits	 0    1    2    3    4    5    6    7    8			 9 to 15


			TSMODE<2:0>
			*************************************************************************
			R_Value			Mode						ZTSmode<2:0> (MSBs on dbus1)
			-------------------------------------------------------------------------
			vTS = BPP		Thermal_Foldback_OFF		101
			16k				100C						100
			32k				110C						011
			48k				120C						010
			64k				130C						001
			vTS = GND		NTC							000
		
		11. vTS set to GND for NTC (Note: NTC is an external resistor that will change with respect to 
										  temperature.  Change is not linear.)
	    12. to do NTC voltage trimming, now goback to I2C by making sure TSPIN = 0V and 
			then bring VPIN down to 0V and pull back up to 3.3V

		13. 0x46,	0x0024		I2C password  16'b0000_0000_0010_0100 (undo 133C internal junction temp)
		14. 0x44,	0x0000		<11> for loop detect 16'b0000_0000_0000_0000
		15. 0x60,	0x0100		bit 8 to disable fault reporting
		16. 0x4C,	0x01		release TSPIN
				
		17. now force TSPIN voltage to 2.5V and observe lower 9bits for 256		
		18. sweeping TSPIN voltage from 2.5V down to 1V should change the digital code 		
	--------------------------------------------------------------------------------------------------------
	*/

	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	//Disable DSM I2C after Vpin or TSpin release
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

	if(1)
	{
		DSM_I2C_Write('b', g_TM_CTRL, 0x07);		//0x40, 0x07	(enable sig mode, core en)
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0424);	//0x46, 0x0424	Set 133C and I2C password  16'b0000_0100_0000_0100
		DSM_I2C_Write('b', 0x42, 0x02);				//look at TSMODE<2:0> first 3 bits
		DSM_I2C_Write('w', 0x44, 0x0800);			//<11> for loop detect 16'b0000_1000_0000_0000
		DSM_I2C_Write('b', 0x4C, 0x01);				//release TSPIN
		//Disable DSM I2C after Vpin or TSpin release
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C
	}

	Close_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0		Connected
	delay(4);

	//Drain setup to connect to Ridder board with RL load and set Drain to 5V
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);	// Does not need 100mA for this test.
		D_dvi->set_voltage(D_ch, 1.0,	VOLT_20_RANGE); // DVI_11_0		(5V would be better for seeing the signal but noisy TS due 
														//				 to Drain switching.  Code diff observed is 1 bit less @5V)
		wait.delay_10_us(20);

	BPP_zigzag(5.5, 4.3, 5.3);

	//Initial observation: Drain output --> expect 101 on TSMODE<2:0> bits using negative duty cycle 
	//										to determine if it's 1 (2us width) or 0 (1us width).

	Disable_n_Disconnect_DSMI2C_via(g_release_TSpin);	//TSpin directly connected to ovi-3-0

	//TS set to 0V (GND) for NTC of TSMODE
		TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
		TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
		delay(1);
		//TEST observed: t_Long(~10us), t_Short(~4us)	TSMODE<2:0> = 000 which is NTC mode

	//12. to do NTC voltage trimming, now goback to I2C by making sure TSPIN = 0V and 
	//	  then bring VPIN down to 0V and pull back up to 3.3V
		Regain_I2C_P(g_Vpin_Low_to_High);

	//Connect RDS_BUF to capture Drain signals for NTC code
	Close_relay(K10_D_TB);	//Drain to RDS_BUF_IN
	delay(5);

	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0024);	//0x46, 0x0024	I2C password  16'b0000_0000_0010_0100 (undo 133C internal junction temp)
	DSM_I2C_Write('w', 0x44, 0x0000);			//<11> for loop detect 16'b0000_1000_0000_0000
	DSM_I2C_Write('w', 0x60, 0x0100);			//bit 8 to disable fault reporting
	DSM_I2C_Write('b', 0x4C, 0x01);				//release TSPIN
				
	Disable_n_Disconnect_DSMI2C_via(g_release_TSpin);

	//Force TSPIN voltage to 2.5V and observe lower 9bits for 256		
	TS_ovi3->set_voltage(TSovi3_ch, 2.5, VOLT_10_RANGE); // OVI_3_0
	TS_ovi3->set_meas_mode(TSovi3_ch, OVI_MEASURE_CURRENT);
	delay(5);	//observe bit9 to bit16

	//Measure ITS @ vTS = 2.5V.  Expect ~50uA being pused into the 2.5V source
	ITS_P = -TS_ovi3->measure_average(25);


	//Setup for Digitizer Channel B trigger
		gage_input_control_xp (GAGE_CHAN_B,		// channel
				GAGE_INPUT_ENABLE,					// enable / disable
				GAGE_DC,							// coupling
				GAGE_PM_5_V|GAGE_1_MOHM_INPUT);			// range, impedance
		
		gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
				GAGE_DC,							// coupling for ext trig
				GAGE_PM_5_V,								// range for CHA trigger
				GAGE_POSITIVE,						// slope
				0.40,								// trigger level	
	   			g_SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE

	//Capture waveform and analyze
		Gage_Start_Capture(  );	
		Gage_Wait_For_Capture_Complete();
		g_WAVE_NAME =  "Dtemp";
		Gage_Find_Dtemp_code(&Dtemp_P, &tLong_Dtemp, &dbus1_HighByte, &tShort_Dtemp, &dbus1_LowByte);
																												//0000 1010
	dbus1_bit12_to_9	= dbus1_HighByte & 0x1E;	//bit 12 to 9	=> 0101 = vss, vdd, vss, vdd or 5 in decimal  xxx1 111x xxxx xxxx
	//TS_Mode_NTC			= dbus1_HighByte & 0xE0;	//NTC mode		=> 000x of ZTSmode<2:0>


	//if(TS_Mode_NTC == 0) TS_Mode_NTC = 1;			//NTC mode selected if 000 from ZTSmode<2:0>

	PiDatalog(func, A_Dbus1_12to9_P,	dbus1_bit12_to_9,	ours->fail_bin, POWER_UNIT);
	//PiDatalog(func, A_TSMode_NTC,		TS_Mode_NTC,		ours->fail_bin, POWER_UNIT);
	PiDatalog(func, A_tLong_Dtemp,		tLong_Dtemp*20e-9,	ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_tShort_Dtemp,		tShort_Dtemp*20e-9,	ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_Dtemp_P,		Dtemp_P,			ours->fail_bin, POWER_UNIT);
	PiDatalog(func, A_ITS_P,			ITS_P,				ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_Dtemp_Tgt_P,	gP_Dtemp_TARGET_Trimops,	ours->fail_bin, POWER_UNIT);


	//VTS_Stop = 1V
	TS_ovi3->set_voltage(TSovi3_ch, 1.0, VOLT_10_RANGE); // OVI_3_0		
	delay(5);

	//Capture waveform and analyze
		Gage_Start_Capture(  );	
		Gage_Wait_For_Capture_Complete();
		g_WAVE_NAME =  "Dtemp_VTS_stop";
		Gage_Find_Dtemp_code(&Dtemp_VTSstop_P, &tLong_Dtemp_VTSstop, &dbus1_HighByte_VTSstop, &tShort_Dtemp_VTSstop, &dbus1_LowByte_VTSstop);

		PiDatalog(func, A_VTSstop_code,		Dtemp_VTSstop_P,		ours->fail_bin, POWER_UNIT);


	Power_Down_I2C_P();
	Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0		disconnect
	Open_relay(K10_D_TB);	//D  to RDS_BUF									disconnect
	delay(1);


}
