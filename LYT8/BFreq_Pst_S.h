//==============================================================================
// BFreq_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BFreq_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_BFreq_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BFreq_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BFreq_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum BFreq_Pst_S{
	A_Func_Num_BFreq_Pst_S,
	A_BFreq_Pst_S,
	A_BFreq_Delta_S,
	A_BFreq_Ton_S,
	A_BFreq_DC_S,
	A_BFreq_Test1_S,
	A_BFreq_Test2_S,
	A_BFreq_Pst_TT
};