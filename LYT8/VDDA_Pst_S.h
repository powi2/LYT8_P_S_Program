//==============================================================================
// VDDA_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VDDA_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_VDDA_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VDDA_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VDDA_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VDDA_Post_S{
	A_Func_Num_VDDA_Post,
	A_VDDA_Post_S,
	A_VDDA_Pct_Del_S,
	A_VDDA_7V_S,
	A_VDDA_8V_S,
	A_VBPS_S,
	A_IBPS_LReg,
	A_VBPS_ILoad,
	A_BPS_Test1,
	A_BPS_Test2,
	A_VDDA_Pst_S_TT
};