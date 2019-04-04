//==============================================================================
// EEprom_DevID.cpp (User function)
// 
//    void EEprom_DevID_user_init(test_function& func)
//    void EEprom_DevID(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "EEprom_DevID.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEprom_DevID_user_init(test_function& func)
{
	EEprom_DevID_params *ours;
    ours = (EEprom_DevID_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEprom_DevID(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEprom_DevID_params *ours;
    ours = (EEprom_DevID_params *)func.params;

	//Variables
	int i = 0;
	int Primary_Die_ID  = 0;
	int	Secondary_DieID = 0;
	int Pri_Untrimmed   = 0;
	int Sec_Untrimmed   = 0;
	int Pri_Erased      = 0;
	int Sec_Erased      = 0;
	int Sec_E0          = 0;
	int Sec_E2          = 0;
	int Sec_E4          = 0;
	int Sec_E6          = 0;
	int Sec_E8          = 0;

	float vVR_set=20, vHSG=0;
	float vVR_Erase_th=0, vVR_Burn_th=0;

	int pE0_data=0,
		pE2_data=0,
		pE4_data=0,
		pE6_data=0,
		pE8_data=0;

	g_Trim_Enable_S = 0;

	// Increment function number //
	gFuncNum++;	

	Pulse pulse;

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_eeprom_devid, gFuncNum, 15, POWER_UNIT);

	// Skip Test if AbortTest set //
	if (AbortTest)
		return;

	if (g_Fn_Continuity == 0 )  return;

	// Test Time Begin //
	 if (g_TstTime_Enble_P)
	 	g_begintime = g_mytimer.GetElapsedTime();

	 bool Primary_ON = true;
	 if(Primary_ON)
	 {
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
		Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
		Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
		//Connect DSM CLK & Data to primary pins: TS & UV
		Close_relay(K1_DSM_TB);	
		Close_relay(K3_DSM_TB);
		Open_relay(K2_DSM_TB);
		Open_relay(K4_DSM_TB);
		delay(5);
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		float vpullup_P=3.3;	//5.0V does not work

		DSM_init_LYT8();
		PowerUp_I2C_P();

		int	DSM_context = 0x00;
		uint16_t address = 0x00;
		//uint16_t address = 0x00;
		uint8_t num_read_bytes = 2;
		uint8_t readDataBuffer[20];
		uint8_t writeDataBuffer[20];
		int i = 0;

		for(i=0;i<20;i++)
		{
			readDataBuffer[i] = 0x00;
			writeDataBuffer[i] = 0x00;
		}

		//-----------------------------------------------------------------------------------------------------------------
		// Read Primary Die ID  *START
		//------------------------------

		g_SlaveAddress_P	= 0x1C;

		//Primary Die ID
		if(1)	
		{
			/*		|			|				  | "Separation   |					 |				|
			Silicon	|			|				  | btw	passFET/  |	"PassFet driver	 |				|
			Options	|  CC Hyst	|	RC time		  |	Boost and CC" |	frequency clamp" |	comm driver	|	HW ID		
			--------|----------------------------------------------------------------------------------------------------------------
					|0mV |0.5mV	|1us | 4us	| 8us |	3.50% |	1.75% |	No Clamp | 50kHz |INNO3	| BINNO	|Hex ID		High Byte	Low Byte	
			-------------------------------------------------------------------------------------------------------------------------
			AT1		|	 |  x	|	 |		|  x  |	 x	  |		  |			 |	x	 |		|	x	|0x18 0x00	0001 1000	0000 0000	
			AT2		|	 |  x	|	 |		|  x  |	 x	  |		  |			 |	x	 |	x	|		|0x18 0x01	0001 1000	0000 0001	
			AT3		| x	 |		| x	 |		|	  |	 x	  |		  |			 |	x	 |	x	|		|0x18 0x02	0001 1000	0000 0010	
			AT4		| x	 |		| x	 |		|	  |	 x	  |		  |			 |	x	 |		|	x	|0x18 0x03	0001 1000	0000 0011	
			AT5		|	 |  x	|	 |	x	|	  |	 x	  |		  |			 |	x	 |		|	x	|0x18 0x04	0001 1000	0000 0100	
			AT6		| x	 |		| x	 |		|	  |	 x	  |		  |	x		 |		 |	x	|		|0x18 0x05	0001 1000	0000 0101	
			AT7		| x	 |		| x	 |		|	  |		  |	  x	  |	x		 |		 |	x	|		|0x18 0x06	0001 1000	0000 0110	
			AT8		| x	 |		|	 |	x	|	  |	 x	  |		  |			 |	x	 |		|	x	|0x18 0x07	0001 1000	0000 0111	
			AT9		| x	 |		|	 |	x	|	  | 	  |   x	  |	x		 |		 |	x	|		|0x18 0x08	0001 1000	0000 1000	
			-------------------------------------------------------------------------------------------------------------------------
			*/
			g_Debug = 1;
			Primary_Die_ID = DSM_I2C_Read(0x00);
			PiDatalog(func, A_Pri_Si_ID, Primary_Die_ID, 20, POWER_UNIT);
		}
		//-----------------------------------------------------------------------------------------------------------------
		// Read Primary Die ID  *END
		//------------------------------

		int Primary_Erase	= 0;	//FOR DEBUG ONLY
		int Primary_Burn	= 0;	//FOR DEBUG ONLY
		if(Primary_Erase)	
		{
			EEPROM_ERASE_P(&g_vDrain_Erase_th_P);
		}

		if(Primary_Burn)
		{
			EEPROM_Write_Enable_P();

			//issue write command per Reg_Addr (0xE0,2,4,6,8) for data to write into
			DSM_I2C_Write('w', 0xE0, 0x0000);
			DSM_I2C_Write('w', 0xE2, 0x0000);
			DSM_I2C_Write('w', 0xE4, 0x0560); //(VX=10110 + DriverSize=0010)
			DSM_I2C_Write('w', 0xE6, 0x0000);
			//DSM_I2C_Write('w', 0xE8, 0x6000); //(Timer bit 77,78)
			DSM_I2C_Write('w', 0xE8, 0x0000); 

			EEPROM_BURN_P(&g_vDrain_Burn_th_P);
		}


		//-----------------------------------------------------------------------------------------------------------------
		// Read EEprom Primary.  Detect & Decide Erase/Trim flag *START
		//-------------------------------------------------------------
		EEPROM_Read_Enable_P();

		//Read data out from EEPROM registers 0xC0
		pE0_data = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
		if(g_LowerByte != 0) //If any bit of lower byte is 1, it's considered Not Erased and we Enable ERASE
		{
			g_Erase_Enable_P = 1;
		}
		else
		{
			pE2_data = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
			pE4_data = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
			pE6_data = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
			pE8_data = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00
			if(pE0_data == 0 && pE2_data == 0 && pE4_data == 0 && pE6_data == 0&& pE8_data ==0)
			{
				g_Erase_Enable_P = 0;
				g_Sim_Enable_P	 = 1;
				Pri_Untrimmed	 = 1;
			}
			else
			{
				g_Sim_Enable_P = 0;
				Pri_Untrimmed	= 0;
			}

		}

		g_Sim_Enable_P = 1;	//for DEBUG ONLY

		PiDatalog(func, A_Pri_UnTrimmed, Pri_Untrimmed, 20, POWER_UNIT);
		//-------------------------------------------------------------
		// Read EEprom Primary.  Detect & Decide Erase/Trim flag *END
		//-----------------------------------------------------------------------------------------------------------------



		//-----------------------------------------------------------------------------------------------------------------
		// ERASE if "g_RTR_Enable" or "g_Erase_Enable_P" and must be at OPCode 4200 *START
		//---------------------------------------------------------------------------------
		////if( g_OPCODE==4200 && g_Erase_Enable_P )
		////{
		////	EEPROM_ERASE_P(&g_vDrain_Erase_th_P);
		////}
		////else if( (g_OPCODE_RTR || g_Erase_Enable_P) && g_OPCODE==4200 )
		////{
		////	EEPROM_ERASE_P(&g_vDrain_Erase_th_P);
		////}
		PiDatalog(func, A_Pri_Erased, g_vDrain_Erase_th_P, 20, POWER_UNIT);

		//-----------------------------------------------------------------------------------------------------------------
		// ERASE if "g_RTR_Enable" or "g_Erase_Enable_P" and must be at OPCode 4200 *END
		//---------------------------------------------------------------------------------




		Power_Down_I2C_P();

		////////SDA = 3.3V via pullup resistor. Ready for I2C.
		//////SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

		////////SCL = 3.3V via pullup resistor. Ready for I2C.
		//////SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
		//////delay(5);
		//////dvi_9->set_current(DVI_CHANNEL_1, 30e-3, RANGE_300_MA);
		//////dvi_9->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE); // DVI_11_1
		//////delay(10);

		//////Open_relay(K2_DSM_TB);
		//////Open_relay(K4_DSM_TB);
		//////delay(5);

		////////Set pullup voltage at TS @ UV pins.
		//////TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
		////////UV = 0V via pullup resistor. Ready for I2C.
		//////UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
		//////wait.delay_10_us(10);

		//////BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
		//////wait.delay_10_us(100);

		////////Connect Pullup R to TS pin.
		//////Open_relay(K1_TS_RB);

		////////Connect Pullup R to UV pin.
		//////Open_relay(K1_UV_RB);

		////////Disconnect DSM from Primary.
		//////mux_14->open_relay(MUX_1_1);	//Primary disconnect from DSM
		//////mux_14->open_relay(MUX_1_3);	//Primary disconnect from DSM
		//////delay(2);

		//Secondary I2C to ready Secondary Die ID.
		//Disconnect DVI_13 from HBP.
		dvi_13->disconnect(CONN_FORCE0);
		delay(5);

		//SDA & SCL set to 0V
		//SDA = 0V via pullup resistor. Ready for I2C.
		SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
		SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

		//SCL = 0V via pullup resistor. Ready for I2C.
		SCL_ovi3->set_current(SCL_ch, 10e-3, RANGE_30_MA);
		SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	}

//
	 bool Secondary_ON = true;
	 if(Secondary_ON)
	 {
////////////	//-------------------------------------------------------------------------------------
////////////	//---------- Secondary EEprom 'Read ID' &'Erase EEprom'  ------------------------------
////////////	//-------------------------------------------------------------------------------------
////////////	/*
////////////		Erase EEProm for Secondary
////////////		1.	vFB = 1.25V
////////////		2.	VR = 15V
////////////        3.  Read Die ID and convert it to decimal for datalogging later.	 
////////////		4.	Test Mode Enable with Drivers_en, Dsbl_FBshrt, ana_EN, Core_En, Comp out on HSG
////////////			a.	0x00 0x5E write 0x16 0x20
////////////			b.	0x00 0x5E write 0x34 0x12
////////////        5.  Read 0xC0 and determine if it's untrimmed and erasing EEprom is required.
////////////        6.  Erase EEprom
////////////			a.	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt
////////////				i.	0x00 0x62 write 0x88 0x00
////////////			b.	ZTMC_ana_EN and Core_en
////////////				i.	0x00 0x40 write 0x06 0x00
////////////			c.	ZVtrim_comp (Comp out on HSG)
////////////				i.	0x00 0x46 write 0x00 0xB8
////////////				ii.	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
////////////			d.	0x00 0x5C write 0x03
////////////			e.	ZTMC_ana_vprog_EN and ZTMC_ana_Vprog_2
////////////				i.	0x00 0x44 write 0x07 0x00
////////////			f.	Raise VR pin voltage >24V until HSG pin toggles to complete Erase (DC voltage could determine toggle or not)
////////////			g.	Stop/End Erase EEprom
////////////				i.	 0x00 0x5C write 0x00
////////////				ii.	 VR set to 15V 
////////////				iii. 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
///////////         7.  Re-Read EEprom 0xC0 to ensure if it's erased properly




	//-----------------------------------------------------------------------------------------------------------------
	//Power down Primary Die
	//------------------------------------------------------------------------------------------------------------------
	//Drain = 0V
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	//BPP = 0V
	BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 

	//TS = 0V 
	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); 
	//UV = 0V 
	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE);

	//-----------------------------------------------------------------------------------------------------------------
	//Setup Resource pins on Secondary.
	//------------------------------------------------------------------------------------------------------------------
	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	FW_ovi3->set_current(FW_ch, 3e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_5_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	HBP_dvi2k->set_current(HBP_ch, 0.0e-6, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);

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


	//Step 1.	vFB = 1.25V
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	//Step 2.	VR = 15V 
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	//Require >30mA else VR -> 10V, droop, then start rising with weird ramps
	VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
	wait.delay_10_us(200);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(50);
	
	//-----------------------------------------------------------------------------------------------------------------
	// Read Secondary Die ID  *START
	//------------------------------

	//Sometimes, DSM I2C can't be written correctly the first time.
	//Change the DSM timeout to 1ms since the default timeout is approximately 35ms.
	//g_Debug = 1;
	DSM_set_I2C_timeout(0, 1);
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Step 3. Reading 2ndary Die ID.
	Secondary_DieID = DSM_I2C_Read(0x00);	//Read Die ID
	//g_Debug = 0;
	//----------------------------------------------------------------------------------------------------------------
	// Read Secondary Die ID  *END
	//-----------------------------------------------------------------------------------------------------------------

	//Step 4.  Enter test mode
	Analog_TM_Enable_Secondary();

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
 	
	//For TEST only..  Manually raise vFB above 2.5V or 3V here to observe HBP will go low and then lower to 1.25V for HSG to go High
	//Below to to make sure the FB controlling HBP is working properly before Disabling it.
	if(0)
	{
		FB_ovi3->set_voltage(FB_ch, 2.00, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.25, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.50, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 2.75, VOLT_5_RANGE); // DVI_11_0
		delay(1);
		FB_ovi3->set_voltage(FB_ch, 3.00, VOLT_5_RANGE); // DVI_11_0	//1uF on HBP.  The drop is slow if it's only 3ms.  Manual observe drop to ~1.7V
		delay(3);
		FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
		delay(1);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Read Back EEprom for Secondary to determine if it's trimmed? *START
	//---------------------------------------------------------------------
	//Step 5.  Read back from 0xC0 to determine if it's trimmed or not.
	DSM_I2C_SREG0_0x7070();			//Get ready for any data to move to read address 0x00
	
	Sec_E0 = DSM_I2C_Read(g_EEP_R_C0);	//Read back data of Register addr 0xE0 from 0xC0 register address through READ_ADDR 0x00

	//Manual force erase.
	//g_LowerByte = 1;

	//If any bit of LowerByte of 0XC0 is not zero, then it's considered a virgin unit and secondary erase flag should be enabled.
	//If Virgin unit then proceed to erase EEprom.
	if(g_LowerByte != 0) 
	{
		g_Erase_Enable_S = 1;
	}
	else
	{
		Sec_E2 = DSM_I2C_Read(g_EEP_R_C2);	//Read back data of Register addr 0xE2 from 0xC2 register address through READ_ADDR 0x00
		Sec_E4 = DSM_I2C_Read(g_EEP_R_C4);	//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
		Sec_E6 = DSM_I2C_Read(g_EEP_R_C6);	//Read back data of Register addr 0xE6 from 0xC6 register address through READ_ADDR 0x00
		Sec_E8 = DSM_I2C_Read(g_EEP_R_C8);	//Read back data of Register addr 0xE8 from 0xC8 register address through READ_ADDR 0x00
		if(Sec_E0 == 0 && Sec_E2 == 0 && Sec_E4 == 0 && Sec_E6 == 0&& Sec_E8 ==0)
		{
			g_Erase_Enable_S = 0;
			g_Trim_Enable_S = 1;
			Sec_Untrimmed = 1;
		}
		else
		{
			g_Trim_Enable_S = 0;
			Sec_Untrimmed = 0;
		}

	}
	

	
	//-------------------------------------
	// Read Back EEprom for Secondary *END
	//-----------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------
	// Erase 2ndary EEprom *START
	//---------------------------------------------------------------------


	//-------------------------------------
	// Erase 2ndary EEprom *END
	//-----------------------------------------------------------------------------------------------------------------
	// Step 6.  Erase EEprom if it's untrimmed.
	if(g_Erase_Enable_S)
	{
		
		Sec_Erased    = 1;
		//6a.	ZTMC_Drivers_en and ZTMC_Dsbl_FBshrt  (The FBshrt -> FB to HBP short fault protection function.)
		//											  (This Test Mode disable 
		//	i.	0x00 0x62 write 0x88 0x00
		DSM_I2C_Write('w', g_TEST_CTRL2, 0x0088);

		//6b.	ZTMC_ana_EN and Core_en
		//	i.	0x00 0x40 write 0x06 0x00
		DSM_I2C_Write('w', g_TM_CTRL, 0x0006);

		//6c.	ZVtrim_comp (Comp out on HSG)
		//	i.	0x00 0x46 write 0x00 0xB8
		//	ii.	Note: If Comp out on HSG is not done rasing vFB above 2.5V/3V would bring HSG output down to ~2V and lower it to 1.25V would see HSG output ~11.5V
		DSM_I2C_Write('w', g_ANA_CTRL_1, 0xB800);
		
		//6d.	0x00 0x5C write 0x03
		DSM_I2C_Write('b', g_EEP_CMD, 0x03);

		//6e.	ZTMC_ana_vprog_EN and ZTMC_ana_Vprog_2
		//	i.	0x00 0x44 write 0x07 0x00
		DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0007);

		//6f.	Raise VR pin voltage >24V until HSG pin toggles to complete Erase (DC voltage could determine toggle or not)
		VR_dvi->set_current(VR_ch, 30e-3, RANGE_300_MA);
		VR_dvi->set_voltage(VR_ch, 20.0, VOLT_50_RANGE); // DVI_11_1
		delay(1);
		HSG_ovi->set_meas_mode(HSG_ch, OVI_MEASURE_VOLTAGE, AUTORANGE);
		i=0;
		while (vVR_set < 28)
		{
			vVR_set = vVR_set + i*0.2;
			VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
			wait.delay_10_us(10);
			vHSG = HSG_ovi->measure_average(5);
			if(vHSG > 2) //exit while loop
			{
				vVR_Erase_th = vVR_set+i*0.2;
				break;
			}
			i++;
		}

		//Hold VR for 2ms.
		VR_dvi->set_voltage(VR_ch, vVR_set, VOLT_50_RANGE); // DVI_11_1
		wait.delay_10_us(200);
		//6g.	Stop/End Erase EEprom
		End_EEprom_Erase_Secondary();
	}
////////////	//---------------------------------
////////////	// Erase EEProm for Secondary *END
////////////	//-----------------------------------------------------------------------------------------------------------------

	//int TrimBank[5];
	//Read_Trim_Register(TrimBank);


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


	//PiDatalog(func, A_Pri_Si_ID, Primary_Die_ID, 20, POWER_UNIT);
	PiDatalog(func, A_Sec_SI_ID, Secondary_DieID, 20, POWER_UNIT);
	PiDatalog(func, A_Sec_UnTrimmed, Sec_Untrimmed, 20, POWER_UNIT);
	PiDatalog(func, A_Sec_Erased, Sec_Erased, 20, POWER_UNIT);
}


}
