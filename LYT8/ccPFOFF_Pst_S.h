//==============================================================================
// ccPFOFF_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ccPFOFF_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_ccPFOFF_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ccPFOFF_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ccPFOFF_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ccPFOFF_Pst{
	A_Func_Num_ccPFOFF_Pst,
	A_ccTH_S,
	A_ccPFOFF_Pst_S,
	A_ccPFOFF_Delta_S,
	A_ccBOFF_S,
	A_ccPFOFF_Test1_S,
	A_ccPFOFF_Test2_S,
	A_ccPFOFF_Pst_TT
};