//==============================================================================
// Vovp.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Vovp_user_init(test_function& func);

// ***********************************************************

void initialize_Vovp(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Vovp_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Vovp(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Vovp{
	A_fNum_Vovp,
	A_V_OVP_6_2,
	A_V_OVP_10,
	A_V_OVP_15,
	A_V_OVP_20,
	A_V_OVP_24,
	A_Delta_V_OVP,
	A_Vovp_TT
};