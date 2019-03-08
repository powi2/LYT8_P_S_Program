//==============================================================================
// VccRef_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VccRef_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_VccRef_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VccRef_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VccRef_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum VccRef_Pre{
	A_Func_Num_VccRef_Pre,
	A_VccRef_pt_S,
	A_VccRef_target_S,
	A_VccRef_TrCode_S,
	A_VccRef_BitCode_S,
	A_VccRef_ExpChg_S,
	A_VccRef_Exp_Value,
	A_Eetr52_DacTr0_S,
	A_Eetr53_DacTr1_S,
	A_Eetr54_DacTr2_S,
	A_Eetr55_DacTr3_S,
	A_Eetr56_DacTr4_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_VccRef_prg_S,
	A_VccRef_prgchg_S,
	A_VccRef_Sim_S,
	A_VccRef_Sim_Chg_S,
	A_VccRef_Pst,
	A_VccRef_Pre_TT
};