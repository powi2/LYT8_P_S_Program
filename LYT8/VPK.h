//==============================================================================
// VPK.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VPK_user_init(test_function& func);

// ***********************************************************

void initialize_VPK(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VPK_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VPK(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VPK{
	A_fNum_VPK,
	A_VPK_5_3_A,
	A_VPK_5_3_B,
	A_Pvpk_5_3_isvth,
	A_Pvpk_5_3_imid,
	A_VPK_10,
	A_VPK_15,
	A_VPK_20_A,
	A_VPK_20_B,
	A_VPK_23_5_A,
	A_TOLP_OUT_ilow1,
	A_TOLP_OUT_ilow2,
	A_TOLP_OUT_imid1,
	A_TOLP_OUT_imid2,
	A_TOLP_OUT_ihigh1,
	A_TOLP_OUT_ihigh2,
	A_t_VI,
	A_VPK_TT	
};