//==============================================================================
// VBP_Supply.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VBP_Supply_user_init(test_function& func);

// ***********************************************************

void initialize_VBP_Supply(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VBP_Supply_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VBP_Supply(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VBP_Supply{
	A_Func_Num_VBP_Supply,
	A_Ishunt_p,
	A_Ishunt_s,
	A_VBPP_P,
	A_VBPP_M,
	A_VBPP_HYS,
	A_VBPP_Reset_p,
	A_VBPS_P,
	A_VBPS_M,
	A_VBPS_HYS,
	A_VBPS_Reset_s,
	A_VBPS_Res_Delta,
	A_IBPS_5_5V,
	A_VSD_S,
	A_ISD_S,
	A_tLOff_Filter_S,
	A_Loff_Pass_S,
	A_VSD_p,
	A_ISD_p,
	A_ISD_func_p,
	A_ChargePumpBPS,
	A_VBP_Supply_TT
};