//==============================================================================
// IRSET_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IRSET_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_IRSET_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IRSET_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IRSET_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IRSET_Pre{
	A_Func_Num_IRSET_Pst,
	A_IRSET_Pst_S,
	A_IRSET_Pct_Delta_S,
	A_I2C_RSET_Chk_S,
	A_RSET_Test1_S,
	A_RSET_Test2_S,
	A_IRSET_Pst_S_TT
};