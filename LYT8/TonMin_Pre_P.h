//==============================================================================
// TonMin_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void TonMin_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_TonMin_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	TonMin_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_TonMin_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum TonMin_Pre_P{
	A_fnum_TMin_Tr_P,
	A_TonMin_pt_P,
	A_TonMin_target_P,
	A_TonMin_code_P,
	A_TonMin_BitCode_P,
	A_TonMin_needed_P,
	A_EeTr77_TonM0_P,
	A_EeTr78_TonM1_P,
	A_EeTr79_TonM2_P,
	A_TonMin_Sim,
	A_TonM_Sim_Chg,
	A_TonMin_pst_P,
	A_TonMin_Tr_P_TT,
};