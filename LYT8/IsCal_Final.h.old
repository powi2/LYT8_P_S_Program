//==============================================================================
// IsCal_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IsCal_Final_user_init(test_function& func);

// ***********************************************************

void initialize_IsCal_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IsCal_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IsCal_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IsCal_Final{
	A_fNum_IsCalFinal,
	A_IsCal_final,
	A_IsCal_Act_Chg,
	A_IsCal_final_TT	
};
