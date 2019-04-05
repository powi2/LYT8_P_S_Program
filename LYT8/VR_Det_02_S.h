//==============================================================================
// VR_Det_02_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VR_Det_02_S_user_init(test_function& func);

// ***********************************************************

void initialize_VR_Det_02_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VR_Det_02_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VR_Det_02_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
