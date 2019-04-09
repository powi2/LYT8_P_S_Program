//==============================================================================
// TSDetect_P.cpp (User function)
// 
//    void TSDetect_P_user_init(test_function& func)
//    void TSDetect_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "TSDetect_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TSDetect_P_user_init(test_function& func)
{
	TSDetect_P_params *ours;
    ours = (TSDetect_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TSDetect_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    TSDetect_P_params *ours;
    ours = (TSDetect_P_params *)func.params;

}
