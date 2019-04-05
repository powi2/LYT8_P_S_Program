//==============================================================================
// IOV_IUV_OT.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_IUV_OT_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_IUV_OT(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_IUV_OT_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_IUV_OT(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_IUV_OT
{
	A_Func_Num_IOV_IUV_OT,
	A_iOV_plus,
	A_iOV_plus_exp,
	A_iOV_plus_act,
	A_iOV_minus,
	A_iOV_Hys,
	A_tOV_P_S,
	A_iUV_minus,
	A_iUV_plus,
	A_iUV_Hys,
	A_tUV_minus,
	A_iBPP_bled,
	A_iBPP_bledOff,
	A_tUV_M_counter,
	A_tUV_400ms,
	A_VPIN_LowPowTime,
	A_IOV_IUV_OT_TT
};