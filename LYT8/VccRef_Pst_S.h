//==============================================================================
// VccRef_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VccRef_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_VccRef_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VccRef_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VccRef_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VccRef_Pst{
	A_Func_Num_VccRef_Pst,
	A_VccRef_Pst_S,
	A_VccRef_Delta_S,
	A_VccRef_Test_S,
	A_VccRef_Pst_TT
};