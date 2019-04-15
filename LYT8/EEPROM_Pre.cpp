//==============================================================================
// EEPROM_Pre.cpp (User function)
// 
//    void EEPROM_Pre_user_init(test_function& func)
//    void EEPROM_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "EEPROM_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void EEPROM_Pre_user_init(test_function& func)
{
	EEPROM_Pre_params *ours;
    ours = (EEPROM_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void EEPROM_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    EEPROM_Pre_params *ours;
    ours = (EEPROM_Pre_params *)func.params;

	// Increment function number //
	gFuncNum++;	

	// Datalog gFuncNum variable //
	if(gDisplay_FuncNum)
		PiDatalog(func, A_fNum_Eeprom_Pre, gFuncNum, 24,	POWER_UNIT);

	int		func_fail_bin = ours->fail_bin;

	/////*int	E0_data_P	=0,
	////	E2_data_P	=0,
	////	E4_data_P	=0,
	////	E6_data_P	=0,
	////	E8_data_P	=0;
	////	
	////int	E0_data_S	=0,
	////	E2_data_S	=0,
	////	E4_data_S	=0,
	////	E6_data_S	=0,
	////	E8_data_S	=0;*/
			
	int	E00_Si_ID_0_P	=0,
		E01_Si_ID_1_P	=0,
		E02_Si_ID_2_P	=0,
		E03_Si_ID_3_P	=0,
		E04_Si_ID_4_P	=0,
		E05_Si_ID_5_P	=0,
		E06_Si_ID_6_P	=0,
		E07_Si_ID_7_P	=0,
		E08_fOSC_0_P	=0,
		E09_fOSC_1_P	=0,
		E10_fOSC_2_P	=0,
		E11_fOSC_3_P	=0,
		E12_yInter_0_P	=0,
		E13_yInter_1_P	=0,
		E14_yInter_2_P	=0,
		E15_yInter_3_P	=0,
		E16_ILIM_0_P	=0,
		E17_ILIM_1_P	=0,
		E18_ILIM_2_P	=0,
		E19_ILIM_3_P	=0,
		E20_ILIM_4_P	=0,
		E21_ArSkip_P	=0,
		E22_ArOnT_P	=0,
		E23_ArOffT_0_P	=0,
		E24_ArOffT_1_P	=0,
		E25_StrtFREQ_P	=0,
		E26_OnTSL_0_P	=0,
		E27_OnTSL_1_P	=0,
		E28_ONTSL_2_P	=0,
		E29_ONTSL_3_P	=0,
		E30_ONTSL_4_P	=0,
		E31_ShunEn_P	=0,
		E32_RcvTH_0_P	=0,
		E33_RcvTH_1_P	=0,
		E34_RcvTH_2_P	=0,
		E35_GanMode_P	=0,
		E36_VxTrim_0_P	=0,
		E37_VxTrim_1_P	=0,
		E38_VxTrim_2_P	=0,
		E39_VxTrim_3_P	=0,
		E40_VxTrim_4_P	=0,
		E41_DrSize_0_P	=0,
		E42_DrSize_1_P	=0,
		E43_DrSize_2_P	=0,
		E44_DrSize_3_P	=0,
		E45_Aron512_P	=0,
		E46_GanDLy1_0_P	=0,
		E47_GanDLy0_1_P	=0,
		E48_IlimTc_0_P	=0,
		E49_IlimTc_1_P	=0,
		E50_IlimTc_2_P	=0,
		E51_IlimTc_3_P	=0,
		E52_SDTemp_0_P	=0,
		E53_SDTemp_1_P	=0,
		E54_DOPL_P	=0,
		E55_DisIL_Cap_P	=0,
		E56_ILIMP_P	=0,
		E57_uVADC_0_P	=0,
		E58_uVADC_1_P	=0,
		E59_uVADC_2_P	=0,
		E60_uVADC_3_P	=0,
		E61_StrTTFB_0_P	=0,
		E62_StrTTFB_1_P	=0,
		E63_StrTTFB_2_P	=0,
		E64_EndTTFB_0_P	=0,
		E65_EndTTFB_1_P	=0,
		E66_EndTTFB_2_P	=0,
		E67_TsADC_0_P	=0,
		E68_TsADC_1_P	=0,
		E69_TsADC_2_P	=0,
		E70_TsADC_3_P	=0,
		E71_UV10pct_P	=0,
		E72_IOV_0_P	=0,
		E73_IOV_1_P	=0,
		E74_IOV_2_P	=0,
		E75_IOV_3_P	=0,
		E76_IOV_4_P	=0,
		E77_TonM_0_P	=0,
		E78_TonM_1_P	=0,
		E79_TonM_2_P	=0,
		E0_Si_ID_0_S	=0,
		E1_Si_ID_1_S	=0,
		E2_Si_ID_2_S	=0,
		E3_Si_ID_3_S	=0,
		E4_Si_ID_4_S	=0,
		E5_Si_ID_5_S	=0,
		E6_Si_ID_6_S	=0,
		E7_Si_ID_7_S	=0,
		E8_tsstart_0_S	=0,
		E9_tsstart_1_S	=0,
		E10_tfbOpt_0_S	=0,
		E11_tfbOpt_1_S	=0,
		E12_tfb_0_S	=0,
		E13_tfb_1_S	=0,
		E14_tfb_2_S	=0,
		E15_DOPL_S	=0,
		E16_TvrOpt_0_S	=0,
		E17_TvrOpt_1_S	=0,
		E18_TenCP_S	=0,
		E19_ZffOpt_0_S	=0,
		E20_ZffOpt_1_S	=0,
		E21_ZDJitDim_S	=0,
		E22_JittOff_S	=0,
		E23_Tcp_0_S	=0,
		E24_Tcp_1_S	=0,
		E25_Tcp_2_S	=0,
		E26_Tcp_3_S	=0,
		E27_ZTM5VL_0_S	=0,
		E28_ZTM5VL_1_S	=0,
		E29_ZTMBStr_0_S	=0,
		E30_ZTMBStr_1_S	=0,
		E31_DsblFlBck_S	=0,
		E32_Zoffset_0_S	=0,
		E33_Zoffset_1_S	=0,
		E34_Zoffset_2_S	=0,
		E35_Icc_0_S	=0,
		E36_Icc_1_S	=0,
		E37_Icc_2_S	=0,
		E38_Zvref_0_S	=0,
		E39_Zvref_1_S	=0,
		E40_Zvref_2_S	=0,
		E41_Zvref_3_S	=0,
		E42_BILIM_0_S	=0,
		E43_BILIM_1_S	=0,
		E44_BILIM_2_S	=0,
		E45_BILIM_3_S	=0,
		E46_BILIM_4_S	=0,
		E47_Dimth_S	=0,
		E48_ZTMFS_0_S	=0,
		E49_ZTMFS_1_S	=0,
		E50_ZTMFS_2_S	=0,
		E51_ZTMFS_3_S	=0,
		E52_DacTr_0_S	=0,
		E53_DacTr_1_S	=0,
		E54_DacTr_2_S	=0,
		E55_DacTr_3_S	=0,
		E56_DacTr_4_S	=0,
		E57_Zttimer_0_S	=0,
		E58_Zttimer_1_S	=0,
		E59_Zttimer_2_S	=0,
		E60_Zttimer_3_S	=0,
		E61_HrtBTOpt_S	=0,
		E62_EnCP_S	=0,
		E63_50KhzStr_S	=0,
		E64_VCO_0_S	=0,
		E65_VCO_1_S	=0,
		E66_VCO_2_S	=0,
		E67_VCO_3_S	=0,
		E68_VCO_4_S	=0,
		E69_VCO_5_S	=0,
		E70_B_0_S	=0,
		E71_B_1_S	=0,
		E72_B_2_S	=0,
		E73_B_3_S	=0,
		E74_FlBckCC_S	=0,
		E75_FlBckSel_S	=0,
		E76_ZTLnt_0_S	=0,
		E77_ZTLnt_1_S	=0,
		E78_ZTLnt_2_S	=0,
		E79_ZTLnt_3_S	=0,
		EEPROM_Erase	=0;
			
	float	EEPROM_pre_TT	=0;

	int i = 0;
	int start_datalog_S = A_E0_Si_ID_0_S;
	int EEpr_S[80] = {0};

//g_Debug = 1;
// Skip Test if AbortTest set 
	if (AbortTest)
		return;

		//-----------------------------------------------------------------------------------------------------------------
		//Primary Die ID Reading
		//------------------------------------------------------------------------------------------------------------------
		//Test conditions:  D = 0, BPP = 5V, wait 150us.  Reading I2C.

		//Drain = 0V
		D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); // DVI_11_0
		//BPP = 0V
		BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
		BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1

		////////////////////////////////////////////////////////////////////////////////////////////////
		//This section is for the primary I2C

		//TS = 0V via pullup resistor. Ready for I2C.
		TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
		TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
		//UV = 0V via pullup resistor. Ready for I2C.
		UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
		UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
		//Connect Pullup R to TS and UV pins
		mux_20->close_relay(MUX_3_2);	//Connect Pullup R to TS pin.
		mux_20->close_relay(MUX_1_3);	//Connect Pullup R to UV pin.
		//Connect DSM CLK & Data to primary pins: TS & UV
		mux_14->close_relay(MUX_1_1);
		mux_14->close_relay(MUX_1_3);
		mux_14->open_relay(MUX_1_2);
		mux_14->open_relay(MUX_1_4);
		delay(5);
		////////////////////////////////////////////////////////////////////////////////////////////////////////

	float vpullup_P=3.3;	//5.0V does not work

	PowerUp_I2C_P();
	EEPROM_Read_Enable_P();

	//Read data out from EEPROM registers 0xC0
	g_Pre_E0_data_P = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
	g_Pre_E2_data_P = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
	g_Pre_E4_data_P = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
	g_Pre_E6_data_P = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
	g_Pre_E8_data_P = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

	//E0 to E8 bank registers decoding bit by bit for both Primary and Secondary
	E00_Si_ID_0_P	=	(g_Pre_E0_data_P	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E01_Si_ID_1_P	=	(g_Pre_E0_data_P	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E02_Si_ID_2_P	=	(g_Pre_E0_data_P	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E03_Si_ID_3_P	=	(g_Pre_E0_data_P	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E04_Si_ID_4_P	=	(g_Pre_E0_data_P	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E05_Si_ID_5_P	=	(g_Pre_E0_data_P	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E06_Si_ID_6_P	=	(g_Pre_E0_data_P	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E07_Si_ID_7_P	=	(g_Pre_E0_data_P	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E08_fOSC_0_P	=	(g_Pre_E0_data_P	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E09_fOSC_1_P	=	(g_Pre_E0_data_P	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E10_fOSC_2_P	=	(g_Pre_E0_data_P	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E11_fOSC_3_P	=	(g_Pre_E0_data_P	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E12_yInter_0_P	=	(g_Pre_E0_data_P	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E13_yInter_1_P	=	(g_Pre_E0_data_P	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E14_yInter_2_P	=	(g_Pre_E0_data_P	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E15_yInter_3_P	=	(g_Pre_E0_data_P	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E16_ILIM_0_P	=	(g_Pre_E2_data_P	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E17_ILIM_1_P	=	(g_Pre_E2_data_P	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E18_ILIM_2_P	=	(g_Pre_E2_data_P	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E19_ILIM_3_P	=	(g_Pre_E2_data_P	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E20_ILIM_4_P	=	(g_Pre_E2_data_P	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E21_ArSkip_P	=	(g_Pre_E2_data_P	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E22_ArOnT_P		=	(g_Pre_E2_data_P	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E23_ArOffT_0_P	=	(g_Pre_E2_data_P	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E24_ArOffT_1_P	=	(g_Pre_E2_data_P	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E25_StrtFREQ_P	=	(g_Pre_E2_data_P	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E26_OnTSL_0_P	=	(g_Pre_E2_data_P	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E27_OnTSL_1_P	=	(g_Pre_E2_data_P	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E28_ONTSL_2_P	=	(g_Pre_E2_data_P	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E29_ONTSL_3_P	=	(g_Pre_E2_data_P	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E30_ONTSL_4_P	=	(g_Pre_E2_data_P	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E31_ShunEn_P	=	(g_Pre_E2_data_P	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E32_RcvTH_0_P	=	(g_Pre_E4_data_P	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E33_RcvTH_1_P	=	(g_Pre_E4_data_P	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E34_RcvTH_2_P	=	(g_Pre_E4_data_P	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E35_GanMode_P	=	(g_Pre_E4_data_P	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E36_VxTrim_0_P	=	(g_Pre_E4_data_P	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E37_VxTrim_1_P	=	(g_Pre_E4_data_P	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E38_VxTrim_2_P	=	(g_Pre_E4_data_P	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E39_VxTrim_3_P	=	(g_Pre_E4_data_P	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E40_VxTrim_4_P	=	(g_Pre_E4_data_P	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E41_DrSize_0_P	=	(g_Pre_E4_data_P	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E42_DrSize_1_P	=	(g_Pre_E4_data_P	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E43_DrSize_2_P	=	(g_Pre_E4_data_P	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E44_DrSize_3_P	=	(g_Pre_E4_data_P	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E45_Aron512_P	=	(g_Pre_E4_data_P	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E46_GanDLy1_0_P	=	(g_Pre_E4_data_P	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E47_GanDLy0_1_P	=	(g_Pre_E4_data_P	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E48_IlimTc_0_P	=	(g_Pre_E6_data_P	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E49_IlimTc_1_P	=	(g_Pre_E6_data_P	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E50_IlimTc_2_P	=	(g_Pre_E6_data_P	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E51_IlimTc_3_P	=	(g_Pre_E6_data_P	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E52_SDTemp_0_P	=	(g_Pre_E6_data_P	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E53_SDTemp_1_P	=	(g_Pre_E6_data_P	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E54_DOPL_P		=	(g_Pre_E6_data_P	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E55_DisIL_Cap_P	=	(g_Pre_E6_data_P	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E56_ILIMP_P		=	(g_Pre_E6_data_P	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E57_uVADC_0_P	=	(g_Pre_E6_data_P	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E58_uVADC_1_P	=	(g_Pre_E6_data_P	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E59_uVADC_2_P	=	(g_Pre_E6_data_P	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E60_uVADC_3_P	=	(g_Pre_E6_data_P	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E61_StrTTFB_0_P	=	(g_Pre_E6_data_P	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E62_StrTTFB_1_P	=	(g_Pre_E6_data_P	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E63_StrTTFB_2_P	=	(g_Pre_E6_data_P	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E64_EndTTFB_0_P	=	(g_Pre_E8_data_P	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E65_EndTTFB_1_P	=	(g_Pre_E8_data_P	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E66_EndTTFB_2_P	=	(g_Pre_E8_data_P	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E67_TsADC_0_P	=	(g_Pre_E8_data_P	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E68_TsADC_1_P	=	(g_Pre_E8_data_P	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E69_TsADC_2_P	=	(g_Pre_E8_data_P	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E70_TsADC_3_P	=	(g_Pre_E8_data_P	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E71_UV10pct_P	=	(g_Pre_E8_data_P	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E72_IOV_0_P		=	(g_Pre_E8_data_P	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E73_IOV_1_P		=	(g_Pre_E8_data_P	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E74_IOV_2_P		=	(g_Pre_E8_data_P	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E75_IOV_3_P		=	(g_Pre_E8_data_P	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E76_IOV_4_P		=	(g_Pre_E8_data_P	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E77_TonM_0_P	=	(g_Pre_E8_data_P	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E78_TonM_1_P	=	(g_Pre_E8_data_P	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E79_TonM_2_P	=	(g_Pre_E8_data_P	&	0x8000	)	/	32768	;	//1000 0000 0000 0000

	//Datalog Pre Trim register bits
	PiDatalog(func	,	A_E00_Si_ID_0_P	,	E00_Si_ID_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E01_Si_ID_1_P	,	E01_Si_ID_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E02_Si_ID_2_P	,	E02_Si_ID_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E03_Si_ID_3_P	,	E03_Si_ID_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E04_Si_ID_4_P	,	E04_Si_ID_4_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E05_Si_ID_5_P	,	E05_Si_ID_5_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E06_Si_ID_6_P	,	E06_Si_ID_6_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E07_Si_ID_7_P	,	E07_Si_ID_7_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E08_fOSC_0_P	,	E08_fOSC_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E09_fOSC_1_P	,	E09_fOSC_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E10_fOSC_2_P	,	E10_fOSC_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E11_fOSC_3_P	,	E11_fOSC_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E12_yInter_0_P	,	E12_yInter_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E13_yInter_1_P	,	E13_yInter_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E14_yInter_2_P	,	E14_yInter_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E15_yInter_3_P	,	E15_yInter_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E16_ILIM_0_P	,	E16_ILIM_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E17_ILIM_1_P	,	E17_ILIM_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E18_ILIM_2_P	,	E18_ILIM_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E19_ILIM_3_P	,	E19_ILIM_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E20_ILIM_4_P	,	E20_ILIM_4_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E21_ArSkip_P	,	E21_ArSkip_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E22_ArOnT_P	,	E22_ArOnT_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E23_ArOffT_0_P	,	E23_ArOffT_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E24_ArOffT_1_P	,	E24_ArOffT_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E25_StrtFREQ_P	,	E25_StrtFREQ_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E26_OnTSL_0_P	,	E26_OnTSL_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E27_OnTSL_1_P	,	E27_OnTSL_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E28_ONTSL_2_P	,	E28_ONTSL_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E29_ONTSL_3_P	,	E29_ONTSL_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E30_ONTSL_4_P	,	E30_ONTSL_4_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E31_ShunEn_P	,	E31_ShunEn_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E32_RcvTH_0_P	,	E32_RcvTH_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E33_RcvTH_1_P	,	E33_RcvTH_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E34_RcvTH_2_P	,	E34_RcvTH_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E35_GanMode_P	,	E35_GanMode_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E36_VxTrim_0_P	,	E36_VxTrim_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E37_VxTrim_1_P	,	E37_VxTrim_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E38_VxTrim_2_P	,	E38_VxTrim_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E39_VxTrim_3_P	,	E39_VxTrim_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E40_VxTrim_4_P	,	E40_VxTrim_4_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E41_DrSize_0_P	,	E41_DrSize_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E42_DrSize_1_P	,	E42_DrSize_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E43_DrSize_2_P	,	E43_DrSize_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E44_DrSize_3_P	,	E44_DrSize_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E45_Aron512_P	,	E45_Aron512_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E46_GanDLy1_0_P	,	E46_GanDLy1_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E47_GanDLy0_1_P	,	E47_GanDLy0_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E48_IlimTc_0_P	,	E48_IlimTc_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E49_IlimTc_1_P	,	E49_IlimTc_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E50_IlimTc_2_P	,	E50_IlimTc_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E51_IlimTc_3_P	,	E51_IlimTc_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E52_SDTemp_0_P	,	E52_SDTemp_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E53_SDTemp_1_P	,	E53_SDTemp_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E54_DOPL_P	,	E54_DOPL_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E55_DisIL_Cap_P	,	E55_DisIL_Cap_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E56_ILIMP_P	,	E56_ILIMP_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E57_uVADC_0_P	,	E57_uVADC_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E58_uVADC_1_P	,	E58_uVADC_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E59_uVADC_2_P	,	E59_uVADC_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E60_uVADC_3_P	,	E60_uVADC_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E61_StrTTFB_0_P	,	E61_StrTTFB_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E62_StrTTFB_1_P	,	E62_StrTTFB_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E63_StrTTFB_2_P	,	E63_StrTTFB_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E64_EndTTFB_0_P	,	E64_EndTTFB_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E65_EndTTFB_1_P	,	E65_EndTTFB_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E66_EndTTFB_2_P	,	E66_EndTTFB_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E67_TsADC_0_P	,	E67_TsADC_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E68_TsADC_1_P	,	E68_TsADC_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E69_TsADC_2_P	,	E69_TsADC_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E70_TsADC_3_P	,	E70_TsADC_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E71_UV10pct_P	,	E71_UV10pct_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E72_IOV_0_P	,	E72_IOV_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E73_IOV_1_P	,	E73_IOV_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E74_IOV_2_P	,	E74_IOV_2_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E75_IOV_3_P	,	E75_IOV_3_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E76_IOV_4_P	,	E76_IOV_4_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E77_TonM_0_P	,	E77_TonM_0_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E78_TonM_1_P	,	E78_TonM_1_P	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E79_TonM_2_P	,	E79_TonM_2_P	,	func_fail_bin	,	POWER_UNIT);


	//Power Down Primary
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	//Power down.

	//SDA = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

	//SCL = 3.3V via pullup resistor. Ready for I2C.
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	delay(2);
		        
	dvi_9->set_current(DVI_CHANNEL_1, 30e-3, RANGE_300_MA);
	dvi_9->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE); // DVI_11_1
	delay(10);

	mux_14->open_relay(MUX_1_2);
	mux_14->open_relay(MUX_1_4);
	delay(5);

	//Set pullup voltage at TS @ UV pins.
	TS_ovi3->set_current(TSovi3_ch, 0.01e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_current(UV_ch, 0.01e-3, RANGE_300_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(10);

	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
	wait.delay_10_us(100);

	//Disconnect Pullup R to TS pin.
	mux_20->open_relay(MUX_3_2);
	//Disconnect Pullup R to UV pin.
	mux_20->open_relay(MUX_1_3);

	//Disconnect DSM from Primary.
	mux_14->open_relay(MUX_1_1);	//Primary disconnect from DSM
	mux_14->open_relay(MUX_1_3);	//Primary disconnect from DSM
	delay(2);

	//Secondary I2C to ready Secondary Die ID.
	//Disconnect DVI_13 from HBP.
	dvi_13->disconnect(CONN_FORCE0);
	delay(5);

	//SDA & SCL set to 0V
	//SDA = 0V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_current(SDA_ch, 10e-3, RANGE_30_MA);
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

	//SCL = 0V via pullup resistor. Ready for I2C.
	SCL_ovi3->set_current(SCL_ch, 10e-3, RANGE_30_MA);
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1

	//----------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	PowerUp_I2C_S();
	
	//Sometimes, DSM I2C can't be written correctly the first time.
	//Change the DSM timeout to 1ms since the default timeout is approximately 35ms.
	//g_Debug = 1;
	//DSM_set_I2C_timeout(0, 5);
	//DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//Enter test mode
	Analog_TM_Enable_Secondary();
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	DSM_I2C_SREG0_0x7070();			//Get ready for any data to move to read address 0x00

	//Read data out from EEPROM registers 0xC0
	g_Pre_E0_data_S = DSM_I2C_Read(g_EEP_R_C0); //Read data of RegAddr 0xE0 from 0xC0 RegAddr from READ_ADDR 0x00
	g_Pre_E2_data_S = DSM_I2C_Read(g_EEP_R_C2); //Read data of RegAddr 0xE2 from 0xC2 RegAddr from READ_ADDR 0x00
	g_Pre_E4_data_S = DSM_I2C_Read(g_EEP_R_C4); //Read data of RegAddr 0xE4 from 0xC4 RegAddr from READ_ADDR 0x00
	g_Pre_E6_data_S = DSM_I2C_Read(g_EEP_R_C6); //Read data of RegAddr 0xE6 from 0xC6 RegAddr from READ_ADDR 0x00
	g_Pre_E8_data_S = DSM_I2C_Read(g_EEP_R_C8); //Read data of RegAddr 0xE8 from 0xC8 RegAddr from READ_ADDR 0x00

		
	//Decode data from 0xCX and assign to EEpromArray for datalogging.
	EEprcode_2_EEprArray(g_Pre_E0_data_S, EEpr_S, 0);
	EEprcode_2_EEprArray(g_Pre_E2_data_S, EEpr_S, 16);
	EEprcode_2_EEprArray(g_Pre_E4_data_S, EEpr_S, 32);
	EEprcode_2_EEprArray(g_Pre_E6_data_S, EEpr_S, 48);
	EEprcode_2_EEprArray(g_Pre_E8_data_S, EEpr_S, 64);

	//EEpr_Bank_S[E0] = EEpr_Bank_S[E0] | g_Pre_E0_data_S;
	//EEpr_Bank_S[E2] = EEpr_Bank_S[E2] | g_Pre_E2_data_S;
	//EEpr_Bank_S[E4] = EEpr_Bank_S[E4] | g_Pre_E4_data_S;
	//EEpr_Bank_S[E6] = EEpr_Bank_S[E6] | g_Pre_E6_data_S;
	//EEpr_Bank_S[E8] = EEpr_Bank_S[E8] | g_Pre_E8_data_S;

	EEpr_Bank_S[E0] = EEpr_Bank_S[E0] | g_Pre_E0_data_S;
	EEpr_Bank_S[E2] = EEpr_Bank_S[E2] | g_Pre_E2_data_S;
	EEpr_Bank_S[E4] = EEpr_Bank_S[E4] | g_Pre_E4_data_S;
	EEpr_Bank_S[E6] = EEpr_Bank_S[E6] | g_Pre_E6_data_S;
	EEpr_Bank_S[E8] = EEpr_Bank_S[E8] | g_Pre_E8_data_S;

	//Power down secondary from here.
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);

	//Not sure why there is a glitch on FW when powering down.
	FW_ovi3->set_voltage(FW_ch, 0.5, VOLT_5_RANGE); 

	//Powerdown Secondary.
	VR_dvi->set_voltage(VR_ch, 5.0, VOLT_50_RANGE); 
	wait.delay_10_us(50);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);
	SDA_ovi3->set_current(SDA_ch, 0.01e-3, RANGE_30_MA);	
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_5_RANGE);
	SCL_ovi3->set_current(SCL_ch, 0.01e-3, RANGE_30_MA);	
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_5_RANGE); 
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);

	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_50_RANGE); 
	wait.delay_10_us(100);

	//Open relays.
	//Disonnect Pullup R from TS and UV pins
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	//Disonnect Pullup R to SCL & SDA
	Open_relay(K1_SDA_SPI_TB);
	Open_relay(K1_SCL_SPI_TB);
	//Disconnect DSM CLK & Data from primary pins: TS & UV
	//Connect DSM CLK & Data to secondary:         SCL & SDA
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	wait.delay_10_us(250);

	
	for(i=0;i<80;i++)
	{
		PiDatalog(func, start_datalog_S+i, EEpr_S[i], func_fail_bin, POWER_UNIT);
	}
/*

	E0_Si_ID_0_S	=	(E0_data_S	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E1_Si_ID_1_S	=	(E0_data_S	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E2_Si_ID_2_S	=	(E0_data_S	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E3_Si_ID_3_S	=	(E0_data_S	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E4_Si_ID_4_S	=	(E0_data_S	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E5_Si_ID_5_S	=	(E0_data_S	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E6_Si_ID_6_S	=	(E0_data_S	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E7_Si_ID_7_S	=	(E0_data_S	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E8_tsstart_0_S	=	(E0_data_S	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E9_tsstart_1_S	=	(E0_data_S	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E10_tfbOpt_0_S	=	(E0_data_S	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E11_tfbOpt_1_S	=	(E0_data_S	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E12_tfb_0_S		=	(E0_data_S	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E13_tfb_1_S		=	(E0_data_S	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E14_tfb_2_S		=	(E0_data_S	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E15_DOPL_S		=	(E0_data_S	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E16_TvrOpt_0_S	=	(E2_data_S	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E17_TvrOpt_1_S	=	(E2_data_S	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E18_TenCP_S		=	(E2_data_S	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E19_ZffOpt_0_S	=	(E2_data_S	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E20_ZffOpt_1_S	=	(E2_data_S	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E21_ZDJitDim_S	=	(E2_data_S	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E22_JittOff_S	=	(E2_data_S	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E23_Tcp_0_S		=	(E2_data_S	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E24_Tcp_1_S		=	(E2_data_S	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E25_Tcp_2_S		=	(E2_data_S	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E26_Tcp_3_S		=	(E2_data_S	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E27_ZTM5VL_0_S	=	(E2_data_S	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E28_ZTM5VL_1_S	=	(E2_data_S	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E29_ZTMBStr_0_S	=	(E2_data_S	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E30_ZTMBStr_1_S	=	(E2_data_S	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E31_DsblFlBck_S	=	(E2_data_S	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E32_Zoffset_0_S	=	(E4_data_S	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E33_Zoffset_1_S	=	(E4_data_S	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E34_Zoffset_2_S	=	(E4_data_S	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E35_Icc_0_S		=	(E4_data_S	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E36_Icc_1_S		=	(E4_data_S	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E37_Icc_2_S		=	(E4_data_S	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E38_Zvref_0_S	=	(E4_data_S	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E39_Zvref_1_S	=	(E4_data_S	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E40_Zvref_2_S	=	(E4_data_S	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E41_Zvref_3_S	=	(E4_data_S	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E42_BILIM_0_S	=	(E4_data_S	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E43_BILIM_1_S	=	(E4_data_S	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E44_BILIM_2_S	=	(E4_data_S	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E45_BILIM_3_S	=	(E4_data_S	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E46_BILIM_4_S	=	(E4_data_S	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E47_Dimth_S		=	(E4_data_S	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E48_ZTMFS_0_S	=	(E6_data_S	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E49_ZTMFS_1_S	=	(E6_data_S	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E50_ZTMFS_2_S	=	(E6_data_S	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E51_ZTMFS_3_S	=	(E6_data_S	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E52_DacTr_0_S	=	(E6_data_S	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E53_DacTr_1_S	=	(E6_data_S	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E54_DacTr_2_S	=	(E6_data_S	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E55_DacTr_3_S	=	(E6_data_S	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E56_DacTr_4_S	=	(E6_data_S	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E57_Zttimer_0_S	=	(E6_data_S	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E58_Zttimer_1_S	=	(E6_data_S	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E59_Zttimer_2_S	=	(E6_data_S	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E60_Zttimer_3_S	=	(E6_data_S	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E61_HrtBTOpt_S	=	(E6_data_S	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E62_EnCP_S		=	(E6_data_S	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E63_50KhzStr_S	=	(E6_data_S	&	0x8000	)	/	32768	;	//1000 0000 0000 0000
	E64_VCO_0_S		=	(E8_data_S	&	0x0001	)	/	1	;	//0000 0000 0000 0001
	E65_VCO_1_S		=	(E8_data_S	&	0x0002	)	/	2	;	//0000 0000 0000 0010
	E66_VCO_2_S		=	(E8_data_S	&	0x0004	)	/	4	;	//0000 0000 0000 0100
	E67_VCO_3_S		=	(E8_data_S	&	0x0008	)	/	8	;	//0000 0000 0000 1000
	E68_VCO_4_S		=	(E8_data_S	&	0x0010	)	/	16	;	//0000 0000 0001 0000
	E69_VCO_5_S		=	(E8_data_S	&	0x0020	)	/	32	;	//0000 0000 0010 0000
	E70_B_0_S		=	(E8_data_S	&	0x0040	)	/	64	;	//0000 0000 0100 0000
	E71_B_1_S		=	(E8_data_S	&	0x0080	)	/	128	;	//0000 0000 1000 0000
	E72_B_2_S		=	(E8_data_S	&	0x0100	)	/	256	;	//0000 0001 0000 0000
	E73_B_3_S		=	(E8_data_S	&	0x0200	)	/	512	;	//0000 0010 0000 0000
	E74_FlBckCC_S	=	(E8_data_S	&	0x0400	)	/	1024	;	//0000 0100 0000 0000
	E75_FlBckSel_S	=	(E8_data_S	&	0x0800	)	/	2048	;	//0000 1000 0000 0000
	E76_ZTLnt_0_S	=	(E8_data_S	&	0x1000	)	/	4096	;	//0001 0000 0000 0000
	E77_ZTLnt_1_S	=	(E8_data_S	&	0x2000	)	/	8192	;	//0010 0000 0000 0000
	E78_ZTLnt_2_S	=	(E8_data_S	&	0x4000	)	/	16384	;	//0100 0000 0000 0000
	E79_ZTLnt_3_S	=	(E8_data_S	&	0x8000	)	/	32768	;	//1000 0000 0000 0000


	PiDatalog(func	,	A_E0_Si_ID_0_S	,	E0_Si_ID_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E1_Si_ID_1_S	,	E1_Si_ID_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E2_Si_ID_2_S	,	E2_Si_ID_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E3_Si_ID_3_S	,	E3_Si_ID_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E4_Si_ID_4_S	,	E4_Si_ID_4_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E5_Si_ID_5_S	,	E5_Si_ID_5_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E6_Si_ID_6_S	,	E6_Si_ID_6_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E7_Si_ID_7_S	,	E7_Si_ID_7_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E8_tsstart_0_S	,	E8_tsstart_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E9_tsstart_1_S	,	E9_tsstart_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E10_tfbOpt_0_S	,	E10_tfbOpt_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E11_tfbOpt_1_S	,	E11_tfbOpt_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E12_tfb_0_S	,	E12_tfb_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E13_tfb_1_S	,	E13_tfb_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E14_tfb_2_S	,	E14_tfb_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E15_DOPL_S	,	E15_DOPL_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E16_TvrOpt_0_S	,	E16_TvrOpt_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E17_TvrOpt_1_S	,	E17_TvrOpt_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E18_TenCP_S	,	E18_TenCP_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E19_ZffOpt_0_S	,	E19_ZffOpt_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E20_ZffOpt_1_S	,	E20_ZffOpt_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E21_ZDJitDim_S	,	E21_ZDJitDim_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E22_JittOff_S	,	E22_JittOff_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E23_Tcp_0_S	,	E23_Tcp_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E24_Tcp_1_S	,	E24_Tcp_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E25_Tcp_2_S	,	E25_Tcp_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E26_Tcp_3_S	,	E26_Tcp_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E27_ZTM5VL_0_S	,	E27_ZTM5VL_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E28_ZTM5VL_1_S	,	E28_ZTM5VL_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E29_ZTMBStr_0_S	,	E29_ZTMBStr_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E30_ZTMBStr_1_S	,	E30_ZTMBStr_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E31_DsblFlBck_S	,	E31_DsblFlBck_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E32_Zoffset_0_S	,	E32_Zoffset_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E33_Zoffset_1_S	,	E33_Zoffset_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E34_Zoffset_2_S	,	E34_Zoffset_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E35_Icc_0_S	,	E35_Icc_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E36_Icc_1_S	,	E36_Icc_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E37_Icc_2_S	,	E37_Icc_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E38_Zvref_0_S	,	E38_Zvref_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E39_Zvref_1_S	,	E39_Zvref_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E40_Zvref_2_S	,	E40_Zvref_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E41_Zvref_3_S	,	E41_Zvref_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E42_BILIM_0_S	,	E42_BILIM_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E43_BILIM_1_S	,	E43_BILIM_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E44_BILIM_2_S	,	E44_BILIM_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E45_BILIM_3_S	,	E45_BILIM_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E46_BILIM_4_S	,	E46_BILIM_4_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E47_Dimth_S	,	E47_Dimth_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E48_ZTMFS_0_S	,	E48_ZTMFS_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E49_ZTMFS_1_S	,	E49_ZTMFS_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E50_ZTMFS_2_S	,	E50_ZTMFS_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E51_ZTMFS_3_S	,	E51_ZTMFS_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E52_DacTr_0_S	,	E52_DacTr_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E53_DacTr_1_S	,	E53_DacTr_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E54_DacTr_2_S	,	E54_DacTr_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E55_DacTr_3_S	,	E55_DacTr_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E56_DacTr_4_S	,	E56_DacTr_4_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E57_Zttimer_0_S	,	E57_Zttimer_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E58_Zttimer_1_S	,	E58_Zttimer_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E59_Zttimer_2_S	,	E59_Zttimer_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E60_Zttimer_3_S	,	E60_Zttimer_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E61_HrtBTOpt_S	,	E61_HrtBTOpt_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E62_EnCP_S	,	E62_EnCP_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E63_50KhzStr_S	,	E63_50KhzStr_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E64_VCO_0_S	,	E64_VCO_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E65_VCO_1_S	,	E65_VCO_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E66_VCO_2_S	,	E66_VCO_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E67_VCO_3_S	,	E67_VCO_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E68_VCO_4_S	,	E68_VCO_4_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E69_VCO_5_S	,	E69_VCO_5_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E70_B_0_S	,	E70_B_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E71_B_1_S	,	E71_B_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E72_B_2_S	,	E72_B_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E73_B_3_S	,	E73_B_3_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E74_FlBckCC_S	,	E74_FlBckCC_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E75_FlBckSel_S	,	E75_FlBckSel_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E76_ZTLnt_0_S	,	E76_ZTLnt_0_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E77_ZTLnt_1_S	,	E77_ZTLnt_1_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E78_ZTLnt_2_S	,	E78_ZTLnt_2_S	,	func_fail_bin	,	POWER_UNIT);
	PiDatalog(func	,	A_E79_ZTLnt_3_S	,	E79_ZTLnt_3_S	,	func_fail_bin	,	POWER_UNIT);
*/
//g_Debug = 0;

}
