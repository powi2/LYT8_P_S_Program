//==============================================================================
// EEprom_DevID.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void EEprom_DevID_user_init(test_function& func);

// ***********************************************************

void initialize_EEprom_DevID(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	EEprom_DevID_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_EEprom_DevID(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************


enum enum_eeprom_devid{
	A_Func_Num_eeprom_devid,
	A_Pri_Si_ID,
	A_Sec_SI_ID,
	A_Pri_UnTrimmed,
	A_Sec_UnTrimmed,
	A_vErase_P,
	A_Pri_Erased,
	A_vErase_S,
	A_Sec_Erased,
	A_FAB_Tracking,
	A_Major_Rev,
	A_Minor_Rev,
	A_EEprom_DevID_TT
};