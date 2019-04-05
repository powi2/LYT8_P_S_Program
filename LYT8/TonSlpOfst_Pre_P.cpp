//==============================================================================
// TonSlpOfst_Pre_P.cpp (User function)
// 
//    void TonSlpOfst_Pre_P_user_init(test_function& func)
//    void TonSlpOfst_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "TonSlpOfst_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TonSlpOfst_Pre_P_user_init(test_function& func)
{
	TonSlpOfst_Pre_P_params *ours;
    ours = (TonSlpOfst_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TonSlpOfst_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TonSlpOfst_Pre_P_params *ours;
    ours = (TonSlpOfst_Pre_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_SLO_Tr_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	//// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	//if (g_Fn_Ton_Pre_P == 0 )  return;

	float	Ton_30kHz_pt_P	=0;
	float	Ton_80kHz_pt_P	=0;
	float	Ton_30kHz_Sim_P	=0;
	float	Ton_80kHz_Sim_P	=0;
	float	dx	=99;
	float	dy	=0;
	float	Slope_pt_P	=0;
	int		Slope_TrCode_P	=0;
	float	Slope_BitCode_P	=0;

	
	float	Slope_Sim_P		=0;	
	float	Slope_Sim_Chg_P	=0;	
	float	Slope_ExpChg_P	=0;	
	float	Slope_pst_P		=0;	
	float	Slope_Pre_TT		=0;	
	float	Slope_P_TrimWt[32]	=	{0.0};
	float	Slope_P_TrCode[32]	=	{0.0};
	float	Slope_P_SignCode[32]	=	{0.0};
	float	Slope_char[32]		=   {0.0};
	float	Ton_30kHz_char[32]		=	{0.0};
	float	Ton_80kHz_char[32]		=	{0.0};
	float	smallest_diff_val			=	999999.9;
	float	temp_1						=	0;
	int		smallest_diff_idx			=	0;
	float	tmeas[20]					= {0};	
	int		i=0, j=0;		

	float	Offset_pt_P			=0;	
	float	Offset_pt1_P		=0;	
	float	Offset_pst1_P		=0;
	int		Offset_TrCode_P		=0;	
	float 	Offset_BitCode_P	=0;	
	float	Offset_Sim_P		=0;	
	float	Offset_SimChg_P		=0;	
	float	Offset_ExpChg_P		=0;	
	float	Offset_pst_P		=0;	
	float	Offset_Pre_TT		=0;	
	float	Offset_P_TrimWt[32]		=	{0.0};
	float	Offset_P_TrCode[32]		=	{0.0};
	float	Offset_P_SignCode[32]	=	{0.0};
	float	Offset_char[32]			=   {0.0};

	int		TrCode_shift_n_bits	=0;

	int		pE0_data[33] = {0};
	int		pE2_data[33] = {0};
	int		pE4_data[33] = {0};
	int		pE6_data[33] = {0};
	int		pE8_data[33] = {0};


	i=0;
	Slope_P_TrCode[i] 	=	0	;		Slope_P_SignCode[i] 	=	0	;		 Slope_P_TrimWt[i] 	=	0.00	;		    i++	;
	Slope_P_TrCode[i] 	=	1	;		Slope_P_SignCode[i] 	=	6	;		 Slope_P_TrimWt[i] 	=	-5.66	;		    i++	;
	Slope_P_TrCode[i] 	=	2	;		Slope_P_SignCode[i] 	=	12	;		 Slope_P_TrimWt[i] 	=	-10.71	;		    i++	;
	Slope_P_TrCode[i] 	=	3	;		Slope_P_SignCode[i] 	=	18	;		 Slope_P_TrimWt[i] 	=	-15.25	;		    i++	;
	Slope_P_TrCode[i] 	=	4	;		Slope_P_SignCode[i] 	=	24	;		 Slope_P_TrimWt[i] 	=	-19.35	;		    i++	;
	Slope_P_TrCode[i] 	=	5	;		Slope_P_SignCode[i] 	=	30	;		 Slope_P_TrimWt[i] 	=	-23.08	;		    i++	;
	Slope_P_TrCode[i] 	=	6	;		Slope_P_SignCode[i] 	=	36	;		 Slope_P_TrimWt[i] 	=	-26.47	;		    i++	;
	Slope_P_TrCode[i] 	=	7	;		Slope_P_SignCode[i] 	=	42	;		 Slope_P_TrimWt[i] 	=	-29.58	;		    i++	;
	Slope_P_TrCode[i] 	=	8	;		Slope_P_SignCode[i] 	=	48	;		 Slope_P_TrimWt[i] 	=	-32.43	;		    i++	;
	Slope_P_TrCode[i] 	=	9	;		Slope_P_SignCode[i] 	=	54	;		 Slope_P_TrimWt[i] 	=	-35.06	;		    i++	;
	Slope_P_TrCode[i] 	=	10	;		Slope_P_SignCode[i] 	=	60	;		 Slope_P_TrimWt[i] 	=	-37.50	;		    i++	;
	Slope_P_TrCode[i] 	=	11	;		Slope_P_SignCode[i] 	=	66	;		 Slope_P_TrimWt[i] 	=	-39.76	;		    i++	;
	Slope_P_TrCode[i] 	=	12	;		Slope_P_SignCode[i] 	=	72	;		 Slope_P_TrimWt[i] 	=	-41.86	;		    i++	;
	Slope_P_TrCode[i] 	=	13	;		Slope_P_SignCode[i] 	=	78	;		 Slope_P_TrimWt[i] 	=	-43.82	;		    i++	;
	Slope_P_TrCode[i] 	=	14	;		Slope_P_SignCode[i] 	=	84	;		 Slope_P_TrimWt[i] 	=	-45.65	;		    i++	;
	Slope_P_TrCode[i] 	=	15	;		Slope_P_SignCode[i] 	=	90	;		 Slope_P_TrimWt[i] 	=	-47.37	;		    i++	;
	Slope_P_TrCode[i] 	=	16	;		Slope_P_SignCode[i] 	=	-6	;		 Slope_P_TrimWt[i] 	=	6.38	;		    i++	;
	Slope_P_TrCode[i] 	=	17	;		Slope_P_SignCode[i] 	=	-12	;		 Slope_P_TrimWt[i] 	=	13.64	;		    i++	;
	Slope_P_TrCode[i] 	=	18	;		Slope_P_SignCode[i] 	=	-18	;		 Slope_P_TrimWt[i] 	=	21.95	;		    i++	;
	Slope_P_TrCode[i] 	=	19	;		Slope_P_SignCode[i] 	=	-24	;		 Slope_P_TrimWt[i] 	=	31.58	;		    i++	;
	Slope_P_TrCode[i] 	=	20	;		Slope_P_SignCode[i] 	=	-30	;		 Slope_P_TrimWt[i] 	=	42.86	;		    i++	;
	Slope_P_TrCode[i] 	=	21	;		Slope_P_SignCode[i] 	=	-36	;		 Slope_P_TrimWt[i] 	=	56.25	;		    i++	;
	Slope_P_TrCode[i] 	=	22	;		Slope_P_SignCode[i] 	=	-42	;		 Slope_P_TrimWt[i] 	=	72.41	;		    i++	;
	Slope_P_TrCode[i] 	=	23	;		Slope_P_SignCode[i] 	=	-48	;		 Slope_P_TrimWt[i] 	=	92.31	;		    i++	;
	Slope_P_TrCode[i] 	=	24	;		Slope_P_SignCode[i] 	=	-54	;		 Slope_P_TrimWt[i] 	=	117.39	;		    i++	;
	Slope_P_TrCode[i] 	=	25	;		Slope_P_SignCode[i] 	=	-60	;		 Slope_P_TrimWt[i] 	=	150.00	;		    i++	;
	Slope_P_TrCode[i] 	=	26	;		Slope_P_SignCode[i] 	=	-66	;		 Slope_P_TrimWt[i] 	=	194.12	;		    i++	;
	Slope_P_TrCode[i] 	=	27	;		Slope_P_SignCode[i] 	=	-72	;		 Slope_P_TrimWt[i] 	=	257.14	;		    i++	;
	Slope_P_TrCode[i] 	=	28	;		Slope_P_SignCode[i] 	=	-78	;		 Slope_P_TrimWt[i] 	=	354.55	;		    i++	;
	Slope_P_TrCode[i] 	=	29	;		Slope_P_SignCode[i] 	=	-84	;		 Slope_P_TrimWt[i] 	=	525.00	;		    i++	;
	Slope_P_TrCode[i] 	=	30	;		Slope_P_SignCode[i] 	=	-90	;		 Slope_P_TrimWt[i] 	=	900.00	;		    i++	;
	Slope_P_TrCode[i] 	=	31	;		Slope_P_SignCode[i] 	=	-96	;		 Slope_P_TrimWt[i] 	=	2400.00	;		    i++	;


	//E2 bits for Slope
	/*
		Slope_4_P	bit 30
		Slope_3_P	bit 29
		Slope_2_P	bit 28
		Slope_1_P	bit 27
		Slope_0_P	bit 26
	*/

	i = 0;																
	Offset_P_TrCode[i] 	=	0	;		Offset_P_SignCode[i] 	=	0.000	;		 Offset_P_TrimWt[i] 	=	0.00	;		    i++	;
	Offset_P_TrCode[i] 	=	1	;		Offset_P_SignCode[i] 	=	1.563	;		 Offset_P_TrimWt[i] 	=	17.26	;		    i++	;
	Offset_P_TrCode[i] 	=	2	;		Offset_P_SignCode[i] 	=	3.125	;		 Offset_P_TrimWt[i] 	=	18.85	;		    i++	;
	Offset_P_TrCode[i] 	=	3	;		Offset_P_SignCode[i] 	=	4.688	;		 Offset_P_TrimWt[i] 	=	20.26	;		    i++	;
	Offset_P_TrCode[i] 	=	4	;		Offset_P_SignCode[i] 	=	-18.750	;		 Offset_P_TrimWt[i] 	=	-5.21	;		    i++	;
	Offset_P_TrCode[i] 	=	5	;		Offset_P_SignCode[i] 	=	-17.188	;		 Offset_P_TrimWt[i] 	=	-2.98	;		    i++	;
	Offset_P_TrCode[i] 	=	6	;		Offset_P_SignCode[i] 	=	-15.625	;		 Offset_P_TrimWt[i] 	=	-1.06	;		    i++	;
	Offset_P_TrCode[i] 	=	7	;		Offset_P_SignCode[i] 	=	-14.063	;		 Offset_P_TrimWt[i] 	=	0.81	;		    i++	;
	Offset_P_TrCode[i] 	=	8	;		Offset_P_SignCode[i] 	=	-12.500	;		 Offset_P_TrimWt[i] 	=	2.74	;		    i++	;
	Offset_P_TrCode[i] 	=	9	;		Offset_P_SignCode[i] 	=	-10.938	;		 Offset_P_TrimWt[i] 	=	4.61	;		    i++	;
	Offset_P_TrCode[i] 	=	10	;		Offset_P_SignCode[i] 	=	-9.375	;		 Offset_P_TrimWt[i] 	=	6.24	;		    i++	;
	Offset_P_TrCode[i] 	=	11	;		Offset_P_SignCode[i] 	=	-7.813	;		 Offset_P_TrimWt[i] 	=	8.16	;		    i++	;
	Offset_P_TrCode[i] 	=	12	;		Offset_P_SignCode[i] 	=	-6.250	;		 Offset_P_TrimWt[i] 	=	9.65	;		    i++	;
	Offset_P_TrCode[i] 	=	13	;		Offset_P_SignCode[i] 	=	-4.688	;		 Offset_P_TrimWt[i] 	=	11.30	;		    i++	;
	Offset_P_TrCode[i] 	=	14	;		Offset_P_SignCode[i] 	=	-3.125	;		 Offset_P_TrimWt[i] 	=	12.93	;		    i++	;
	Offset_P_TrCode[i] 	=	15	;		Offset_P_SignCode[i] 	=	-1.563	;		 Offset_P_TrimWt[i] 	=	14.45	;		    i++	;



	//E0 bits for Offset
	/*
		Offset_3_P	bit 15
		Offset_2_P	bit 14
		Offset_1_P	bit 13
		Offset_0_P	bit 12
	*/


	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	//Setup for Ton_Min measurement
	Close_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Connect
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);


	Pulse pulse;
	pulse.do_pulse();	


	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	if(g_Load_previous_RegBits)	//Always set to 1 for PRODUCTION use at 4200 or 4200RTR
	{
		EEPROM_Write_Enable_P();
		Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
	}

	DSM_I2C_Write('b', g_TM_CTRL, 0x02);	//0x40, 0x06 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x0024 (I2C password + observe drain 
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

	//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
	Close_relay(K2_D_RB);
	delay(4);
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
		delay(1);
		D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
		delay(1);
	
	BPP_zigzag(5.5, 4.3, 5.3);

		Load_30Khz_Pulses_TS();
		delay(1);
		Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		delay(1);
		//Observe 1.44us Ton_min at 30kHz TS request
		tmeas[1]=0;
		Ton_30kHz_pt_P=0;
		for(i=1; i<=10; i++)
		{
			tmeas[i]=0;		//reset array values before use again.
			tmu_6->arm();				
			wait.delay_10_us(10);
			tmeas[i] = tmu_6->read(100e-6);	
			Ton_30kHz_pt_P += tmeas[i];
		}
		Ton_30kHz_pt_P = Ton_30kHz_pt_P/10;


		tmu_6->stop_trigger_setup(0.3,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope

		pulse.do_pulse();	
		Load_80Khz_Pulses_TS();
		delay(1);
		Run_80Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		delay(1);
		//Observe that the part react to faster freq request and adjust Ton accordingly
		//The first two Ton is due to transient behavior.  We want to ignore them.
		//We need to observe from the 4th pulse and expect all Ton stays the same after the 4th pulse.
		//Observe 5.64us Ton_min at 80kHz TS request.
		Ton_80kHz_pt_P=0;
		for(i=1; i<=10; i++)
		{
			tmeas[i]=0;		//reset array values before use again.
			tmu_6->arm();				
			wait.delay_10_us(10);
			tmeas[i] = tmu_6->read(100e-6);	
			Ton_80kHz_pt_P += tmeas[i];
		}
		Ton_80kHz_pt_P = Ton_80kHz_pt_P/10;

		dy = Ton_80kHz_pt_P - Ton_30kHz_pt_P;
		dx = 80 - 30;
		Slope_pt_P = dy/dx;	//us/kHz

	//Datalog
	PiDatalog(func, A_Slope_pt_P,		Slope_pt_P,					14,	POWER_MICRO);	
	PiDatalog(func, A_Slope_target_P,	gP_Slope_TARGET_Trimops,	14,	POWER_MICRO);	

	//---------------------------------------------------------------------------------
	//------- Offset Before Slope_Sim Start ---------------------------
	//---------------------------------------------------------------------------------
	if(1)
	{
		//Find offset using formula y = mx + b where m = slope, x = known frequency in kHz, y = TonMin @ x 
		////Offset_pt_P = Ton_80kHz_pt_P - (Slope_pt_P * 80);
		//	Designer is using y = mx - b instead of y = mx + b.  Hence b = mx - y ==> Offset = (Slope * 80) - Ton_80k
		Offset_pt_P = (Slope_pt_P * 80) - Ton_80kHz_pt_P;

		PiDatalog(func, A_Offset_pt_P,		Offset_pt_P,				14,	POWER_MICRO);	
		PiDatalog(func, A_Offset_target_P,	gP_Offset_TARGET_Trimops,	14,	POWER_MICRO);	
	}
	//---------------------------------------------------------------------------------
	//------- Offset Before Slope_Sim Stop ---------------------------
	//---------------------------------------------------------------------------------

	//*********************************************************************************************
	//*** Slope_P Simulation Start ****************************************************************
	//*********************************************************************************************
	if(g_Sim_Enable_P)
	{
		// Find which trim code will make Slope_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			temp_1 = (Slope_pt_P * (1 + (Slope_P_TrimWt[i]/100)) -  gP_Slope_TARGET_Trimops);
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

		Slope_TrCode_P   = smallest_diff_idx;
		Slope_TrCode_P   = Slope_P_TrCode[smallest_diff_idx];
		Slope_BitCode_P  = Slope_P_SignCode[smallest_diff_idx];
		Slope_ExpChg_P     = Slope_P_TrimWt[smallest_diff_idx];
		//Slope_ExpHz_P		= (Slope_P_TrimWt[smallest_diff_idx]/100 +1)*Slope_pt_P - Slope_pt_P;

			PiDatalog(func, 	A_Slope_TrCode_P,	Slope_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Slope_BitCode_P,	Slope_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Slope_ExpChg_P,	Slope_ExpChg_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr26_Slp0_P,	(Slope_TrCode_P & 0x01)/1,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr27_Slp1_P,	(Slope_TrCode_P & 0x02)/2,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr28_Slp2_P,	(Slope_TrCode_P & 0x04)/4,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr29_Slp3_P,	(Slope_TrCode_P & 0x08)/8,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr30_Slp4_P,	(Slope_TrCode_P & 0x08)/16,		26, POWER_UNIT);

		TrimCode_To_TrimBit(Slope_TrCode_P, "Slope_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_OnTSL - g_E2_start_bit;
		EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( Slope_TrCode_P << TrCode_shift_n_bits );

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
		Program_Single_TrimRegister_P(g_EEP_W_E2);

		//TS setup for 30kHz and 80kHz toggling
			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);

		//Ton at TS_30kHz measurement
			tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
			Load_30Khz_Pulses_TS();
			delay(1);
			Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
			delay(1);
			//Observe 1.44us Ton_min at 30kHz TS request
			tmeas[1]=0;
			Ton_30kHz_Sim_P=0;
			for(j=1; j<=10; j++)
			{
				tmeas[j]=0;		//reset array values before use again.
				tmu_6->arm();				
				wait.delay_10_us(10);
				tmeas[j] = tmu_6->read(100e-6);	
				Ton_30kHz_Sim_P += tmeas[j];
			}
			Ton_30kHz_Sim_P = Ton_30kHz_Sim_P/10;


		//Ton at TS_80kHz measurement
			tmu_6->stop_trigger_setup(0.3,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
			Load_80Khz_Pulses_TS();
			delay(1);
			Run_80Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
			delay(1);
			//Observe that the part react to faster freq request and adjust Ton accordingly
			//The first two Ton is due to transient behavior.  We want to ignore them.
			//We need to observe from the 4th pulse and expect all Ton stays the same after the 4th pulse.
			//Observe 5.64us Ton_min at 80kHz TS request.
			Ton_80kHz_Sim_P=0;
			for(j=1; j<=10; j++)
			{
				tmeas[j]=0;		//reset array values before use again.
				tmu_6->arm();				
				wait.delay_10_us(10);
				tmeas[j] = tmu_6->read(100e-6);	
				Ton_80kHz_Sim_P += tmeas[j];
			}
			Ton_80kHz_Sim_P = Ton_80kHz_Sim_P/10;

		//Slope of simulated trimcode
			dy = Ton_80kHz_Sim_P - Ton_30kHz_Sim_P;
			dx = 80 - 30;
			Slope_Sim_P = dy/dx;	//us/kHz
			wait.delay_10_us(1);

			Slope_Sim_Chg_P = (Slope_Sim_P/Slope_pt_P -1.0)*100.0;

			PiDatalog(func, A_Slope_Sim_P,		Slope_Sim_P,			ours->fail_bin, POWER_MICRO);
			PiDatalog(func, A_Slope_SimChg_P,	Slope_Sim_Chg_P,		ours->fail_bin, POWER_UNIT);
	}

	//*********************************************************************************************
	//*** Slope_P Simulation Stop *****************************************************************
	//*********************************************************************************************



	//---- Slope_Sim Bitweight CHAR starts --------------------------------- 
	//For bitweight char only (TEST Engineer will need to manually measure from scope)
	if(0)
	{
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
		EEPROM_Read_Enable_P();
		pE0_data[0] = DSM_I2C_Read(g_EEP_R_C0); //Read data[0] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		pE2_data[0] = DSM_I2C_Read(g_EEP_R_C2); //Read data[0] of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
		pE4_data[0] = DSM_I2C_Read(g_EEP_R_C4); //Read data[0] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
		pE6_data[0] = DSM_I2C_Read(g_EEP_R_C6); //Read data[0] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
		pE8_data[0] = DSM_I2C_Read(g_EEP_R_C8); //Read data[0] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		for(i=1; i<=31; i++)
		{
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


			smallest_diff_idx	= i;	//expect sim result to be the same if 0.  
			EEpr_Bank_P[E2]		= 0;	//
			Slope_TrCode_P   = smallest_diff_idx;
			Slope_TrCode_P   = Slope_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(Slope_TrCode_P, "Slope_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_OnTSL - g_E2_start_bit;
			EEpr_Bank_P[E2] = EEpr_Bank_P[E2] | ( Slope_TrCode_P << TrCode_shift_n_bits );

			Program_Single_TrimRegister_P(g_EEP_W_E2);
			wait.delay_10_us(1);

		EEPROM_Read_Enable_P();
		pE0_data[i] = DSM_I2C_Read(g_EEP_R_C0); //Read data[i] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		pE2_data[i] = DSM_I2C_Read(g_EEP_R_C2); //Read data[i] of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
		pE4_data[i] = DSM_I2C_Read(g_EEP_R_C4); //Read data[i] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
		pE6_data[i] = DSM_I2C_Read(g_EEP_R_C6); //Read data[i] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
		pE8_data[i] = DSM_I2C_Read(g_EEP_R_C8); //Read data[i] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00


			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);


				tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
				Load_30Khz_Pulses_TS();
				delay(1);
				Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
				delay(1);
				//Observe 1.44us Ton_min at 30kHz TS request
				tmeas[1]=0;
				Ton_30kHz_pt_P=0;
				for(j=1; j<=10; j++)
				{
					tmeas[j]=0;		//reset array values before use again.
					tmu_6->arm();				
					wait.delay_10_us(10);
					tmeas[j] = tmu_6->read(100e-6);	
					Ton_30kHz_pt_P += tmeas[j];
				}
				Ton_30kHz_char[i] = Ton_30kHz_pt_P/10;


				tmu_6->stop_trigger_setup(0.3,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope

				pulse.do_pulse();	
				Load_80Khz_Pulses_TS();
				delay(1);
				Run_80Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
				delay(1);
				//Observe that the part react to faster freq request and adjust Ton accordingly
				//The first two Ton is due to transient behavior.  We want to ignore them.
				//We need to observe from the 4th pulse and expect all Ton stays the same after the 4th pulse.
				//Observe 5.64us Ton_min at 80kHz TS request.
				Ton_80kHz_pt_P=0;
				for(j=1; j<=10; j++)
				{
					tmeas[j]=0;		//reset array values before use again.
					tmu_6->arm();				
					wait.delay_10_us(10);
					tmeas[j] = tmu_6->read(100e-6);	
					Ton_80kHz_pt_P += tmeas[j];
				}
				Ton_80kHz_char[i] = Ton_80kHz_pt_P/10;

				dy = Ton_80kHz_pt_P - Ton_30kHz_pt_P;
				dx = 80 - 30;
				Slope_char[i] = dy/dx;	//us/kHz
				wait.delay_10_us(1);
		}
	}

	//---- Slope_Sim Bitweight CHAR stop --------------------------------- 



	//---------------------------------------------------------------------------------
	//------- Offset after Sim Start ---------------------------
	//---------------------------------------------------------------------------------
	if(g_Sim_Enable_P)
	{
		//Find offset using formula y = mx + b where m = slope, x = known frequency in kHz, y = TonMin @ x 
		////Offset_pt1_P = Ton_80kHz_Sim_P - (Slope_Sim_P * 80);
		//	Designer is using y = mx - b instead of y = mx + b.  Hence b = mx - y ==> Offset = (Slope * 80) - Ton_80k
		Offset_pt1_P	= (Slope_Sim_P * 80) - Ton_80kHz_Sim_P;
		Offset_pst1_P	= Offset_pt1_P + Ton_30kHz_Sim_P - 1.08666666667e-6;

		PiDatalog(func, A_Offset_pt1_P, Offset_pst1_P, 14,	POWER_MICRO);	
		//PiDatalog(func, A_Offset_pt1_P, Offset_pt1_P, 14,	POWER_MICRO);	
	}
	//---------------------------------------------------------------------------------
	//------- Offset after Sim Stop ---------------------------
	//---------------------------------------------------------------------------------

	
	//*********************************************************************************************
	//*** Offset Simulation Start ************************************************************************
	//*********************************************************************************************
	if(g_Sim_Enable_P)
	{
		// Find which trim code will make Offset_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			//temp_1 = (Offset_pt_P * (1 + (Offset_P_TrimWt[i]/100)) -  gP_Offset_TARGET_Trimops);
			temp_1 = (Offset_pst1_P * (1 + (Offset_P_TrimWt[i]/100)) -  gP_Offset_TARGET_Trimops);
			if (fabs(temp_1) < fabs(smallest_diff_val))
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		//Debug only start for Manual forcing
			//smallest_diff_idx	= 5;	//expect sim result to be the same if 0.  
			//EEpr_Bank_P[E0]		= 0;	//
		//Debug only stop for Manual forcing

		Offset_TrCode_P   = smallest_diff_idx;
		Offset_TrCode_P   = Offset_P_TrCode[smallest_diff_idx];
		Offset_BitCode_P  = Offset_P_SignCode[smallest_diff_idx];
		Offset_ExpChg_P   = Offset_P_TrimWt[smallest_diff_idx];
		//Offset_ExpHz_P		= (Offset_P_TrimWt[smallest_diff_idx]/100 +1)*Offset_pt_P - Offset_pt_P;

			PiDatalog(func, 	A_Offset_TrCode_P,	Offset_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_OffsetBitCode_P,	Offset_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Offset_ExpChg_P,	Offset_ExpChg_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr12_yInt0_P,	(Offset_TrCode_P & 0x01)/1,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr13_yInt1_P,	(Offset_TrCode_P & 0x02)/2,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr14_yInt2_P,	(Offset_TrCode_P & 0x04)/4,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr15_yInt3_P,	(Offset_TrCode_P & 0x08)/8,		26, POWER_UNIT);

		TrimCode_To_TrimBit(Offset_TrCode_P, "Offset_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_yInter - g_E0_start_bit;
		EEpr_Bank_P[E0] = EEpr_Bank_P[E0] | ( Offset_TrCode_P << TrCode_shift_n_bits );

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
		Program_Single_TrimRegister_P(g_EEP_W_E0);

		//TS setup for 30kHz and 80kHz toggling
			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);

		//Ton at TS_30kHz measurement
			tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
			Load_30Khz_Pulses_TS();
			delay(1);
			Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
			delay(1);
			//Observe 1.44us Ton_min at 30kHz TS request
			tmeas[1]=0;
			Ton_30kHz_Sim_P=0;
			for(j=1; j<=10; j++)
			{
				tmeas[j]=0;		//reset array values before use again.
				tmu_6->arm();				
				wait.delay_10_us(10);
				tmeas[j] = tmu_6->read(100e-6);	
				Ton_30kHz_Sim_P += tmeas[j];
			}
			Ton_30kHz_Sim_P = Ton_30kHz_Sim_P/10;

			Offset_Sim_P = Offset_pst1_P + Ton_30kHz_Sim_P - 1.08666666667e-6;	//if Ton_25k, it would be 0.7us instead of 1.08666666667us
			Offset_SimChg_P = (Offset_Sim_P/Offset_pst1_P -1.0)*100.0;

		//////Ton at TS_80kHz measurement
		////	tmu_6->stop_trigger_setup(0.3,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
		////	Load_80Khz_Pulses_TS();
		////	delay(1);
		////	Run_80Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
		////	delay(1);
		////	//Observe that the part react to faster freq request and adjust Ton accordingly
		////	//The first two Ton is due to transient behavior.  We want to ignore them.
		////	//We need to observe from the 4th pulse and expect all Ton stays the same after the 4th pulse.
		////	//Observe 5.64us Ton_min at 80kHz TS request.
		////	Ton_80kHz_Sim_P=0;
		////	for(j=1; j<=10; j++)
		////	{
		////		tmeas[j]=0;		//reset array values before use again.
		////		tmu_6->arm();				
		////		wait.delay_10_us(10);
		////		tmeas[j] = tmu_6->read(100e-6);	
		////		Ton_80kHz_Sim_P += tmeas[j];
		////	}
		////	Ton_80kHz_Sim_P = Ton_80kHz_Sim_P/10;

		//////Offset of simulated trimcode
		////	dy = Ton_80kHz_Sim_P - Ton_30kHz_Sim_P;
		////	dx = 80 - 30;
		////	Offset_Sim_P = dy/dx;	//us/kHz
		////	wait.delay_10_us(1);

		////	Offset_Sim_Chg_P = (Offset_Sim_P/Offset_pt_P -1.0)*100.0;

			PiDatalog(func, A_Offset_Sim_P,		Offset_Sim_P,			ours->fail_bin, POWER_MICRO);
			PiDatalog(func, A_Offset_SimChg_P,	Offset_SimChg_P,		ours->fail_bin, POWER_UNIT);
	}
	//*********************************************************************************************
	//*** Offset Simulation End **************************************************************************
	//*********************************************************************************************

	//---- Offset Bitweight CHAR starts --------------------------------- 
	//For bitweight char only (TEST Engineer will need to manually measure from scope)
	if(0)
	{
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
		EEPROM_Read_Enable_P();
		pE0_data[0] = DSM_I2C_Read(g_EEP_R_C0); //Read data[0] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		pE2_data[0] = DSM_I2C_Read(g_EEP_R_C2); //Read data[0] of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
		pE4_data[0] = DSM_I2C_Read(g_EEP_R_C4); //Read data[0] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
		pE6_data[0] = DSM_I2C_Read(g_EEP_R_C6); //Read data[0] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
		pE8_data[0] = DSM_I2C_Read(g_EEP_R_C8); //Read data[0] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		for(i=0; i<=15; i++)
		{
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


			smallest_diff_idx	= i;	//expect sim result to be the same if 0.  
			EEpr_Bank_P[E0]		= 0;	//
			Offset_TrCode_P   = smallest_diff_idx;
			Offset_TrCode_P   = Offset_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(Offset_TrCode_P, "Offset_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_yInter - g_E0_start_bit;
			EEpr_Bank_P[E0] = EEpr_Bank_P[E0] | ( Offset_TrCode_P << TrCode_shift_n_bits );

			Program_Single_TrimRegister_P(g_EEP_W_E0);
			wait.delay_10_us(1);

		EEPROM_Read_Enable_P();
		pE0_data[i] = DSM_I2C_Read(g_EEP_R_C0); //Read data[i] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		pE2_data[i] = DSM_I2C_Read(g_EEP_R_C2); //Read data[i] of RegAddr 0xE0 from 0xC2 RegAddr from READ_ADDR 0x00
		pE4_data[i] = DSM_I2C_Read(g_EEP_R_C4); //Read data[i] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
		pE6_data[i] = DSM_I2C_Read(g_EEP_R_C6); //Read data[i] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
		pE8_data[i] = DSM_I2C_Read(g_EEP_R_C8); //Read data[i] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00


			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);


				tmu_6->stop_trigger_setup(0.1,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//update thres to correlate better with scope
				Load_30Khz_Pulses_TS();
				delay(1);
				Run_30Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
				delay(1);
				//Observe 1.44us Ton_min at 30kHz TS request
				tmeas[1]=0;
				Ton_30kHz_pt_P=0;
				for(j=1; j<=10; j++)
				{
					tmeas[j]=0;		//reset array values before use again.
					tmu_6->arm();				
					wait.delay_10_us(10);
					tmeas[j] = tmu_6->read(100e-6);	
					Ton_30kHz_pt_P += tmeas[j];
				}
				Ton_30kHz_char[i] = Ton_30kHz_pt_P/10;

				Offset_char[i] = Offset_pt1_P + (Ton_30kHz_char[i] - 0.7e-6);	//offsetpost = OffsetAfterSlopeSim + (Ton_30kHz - 0.7us)
				wait.delay_10_us(1);
		}
	}
	//---- Offset Bitweight CHAR stop --------------------------------- 		

	delay(4);
	Stop_100Khz_Pulses_TS();
	Power_Down_I2C_P();
	Open_relay(K2_D_RB);
	Open_relay(K2_TS_TB); //TS to OVI_3_0_TS_RB								Connect
	Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS	Disconnect



}
