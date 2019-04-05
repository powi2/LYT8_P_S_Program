//==============================================================================
// Fosc_pt_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_pt_S_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_pt_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_pt_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_pt_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_Pre_S{
	A_Func_Num_Fosc_Pre_S,
	A_Fosc_pt_S,
	A_Fosc_target_S,
	A_Fosc_TrCode_S,
	A_Fosc_BitCode_S,
	A_Fosc_ExpChg_S,
	A_Fosc_Exp_Value,
	A_Eetr64_VCO0_S,
	A_Eetr65_VCO1_S,
	A_Eetr66_VCO2_S,
	A_Eetr67_VCO3_S,
	A_Eetr68_VCO4_S,
	A_Eetr69_VCO5_S,
	A_Bin2Dec1_S,
	A_Bin2Dec2_S,	
	A_Fosc_prg_S,
	A_Fosc_prgchg_S,
	A_Fosc_Sim_S,
	A_Fosc_Sim_Chg_S,
	A_Fosc_Pst,
	A_Fosc_Pre_TT
};