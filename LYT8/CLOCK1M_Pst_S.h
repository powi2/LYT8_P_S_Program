//==============================================================================
// CLOCK1M_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CLOCK1M_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_CLOCK1M_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CLOCK1M_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CLOCK1M_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CLK1M_Pst{
	A_Func_Num_CLK1M_Pst,
	A_CLK1M_Pst_S,
	A_CLK1M_Delta_S,
	A_CLK1M_DCycle_S,
	A_CLK6M_S,
	A_CLK6M_DCycle_S,
	A_CLK_Test1_S,
	A_CLK_Test2_S,
	A_CLK1M_Pst_TT
};
