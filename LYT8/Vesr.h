//==============================================================================
// Vesr.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Vesr_user_init(test_function& func);

// ***********************************************************

void initialize_Vesr(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Vesr_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Vesr(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Vesr
{
	A_Func_Num_Vesr,
	A_Vesr_Vfb1_S,
	A_Vesr_DeltaT1_S,
	A_Vesr_Vfb2_S,
	A_Vesr_DeltaT2_S,
	A_Vesr_Vfb3_S,
	A_Vesr_DeltaT3_S,
	A_Vesr_Vfb4_S,
	A_Vesr_DeltaT4_S,
	A_Vesr_slope1_S,
	A_Vesr_intcp1_S,
	A_Vesr_slope2_S,
	A_Vesr_intcp2_S,
	A_Vesr_Knee1_S,
	A_Vesr_Knee2_S,
	A_Vesr_Knee_S,
	A_Vesr_Peak_S,
	A_Vesr_TT
};

