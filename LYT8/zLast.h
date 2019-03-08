//==============================================================================
// zLast.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void zLast_user_init(test_function& func);

// ***********************************************************

void initialize_zLast(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	zLast_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_zLast(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum zLast{
	A_fNum_Last,
	A_Num_Functions,
	A_Error_Flag,
	A_TestTime,
	A_TestTime_PP,
	A_ENG1,
	A_ENG2,
	A_ENG3,
	A_ENG4,
	A_ENG5,
	A_ENG6,
	A_ENG7,
	A_ENG8,
	A_ENG9,
	A_ENG10,
	A_Last_TT
};