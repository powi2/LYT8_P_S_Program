//==============================================================================
// IOV_P.cpp (User function)
// 
//    void IOV_P_user_init(test_function& func)
//    void IOV_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "IOV_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_P_user_init(test_function& func)
{
	IOV_P_params *ours;
    ours = (IOV_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_P_params *ours;
    ours = (IOV_P_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_IOV_P, gFuncNum, 24,	POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	// Test Names //
	float	iOVp_Tgt_P	=0,
			iOVp_L_PF_P	=0,
			iOVp_H_PF_P	=0,
			iOVp_P		=0,
			iOVp_Err_P	=0,
			iOVm_L_PF_P	=0,
			iOVm_H_PF_P	=0,
			iOVm_P		=0,
			iOVm_Err_P	=0,
			iOV_Hys_P	=0,
			IOV_P_TT	=0;

	//int		i;

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
			Search_iOVp_P(&iOVp_P);
				PiDatalog(func, 	A_iOVp_P,      iOVp_P,					26, POWER_MICRO);
				PiDatalog(func, 	A_iOVp_Tgt_P,  gP_iOVp_TARGET_Trimops,  26, POWER_MICRO);

			g_iOVp_meas_P = iOVp_P;
			if(iOVp_P > 90) g_iOVp_meas_P = 99e-6;

			Search_iOVm_P(&iOVm_P);  
				PiDatalog(func, 	A_iOVm_P,      iOVm_P,					26, POWER_MICRO);

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
			Search_iOVp_P(&iOVp_P);
			PiDatalog(func, 	A_iOVp_P,      iOVp_P,              26, POWER_MICRO);

			Open_relay(K1_UV_RB);	//UV to RB_10kohm
			Open_relay(K2_UV_RB);	//UV to RB_600k to K2_UV to DVI-21-1
			Open_relay(K2_D_RB);	//D  to RB_82uH_50ohm to K2_D to DVI-11-0
			delay(1);

		Power_Down_I2C_P();
	}


}
