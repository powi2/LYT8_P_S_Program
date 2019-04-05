//==============================================================================
// EEPROM_Write.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void EEPROM_Write_user_init(test_function& func);

// ***********************************************************

void initialize_EEPROM_Write(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	EEPROM_Write_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_EEPROM_Write(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CC_Trim{
	A_fNum_EEPROM_Wrt,
	A_EEPROM_Write,
	A_EEPROM_Write_TT
};
