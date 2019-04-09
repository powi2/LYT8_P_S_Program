//==============================================================================
// IUV_Pre_P.cpp (User function)
// 
//    void IUV_Pre_P_user_init(test_function& func)
//    void IUV_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IUV_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IUV_Pre_P_user_init(test_function& func)
{
	IUV_Pre_P_params *ours;
    ours = (IUV_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IUV_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    IUV_Pre_P_params *ours;
    ours = (IUV_Pre_P_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fnum_iUVp_Tr_P, gFuncNum, 24,	POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	// Test Names //
	float iUVp_pt_P     =0;
	float iUVm_pt_P		=0;
	float iUVp_prg_P    =0;
	float iUVp_Target_P = 5.25; 
	int iUVp_TrCode_P   = 0;
	int iUVp_BitCode_P  = 0;
	int EEtr27_ZTML0_P  = 0;
	int EEtr28_ZTML1_P  = 0;
	
	float iUVp_Sim_P = 0;
	float iUVp_Sim_Chg_P	 = 0;
	float iUVp_ExpChg_P		= 0;
	float iUVp_ExpA_P		= 0;
	float iUVp_PrgChg		= 0;
	float iUVp_pst_P =0;
	float iUVp_Pre_TT =0;


	//Trimcode & bit weights.
	float	iUVp_TrimWt[32]   = {0.0};
	float	iUV_P_TrCode[32]     = {0.0};
	float	iUVp_SignCode[32]  = {0.0};

	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		i;
	int		TrCode_shift_n_bits	=0;

	float	iUVp_char[32]			=   {0.0};

	int		pE0_data[33] = {0};
	int		pE2_data[33] = {0};
	int		pE4_data[33] = {0};
	int		pE6_data[33] = {0};
	int		pE8_data[33] = {0};


	i = 0;																
	iUV_P_TrCode[i] 	=	0	;		iUVp_SignCode[i] 	=	0	;		 iUVp_TrimWt[i] 	=	0.00	;		    i++	;
	iUV_P_TrCode[i] 	=	1	;		iUVp_SignCode[i] 	=	1	;		 iUVp_TrimWt[i] 	=	-0.99	;		    i++	;
	iUV_P_TrCode[i] 	=	2	;		iUVp_SignCode[i] 	=	2	;		 iUVp_TrimWt[i] 	=	-1.96	;		    i++	;
	iUV_P_TrCode[i] 	=	3	;		iUVp_SignCode[i] 	=	3	;		 iUVp_TrimWt[i] 	=	-2.91	;		    i++	;
	iUV_P_TrCode[i] 	=	4	;		iUVp_SignCode[i] 	=	4	;		 iUVp_TrimWt[i] 	=	-3.85	;		    i++	;
	iUV_P_TrCode[i] 	=	5	;		iUVp_SignCode[i] 	=	5	;		 iUVp_TrimWt[i] 	=	-4.76	;		    i++	;
	iUV_P_TrCode[i] 	=	6	;		iUVp_SignCode[i] 	=	6	;		 iUVp_TrimWt[i] 	=	-5.66	;		    i++	;
	iUV_P_TrCode[i] 	=	7	;		iUVp_SignCode[i] 	=	7	;		 iUVp_TrimWt[i] 	=	-6.54	;		    i++	;
	iUV_P_TrCode[i] 	=	8	;		iUVp_SignCode[i] 	=	-8	;		 iUVp_TrimWt[i] 	=	8.70	;		    i++	;
	iUV_P_TrCode[i] 	=	9	;		iUVp_SignCode[i] 	=	-7	;		 iUVp_TrimWt[i] 	=	7.53	;		    i++	;
	iUV_P_TrCode[i] 	=	10	;		iUVp_SignCode[i] 	=	-6	;		 iUVp_TrimWt[i] 	=	6.38	;		    i++	;
	iUV_P_TrCode[i] 	=	11	;		iUVp_SignCode[i] 	=	-5	;		 iUVp_TrimWt[i] 	=	5.26	;		    i++	;
	iUV_P_TrCode[i] 	=	12	;		iUVp_SignCode[i] 	=	-4	;		 iUVp_TrimWt[i] 	=	4.17	;		    i++	;
	iUV_P_TrCode[i] 	=	13	;		iUVp_SignCode[i] 	=	-3	;		 iUVp_TrimWt[i] 	=	3.09	;		    i++	;
	iUV_P_TrCode[i] 	=	14	;		iUVp_SignCode[i] 	=	-2	;		 iUVp_TrimWt[i] 	=	2.04	;		    i++	;
	iUV_P_TrCode[i] 	=	15	;		iUVp_SignCode[i] 	=	-1	;		 iUVp_TrimWt[i] 	=	1.01	;		    i++	;



	
	/*
	--------------------------------------------------------------------------------------------------------
	Measurement	Target		Notes 
	iUV+		12.5uA		2% tolerance, use steps much finer than 1.125uA, like 0.1uA ok?
	iUV-		9.63uA		(Trim for Internal ADC full scale value)

				Record the peak code<8:0> on the drain when injecting 12.5uA (2% tolerance, make it accruate) 
				into vpin.  Expect IUV to be pretty close after Iov trim, but IUV done digitally via adc, 
				trim out nonidealities through ADC path.
				
				TargetCode = 312

	Procedure from Design:
		After ILIM test, go back into I2C mode, and bring DPEAK<8:0> out on dbus0.  dbus0 has 16 bits of 
		information.  The 1st 7 bits are the TON foldback amount, so ignore this.  Just capture the last 9 bits 
		(shifted out MSB first)	Then release VPIN and apply 12.5uA into it and trim the code to 312.  After 
		trimming is finished, sweep current around 12.5uA until output code is 312, then that is iUV+.  
		Then sweep current around 9.63uA until code is 240, then that is iUV-
		Note the code is in-phase on gate, so it will be inverted when looking at the drain; can also put 
		inverter after drain


	Procedure in Program:		
		1. Power up into I2C mode
		2. have BPP just go from 0 to 5V stay there don't complete zig-zag, 
		3. 0x40, 0x06
		4. 0x46, 0x0824		"LUV --> Drain"  Vpin is still disable here
		5. 0x4E, 0x01		Release Vpin.  Observed Vpin drop to ~1V on bench
		6. Ramp up iUV with Voltage source through Resistor for better accuracy until D switch from 0 to 1
		7. Ramp dn iUV to find iUV-		

	Vrigin parts are ~ 53uA iUV+ for first silicon
	--------------------------------------------------------------------------------------------------------
	*/
	Pulse pulse;
	//pulse.do_pulse();	

	if(g_USE_VR_600K==false)
	{
		Setup_Resources_for_I2C_P();
		PowerUp_I2C_P();

		if(g_Load_previous_RegBits)	//Always set to 1 for PRODUCTION use at 4200 or 4200RTR
		{
			EEPROM_Write_Enable_P();
			Program_All_TrimRegister_P();	//Loading previous trimming before performing the test.
		}

		DSM_I2C_Write('b', g_TM_CTRL, 0x06);		//0x40, 0x06 (enable analog mode + core_en)
	////DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2824);	//0x46, 0x0824 "FOSC --> Drain" & password
	////Close_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
	////Close_relay(K1_TMU_TB);	//D  to TMU_HIZ1
	////delay(4);
	//////Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
	////D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	////delay(1);
	////D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
	////delay(1);

		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0824);	//0x46, 0x0824 "LUV --> Drain"

		//Release Vpin and expect Vpin drop to ~2.3V after command issued.
		DSM_I2C_Write('b', g_PINSDA_CTRL, 0x01);	//0x4E, 0x01 (release Vpin)

		Disable_n_Disconnect_DSMI2C_via(g_release_Vpin);

		////Disconnect DSM from Primary after releasing VPIN or TS pins
		//Open_relay(K1_DSM_TB);	
		//Open_relay(K3_DSM_TB);	
		//delay(1);

		//6. release VPIN (SDA) for VPIN operation.  		
			UV_dvi->set_current(UV_ch, 5e-6, RANGE_300_UA);	//set really low current to start
			UV_dvi->set_voltage(UV_ch, 45, VOLT_50_RANGE); 
			delay(1);

		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
			D_dvi->set_current(D_ch, 5e-3, RANGE_300_MA); // Does not need 100mA for this test.
			D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
			//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
			D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
			wait.delay_10_us(20);

	BPP_zigzag(5.5, 4.3, 5.3);
	delay(40);

		//7. Ramp up iUV with Voltage source through Resistor for better accuracy until D switch from 0 to 1
			Search_iUVp_P(&iUVp_pt_P);
			PiDatalog(func, 	A_iUVp_pt_P,      iUVp_pt_P,					26, POWER_MICRO);
			PiDatalog(func, 	A_iUVp_target_P,  gP_iUVp_TARGET_Trimops,      26, POWER_MICRO);

			g_iUVp_pt_P = iUVp_pt_P;

			//Search_iUVm_P(&iUVm_pt_P);  //only for TEST to observe iOV- is working here.  No need to datalog.



	//*********************************************************************************************
	//*** Simulation IUV_Sim Start ****************************************************************
	//*********************************************************************************************
	if(0)
	{
		// Find which trim code will make iUVp_pt_P closest to target //
		smallest_diff_val = 999999.9;
		smallest_diff_idx = 0;
		for (i=0; i<=31; i++)
		{
			temp_1 = (iUVp_pt_P * (1 + (iUVp_TrimWt[i]/100)) -  gP_iUVp_TARGET_Trimops);
			if (fabs(temp_1) < fabs(smallest_diff_val))
			{
				smallest_diff_val = temp_1;
				smallest_diff_idx = i;
			}
		}

		//Debug only start for Manual forcing
			//smallest_diff_idx	= 31;	//expect sim result to be the same if 0.  
			EEpr_Bank_P[E6]		= 0;	//
		//Debug only stop for Manual forcing

		iUVp_TrCode_P   = smallest_diff_idx;
		iUVp_TrCode_P   = iUV_P_TrCode[smallest_diff_idx];
		iUVp_BitCode_P  = iUVp_SignCode[smallest_diff_idx];
		iUVp_ExpChg_P   = iUVp_TrimWt[smallest_diff_idx];
		iUVp_ExpA_P		= (iUVp_TrimWt[smallest_diff_idx]/100 +1)*iUVp_pt_P - iUVp_pt_P;

			PiDatalog(func, 	A_iUVp_TrCode_P,   iUVp_TrCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_iUVp_BitCode_P,  iUVp_BitCode_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_iUVp_ExpChg_P,   iUVp_ExpChg_P,				26, POWER_UNIT);
			PiDatalog(func, 	A_iUVp_ExpA_P,	   iUVp_ExpA_P,					26, POWER_MICRO);
			PiDatalog(func, 	A_EeTr57_iUVp0_P,   (iUVp_TrCode_P & 0x01)/1,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr58_iUVp1_P,   (iUVp_TrCode_P & 0x02)/2,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr59_iUVp2_P,   (iUVp_TrCode_P & 0x04)/4,	26, POWER_UNIT);
			PiDatalog(func, 	A_EeTr60_iUVp3_P,   (iUVp_TrCode_P & 0x08)/8,	26, POWER_UNIT);

		TrimCode_To_TrimBit(iUVp_TrCode_P, "IUV_P", 'p');	//convert trimcode to register bits and store to register temp array

		TrCode_shift_n_bits = gP_Reg_Start_Bit_uVADC - g_E6_start_bit;
		EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( iUVp_TrCode_P << TrCode_shift_n_bits );

		Regain_I2C_P(g_TSpin_Low_to_High);
		//EEPROM_Write_Enable_P();
		Program_Single_TrimRegister_P(g_EEP_W_E6);

		Disable_n_Disconnect_DSMI2C_via(g_release_Vpin);

		//release VPIN (SDA) for VPIN operation.  		
			UV_dvi->set_current(UV_ch, 5e-6, RANGE_300_UA);	//set really low current to start
			UV_dvi->set_voltage(UV_ch, 45, VOLT_50_RANGE); 
			delay(1);

		//Ramp up iUV with Voltage source through Resistor for better accuracy until D switch from 0 to 1
			Search_iUVp_P(&iUVp_Sim_P);

			iUVp_Sim_Chg_P = ((iUVp_Sim_P/iUVp_pt_P)-1)*100.0;

				PiDatalog(func, 	A_iUVp_Sim_P,      iUVp_Sim_P,              26, POWER_MICRO);
				PiDatalog(func, 	A_iUVp_Sim_Chg_P,  iUVp_Sim_Chg_P,          26, POWER_UNIT);
	}
	//*********************************************************************************************
	//*** Simulation IUV_Sim End ******************************************************************
	//*********************************************************************************************


	//-----------------------------------------------------------------
	//---- iUV Bitweight CHAR starts --------------------------------- 
	//For bitweight char only (TEST Engineer will need to manually measure from scope)
	if(0)
	{
		Regain_I2C_P(g_TSpin_Low_to_High);
		DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00

		for(i=0; i<=15; i++)
		{
			smallest_diff_idx	= i;	//expect sim result to be the same if 0.  
			//EEpr_Bank_P[E6]		= 0;	//
			iUVp_TrCode_P   = smallest_diff_idx;
			iUVp_TrCode_P   = iUV_P_TrCode[smallest_diff_idx];
			TrimCode_To_TrimBit(iUVp_TrCode_P, "uVADC_P", 'p');	//convert trimcode to register bits and store to register temp array
			TrCode_shift_n_bits = gP_Reg_Start_Bit_uVADC - g_E6_start_bit;
			EEpr_Bank_P[E6] = EEpr_Bank_P[E6] | ( iUVp_TrCode_P << TrCode_shift_n_bits );

		Regain_I2C_P(g_TSpin_Low_to_High);
	////			DSM_set_I2C_timeout(0, 1);
	////			DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	////DSM_I2C_Write('w', g_ANA_CTRL_1, 0x2824);	//0x46, 0x0824 "FOSC --> Drain" & password
	////D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA); 
	////delay(1);
	////	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0824);	//0x46, 0x0824 "LUV --> Drain"

		//EEPROM_Read_Enable_P();
		//DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00

			Program_Single_TrimRegister_P(g_EEP_W_E6);
			delay(15);

			//pE0_data[i] = DSM_I2C_Read(g_EEP_R_C0); //Read data[i] of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
			//pE2_data[i] = DSM_I2C_Read(g_EEP_R_C2); //Read data[i] of RegAddr 0xE0 from 0xC2 RegAddr from READ_ADDR 0x00
			//pE4_data[i] = DSM_I2C_Read(g_EEP_R_C4); //Read data[i] of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
			pE6_data[i] = DSM_I2C_Read(g_EEP_R_C6); //Read data[i] of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
			//pE8_data[i] = DSM_I2C_Read(g_EEP_R_C8); //Read data[i] of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00


		Disable_n_Disconnect_DSMI2C_via(g_release_Vpin);

			//release VPIN (SDA) for VPIN operation.  		
				UV_dvi->set_current(UV_ch, 5e-6, RANGE_300_UA);	//set really low current to start
				UV_dvi->set_voltage(UV_ch, 45, VOLT_50_RANGE); 
				delay(1);

			//Ramp up iUV with Voltage source through Resistor for better accuracy until D switch from 0 to 1
				Search_iUVp_P(&iUVp_char[i]);
				wait.delay_10_us(1);
		}
	}
	//---- iUV Bitweight CHAR stop --------------------------------- 	
	//-----------------------------------------------------------------



			Open_relay(K1_UV_RB);	//UV to RB_10kohm
			Open_relay(K2_UV_RB);	//UV to RB_600k to K2_UV to DVI-21-1
			Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
			delay(1);

		Power_Down_I2C_P();
	}


	//vForce control iVpin version
	if(g_USE_VR_600K==true)
	{
		Setup_Resources_for_I2C_P();
		PowerUp_I2C_P();

		DSM_I2C_Write('b', g_TM_CTRL, 0x06);	//0x40, 0x06 (enable analog mode + core_en)

		//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0824);	//0x46, 0x0024 (I2C password + observe drain "Line OV" signal

		//Release Vpin and expect Vpin drop to ~2.3V after command issued.
		DSM_I2C_Write('b', g_PINSDA_CTRL, 0x01);	//0x4E, 0x01 (release Vpin)
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

		////Force lines could not be connected  (will cause Vpin to go low if connected)
		//dvi_9->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_DIFF);
		//dvi_9->set_diff_range(RANGE_100_V);
		//dvi_9->open_relay(CONN_FORCE0);
		//dvi_9->open_relay(CONN_FORCE1);
		//delay(1);
		//Close_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(4);

		UV_dvi->set_voltage(UV_ch, 0.01, VOLT_50_RANGE); 
		wait.delay_10_us(20);
		UV_dvi->set_current(UV_ch, 20e-6, RANGE_300_UA);	
		UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_CURRENT);
		wait.delay_10_us(20);

		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

		Close_relay(K1_UV_RB);	//UV to RB_10kohm
		Close_relay(K2_UV_RB);	//UV to RB_600k to K2_UV to DVI-21-1
		Close_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
			delay(4);

		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
			D_dvi->set_current(D_ch, 5e-3, RANGE_300_MA); // Does not need 100mA for this test.
			D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
			//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
			D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
			wait.delay_10_us(20);

	BPP_zigzag(5.5, 4.3, 5.3);

		//7. inject current into VPIN starting low to find the IOV+ threshold by looking when drain flips.	
			//8. Once drain flipped, now search down to find IOV-		
			Search_iUVp_P(&iUVp_pt_P);
			PiDatalog(func, 	A_iUVp_pt_P,      iUVp_pt_P,              26, POWER_MICRO);

			Open_relay(K1_UV_RB);	//UV to RB_10kohm
			Open_relay(K2_UV_RB);	//UV to RB_600k to K2_UV to DVI-21-1
			Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
			delay(1);

		Power_Down_I2C_P();
	}

}
