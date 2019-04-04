//==============================================================================
// EEPROM_Burn_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void EEPROM_Burn_P_user_init(test_function& func);

// ***********************************************************

void initialize_EEPROM_Burn_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	EEPROM_Burn_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_EEPROM_Burn_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum EEPROM_Burn_P{
			A_fNum_EEprP_Burn,
			A_vBurn_P_Tr,
			A_EEpr_P_Burn,
			A_EEprP_Burn_TT,
};