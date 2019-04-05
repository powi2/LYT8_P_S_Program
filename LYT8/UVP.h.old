//==============================================================================
// UVP.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void UVP_user_init(test_function& func);

// ***********************************************************

void initialize_UVP(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	UVP_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_UVP(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum UVP{
	A_fNum_UVP,
	A_V_UVP_3,
	A_V_UVP_8,
	A_V_UVP_14,
	A_V_UVP_19,
	A_V_UVP_24,
	A_Delta_V_UVP,
	A_t_UVP_8,
	A_t_UVP_16,
	A_t_UVP_32,
	A_t_UVP_64,
	A_UVP_TT
};