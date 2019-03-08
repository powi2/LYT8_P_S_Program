//==============================================================================
// CLOCK1M_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CLOCK1M_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_CLOCK1M_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CLOCK1M_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CLOCK1M_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum CLK1M_Pre{
	A_Func_Num_CLK1M_Pre,
	A_CLK1M_pt_S,
	A_CLK1M_target_S,
	A_CLK1M_TrCode_S,
	A_CLK1M_BitCode_S,
	A_CLK1M_ExpChg_S,
	A_CLK1M_Exp_Value,
	A_Eetr70_B0_S,
	A_Eetr71_B1_S,
	A_Eetr72_B2_S,
	A_Eetr73_B3_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_CLK1M_prg_S,
	A_CLK1M_prgchg_S,
	A_CLK1M_Sim_S,
	A_CLK1M_Sim_Chg_S,
	A_CLK1M_Pst,
	A_CLK1M_Pre_TT
};