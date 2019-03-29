//==============================================================================
// Fosc_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_Pre_P{
		A_fnum_Fosc_Tr_P	,
		A_Fosc_pt_P	,
		A_Fosc_target_P	,
		A_Fosc_TrCode_P	,
		A_Fosc_BitCode_P	,
		A_Fosc_ExpChg_P	,
		//A_Fosc_ExpHz_P	,
		A_EeTr8_fOSC0_P	,
		A_EeTr9_fOSC1_P	,
		A_EeTr10_fOSC2_P	,
		A_EeTr11_fOSC3_P	,
			
		A_Fosc_Sim_P	,
		A_Fosc_Sim_Chg_P	,
		A_Fosc_pst_P	,
		A_Fosc_Trim_P_TT	,

};