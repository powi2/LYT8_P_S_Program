//==============================================================================
// IUV_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IUV_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_IUV_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IUV_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IUV_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IUV_pre_P
{
	A_fnum_iUVp_Tr_P,
	A_iUVp_pt_P,
	A_iUVp_target_P,
	A_iUVp_TrCode_P,
	A_iUVp_BitCode_P,
	A_iUVp_ExpChg_P,
	A_iUVp_ExpA_P,
	A_EeTr57_iUVp0_P,
	A_EeTr58_iUVp1_P,
	A_EeTr59_iUVp2_P,
	A_EeTr60_iUVp3_P,
	A_iUVp_Sim_P,
	A_iUVp_Sim_Chg_P,
	A_iUVp_pst_P,
	A_iUVp_Trim_P_TT,

};