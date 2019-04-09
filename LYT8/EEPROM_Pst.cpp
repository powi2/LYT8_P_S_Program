//==============================================================================
// EEPROM_Pst.cpp (User function)
// 
//    void EEPROM_Pst_user_init(test_function& func)
//    void EEPROM_Pst(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "EEPROM_Pst.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_Pst_user_init(test_function& func)
{
	EEPROM_Pst_params *ours;
    ours = (EEPROM_Pst_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_Pst(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_Pst_params *ours;
    ours = (EEPROM_Pst_params *)func.params;

	gFuncNum++;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_Eeprom_Pst, gFuncNum, 27, POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	
	// Test Time Begin //
	if (g_TstTime_Enble_P)
		g_begintime = g_mytimer.GetElapsedTime();

	int		func_fail_bin = ours->fail_bin;

	int	E0_data_P	=0,
		E2_data_P	=0,
		E4_data_P	=0,
		E6_data_P	=0,
		E8_data_P	=0;
		
	int	E0_data_S	=0,
		E2_data_S	=0,
		E4_data_S	=0,
		E6_data_S	=0,
		E8_data_S	=0;
			

	float	EEPROM_Pst_TT	=0;
	int		i = 0;
	int		start_datalog_P = A_E00_Si_ID_0_P;
	int		EEpr_P[80] = {0};
	int		start_datalog_S = A_E0_Si_ID_0_S;
	int		EEpr_S[80] = {0};
	int     EEpr_Chk_P = 0;
	int     EEpr_Chk_S = 0;

	//-----------------------------------------------------------------------------------------------------------------
	//Primary Die ID Reading
	//------------------------------------------------------------------------------------------------------------------
	//Test conditions:  D = 0, BPP = 5V, wait 150us.  Reading I2C.

	//Drain = 0V
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
	//BPP = 0V
	BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1

	////////////////////////////////////////////////////////////////////////////////////////////////
	//This section is for the primary I2C

	//TS = 0V via pullup resistor. Ready for I2C.
	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	//Connect Pullup R to TS and UV pins
	mux_20->close_relay(MUX_3_2);	//Connect Pullup R to TS pin.
	mux_20->close_relay(MUX_1_3);	//Connect Pullup R to UV pin.
	//Connect DSM CLK & Data to primary pins: TS & UV
	mux_14->close_relay(MUX_1_1);
	mux_14->close_relay(MUX_1_3);
	mux_14->open_relay(MUX_1_2);
	mux_14->open_relay(MUX_1_4);
	delay(5);
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	float vpullup_P=3.3;	//5.0V does not work

	PowerUp_I2C_P();
	EEPROM_Read_Enable_P();

	//Read data out from EEPROM registers 0xC0
	E0_data_P = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
	E2_data_P = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
	E4_data_P = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
	E6_data_P = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
	E8_data_P = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

	//Decode data from 0xCX and assign to EEpromArray for datalogging.
	EEprcode_2_EEprArray(E0_data_P, EEpr_P, 0);
	EEprcode_2_EEprArray(E2_data_P, EEpr_P, 16);
	EEprcode_2_EEprArray(E4_data_P, EEpr_P, 32);
	EEprcode_2_EEprArray(E6_data_P, EEpr_P, 48);
	EEprcode_2_EEprArray(E8_data_P, EEpr_P, 64);

	//Power down Primary from here.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);

	for(i=0;i<80;i++)
	{
		PiDatalog(func, start_datalog_P+i, EEpr_P[i], func_fail_bin, POWER_UNIT);
	}
	//---------------------------------------------------------------------------
	//Power Down Primary
	//Power down.
	//---------------------------------------------------------------------------
	//SDA = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

	//SCL = 3.3V via pullup resistor. Ready for I2C.
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	delay(5);
	dvi_9->set_current(DVI_CHANNEL_1, 30e-3, RANGE_300_MA);
	dvi_9->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE); // DVI_11_1
	delay(10);

	mux_14->open_relay(MUX_1_2);
	mux_14->open_relay(MUX_1_4);
	delay(5);

	//Set pullup voltage at TS @ UV pins.
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(10);

	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
	wait.delay_10_us(100);

	//Connect Pullup R to TS pin.
	mux_20->open_relay(MUX_3_2);

	//Connect Pullup R to UV pin.
	mux_20->open_relay(MUX_1_3);

	//Disconnect DSM from Primary.
	mux_14->open_relay(MUX_1_1);	//Primary disconnect from DSM
	mux_14->open_relay(MUX_1_3);	//Primary disconnect from DSM
	delay(2);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect DVI_13 from HBP.
	dvi_13->disconnect(CONN_FORCE0);
	delay(5);

	//SDA & SCL set to 0V
	//SDA = 0V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_current(SDA_ch, 0.1e-3, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

	//SCL = 0V via pullup resistor. Ready for I2C.
	SCL_ovi3->set_current(SCL_ch, 0.1e-3, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//----------------------------------------------------------------------------------------------
	//Start Secondary 
	//---------------------------------------------------------------------------------------------
	PowerUp_I2C_S();
	
	//Sometimes, DSM I2C can't be written correctly the first time.
	//Change the DSM timeout to 1ms since the default timeout is approximately 35ms.
	//g_Debug = 1;
	DSM_set_I2C_timeout(0, 1);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter test mode
	Analog_TM_Enable_Secondary();
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	DSM_I2C_SREG0_0x7070();			//Get ready for any data to move to read address 0x00
DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Read data out from EEPROM registers 0xC0
	E0_data_S = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
	E2_data_S = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
	E4_data_S = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
	E6_data_S = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
	E8_data_S = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

	//Decode data from 0xCX and assign to EEpromArray for datalogging.
	EEprcode_2_EEprArray(E0_data_S, EEpr_S, 0);
	EEprcode_2_EEprArray(E2_data_S, EEpr_S, 16);
	EEprcode_2_EEprArray(E4_data_S, EEpr_S, 32);
	EEprcode_2_EEprArray(E6_data_S, EEpr_S, 48);
	EEprcode_2_EEprArray(E8_data_S, EEpr_S, 64);

	//Power down secondary from here.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);

	//Not sure why there is a glitch on FW when powering down.
	FW_ovi3->set_voltage(FW_ch, 0.5, VOLT_5_RANGE); 

	//Powerdown Secondary.
	VR_dvi->set_voltage(VR_ch, 5.0, VOLT_50_RANGE); 
	wait.delay_10_us(50);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_5_RANGE);
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);	
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_5_RANGE); 
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);

	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//Open relays.
	//Disonnect Pullup R from TS and UV pins
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	//Disonnect Pullup R to SCL & SDA
	Open_relay(K1_SDA_SPI_TB);
	Open_relay(K1_SCL_SPI_TB);
	//Disconnect DSM CLK & Data from primary pins: TS & UV
	//Connect DSM CLK & Data to secondary:         SCL & SDA
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	
	for(i=0;i<80;i++)
	{
		PiDatalog(func, start_datalog_S+i, EEpr_S[i], func_fail_bin, POWER_UNIT);
	}

	if(g_Pre_E0_data_P == E0_data_P &&
	   g_Pre_E2_data_P == E2_data_P &&
	   g_Pre_E4_data_P == E4_data_P &&
	   g_Pre_E6_data_P == E6_data_P &&
	   g_Pre_E8_data_P == E8_data_P   )
	{
		EEpr_Chk_P = 1;
	}
	//----------------------------------------------------------------------------
	//Primary Pre & Pst C0
	PiDatalog(func, A_EEPR_C0_Pre_P, g_Pre_E0_data_P, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C0_Pst_P, E0_data_P,       func_fail_bin, POWER_UNIT);
	//Primary Pre & Pst C2
	PiDatalog(func, A_EEPR_C2_Pre_P, g_Pre_E2_data_P, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C2_Pst_P, E2_data_P,       func_fail_bin, POWER_UNIT);
	//Primary Pre & Pst C4
	PiDatalog(func, A_EEPR_C4_Pre_P, g_Pre_E4_data_P, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C4_Pst_P, E4_data_P,       func_fail_bin, POWER_UNIT);
	//Primary Pre & Pst C6
	PiDatalog(func, A_EEPR_C6_Pre_P, g_Pre_E6_data_P, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C6_Pst_P, E6_data_P,       func_fail_bin, POWER_UNIT);
	//Primary Pre & Pst C8
	PiDatalog(func, A_EEPR_C8_Pre_P, g_Pre_E8_data_P, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C8_Pst_P, E8_data_P,       func_fail_bin, POWER_UNIT);

	PiDatalog(func, A_EEPROM_CHK_P, EEpr_Chk_P,       func_fail_bin, POWER_UNIT);

	//--------------------------------------------------------------------------------
	

	//-------------------------------------------------------------------------------
	//If Secondary is untrimmed, then Pretrim EEprom readings required to be updated.
	//--------------------------------------------------------------------------------
	if (g_Burn_Enable_S )
	{
		g_Pre_E0_data_S = EEpr_Bank_S[E0];
		g_Pre_E2_data_S = EEpr_Bank_S[E2];
		g_Pre_E4_data_S = EEpr_Bank_S[E4];
		g_Pre_E6_data_S = EEpr_Bank_S[E6];
		g_Pre_E8_data_S = EEpr_Bank_S[E8];
	}

	if(g_Pre_E0_data_S == E0_data_S &&
	   g_Pre_E2_data_S == E2_data_S &&
	   g_Pre_E4_data_S == E4_data_S &&
	   g_Pre_E6_data_S == E6_data_S &&
	   g_Pre_E8_data_S == E8_data_S   )
	{
		EEpr_Chk_S = 1;
	}
	//Secondary Pre & Pst C0
	PiDatalog(func, A_EEPR_C0_Pre_S, g_Pre_E0_data_S, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C0_Pst_S, E0_data_S,       func_fail_bin, POWER_UNIT);
	//Secondary Pre & Pst C2
	PiDatalog(func, A_EEPR_C2_Pre_S, g_Pre_E2_data_S, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C2_Pst_S, E2_data_S,       func_fail_bin, POWER_UNIT);
	//Secondary Pre & Pst C4
	PiDatalog(func, A_EEPR_C4_Pre_S, g_Pre_E4_data_S, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C4_Pst_S, E4_data_S,       func_fail_bin, POWER_UNIT);
	//Secondary Pre & Pst C6
	PiDatalog(func, A_EEPR_C6_Pre_S, g_Pre_E6_data_S, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C6_Pst_S, E6_data_S,       func_fail_bin, POWER_UNIT);
	//Secondary Pre & Pst C8
	PiDatalog(func, A_EEPR_C8_Pre_S, g_Pre_E8_data_S, func_fail_bin, POWER_UNIT);
	PiDatalog(func, A_EEPR_C8_Pst_S, E8_data_S,       func_fail_bin, POWER_UNIT);

	PiDatalog(func, A_EEPROM_CHK_S, EEpr_Chk_S,       func_fail_bin, POWER_UNIT);


}
