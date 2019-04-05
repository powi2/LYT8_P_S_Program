//==============================================================================
// CP_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CP_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_CP_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CP_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CP_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CP_Pre_S{
	A_Func_Num_CP_Pre_S,
	A_CP_pt_S,
	A_CP_target_S,
	A_CP_TrCode_S,
	A_CP_BitCode_S,
	A_CP_ExpChg_S,
	A_CP_Exp_Value,
	A_Eetr23_Tcp0_S,
	A_Eetr24_Tcp1_S,
	A_Eetr25_Tcp2_S,
	A_Eetr26_Tcp3_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_CP_prg_S,
	A_CP_prgchg_S,
	A_CP_Sim_S,
	A_CP_Sim_Chg_S,
	A_CP_Pst,
	A_CP_Pre_TT
};