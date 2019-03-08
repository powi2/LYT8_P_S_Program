//==============================================================================
// IRSET_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IRSET_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_IRSET_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IRSET_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IRSET_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum IRSET_Pre{
	A_Func_Num_IRSET_Pre,
	A_IRSET_pt_S,
	A_IRSET_target_S,
	A_IRSET_TrCode_S,
	A_IRSET_BitCode_S,
	A_IRSET_ExpChg_S,
	A_Eetr76_ZTLnt0_S,
	A_Eetr77_ZTLnt1_S,
	A_Eetr78_ZTLnt2_S,
	A_Eetr79_ZTLnt3_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,
	A_IRSET_prg_S,
	A_IRSET_prgchg_S,
	A_IRSET_Sim_S,
	A_IRSET_Sim_Chg_S,
	A_IRSET_Pst,
	A_IRSET_Pre_TT
};