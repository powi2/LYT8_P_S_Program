//==============================================================================
// VbILimit_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VbILimit_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_VbILimit_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VbILimit_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VbILimit_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VbIlimit_Pre_S{
	A_Func_Num_VbIlim_Pre_S,
	A_VbIlim_pt_S,
	A_VbIlim_target_S,
	A_VbIlim_TrCode_S,
	A_VbIlim_BitCode_S,
	A_VbIlim_ExpChg_S,
	A_VbIlim_Exp_Value,
	A_Eetr42_BILIM0_S,
	A_Eetr43_BILIM1_S,
	A_Eetr44_BILIM2_S,	
	A_Eetr45_BILIM3_S,	
	A_Eetr46_BILIM4_S,	
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_VbIlim_prg_S,
	A_VbIlim_prgchg_S,
	A_VbIlim_Sim_S,
	A_VbIlim_Sim_Chg_S,
	A_VbIlim_Pst,
	A_VbIlim_Pre_TT
};