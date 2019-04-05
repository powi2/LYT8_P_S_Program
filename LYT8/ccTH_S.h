//==============================================================================
// ccTH_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ccTH_S_user_init(test_function& func);

// ***********************************************************

void initialize_ccTH_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ccTH_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ccTH_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
