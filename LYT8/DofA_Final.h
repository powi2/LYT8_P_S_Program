//==============================================================================
// DofA_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void DofA_Final_user_init(test_function& func);

// ***********************************************************

void initialize_DofA_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	DofA_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_DofA_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum DofA_Pt{
	A_fNum_DofA_Final,
	A_DofA_final,
	A_DofA_TrCode0,
	A_DofA_TrCode1,
	A_DofA_TrCode2,
	A_DofA_TrCode4,
	A_DofA_TrCode8,
	A_DofA_TrCode16,
	A_DofA_TrCode31,
	A_DofA_Act_Chg,
	A_DofA_final_TT
};
