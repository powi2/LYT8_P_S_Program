//==============================================================================
// ZTtimer_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ZTtimer_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_ZTtimer_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ZTtimer_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ZTtimer_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum ZTtimer_Pre{
	A_Func_Num_ZTtimer_Pre,
	A_ZTtimer_pt_S,
	A_ZTtimer_target_S,
	A_ZTtimer_TrCode_S,
	A_ZTtimer_BitCode_S,
	A_ZTtimer_ExpChg_S,
	A_ZTtimer_Exp_Value,
	A_Eetr57_ZTtimer0_S,
	A_Eetr58_ZTtimer1_S,
	A_Eetr59_ZTtimer2_S,
	A_Eetr60_ZTtimer3_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_ZTtimer_prg_S,
	A_ZTtimer_prgchg_S,
	A_ZTtimer_Sim_S,
	A_ZTtimer_Sim_Chg_S,
	A_ZTtimer_Pst,
	A_ZTtimer_Pre_TT
};