//==============================================================================
// SoftStart.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void SoftStart_user_init(test_function& func);

// ***********************************************************

void initialize_SoftStart(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	SoftStart_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_SoftStart(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum SoftStart{
	A_fNum_SoftStart,
	A_ILIM_70pct_mA_P,
	A_ILIM_70pct_P,
	A_tsoft_SSS,
	A_tHandshake_SSS,
	A_Fosc_min_SSS,
	A_Fosc_max_SSS,
	A_Fosc_Mod_S,
	A_IlimHigh_JitterLow_S,
	A_IlimLow_JitterHigh_S,
	A_ILIM_Jit132K_S,
	A_Fosc_Sss_P,
	A_ILIM_Jit18K_S,
	A_IlimHigh_JitterLow_18kHz_S,
	A_IlimLow_JitterHigh_18kHz_S,
	A_Fosc_Mod_18kHz_S,
	A_tChUp_RTM_P,
	A_SoftStart_TT
};
