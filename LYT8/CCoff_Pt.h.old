//==============================================================================
// CCoff_Pt.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CCoff_Pt_user_init(test_function& func);

// ***********************************************************

void initialize_CCoff_Pt(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CCoff_Pt_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CCoff_Pt(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CCoff_Pt{
	A_fNum_CCoff_Pt,
	A_CCoff_Pt_S,
	A_CCoff_Target_S,
	A_CCoff_TrCode_S,
	A_CCoff_BitCode_S,
	A_EEtr_CCoff1_S,
	A_EEtr_CCoff2_S,
	A_EEtr_CCoff3_S,
	A_CCoff_Sim_S,
	A_CCoff_Sim_Chg_S,
	A_CCoff_Pt_TT
};