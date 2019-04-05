//==============================================================================
// ccOffset_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ccOffset_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_ccOffset_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ccOffset_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ccOffset_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CCOffset_Pst{
	A_Func_Num_CCOffset_Pst,
	A_CCOffset_Pst_S,
	A_CCOffset_Delta_S,
	A_CCOffset_Test_S,
	A_CCOffset_Pst_TT
};