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
    USHORT      REL_Enable;
    USHORT      TRIM_Enable;
    USHORT      TRIM_Voltage;
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
} HBP_Pre_S_params;


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
} TonMin_Slope_P_params;


typedef struct
{
    USHORT      fail_bin;
} ILIM_Pre_params;


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
} EEPROM_P_Burn_params;


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
} CCoff_Pt_params;


typedef struct
{
    double      NEW_PARAM;
} IsCal_Pt_params;


typedef struct
{
    double      NEW_PARAM;
} ADC_Pt_params;


typedef struct
{
    double      NEW_PARAM;
} EEPROM_Write_params;


typedef struct
{
    USHORT      fail_bin;
} IzPost_params;


typedef struct
{
    double      NEW_PARAM;
} SoftStart_params;


typedef struct
{
    USHORT      fail_bin;
} VBP_Supply_params;


typedef struct
{
    USHORT      fail_bin;
} IBP_Supply_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_IUV_OT_params;


typedef struct
{
    USHORT      fail_bin;
} FOSC_Ton_ARST_params;


typedef struct
{
    USHORT      fail_bin;
} FWPK_params;


typedef struct
{
    USHORT      fail_bin;
} SR_Delay_tREQinh_params;


typedef struct
{
    USHORT      fail_bin;
} SOA_SDS_TW50_params;


typedef struct
{
    double      NEW_PARAM;
} IsCal_Final_params;


typedef struct
{
    double      NEW_PARAM;
} Iout_params;


typedef struct
{
    double      NEW_PARAM;
} CV_nDAC_pDAC_params;


typedef struct
{
    USHORT      fail_bin;
} Vesr_params;


typedef struct
{
    USHORT      fail_bin;
} Isvth3X_AR_ISSC_params;


typedef struct
{
    double      NEW_PARAM;
} Vovp_params;


typedef struct
{
    double      NEW_PARAM;
} UVP_params;


typedef struct
{
    double      NEW_PARAM;
} VBD_uVCC_params;


typedef struct
{
    double      NEW_PARAM;
} OSC_Final_params;


typedef struct
{
    double      NEW_PARAM;
} DofA_Final_params;


typedef struct
{
    double      NEW_PARAM;
} IsDAC_Final_params;


typedef struct
{
    double      NEW_PARAM;
} Gain_Final_params;


typedef struct
{
    double      NEW_PARAM;
} CDC_Final_params;


typedef struct
{
    double      NEW_PARAM;
} Ccoff_Final_params;


typedef struct
{
    double      NEW_PARAM;
} VPK_params;


typedef struct
{
    double      NEW_PARAM;
} ADC_Final_params;


typedef struct
{
    USHORT      fail_bin;
} DATT_params;


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

/////////// HBP_Pre_S ///////////////////////////////////////////////////////
void HBP_Pre_S(test_function &func);
void initialize_HBP_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_HBP_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

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

