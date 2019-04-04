//==============================================================================
// TSDetect_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void TSDetect_P_user_init(test_function& func);

// ***********************************************************

void initialize_TSDetect_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	TSDetect_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_TSDetect_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
