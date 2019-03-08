//==============================================================================
// ADC_Pt.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ADC_Pt_user_init(test_function& func);

// ***********************************************************

void initialize_ADC_Pt(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ADC_Pt_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ADC_Pt(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ADC_Pt{
	A_fNum_ADC_Pt,
	A_ADC_Pt,
	A_VTOL_Vo3_VFB_p,
	A_VTOL_Vo3_20mV_p,
	A_VTOL_Vo4_VFB_p,
	A_VTOL_Vo4_20mV_p,
	A_VTOL_Vo5_VFB_p,
	A_VTOL_Vo5_20mV_p,
	A_VTOL_Vo6_VFB_p,
	A_VTOL_Vo6_20mV_p,
	A_VTOL_Vo7_VFB_p,
	A_VTOL_Vo7_20mV_p,
	A_ADC_Target_S,
	A_ADC_TrCode_S,
	A_ADC_BitCode_S,
	A_EEtr_ADC1_S,
	A_EEtr_ADC2_S,
	A_EEtr_ADC3_S,
	A_EEtr_ADC4_S,
	A_EEtr_ADC5_S,
	A_ADC_Sim_S,
	A_ADC_Sim_Chg_S,
	A_ADC_Pt_TT
};
