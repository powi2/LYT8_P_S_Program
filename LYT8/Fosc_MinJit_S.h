//==============================================================================
// Fosc_MinJit_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_MinJit_S_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_MinJit_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_MinJit_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_MinJit_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_MinJit_S{
	A_Func_Num_Fosc_MinJit_S,
	A_Fosc_25K_NoFF_S,
	A_Ton_25K_NoFF_S,
	A_Fosc40us_NoFF_S,
	A_Ton40us_NoFF_S,
	A_Fosc_25K_WFF_S,
	A_Ton_25K_WFF_S,
	A_Fosc40us_WFF_S,
	A_Ton40us_WFF_S,
	A_FMin_D_NFFWFF_S,
	A_TMin_D_NFFWFF_S,
	A_Fosc_MinJit_TT
};