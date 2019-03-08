//==============================================================================
// CCOffset_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CCOffset_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_CCOffset_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CCOffset_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CCOffset_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum CCOffset_Pre{
	A_Func_Num_CCOffset_Pre,
	A_CCOffset_pt_S,
	A_CCOffset_target_S,
	A_CCOffset_TrCode_S,
	A_CCOffset_BitCode_S,
	A_CCOffset_ExpChg_S,
	A_CCOffset_Exp_Value,
	A_Eetr32_Zoffset0_S,
	A_Eetr33_Zoffset1_S,
	A_Eetr34_Zoffset2_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_CCOffset_prg_S,
	A_CCOffset_prgchg_S,
	A_CCOffset_Sim_S,
	A_CCOffset_Sim_Chg_S,
	A_CCOffset_Pst,
	A_CCOffset_Pre_TT
};