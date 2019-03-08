//==============================================================================
// VDDA_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VDDA_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_VDDA_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VDDA_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VDDA_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum VDDA_Pre{
	A_Func_Num_VDDA_Pre,
	A_VDDA_pt_S,
	A_VDDA_target_S,
	A_VDDA_TrCode_S,
	A_VDDA_BitCode_S,
	A_VDDA_ExpChg_S,
	A_Eetr27_ZTML0_S,
	A_Eetr28_ZTML1_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,
	A_VDDA_Sim_S,
	A_VDDA_Sim_Chg_S,
	A_VDDA_prg_S,
	A_VDDA_prgchg_S,
	A_VDDA_Pst,
	A_VDDA_Pre_TT
};