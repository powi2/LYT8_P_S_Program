//==============================================================================
// VR_D_Ext_01_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VR_D_Ext_01_S_user_init(test_function& func);

// ***********************************************************

void initialize_VR_D_Ext_01_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VR_D_Ext_01_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VR_D_Ext_01_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VR_DE_01_S{
	A_Func_Num_VR_DE_01_S,
	A_VR_DE01_Opt,
	A_AVR_DE01_Tap1,
	A_AVR_DE01_Tap2,
	A_AVR_DE01_Tap3,
	A_AVR_DE01_Tap4,
	A_VFB_ExHBP_44_01,
	A_A0_ExHBP_44_01,
	A_A1_ExHBP_44_01,
	A_A2_ExHBP_44_01,
	A_A3_ExHBP_44_01,
	A_B1_ExHBP_44_01,
	A_B2_ExHBP_44_01,
	A_BSk_ExHBP_44_01,
	A_BD_ExHBP_44_01,
	A_BLOSkExHBP44_01,
	A_BLO_ExHBP44_01,
	A_B3_ExHBP_44_01,
	A_VFB_ExHBP_32_01,
	A_A0_ExHBP_32_01,
	A_A1_ExHBP_32_01,
	A_A2_ExHBP_32_01,
	A_A3_ExHBP_32_01,
	A_B1_ExHBP_32_01,
	A_B2_ExHBP_32_01,
	A_BSk_ExHBP_32_01,
	A_BD_ExHBP_32_01,
	A_BLOSkExHBP32_01,
	A_BLO_ExHBP32_01,
	A_B3_ExHBP_32_01,
	A_VFB_ExHBP_25_01,
	A_A0_ExHBP_25_01,
	A_A1_ExHBP_25_01,
	A_A2_ExHBP_25_01,
	A_A3_ExHBP_25_01,
	A_B1_ExHBP_25_01,
	A_B2_ExHBP_25_01,
	A_BSk_ExHBP_25_01,
	A_BD_ExHBP_25_01,
	A_BLOSkExHBP25_01,
	A_BLO_ExHBP25_01,
	A_B3_ExHBP_25_01,
	A_VFB_ExHBP_17_01,
	A_A0_ExHBP_17_01,
	A_A1_ExHBP_17_01,
	A_A2_ExHBP_17_01,
	A_A3_ExHBP_17_01,
	A_B1_ExHBP_17_01,
	A_B2_ExHBP_17_01,
	A_BSk_ExHBP_17_01,
	A_BD_ExHBP_17_01,
	A_BLOSkExHBP17_01,
	A_BLO_ExHBP17_01,
	A_B3_ExHBP_17_01,
	A_VR_DE_01_S_TT
};