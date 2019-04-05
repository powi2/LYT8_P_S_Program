//==============================================================================
// Leakage.cpp (User function)
// 
//    void Leakage_user_init(test_function& func)
//    void Leakage(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Leakage.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!
#include <fstream>
// *************************************************************************

void Leakage_user_init(test_function& func)
{
	Leakage_params *ours;
    ours = (Leakage_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Leakage(test_function& func)
{
    // The two lines below must be the first two in the function.
    Leakage_params *ours;
    ours = (Leakage_params *)func.params;

	// Increment function number //
	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Leakage, gFuncNum, 11, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_Leakage == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Declare Variables //
	float ILL_D		=0;
	float ILH_UV	= 0;
	float ILL_UV	= 0;
	float ILH_TS	= 0;
	float ILL_TS	= 0;
	float ILH1_FW	= 0;
	float ILH2_FW	= 0;
	float ILL1_FW	= 0;
	float ILL2_FW	= 0;
	float ILH1_IS	= 0;
	float ILH2_IS	= 0;
	float ILL_IS	= 0;
	float ILH_FB	= 0;
	float ILL_FB	= 0;
	float ILH_B	    = 0;
	float ILL_B  	= 0;
	float ILH_HSG	= 0;
	float ILL_HSG  	= 0;
	float ILH1_SDA	= 0;
	float ILH2_SDA	= 0;
	float ILL_SDA  	= 0;
	float ILH_SCL	= 0;
	float ILL_SCL  	= 0;
	float ILL_VR	= 0;
	float ILH1_VR  	= 0;
	float ILH2_VR  	= 0;
	float ILH3_VR  	= 0;



Pulse pulse;

	// Open all relays //
	Initialize_Relays();

	// Setup Instruments //
	// Primary
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);                  // DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-6, RANGE_300_UA);     
	UV_dvi->set_voltage(UV_ch, 0.0, RANGE_10_V);                   // DVI_21_1
	UV_dvi->set_current(UV_ch, 3e-3, RANGE_3_MA);	
	BPP_dvi->set_voltage(BPP_ch, 0.0, RANGE_10_V);				   // DVI_11_1
	BPP_dvi->set_current(BPP_ch, 200e-3, RANGE_300_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE);            // OVI_3_0
	TS_ovi3->set_current(TSovi3_ch, 3e-3, RANGE_3_MA);

	//Secondary.
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);				// DVI_13_1
	IS_dvi2k->set_current(IS_ch, 200.0e-6, RANGE_200_UA);
	SDA_ovi3->set_current(SDA_ch, 300e-6, RANGE_300_UA);	        //OVI_3_5
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 300e-6, RANGE_30_MA);				//OVI_3_6
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); // DVI_9_1
	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
	////



	//BP leakage is skipped because BPP is a supply pin.  Unable to measure leakage on this pin.
	//Drain Low Leakage test only (High leakage is already in BV_Drain function)
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 
	D_dvi->set_current(D_ch, 300.0e-6, RANGE_300_UA); 
	wait.delay_10_us(150);	

	ILL_D = D_dvi->measure_average(15);

	//UV & TS Leakage required to enter I2C because these 2 pins always consume current in normal mode.
	//I2C mode, these two pins will be disconnected from the normal consumption mode, which the currents will be
	//considered as leakage currents.

	//Connect Pullup R to TS and UV pins
	Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
	Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.

	//Connect DSM CLK & Data to primary pins: TS & UV
	mux_14->open_relay(MUX_1_1);
	mux_14->open_relay(MUX_1_3);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	//Drain already @ 0V
	//BPP to 5.0V to enter I2C mode.
	float j = 0.0, vpullup_P = 5.0;
	while(j<=5)
	{
		BPP_dvi->set_voltage(BPP_ch, j, VOLT_10_RANGE); // DVI_11_1
		if(j >=vpullup_P)
		{
			TS_ovi3->set_voltage(TSovi3_ch, vpullup_P, VOLT_10_RANGE); // OVI_3_0
			UV_dvi->set_voltage(UV_ch,		vpullup_P, VOLT_10_RANGE); // DVI_21_1
		}
		j=j+0.5;
	}
	BPP_dvi->set_voltage(BPP_ch, 5, VOLT_10_RANGE); // DVI_11_1
	wait.delay_10_us(50);

	//-----------------------------------------------------------------------------------------
	// Vpin pin leakages 
	//-----------------------------------------------------------------------------------------
	UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_CURRENT);
	UV_dvi->set_voltage(UV_ch, 5.0, RANGE_10_V);
	UV_dvi->set_current(UV_ch, 300e-6, RANGE_300_UA);	
	wait.delay_10_us(200);

	ILH_UV = UV_dvi->measure_average(25);

	//UV back to 3mA range before setting to 0V.
	UV_dvi->set_current(UV_ch, 3e-3, RANGE_3_MA);
	wait.delay_10_us(50);
	UV_dvi->set_voltage(UV_ch, 0.0, RANGE_10_V); 
	wait.delay_10_us(50);
	//Reduce curent range for more accuracy.
	UV_dvi->set_current(UV_ch, 300e-6, RANGE_300_UA);	
	wait.delay_10_us(200);

	ILL_UV = UV_dvi->measure_average(25);

	//UV back to 5.0V/3mA range before TS leakage current tests.
	UV_dvi->set_current(UV_ch, 3e-3, RANGE_3_MA);
	UV_dvi->set_voltage(UV_ch, 5.0, RANGE_10_V); 
	wait.delay_10_us(50);
	
	//-------------------------------------------------------------------------------------------
	//  TS pin leakages 
	//------------------------------------------------------------------------------------------
	TS_ovi3->set_meas_mode(TSovi3_ch, OVI_MEASURE_CURRENT);
	TS_ovi3->set_voltage(TSovi3_ch, 5.0, RANGE_10_V);
	TS_ovi3->set_current(TSovi3_ch, 300e-6, RANGE_300_UA);	
	wait.delay_10_us(200);

	ILH_TS = TS_ovi3->measure_average(25);
	//Due to overshoot. Need to go back to 3mA and drop to 0.5V first.
	TS_ovi3->set_current(TSovi3_ch, 3e-3, RANGE_3_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.5, RANGE_10_V); 
	wait.delay_10_us(50);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, RANGE_10_V); 
	wait.delay_10_us(50);
	TS_ovi3->set_current(TSovi3_ch, 300e-6, RANGE_300_UA);
	wait.delay_10_us(200);

	ILL_TS = TS_ovi3->measure_average(25);

	//PowerDown. Need to power down to 1V first due to undershoot.
	TS_ovi3->set_voltage(TSovi3_ch, 1, RANGE_10_V); 
	wait.delay_10_us(50);

	TS_ovi3->set_current(TSovi3_ch, 3e-3, RANGE_3_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 1, VOLT_10_RANGE); 
	UV_dvi->set_voltage(UV_ch,		1, VOLT_10_RANGE); 
	BPP_dvi->set_voltage(BPP_ch,    1, VOLT_10_RANGE); 
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(50);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); 
	UV_dvi->set_voltage(UV_ch,		0.0, VOLT_10_RANGE); 
	BPP_dvi->set_voltage(BPP_ch,    0.0, VOLT_10_RANGE); 
	wait.delay_10_us(50);
	Open_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
	Open_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
	//Connect DSM CLK & Data to primary pins: TS & UV
	mux_14->open_relay(MUX_1_1);
	mux_14->open_relay(MUX_1_3);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	//----------------------------------------------------------------------------------------------------------------
	//End of Primary Leakage.
	//---------------------------------------------------------------------------------------------------------------
	
	//----------------------------------------------------------------------------------------------------------------
	//Start of Secondary Leakage.
	//---------------------------------------------------------------------------------------------------------------
	//Unable to measure leakage on HBP & BPS because these 2 pins are supply pins.
	DSM_init_LYT8();
	//Set current & voltage ranges first.
	//Secondary.
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	FW_ovi3->set_current(FW_ch, 300e-6, RANGE_300_UA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);//Keep 200mA range here or IS will drop below ground.
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	HBP_dvi2k->set_current(HBP_ch, 0.0e-6, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);


