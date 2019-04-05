//==============================================================================
// CP_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CP_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_CP_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CP_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CP_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CP_Pst_S{
	A_Func_Num_CP_Pst_S,
	A_CP1_BOFF_Pst_S,
	A_CP2_BOFF_Pst_S,
	A_CP3_BOFF_Pst_S,
	A_CP4_BOFF_Pst_S,
	A_CP1_IS_Pst_S,
	A_CP2_IS_Pst_S,
	A_CP3_IS_Pst_S,
	A_CP4_IS_Pst_S,
	A_CP1_PFOFF_Pst_S,
	A_CP2_PFOFF_Pst_S,
	A_CP3_PFOFF_Pst_S,
	A_CP4_PFOFF_Pst_S,
	A_CP_IS_Delta_S,
	A_CP_IS_Test1_S,
	A_CP_IS_Test2_S,
	A_CP_Pst_TT
};