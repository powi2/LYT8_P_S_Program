//==============================================================================
// FUNCTION.H 
//==============================================================================

// ********************************************************************
// For each individual test function, define a structure that holds all of its parameters.

typedef struct
{
    USHORT      Loop_wait;
    USHORT      Rewrite_EPROM;
    USHORT      fNum_DlogEnable;
    USHORT      TestTime_Enable;
    USHORT      GRR_Enable;
    USHORT      CHAR_Enable;
    USHORT      CHAR_TEMP;
    USHORT      REL_Enable;
    USHORT      force_ERASE_P;
    USHORT      force_ERASE_S;
    USHORT      BURN_Enable_P;
    USHORT      BURN_Enable_S;
    USHORT      Sim_Enable_P;
    USHORT      Sim_Enable_S;
    short       IOV_Code_P;
    short       FOSC_Code_P;
    short       TonMin_Code_P;
    short       Slope_Code_P;
    short       Offset_Code_P;
    short       Ilim_Code_P;
    short       UV_Code_P;
    short       NTC_Code_P;
    short       VDDA_Code_S;
    short       VREF_Code_S;
    short       IRSET_Code_S;
    short       nDAC_Code_S;
    short       ZTime_Code_S;
    short       VADC_Code_S;
    short       Clock1M_Code_S;
    short       CCoffset_Code_S;
    short       VccRef_Code_S;
    short       CCPFOFF_Code_S;
    short       FOSC_Code_S;
    short       BFreq_Code_S;
    short       CP_Code_S;
    short       VbILimit_Code_S;
    float       ExtraParam1;
    float       ExtraParam2;
} First_params;


typedef struct
{
    USHORT      fail_bin;
} Continuity_params;


typedef struct
{
    USHORT      fail_bin;
} Leakage_params;


typedef struct
{
    USHORT      fail_bin;
} EEprom_DevID_params;


typedef struct
{
    USHORT      fail_bin;
} HBP_Pre_S_params;


typedef struct
{
    USHORT      fail_bin;
} Scan_Pre_Stress_params;


typedef struct
{
    USHORT      fail_bin;
} Is_Pre_Stress_params;


typedef struct
{
    USHORT      fail_bin;
    float       vStress;
} STRESS_params;


typedef struct
{
    USHORT      fail_bin;
} Is_Post_Stress_params;


typedef struct
{
    double      NEW_PARAM;
} Scan_Post_Stress_params;


typedef struct
{
    USHORT      fail_bin;
} Leakage_Post_Stress_params;


typedef struct
{
    USHORT      fail_bin;
    double      BV_Clamp;
    double      BV_stress_time;
} BV_Vpin_params;


typedef struct
{
    USHORT      fail_bin;
    double      BVD_D_Clamp;
    double      BVD_stress_time;
} BV_Drain_params;


typedef struct
{
    USHORT      fail_bin;
} VBP_Init_params;


typedef struct
{
    USHORT      fail_bin;
} EEPROM_Pre_params;


typedef struct
{
    USHORT      fail_bin;
} Feature_Trim_P_params;


typedef struct
{
    bool        Manual_Prog;
    short       tsstart_B_8_9_S;
    short       tfbOption_B_10_11_S;
    short       DOPL_B_15_S;
    short       TvrOption_B_16_17_S;
    short       tenCP_B_18_S;
    short       zffOption_B_19_20_S;
    short       DsblJitDim_B_21_S;
    short       JitterOff_B_22_S;
    short       ZTMBStr_B_29_30_S;
    short       DsblFlBck_B_31_S;
    short       DimTh_B_47_S;
    short       tHrtBtOpt_B_61_S;
    short       CPNonI2C_B_62_S;
    short       Zee_50KStr_B_63_S;
    short       FlBck_Ccopt_B_74_S;
    short       FlBck_Sel_B_75_S;
    USHORT      fail_bin;
} Feature_Trim_S_params;


typedef struct
{
    double      NEW_PARAM;
} BPS_STRESS_params;


typedef struct
{
    double      NEW_PARAM;
} BPP_STRESS_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} TonMin_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} TonSlpOfst_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} ILIM_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} IUV_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
} NTC_Pre_P_params;


typedef struct
{
    double      NEW_PARAM;
} EEPROM_Burn_P_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_P_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_P_params;


