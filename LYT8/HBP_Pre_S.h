//==============================================================================
// HBP_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void HBP_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_HBP_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	HBP_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_HBP_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum enum_HBP_Pre_S{
	A_Func_Num_HBP_Pre_S,
	A_HBP_Pre_S,
	A_HBP_Pre_S_TT
};