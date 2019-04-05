//==============================================================================
// CDC_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CDC_Final_user_init(test_function& func);

// ***********************************************************

void initialize_CDC_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CDC_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CDC_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CDC_Final{
	A_fNum_CDC_Final,
	A_CDC_0mV_S,
	A_CDC_50mV_S,
	A_CDC_100mV_S,
	A_CDC_200mV_S,
	A_CDC_400mV_S,
	A_CDC_Final_S,
	A_CDC_Act_Chg_S,
	A_Delta_CDC,
	A_CDC_Final_TT
};