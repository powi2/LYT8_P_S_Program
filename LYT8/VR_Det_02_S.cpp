//==============================================================================
// VR_Det_02_S.cpp (User function)
// 
//    void VR_Det_02_S_user_init(test_function& func)
//    void VR_Det_02_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)

#include "VR_Det_02_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VR_Det_02_S_user_init(test_function& func)
{
	VR_Det_02_S_params *ours;
    ours = (VR_Det_02_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VR_Det_02_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    VR_Det_02_S_params *ours;
    ours = (VR_Det_02_S_params *)func.params;

}
