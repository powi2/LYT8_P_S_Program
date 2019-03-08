//==============================================================================
// Gain_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Gain_Final_user_init(test_function& func);

// ***********************************************************

void initialize_Gain_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Gain_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Gain_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Gain_Final{
	A_fNum_Gain_Final,
	A_Gain_Final,
	A_Gain_IsPin_32mV,
	A_Gain_Act_Chg,
	A_Gain_Final_TT	
};
