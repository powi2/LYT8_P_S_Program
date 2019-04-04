//==============================================================================
// IOV_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_P_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_P
{
		A_fNum_IOV_P	,	
		A_iOVp_Tgt_P	,	
		A_iOVp_L_PF_P	,	
		A_iOVp_H_PF_P	,	
		A_iOVp_P		,	
		A_iOVp_Err_P	,	
		A_iOVm_L_PF_P	,	
		A_iOVm_H_PF_P	,	
		A_iOVm_P		,	
		A_iOVm_Err_P	,	
		A_iOV_Hys_P		,	
		A_IOV_P_TT		,	
};