//==============================================================================
// NTC_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void NTC_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_NTC_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	NTC_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_NTC_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum NTC_Pre_P{
		A_fnum_NTC_Tr_P,
		A_dbus1_12_to_9,
		A_TSMode_NTC,
		A_tLong_Dtemp,
		A_tShort_Dtemp,
		A_Dtemp_pt_P,
		A_ITS_P,
		A_Dtemp_target_P,
		A_Dtemp_TrCode_P,
		A_Dtemp_BitCode_P,
		A_Dtemp_ExpChg_P,
		A_Dtemp_ExpV_P,
		A_EeTr67_TsADC0_P,
		A_EeTr68_TsADC1_P,
		A_EeTr69_TsADC2_P,
		A_EeTr70_TsADC3_P,
		A_Dtemp_Sim,
		A_Dtemp_Sim_Chg_P,
		A_Dtemp_pst_P,
		A_VTSstart_256,
		A_VTSstop_511,
		A_NTC_Tr_P_TT,

};