//==============================================================================
// Leakage.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Leakage_user_init(test_function& func);

// ***********************************************************

void initialize_Leakage(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Leakage_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Leakage(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_Leakage{
	A_Func_Num_Leakage,
	A_FB_Divider_Check,
	A_FB_Divider_Value,
	A_TS_Comp_Check,
	A_TS_Comp_Value,
	A_IS_Buff_Check,
	A_IS_Buff_Value,
	A_HSG_Buff_Check,
	A_HSG_Buff_Value,
	A_B_Buff_Check,
	A_B_Buff_Value,
	A_HSG_Gnd_Res,
	A_B_Gnd_Res,
	A_MUX20_Check,
	A_Silicon_Pri_Rev,
	A_Silicon_Sec_Rev,
	A_IIL_D,
	A_IIH_D,
	A_IIL_BPP,
	A_IIH_BPP,
	A_IIL_TS,
	A_IIH_TS,
	A_IIL_UV,
	A_IIH_UV,
	A_IIL1_FW,
	A_IIL2_FW,
	A_IIH1_FW,
	A_IIH2_FW,
	A_IIL_VR,
	A_IIH1_VR,
	A_IIH2_VR,
	A_IIH3_VR,
	A_IIL_HSG,
	A_IIH_HSG,
	A_IIL_B,
	A_IIH_B,
	A_IIL_HBP,
	A_IIH_HBP,
	A_IIL_FB,
	A_IIH_FB,
	A_IIL_BPS,
	A_IIH_BPS,
	A_IIL_SCL,
	A_IIH_SCL,
	A_IIL_SDA,
	A_IIH1_SDA,
	A_IIH2_SDA,
	A_IIL_IS,
	A_IIH1_IS,
	A_IIH2_IS,
	A_Leakage_TT
};