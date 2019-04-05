//==============================================================================
// OSC_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void OSC_Final_user_init(test_function& func);

// ***********************************************************

void initialize_OSC_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	OSC_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_OSC_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CV_Pre{
	A_fNum_OSC_Final,
	A_OSC_Final,
	A_OSC_Act_Chg,
	A_OSC_Final_TT
};