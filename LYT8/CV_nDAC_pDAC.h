//==============================================================================
// CV_nDAC_pDAC.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void CV_nDAC_pDAC_user_init(test_function& func);

// ***********************************************************

void initialize_CV_nDAC_pDAC(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	CV_nDAC_pDAC_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_CV_nDAC_pDAC(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum CV_nDAC_pDAC{
	A_fNum_CVnDACpDAC,
	A_pDAC_3V_S,
	A_pDAC_4p84V_S,
	A_pDAC_4p92V_S,
	A_pDAC_4p96V_S,
	A_pDAC_4p98V_S,
	A_pDAC_4p99V_S,
	A_pDAC_Final_S,
	A_pDAC_Final_dlta,
	A_pDAC_TrCode0,
	A_pDAC_TrCode1,
	A_pDAC_TrCode2,
	A_pDAC_TrCode4,
	A_pDAC_TrCode8,
	A_pDAC_TrCode16,
	A_pDAC_TrCode31,
	A_pDAC_Act_Chg_S,
	A_nDAC_5p1V_S,
	A_nDAC_5p2V_S,
	A_nDAC_5p4V_S,
	A_nDAC_5p8V_S,
	A_nDAC_6p6V_S,
	A_nDAC_8p2V_S,
	A_nDAC_20V_S,
	A_nDAC_24V_S,
	A_nDAC_Final_S,
	A_nDAC_Final_dlta,
	A_nDAC_TrCode0,
	A_nDAC_TrCode1,
	A_nDAC_TrCode2,
	A_nDAC_TrCode4,
	A_nDAC_TrCode8,
	A_nDAC_TrCode16,
	A_nDAC_TrCode31,
	A_nDAC_Act_Chg_S,
	A_CV_Final_S,
	A_CV_Act_Chg_S,
	A_DeltaVOUT_10mV,
	A_DeltaVOUT_100mV,
	A_VOUT_T,
	A_CVO_timer,
	A_VTOL_Vo3_VFB,
	A_VTOL_Vo3_20mV,
	A_VTOL_Vo3_Avg,
	A_VTOL_Vo4_VFB,
	A_VTOL_Vo4_20mV,
	A_VTOL_Vo4_Avg,
	A_VTOL_Vo5_VFB,
	A_VTOL_Vo5_20mV,
	A_VTOL_Vo5_Avg,
	A_VTOL_Vo6_VFB,
	A_VTOL_Vo6_20mV,
	A_VTOL_Vo6_Avg,
	A_VTOL_Vo7_VFB,
	A_VTOL_Vo7_20mV,
	A_VTOL_Vo7_Avg,
	A_VTOL_Vo9_VFB,
	A_VTOL_Vo9_50mV,
	A_VTOL_Vo9_Avg,
	A_VTOL_Vo12_VFB,
	A_VTOL_Vo12_100mV,
	A_VTOL_Vo12_Avg,
	A_VTOL_Vo21_VFB,
	A_VTOL_Vo21_100mV,
	A_VTOL_Vo21_Avg,
	A_VTOL_Vo24_VFB,
	A_VTOL_Vo24_100mV,
	A_VTOL_Vo24_Avg,
	A_CV_nDAC_pDAC_TT	
};