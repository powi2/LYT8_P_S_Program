//==============================================================================
// Fosc_Pst_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_Pst_S_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_Pst_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_Pst_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_Pst_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_Pst_S{
	A_Func_Num_Fosc_Pst_S,
	A_Fosc_Pst_S,
	A_Fosc_Delta_S,
	A_Fosc_TonMax_S,
	A_Fosc_DCMax_S,
	A_Fosc_FF_00_S,
	A_Fosc_FF_00_Ton_S,
	A_Fosc_FF_00_DC_S,
	A_Fosc_FF_01_S,
	A_Fosc_FF_01_Ton_S,
	A_Fosc_FF_01_DC_S,
	A_Fosc_FF_10_S,
	A_Fosc_FF_10_Ton_S,
	A_Fosc_FF_10_DC_S,
	A_Fosc_FF_11_S,
	A_Fosc_FF_11_Ton_S,
	A_Fosc_FF_11_DC_S,
	A_Fosc_Jit_Max_S,
	A_Fosc_Jit_Min_S,
	A_Fosc_Jitter_S,
	A_Fosc_Pst_TT
};