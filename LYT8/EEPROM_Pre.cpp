//==============================================================================
// EEPROM_Pre.cpp (User function)
// 
//    void EEPROM_Pre_user_init(test_function& func)
//    void EEPROM_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "EEPROM_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_Pre_user_init(test_function& func)
{
	EEPROM_Pre_params *ours;
    ours = (EEPROM_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_Pre_params *ours;
    ours = (EEPROM_Pre_params *)func.params;

}
