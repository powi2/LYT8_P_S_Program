//==============================================================================
// Scan_Post_Stress.cpp (User function)
// 
//    void Scan_Post_Stress_user_init(test_function& func)
//    void Scan_Post_Stress(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Scan_Post_Stress.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Scan_Post_Stress_user_init(test_function& func)
{
	Scan_Post_Stress_params *ours;
    ours = (Scan_Post_Stress_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Scan_Post_Stress(test_function& func)
{
    // The two lines below must be the first two in the function.
    Scan_Post_Stress_params *ours;
    ours = (Scan_Post_Stress_params *)func.params;

}
