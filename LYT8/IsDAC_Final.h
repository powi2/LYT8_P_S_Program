//==============================================================================
// IsDAC_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IsDAC_Final_user_init(test_function& func);

// ***********************************************************

void initialize_IsDAC_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IsDAC_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IsDAC_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IsDAC_Pt{
	A_fNum_IsDACfinal,
	A_IsDAC_final,
	A_IsDAC_TrCode0,
	A_IsDAC_TrCode1,
	A_IsDAC_TrCode2,
	A_IsDAC_TrCode4,
	A_IsDAC_TrCode8,
	A_IsDAC_TrCode16,
	A_IsDAC_TrCode31,
	A_IsDAC_Act_Chg,
	A_IsDAC_final_TT
};