//------------------------------------------------------------------------------------------------------------------

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	//HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);
	Close_relay(K1_SDA_SPI_TB);       //Connect pullup R to SDA.
	Close_relay(K1_SCL_SPI_TB);       //Connect pullup R to SCL
	Close_relay(K2_DSM_TB);           //Connect DSM SDA to DUT SDA
	Close_relay(K4_DSM_TB);           //Connect DSM SCL to DUT SCL
	wait.delay_10_us(250);
	
	///Power up VR to 15V to wake up 2ndary.
	VR_dvi->set_voltage(VR_ch, 15, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	//FB = 1.25V
	FB_ovi3->set_current(FB_ch, 300e-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 1.00, VOLT_10_RANGE); 
	
	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); 
	wait.delay_10_us(200);

	//////////IS leakage can be measured here??
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, 2e-3, RANGE_200_MA);
	IS_dvi2k->set_voltage(IS_ch, 1.0, VOLT_10_RANGE);
	wait.delay_10_us(100);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	
	//Designer format is Lower Byte then Upper Byte.
	//1) 0x00 0x5E write 0x16 0x20
	DSM_I2C_Write('w', 0x5E, 0x2016);	

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//2.0x00 0x5E write 0x34 0x12  ==> access test mode.
	DSM_I2C_Write('w', 0x5E, 0x1234);	

	//3.0x00 0x62 write 0x88 0x00  ==> enable the HSG/B driver and disable FB-to_HBP short.
	DSM_I2C_Write('w', 0x62, 0x0088);

	//4.0x00 0x60 write 0x00 0xC0  ==> Open Drain on HSG & B.
	DSM_I2C_Write('w', 0x60, 0xC000);	

	//5.0x00 0x40 write 0x07 0x00  ==> enable SIG & Analog test modes & Set Core Enable to 1.
	DSM_I2C_Write('w', 0x40, 0x0007);

	//6.0x00 0x42 write 0x14 0x00  ==> enable Dfb_comps_out to disable the lower FET.
	DSM_I2C_Write('w', 0x42, 0x0014);

	//---------------------------------------------------------------------------
	//Measure FB Leakage.
	//---------------------------------------------------------------------------
	FB_ovi3->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);
	//FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 5.0, VOLT_10_RANGE); 
	wait.delay_10_us(500);
	ILH_FB = FB_ovi3->measure_average(25);
	
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(500);
	ILL_FB = FB_ovi3->measure_average(25);

	//Reset FB to 1V
	FB_ovi3->set_voltage(FB_ch, 1.0, VOLT_10_RANGE); 
	wait.delay_10_us(100);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//-----------------------------------------------------------------------------------------------------
	//SDA
	//------------------------------------------------------------------------------------------------------
	SDA_ovi3->set_meas_mode(SDA_ch, OVI_MEASURE_CURRENT);
	SDA_ovi3->set_current(SDA_ch, 10e-6, RANGE_300_UA);
	SDA_ovi3->set_voltage(SDA_ch,0.0, VOLT_10_RANGE);
	SCL_ovi3->set_current(SCL_ch, 10e-6, RANGE_300_UA);
	SCL_ovi3->set_voltage(SCL_ch,0.0, VOLT_10_RANGE);
	delay(5);

	//Remove Pullup Resistor.
	Open_relay(K1_SDA_SPI_TB);       //Disconnect pullup R from SDA.
	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	Open_relay(K1_SCL_SPI_TB);       //Disconnect pullup R from SCL.
	Open_relay(K4_DSM_TB);           //Disconnect DSM SCL from DUT SCL
	wait.delay_10_us(250);

	SDA_ovi3->set_current(SDA_ch, 300e-6, RANGE_300_UA);
	SDA_ovi3->set_voltage(SDA_ch,5.0, VOLT_10_RANGE);
	delay(5);
	ILH2_SDA = SDA_ovi3->measure_average(100);

	SDA_ovi3->set_voltage(SDA_ch,3.3, VOLT_10_RANGE);
	delay(5);
	ILH1_SDA = SDA_ovi3->measure_average(100);

	SDA_ovi3->set_voltage(SDA_ch,0.0, VOLT_10_RANGE);
	delay(5);
	ILL_SDA = SDA_ovi3->measure_average(100);

	//-----------------------------------------------------------------------------------------------------
	//SCL
	//------------------------------------------------------------------------------------------------------
	SCL_ovi3->set_meas_mode(SCL_ch, OVI_MEASURE_CURRENT);
	SCL_ovi3->set_current(SCL_ch, 300e-6, RANGE_300_UA);
	SCL_ovi3->set_voltage(SCL_ch,10.0, VOLT_10_RANGE);
	delay(10);
	ILH_SCL = SCL_ovi3->measure_average(100);

	SCL_ovi3->set_voltage(SCL_ch,0.0, VOLT_10_RANGE);
	delay(10);
	ILL_SCL = SCL_ovi3->measure_average(100);
	
	//////------------------------------------------------------------------------------------------------------
	//////FW
	//////------------------------------------------------------------------------------------------------------
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, -0.1, VOLT_10_RANGE);
	FW_ovi3->set_meas_mode(FW_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(500);
	ILL1_FW = FW_ovi3->measure_average(25);

	FW_ovi3->set_voltage(FW_ch, 5.0, VOLT_10_RANGE);
	wait.delay_10_us(500);
	ILH2_FW = FW_ovi3->measure_average(25);

	FW_ovi3->set_current(FW_ch, 300e-6, RANGE_300_UA);
	FW_ovi3->set_voltage(FW_ch, 3.3, VOLT_10_RANGE);
	wait.delay_10_us(500);
	ILH1_FW = FW_ovi3->measure_average(25);

	FW_ovi3->set_voltage(FW_ch, 0.1, VOLT_10_RANGE);
	wait.delay_10_us(500);
	ILL2_FW = FW_ovi3->measure_average(25);

	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(500);

	//------------------------------------------------------------------------------------------------------
	//Boost
	//------------------------------------------------------------------------------------------------------
	

	B_ovi3->set_meas_mode(B_ch1, OVI_MEASURE_CURRENT);
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 5.0, VOLT_10_RANGE); 
	delay(5);
	ILH_B = B_ovi3->measure_average(100);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE); 
	delay(5);
	ILL_B = B_ovi3->measure_average(100);

	//-----------------------------------------------------------------------------------------------------
	//HSG
	//------------------------------------------------------------------------------------------------------
	HBP_dvi2k->set_meas_mode(HBP_ch, DVI_MEASURE_VOLTAGE);
	delay(2);
	float v_HBP = HBP_dvi2k->measure_average(5);

	g_HBP_Pre_S = v_HBP;

	if(v_HBP < 11) v_HBP = 11.5;


	HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_CURRENT);
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, v_HBP, VOLT_20_RANGE); 
	delay(5);
	ILH_HSG = HSG_ovi->measure_average(25);

	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, 0.0, VOLT_20_RANGE); 
	delay(5);
	ILL_HSG = HSG_ovi->measure_average(100);

	//////////------------------------------------------------------------------------------------------------------
	//////////IS Leakage
	//////////------------------------------------------------------------------------------------------------------
	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
	IS_dvi2k->set_current(IS_ch, 200e-6, RANGE_200_UA);
	IS_dvi2k->set_voltage(IS_ch, 3.3, VOLT_10_RANGE);
	wait.delay_10_us(500);
	ILH1_IS = IS_dvi2k->measure_average(25);

	//IS_dvi2k->set_current(IS_ch, 20e-3, RANGE_20_MA);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(500);
	ILL_IS = IS_dvi2k->measure_average(25);

	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);
	wait.delay_10_us(100);

	HBP_dvi2k->set_current(HBP_ch, 50e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 13, VOLT_20_RANGE);
	delay(5);



	//THIS IS A TRADEOFF BETWEEN ERROR AND ACCURACY. 3MA RANGE VS 300UA RANGE.
	//300uA will cause overshoot It requires wait time at least 6ms for a stable measurement.
	VR_dvi->set_meas_mode(VR_ch, DVI_MEASURE_CURRENT);
	VR_dvi->set_current(VR_ch, 3e-3, RANGE_3_MA);	
	VR_dvi->set_voltage(VR_ch, 15, VOLT_50_RANGE);
	delay(10);
	ILH1_VR = VR_dvi->measure_average(25);

	VR_dvi->set_voltage(VR_ch, 20.0, VOLT_50_RANGE);
	delay(10);
	VR_dvi->set_voltage(VR_ch, 30.0, VOLT_50_RANGE);
	delay(10);

	ILH2_VR = VR_dvi->measure_average(25);

	//It takes more than 10ms for VR to be stable at 50V.  
	//For production, it's best to use 3mA with the cost of accuracy in order to reduce test time.
	VR_dvi->set_voltage(VR_ch, 50.0, VOLT_50_RANGE);
	delay(20);

	ILH3_VR = VR_dvi->measure_average(25);

	//At 0V, Vr leakage is high, drawing more than 20mA.  Will need to check with design.
	///*VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE);
	//delay(20);

	//ILL_VR = VR_dvi->measure_average(25);*/


	//VR current range change is done on purpose to smooth out the undershoot.
	VR_dvi->set_current(VR_ch, 0.1e-3, RANGE_30_MA);
	VR_dvi->set_voltage(VR_ch, 10.0, VOLT_50_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 10.0, VOLT_20_RANGE);
	delay(1);
	VR_dvi->set_voltage(VR_ch, 5.0, VOLT_50_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 5.0, VOLT_20_RANGE);
	delay(1);
	VR_dvi->set_voltage(VR_ch, 2.0, VOLT_50_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 2.0, VOLT_20_RANGE);
	delay(1);
	VR_dvi->set_voltage(VR_ch, 0.5, VOLT_50_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 0.5, VOLT_20_RANGE);
	delay(1);
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	delay(1);

	///*HBP_dvi2k->set_current(HBP_ch, 10e-3, RANGE_20_MA);
	//HBP_dvi2k->set_voltage(HBP_ch, 5.0, VOLT_20_RANGE);
	//delay(5);
	//HBP_dvi2k->set_current(HBP_ch, 10e-3, RANGE_20_MA);
	//HBP_dvi2k->set_voltage(HBP_ch, 2.0, VOLT_20_RANGE);
	//delay(5);
	//HBP_dvi2k->set_current(HBP_ch, 10e-3, RANGE_20_MA);
	//HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//delay(10);*/


