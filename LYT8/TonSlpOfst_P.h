//==============================================================================
// TonSlpOfst_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void TonSlpOfst_P_user_init(test_function& func);

// ***********************************************************

void initialize_TonSlpOfst_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	TonSlpOfst_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_TonSlpOfst_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum TonSlpOfst_P{
			A_fnum_SlpOfst_P	,
			A_Slope_Tgt_P	,
			A_Slope_P	,
			A_Slope_Err_P	,
			A_Offset_Tgt_P	,
			A_Offset_P	,
			A_Offset_Err_P	,
			A_SlpOfst_P_TT	,

};