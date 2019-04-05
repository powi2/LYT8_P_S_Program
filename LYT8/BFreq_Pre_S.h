//==============================================================================
// BFreq_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BFreq_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_BFreq_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BFreq_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BFreq_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum BFreq_Pre_S{
	A_Func_Num_BFreq_Pre_S,
	A_BFreq_pt_S,
	A_BFreq_target_S,
	A_BFreq_TrCode_S,
	A_BFreq_BitCode_S,
	A_BFreq_ExpChg_S,
	A_BFreq_Exp_Value,
	A_Eetr12_tfb0_S,
	A_Eetr13_tfb1_S,
	A_Eetr14_tfb2_S,	
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_BFreq_prg_S,
	A_BFreq_prgchg_S,
	A_BFreq_Sim_S,
	A_BFreq_Sim_Chg_S,
	A_BFreq_Pst,
	A_BFreq_Pre_TT
};