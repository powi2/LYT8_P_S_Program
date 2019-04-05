//==============================================================================
// VbILimit_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VbILimit_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_VbILimit_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VbILimit_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VbILimit_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VbIlimit_Pre_S{
	A_Func_Num_VbIlim_Pst_S,
	A_VbIlim1_Pst_S,
	A_VbIlim2_Pst_S,
	A_VbIlim_Delta_S,
	A_VbIlim_IS0p2V_S,
	A_VbIlim_Test1_S,
	A_VbIlim_Test2_S,
	A_VbIlim_Pst_TT,
};