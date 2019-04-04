//==============================================================================
// Fosc_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_P_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_P{
		A_fnum_Fosc_P	,
		A_Fosc_Tgt_P	,
		A_Fosc_P	,
		A_Fosc_Err_P	,
		A_TonMax_P	,
		A_DCMax_P	,
		A_Fosc_P_TT	,
};