//==============================================================================
// VBD_uVCC.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VBD_uVCC_user_init(test_function& func);

// ***********************************************************

void initialize_VBD_uVCC(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VBD_uVCC_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VBD_uVCC(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VBD_uVCC{
	A_fNum_VBD_uVCC,
	A_uVCC_Reset,
	A_uVCC_Reset_b,
	A_V_VBD_Vout5V,
	A_V_VBD_Vo5V_VBPp,
	A_V_VBD_Vout3V,
	A_V_VBD_Vout24V,
	A_Ruvcc,
	A_tR_VBD,
	A_tF_VBD,
	A_VBD_RDSON,
	A_VBD_OFF,
	A_tWDT,
	A_uVCC,
	A_uVCC_10mA,
	A_I_uVCC,
	A_uVCC_VoutLow,
	A_uVCC_VoutHigh,
	A_uVCC_b,
	A_uVCC_10mA_b,
	A_I_uVCC_b,
	A_uVCC_VoutLow_b,
	A_uVCC_VoutHigh_b,
	A_SCL_interrupt,
	A_uVCC_VBD_short,
	A_DisableVBEN,
	A_VOL,
	A_VBD_uVCC_TT
};