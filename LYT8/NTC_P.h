//==============================================================================
// NTC_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void NTC_P_user_init(test_function& func);

// ***********************************************************

void initialize_NTC_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	NTC_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_NTC_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum NTC_P{
			A_fnum_NTC_P	,
			A_Dbus1_12to9_P	,
			A_tLong_Dtemp	,
			A_tShort_Dtemp	,
			A_Dtemp_Tgt_P	,
			A_Dtemp_P	,
			A_Dtemp_Err_P	,
			A_ITS_P	,
			A_ITS_Err_P	,
			A_VTSstart_code	,
			A_VTSstop_code	,
			A_NTC_P_TT	,


};