//==============================================================================
// Continuity.cpp (User function)
// 
//    void Continuity_user_init(test_function& func)
//    void Continuity(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "Continuity.h"
#include "digital_scan_module.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Continuity_user_init(test_function& func)
{
	Continuity_params *ours;
    ours = (Continuity_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Continuity(test_function& func)
{
    // The two lines below must be the first two in the function.
    Continuity_params *ours;
    ours = (Continuity_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Continuity, gFuncNum, 15, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_Continuity == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();


	// Test Names //
	float VcontD=0; 
	float IcontD=0;
	float VcontD_1mA=0; 
	float VcontD_Rat=0;

	float VcontBPP=0; 
	float IcontBPP=0;
	float VcontBPP_1mA=0; 
	float VcontBPP_Rat=0; 

	float VcontUV=0;
	float IcontUV=0;
	float VcontUV_1mA=0; 
	float VcontUV_Rat=0; 

	float VcontTS=0;
	float IcontTS=0;
	float VcontTS_1mA=0; 
	float VcontTS_Rat=0; 

	float VcontBPS=0; 
	float IcontBPS=0; 
	float VcontBPS_1mA=0; 
	float VcontBPS_Rat=0; 

	float VcontHBP=0; 
	float IcontHBP=0; 
	float VcontHBP_1mA=0; 
	float VcontHBP_Rat=0; 


	float VcontFB=0;
	float IcontFB=0; 
	float VcontFB_1mA=0; 
	float VcontFB_Rat=0; 

	float VcontIS=0;
	float Icont6mA_IS=0; 
	float VcontIS_1mA=0; 
	float VcontIS_Rat=0; 

	float VcontSDA=0;
	float IcontSDA=0; 
	float VcontSDA_1mA=0; 
	float VcontSDA_Rat=0; 

	float VcontSCL=0;
	float IcontSCL=0; 
	float VcontSCL_1mA=0; 
	float VcontSCL_Rat=0;

	float VcontFW=0;
	float IcontFW=0; 
	float VcontFW_1mA=0; 
	float VcontFW_Rat=0; 

	float VcontVR=0;
	float IcontVR=0; 
	float VcontVR_1mA=0; 
	float VcontVR_Rat=0; 

	float VcontB=0;
	float IcontB=0; 
	float VcontB_1mA=0; 
	float VcontB_Rat=0; 

	float VcontHSG=0;
	float IcontHSG=0; 
	float VcontHSG_1mA=0; 
	float VcontHSG_Rat=0; 

	float VcontBPP_cap = 0;
	int VcontBPP_capGNG = 0;

	////////float VcontUV=0;
	////////float VcontIS=0; 
	
	
	////////float VcontSR=0;
	////////float VcontVO=0; 
	////////float VcontFW=0;

	 
	////////float IcontUV=0;
	////////float IcontIS=0; 

	
	////////float IcontSR=0;
	////////float IcontVO=0; 
	////////float IcontFW=0;
	//////////float GNDRes_Se=0;
	//////////float GNDRes_Pri=0;
	
	
	////////float VcontUV_1mA=0;
	////////float VcontIS_1mA=0; 
	
	
	////////float VcontSR_1mA=0; 
	////////float VcontVO_1mA=0; 
	////////float VcontFW_1mA=0;
	
	
	////////float VcontUV_Rat=0;
	////////float VcontIS_Rat=0; 
	
	
	////////float VcontSR_Rat=0;
	////////float VcontVO_Rat=0; 
	////////float VcontFW_Rat=0;
	////////float vmeas=0;
	////////float imeas=0;
	////////float Icont6mA_IS=0;
	////////float Vcont_VBD_low = 0;
	////////float Vcont_VBD_high = 0;
	////////float Vcont_VBD_rat  = 0;	
	////////float Vcont_SDA_low = 0;
	////////float Vcont_SDA_high = 0;
	////////float Vcont_SDA_rat = 0;		
	////////float Vcont_uVCC_low = 0;
	////////float Vcont_uVCC_high = 0;
	////////float Vcont_uVCC_rat = 0;		
	////////float Vcont_SCL_low = 0;
	////////float Vcont_SCL_high = 0;
	////////float Vcont_SCL_rat = 0;			
	////////float Vcont_COMP_low = 0;
	////////float Vcont_COMP_high = 0;
	////////float Vcont_COMP_rat = 0;
	////////float Icont_VBD = 0;
	////////float Icont6mA_SR = 0;
	////////float Icont_SDA = 0;
	////////float Icont_SCL = 0;
	////////float Icont_uVCC = 0;
	////////float VcontBPP_cap = 0;
	////////int VcontBPP_capGNG = 0;
	float Continuity_TT = 0;
	Pulse pulse;

	// Declare Variables //
	float UpperLimit = 0;
	float LowerLimit = 0;

	//--------------------------------------------------------------------------------------------------------------
	// Pins can be tested in groups first with -100uA and 1mA ESD tests to save test time.
	// Primary:   Drain, TS, UV & BPP.
	// Secondary: IS, SDA, SCL, BPS, FB, HBP, Boost, HSG, VR & FW. (pin 12 is NC.  No continuity test)
	// Then Rcontact on Primary & Secondary.
	// 16 pins total.

	//----------------------------------------------------------------------------------------------------------------
	//Need to pay attention to DVI_AGNDS on LB to ensure it's connected properly to either Primary or Secondary.
	//By default, DVI_9_GNDS, DVI_11_GNDS & DVI_13_GNDS & DVI_21_GNDS are connected to Primary GND.
	//Test Primary Continuity first: Drain (DVI_11_0), BPP (DVI_11_1), TS (OVI_3_0) & Vpin (DVI_21_1).
	//Test Secondary Continuity 2nd: IS (DVI_13_1), SDA (OVI_3_5), SCL (OVI_3_6), BPS (DVI_21_0), FB (OVI_3_7)
	//                               HBP (DVI_13_0), B (OVI_3_2), HSG (OVI_1_0), VR (DVI_9_1) & FW (OVI_3_4)
	//Test Primary & Secondary GND sense.
	//--------------------------------------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------------------------------------------
	//Vcont for  Drain (DVI_11_0), BPP (DVI_11_1), TS (OVI_3_0) & UV  (DVI_21_1)
	//--------------------------------------------------------------------------------------------------------------

	//Start -------------------------- 100uA -----------------------------------------------------------------------------//

	//Set up instruments:

	//Primary:
	D_dvi->set_current(D_ch, 100e-6, RANGE_300_UA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	BPP_dvi->set_current(BPP_ch, 100e-6, RANGE_300_UA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE); 
	TS_ovi3->set_current(TSovi3_ch, 100e-6, RANGE_300_UA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_2_RANGE); 
	UV_dvi->set_current(UV_ch, 100e-6, RANGE_300_UA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); 

	//Secondary:
	IS_dvi2k->set_current(IS_ch, 100e-6, RANGE_200_UA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); 
	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_20_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_2_RANGE); 
	SDA_ovi3->set_current(SDA_ch, 100e-6, RANGE_3_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_2_RANGE);
	FW_ovi3->set_current(FW_ch, 100e-6, RANGE_3_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 100e-6, RANGE_3_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_2_RANGE); 
	HSG_ovi->set_current(HSG_ch, 0.1e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_2_RANGE);
	B_ovi3->set_current(B_ch1, 100e-6, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_2_RANGE); 
	VR_dvi->set_current(VR_ch, 100e-6, RANGE_3_MA);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_2_RANGE); 
	FW_ovi3->set_current(FW_ch, 100e-6, RANGE_3_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(100);



	// Drain //
	D_dvi->set_current(D_ch, -100e-6, RANGE_300_UA);
	D_dvi->set_voltage(D_ch, -2.0, VOLT_2_RANGE); 
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);

	// BPP //
	BPP_dvi->set_current(BPP_ch, -100e-6, RANGE_300_UA);
	BPP_dvi->set_voltage(BPP_ch, -2.0, VOLT_2_RANGE); 
	
	// TS //
	TS_ovi3->set_current(TSovi3_ch, -100e-6, RANGE_300_UA);
	TS_ovi3->set_voltage(TSovi3_ch, -2.0, VOLT_2_RANGE); 
	TS_ovi3->set_meas_mode(TSovi3_ch, DVI_MEASURE_VOLTAGE);

	// UV //
	UV_dvi->set_current(UV_ch, -100e-6, RANGE_300_UA);
	UV_dvi->set_voltage(UV_ch, -2.0, VOLT_2_RANGE); 
	UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_VOLTAGE);


	// 100uA continuity //
	wait.delay_10_us(200);
	VcontD  = D_dvi->measure_average(5);
	VcontTS = TS_ovi3->measure_average(5);
	VcontUV = UV_dvi->measure_average(5);

	BPP_dvi->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(200);
	VcontBPP = BPP_dvi->measure_average(5);
	//End -------------------------- 100uA -----------------------------------------------------------------------------//


	//Start -------------------------- 1mA -----------------------------------------------------------------------------//
	// BPP //
	BPP_dvi->set_current(BPP_ch, -1.0e-3, RANGE_3_MA);
	// Drain //
	D_dvi->set_current(D_ch, -1.0e-3, RANGE_3_MA);	
	// TS //
	TS_ovi3->set_current(TSovi3_ch, -1.0e-3, RANGE_3_MA);
	// UV //
	UV_dvi->set_current(UV_ch, -1.0e-3, RANGE_3_MA);

	// 1mA continuity //
	wait.delay_10_us(200);
	VcontBPP_1mA = BPP_dvi->measure_average(5);
	VcontTS_1mA = TS_ovi3->measure_average(5);
	VcontUV_1mA = UV_dvi->measure_average(5);

	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(200);
	VcontD_1mA = D_dvi->measure_average(5);
	
	if(VcontD  != 0.0) VcontD_Rat   = VcontD_1mA   / VcontD;
	if(VcontBPP!= 0.0) VcontBPP_Rat = VcontBPP_1mA / VcontBPP;
	if(VcontUV != 0.0) VcontUV_Rat  = VcontUV_1mA  / VcontUV;
	if(VcontTS != 0.0) VcontTS_Rat  = VcontTS_1mA  / VcontTS;

	// Drain //
	D_dvi->set_current(D_ch, 100e-6, RANGE_3_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	// BPP //
	BPP_dvi->set_current(BPP_ch, 100e-6, RANGE_3_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE); 
	// TS //
	TS_ovi3->set_current(TSovi3_ch, 100e-6, RANGE_3_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_2_RANGE); 
	// UV //
	UV_dvi->set_current(UV_ch, 100e-6, RANGE_3_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); 

	//Change DVI current range for Icont tests next.
	// Drain //
	D_dvi->set_current(D_ch, 100e-6, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	// BPP //
	BPP_dvi->set_current(BPP_ch, 100e-6, RANGE_30_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE); 
	// TS //
	TS_ovi3->set_current(TSovi3_ch, 100e-6, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_2_RANGE); 
	// UV //
	UV_dvi->set_current(UV_ch, 100e-6, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); 

	//End -------------------------- 1mA -----------------------------------------------------------------------------//
	

	// -------------------------------------------------------------------------------------------------------------- //
	//								Icont test for Primary								                              //
	// -------------------------------------------------------------------------------------------------------------- //
	// Setup Drain pin Icont (DVI_11_0) & BPP (DVI_11_1) is used as GND.
	//--------------------------------------------------------------------------------------------------------------
	
	//Set up BPP_DVI_11_1 as GND.
	BPP_dvi->close_relay(CHANNEL_SHORT);
	BPP_dvi->close_relay(BUS_SENSE1);
	BPP_dvi->close_relay(BUS_FORCE1);
	BPP_dvi->set_meas_mode(BPP_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(250);


	BPP_dvi->set_current(BPP_ch, 20.0e-3, RANGE_30_MA);
	D_dvi->set_current(D_ch, -6e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, -0.1, VOLT_2_RANGE); 
	wait.delay_10_us(50);//Prevent glitch.
	D_dvi->set_voltage(D_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(50);//Prevent glitch.

	IcontD   = BPP_dvi->measure_average(5);

	//----------------------------------------------------------------------------------------------------------------//
	// BPP  Icont (DVI_11_1) & Drain (DVI_11_0) will be used as GND.
	//-----------------------------------------------------------------------------------------------------------------
	// Drain (DVI_11_0) is used as GND. Both BPP & D need to be at 0mA or glitches happen.
	//-----------------------------------------------------------------------------------------------------------------
	BPP_dvi->set_current(BPP_ch, 0.0e-3, RANGE_30_MA);
	D_dvi->set_current(D_ch, 0.0e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(100);//Prevent glitch.

	BPP_dvi->open_relay(BUS_SENSE1);
	BPP_dvi->open_relay(BUS_FORCE1);
	D_dvi->close_relay(BUS_SENSE0);
	D_dvi->close_relay(BUS_FORCE0);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(250);

	D_dvi->set_current(D_ch, 20e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	BPP_dvi->set_current(BPP_ch, -6e-3, RANGE_30_MA);
	BPP_dvi->set_voltage(BPP_ch, -0.1, VOLT_2_RANGE); // DVI_11_1
	wait.delay_10_us(50);//Prevent glitch.

	BPP_dvi->set_voltage(BPP_ch, -1.5, VOLT_2_RANGE); // DVI_11_1
	wait.delay_10_us(100);

	IcontBPP = D_dvi->measure_average(5);

	D_dvi->set_current(D_ch, 20e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	BPP_dvi->set_current(BPP_ch, 6e-3, RANGE_30_MA);
	BPP_dvi->set_voltage(BPP_ch, -0.1, VOLT_2_RANGE); // DVI_11_1
	wait.delay_10_us(50);//Prevent glitch.

	D_dvi->set_current(D_ch, 0.1e-3, RANGE_30_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	BPP_dvi->set_current(BPP_ch, 0.1e-3, RANGE_30_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(50);

	BPP_dvi->open_relay(CHANNEL_SHORT);
	D_dvi->open_relay(BUS_SENSE0);
	D_dvi->open_relay(BUS_FORCE0);
	Open_relay(K3_D_TB);
	wait.delay_10_us(250);

	//----------------------------------------------------------------------------------------------------------------//
	// UV  Icont (DVI_21_1) & BPS (DVI_21_0) will be used as GND
	//----------------------------------------------------------------------------------------------------------------

	// UV //
	UV_dvi->set_current(UV_ch, 100e-6, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); // DVI_21_1

	//BPS_DVI_21_0 is used as GND.
	BPS_dvi->set_current(BPS_ch, 100e-6, RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE); // DVI_21_0
	wait.delay_10_us(10);

	BPS_dvi->close_relay(CHANNEL_SHORT);
	BPS_dvi->close_relay(BUS_SENSE0);
	BPS_dvi->close_relay(BUS_FORCE0);
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(250);

	BPS_dvi->set_current(BPS_ch, 20.0e-3, RANGE_30_MA);
	UV_dvi->set_current(UV_ch, -6e-3, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, -0.1, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(50);//Prevent glitch.
	UV_dvi->set_voltage(UV_ch, -1.5, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(50);//Prevent glitch.

	IcontUV   = BPS_dvi->measure_average(5);

	UV_dvi->set_current(UV_ch, 0.1e-3, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	BPS_dvi->set_current(BPS_ch, 0.1e-3, RANGE_30_MA);
	wait.delay_10_us(50);

	BPS_dvi->open_relay(CHANNEL_SHORT);
	BPS_dvi->open_relay(BUS_SENSE0);
	BPS_dvi->open_relay(BUS_FORCE0);
	wait.delay_10_us(250);
	//-----------------------------------------------------------------------------------------------------------------//
	// IcontTS @ OVI_3_0 and OVI_3_1 (Boost) through K_OVI3_1 on the LB will be used as GND.
	//-----------------------------------------------------------------------------------------------------------------//
	//OVI3_1 (Boost) is used as GND pin after closing K_OVI_3_1 on the LB. Not TB.
	// Boost //
	B_ovi3->set_current(B_ch1, 100e-6, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_2_RANGE); // OVI_3_1
	//TS
	TS_ovi3->set_current(TSovi3_ch, 100e-6, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_2_RANGE); // OVI_3_0
	wait.delay_10_us(50);
	mux_20->close_relay(MUX_7_3);  //Close K_OVI_3_1 on LB to short OVI_3_1 to OVI3_0
	Close_relay(K1_B_SPI_RB);      //Close relay on K1_B to ensure Force and Sense of OVI_3_1 are shorted together
	wait.delay_10_us(250);
	// Boost //
	B_ovi3->set_current(B_ch1, 20e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0, VOLT_2_RANGE); //OVI_3_1
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	//TS
	TS_ovi3->set_current(TSovi3_ch, -6e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, -1.5, VOLT_2_RANGE); // OVI_3_0
	wait.delay_10_us(50);
	IcontTS = B_ovi3->measure_average(5);

	//Reset back to 0V
	//TS
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_2_RANGE); // OVI_3_0
	wait.delay_10_us(10);
	TS_ovi3->set_current(TSovi3_ch, 0.1e-3, RANGE_30_MA);
	wait.delay_10_us(10);
	//Open K_OVI_3_1 on LB to short OVI_3_1 to OVI3_0
	mux_20->open_relay(MUX_7_3);
	Open_relay(K1_B_SPI_RB);  
	wait.delay_10_us(250);

	// -------------------------------------------------------------------------------------------- //
	// Primary SRC-P Gnd Res check
	// --------------------------------------------------------------------------------------------- //
	// Float UV (DVI_21_1) & TS (OVI_3_0)
	UV_dvi->open_relay(CONN_FORCE1);
	UV_dvi->open_relay(CONN_SENSE1);
	TS_ovi3->disconnect(TSovi3_ch);

	// Connect DVI11_1 (BPP) to GND through BUS lines
	BPP_dvi->close_relay(BUS_SENSE1);
	BPP_dvi->open_relay(BUS_FORCE1);
	BPP_dvi->open_relay(CONN_FORCE1);
	BPP_dvi->open_relay(CONN_SENSE1);

	//Disconnect unnecssary muxes.
	mux_14->open_relay(MUX_BANK_3_4);
	mux_14->open_relay(MUX_BANK_1_2);

	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	mux_14->open_relay(MUX_2_GND);
	mux_14->close_relay(MUX_2_1);   // Connect DVI11_1 BUS_SENSE to GND 
	wait.delay_10_us(250);

	//Measure voltage from BPP (DVI_11_1)
	BPP_dvi->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE);

	// Force -2V, 100mA through Drain pin //
	D_dvi->set_current(D_ch, -100.0e-3, RANGE_300_MA); 
	D_dvi->set_voltage(D_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(50);
	float vmeas = BPP_dvi->measure_average(25);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT); // DVI_11_0 //
	wait.delay_10_us(50);

	float imeas = D_dvi->measure_average(25);
	g_GNDRes_Pri = -vmeas/(imeas + 1e-23);
	if (g_GNDRes_Pri > 0.185) // Fail if GNDRes_Pri higher than 185mohm //
	{
		g_GNDRes_Pri = -g_GNDRes_Pri; // Make negative to force failure. //
		g_Error_Flag = -229;
	}

	// Power down GNDRes 
	
	D_dvi->set_voltage(D_ch, 0, VOLT_2_RANGE); 
	D_dvi->set_current(D_ch, 0.1e-3, RANGE_300_MA); 
	wait.delay_10_us(200);

	// Connect DVI11_1 (BPP) to GND through BUS lines
	BPP_dvi->open_relay(BUS_SENSE1);
	BPP_dvi->open_relay(BUS_FORCE1);
	BPP_dvi->close_relay(CONN_FORCE1);
	BPP_dvi->close_relay(CONN_SENSE1);

	//Reconnect Muxes
	mux_14->close_relay(MUX_BANK_3_4);
	mux_14->close_relay(MUX_BANK_1_2);
	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->open_relay(MUX_3_BUS3);
	mux_14->close_relay(MUX_2_GND);
	mux_14->open_relay(MUX_2_1);   
	wait.delay_10_us(250);

	D_dvi->close_relay(CONN_FORCE0);
	D_dvi->close_relay(CONN_SENSE0);
	D_dvi->open_relay(BUS_FORCE0);
	D_dvi->open_relay(BUS_SENSE0);

	// Float UV (DVI_21_1), TS (OVI_3_0)
	UV_dvi->close_relay(CONN_FORCE1);
	UV_dvi->close_relay(CONN_SENSE1);
	TS_ovi3->connect(TSovi3_ch);
	wait.delay_10_us(250);
	
	//-----------------------------------------------------------------------------------------------------------------
	//Vcont & Icont tests are done on the primary side.
	//Secondary Vcont & Icont tests
	//Switch DVI GNDS to Secondary with relays on LB
	//--------------------------------------------------------------------------------------------------------------


	//Switch GNDs on TMT LB not TB
	mux_20->close_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->close_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->close_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	//-----------------------------------------------------------------------------------------------------------------
	//IS @ DVI_13_1.  Will need to use HBP (DVI_13_0) as GND for IcontIS test.
	//--------------------------------------------------------------------------------------------------------------

	Open_relay(K1_IS_SPI_TB);   //Not sure why K1_IS was closed initially.  Should not be close at this point.
	Open_relay(K1_HBP_SPI_RB);
	Open_relay(K6_VR_SPI_RB);
	delay(3);
	IS_dvi2k->set_current(IS_ch, 100e-6, RANGE_200_UA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_1
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(10);
	IS_dvi2k->set_voltage(IS_ch, -1.5, VOLT_2_RANGE); 	
	wait.delay_10_us(50);
	// 100uA continuity //
	VcontIS = IS_dvi2k->measure_average(5);

	// 1mA continuity //	
	IS_dvi2k->set_current(IS_ch, -1.0e-3, RANGE_2_MA);
	wait.delay_10_us(100);
	VcontIS_1mA = IS_dvi2k->measure_average(5);
	// Calculate ratio //
	if(VcontIS != 0.0)	VcontIS_Rat = VcontIS_1mA  / VcontIS;

	IS_dvi2k->set_current(IS_ch, 100e-6, RANGE_2_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	HBP_dvi2k->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(250);

	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_20_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_2_RANGE); // DVI_13_0
	HBP_dvi2k->set_meas_mode(HBP_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, -6.0e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, -0.1, VOLT_2_RANGE); 
	wait.delay_10_us(50);//Prevent glitch.
	IS_dvi2k->set_voltage(IS_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(100);

	Icont6mA_IS = HBP_dvi2k->measure_average(5);

	IS_dvi2k->set_current(IS_ch, 0.1e-3, RANGE_2_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); 
	HBP_dvi2k->set_current(HBP_ch, 0.1e-3, RANGE_20_MA);
	wait.delay_10_us(50);

	HBP_dvi2k->open_relay(CHANNEL_SHORT);
	wait.delay_10_us(250);
	//-----------------------------------------------------------------------------------------------------------------
	//End of VcontIS & IcontIS
	//-------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------
	//SDA (OVI_3_5), FW (OVI_3_4)
	//SCL (OVI_3_6), FB (OVI_3_7)
	//Icont SDA & FW will be checked in parallel because of closing K_OVI3_4 relay on LB.
	//Icont SCL & FB will be checked in parallel because of closing K_OVI3_4 relay on LB.
	//--------------------------------------------------------------------------------------------------------------
	//SDA (OVI3_5)
	SDA_ovi3->set_current(SDA_ch, -100e-6, RANGE_3_MA);
	SDA_ovi3->set_voltage(SDA_ch, -1.5, VOLT_2_RANGE); // OVI_3_5
	SDA_ovi3->set_meas_mode(SDA_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	VcontSDA = SDA_ovi3->measure_average(5);

	SDA_ovi3->set_current(SDA_ch, 1e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	VcontSDA_1mA = SDA_ovi3->measure_average(5);

	//Calculate Ratio
	if(VcontSDA != 0.0)	VcontSDA_Rat = VcontSDA_1mA / VcontSDA;

	SDA_ovi3->set_current(SDA_ch, 100e-6, RANGE_3_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);

	//-----------------------------------------------------------------------------------------------
	//FW
	//----------------------------------------------------------------------------------------------
	//FW (OVI3_4)
	FW_ovi3->set_current(FW_ch, -100e-6, RANGE_3_MA);
	FW_ovi3->set_voltage(FW_ch, -1.5, VOLT_2_RANGE); // OVI_3_5
	FW_ovi3->set_meas_mode(FW_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	VcontFW = FW_ovi3->measure_average(5);

	FW_ovi3->set_current(FW_ch, 1e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	VcontFW_1mA = FW_ovi3->measure_average(5);

	//Calculate Ratio
	if(VcontFW != 0.0)	VcontFW_Rat = VcontFW_1mA / VcontFW;

	FW_ovi3->set_current(FW_ch, 100e-6, RANGE_3_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);

	//-----------------------------------------------------------------------------------------------
	//SCL
	//----------------------------------------------------------------------------------------------
	//SCL (OVI3_6)
	SCL_ovi3->set_current(SCL_ch, -100e-6, RANGE_3_MA);
	SCL_ovi3->set_voltage(SCL_ch, -1.5, VOLT_2_RANGE); // OVI_3_5
	SCL_ovi3->set_meas_mode(SCL_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	VcontSCL = SCL_ovi3->measure_average(5);

	SCL_ovi3->set_current(SCL_ch, 1e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	VcontSCL_1mA = SCL_ovi3->measure_average(5);

	//Calculate Ratio
	if(VcontSCL != 0.0)	VcontSCL_Rat = VcontSCL_1mA / VcontSCL;

	SCL_ovi3->set_current(SCL_ch, 100e-6, RANGE_3_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);

	//-----------------------------------------------------------------------------------------------
	//FB
	//----------------------------------------------------------------------------------------------
	//FB (OVI3_7)
	FB_ovi3->set_current(FB_ch, -100e-6, RANGE_3_MA);
	FB_ovi3->set_voltage(FB_ch, -1.5, VOLT_2_RANGE); 
	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);

	// 100uA continuity //
	VcontFB = FB_ovi3->measure_average(5);

	// 1mA continuity //	
	FB_ovi3->set_current(FB_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	VcontFB_1mA = FB_ovi3->measure_average(5);
	// Calculate ratio //
	if(VcontFB != 0.0) VcontFB_Rat = VcontFB_1mA  / VcontFB;

	FB_ovi3->set_current(FB_ch, 100e-6, RANGE_3_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 

	//-------------------------------------------------------------------------------------------------------
	//End of Vcont tests for SDA, SCL, FW, FB pins.
	//-------------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------------
	//Icont tests for SDA, SCL, FW, FB pins.
	//-------------------------------------------------------------------------------------------------------

	//Close Relay K_OVI3_4 (Mux_20_8_2) to short OVI3_4 to OVI3_5, OVI3_6 to OVI3_7.
	mux_20->close_relay(MUX_8_2);
	Close_relay(K1_SDA_SPI_TB);   //To guarantee OVI_3_5 is at GND even if no Kelvin connection @ SDA.
	Close_relay(K1_FB_SPI_TB);    //To guarantee OVI_3_7 is at GND even if no Kelvin connection @ FB.
	wait.delay_10_us(250);

	//USE OVI_3_5 & OVI_3_7 as GND.  Current Range change in this case.
	//Check Kelvin connection @ FW (OVI_3_4 ) and SCL (OVI_3_6)
	//OVI_3_5
	SDA_ovi3->set_current(SDA_ch, 100e-6, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_2_RANGE); 
	//OVI_3_7
	FB_ovi3->set_current(FB_ch, 100e-6, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
	//OVI_3_4
	FW_ovi3->set_current(FW_ch, 100e-6, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	//OVI_3_6
	SCL_ovi3->set_current(SCL_ch, 100e-6, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(10);
	//OVI_3_5
	SDA_ovi3->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	SDA_ovi3->set_meas_mode(SDA_ch, OVI_MEASURE_CURRENT);  //To measure IcontFW on OVI_3_4.
	//OVI_3_7
	FB_ovi3->set_current(FB_ch, 20e-3, RANGE_30_MA);
	wait.delay_10_us(10);
	//OVI_3_4
	FW_ovi3->set_current(FW_ch, -6e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, -1.5, VOLT_2_RANGE); 
	//OVI_3_6
	SCL_ovi3->set_current(SCL_ch, -6e-3, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(100);

	IcontFW = SDA_ovi3->measure_average(5);

	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT); //To measure IcontSCL on OVI_3_6.
	wait.delay_10_us(100);

	IcontSCL = FB_ovi3->measure_average(5);

	FW_ovi3->set_current(FW_ch, 0.1e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	FW_ovi3->set_meas_mode(FW_ch, OVI_MEASURE_CURRENT);
	//OVI_3_6
	SCL_ovi3->set_current(SCL_ch, 0.1e-3, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(100);
	Open_relay(K1_SDA_SPI_TB);   //Return Kelvin connection to SDA.
	Open_relay(K1_FB_SPI_TB);    //Return Kelvin connection to FB.
	//Checking Kelvin connection @ SDA & FB.
	//Use FW (OVI_3_4) & SCL (OVI_3_6 ) as GND.
	Close_relay(K1_FW_SPI_TB);   //To guarantee OVI_3_4 is at GND even if no Kelvin connection @ FW.
	Close_relay(K1_SCL_SPI_TB);  //To guarantee OVI_3_5 is at GND even if no Kelvin connection @ SCL.
	wait.delay_10_us(250);

	FW_ovi3->set_current(FW_ch, 20e-3, RANGE_30_MA);     //FW @ 0V/20mA
	SCL_ovi3->set_current(SCL_ch, 20e-3, RANGE_30_MA);   //SCL @ 0V/20mA
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, -6e-3, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, -1.5, VOLT_2_RANGE);

	FW_ovi3->set_meas_mode(FW_ch, OVI_MEASURE_CURRENT);  //To measure IcontSDA on OVI_3_4.

	FB_ovi3->set_current(FB_ch, -6e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(100);

	IcontSDA = FW_ovi3->measure_average(5);

	SCL_ovi3->set_meas_mode(SCL_ch, OVI_MEASURE_CURRENT);  //To measure IcontFB on OVI_3_7.
	wait.delay_10_us(100);

	IcontFB = SCL_ovi3->measure_average(5);

	SDA_ovi3->set_current(SDA_ch, 0.1e-3, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_2_RANGE);
	FB_ovi3->set_current(FB_ch, 0.1e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(10);

	FW_ovi3->set_current(FW_ch, 0.1e-3, RANGE_30_MA);     //FW @ 0V/20mA
	SCL_ovi3->set_current(SCL_ch, 0.1e-3, RANGE_30_MA);   //SCL @ 0V/20mA
	wait.delay_10_us(50);

	Open_relay(K1_FW_SPI_TB);   //Return Kelvin to FW pin.
	Open_relay(K1_SCL_SPI_TB);  //Return Kelvin to SCL pin.
	mux_20->open_relay(MUX_8_2);//Disconnect OVI_3_4 from OVI_3_5 and OVI_3_6 from OVI_3_7
	wait.delay_10_us(250);
	//-----------------------------------------------------------------------------------------------------------------
	//End of Vcont & Icont tests for SDA (OVI_3_5), FW (OVI_3_4), SCL (OVI_3_6) & FB (OVI_3_7)
	//--------------------------------------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------------------------------------
	//BPS @ DVI_21_0.  Will need to use DVI_21_1 as GND for IcontBPS tests.
	//--------------------------------------------------------------------------------------------------------------

	// BPS //
	BPS_dvi->set_current(BPS_ch, 2.5e-3, RANGE_3_MA);
	BPS_dvi->set_voltage(BPS_ch, -1.5, VOLT_2_RANGE); // DVI_21_0
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);
	BPS_dvi->set_current(BPS_ch, -100e-6, RANGE_3_MA);

	// 100uA continuity //
	wait.delay_10_us(100);
	VcontBPS = BPS_dvi->measure_average(5);

	// 1mA continuity //	
	BPS_dvi->set_current(BPS_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	VcontBPS_1mA = BPS_dvi->measure_average(5);
	// Calculate ratio //
	if(VcontBPS != 0.0) VcontBPS_Rat = VcontBPS_1mA  / VcontBPS;


	BPS_dvi->set_current(BPS_ch, 100e-6, RANGE_3_MA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(10);
	BPS_dvi->set_current(BPS_ch, 100e-6, RANGE_30_MA);
	UV_dvi->set_current(UV_ch, 100e-6, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(10);

	UV_dvi->close_relay(CHANNEL_SHORT);
	UV_dvi->close_relay(BUS_SENSE1);
	UV_dvi->close_relay(BUS_FORCE1);
	UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(250);

	UV_dvi->set_current(UV_ch, 20e-3, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); // DVI_21_1
	BPS_dvi->set_current(BPS_ch, -6e-3, RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch, -0.1, VOLT_2_RANGE); // DVI_21_0
	wait.delay_10_us(10);
	BPS_dvi->set_voltage(BPS_ch, -1.5, VOLT_2_RANGE); // DVI_21_0
	wait.delay_10_us(100);

	IcontBPS = UV_dvi->measure_average(5);

	UV_dvi->set_current(UV_ch, 0.1e-3, RANGE_30_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_2_RANGE); // DVI_21_1
	BPS_dvi->set_current(BPS_ch, 0.1e-3, RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE); // DVI_21_0
	wait.delay_10_us(50);

	UV_dvi->open_relay(CHANNEL_SHORT);
	UV_dvi->open_relay(BUS_SENSE1);
	UV_dvi->open_relay(BUS_FORCE1);
	wait.delay_10_us(250);
	//-----------------------------------------------------------------------------------------------------------------
	//End of VcontBPS & IcontBPS
	//-------------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------------
	// HBP @ dvi_13_0 and will need to use dvi_13_1 (IS) as GND for IcontHBP
	//--------------------------------------------------------------------------------------------------------------
	HBP_dvi2k->set_current(HBP_ch, 2e-3, RANGE_2_MA);
	HBP_dvi2k->set_voltage(HBP_ch, -1.5, VOLT_2_RANGE); 
	HBP_dvi2k->set_meas_mode(HBP_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);
	HBP_dvi2k->set_current(HBP_ch, -100e-6, RANGE_20_MA);

	// 100uA continuity //
	wait.delay_10_us(100);
	VcontHBP = HBP_dvi2k->measure_average(5);

	// 1mA continuity //	
	HBP_dvi2k->set_current(HBP_ch, -1.0e-3, RANGE_2_MA);
	wait.delay_10_us(200);
	VcontHBP_1mA = HBP_dvi2k->measure_average(5);
	// Calculate ratio //
	if(VcontHBP != 0.0) VcontHBP_Rat = VcontHBP_1mA  / VcontHBP;

	
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);
	HBP_dvi2k->set_current(HBP_ch, 0.1e-3, RANGE_20_MA);
	IS_dvi2k->set_current(IS_ch, 0.1e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); 
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(50);

	IS_dvi2k->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(250);
	//IS @ GND 0V/20mA
	IS_dvi2k->set_current(IS_ch, 19e-3, RANGE_20_MA);
	HBP_dvi2k->set_current(HBP_ch, -6e-3, RANGE_20_MA);
	HBP_dvi2k->set_voltage(HBP_ch, -1.5, VOLT_2_RANGE);
	wait.delay_10_us(500);

	IcontHBP = IS_dvi2k->measure_average(5);

	HBP_dvi2k->set_current(HBP_ch, 0.1e-3, RANGE_20_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_2_RANGE);
	IS_dvi2k->set_current(IS_ch, 0.1e-3, RANGE_20_MA);
	wait.delay_10_us(50);

	IS_dvi2k->open_relay(CHANNEL_SHORT);
	wait.delay_10_us(250);

	//-----------------------------------------------------------------------------------------------------------------
	//End of VcontHBP & IcontHBP
	//-------------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------
	//VR (DVI_9_1).  DVI_9_0 (connected to VR Insert Board) will be used as GND.
	
	//--------------------------------------------------------------------------------------------------------------
	//VR 

	VR_dvi->set_current(VR_ch, 100e-6, RANGE_3_MA);
	VR_dvi->set_voltage(VR_ch, -1.5, VOLT_2_RANGE); 
	VR_dvi->set_meas_mode(VR_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(1000);

	VcontVR = VR_dvi->measure_average(5);

	// 1mA continuity //	
	VR_dvi->set_current(VR_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(500);
	VcontVR_1mA = VR_dvi->measure_average(5);
	// Calculate ratio //
	if(VcontVR != 0.0) VcontVR_Rat = VcontVR_1mA  / VcontVR;

	VR_dvi->set_current(VR_ch, 100e-6, RANGE_3_MA);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(10);
	VR_dvi->set_current(VR_ch, 100e-6, RANGE_30_MA);
	VR_dvi->set_current(VRstep_ch, 100e-6, RANGE_30_MA);
	VR_dvi->set_voltage(VRstep_ch, 0.0, VOLT_2_RANGE); 
	VR_dvi->set_meas_mode(VRstep_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(100);

	VR_dvi->close_relay(CHANNEL_SHORT);
	VR_dvi->close_relay(BUS_SENSE0);
	VR_dvi->close_relay(BUS_FORCE0);
	wait.delay_10_us(250);

	VR_dvi->set_current(VRstep_ch, 20E-3, RANGE_30_MA);
	VR_dvi->set_current(VR_ch, -6e-3, RANGE_30_MA);
	VR_dvi->set_voltage(VR_ch, -1.5, VOLT_2_RANGE); 
	wait.delay_10_us(100);

	IcontVR = VR_dvi->measure_average(5);

	VR_dvi->set_current(VR_ch, 0.1e-3, RANGE_30_MA);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_2_RANGE); 
	VR_dvi->set_current(VRstep_ch, 0.1E-3, RANGE_30_MA);
	wait.delay_10_us(100);

	VR_dvi->open_relay(CHANNEL_SHORT);
	VR_dvi->open_relay(BUS_SENSE0);
	VR_dvi->open_relay(BUS_FORCE0);
	wait.delay_10_us(250);

	//-----------------------------------------------------------------------------------------------------------------
	//End of VcontVR & IcontVR
	//-------------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------
	//Boost (OVI_3_1).  OVI_3_0 (TS pin) will be needed as GND for IcontB thru K_OVI3_1 on LB.
	//HSG   (OVI_1_0).  OVI_1_1 (Bufwill be needed as GND for IcontHSG thru K_OVI1_0 on LB
	//--------------------------------------------------------------------------------------------------------------
	//Boost (OVI3_1)
	B_ovi3->set_current(B_ch1, -100e-6, RANGE_3_MA);
	B_ovi3->set_voltage(B_ch1, -1.5, VOLT_2_RANGE); // OVI_3_5
	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	VcontB = B_ovi3->measure_average(5);

	B_ovi3->set_current(B_ch1, 1e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	VcontB_1mA = B_ovi3->measure_average(5);

	//Calculate Ratio
	if(VcontB != 0.0)	VcontB_Rat = VcontB_1mA / VcontB;

	B_ovi3->set_current(B_ch1, 100e-6, RANGE_3_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);

	B_ovi3->set_current(B_ch1, 100e-6, RANGE_30_MA);
	TS_ovi3->set_current(TSovi3_ch, 100e-6, RANGE_30_MA);
	TS_ovi3->set_meas_mode(TSovi3_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	//Short OVI_3_0 to OVI_3_1 thru K_OVI3_1.
	mux_20->close_relay(MUX_7_3);
	mux_20->open_relay(MUX_7_2);
	Close_relay(K1_TS_RB);     //Ensure OVI_3_0 is connected to GND
	wait.delay_10_us(250);

	//Start pulling current thru Boost pin.
	TS_ovi3->set_current(TSovi3_ch, 20E-3, RANGE_30_MA);
	B_ovi3->set_current(B_ch1, -6e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, -1.5, VOLT_2_RANGE);
	wait.delay_10_us(100);

	IcontB = TS_ovi3->measure_average(5);

	TS_ovi3->set_current(TSovi3_ch, 0.1E-3, RANGE_30_MA);
	B_ovi3->set_current(B_ch1, 0.1e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(100);

	mux_20->open_relay(MUX_7_3);
	Open_relay(K1_TS_RB);
	wait.delay_10_us(250);
	
	//-----------------------------------------------------------------------------------------------------------------
	//End of VcontB & IcontB.  IcontB has issue.  Need to resolve.
	//-------------------------------------------------------------------------------------------------------------------
	//HSG (OVI1_0)
	HSG_ovi->set_current(HSG_ch, -100e-6, RANGE_3_MA);
	HSG_ovi->set_voltage(HSG_ch, -1.5, VOLT_2_RANGE); // OVI_3_5
	HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	VcontHSG = HSG_ovi->measure_average(5);

	HSG_ovi->set_current(HSG_ch, 1e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	VcontHSG_1mA = HSG_ovi->measure_average(5);

	//Calculate Ratio
	if(VcontHSG != 0.0)	VcontHSG_Rat = VcontHSG_1mA / VcontHSG;

	HSG_ovi->set_current(HSG_ch, 100e-6, RANGE_3_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_2_RANGE); 
	wait.delay_10_us(50);

	HSG_ovi->set_current(HSG_ch, 100e-6, RANGE_30_MA);
	BCLMP_ovi->set_current(BUFCLMP_ch, 100e-6, RANGE_30_MA);
	BCLMP_ovi->set_voltage(BUFCLMP_ch, 0.0, VOLT_2_RANGE); 
	BCLMP_ovi->set_meas_mode(BUFCLMP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	//Short OVI_3_0 to OVI_3_1 thru K_OVI3_0.
	mux_20->close_relay(MUX_8_3);
	wait.delay_10_us(250);

	//Start pulling current thru HSG pin.
	BCLMP_ovi->set_current(BUFCLMP_ch, 20E-3, RANGE_30_MA);
	HSG_ovi->set_current(HSG_ch, -6e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, -1.5, VOLT_2_RANGE);
	wait.delay_10_us(100);

	IcontHSG = BCLMP_ovi->measure_average(5);

	BCLMP_ovi->set_current(BUFCLMP_ch, 0.1E-3, RANGE_30_MA);
	HSG_ovi->set_current(HSG_ch, 0.1e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(100);

	mux_20->open_relay(MUX_8_3);
	wait.delay_10_us(250);

	//------------------------------------------------------------------------------------------- //
	// Secondary SRC-S Gnd Res check
	// ------------------------------------------------------------------------------------------- //
	// Float all pins except IS and VR to prevent extra current path. //
	SDA_ovi3->disconnect(SDA_ch);
	SCL_ovi3->disconnect(SCL_ch);
	BPS_dvi->open_relay(CONN_FORCE0); // Float //
	BPS_dvi->open_relay(CONN_SENSE0); // Float //
	FB_ovi3->disconnect(FB_ch);
	B_ovi3->disconnect(B_ch1);
	HSG_ovi->disconnect(HSG_ch);
	HBP_dvi2k->open_relay(CONN_FORCE0);
	HBP_dvi2k->open_relay(CONN_SENSE0);
	FW_ovi3->disconnect(FW_ch);

	//Disconnect unnecssary muxes.
	mux_14->open_relay(MUX_BANK_3_4);
	mux_14->open_relay(MUX_BANK_1_2);

	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	mux_14->open_relay(MUX_2_GND);
	mux_14->close_relay(MUX_2_1);   // Connect DVI21_1 BUS_SENSE to GND 
	
	// Connect DVI21_1 (VR) to GND through BUS lines
	VR_dvi->close_relay(BUS_SENSE1);
	VR_dvi->open_relay(BUS_FORCE1);
	VR_dvi->open_relay(CONN_FORCE1);
	VR_dvi->open_relay(CONN_SENSE1);
	
	wait.delay_10_us(400);
	VR_dvi->set_meas_mode(VR_ch, DVI_MEASURE_VOLTAGE);

	// Force -2V, 100mA through IS pin //

	//There is a 1V positive glitch on Is due to current range change from 20mA to 200mA.
	IS_dvi2k->set_current(IS_ch, -1e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(10);

	IS_dvi2k->set_current(IS_ch, -100.0e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, -2, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(50);
	vmeas = VR_dvi->measure_average(25);

	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT); // DVI_13_0, dvi2k // 
	wait.delay_10_us(50);
	imeas = IS_dvi2k->measure_average(25);
	g_GNDRes_Se = -vmeas/(imeas + 1e-23);
	if (g_GNDRes_Se > 0.1) // Fail if GNDRes_Se higher than 100mohm //
	{
		g_GNDRes_Se = -g_GNDRes_Se; // Make negative to force failure. //
		g_Error_Flag = -228;
	}

	// Reset IS voltage and current.
	IS_dvi2k->set_current(IS_ch, -100e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(50);

	// Reset IS voltage and current.
	IS_dvi2k->set_current(IS_ch, 0.1e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(50);

	// Reconnect Resources to DUT Pins.
	SDA_ovi3->connect(SDA_ch);
	SCL_ovi3->connect(SCL_ch);
	BPS_dvi->close_relay(CONN_FORCE0); // Float //
	BPS_dvi->close_relay(CONN_SENSE0); // Float //
	FB_ovi3->connect(FB_ch);
	B_ovi3->connect(B_ch1);
	HSG_ovi->connect(HSG_ch);
	HBP_dvi2k->close_relay(CONN_FORCE0);
	HBP_dvi2k->close_relay(CONN_SENSE0);
	FW_ovi3->connect(FW_ch);

	//Disconnect unnecssary muxes.
	mux_14->close_relay(MUX_BANK_3_4);
	mux_14->close_relay(MUX_BANK_1_2);

	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->open_relay(MUX_3_BUS3);
	mux_14->close_relay(MUX_2_GND);
	mux_14->open_relay(MUX_2_1);   // Connect DVI21_1 BUS_SENSE to GND 
	
	// Connect DVI21_1 (VR) to GND through BUS lines
	VR_dvi->open_relay(BUS_SENSE1);
	VR_dvi->open_relay(BUS_FORCE1);
	VR_dvi->close_relay(CONN_FORCE1);
	VR_dvi->close_relay(CONN_SENSE1);
	wait.delay_10_us(400);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Switch GNDs back to primary GNDS
	mux_20->open_relay(MUX_6_4); //TMT Analog GNDS from Primary to Secondary.
	mux_20->open_relay(MUX_5_1); //DVI_11_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_2); //DVI_9_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_3); //DVI_13_GNDS to Secondary GNDS on TB.
	mux_20->open_relay(MUX_5_4); //DVI_21_GNDS to Secondary GNDS on TB.
	wait.delay_10_us(250);

	// VcontBPP_cap based on Inno-VI (2uF on BinnoTB)
	// Continuity check for ground connection of BPP pin capacitor.
	// Force 100uA to BPP.  If BPP capacitor ground is NOT connected, BPP voltage will 
	// rise up very quickly.  If BPP capacitor ground is connected properly, the BPP 
	// voltage rises up more slowly.  Datalog BPP voltage, 350usec after 100uA forced to BPP.  //
	BPP_dvi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_dvi->set_current(BPP_ch, 100e-6, RANGE_300_UA); // OVI_1_0 //
	BPP_dvi->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE); // OVI_1_0 //
	wait.delay_10_us(150);

	BPP_dvi->set_voltage(BPP_ch, 5, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(200); // 2ms.  Don't change //
	VcontBPP_cap = BPP_dvi->measure();
	BPP_dvi->set_voltage(BPP_ch, 0.1, RANGE_10_V); // OVI_1_0, prevent undershoot. //
	BPP_dvi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	wait.delay_10_us(15);
	BPP_dvi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(20);
	VcontBPP_capGNG = 1; // Default is pass //
	if (VcontBPP_cap > 0.9) // Fail //
	{
		g_Error_Flag = -225;
		VcontBPP_capGNG = -99;
	}
	

////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	//Primary Die ID Reading
////////////////	//------------------------------------------------------------------------------------------------------------------
////////////////	//Test conditions:  D = 0, BPP = 5V, wait 150us.  Reading I2C.
////////////////
////////////////	//Drain = 0V
////////////////	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
////////////////	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
////////////////	//BPP = 0V
////////////////	BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
////////////////	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
////////////////
////////////////	////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	//This section is for the primary I2C
////////////////
////////////////	//TS = 0V via pullup resistor. Ready for I2C.
////////////////	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
////////////////	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////////	//UV = 0V via pullup resistor. Ready for I2C.
////////////////	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
////////////////	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////////	//Connect Pullup R to TS and UV pins
////////////////	Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
////////////////	Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
////////////////	//Connect DSM CLK & Data to primary pins: TS & UV
////////////////	Close_relay(K1_DSM_TB);	
////////////////	Close_relay(K3_DSM_TB);
////////////////	Open_relay(K2_DSM_TB);
////////////////	Open_relay(K4_DSM_TB);
////////////////	delay(5);
////////////////	////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////
////////////////float vpullup_P=3.3;	//5.0V does not work
////////////////
////////////////
////////////////			DSM_init(DSM_CONTEXT); //only call at start of lot
////////////////			DSM_version(); //1.5
////////////////			DSM_firmware(DSM_CONTEXT); //1.5
////////////////			//DSM_set_vector_clock_freq(DSM_CONTEXT, 1200);//Freq in kHZ
////////////////			DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);
////////////////			DSM_set_drv_comp(DSM_CONTEXT,DRV_COMP_ALL,	2.5); 
////////////////			DSM_set_high_level(DSM_CONTEXT,		ALL_CH, 5);	//DOUT high levels						     
////////////////			DSM_set_low_level(DSM_CONTEXT,		ALL_CH, 0);
////////////////			DSM_set_voltage_ref(DSM_CONTEXT,	ALL_CH, 2.0);
////////////////			DSM_set_voltage_I2C(DSM_CONTEXT,			vpullup_P);
////////////////			DSM_enable_outputs(DSM_CONTEXT, NONE_CH);       //Disable outputs
////////////////			DSM_enable_open_drain(DSM_CONTEXT, NONE_CH);    //Disable Open Drain
////////////////			DSM_set_no_delay(DSM_CONTEXT);            //Set 0 second delay	
////////////////
////////////////pulse.do_pulse();
////////////////
////////////////
////////////////	//BPP to 5.0V first.
////////////////	float j = 0.0;
////////////////	while(j<=vpullup_P)
////////////////	{
////////////////		BPP_dvi->set_voltage(BPP_ch, j, VOLT_10_RANGE); // DVI_11_1
////////////////		if(j >=vpullup_P)
////////////////		{
////////////////		TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_10_RANGE); // OVI_3_0
////////////////		UV_dvi->set_voltage(UV_ch,		vpullup_P, VOLT_10_RANGE); // DVI_21_1
////////////////		}
////////////////		j=j+1;
////////////////	}
////////////////	BPP_dvi->set_voltage(BPP_ch, 5, VOLT_10_RANGE); // DVI_11_1
////////////////	wait.delay_10_us(10);
////////////////
////////////////	//Set pullup voltage at TS @ UV pins.
////////////////	TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_10_RANGE); // OVI_3_0
////////////////
////////////////	//UV = 0V via pullup resistor. Ready for I2C.
////////////////	UV_dvi->set_voltage(UV_ch, vpullup_P, VOLT_10_RANGE); // DVI_21_1
////////////////	wait.delay_10_us(5);
////////////////
////////////////
////////////////	int	DSM_context = 0x00;
////////////////	uint16_t address = 0x00;
////////////////	//uint16_t address = 0x00;
////////////////	uint8_t num_read_bytes = 2;
////////////////	uint8_t readDataBuffer[20];
////////////////	uint8_t writeDataBuffer[20];
////////////////	int i = 0;
////////////////
////////////////	for(i=0;i<20;i++)
////////////////	{
////////////////		readDataBuffer[i] = 0x00;
////////////////		writeDataBuffer[i] = 0x00;
////////////////	}
////////////////
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// Read Primary Die ID  *START
////////////////	//------------------------------
////////////////	if(1)
////////////////	{
////////////////		DSM_I2C_Read(0x00);	//Read Die ID 
////////////////	}
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// Read Primary Die ID  *END
////////////////	//------------------------------
////////////////
////////////////	float	vD_set=0, 
////////////////			vDrain_Erase_th=0, 
////////////////			vDrain_Write_th=0, 
////////////////			vVpin=0;
////////////////
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// ERASE EEprom Primary *START
////////////////	//------------------------------
////////////////	int Primary_Erase = 0;
////////////////	int Primary_Burn  = 0;
////////////////	if(Primary_Erase)
////////////////	{
////////////////		EEPROM_ERASE_P(g_vDrain_Erase_th_P);
////////////////
////////////////////		/* Refer to TestPlan from Design "EEPROMWriteErase"
////////////////////
////////////////////			ERASE Primary EEprom Procedure:
////////////////////			----------------------------------------------------------------------------------------------------------------------
////////////////////			1.  Start up I2C: Drain(0V) BPP(5V)
////////////////////			2.  Analog Test Mode Enable					--> 0x00 0x40 write 0x02
////////////////////			3.  Set EE comparator voltage on CFG14		--> 0x00 0x44 write 0x00 0xC0	(for ERASE)
////////////////////			4.  Observe EE comparator on Vpin			--> 0x00 0x46 write 0x44 0xF8
////////////////////			5.  Write EEprom Erase command				--> 0x00 0x5C write 0x03		(for ERASE)
////////////////////			6.  release Vpin(SDA) for observation		--> 0x00 0x4E write 0x01
////////////////////			7.  set vBPP=7V, vDrain > 24V for Erase.  Ramp vDrain > 24V until Vpin go from Low to High.  Set Drain(0V) BPP(5V)
////////////////////			8.  regain I2C control by taking TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
////////////////////			9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
////////////////////		*/
////////////////////		
////////////////////		Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
////////////////////		DSM_I2C_Write('w', 0x44, 0xC000);	//3.  write CFG14 (ANA_CTRL0) enable EE comparator erase voltage
////////////////////		DSM_I2C_Write('w', 0x46, 0xF844);	//4.  write to ANA_CTRL0 to enable CFGs for VPIN observe, select EE comparator signal, and set I2C password
////////////////////		DSM_I2C_Write('b', 0x5C, 0x03);	//5.  Write EEprom Erase command			
////////////////////		DSM_I2C_Write('b', 0x4E, 0x01);	//6.  release Vpin(SDA) for observation	--> 0x00 0x4E write 0x01
////////////////////			//TEST to observe Vpin here (cx observed Vpin drop to 1V at ATE.  drop to <0.5V at Bench)
////////////////////
////////////////////		//////7. set vBPP=7V, vDrain > 24V for Erase.  Ramp vDrain > 24V until Vpin go from Low to High.  Set Drain(0V) BPP(5V)
////////////////////			BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
////////////////////			BPP_dvi->set_voltage(BPP_ch, 7.0, VOLT_10_RANGE); 
////////////////////			wait.delay_10_us(10);
////////////////////			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////////////////////			D_dvi->set_voltage(D_ch, 22.0, VOLT_50_RANGE); 
////////////////////			wait.delay_10_us(10);
////////////////////
////////////////////			UV_dvi->set_current(UV_ch, 1e-9, RANGE_300_UA);	//set really low current for Vmeas
////////////////////			UV_dvi->set_voltage(UV_ch, vpullup_P, VOLT_5_RANGE); 
////////////////////			UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_VOLTAGE);
////////////////////			wait.delay_10_us(20);
////////////////////
////////////////////			vD_set	= 22;
////////////////////			vVpin	= 0;
////////////////////			while (vD_set < 28)
////////////////////			{
////////////////////				vD_set += 0.1;
////////////////////				D_dvi->set_voltage(D_ch, vD_set, VOLT_50_RANGE); 
////////////////////				wait.delay_10_us(10);
////////////////////				vVpin = UV_dvi->measure_average(5);
//////////////////////				if(vVpin > 1.5) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V with Vpullup_P=3.3V)
////////////////////				if(vVpin > 2.0) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V with Vpullup_P=3.3V)
////////////////////				{
////////////////////					vDrain_Erase_th = vD_set+1;  //cx observed that with Vpullup_P = 4.0V, it does not work.
////////////////////					D_dvi->set_voltage(D_ch, vDrain_Erase_th, VOLT_50_RANGE); 
////////////////////					delay(5);
////////////////////					break;                       //HL added 1V to the vDrain_Erase voltage.
////////////////////				}
////////////////////			}
////////////////////			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); 
////////////////////			wait.delay_10_us(10);
////////////////////			BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
////////////////////			wait.delay_10_us(10);
////////////////////
////////////////////			//Disable DSM I2C (Any I2C write command will bring back I2C)
////////////////////			DSM_set_I2C_timeout(0, 1);
////////////////////			DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
////////////////////
////////////////////		//8.  regain I2C control by taking TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
////////////////////			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE); 
////////////////////			delay(1);
////////////////////			TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_5_RANGE); 
////////////////////			wait.delay_10_us(10);
////////////////////			UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
////////////////////			wait.delay_10_us(10);
////////////////////
////////////////////
////////////////////		//9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
////////////////////		DSM_I2C_Write('b', 0x5C, 0x00);	//Vpin stays low until the "READ EEPROM" command issue.  I2C regain control
////////////////////
////////////////////		//BPP cycle has to happen in order for ERASE to reflect
////////////////////		BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 
////////////////////		delay(1);
////////////////////		BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
////////////////////		delay(1);
////////////////
////////////////	}
////////////////	//------------------------------
////////////////	// ERASE EEprom Primary  *END
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////
////////////////
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// WRITE/Burn EEprom Primary *START
////////////////	//---------------------------------
////////////////	if(Primary_Burn)
////////////////	{
////////////////		/* Refer to TestPlan from Design "EEPROMWriteErase"
////////////////
////////////////			WRITE Procedure:
////////////////			----------------------------------------------------------------------------------------------------------------------
////////////////			1. Start up I2C: Drain(0V) BPP(5V)
////////////////			2. Analog Test Mode Enable					--> 0x00 0x40 write 0x02
////////////////			3. Set EE comparator voltage on CFG14		--> 0x00 0x44 write 0x00 0x40	(for WRITE)
////////////////
//////////////////			4.  Observe EE comparator on Vpin			--> 0x00 0x46 write 0x44 0xF8
//////////////////			5.  Write EEprom Write command				--> 0x00 0x5C write 0x01		(for WRITE) 
//////////////////			3c.  release Vpin(SDA) for observation		--> 0x00 0x4E write 0x01
//////////////////			3d.  set vBPP=7V, vDrain > 18V for Write.  Ramp vDrain > 18V until Vpin go from Low to High.  Set BPP(5V) Drain(0V)
//////////////////			3e.  regain I2C control by taking TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
////////////////
//////////////////			6.  set CFG14 for 18V						--> 0x00 0x44 write 0x00 0x40
////////////////			7.  issue write command per Reg_Addr (0xE0,2,4,6,8) for data to write into
////////////////														--> 0x00 0xE8 write 0xXX 0xXX
////////////////														--> 0x00 0xE6 write 0xXX 0xXX
////////////////														--> 0x00 0xE4 write 0xXX 0xXX
////////////////														--> 0x00 0xE2 write 0xXX 0xXX
////////////////														--> 0x00 0xE0 write 0xXX 0xXX
////////////////			8.	write "WRITE EEPROM"					--> 0x00 0x5C write 0x01
////////////////			9.  release Vpin(SDA) for observation		--> 0x00 0x4E write 0x01
////////////////			10. set vBPP=7V, vDrain > 18V for Erase.  Ramp vDrain > 18V until Vpin go from Low to High.  Set BPP(5V) Drain(0V)
////////////////			11. regain I2C control by bringing TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
//////////////////			3m.  Read EEprom to end Erase				--> 0x00 0x5C read 0x00
////////////////		*/
////////////////
////////////////
////////////////		EEPROM_Write_Enable_P();
////////////////		//////HL-PowerDown.  This is observed from design bench.  
////////////////		//////SDA(Vpin), SCLK(TS) & reset TS & Vpin current.
////////////////		////TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
////////////////		////TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////////		////UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
////////////////		////UV_dvi->set_voltage(UV_ch,		0.0, VOLT_10_RANGE); // DVI_21_1
////////////////		////delay(1);
////////////////
////////////////		////TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_10_RANGE); // OVI_3_0
////////////////		////UV_dvi->set_voltage(UV_ch,		vpullup_P, VOLT_10_RANGE); // DVI_21_1
////////////////		////delay(1);
////////////////		////
////////////////		////Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
////////////////		////DSM_I2C_Write('w', 0x44, 0x4000);	//3.  Set EE comparator voltage on CFG14
////////////////		////DSM_I2C_Write('w', 0x46, 0xF844);	//4.  write to ANA_CTRL0 to enable CFGs for VPIN observe, select EE comparator signal, and set I2C password
////////////////
////////////////		//////HL. Do not execute Write EEProm before sending in the pattern or will reading all 0 instead. 
////////////////		//////DSM_I2C_Write2('b', 0x5C, 0x01);	//8.  write "WRITE EEPROM"  <<===== DONT DO IT!!!!! It won't write.
////////////////
////////////////
////////////////
////////////////		//3i.  issue write command per Reg_Addr (0xE0,2,4,6,8) for data to write into
////////////////			DSM_I2C_Write('w', 0xE0, 0x0000);
////////////////			DSM_I2C_Write('w', 0xE2, 0x0000);
////////////////			DSM_I2C_Write('w', 0xE4, 0x0048); //(VX=00100 + GanBit)
////////////////			DSM_I2C_Write('w', 0xE6, 0x0000);
////////////////			DSM_I2C_Write('w', 0xE8, 0x6000); //(Timer bit 77,78)
////////////////
////////////////
////////////////		EEPROM_BURN_P(g_vDrain_Burn_th_P);
////////////////		////DSM_I2C_Write('b', 0x5C, 0x01);	//8.  write "WRITE EEPROM"
////////////////		////DSM_I2C_Write('b', 0x4E, 0x01);	//9.  release Vpin(SDA) for observation	
////////////////
////////////////		//////10. set vBPP=7V, vDrain > 18V for Erase.  Ramp vDrain > 18V until Vpin go from Low to High.  Set BPP(5V) Drain(0V)
////////////////		////	BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
////////////////		////	BPP_dvi->set_voltage(BPP_ch, 7.0, VOLT_10_RANGE); 
////////////////		////	wait.delay_10_us(10);
////////////////		////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////////////////		////	D_dvi->set_voltage(D_ch, 16.0, VOLT_50_RANGE); 
////////////////		////	wait.delay_10_us(10);
////////////////
////////////////		////	UV_dvi->set_current(UV_ch, 1e-9, RANGE_300_UA);	//set really low current for Vmeas
////////////////		////	UV_dvi->set_voltage(UV_ch, vpullup_P, VOLT_5_RANGE); 
////////////////		////	UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_VOLTAGE);
////////////////		////	wait.delay_10_us(20);
////////////////
////////////////		////	vD_set	= 16;
////////////////		////	vVpin	= 0;
////////////////		////	while (vD_set < 21)
////////////////		////	{
////////////////		////		vD_set += 0.1;
////////////////		////		D_dvi->set_voltage(D_ch, vD_set, VOLT_50_RANGE); 
////////////////		////		wait.delay_10_us(10);
////////////////		////		vVpin = UV_dvi->measure_average(5);
////////////////		////		//if(vVpin > 1.5) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V)
////////////////		////		if(vVpin > 2.0) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V)
////////////////		////		{
////////////////		////			vDrain_Write_th = vD_set+0.2;
////////////////		////			D_dvi->set_voltage(D_ch, vDrain_Write_th, VOLT_50_RANGE);
////////////////		////			delay(5);
////////////////		////			break;
////////////////		////		}
////////////////		////	}
////////////////
////////////////		////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); 
////////////////		////	wait.delay_10_us(10);
////////////////		////	BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
////////////////		////	wait.delay_10_us(10);
////////////////
////////////////		////	//Disable DSM I2C (Any I2C write command will bring back I2C)
////////////////		////	DSM_set_I2C_timeout(0, 1);
////////////////		////	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
////////////////
////////////////		//////11. regain I2C control by bringing TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
////////////////		////	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE); 
////////////////		////	delay(1);
////////////////		////	TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_5_RANGE); 
////////////////		////	wait.delay_10_us(10);
////////////////		////	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
////////////////		////	wait.delay_10_us(10);
////////////////
////////////////
////////////////		//////9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
////////////////		//////    HL needed.  Or the 1st readback is invalid.
////////////////		////DSM_I2C_Write('b', 0x5C, 0x00);	//Vpin stays low until the "READ EEPROM" command issue.  I2C regain control
////////////////
////////////////			
////////////////
////////////////	}
////////////////	//---------------------------------
////////////////	// WRITE/Burn EEprom Primary  *END
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////
////////////////
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// Read EEprom Primary *START
////////////////	//------------------------------
////////////////	if(1)
////////////////	{
////////////////		EEPROM_Read_Enable_P();
////////////////		////Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
////////////////		////DSM_I2C_Write('w', 0x44, 0x4000);	//3.  Set EE comparator voltage on CFG14
////////////////
////////////////		////DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
////////////////		g_Debug = 1;
////////////////		DSM_I2C_Read(0xC4);
////////////////		DSM_I2C_Read(0xC8);		//Read back data of Register addr 0xE8 from 0xC8 register address through READ_ADDR 0x00
////////////////
////////////////		g_Debug = 0;
////////////////		//This is an experiment section to try readback with addresses of 0x1c, 0x1c and 0x1d for primary per design.
////////////////		//DSM_I2C_Pri_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
////////////////		//DSM_I2C_Pri_Read(0xC0);		//Read back data of Register addr 0xE0 from 0xC0 register address through READ_ADDR 0x00
////////////////		//DSM_I2C_Pri_Read(0xC2);		//Read back data of Register addr 0xE2 from 0xC2 register address through READ_ADDR 0x00
////////////////		//DSM_I2C_Pri_Read(0xC4);		//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
////////////////		//DSM_I2C_Pri_Read(0xC6);		//Read back data of Register addr 0xE6 from 0xC6 register address through READ_ADDR 0x00
////////////////
////////////////	}
////////////////	//------------------------------
////////////////	// Read EEprom Primary *END
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////
////////////////
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	// Program GaN bit Primary *START
////////////////	//------------------------------
////////////////	if(1)
////////////////	{
////////////////		////2. Shift in TRIM pattern
////////////////		//DSM_I2C_Write2('w', 0xE4, 0x0008);
////////////////
////////////////		//DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
////////////////		//DSM_I2C_Read(0xC4);		//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
////////////////
////////////////	}
////////////////	//------------------------------
////////////////	// Program GaN bit Primary *END
////////////////	//-----------------------------------------------------------------------------------------------------------------
////////////////	
////////////////	//Continue I2C from here.
////////////////	//Write password.
////////////////
////////////////
////////////////
////////////////
////////////////	//Power down.
////////////////
////////////////	//SDA = 3.3V via pullup resistor. Ready for I2C.
////////////////	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////////
////////////////	//SCL = 3.3V via pullup resistor. Ready for I2C.
////////////////	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////////	delay(5);
////////////////	dvi_9->set_current(DVI_CHANNEL_1, 30e-3, RANGE_300_MA);
////////////////	dvi_9->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE); // DVI_11_1
////////////////	delay(10);
////////////////
////////////////	Open_relay(K2_DSM_TB);
////////////////	Open_relay(K4_DSM_TB);
////////////////	delay(5);
////////////////
////////////////	//Set pullup voltage at TS @ UV pins.
////////////////	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////////	//UV = 0V via pullup resistor. Ready for I2C.
////////////////	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////////	wait.delay_10_us(10);
////////////////
////////////////	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
////////////////	wait.delay_10_us(100);
////////////////
////////////////	//Connect Pullup R to TS pin.
////////////////	Open_relay(K1_TS_RB);
////////////////
////////////////	//Connect Pullup R to UV pin.
////////////////	Open_relay(K1_UV_RB);
////////////////
////////////////	//Disconnect DSM from Primary.
////////////////	mux_14->open_relay(MUX_1_1);	//Primary disconnect from DSM
////////////////	mux_14->open_relay(MUX_1_3);	//Primary disconnect from DSM
////////////////	delay(2);
////////////////
////////////////	//Secondary I2C to ready Secondary Die ID.
////////////////	//Disconnect DVI_13 from HBP.
////////////////	dvi_13->disconnect(CONN_FORCE0);
//////////////////	dvi_13->disconnect(CONN_SENSE0);
////////////////	delay(5);
////////////////
////////////////	//SDA & SCL set to 0V
////////////////	//SDA = 0V via pullup resistor. Ready for I2C.
////////////////	SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
////////////////	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////////
////////////////	//SCL = 0V via pullup resistor. Ready for I2C.
////////////////	SCL_ovi3->set_current(SCL_ch, 10e-3, RANGE_30_MA);
////////////////	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////////





////////////	//-------------------------------------------------------------------------------------
////////////	//---------- Secondary EEprom 'Read ID', 'Erase EEprom', 'Trim/Burn EEprom' -----------
////////////	//-------------------------------------------------------------------------------------
////////////	/*
////////////		Erase EEProm for Secondary
////////////		1.	vFB = 1.25V
////////////		2.	VR = 15V
////////////		3.	Test Mode Enable with Drivers_en, Dsbl_FBshrt, ana_EN, Core_En, Comp out on HSG
////////////			a.	0x00 0x5E write 0x16 0x20
////////////			b.	0x00 0x5E write 0x34 0x12
////////////			c.	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt
////////////				i.	0x00 0x62 write 0x88 0x00
////////////			d.	ZTMC_ana_EN and Core_en
////////////				i.	0x00 0x40 write 0x06 0x00
////////////			e.	ZVtrim_comp (Comp out on HSG)
////////////				i.	0x00 0x46 write 0x00 0xB8
////////////				ii.	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
////////////		4.	Erase EEprom
////////////			a.	0x00 0x5C write 0x03
////////////			b.	ZTMC_ana_vprog_EN and ZTMC_ana_Vprog_2
////////////				i.	0x00 0x44 write 0x07 0x00
////////////			c.	Raise VR pin voltage >24V until HSG pin toggles to complete Erase (DC voltage could determine toggle or not)
////////////			d.	Stop/End Erase EEprom
////////////				i.	 0x00 0x5C write 0x00
////////////				ii.	 VR set to 15V 
////////////				iii. 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
////////////
////////////		Trim/Burn EEprom for Secondary
////////////		1.	vFB = 1.25V
////////////		2.	VR = 15V
////////////		3.	Test Mode Enable with Drivers_en, Dsbl_FBshrt, ana_EN, Core_En, Comp out on HSG
////////////			a.	0x00 0x5E write 0x16 0x20
////////////			b.	0x00 0x5E write 0x34 0x12
////////////			c.	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt
////////////				i.	0x00 0x62 write 0x88 0x00
////////////			d.	ZTMC_ana_EN and Core_en
////////////				i.	0x00 0x40 write 0x06 0x00
////////////			e.	ZVtrim_comp (Comp out on HSG)
////////////				i.	0x00 0x46 write 0x00 0xB8
////////////				ii.	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
////////////		4.	Program any trim code to EEprom register
////////////			a.	E0 write 	E0 ??D[15:0]
////////////			b.	E2 write 	E0 ??D[31:16]
////////////			c.	E4 write 	E0 ??D[17:32]
////////////			d.	E6 write 	E0 ??D[63:48]
////////////			e.	E8 write 	E0 ??D[79:64]
////////////		5.	Burn to EEprom Cell
////////////			a.	Write whats programmed to the EEprom register to EEprom Cell.
////////////				i.	0x00 0x5C write 0x01
////////////			b.	ZTMC_ana_Vprog_En and ZTMC_trim_EN_vDDA
////////////				i.	0x00 0x44 write 0x05 0x00
////////////			c.	Raise VR > 18V until HSG is toggling to burn programmed trimcodes to EEprom cell.  (DC voltage to determine switching or not)
////////////
////////////		Pins involved for Secondary EEprom:
////////////			FB, BPS, VR, HSG, SDA(SET), SCL(DIM)
////////////
////////////		What to expect with VR set to 15V
////////////			BPS regulated to 3.3V internally
////////////			HSG regulated to 11.5V internally
////////////	*/
////////////
////////////	//Disconnect DSM from Primary.
////////////	mux_14->open_relay(MUX_1_1);
////////////	mux_14->open_relay(MUX_1_3);
////////////	delay(1);
////////////
////////////	//Secondary I2C to ready Secondary Die ID.
////////////	//Disconnect DVI_13 from HBP.
////////////	dvi_13->disconnect(CONN_FORCE0);
//////////////	dvi_13->disconnect(CONN_SENSE0);
////////////	delay(5);
////////////
////////////	//SDA & SCL set to 0V
////////////	//SDA = 0V via pullup resistor. Ready for I2C.
////////////	SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
////////////	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////
////////////	//SCL = 0V via pullup resistor. Ready for I2C.
////////////	SCL_ovi3->set_current(SCL_ch, 10e-3, RANGE_30_MA);
////////////	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////
////////////	//Connect DSM CLK & Data to Secondary pins: SDA & SCL
////////////	mux_14->close_relay(MUX_1_2);	//SDA	K2_DSM
////////////	mux_14->close_relay(MUX_1_4);	//SCL	K4_DSM
////////////	delay(5);
////////////
////////////	//1.	vFB = 1.25V
////////////	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
////////////	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
////////////	delay(1);
////////////
////////////	//2.	VR = 15V (20V from Hang)
////////////	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	//Require >30mA else VR -> 10V, droop, then start rising with weird ramps
////////////	VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
////////////	delay(10);
////////////
////////////	//Need to close K1_SDA.  Manually short due to SPI relay driver issues.
////////////
////////////	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
////////////	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
////////////	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); // DVI_21_1
////////////	delay(5);
////////////	
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////	// Read Secondary Die ID  *START
////////////	//------------------------------
////////////	if(1)
////////////	{
////////////		DSM_I2C_Read(0x00);	//Read Die ID
////////////	}
////////////	//------------------------------
////////////	// Read Secondary Die ID  *END
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////
////////////
////////////
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////	// TestMode Secondary *START
////////////	//------------------------------
////////////	if(1)
////////////	{
////////////		//3a.	0x00 0x5E write 0x16 0x20
////////////		DSM_I2C_Write('w', 0x5E, 0x2016);	
////////////
////////////		//3b.	0x00 0x5E write 0x34 0x12
////////////		DSM_I2C_Write('w', 0x5E, 0x1234);	
////////////
////////////			//////For TEST only..  Manually raise vFB above 2.5V or 3V here to observe HBP will go low and then lower to 1.25V for HSG to go High
////////////			//////Below to to make sure the FB controlling HBP is working properly before Disabling it.
////////////			////if(1)
////////////			////{
////////////			////	FB_ovi3->set_voltage(FB_ch, 2.00, VOLT_5_RANGE); // DVI_11_0
////////////			////	delay(1);
////////////			////	FB_ovi3->set_voltage(FB_ch, 2.25, VOLT_5_RANGE); // DVI_11_0
////////////			////	delay(1);
////////////			////	FB_ovi3->set_voltage(FB_ch, 2.50, VOLT_5_RANGE); // DVI_11_0
////////////			////	delay(1);
////////////			////	FB_ovi3->set_voltage(FB_ch, 2.75, VOLT_5_RANGE); // DVI_11_0
////////////			////	delay(1);
////////////			////	FB_ovi3->set_voltage(FB_ch, 3.00, VOLT_5_RANGE); // DVI_11_0	//1uF on HBP.  The drop is slow if it's only 3ms.  Manual observe drop to ~1.7V
////////////			////	delay(3);
////////////			////	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
////////////			////	delay(1);
////////////			////}
////////////	}
////////////	//------------------------------
////////////	// TestMode Secondary *END
////////////	//----------------------------------------------------------------------------------------------------------------
////////////int Secondary_Erase_Trim = 0;
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////	// Erase EEProm for Secondary *START
////////////	//-----------------------------------
////////////	float vVR_set=20, vHSG=0;
////////////	float vVR_Erase_th=0, vVR_Burn_th=0;
////////////	if(Secondary_Erase_Trim)
////////////	{
////////////		//3c.	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
////////////		//											  (This Test Mode disable 
////////////		//	i.	0x00 0x62 write 0x88 0x00
////////////		DSM_I2C_Write('w', 0x62, 0x0088);
////////////
////////////		//3d.	ZTMC_ana_EN and Core_en
////////////		//	i.	0x00 0x40 write 0x06 0x00
////////////		DSM_I2C_Write('w', 0x40, 0x0006);
////////////
////////////		//3e.	ZVtrim_comp (Comp out on HSG)
////////////		//	i.	0x00 0x46 write 0x00 0xB8
////////////		//	ii.	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
////////////		DSM_I2C_Write('w', 0x46, 0xB800);
////////////
////////////		//4. Erase EEprom
////////////		//4a.	0x00 0x5C write 0x03
////////////		DSM_I2C_Write('b', 0x5C, 0x03);
////////////
////////////		//4b.	ZTMC_ana_vprog_EN and ZTMC_ana_Vprog_2
////////////		//	i.	0x00 0x44 write 0x07 0x00
////////////		DSM_I2C_Write('w', 0x44, 0x0007);
////////////
////////////		//4c.	Raise VR pin voltage >24V until HSG pin toggles to complete Erase (DC voltage could determine toggle or not)
////////////		VR_dvi->set_current(VR_ch, 30e-3, RANGE_300_MA);
////////////		VR_dvi->set_voltage(VR_ch, 20.0, VOLT_50_RANGE); // DVI_11_1
////////////		delay(1);
////////////		HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_VOLTAGE, AUTORANGE);
////////////		i=0;
////////////		while (vVR_set < 28)
////////////		{
////////////			vVR_set = vVR_set + i*0.2;
////////////			VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
////////////			wait.delay_10_us(10);
////////////			vHSG = HSG_ovi->measure_average(5);
////////////			if(vHSG > 2) //exit while loop
////////////			{
////////////				vVR_Erase_th = vVR_set+i*0.2;
////////////				break;
////////////			}
////////////			i++;
////////////		}
////////////
////////////		//4d.	Stop/End Erase EEprom
////////////		End_EEprom_Erase_Secondary();
////////////		
////////////		
////////////		////DSM_I2C_Write2('b', 0x5C, 0x00);					//	i.	 0x00 0x5C write 0x00
////////////		////VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE);	//	ii.	 VR set to 15V (optional)
////////////		////delay(5);
////////////		////DSM_I2C_Write2('w', 0x44, 0x0000);					//	iii. 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
////////////
////////////	}
////////////	//---------------------------------
////////////	// Erase EEProm for Secondary *END
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////
////////////
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////	// Trim/Burn EEprom for Secondary *START
////////////	//---------------------------------------
////////////	if(Secondary_Erase_Trim)
////////////	{
////////////		uint16_t D15_0, D31_16, D47_32, D63_48, D79_64;
////////////		D15_0  = 0x0000;
////////////		D31_16 = 0x001C; //Trim Bit 18,19 & 20 per design request. Upper Byte = 0x00, Lower Byte 0x1C
////////////		D47_32 = 0x0000;
////////////		D63_48 = 0x0000;
////////////		D79_64 = 0x0000;
////////////		//Since the previous I2C commands were just ERASE, we can continue without going through steps 1 to 3 like above.
////////////
////////////		//4a to 4e.  Program any trim code to EEprom registers
////////////			DSM_I2C_Write('w', 0xE0, D15_0);	//4a. E0 <--> D[15:0]
////////////			DSM_I2C_Write('w', 0xE2, D31_16);	//4b. E2 <--> D[31:16]
////////////			DSM_I2C_Write('w', 0xE4, D47_32);	//4c. E4 <--> D[47:32]
////////////			DSM_I2C_Write('w', 0xE6, D63_48);	//4d. E6 <--> D[63:48]
////////////			DSM_I2C_Write('w', 0xE8, D79_64);	//4e. E8 <--> D[79:64]
////////////		//5a. Write whats programmed to the EEprom register to EEprom Cell.	(0x00 0x5C write 0x01)
////////////			DSM_I2C_Write('b', 0x5C, 0x01);
////////////		//5b. ZTMC_ana_Vprog_En and ZTMC_trim_EN_vDDA	(0x00 0x44 write 0x05 0x00)
////////////			DSM_I2C_Write('w', 0x44, 0x0005);
////////////		//5c. Raise VR > 18V until HSG is toggling to burn programmed trimcodes to EEprom cell.  
////////////		//											(DC voltage to determine switching or not) 
////////////			VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
////////////			delay(1);
////////////			HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_VOLTAGE, AUTORANGE);
////////////			vVR_set=15;
////////////			vHSG=0;
////////////			i=0;
////////////			while (vVR_set < 21)
////////////			{
////////////				vVR_set = vVR_set + i*0.2;
////////////				VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
////////////				wait.delay_10_us(10);
////////////				vHSG = HSG_ovi->measure_average(5);
////////////				if(vHSG > 2) //exit while loop
////////////				{
////////////					vVR_Burn_th = vVR_set+i*0.2;
////////////					break;
////////////				}
////////////				i++;
////////////			}
////////////		//5d. Stop/End Burn EEprom
////////////			//i.  0x00 0x5C write 0x00
////////////			DSM_I2C_Write('b', 0x5C, 0x00);
////////////			//ii. 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
////////////			DSM_I2C_Write('w', 0x44, 0x0000);
////////////	}
////////////	//-------------------------------------
////////////	// Trim/Burn EEprom for Secondary *END
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////
////////////
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////	// Read Back EEprom for Secondary *START
////////////	//---------------------------------------
////////////	if(1)
////////////	{
////////////		DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
////////////		//DSM_I2C_Read(0xC0);	//Read back data of Register addr 0xE0 from 0xC0 register address through READ_ADDR 0x00
////////////		g_Debug = 1;
////////////		DSM_I2C_Read(0xC2);	//Read back data of Register addr 0xE2 from 0xC2 register address through READ_ADDR 0x00
////////////		g_Debug = 0;
////////////		//DSM_I2C_Read(0xC4);	//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
////////////		//DSM_I2C_Read(0xC6);	//Read back data of Register addr 0xE6 from 0xC6 register address through READ_ADDR 0x00
////////////		//DSM_I2C_Read(0xC8);	//Read back data of Register addr 0xE8 from 0xC8 register address through READ_ADDR 0x00
////////////		//DSM_I2C_Pri_Read(0xC2);
////////////	}
////////////	//-------------------------------------
////////////	// Read Back EEprom for Secondary *END
////////////	//-----------------------------------------------------------------------------------------------------------------
////////////
////////////
////////////	//Power Down from Secondary use
////////////	//SDA,SCL = 0.0V via pullup resistor. Ready for I2C.
////////////	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
////////////	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////////////	//VR=0V
////////////	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); // DVI_11_1
////////////	//FB=0V
////////////	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); // DVI_11_0
////////////	delay(1);
////////////	//Disconnect DSM CLK & Data from Secondary pins: SDA & SCL
////////////	Open_relay(K2_DSM_TB);	//SDA	K2_DSM
////////////	Open_relay(K4_DSM_TB);	//SCL	K4_DSM
////////////	delay(5);


// Datalog //
	//-------------------------------------------------------------------------------------
	//Drain
	UpperLimit = (func.dlog->tests[A_VcontD].f_max_limit_val[0]); // Get upper limit //
	if (VcontD > UpperLimit)
		PiDatalog(func, A_VcontD, VcontD, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontD, VcontD, 15, POWER_UNIT);


	UpperLimit = (func.dlog->tests[A_VcontD_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontD_1mA > UpperLimit)
		PiDatalog(func, A_VcontD_1mA, VcontD_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontD_1mA, VcontD_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontD_Rat, VcontD_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontD].f_max_limit_val[0]); // Get upper limit //
	if (IcontD > UpperLimit)
		PiDatalog(func, A_IcontD, IcontD, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontD, IcontD, 15, POWER_MILLI);	

	//-------------------------------------------------------------------------------------
	//BPP

	UpperLimit = (func.dlog->tests[A_VcontBPP].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPP > UpperLimit)
		PiDatalog(func, A_VcontBPP, VcontBPP, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPP, VcontBPP, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontBPP_p, VcontBPP_p, 15,	POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontBPP_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPP_1mA > UpperLimit)
		PiDatalog(func, A_VcontBPP_1mA, VcontBPP_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPP_1mA, VcontBPP_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontBPP_Rat, VcontBPP_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontBPP].f_max_limit_val[0]); // Get upper limit //
	if (IcontBPP > UpperLimit)
		PiDatalog(func, A_IcontBPP, IcontBPP, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontBPP, IcontBPP, 15, POWER_MILLI);	

	//-------------------------------------------------------------------------------------
	//UV


	UpperLimit = (func.dlog->tests[A_VcontUV].f_max_limit_val[0]); // Get upper limit //
	if (VcontUV > UpperLimit)
		PiDatalog(func, A_VcontUV,	VcontUV, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontUV,	VcontUV, 15, POWER_UNIT);
	

	UpperLimit = (func.dlog->tests[A_VcontUV_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontUV_1mA > UpperLimit)
		PiDatalog(func, A_VcontUV_1mA, VcontUV_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontUV_1mA, VcontUV_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontUV_Rat, VcontUV_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontUV].f_max_limit_val[0]); // Get upper limit //
	if (IcontUV > UpperLimit)
		PiDatalog(func, A_IcontUV,	IcontUV, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontUV,	IcontUV, 15, POWER_MILLI);

//-------------------------------------------------------------------------------------
	//TS

	UpperLimit = (func.dlog->tests[A_VcontTS].f_max_limit_val[0]); // Get upper limit //
	if (VcontTS > UpperLimit)
		PiDatalog(func, A_VcontTS, VcontTS, 29,	POWER_UNIT);
	else
		PiDatalog(func, A_VcontTS, VcontTS, 15,	POWER_UNIT);
	
	//PiDatalog(func, A_VcontSR_p, VcontSR_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontTS_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontTS_1mA > UpperLimit)
		PiDatalog(func, A_VcontTS_1mA, VcontTS_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontTS_1mA, VcontTS_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontTS_Rat, VcontTS_Rat, 15, POWER_UNIT);


	UpperLimit = (func.dlog->tests[A_IcontTS].f_max_limit_val[0]); // Get upper limit //
	if (IcontTS > UpperLimit)
		PiDatalog(func, A_IcontTS, IcontTS, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontTS, IcontTS, 15,	POWER_MILLI);

 
	//------------------------------------------------------------------------------------------------------
	//FW
	//--------------------------------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontFW].f_max_limit_val[0]); // Get upper limit //
	if (VcontFW > UpperLimit)
		PiDatalog(func, A_VcontFW, VcontFW, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFW, VcontFW, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontFW_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontFW_1mA > UpperLimit)
		PiDatalog(func, A_VcontFW_1mA, VcontFW_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFW_1mA, VcontFW_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontFW_Rat, VcontFW_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontFW].f_max_limit_val[0]); // Get upper limit //
	if (IcontFW > UpperLimit)
		PiDatalog(func, A_IcontFW, IcontFW, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontFW, IcontFW, 15,	POWER_MILLI);


	//------------------------------------------------------------------------------------------------------
	//VR
	//--------------------------------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontVR].f_max_limit_val[0]); // Get upper limit //
	if (VcontFW > UpperLimit)
		PiDatalog(func, A_VcontVR, VcontVR, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontVR, VcontVR, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontVR_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontVR_1mA > UpperLimit)
		PiDatalog(func, A_VcontVR_1mA, VcontVR_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontVR_1mA, VcontVR_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontVR_Rat, VcontVR_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontVR].f_max_limit_val[0]); // Get upper limit //
	if (IcontFW > UpperLimit)
		PiDatalog(func, A_IcontVR, IcontVR, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontVR, IcontVR, 15,	POWER_MILLI);


	//------------------------------------------------------------------------------------------------------
	//HSG
	//--------------------------------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontHSG].f_max_limit_val[0]); // Get upper limit //
	if (VcontHSG > UpperLimit)
		PiDatalog(func, A_VcontHSG, VcontHSG, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontHSG, VcontHSG, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontHSG_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontHSG_1mA > UpperLimit)
		PiDatalog(func, A_VcontHSG_1mA, VcontHSG_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontHSG_1mA, VcontHSG_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontHSG_Rat, VcontHSG_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontHSG].f_max_limit_val[0]); // Get upper limit //
	if (IcontHSG > UpperLimit)
		PiDatalog(func, A_IcontHSG, IcontHSG, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontHSG, IcontHSG, 15,	POWER_MILLI);

	//--------------------------------------------------------------------------------------------------------
	//B
	//--------------------------------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontB].f_max_limit_val[0]); // Get upper limit //
	if (VcontB > UpperLimit)
		PiDatalog(func, A_VcontB, VcontB, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontB, VcontB, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontB_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontB_1mA > UpperLimit)
		PiDatalog(func, A_VcontB_1mA, VcontB_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontB_1mA, VcontB_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontB_Rat, VcontB_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontHSG].f_max_limit_val[0]); // Get upper limit //
	if (IcontB > UpperLimit)
		PiDatalog(func, A_IcontB, IcontB, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontB, IcontB, 15,	POWER_MILLI);

	//-------------------------------------------------------------------------------------
	//HBP
	//-------------------------------------------------------------------------------------

	UpperLimit = (func.dlog->tests[A_VcontHBP].f_max_limit_val[0]); // Get upper limit //
	if (VcontHBP > UpperLimit)
		PiDatalog(func, A_VcontHBP, VcontHBP, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontHBP, VcontHBP, 15, POWER_UNIT);
	

	UpperLimit = (func.dlog->tests[A_VcontHBP_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontHBP_1mA > UpperLimit)
		PiDatalog(func, A_VcontHBP_1mA, VcontHBP_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontHBP_1mA, VcontHBP_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontHBP_Rat, VcontHBP_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontHBP].f_max_limit_val[0]); // Get upper limit //
	if (IcontHBP > UpperLimit)
		PiDatalog(func, A_IcontHBP, IcontHBP, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontHBP, IcontHBP, 15,	POWER_MILLI);

	//------------------------------------------------------------------------------
	//FB
	//------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontFB].f_max_limit_val[0]); // Get upper limit //
	if (VcontFB > UpperLimit)
		PiDatalog(func, A_VcontFB, VcontFB, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFB, VcontFB, 15, POWER_UNIT);
	

	UpperLimit = (func.dlog->tests[A_VcontFB_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontFB_1mA > UpperLimit)
		PiDatalog(func, A_VcontFB_1mA, VcontFB_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFB_1mA, VcontFB_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontFB_Rat, VcontFB_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontFB].f_max_limit_val[0]); // Get upper limit //
	if (IcontFB > UpperLimit)
		PiDatalog(func, A_IcontFB, IcontFB, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontFB, IcontFB, 15, POWER_MILLI);

	//-------------------------------------------------------------------------------------
	//BPS
	//-------------------------------------------------------------------------------------
	UpperLimit = (func.dlog->tests[A_VcontBPS].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPS > UpperLimit)
		PiDatalog(func, A_VcontBPS, VcontBPS, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPS, VcontBPS, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontBPS_p, VcontBPS_p,15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontBPS_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPS_1mA > UpperLimit)
		PiDatalog(func, A_VcontBPS_1mA, VcontBPS_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPS_1mA, VcontBPS_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontBPS_Rat, VcontBPS_Rat,15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontBPS].f_max_limit_val[0]); // Get upper limit //
	if (IcontBPS > UpperLimit)
		PiDatalog(func, A_IcontBPS, IcontBPS, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontBPS, IcontBPS, 15, POWER_MILLI);

	///////////////////////////////////////////////////////////////////////////////////
	// IS /////////////////////////////////////////////////////////////////////////////

		UpperLimit = (func.dlog->tests[A_VcontIS].f_max_limit_val[0]); // Get upper limit //
	if (VcontIS > UpperLimit)
		PiDatalog(func, A_VcontIS, VcontIS, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontIS, VcontIS, 15, POWER_UNIT);
	
	UpperLimit = (func.dlog->tests[A_VcontIS_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontIS_1mA > UpperLimit)
		PiDatalog(func, A_VcontIS_1mA, VcontIS_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontIS_1mA, VcontIS_1mA, 15, POWER_UNIT);

	//need to enable it
	PiDatalog(func, A_VcontIS_Rat, VcontIS_Rat, 15, POWER_UNIT);

		UpperLimit = (func.dlog->tests[A_IcontIS].f_max_limit_val[0]); // Get upper limit //

	if (Icont6mA_IS > UpperLimit)
		PiDatalog(func, A_IcontIS, Icont6mA_IS, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontIS, Icont6mA_IS, 15, POWER_MILLI);

	//-------------------------------------------------------------------------------------
	//SDA
	//-------------------------------------------------------------------------------------
	
	//SDA
	UpperLimit = (func.dlog->tests[A_VcontSDA].f_max_limit_val[0]); // Get upper limit //
	if (VcontSDA > UpperLimit)
		PiDatalog(func, A_VcontSDA, VcontSDA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontSDA, VcontSDA, 15, POWER_UNIT);
		
	UpperLimit = (func.dlog->tests[A_VcontSDA_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontSDA_1mA > UpperLimit)
		PiDatalog(func, A_VcontSDA_1mA, VcontSDA_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontSDA_1mA, VcontSDA_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontSDA_Rat, VcontSDA_Rat, 15, POWER_UNIT);
	
	LowerLimit = (func.dlog->tests[A_IcontSDA].f_min_limit_val[0]); // Get lower limit //
	if (IcontSDA < LowerLimit)
		PiDatalog(func, A_IcontSDA, IcontSDA, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontSDA, IcontSDA, 15, POWER_MILLI);
	

	//-------------------------------------------------------------------------------------
	//SCL
	//-------------------------------------------------------------------------------------
	
	//SCL
	UpperLimit = (func.dlog->tests[A_VcontSCL].f_max_limit_val[0]); // Get upper limit //
	if (VcontSCL > UpperLimit)
		PiDatalog(func, A_VcontSCL, VcontSCL, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontSCL, VcontSCL, 15, POWER_UNIT);
		
	UpperLimit = (func.dlog->tests[A_VcontSCL_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontSCL_1mA > UpperLimit)
		PiDatalog(func, A_VcontSCL_1mA, VcontSCL_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontSCL_1mA, VcontSCL_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_SCL_Rat, VcontSCL_Rat, 15, POWER_UNIT);
	
	LowerLimit = (func.dlog->tests[A_IcontSCL].f_min_limit_val[0]); // Get lower limit //
	if (IcontSDA < LowerLimit)
		PiDatalog(func, A_IcontSCL, IcontSCL, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontSCL, IcontSCL, 15, POWER_MILLI);



	PiDatalog(func, A_GNDRes_Se, g_GNDRes_Se, 15, POWER_MILLI);	
	PiDatalog(func, A_GNDRes_Pri, g_GNDRes_Pri,15, POWER_MILLI);
	PiDatalog(func, A_VcontBPP_cap, VcontBPP_cap, 15, POWER_UNIT);
	PiDatalog(func, A_VcontBPP_capGNG, VcontBPP_capGNG, 15, POWER_UNIT);

	// Check for any failures //
	if (PiGetAnyFailStatus())
	{
		AbortTest = true;
		delay(50);	// Wait 50ms if failing continuity for Handler to respond properly
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Continuity_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Continuity_TT, Continuity_TT, 15, POWER_MILLI);
	}	

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}	
	


/*
	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Connect Relays //
	Close_relay(K2); // Connects Drain to DVI_11_0
	Close_relay(K18); // Connects FW to DVI_11_1
	wait.delay_10_us(200);

	// Vpin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 20.0e-3, RANGE_30_MA);	

	// Vout //
	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_2_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 20.0e-3, RANGE_30_MA);	

	// BPS //
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE); // DVI_9_1
	BPS_dvi->set_current(BPS_ch, 20.0e-3, RANGE_30_MA);	
	
	// Drain //
	D_dvi->set_current(D_ch, -100e-6, RANGE_300_UA);
	D_dvi->set_voltage(D_ch, -2.0, VOLT_2_RANGE); // DVI_11_0
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);

	// BPP //
	BPP_ovi->set_current(BPP_ch, -0.5e-3, RANGE_3_MA); // BPP with 4.7uF
	BPP_ovi->set_voltage(BPP_ch, -2.0, RANGE_2_V);	// OVI_1_0
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE);
	
	// IS pin //
	IS_dvi2k->set_current(IS_ch, -100e-6, RANGE_200_UA);
	IS_dvi2k->set_voltage(IS_ch, -2.0, VOLT_2_RANGE);	// DVI_21_0
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_VOLTAGE);
	
	// 100uA continuity //
	wait.delay_10_us(200);
	VcontD = D_dvi->measure_average(5);
	VcontBPP = BPP_ovi->measure_average(5);
	VcontIS = IS_dvi2k->measure_average(5);

	// 1mA continuity //	
	D_dvi->set_current(D_ch, -1.0e-3, RANGE_3_MA);
	BPP_ovi->set_current(BPP_ch, -1.0e-3, RANGE_3_MA); // BPP with 4.7uF
	IS_dvi2k->set_current(IS_ch, -1.0e-3, RANGE_2_MA);
	wait.delay_10_us(200);
	VcontD_1mA = D_dvi->measure_average(5);
	VcontBPP_1mA = BPP_ovi->measure_average(5);
	VcontIS_1mA = IS_dvi2k->measure_average(5);	// No ESD diode. Expect to read -2V. 

	// Calculate ratio //
	VcontD_Rat = VcontD_1mA  / VcontD;
	VcontBPP_Rat = VcontBPP_1mA / VcontBPP;
	VcontIS_Rat = VcontIS_1mA / VcontIS;

	// FW //
	FW_dvi->set_current(FW_ch, -100e-6,	RANGE_300_UA);
	FW_dvi->set_voltage(FW_ch, -2.0, VOLT_2_RANGE);	// DVI_11_1
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_VOLTAGE);

	// SR //
	SR_dvi2k->set_current(SR_ch, -100e-6, RANGE_200_UA);
	SR_dvi2k->set_voltage(SR_ch, -2.0, VOLT_2_RANGE); // DVI_21_1
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE);

	// FB //
	FB_ovi->set_current(FB_ch, -100e-6, RANGE_300_UA);
	FB_ovi->set_voltage(FB_ch, -2.0, RANGE_2_V); // OVI_1_2
	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE);

	// 100uA continuity //
	wait.delay_10_us(100);
	VcontFW = FW_dvi->measure_average(5);
	VcontSR = SR_dvi2k->measure_average(5);
	VcontFB = FB_ovi->measure_average(5);

	// 1mA continuity //
	FW_dvi->set_current(FW_ch, -1.0e-3, RANGE_3_MA);
	SR_dvi2k->set_current(SR_ch, -1.0e-3, RANGE_2_MA);
	FB_ovi->set_current(FB_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	VcontFW_1mA   = FW_dvi->measure_average(5);
	VcontSR_1mA = SR_dvi2k->measure_average(5);
	VcontFB_1mA  = FB_ovi->measure_average(5);

	// Calculate ratio //
	VcontFW_Rat = VcontFW_1mA / VcontFW;
	VcontSR_Rat = VcontSR_1mA / VcontSR;
	VcontFB_Rat = VcontFB_1mA / VcontFB;

	// Powerdown //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	D_dvi->set_current(D_ch, 20.0e-3, RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_2_V); // OVI_1_0
	BPP_ovi->set_current(BPP_ch, 20.0e-3, RANGE_30_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_21_0
	wait.delay_10_us(8); // Prevent glitch //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA);
	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); // DVI_11_1
	FW_dvi->set_current(FW_ch, 20.0e-3, RANGE_30_MA);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_21_1
	wait.delay_10_us(10); // Prevent glitch //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA);
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V);	// OVI_1_2
	FB_ovi->set_current(FB_ch, 20.0e-3, RANGE_30_MA);

	// Vpin //
	VPIN_ovi->set_current(VPIN_ch, -100e-6, RANGE_300_UA);
	VPIN_ovi->set_voltage(VPIN_ch, -2.0, RANGE_2_V); // OVI_1_1
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_VOLTAGE);

	// Vout //
	VO_dvi->set_current(VO_ch, -100e-6, RANGE_300_UA);
	VO_dvi->set_voltage(VO_ch, -2.0, VOLT_2_RANGE);	// DVI_9_0
	VO_dvi->set_meas_mode(VO_ch, OVI_MEASURE_VOLTAGE);
	
	// 100uA continuity //
	wait.delay_10_us(100);
	VcontUV = VPIN_ovi->measure_average(5);
	VcontVO = VO_dvi->measure_average(5);

	// 1mA continuity //
	VPIN_ovi->set_current(VPIN_ch, -1.0e-3, RANGE_3_MA);
	VO_dvi->set_current(VO_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	VcontUV_1mA = VPIN_ovi->measure_average(5);
	VcontVO_1mA = VO_dvi->measure_average(5);

	// Calculate ratio //
	VcontUV_Rat = VcontUV_1mA / VcontUV;
	VcontVO_Rat = VcontVO_1mA / VcontVO;

	// 100uA continuity //
	BPS_dvi->set_current(BPS_ch, -100e-6, RANGE_300_UA);
	BPS_dvi->set_voltage(BPS_ch, -2.0, VOLT_2_RANGE); // DVI_9_1
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(200);
	VcontBPS = BPS_dvi->measure_average(5);

	// 1mA continuity //
	BPS_dvi->set_current(BPS_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);;
	VcontBPS_1mA = BPS_dvi->measure_average(5);

	// Calculate ratio //
	VcontBPS_Rat = VcontBPS_1mA / VcontBPS;

	// Powerdown //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V); // OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 3.0e-3, RANGE_3_MA);
	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_2_RANGE); // DVI_9_0
	VO_dvi->set_current(VO_ch, 3.0e-3, RANGE_3_MA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE); // DVI_9_1
	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
	
	// Test VB/D, SDA pins. Put to 0V uVCC and SCL pins //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_2_V);	
	uVCC_ovi->set_current(uVCC_ch, 1.0e-3, RANGE_3_MA);
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_2_V);	
	SCL_ovi->set_current(SCL_ch, 1.0e-3, RANGE_3_MA);

	// VBD //
	VBD_dvi->set_current(VBD_ch, -100.0e-6, RANGE_300_UA);
	VBD_dvi->set_voltage(VBD_ch, -2.0, VOLT_2_RANGE);	
	VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);

	Vcont_VBD_low = VBD_dvi->measure_average(5);
	VBD_dvi->set_current(VBD_ch, -1e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	Vcont_VBD_high = VBD_dvi->measure_average(5);
	Vcont_VBD_rat = (Vcont_VBD_high / Vcont_VBD_low);
	
	//SDA
	SDA_ovi->set_current(SDA_ch, -100.0e-6, RANGE_300_UA);
	SDA_ovi->set_voltage(SDA_ch, -2.0, RANGE_2_V);	
	SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);
	Vcont_SDA_low = SDA_ovi->measure_average(5);
	SDA_ovi->set_current(SDA_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	Vcont_SDA_high = SDA_ovi->measure_average(5);
	Vcont_SDA_rat = (Vcont_SDA_high / Vcont_SDA_low);

	// Powerdown //
	//Test uVCC, SCL pins. Put VB/D and SDA pins to 0V.
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_2_RANGE);
	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_2_V);	
	wait.delay_10_us(100);

	// uVCC //
	// 4.7uF cap on uVCC pin. //
	uVCC_ovi->set_current(uVCC_ch, -3.0e-3, RANGE_3_MA);
	uVCC_ovi->set_voltage(uVCC_ch, -2.0, RANGE_2_V);	
	uVCC_ovi->set_meas_mode(uVCC_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);
	uVCC_ovi->set_current(uVCC_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(200);
	Vcont_uVCC_high = uVCC_ovi->measure_average(5);
	uVCC_ovi->set_current(uVCC_ch, -100.0e-6, RANGE_300_UA);
	wait.delay_10_us(600);
	Vcont_uVCC_low = uVCC_ovi->measure_average(5);
	Vcont_uVCC_rat = (Vcont_uVCC_high / Vcont_uVCC_low);
	uVCC_ovi->set_voltage(uVCC_ch, 0, RANGE_2_V);	
	uVCC_ovi->set_current(uVCC_ch, 30.0e-3, RANGE_30_MA);

	//SCL
	SCL_ovi->set_current(SCL_ch, -100.0e-6, RANGE_300_UA);
	SCL_ovi->set_voltage(SCL_ch, -2.0, RANGE_2_V);	
	SCL_ovi->set_meas_mode(SCL_ch, OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(100);
	Vcont_SCL_low = SCL_ovi->measure_average(5);
	SCL_ovi->set_current(SCL_ch, -1.0e-3, RANGE_3_MA);
	wait.delay_10_us(100);
	Vcont_SCL_high = SCL_ovi->measure_average(5);
	Vcont_SCL_rat = (Vcont_SCL_high / Vcont_SCL_low);

	// Powerdown //
	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_2_V);	

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//								Icont test									  //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Setup FW pin Icont test //
	FW_dvi->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(50);
	FW_dvi->set_current(FW_ch, -6.0e-3, RANGE_30_MA);
	FW_dvi->set_voltage(FW_ch, -0.5, VOLT_2_RANGE); // Avoid glitch //
	wait.delay_10_us(15); // Avoid glitch //
	FW_dvi->set_voltage(FW_ch, -1.5, VOLT_2_RANGE);

	// Sink Current to check Force and Sense connectivity
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE);
	D_dvi->set_current(D_ch, 20e-3, RANGE_30_MA); 
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);

	// Sink Current to check Force and Sense connectivity
	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_2_RANGE);
	VO_dvi->set_current(VO_ch, 20e-3, RANGE_30_MA); 
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);

	// Setup BPS pin Icont test //
	BPS_dvi->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(50);
	BPS_dvi->set_current(BPS_ch, -6.0e-3, RANGE_30_MA);		
	BPS_dvi->set_voltage(BPS_ch, -0.5, VOLT_2_RANGE); // Avoid glitch //
	wait.delay_10_us(15); // Avoid glitch //
	BPS_dvi->set_voltage(BPS_ch, -1.5, VOLT_2_RANGE);  
	
	// Setup SR pin Icont test
	SR_dvi2k->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(50);
	SR_dvi2k->set_current(SR_ch, -6.0e-3, RANGE_20_MA);
	SR_dvi2k->set_voltage(SR_ch, -0.5, VOLT_2_RANGE); // Avoid glitch // 
	wait.delay_10_us(15); // Avoid glitch //
	SR_dvi2k->set_voltage(SR_ch, -1.5, VOLT_2_RANGE);  
	
	// Sink Current to check Force and Sense connectivity
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE);
	IS_dvi2k->set_current(IS_ch, 20e-3, RANGE_20_MA); 
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(200);
	D_dvi->close_relay(BUS_SENSE0); // Need to close BUS_SENSE and BUS_FORCE to avoid failing the ICont on the wrong pin
	D_dvi->close_relay(BUS_FORCE0);
	wait.delay_10_us(100);
	IcontFW = D_dvi->measure_average(5); // Check current from FW dvi to D dvi

	D_dvi->open_relay(BUS_SENSE0);
	D_dvi->open_relay(BUS_FORCE0);
	wait.delay_10_us(100);
	IcontBPS = VO_dvi->measure_average(5); // Check current from BPS dvi to VO dvi

	VO_dvi->open_relay(BUS_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);

	// Power down FW, BPS, SR pins and open CONN BUS relays, Leave CHANNEL_SHORT relay close
	FW_dvi->set_voltage(FW_ch, 0.5, VOLT_2_RANGE);
	BPS_dvi->set_voltage(BPS_ch, 0.5, VOLT_2_RANGE); 
	SR_dvi2k->set_voltage(SR_ch, 0.5, VOLT_2_RANGE);
	wait.delay_10_us(15);
	FW_dvi->set_current(FW_ch, 20.0e-3, RANGE_30_MA);		
	BPS_dvi->set_current(BPS_ch, 20.0e-3, RANGE_30_MA);	
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA);	
	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);  

	// Setup D pin Icont test //
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
	D_dvi->set_current(D_ch, -6.0e-3, RANGE_30_MA);	
	D_dvi->set_voltage(D_ch, -0.5, VOLT_2_RANGE); // Avoid glitch // 
	wait.delay_10_us(15); // Avoid glitch //
	D_dvi->set_voltage(D_ch, -1.5, VOLT_2_RANGE);  
	
	// Setup D pin Icont test //
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	VO_dvi->set_current(VO_ch, -6.0e-3, RANGE_30_MA);
	VO_dvi->set_voltage(VO_ch, -0.5, VOLT_2_RANGE); 
	wait.delay_10_us(15); // Avoid glitch //
	VO_dvi->set_voltage(VO_ch, -1.5, VOLT_2_RANGE);  
	
	// Setup D pin Icont test //
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_voltage(IS_ch, -1.5, VOLT_2_RANGE);  
	IS_dvi2k->set_current(IS_ch, -6.0e-3, RANGE_20_MA);	
	wait.delay_10_us(200);
	IcontD = FW_dvi->measure_average(5); // Check current from D dvi  to FW dvi

	// Setup Vout Icont test //
	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);
	wait.delay_10_us(100);
	IcontVO = BPS_dvi->measure_average(5); // Check current from VO dvi to BPS dvi

	// Powerdown //
	BPS_dvi->open_relay(BUS_SENSE1);
	BPS_dvi->open_relay(BUS_FORCE1);
	D_dvi->set_voltage(D_ch, 0, VOLT_2_RANGE);  
	D_dvi->set_current(D_ch, 100e-6, RANGE_300_UA);		
	VO_dvi->set_voltage(VO_ch, 0, VOLT_2_RANGE);  
	VO_dvi->set_current(VO_ch, 100e-6, RANGE_300_UA);	
	IS_dvi2k->set_voltage(IS_ch, 0, VOLT_2_RANGE);  
	IS_dvi2k->set_current(IS_ch, 100e-6, RANGE_200_UA);

	// Check BPP Icont //
	Close_relay(K11);
	Close_relay(K3);	
	wait.delay_10_us(200);

	// Source current
	BPP_DVI->set_current(BPP_ch, -6.0e-3, RANGE_30_MA); 
	wait.delay_10_us(10);
	BPP_DVI->set_voltage(BPP_ch, -1.5, VOLT_2_RANGE);  
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
	wait.delay_10_us(200);

	// Take measurements //
	IcontBPP= FW_dvi->measure_average(5); // Check current from BPP dvi to FW dvi

	// Powerdown //
	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);
	Open_relay(K11);
	Open_relay(K3);			
	BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE);  
	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_2_RANGE);  
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE);  
	wait.delay_10_us(10);
	FW_dvi->open_relay(CHANNEL_SHORT);
	BPS_dvi->open_relay(CHANNEL_SHORT);
	SR_dvi2k->open_relay(CHANNEL_SHORT);

	// Test DVI17_Ch0 on VBD
	Mux20_Open_relay(K36);//Make sure VBD is connected to DVI17_Ch0
	wait.delay_10_us(200);

	// Sink Current to check Force and Sense connectivity
	//dvi_17->set_voltage(1, 0.0, VOLT_2_RANGE);
	//dvi_17->set_current(1, 20e-3, RANGE_30_MA);
	//dvi_17->set_meas_mode(1,DVI_MEASURE_CURRENT);
	//wait.delay_10_us(200);
	//dvi_17->close_relay(BUS_SENSE1);
	//dvi_17->close_relay(BUS_FORCE1);
	dvi_21->set_voltage(1, 0.0, VOLT_2_RANGE);
	dvi_21->set_current(1, 20e-3, RANGE_30_MA);
	dvi_21->set_meas_mode(1,DVI_MEASURE_CURRENT);
	wait.delay_10_us(200);
	dvi_21->close_relay(BUS_SENSE1);
	dvi_21->close_relay(BUS_FORCE1);

	// Close DV17 channel short
	VBD_dvi->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(50);
	VBD_dvi->set_current(VBD_ch, -6.0e-3, RANGE_30_MA);	
	VBD_dvi->set_voltage(VBD_ch, -0.5, VOLT_2_RANGE);  
	wait.delay_10_us(15); // Avoid glitch //
	VBD_dvi->set_voltage(VBD_ch, -1.5, VOLT_2_RANGE);  
	wait.delay_10_us(200);
	//Icont_VBD  = dvi_17->measure_average(5); // Check current
	Icont_VBD  = dvi_21->measure_average(5); // Check current 

	// Powerdown //
	VBD_dvi->set_voltage(VBD_ch, 1.5, VOLT_2_RANGE); // Avoid glitch // 
	//dvi_17->set_voltage(1, 1.5, VOLT_2_RANGE); // Avoid glitch //
	dvi_21->set_voltage(1, 1.5, VOLT_2_RANGE); // Avoid glitch // 
	wait.delay_10_us(10);
	VBD_dvi->open_relay(CHANNEL_SHORT);
	//dvi_17->open_relay(BUS_SENSE1);
	//dvi_17->open_relay(BUS_FORCE1);
	dvi_21->open_relay(BUS_SENSE1);
	dvi_21->open_relay(BUS_FORCE1);
	wait.delay_10_us(50); // Avoid glitch // 
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_2_RANGE);
	//dvi_17->set_voltage(1, 0, VOLT_2_RANGE);
	dvi_21->set_voltage(1, 0, VOLT_2_RANGE);

	// Test DVI2K (DVI13)Ch0 (IS)
	IS_dvi2k->close_relay(CHANNEL_SHORT);
	wait.delay_10_us(50);
	IS_dvi2k->set_current(IS_ch, -6.0e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, -0.5, VOLT_2_RANGE);
	wait.delay_10_us(15); // Avoid glitch //
	IS_dvi2k->set_voltage(IS_ch, -1.5, VOLT_2_RANGE);
	
	// Sink Current to check Force and Sense connectivity
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
	SR_dvi2k->set_current(SR_ch,20e-3, RANGE_20_MA);
	SR_dvi2k->set_meas_mode(SR_ch,DVI_MEASURE_CURRENT);
	wait.delay_10_us(200);
	SR_dvi2k->close_relay(BUS_SENSE1);
	SR_dvi2k->close_relay(BUS_FORCE1);
	wait.delay_10_us(200);
	Icont6mA_IS = SR_dvi2k->measure_average(5);		// Check current 

	// Power down //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
	wait.delay_10_us(200);
	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	wait.delay_10_us(200);

	// Test DVI2K (DVI13) Ch1 (SR) //
	//Channel Short already closed up above
	// Source current
	SR_dvi2k->set_current(SR_ch, -6.0e-3, RANGE_20_MA);
	SR_dvi2k->set_voltage(SR_ch, -0.2, VOLT_2_RANGE);
	wait.delay_10_us(100); // Avoid glitch //
	SR_dvi2k->set_voltage(SR_ch, -1.5, VOLT_2_RANGE);
	
	// Sink Current to check Force and Sense connectivity
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE);
	IS_dvi2k->set_current(IS_ch,20e-3, RANGE_20_MA);
	IS_dvi2k->set_meas_mode(IS_ch,DVI_MEASURE_CURRENT);
	wait.delay_10_us(200);

	IS_dvi2k->close_relay(BUS_SENSE0);
	IS_dvi2k->close_relay(BUS_FORCE0);
	wait.delay_10_us(200);

	Icont6mA_SR  = IS_dvi2k->measure_average(5);		// Check current 
	//Power down
	IS_dvi2k->set_voltage(IS_ch, 1.5, VOLT_2_RANGE); // Avoid glitch // 
	SR_dvi2k->set_voltage(SR_ch, 1.5, VOLT_2_RANGE); // Avoid glitch // 
	wait.delay_10_us(10);
	IS_dvi2k->open_relay(BUS_SENSE0);
	IS_dvi2k->open_relay(BUS_FORCE0);
	IS_dvi2k->open_relay(CHANNEL_SHORT);
	wait.delay_10_us(50); // Avoid glitch // 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE);
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);

	//Now measure ICONT on all OVI resources SDA, SCL, uVCC
	// Icont_SCL //
	Mux20_Close_relay(K51);
	wait.delay_10_us(200);
	SDA_ovi->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	SDA_ovi->set_voltage(SDA_ch, 0, VOLT_5_RANGE);
	SCL_ovi->set_current(SCL_ch, -6e-3, RANGE_30_MA);
	SCL_ovi->set_voltage(SCL_ch, -1.9, VOLT_2_RANGE);
	SCL_ovi->set_meas_mode(SCL_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(100);
	Icont_SCL = SCL_ovi->measure();
	SDA_ovi->set_voltage(SDA_ch, 0, VOLT_2_RANGE);
	SDA_ovi->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	SCL_ovi->set_voltage(SCL_ch, 0, VOLT_2_RANGE);
	SCL_ovi->set_current(SCL_ch, 20e-3, RANGE_30_MA);

	// Icont_SDA //
	SCL_ovi->set_current(SCL_ch, 20e-3, RANGE_30_MA);
	SCL_ovi->set_voltage(SCL_ch, 0, VOLT_5_RANGE);
	SDA_ovi->set_current(SDA_ch, -6e-3, RANGE_30_MA);
	SDA_ovi->set_voltage(SDA_ch, -1.9, VOLT_2_RANGE);
	SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(100);
	Icont_SDA = SDA_ovi->measure();
	SDA_ovi->set_voltage(SDA_ch, 0, VOLT_2_RANGE);
	SDA_ovi->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	SCL_ovi->set_voltage(SCL_ch, 0, VOLT_2_RANGE);
	SCL_ovi->set_current(SCL_ch, 20e-3, RANGE_30_MA);

	//Icont_uVCC //
	SDA_ovi->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	SDA_ovi->set_voltage(SDA_ch, 0, VOLT_5_RANGE);
	uVCC_ovi->set_current(uVCC_ch, -6e-3, RANGE_30_MA);
	uVCC_ovi->set_voltage(uVCC_ch, -1.9, VOLT_2_RANGE);
	uVCC_ovi->set_meas_mode(uVCC_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(100);
	Icont_uVCC = SDA_ovi->measure();
	SDA_ovi->set_voltage(SDA_ch, 0, VOLT_2_RANGE);
	SDA_ovi->set_current(SDA_ch, 20e-3, RANGE_30_MA);
	uVCC_ovi->set_voltage(uVCC_ch, 0, VOLT_2_RANGE);
	uVCC_ovi->set_current(uVCC_ch, 20e-3, RANGE_30_MA);
	wait.delay_10_us(200);
	Mux20_Open_relay(K51);
	wait.delay_10_us(200);

	// Check FB and UV Icont with OVI //
	Close_relay(MUX_1_1);
	Close_relay(MUX_1_2);
	Close_relay(MUX_1_3); // Added for connecting F and S of VPIN_ovi - HQL
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(200);

	// Sink Current to check Force and Sense connectivity
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 20e-3, RANGE_30_MA);	

	// FB Source current
	FB_ovi->set_current(FB_ch, -6.0e-3, RANGE_30_MA); 
	FB_ovi->set_voltage(FB_ch, -0.5, RANGE_2_V);
	wait.delay_10_us(15); // Avoid glitch //
	FB_ovi->set_voltage(FB_ch, -1.5, RANGE_2_V);
	wait.delay_10_us(500);
	IcontFB = VPIN_ovi->measure_average(5); // Check current from FB ovi  to UV ovi

	// Notes for v1.5-2.0 silicon
	/ UV Sense can't be checked on v1.5-2.0 silicon due to lack of ESD diode on UV pin.
	/ As long as both force and sense make connections, IcontUV will still read -6.0mA. 
	/ If only force is broken, this test will failed reading around -0.2mA				
	// UV Source current
	Open_relay(MUX_1_3);
	Close_relay(MUX_1_4); // Added for connecting F and S of FB_ovi - HQL
	wait.delay_10_us(100);
	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);

	// Sink Current to check Force and Sense connectivity
	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // Use -5V pull down through 2V range on DVI
	FB_ovi->set_current(FB_ch, 20e-3, RANGE_30_MA); 
	VPIN_ovi->set_current(VPIN_ch, -6.0e-3, RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, -0.5, RANGE_2_V);
	wait.delay_10_us(15); // Avoid glitch //
	VPIN_ovi->set_voltage(VPIN_ch, -1.5, RANGE_2_V);
	wait.delay_10_us(500);
	IcontUV = FB_ovi->measure_average(5);		// Check current from FB ovi  to UV ovi

	// Power down Icont OVI circuit on UV and FB
	FB_ovi->set_voltage(FB_ch, 0.0,		RANGE_2_V); // Use -5V pull down through 2V range on DVI
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,	RANGE_2_V);  wait.delay_10_us(10);
	Open_relay(MUX_1_1);	
	Open_relay(MUX_1_2);
	Open_relay(MUX_1_4);


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Secondary SRC-S Gnd Res check
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Float all pins except IS and Vout to prevent extra current path. //
	SR_dvi2k->open_relay(CONN_FORCE1); // Float //
	SR_dvi2k->open_relay(CONN_SENSE1); // Float //
	VBD_dvi->open_relay(CONN_FORCE0); // Float //
	VBD_dvi->open_relay(CONN_SENSE0); // Float //
	uVCC_ovi->disconnect(2); // Float //
	SDA_ovi->disconnect(0); // Float //
	SCL_ovi->disconnect(1); // Float //
	BPS_dvi->open_relay(CONN_FORCE1); // Float //
	BPS_dvi->open_relay(CONN_SENSE1); // Float //
	FB_ovi->disconnect(2); // Float //
	
	// Connect DVI9_0 to GND through BUS lines
	VO_dvi->close_relay(BUS_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);
	mux_14->close_relay(MUX_2_BUS2);
	Close_relay(MUX_2_1);	// Connect DVI9_0 BUS_SENSE to GND
	wait.delay_10_us(400);
	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE);

	// Force -2V, 100mA through IS pin //
	//BPS_dvi->set_voltage(BPS_ch, -1.5,		VOLT_2_RANGE);  
	//BPS_dvi->set_current(BPS_ch, -100.0e-3,	RANGE_300_MA);
	//SR_dvi2k->set_voltage(SR_ch, -1.5, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, -100.0e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
	IS_dvi2k->set_current(IS_ch, -100.0e-3, RANGE_200_MA); // DVI_13_0, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, -2, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	wait.delay_10_us(50);
	vmeas = VO_dvi->measure_average(25);
	//BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	//SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT); // DVI_13_1, dvi2k //
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT); // DVI_13_0, dvi2k // 
	wait.delay_10_us(50);
	//imeas = BPS_dvi->measure_average(25);
	//imeas = SR_dvi2k->measure_average(25);
	imeas = IS_dvi2k->measure_average(25);
	g_GNDRes_Se = -vmeas/(imeas + 1e-23);
	if (g_GNDRes_Se > 0.1) // Fail if GNDRes_Se higher than 100mohm //
	{
		g_GNDRes_Se = -g_GNDRes_Se; // Make negative to force failure. //
		g_Error_Flag = -228;
	}


	// Power down GNDRes 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_2_RANGE);  
	//SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
	SR_dvi2k->close_relay(CONN_SENSE1);
	SR_dvi2k->close_relay(CONN_FORCE1);
	VBD_dvi->close_relay(CONN_SENSE0);
	VBD_dvi->close_relay(CONN_FORCE0);
	uVCC_ovi->connect(2);
	SDA_ovi->connect(0);
	SCL_ovi->connect(1);
	BPS_dvi->close_relay(CONN_FORCE1);
	BPS_dvi->close_relay(CONN_SENSE1);
	FB_ovi->connect(2);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(BUS_SENSE0);
	Open_relay(MUX_2_BUS2);
	Open_relay(MUX_2_1); // Disconnect DVI9_0 BUS_SENSE from GND //
	Open_relay(K2);
	Open_relay(K18);


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Primary SRC-P Gnd Res check
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Open_relay(MUX_BANK_3_4);

	// Float Vpin to prevent extra current path. //
	VPIN_ovi->disconnect(1); // Float //

	// Connect DVI11_1 to GND through BUS lines
	FW_dvi->close_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);
	FW_dvi->open_relay(CONN_FORCE1);
	FW_dvi->open_relay(CONN_SENSE1);
	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	Close_relay(MUX_2_1);   // Connect DVI11_1 BUS_SENSE to GND 
	//Close_relay(K11); // Connect DVI11_0 to BPP
	Close_relay(K2);
	//Close_relay(K3);
	wait.delay_10_us(500);
	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_VOLTAGE);

	// Force -2V, 100mA through Drain pin //
	//BPP_DVI->set_voltage(BPP_ch, -1.5,        VOLT_2_RANGE);  
	//BPP_DVI->set_current(BPP_ch, -100.0e-3,   RANGE_300_MA);
	D_dvi->set_current(D_ch, -100.0e-3, RANGE_300_MA); // DVI_11_0 //
	D_dvi->set_voltage(D_ch, -1.5, VOLT_2_RANGE); // DVI_11_0 //
	wait.delay_10_us(50);
	vmeas = FW_dvi->measure_average(25);
	//BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_CURRENT);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT); // DVI_11_0 //
	wait.delay_10_us(50);
	//imeas = BPP_DVI->measure_average(25);
	imeas = D_dvi->measure_average(25);
	g_GNDRes_Pri = -vmeas/(imeas + 1e-23);
	if (g_GNDRes_Pri > 0.185) // Fail if GNDRes_Pri higher than 185mohm //
	{
		g_GNDRes_Pri = -g_GNDRes_Pri; // Make negative to force failure. //
		g_Error_Flag = -229;
	}

	// Power down GNDRes 
	BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE); 
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(BUS_SENSE0);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->close_relay(CONN_FORCE1);
	FW_dvi->close_relay(CONN_SENSE1);
	mux_14->open_relay(MUX_BANK_2_3);
	Open_relay(MUX_3_BUS3);
	Open_relay(MUX_2_1);	// Disconnect DVI9_0 BUS_SENSE from GND 
	Open_relay(K11);
	Open_relay(K2);
	//Open_relay(K3);
	VPIN_ovi->connect(1);
	Close_relay(MUX_BANK_3_4);

	// Power down and Open relays
	Open_relay(K2);
	Open_relay(K8);
	Open_relay(K18);
	Open_relay(K19);

	// VcontBPP_cap.
	// Continuity check for ground connection of BPP pin capacitor.
	// Force 100uA to BPP.  If BPP capacitor ground is NOT connected, BPP voltage will 
	// rise up very quickly.  If BPP capacitor ground is connected properly, the BPP 
	// voltage rises up more slowly.  Datalog BPP voltage, 350usec after 100uA forced to BPP.  //
	wait.delay_10_us(300); // Wait for relays //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 100e-6, RANGE_300_UA); // OVI_1_0 //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE); // OVI_1_0 //
	wait.delay_10_us(150);
	BPP_ovi->set_voltage(BPP_ch, 5, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(35); // 350usec.  Don't change //
	VcontBPP_cap = BPP_ovi->measure();
	BPP_ovi->set_voltage(BPP_ch, 0.1, RANGE_10_V); // OVI_1_0, prevent undershoot. //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	wait.delay_10_us(15);
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(20);
	VcontBPP_capGNG = 1; // Default is pass //
	if (VcontBPP_cap > 0.9) // Fail //
	{
		g_Error_Flag = -225;
		VcontBPP_capGNG = -99;
	}

	// Datalog //
	UpperLimit = (func.dlog->tests[A_VcontD].f_max_limit_val[0]); // Get upper limit //
	if (VcontD > UpperLimit)
		PiDatalog(func, A_VcontD, VcontD, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontD, VcontD, 15, POWER_UNIT);

	//PiDatalog(func, A_VcontD_p, VcontD_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontD_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontD_1mA > UpperLimit)
		PiDatalog(func, A_VcontD_1mA, VcontD_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontD_1mA, VcontD_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontD_Rat, VcontD_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontD].f_max_limit_val[0]); // Get upper limit //
	if (IcontD > UpperLimit)
		PiDatalog(func, A_IcontD, IcontD, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontD, IcontD, 15, POWER_MILLI);	
	
	//PiDatalog(func, A_ILL_D, ILL_D, 15, POWER_MICRO);
	//PiDatalog(func, A_ILH_D, ILH_D, 15, POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontBPP].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPP > UpperLimit)
		PiDatalog(func, A_VcontBPP, VcontBPP, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPP, VcontBPP, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontBPP_p, VcontBPP_p, 15,	POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontBPP_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPP_1mA > UpperLimit)
		PiDatalog(func, A_VcontBPP_1mA, VcontBPP_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPP_1mA, VcontBPP_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontBPP_Rat, VcontBPP_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontBPP].f_max_limit_val[0]); // Get upper limit //
	if (IcontBPP > UpperLimit)
		PiDatalog(func, A_IcontBPP, IcontBPP, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontBPP, IcontBPP, 15, POWER_MILLI);	
	
	//PiDatalog(func, A_ILL_BPP, ILL_BPP, 15, POWER_MICRO);
	//PiDatalog(func, A_ILH_BPP, ILH_BPP, 15, POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontUV].f_max_limit_val[0]); // Get upper limit //
	if (VcontUV > UpperLimit)
		PiDatalog(func, A_VcontUV,	VcontUV, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontUV,	VcontUV, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontUV_p, VcontUV_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontUV_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontUV_1mA > UpperLimit)
		PiDatalog(func, A_VcontUV_1mA, VcontUV_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontUV_1mA, VcontUV_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontUV_Rat, VcontUV_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontUV].f_max_limit_val[0]); // Get upper limit //
	if (IcontUV > UpperLimit)
		PiDatalog(func, A_IcontUV,	IcontUV, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontUV,	IcontUV, 15, POWER_MILLI);	
	
	//PiDatalog(func, A_ILL_UV,	ILL_UV, 15, POWER_MICRO);
	//PiDatalog(func, A_ILH_UV,	ILH_UV, 15, POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontFW].f_max_limit_val[0]); // Get upper limit //
	if (VcontFW > UpperLimit)
		PiDatalog(func, A_VcontFW, VcontFW, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFW, VcontFW, 15, POWER_UNIT);

	//PiDatalog(func, A_VcontFW_p, VcontFW_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontFW_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontFW_1mA > UpperLimit)
		PiDatalog(func, A_VcontFW_1mA, VcontFW_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontFW_1mA, VcontFW_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontFW_Rat, VcontFW_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontFW].f_max_limit_val[0]); // Get upper limit //
	if (IcontFW > UpperLimit)
		PiDatalog(func, A_IcontFW, IcontFW, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_IcontFW, IcontFW, 15,	POWER_MILLI);
	
	//PiDatalog(func, A_ILL_FW,	ILL_FW, 15,	POWER_MICRO);
	//PiDatalog(func, A_ILH_FW,	ILH_FW, 15,	POWER_MILLI);


	UpperLimit = (func.dlog->tests[A_VcontVO].f_max_limit_val[0]); // Get upper limit //
	if (VcontVO > UpperLimit)
		PiDatalog(func, A_VcontVO, VcontVO, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontVO, VcontVO, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontVO_p, VcontVO_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontVO_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontVO_1mA > UpperLimit)
		PiDatalog(func, A_VcontVO_1mA, VcontVO_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontVO_1mA, VcontVO_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontVO_Rat, VcontVO_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontVO].f_max_limit_val[0]); // Get upper limit //
	if (IcontVO > UpperLimit)
		PiDatalog(func, A_IcontVO, IcontVO, 29, POWER_MILLI);	
	else
		PiDatalog(func, A_IcontVO, IcontVO, 15, POWER_MILLI);	
	
	//PiDatalog(func, A_ILL_VO, ILL_VO, 15,	POWER_MICRO);
	//PiDatalog(func, A_ILH_VO,	ILH_VO, 15,	POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontSR].f_max_limit_val[0]); // Get upper limit //
	if (VcontSR > UpperLimit)
		PiDatalog(func, A_VcontSR, VcontSR, 29,	POWER_UNIT);
	else
		PiDatalog(func, A_VcontSR, VcontSR, 15,	POWER_UNIT);
	
	//PiDatalog(func, A_VcontSR_p, VcontSR_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontSR_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontSR_1mA > UpperLimit)
		PiDatalog(func, A_VcontSR_1mA, VcontSR_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontSR_1mA, VcontSR_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontSR_Rat, VcontSR_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontSR].f_max_limit_val[0]); // Get upper limit //
	if (Icont6mA_SR > UpperLimit)
		PiDatalog(func, A_IcontSR, Icont6mA_SR, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontSR, Icont6mA_SR, 15, POWER_MILLI);
	
	// Will always measure the current forced from SR pin due to IS pin is tied to the GND in the device. 
	// The SR current will sink to the GND. 
	// PiDatalog(func, A_IcontSR,	IcontSR, 15, POWER_MILLI);	
	//PiDatalog(func, A_ILL_SR,	ILL_SR, 15,	POWER_MICRO);
	//PiDatalog(func, A_ILH_SR,	ILH_SR, 15,	POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontBPS].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPS > UpperLimit)
		PiDatalog(func, A_VcontBPS, VcontBPS, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPS, VcontBPS, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontBPS_p, VcontBPS_p,15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontBPS_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontBPS_1mA > UpperLimit)
		PiDatalog(func, A_VcontBPS_1mA, VcontBPS_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontBPS_1mA, VcontBPS_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontBPS_Rat, VcontBPS_Rat,15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontBPS].f_max_limit_val[0]); // Get upper limit //
	if (IcontBPS > UpperLimit)
		PiDatalog(func, A_IcontBPS, IcontBPS, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontBPS, IcontBPS, 15, POWER_MILLI);
	
	//PiDatalog(func, A_ILL_BPS, ILL_BPS,15, POWER_MICRO);
	//PiDatalog(func, A_ILH_BPS, ILH_BPS,15, POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_Vcont_COMP_low].f_max_limit_val[0]); // Get upper limit //
	if (VcontFB > UpperLimit)
		PiDatalog(func, A_Vcont_COMP_low, VcontFB, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_COMP_low, VcontFB, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontFB_p,	VcontFB_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_Vcont_COMP_high].f_max_limit_val[0]); // Get upper limit //
	if (VcontFB_1mA > UpperLimit)
		PiDatalog(func, A_Vcont_COMP_high, VcontFB_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_COMP_high, VcontFB_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_COMP_rat, VcontFB_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_Icont_COMP].f_max_limit_val[0]); // Get upper limit //
	if (IcontFB > UpperLimit)
		PiDatalog(func, A_Icont_COMP, IcontFB, 29, POWER_MILLI);
	else
		PiDatalog(func, A_Icont_COMP, IcontFB, 15, POWER_MILLI);
	
	//PiDatalog(func, A_ILL_FB,	ILL_FB, 15,	POWER_MICRO);
	//PiDatalog(func, A_ILH_FB,	ILH_FB, 15,	POWER_MILLI);

	UpperLimit = (func.dlog->tests[A_VcontIS].f_max_limit_val[0]); // Get upper limit //
	if (VcontIS > UpperLimit)
		PiDatalog(func, A_VcontIS, VcontIS, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontIS, VcontIS, 15, POWER_UNIT);
	
	//PiDatalog(func, A_VcontIS_p, VcontIS_p, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_VcontIS_1mA].f_max_limit_val[0]); // Get upper limit //
	if (VcontIS_1mA > UpperLimit)
		PiDatalog(func, A_VcontIS_1mA, VcontIS_1mA, 29, POWER_UNIT);
	else
		PiDatalog(func, A_VcontIS_1mA, VcontIS_1mA, 15, POWER_UNIT);
	
	PiDatalog(func, A_VcontIS_Rat, VcontIS_Rat, 15, POWER_UNIT);

	UpperLimit = (func.dlog->tests[A_IcontIS].f_max_limit_val[0]); // Get upper limit //
	if (Icont6mA_IS > UpperLimit)
		PiDatalog(func, A_IcontIS, Icont6mA_IS, 29, POWER_MILLI);
	else
		PiDatalog(func, A_IcontIS, Icont6mA_IS, 15, POWER_MILLI);
	
	//VBD
	UpperLimit = (func.dlog->tests[A_Vcont_VBD_low].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_VBD_low > UpperLimit)
		PiDatalog(func, A_Vcont_VBD_low, Vcont_VBD_low, 29, POWER_UNIT);	
	else
		PiDatalog(func, A_Vcont_VBD_low, Vcont_VBD_low, 15, POWER_UNIT);	
	
	
	UpperLimit = (func.dlog->tests[A_Vcont_VBD_high].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_VBD_high > UpperLimit)
		PiDatalog(func, A_Vcont_VBD_high, Vcont_VBD_high, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_VBD_high, Vcont_VBD_high, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_VBD_rat, Vcont_VBD_rat, 15,	POWER_UNIT);
	
	UpperLimit = (func.dlog->tests[A_Icont_VBD].f_max_limit_val[0]); // Get upper limit //
	if (Icont_VBD > UpperLimit)
		PiDatalog(func, A_Icont_VBD, Icont_VBD, 29,	POWER_MILLI);
	else
		PiDatalog(func, A_Icont_VBD, Icont_VBD, 15,	POWER_MILLI);
	
	//SDA
	UpperLimit = (func.dlog->tests[A_Vcont_SDA_low].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_SDA_low > UpperLimit)
		PiDatalog(func, A_Vcont_SDA_low, Vcont_SDA_low, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_SDA_low, Vcont_SDA_low, 15, POWER_UNIT);
		
	UpperLimit = (func.dlog->tests[A_Vcont_SDA_high].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_SDA_high > UpperLimit)
		PiDatalog(func, A_Vcont_SDA_high, Vcont_SDA_high, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_SDA_high, Vcont_SDA_high, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_SDA_rat, Vcont_SDA_rat, 15, POWER_UNIT);
	
	LowerLimit = (func.dlog->tests[A_Icont_SDA].f_min_limit_val[0]); // Get lower limit //
	if (Icont_SDA < LowerLimit)
		PiDatalog(func, A_Icont_SDA, Icont_SDA, 29, POWER_MILLI);
	else
		PiDatalog(func, A_Icont_SDA, Icont_SDA, 15, POWER_MILLI);
	

	//SCL
	UpperLimit = (func.dlog->tests[A_Vcont_SCL_low].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_SCL_low > UpperLimit)
		PiDatalog(func, A_Vcont_SCL_low, Vcont_SCL_low, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_SCL_low, Vcont_SCL_low, 15, POWER_UNIT);
	
	UpperLimit = (func.dlog->tests[A_Vcont_SCL_high].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_SCL_high > UpperLimit)
		PiDatalog(func, A_Vcont_SCL_high, Vcont_SCL_high, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_SCL_high, Vcont_SCL_high, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_SCL_rat, Vcont_SCL_rat, 15, POWER_UNIT);

	LowerLimit = (func.dlog->tests[A_Icont_SCL].f_min_limit_val[0]); // Get lower limit //
	if (Icont_SCL < LowerLimit)
		PiDatalog(func, A_Icont_SCL, Icont_SCL, 29, POWER_MILLI);
	else
		PiDatalog(func, A_Icont_SCL, Icont_SCL, 15, POWER_MILLI);
	
	//uVCC
	UpperLimit = (func.dlog->tests[A_Vcont_uVCC_low].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_uVCC_low > UpperLimit)
		PiDatalog(func, A_Vcont_uVCC_low, Vcont_uVCC_low, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_uVCC_low, Vcont_uVCC_low, 15, POWER_UNIT);
	
	UpperLimit = (func.dlog->tests[A_Vcont_uVCC_high].f_max_limit_val[0]); // Get upper limit //
	if (Vcont_uVCC_high > UpperLimit)
		PiDatalog(func, A_Vcont_uVCC_high, Vcont_uVCC_high, 29, POWER_UNIT);
	else
		PiDatalog(func, A_Vcont_uVCC_high, Vcont_uVCC_high, 15, POWER_UNIT);
	
	PiDatalog(func, A_Vcont_uVCC_rat, Vcont_uVCC_rat, 15, POWER_UNIT);

	LowerLimit = (func.dlog->tests[A_Icont_uVCC].f_min_limit_val[0]); // Get lower limit //
	if (Icont_uVCC < LowerLimit)
		PiDatalog(func, A_Icont_uVCC, Icont_uVCC, 29, POWER_MILLI);
	else
		PiDatalog(func, A_Icont_uVCC, Icont_uVCC, 15, POWER_MILLI);
	
	PiDatalog(func, A_GNDRes_Se, g_GNDRes_Se, 15, POWER_MILLI);	
	PiDatalog(func, A_GNDRes_Pri, g_GNDRes_Pri,15, POWER_MILLI);
	PiDatalog(func, A_VcontBPP_cap, VcontBPP_cap, 15, POWER_UNIT);
	PiDatalog(func, A_VcontBPP_capGNG, VcontBPP_capGNG, 15, POWER_UNIT);

	// Check for any failures //
	if (PiGetAnyFailStatus())
	{
		AbortTest = true;
		delay(50);	// Wait 50ms if failing continuity for Handler to respond properly
	}

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		Continuity_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_Continuity_TT, Continuity_TT, 15, POWER_MILLI);
	}	

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}	
*/
}
