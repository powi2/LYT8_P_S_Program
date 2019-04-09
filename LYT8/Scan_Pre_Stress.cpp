//==============================================================================
// Scan_Pre_Stress.cpp (User function)
// 
//    void Scan_Pre_Stress_user_init(test_function& func)
//    void Scan_Pre_Stress(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Scan_Pre_Stress.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Scan_Pre_Stress_user_init(test_function& func)
{
	Scan_Pre_Stress_params *ours;
    ours = (Scan_Pre_Stress_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Scan_Pre_Stress(test_function& func)
{
    // The two lines below must be the first two in the function.
    Scan_Pre_Stress_params *ours;
    ours = (Scan_Pre_Stress_params *)func.params;


	/*
	----------------------------------------------------------------------------------------------------
	  Measurements:
		Apply SCAN pattern and compare drain output with expected pattern.  
		(For SCAN mode, signal on drain should be in phase with expected pattern)

	  Procedure:
		Once SCAN is entered, no way to exit until POR, so should place this test when ready to do POR
		1. Go into I2C mode
		2. write 8C to ADDR_TM_CTRL
		3. Bring BPP over OV point to set scan ENABLE
		   To do stress testing while doing SCAN (want BPP at 8V)
		4. Set CFG25 to toggle SCANEN
		5. send clk via TS, data via VPIN
		6. After POR, SCANEN = 0
		when we start SCAN test and need to set SCANEN = 1, bring BPP = 8V > BPPOV
		now when we want SCANEN = 0, bring BPP to 5.25V and then bring it back to 8V, then SCANEN toggles to 1!


	Scan Vector files are located at:
		\\pishare02\npi\binno\Test\Test Plan\from DESIGN\Primary\scan_vectors
		\\pishare02\npi\binno\Test\Test Plan\from DESIGN\Secondary\scan_vectors

	Sim File located at:
		\\pishare02\npi\binno\Test\Test Plan\from DESIGN\Primary\sampleTestbenchesI2C\stim_i2c_SCANtesting.vams 

	----------------------------------------------------------------------------------------------------
	*/

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

	PowerUp_I2C_P();
	DSM_I2C_Write('b', g_TM_CTRL, 0x8C);	//g_S_TM_CTRL = 0x40
	//3. Bring BPP higher than OV point (8V) to set scan ENABLE
	BPP_dvi->set_voltage(BPP_ch, 8.0, VOLT_10_RANGE); // DVI_11_1

	//4. Set CFG25 to toggle SCANEN
	DSM_I2C_Write('w', g_ANA_CTRL_1, 0x0200);	//g_S_ANA_CTRL_1 = 0x46, CFG25 = 1 (0x0200)

	//5. Send in Scan Chain

		////6. After POR, SCANEN = 0
		////when we start SCAN test and need to set SCANEN = 1, bring BPP = 8V > BPPOV
		////now when we want SCANEN = 0, bring BPP to 5.25V and then bring it back to 8V, then SCANEN toggles to 1!



}
