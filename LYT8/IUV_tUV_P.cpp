//==============================================================================
// IUV_tUV_P.cpp (User function)
// 
//    void IUV_tUV_P_user_init(test_function& func)
//    void IUV_tUV_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IUV_tUV_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IUV_tUV_P_user_init(test_function& func)
{
	IUV_tUV_P_params *ours;
    ours = (IUV_tUV_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IUV_tUV_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    IUV_tUV_P_params *ours;
    ours = (IUV_tUV_P_params *)func.params;

}
