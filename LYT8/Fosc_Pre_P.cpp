//==============================================================================
// Fosc_Pre_P.cpp (User function)
// 
//    void Fosc_Pre_P_user_init(test_function& func)
//    void Fosc_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Pre_P_user_init(test_function& func)
{
	Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_Fosc_Tr_P, gFuncNum, 14, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0&& g_GRR_Enable == 0)
		return;		

	if (g_OPCODE==4250 || g_OPCODE==4300 || g_OPCODE==4500)
		return;

	//if (g_Fn_Fosc_Pre_P == 0 )  return;

	float	Fosc_pt_P		=0;
	float	Fosc_prg_P		=0;
	int		Fosc_TrCode_P   =0;
	int		Fosc_BitCode_P  =0;
	int		EEtr27_ZTML0_P  =0;
	int		EEtr28_ZTML1_P  =0;
	
	float Fosc_Sim_P		=0;
	float Fosc_Sim_Chg_P	=0;
	float Fosc_ExpChg_P		=0;
	float Fosc_ExpHz_P		=0;
	float Fosc_PrgChg_P		=0;
	float Fosc_pst_P		=0;
	float Fosc_Pre_P_TT		=0;


	//Trimcode & bit weights.
	float	Fosc_P_TrimWt[32]   = {0.0};
	float	Fosc_P_TrCode[32]     = {0.0};
	float	Fosc_P_SignCode[32] = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;
	int		TrCode_shift_n_bits	=0;

	float	tmeas=0;


	i=0;																
	Fosc_P_TrCode[i]	=	0	;		Fosc_P_SignCode[i] 	=	0	;		 Fosc_P_TrimWt[i] 	=	0.00	;		    i++	;
	Fosc_P_TrCode[i]	=	1	;		Fosc_P_SignCode[i] 	=	-4	;		 Fosc_P_TrimWt[i] 	=	-3.97	;		    i++	;
	Fosc_P_TrCode[i]	=	2	;		Fosc_P_SignCode[i] 	=	-8	;		 Fosc_P_TrimWt[i] 	=	-8.40	;		    i++	;
	Fosc_P_TrCode[i]	=	3	;		Fosc_P_SignCode[i] 	=	-12	;		 Fosc_P_TrimWt[i] 	=	-12.70	;		    i++	;
	Fosc_P_TrCode[i]	=	4	;		Fosc_P_SignCode[i] 	=	-16	;		 Fosc_P_TrimWt[i] 	=	-16.68	;		    i++	;
	Fosc_P_TrCode[i]	=	5	;		Fosc_P_SignCode[i] 	=	-20	;		 Fosc_P_TrimWt[i] 	=	-20.68	;		    i++	;
	Fosc_P_TrCode[i]	=	6	;		Fosc_P_SignCode[i] 	=	-24	;		 Fosc_P_TrimWt[i] 	=	-24.65	;		    i++	;
	Fosc_P_TrCode[i]	=	7	;		Fosc_P_SignCode[i] 	=	-28	;		 Fosc_P_TrimWt[i] 	=	-28.57	;		    i++	;
	Fosc_P_TrCode[i]	=	8	;		Fosc_P_SignCode[i] 	=	32	;		 Fosc_P_TrimWt[i] 	=	30.92	;		    i++	;
	Fosc_P_TrCode[i]	=	9	;		Fosc_P_SignCode[i] 	=	28	;		 Fosc_P_TrimWt[i] 	=	27.18	;		    i++	;
	Fosc_P_TrCode[i]	=	10	;		Fosc_P_SignCode[i] 	=	24	;		 Fosc_P_TrimWt[i] 	=	22.71	;		    i++	;
	Fosc_P_TrCode[i]	=	11	;		Fosc_P_SignCode[i] 	=	20	;		 Fosc_P_TrimWt[i] 	=	19.21	;		    i++	;
	Fosc_P_TrCode[i]	=	12	;		Fosc_P_SignCode[i] 	=	16	;		 Fosc_P_TrimWt[i] 	=	15.59	;		    i++	;
	Fosc_P_TrCode[i]	=	13	;		Fosc_P_SignCode[i] 	=	12	;		 Fosc_P_TrimWt[i] 	=	11.74	;		    i++	;
	Fosc_P_TrCode[i]	=	14	;		Fosc_P_SignCode[i] 	=	8	;		 Fosc_P_TrimWt[i] 	=	7.80	;		    i++	;
	Fosc_P_TrCode[i]	=	15	;		Fosc_P_SignCode[i] 	=	4	;		 Fosc_P_TrimWt[i] 	=	3.72	;		    i++	;


