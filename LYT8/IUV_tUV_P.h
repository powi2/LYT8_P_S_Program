//==============================================================================
// IUV_tUV_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IUV_tUV_P_user_init(test_function& func);

// ***********************************************************

void initialize_IUV_tUV_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IUV_tUV_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IUV_tUV_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
