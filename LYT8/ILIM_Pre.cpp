//==============================================================================
// ILIM_Pre.cpp (User function)
// 
//    void ILIM_Pre_user_init(test_function& func)
//    void ILIM_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "ILIM_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_Pre_user_init(test_function& func)
{
	ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_ILIM_Tr_P, gFuncNum, 9, POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Trim_Enable_P set //
	//if (g_Trim_Enable_P == 0)	return;

	//if (g_Fn_ILIM_Pre == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	float	ILIM_pt_P = 0;
	int		ILIM_TrCode_P	=0;
	int		ILIM_BitCode_P	=0;

	float	ILIM_Sim_P		=0;	
	float	ILIM_Sim_Chg_P	=0;	
	float	ILIM_ExpChg_P	=0;	
	float	ILIM_pst_P		=0;	
	float	ILIM_Pre_TT		=0;	
	float	ILIM_P_TrimWt[32]	=	{0.0};
	float	ILIM_P_TrCode[32]	=	{0.0};
	float	ILIM_P_SignCode[32]	=	{0.0};
	float	ILIM_char[32]		=   {0.0};
	float	ILIM_char_didt[32]	=   {0.0};
	float	ILIM_char_ton[32]	=   {0.0};

	float	smallest_diff_val			=	999999.9;
	float	temp_1						=	0;
	int		smallest_diff_idx			=	0;
	float	tmeas[20]					= {0};	
	int		i=0, j=0;		

	float ILIM_pt_didt_P = 0;
	float ILIM_pt_ton_P = 0;
	float ILIM_Sim_didt_P = 0;
	float ILIM_Sim_ton_P = 0;

	// Declare Variables //
	//int NObin[1] = {0}; // Place holder //
	//int NOhex = 0; // Place holder //
	float Dummy_rdson_peak = 0.0;
	float Dummy_rdson_spec;
	//float PV3_Charge =0.0;
	//float Vped_meas  =0.0;
	//float Vpv3_meas  =0.0;
	//int lcnt=0;
	//float ChB_vrng=0.0;
	//int vrng_b	=0.0;

	int		TrCode_shift_n_bits	=0;

	int		pE0_data[33] = {0};
	int		pE2_data[33] = {0};
	int		pE4_data[33] = {0};
	int		pE6_data[33] = {0};
	int		pE8_data[33] = {0};


	i = 0;																
	ILIM_P_TrCode[i] 	=	0	;		ILIM_P_SignCode[i] 	=	0.00	;		 ILIM_P_TrimWt[i] 	=	0.00	;		    i++	;
	ILIM_P_TrCode[i] 	=	1	;		ILIM_P_SignCode[i] 	=	2.50	;		 ILIM_P_TrimWt[i] 	=	1.45	;		    i++	;
	ILIM_P_TrCode[i] 	=	2	;		ILIM_P_SignCode[i] 	=	5.00	;		 ILIM_P_TrimWt[i] 	=	3.47	;		    i++	;
	ILIM_P_TrCode[i] 	=	3	;		ILIM_P_SignCode[i] 	=	7.50	;		 ILIM_P_TrimWt[i] 	=	5.49	;		    i++	;
	ILIM_P_TrCode[i] 	=	4	;		ILIM_P_SignCode[i] 	=	10.00	;		 ILIM_P_TrimWt[i] 	=	8.34	;		    i++	;
	ILIM_P_TrCode[i] 	=	5	;		ILIM_P_SignCode[i] 	=	12.50	;		 ILIM_P_TrimWt[i] 	=	10.01	;		    i++	;
	ILIM_P_TrCode[i] 	=	6	;		ILIM_P_SignCode[i] 	=	15.00	;		 ILIM_P_TrimWt[i] 	=	11.91	;		    i++	;
	ILIM_P_TrCode[i] 	=	7	;		ILIM_P_SignCode[i] 	=	17.50	;		 ILIM_P_TrimWt[i] 	=	14.83	;		    i++	;
	ILIM_P_TrCode[i] 	=	8	;		ILIM_P_SignCode[i] 	=	20.00	;		 ILIM_P_TrimWt[i] 	=	16.73	;		    i++	;
	ILIM_P_TrCode[i] 	=	9	;		ILIM_P_SignCode[i] 	=	22.50	;		 ILIM_P_TrimWt[i] 	=	19.06	;		    i++	;
	ILIM_P_TrCode[i] 	=	10	;		ILIM_P_SignCode[i] 	=	25.00	;		 ILIM_P_TrimWt[i] 	=	21.12	;		    i++	;
	ILIM_P_TrCode[i] 	=	11	;		ILIM_P_SignCode[i] 	=	27.50	;		 ILIM_P_TrimWt[i] 	=	23.78	;		    i++	;
	ILIM_P_TrCode[i] 	=	12	;		ILIM_P_SignCode[i] 	=	30.00	;		 ILIM_P_TrimWt[i] 	=	25.86	;		    i++	;
	ILIM_P_TrCode[i] 	=	13	;		ILIM_P_SignCode[i] 	=	32.50	;		 ILIM_P_TrimWt[i] 	=	27.97	;		    i++	;
	ILIM_P_TrCode[i] 	=	14	;		ILIM_P_SignCode[i] 	=	35.00	;		 ILIM_P_TrimWt[i] 	=	29.84	;		    i++	;
	ILIM_P_TrCode[i] 	=	15	;		ILIM_P_SignCode[i] 	=	37.50	;		 ILIM_P_TrimWt[i] 	=	32.59	;		    i++	;
	ILIM_P_TrCode[i] 	=	16	;		ILIM_P_SignCode[i] 	=	-40.00	;		 ILIM_P_TrimWt[i] 	=	-36.57	;		    i++	;
	ILIM_P_TrCode[i] 	=	17	;		ILIM_P_SignCode[i] 	=	-37.50	;		 ILIM_P_TrimWt[i] 	=	-34.72	;		    i++	;
	ILIM_P_TrCode[i] 	=	18	;		ILIM_P_SignCode[i] 	=	-35.00	;		 ILIM_P_TrimWt[i] 	=	-32.23	;		    i++	;
	ILIM_P_TrCode[i] 	=	19	;		ILIM_P_SignCode[i] 	=	-32.50	;		 ILIM_P_TrimWt[i] 	=	-30.01	;		    i++	;
	ILIM_P_TrCode[i] 	=	20	;		ILIM_P_SignCode[i] 	=	-30.00	;		 ILIM_P_TrimWt[i] 	=	-27.94	;		    i++	;
	ILIM_P_TrCode[i] 	=	21	;		ILIM_P_SignCode[i] 	=	-27.50	;		 ILIM_P_TrimWt[i] 	=	-25.85	;		    i++	;
	ILIM_P_TrCode[i] 	=	22	;		ILIM_P_SignCode[i] 	=	-25.00	;		 ILIM_P_TrimWt[i] 	=	-23.79	;		    i++	;
	ILIM_P_TrCode[i] 	=	23	;		ILIM_P_SignCode[i] 	=	-22.50	;		 ILIM_P_TrimWt[i] 	=	-21.22	;		    i++	;
	ILIM_P_TrCode[i] 	=	24	;		ILIM_P_SignCode[i] 	=	-20.00	;		 ILIM_P_TrimWt[i] 	=	-19.03	;		    i++	;
	ILIM_P_TrCode[i] 	=	25	;		ILIM_P_SignCode[i] 	=	-17.50	;		 ILIM_P_TrimWt[i] 	=	-16.76	;		    i++	;
	ILIM_P_TrCode[i] 	=	26	;		ILIM_P_SignCode[i] 	=	-15.00	;		 ILIM_P_TrimWt[i] 	=	-14.30	;		    i++	;
	ILIM_P_TrCode[i] 	=	27	;		ILIM_P_SignCode[i] 	=	-12.50	;		 ILIM_P_TrimWt[i] 	=	-12.12	;		    i++	;
	ILIM_P_TrCode[i] 	=	28	;		ILIM_P_SignCode[i] 	=	-10.00	;		 ILIM_P_TrimWt[i] 	=	-10.04	;		    i++	;
	ILIM_P_TrCode[i] 	=	29	;		ILIM_P_SignCode[i] 	=	-7.50	;		 ILIM_P_TrimWt[i] 	=	-7.54	;		    i++	;
	ILIM_P_TrCode[i] 	=	30	;		ILIM_P_SignCode[i] 	=	-5.00	;		 ILIM_P_TrimWt[i] 	=	-5.46	;		    i++	;
	ILIM_P_TrCode[i] 	=	31	;		ILIM_P_SignCode[i] 	=	-2.50	;		 ILIM_P_TrimWt[i] 	=	-3.70	;		    i++	;




	Pulse pulse; // External trigger pulse from dvi for debug //

	//Decide what Inductor pullup voltage to use per FET SIZE
	gVind_RM = 42.5;	//size x8

	PV3_CHARGE_ON(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	g_SAMPLE_SIZE = GAGE_POST_32K;
	BINNO_Gage_ChanAB_setup(0.15);	// Only do it if g_SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)
	//vrng_b = 0;
	//ChB_vrng = 0;
	
	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	if (g_Trim_Enable_P != 0)
	{
		EEPROM_Write_Enable_P();
		Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
	}

	DSM_I2C_Write('b', g_TM_CTRL, 0x06);		//0x40, 0x06 (enable analog mode + core_en)
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x2804
	DSM_I2C_Write('w', 0x44, 0x0402);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
	DSM_I2C_Write('b', 0x4C, 0x01);				//release TS pin

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

	//--------------------------------------------------------------------------------------------
	//Setup for TS to run 100kHz
		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);


	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	wait.delay_10_us(10);

	Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
	Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
	delay(4);

	TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
	wait.delay_10_us(10);

	if(0)	//Observe from RL pullup
	{
		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
		Close_relay(K2_D_RB);
		delay(4);
			D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
			delay(1);
			D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE); // DVI_11_0
			delay(1);
	}
	else	//Observe from Inductor pullup
	{
		//Connect Drain to IM with PV3
		Close_relay(K3_D_TB);	// disconnect	Drain from RL pullup 
		Close_relay(K9_D_TB);	// Connect		Drain to CT- to Pearson to CT+ & CT2+
				//Close_relay(K1_D_RB);	// Connect		Iped to CT2+ to CT2-
		Close_relay(K1_IM_TB);	// Connect		Vind to CT2+ to CT2-
		delay(5);
		PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
	}

	BPP_zigzag(5.5, 4.3, 5.3);

		Load_100Khz_Pulses_TS();
		wait.delay_10_us(50);
	Gage_Start_Capture(  );
		Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		wait.delay_10_us(50);
	Gage_Wait_For_Capture_Complete();
	pv3_4->drive_off();	
		Stop_100Khz_Pulses_TS();

