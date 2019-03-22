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

	// Skip trimming if g_Trim_Enable_P set //
	//if (g_Trim_Enable_P == 0)
	//	return;

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
	float iUVp_Sim_Chg_P = 0;
	float iUVp_ExpChg   = 0;
	float iUVp_PrgChg   = 0;
	float iUVp_pst_P =0;
	float iUVp_Pre_TT =0;


	//Trimcode & bit weights.
	float	iUVp_TrimWt[32]   = {0.0};
	float	iUVp_code[32]     = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;

	i = 0;
	iUVp_code[i] =  0	;	 iUVp_TrimWt[i] 	=	0.000	;	    i++	;
	iUVp_code[i] =  1	;	 iUVp_TrimWt[i] 	=	-0.990	;	    i++	;
	iUVp_code[i] =  2	;	 iUVp_TrimWt[i] 	=	-1.961	;	    i++	;
	iUVp_code[i] =  3	;	 iUVp_TrimWt[i] 	=	-2.913	;	    i++	;
	iUVp_code[i] =  4	;	 iUVp_TrimWt[i] 	=	-3.846	;	    i++	;
	iUVp_code[i] =  5	;	 iUVp_TrimWt[i] 	=	-4.762	;	    i++	;
	iUVp_code[i] =  6	;	 iUVp_TrimWt[i] 	=	-5.660	;	    i++	;
	iUVp_code[i] =  7	;	 iUVp_TrimWt[i] 	=	-6.542	;	    i++	;
	iUVp_code[i] =  8	;	 iUVp_TrimWt[i] 	=	-7.407	;	    i++	;
	iUVp_code[i] =  9	;	 iUVp_TrimWt[i] 	=	-8.257	;	    i++	;
	iUVp_code[i] = 10	;	 iUVp_TrimWt[i] 	=	-9.091	;	    i++	;
	iUVp_code[i] = 11	;	 iUVp_TrimWt[i] 	=	-9.910	;	    i++	;
	iUVp_code[i] = 12	;	 iUVp_TrimWt[i] 	=	-10.714	;	    i++	;
	iUVp_code[i] = 13	;	 iUVp_TrimWt[i] 	=	-11.504	;	    i++	;
	iUVp_code[i] = 14	;	 iUVp_TrimWt[i] 	=	-12.281	;	    i++	;
	iUVp_code[i] = 15	;	 iUVp_TrimWt[i] 	=	-13.043	;	    i++	;


	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //
	// E6 Trim register bank start from bit 48 and end at bit 63

	//Pass Bank E8 trim registers data to the WordArray
	WordArray[0]  = g_TrimRegister_P[48];
	WordArray[1]  = g_TrimRegister_P[49];
	WordArray[2]  = g_TrimRegister_P[50];
	WordArray[3]  = g_TrimRegister_P[51];
	WordArray[4]  = g_TrimRegister_P[52];
	WordArray[5]  = g_TrimRegister_P[53];
	WordArray[6]  = g_TrimRegister_P[54]; 
	WordArray[7]  = g_TrimRegister_P[55]; 
	WordArray[8]  = g_TrimRegister_P[56]; 
	WordArray[9]  = g_TrimRegister_P[57]; //uVADC_0_P
	WordArray[10] = g_TrimRegister_P[58]; //uVADC_1_P
	WordArray[11] = g_TrimRegister_P[59]; //uVADC_2_P
	WordArray[12] = g_TrimRegister_P[60]; //uVADC_3_P
	WordArray[13] = g_TrimRegister_P[61]; 
	WordArray[14] = g_TrimRegister_P[62]; 
	WordArray[15] = g_TrimRegister_P[63];

	
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

		DSM_I2C_Write('b', g_TM_CTRL, 0x06);		//0x40, 0x06 (enable analog mode + core_en)
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0824);	//0x46, 0x0824 "LUV --> Drain"

		//Release Vpin and expect Vpin drop to ~2.3V after command issued.
		DSM_I2C_Write('b', g_PINSDA_CTRL, 0x01);	//0x4E, 0x01 (release Vpin)
		//DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C
		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

		//6. release VPIN (SDA) for VPIN operation.  		
			UV_dvi->set_current(UV_ch, 5e-6, RANGE_300_UA);	//set really low current to start
			UV_dvi->set_voltage(UV_ch, 45, VOLT_50_RANGE); 
			delay(1);
		delay(5);

		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
			D_dvi->set_current(D_ch, 5e-3, RANGE_300_MA); // Does not need 100mA for this test.
			D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
			//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
			D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
			wait.delay_10_us(20);
	//BPP zig zag (5V to 5.5V to 4.3V to 5.4V below OV threshold)
	BPP_dvi->set_voltage(BPP_ch, 5.5, VOLT_10_RANGE); // DVI_11_1
	delay(1);
	BPP_dvi->set_voltage(BPP_ch, 4.3, VOLT_10_RANGE); // DVI_11_1
	delay(1);
	BPP_dvi->set_voltage(BPP_ch, 5.4, VOLT_10_RANGE); // DVI_11_1
	delay(1);



		//7. Ramp up iUV with Voltage source through Resistor for better accuracy until D switch from 0 to 1
			Search_iUVp_P(&iUVp_pt_P);
			PiDatalog(func, 	A_iUVp_pt_P,      iUVp_pt_P,              26, POWER_MICRO);

			g_iUVp_pt_P = iUVp_pt_P;

			Search_iUVm_P(&iUVm_pt_P);  //only for TEST to observe iOV- is working here.  No need to datalog.

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


	//BPP zig zag (5V to 5.5V to 4.3V to 5.4V below OV threshold)
	////BPP_dvi->set_voltage(BPP_ch, 5.5, VOLT_10_RANGE); // DVI_11_1
	////delay(1);
	////BPP_dvi->set_voltage(BPP_ch, 4.3, VOLT_10_RANGE); // DVI_11_1
	////delay(1);
	////BPP_dvi->set_voltage(BPP_ch, 5.4, VOLT_10_RANGE); // DVI_11_1
	////delay(1);
	BPP_zigzag(5.5, 4.3, 5.4);

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