//g_Debug = 1;
	//Bank E0 trim registers
	/*
		fOSC_3_P	bit 11
		fOSC_2_P	bit 10
		fOSC_1_P	bit 9
		fOSC_0_P	bit 8
	*/

	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();



	Setup_Resources_for_I2C_P();
	PowerUp_I2C_P();

	if(g_Load_previous_RegBits&& g_GRR_Enable == 0)	//Always set to 1 for PRODUCTION use at 4200 or 4200RTR
	{
		EEPROM_Write_Enable_P();
		Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
	}

	DSM_I2C_Write('b', g_TM_CTRL, 0x06);	//0x40, 0x06 (enable analog mode + core_en)

	//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2824);	//0x46, 0x0024 (I2C password + observe drain 

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

	Close_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	Close_relay(K1_TMU_TB);	//D  to TMU_HIZ1
		//delay(4);

	//HL moved Drain settings after connecting TMU
	////////Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
	//////	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	//////	delay(1);
	//////	D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
	//////	delay(1);

	//Drain signal shows sharper rising edge, hence use START/STOP POSITIVE/POSITIVE
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		
	tmu_6->stop_trigger_setup(1.7,  NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	//tmu_6->start_trigger_setup(-0.25, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		//noise level only
	//tmu_6->stop_trigger_setup(-0.15,  NEG_SLOPE, TMU_HIZ, TMU_IN_5V);		//noise level only
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(10,TRUE);
	wait.delay_10_us(100);
	delay(4);

//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
		delay(1);
		D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
		delay(1);

	tmu_6->arm();				
	delay(1);					
	tmeas = tmu_6->read(1e-3);	
	tmeas/=10;	
	Fosc_pt_P = 1/tmeas;

	//
	//Datalog
	PiDatalog(func, A_Fosc_pt_P,		Fosc_pt_P,					14,	POWER_MEGA);
	if(g_GRR_Enable == 0)
		PiDatalog(func, A_Fosc_target_P,	gP_Fosc_TARGET_Trimops,	14,	POWER_MEGA);	


	//*********************************************************************************************
	//*** Fosc_P Simulation Start *****************************************************************
	//*********************************************************************************************
	if(g_Sim_Enable_P)
	{
		// Find which trim code will make Fosc_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			temp_1 = (Fosc_pt_P * (1 + (Fosc_P_TrimWt[i]/100)) -  gP_Fosc_TARGET_Trimops);
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

		Fosc_TrCode_P   = smallest_diff_idx;
		Fosc_TrCode_P   = Fosc_P_TrCode[smallest_diff_idx];
		Fosc_BitCode_P  = Fosc_P_SignCode[smallest_diff_idx];
		Fosc_ExpChg_P     = Fosc_P_TrimWt[smallest_diff_idx];
		Fosc_ExpHz_P		= (Fosc_P_TrimWt[smallest_diff_idx]/100 +1)*Fosc_pt_P - Fosc_pt_P;

			PiDatalog(func, 	A_Fosc_TrCode_P,	Fosc_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Fosc_BitCode_P,	Fosc_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_Fosc_ExpChg_P,	Fosc_ExpChg_P,				26, POWER_UNIT);
			//PiDatalog(func, 	A_Fosc_ExpHz_P,		Fosc_ExpHz_P,				26, POWER_KILO);
			PiDatalog(func, 	A_EeTr8_fOSC0_P,	(Fosc_TrCode_P & 0x01)/1,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr9_fOSC1_P,	(Fosc_TrCode_P & 0x02)/2,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr10_fOSC2_P,   (Fosc_TrCode_P & 0x04)/4,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr11_fOSC3_P,   (Fosc_TrCode_P & 0x08)/8,	26, POWER_UNIT);

		TrimCode_To_TrimBit(Fosc_TrCode_P, "fOSC_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_fOSC - g_E0_start_bit;
		EEpr_Bank_P[E0] = EEpr_Bank_P[E0] | ( Fosc_TrCode_P << TrCode_shift_n_bits );

		Program_Single_TrimRegister_P(g_EEP_W_E0);

		//Measure simulated Fosc_P with TrimCode 
		tmu_6->arm();				
		delay(1);					
		tmeas = tmu_6->read(1e-3);	
		tmeas/=10;	
		Fosc_Sim_P = 1/tmeas;

		Fosc_Sim_Chg_P = (Fosc_Sim_P/Fosc_pt_P -1.0)*100.0;

		PiDatalog(func, A_Fosc_Sim_P,		Fosc_Sim_P,			ours->fail_bin, POWER_MEGA);
		PiDatalog(func, A_Fosc_Sim_Chg_P,	Fosc_Sim_Chg_P,		ours->fail_bin, POWER_UNIT);
	}
	//*********************************************************************************************
	//*** Fosc_P Simulation End *******************************************************************
	//*********************************************************************************************

	//---------------------------------
	//For bitweight char only
	if(0)
	{
		for(i=1; i<=15; i++)
		{
			smallest_diff_idx	= i;	//expect sim result to be the same if 0.  
			EEpr_Bank_P[E0]		= 0;	//
			Fosc_TrCode_P   = smallest_diff_idx;
			Fosc_TrCode_P   = Fosc_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(Fosc_TrCode_P, "fOSC_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_fOSC - g_E0_start_bit;
			EEpr_Bank_P[E0] = EEpr_Bank_P[E0] | ( Fosc_TrCode_P << TrCode_shift_n_bits );

			Program_Single_TrimRegister_P(g_EEP_W_E0);
			tmu_6->arm();				
			delay(1);					
			tmeas = tmu_6->read(1e-3);	
			tmeas/=10;	
			Fosc_Sim_P = 1/tmeas;
			wait.delay_10_us(1);
		}
	}
	//---------------------------------

	//--------------------------------------------------------------
	//HL added...need to set D = 0V before opening the relays.
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);
	D_dvi->set_current(D_ch, 0.001e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_20_RANGE); // DVI_11_0
	delay(1);
	//--------------------------------------------------------------

	Power_Down_I2C_P();

	tmu_6->open_relay(TMU_HIZ_DUT1);    //TMU HIZ1 to Drain 
	Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	Open_relay(K1_TMU_TB);	//D  to TMU_HIZ1
	delay(4);
	//Power_Down_I2C_P();



	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Fosc_Pre_P_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Fosc_Trim_P_TT, Fosc_Pre_P_TT, 14, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}




//g_Debug = 0;






}
