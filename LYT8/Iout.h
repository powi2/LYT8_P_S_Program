//==============================================================================
// Iout.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Iout_user_init(test_function& func);

// ***********************************************************

void initialize_Iout(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Iout_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Iout(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Iout{
	A_fNum_Iout,
	A_ISVTH,
	A_ISVTH_NoCal,
	A_ISVTH_NOS,
	A_ISVTH_NoCal_NOS,
	A_Delta_IOUT,
	A_AvgReg_LFdly,
	A_AvgReg_HFdly,
	A_iTOL_6p25_mV,
	A_iTOL_6p25_Avg,
	A_iTOL_19_mV,
	A_iTOL_19_mV_Avg,
	A_iTOL_32_mV,
	A_iTOL_32_mV_Avg,
	A_Iout_TT
};