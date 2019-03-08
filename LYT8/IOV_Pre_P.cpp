//==============================================================================
// IOV_Pre_P.cpp (User function)
// 
//    void IOV_Pre_P_user_init(test_function& func)
//    void IOV_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IOV_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_Pre_P_user_init(test_function& func)
{
	IOV_Pre_P_params *ours;
    ours = (IOV_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_Pre_P_params *ours;
    ours = (IOV_Pre_P_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_iOVp_Pre, gFuncNum, 24,	POWER_UNIT);

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
	float iOVp_pt_P     =0;
	float iOVm_pt_P     =0;
	float iOVp_prg_P    =0;
	float iOVp_Target_P = 5.25; 
	int iOVp_TrCode_P   = 0;
	int iOVp_BitCode_P  = 0;
	int EEtr27_ZTML0_P  = 0;
	int EEtr28_ZTML1_P  = 0;
	
	float iOVp_Sim_P = 0;
	float iOVp_Sim_Chg_P = 0;
	float iOVp_ExpChg   = 0;
	float iOVp_PrgChg   = 0;
	float iOVp_pst_P =0;
	float iOVp_Pre_TT =0;


	//Trimcode & bit weights.
	float	iOVp_TrimWt[32]   = {0.0};
	float	iOVp_code[32]     = {0.0};
	float   smallest_diff_val  = 999999.9;
	float   temp_1             = 0;
	int     smallest_diff_idx  = 0;
	int		WordArray[16]	   = {0};
	int		i;

	i = 0;
	iOVp_code[i] =  0	;	 iOVp_TrimWt[i] 	=	0.000	;	    i++	;
	iOVp_code[i] =  1	;	 iOVp_TrimWt[i] 	=	-0.990	;	    i++	;
	iOVp_code[i] =  2	;	 iOVp_TrimWt[i] 	=	-1.961	;	    i++	;
	iOVp_code[i] =  3	;	 iOVp_TrimWt[i] 	=	-2.913	;	    i++	;
	iOVp_code[i] =  4	;	 iOVp_TrimWt[i] 	=	-3.846	;	    i++	;
	iOVp_code[i] =  5	;	 iOVp_TrimWt[i] 	=	-4.762	;	    i++	;
	iOVp_code[i] =  6	;	 iOVp_TrimWt[i] 	=	-5.660	;	    i++	;
	iOVp_code[i] =  7	;	 iOVp_TrimWt[i] 	=	-6.542	;	    i++	;
	iOVp_code[i] =  8	;	 iOVp_TrimWt[i] 	=	-7.407	;	    i++	;
	iOVp_code[i] =  9	;	 iOVp_TrimWt[i] 	=	-8.257	;	    i++	;
	iOVp_code[i] = 10	;	 iOVp_TrimWt[i] 	=	-9.091	;	    i++	;
	iOVp_code[i] = 11	;	 iOVp_TrimWt[i] 	=	-9.910	;	    i++	;
	iOVp_code[i] = 12	;	 iOVp_TrimWt[i] 	=	-10.714	;	    i++	;
	iOVp_code[i] = 13	;	 iOVp_TrimWt[i] 	=	-11.504	;	    i++	;
	iOVp_code[i] = 14	;	 iOVp_TrimWt[i] 	=	-12.281	;	    i++	;
	iOVp_code[i] = 15	;	 iOVp_TrimWt[i] 	=	-13.043	;	    i++	;
	iOVp_code[i] =  16	;	 iOVp_TrimWt[i] 	=	1.010	;	    i++	;
	iOVp_code[i] =  17	;	 iOVp_TrimWt[i] 	=	2.041	;	    i++	;
	iOVp_code[i] =  18	;	 iOVp_TrimWt[i] 	=	3.093	;	    i++	;
	iOVp_code[i] =  19	;	 iOVp_TrimWt[i] 	=	4.167	;	    i++	;
	iOVp_code[i] =  20	;	 iOVp_TrimWt[i] 	=	5.263	;	    i++	;
	iOVp_code[i] =  21	;	 iOVp_TrimWt[i] 	=	6.383	;	    i++	;
	iOVp_code[i] =  22	;	 iOVp_TrimWt[i] 	=	7.527	;	    i++	;
	iOVp_code[i] =  23	;	 iOVp_TrimWt[i] 	=	8.696	;	    i++	;
	iOVp_code[i] =  24	;	 iOVp_TrimWt[i] 	=	9.890	;	    i++	;
	iOVp_code[i] =  25	;	 iOVp_TrimWt[i] 	=	11.111	;	    i++	;
	iOVp_code[i] =  26	;	 iOVp_TrimWt[i] 	=	12.360	;	    i++	;
	iOVp_code[i] =  27	;	 iOVp_TrimWt[i] 	=	13.636	;	    i++	;
	iOVp_code[i] =  28	;	 iOVp_TrimWt[i] 	=	14.943	;	    i++	;
	iOVp_code[i] =  29	;	 iOVp_TrimWt[i] 	=	16.279	;	    i++	;
	iOVp_code[i] =  30	;	 iOVp_TrimWt[i] 	=	17.647	;	    i++	;
	iOVp_code[i] =  31	;	 iOVp_TrimWt[i] 	=	19.048	;	    i++	;



	// Load WordArray[] with contents of g_Sec_TrimRegister[] array!  This includes trim bit from other tests & trim options 
    // This is important for proper trimming! //
	// E8 Trim register bank start from bit 64 and end at bit 79

	//Pass Bank E8 trim registers data to the WordArray
	WordArray[0]  = g_TrimRegister_P[64];
	WordArray[1]  = g_TrimRegister_P[65];
	WordArray[2]  = g_TrimRegister_P[66];
	WordArray[3]  = g_TrimRegister_P[67];
	WordArray[4]  = g_TrimRegister_P[68];
	WordArray[5]  = g_TrimRegister_P[69];
	WordArray[6]  = g_TrimRegister_P[70]; 
	WordArray[7]  = g_TrimRegister_P[71]; 
	WordArray[8]  = g_TrimRegister_P[72]; //IOV_0_P
	WordArray[9]  = g_TrimRegister_P[73]; //IOV_1_P
	WordArray[10] = g_TrimRegister_P[74]; //IOV_2_P
	WordArray[11] = g_TrimRegister_P[75]; //IOV_3_P
	WordArray[12] = g_TrimRegister_P[76]; //IOV_4_P
	WordArray[13] = g_TrimRegister_P[77]; 
	WordArray[14] = g_TrimRegister_P[78]; 
	WordArray[15] = g_TrimRegister_P[79];

	
	/*
	--------------------------------------------------------------------------------------------------------
	Measurement	Target		Notes 
	IOV+		56.25uA		2% tolerance, use steps much finer than 1.125uA, like 0.1uA ok?
	IOV-		54.55uA	
			
	Procedure:		
		1. Power up into I2C mode
		2. have BPP just go from 0 to 5V stay there don't complete zig-zag, 
		3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.  Refer to 'ConfigBit' sheet 
		   Bit 17: password to remain in testmode0
		   Bit 18: password to remain in testmode1 & prevent drain High exiting I2C
		4. observe ZLOV on drain, 
		5. TEST_CTRL1<5>=1 to disable delays on VPIN, 
		6. release VPIN (SDA) for VPIN operation.  		
		7. inject current into VPIN starting low to find the IOV+ threshold by looking when drain flips.		
		8. Once drain flipped, now search down to find IOV-		

	Vrigin parts are ~ 53uA IOV+ for first silicon
	--------------------------------------------------------------------------------------------------------
	*/

	if(g_USE_VR_600K==false)
	{
		Setup_Resources_for_I2C_P();
		PowerUp_I2C_P();

		DSM_I2C_Write('b', g_TM_CTRL, 0x06);	//0x40, 0x06 (enable analog mode + core_en)

		//3. write CFG<18:17>=10 on RegAddr 'ANA_CTRL_1' to stay in I2C after powerup.
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0024);	//0x46, 0x0024 (I2C password + observe drain "Line OV" signal

		//Release Vpin and expect Vpin drop to ~2.3V after command issued.
		DSM_I2C_Write('b', g_PINSDA_CTRL, 0x01);	//0x4E, 0x01 (release Vpin)
		//DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);	//Disable DSM I2C

		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

		//6. release VPIN (SDA) for VPIN operation.  		
			UV_dvi->set_current(UV_ch, 1e-9, RANGE_300_UA);	//set really low current for Vmeas
			UV_dvi->set_voltage(UV_ch, 45, VOLT_50_RANGE); 
			delay(1);

		//Drain setup to connect to Ridder board with RL load and set Drain to 5V and ready for vMeas mode
			D_dvi->set_current(D_ch, 5e-3, RANGE_300_MA); // Does not need 100mA for this test.
			D_dvi->set_voltage(D_ch, 5.0, VOLT_20_RANGE); // DVI_11_0
			//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
			D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
			wait.delay_10_us(20);
			
			//7. inject current into VPIN starting low to find the IOV+ threshold by looking when drain flips.	
			//8. Once drain flipped, now search down to find IOV-		
			Search_iOVp_P(&iOVp_pt_P);
			PiDatalog(func, 	A_iOVp_pt_P,      iOVp_pt_P,              26, POWER_MICRO);

			g_iOVp_pt_P = iOVp_pt_P;

			Search_iOVm_P(&iOVm_pt_P);  //only for TEST to observe iOV- is working here.  No need to datalog.

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
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0024);	//0x46, 0x0024 (I2C password + observe drain "Line OV" signal

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

		UV_dvi->set_voltage(UV_ch, 30, VOLT_50_RANGE); 
		wait.delay_10_us(20);
		UV_dvi->set_current(UV_ch, 70e-6, RANGE_300_UA);	
		UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_CURRENT);
		wait.delay_10_us(20);

		//7. inject current into VPIN starting low to find the IOV+ threshold by looking when drain flips.	
			//8. Once drain flipped, now search down to find IOV-		
			Search_iOVp_P(&iOVp_pt_P);
			PiDatalog(func, 	A_iOVp_pt_P,      iOVp_pt_P,              26, POWER_MICRO);

			Open_relay(K1_UV_RB);	//UV to RB_10kohm
			Open_relay(K2_UV_RB);	//UV to RB_600k to K2_UV to DVI-21-1
			Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
			delay(1);

		Power_Down_I2C_P();
	}
}
