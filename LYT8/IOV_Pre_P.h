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
	A_Iztr_Vref0_P,
	A_Iztr_Vref1_P,
	A_Iztr_Vref2_P,
	A_Iztr_Vref3_P,
	A_Bin2Dec1_P,
	A_Bin2Dec2_P,
	A_iOVp_Sim_P,
	A_iOVp_Sim_Chg_P,
	A_iOVp_prg_P,
	A_iOVp_prgchg_P,
	A_cVPFOff_pst_P,
	A_cvBOff_pst_P,
	A_iOVp_Pst,
	A_iOVp_Pre_TT

};