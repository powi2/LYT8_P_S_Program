//==============================================================================
// CV_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CV_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_CV_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CV_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CV_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CV_Post{
	A_Func_Num_CV_Post,
	A_CV_pst_L_S_PF,
	A_CV_pst_S,
	A_CV_pst_H_S_PF,
	A_CV_pct_Detla_S,
	A_VcvPFOFF_L_S_PF,
	A_VcvPFOFF_S,
	A_VcvPFOFF_H_S_PF,
	A_Vref1p25_L_S_PF,
	A_Vref1p25_S,
	A_Vref1p25_H_S_PF,
	A_VcvBoost_L_S_PF,
	A_VcvBoost_S,
	A_VcvBoost_H_S_PF,
	A_VcvLowFB_L_S_PF,
	A_VcvLowFB_S,
	A_VcvLowFB_H_S_PF,
	A_VcvSkip5A_L_S_PF,
	A_VcvSkip5A_S,
	A_VcvSkip5A_H_S_PF,
	A_VcvOVP5A_L_S_PF,
	A_VcvOVP5A_S,
	A_VcvOVP5A_H_S_PF,
	A_IFB_Pullup_S,
	A_FB_Test1, 
	A_FB_Test2,
	A_CV_Pst_TT
};