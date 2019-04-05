//==============================================================================
// Feature_Trim_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Feature_Trim_S_user_init(test_function& func);

// ***********************************************************

void initialize_Feature_Trim_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Feature_Trim_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Feature_Trim_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Feature_Trim_S{
	A_Func_Num_Feature_Trim_S,
	A_Eetr8_tsstart0_S,
	A_Eetr9_tsstart1_S,
	A_Eetr10_tfbOption0_S,
	A_Eetr11_tfbOption1_S,
	A_Eetr15_DOPL_S,
	A_Eetr16_TvrOption0_S,
	A_Eetr17_TvrOption1_S,
	A_Eetr18_TenCP_S,
	A_Eetr19_ZffOption0_S,
	A_Eetr20_ZffOption1_S,
	A_Eetr21_DsblJitDim_S,
	A_Eetr22_JitterOff_S,
	A_Eetr29_ZTMBStr0_S,
	A_Eetr30_ZTMBStr1_S,
	A_Eetr31_DsblFolBack_S,
	A_Eetr47_DimTh_S,
	A_Eetr61_tHrtBtOpt_S,
	A_Eetr62_CPNI2C_S,
	A_Eetr63_50KStart_S,
	A_Eetr74_FldBck_CCopt_S,
	A_Eetr75_FldBck_Sel_S,
	A_Ftr_Trim_S_TT
};