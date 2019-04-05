//==============================================================================
// IsCal_Pt.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IsCal_Pt_user_init(test_function& func);

// ***********************************************************

void initialize_IsCal_Pt(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IsCal_Pt_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IsCal_Pt(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IsCal_Pt{
	A_fNum_IsCal_Pt,
	A_IsCal_Pt_S,
	A_IsCal_Target_S,
	A_IsCal_TrCode_S,
	A_IsCal_BitCode_S,
	A_EEtr_IsCal1_S,
	A_EEtr_IsCal2_S,
	A_EEtr_IsCal3_S,
	A_IsCal_Sim_S,
	A_IsCal_Sim_Chg_S,
	A_IsCal_Pt_TT	
};