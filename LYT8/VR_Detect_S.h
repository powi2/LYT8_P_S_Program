//==============================================================================
// VR_Detect_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VR_Detect_S_user_init(test_function& func);

// ***********************************************************

void initialize_VR_Detect_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VR_Detect_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VR_Detect_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VR_Detect_S{
	A_Func_Num_VR_Detect_S,
	A_VR_Opt,
	A_AVR_Tap1,
	A_AVR_Tap2,
	A_AVR_Tap3,
	A_AVR_Tap4,
	A_VFB_InHBP_44_00,
	A_A0_InHBP_44_00,
	A_A1_InHBP_44_00,
	A_A2_InHBP_44_00,
	A_A3_InHBP_44_00,
	A_B1_InHBP_44_00,
	A_B2_InHBP_44_00,
	A_BSk_InHBP_44_00,
	A_BD_InHBP_44_00,
	A_BLOSkInHBP44_00,
	A_BLO_InHBP44_00,
	A_B3_InHBP_44_00,
	A_VFB_InHBP_32_00,
	A_A0_InHBP_32_00,
	A_A1_InHBP_32_00,
	A_A2_InHBP_32_00,
	A_A3_InHBP_32_00,
	A_B1_InHBP_32_00,
	A_B2_InHBP_32_00,
	A_BSk_InHBP_32_00,
	A_BD_InHBP_32_00,
	A_BLOSkInHBP32_00,
	A_BLO_InHBP32_00,
	A_B3_InHBP_32_00,
	A_VFB_InHBP_25_00,
	A_A0_InHBP_25_00,
	A_A1_InHBP_25_00,
	A_A2_InHBP_25_00,
	A_A3_InHBP_25_00,
	A_B1_InHBP_25_00,
	A_B2_InHBP_25_00,
	A_BSk_InHBP_25_00,
	A_BD_InHBP_25_00,
	A_BLOSkInHBP25_00,
	A_BLO_InHBP25_00,
	A_B3_InHBP_25_00,
	A_VFB_InHBP_17_00,
	A_A0_InHBP_17_00,
	A_A1_InHBP_17_00,
	A_A2_InHBP_17_00,
	A_A3_InHBP_17_00,
	A_B1_InHBP_17_00,
	A_B2_InHBP_17_00,
	A_BSk_InHBP_17_00,
	A_BD_InHBP_17_00,
	A_BLOSkInHBP17_00,
	A_BLO_InHBP17_00,
	A_B3_InHBP_17_00,
	A_VR_Detect_S_TT
};