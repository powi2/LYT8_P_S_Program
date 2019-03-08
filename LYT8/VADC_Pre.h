//==============================================================================
// VADC_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VADC_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_VADC_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VADC_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VADC_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum VADC_Pre{
	A_Func_Num_VADC_Pre,
	A_VADC_pt_S,
	A_VADC_target_S,
	A_VADC_TrCode_S,
	A_VADC_BitCode_S,
	A_VADC_ExpChg_S,
	A_VADC_Exp_Value,
	A_Eetr48_ZTMFS0_S,
	A_Eetr49_ZTMFS1_S,
	A_Eetr50_ZTMFS2_S,
	A_Eetr51_ZTMFS3_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_VADC_prg_S,
	A_VADC_prgchg_S,
	A_VADC_Sim_S,
	A_VADC_Sim_Chg_S,
	A_VADC_Pst,
	A_VADC_Pre_TT
};