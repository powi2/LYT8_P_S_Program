//==============================================================================
// STRESS.cpp (User function)
// 
//    void STRESS_user_init(test_function& func)
//    void STRESS(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "STRESS.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void STRESS_user_init(test_function& func)
{
	STRESS_params *ours;
    ours = (STRESS_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void STRESS(test_function& func)
{
    // The two lines below must be the first two in the function.
    STRESS_params *ours;
    ours = (STRESS_params *)func.params;

}