//////////Secondary Powerdown.
	HSG_ovi->set_current(HSG_ch, 300e-6, RANGE_300_UA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	FW_ovi3->set_current(FW_ch, 300e-6, RANGE_300_UA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	FB_ovi3->set_current(FB_ch, 300E-6, RANGE_300_UA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-6, RANGE_200_UA);
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-6, RANGE_300_MA);
	HBP_dvi2k->set_current(HBP_ch, 200.0e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	VR_dvi->set_current(VR_ch, 100.0e-6, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(200);

	Open_relay(K1_SDA_SPI_TB);       //Disconnect pullup R from SDA.
	Open_relay(K1_SCL_SPI_TB);       //Disconnect pullup R from SCL
	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	Open_relay(K4_DSM_TB);           //Disconnect DSM SCL from DUT SCL
	wait.delay_10_us(250);



	//Primary Datalog
	PiDatalog(func, A_IIL_D,     ILL_D, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_TS,    ILL_TS, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_TS,    ILH_TS, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_UV,    ILL_UV, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_UV,    ILH_UV, 11, POWER_MICRO);
	PiDatalog(func, A_IIL1_FW,   ILL1_FW, 11, POWER_MILLI);
	PiDatalog(func, A_IIL2_FW,   ILL2_FW, 11, POWER_MICRO);
	PiDatalog(func, A_IIH1_FW,   ILH1_FW, 11, POWER_MICRO);
	PiDatalog(func, A_IIH2_FW,   ILH2_FW, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_IS,    ILL_IS, 11, POWER_MICRO);
	PiDatalog(func, A_IIH1_IS,   ILH1_IS, 11, POWER_MICRO);
	//PiDatalog(func, A_IIH2_IS,   ILH2_IS, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_FB,    ILL_FB, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_FB,    ILH_FB, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_B,     ILL_B, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_B,     ILH_B, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_HSG,   ILL_HSG, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_HSG,   ILH_HSG, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_SCL,   ILL_SCL, 11, POWER_MICRO);
	PiDatalog(func, A_IIH_SCL,   ILH_SCL, 11, POWER_MICRO);
	PiDatalog(func, A_IIL_SDA,   ILL_SDA, 11, POWER_MICRO);
	PiDatalog(func, A_IIH1_SDA,  ILH1_SDA, 11, POWER_MICRO);
	PiDatalog(func, A_IIH2_SDA,  ILH2_SDA, 11, POWER_MICRO);
	PiDatalog(func, A_IIH2_SDA,  ILH2_SDA, 11, POWER_MICRO);
	PiDatalog(func, A_IIH1_VR,  ILH1_VR, 11, POWER_MICRO);
	PiDatalog(func, A_IIH2_VR,  ILH2_VR, 11, POWER_MICRO);
	PiDatalog(func, A_IIH3_VR,  ILH3_VR, 11, POWER_MICRO);



	//PiDatalog(func, A_ILH_UV, ILH_UV, 11, POWER_MICRO);

	////FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); // DVI_11_1
	////FW_dvi->set_current(FW_ch, 20.0e-6, RANGE_30_UA);
	////SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	////SR_dvi2k->set_current(SR_ch, 200.0e-6, RANGE_200_UA);
	////FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2
	////FB_ovi->set_current(FB_ch, 30.0e-6, RANGE_30_UA);
	////uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
	////uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	////SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V);
	////SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
	////SCL_ovi->set_voltage(SCL_ch, 0, RANGE_5_V);	
	////SCL_ovi->set_current(SCL_ch, 29e-6, RANGE_30_UA);
	////VBD_dvi->set_voltage(VBD_ch, 0, VOLT_50_RANGE);	
	////VBD_dvi->set_current(VBD_ch, 1e-3, RANGE_3_MA);	










////	int FB_Buff_Check = 0;
////	float FB_Buff_Value = 0;
////	float SR_Gnd_Res = 0;
////	int MUX20_Check = 0;
////	float ILL_D=0;
////	float ILL_BPP=0; 
////	float ILL_UV=0;
////	//float ILL_IS=0;
////	g_ILL_IS = 0;
////	//float ILL_FB=0; 
////	g_ILL_FB = 0;
////	float ILL_BPS=0; 
////	float ILL_SR=0;
////	//float ILL_VO=0;
////	g_ILL_VO = 0;
////	//float ILL_FW=0;
////	g_ILL_FW = 0;
////	//float ILL_SDA=0;
////	g_ILL_SDA = 0;
////	//float ILL_SCL=0;
////	g_ILL_SCL = 0;
////	float ILH_D=0;
////	float ILH_BPP=0; 
////	float ILH_UV=0;
////	float ILH_IS=0; 
////	//float ILH_FB=0;
////	g_ILH_FB = 0;
////	float ILH_BPS=0; 
////	float ILH_SR=0;
////	float ILH_VO=0; 
////	float ILH_FW=0;
////	//float ILH_SDA=0;
////	g_ILH_SDA = 0;
////	//float ILH_SCL=0;
////	g_ILH_SCL = 0;
////	//float ILH_VBD=0;
////	g_ILH_VBD = 0;
////	//float ILL_VBD=0;
////	g_ILL_VBD = 0;
////	float IIL_uVCC=0;
////	float IIH_uVCC=0;
////	float vmeas=0; 
////	float imeas=0;
////	float starttime=0;
////	float stoptime =0;
////	int i=0;
////	float FB_buf_In = 0;
////	float FB_buf_Out = 0;
////	float FB_buf_PercentError = 0;
////	float SR_volt = 0;
////	float UpperLimit = 0;
////	float LowerLimit = 0;
////	float CurrentClamp = 0;
////	char STRINGarray[1024] = {'\0'};//buffer to store formatted input.
////	float Leakage_TT = 0;
////
////	//Initialize all variables to be 999uA;
////	ILL_D =99e-3;
////	ILL_BPP =99e-3; 
////	ILL_UV =99e-3; 
////	g_ILL_IS =99e-3; 
////	g_ILL_FB =99e-3; 
////	ILL_BPS =99e-3; 
////	ILL_SR =99e-3; 
////	g_ILL_VO =99e-3; 
////	g_ILL_FW =99e-3;
////	g_ILL_SDA =99e-3;
////	g_ILL_SCL =99e-3;
////	ILH_D =99e-3; 
////	ILH_BPP =99e-3; 
////	ILH_UV =99e-3; 
////	ILH_IS =99e-3; 
////	g_ILH_FB =99e-3; 
////	ILH_BPS =99e-3; 
////	ILH_SR =99e-3; 
////	ILH_VO =99e-3; 
////	ILH_FW =99e-3;
////	g_ILH_SDA =99e-3;
////	g_ILH_SCL =99e-3;
////	g_ILH_VBD =99e-3;
////	g_ILL_VBD =99e-3;
////	vmeas =99e-3; 
////	imeas =99e-3;
////	Pulse pulse(PULSE_RISING_EDGE,10e-6); //external trigger pulse from dvi for debug
////
////
////	// Check fall time of InvSync circuit output.   If fall time is too long, test repeatability problems occur.//
////	// Measurement was made in aFirst.cpp //
////	if (g_InvSyn_Fall > g_Inv_threshold || g_InvSyn_Fall < 1)
////	{
////		//Setup = 999; // Failed setup //
////		g_Error_Flag = -222;
////		sprintf(STRINGarray,"InvSync fall time out of spec.\n\n%f nsec.\n", g_InvSyn_Fall);
////		cout << endl << endl << "InvSyncFallTime = " << g_InvSyn_Fall << endl; 
////		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
////	}
////	if (g_FWmeasV < -0.27)
////	{
////		//Setup = 999; // Failed setup //
////		g_Error_Flag = -222;
////		sprintf(STRINGarray,"InvSync output not return to zero.\n\n%f V.\n", g_FWmeasV);
////		cout << endl << endl << "InvSync Ouput = " << g_FWmeasV << endl; 
////		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
////	}
////
////	// Open all relays //
////	Initialize_Relays();
////
////	// Initialize Instruments //
////	Initialize_Instruments();
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Check FB pin buffer (OP07) //
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	FB_buf_In = 0.9; // Buffer input voltage //
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 0.1e-6, RANGE_30_UA); // DVI_9_0, no current on Vout //
////	Mux20_Close_relay(K59); // Connect buffer input to DVI_13_1, dvi2k  //
////	Mux20_Close_relay(K55); // Buffer input connection //
////	Mux20_Close_relay(K56); // Buffer output connection //
////	FB_ovi->disconnect(2);
////	Mux20_Close_relay(K46); // Connect buffer output to DVI_13_0, dvi2k //
////	dvi_13->set_current(DVI_CHANNEL_0, 0.1e-9, RANGE_20_UA); // DVI_13_0, dvi2k, buffer output  //
////	dvi_13->open_relay(CONN_FORCE0);
////	dvi_13->set_voltage(DVI_CHANNEL_1, FB_buf_In, VOLT_1_RANGE); // DVI_13_1, dvi2k, buffer input //
////	dvi_13->set_current(DVI_CHANNEL_1, 20e-3, RANGE_20_MA); // DVI_13_1, dvi2k, buffer input  //
////	wait.delay_10_us(300);
////	dvi_13->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_VOLTAGE); // Buffer output //
////	wait.delay_10_us(30);
////	FB_buf_Out = dvi_13->measure_average(20); // Buffer output //
////	FB_buf_PercentError = ( (FB_buf_Out-FB_buf_In)/FB_buf_In ) * 100;
////	if(FB_buf_PercentError < 0) // Remove negative //
////		FB_buf_PercentError *= -1; // Remove negative //
////	Mux20_Open_relay(K59);
////	Mux20_Open_relay(K55);
////	Mux20_Open_relay(K56);
////	FB_ovi->connect(2);
////	Mux20_Open_relay(K46);
////	dvi_13->set_current(DVI_CHANNEL_0, 20e-3, RANGE_20_MA); // DVI_13_0, dvi2k, buffer output  //
////	dvi_13->close_relay(CONN_FORCE0);
////	dvi_13->set_voltage(DVI_CHANNEL_1, 0, VOLT_1_RANGE); // DVI_13_1, dvi2k, buffer input //
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
////	FB_Buff_Check = 1; // Default is pass //
////	if (FB_buf_PercentError > 0.11) // Error //
////	{
////		FB_Buff_Check = -99;
////		g_Error_Flag = -191;
////	}
////	FB_Buff_Value = FB_buf_PercentError;
////
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	// Check to make sure relay K50 is working properly and provides a good SR pin short to 
////	// ground.  This is important for repeatability throughout test program.
////	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_1_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
////	wait.delay_10_us(20);
////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
////	wait.delay_10_us(250);
////	SR_dvi2k->set_current(SR_ch, 100e-3, RANGE_200_MA); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_voltage(SR_ch, 1, VOLT_1_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k //
////	wait.delay_10_us(250);
////	SR_volt = SR_dvi2k->measure();
////	SR_Gnd_Res = SR_volt / 100e-3;
////	SR_dvi2k->set_voltage(SR_ch, 0, VOLT_1_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 1e-6, RANGE_200_UA); // DVI_13_1, dvi2k //
////	Mux20_Open_relay(K50);
////	if (SR_Gnd_Res < .001 || SR_Gnd_Res > .040) // K50 should short SR pin to ground with less than 40mOhm resistance. //
////	{
////		//MessageBox(NULL, "Relay K50 on loadboard is not making good contact.", "Error", MB_OK|MB_TOPMOST);
////		sprintf(STRINGarray,"Relay K50 on loadboard is not making good contact.\n\n%f\n", SR_Gnd_Res);
////		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
////		g_Error_Flag = -196;
////	}
////
////	//MUX20_Test();
////
////	// Open all relays //
////	//Initialize_Relays();
////
////	// Connect Relays //
////	Close_relay(K2); //Connects Drain to DVI_11_0
////	Close_relay(K18); //Connects FW to DVI_11_1
////
////	// Setup Instruments //
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V); // OVI_1_1
////	VPIN_ovi->set_current(VPIN_ch, 300.0e-6, RANGE_300_UA);	
////	VO_dvi->set_voltage(VO_ch, 0.0, VOLT_5_RANGE); // DVI_9_0
////	VO_dvi->set_current(VO_ch, 300e-6, RANGE_300_UA);
////	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); // DVI_9_1
////	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
////	D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE); // DVI_21_0
////	IS_dvi2k->set_current(IS_ch, 200.0e-6, RANGE_200_UA);
////	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); // DVI_11_1
////	FW_dvi->set_current(FW_ch, 20.0e-6, RANGE_30_UA);
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
////	SR_dvi2k->set_current(SR_ch, 200.0e-6, RANGE_200_UA);
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2
////	FB_ovi->set_current(FB_ch, 30.0e-6, RANGE_30_UA);
////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V);
////	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
////	SCL_ovi->set_voltage(SCL_ch, 0, RANGE_5_V);	
////	SCL_ovi->set_current(SCL_ch, 29e-6, RANGE_30_UA);
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_50_RANGE);	
////	VBD_dvi->set_current(VBD_ch, 1e-3, RANGE_3_MA);	
////
////	//Drain Low Leakage test only (High leakage is already in BV_Drain function)
////	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 
////	D_dvi->set_current(D_ch, 300.0e-6, RANGE_300_UA); // Use 3mA to bring it to GND faster then smaller Range to 
////	wait.delay_10_us(150);	
////
////	ILL_D = D_dvi->measure_average(15);
////
////	// Normal Power Up //
////	D_dvi->set_voltage(D_ch, 5.5, VOLT_10_RANGE); 
////	wait.delay_10_us(50);
////	//If BPP is set to 5.5V, Vpin at 20V will fail (It has to go through the BPP power cycle)
////	VBPP_ramp_up(0, 5.5, 0.2); // Prevent overshoot //
////	wait.delay_10_us(50);
////	BPP_ovi->set_voltage(BPP_ch, 4.5, VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
////	wait.delay_10_us(100);
////	BPP_ovi->set_voltage(BPP_ch, 5.1, VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
////
////
////	// Vpin leakage //
////	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
////	//VPIN_ovi->set_voltage(VPIN_ch, 20.0, RANGE_20_V);	//Temporary use this to satisfy the high Vpin BV leakage test
////	//wait.delay_10_us(50);
////	//delay(1);
////	//ILH_UV = VPIN_ovi->measure_average(5);		
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_2_V); 
////	wait.delay_10_us(10);
////	ILL_UV = VPIN_ovi->measure_average(5);		
////
////	//Primary pins set to 0V
////	//BPP_ovi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 
////	VBPP_ramp_down(5.1, 0, 0.2); // Prevent undershoot //
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); 
////
////	BPS_dvi->set_current(BPS_ch, 10.0e-3, RANGE_30_MA);
////
////	// Prevent overshoot //
////	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
////	BPS_dvi->set_voltage(BPS_ch, 2, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 3, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 3.5, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 4, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 4.25, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 4.375, VOLT_5_RANGE);
////	wait.delay_10_us(20);
////	BPS_dvi->set_voltage(BPS_ch, 4.5, VOLT_5_RANGE);
////	wait.delay_10_us(100);
//////	ILH_BPS = BPS_dvi->measure_average(5);
////
////	//FW leakage (Make sure it's less than vBPS else it could provide charge to BPS easily)
////	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
////	FW_dvi->set_current(FW_ch, 30.0e-6, RANGE_30_UA);
////	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE);
////	wait.delay_10_us(205);
////	g_ILL_FW  = FW_dvi->measure_average(5);
////
////	//FW_BV has the leakage test in it already.
////	FW_dvi->set_current(FW_ch, 200e-6, RANGE_300_UA);
////	FW_dvi->set_voltage(FW_ch, 5, VOLT_5_RANGE); 
////	wait.delay_10_us(100);
////	ILH_FW  = FW_dvi->measure_average(5);		
////	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE);
////
////	// FB(COMP) leakage
////	CurrentClamp = 29.991e-6;
////	FB_ovi->set_current(FB_ch, CurrentClamp, RANGE_30_UA);
////	FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_CURRENT);
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); 
////	wait.delay_10_us(105);
////	g_ILL_FB = FB_ovi->measure_average(5);
////
////	// Make sure test limits are not wider than current clamp. //
////	UpperLimit = (func.dlog->tests[A_IIL_COMP].f_max_limit_val[0]); // Get upper test limit //
////	LowerLimit = (func.dlog->tests[A_IIL_COMP].f_min_limit_val[0]); // Get lower test limit //
////	if (UpperLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -209;
////			g_ILL_FB = -999;
////		}
////	}
////	if (UpperLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -209;
////			g_ILL_FB = -999;
////		}
////	}
////	if (LowerLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -209;
////			g_ILL_FB = -999;
////		}
////	}
////	if (LowerLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -209;
////			g_ILL_FB = -999;
////		}
////	}
////
////	FB_ovi->set_current(FB_ch, 300.0e-6, RANGE_300_UA);//FB goes to resistor divider
////	wait.delay_10_us(50);
////	FB_ovi->set_voltage(FB_ch, 5.5, RANGE_10_V); 
////	wait.delay_10_us(100);
////	g_ILH_FB = FB_ovi->measure_average(5); 
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); 
////
////	// Vout Leakage //
////	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_CURRENT);
////	wait.delay_10_us(205);
////	g_ILL_VO = VO_dvi->measure_average(5);		
////
////	//VO_dvi->set_voltage(VO_ch, 1, VOLT_5_RANGE);  
////	//wait.delay_10_us(20);
////	//ILH_VO = VO_dvi->measure_average(5);		
////	//VO_dvi->set_voltage(VO_ch, 0.0, VOLT_5_RANGE);  
////
////	//////SR Leakage (Low Leakage test only.  SR push/pull MOSFET kick in at High.  Couldn't measure leakage at vHigh)
////	////SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_CURRENT);
////	////SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE);
////	////delay(20);
////	////wait.delay_10_us(10000);
////	////ILL_SR = IS_dvi2k->measure_average(5);
////
////	////SR_dvi2k->set_voltage(SR_ch, 4.5, VOLT_10_RANGE); 
////	////wait.delay_10_us(50);
////	////ILH_SR	 = IS_dvi2k->measure_average(5);
////	////SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE);
////	
////	// IS Leakage //
////	IS_dvi2k->set_current(IS_ch, 200.0e-6, RANGE_200_UA);
////	IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_CURRENT);
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);	// DVI_21_0
////	wait.delay_10_us(205);
////	g_ILL_IS = IS_dvi2k->measure_average(5);
////
////	//IS_dvi2k->set_voltage(IS_ch, 4.5, VOLT_10_RANGE); 
////	//wait.delay_10_us(50);
////	//ILH_IS = IS_dvi2k->measure_average(5);
////	//IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_10_RANGE);
////
//////============================================Inno VI pins SDA/SCL/VB pin=====================================================//
////
////	// When DOPL bits trimmed, the VBD pin goes high when BPS is powered up, 
////	// causing leakage failure.  Need to reduce BPS to prevent VBD from going high. //
////	if(gTrim_SdwReg22_Trimops) // DOPL //
////	{
////		VBPS_ramp_down(4.5, 3, 0.1);
////		BPS_dvi->set_voltage(BPS_ch, 3, VOLT_5_RANGE);
////	}
////
////	// VB/D //
////	Mux20_Open_relay(K36);//Make sure VB/D is connected to DVI17 Ch.0
////	VO_dvi->set_voltage(VO_ch, 5.0, VOLT_5_RANGE); // DVI_9_0
////	VO_dvi->set_current(VO_ch, 29.0e-3, RANGE_30_MA);//~needs 19mA
////	VBD_dvi->set_voltage(VBD_ch, 30.0, VOLT_50_RANGE);	
////	VBD_dvi->set_current(VBD_ch, 1e-3, RANGE_3_MA);	
////	VBD_dvi->set_meas_mode(VBD_ch,DVI_MEASURE_CURRENT);
////	wait.delay_10_us(100);
////	g_ILH_VBD = VBD_dvi->measure_average(5);
////
////	VBD_dvi->set_voltage(VBD_ch, 15.0, VOLT_50_RANGE);
////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA);//Change ranges away from abs. max to avoid glitch
////	
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_50_RANGE);
////	wait.delay_10_us(120);
////	g_ILL_VBD = VBD_dvi->measure_average(5);	
////
////	// Return to previous //
////	// When DOPL bits trimmed, the VBD pin goes high when BPS is powered up, 
////	// causing leakage failure. //
////	if(gTrim_SdwReg22_Trimops) // DOPL //
////	{
////		VBPS_ramp_up(3, 4.5, 0.1);
////		BPS_dvi->set_voltage(BPS_ch, 4.5, VOLT_5_RANGE);
////	}
////
////	Mux20_Open_relay(K37);//Make sure OVI3 CH.0 connected to SDA
////	wait.delay_10_us(200);
////	Mux20_Close_relay(K39);
////	wait.delay_10_us(200);
////
////	// g_ILH_SDA //
////	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
////	SDA_ovi->set_voltage(SDA_ch, 3.3, RANGE_5_V);	
////	wait.delay_10_us(30);
////	CurrentClamp = 28e-6;
////	SDA_ovi->set_current(SDA_ch, CurrentClamp, RANGE_30_UA);
////	SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_CURRENT);
////	wait.delay_10_us(100);
////	g_ILH_SDA = SDA_ovi->measure_average(5);
////	
////	// Make sure test limits are not wider than current clamp. //
////	UpperLimit = (func.dlog->tests[A_IIH_SDA].f_max_limit_val[0]); // Get upper test limit //
////	LowerLimit = (func.dlog->tests[A_IIH_SDA].f_min_limit_val[0]); // Get lower test limit //
////	if (UpperLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -208;
////			g_ILH_SDA = -999;
////		}
////	}
////	if (UpperLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -208;
////			g_ILH_SDA = -999;
////		}
////	}
////	if (LowerLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -208;
////			g_ILH_SDA = -999;
////		}
////	}
////	if (LowerLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -208;
////			g_ILH_SDA = -999;
////		}
////	}
////
////	// g_ILL_SDA //
////	SDA_ovi->set_current(SDA_ch, 2.9e-3, RANGE_3_MA);
////	SDA_ovi->set_voltage(SDA_ch, 0, RANGE_5_V);//Change current ranges away from abs max to avoid glitch	
////	wait.delay_10_us(50);
////	CurrentClamp = 2.991e-6;
////	SDA_ovi->set_current(SDA_ch, CurrentClamp, RANGE_3_UA);
////	wait.delay_10_us(100);
////	g_ILL_SDA = SDA_ovi->measure_average(5);
////
////	// Make sure test limits are not wider than current clamp. //
////	UpperLimit = (func.dlog->tests[A_IIL_SDA].f_max_limit_val[0]); // Get upper test limit //
////	LowerLimit = (func.dlog->tests[A_IIL_SDA].f_min_limit_val[0]); // Get lower test limit //
////	if (UpperLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -207;
////			g_ILL_SDA = -999;
////		}
////	}
////	if (UpperLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -207;
////			g_ILL_SDA = -999;
////		}
////	}
////	if (LowerLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -207;
////			g_ILL_SDA = -999;
////		}
////	}
////	if (LowerLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -207;
////			g_ILL_SDA = -999;
////		}
////	}
////
////	Mux20_Open_relay(K39);
////	Mux20_Close_relay(K37);
////	delay(2);
////
////	//SCL
////	SCL_ovi->set_voltage(SCL_ch, 3.3, RANGE_5_V);	
////	wait.delay_10_us(25);
////	SCL_ovi->set_current(SCL_ch, 29e-6, RANGE_30_UA);
////	SCL_ovi->set_meas_mode(SCL_ch, OVI_MEASURE_CURRENT);
////	wait.delay_10_us(150);
////	g_ILH_SCL = SCL_ovi->measure_average(5);
////
////	// Ramp down- prevent undershoot //
////	SCL_ovi->set_voltage(SCL_ch, 1.5, RANGE_5_V);//Change current ranges away from abs max to avoid glitch	
////	wait.delay_10_us(10);
////	SCL_ovi->set_voltage(SCL_ch, 0.6, RANGE_5_V);
////	wait.delay_10_us(10);
////	SCL_ovi->set_voltage(SCL_ch, 0.3, RANGE_5_V);
////	wait.delay_10_us(10);
////	SCL_ovi->set_voltage(SCL_ch, 0.15, RANGE_5_V);
////	wait.delay_10_us(10);
////	SCL_ovi->set_voltage(SCL_ch, 0, RANGE_5_V);
////	wait.delay_10_us(20);
////	CurrentClamp = 2.991e-6;
////	SCL_ovi->set_current(SCL_ch, CurrentClamp, RANGE_3_UA);
////	wait.delay_10_us(100);
////	g_ILL_SCL = SCL_ovi->measure_average(5);
////
////	// Make sure test limits are not wider than current clamp. //
////	UpperLimit = (func.dlog->tests[A_IIL_SCL].f_max_limit_val[0]); // Get upper test limit //
////	LowerLimit = (func.dlog->tests[A_IIL_SCL].f_min_limit_val[0]); // Get lower test limit //
////	if (UpperLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -206;
////			g_ILL_SCL = -999;
////		}
////	}
////	if (UpperLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -206;
////			g_ILL_SCL = -999;
////		}
////	}
////	if (LowerLimit < 0)
////	{
////		if((-1*CurrentClamp) > LowerLimit)
////		{	
////			g_Error_Flag = -206;
////			g_ILL_SCL = -999;
////		}
////	}
////	if (LowerLimit > 0)
////	{
////		if(CurrentClamp < UpperLimit)
////		{	
////			g_Error_Flag = -206;
////			g_ILL_SCL = -999;
////		}
////	}
////
////	// Powerdown //
////	Open_relay(K2);
////	Open_relay(K18);
////	Mux20_Open_relay(K37);
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_10_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1, prevent undershoot //
////	wait.delay_10_us(4);
////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////	wait.delay_10_us(4);
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
////	uVCC_ovi->set_voltage(uVCC_ch, 1.0, RANGE_10_V); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	wait.delay_10_us(30);
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
////	wait.delay_10_us(100);
////	uVCC_ramp_down(1, 0, .05);
////	BPS_dvi->set_current(BPS_ch, 30.0e-3, RANGE_30_MA);
////	VBPS_ramp_down(3, 0, 200e-3);
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2 //
////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE);
////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////	wait.delay_10_us(200); // Wait for relays //
////
////
////	//Datalog
////	PiDatalog(func, A_FB_Buff_Check, FB_Buff_Check, 31, POWER_UNIT);
////	PiDatalog(func, A_FB_Buff_Value, FB_Buff_Value, 31, POWER_UNIT);
////	PiDatalog(func, A_SR_Gnd_Res, SR_Gnd_Res, 31, POWER_MILLI);
////	//PiDatalog(func, A_MUX20_Check, MUX20_Check, 31, POWER_UNIT);
////	PiDatalog(func, A_Silicon_Rev, g_SiliconRev_Sec, 31, POWER_UNIT);
////	PiDatalog(func, A_IIL_D, ILL_D, 11, POWER_MICRO);
////	//PiDatalog(func, A_ILH_D, ILH_D, 11, POWER_MICRO);
////
////	//PiDatalog(func, A_IIL_BPP, ILL_BPP, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_BPP, ILH_BPP, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIL_UV, ILL_UV, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_UV, ILH_UV, 11, POWER_MICRO); // Not needed, covered by BV_Vpin. //
////
////	PiDatalog(func, A_IIL_FW, g_ILL_FW, 11, POWER_MICRO);
////	PiDatalog(func, A_IIH_FW, ILH_FW, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIL_VO, g_ILL_VO, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_VO, ILH_VO, 11,	POWER_MICRO);
////
////	// The SR current will sink to the GND. 
////	//PiDatalog(func, A_ILL_SR, ILL_SR, 11,	POWER_MICRO);
////	//PiDatalog(func, A_ILH_SR, ILH_SR, 11,	POWER_MICRO);
////
////	//PiDatalog(func, A_IIL_BPS, ILL_BPS, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_BPS, ILH_BPS, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIL_COMP,	g_ILL_FB, 11, POWER_MICRO);
////	PiDatalog(func, A_IIH_COMP,	g_ILH_FB, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIL_IS, g_ILL_IS, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_IS, ILH_IS, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIH_VBD,	g_ILH_VBD, 11, POWER_MICRO);
////	PiDatalog(func, A_IIL_VBD,	g_ILL_VBD, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIH_SDA,	g_ILH_SDA, 11, POWER_MICRO);
////	PiDatalog(func, A_IIL_SDA,	g_ILL_SDA, 11, POWER_MICRO);
////
////	PiDatalog(func, A_IIH_SCL,	g_ILH_SCL, 11, POWER_MICRO);
////	PiDatalog(func, A_IIL_SCL,	g_ILL_SCL, 11, POWER_MICRO);
////
////	//PiDatalog(func, A_IIL_uVCC, IIL_uVCC, 11, POWER_MICRO);
////	//PiDatalog(func, A_IIH_uVCC, IIH_uVCC, 11, POWER_MICRO);
////
////	if (PiGetAnyFailStatus())
////	{
////		AbortTest = true;
////		delay(50); // Wait 50ms if failing continuity for Handler to respond properly
////	}
////
//////	Power_Down_Everything();
//////	Open_All_Relays();
////
////
////	// Test Time End //
////	if (g_TstTime_Enble_P)
////	{
////		g_endtime = g_mytimer.GetElapsedTime();
////		Leakage_TT = (g_endtime - g_begintime)*1e-6;
////		PiDatalog(func, A_Leakage_TT, Leakage_TT, 11, POWER_MILLI);
////	}	
////
////	// Check any test failed //
////	if (PiGetAnyFailStatus())		
////	{
////		g_PartFailed = 1;
////	}
}
