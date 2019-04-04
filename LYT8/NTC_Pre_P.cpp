//==============================================================================
// NTC_Pre_P.cpp (User function)
// 
//    void NTC_Pre_P_user_init(test_function& func)
//    void NTC_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "NTC_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void NTC_Pre_P_user_init(test_function& func)
{
	NTC_Pre_P_params *ours;
    ours = (NTC_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void NTC_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    NTC_Pre_P_params *ours;
    ours = (NTC_Pre_P_params *)func.params;


	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_NTC_Tr_P, gFuncNum, 9, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)	return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	int		Dtemp_pt_P		= 0;
	float	ITS_P			= 0;
	float	iUVm_pt_P		= 0;
	int		Dtemp_Target_P	= 256; 
	int		EEtr27_ZTML0_P  = 0;
	int		EEtr28_ZTML1_P  = 0;
	
	int		Dtemp_Sim_P = 0;
	float	Dtemp_Sim_Chg_P = 0;
	float	Dtemp_ExpChg   = 0;
	int		Dtemp_SimChg   = 0;
	int		Dtemp_pst_P =0;
	float	Dtemp_Pre_TT =0;


	//Trimcode & bit weights.
	int		Dtemp_TrCode_P		= 0;
	int		Dtemp_BitCode_P		= 0;
	float	Dtemp_TrimCode[32] = {0.0};
	float	Dtemp_SignCode[32] = {0.0};
	float	Dtemp_TrimWt[32]   = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;

	float	tLong_Dtemp, 
			tShort_Dtemp;
	float	tLong_Dtemp_Sim, 
			tShort_Dtemp_Sim;
	float	tLong_Dtemp_VTSstop, 
			tShort_Dtemp_VTSstop;
	int		dbus1_HighByte, 
			dbus1_LowByte, 
			dbus1_bit12_to_9, 
			TS_Mode_NTC;
	int		dbus1_HighByte_Sim, 
			dbus1_LowByte_Sim, 
			dbus1_bit12_to_9_Sim, 
			TS_Mode_NTC_Sim;
	int		Dtemp_VTSstop_P			=0,
			dbus1_HighByte_VTSstop		=0, 
			dbus1_LowByte_VTSstop		=0, 
			dbus1_bit12_to_9_VTSstop	=0, 
			TS_Mode_NTC_VTSstop		=0;

	int		TrCode_shift_n_bits	=0,
			code_diff			=0;

	float	VTS_start	=0,
			VTS_stop	=0,
			Dtemp_LSBmV	=0;


	uint16_t converted_dec1 = 0;
	uint16_t converted_dec2 = 0;

	tLong_Dtemp			=0;
	tShort_Dtemp		=0;
	dbus1_HighByte		=999;
	dbus1_LowByte		=999;
	dbus1_bit12_to_9	=0;


	//i = 0;
	//Dtemp_TrimCode[i] 	=	0	;	 Dtemp_TrimWt[i] 	=	0	;	Dtemp_SignCode[i] 	=	0	;	    i++	;
	//Dtemp_TrimCode[i] 	=	1	;	 Dtemp_TrimWt[i] 	=	1	;	Dtemp_SignCode[i] 	=	1	;	    i++	;
	//Dtemp_TrimCode[i] 	=	2	;	 Dtemp_TrimWt[i] 	=	2	;	Dtemp_SignCode[i] 	=	2	;	    i++	;
	//Dtemp_TrimCode[i] 	=	3	;	 Dtemp_TrimWt[i] 	=	3	;	Dtemp_SignCode[i] 	=	3	;	    i++	;
	//Dtemp_TrimCode[i] 	=	4	;	 Dtemp_TrimWt[i] 	=	4	;	Dtemp_SignCode[i] 	=	4	;	    i++	;
	//Dtemp_TrimCode[i] 	=	5	;	 Dtemp_TrimWt[i] 	=	5	;	Dtemp_SignCode[i] 	=	5	;	    i++	;
	//Dtemp_TrimCode[i] 	=	6	;	 Dtemp_TrimWt[i] 	=	6	;	Dtemp_SignCode[i] 	=	6	;	    i++	;
	//Dtemp_TrimCode[i] 	=	7	;	 Dtemp_TrimWt[i] 	=	7	;	Dtemp_SignCode[i] 	=	7	;	    i++	;
	//Dtemp_TrimCode[i] 	=	8	;	 Dtemp_TrimWt[i] 	=	-8	;	Dtemp_SignCode[i] 	=	-8	;	    i++	;
	//Dtemp_TrimCode[i] 	=	9	;	 Dtemp_TrimWt[i] 	=	-7	;	Dtemp_SignCode[i] 	=	-7	;	    i++	;
	//Dtemp_TrimCode[i] 	=	10	;	 Dtemp_TrimWt[i] 	=	-6	;	Dtemp_SignCode[i] 	=	-6	;	    i++	;
	//Dtemp_TrimCode[i] 	=	11	;	 Dtemp_TrimWt[i] 	=	-5	;	Dtemp_SignCode[i] 	=	-5	;	    i++	;
	//Dtemp_TrimCode[i] 	=	12	;	 Dtemp_TrimWt[i] 	=	-4	;	Dtemp_SignCode[i] 	=	-4	;	    i++	;
	//Dtemp_TrimCode[i] 	=	13	;	 Dtemp_TrimWt[i] 	=	-3	;	Dtemp_SignCode[i] 	=	-3	;	    i++	;
	//Dtemp_TrimCode[i] 	=	14	;	 Dtemp_TrimWt[i] 	=	-2	;	Dtemp_SignCode[i] 	=	-2	;	    i++	;
	//Dtemp_TrimCode[i] 	=	15	;	 Dtemp_TrimWt[i] 	=	-1	;	Dtemp_SignCode[i] 	=	-1	;	    i++	;

	i = 0;
	Dtemp_TrimCode[i] 	=	0	;	 Dtemp_TrimWt[i] 	=	0	;	Dtemp_SignCode[i] 	=	0	;	    i++	;
	Dtemp_TrimCode[i] 	=	1	;	 Dtemp_TrimWt[i] 	=	-1	;	Dtemp_SignCode[i] 	=	-1	;	    i++	;
	Dtemp_TrimCode[i] 	=	2	;	 Dtemp_TrimWt[i] 	=	-2	;	Dtemp_SignCode[i] 	=	-2	;	    i++	;
	Dtemp_TrimCode[i] 	=	3	;	 Dtemp_TrimWt[i] 	=	-3	;	Dtemp_SignCode[i] 	=	-3	;	    i++	;
	Dtemp_TrimCode[i] 	=	4	;	 Dtemp_TrimWt[i] 	=	-4	;	Dtemp_SignCode[i] 	=	-4	;	    i++	;
	Dtemp_TrimCode[i] 	=	5	;	 Dtemp_TrimWt[i] 	=	-5	;	Dtemp_SignCode[i] 	=	-5	;	    i++	;
	Dtemp_TrimCode[i] 	=	6	;	 Dtemp_TrimWt[i] 	=	-6	;	Dtemp_SignCode[i] 	=	-6	;	    i++	;
	Dtemp_TrimCode[i] 	=	7	;	 Dtemp_TrimWt[i] 	=	-7	;	Dtemp_SignCode[i] 	=	-7	;	    i++	;
	Dtemp_TrimCode[i] 	=	8	;	 Dtemp_TrimWt[i] 	=	1.8	;	Dtemp_SignCode[i] 	=	1	;	    i++	;
	Dtemp_TrimCode[i] 	=	9	;	 Dtemp_TrimWt[i] 	=	2.8	;	Dtemp_SignCode[i] 	=	2	;	    i++	;
	Dtemp_TrimCode[i] 	=	10	;	 Dtemp_TrimWt[i] 	=	3.8	;	Dtemp_SignCode[i] 	=	3	;	    i++	;
	Dtemp_TrimCode[i] 	=	11	;	 Dtemp_TrimWt[i] 	=	4.8	;	Dtemp_SignCode[i] 	=	4	;	    i++	;
	Dtemp_TrimCode[i] 	=	12	;	 Dtemp_TrimWt[i] 	=	5.8	;	Dtemp_SignCode[i] 	=	5	;	    i++	;
	Dtemp_TrimCode[i] 	=	13	;	 Dtemp_TrimWt[i] 	=	6.8	;	Dtemp_SignCode[i] 	=	6	;	    i++	;
	Dtemp_TrimCode[i] 	=	14	;	 Dtemp_TrimWt[i] 	=	7.8	;	Dtemp_SignCode[i] 	=	7	;	    i++	;
	Dtemp_TrimCode[i] 	=	15	;	 Dtemp_TrimWt[i] 	=	8.8	;	Dtemp_SignCode[i] 	=	8	;	    i++	;


	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //

	// TsADC register bits 67 to 70
	//Pass Bank E8 trim registers data to the WordArray
	WordArray[0]  = g_TrimRegister_P[g_E8_start_bit];		//64 EndTTFB_0_P
	WordArray[1]  = g_TrimRegister_P[g_E8_start_bit +1];	//65 EndTTFB_1_P
	WordArray[2]  = g_TrimRegister_P[g_E8_start_bit +2];	//66 EndTTFB_2_P
	WordArray[3]  = g_TrimRegister_P[g_E8_start_bit +3];	//67 TsADC_0_P
	WordArray[4]  = g_TrimRegister_P[g_E8_start_bit +4];	//68 TsADC_1_P
	WordArray[5]  = g_TrimRegister_P[g_E8_start_bit +5];	//69 TsADC_2_P
	WordArray[6]  = g_TrimRegister_P[g_E8_start_bit +6]; 	//70 TsADC_3_P
	WordArray[7]  = g_TrimRegister_P[g_E8_start_bit +7]; 	//71 UV10pct_P
	WordArray[8]  = g_TrimRegister_P[g_E8_start_bit +8]; 	//72 IOV_0_P
	WordArray[9]  = g_TrimRegister_P[g_E8_start_bit +9]; 	//73 IOV_1_P
	WordArray[10] = g_TrimRegister_P[g_E8_start_bit +10]; 	//74 IOV_2_P
	WordArray[11] = g_TrimRegister_P[g_E8_start_bit +11]; 	//75 IOV_3_P
	WordArray[12] = g_TrimRegister_P[g_E8_start_bit +12]; 	//76 IOV_4_P
	WordArray[13] = g_TrimRegister_P[g_E8_start_bit +13]; 	//77 TonM_0_P
	WordArray[14] = g_TrimRegister_P[g_E8_start_bit +14]; 	//78 TonM_1_P
	WordArray[15] = g_TrimRegister_P[g_E8_start_bit +15];	//79 TonM_2_P

	Pulse pulse; // External trigger pulse from dvi for debug //
	pulse.do_pulse();

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

	if(g_Load_previous_RegBits)	//Always set to 1 for PRODUCTION use at 4200 or 4200RTR
	{
		EEPROM_Write_Enable_P();
		Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
	}

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
		g_WAVE_NAME =  "Dtemp_Pre";
		Gage_Find_Dtemp_code(&Dtemp_pt_P, &tLong_Dtemp, &dbus1_HighByte, &tShort_Dtemp, &dbus1_LowByte);
																												//0000 1010
	dbus1_bit12_to_9	= dbus1_HighByte & 0x1E;	//bit 12 to 9	=> 0101 = vss, vdd, vss, vdd or 5 in decimal  xxx1 111x xxxx xxxx
	TS_Mode_NTC			= dbus1_HighByte & 0xE0;	//NTC mode		=> 000x of ZTSmode<2:0>


	if(TS_Mode_NTC == 0) TS_Mode_NTC = 1;			//NTC mode selected if 000 from ZTSmode<2:0>

	PiDatalog(func, A_dbus1_12_to_9,	dbus1_bit12_to_9,	ours->fail_bin, POWER_UNIT);
	PiDatalog(func, A_TSMode_NTC,		TS_Mode_NTC,		ours->fail_bin, POWER_UNIT);
	PiDatalog(func, A_tLong_Dtemp,		tLong_Dtemp*20e-9,	ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_tShort_Dtemp,		tShort_Dtemp*20e-9,	ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_Dtemp_pt_P,		Dtemp_pt_P,			ours->fail_bin, POWER_UNIT);
	PiDatalog(func, A_ITS_P,			ITS_P,				ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_Dtemp_target_P,	gP_Dtemp_TARGET_Trimops,	ours->fail_bin, POWER_UNIT);


	//*********************************************************************************************
	//*** Dtemp_P Simulation  Start ****************************************************************
	//*********************************************************************************************
	if(g_Sim_Enable_P)
	{
		// Find which trim code will make closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=15; i++)
		{
			temp_1 = (Dtemp_pt_P * (1 + (Dtemp_TrimWt[i]/100)) -  gP_Dtemp_TARGET_Trimops);
			if (fabs(temp_1) < fabs(smallest_diff_val))
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		Dtemp_BitCode_P = Dtemp_SignCode[smallest_diff_idx];
		Dtemp_TrCode_P  = Dtemp_TrimCode[smallest_diff_idx];
		Dtemp_ExpChg    = Dtemp_TrimWt[smallest_diff_idx];

		//Debug only start
			//Dtemp_TrCode_P = 7;	//expect sim result to be the same if 0.  
			//EEpr_Bank_P[E8]= 0;
		//Debug only stop

			PiDatalog(func, 	A_Dtemp_TrCode_P,   Dtemp_TrCode_P,					26, POWER_UNIT);
			PiDatalog(func, 	A_Dtemp_BitCode_P,  Dtemp_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Dtemp_ExpChg_P,   Dtemp_ExpChg,					26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr67_TsADC0_P,   (Dtemp_TrCode_P & 0x01)/1,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr68_TsADC1_P,   (Dtemp_TrCode_P & 0x02)/2,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr69_TsADC2_P,   (Dtemp_TrCode_P & 0x04)/4,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr70_TsADC3_P,   (Dtemp_TrCode_P & 0x08)/8,		26, POWER_UNIT);

		TrimCode_To_TrimBit(Dtemp_TrCode_P, "TsADC_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_TsADC - g_E8_start_bit;
		EEpr_Bank_P[E8] = EEpr_Bank_P[E8] | ( Dtemp_TrCode_P << TrCode_shift_n_bits );


		Regain_I2C_P(g_Vpin_Low_to_High);
		//EEPROM_Write_Enable_P();	//Only if you need to burn, then you need to do a Write Enable
		Program_Single_TrimRegister(g_EEP_W_E8);

		DSM_I2C_Write('b', 0x4C, 0x01);				//release TSPIN			
		Disable_n_Disconnect_DSMI2C_via(g_release_TSpin);

		//Force TSPIN voltage to 2.5V and observe lower 9bits for 256		
		TS_ovi3->set_voltage(TSovi3_ch, 2.5, VOLT_10_RANGE); // OVI_3_0
		delay(5);

		//Capture waveform and analyze
			Gage_Start_Capture(  );	
			Gage_Wait_For_Capture_Complete();
			g_WAVE_NAME =  "Dtemp_Sim";
			Gage_Find_Dtemp_code(&Dtemp_Sim_P, &tLong_Dtemp_Sim, &dbus1_HighByte_Sim, &tShort_Dtemp_Sim, &dbus1_LowByte_Sim);

			Dtemp_Sim_Chg_P = ((float)Dtemp_Sim_P/(float)Dtemp_pt_P -1.0)*100.0;

			PiDatalog(func, A_Dtemp_Sim,		Dtemp_Sim_P,		ours->fail_bin, POWER_UNIT);
			PiDatalog(func, A_Dtemp_Sim_Chg_P,	Dtemp_Sim_Chg_P,    ours->fail_bin, POWER_UNIT);

		//code_diff	= Dtemp_Sim_P - 256;
		//Dtemp_LSBmV	= 2.5/256.0;
		//if(code_diff < 0)	
		//	VTS_start = 2.5 - code_diff * Dtemp_LSBmV;
		//else				
		//	VTS_start = 2.5 + code_diff * Dtemp_LSBmV;

		//Force TSPIN voltage to 2.5V and observe lower 9bits for 256		
		//TS_ovi3->set_voltage(TSovi3_ch, VTS_start, VOLT_10_RANGE); // OVI_3_0

		//VTS_Stop = 1V
		TS_ovi3->set_voltage(TSovi3_ch, 1.0, VOLT_10_RANGE); // OVI_3_0		
		delay(5);

		//Capture waveform and analyze
			Gage_Start_Capture(  );	
			Gage_Wait_For_Capture_Complete();
			g_WAVE_NAME =  "Dtemp_VTS_stop";
			Gage_Find_Dtemp_code(&Dtemp_VTSstop_P, &tLong_Dtemp_VTSstop, &dbus1_HighByte_VTSstop, &tShort_Dtemp_VTSstop, &dbus1_LowByte_VTSstop);

			PiDatalog(func, A_VTSstop_511,		Dtemp_VTSstop_P,		ours->fail_bin, POWER_UNIT);
	}

	Power_Down_I2C_P();
	Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0		disconnect
	Open_relay(K10_D_TB);	//D  to RDS_BUF									disconnect
	delay(1);

}
