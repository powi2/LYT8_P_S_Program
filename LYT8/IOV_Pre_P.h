//==============================================================================
// IOV_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_pre_P
{
	A_Func_Num_iOVp_Pre,
	A_iOVp_pt_P,
	A_iOVp_target_P,
	A_iOVp_TrCode_P,
	A_iOVp_BitCode_P,
	A_iOVp_ExpChg_P,
	A_iOVp_ExpA_P,
	A_EeTr72_iOV0_P,
	A_EeTr73_iOV1_P,
	A_EeTr74_iOV2_P,
	A_EeTr75_iOV3_P,
	A_EeTr76_iOV4_P,
	A_iOVp_Sim_P,
	A_iOVp_Sim_Chg_P,
	A_iOVp_prg_P,
	A_iOVp_prgchg_P,
	A_cVPFOff_pst_P,
	A_cvBOff_pst_P,
	A_iOVp_Pst,
	A_iOVp_Pre_TT

};