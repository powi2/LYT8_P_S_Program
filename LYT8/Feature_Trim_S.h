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
	A_IZtr_PK1_S,
	A_IZtr_DVesrSlpAdj,
	A_IZtr_AR1_S,
	A_IZtr_AR2_S,
	A_IZtr_CBEN_S,
	A_IZtr_DsoftEn_S,
	A_IZtr_DOPL_S,
	A_IZtr_OVLO_S,
	A_IZtr_VR1_S,
	A_IZtr_VR2_S,
	A_IZtr_XFWPK_S,
	A_IZtr_SCEN_S,
	A_IZtr_CR_S,
	A_IZtr_CCAR_S,
	A_EEtr_DoplEnCp_S,
	A_IZtr_ESRsel_S,
	A_IZtr_DdampEn_S,
	A_Fetur_Trim_S_TT
};