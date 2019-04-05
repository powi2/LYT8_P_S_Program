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
	{ "HBP_Pre_S",-1L,HBP_Pre_S,setup_HBP_Pre_S,initialize_HBP_Pre_S,sizeof(HBP_Pre_S_params) },
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
	{ "IOV_Pre_P",-1L,IOV_Pre_P,setup_IOV_Pre_P,initialize_IOV_Pre_P,sizeof(IOV_Pre_P_params) },
	{ "Fosc_Pre_P",-1L,Fosc_Pre_P,setup_Fosc_Pre_P,initialize_Fosc_Pre_P,sizeof(Fosc_Pre_P_params) },
	{ "TonMin_Pre_P",-1L,TonMin_Pre_P,setup_TonMin_Pre_P,initialize_TonMin_Pre_P,sizeof(TonMin_Pre_P_params) },
	{ "TonSlpOfst_Pre_P",-1L,TonSlpOfst_Pre_P,setup_TonSlpOfst_Pre_P,initialize_TonSlpOfst_Pre_P,sizeof(TonSlpOfst_Pre_P_params) },
	{ "ILIM_Pre_P",-1L,ILIM_Pre_P,setup_ILIM_Pre_P,initialize_ILIM_Pre_P,sizeof(ILIM_Pre_P_params) },
	{ "IUV_Pre_P",-1L,IUV_Pre_P,setup_IUV_Pre_P,initialize_IUV_Pre_P,sizeof(IUV_Pre_P_params) },
	{ "NTC_Pre_P",-1L,NTC_Pre_P,setup_NTC_Pre_P,initialize_NTC_Pre_P,sizeof(NTC_Pre_P_params) },
	{ "EEPROM_Burn_P",-1L,EEPROM_Burn_P,setup_EEPROM_Burn_P,initialize_EEPROM_Burn_P,sizeof(EEPROM_Burn_P_params) },
	{ "IOV_P",-1L,IOV_P,setup_IOV_P,initialize_IOV_P,sizeof(IOV_P_params) },
	{ "Fosc_P",-1L,Fosc_P,setup_Fosc_P,initialize_Fosc_P,sizeof(Fosc_P_params) },
	{ "TonMin_P",-1L,TonMin_P,setup_TonMin_P,initialize_TonMin_P,sizeof(TonMin_P_params) },
	{ "TonSlpOfst_P",-1L,TonSlpOfst_P,setup_TonSlpOfst_P,initialize_TonSlpOfst_P,sizeof(TonSlpOfst_P_params) },
	{ "ILIM_P",-1L,ILIM_P,setup_ILIM_P,initialize_ILIM_P,sizeof(ILIM_P_params) },
	{ "IUV_tUV_P",-1L,IUV_tUV_P,setup_IUV_tUV_P,initialize_IUV_tUV_P,sizeof(IUV_tUV_P_params) },
	{ "TSDetect_P",-1L,TSDetect_P,setup_TSDetect_P,initialize_TSDetect_P,sizeof(TSDetect_P_params) },
	{ "NTC_P",-1L,NTC_P,setup_NTC_P,initialize_NTC_P,sizeof(NTC_P_params) },
	{ "CV_Pre",-1L,CV_Pre,setup_CV_Pre,initialize_CV_Pre,sizeof(CV_Pre_params) },
	{ "VDDA_Pre",-1L,VDDA_Pre,setup_VDDA_Pre,initialize_VDDA_Pre,sizeof(VDDA_Pre_params) },
	{ "IRSET_Pre",-1L,IRSET_Pre,setup_IRSET_Pre,initialize_IRSET_Pre,sizeof(IRSET_Pre_params) },
	{ "ZTtimer_Pre",-1L,ZTtimer_Pre,setup_ZTtimer_Pre,initialize_ZTtimer_Pre,sizeof(ZTtimer_Pre_params) },
	{ "VADC_Pre",-1L,VADC_Pre,setup_VADC_Pre,initialize_VADC_Pre,sizeof(VADC_Pre_params) },
	{ "CLOCK1M_Pre",-1L,CLOCK1M_Pre,setup_CLOCK1M_Pre,initialize_CLOCK1M_Pre,sizeof(CLOCK1M_Pre_params) },
	{ "CCOffset_Pre",-1L,CCOffset_Pre,setup_CCOffset_Pre,initialize_CCOffset_Pre,sizeof(CCOffset_Pre_params) },
	{ "VccRef_Pre_S",-1L,VccRef_Pre_S,setup_VccRef_Pre_S,initialize_VccRef_Pre_S,sizeof(VccRef_Pre_S_params) },
	{ "ccPFOFF_Pre_S",-1L,ccPFOFF_Pre_S,setup_ccPFOFF_Pre_S,initialize_ccPFOFF_Pre_S,sizeof(ccPFOFF_Pre_S_params) },
	{ "Fosc_pt_S",-1L,Fosc_pt_S,setup_Fosc_pt_S,initialize_Fosc_pt_S,sizeof(Fosc_pt_S_params) },
	{ "BFreq_Pre_S",-1L,BFreq_Pre_S,setup_BFreq_Pre_S,initialize_BFreq_Pre_S,sizeof(BFreq_Pre_S_params) },
	{ "CP_Pre_S",-1L,CP_Pre_S,setup_CP_Pre_S,initialize_CP_Pre_S,sizeof(CP_Pre_S_params) },
	{ "VbILimit_Pre_S",-1L,VbILimit_Pre_S,setup_VbILimit_Pre_S,initialize_VbILimit_Pre_S,sizeof(VbILimit_Pre_S_params) },
	{ "EEPROM_S_Write",-1L,EEPROM_S_Write,setup_EEPROM_S_Write,initialize_EEPROM_S_Write,sizeof(EEPROM_S_Write_params) },
	{ "HBP_S",-1L,HBP_S,setup_HBP_S,initialize_HBP_S,sizeof(HBP_S_params) },
	{ "CV_Pst_S",-1L,CV_Pst_S,setup_CV_Pst_S,initialize_CV_Pst_S,sizeof(CV_Pst_S_params) },
	{ "VDDA_Pst_S",-1L,VDDA_Pst_S,setup_VDDA_Pst_S,initialize_VDDA_Pst_S,sizeof(VDDA_Pst_S_params) },
	{ "IRSET_Pst_S",-1L,IRSET_Pst_S,setup_IRSET_Pst_S,initialize_IRSET_Pst_S,sizeof(IRSET_Pst_S_params) },
	{ "ZTtimer_Pst_S",-1L,ZTtimer_Pst_S,setup_ZTtimer_Pst_S,initialize_ZTtimer_Pst_S,sizeof(ZTtimer_Pst_S_params) },
	{ "VADC_Pst_S",-1L,VADC_Pst_S,setup_VADC_Pst_S,initialize_VADC_Pst_S,sizeof(VADC_Pst_S_params) },
	{ "CLOCK1M_Pst_S",-1L,CLOCK1M_Pst_S,setup_CLOCK1M_Pst_S,initialize_CLOCK1M_Pst_S,sizeof(CLOCK1M_Pst_S_params) },
	{ "ccOffset_Pst_S",-1L,ccOffset_Pst_S,setup_ccOffset_Pst_S,initialize_ccOffset_Pst_S,sizeof(ccOffset_Pst_S_params) },
	{ "VccRef_Pst_S",-1L,VccRef_Pst_S,setup_VccRef_Pst_S,initialize_VccRef_Pst_S,sizeof(VccRef_Pst_S_params) },
	{ "ccPFOFF_Pst_S",-1L,ccPFOFF_Pst_S,setup_ccPFOFF_Pst_S,initialize_ccPFOFF_Pst_S,sizeof(ccPFOFF_Pst_S_params) },
	{ "Fosc_Pst_S",-1L,Fosc_Pst_S,setup_Fosc_Pst_S,initialize_Fosc_Pst_S,sizeof(Fosc_Pst_S_params) },
	{ "BFreq_Pst_S",-1L,BFreq_Pst_S,setup_BFreq_Pst_S,initialize_BFreq_Pst_S,sizeof(BFreq_Pst_S_params) },
	{ "CP_Pst_S",-1L,CP_Pst_S,setup_CP_Pst_S,initialize_CP_Pst_S,sizeof(CP_Pst_S_params) },
	{ "VbILimit_Pst_S",-1L,VbILimit_Pst_S,setup_VbILimit_Pst_S,initialize_VbILimit_Pst_S,sizeof(VbILimit_Pst_S_params) },
	{ "VR_Detect_S",-1L,VR_Detect_S,setup_VR_Detect_S,initialize_VR_Detect_S,sizeof(VR_Detect_S_params) },
	{ "VR_Det_01_S",-1L,VR_Det_01_S,setup_VR_Det_01_S,initialize_VR_Det_01_S,sizeof(VR_Det_01_S_params) },
	{ "VR_Det_02_S",-1L,VR_Det_02_S,setup_VR_Det_02_S,initialize_VR_Det_02_S,sizeof(VR_Det_02_S_params) },
	{ "VR_Det_03_S",-1L,VR_Det_03_S,setup_VR_Det_03_S,initialize_VR_Det_03_S,sizeof(VR_Det_03_S_params) },
	{ "VR_D_Ext_00_S",-1L,VR_D_Ext_00_S,setup_VR_D_Ext_00_S,initialize_VR_D_Ext_00_S,sizeof(VR_D_Ext_00_S_params) },
	{ "VR_D_Ext_01_S",-1L,VR_D_Ext_01_S,setup_VR_D_Ext_01_S,initialize_VR_D_Ext_01_S,sizeof(VR_D_Ext_01_S_params) },
	{ "VR_tDeglitch_S",-1L,VR_tDeglitch_S,setup_VR_tDeglitch_S,initialize_VR_tDeglitch_S,sizeof(VR_tDeglitch_S_params) },
	{ "ccTH_S",-1L,ccTH_S,setup_ccTH_S,initialize_ccTH_S,sizeof(ccTH_S_params) },
	{ "Fosc_MinJit_S",-1L,Fosc_MinJit_S,setup_Fosc_MinJit_S,initialize_Fosc_MinJit_S,sizeof(Fosc_MinJit_S_params) },
	{ "EEPROM_Pst",-1L,EEPROM_Pst,setup_EEPROM_Pst,initialize_EEPROM_Pst,sizeof(EEPROM_Pst_params) },
	{ "zLast",-1L,zLast,setup_zLast,initialize_zLast,sizeof(zLast_params) },
	{ NULL,NULL }
};
// ASL_CREATE END_TEST_LIST_INIT}
