//==============================================================================
// ADC_Final.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ADC_Final_user_init(test_function& func);

// ***********************************************************

void initialize_ADC_Final(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ADC_Final_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ADC_Final(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ADC_Final{
	A_fNum_ADC_Final,
	A_ADC_Final,
	A_ADC_Act_Chg,
	A_IIL_VO_final,
	A_IIH_COMP_final,
	A_IIH_FW_final,
	A_ADC_Final_TT
};