typedef struct
{
    USHORT      fail_bin;
} TonMin_P_params;


typedef struct
{
    USHORT      fail_bin;
} TonSlpOfst_P_params;


typedef struct
{
    USHORT      fail_bin;
} ILIM_P_params;


typedef struct
{
    USHORT      fail_bin;
} IUV_tUV_P_params;


typedef struct
{
    USHORT      fail_bin;
} TSDetect_P_params;


typedef struct
{
    USHORT      fail_bin;
} NTC_P_params;


typedef struct
{
    USHORT      fail_bin;
} CV_Pre_params;


typedef struct
{
    USHORT      fail_bin;
} VDDA_Pre_params;


typedef struct
{
    bool        Debug;
    float       V_tmp;
    float       I_tmp;
} IRSET_Pre_params;


typedef struct
{
    double      NEW_PARAM;
} ZTtimer_Pre_params;


typedef struct
{
    double      NEW_PARAM;
} VADC_Pre_params;


typedef struct
{
    double      NEW_PARAM;
} CLOCK1M_Pre_params;


typedef struct
{
    double      NEW_PARAM;
} CCOffset_Pre_params;


typedef struct
{
    USHORT      fail_bin;
} VccRef_Pre_S_params;


typedef struct
{
    double      NEW_PARAM;
} ccPFOFF_Pre_S_params;


typedef struct
{
    double      NEW_PARAM;
} Fosc_pt_S_params;


typedef struct
{
    double      NEW_PARAM;
} BFreq_Pre_S_params;


typedef struct
{
    double      NEW_PARAM;
} CP_Pre_S_params;


typedef struct
{
    double      NEW_PARAM;
} VbILimit_Pre_S_params;


typedef struct
{
    double      NEW_PARAM;
} EEPROM_S_Write_params;


typedef struct
{
    USHORT      fail_bin;
} HBP_S_params;


typedef struct
{
    double      NEW_PARAM;
} CV_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} VDDA_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} IRSET_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} ZTtimer_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} VADC_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} CLOCK1M_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} ccOffset_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} VccRef_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} ccPFOFF_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} Fosc_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} BFreq_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} CP_Pst_S_params;


typedef struct
{
    double      NEW_PARAM;
} VbILimit_Pst_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_Detect_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_Det_01_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_Det_02_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_Det_03_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_D_Ext_00_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_D_Ext_01_S_params;


typedef struct
{
    USHORT      fail_bin;
} VR_tDeglitch_S_params;


typedef struct
{
    double      NEW_PARAM;
} ccTH_S_params;


typedef struct
{
    double      NEW_PARAM;
} Fosc_MinJit_S_params;


typedef struct
{
    USHORT      fail_bin;
} EEPROM_Pst_params;


typedef struct
{
    USHORT      fail_bin;
} zLast_params;

// ********************************************************************
// Now pre-define the routines used in program development

