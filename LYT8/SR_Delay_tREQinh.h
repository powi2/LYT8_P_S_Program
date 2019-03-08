//==============================================================================
// SR_Delay_tREQinh.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void SR_Delay_tREQinh_user_init(test_function& func);

// ***********************************************************

void initialize_SR_Delay_tREQinh(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	SR_Delay_tREQinh_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_SR_Delay_tREQinh(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum SR_Delay{
	A_Func_Num_SR_Delay,
	A_ISR_Pulldown,
	A_ISR_Pulldown_C1,
	A_SR_delay,
	A_ISR_Pullup,
	A_Rpu,
	A_Rpd,
	A_Rpd_SR_C1,
	A_SR_threshold,
	A_SR_chk_Open,
	A_SR_chk_5nF,
	A_tREQ_Inhibit,
	A_nCycles_Inhibit,
	A_Unwanted_pulses,
	A_Pulse_dly_HS,
	A_Pulse_dly_0V,
	A_FWFlate_filter_NM,
	A_FWFlate_dly_0V,
	A_Delta_dly_0V,
	A_SR_Delay_TT
};