//==============================================================================
// First.cpp (User function)
// 
//    void First_user_init(test_function& func)
//    void First(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable :4305)


#include "First.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void First_user_init(test_function& func)
{
	First_params *ours;
    ours = (First_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void First(test_function& func)
{
    // The two lines below must be the first two in the function.
    First_params *ours;
    ours = (First_params *)func.params;


	// Test Names //
	int fNum_Setup = 0;
	float Setup = 0;
	int Site = 0;
	float ProcessorType = 0;
	int Loadboard_ID = 0;
	//int Loadboard_Rev = 0;
	int Inductor_ID = 0;
	int Inductor_Rev = 0;
	int Contactor_ID = 0;
	//int Contactor_Rev = 0;
	int Handsockt_ID = 0;
	int Handsockt_Rev = 0;
	float p_Loop_wait = 0;

	int p_IOV_Code_P      = 0;
	int p_FOSC_Code_P     = 0;
	int p_TonMin_Code_P   = 0;
	int p_Slope_Code_P    = 0;
	int p_Offset_Code_P   = 0;
	int p_ILIM_Code_P     = 0;
	int p_UV_Code_P       = 0;
    int p_NTC_Code_P      = 0;

	int p_VDDA_Code_S     = 0;
	int p_VREF_Code_S     = 0;
	int p_IRSET_Code_S    = 0;
	int p_nDAC_Code_S     = 0;
	int p_ZTime_Code_S    = 0;
	int p_VADC_Code_S     = 0;
	int p_Clock1M_Code_S  = 0;
	int p_CCoffset_Code_S = 0;
	int p_VccRef_Code_S   = 0;
    int p_CCPFOFF_Code_S  = 0;
	int p_FOSC_Code_S     = 0;
	int p_BFreq_Code_S    = 0;
	int p_CP_Code_S       = 0;
	int p_VbILimit_Code_S = 0;

	int p_TstTime_Enble = 0;
	int p_Rewrite_EPROM = 0;
	float p_ExtraParam1 = 0;
	float p_ExtraParam2 = 0;
	float iPV3_Cal_CC90 = 0;
	float iPV3_Cal_CC80 = 0;
	float iPV3_Cal_CC65 = 0;
	float iPV3_Cal_CC55 = 0;
	float DVI2K_ch0_Temp = 0;
	float DVI2K_ch1_Temp = 0;
	float First_TT = 0;

	g_GRR          = 0;
	g_HBP_P_S	   = 0;
	g_HBP_Pre_S    = 0;
	g_CV_Pre       = 0;
	g_VDDA_Pre     = 0;
	g_IRSET_Pre    = 0;
	g_ZTtimer_Pre  = 0;
	g_VADC_Pre     = 0;
	g_CLK1M_Pre    = 0;
	g_CCOffset_Pre = 0;
	g_VccRef_Pre   = 0;
	g_ccPFOFF_Pre  = 0;
	g_Fosc_Pre     = 0;
	g_BFreq_Pre    = 0;
	g_CP_IS_Pre    = 0;
	g_VbIlim_Pre   = 0;
	//g_DOPL_Primary = 0;

	g_Pre_E0_data_P = 0;
	g_Pre_E2_data_P = 0;
	g_Pre_E4_data_P = 0;
	g_Pre_E6_data_P = 0;
	g_Pre_E8_data_P = 0;
		
	g_Pre_E0_data_S = 0;
	g_Pre_E2_data_S = 0;
	g_Pre_E4_data_S = 0;
	g_Pre_E6_data_S = 0;
	g_Pre_E8_data_S = 0;

	// Declare Variables //

	g_Char_Enable_S=0;

	if(ours->CHAR_Enable == 2||ours->CHAR_Enable == 3)  g_Char_Enable_S=1;

	if(ours->GRR_Enable)   g_GRR = 1;

	//if(ours->ExtraParam1 > 0) g_DOPL_Primary = 1;

	int BUFRes_Div_ratio =0.0;
	float ical_frc =0.0;
	int i = 0;
	float Site_Current = 0;
	float TempVmeas = 0;
	//float R1_current = 0;
	//float R1_ohms = 0;
	char STRINGarray[1024] = {'\0'};//buffer to store formatted input.
	//float DSM_Library_Version = 0;
	//float DSM_Firmware_Version = 0;
	//float FWmeasV = 0;


	// Load pass parameters //
	gDisplay_FuncNum  = ours->fNum_DlogEnable;
	p_Loop_wait       = ours->Loop_wait;
	g_Char_Enable_P   = ours->CHAR_Enable;
	g_Rel_Enable_P    = ours->REL_Enable;
	p_IOV_Code_P      = ours->IOV_Code_P;
	p_FOSC_Code_P     = ours->FOSC_Code_P;
	p_TonMin_Code_P   = ours->TonMin_Code_P;
	p_Slope_Code_P    = ours->Slope_Code_P;
	p_Offset_Code_P   = ours->Offset_Code_P;
	p_ILIM_Code_P     = ours->Ilim_Code_P;
	p_UV_Code_P       = ours->UV_Code_P;
    p_NTC_Code_P      = ours->NTC_Code_P;

	p_VDDA_Code_S     = ours->VDDA_Code_S;
	p_VREF_Code_S     = ours->VREF_Code_S;
	p_IRSET_Code_S    = ours->IRSET_Code_S;
	p_nDAC_Code_S     = ours->nDAC_Code_S;
	p_ZTime_Code_S    = ours->ZTime_Code_S;
	p_VADC_Code_S     = ours->VADC_Code_S;
	p_Clock1M_Code_S  = ours->Clock1M_Code_S;
	p_CCoffset_Code_S = ours->CCoffset_Code_S;
	p_VccRef_Code_S   = ours->VccRef_Code_S;
    p_CCPFOFF_Code_S  = ours->CCPFOFF_Code_S;
	p_FOSC_Code_S     = ours->FOSC_Code_S;
	p_BFreq_Code_S    = ours->BFreq_Code_S;
	p_CP_Code_S       = ours->CP_Code_S;
	p_VbILimit_Code_S = ours->VbILimit_Code_S;

	g_Burn_Enable_P = ours->BURN_Enable_P;
	g_TstTime_Enble_P = ours->TestTime_Enable;
	p_Rewrite_EPROM = ours->Rewrite_EPROM;
	p_ExtraParam1 = ours->ExtraParam1;
	p_ExtraParam2 = ours->ExtraParam2;

	gFuncNum=1;
	if(gDisplay_FuncNum)
	{
		PiDatalog(func, A_fNum_First, gFuncNum, 31, POWER_UNIT);
	}

	if (g_Fn_aFirst == 0 )  return;


	// Initialize timer to zero //
	g_mytimer.Start();

	// Test Time Begin //
	g_begintime = g_mytimer.GetElapsedTime();


	Pulse pulse;

	//---------------------------------------------------
	//Global Variables
	//---------------------------------------------------

	g_Require_PartID = false;

	//Global Characterization variables
	g_Char_iOVp_XYplot = 0;
	g_Char_iOVm_XYplot = 0;
	g_USE_VR_600K = false;

	//Global digitizer Awav and Text variables
	g_Save_Awav_TextDebug_ALL		= 0;
	g_Save_Awav_TextDebug_Dtemp		= 1;

	



	hvs_15->init();

	g_vDSM_pullup_P = 3.3;
	g_vDSM_pullup_S = 3.3;
	g_DDD_Period	= 1e-6;

	//Global Erase/Burn Delays
	g_Erase_dly_P	= 5;	//ms
	g_Burn_dly_P	= 5;	//ms
	g_Erase_dly_S	= 5;	//ms
	g_Burn_dly_S	= 5;	//ms


	//Global search thresholds
	g_vDrain_Erase_th_P = 0;
	g_vDrain_Burn_th_P = 0;

	// Initialize variables //
	for(i=0;i<=80;i++)
	{
		g_TrimRegister_P[i]     = 0;
		g_S_TrimRegister[i]     = 0;
		g_TrimRegisterTemp_P[i] = 0;
		g_S_TrimRegisterTemp[i] = 0;
	}

	EEpr_Bank_P[E0]		= 0;
	EEpr_Bank_P[E2]		= 0;
	EEpr_Bank_P[E4]		= 0;
	EEpr_Bank_P[E6]		= 0;
	EEpr_Bank_P[E8]		= 0;


	gVBPS_P_Init=0.0; 
	gVBPP_P_Init=0.0; 
	gVBPP_M_Init= 0.0; 
	gVBPS_M_Init=0.0; 
	gVBPS_final = 0;
	gVBPP_VCEN =0.0; 
	gIzpt_NoZ_s=0.0;
	gIZ_NoZ_s=0.0;
    gVread_AF_primary =0.0; 
	gVread_AF_secondary=0.0;
    gSec_tr1_ZapTime =0.0;
    gSec_tr2_AFtrhd =0.0;
	g_Fosc_pt_P =0.0;    
	g_FOSC_pt_S =0.0;
    g_FOSC_exp_P =0.0;   
	g_FOSC_exp_S =0.0;
 //   g_TonMax_Pt  =0.0;
 //   g_TonMax_exp =0.0;
	//g_tOVL_Pt	=0;
	//g_tOVL_exp	=0;
 //   g_HandShake_PASS =0;
	gCV_VO_pt_S  =0.0;
	gCV_S =0.0;
    gVclamp_2pct_S=0.0; 
	gVclamp_10pct_S=0.0;
	gCC_pt_S =0.0;
	gCC_exp_S =0.0;
    gCB_exp_S =0.0;
    g_ILIM_pt_S  =0.0;
    g_ILIM_exp_S =0.0;
	g_ILIM_I2f_pt_S =0.0;
	gISvth =0.0;
    gVshunt_Init_Pr =0.0;
    gVshunt_Init_Se =0.0;
	MEAS_Isvth_FLAG =0;
	gDly_Wait_and_Listen_Test_Mode = 260; //Test Mode delay for "Wait and Listen" 2.5ms (250 x 10us)
	gDly_Wait_and_Listen_Normal_Mode = 90; //Normal Mode delay for "Wait and Listen" 90 ms
	g_readTime_p = 10; //x*10us => 100us 
	g_readTime_s = 10; //x*10us => 100us 
	g_trimTime_p = 500; //x*10us =>   5ms 
	g_trimTime_s = 500; //x*10us =>   5ms 
	g_ILIM_dly = 95;
	g_REL_dly = 100;
	gVread_AF_primary = 5.5; // lower to 5.5V and expect post trim to be around 200uA to 300uA instead of 600uA to 800uA)
	gTrim_Voltage = 50;
	g_Error_Flag = 0;
	g_Fosc_Sim_S = 0;
	g_Fosc_Sim_Chg_S = 0;
	g_CCoff_Pt_S = 0;
	g_IsDAC_Pt_S = 0;
	g_IsCal_Pt_S = 0;
	g_Gain_Pt_S = 0;
	g_DofA_Pt_S = 0;
	g_pDAC_Pt_S = 0;
	g_nDAC_Pt_S = 0;
	g_CV_pt_S = 0;
	g_OSC_Pt_S = 0;
	g_ISvth3X_pt_S = 0;
	g_CDC_Target_S = 0.600; // CDC target //
	g_CV_Final_S = 0;
	g_CDC_Pt_S = 0;
	AbortTest =0;
	Setup =0;
	g_IsDAC_final = 0;
	g_IsDAC_Sim_S = 0;
	g_PartFailed = 0;
	g_ILIM_S = 0;
	g_ADC_Pt = 0;
	g_ADC_Final = 0;
	g_EE_ShadReg38 = 0; // bit[38]: assign trim_CCesr //
	g_EEpt_ShadReg63 = 0; // bit[63]: trim_no_fb_pin //
	g_EE_ShadReg63 = 0; // bit[63]: trim_no_fb_pin //
	g_EEpt_ShadReg104 = 0; // eep_sreg[104]: trim_ldo_3p6v //
	g_EE_ShadReg104 = 0; // eep_sreg[104]: trim_ldo_3p6v //
	g_Bit63_Change_Flag = 0;
	g_FOSC_S = 0;
	gVBPP_PV_final = 0;
	gVBPP_PV_Init = 0;
	gVBPP_P_final = 0;
	g_VBPP_P_S_Init_S = 0;
	g_VBPP_P_s_final = 0;
	g_ISVTH = 0;
	g_CCoff_final = 0;
	g_IsCal_final = 0;
	g_I2C_Pullup = 3.3;
	g_VBPP_P_S_FailFlag = 0;
	g_DDDwait = 50; // 1ms //
	g_DDDwait_b = 100; // 1ms //
	g_BPP_Stress_Volt = 0;
	g_BPP_IS1_Pre = 0;
	g_BPP_IS2_Pre = 0;
	g_iLeak_V_Pre = 0;
	g_iLeak_V_Post = 0;
	g_iLeak_V_Delta = 0;
	g_BPS_IS1_Pre = 0;
	g_BPP_IS1_Diff = 0;
	g_BPS_IS2_Pre = 0;
	g_BPP_IS2_Diff = 0;
	g_GNDRes_Se = 0;
	g_GNDRes_Pri = 0;
	g_Inv_threshold = 200; // 200nsec //

	// DDD level initialize //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 3.3; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	
	// Initialize shadow register array. //
	for (i=0;i<112;i++)
	{
		g_ShadowRegister[i] = 0;
	}
	
	// Initialize Antifuse array //
	for (i=0;i<100;i++)
	{
		g_xChk_P[i] = 0;
	}
	
	// Resource Mapping //
	VR_dvi      = dvi_9;   //DVI_9_1.
	D_dvi       = dvi_11;  //DVI_11_0
	BPP_dvi     = dvi_11;  //DVI_11_1
	HBP_dvi2k   = dvi_13;  //DVI_13_0
	IS_dvi2k    = dvi_13;  //DVI_13_1
	BPS_dvi     = dvi_21;  //DVI_21_0
	UV_dvi      = dvi_21;  //DVI_21_1

	HSG_ovi     = ovi_1;  //OVI_1_0
	BUFCLMP_ovi   = ovi_1;  //OVI_1_1
	IS_ovi      = ovi_1;  //OVI_1_2,OVI_1_4
	NC_ovi      = ovi_1;  //OVI_1_3
	TS_ovi      = ovi_1;  //OVI_1_5
	Site_ovi    = ovi_1;  //OVI_1_7
	
	TS_ovi3     = ovi_3;  //OVI_3_0
	B_ovi3      = ovi_3;  //OVI_3_1,OVI_3_2
	SYNC_ovi3   = ovi_3;  //OVI_3_3
	FW_ovi3     = ovi_3;  //OVI_3_4
	SDA_ovi3    = ovi_3;  //OVI_3_5
	SCL_ovi3    = ovi_3;  //OVI_3_6
	FB_ovi3     = ovi_3;  //OVI_3_7






	// Get serial number //
	//GetSerialNum(CURRENT_SERIAL_NUM);
	//g_SERIAL_NUM= atoi(CURRENT_SERIAL_NUM);

	//if (g_First_Time_Run || g_FirstPart <2)
	if (g_FirstPart)
	{
		Hardware_Check_Binno();
		mode_change();
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Check limit set. Make sure limit set was not changed.  If it was changed, flag error 
	// and require program reload. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Declare Variables //
	int TempOpcode = 0;
	char dummy[40];
	STRING mystring;
	
	// Get limit set //
	GetLimitSetName( mystring );
	istrstream theLimitSetName( (char*)((const char*)mystring) );
	theLimitSetName >> Part_ID_LimitSet  >> g_OperCode >> dummy >> dummy;
	
	// Set TempOpcode  //
	if (!strnicmp( g_OperCode, "4200", 4 ))
		TempOpcode = 4200;						
	if (!strnicmp( g_OperCode, "4250", 4 ))	
		TempOpcode = 4250;						
	if (!strnicmp( g_OperCode, "4500", 4 ))	
		TempOpcode = 4500;						
	if (!strnicmp( g_OperCode, "4300", 4 ))
		TempOpcode = 4300;						
	if (!strnicmp( g_OperCode, "4400", 4 ))
		TempOpcode = 4400;						
	if (!strnicmp( g_OperCode, "2400", 4 ))
		TempOpcode = 2400;

	// Check if limit set changed. //
	if(TempOpcode != g_OPCODE || g_LimitSetChanged == 1)
	{
		Setup = 999; // Failed setup
		g_Error_Flag = -222;
		MessageBox(NULL, "The limit set was changed.  Must reload test program.", "Error", MB_OK|MB_TOPMOST);	
		g_LimitSetChanged = 1;
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //



	// Check to make sure the program (.prg) selected matches the Part ID entered in the New Lot Information Screen. //
	if (0)//!strnicmp( Part_ID_LimitSet, "SC", 2)) HL disabled for Binno preliminary trimming
	{
		if (strnicmp( Part_ID_LimitSet, g_Part_ID_Trimops, 6))
		{
			Setup = 999; // Failed setup
			g_Error_Flag = -222;
			MessageBox(NULL, "The program (.prg) selected does not match the Part ID entered in the New Lot Information Screen.", "Error", MB_OK|MB_TOPMOST);
		}
	}
	else
	{
		if (0)//strnicmp( Part_ID_LimitSet, g_Part_ID_Trimops, 7)) HL disabled for Binno preliminary trimming
		{
			Setup = 999; // Failed setup
			g_Error_Flag = -222;
			MessageBox(NULL, "The program (.prg) selected does not match the Part ID entered in the New Lot Information Screen.", "Error", MB_OK|MB_TOPMOST);
		}
	}

	//Mux bank 20 will need to be closed continuity tests ..etc.
	mux_20->close_relay(MUX_BANK_1_2);
	mux_20->close_relay(MUX_BANK_2_3);
	mux_20->close_relay(MUX_BANK_3_4);
	mux_20->close_relay(MUX_BANK_4_5);
	mux_20->close_relay(MUX_BANK_5_6);
	mux_20->close_relay(MUX_BANK_6_7);
	mux_20->close_relay(MUX_BANK_7_8);
	mux_20->close_relay(MUX_BANK_8_1);	
	wait.delay_10_us(250);
	
	////// Check DVI2K ch0 temperature
	HBP_dvi2k->set_meas_mode(HBP_ch,DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch0_Temp =  HBP_dvi2k->measure();	// If it is greater than 140F, DVI is overheat
	
	////// Check DVI2K ch1 temperature
	IS_dvi2k->set_meas_mode(IS_ch,DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch1_Temp =  IS_dvi2k->measure(); // If it is greater than 140F, DVI is overheat

	// Disable trimming if not 4200 opcode. //
	if (g_OPCODE != 4200)
		g_Burn_Enable_P =0;

	// Check for golden unit program //
	if (!strnicmp( g_PrgName, "LYT8375GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8365GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8376GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8367GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8368GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8369GoldenUnit", 17 ) || 
		!strnicmp( g_PrgName, "LYT8380GoldenUnit", 17 ))
	{
		g_Burn_Enable_P =0;  // Do not trim golden units. //
	}

	//if (g_DevNum_Trimops == -99)
	//{
	//	//Setup = 999; // Failed setup
	//	//g_Error_Flag = -222;
	//}
	//if( !HardwareList.VerifyRequiredBoardList() )
	if(g_Setup_OK == 0)
	{
		Setup = 999; // Failed setup
		//g_Error_Flag = -222;
		MessageBox(NULL, "Hardware ID failure.  Make sure hardware ID cable is plugged in. Hardware ID chip may be defective.", "Error", MB_OK|MB_TOPMOST);
	}	
	if (g_FirstPart)
	{
		// Determine what digitizer we have on PC //
		if (!strnicmp( CsSysInfo.strBoardName, "CS14100", 7 )) // 14100 //
		{
			g_DigitizerType = 14100; // 14100 //
		}
		else if (!strnicmp( CsSysInfo.strBoardName, "CS1422", 6 ) // PCI 14bits //
				|| !strnicmp( CsSysInfo.strBoardName, "CSE1422", 7 )) // PCI 16bits //
		{
			g_DigitizerType = 1422; // Razor 1422 //
		}
		else if (!strnicmp( CsSysInfo.strBoardName, "CS1622", 6 ) // PCIex 14bits //
				|| !strnicmp( CsSysInfo.strBoardName, "CSE1622", 7 )) // PCIex 16bits //
		{
			g_DigitizerType = 1622; // Razor 1422 //
		}

		// Find RDSON buffer gain //
		g_SAMPLE_SIZE = GAGE_POST_4K;
		BUFRes_Div_ratio = 1.0;
		g_BUFgain = Rdson_Buffer_Cal(BUFRes_Div_ratio);

		// Get Framework Version for datalogging. The PiGetFrameworkVersion() function returns the framework 
		// version as a string.  Need to convert to a number for datalogging.  //
		char *FramewrkVer[50];
		int StringLength = 0;
		int ASCIIvalue[50] = {0};
		int TempNum = 0;
		long int DecimalFactor = 1;
		*FramewrkVer=PiGetFrameworkVersion();
		char *TempString = FramewrkVer[0];	
		StringLength = strlen(*FramewrkVer);
		for(i=0;i<StringLength;i++)
		{
			ASCIIvalue[i] = TempString[i];
		}
		for(i=(StringLength-1);i>-1;i--)
		{
			if (ASCIIvalue[i] == 48) // ASCII 48 = char "0" //
				TempNum = 0;
			if (ASCIIvalue[i] == 49) // ASCII 49 = char "1" //
				TempNum = 1;
			if (ASCIIvalue[i] == 50) // ASCII 50 = char "2" //
				TempNum = 2;
			if (ASCIIvalue[i] == 51) // ASCII 51 = char "3" //
				TempNum = 3;
			if (ASCIIvalue[i] == 52) // ASCII 52 = char "4" //
				TempNum = 4;
			if (ASCIIvalue[i] == 53) // ASCII 53 = char "5" //
				TempNum = 5;
			if (ASCIIvalue[i] == 54) // ASCII 54 = char "6" //
				TempNum = 6;
			if (ASCIIvalue[i] == 55) // ASCII 55 = char "7" //
				TempNum = 7;
			if (ASCIIvalue[i] == 56) // ASCII 56 = char "8" //
				TempNum = 8;
			if (ASCIIvalue[i] == 57) // ASCII 57 = char "9" //
				TempNum = 9;
			if (ASCIIvalue[i] == 46) // ASCII 46 = char "." //
				TempNum = -999;
			if(TempNum > -1)
			{
				g_Framework_Rev = g_Framework_Rev + (DecimalFactor*TempNum);
				DecimalFactor = DecimalFactor*10;
			}
		}
	}
	

	// Inductor //
	//float in_type,in_sbtype,in_rev,in_cal;
	Inductor_Rev = HardwareList.Inductor().HardwareRevision();
	Inductor_ID = Get_Inductor_ID();
/*
	// Check to make sure the inductor module has been qualified to run in production- i.e. GRR done //
	// The following modules are qualified. //
	if (Inductor_ID == 2750 ||	// Size 5 //
		Inductor_ID == 2749 ||	// Size 5 //
		Inductor_ID == 2748 ||	// Size 5 //
		Inductor_ID == 2883 ||	// Size 5 //
		Inductor_ID == 2884 ||	// Size 5 //
		Inductor_ID == 2885 ||	// Size 5 //
		Inductor_ID == 2892 ||	// Size 5 //
		Inductor_ID == 2893 ||	// Size 5 //
		Inductor_ID == 2894 ||	// Size 5 //
		Inductor_ID == 2907 ||	// Size 5 //
		Inductor_ID == 2908 ||	// Size 5 //
		Inductor_ID == 2909 ||	// Size 5 //
		Inductor_ID == 2910 ||	// Size 5 //
		Inductor_ID == 2911 ||	// Size 5 //
		Inductor_ID == 2912 ||	// Size 5 //
		Inductor_ID == 2947 ||	// Size 5 //
		Inductor_ID == 2948 ||	// Size 5 //
		Inductor_ID == 2754 ||  // Size 6 //
		Inductor_ID == 2751 ||  // Size 6 //
		Inductor_ID == 2752 ||  // Size 6 //
		Inductor_ID == 2753 ||  // Size 6 //
		Inductor_ID == 2886 ||  // Size 6 //
		Inductor_ID == 2887 ||  // Size 6 //
		Inductor_ID == 2888 ||  // Size 6 //
		Inductor_ID == 2895 ||  // Size 6 //
		Inductor_ID == 2896 ||  // Size 6 //
		Inductor_ID == 2897 ||  // Size 6 //
		Inductor_ID == 2913 ||  // Size 6 //
		Inductor_ID == 2914 ||  // Size 6 //
		Inductor_ID == 2915 ||  // Size 6 //
		Inductor_ID == 2916 ||  // Size 6 //
		Inductor_ID == 2917 ||  // Size 6 //
		Inductor_ID == 2918 ||  // Size 6 //
		Inductor_ID == 2949 ||  // Size 6 //
		Inductor_ID == 2950 ||  // Size 6 //
		Inductor_ID == 2951 ||  // Size 6 //
		Inductor_ID == 2952 ||  // Size 6 //
		Inductor_ID == 2953 ||  // Size 6 //
		Inductor_ID == 2901 ||	// Size 7/8 //
		Inductor_ID == 2902 ||	// Size 7/8 //
		Inductor_ID == 2903 ||	// Size 7/8 //
		Inductor_ID == 2904 ||	// Size 7/8 //
		Inductor_ID == 2905 ||	// Size 7/8 //
		Inductor_ID == 2906 ||	// Size 7/8 //
		Inductor_ID == 2758 ||	// Size 7/8 //
		Inductor_ID == 2757 ||	// Size 7/8 //
		Inductor_ID == 2755 ||	// Size 7/8 //
		Inductor_ID == 2756 ||	// Size 7/8 //
		Inductor_ID == 2898 ||	// Size 7/8 //
		Inductor_ID == 2899 ||	// Size 7/8 //
		Inductor_ID == 2900 ||	// Size 7/8 //
		Inductor_ID == 2889 ||	// Size 7/8 //
		Inductor_ID == 2890 ||	// Size 7/8 //
		Inductor_ID == 2891 ||	// Size 7/8 //
		Inductor_ID == 2924 ||	// Size 7/8 //
		Inductor_ID == 2925 ||	// Size 7/8 //
		Inductor_ID == 2926 ||	// Size 7/8 //
		Inductor_ID == 2927 ||	// Size 7/8 //
		Inductor_ID == 2928 ||	// Size 7/8 //
		Inductor_ID == 2929 ||	// Size 7/8 //
		Inductor_ID == 2930 ||	// Size 7/8 //
		Inductor_ID == 2954 ||	// Size 7/8 //
		Inductor_ID == 2955 ||	// Size 7/8 //
		Inductor_ID == 2956 ||	// Size 7/8 //
		Inductor_ID == 2957 ||	// Size 7/8 //
		Inductor_ID == 2958)	// Size 7/8 //
	{
		// OK //
	}
	else
	{
		//MessageBox(NULL, "Inductor(ILIM) module has not been qualified.", "Error", MB_OK|MB_SYSTEMMODAL);
		sprintf(STRINGarray,"Inductor(ILIM) module has not been qualified.\n\n%d\n", Inductor_ID);
		MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
	}
*/
	// LoadBoard //
	//float lb_type,lb_sbtype,lb_rev,lb_cal;
	//gLoadBoardRev = HardwareList.LoadBoard().HardwareRevision();
	
	//Loadboard_ID = Get_Loadboard_ID();

	//Loadboard_ID = 
	
	// Check to make sure the loadboard has been qualified to run in production- i.e. GRR done. //
	// The following boards are qualified. //
	//////if (Loadboard_ID == 2086 || Loadboard_ID == 2087 || Loadboard_ID == 2088 || Loadboard_ID == 2089 ||
	//////	Loadboard_ID == 2213 || Loadboard_ID == 2214 || Loadboard_ID == 2223 || Loadboard_ID == 2224 || 
	//////	Loadboard_ID == 2225 || Loadboard_ID == 2219/*NEW*/ || Loadboard_ID == 2220/*NEW*/ || 
	//////	Loadboard_ID == 2221/*NEW*/ || Loadboard_ID == 2234/*NEW*/ || Loadboard_ID == 2239/*NEW*/ ||
	//////	Loadboard_ID == 2238/*NEW*/ || Loadboard_ID == 2235/*NEW*/ || Loadboard_ID == 2233/*NEW*/ || 
	//////	Loadboard_ID == 2240/*NEW*/ || Loadboard_ID == 2241/*NEW*/ || Loadboard_ID == 2242/*NEW*/ || 
	//////	Loadboard_ID == 2243/*NEW*/ || Loadboard_ID == 2244/*NEW*/ || Loadboard_ID == 2245/*NEW*/ ||
	//////	Loadboard_ID == 2212/*NEW*/ || Loadboard_ID == 2246/*NEW*/ || Loadboard_ID == 2247/*NEW*/)
	//////{
	//////	// OK //
	//////}
	//////else
	//////{
	//////	//MessageBox(NULL, "Loadboard has not been qualified.", "Error", MB_OK|MB_SYSTEMMODAL);
	//////	//sprintf(STRINGarray,"Loadboard has not been qualified.\n\n%d\n", Loadboard_ID);
	//////	//MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
	//////}

	// Contactor Board //
	//float tb_type,tb_sbtype,tb_rev,tb_cal;
	gContactorRev = HardwareList.HandlerContactor().HardwareRevision();
	Contactor_ID = Get_Contactor_ID();

	// Check to make sure the contactor board has been qualified to run in production- i.e. GRR done. //
	// The following boards are qualified. //
	// OLD HANDWIRED CONTACTOR BOARDS //
	if (Contactor_ID == 2465 || Contactor_ID == 2468 || Contactor_ID == 2467 || Contactor_ID == 2469 || 
		Contactor_ID == 2615 || Contactor_ID == 2614 || Contactor_ID == 2471 || Contactor_ID == 2470 || 
		Contactor_ID == 2638/*NEW*/ || Contactor_ID == 2633/*NEW*/ || Contactor_ID == 2634/*NEW*/ ||
		Contactor_ID == 2635/*NEW*/ || Contactor_ID == 2636/*NEW*/ || Contactor_ID == 2637/*NEW*/ ||
		Contactor_ID == 2622/*NEW*/ || Contactor_ID == 2623/*NEW*/ || Contactor_ID == 2666/*NEW*/ || 
		Contactor_ID == 2667/*NEW*/ || Contactor_ID == 2668/*NEW*/ || Contactor_ID == 2669/*NEW*/ || 
		Contactor_ID == 2670/*NEW*/ || Contactor_ID == 2671/*NEW*/ || Contactor_ID == 2675/*NEW*/ || 
		Contactor_ID == 2682/*NEW*/ || Contactor_ID == 2672/*NEW*/ || Contactor_ID == 2673/*NEW*/ || 
		Contactor_ID == 2674/*NEW*/)
	{
		// OK //
	}
	else
	{
		//MessageBox(NULL, "Contactor board has not been qualified.", "Error", MB_OK|MB_SYSTEMMODAL);
		//sprintf(STRINGarray,"Contactor board has not been qualified.\n\n%d\n", Contactor_ID);
		//MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
	}

	

	// Check 50ohm drain pullup resistor R1, make sure correct value.  Should be 50 ohms. //
	if (g_FirstPart)
	{
		if(gLoadBoardRev > 24)
		{
			////ovi_1->connect(OVI_CHANNEL_7);
			////ovi_1->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_2_V); // OVI_1_7 //
			////ovi_1->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_1_7 //
			//////ovi_1->set_meas_mode(OVI_CHANNEL_7, OVI_MEASURE_VOLTAGE); // OVI_1_7 //
			////D_dvi->set_voltage(D_ch, 0, VOLT_1_RANGE); // DVI_11_0 //
			////D_dvi->set_current(D_ch, 29e-3, RANGE_30_MA); // DVI_11_0 //
			////D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT); // DVI_11_0 //
			////Close_relay(K3);
			////Close_relay(K14); // Connect ovi1_7 //
			////wait.delay_10_us(300);
			////D_dvi->set_voltage(D_ch, 1, VOLT_1_RANGE); // DVI_11_0 //
			////wait.delay_10_us(100);
			////g_R1_current = D_dvi->measure();
			////D_dvi->set_voltage(D_ch, 0, VOLT_1_RANGE); // DVI_11_0 //
			////wait.delay_10_us(100);
			////Open_relay(K3);
			////Open_relay(K14); // Disconnect ovi1_7 //
			////wait.delay_10_us(300);
			////if (g_R1_current == 0) // Prevent divide by zero. //
			////{
			////	g_R1_current = 0.0001;
			////}
			////g_R1_ohms = 1 / g_R1_current;
		}
	}
	if(gLoadBoardRev > 24)
	{
		// There is a 82uH inductor in series with the 50ohm resistor which has ~5ohm resistance. //
		if (g_R1_ohms < 52.6 || g_R1_ohms > 58.5)
		{
			////Setup = 999; // Failed setup //
			////g_Error_Flag = -222;
			////sprintf(STRINGarray,"50 ohm loadboard resistor R1 is out of spec, it measures %f ohms.\n The problem could also be inductor L1 (82uH) or relay K14.",g_R1_ohms);
			////cout << endl << endl << "R1 + L1 = " << g_R1_ohms << endl; 
			////MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
		}
	}


	// Check fall time of InvSync circuit output.   If fall time is too long, test repeatability problems occur.//
	// Result will be checked in Leakage.cpp //
	if (g_FirstPart)
	{
		//////// Connect InvSync circuit between drain and FW pin.  Raise drain to 10V and use TMU to measure 
		//////// how long it takes FW to fall. //
		//////BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
		//////BPS_dvi->set_voltage(BPS_ch, 3.5, VOLT_10_RANGE); // DVI_9_1, must raise BPS before connecting InvSyn to FW, othwise to much current out of InvSyn. //
		//////D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
		//////D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
		//////Close_relay(K2);
		//////Open_relay(K3);
		//////wait.delay_10_us(30);
		//////Connect_InvSyn_IM(Low_Load_Vd_Input);
		//////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3, VOLT_20_RANGE); // OVI_1_4
		//////tmu_6->close_relay(TMU_CHAN_A_DUT1); // Connect TMU CHA to FW
		//////tmu_6->start_trigger_setup(2.5, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		//////tmu_6->stop_trigger_setup(0.001, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		//////tmu_6->start_holdoff(0,FALSE);
		//////tmu_6->stop_holdoff(0,FALSE);
		//////wait.delay_10_us(300);
		//////tmu_6->arm();
		//////wait.delay_10_us(50);
		//////D_dvi->set_voltage(D_ch, 10, VOLT_10_RANGE); // DVI_11_0 //
		//////wait.delay_10_us(20);
		//////g_InvSyn_Fall = tmu_6->read(150e-6);
		//////g_InvSyn_Fall *= 1e9; // Units //
		//////if (g_InvSyn_Fall > g_Inv_threshold || g_InvSyn_Fall < 1) // Check again too make sure //
		//////{
		//////	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
		//////	wait.delay_10_us(50);
		//////	tmu_6->arm();
		//////	wait.delay_10_us(50);
		//////	D_dvi->set_voltage(D_ch, 10, VOLT_10_RANGE); // DVI_11_0 //
		//////	wait.delay_10_us(20);
		//////	g_InvSyn_Fall = tmu_6->read(150e-6);
		//////	g_InvSyn_Fall *= 1e9; // Units //
		//////}

		//////// Even if InvSync falltime is OK, it may still be defective.  
		//////// The output should return to 0V when output ovi is set to 0V.  Have seen 
		//////// faulty InvSync output stay at -0.7V.  Set ovi to 0V and make sure output returns to 0V. //
		//////ovi_1->set_voltage(OVI_CHANNEL_6, 0, VOLT_5_RANGE);
		//////FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
		//////FW_dvi->set_current(FW_ch, 0.1e-9, RANGE_30_UA); // DVI_11_1, float //
		//////FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_VOLTAGE); // DVI_11_1 //
		//////wait.delay_10_us(30);
		//////Close_relay(K18);
		//////wait.delay_10_us(300);
		//////g_FWmeasV = FW_dvi->measure();
		//////Open_relay(K18);
		//////D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE); // DVI_11_0 //
		//////wait.delay_10_us(20);
		//////Disconnect_InvSyn_IM();
		//////wait.delay_10_us(150);
		//////BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE); // DVI_9_1 //
		//////wait.delay_10_us(50);
		//////Open_relay(K2);
		//////tmu_6->open_relay(TMU_CHAN_A_DUT1);
		//////wait.delay_10_us(300);
		//////FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
	}
	

	// Check if testing Site 1 or Site 2. //
	if(1)//gLoadBoardRev > 24 && gContactorRev > 20)
	{

		////ovi_3->connect(3);
		////Mux20_Close_relay(K49);
		////wait.delay_10_us(250);
		////ovi_3->set_voltage(OVI_CHANNEL_3, 2, RANGE_10_V); // OVI_3_3 //
		////ovi_3->set_current(OVI_CHANNEL_3, 3e-3, RANGE_3_MA); // OVI_3_3 //
		////ovi_3->set_meas_mode(OVI_CHANNEL_3, OVI_MEASURE_CURRENT); // OVI_3_3 //
		////wait.delay_10_us(40);
		////Site_Current = ovi_3->measure();
		////ovi_3->set_voltage(OVI_CHANNEL_3, 0, RANGE_10_V); // OVI_3_3 //
		////wait.delay_10_us(30);
		////ovi_3->disconnect(3);
		////Mux20_Open_relay(K49);
		////wait.delay_10_us(250);
		////if (Site_Current > 500e-6) // Site 1 //
		////	g_Site = 1;
		////else
		////	g_Site = 2;
	}

	// All the little boxes in .prg should be set to green, even if they will not 
	// be executed.  If the total number of functions executed is not 66 then abort 
	// all testing and provide a message box. The purpose is to keep control of 
	//which functions are executed under source code control. //
	if (0)//g_Wrong_Number_Of_Functions)
	{
		Setup = 999; // Failed setup
		g_Error_Flag = -222;
		MessageBox(NULL, "All the functions in the .prg were not initially green.  You must exit and restart Visual ATE.", "Error", MB_OK|MB_TOPMOST);
	}

	if (g_Enable_ScanChain)
	{
		// DSM MODULE CODE //
		if (g_Wrong_Scan_Pattern)
		{
			Setup = 999; // Failed setup	
			g_Error_Flag = -222;
			MessageBox(NULL, "Please check Scan Pattern Text file name.", "Error", MB_OK|MB_TOPMOST);
		}
		if (g_No_DSM_USB)
		{
			Setup = 999; // Failed setup
			g_Error_Flag = -222;
			MessageBox(NULL, "Please check DSM USB connection on both ends.", "Error", MB_OK|MB_TOPMOST);
		}
		// DSM MODULE CODE //
	}

	if (0)//g_Enable_ScanChain)
	{
		// Check DSM (Digital Scan Module) library and firmware revision. //
		if (g_FirstPart)
		{
			// Check DSM (Digital Scan Module) library revision. //
			g_DSM_Library_Version = DSM_version();
			//g_DSM_Library_Version = s_DSM_version();
			g_DSM_Library_Version = (int)(g_DSM_Library_Version * 10000);
		
			// Check DSM (Digital Scan Module) firmware revision. //
			g_DSM_Firmware_Version = DSM_firmware(DSM_CONTEXT);
			g_DSM_Firmware_Version = (int)(g_DSM_Firmware_Version * 10000);
			//g_DSM_Firmware_Version = s_DSM_firmware(DSM_CONTEXT);
		}
		if ( g_DSM_Library_Version != 21400 ) // DEBUG ONLY!!! Should be 21400 for production. //
		{
			Setup = 999; // Failed setup
			g_Error_Flag = -223;
			sprintf(STRINGarray,"Wrong DSM library version %f.\n", g_DSM_Library_Version/10000);
			cout << endl << endl << "DSM_Library_Version = " << g_DSM_Library_Version/10000 << endl; 
			MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
		}
		if ( g_DSM_Firmware_Version != 21400 ) // DEBUG ONLY!!! Should be 21400 for production. //
		{
			Setup = 999; // Failed setup
			g_Error_Flag = -224;
			sprintf(STRINGarray,"Wrong DSM firmware version %f.\n", g_DSM_Firmware_Version/10000);
			cout << endl << endl << "DSM_Firmware_Version = " << g_DSM_Firmware_Version/10000 << endl; 
			MessageBox(NULL, STRINGarray, "Error", MB_OK|MB_SYSTEMMODAL);
		}
	}


	//HL 03/01/19

	g_Device_ID_S = 0;
	g_B2_MaxSate    = 0.0;
	g_B1_FastUpdate = 0.0;
	g_A3_Target_VR  = 0.0;
	g_A2_FastUpdate = 0.0;
	g_A1_MinState   = 0.0;
	g_A_Skipping    = 0.0;

	for(i=0;i<5;i++)
	{
		EEpr_Array[i] = 0;
	}
	// Test program delay //
	if (p_Loop_wait > 0)
		wait.delay_10_us(p_Loop_wait*100);

	// Datalog //
	PiDatalog(func, A_Setup, Setup, 31, POWER_UNIT);
	PiDatalog(func, A_Site, g_Site, 31, POWER_UNIT);
	PiDatalog(func, A_Opcode, g_OPCODE, 31, POWER_UNIT);
	//PiDatalog(func, A_Framework_Rev, g_Framework_Rev, 31, POWER_UNIT);
	PiDatalog(func, A_ProcessorType, ProcessorType, 31, POWER_UNIT);
	PiDatalog(func, A_Loadboard_ID, gLoadBoard_SubType , 31, POWER_UNIT);
	PiDatalog(func, A_Loadboard_Rev, gLoadBoardRev, 31, POWER_UNIT);
	//PiDatalog(func, A_Inductor_ID, Inductor_ID, 31, POWER_UNIT);
	//PiDatalog(func, A_Inductor_Rev, Inductor_Rev, 31, POWER_UNIT);
	PiDatalog(func, A_Contactor_ID, gTestBlock_SubType, 31, POWER_UNIT);
	PiDatalog(func, A_Contactor_Rev, gTestBlockRev, 31, POWER_UNIT);
	PiDatalog(func, A_p_Loop_wait, p_Loop_wait/1000, 31, POWER_MILLI);
	PiDatalog(func, A_p_Char_Enable, g_Char_Enable_P, 31, POWER_UNIT);
	PiDatalog(func, A_p_Rel_Enable, g_Rel_Enable_P, 31, POWER_UNIT);



	PiDatalog(func, A_p_Trim_Enable, g_Burn_Enable_P, 31, POWER_UNIT);
	PiDatalog(func, A_p_TstTime_Enble, p_TstTime_Enble, 31, POWER_UNIT);
	PiDatalog(func, A_Rewrite_EPROM, p_Rewrite_EPROM, 31, POWER_UNIT);
	PiDatalog(func, A_ExtraParam1, p_ExtraParam1, 31, POWER_UNIT);
	PiDatalog(func, A_ExtraParam2, p_ExtraParam2, 31, POWER_UNIT);



//	PiDatalog(func, A_BUFgain, g_BUFgain, 31, POWER_UNIT);
	PiDatalog(func, A_DVI2K_ch0_Temp, DVI2K_ch0_Temp, 31, POWER_UNIT);
	PiDatalog(func, A_DVI2K_ch1_Temp, DVI2K_ch1_Temp, 31, POWER_UNIT);
	PiDatalog(func, A_Dig_Type, g_DigitizerType, 31, POWER_UNIT);
	
	
	



	
	

	
	
	

	if (PiGetAnyFailStatus())		
	{
		//g_First_Time_Run = 1; // Re-run calibration if setup fails
		AbortTest = 1 ;
		g_PartFailed = 1;
	}
	//else
	//	g_First_Time_Run = 0;	

	// Set flag to indicate the first part has been run. //
	g_FirstPart = 0; 

	// Test Time End //
	if (g_TstTime_Enble_P)
	{
		g_endtime = g_mytimer.GetElapsedTime();
		First_TT = (g_endtime - g_begintime)*1e-6;
		PiDatalog(func, A_First_TT, First_TT, 31, POWER_MILLI);
	}

}
