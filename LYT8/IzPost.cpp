//==============================================================================
// IzPost.cpp (User function)
// 
//    void IzPost_user_init(test_function& func)
//    void IzPost(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "IzPost.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IzPost_user_init(test_function& func)
{
	IzPost_params *ours;
    ours = (IzPost_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IzPost(test_function& func)
{
    // The two lines below must be the first two in the function.
    IzPost_params *ours;
    ours = (IzPost_params *)func.params;

	// Increment function number //
	gFuncNum++;

//////	// Datalog gFuncNum variable //
//////	if(gDisplay_FuncNum)
//////		PiDatalog(func, A_fNum_IzPost, gFuncNum, 16, POWER_UNIT);
//////
//////	//Skip Test if AbortTest set 
//////	if (AbortTest)
//////		return;
//////
//////	if (g_Fn_IzPost == 0 )  return;
//////
//////	// Test Time Begin //
//////	if (g_TstTime_Enble_P)
//////		g_begintime = g_mytimer.GetElapsedTime();
//////
//////	// Test Names //
//////	// Primary //
//////	float IZ_iov1_p = 0;
//////	float IZ_iov2_p = 0;
//////	float IZ_iov3_p = 0;
//////	float IZ_iov4_p = 0;
//////	float IZ_iovSign_p = 0;
//////	float IZ_iL1_p = 0;
//////	float IZ_iL2_p = 0;
//////	float IZ_iL3_p = 0;
//////	float IZ_iLsign_p = 0;
//////	float IZ_tOVL1_p = 0;
//////	float IZ_tOVL2_p = 0;
//////	float IZ_tOVLSign_p = 0;
//////	float IZ_f1_p = 0;
//////	float IZ_f2_p = 0;
//////	float IZ_fSign_p = 0;
//////	float IZ_iov_Off_p = 0;
//////	float IZ_iuvMinus_p = 0;
//////	float IZ_uvDelay_p = 0;
//////	float IZ_Loff_AR_p = 0;
//////	float IZ_DisablAR_p = 0;
//////	float IZ_didtComp_p = 0;
//////	float IZ_OT_Hys_p = 0;
//////	float IZ_LoffwOT_p = 0;
//////	float IZ_iLselOff_p = 0;
//////	float IZ_iLStdIcr_p = 0;
//////	float IZ_iL20dn_p = 0;
//////	float IZ_iL20up_p = 0;
//////	float IZ_SAM_p = 0;
//////	float IZ_OTP1_p = 0;
//////	float IZ_OTP2_p = 0;
//////	float IZ_OTP3_p = 0;
//////	float IZ_SDSoff_p = 0;
//////	float IZ_Rcv1_p = 0;
//////	float IZ_Rcv2_p = 0;
//////	float IZ_RcvSign_p = 0;
//////	float IZ_drvSize1_p = 0;
//////	float IZ_drvSize2_p = 0;
//////	float IZ_drvSize3_p = 0;
//////	float IZ_drvSize4_p = 0;
//////	float IZ_RsenseUp_p = 0;
//////	float IZ_vxAdj1_p = 0;
//////	float IZ_vxAdj2_p = 0;
//////	float IZ_vxAdj3_p = 0;
//////	float IZ_vxAdj4_p = 0;
//////	float IZ_vxAdj5_p = 0;
//////	float IZ_iLRatio1_p = 0;
//////	float IZ_iLRatio2_p = 0;
//////	float IZ_iLRatio3_p = 0;
//////	float IZ_iLRatio4_p = 0;
//////	float IZ_iLTC1_p = 0;
//////	float IZ_iLTC2_p = 0;
//////	float IZ_iLTC3_p = 0;
//////	float IZ_iLTC4_p = 0;
//////	float IZ_ARreq_p = 0;
//////	float IZ_ZF_p = 0;
//////
//////	// Test Names //
//////	// Secondary //
//////	int EE_F1_S = 0;
//////	int EE_F2_S = 0;
//////	int EE_F3_S = 0;
//////	int EE_F_Iint1_S = 0;
//////	int EE_F_Iint2_S = 0;
//////	int EE_F_Iint3_S = 0;
//////	int EE_F_Iint4_S = 0;
//////	int EE_PKspdLd_S = 0;
//////	int EE_CV1_S = 0;
//////	int EE_VesrAdp_S = 0;
//////	int EE_ISvth3X1_S = 0;
//////	int EE_ISvth3X2_S = 0;
//////	int EE_ISvth3X3_S = 0;
//////	int EE_ISvth3X4_S = 0;
//////	int EE_ISvth3X5_S = 0;
//////	int EE_ISvth3X6_S = 0;
//////	int EE_CDC1_S = 0;
//////	int EE_CDC2_S = 0;
//////	int EE_CDC3_S = 0;
//////	int EE_CV2_S = 0;
//////	int EE_CV3_S = 0;
//////	int EE_CV4_S = 0;
//////	int EE_CV5_S = 0;
//////	int EE_CV6_S = 0;
//////	int EE_OSC0_S = 0;
//////	int EE_OSC1_S = 0;
//////	int EE_OSC2_S = 0;
//////	int EE_OSC3_S = 0;
//////	int EE_nDAC1_S = 0;
//////	int EE_nDAC2_S = 0;
//////	int EE_nDAC3_S = 0;
//////	int EE_nDAC4_S = 0;
//////	int EE_nDAC5_S = 0;
//////	int EE_pDAC1_S = 0;
//////	int EE_pDAC2_S = 0;
//////	int EE_pDAC3_S = 0;
//////	int EE_pDAC4_S = 0;
//////	int EE_pDAC5_S = 0;
//////	int EE_DofA1_S = 0;
//////	int EE_DofA2_S = 0;
//////	int EE_DofA3_S = 0;
//////	int EE_DofA4_S = 0;
//////	int EE_DofA5_S = 0;
//////	int EE_IsDAC1_S = 0;
//////	int EE_IsDAC2_S = 0;
//////	int EE_IsDAC3_S = 0;
//////	int EE_IsDAC4_S = 0;
//////	int EE_IsDAC5_S = 0;
//////	int EE_Gain1_S = 0;
//////	int EE_Gain2_S = 0;
//////	int EE_Gain3_S = 0;
//////	int EE_Gain4_S = 0;
//////	int EE_CCoff1_S = 0;
//////	int EE_CCoff2_S = 0;
//////	int EE_CCoff3_S = 0;
//////	int EE_IsCal1_S = 0;
//////	int EE_IsCal2_S = 0;
//////	int EE_IsCal3_S = 0;
//////	int EE_DsoftEn_S = 0;
//////	int EE_DOPL_S = 0;
//////	int EE_CCAR_S = 0;
//////	int EE_DoplEnCp_S =0;
//////	int EE_ESRsel_S = 0;
//////	int EE_DdampEn_S = 0;
//////	/*
//////	int EE_ShadReg0 = 0;
//////	int EE_ShadReg1 = 0;
//////	int EE_ShadReg2 = 0;
//////	int EE_ShadReg3 = 0;
//////	int EE_ShadReg4 = 0;
//////	int EE_ShadReg5 = 0;
//////	int EE_ShadReg6 = 0;
//////	int EE_ShadReg7 = 0;
//////	int EE_ShadReg8 = 0;
//////	int EE_ShadReg9 = 0;
//////	int EE_ShadReg10 = 0;
//////	int EE_ShadReg11 = 0;
//////	int EE_ShadReg12 = 0;
//////	int EE_ShadReg13 = 0;
//////	int EE_ShadReg14 = 0;
//////	int EE_ShadReg15 = 0;
//////	int EE_ShadReg16 = 0;
//////	int EE_ShadReg17 = 0;
//////	int EE_ShadReg18 = 0;
//////	int EE_ShadReg19 = 0;
//////	int EE_ShadReg20 = 0;
//////	int EE_ShadReg21 = 0;
//////	//int EE_ShadReg22 = 0; // Using global variable g_EE_ShadReg22 instead.  bit[22]: trim_dopl //
//////	int EE_ShadReg23 = 0;
//////	int EE_ShadReg24 = 0;
//////	int EE_ShadReg25 = 0;
//////	int EE_ShadReg26 = 0;
//////	int EE_ShadReg27 = 0;
//////	int EE_ShadReg28 = 0;
//////	int EE_ShadReg29 = 0;
//////	int EE_ShadReg30 = 0;
//////	int EE_ShadReg31 = 0;
//////	int EE_ShadReg32 = 0;
//////	int EE_ShadReg33 = 0;
//////	int EE_ShadReg34 = 0;
//////	int EE_ShadReg35 = 0;
//////	int EE_ShadReg36 = 0;
//////	int EE_ShadReg37 = 0;
//////	//int EE_ShadReg38 = 0; // Using global variable g_EE_ShadReg38 instead.  bit[38]: assign trim_CCesr //
//////	int EE_ShadReg39 = 0;
//////	int EE_ShadReg40 = 0;
//////	int EE_ShadReg41 = 0;
//////	int EE_ShadReg42 = 0;
//////	int EE_ShadReg43 = 0;
//////	int EE_ShadReg44 = 0;
//////	int EE_ShadReg45 = 0;
//////	int EE_ShadReg46 = 0;
//////	int EE_ShadReg47 = 0;
//////	int EE_ShadReg48 = 0;
//////	int EE_ShadReg49 = 0;
//////	int EE_ShadReg50 = 0;
//////	int EE_ShadReg51 = 0;
//////	int EE_ShadReg52 = 0;
//////	int EE_ShadReg53 = 0;
//////	int EE_ShadReg54 = 0;
//////	int EE_ShadReg55 = 0;
//////	int EE_ShadReg56 = 0;
//////	int EE_ShadReg57 = 0;
//////	int EE_ShadReg58 = 0;
//////	int EE_ShadReg59 = 0;
//////	int EE_ShadReg60 = 0;
//////	int EE_ShadReg61 = 0;
//////	int EE_ShadReg62 = 0;
//////	//int EE_ShadReg63 = 0; // Using global variable g_EE_ShadReg63 instead.  bit[63]: trim_no_fb_pin //
//////	int EE_ShadReg64 = 0;
//////	int EE_ShadReg65 = 0;
//////	int EE_ShadReg66 = 0;
//////	int EE_ShadReg67 = 0;
//////	int EE_ShadReg68 = 0;
//////	//int EE_ShadReg69 = 0; // Using global variable g_EE_ShadReg69 instead. //
//////	//int EE_ShadReg70 = 0; // Using global variable g_EE_ShadReg70 instead. //
//////	//int EE_ShadReg71 = 0; // Using global variable g_EE_ShadReg71 instead. //
//////	int EE_ShadReg72 = 0;
//////	int EE_ShadReg73 = 0;
//////	int EE_ShadReg74 = 0;
//////	int EE_ShadReg75 = 0;
//////	int EE_ShadReg76 = 0;
//////	int EE_ShadReg77 = 0;
//////	int EE_ShadReg78 = 0;
//////	int EE_ShadReg79 = 0;
//////	int EE_ShadReg80 = 0;
//////	int EE_ShadReg81 = 0;
//////	int EE_ShadReg82 = 0;
//////	int EE_ShadReg83 = 0;
//////	int EE_ShadReg84 = 0;
//////	int EE_ShadReg85 = 0;
//////	int EE_ShadReg86 = 0;
//////	int EE_ShadReg87 = 0;
//////	int EE_ShadReg88 = 0;
//////	int EE_ShadReg89 = 0;
//////	int EE_ShadReg90 = 0;
//////	int EE_ShadReg91 = 0;
//////	int EE_ShadReg92 = 0;
//////	int EE_ShadReg93 = 0;
//////	int EE_ShadReg94 = 0;
//////	int EE_ShadReg95 = 0;
//////	int EE_ShadReg96 = 0;
//////	int EE_ShadReg97 = 0;
//////	int EE_ShadReg98 = 0;
//////	int EE_ShadReg99 = 0;
//////	int EE_ShadReg100 = 0;
//////	int EE_ShadReg101 = 0;
//////	int EE_ShadReg102 = 0;
//////	int EE_ShadReg103 = 0;
//////	//int EE_ShadReg104 = 0; // Using global variable g_EE_ShadReg104 instead.  eep_sreg[104]: trim_ldo_3p6v //
//////	int EE_ShadReg105 = 0;
//////	int EE_ShadReg106 = 0;
//////	int EE_ShadReg107 = 0;
//////	int EE_ShadReg108 = 0;
//////	int EE_ShadReg109 = 0;
//////	int EE_ShadReg110 = 0;
//////	int EE_ShadReg111 = 0;
//////	*/
//////	float IzPost_TT = 0;
//////
//////	// Declare Variables //
//////	int NObin[1] = {0}; // Place holder //
//////	int NOhex = 0; // Place holder //
//////	int WordArray[16] = {0};
//////	int TempArray[30] = {0};
//////	int READ0_word[16] = {0};
//////	int READ1_word[16] = {0};
//////	int READ2_word[16] = {0};
//////	int READ3_word[16] = {0};
//////	int READ4_word[16] = {0};
//////	int READ5_word[16] = {0};
//////	int READ6_word[16] = {0};
//////	int READ7_word[16] = {0};
//////	int READ8_word[16] = {0};
//////	int READ9_word[16] = {0};
//////	int READ10_word[16] = {0};
//////	int READ11_word[16] = {0};
//////	int READ12_word[16] = {0};
//////	int READ13_word[16] = {0};
//////	int READ14_word[16] = {0};
//////	int READ15_word[16] = {0};
//////	int READ16_word[16] = {0};
//////	int READ17_word[16] = {0};
//////	int READ18_word[16] = {0};
//////	int READ19_word[16] = {0};
//////	int READ56_word[16] = {0};
//////	int READ57_word[16] = {0};
//////	int READ58_word[16] = {0};
//////	int READ59_word[16] = {0};
//////	int READ60_word[16] = {0};
//////	int READ61_word[16] = {0};
//////	int READ62_word[16] = {0};
//////	float iAFp_th =0.0;
//////	float iAF_array_p[100] = {0};
//////	//float iAF_array_s[100] = {0};
//////	int addr =0;
//////	int	Total_Addr_Count_p=0;
//////	int	Total_Addr_Count_s=0;
//////	int i=0;
//////	int	Trimmed=0;
//////	int	readTime=0;
//////	int TempShadowArray[112] = {0};
//////	int AntiFuse_Final = 1;
//////	int EEPROM_Final = 1;
//////	Pulse pulse;
//////
//////	// Reinit global variable
//////	for(i=0; i<100; i++)
//////	{
//////		gIZ_AF_post_P[i] = 0;
//////	}
//////
//////	// Initialize //
//////	//readTime = 3; // x*10us => 200us if readTime = 20
//////	readTime = 10; // x*10us => 200us if readTime = 20
//////	iAFp_th = 300e-6; // Threshold use to determine if Primary   is trimmed or not.  If trimmed, iAFp ~= 600uA
//////
//////	VBPP_Negative_Cycle();
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Setup //
////////	dvi_13->open_relay(BUS_SENSE1);
////////	dvi_13->open_relay(BUS_FORCE1);
////////	mux_14->open_relay(MUX_3_BUS3);
//////
//////	// Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
//////	VO_dvi->open_relay(CONN_FORCE0);
//////	VO_dvi->open_relay(CONN_SENSE0);
//////
//////	ovi_1->disconnect(OVI_CHANNEL_1); // Vpin does not use ovi-1-1 for Iz function
//////
//////	// Initialize DDD
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 4.0; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////	wait.delay_10_us(10);
//////	Close_relay(K2); // Primary: Connect DVI11_0 to Drain pin
//////	Close_relay(K12); // Primary: Connect DDD7_1 to Vpin(UV) pin
////////	Close_relay(K18); // Secondary: Connect DVI11_1 to FB pin
////////	Close_relay(K27); // Secondary: Connect DDD7_4 to Vout pin (Inno4)
//////	delay(4); // 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking
//////
//////	Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
//////	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);
//////
//////	Total_Addr_Count_p = 55;
//////
//////	for (i = 1; i<=Total_Addr_Count_p; i++)		
//////	{
//////		// Require more wait time for the first AF link
//////		if(i==1)	
//////			wait.delay_10_us(70);
//////		
//////		addr=i;
//////		DDD_Clock_UV_Antifuse(1); // Vpin(UV) clock through all AF links one by one
//////
//////		// Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
//////		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop); // Assert data pulse 
//////		wait.delay_10_us(readTime);		
//////		iAF_array_p[addr] = D_dvi->measure_average(5);
//////		gIZ_AF_post_P[addr] = iAF_array_p[addr];
//////		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop); // Deassert data pulse 
//////		wait.delay_10_us(3);
//////	}
//////
//////	// Power Down //
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA); // DVI_11_0 //
//////	VBPP_ramp_down(3, 0.0, 0.05);
//////	Open_relay(K12);
//////	Open_relay(K2); // Primary: Connect DVI11_0 to Drain pin
//////	VO_dvi->close_relay(CONN_FORCE0);
//////	VO_dvi->close_relay(CONN_SENSE0);
//////	VPIN_ovi->connect(VPIN_ch); // OVI_1_1 //
//////	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
//////
//////	// Antifuse current results
//////	// Primary
//////    IZ_iov1_p		=iAF_array_p[1];
//////	IZ_iov2_p		=iAF_array_p[2];
//////	IZ_iov3_p		=iAF_array_p[3]; 
//////	IZ_iov4_p		=iAF_array_p[4]; 
//////	IZ_iovSign_p	=iAF_array_p[5]; 
//////	IZ_iL1_p		=iAF_array_p[6];
//////	IZ_iL2_p		=iAF_array_p[7];
//////	IZ_iL3_p		=iAF_array_p[8]; 
//////	IZ_iLsign_p		=iAF_array_p[9]; 
//////	IZ_tOVL1_p		=iAF_array_p[10];
//////	IZ_tOVL2_p		=iAF_array_p[11];
//////	IZ_tOVLSign_p	=iAF_array_p[12]; 
//////	IZ_f1_p			=iAF_array_p[13];  
//////	IZ_f2_p			=iAF_array_p[14];
//////	IZ_fSign_p		=iAF_array_p[15];
//////	IZ_iov_Off_p	=iAF_array_p[16];
//////	IZ_iuvMinus_p	=iAF_array_p[17];
//////	IZ_uvDelay_p	=iAF_array_p[18];
//////	IZ_Loff_AR_p	=iAF_array_p[19];
//////	IZ_DisablAR_p	=iAF_array_p[20];
//////	IZ_didtComp_p	=iAF_array_p[21];
//////	IZ_OT_Hys_p		=iAF_array_p[22];
//////	IZ_LoffwOT_p	=iAF_array_p[23];
//////	IZ_iLselOff_p	=iAF_array_p[24];
//////	IZ_iLStdIcr_p	=iAF_array_p[25];
//////	IZ_iL20dn_p		=iAF_array_p[26];
//////	IZ_iL20up_p		=iAF_array_p[27];
//////	IZ_SAM_p		=iAF_array_p[28];
//////	IZ_OTP1_p		=iAF_array_p[29];
//////	IZ_OTP2_p		=iAF_array_p[30];
//////	IZ_OTP3_p		=iAF_array_p[31];
//////	IZ_SDSoff_p		=iAF_array_p[32];
//////	IZ_Rcv1_p		=iAF_array_p[33];
//////	IZ_Rcv2_p		=iAF_array_p[34];
//////	IZ_RcvSign_p	=iAF_array_p[35];
//////	IZ_drvSize1_p	=iAF_array_p[36];
//////	IZ_drvSize2_p	=iAF_array_p[37];
//////	IZ_drvSize3_p	=iAF_array_p[38];
//////	IZ_drvSize4_p	=iAF_array_p[39];
//////	IZ_RsenseUp_p	=iAF_array_p[40];
//////	IZ_vxAdj1_p		=iAF_array_p[41];
//////	IZ_vxAdj2_p		=iAF_array_p[42];
//////	IZ_vxAdj3_p		=iAF_array_p[43];
//////	IZ_vxAdj4_p		=iAF_array_p[44];
//////	IZ_vxAdj5_p		=iAF_array_p[45];
//////	IZ_iLRatio1_p	=iAF_array_p[46];
//////	IZ_iLRatio2_p	=iAF_array_p[47];
//////	IZ_iLRatio3_p	=iAF_array_p[48];
//////	IZ_iLRatio4_p	=iAF_array_p[49];
//////	IZ_iLTC1_p		=iAF_array_p[50];
//////	IZ_iLTC2_p		=iAF_array_p[51];
//////	IZ_iLTC3_p		=iAF_array_p[52];
//////	IZ_iLTC4_p		=iAF_array_p[53];
//////	IZ_ARreq_p		=iAF_array_p[54];
//////	IZ_ZF_p			=iAF_array_p[55];
//////
//////	// Check to be sure the anti-fuses have the correct values. //
//////	AntiFuse_Final = 1;
//////	if (g_OPCODE==4200 && g_Trim_Enable_P == 1)
//////	{
//////		for (i=1;i<56;i++)
//////		{
//////			if (iAF_array_p[i] > 200e-6 && g_xChk_P[i] == 0)
//////			{
//////					AntiFuse_Final = -999;
//////					g_Error_Flag = -168;
//////			}
//////			if (iAF_array_p[i] < 200e-6 && g_xChk_P[i] == 1)
//////			{
//////					AntiFuse_Final = -999;
//////					g_Error_Flag = -168;
//////			}
//////		}
//////	}
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BEGIN:
//////	// Check to make sure the feature trims from the InnoVI-TrimOptions.csv file 
//////	// data were correctly written to anti-fuses. //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	//g_xChk_P[1] = 0;
//////	//g_xChk_P[2] = 0;
//////	//g_xChk_P[3] = 0;
//////	//g_xChk_P[4] = 0;
//////	//g_xChk_P[5] = 0;
//////	//g_xChk_P[6] = 0;
//////	//g_xChk_P[7] = 0;
//////	//g_xChk_P[8] = 0;
//////	//g_xChk_P[9] = 0;
//////	//g_xChk_P[10] = 0;
//////	//g_xChk_P[11] = 0;
//////	//g_xChk_P[12] = 0;
//////	//g_xChk_P[13] = 0;
//////	//g_xChk_P[14] = 0;
//////	//g_xChk_P[15] = 0;
//////	//g_xChk_P[16] = 0;
//////	if ( (iAF_array_p[17] > 200e-6 && gTrim_iuvMinus_P_Trimops == 0) || (iAF_array_p[17] < 200e-6 && gTrim_iuvMinus_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_iuvMinus_P_Trimops //
//////	if ( (iAF_array_p[18] > 200e-6 && gTrim_uvDelay_P_Trimops == 0) || (iAF_array_p[18] < 200e-6 && gTrim_uvDelay_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_uvDelay_P_Trimops //
//////	if ( (iAF_array_p[19] > 200e-6 && gTrim_Loff_AR_P_Trimops == 0) || (iAF_array_p[19] < 200e-6 && gTrim_Loff_AR_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_Loff_AR_P_Trimops //
//////	if ( (iAF_array_p[20] > 200e-6 && gTrim_DisablAR_P_Trimops == 0) || (iAF_array_p[20] < 200e-6 && gTrim_DisablAR_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_DisablAR_P_Trimops //
//////	if ( (iAF_array_p[21] > 200e-6 && gTrim_didtComp_P_Trimops == 0) || (iAF_array_p[21] < 200e-6 && gTrim_didtComp_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_didtComp_P_Trimops //
//////	if ( (iAF_array_p[22] > 200e-6 && gTrim_OT_Hys_P == 0) || (iAF_array_p[22] < 200e-6 && gTrim_OT_Hys_P == 1)) AntiFuse_Final = -999; // gTrim_OT_Hys_P //
//////	if ( (iAF_array_p[23] > 200e-6 && gTrim_LoffwOT_P_Trimops == 0) || (iAF_array_p[23] < 200e-6 && gTrim_LoffwOT_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_LoffwOT_P_Trimops //
//////	if ( (iAF_array_p[24] > 200e-6 && gTrim_iLselOff_P_Trimops == 0) || (iAF_array_p[24] < 200e-6 && gTrim_iLselOff_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_iLselOff_P_Trimops //
//////	if ( (iAF_array_p[25] > 200e-6 && gTrim_iLStdIcr_P_Trimops == 0) || (iAF_array_p[25] < 200e-6 && gTrim_iLStdIcr_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_iLStdIcr_P_Trimops //
//////	if ( (iAF_array_p[26] > 200e-6 && gTrim_iL20dn_P_Trimops == 0) || (iAF_array_p[26] < 200e-6 && gTrim_iL20dn_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_iL20dn_P_Trimops //
//////	if ( (iAF_array_p[27] > 200e-6 && gTrim_iL20up_P_Trimops == 0) || (iAF_array_p[27] < 200e-6 && gTrim_iL20up_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_iL20up_P_Trimops //
//////	if ( (iAF_array_p[28] > 200e-6 && gTrim_SAM_P_Trimops == 0) || (iAF_array_p[28] < 200e-6 && gTrim_SAM_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_SAM_P_Trimops //
//////
//////	//Check OTP trim bits, 3 bits
//////	if((gTrim_OTP_P_Trimops & 1) == 1) // Trim_OTP1_P //
//////	{
//////		if(iAF_array_p[29] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_OTP_P_Trimops & 1) == 0) // Trim_OTP1_P //
//////	{
//////		if(iAF_array_p[29] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_OTP_P_Trimops & 2) == 2) // Trim_OTP2_P //
//////	{
//////		if(iAF_array_p[30] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_OTP_P_Trimops & 2) == 0) // Trim_OTP2_P //
//////	{
//////		if(iAF_array_p[30] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_OTP_P_Trimops & 4) == 4) // Trim_OTP3_P //
//////	{
//////		if(iAF_array_p[31] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_OTP_P_Trimops & 4) == 0) // Trim_OTP3_P //
//////	{
//////		if(iAF_array_p[31] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if ( (iAF_array_p[32] > 200e-6 && gTrim_SDSoff_P_Trimops == 0) || (iAF_array_p[32] < 200e-6 && gTrim_SDSoff_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_SDSoff_P_Trimops //
//////
//////	// Check Rcv trim bits, 3 bits //
//////	if((gTrim_Rcv_P_Trimops & 1) == 1) // Trim_Rcv1_P //
//////	{
//////		if(iAF_array_p[33] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_Rcv_P_Trimops & 1) == 0) // Trim_Rcv1_P //
//////	{
//////		if(iAF_array_p[33] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_Rcv_P_Trimops & 2) == 2) // Trim_Rcv2_P //
//////	{
//////		if(iAF_array_p[34] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_Rcv_P_Trimops & 2) == 0) // Trim_Rcv2_P //
//////	{
//////		if(iAF_array_p[34] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_Rcv_P_Trimops & 4) == 4) // Trim_RcvSign_P //
//////	{
//////		if(iAF_array_p[35] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_Rcv_P_Trimops & 4) == 0) // Trim_RcvSign_P //
//////	{
//////		if(iAF_array_p[35] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	// Check Driver Size trim bits, 4 bits //
//////	if((gTrim_drvSize_P_Trimops & 1) == 1) // Trim_drvSize1_P //
//////	{
//////		if(iAF_array_p[36] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 1) == 0) // Trim_drvSize1_P //
//////	{
//////		if(iAF_array_p[36] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 2) == 2) // Trim_drvSize2_P //
//////	{
//////		if(iAF_array_p[37] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 2) == 0) // Trim_drvSize2_P //
//////	{
//////		if(iAF_array_p[37] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 4) == 4) // Trim_drvSize3_P //
//////	{
//////		if(iAF_array_p[38] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 4) == 0) // Trim_drvSize3_P //
//////	{
//////		if(iAF_array_p[38] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 8) == 8) // Trim_drvSize4_P //
//////	{
//////		if(iAF_array_p[39] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_drvSize_P_Trimops & 8) == 0) // Trim_drvSize4_P //
//////	{
//////		if(iAF_array_p[39] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if ( (iAF_array_p[40] > 200e-6 && gTrim_RsenseUp_P_Trimops == 0) || (iAF_array_p[40] < 200e-6 && gTrim_RsenseUp_P_Trimops == 1)) AntiFuse_Final = -999; // gTrim_RsenseUp_P_Trimops //
//////
//////	// Check vxAdj trim bits, 5 bits //
//////	if((gTrim_vxAdj_P_Trimops & 1) == 1) // Trim_vxAdj1_P //
//////	{
//////		if(iAF_array_p[41] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_vxAdj_P_Trimops & 1) == 0) // Trim_vxAdj1_P //
//////	{
//////		if(iAF_array_p[41] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_vxAdj_P_Trimops & 2) == 2) // Trim_vxAdj2_P //
//////	{
//////		if(iAF_array_p[42] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_vxAdj_P_Trimops & 2) == 0) // Trim_vxAdj2_P //
//////	{
//////		if(iAF_array_p[42] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_vxAdj_P_Trimops & 4) == 4) // Trim_vxAdj3_P //
//////	{
//////		if(iAF_array_p[43] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_vxAdj_P_Trimops & 4) == 0) // Trim_vxAdj3_P //
//////	{
//////		if(iAF_array_p[43] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_vxAdj_P_Trimops & 8) == 8) // Trim_vxAdj4_P //
//////	{
//////		if(iAF_array_p[44] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_vxAdj_P_Trimops & 8) == 0) // Trim_vxAdj4_P //
//////	{
//////		if(iAF_array_p[44] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_vxAdj_P_Trimops & 16) == 16) // Trim_vxAdj5_P //
//////	{
//////		if(iAF_array_p[45] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_vxAdj_P_Trimops & 16) == 0) // Trim_vxAdj5_P //
//////	{
//////		if(iAF_array_p[45] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	// Check ILIM Ratio trim bits, 4 bits //
//////	if((gTrim_iLRatio_P_Trimops & 1) == 1) // Trim_iLRatio1_P //
//////	{
//////		if(iAF_array_p[46] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLRatio_P_Trimops & 1) == 0) // Trim_iLRatio1_P //
//////	{
//////		if(iAF_array_p[46] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLRatio_P_Trimops & 2) == 2) // Trim_iLRatio2_P //
//////	{
//////		if(iAF_array_p[47] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLRatio_P_Trimops & 2) == 0) // Trim_iLRatio2_P //
//////	{
//////		if(iAF_array_p[47] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLRatio_P_Trimops & 4) == 4) // Trim_iLRatio3_P //
//////	{
//////		if(iAF_array_p[48] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLRatio_P_Trimops & 4) == 0) // Trim_iLRatio3_P //	
//////	{
//////		if(iAF_array_p[48] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLRatio_P_Trimops & 8) == 8) // Trim_iLRatio4_P //
//////	{
//////		if(iAF_array_p[49] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLRatio_P_Trimops & 8) == 0) // Trim_iLRatio4_P //
//////	{
//////		if(iAF_array_p[49] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	// Check ILIM TC trim bits, 4 bits //
//////	if((gTrim_iLTC_P_Trimops & 1) == 1) // Trim_iLTC1_P //
//////	{
//////		if(iAF_array_p[50] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLTC_P_Trimops & 1) == 0) // Trim_iLTC1_P //
//////	{
//////		if(iAF_array_p[50] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLTC_P_Trimops & 2) == 2) // Trim_iLTC2_P //
//////	{
//////		if(iAF_array_p[51] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLTC_P_Trimops & 2) == 0) // Trim_iLTC2_P //
//////	{
//////		if(iAF_array_p[51] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLTC_P_Trimops & 4) == 4) // Trim_iLTC3_P //
//////	{
//////		if(iAF_array_p[52] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLTC_P_Trimops & 4) == 0) // Trim_iLTC3_P //
//////	{
//////		if(iAF_array_p[52] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if((gTrim_iLTC_P_Trimops & 8) == 8) // Trim_iLTC4_P //
//////	{
//////		if(iAF_array_p[53] < 200e-6)  AntiFuse_Final = -999;
//////	}
//////	if((gTrim_iLTC_P_Trimops & 8) == 0) // Trim_iLTC4_P //
//////	{
//////		if(iAF_array_p[53] > 200e-6)  AntiFuse_Final = -999;
//////	}
//////
//////	if ( (iAF_array_p[54] > 200e-6 && gTrim_AR_req_Trimops == 0) || (iAF_array_p[54] < 200e-6 && gTrim_AR_req_Trimops == 1)) AntiFuse_Final = -999; // gTrim_AR_req_Trimops //
//////	if ( iAF_array_p[55] < 200e-6 ) AntiFuse_Final = -999; // Final Zener Trim should always be trimmed. //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// END:
//////	// Check to make sure the feature trims from the InnoVI-TrimOptions.csv file 
//////	// data were correctly written to the anti-fuses. //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////
//////	// Error check //
//////	if (AntiFuse_Final < 0)
//////	{
//////		g_Error_Flag = -169;
//////	}
//////
//////	// Datalog //
//////	// Primary //
//////	PiDatalog(func, A_IZ_iov1_p, IZ_iov1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iov2_p, IZ_iov2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iov3_p, IZ_iov3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iov4_p, IZ_iov4_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iovSign_p, IZ_iovSign_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iL1_p, IZ_iL1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iL2_p, IZ_iL2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iL3_p, IZ_iL3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLsign_p, IZ_iLsign_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_tOVL1_p, IZ_tOVL1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_tOVL2_p, IZ_tOVL2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_tOVLSign_p, IZ_tOVLSign_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_f1_p, IZ_f1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_f2_p, IZ_f2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_fSign_p, IZ_fSign_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iov_Off_p, IZ_iov_Off_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iuvMinus_p, IZ_iuvMinus_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_uvDelay_p, IZ_uvDelay_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_Loff_AR_p, IZ_Loff_AR_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_DisablAR_p, IZ_DisablAR_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_didtComp_p, IZ_didtComp_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_OT_Hys_p, IZ_OT_Hys_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_LoffwOT_p, IZ_LoffwOT_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLselOff_p, IZ_iLselOff_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLStdIcr_p, IZ_iLStdIcr_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iL20dn_p, IZ_iL20dn_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iL20up_p, IZ_iL20up_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_SAM_p, IZ_SAM_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_OTP1_p, IZ_OTP1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_OTP2_p, IZ_OTP2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_OTP3_p, IZ_OTP3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_SDSoff_p, IZ_SDSoff_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_Rcv1_p, IZ_Rcv1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_Rcv2_p, IZ_Rcv2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_RcvSign_p, IZ_RcvSign_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_drvSize1_p, IZ_drvSize1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_drvSize2_p, IZ_drvSize2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_drvSize3_p, IZ_drvSize3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_drvSize4_p, IZ_drvSize4_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_RsenseUp_p, IZ_RsenseUp_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_vxAdj1_p, IZ_vxAdj1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_vxAdj2_p, IZ_vxAdj2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_vxAdj3_p, IZ_vxAdj3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_vxAdj4_p, IZ_vxAdj4_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_vxAdj5_p, IZ_vxAdj5_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLRatio1_p, IZ_iLRatio1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLRatio2_p, IZ_iLRatio2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLRatio3_p, IZ_iLRatio3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLRatio4_p, IZ_iLRatio4_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLTC1_p, IZ_iLTC1_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLTC2_p, IZ_iLTC2_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLTC3_p, IZ_iLTC3_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_iLTC4_p, IZ_iLTC4_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_ARreq_p, IZ_ARreq_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_IZ_ZF_p, IZ_ZF_p, 16, POWER_MICRO);
//////	PiDatalog(func, A_AntiFuse_Final, AntiFuse_Final, 16, POWER_UNIT);
//////
//////	// Open all relays //
//////	Initialize_Relays();
//////
//////	// Initialize Instruments //
//////	Initialize_Instruments();
//////
//////	// Drain //
//////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
//////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
//////
//////	// BPP //
//////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
//////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
//////
//////	// V pin //
//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
//////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
//////
//////	// FW //
//////	Close_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 1, VOLT_10_RANGE); // DVI_11_1 //
//////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
//////
//////	// SR //
//////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
//////	//SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	SR_dvi2k->set_current(SR_ch, 0.1e-9, RANGE_20_UA); // DVI_13_1, dvi2k //
//////	Mux20_Close_relay(K50); // SR pin hard short to GND with relay //
//////
//////	// BPS //
//////	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA); // DVI_9_1 //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 200e-3, VOLT_10_RANGE); // DVI_9_1 //
//////
//////	// IS //
//////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
//////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
//////
//////	// Vout //
//////	VO_dvi->set_voltage(VO_ch, 4.5, VOLT_10_RANGE); // DVI_9_0 //
//////	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
//////
//////	// COMP //
//////	FB_ovi->disconnect(2);
//////
//////	// VBD //
//////	VBD_dvi->set_voltage(VBD_ch, 0.0, VOLT_5_RANGE); // DVI_21_0 //
//////	VBD_dvi->set_current(VBD_ch, 30e-6, RANGE_30_UA); // DVI_21_0, prevent glitch //
//////	wait.delay_10_us(25); // Prevent glitch //
//////	VBD_dvi->set_current(VBD_ch, 0.1e-9, RANGE_30_UA); // DVI_21_0, Float //
//////
//////	// uVCC //
//////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_5_V); // OVI_3_2 //
//////	uVCC_ovi->set_current(uVCC_ch, 0.1e-9, RANGE_30_UA); // OVI_3_2, Float //
//////
//////	// DDD level //
//////	g_DDD_Low = 0.0; // Save current value //
//////	g_DDD_High = 3.3; // Save current value //
//////	wait.delay_10_us(g_DDDwait);
//////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(g_DDDwait);
//////
//////	// SDA //
//////	Mux20_Close_relay(K64);  // SDA pullup to 3.3V through 1.5kohm resistor. //
//////	ovi_3->set_voltage(OVI_CHANNEL_7, g_I2C_Pullup, RANGE_5_V); // OVI_3_7 //
//////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
//////	Mux20_Close_relay(K37);  // Disconnect ovi from SDA. //
//////	Mux20_Close_relay(K38);  // Connect SDA and SCL to DDD. //
//////	Mux20_Close_relay(K40);  // Connect SDA and SCL to DDD. //
//////
//////	// SCL //
//////	Mux20_Close_relay(K39);  // Disconnect ovi from SCL. //
//////	ddd_7->ddd_run_pattern(g_SDA_SCL_Low_start, g_SDA_SCL_Low_stop);  // Start with SDA and SCL low with DDD. //
//////	
//////	// Set DDD for I2C. //
//////	ddd_7->ddd_set_clock_period(g_Dclk_I2C);	
//////	ddd_7->ddd_set_voltage_ref(g_Vref_I2C);
//////		
//////	// Wait for relays //
//////	wait.delay_10_us(200); 
//////
//////	// Powerup //
//////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
//////	wait.delay_10_us(100); // Must wait long enough for uVCC to come up before sending I2C commands. //
//////
//////	// Powerup into test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Password, NObin, HEX); // Write I2C password for test mode. //
//////	Write_Word(g_TM_EN, g_TestMode_Enter, NObin, HEX); // Write I2C key to get into test mode. //
//////	//Write_Byte(g_Watchdog_Timer, 0x00, NObin, HEX); // Disable watchdog timer //
//////
//////	// Read all secondary registers using I2C. //
//////	Write_Word(g_RDADDR, g_READ56, NObin, HEX);// SREG0.  Shadow register. //
//////	Read_Word(g_RDADDR, READ56_word);// SREG0.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ57, NObin, HEX);// SREG1.  Shadow register. //
//////	Read_Word(g_RDADDR, READ57_word);// SREG1.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
//////	Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
//////	Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ60, NObin, HEX); // SREG4.  Shadow register. //
//////	Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ61, NObin, HEX); // SREG5.  Shadow register. //
//////	Read_Word(g_RDADDR, READ61_word); // SREG5.  Shadow register. //
//////
//////	Write_Word(g_RDADDR, g_READ62, NObin, HEX); // SREG6.  Shadow register. //
//////	Read_Word(g_RDADDR, READ62_word); // SREG6.  Shadow register. //
//////
//////	// Load TempShadowArray[] //
//////	TempShadowArray[0] = READ56_word[0];
//////	TempShadowArray[1] = READ56_word[1];
//////	TempShadowArray[2] = READ56_word[2];
//////	TempShadowArray[3] = READ56_word[3];
//////	TempShadowArray[4] = READ56_word[4];
//////	TempShadowArray[5] = READ56_word[5];
//////	TempShadowArray[6] = READ56_word[6];
//////	TempShadowArray[7] = READ56_word[7];
//////	TempShadowArray[8] = READ56_word[8];
//////	TempShadowArray[9] = READ56_word[9];
//////	TempShadowArray[10] = READ56_word[10];
//////	TempShadowArray[11] = READ56_word[11];
//////	TempShadowArray[12] = READ56_word[12];
//////	TempShadowArray[13] = READ56_word[13];
//////	TempShadowArray[14] = READ56_word[14];
//////	TempShadowArray[15] = READ56_word[15];
//////	TempShadowArray[16] = READ57_word[0];
//////	TempShadowArray[17] = READ57_word[1];
//////	TempShadowArray[18] = READ57_word[2];
//////	TempShadowArray[19] = READ57_word[3];
//////	TempShadowArray[20] = READ57_word[4];
//////	TempShadowArray[21] = READ57_word[5];
//////	TempShadowArray[22] = READ57_word[6];
//////	TempShadowArray[23] = READ57_word[7];
//////	TempShadowArray[24] = READ57_word[8];
//////	TempShadowArray[25] = READ57_word[9];
//////	TempShadowArray[26] = READ57_word[10];
//////	TempShadowArray[27] = READ57_word[11];
//////	TempShadowArray[28] = READ57_word[12];
//////	TempShadowArray[29] = READ57_word[13];
//////	TempShadowArray[30] = READ57_word[14];
//////	TempShadowArray[31] = READ57_word[15];
//////	TempShadowArray[32] = READ58_word[0];
//////	TempShadowArray[33] = READ58_word[1];
//////	TempShadowArray[34] = READ58_word[2];
//////	TempShadowArray[35] = READ58_word[3];
//////	TempShadowArray[36] = READ58_word[4];
//////	TempShadowArray[37] = READ58_word[5];
//////	TempShadowArray[38] = READ58_word[6];
//////	TempShadowArray[39] = READ58_word[7];
//////	TempShadowArray[40] = READ58_word[8];
//////	TempShadowArray[41] = READ58_word[9];
//////	TempShadowArray[42] = READ58_word[10];
//////	TempShadowArray[43] = READ58_word[11];
//////	TempShadowArray[44] = READ58_word[12];
//////	TempShadowArray[45] = READ58_word[13];
//////	TempShadowArray[46] = READ58_word[14];
//////	TempShadowArray[47] = READ58_word[15];
//////	TempShadowArray[48] = READ59_word[0];
//////	TempShadowArray[49] = READ59_word[1];
//////	TempShadowArray[50] = READ59_word[2];
//////	TempShadowArray[51] = READ59_word[3];
//////	TempShadowArray[52] = READ59_word[4];
//////	TempShadowArray[53] = READ59_word[5];
//////	TempShadowArray[54] = READ59_word[6];
//////	TempShadowArray[55] = READ59_word[7];
//////	TempShadowArray[56] = READ59_word[8];
//////	TempShadowArray[57] = READ59_word[9];
//////	TempShadowArray[58] = READ59_word[10];
//////	TempShadowArray[59] = READ59_word[11];
//////	TempShadowArray[60] = READ59_word[12];
//////	TempShadowArray[61] = READ59_word[13];
//////	TempShadowArray[62] = READ59_word[14];
//////	TempShadowArray[63] = READ59_word[15];
//////	TempShadowArray[64] = READ60_word[0];
//////	TempShadowArray[65] = READ60_word[1];
//////	TempShadowArray[66] = READ60_word[2];
//////	TempShadowArray[67] = READ60_word[3];
//////	TempShadowArray[68] = READ60_word[4];
//////	TempShadowArray[69] = READ60_word[5];
//////	TempShadowArray[70] = READ60_word[6];
//////	TempShadowArray[71] = READ60_word[7];
//////	TempShadowArray[72] = READ60_word[8];
//////	TempShadowArray[73] = READ60_word[9];
//////	TempShadowArray[74] = READ60_word[10];
//////	TempShadowArray[75] = READ60_word[11];
//////	TempShadowArray[76] = READ60_word[12];
//////	TempShadowArray[77] = READ60_word[13];
//////	TempShadowArray[78] = READ60_word[14];
//////	TempShadowArray[79] = READ60_word[15];
//////	TempShadowArray[80] = READ61_word[0];
//////	TempShadowArray[81] = READ61_word[1];
//////	TempShadowArray[82] = READ61_word[2];
//////	TempShadowArray[83] = READ61_word[3];
//////	TempShadowArray[84] = READ61_word[4];
//////	TempShadowArray[85] = READ61_word[5];
//////	TempShadowArray[86] = READ61_word[6];
//////	TempShadowArray[87] = READ61_word[7];
//////	TempShadowArray[88] = READ61_word[8];
//////	TempShadowArray[89] = READ61_word[9];
//////	TempShadowArray[90] = READ61_word[10];
//////	TempShadowArray[91] = READ61_word[11];
//////	TempShadowArray[92] = READ61_word[12];
//////	TempShadowArray[93] = READ61_word[13];
//////	TempShadowArray[94] = READ61_word[14];
//////	TempShadowArray[95] = READ61_word[15];
//////	TempShadowArray[96] = READ62_word[0];
//////	TempShadowArray[97] = READ62_word[1];
//////	TempShadowArray[98] = READ62_word[2];
//////	TempShadowArray[99] = READ62_word[3];
//////	TempShadowArray[100] = READ62_word[4];
//////	TempShadowArray[101] = READ62_word[5];
//////	TempShadowArray[102] = READ62_word[6];
//////	TempShadowArray[103] = READ62_word[7];
//////	TempShadowArray[104] = READ62_word[8];
//////	TempShadowArray[105] = READ62_word[9];
//////	TempShadowArray[106] = READ62_word[10];
//////	TempShadowArray[107] = READ62_word[11];
//////	TempShadowArray[108] = READ62_word[12];
//////	TempShadowArray[109] = READ62_word[13];
//////	TempShadowArray[110] = READ62_word[14];
//////	TempShadowArray[111] = READ62_word[15];
//////
//////	// Load EE_ShadRegXXX bits. //
//////	g_EE_ShadReg0 = TempShadowArray[0];
//////	g_EE_ShadReg1 = TempShadowArray[1];
//////	g_EE_ShadReg2 = TempShadowArray[2];
//////	g_EE_ShadReg3 = TempShadowArray[3];
//////	g_EE_ShadReg4 = TempShadowArray[4];
//////	g_EE_ShadReg5 = TempShadowArray[5];
//////	g_EE_ShadReg6 = TempShadowArray[6];
//////	g_EE_ShadReg7 = TempShadowArray[7];
//////	g_EE_ShadReg8 = TempShadowArray[8];
//////	g_EE_ShadReg9 = TempShadowArray[9];
//////	g_EE_ShadReg10 = TempShadowArray[10];
//////	g_EE_ShadReg11 = TempShadowArray[11];
//////	g_EE_ShadReg12 = TempShadowArray[12];
//////	g_EE_ShadReg13 = TempShadowArray[13];
//////	g_EE_ShadReg14 = TempShadowArray[14];
//////	g_EE_ShadReg15 = TempShadowArray[15];
//////	g_EE_ShadReg16 = TempShadowArray[16];
//////	g_EE_ShadReg17 = TempShadowArray[17];
//////	g_EE_ShadReg18 = TempShadowArray[18];
//////	g_EE_ShadReg19 = TempShadowArray[19];
//////	g_EE_ShadReg20 = TempShadowArray[20];
//////	g_EE_ShadReg21 = TempShadowArray[21];
//////	g_EE_ShadReg22 = TempShadowArray[22]; // bit[22]: trim_dopl //
//////	g_EE_ShadReg23 = TempShadowArray[23];
//////	g_EE_ShadReg24 = TempShadowArray[24];
//////	g_EE_ShadReg25 = TempShadowArray[25];
//////	g_EE_ShadReg26 = TempShadowArray[26];
//////	g_EE_ShadReg27 = TempShadowArray[27];
//////	g_EE_ShadReg28 = TempShadowArray[28];
//////	g_EE_ShadReg29 = TempShadowArray[29];
//////	g_EE_ShadReg30 = TempShadowArray[30];
//////	g_EE_ShadReg31 = TempShadowArray[31];
//////	g_EE_ShadReg32 = TempShadowArray[32];
//////	g_EE_ShadReg33 = TempShadowArray[33];
//////	g_EE_ShadReg34 = TempShadowArray[34];
//////	g_EE_ShadReg35 = TempShadowArray[35];
//////	g_EE_ShadReg36 = TempShadowArray[36];
//////	g_EE_ShadReg37 = TempShadowArray[37];
//////	g_EE_ShadReg38 = TempShadowArray[38]; // bit[38]: assign trim_CCesr //
//////	g_EE_ShadReg39 = TempShadowArray[39];
//////	g_EE_ShadReg40 = TempShadowArray[40];
//////	g_EE_ShadReg41 = TempShadowArray[41];
//////	g_EE_ShadReg42 = TempShadowArray[42];
//////	g_EE_ShadReg43 = TempShadowArray[43];
//////	g_EE_ShadReg44 = TempShadowArray[44];
//////	g_EE_ShadReg45 = TempShadowArray[45];
//////	g_EE_ShadReg46 = TempShadowArray[46];
//////	g_EE_ShadReg47 = TempShadowArray[47];
//////	g_EE_ShadReg48 = TempShadowArray[48];
//////	g_EE_ShadReg49 = TempShadowArray[49];
//////	g_EE_ShadReg50 = TempShadowArray[50];
//////	g_EE_ShadReg51 = TempShadowArray[51];
//////	g_EE_ShadReg52 = TempShadowArray[52];
//////	g_EE_ShadReg53 = TempShadowArray[53];
//////	g_EE_ShadReg54 = TempShadowArray[54];
//////	g_EE_ShadReg55 = TempShadowArray[55];
//////	g_EE_ShadReg56 = TempShadowArray[56];
//////	g_EE_ShadReg57 = TempShadowArray[57];
//////	g_EE_ShadReg58 = TempShadowArray[58];
//////	g_EE_ShadReg59 = TempShadowArray[59];
//////	g_EE_ShadReg60 = TempShadowArray[60];
//////	g_EE_ShadReg61 = TempShadowArray[61];
//////	g_EE_ShadReg62 = TempShadowArray[62];
//////	g_EE_ShadReg63 = TempShadowArray[63]; // bit[63]: trim_no_fb_pin //
//////	g_EE_ShadReg64 = TempShadowArray[64];
//////	g_EE_ShadReg65 = TempShadowArray[65];
//////	g_EE_ShadReg66 = TempShadowArray[66];
//////	g_EE_ShadReg67 = TempShadowArray[67];
//////	g_EE_ShadReg68 = TempShadowArray[68];
//////	g_EE_ShadReg69 = TempShadowArray[69];
//////	g_EE_ShadReg70 = TempShadowArray[70];
//////	g_EE_ShadReg71 = TempShadowArray[71];
//////	g_EE_ShadReg72 = TempShadowArray[72];
//////	g_EE_ShadReg73 = TempShadowArray[73];
//////	g_EE_ShadReg74 = TempShadowArray[74];
//////	g_EE_ShadReg75 = TempShadowArray[75];
//////	g_EE_ShadReg76 = TempShadowArray[76];
//////	g_EE_ShadReg77 = TempShadowArray[77];
//////	g_EE_ShadReg78 = TempShadowArray[78];
//////	g_EE_ShadReg79 = TempShadowArray[79];
//////	g_EE_ShadReg80 = TempShadowArray[80];
//////	g_EE_ShadReg81 = TempShadowArray[81];
//////	g_EE_ShadReg82 = TempShadowArray[82];
//////	g_EE_ShadReg83 = TempShadowArray[83];
//////	g_EE_ShadReg84 = TempShadowArray[84];
//////	g_EE_ShadReg85 = TempShadowArray[85];
//////	g_EE_ShadReg86 = TempShadowArray[86];
//////	g_EE_ShadReg87 = TempShadowArray[87];
//////	g_EE_ShadReg88 = TempShadowArray[88];
//////	g_EE_ShadReg89 = TempShadowArray[89];
//////	g_EE_ShadReg90 = TempShadowArray[90];
//////	g_EE_ShadReg91 = TempShadowArray[91];
//////	g_EE_ShadReg92 = TempShadowArray[92];
//////	g_EE_ShadReg93 = TempShadowArray[93];
//////	g_EE_ShadReg94 = TempShadowArray[94];
//////	g_EE_ShadReg95 = TempShadowArray[95];
//////	g_EE_ShadReg96 = TempShadowArray[96];
//////	g_EE_ShadReg97 = TempShadowArray[97];
//////	g_EE_ShadReg98 = TempShadowArray[98];
//////	g_EE_ShadReg99 = TempShadowArray[99];
//////	g_EE_ShadReg100 = TempShadowArray[100];
//////	g_EE_ShadReg101 = TempShadowArray[101];
//////	g_EE_ShadReg102 = TempShadowArray[102];
//////	g_EE_ShadReg103 = TempShadowArray[103];
//////	g_EE_ShadReg104 = TempShadowArray[104]; // eep_sreg[104]: trim_ldo_3p6v //
//////	g_EE_ShadReg105 = TempShadowArray[105];
//////	g_EE_ShadReg106 = TempShadowArray[106];
//////	g_EE_ShadReg107 = TempShadowArray[107];
//////	g_EE_ShadReg108 = TempShadowArray[108];
//////	g_EE_ShadReg109 = TempShadowArray[109];
//////	g_EE_ShadReg110 = TempShadowArray[110];
//////	g_EE_ShadReg111 = TempShadowArray[111];
//////
//////	// Load other EE_XX bits //
//////	EE_F1_S = TempShadowArray[12];
//////	EE_F2_S = TempShadowArray[13];
//////	EE_F3_S = TempShadowArray[14];
//////	EE_PKspdLd_S = TempShadowArray[45]; // 999 in InnoVI-TrimOptions.csv file // 
//////	EE_CV1_S = TempShadowArray[16];
//////	EE_VesrAdp_S = TempShadowArray[27];
//////	EE_ISvth3X1_S = TempShadowArray[32];
//////	EE_ISvth3X2_S = TempShadowArray[33];
//////	EE_ISvth3X3_S = TempShadowArray[34];
//////	EE_ISvth3X4_S = TempShadowArray[35];
//////	EE_ISvth3X5_S = TempShadowArray[36];
//////	EE_ISvth3X6_S = TempShadowArray[37];
//////	EE_CDC1_S = TempShadowArray[24];
//////	EE_CDC2_S = TempShadowArray[25];
//////	EE_CDC3_S = TempShadowArray[26];
//////	EE_CV2_S = TempShadowArray[17];
//////	EE_CV3_S = TempShadowArray[18];
//////	EE_CV4_S = TempShadowArray[19];
//////	EE_CV5_S = TempShadowArray[20];
//////	EE_CV6_S = TempShadowArray[21];
//////	EE_OSC0_S = TempShadowArray[8];
//////	EE_OSC1_S = TempShadowArray[9];
//////	EE_OSC2_S = TempShadowArray[10];
//////	EE_OSC3_S = TempShadowArray[11];
//////	EE_nDAC1_S = TempShadowArray[40];
//////	EE_nDAC2_S = TempShadowArray[41];
//////	EE_nDAC3_S = TempShadowArray[42];
//////	EE_nDAC4_S = TempShadowArray[43];
//////	EE_nDAC5_S = TempShadowArray[44];
//////	EE_pDAC1_S = TempShadowArray[48];
//////	EE_pDAC2_S = TempShadowArray[49];
//////	EE_pDAC3_S = TempShadowArray[50];
//////	EE_pDAC4_S = TempShadowArray[51];
//////	EE_pDAC5_S = TempShadowArray[52];
//////	EE_DofA1_S = TempShadowArray[56];
//////	EE_DofA2_S = TempShadowArray[57];
//////	EE_DofA3_S = TempShadowArray[58];
//////	EE_DofA4_S = TempShadowArray[59];
//////	EE_DofA5_S = TempShadowArray[60];
//////	EE_IsDAC1_S = TempShadowArray[64];
//////	EE_IsDAC2_S = TempShadowArray[65];
//////	EE_IsDAC3_S = TempShadowArray[66];
//////	EE_IsDAC4_S = TempShadowArray[67];
//////	EE_IsDAC5_S = TempShadowArray[68];
//////	EE_Gain1_S = TempShadowArray[72];
//////	EE_Gain2_S = TempShadowArray[73];
//////	EE_Gain3_S = TempShadowArray[74];
//////	EE_Gain4_S = TempShadowArray[75];
//////	EE_CCoff1_S = TempShadowArray[69];
//////	EE_CCoff2_S = TempShadowArray[70];
//////	EE_CCoff3_S = TempShadowArray[71];
//////	EE_IsCal1_S = TempShadowArray[76];
//////	EE_IsCal2_S = TempShadowArray[77];
//////	EE_IsCal3_S = TempShadowArray[78];
//////	EE_DsoftEn_S = TempShadowArray[23];
//////	EE_DOPL_S = TempShadowArray[22];
//////	EE_DoplEnCp_S = TempShadowArray[15];
//////	EE_ESRsel_S = TempShadowArray[29];
//////	EE_DdampEn_S = TempShadowArray[28];
//////	//EE_ZF_S = TempShadowArray[ // Removed from Inno3.  Not in InnoVI. //
//////	//EE_SiRev3_s = TempShadowArray[]; // Inno3 only, not for InnoVI //
//////	//EE_SiRev2_s = TempShadowArray[]; // Inno3 only, not for InnoVI //
//////	//EE_SiRev1_s = TempShadowArray[]; // Inno3 only, not for InnoVI //
//////
//////	// Check to be sure the Shadow Register has correct values. //
//////	EEPROM_Final = 1;
//////	if (g_OPCODE==4200)
//////	{
//////		for (i=0;i<112;i++)
//////		{
//////			if (TempShadowArray[i] != g_ShadowRegister[i])
//////			{
//////				EEPROM_Final = -999;
//////				g_Error_Flag = -129;
//////			}
//////		}
//////	}
//////
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// BEGIN:
//////	// Check to make sure the feature trims from the InnoVI-TrimOptions.csv file 
//////	// data were correctly written to EEPROM. //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// TempShadowArray[0] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[1] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[2] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[3] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[4] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[5] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[6] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[7] = ; // bit[7:0]: Manufacture information //
//////	// TempShadowArray[8] = ; // OSC trim.  bit[11:8]: trim_chy_osc //
//////	// TempShadowArray[9] = ; // OSC trim.  bit[11:8]: trim_chy_osc //
//////	// TempShadowArray[10] = ; // OSC trim.  bit[11:8]:trim_chy_osc //
//////	// TempShadowArray[11] = ; // OSC trim.  bit[11:8]: trim_chy_osc //
//////	// TempShadowArray[12] = ; // FOSC-S trim.  bit[14:12]: trim_inno_osc //  
//////	// TempShadowArray[13] = ; // FOSC-S trim.  bit[14:12]: trim_inno_osc //
//////	// TempShadowArray[14] = ; // FOSC-S trim.  bit[14:12]: trim_inno_osc //
//////	if (TempShadowArray[15] != gTrim_SdwReg15_Trimops)  EEPROM_Final = -999; // bit[15]: trim_dopl_en_cp //
//////	// TempShadowArray[16] = ; // CV trim.  bit[21:16]: trim_cv //
//////	// TempShadowArray[17] = ; // CV trim.  bit[21:16]: trim_cv //
//////	// TempShadowArray[18] = ; // CV trim.  bit[21:16]: trim_cv //
//////	// TempShadowArray[19] = ; // CV trim.  bit[21:16]: trim_cv //
//////	// TempShadowArray[20] = ; // CV trim.  bit[21:16]: trim_cv //
//////	// TempShadowArray[21] = ; // CV trim.  bit[21:16]: trim_cv //
//////	if (TempShadowArray[22] != gTrim_SdwReg22_Trimops)  EEPROM_Final = -999; // DOPL.  bit[22]: trim_dopl //
//////	if (TempShadowArray[23] != gTrim_SdwReg23_Trimops)  EEPROM_Final = -999; // DsoftEn.  bit[23]: trim_dsoften //
//////	// TempShadowArray[24] = ; // CDC trim.  bit[26:24]: trim_cdc // 
//////	// TempShadowArray[25] = ; // CDC trim.  bit[26:24]: trim_cdc //
//////	// TempShadowArray[26] = ; // CDC trim.  bit[26:24]: trim_cdc //
//////	if (TempShadowArray[27] != gTrim_SdwReg27_Trimops)  EEPROM_Final = -999; // VesrAdp.  bit[27]: trim_dversrslpadj //
//////	if (TempShadowArray[28] != gTrim_SdwReg28_Trimops)  EEPROM_Final = -999; // DdampEn.  bit[28]: trim_ddamen //
//////	if (TempShadowArray[29] != gTrim_SdwReg29_Trimops)  EEPROM_Final = -999; // ESRsel.  bit[29]: trim_esrhi //
//////	if (TempShadowArray[30] != gTrim_SdwReg30_Trimops)  EEPROM_Final = -999; // bit[30]: trim_en_b_bps_cp //
//////	// TempShadowArray[31] = ; // ADC trim.  bit[31]: trim_vout_sns[0] //
//////	// TempShadowArray[32] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	// TempShadowArray[33] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	// TempShadowArray[34] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	// TempShadowArray[35] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	// TempShadowArray[36] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	// TempShadowArray[37] = ; // ISvth3X-S trim.  bit[37:32]: assign trim_cc_3x //
//////	if (TempShadowArray[38] != gTrim_SdwReg38_Trimops)  EEPROM_Final = -999; // Vesr CC.  bit[38]: assign trim_CCesr //
//////	if (TempShadowArray[39] != gTrim_SdwReg39_Trimops)  EEPROM_Final = -999; // bit[39]: assign trim_t2;  no longer used for TF. Not used. //
//////	// TempShadowArray[40] = ; // nDAC trim.  bit[44:40]: assign trim_dac_100mv //
//////	// TempShadowArray[41] = ; // nDAC trim.  bit[44:40]: assign trim_dac_100mv //
//////	// TempShadowArray[42] = ; // nDAC trim.  bit[44:40]: assign trim_dac_100mv //
//////	// TempShadowArray[43] = ; // nDAC trim.  bit[44:40]: assign trim_dac_100mv //
//////	// TempShadowArray[44] = ; // nDAC trim.  bit[44:40]: assign trim_dac_100mv //
//////	if (TempShadowArray[45] != gTrim_SdwReg45_Trimops)  EEPROM_Final = -999; // bit[47:45]: assign trim_pk //
//////	if (TempShadowArray[46] != gTrim_SdwReg46_Trimops)  EEPROM_Final = -999; // bit[47:45]: assign trim_pk //
//////	if (TempShadowArray[47] != gTrim_SdwReg47_Trimops)  EEPROM_Final = -999; // bit[47:45]: assign trim_pk //
//////	// TempShadowArray[48] = ; // pDAC trim.  bit[52:48]: trim_dac_12p5mv //
//////	// TempShadowArray[49] = ; // pDAC trim.  bit[52:48]: trim_dac_12p5mv //
//////	// TempShadowArray[50] = ; // pDAC trim.  bit[52:48]: trim_dac_12p5mv //
//////	// TempShadowArray[51] = ; // pDAC trim.  bit[52:48]: trim_dac_12p5mv //
//////	// TempShadowArray[52] = ; // pDAC trim.  bit[52:48]: trim_dac_12p5mv //
//////	if (TempShadowArray[53] != gTrim_SdwReg53_Trimops)  EEPROM_Final = -999; // bit[54:53]: trim_OVLTIMER //
//////	if (TempShadowArray[54] != gTrim_SdwReg54_Trimops)  EEPROM_Final = -999; // bit[54:53]: trim_OVLTIMER //
//////	if (TempShadowArray[55] != gTrim_SdwReg55_Trimops)  EEPROM_Final = -999; // bit[55]: trim_dis_cali //
//////	// TempShadowArray[56] = ; // DofA trim.  bit[60:56]: trim_dac_adc //
//////	// TempShadowArray[57] = ; // DofA trim.  bit[60:56]: trim_dac_adc //
//////	// TempShadowArray[58] = ; // DofA trim.  bit[60:56]: trim_dac_adc //
//////	// TempShadowArray[59] = ; // DofA trim.  bit[60:56]: trim_dac_adc //
//////	// TempShadowArray[60] = ; // DofA trim.  bit[60:56]: trim_dac_adc //
//////	if (TempShadowArray[61] != gTrim_SdwReg61_Trimops)  EEPROM_Final = -999; // bit[62:61]: trim_bleed_k //
//////	if (TempShadowArray[62] != gTrim_SdwReg62_Trimops)  EEPROM_Final = -999; // bit[62:61]: trim_bleed_k //
//////	if (TempShadowArray[63] != gTrim_SdwReg63_Trimops)  EEPROM_Final = -999; // bit[63]: trim_no_fb_pin //
//////	// TempShadowArray[64] = ; // IsDAC trim.  bit[68:64]: trim_dac_cc //
//////	// TempShadowArray[65] = ; // IsDAC trim.  bit[68:64]: trim_dac_cc //
//////	// TempShadowArray[66] = ; // IsDAC trim.  bit[68:64]: trim_dac_cc //
//////	// TempShadowArray[67] = ; // IsDAC trim.  bit[68:64]: trim_dac_cc //
//////	// TempShadowArray[68] = ; // IsDAC trim.  bit[68:64]: trim_dac_cc //
//////	if (TempShadowArray[69] != gTrim_SdwReg69_Trimops)  EEPROM_Final = -999; // CCoff trim.  bit[71:69]: trim_comp_cc // 
//////	if (TempShadowArray[70] != gTrim_SdwReg70_Trimops)  EEPROM_Final = -999; // CCoff trim.  bit[71:69]: trim_comp_cc // 
//////	if (TempShadowArray[71] != gTrim_SdwReg71_Trimops)  EEPROM_Final = -999; // CCoff trim.  bit[71:69]: trim_comp_cc //
//////	// TempShadowArray[72] = ; // Gain trim.  bit[75:72]: trim_is_gain // 
//////	// TempShadowArray[73] = ; // Gain trim.  bit[75:72]: trim_is_gain //
//////	// TempShadowArray[74] = ; // Gain trim.  bit[75:72]: trim_is_gain //
//////	// TempShadowArray[75] = ; // Gain trim.  bit[75:72]: trim_is_gain //
//////	if (TempShadowArray[76] != gTrim_SdwReg76_Trimops)  EEPROM_Final = -999; // bit[76]: trim_no_sec_req_adc //
//////	// TempShadowArray[77] = ; // IsCal trim.  bit[79:77]: trim_is_cali //
//////	// TempShadowArray[78] = ; // IsCal trim.  bit[79:77]: trim_is_cali //
//////	// TempShadowArray[79] = ; // IsCal trim.  bit[79:77]: trim_is_cali //
//////	if (TempShadowArray[80] != gTrim_SdwReg80_Trimops)  EEPROM_Final = -999; // eep_sreg[80]: adc retiming timeout option //
//////	if (TempShadowArray[81] != gTrim_SdwReg81_Trimops)  EEPROM_Final = -999; // eep_sreg[82:81]: K value for I_measure filter block //
//////	if (TempShadowArray[82] != gTrim_SdwReg82_Trimops)  EEPROM_Final = -999; // eep_sreg[82:81]: K value for I_measure filter block //
//////	if (TempShadowArray[83] != gTrim_SdwReg83_Trimops)  EEPROM_Final = -999; // eep_sreg[83]: ignor_lsb, FB DAC calculation //
//////	if (TempShadowArray[84] != gTrim_SdwReg84_Trimops)  EEPROM_Final = -999; // eep_sreg[84]: cp_res, FB DAC calculation //
//////	if (TempShadowArray[85] != gTrim_SdwReg85_Trimops)  EEPROM_Final = -999; // eep_sreg[85]: CC register value lower limit. 0=>32, 1=>12 //
//////	if (TempShadowArray[86] != gTrim_SdwReg86_Trimops)  EEPROM_Final = -999; // eep_sreg[87:86]:trim_cc_cali_hys //
//////	if (TempShadowArray[87] != gTrim_SdwReg87_Trimops)  EEPROM_Final = -999; // eep_sreg[87:86]:trim_cc_cali_hys //
//////	if (TempShadowArray[88] != gTrim_SdwReg88_Trimops)  EEPROM_Final = -999; // eep_sreg[88]: trim_i2c_slave_addr_bit0 //
//////	if (TempShadowArray[89] != gTrim_SdwReg89_Trimops)  EEPROM_Final = -999; // eep_sreg[89]: trim_i2c_slave_addr_bit5 //
//////	if (!g_EE_ShadReg55) // If calibration enabled (bit 55 not trimmed) //
//////	{
//////		if (TempShadowArray[90] != gTrim_SdwReg90_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////		if (TempShadowArray[91] != gTrim_SdwReg91_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////		if (TempShadowArray[92] != gTrim_SdwReg92_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////		if (TempShadowArray[93] != gTrim_SdwReg93_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////		if (TempShadowArray[94] != gTrim_SdwReg94_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////		if (TempShadowArray[95] != gTrim_SdwReg95_Trimops)  EEPROM_Final = -999; // eep_sreg[95:90]: trim_cali_ofst[5:0] //
//////	}
//////	// TempShadowArray[96] = ; // FOSC-S trim(current ref trim) eep_sreg[99:96]: trim_inno_iint[3:0] //
//////	// TempShadowArray[97] = ; // FOSC-S trim(current ref trim) eep_sreg[99:96]: trim_inno_iint[3:0] //
//////	// TempShadowArray[98] = ; // FOSC-S trim(current ref trim) eep_sreg[99:96]: trim_inno_iint[3:0] //
//////	// TempShadowArray[99] = ; // FOSC-S trim(current ref trim) eep_sreg[99:96]: trim_inno_iint[3:0] //
//////	// TempShadowArray[100] = ; // ADC trim. eep_sreg[103:100]: trim_vout_sns[4:1] //
//////	// TempShadowArray[101] = ; // ADC trim. eep_sreg[103:100]: trim_vout_sns[4:1] //
//////	// TempShadowArray[102] = ; // ADC trim. eep_sreg[103:100]: trim_vout_sns[4:1] //
//////	// TempShadowArray[103] = ; // ADC trim. eep_sreg[103:100]: trim_vout_sns[4:1] //
//////	if (TempShadowArray[104] != gTrim_SdwReg104_Trimops)  EEPROM_Final = -999; // eep_sreg[104]: trim_ldo_3p6v //
//////	if (TempShadowArray[105] != gTrim_SdwReg105_Trimops)  EEPROM_Final = -999; // eep_sreg[106:105]:trim_spare_bits[1:0] //
//////	if (TempShadowArray[106] != gTrim_SdwReg106_Trimops)  EEPROM_Final = -999; // eep_sreg[106:105]:trim_spare_bits[1:0] //
//////	if (TempShadowArray[107] != gTrim_SdwReg107_Trimops)  EEPROM_Final = -999; // eep_sreg[111:107]:H code[4:0] //
//////	if (TempShadowArray[108] != gTrim_SdwReg108_Trimops)  EEPROM_Final = -999; // eep_sreg[111:107]:H code[4:0] //
//////	if (TempShadowArray[109] != gTrim_SdwReg109_Trimops)  EEPROM_Final = -999; // eep_sreg[111:107]:H code[4:0] //
//////	if (TempShadowArray[110] != gTrim_SdwReg110_Trimops)  EEPROM_Final = -999; // eep_sreg[111:107]:H code[4:0] //
//////	if (TempShadowArray[111] != gTrim_SdwReg111_Trimops)  EEPROM_Final = -999; // eep_sreg[111:107]:H code[4:0] //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////	// END:
//////	// Check to make sure the feature trims from the InnoVI-TrimOptions.csv file 
//////	// data were correctly writte to EEPROM. //
//////	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//////
//////	// Error check //
//////	if (EEPROM_Final < 0)
//////	{
//////		g_Error_Flag = -129;
//////	}
//////
//////	// Powerdown //
//////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
//////	Mux20_Open_relay(K64);
//////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
//////	Mux20_Open_relay(K37);
//////	Mux20_Open_relay(K38);
//////	Mux20_Open_relay(K40);
//////	Mux20_Open_relay(K39);
//////	Mux20_Open_relay(K50); // SR pin hard short to GND with relay //
//////	VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE); // DVI_9_0 //
//////	wait.delay_10_us(20);
//////	Open_relay(K18);
//////	FW_dvi->set_voltage(FW_ch, 0, VOLT_10_RANGE); // DVI_11_1 //
//////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
//////	uVCCrampDown(0.5, 0, 0.1);
//////	VBPS_ramp_down(4, 0, 200e-3);
//////	VBD_dvi->set_voltage(VBD_ch, 3, VOLT_5_RANGE); // DVI_21_0, prevent undershoot //
//////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
//////	wait.delay_10_us(20);
//////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_5_RANGE); // DVI_21_0 //
//////	FB_ovi->connect(2);
//////	ddd_7->ddd_set_clock_period(Dclk_period);
//////	ddd_7->ddd_set_voltage_ref(DDD_Vref);
//////	
//////	// DDD level //
//////	//g_DDD_Low = 0.0; // Save current value //
//////	//g_DDD_High = 4.0; // Save current value //
//////	//wait.delay_10_us(100);
//////	//ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
//////	//ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
//////	wait.delay_10_us(200); // Wait for relays //
//////
//////	// Datalog //
//////	// Secondary //
//////	PiDatalog(func, A_EE_F1_S, EE_F1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F2_S, EE_F2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F3_S, EE_F3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F_Iint1_S, EE_F_Iint1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F_Iint2_S, EE_F_Iint2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F_Iint3_S, EE_F_Iint3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_F_Iint4_S, EE_F_Iint4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_PKspdLd_S, EE_PKspdLd_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV1_S, EE_CV1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_VesrAdp_S, EE_VesrAdp_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X1_S, EE_ISvth3X1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X2_S, EE_ISvth3X2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X3_S, EE_ISvth3X3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X4_S, EE_ISvth3X4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X5_S, EE_ISvth3X5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ISvth3X6_S, EE_ISvth3X6_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CDC1_S, EE_CDC1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CDC2_S, EE_CDC2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CDC3_S, EE_CDC3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV2_S, EE_CV2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV3_S, EE_CV3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV4_S, EE_CV4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV5_S, EE_CV5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CV6_S, EE_CV6_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_OSC0_S, EE_OSC0_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_OSC1_S, EE_OSC1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_OSC2_S, EE_OSC2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_OSC3_S, EE_OSC3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_nDAC1_S, EE_nDAC1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_nDAC2_S, EE_nDAC2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_nDAC3_S, EE_nDAC3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_nDAC4_S, EE_nDAC4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_nDAC5_S, EE_nDAC5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_pDAC1_S, EE_pDAC1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_pDAC2_S, EE_pDAC2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_pDAC3_S, EE_pDAC3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_pDAC4_S, EE_pDAC4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_pDAC5_S, EE_pDAC5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DofA1_S, EE_DofA1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DofA2_S, EE_DofA2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DofA3_S, EE_DofA3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DofA4_S, EE_DofA4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DofA5_S, EE_DofA5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsDAC1_S, EE_IsDAC1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsDAC2_S, EE_IsDAC2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsDAC3_S, EE_IsDAC3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsDAC4_S, EE_IsDAC4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsDAC5_S, EE_IsDAC5_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_Gain1_S, EE_Gain1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_Gain2_S, EE_Gain2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_Gain3_S, EE_Gain3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_Gain4_S, EE_Gain4_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CCoff1_S, EE_CCoff1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CCoff2_S, EE_CCoff2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_CCoff3_S, EE_CCoff3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsCal1_S, EE_IsCal1_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsCal2_S, EE_IsCal2_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_IsCal3_S, EE_IsCal3_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DsoftEn_S, EE_DsoftEn_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DOPL_S, EE_DOPL_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DoplEnCp_S, EE_DoplEnCp_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ESRsel_S, EE_ESRsel_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_DdampEn_S, EE_DdampEn_S, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg0, g_EE_ShadReg0, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg1, g_EE_ShadReg1, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg2, g_EE_ShadReg2, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg3, g_EE_ShadReg3, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg4, g_EE_ShadReg4, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg5, g_EE_ShadReg5, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg6, g_EE_ShadReg6, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg7, g_EE_ShadReg7, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg8, g_EE_ShadReg8, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg9, g_EE_ShadReg9, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg10, g_EE_ShadReg10, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg11, g_EE_ShadReg11, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg12, g_EE_ShadReg12, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg13, g_EE_ShadReg13, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg14, g_EE_ShadReg14, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg15, g_EE_ShadReg15, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg16, g_EE_ShadReg16, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg17, g_EE_ShadReg17, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg18, g_EE_ShadReg18, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg19, g_EE_ShadReg19, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg20, g_EE_ShadReg20, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg21, g_EE_ShadReg21, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg22, g_EE_ShadReg22, 16, POWER_UNIT); // bit[22]: trim_dopl //
//////	PiDatalog(func, A_EE_ShadReg23, g_EE_ShadReg23, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg24, g_EE_ShadReg24, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg25, g_EE_ShadReg25, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg26, g_EE_ShadReg26, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg27, g_EE_ShadReg27, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg28, g_EE_ShadReg28, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg29, g_EE_ShadReg29, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg30, g_EE_ShadReg30, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg31, g_EE_ShadReg31, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg32, g_EE_ShadReg32, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg33, g_EE_ShadReg33, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg34, g_EE_ShadReg34, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg35, g_EE_ShadReg35, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg36, g_EE_ShadReg36, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg37, g_EE_ShadReg37, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg38, g_EE_ShadReg38, 16, POWER_UNIT); // bit[38]: assign trim_CCesr //
//////	PiDatalog(func, A_EE_ShadReg39, g_EE_ShadReg39, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg40, g_EE_ShadReg40, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg41, g_EE_ShadReg41, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg42, g_EE_ShadReg42, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg43, g_EE_ShadReg43, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg44, g_EE_ShadReg44, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg45, g_EE_ShadReg45, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg46, g_EE_ShadReg46, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg47, g_EE_ShadReg47, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg48, g_EE_ShadReg48, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg49, g_EE_ShadReg49, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg50, g_EE_ShadReg50, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg51, g_EE_ShadReg51, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg52, g_EE_ShadReg52, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg53, g_EE_ShadReg53, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg54, g_EE_ShadReg54, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg55, g_EE_ShadReg55, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg56, g_EE_ShadReg56, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg57, g_EE_ShadReg57, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg58, g_EE_ShadReg58, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg59, g_EE_ShadReg59, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg60, g_EE_ShadReg60, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg61, g_EE_ShadReg61, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg62, g_EE_ShadReg62, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg63, g_EE_ShadReg63, 16, POWER_UNIT); // bit[63]: trim_no_fb_pin //
//////	PiDatalog(func, A_EE_ShadReg64, g_EE_ShadReg64, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg65, g_EE_ShadReg65, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg66, g_EE_ShadReg66, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg67, g_EE_ShadReg67, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg68, g_EE_ShadReg68, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg69, g_EE_ShadReg69, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg70, g_EE_ShadReg70, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg71, g_EE_ShadReg71, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg72, g_EE_ShadReg72, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg73, g_EE_ShadReg73, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg74, g_EE_ShadReg74, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg75, g_EE_ShadReg75, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg76, g_EE_ShadReg76, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg77, g_EE_ShadReg77, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg78, g_EE_ShadReg78, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg79, g_EE_ShadReg79, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg80, g_EE_ShadReg80, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg81, g_EE_ShadReg81, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg82, g_EE_ShadReg82, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg83, g_EE_ShadReg83, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg84, g_EE_ShadReg84, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg85, g_EE_ShadReg85, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg86, g_EE_ShadReg86, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg87, g_EE_ShadReg87, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg88, g_EE_ShadReg88, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg89, g_EE_ShadReg89, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg90, g_EE_ShadReg90, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg91, g_EE_ShadReg91, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg92, g_EE_ShadReg92, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg93, g_EE_ShadReg93, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg94, g_EE_ShadReg94, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg95, g_EE_ShadReg95, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg96, g_EE_ShadReg96, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg97, g_EE_ShadReg97, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg98, g_EE_ShadReg98, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg99, g_EE_ShadReg99, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg100, g_EE_ShadReg100, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg101, g_EE_ShadReg101, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg102, g_EE_ShadReg102, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg103, g_EE_ShadReg103, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg104, g_EE_ShadReg104, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg105, g_EE_ShadReg105, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg106, g_EE_ShadReg106, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg107, g_EE_ShadReg107, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg108, g_EE_ShadReg108, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg109, g_EE_ShadReg109, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg110, g_EE_ShadReg110, 16, POWER_UNIT);
//////	PiDatalog(func, A_EE_ShadReg111, g_EE_ShadReg111, 16, POWER_UNIT);
//////	PiDatalog(func, A_EEPROM_Final, EEPROM_Final, 16, POWER_UNIT);
//////
//////	// Test Time End //
//////	if (g_TstTime_Enble_P)
//////	{
//////		g_endtime = g_mytimer.GetElapsedTime();
//////		IzPost_TT = (g_endtime - g_begintime)*1e-6;
//////		PiDatalog(func, A_IzPost_TT, IzPost_TT, 16, POWER_MILLI);
//////	}
//////
//////	// Check any test failed //
//////	if (PiGetAnyFailStatus())		
//////	{
//////		g_PartFailed = 1;
//////	}
}
