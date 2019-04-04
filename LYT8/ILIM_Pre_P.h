//==============================================================================
// ILIM_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ILIM_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_ILIM_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ILIM_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ILIM_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ILIM_Pre_P{
		A_fnum_ILIM_Tr_P,
		A_ILIM_target_P,
		A_ILIM_pt_P,
		A_ILIM_pt_didt_P,
		A_ILIM_pt_ton_P,
		A_ILIM_TrCode_P,
		A_ILIM_BitCode_P,
		A_ILIM_ExpChg_P,
		A_ILIM_ExpA_P,
		A_EeTr16_ILIM0_P,
		A_EeTr17_ILIM1_P,
		A_EeTr18_ILIM2_P,
		A_EeTr19_ILIM3_P,
		A_EeTr20_ILIM4_P,
		A_ILIM_Sim_P,
		A_ILIM_SimChg_P,
		A_ILIM_pst_P,
		A_ILIM_pst_didt_P,
		A_ILIM_pst_ton_P,
		A_ILIM_Tr_P_TT,
};