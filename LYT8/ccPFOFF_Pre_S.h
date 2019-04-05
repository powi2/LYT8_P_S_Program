//==============================================================================
// ccPFOFF_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ccPFOFF_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_ccPFOFF_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ccPFOFF_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ccPFOFF_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ccPFOFF_Pre{
	A_Func_Num_ccPFOFF_Pre,
	A_ccPFOFF_pt_S,
	A_ccPFOFF_target_S,
	A_ccPFOFF_TrCode_S,
	A_ccPFOFF_BitCode_S,
	A_ccPFOFF_ExpChg_S,
	A_ccPFOFF_Exp_Value,
	A_Eetr35_Icc0_S,
	A_Eetr36_Icc1_S,
	A_Eetr37_Icc2_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_ccPFOFF_prg_S,
	A_ccPFOFF_prgchg_S,
	A_ccPFOFF_Sim_S,
	A_ccPFOFF_Sim_Chg_S,
	A_ccPFOFF_Pst,
	A_ccPFOFF_Pre_TT
};