//==============================================================================
// TonMin_Slope_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void TonMin_Slope_P_user_init(test_function& func);

// ***********************************************************

void initialize_TonMin_Slope_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	TonMin_Slope_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_TonMin_Slope_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum TonMin_Slope_P{
		A_fnum_SLO_Tr_P,
		A_Slope_pt_P,
		A_Slope_target_P,
		A_Offset_pt_P,
		A_Offset_target_P,
		A_Slope_code_P,
		A_Slope_BitCode_P,
		A_Slope_needed_P,
		A_EeTr26_Slp0_P,
		A_EeTr27_slp1_P,
		A_EeTr28_slp2_P,
		A_EeTr29_slp3_P,
		A_EeTr30_slp4_P,
		A_Slope_Sim,
		A_Slope_Sim_Chg,
		A_Slope_pst_P,
		A_Offset_pt1_P,
		A_Offset_code_P,
		A_OffsetBitCode_P,
		A_Offset_needed_P,
		A_EeTr12_yInt0_P,
		A_EeTr13_yInt1_P,
		A_EeTr14_yInt2_P,
		A_EeTr15_yInt3_P,
		A_Offset_Sim,
		A_Offset_Sim_Chg,
		A_Offset_pst_P,
		A_SLO_Trim_P_TT,
};