DEBUG=0;
g_Debug=0;
	g_WAVE_NAME =  "ILIM_Pre";
	g_FIND_RDSON_Peak_FLAG = 0;
	Gage_Find_Ilim(&ILIM_pt_P, &ILIM_pt_didt_P, &ILIM_pt_ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);
DEBUG=0;
g_Debug=0;

	PiDatalog(func, A_ILIM_pt_P,		ILIM_pt_P,					ours->fail_bin, POWER_MILLI);
	PiDatalog(func, A_ILIM_pt_didt_P,	ILIM_pt_didt_P,				ours->fail_bin, POWER_MILLI);
	PiDatalog(func, A_ILIM_pt_ton_P,	ILIM_pt_ton_P,				ours->fail_bin, POWER_MICRO);
	PiDatalog(func, A_ILIM_target_P,	gP_ILIM_TARGET_Trimops,	ours->fail_bin, POWER_MILLI);
	
	//*********************************************************************************************
	//*** ILIM_P Simulation  Start ****************************************************************
	//*********************************************************************************************
	if(g_Trim_Enable_P)
	{
		// Find which trim code will make ILIM_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			temp_1 = (ILIM_pt_P * (1 + (ILIM_P_TrimWt[i]/100)) -  gP_ILIM_TARGET_Trimops);
			if (fabs(temp_1) < fabs(smallest_diff_val))
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		//Debug only start for Manual forcing
			//smallest_diff_idx	= 5;	//expect sim result to be the same if 0.  
			//EEpr_Bank_P[E2]		= 0;	//
		//Debug only stop for Manual forcing

		ILIM_TrCode_P   = smallest_diff_idx;
		ILIM_TrCode_P   = ILIM_P_TrCode[smallest_diff_idx];
		ILIM_BitCode_P  = ILIM_P_SignCode[smallest_diff_idx];
		ILIM_ExpChg_P     = ILIM_P_TrimWt[smallest_diff_idx];
		//ILIM_ExpHz_P		= (ILIM_P_TrimWt[smallest_diff_idx]/100 +1)*ILIM_pt_P - ILIM_pt_P;

			PiDatalog(func, 	A_ILIM_TrCode_P,	ILIM_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_ILIM_BitCode_P,	ILIM_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_ILIM_ExpChg_P,	ILIM_ExpChg_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr16_ILIM0_P,	(ILIM_TrCode_P & 0x01)/1,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr17_ILIM1_P,	(ILIM_TrCode_P & 0x02)/2,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr18_ILIM2_P,	(ILIM_TrCode_P & 0x04)/4,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr19_ILIM3_P,	(ILIM_TrCode_P & 0x08)/8,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr20_ILIM4_P,	(ILIM_TrCode_P & 0x08)/16,		26, POWER_UNIT);

		TrimCode_To_TrimBit(ILIM_TrCode_P, "ILIM_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_ILIM - g_E2_start_bit;
		EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( ILIM_TrCode_P << TrCode_shift_n_bits );

		//Program in the trimcode
			Stop_100Khz_Pulses_TS();
			TS_ovi->set_voltage(TSovi1_ch, 0.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			Open_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Connect DSM from Primary after releasing VPIN or TS pins
			Close_relay(K1_DSM_TB);	
			Close_relay(K3_DSM_TB);	
			delay(4);
			TS_ovi3->set_voltage(TSovi3_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
		Program_Single_TrimRegister(g_EEP_W_E2);



			Stop_100Khz_Pulses_TS();
			TS_ovi->set_voltage(TSovi1_ch, 0.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			Open_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Connect DSM from Primary after releasing VPIN or TS pins
			Close_relay(K1_DSM_TB);	
			Close_relay(K3_DSM_TB);	
			delay(4);
			TS_ovi3->set_voltage(TSovi3_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);

			Program_Single_TrimRegister(g_EEP_W_E2);
			wait.delay_10_us(1);

			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);


			PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
			delay(15);
			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);

				Load_100Khz_Pulses_TS();
				wait.delay_10_us(50);
			Gage_Start_Capture(  );
				Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
				wait.delay_10_us(50);
			Gage_Wait_For_Capture_Complete();
			pv3_4->drive_off();	
				Stop_100Khz_Pulses_TS();
			
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);

			Gage_Find_Ilim(&ILIM_Sim_P, &ILIM_Sim_didt_P, &ILIM_Sim_ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);

			ILIM_Sim_Chg_P = (ILIM_Sim_P/ILIM_pt_P -1.0)*100.0;

			PiDatalog(func, A_ILIM_Sim_P,		ILIM_Sim_P,			ours->fail_bin, POWER_UNIT);
			PiDatalog(func, A_ILIM_SimChg_P,	ILIM_Sim_Chg_P,		ours->fail_bin, POWER_UNIT);
	}
	//*********************************************************************************************
	//*** ILIM_P Simulation  End ******************************************************************
	//*********************************************************************************************




	//---- ILIM_Sim Bitweight CHAR starts --------------------------------- 
	//For bitweight char only (TEST Engineer will need to manually measure from scope)
	if(0)
	{
		ILIM_char[0] = ILIM_pt_P;
			//PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
			//delay(15);


		////	Stop_100Khz_Pulses_TS();
		////	TS_ovi->set_voltage(TSovi1_ch, 0.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
		////	wait.delay_10_us(10);
		////	Open_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
		////	Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
		////	//Connect DSM from Primary after releasing VPIN or TS pins
		////	Close_relay(K1_DSM_TB);	
		////	Close_relay(K3_DSM_TB);	
		////	delay(4);
		////	TS_ovi3->set_voltage(TSovi3_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
		////	wait.delay_10_us(10);
		////EEPROM_Read_Enable_P();
		////pE0_data[0] = DSM_I2C_Read(g_EEP_R_C0); //Read data[0] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		////pE2_data[0] = DSM_I2C_Read(g_EEP_R_C2); //Read data[0] of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
		////pE4_data[0] = DSM_I2C_Read(g_EEP_R_C4); //Read data[0] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
		////pE6_data[0] = DSM_I2C_Read(g_EEP_R_C6); //Read data[0] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
		////pE8_data[0] = DSM_I2C_Read(g_EEP_R_C8); //Read data[0] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		//for(i=1; i<=31; i++)
		for(i=1; i<=31; i++)	//PVI IS ONLY GOOD FOR MAX 3 SIMS 
		{
			smallest_diff_idx	= i;	//expect sim result to be the same if 0.  
			EEpr_Bank_P[E2]		= 0;	//
			ILIM_TrCode_P   = smallest_diff_idx;
			ILIM_TrCode_P   = ILIM_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(ILIM_TrCode_P, "ILIM_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_ILIM - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( ILIM_TrCode_P << TrCode_shift_n_bits );

			Stop_100Khz_Pulses_TS();
			TS_ovi->set_voltage(TSovi1_ch, 0.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			Open_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Connect DSM from Primary after releasing VPIN or TS pins
			Close_relay(K1_DSM_TB);	
			Close_relay(K3_DSM_TB);	
			delay(4);
			TS_ovi3->set_voltage(TSovi3_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);

			Program_Single_TrimRegister(g_EEP_W_E2);
			wait.delay_10_us(1);

			//EEPROM_Read_Enable_P();
			//pE0_data[i] = DSM_I2C_Read(g_EEP_R_C0); //Read data[i] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
			//pE2_data[i] = DSM_I2C_Read(g_EEP_R_C2); //Read data[i] of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
			//pE4_data[i] = DSM_I2C_Read(g_EEP_R_C4); //Read data[i] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
			//pE6_data[i] = DSM_I2C_Read(g_EEP_R_C6); //Read data[i] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
			//pE8_data[i] = DSM_I2C_Read(g_EEP_R_C8); //Read data[i] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00


			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);


			PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
			delay(15);
			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);

				Load_100Khz_Pulses_TS();
				wait.delay_10_us(50);
			Gage_Start_Capture(  );
				Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
				wait.delay_10_us(50);
			Gage_Wait_For_Capture_Complete();
			pv3_4->drive_off();	
				Stop_100Khz_Pulses_TS();
			
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);

			Gage_Find_Ilim(&ILIM_char[i], &ILIM_char_didt[i], &ILIM_char_ton[i], &Dummy_rdson_peak, &Dummy_rdson_spec);
		}
	}
	//---- ILIM_Sim Bitweight CHAR stop --------------------------------- 

	pv3_4->drive_off();	

	pv3_4->set_current(0.1e-9);						
	pv3_4->set_voltage(0, RANGE_100_V);
	wait.delay_10_us(10);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_1);
	pv3_4->open_switch(PV3_HIGH_SENSE_1);
	delay(1);
	pv3_4->charge_on();	

	Power_Down_I2C_P();
	Open_relay(K2_D_RB);				//D			to RB_82uH_50ohm to K2_D to DVI-11-0		Disconnect
	Open_relay(K2_TS_TB);				//TS		to OVI_3_0_TS_RB							Connect
	Open_relay(K3_TS_IB);				//DDD7_1	to Comparator LT1719 to COMP_OUT to TS		Disconnect

	//disconnect Drain from IM
	Open_relay(K3_D_TB);	// Connect			Drain to RL pullup 
	Open_relay(K9_D_TB);	// disConnect		Drain to CT2-
	//Open_relay(K1_D_RB);	// disConnect		Iped to CT2+ to CT2-
	Open_relay(K1_IM_TB);	// disConnect		Vind to CT2+ to CT2-
	delay(1);



/*
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		ILIM_Pre_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_ILIM_Pre_TT, ILIM_Pre_TT, 9, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
