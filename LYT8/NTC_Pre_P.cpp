//==============================================================================
// NTC_Pre_P.cpp (User function)
// 
//    void NTC_Pre_P_user_init(test_function& func)
//    void NTC_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "NTC_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void NTC_Pre_P_user_init(test_function& func)
{
	NTC_Pre_P_params *ours;
    ours = (NTC_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void NTC_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    NTC_Pre_P_params *ours;
    ours = (NTC_Pre_P_params *)func.params;

}
