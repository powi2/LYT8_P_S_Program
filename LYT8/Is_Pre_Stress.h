//==============================================================================
// Is_Pre_Stress.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Is_Pre_Stress_user_init(test_function& func);

// ***********************************************************

void initialize_Is_Pre_Stress(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Is_Pre_Stress_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Is_Pre_Stress(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
