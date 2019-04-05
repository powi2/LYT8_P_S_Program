//==============================================================================
// VADC_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VADC_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_VADC_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VADC_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VADC_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VADC_Post{
	A_Func_Num_VADC_Post,
	A_VADC_Post_S,
	A_VADC_Delta_S,
	A_VADC_Test1_S,
	A_VADC_Test2_S,
	A_VADC_Post_TT
};