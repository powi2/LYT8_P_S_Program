//==============================================================================
// BV_Drain.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BV_Drain_user_init(test_function& func);

// ***********************************************************

void initialize_BV_Drain(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BV_Drain_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BV_Drain(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_BV_Drain{
	A_fNum_BV_Drain,
	A_IDSS_StressCurr,
	A_BVDSS_ISTR,
	A_BVDSS_STR1,
	A_BVDSS_STR2,
	A_BVDSS_WALK,
	A_BVD_100UA,
	A_IDS_BVD_10V,
	A_IDS_80BVD,
	A_IDS_325V,
	A_IDS_150V,
	A_IDS_30V,
	A_BV_Drain_TT
};