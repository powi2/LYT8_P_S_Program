//==============================================================================
// LIST.CPP
//==============================================================================
#include "asl.h"
#include "function.h"

// There are five elements in each structure for each array position
// as shown below :-
/*
typedef struct	{
		// First, a name that is displayed on the list of functions screen
	char		*name;
		// Next the development number;
	unsigned long develop_no;
		// Next, the name of the actual function.
	void far	(*address)(test_function& func);
		// Next, the parameter setup section of the function
	void far	(*setup)(test_function& func,char **function_name,char *heading_line);
		// Next, the default initialization of the parameters (and various
		// memory requirements.
	void far	(*initialize)(short entry,test_function& func,char **function_name);
		// Lastly, the size of the block of parameters
	short			sizeof_param_block;
				} test_descriptions;
*/

//{ASL_CREATE BEGIN_TEST_LIST_INIT

test_descriptions g_test_list[] =
{
	{ "First",-1L,First,setup_First,initialize_First,sizeof(First_params) },
	{ "Continuity",-1L,Continuity,setup_Continuity,initialize_Continuity,sizeof(Continuity_params) },
	{ "Leakage",-1L,Leakage,setup_Leakage,initialize_Leakage,sizeof(Leakage_params) },
	{ "EEprom_DevID",-1L,EEprom_DevID,setup_EEprom_DevID,initialize_EEprom_DevID,sizeof(EEprom_DevID_params) },
	{ "Scan_Pre_Stress",-1L,Scan_Pre_Stress,setup_Scan_Pre_Stress,initialize_Scan_Pre_Stress,sizeof(Scan_Pre_Stress_params) },
	{ "Is_Pre_Stress",-1L,Is_Pre_Stress,setup_Is_Pre_Stress,initialize_Is_Pre_Stress,sizeof(Is_Pre_Stress_params) },
	{ "STRESS",-1L,STRESS,setup_STRESS,initialize_STRESS,sizeof(STRESS_params) },
	{ "Is_Post_Stress",-1L,Is_Post_Stress,setup_Is_Post_Stress,initialize_Is_Post_Stress,sizeof(Is_Post_Stress_params) },
	{ "Scan_Post_Stress",-1L,Scan_Post_Stress,setup_Scan_Post_Stress,initialize_Scan_Post_Stress,sizeof(Scan_Post_Stress_params) },
	{ "Leakage_Post_Stress",-1L,Leakage_Post_Stress,setup_Leakage_Post_Stress,initialize_Leakage_Post_Stress,sizeof(Leakage_Post_Stress_params) },
	{ "BV_Vpin",-1L,BV_Vpin,setup_BV_Vpin,initialize_BV_Vpin,sizeof(BV_Vpin_params) },
	{ "BV_Drain",-1L,BV_Drain,setup_BV_Drain,initialize_BV_Drain,sizeof(BV_Drain_params) },
	{ "VBP_Init",-1L,VBP_Init,setup_VBP_Init,initialize_VBP_Init,sizeof(VBP_Init_params) },
	{ "EEPROM_Pre",-1L,EEPROM_Pre,setup_EEPROM_Pre,initialize_EEPROM_Pre,sizeof(EEPROM_Pre_params) },
	{ "Feature_Trim_P",-1L,Feature_Trim_P,setup_Feature_Trim_P,initialize_Feature_Trim_P,sizeof(Feature_Trim_P_params) },
	{ "Feature_Trim_S",-1L,Feature_Trim_S,setup_Feature_Trim_S,initialize_Feature_Trim_S,sizeof(Feature_Trim_S_params) },
	{ "BPS_STRESS",-1L,BPS_STRESS,setup_BPS_STRESS,initialize_BPS_STRESS,sizeof(BPS_STRESS_params) },
	{ "BPP_STRESS",-1L,BPP_STRESS,setup_BPP_STRESS,initialize_BPP_STRESS,sizeof(BPP_STRESS_params) },
	{ "HBP_Pre_S",-1L,HBP_Pre_S,setup_HBP_Pre_S,initialize_HBP_Pre_S,sizeof(HBP_Pre_S_params) },
	{ "IOV_Pre_P",-1L,IOV_Pre_P,setup_IOV_Pre_P,initialize_IOV_Pre_P,sizeof(IOV_Pre_P_params) },
	{ "Fosc_Pre_P",-1L,Fosc_Pre_P,setup_Fosc_Pre_P,initialize_Fosc_Pre_P,sizeof(Fosc_Pre_P_params) },
	{ "TonMin_Pre_P",-1L,TonMin_Pre_P,setup_TonMin_Pre_P,initialize_TonMin_Pre_P,sizeof(TonMin_Pre_P_params) },
	{ "TonMin_Slope_P",-1L,TonMin_Slope_P,setup_TonMin_Slope_P,initialize_TonMin_Slope_P,sizeof(TonMin_Slope_P_params) },
	{ "ILIM_Pre",-1L,ILIM_Pre,setup_ILIM_Pre,initialize_ILIM_Pre,sizeof(ILIM_Pre_params) },
	{ "IUV_Pre_P",-1L,IUV_Pre_P,setup_IUV_Pre_P,initialize_IUV_Pre_P,sizeof(IUV_Pre_P_params) },
	{ "NTC_Pre_P",-1L,NTC_Pre_P,setup_NTC_Pre_P,initialize_NTC_Pre_P,sizeof(NTC_Pre_P_params) },
	{ "CV_Pre",-1L,CV_Pre,setup_CV_Pre,initialize_CV_Pre,sizeof(CV_Pre_params) },
	{ "VDDA_Pre",-1L,VDDA_Pre,setup_VDDA_Pre,initialize_VDDA_Pre,sizeof(VDDA_Pre_params) },
	{ "IRSET_Pre",-1L,IRSET_Pre,setup_IRSET_Pre,initialize_IRSET_Pre,sizeof(IRSET_Pre_params) },
	{ "ZTtimer_Pre",-1L,ZTtimer_Pre,setup_ZTtimer_Pre,initialize_ZTtimer_Pre,sizeof(ZTtimer_Pre_params) },
	{ "VADC_Pre",-1L,VADC_Pre,setup_VADC_Pre,initialize_VADC_Pre,sizeof(VADC_Pre_params) },
	{ "CLOCK1M_Pre",-1L,CLOCK1M_Pre,setup_CLOCK1M_Pre,initialize_CLOCK1M_Pre,sizeof(CLOCK1M_Pre_params) },
	{ "CCOffset_Pre",-1L,CCOffset_Pre,setup_CCOffset_Pre,initialize_CCOffset_Pre,sizeof(CCOffset_Pre_params) },
	{ "VccRef_Pre_S",-1L,VccRef_Pre_S,setup_VccRef_Pre_S,initialize_VccRef_Pre_S,sizeof(VccRef_Pre_S_params) },
	{ "CCoff_Pt",-1L,CCoff_Pt,setup_CCoff_Pt,initialize_CCoff_Pt,sizeof(CCoff_Pt_params) },
	{ "IsCal_Pt",-1L,IsCal_Pt,setup_IsCal_Pt,initialize_IsCal_Pt,sizeof(IsCal_Pt_params) },
	{ "ADC_Pt",-1L,ADC_Pt,setup_ADC_Pt,initialize_ADC_Pt,sizeof(ADC_Pt_params) },
	{ "EEPROM_Write",-1L,EEPROM_Write,setup_EEPROM_Write,initialize_EEPROM_Write,sizeof(EEPROM_Write_params) },
	{ "IzPost",-1L,IzPost,setup_IzPost,initialize_IzPost,sizeof(IzPost_params) },
	{ "SoftStart",-1L,SoftStart,setup_SoftStart,initialize_SoftStart,sizeof(SoftStart_params) },
	{ "VBP_Supply",-1L,VBP_Supply,setup_VBP_Supply,initialize_VBP_Supply,sizeof(VBP_Supply_params) },
	{ "IBP_Supply",-1L,IBP_Supply,setup_IBP_Supply,initialize_IBP_Supply,sizeof(IBP_Supply_params) },
	{ "IOV_IUV_OT",-1L,IOV_IUV_OT,setup_IOV_IUV_OT,initialize_IOV_IUV_OT,sizeof(IOV_IUV_OT_params) },
	{ "FOSC_Ton_ARST",-1L,FOSC_Ton_ARST,setup_FOSC_Ton_ARST,initialize_FOSC_Ton_ARST,sizeof(FOSC_Ton_ARST_params) },
	{ "FWPK",-1L,FWPK,setup_FWPK,initialize_FWPK,sizeof(FWPK_params) },
	{ "SR_Delay_tREQinh",-1L,SR_Delay_tREQinh,setup_SR_Delay_tREQinh,initialize_SR_Delay_tREQinh,sizeof(SR_Delay_tREQinh_params) },
	{ "SOA_SDS_TW50",-1L,SOA_SDS_TW50,setup_SOA_SDS_TW50,initialize_SOA_SDS_TW50,sizeof(SOA_SDS_TW50_params) },
	{ "IsCal_Final",-1L,IsCal_Final,setup_IsCal_Final,initialize_IsCal_Final,sizeof(IsCal_Final_params) },
	{ "Iout",-1L,Iout,setup_Iout,initialize_Iout,sizeof(Iout_params) },
	{ "CV_nDAC_pDAC",-1L,CV_nDAC_pDAC,setup_CV_nDAC_pDAC,initialize_CV_nDAC_pDAC,sizeof(CV_nDAC_pDAC_params) },
	{ "Vesr",-1L,Vesr,setup_Vesr,initialize_Vesr,sizeof(Vesr_params) },
	{ "Isvth3X_AR_ISSC",-1L,Isvth3X_AR_ISSC,setup_Isvth3X_AR_ISSC,initialize_Isvth3X_AR_ISSC,sizeof(Isvth3X_AR_ISSC_params) },
	{ "Vovp",-1L,Vovp,setup_Vovp,initialize_Vovp,sizeof(Vovp_params) },
	{ "UVP",-1L,UVP,setup_UVP,initialize_UVP,sizeof(UVP_params) },
	{ "VBD_uVCC",-1L,VBD_uVCC,setup_VBD_uVCC,initialize_VBD_uVCC,sizeof(VBD_uVCC_params) },
	{ "OSC_Final",-1L,OSC_Final,setup_OSC_Final,initialize_OSC_Final,sizeof(OSC_Final_params) },
	{ "DofA_Final",-1L,DofA_Final,setup_DofA_Final,initialize_DofA_Final,sizeof(DofA_Final_params) },
	{ "IsDAC_Final",-1L,IsDAC_Final,setup_IsDAC_Final,initialize_IsDAC_Final,sizeof(IsDAC_Final_params) },
	{ "Gain_Final",-1L,Gain_Final,setup_Gain_Final,initialize_Gain_Final,sizeof(Gain_Final_params) },
	{ "CDC_Final",-1L,CDC_Final,setup_CDC_Final,initialize_CDC_Final,sizeof(CDC_Final_params) },
	{ "Ccoff_Final",-1L,Ccoff_Final,setup_Ccoff_Final,initialize_Ccoff_Final,sizeof(Ccoff_Final_params) },
	{ "VPK",-1L,VPK,setup_VPK,initialize_VPK,sizeof(VPK_params) },
	{ "ADC_Final",-1L,ADC_Final,setup_ADC_Final,initialize_ADC_Final,sizeof(ADC_Final_params) },
	{ "DATT",-1L,DATT,setup_DATT,initialize_DATT,sizeof(DATT_params) },
	{ "zLast",-1L,zLast,setup_zLast,initialize_zLast,sizeof(zLast_params) },
	{ NULL,NULL }
};
// ASL_CREATE END_TEST_LIST_INIT}
