//==============================================================================
// EEPROM_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void EEPROM_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_EEPROM_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	EEPROM_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_EEPROM_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
