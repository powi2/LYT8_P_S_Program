//==============================================================================
// Feature_Trim_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Feature_Trim_P_user_init(test_function& func);

// ***********************************************************

void initialize_Feature_Trim_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Feature_Trim_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Feature_Trim_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Feature_Trim_P{
	A_fnum_FetrTrim_P	,
	A_AR_SkipT_P	,
	A_AR_OnT_P	,
	A_AR_OFFT_P	,
	A_StartFreq_P	,
	A_EnShuntCapSel_P	,
	A_Rcv_TH_P	,
	A_GanMode_P	,
	A_Vx_Trim_P	,
	A_DriverSize_P	,
	A_ARON_512ms_P	,
	A_GanDelay_P	,
	A_ILIMTC_P	,
	A_SDTemp_P	,
	A_DOPL_P	,
	A_Dsb_IlimCap_P	,
	A_IlimPlus_P	,
	A_StrTherTemp_P	,
	A_EndTherTemp_P	,
	A_UV_10pct_P	,
	A_FetrTrim_P_TT	,

};