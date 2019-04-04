//==============================================================================
// EEPROM_Write.cpp (User function)
// 
//    void EEPROM_Write_user_init(test_function& func)
//    void EEPROM_Write(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "EEPROM_Write.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_Write_user_init(test_function& func)
{
	EEPROM_Write_params *ours;
    ours = (EEPROM_Write_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_Write(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_Write_params *ours;
    ours = (EEPROM_Write_params *)func.params;

	// Increment function number //
	gFuncNum++;

if(g_Trim_Enable_S)
{

	float vVR_set=15;
	float vHSG=0;
	float vVR_Burn_th = 0;
	int i=0;
	//Secondary.
	//HSG 
	HSG_ovi->set_current(HSG_ch, 0.001e-6, RANGE_3_UA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	//B:  disconnect OVI and connect to 2nF to GND.
	B_ovi3->set_current(B_ch1, 300e-6, RANGE_300_UA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	//FW = 0V/30mA
	FW_ovi3->set_current(FW_ch, 30e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	//FB 
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	//IS = 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);
	//SDA will be at 3.3V/30mA for I2C
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	//SCL will be at 3.3V/30mA for I2C
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	//BPS will be Hiz
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	//HBP will be Hiz.
	HBP_dvi2k->set_current(HBP_ch, 20e-3, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	//VR will be set at 15V.  Test plan requires at 20V.
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect HBP & BPs and use VR to powerup 2ndary.
	HBP_dvi2k->open_relay(CONN_FORCE0);
	BPS_dvi->open_relay(CONN_FORCE0);

	Open_relay(K2_HSG_SPI_TB);      //Keep OVI_1_0 on HSG.
	Close_relay(K1_HSG_SPI_RB);     //Connect pullup R on HSG.
	Close_relay(K3_B_SPI_TB);		//Connect 2nF to B
	//Disonnect Pullup R from TS and UV pins
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	//Connect Pullup R to SCL & SDA
	Close_relay(K1_SDA_SPI_TB);
	Close_relay(K1_SCL_SPI_TB);
	//Disconnect DSM CLK & Data from primary pins: TS & UV
	//Connect DSM CLK & Data to secondary:         SCL & SDA
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Close_relay(K2_DSM_TB);
	Close_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	//1.	vFB = 1.25V
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
	delay(1);

	//2.	VR = 15V 
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	//Require >30mA else VR -> 10V, droop, then start rising with weird ramps
	VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
	delay(10);

	//Need to close K1_SDA.  Manually short due to SPI relay driver issues.

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); // DVI_21_1
	delay(5);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter TM
	Analog_TM_Enable_Secondary();

	//	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
	//											  (This Test Mode disable 
	//	i.	0x00 0x62 write 0x88 0x00
	DSM_I2C_Write('w', 0x62, 0x0088);

	//	ZTMC_ana_EN and Core_en
	//	i.	0x00 0x40 write 0x06 0x00
	DSM_I2C_Write('w', 0x40, 0x0006);

	//	ZVtrim_comp (Comp out on HSG)
	//		0x00 0x46 write 0x00 0xB8
	//	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
	DSM_I2C_Write('w', 0x46, 0xB800);

	//Loading all of the bits to EEprom.
	Program_Trim_Register(g_S_TrimRegister);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Write whats programmed to the EEprom register to EEprom Cell.	(0x00 0x5C write 0x01)
	DSM_I2C_Write('b', 0x5C, 0x01);
	// ZTMC_ana_Vprog_En and ZTMC_trim_EN_vDDA	(0x00 0x44 write 0x05 0x00)
	DSM_I2C_Write('w', 0x44, 0x0005);
	//Raise VR > 18V until HSG is toggling to burn programmed trimcodes to EEprom cell.  
	//										(DC voltage to determine switching or not) 
	VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
	delay(1);
	HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_VOLTAGE, AUTORANGE);
	
	while (vVR_set < 21)
	{
		vVR_set = vVR_set + i*0.2;
		VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
		wait.delay_10_us(10);
		vHSG = HSG_ovi->measure_average(5);
		if(vHSG > 2) //exit while loop
		{
			vVR_Burn_th = vVR_set+i*0.2;
			break;
		}
		i++;
	}

	VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
	wait.delay_10_us(200);
	// Stop/End Burn EEprom
	//  0x00 0x5C write 0x00
	DSM_I2C_Write('b', 0x5C, 0x00);
	// 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
	DSM_I2C_Write('w', 0x44, 0x0000);
	}
	//-------------------------------------
	// Trim/Burn EEprom for Secondary *END
	//--------------------------------------

//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//Powerdown
	//-------------------------------------------------------------------------------
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	VR_dvi->set_voltage(VR_ch, 5, VOLT_50_RANGE); 
	wait.delay_10_us(200);
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_1_RANGE);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); 
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); 
	wait.delay_10_us(10);
	SDA_ovi3->set_current(SDA_ch, 0.01e-6, RANGE_30_MA);	        
	SCL_ovi3->set_current(SCL_ch, 0.01e-6, RANGE_30_MA);				
	wait.delay_10_us(10);

	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(500);

	HBP_dvi2k->close_relay(CONN_FORCE0);
	BPS_dvi->close_relay(CONN_FORCE0);
	Open_relay(K1_SDA_SPI_TB);       //Disconnect pullup R from SDA.
	Open_relay(K1_SCL_SPI_TB);       //Disconnect pullup R from SCL
	Open_relay(K2_DSM_TB);           //Disconnect DSM SDA from DUT SDA
	Open_relay(K4_DSM_TB);           //Disconnect DSM SCL from DUT SCL
	Open_relay(K2_HSG_SPI_TB);		 //Reconnect OVI_1_0 to HSG
	Open_relay(K2_B_SPI_TB);         //Reconnect OVI_3_1 to B.
	Open_relay(K3_B_SPI_TB);		 //Disconnect 2nF from B
	Open_relay(K3_HSG_SPI_TB);       //Disconnect 2nF from HSG
	Open_relay(K1_HSG_SPI_RB);		 //Disconnect pullup R from HSG.
	Open_relay(K1_FB_SPI_TB);		 //Reconnect OVI to FB
	wait.delay_10_us(250);





/*
	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_EEPROM_Wrt, gFuncNum, 25, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	// Skip trimming if g_Sim_Enable_P set //
	if (g_Sim_Enable_P == 0)
		return;

	if (g_Fn_EEPROM_Write == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	// Test Names //
	int EEPROM_Write = 1;
	float EEPROM_Write_TT = 0;

	// Declare Variables //
	int NObin[1] = {0}; // Place holder //
	int NOhex = 0; // Place holder //
	int ReadResult[112] = {0};
	float Vforce = 0;
	int READ13_word[16] = {0};
	int READ14_word[16] = {0};
	int READ15_word[16] = {0};
	int READ16_word[16] = {0};
	int READ17_word[16] = {0};
	int READ18_word[16] = {0};
	int READ19_word[16] = {0};
	int READ56_word[16] = {0};
	int READ57_word[16] = {0};
	int READ58_word[16] = {0};
	int READ59_word[16] = {0};
	int READ60_word[16] = {0};
	int READ61_word[16] = {0};
	int READ62_word[16] = {0};
	int i = 0;
	Pulse pulse;


	// Open all relays //
	Initialize_Relays();

	// Initialize Instruments //
	Initialize_Instruments();

	// Drain //
	Close_relay(K2);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //

	// BPP //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //

	// V pin //
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //

	// FW //
	Close_relay(K18); // Connect FW to DVI_11_1 //
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 300e-3, RANGE_300_MA); // DVI_11_1 //

	// SR //
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //

	// BPS //
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //

	// IS //
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
	
	// FB (COMP) //
	FB_ovi->disconnect(2);

	// VBD //
	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
	wait.delay_10_us(25); // Prevent glitch //
	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //

	// uVCC //
	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 3.3; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

	// SDA //
	Mux20_Close_relay(K64); // SDA pullup to 3.3V through 1.5kohm resistor. //
	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
	Mux20_Close_relay(K37); // Disconnect ovi from SDA. //
	Mux20_Close_relay(K38); // Connect SDA and SCL to DDD. //
	Mux20_Close_relay(K40); // Connect SDA and SCL to DDD. //

	// SCL //
	Mux20_Close_relay(K39); // Disconnect ovi from SCL. //
	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
	
	// Set DDD for I2C. //
	ddd_7->ddd_set_clock_period(g_Dclk_I2C);	
	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
	
	// Wait for relays //
	wait.delay_10_us(200);

	// Powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
	
	// Wait //
	wait.delay_10_us(100);

	// Must Erase before Write //
	// Erase EEPROM with I2C //
	Write_Byte(g_EEP_CMD, 0x03, NObin, HEX); // Erase EEPROM //

	// Wait //
	wait.delay_10_us(100);

	// Ramp BPS up to 7V //
	Vforce = gVBPS_final;
	while(Vforce < 7.0)
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce += 0.1;
	}
	BPS_dvi->set_voltage(BPS_ch, 7.0, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(2);

	// Bring up Erase voltage on FW pin //
	// Ramp up to 24V in ~2msec //
	Vforce = 0;
	while(Vforce < 24.0)
	{
		FW_dvi->set_voltage(FW_ch, Vforce, VOLT_50_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		Vforce += 0.120;
	}
	FW_dvi->set_voltage(FW_ch, 24.0, VOLT_50_RANGE); // DVI_11_1 //
	//wait.delay_10_us(1);

	// Hold 24V for 4msec //
	wait.delay_10_us(400);

	// Ramp down to 0V in ~2msec //
	Vforce = 24;
	while(Vforce > 0)
	{
		FW_dvi->set_voltage(FW_ch, Vforce, VOLT_50_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		Vforce -= 0.120;
	}
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	wait.delay_10_us(2);

	// Ramp BPS down to gVBPS_final //
	Vforce = 7.0;
	while(Vforce > gVBPS_final)
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce -= 0.02;
	}
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(2);

	// Terminate Erase command by issuing another EEP_CMD command (any command, we use Read command). 
	// This command’s function is only for terminating erasing. //
	Write_Byte(g_EEP_CMD, 0x00, NObin, HEX); // Terminate Erase with Read command //

	// Load final shadow register. // //
	// The g_ShadowRegister[] array will be written to the EEPROM //
	LoadShadowRegister();

	// Write EEPROM with I2C //
	Write_Byte(g_EEP_CMD, 0x01, NObin, HEX); // Write EEPROM //
//	wait.delay_10_us(50);

	// Ramp BPS up to 7V //
	Vforce = gVBPS_final;
	while(Vforce < 7.0)
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce += 0.1;
	}
	BPS_dvi->set_voltage(BPS_ch, 7.0, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(2);

	// Bring up Write voltage on FW pin //
	// Ramp up to 18V in ~2msec //
	Vforce = 0;
	while(Vforce < 18.0)
	{
		FW_dvi->set_voltage(FW_ch, Vforce, VOLT_50_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		Vforce += 0.09;
	}
	FW_dvi->set_voltage(FW_ch, 18.0, VOLT_50_RANGE); // DVI_11_1 //
	//wait.delay_10_us(1);

	// Hold 18V for 2msec //
	wait.delay_10_us(200);

	// Ramp down to 0V in ~2msec //
	Vforce = 18;
	while(Vforce > 0)
	{
		FW_dvi->set_voltage(FW_ch, Vforce, VOLT_50_RANGE); // DVI_11_1 //
		wait.delay_10_us(1);
		Vforce -= 0.09;
	}
	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
	wait.delay_10_us(2);

	// Ramp BPS down to gVBPS_final //
	Vforce = 7.0;
	while(Vforce > gVBPS_final)
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce -= 0.02;
	}
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(2);

	// Terminate Write command by issuing another EEP_CMD command (any command, we use Read command). 
	// This command’s function is only for terminating writing. //
	Write_Byte(g_EEP_CMD, 0x00, NObin, HEX); // Terminate Write with Read command //
	wait.delay_10_us(2);

	// Power down //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //

	// Ramp BPS down to gVBPS_final //
	Vforce = gVBPS_final;
	while(Vforce > 0)
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce -= 0.02;
	}
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(200);

	// Power back up and make sure EEPROM was written correctly. //
	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //

	// Ramp BPS up to prevent overshoot //
	Vforce = 0;
	while(Vforce < (gVBPS_M_Init - 200e-3))
	{
		BPS_dvi->set_voltage(BPS_ch, Vforce, VOLT_10_RANGE); // DVI_9_1 //
		wait.delay_10_us(1);
		Vforce += 0.1;
	}
	BPS_dvi->set_voltage(BPS_ch,gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_5_RANGE); // DVI_9_0 //
	wait.delay_10_us(100);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //

	// I2C into test mode. //  
	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
	Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //

	// Read the shadow register. //
	Write_Word(g_RDADDR, g_READ56, NObin, HEX);// SREG0.  Shadow register. //
	Read_Word(g_RDADDR, READ56_word);// SREG0.  Shadow register. //

	Write_Word(g_RDADDR, g_READ57, NObin, HEX);// SREG1.  Shadow register. //
	Read_Word(g_RDADDR, READ57_word);// SREG1.  Shadow register. //

	Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
	Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //

	Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
	Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //

	Write_Word(g_RDADDR, g_READ60, NObin, HEX); // SREG4.  Shadow register. //
	Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //

	Write_Word(g_RDADDR, g_READ61, NObin, HEX); // SREG5.  Shadow register. //
	Read_Word(g_RDADDR, READ61_word); // SREG5.  Shadow register. //

	Write_Word(g_RDADDR, g_READ62, NObin, HEX); // SREG6.  Shadow register. //
	Read_Word(g_RDADDR, READ62_word); // SREG6.  Shadow register. //

	// Save results that were read out of shadow register //
	ReadResult[0] = READ56_word[0];
	ReadResult[1] = READ56_word[1];
	ReadResult[2] = READ56_word[2];
	ReadResult[3] = READ56_word[3];
	ReadResult[4] = READ56_word[4];
	ReadResult[5] = READ56_word[5];
	ReadResult[6] = READ56_word[6];
	ReadResult[7] = READ56_word[7];
	ReadResult[8] = READ56_word[8];
	ReadResult[9] = READ56_word[9];
	ReadResult[10] = READ56_word[10];
	ReadResult[11] = READ56_word[11];
	ReadResult[12] = READ56_word[12];
	ReadResult[13] = READ56_word[13];
	ReadResult[14] = READ56_word[14];
	ReadResult[15] = READ56_word[15];
	ReadResult[16] = READ57_word[0];
	ReadResult[17] = READ57_word[1];
	ReadResult[18] = READ57_word[2];
	ReadResult[19] = READ57_word[3];
	ReadResult[20] = READ57_word[4];
	ReadResult[21] = READ57_word[5];
	ReadResult[22] = READ57_word[6];
	ReadResult[23] = READ57_word[7];
	ReadResult[24] = READ57_word[8];
	ReadResult[25] = READ57_word[9];
	ReadResult[26] = READ57_word[10];
	ReadResult[27] = READ57_word[11];
	ReadResult[28] = READ57_word[12];
	ReadResult[29] = READ57_word[13];
	ReadResult[30] = READ57_word[14];
	ReadResult[31] = READ57_word[15];
	ReadResult[32] = READ58_word[0];
	ReadResult[33] = READ58_word[1];
	ReadResult[34] = READ58_word[2];
	ReadResult[35] = READ58_word[3];
	ReadResult[36] = READ58_word[4];
	ReadResult[37] = READ58_word[5];
	ReadResult[38] = READ58_word[6];
	ReadResult[39] = READ58_word[7];
	ReadResult[40] = READ58_word[8];
	ReadResult[41] = READ58_word[9];
	ReadResult[42] = READ58_word[10];
	ReadResult[43] = READ58_word[11];
	ReadResult[44] = READ58_word[12];
	ReadResult[45] = READ58_word[13];
	ReadResult[46] = READ58_word[14];
	ReadResult[47] = READ58_word[15];
	ReadResult[48] = READ59_word[0];
	ReadResult[49] = READ59_word[1];
	ReadResult[50] = READ59_word[2];
	ReadResult[51] = READ59_word[3];
	ReadResult[52] = READ59_word[4];
	ReadResult[53] = READ59_word[5];
	ReadResult[54] = READ59_word[6];
	ReadResult[55] = READ59_word[7];
	ReadResult[56] = READ59_word[8];
	ReadResult[57] = READ59_word[9];
	ReadResult[58] = READ59_word[10];
	ReadResult[59] = READ59_word[11];
	ReadResult[60] = READ59_word[12];
	ReadResult[61] = READ59_word[13];
	ReadResult[62] = READ59_word[14];
	ReadResult[63] = READ59_word[15];
	ReadResult[64] = READ60_word[0];
	ReadResult[65] = READ60_word[1];
	ReadResult[66] = READ60_word[2];
	ReadResult[67] = READ60_word[3];
	ReadResult[68] = READ60_word[4];
	ReadResult[69] = READ60_word[5];
	ReadResult[70] = READ60_word[6];
	ReadResult[71] = READ60_word[7];
	ReadResult[72] = READ60_word[8];
	ReadResult[73] = READ60_word[9];
	ReadResult[74] = READ60_word[10];
	ReadResult[75] = READ60_word[11];
	ReadResult[76] = READ60_word[12];
	ReadResult[77] = READ60_word[13];
	ReadResult[78] = READ60_word[14];
	ReadResult[79] = READ60_word[15];
	ReadResult[80] = READ61_word[0];
	ReadResult[81] = READ61_word[1];
	ReadResult[82] = READ61_word[2];
	ReadResult[83] = READ61_word[3];
	ReadResult[84] = READ61_word[4];
	ReadResult[85] = READ61_word[5];
	ReadResult[86] = READ61_word[6];
	ReadResult[87] = READ61_word[7];
	ReadResult[88] = READ61_word[8];
	ReadResult[89] = READ61_word[9];
	ReadResult[90] = READ61_word[10];
	ReadResult[91] = READ61_word[11];
	ReadResult[92] = READ61_word[12];
	ReadResult[93] = READ61_word[13];
	ReadResult[94] = READ61_word[14];
	ReadResult[95] = READ61_word[15];
	ReadResult[96] = READ62_word[0];
	ReadResult[97] = READ62_word[1];
	ReadResult[98] = READ62_word[2];
	ReadResult[99] = READ62_word[3];
	ReadResult[100] = READ62_word[4];
	ReadResult[101] = READ62_word[5];
	ReadResult[102] = READ62_word[6];
	ReadResult[103] = READ62_word[7];
	ReadResult[104] = READ62_word[8];
	ReadResult[105] = READ62_word[9];
	ReadResult[106] = READ62_word[10];
	ReadResult[107] = READ62_word[11];
	ReadResult[108] = READ62_word[12];
	ReadResult[109] = READ62_word[13];
	ReadResult[110] = READ62_word[14];
	ReadResult[111] = READ62_word[15];

	// Compare read results to expected. //
	EEPROM_Write = 1;
	for (i=0;i<112;i++)
	{
		if (ReadResult[i] != g_ShadowRegister[i])
		{
			EEPROM_Write = -999;
			g_Error_Flag = -125;
		}
	}

	// Power down //
	Open_relay(K2);
	Open_relay(K18);
	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
	VO_dvi->set_voltage(VO_ch, 0, VOLT_10_RANGE);
	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	uVCCrampDown(1, 0, 0.1);
	FB_ovi->connect(2);
	VBD_dvi->set_voltage(VBD_ch, 1, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	wait.delay_10_us(20);
	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
	//VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
	//uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
	Mux20_Open_relay(K64);
	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
	Mux20_Open_relay(K37);
	Mux20_Open_relay(K38);
	Mux20_Open_relay(K40);
	Mux20_Open_relay(K39);
	Mux20_Open_relay(K50); 
	ddd_7->ddd_set_clock_period(Dclk_period);
	ddd_7->ddd_set_voltage_ref(DDD_Vref);

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 4.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(200); // Wait for relays //

	// Datalog //
	PiDatalog(func, A_EEPROM_Write, EEPROM_Write, 25, POWER_UNIT);
	
	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		EEPROM_Write_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_EEPROM_Write_TT, EEPROM_Write_TT, 25, POWER_MILLI);
	}

	// Check any test failed //
	if (PiGetAnyFailStatus())		
	{
		g_PartFailed = 1;
	}
*/
}
