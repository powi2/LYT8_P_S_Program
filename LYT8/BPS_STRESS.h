//==============================================================================
// BPS_STRESS.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BPS_STRESS_user_init(test_function& func);

// ***********************************************************

void initialize_BPS_STRESS(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BPS_STRESS_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BPS_STRESS(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum BPS_STRESS{
	A_fNum_BPS_Stress,
	A_BPS_Stress_Volt,
	A_IIL_FW_Post,
	A_IIL_FW_Delta,
	A_IIL_VO_Post,
	A_IIL_VO_Delta,
	A_IIL_IS_Post,
	A_IIL_IS_Delta,
	A_IIL_VBD_Post,
	A_IIL_VBD_Delta,
	A_IIH_VBD_Post,
	A_IIH_VBD_Delta,
	A_IIL_SDA_Post,
	A_IIL_SDA_Delta,
	A_IIH_SDA_Post,
	A_IIH_SDA_Delta,
	A_IIL_SCL_Post,
	A_IIL_SCL_Delta,
	A_IIH_SCL_Post,
	A_IIH_SCL_Delta,
	A_IIL_COMP_Post,
	A_IIL_COMP_Delta,
	A_IIH_COMP_Post,
	A_IIH_COMP_Delta,
	A_BPS_IS1_Pre,
	A_BPS_IS1_Post,	
	A_BPS_IS1_Delta,
	A_BPS_IS1hf_Pre,
	A_BPS_IS1hf_Post,
	A_BPS_IS1hf_Delta,
	A_BPS_IS2_Pre,
	A_BPS_IS2_Post,
	A_BPS_IS2_Delta
};