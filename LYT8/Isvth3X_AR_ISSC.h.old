//==============================================================================
// Isvth3X_AR_ISSC.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Isvth3X_AR_ISSC_user_init(test_function& func);

// ***********************************************************

void initialize_Isvth3X_AR_ISSC(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Isvth3X_AR_ISSC_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Isvth3X_AR_ISSC(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CV_CC_CB_Vout{
	
	A_Func_Num_Isvth3X,
	A_vFB_SC_OFF_S,
	A_AR_tISvth_S,
	A_ISSC_tIS_S,
	A_ISSC_tIS_TM_S,
	A_ISSC_ISvth_NM_S,
	A_ISSC_ISvth_TM_S,
	A_VVO_2pct_BLD,
	A_VVO_2pct_BLDrat,
	A_IVO_2pct_BLD,
	A_IVO_BLD_Off,
	A_VVO_BLD,
	A_VVO_BLD_ratio,
	A_IVO_BLD,
	A_ISSC_LOff_S,
	A_ISvth3X_S,
	A_ISvth3X_act_S,
	A_Isvth3X_ISSC_TT
};