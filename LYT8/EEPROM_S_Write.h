//==============================================================================
// EEPROM_S_Write.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void EEPROM_S_Write_user_init(test_function& func);

// ***********************************************************

void initialize_EEPROM_S_Write(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	EEPROM_S_Write_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_EEPROM_S_Write(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum EEprom_S_Write{
	A_Func_Num_EEpr_S_Write,
	A_EEpr_S_Write_S,
	A_EEpr_S_Write_TT
};