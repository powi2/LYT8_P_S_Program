//==============================================================================
// ZTtimer_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ZTtimer_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_ZTtimer_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ZTtimer_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ZTtimer_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ZTtimer_Pre{
	A_Func_Num_ZTtimer_Pst,
	A_ZTtimer_pst_S,
	A_ZTtimer_Pct_Delta_S,
	A_ZTimer_DPTx_S,
	A_tMinOff_S,
	A_tMinOff_DPTx_S,
	A_tHS_Window1_S,
	A_tHS_Window2_S,
	A_Timer1_S,
	A_Timer2_S,
	A_ZTtimer_Pst_TT
};