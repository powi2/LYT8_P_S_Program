//==============================================================================
// VR_tDeglitch_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VR_tDeglitch_S_user_init(test_function& func);

// ***********************************************************

void initialize_VR_tDeglitch_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VR_tDeglitch_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VR_tDeglitch_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VR_tDeglitch_S{
	A_Func_Num_VR_tDeglitch_S,
	A_t_VRB_10V15V,
	A_t_VRB_15V20V,
	A_t_VRB_20V25V,
	A_t_VRB_25V30V,
	A_t_VRB_30V35V,
	A_t_VRB_35V40V,
	A_t_VRB_40V45V,
	A_t_VRB_45V50V,	
	A_VRB_tDeglitch_S_TT
};