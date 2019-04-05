//==============================================================================
// ccTH_S.cpp (User function)
// 
//    void ccTH_S_user_init(test_function& func)
//    void ccTH_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "ccTH_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ccTH_S_user_init(test_function& func)
{
	ccTH_S_params *ours;
    ours = (ccTH_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ccTH_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    ccTH_S_params *ours;
    ours = (ccTH_S_params *)func.params;

}
