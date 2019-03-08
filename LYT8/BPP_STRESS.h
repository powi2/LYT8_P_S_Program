//==============================================================================
// BPP_STRESS.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BPP_STRESS_user_init(test_function& func);

// ***********************************************************

void initialize_BPP_STRESS(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BPP_STRESS_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BPP_STRESS(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum BPS_STRESS{
	A_fNum_BPP_Stress,
	A_BPP_Stress_Volt,
	A_BPP_IS1_Pre,
	A_BPP_IS2_Pre,
	A_iLeak_V_Pre,
	A_BPP_IS1_Post,
	A_BPP_IS1_Delta,
	A_BPP_IS2_Post,
	A_BPP_IS2_Delta,
	A_iLeak_V_Post,
	A_iLeak_V_Delta
};