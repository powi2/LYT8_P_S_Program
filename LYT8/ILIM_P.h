//==============================================================================
// ILIM_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ILIM_P_user_init(test_function& func);

// ***********************************************************

void initialize_ILIM_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ILIM_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ILIM_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ILIM_P{
		A_fnum_ILIM_P	,
		A_ILIM_Tgt_P	,
		A_ILIM_P	,
		A_ILIM_Err_P	,
		A_ILIM_didt_P	,
		A_ILIM_Ton_P	,
		A_ILIM_Rdson_P	,
		A_ILIMp1_P	,
		A_ILIMp1_Err_P	,
		A_ILIMp1_didt_P	,
		A_ILIMp1_Ton_P	,
		A_ILIMp1_Rdson_P	,
		A_ILIM_P_TT	,

};