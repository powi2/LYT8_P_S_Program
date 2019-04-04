//==============================================================================
// VBP_Init.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VBP_Init_user_init(test_function& func);

// ***********************************************************

void initialize_VBP_Init(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VBP_Init_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VBP_Init(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VBP_init{
		A_Func_Num_VBP_init,
		A_ID_1V_2V,
		A_Vshunt_Init_Pr,
		A_Vshunt_Init_Se,
		A_VBPP_PV_Init,
		A_VBPP_M_Init,
		A_VBPP_P_Init,
		A_VBPP_P_S_Init_S,
		A_VBPP_P_iHVoff,
		A_VBPP_Vshunt_PUseq,
		A_VBPP_HYS_Init,
		A_VBPS_P_Init,
		A_VBPS_M_Init,
		A_VBPS_HYS_Init,
		A_IS_Buff_Check,
		A_IS_Buff_Value,
		A_IS_buff_Mid,
		A_IS_buff_Low,
		A_IS_buff_ovi,
		A_VBP_Init_TT,

};
