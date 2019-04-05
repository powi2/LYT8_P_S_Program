//==============================================================================
// HBP_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void HBP_S_user_init(test_function& func);

// ***********************************************************

void initialize_HBP_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	HBP_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_HBP_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum HBP_S{
	A_Func_Num_HBP_S,
	A_HBP_P_S,
	A_HBP_M_L_PF_S,
	A_HBP_M_S_CHAR_S,
	A_HBP_M_H_PF_S,
	A_HBP_Shunt_S,
	A_HBP_Ext_L_S_PF,
	A_HBP_Ext_S_CHAR,
	A_HBP_Ext_H_S_PF,
	A_HBP_FB_Short_S,	
	A_HBP_80us_F_S,
	A_HBP_Test1,	
	A_HBP_Test2,
	A_HBP_S_TT	
};