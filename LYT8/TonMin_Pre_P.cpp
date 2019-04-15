//==============================================================================
// TonMin_Pre_P.cpp (User function)
// 
//    void TonMin_Pre_P_user_init(test_function& func)
//    void TonMin_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "TonMin_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TonMin_Pre_P_user_init(test_function& func)
{
	TonMin_Pre_P_params *ours;
    ours = (TonMin_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TonMin_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TonMin_Pre_P_params *ours;
    ours = (TonMin_Pre_P_params *)func.params;


	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_TMin_Tr_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0&& g_GRR_Enable == 0)
		return;

	if (g_OPCODE==4250 || g_OPCODE==4300 || g_OPCODE==4500)
		return;

	//if (g_Fn_TonMin_Pre_P == 0 )  return;

	float	TonMin_pt_P     =0;
	float	TonMin_prg_P    =0;
	int		TonMin_TrCode_P   = 0;
	int		TonMin_BitCode_P  = 0;
	
	float	TonMin_Sim_P = 0;
	float	TonMin_Sim_Chg_P = 0;
	float	TonMin_ExpChg_P	=0;
	float	TonMin_ExpUs_P	=0;

	float	TonMin_pst_P =0;
	float	TonMin_Pre_P_TT =0;


	//Trimcode & bit weights.
	float	TonMin_P_TrimWt[32]		= {0.0};
	float	TonMin_P_TrCode[32]     = {0.0};
	float	TonMin_P_SignCode[32]	= {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		i;
	int		TrCode_shift_n_bits	=0;

	float	tmeas[20]			= {0};

	i=0;																
	TonMin_P_TrCode[i]	=	0	;		TonMin_P_SignCode[i] 	=	0	;		 TonMin_P_TrimWt[i] 	=	0.00	;		    i++	;
	TonMin_P_TrCode[i]	=	1	;		TonMin_P_SignCode[i] 	=	4	;		 TonMin_P_TrimWt[i] 	=	-3.13	;		    i++	;
	TonMin_P_TrCode[i]	=	2	;		TonMin_P_SignCode[i] 	=	8	;		 TonMin_P_TrimWt[i] 	=	-6.68	;		    i++	;
	TonMin_P_TrCode[i]	=	3	;		TonMin_P_SignCode[i] 	=	12	;		 TonMin_P_TrimWt[i] 	=	-9.95	;		    i++	;
	TonMin_P_TrCode[i]	=	4	;		TonMin_P_SignCode[i] 	=	-16	;		 TonMin_P_TrimWt[i] 	=	17.98	;		    i++	;
	TonMin_P_TrCode[i]	=	5	;		TonMin_P_SignCode[i] 	=	-12	;		 TonMin_P_TrimWt[i] 	=	13.35	;		    i++	;
	TonMin_P_TrCode[i]	=	6	;		TonMin_P_SignCode[i] 	=	-8	;		 TonMin_P_TrimWt[i] 	=	8.31	;		    i++	;
	TonMin_P_TrCode[i]	=	7	;		TonMin_P_SignCode[i] 	=	-4	;		 TonMin_P_TrimWt[i] 	=	4.36	;		    i++	;


	//Pass Bank E0 trim registers data to the WordArray
	/*
		TonMin_2_P	bit 79
		TonMin_1_P	bit 78
		TonMin_0_P	bit 77
	*/


	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	//Setup for Ton_Min measurement
	Close_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Connect
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(0.02,  POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100);


	Pulse pulse;
		

	Setup_Resources_for_I2C_P();

	PowerUp_I2C_P();


//pulse.do_pulse();

	if(g_Load_previous_RegBits&& g_GRR_Enable == 0)	//Always set to 1 for PRODUCTION use at 4200 or 4200RTR
	{
		EEPROM_Write_Enable_P();
		Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
	}

	DSM_I2C_Write('b', g_TM_CTRL, 0x02);	//0x40, 0x02 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2804);	//0x46, 0x0024 (I2C password + observe drain 
	DSM_I2C_Write('w', 0x44, 0x0442);			//choose min ON time and allow flux link thru TSPIN + disable receiver output
	DSM_I2C_Write('b', 0x4C, 0x01);				//release TS pin

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C


		//HL-Question: Should TS/UV pins be powered down before opening relays?
		//This can be hot-switching the DSM relays on the primary sides.
		//Disconnect DSM from Primary after releasing VPIN or TS pins
		TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
		//UV = 0V via pullup resistor. Ready for I2C.
		UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
		wait.delay_10_us(10);
		TS_ovi3->set_current(TSovi3_ch, 0.01e-3, RANGE_30_MA);
		UV_dvi->set_current(UV_ch, 0.01e-3, RANGE_300_MA);
		wait.delay_10_us(10);
	//--------------------------------------------------------------------------------------------
	//Setup for TS to run 100kHz
		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_1_RANGE); // OVI_3_0
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

	//HL-added.  Will need to check with design of the BPP current needed for this test.	
	BPP_dvi->set_current(BPP_ch, 2e-3, RANGE_300_MA);
	BPP_zigzag(gVBPP_PV_final, gVBPP_M_final, gVBPP_P_final, 2.0e-3);
	//BPP_zigzag(5.5, 4.3, 5.35, 2.0e-3);


	//	BPP_dvi->set_current(BPP_ch, 5.0e-3, RANGE_300_MA);	// Any current above 3mA would have Shunt started

	Load_100Khz_Pulses_TS();
	delay(1);

	Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
	delay(4);
	Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
	delay(1);



	tmeas[1]=0;
	TonMin_pt_P=0;
	for(i=1; i<=10; i++)
	{
		tmu_6->arm();				
		wait.delay_10_us(10);
		tmeas[i] = tmu_6->read(100e-6);	
		TonMin_pt_P += tmeas[i];
	}
	TonMin_pt_P = TonMin_pt_P/10;

	//Datalog
	PiDatalog(func, A_TonMin_pt_P,		TonMin_pt_P,				14,	POWER_MICRO);	
	if(g_GRR_Enable == 0)
		PiDatalog(func, A_TonMin_target_P,	gP_TonMin_TARGET_Trimops,	14,	POWER_MICRO);	

	//*********************************************************************************************
	//*** TonMin_P Simulation Start ***************************************************************
	//*********************************************************************************************
	if(g_Sim_Enable_P)
	{
		// Find which trim code will make TonMin_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			temp_1 = (TonMin_pt_P * (1 + (TonMin_P_TrimWt[i]/100)) -  gP_TonMin_TARGET_Trimops);
			if (fabs(temp_1) < fabs(smallest_diff_val))
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		//Debug only start for Manual forcing
			//smallest_diff_idx	= 0;	//expect sim result to be the same if 0.  
			//EEpr_Bank_P[E8]		= 0;	//
		//Debug only stop for Manual forcing

		TonMin_TrCode_P		= smallest_diff_idx;
		TonMin_TrCode_P		= TonMin_P_TrCode[smallest_diff_idx];
		TonMin_BitCode_P	= TonMin_P_SignCode[smallest_diff_idx];
		TonMin_ExpChg_P     = TonMin_P_TrimWt[smallest_diff_idx];
		TonMin_ExpUs_P		= (TonMin_P_TrimWt[smallest_diff_idx]/100 +1)*TonMin_pt_P - TonMin_pt_P;

			PiDatalog(func, 	A_TonMin_TrCode_P,	TonMin_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_TonMinBitCode_P,	TonMin_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_TonMin_ExpChg_P,	TonMin_ExpChg_P,				26, POWER_UNIT);
			//PiDatalog(func, 	A_TonMin_ExpUs_P,		TonMin_ExpUs_P,				26, POWER_MICRO);
			PiDatalog(func, 	A_EeTr77_TonM0_P,	(TonMin_TrCode_P & 0x01)/1,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr78_TonM1_P,	(TonMin_TrCode_P & 0x02)/2,		26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr79_TonM2_P,   (TonMin_TrCode_P & 0x04)/4,		26, POWER_UNIT);

		TrimCode_To_TrimBit(TonMin_TrCode_P, "TonMin_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_TonM - g_E8_start_bit;
		EEpr_Bank_P[E8] = EEpr_Bank_P[E8] | ( TonMin_TrCode_P << TrCode_shift_n_bits );


			Stop_100Khz_Pulses_TS();
			TS_ovi->set_voltage(TSovi1_ch, 0.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			Open_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Open_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			//Connect DSM from Primary after releasing VPIN or TS pins
			Close_relay(K1_DSM_TB);	
			Close_relay(K3_DSM_TB);	
			delay(4);
			//HL added to repower up TS & UV
			TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
			UV_dvi->set_current(UV_ch, 30e-3, RANGE_300_MA);
			UV_dvi->set_voltage(UV_ch, 3.3, VOLT_10_RANGE); // DVI_21_1
			TS_ovi3->set_voltage(TSovi3_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);

		Program_Single_TrimRegister_P(g_EEP_W_E8);

			TS_ovi->set_voltage(TSovi1_ch, 1.0, VOLT_1_RANGE); // OVI_1_5 for Comparator LT1719 Vref input
			wait.delay_10_us(10);
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			wait.delay_10_us(10);
			Close_relay(K2_TS_TB); //TS disconnect from OVI_3_0_TS_RB
			Close_relay(K3_TS_IB); //DDD7_1 to Comparator LT1719 to COMP_OUT to TS
			delay(3);
			//HL added setting TS & UV ovi to 0V.
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
			UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
			wait.delay_10_us(10);
			TS_ovi3->set_current(TSovi3_ch, 0.01e-3, RANGE_30_MA);
			UV_dvi->set_current(UV_ch, 0.01e-3, RANGE_300_MA);
			wait.delay_10_us(10);
			//Disconnect DSM from Primary after releasing VPIN or TS pins
			Open_relay(K1_DSM_TB);	
			Open_relay(K3_DSM_TB);	
			delay(4);
			Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
			delay(1);
			
			tmeas[1]=0;
			TonMin_Sim_P=0;
			for(i=1; i<=10; i++)
			{
				tmu_6->arm();				
				wait.delay_10_us(10);
				tmeas[i] = tmu_6->read(100e-6);	
				TonMin_Sim_P += tmeas[i];
			}
			TonMin_Sim_P = TonMin_Sim_P/10;

			TonMin_Sim_Chg_P = (TonMin_Sim_P/TonMin_pt_P -1.0)*100.0;

			PiDatalog(func, A_TonMin_Sim_P,		TonMin_Sim_P,		14,	POWER_MICRO);		
			PiDatalog(func, A_TonMin_SimChg_P, TonMin_Sim_Chg_P,	14,	POWER_UNIT);	
	}
	//*********************************************************************************************
	//*** TonMin_P Simulation Stop ****************************************************************
	//*********************************************************************************************

	//---------------------------------
	//For bitweight char only (TEST Engineer will need to manually measure from scope)
	if(0)
	{
		////int pE0_data = 0;
		////int pE2_data = 0;
		////int pE4_data = 0;
		////int pE6_data = 0;
		////int pE8_data = 0;
		////EEPROM_Read_Enable_P();
		////pE0_data = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00
		////pE2_data = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00
		////pE4_data = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00
		////pE6_data = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00
		////pE8_data = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		for(i=1; i<=7; i++)
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
			EEpr_Bank_P[E8]		= 0;	//
			TonMin_TrCode_P   = smallest_diff_idx;
			TonMin_TrCode_P   = TonMin_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(TonMin_TrCode_P, "TonMin_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_TonM - g_E8_start_bit;
			EEpr_Bank_P[E8] = EEpr_Bank_P[E8] | ( TonMin_TrCode_P << TrCode_shift_n_bits );

			Program_Single_TrimRegister_P(g_EEP_W_E8);
			wait.delay_10_us(1);

		//EEPROM_Read_Enable_P();
		//pE8_data = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

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
			Run_100Khz_Pulses_TS();	//DE want 50ns high duty cycle ideally.
			delay(1);

		}
	}
	//---------------------------------

	//HL added.  Power down Drain first before disconnecting TMU
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);
	D_dvi->set_current(D_ch, 0.1e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);

	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain									
	Open_relay(K1_TMU_TB);				//D  to TMU_HIZ1										Disconnect
	delay(4);
	Stop_100Khz_Pulses_TS();
	Power_Down_I2C_P();
	Open_relay(K2_D_RB);				//D			to RB_82uH_50ohm to K2_D to DVI-11-0		Disconnect
	Open_relay(K2_TS_TB);				//TS		to OVI_3_0_TS_RB							Connect
	Open_relay(K3_TS_IB);				//DDD7_1	to Comparator LT1719 to COMP_OUT to TS		Disconnect
	delay(3);


}