/////////// First ///////////////////////////////////////////////////////
void First(test_function &func);
void initialize_First(short test_entry, test_function &func, char **func_name);
void setup_First(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Continuity ///////////////////////////////////////////////////////
void Continuity(test_function &func);
void initialize_Continuity(short test_entry, test_function &func, char **func_name);
void setup_Continuity(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Leakage ///////////////////////////////////////////////////////
void Leakage(test_function &func);
void initialize_Leakage(short test_entry, test_function &func, char **func_name);
void setup_Leakage(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEprom_DevID ///////////////////////////////////////////////////////
void EEprom_DevID(test_function &func);
void initialize_EEprom_DevID(short test_entry, test_function &func, char **func_name);
void setup_EEprom_DevID(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// HBP_Pre_S ///////////////////////////////////////////////////////
void HBP_Pre_S(test_function &func);
void initialize_HBP_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_HBP_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Scan_Pre_Stress ///////////////////////////////////////////////////////
void Scan_Pre_Stress(test_function &func);
void initialize_Scan_Pre_Stress(short test_entry, test_function &func, char **func_name);
void setup_Scan_Pre_Stress(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Is_Pre_Stress ///////////////////////////////////////////////////////
void Is_Pre_Stress(test_function &func);
void initialize_Is_Pre_Stress(short test_entry, test_function &func, char **func_name);
void setup_Is_Pre_Stress(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// STRESS ///////////////////////////////////////////////////////
void STRESS(test_function &func);
void initialize_STRESS(short test_entry, test_function &func, char **func_name);
void setup_STRESS(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Is_Post_Stress ///////////////////////////////////////////////////////
void Is_Post_Stress(test_function &func);
void initialize_Is_Post_Stress(short test_entry, test_function &func, char **func_name);
void setup_Is_Post_Stress(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Scan_Post_Stress ///////////////////////////////////////////////////////
void Scan_Post_Stress(test_function &func);
void initialize_Scan_Post_Stress(short test_entry, test_function &func, char **func_name);
void setup_Scan_Post_Stress(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Leakage_Post_Stress ///////////////////////////////////////////////////////
void Leakage_Post_Stress(test_function &func);
void initialize_Leakage_Post_Stress(short test_entry, test_function &func, char **func_name);
void setup_Leakage_Post_Stress(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_Vpin ///////////////////////////////////////////////////////
void BV_Vpin(test_function &func);
void initialize_BV_Vpin(short test_entry, test_function &func, char **func_name);
void setup_BV_Vpin(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_Drain ///////////////////////////////////////////////////////
void BV_Drain(test_function &func);
void initialize_BV_Drain(short test_entry, test_function &func, char **func_name);
void setup_BV_Drain(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VBP_Init ///////////////////////////////////////////////////////
void VBP_Init(test_function &func);
void initialize_VBP_Init(short test_entry, test_function &func, char **func_name);
void setup_VBP_Init(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_Pre ///////////////////////////////////////////////////////
void EEPROM_Pre(test_function &func);
void initialize_EEPROM_Pre(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Feature_Trim_P ///////////////////////////////////////////////////////
void Feature_Trim_P(test_function &func);
void initialize_Feature_Trim_P(short test_entry, test_function &func, char **func_name);
void setup_Feature_Trim_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Feature_Trim_S ///////////////////////////////////////////////////////
void Feature_Trim_S(test_function &func);
void initialize_Feature_Trim_S(short test_entry, test_function &func, char **func_name);
void setup_Feature_Trim_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BPS_STRESS ///////////////////////////////////////////////////////
void BPS_STRESS(test_function &func);
void initialize_BPS_STRESS(short test_entry, test_function &func, char **func_name);
void setup_BPS_STRESS(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BPP_STRESS ///////////////////////////////////////////////////////
void BPP_STRESS(test_function &func);
void initialize_BPP_STRESS(short test_entry, test_function &func, char **func_name);
void setup_BPP_STRESS(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_Pre_P ///////////////////////////////////////////////////////
void IOV_Pre_P(test_function &func);
void initialize_IOV_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_IOV_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Pre_P ///////////////////////////////////////////////////////
void Fosc_Pre_P(test_function &func);
void initialize_Fosc_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TonMin_Pre_P ///////////////////////////////////////////////////////
void TonMin_Pre_P(test_function &func);
void initialize_TonMin_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_TonMin_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TonSlpOfst_Pre_P ///////////////////////////////////////////////////////
void TonSlpOfst_Pre_P(test_function &func);
void initialize_TonSlpOfst_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_TonSlpOfst_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM_Pre_P ///////////////////////////////////////////////////////
void ILIM_Pre_P(test_function &func);
void initialize_ILIM_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_ILIM_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IUV_Pre_P ///////////////////////////////////////////////////////
void IUV_Pre_P(test_function &func);
void initialize_IUV_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_IUV_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// NTC_Pre_P ///////////////////////////////////////////////////////
void NTC_Pre_P(test_function &func);
void initialize_NTC_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_NTC_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_Burn_P ///////////////////////////////////////////////////////
void EEPROM_Burn_P(test_function &func);
void initialize_EEPROM_Burn_P(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_Burn_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_P ///////////////////////////////////////////////////////
void IOV_P(test_function &func);
void initialize_IOV_P(short test_entry, test_function &func, char **func_name);
void setup_IOV_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_P ///////////////////////////////////////////////////////
void Fosc_P(test_function &func);
void initialize_Fosc_P(short test_entry, test_function &func, char **func_name);
void setup_Fosc_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TonMin_P ///////////////////////////////////////////////////////
void TonMin_P(test_function &func);
void initialize_TonMin_P(short test_entry, test_function &func, char **func_name);
void setup_TonMin_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TonSlpOfst_P ///////////////////////////////////////////////////////
void TonSlpOfst_P(test_function &func);
void initialize_TonSlpOfst_P(short test_entry, test_function &func, char **func_name);
void setup_TonSlpOfst_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM_P ///////////////////////////////////////////////////////
void ILIM_P(test_function &func);
void initialize_ILIM_P(short test_entry, test_function &func, char **func_name);
void setup_ILIM_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IUV_tUV_P ///////////////////////////////////////////////////////
void IUV_tUV_P(test_function &func);
void initialize_IUV_tUV_P(short test_entry, test_function &func, char **func_name);
void setup_IUV_tUV_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TSDetect_P ///////////////////////////////////////////////////////
void TSDetect_P(test_function &func);
void initialize_TSDetect_P(short test_entry, test_function &func, char **func_name);
void setup_TSDetect_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// NTC_P ///////////////////////////////////////////////////////
void NTC_P(test_function &func);
void initialize_NTC_P(short test_entry, test_function &func, char **func_name);
void setup_NTC_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CV_Pre ///////////////////////////////////////////////////////
void CV_Pre(test_function &func);
void initialize_CV_Pre(short test_entry, test_function &func, char **func_name);
void setup_CV_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VDDA_Pre ///////////////////////////////////////////////////////
void VDDA_Pre(test_function &func);
void initialize_VDDA_Pre(short test_entry, test_function &func, char **func_name);
void setup_VDDA_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IRSET_Pre ///////////////////////////////////////////////////////
void IRSET_Pre(test_function &func);
void initialize_IRSET_Pre(short test_entry, test_function &func, char **func_name);
void setup_IRSET_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ZTtimer_Pre ///////////////////////////////////////////////////////
void ZTtimer_Pre(test_function &func);
void initialize_ZTtimer_Pre(short test_entry, test_function &func, char **func_name);
void setup_ZTtimer_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VADC_Pre ///////////////////////////////////////////////////////
void VADC_Pre(test_function &func);
void initialize_VADC_Pre(short test_entry, test_function &func, char **func_name);
void setup_VADC_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CLOCK1M_Pre ///////////////////////////////////////////////////////
void CLOCK1M_Pre(test_function &func);
void initialize_CLOCK1M_Pre(short test_entry, test_function &func, char **func_name);
void setup_CLOCK1M_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CCOffset_Pre ///////////////////////////////////////////////////////
void CCOffset_Pre(test_function &func);
void initialize_CCOffset_Pre(short test_entry, test_function &func, char **func_name);
void setup_CCOffset_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VccRef_Pre_S ///////////////////////////////////////////////////////
void VccRef_Pre_S(test_function &func);
void initialize_VccRef_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_VccRef_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ccPFOFF_Pre_S ///////////////////////////////////////////////////////
void ccPFOFF_Pre_S(test_function &func);
void initialize_ccPFOFF_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_ccPFOFF_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_pt_S ///////////////////////////////////////////////////////
void Fosc_pt_S(test_function &func);
void initialize_Fosc_pt_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_pt_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BFreq_Pre_S ///////////////////////////////////////////////////////
void BFreq_Pre_S(test_function &func);
void initialize_BFreq_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_BFreq_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CP_Pre_S ///////////////////////////////////////////////////////
void CP_Pre_S(test_function &func);
void initialize_CP_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_CP_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VbILimit_Pre_S ///////////////////////////////////////////////////////
void VbILimit_Pre_S(test_function &func);
void initialize_VbILimit_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_VbILimit_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_S_Write ///////////////////////////////////////////////////////
void EEPROM_S_Write(test_function &func);
void initialize_EEPROM_S_Write(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_S_Write(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// HBP_S ///////////////////////////////////////////////////////
void HBP_S(test_function &func);
void initialize_HBP_S(short test_entry, test_function &func, char **func_name);
void setup_HBP_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CV_Pst_S ///////////////////////////////////////////////////////
void CV_Pst_S(test_function &func);
void initialize_CV_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_CV_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VDDA_Pst_S ///////////////////////////////////////////////////////
void VDDA_Pst_S(test_function &func);
void initialize_VDDA_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_VDDA_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IRSET_Pst_S ///////////////////////////////////////////////////////
void IRSET_Pst_S(test_function &func);
void initialize_IRSET_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_IRSET_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ZTtimer_Pst_S ///////////////////////////////////////////////////////
void ZTtimer_Pst_S(test_function &func);
void initialize_ZTtimer_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_ZTtimer_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VADC_Pst_S ///////////////////////////////////////////////////////
void VADC_Pst_S(test_function &func);
void initialize_VADC_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_VADC_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CLOCK1M_Pst_S ///////////////////////////////////////////////////////
void CLOCK1M_Pst_S(test_function &func);
void initialize_CLOCK1M_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_CLOCK1M_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ccOffset_Pst_S ///////////////////////////////////////////////////////
void ccOffset_Pst_S(test_function &func);
void initialize_ccOffset_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_ccOffset_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VccRef_Pst_S ///////////////////////////////////////////////////////
void VccRef_Pst_S(test_function &func);
void initialize_VccRef_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_VccRef_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ccPFOFF_Pst_S ///////////////////////////////////////////////////////
void ccPFOFF_Pst_S(test_function &func);
void initialize_ccPFOFF_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_ccPFOFF_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Pst_S ///////////////////////////////////////////////////////
void Fosc_Pst_S(test_function &func);
void initialize_Fosc_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BFreq_Pst_S ///////////////////////////////////////////////////////
void BFreq_Pst_S(test_function &func);
void initialize_BFreq_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_BFreq_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CP_Pst_S ///////////////////////////////////////////////////////
void CP_Pst_S(test_function &func);
void initialize_CP_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_CP_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VbILimit_Pst_S ///////////////////////////////////////////////////////
void VbILimit_Pst_S(test_function &func);
void initialize_VbILimit_Pst_S(short test_entry, test_function &func, char **func_name);
void setup_VbILimit_Pst_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_Detect_S ///////////////////////////////////////////////////////
void VR_Detect_S(test_function &func);
void initialize_VR_Detect_S(short test_entry, test_function &func, char **func_name);
void setup_VR_Detect_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_Det_01_S ///////////////////////////////////////////////////////
void VR_Det_01_S(test_function &func);
void initialize_VR_Det_01_S(short test_entry, test_function &func, char **func_name);
void setup_VR_Det_01_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_Det_02_S ///////////////////////////////////////////////////////
void VR_Det_02_S(test_function &func);
void initialize_VR_Det_02_S(short test_entry, test_function &func, char **func_name);
void setup_VR_Det_02_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_Det_03_S ///////////////////////////////////////////////////////
void VR_Det_03_S(test_function &func);
void initialize_VR_Det_03_S(short test_entry, test_function &func, char **func_name);
void setup_VR_Det_03_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_D_Ext_00_S ///////////////////////////////////////////////////////
void VR_D_Ext_00_S(test_function &func);
void initialize_VR_D_Ext_00_S(short test_entry, test_function &func, char **func_name);
void setup_VR_D_Ext_00_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_D_Ext_01_S ///////////////////////////////////////////////////////
void VR_D_Ext_01_S(test_function &func);
void initialize_VR_D_Ext_01_S(short test_entry, test_function &func, char **func_name);
void setup_VR_D_Ext_01_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VR_tDeglitch_S ///////////////////////////////////////////////////////
void VR_tDeglitch_S(test_function &func);
void initialize_VR_tDeglitch_S(short test_entry, test_function &func, char **func_name);
void setup_VR_tDeglitch_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ccTH_S ///////////////////////////////////////////////////////
void ccTH_S(test_function &func);
void initialize_ccTH_S(short test_entry, test_function &func, char **func_name);
void setup_ccTH_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_MinJit_S ///////////////////////////////////////////////////////
void Fosc_MinJit_S(test_function &func);
void initialize_Fosc_MinJit_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_MinJit_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_Pst ///////////////////////////////////////////////////////
void EEPROM_Pst(test_function &func);
void initialize_EEPROM_Pst(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_Pst(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// zLast ///////////////////////////////////////////////////////
void zLast(test_function &func);
void initialize_zLast(short test_entry, test_function &func, char **func_name);
void setup_zLast(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);


#include "USER.H"
