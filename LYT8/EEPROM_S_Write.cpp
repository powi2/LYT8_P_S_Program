//==============================================================================
// EEPROM_S_Write.cpp (User function)
// 
//    void EEPROM_S_Write_user_init(test_function& func)
//    void EEPROM_S_Write(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "EEPROM_S_Write.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_S_Write_user_init(test_function& func)
{
	EEPROM_S_Write_params *ours;
    ours = (EEPROM_S_Write_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_S_Write(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_S_Write_params *ours;
    ours = (EEPROM_S_Write_params *)func.params;

		// Increment function number //
	gFuncNum++;

// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_EEpr_S_Write, gFuncNum, 27, POWER_UNIT);

	if (g_OPCODE==4250 || g_OPCODE==4300 || g_OPCODE==4500)
		return;

if(g_Burn_Enable_S && g_GRR_Enable == 0)
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
	//Program_Trim_Register(g_S_TrimRegister);
	Program_All_TrimRegister();
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

	VR_dvi->set_voltage(VR_ch, vVR_Burn_th, VOLT_50_RANGE); // DVI_11_1
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

	if(g_Burn_Enable_S)
	{
		PiDatalog(func, A_EEpr_S_Write_S,      1,     26, POWER_UNIT);
	}
	else
	{
		PiDatalog(func, A_EEpr_S_Write_S,      0,     26, POWER_UNIT);

	}


}