/////////// TonMin_Slope_P ///////////////////////////////////////////////////////
void TonMin_Slope_P(test_function &func);
void initialize_TonMin_Slope_P(short test_entry, test_function &func, char **func_name);
void setup_TonMin_Slope_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM_Pre ///////////////////////////////////////////////////////
void ILIM_Pre(test_function &func);
void initialize_ILIM_Pre(short test_entry, test_function &func, char **func_name);
void setup_ILIM_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IUV_Pre_P ///////////////////////////////////////////////////////
void IUV_Pre_P(test_function &func);
void initialize_IUV_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_IUV_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// NTC_Pre_P ///////////////////////////////////////////////////////
void NTC_Pre_P(test_function &func);
void initialize_NTC_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_NTC_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_P_Burn ///////////////////////////////////////////////////////
void EEPROM_P_Burn(test_function &func);
void initialize_EEPROM_P_Burn(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_P_Burn(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

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

/////////// CCoff_Pt ///////////////////////////////////////////////////////
void CCoff_Pt(test_function &func);
void initialize_CCoff_Pt(short test_entry, test_function &func, char **func_name);
void setup_CCoff_Pt(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IsCal_Pt ///////////////////////////////////////////////////////
void IsCal_Pt(test_function &func);
void initialize_IsCal_Pt(short test_entry, test_function &func, char **func_name);
void setup_IsCal_Pt(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ADC_Pt ///////////////////////////////////////////////////////
void ADC_Pt(test_function &func);
void initialize_ADC_Pt(short test_entry, test_function &func, char **func_name);
void setup_ADC_Pt(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// EEPROM_Write ///////////////////////////////////////////////////////
void EEPROM_Write(test_function &func);
void initialize_EEPROM_Write(short test_entry, test_function &func, char **func_name);
void setup_EEPROM_Write(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IzPost ///////////////////////////////////////////////////////
void IzPost(test_function &func);
void initialize_IzPost(short test_entry, test_function &func, char **func_name);
void setup_IzPost(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SoftStart ///////////////////////////////////////////////////////
void SoftStart(test_function &func);
void initialize_SoftStart(short test_entry, test_function &func, char **func_name);
void setup_SoftStart(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VBP_Supply ///////////////////////////////////////////////////////
void VBP_Supply(test_function &func);
void initialize_VBP_Supply(short test_entry, test_function &func, char **func_name);
void setup_VBP_Supply(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IBP_Supply ///////////////////////////////////////////////////////
void IBP_Supply(test_function &func);
void initialize_IBP_Supply(short test_entry, test_function &func, char **func_name);
void setup_IBP_Supply(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_IUV_OT ///////////////////////////////////////////////////////
void IOV_IUV_OT(test_function &func);
void initialize_IOV_IUV_OT(short test_entry, test_function &func, char **func_name);
void setup_IOV_IUV_OT(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// FOSC_Ton_ARST ///////////////////////////////////////////////////////
void FOSC_Ton_ARST(test_function &func);
void initialize_FOSC_Ton_ARST(short test_entry, test_function &func, char **func_name);
void setup_FOSC_Ton_ARST(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// FWPK ///////////////////////////////////////////////////////
void FWPK(test_function &func);
void initialize_FWPK(short test_entry, test_function &func, char **func_name);
void setup_FWPK(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SR_Delay_tREQinh ///////////////////////////////////////////////////////
void SR_Delay_tREQinh(test_function &func);
void initialize_SR_Delay_tREQinh(short test_entry, test_function &func, char **func_name);
void setup_SR_Delay_tREQinh(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SOA_SDS_TW50 ///////////////////////////////////////////////////////
void SOA_SDS_TW50(test_function &func);
void initialize_SOA_SDS_TW50(short test_entry, test_function &func, char **func_name);
void setup_SOA_SDS_TW50(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IsCal_Final ///////////////////////////////////////////////////////
void IsCal_Final(test_function &func);
void initialize_IsCal_Final(short test_entry, test_function &func, char **func_name);
void setup_IsCal_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Iout ///////////////////////////////////////////////////////
void Iout(test_function &func);
void initialize_Iout(short test_entry, test_function &func, char **func_name);
void setup_Iout(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CV_nDAC_pDAC ///////////////////////////////////////////////////////
void CV_nDAC_pDAC(test_function &func);
void initialize_CV_nDAC_pDAC(short test_entry, test_function &func, char **func_name);
void setup_CV_nDAC_pDAC(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Vesr ///////////////////////////////////////////////////////
void Vesr(test_function &func);
void initialize_Vesr(short test_entry, test_function &func, char **func_name);
void setup_Vesr(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Isvth3X_AR_ISSC ///////////////////////////////////////////////////////
void Isvth3X_AR_ISSC(test_function &func);
void initialize_Isvth3X_AR_ISSC(short test_entry, test_function &func, char **func_name);
void setup_Isvth3X_AR_ISSC(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Vovp ///////////////////////////////////////////////////////
void Vovp(test_function &func);
void initialize_Vovp(short test_entry, test_function &func, char **func_name);
void setup_Vovp(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// UVP ///////////////////////////////////////////////////////
void UVP(test_function &func);
void initialize_UVP(short test_entry, test_function &func, char **func_name);
void setup_UVP(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VBD_uVCC ///////////////////////////////////////////////////////
void VBD_uVCC(test_function &func);
void initialize_VBD_uVCC(short test_entry, test_function &func, char **func_name);
void setup_VBD_uVCC(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// OSC_Final ///////////////////////////////////////////////////////
void OSC_Final(test_function &func);
void initialize_OSC_Final(short test_entry, test_function &func, char **func_name);
void setup_OSC_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// DofA_Final ///////////////////////////////////////////////////////
void DofA_Final(test_function &func);
void initialize_DofA_Final(short test_entry, test_function &func, char **func_name);
void setup_DofA_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IsDAC_Final ///////////////////////////////////////////////////////
void IsDAC_Final(test_function &func);
void initialize_IsDAC_Final(short test_entry, test_function &func, char **func_name);
void setup_IsDAC_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Gain_Final ///////////////////////////////////////////////////////
void Gain_Final(test_function &func);
void initialize_Gain_Final(short test_entry, test_function &func, char **func_name);
void setup_Gain_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// CDC_Final ///////////////////////////////////////////////////////
void CDC_Final(test_function &func);
void initialize_CDC_Final(short test_entry, test_function &func, char **func_name);
void setup_CDC_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Ccoff_Final ///////////////////////////////////////////////////////
void Ccoff_Final(test_function &func);
void initialize_Ccoff_Final(short test_entry, test_function &func, char **func_name);
void setup_Ccoff_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VPK ///////////////////////////////////////////////////////
void VPK(test_function &func);
void initialize_VPK(short test_entry, test_function &func, char **func_name);
void setup_VPK(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ADC_Final ///////////////////////////////////////////////////////
void ADC_Final(test_function &func);
void initialize_ADC_Final(short test_entry, test_function &func, char **func_name);
void setup_ADC_Final(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// DATT ///////////////////////////////////////////////////////
void DATT(test_function &func);
void initialize_DATT(short test_entry, test_function &func, char **func_name);
void setup_DATT(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// zLast ///////////////////////////////////////////////////////
void zLast(test_function &func);
void initialize_zLast(short test_entry, test_function &func, char **func_name);
void setup_zLast(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);


#include "USER.H"
