/************************************************************************************																					*
 *			POWER INTEGRATION BINNO/LYT8 FAMILY TEST PROGRAM HISTORY				*													 
 ************************************************************************************
10/12/18 HL v0.0010  - Initial development.
10/18/18 HL v0.0011  - Resource mapping. Done.
10/19/18 HL v0.0012  - Mapping relay- ongoing.
12/13/18 HL v0.0013  - Added ESD tests for Drain, BPP, HBP (datalogged as VO) and FB (datalogged as COMP)until datalog is updated.
12/17/18 HL v0.0013  - Added ESD tests for UV & TS (datalogged as SR)
01/03/19 CX v0.0014  - Update I2C coding for Primary Trimming and Read Back Trim Data in Continuity function.
01/04/19 CX v0.0015  - Added I2C coding for Secondary EEprom Erase in continuity function.  Not working yet.
01/07/19 CX v0.0016  - Update 2ndary Trim/Burn/Readback coding in continuity function.  Verified working.                       
01/07/19 HL v0.0017  - Added I2C Write/Read functions.
01/09/19 CX v0.0018  - Add coding for Primary EEprom ERASE,BURN,READ_What's_Burn  
01/10/19 HL v0.0019  - Fixed primary trimming issue.  Added functions to write & read for primary.  Will need to verify if these functions work for 2ndary.
01/10/19 HL v0.0020  - Adjusted test program for blind-trim Primary & Secondary per Design request.  
					 - Primary I2C reading based on address 0x1c, 0x1c and 0x1d wil need only 2 bytes.
					   However, these functions won't work on secondary.  If using same function for both primary & secondary, number byte = 3.
					   Not a concern since the extra bytes are the repeat of the lower & high bytes.
					   Adjusted function name from DSM_I2C_Write2() to DSM_I2C_Write()
01/16/19 HL v0.0021    Added Cont tests.  IcontB & IcontHSG not working yet.  Possible HW modification required.
01/17/19 HL v0.0022    Fixed IcontHSG: Required TB modification.  Short LNK45 to LNK46 (OVI side). This is to short F & S to 
                       ensure OVI_3_0 can be at GND.
					   Fixed IcontB:  This is due to soldering issue.
01/17/19 HL v0.0023	   Added Pri & Sec GNDres tests.
01/18/19 HL v0.0024    Added BPP Cap Check.
01/18/19 HL v0.0025    Added Leakage tests for Primary.
01/19/19 HL v0.0026    Added various function checks to Leakage Function in Create.
01/20/19 HL v0.0027    Added IS leakage tests of the 2ndary.  More leakage tests to come.
01/21/19 CX v0.0028  - Added Hardware_Check_Binno() function for MUX20.  TS_COMP_IB is not in place so MUX_3_4 could not be verified.
						Need to add printf or pop-up for the mux failures.
01/22/19 HL v0.0029  - Added various leakage tests for secondary except VR.  VR still required some debugging.
01/23/19 HL v0.0030  - New test conditions from design to measure 2ndary leakage thru i2c mode.  VR implementation pending.
01/25/19 HL v0.0031  - Fixed IIH_SCL, IIL_SCL & IIH_HSG high leakage issue & added VR leakage tests.
01/25/19 HL v0.0032  - Deglitched and changed test name per design's request.
01/28/19 HL v0.0033  - Released as Continuity & Leakage for REL with other functions removed to avoid confusion.
01/28/19 HL v0.0034  - Worked on secondary tests.
01/30/19 HL v0.0035  - Worked on CV test.
02/01/19 HL v0.0036  - Added CV, VcvPassFETOff, VcvBOff, Bin2Dec to CV_Pre function.
02/01/19 HL v0.0036  - Added VDDA_S trim function.
02/01/19 HL v0.0037  - Finished VDDA_S trim function.
02/03/19 HL v0.0038  - Added IRSET Trim test.  
02/05/19 HL v0.0039  - Added VADC_Pre_S
02/05/19 HL v0.0040  - Merged with Charles' new test program.
02/05/19 HL v0.0041  - Added CLK1M_Pre test
02/06/19 HL v0.0042  - Load previous trimming bit into EEprom prior to measuring pretrim values. 
02/06/19 HL v0.0043  - Fixed CCOffset trimming & Update EEpromID function.
02/08/19 CX v0.0043cx - Added functions "EEPROM_ERASE_P", "EEPROM_BURN_P", "EEPROM_Write_Enable_P", 
						"EEPROM_Read_Enable_P"
					  - Added coding for Primary in function EEprom_DevID function.
02/08/19 HL v0.0044  - Fixed ZTtimer measuring problem. 
02/10/19 HL v0.0045  - Added function VccRef_S.
02/11/19 CX v0.0043cxA- Remark unrelated coding from InnoVI
02/13/19 CX v0.0043cxB- Added iOVp coding
02/22/19 CX v0.0043cxC- Added Fosc_P, TonMin_P, TonMin_Slope_P functions and coding
02/26/19 CX v0.0046cxD- Finish TonMin_P and TonMin_Slope_P and Offset_P
03/01/19 CX v0.0046cxE- Finish iUV_P.
03/14/19 CX v0.46cxF  - Finish ILIM_Pre, Working on NTC_Pre
03/14/19 CX v0.46cxG  - NTC_Pre coding in progress
03/19/19 CX v0.46cxH  - Done with NTC_Pre coding.  WIP for trimming
03/20/19 CX v0.46cxI  - Update some simulation coding for NTC.  WIP
03/21/19 CX v0.46cxJ  - Add simulation coding for iOV, NTC.  Need to work on other Primary trim simulations.
03/28/19 CX v0.46cxK  - Add sim coding for all trim parameters and verified trimweight except iUVp
04/02/19 CX v0.46cxL  - added EEPROM_P_Burn function and merge EEPROM_Pre function. Work on postTrim funcs next

History Revisions (Above)
*/

//==============================================================================
// USER.CPP
//==============================================================================
// include this nafxcwd.lib in linker->input-> ignore specific library for linker problem
// after ATE Generate Source Code
#include "asl.h"
#include "USER.H"
#include "piclasses.h"
#include "piautocorr.h"
#include "PITrimOptions.h"
#include "userinfo.h"	// added for login. See "user_start_test"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <math.h>

// DSM MODULE CODE //
#define DSM_CONTEXT 0
#include <stdio.h>//For DSM
#include <string.h>//For DSM
#include "digital_scan_module.h"
// DSM MODULE CODE //

// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

ModalDialogDescription mdb;		// Create class object, allocate memory. 	Credence function

extern "C" __declspec(dllexport) void user_init (void);
extern "C" __declspec(dllexport) void user_load (void);
extern "C" __declspec(dllexport) void user_start_lot (void);
extern "C" __declspec(dllexport) void user_wait_sot (void);
extern "C" __declspec(dllexport) void user_start_test (void);
extern "C" __declspec(dllexport) void user_before_binning (void);
extern "C" __declspec(dllexport) void user_end_test (void);
extern "C" __declspec(dllexport) void user_next_device (void);
extern "C" __declspec(dllexport) void user_end_lot (void);
extern "C" __declspec(dllexport) void user_exit (void);
extern "C" __declspec(dllexport) void user_dut_power_off (void);
extern "C" __declspec(dllexport) void user_dut_power_on (void);
extern "C" __declspec(dllexport) void user_F12 (void);

#if defined(CSC_SITEBASE) && ((CSC_SITEBASE == 0) || (CSC_SITEBASE == 1))
const bool IsSiteSet = vISetSharedData::SetSiteBase(CSC_SITEBASE);  // This sets the systems Site Base
#elif defined(CSC_SITEBASE)
#error Invalid CSC_SITEBASE!
#endif

int g_pid = 0;  // Not really a global, but watch sheets need this exact name.

//{ASL_CREATE BEGIN BOARDS_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive the changes to this code.
Ovi * ovi_1;
Ovi * ovi_3;
Pv3 * pv3_4;
Tmu * tmu_6;
Ddd * ddd_7;
Dvi * dvi_9;
Dvi * dvi_11;
Dvi * dvi_13;
Mux * mux_14;
Hvs * hvs_15;
Mux * mux_20;
Dvi * dvi_21;
 
void board_ptr_init(void)
{
	ovi_1 = &ovi_cards[board_ptr[BOARD_1]];
	ovi_3 = &ovi_cards[board_ptr[BOARD_3]];
	pv3_4 = &pv3_cards[board_ptr[BOARD_4]];
	tmu_6 = &tmu_cards[board_ptr[BOARD_6]];
	ddd_7 = &ddd_cards[board_ptr[BOARD_7]];
	dvi_9 = &dvi_cards[board_ptr[BOARD_9]];
	dvi_11 = &dvi_cards[board_ptr[BOARD_11]];
	dvi_13 = &dvi_cards[board_ptr[BOARD_13]];
	mux_14 = &mux_cards[board_ptr[BOARD_14]];
	hvs_15 = &hvs_cards[board_ptr[BOARD_15]];
	mux_20 = &mux_cards[board_ptr[BOARD_20]];
	dvi_21 = &dvi_cards[board_ptr[BOARD_21]];
}
 
void board_hardware_init(void)
{
	ovi_1->init();
	ovi_3->init();
	pv3_4->init();
	tmu_6->init();
	ddd_7->init();
	dvi_9->init();
	dvi_11->init();
	dvi_13->init();
	mux_14->init();
	hvs_15->init();
	mux_20->init();
	dvi_21->init();
}
//ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}

// This file must be present even if no user code is placed below
// Below are a number of routines that are called by the main program at
// various times. If the user needs to initialize any variables, or check for
// any situations during these times he may "fill in the blanks".

// **************************************************************************


// Resource Mapping //
Dvi	*VR_dvi      = dvi_9;       //DVI_9_1
Dvi *D_dvi       = dvi_11;      //DVI_11_0
Dvi *BPP_dvi     = dvi_11;      //DVI_11_1
Dvi *HBP_dvi2k   = dvi_13;      //DVI_13_0
Dvi *IS_dvi2k    = dvi_13;      //DVI_13_1
Dvi *BPS_dvi     = dvi_21;      //DVI_21_0
Dvi *UV_dvi      = dvi_21;      //DVI_21_1

Ovi *HSG_ovi     = ovi_1;      //OVI_1_0
Ovi *BUFCLMP_ovi   = ovi_1;      //OVI_1_1
Ovi	*IS_ovi      = ovi_1;      //OVI_1_2,OVI_1_4
Ovi *NC_ovi      = ovi_1;      //OVI_1_3
Ovi	*TS_ovi      = ovi_1;	   //OVI_1_5
Ovi	*Site_ovi    = ovi_1;      //OVI_1_7
	
Ovi	*TS_ovi3     = ovi_3;	   //OVI_3_0
Ovi *B_ovi3      = ovi_3;      //OVI_3_1,OVI_3_2
Ovi	*SYNC_ovi3   = ovi_3;      //OVI_3_3
Ovi *FW_ovi3     = ovi_3;      //OVI_3_4
Ovi *SDA_ovi3    = ovi_3;      //OVI_3_5
Ovi *SCL_ovi3    = ovi_3;      //OVI_3_6
Ovi *FB_ovi3     = ovi_3;      //OVI_3_7


// Resource Mapping //
int	VR_ch      = 1;       //DVI_9_1.
int VRstep_ch = 0;        //DVI_9_0.
int	D_ch       = 0;       //DVI_11_0
int	BPP_ch     = 1;		  //DVI_11_1
int	HBP_ch     = 0;		  //DVI_13_0
int	IS_ch      = 1;       //DVI_13_1
int	BPS_ch     = 0;       //DVI_21_0
int	UV_ch      = 1;       //DVI_21_1

int	HSG_ch     = 0;        //OVI_1_0
int	BUFCLMP_ch = 1;        //OVI_1_1
int	IS_ch2     = 2;        //OVI_1_2
int IS_ch4     = 4;        //OVI_1_4
int	NC_ch      = 3;		   //OVI_1_3
int	TSovi1_ch  = 5;        //OVI_1_5
int TSovi3_ch  = 0;        //OVI_3_0
int	Site_ch    = 7;        //OVI_1_7
	
int	B_ch1      = 1;        //OVI_3_1
int B_ch2      = 2;        //OVI_3_2
int	SYNC_ch    = 3;        //OVI_3_3
int	FW_ch      = 4;        //OVI_3_4
int	SDA_ch     = 5;        //OVI_3_5
int	SCL_ch     = 6;        //OVI_3_6
int	FB_ch      = 7;        //OVI_3_7

/* ======================  Test Hardware ID Parameters  ============================*/
int	gLoadBoard_SubType;				// Loadboard type for hardware ID
int	gLoadBoardRev;
int	g_LB_rev_needed;
int	gInductor_SubType;				// Inductor type for hardware ID
int	gInductorRev;
int	gContactor_SubType;			// Contactor type for hardware ID
int	gContactorRev;
int g_CB_rev_needed;
//HL added.
int gTestBlock_SubType;
int gTestBlockRev;
int g_TB_rev_needed;
int g_Setup_OK = 0;  //HL added.

//HL---------------------------------------------------------------------------------
//Secondary Variables.
//-----------------------------------------------------------------------------------
float g_HBP_Pre_S = 0;

/* ======================  Trim Option Table variable  =============================*/
STRING Table_Rev_Trimops = 0;

/* ======================  Die Parameters  =========================================*/
//int  g_DevNum_Trimops	=0;
int		g_BV_Trimops									=0,
		g_FET_Size_Trimops								=0,
		gP_Reserved_Trimops								=0, //bit 0 to 7
		gP_Trim_AR_SKIP_time_Trimops					=0,	//bit 21
		gP_Trim_Disable_TON_foldback_Trimops			=0,	//bit 22
		gP_Trim_AR_OFF_TIME_Trimops						=0,	//bit 23,24
		gP_Trim_START_UP_FREQ_Trimops					=0, //bit 25
		gP_Trim_Enable_Shunt_during_Cap_Select_Trimops	=0, //bit31
		gP_Trim_RCV_threshold_Trimops					=0, //bit 32,33,34
		gP_Trim_GaN_Mode_Trimops						=0, //bit 35
		gP_Trim_Sense_Voltage_ILIM_Trimops				=0, //bit 36,37,38,39,40
		gP_Trim_Driver_Size_Trimops						=0, //bit 41,42,43,44
		gP_Trim_AR_ON_time_Trimops						=0, //bit 45
		gP_Trim_GaN_On_Delay_Trimops					=0, //bit 46,47
		gP_Trim_ILIMTC_Trimops							=0, //bit 48,49,50,51
		gP_Trim_Bandgap_TSD_Trimops						=0, //bit 52,53
		gP_Trim_DOPL_mode_Trimops						=0, //bit 54
		gP_Trim_Disable_ILIM_cap_Select_Trimops			=0, //bit 55
		gP_Trim_Set_ILIMP_Trimops						=0, //bit 56
		gP_Trim_Junction_Start_Temp_Trimops				=0, //bit 61,62,63
		gP_Trim_Junction_TSD_Trimops					=0, //bit 64,65,66
		gP_Trim_iUV_10pct_Trimops						=0; //bit 71

/* ======================  Test Flow Control Parameter  ============================*/
//int  g_First_Time_Run =1;
bool  g_Require_PartID = true;
int	  AbortTest =0; 
int	  g_Trim_Enable_P =0;
int   g_Trim_Enable_S = 0;
int	  g_Erase_Enable_P =0;
int   g_Erase_Enable_S = 0;
int   g_TstTime_Enble_P = 0;
char* g_Part_ID_Trimops;
char *PrgRev;
char *FamilyName;
int	 g_DevFamily_Trimops =0;
char g_OperCode[50] ={0};
char g_DevName[50]	={0};

char Part_ID_LimitSet[50] ={0};
int  g_OPCODE		= 0;
int  g_OPCODE_RTR	= 0;
int  g_Rel_Enable_P = 0;
//int  Golden_Unit_Prg =0;
int	 g_Char_Enable_P=0;
int g_Debug = 0;

// ======================  Debug Parameters ============================ //
char *g_Func_name;
char *g_WAVE_NAME = "NoWaveName"; 

// ======================  Setup Variable  ============================//
//STRING CURRENT_SERIAL_NUM; 
int  g_FirstPart = 0; // Must initialize to 1 to start. //
int  gFuncNum=0;
int  gDisplay_FuncNum=0;
bool g_Wrong_Number_Of_Functions = false;

// ======================  Trimming Variable  ============================//
float gTrim_Voltage = 0.0;

//=======================    Test Debug Variables    ===============================//
CMicroTimer mytimer;					
LONGLONG starttime;
LONGLONG stoptime;
int DEBUG =0;
//char *WAVE_NAME = "NoWaveName"; 

//=======================    Golden Unit Variables    ===============================//
bool GoldenUnit = false;

//=======================		DDD Variables		 ===============================//
float Dclk_period = 0; // DDD clock period
float DDD_Vref = 0; // DDD voltage reference
float g_Dclk_I2C = 0; // I2C DDD clock period //
float g_Vref_I2C = 0; // I2C DDD voltage reference //
int g_DDD_fast = 0;

// DSM I2C error counters
//uint32_t __dsm_write_fail_count = 0;
//uint32_t __dsm_write_retry_count = 0;
//uint32_t __dsm_write_pass_count = 0;
//uint32_t __dsm_read_fail_count = 0;
//uint32_t __dsm_read_pass_count = 0;

//bool DSM_halt_exec_on_error = TRUE;
float g_vDSM_pullup_P = 0;
float g_vDSM_pullup_S = 0;

//Global Characterization variables
bool	g_Char_iOVp_XYplot = false;
bool	g_Char_iOVm_XYplot = false;
bool	g_Char_iUVp_XYplot = false;
bool	g_Char_iUVm_XYplot = false;

//iOV function global variables
bool g_USE_VR_600K = true;

//Global Delay variables
int		g_Erase_dly_P,
		g_Burn_dly_P,
		g_Erase_dly_S,
		g_Burn_dly_S;

//CX added for Primary variables
float g_vDrain_Erase_th_P = 0;
float g_vDrain_Burn_th_P = 0;

//HL added for the 2ndary variables.
int   g_DDD_10Khz_Pulses_StopAddr = 0;
int   g_DDD_100Khz_Pulses_StopAddr = 0;
float g_DDD_Period = 0;

int First_address; 
int g_NextAddrFixed = 0;
int g_NextAddr;
int Low_pat_start, Low_pat_stop, 
	Low_XXX_pat_start, Low_XXX_pat_stop,
	High_pat_start, High_pat_stop,
	High_pat_FB_start, High_pat_FB_stop,
	//High_pat_FW_start, High_pat_FW_stop,
	HIZ_SDA_SCL_start,HIZ_SDA_SCL_stop,
	SDA_SCL_HIZ_FW_High_start, SDA_SCL_HIZ_FW_High_stop,
	//FWhi_FBhi_Vlow_start, FWhi_FBhi_Vlow_stop,
	//FWhi_FBlow_Vhi_start, FWhi_FBlow_Vhi_stop,
	FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop,
	FW_Neg_2nd_pulse_start, FW_Neg_2nd_pulse_stop,
	FW_Neg_3rd_pulse_start, FW_Neg_3rd_pulse_stop,
	FWneg_FBhi_Vlo_1st_pulse_start, FWneg_FBhi_Vlo_1st_pulse_stop,
	FWneg_FBhi_Vlo_2nd_pulse_start, FWneg_FBhi_Vlo_2nd_pulse_stop,
	FWneg_FBhi_Vlo_3rd_pulse_start, FWneg_FBhi_Vlo_3rd_pulse_stop,
	//FW_Neg_4th_pulse_start, FW_Neg_4th_pulse_stop,
	//FW_Neg_5th_pulse_start, FW_Neg_5th_pulse_stop,
	FWPK_300kHz_Ring_start, FWPK_300kHz_Ring_stop,
	FWPK_1MHz_Ring_start, FWPK_1MHz_Ring_stop,
	FWPK_Max_Ring_start, FWPK_Max_Ring_stop,
	FWPK_Min_Ring_start, FWPK_Min_Ring_stop,
	FWPK_test_pulses_start1, FWPK_test_pulses_stop1,
	FWPK_test_pulses_start1_single, FWPK_test_pulses_stop1_single,
	FWPK_test_pulses_start2_single, FWPK_test_pulses_stop2_single,
	FWPK_test_pulses_start3_single, FWPK_test_pulses_stop3_single,
	FWPK_test_pulses_start4_single, FWPK_test_pulses_stop4_single,
	FWPK_test_pulses_start5_single, FWPK_test_pulses_stop5_single,
	HIZallChannels_start, HIZallChannels_stop,
	Vout_loop_pulse_start, Vout_loop_pulse_stop,
	FW_Neg_loop_pulse_start, FW_Neg_loop_pulse_stop,
	Vpin_loop_pulse_start, Vpin_loop_pulse_stop,
	FB_100kHz_loop_pulse_start, FB_100kHz_loop_pulse_stop, 
	FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop,
	FB_tOVL_start, FB_tOVL_stop,
	AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop,
	AF_Vpin_Clk_pulse_start_132kHz, AF_Vpin_Clk_pulse_stop_132kHz,
	AF_Vpin_Data_pulse_start,AF_Vpin_Data_pulse_stop;

	int Vpin_100kHz_ILIM_pulse_start;
	int Vpin_100kHz_ILIM_pulse_stop;

	int FB_18kHz_pulse_start;
	int FB_18kHz_pulse_stop;
	int FB_125kHz_pulse_start;
	int FB_125kHz_pulse_stop;

	int Vpin_125kHz_pulse_start_X;
	int Vpin_125kHz_pulse_stop_X;
	int Vpin_100kHz_ILIM_pulse_start_X;
	int Vpin_100kHz_ILIM_pulse_stop_X;
	int Vpin_6clocks_start;
	int Vpin_6clocks_stop;
	int Vpin_4clocks_start;
	int Vpin_4clocks_stop;
	int Vpin_2clocks_start;
	int Vpin_2clocks_stop;
	int Vpin_3NegClocks_start;
	int Vpin_3NegClocks_stop;
	int Vpin_30usec_start;
	int Vpin_30usec_stop;
	int Vpin_one_30us_clock_start;
	int Vpin_one_30us_clock_stop;
	int FB_100kHz_pulse_start_5X;
	int FB_100kHz_pulse_stop_5X;

/*=======================    Internal Registers   ===============================*/
int gVpin_Internal_Signal[16]	={0};	//Primary Internal Registers
float gIZ_AF_post_P[100]			={0};

/*=======================    BVD Function Variables    ===============================*/
float g_scaled_ifrc = 0.0;
float	gBVD_Room_Trimops=0.0;
float	gBVD_Hot_Trimops=0.0;

/*============================    VBP function   ===============================*/
float gVshunt_BPP =0.0, gVshunt_BPS =0.0;
float gVBPP_P_Init =0.0, gVBPP_P_final=0.0, gVBPS_P_Init =0.0,  gVBPS_final=0.0, 
	  gVBPP_M_Init =0.0, gVBPS_M_Init =0.0, gVBPP_PV_Init=0, gVBPP_PV_final=0; 
float g_VBPP_P_S_Init_S = 0;
float g_VBPP_P_s_final = 0;
float gVBPP_VCEN=0.0;
float gIBPS_nsw=0.0;
float gIBPS_nswHF=0.0;
float gVBPS_P=0.0;

/*============================    Timing Global Variables   ===============================*/
float gDly_Wait_and_Listen_Normal_Mode = 0.0;
float gDly_Wait_and_Listen_Test_Mode = 0.0;
float g_readTime_p =0.0;
float g_readTime_s =0.0;
float g_trimTime_p =0.0;
float g_trimTime_s =0.0;
float g_StartTime  =0.0;
float g_StopTime   =0.0;
int   g_ILIM_dly    =0.0;
int	  g_REL_dly    =0.0;
int	  g_tHandshake_SSS =0.0;

/*============================    FB Global Variables   ===============================*/
ofstream dumparray;
/*============================    Anti-Fuse Variables   ===============================*/
//Primary
int 	gP_Reg_Start_Bit_SiID		=	0	,
		gP_Reg_Start_Bit_fOSC		=	0	,
		gP_Reg_Start_Bit_yInter		=	0	,
		gP_Reg_Start_Bit_ILIM		=	0	,
		gP_Reg_Start_Bit_ArSkip		=	0	,
		gP_Reg_Start_Bit_ArOnT		=	0	,
		gP_Reg_Start_Bit_ArOffT		=	0	,
		gP_Reg_Start_Bit_StrFREQ	=	0	,
		gP_Reg_Start_Bit_OnTSL		=	0	,
		gP_Reg_Start_Bit_ShuntEn	=	0	,
		gP_Reg_Start_Bit_RcvTH		=	0	,
		gP_Reg_Start_Bit_GanMode	=	0	,
		gP_Reg_Start_Bit_VxTrim		=	0	,
		gP_Reg_Start_Bit_DrSize		=	0	,
		gP_Reg_Start_Bit_AROn512	=	0	,
		gP_Reg_Start_Bit_GanDLy1	=	0	,
		gP_Reg_Start_Bit_IlimTc		=	0	,
		gP_Reg_Start_Bit_SDTemp		=	0	,
		gP_Reg_Start_Bit_DOPL		=	0	,
		gP_Reg_Start_Bit_DisIlimCap	=	0	,
		gP_Reg_Start_Bit_ILIMP		=	0	,
		gP_Reg_Start_Bit_uVADC		=	0	,
		gP_Reg_Start_Bit_StrTTFB	=	0	,
		gP_Reg_Start_Bit_EndTTFB	=	0	,
		gP_Reg_Start_Bit_TsADC		=	0	,
		gP_Reg_Start_Bit_UV10pct	=	0	,
		gP_Reg_Start_Bit_IOV		=	0	,
		gP_Reg_Start_Bit_TonM		=	0	;

int 	gP_Total_Bits_SiID			=	0	,
		gP_Total_Bits_fOSC			=	0	,
		gP_Total_Bits_yInter		=	0	,
		gP_Total_Bits_ILIM			=	0	,
		gP_Total_Bits_ArSkip		=	0	,
		gP_Total_Bits_ArOnT			=	0	,
		gP_Total_Bits_ArOffT		=	0	,
		gP_Total_Bits_StrFREQ		=	0	,
		gP_Total_Bits_OnTSL			=	0	,
		gP_Total_Bits_ShuntEn		=	0	,
		gP_Total_Bits_RcvTH			=	0	,
		gP_Total_Bits_GanMode		=	0	,
		gP_Total_Bits_VxTrim		=	0	,
		gP_Total_Bits_DrSize		=	0	,
		gP_Total_Bits_AROn512		=	0	,
		gP_Total_Bits_GanDLy1		=	0	,
		gP_Total_Bits_IlimTc		=	0	,
		gP_Total_Bits_SDTemp		=	0	,
		gP_Total_Bits_DOPL			=	0	,
		gP_Total_Bits_DisIlimCap	=	0	,
		gP_Total_Bits_ILIMP			=	0	,
		gP_Total_Bits_uVADC			=	0	,
		gP_Total_Bits_StrTTFB		=	0	,
		gP_Total_Bits_EndTTFB		=	0	,
		gP_Total_Bits_TsADC			=	0	,
		gP_Total_Bits_UV10pct		=	0	,
		gP_Total_Bits_IOV			=	0	,
		gP_Total_Bits_TonM			=	0	;


//Secondary
int	gPK_AF_Addr_Start					=0,						
	gCV_AF_Addr_Start					=0,
	gSpare_Addr_Start					=0,
	gZF_S_Addr							=0;
/*============================    Feature Trim Variables   ===============================*/
double	g_Hcode_Trimops =0,
		gTrim_code_Trimops =0;

int		gTrim_iov_Off_P_Trimops		=0,
		gTrim_iuvMinus_P_Trimops	=0,
		gTrim_uvDelay_P_Trimops		=0,
		gTrim_Loff_AR_P_Trimops		=0,
		gTrim_DisablAR_P_Trimops	=0,
		gTrim_didtComp_P_Trimops	=0,
		gTrim_OT_Hys_P		=0,
		gTrim_LoffwOT_P_Trimops		=0,
		gTrim_iLselOff_P_Trimops	=0,
		gTrim_iLStdIcr_P_Trimops	=0,
		gTrim_iL20dn_P_Trimops		=0,
		gTrim_iL20up_P_Trimops		=0,
		gTrim_SAM_P_Trimops			=0,
		gTrim_OTP_P_Trimops			=0,	//3 bits
		gTrim_SDSoff_P_Trimops		=0,
		gTrim_Rcv_P_Trimops			=0, //3 bits
		gTrim_drvSize_P_Trimops		=0, //4 bits
		gTrim_RsenseUp_P_Trimops	=0,
		gTrim_vxAdj_P_Trimops		=0, //5 bits
		gTrim_iLRatio_P_Trimops		=0, //4 bits
		gTrim_iLTC_P_Trimops		=0, //4 bits
		gTrim_AR_req_Trimops		=0;






int gTrim_SdwReg0_Trimops  = 0;
int gTrim_SdwReg1_Trimops  = 0;
int gTrim_SdwReg2_Trimops  = 0;
int gTrim_SdwReg3_Trimops  = 0;
int gTrim_SdwReg4_Trimops  = 0;
int gTrim_SdwReg5_Trimops  = 0;
int gTrim_SdwReg6_Trimops  = 0;
int gTrim_SdwReg7_Trimops  = 0;
int gTrim_SdwReg8_Trimops  = 0;
int gTrim_SdwReg9_Trimops  = 0;
int gTrim_SdwReg10_Trimops  = 0;
int gTrim_SdwReg11_Trimops  = 0;
int gTrim_SdwReg12_Trimops  = 0;
int gTrim_SdwReg13_Trimops  = 0;
int gTrim_SdwReg14_Trimops  = 0;
int gTrim_SdwReg15_Trimops  = 0;
int gTrim_SdwReg16_Trimops  = 0;
int gTrim_SdwReg17_Trimops  = 0;
int gTrim_SdwReg18_Trimops  = 0;
int gTrim_SdwReg19_Trimops  = 0;
int gTrim_SdwReg20_Trimops  = 0;
int gTrim_SdwReg21_Trimops  = 0;
int gTrim_SdwReg22_Trimops  = 0;
int gTrim_SdwReg23_Trimops  = 0;
int gTrim_SdwReg24_Trimops  = 0;
int gTrim_SdwReg25_Trimops  = 0;
int gTrim_SdwReg26_Trimops  = 0;
int gTrim_SdwReg27_Trimops  = 0;
int gTrim_SdwReg28_Trimops  = 0;
int gTrim_SdwReg29_Trimops  = 0;
int gTrim_SdwReg30_Trimops  = 0;
int gTrim_SdwReg31_Trimops  = 0;
int gTrim_SdwReg32_Trimops  = 0;
int gTrim_SdwReg33_Trimops  = 0;
int gTrim_SdwReg34_Trimops  = 0;
int gTrim_SdwReg35_Trimops  = 0;
int gTrim_SdwReg36_Trimops  = 0;
int gTrim_SdwReg37_Trimops  = 0;
int gTrim_SdwReg38_Trimops  = 0;
int gTrim_SdwReg39_Trimops  = 0;
int gTrim_SdwReg40_Trimops  = 0;
int gTrim_SdwReg41_Trimops  = 0;
int gTrim_SdwReg42_Trimops  = 0;
int gTrim_SdwReg43_Trimops  = 0;
int gTrim_SdwReg44_Trimops  = 0;
int gTrim_SdwReg45_Trimops  = 0;
int gTrim_SdwReg46_Trimops  = 0;
int gTrim_SdwReg47_Trimops  = 0;
int gTrim_SdwReg48_Trimops  = 0;
int gTrim_SdwReg49_Trimops  = 0;
int gTrim_SdwReg50_Trimops  = 0;
int gTrim_SdwReg51_Trimops  = 0;
int gTrim_SdwReg52_Trimops  = 0;
int gTrim_SdwReg53_Trimops  = 0;
int gTrim_SdwReg54_Trimops  = 0;
int gTrim_SdwReg55_Trimops  = 0;
int gTrim_SdwReg56_Trimops  = 0;
int gTrim_SdwReg57_Trimops  = 0;
int gTrim_SdwReg58_Trimops  = 0;
int gTrim_SdwReg59_Trimops  = 0;
int gTrim_SdwReg60_Trimops  = 0;
int gTrim_SdwReg61_Trimops  = 0;
int gTrim_SdwReg62_Trimops  = 0;
int gTrim_SdwReg63_Trimops  = 0;
int gTrim_SdwReg64_Trimops  = 0;
int gTrim_SdwReg65_Trimops  = 0;
int gTrim_SdwReg66_Trimops  = 0;
int gTrim_SdwReg67_Trimops  = 0;
int gTrim_SdwReg68_Trimops  = 0;
int gTrim_SdwReg69_Trimops  = 0;
int gTrim_SdwReg70_Trimops  = 0;
int gTrim_SdwReg71_Trimops  = 0;
int gTrim_SdwReg72_Trimops  = 0;
int gTrim_SdwReg73_Trimops  = 0;
int gTrim_SdwReg74_Trimops  = 0;
int gTrim_SdwReg75_Trimops  = 0;
int gTrim_SdwReg76_Trimops  = 0;
int gTrim_SdwReg77_Trimops  = 0;
int gTrim_SdwReg78_Trimops  = 0;
int gTrim_SdwReg79_Trimops  = 0;
int gTrim_SdwReg80_Trimops  = 0;
int gTrim_SdwReg81_Trimops  = 0;
int gTrim_SdwReg82_Trimops  = 0;
int gTrim_SdwReg83_Trimops  = 0;
int gTrim_SdwReg84_Trimops  = 0;
int gTrim_SdwReg85_Trimops  = 0;
int gTrim_SdwReg86_Trimops  = 0;
int gTrim_SdwReg87_Trimops  = 0;
int gTrim_SdwReg88_Trimops  = 0;
int gTrim_SdwReg89_Trimops  = 0;
int gTrim_SdwReg90_Trimops  = 0;
int gTrim_SdwReg91_Trimops  = 0;
int gTrim_SdwReg92_Trimops  = 0;
int gTrim_SdwReg93_Trimops  = 0;
int gTrim_SdwReg94_Trimops  = 0;
int gTrim_SdwReg95_Trimops  = 0;
int gTrim_SdwReg96_Trimops  = 0;
int gTrim_SdwReg97_Trimops  = 0;
int gTrim_SdwReg98_Trimops  = 0;
int gTrim_SdwReg99_Trimops  = 0;
int gTrim_SdwReg100_Trimops  = 0;
int gTrim_SdwReg101_Trimops  = 0;
int gTrim_SdwReg102_Trimops  = 0;
int gTrim_SdwReg103_Trimops  = 0;
int gTrim_SdwReg104_Trimops  = 0;
int gTrim_SdwReg105_Trimops  = 0;
int gTrim_SdwReg106_Trimops  = 0;
int gTrim_SdwReg107_Trimops  = 0;
int gTrim_SdwReg108_Trimops  = 0;
int gTrim_SdwReg109_Trimops  = 0;
int gTrim_SdwReg110_Trimops  = 0;
int gTrim_SdwReg111_Trimops  = 0;

int g_SiliconRev_Pri = 1; // Primary silicon revision //
int g_SiliconRev_Sec = 1; // Secondary silicon revision //

uint16_t EEpr_Bank_P[5] = {0};
uint16_t EEpr_Array_S[5] = {0};

int	g_Pre_E0_data_P = 0;
int	g_Pre_E2_data_P = 0;
int	g_Pre_E4_data_P = 0;
int g_Pre_E6_data_P = 0;
int g_Pre_E8_data_P = 0;
		
int	g_Pre_E0_data_S = 0;
int g_Pre_E2_data_S = 0;
int	g_Pre_E4_data_S = 0;
int g_Pre_E6_data_S = 0;
int	g_Pre_E8_data_S = 0;

/*=======================    IzPre Function Variables    ===============================*/
float	gIzpt_NoZ_s=0.0, gIZ_NoZ_s=0.0;
float   gVread_AF_primary =0.0, gVread_AF_secondary =0.0;
float   gSec_tr1_ZapTime =0.0;
float   gSec_tr2_AFtrhd  = 0.0;
int		gSiOption_s=-99;

/*====================    Fosc Function Variables    ===============================*/
float	gP_Fosc_TARGET_Trimops=0.0, gFOSC_TARGET_S_Trimops =0.0;
float   g_Fosc_pt_P =0.0,   g_FOSC_pt_S =0.0;
float   g_FOSC_S = 0;
float   g_FOSC_exp_P =0.0,  g_FOSC_exp_S=0.0;

/*======================    TonMin Variables    ====================================*/
float   gP_TonMin_TARGET_Trimops		=0.0;

/*======================    Ton Slope & Offset Variables    ====================================*/
float   gP_Slope_TARGET_Trimops	=0.0;
float	gP_Offset_TARGET_Trimops	=0.0;
//float	g_TonMax_Pt =0.0, g_TonMax_S=0.0;
//float   g_ToffMin_s = 0;
//float   g_TonMax_exp=0.0;
//float   g_tOVL_TARGET_Trimops=0.0;
//float	g_tOVL_Pt =0.0;
//float   g_tOVL_exp=0.0;
//int		g_HandShake_PASS =0;

/*======================    iOV+ Variables    ====================================*/
float   gP_iOVp_TARGET_Trimops=0.0;
float   gP_iOVm_TARGET_Trimops=0.0;
float	g_iOVp_pt_P =0.0;
float   g_iOVp_exp=0.0;

/*======================    iUV Variables    ====================================*/
float   gP_iUVp_TARGET_Trimops=0.0;
float   gP_iUVm_TARGET_Trimops=0.0;
float	g_iUVp_pt_P =0.0;
float   g_iUVp_exp=0.0;

/*======================    CV Variables    ====================================*/
float 	gCV_FB_Init_pt_S =0.0;
//float	gCV_FB_pt_S =0;
float	gCV_VO_pt_S =0;
//float   gCVtgt_15pct_Higher=0.0; //gCV_FB_Pre=0.0;
float   gCV_Vout_TARGET_Trimops;
float	gCV_S =0.0, gCV_post_S=0;
float	gCV_FB_S=0, gCV_FB_post_S=0;
float	gCV_VO_S=0,	gCV_VO_post_S=0;
float   gVclamp_2pct_S =0.0, gVclamp_10pct_S =0.0;

/*======================    CC Variables    ====================================*/
float 	gCC_pt_S =0.0;
float 	gKP_pt_S =0.0;
//float	gCC_Amp_pt_S =0.0;
float	gISvth_pt_S =0.0;
float   gISvth_TARGET_Trimops=0.0;

float	gCC_KPpt_S=0.0;
float	gCV_NM_KPpt_S=0.0;
float	gCB_KPpt_S=0.0;
float	gSL_pt_S=0.0;
float	gCC_Amp_SLpt_S=0.0;
float	gCC_ISvth_SLpt_S=0.0;
float	gVknee_actual_SLpt_S=0.0;
float	gCC_Amp_S=0.0;
float	gVknee_actual_S=0.0;

float	gCC_S_9V_TARGET=0.0;
float	gCC_S_12V_TARGET=0.0;
float	gCC_S_20V_TARGET=0.0;
float   gCC_exp_S=0.0;
float	gISvth_S_9V_TARGET=0.0;
float	gISvth_S_12V_TARGET=0.0;
float	gISvth_S_20V_TARGET=0.0;
float	gKP_exp_S=0.0;
float	gSL_exp_S=0.0;
float   iPV3_Cal_CC90=0.0;
float   iPV3_Cal_CC80=0.0;
float   iPV3_Cal_CC65=0.0;
float   iPV3_Cal_CC55=0.0;
float	iPV3_CC90  = 0.0;
float	iPV3_CC80  = 0.0;
float	iPV3_CC65  = 0.0;
float	iPV3_CC55  = 0.0;

/*======================    CB Variables    ====================================*/
int		gCB_CODE =0.0;
float   gCB_exp_S=0.0;
float   iPV3_Load=0.0, iDVI2K_Load=0.0;	// For CB vs load experiment
float	gCB_NoLoad_Pct_pt;
float	gvCB_pre_TM_S;

/*======================    IFB Variables    ====================================*/
float	gIFB_TH_Target_S	=0.0;
float	gIFB_250mA_pt_S		=0.0;
float	gIFB_130mA_pt_S		=0.0;
float	gIFB_TH_pt_S		=0.0;
float   gIFB_exp_S			=0.0;

/*======================    Dtemp Variables    ====================================*/
float	gP_Dtemp_TARGET_Trimops=0;
float	gP_VTSstart_TARGET_Trimops=0;

/*======================    ILIM Variables    ====================================*/
float	gVped_Ilim =0.0, gVped_Ilim_Incr=0.0;
float	gVind_RM =0.0;
float g_Vpedestal = 0;

float	gP_ILIM_TARGET_Trimops=0.0;
float	g_ILIM_LO_TARGET=0.0;
float	g_ILIM_LO_Med_TARGET=0.0;
float	g_ILIM_UP_Med_TARGET=0.0;
float	g_I2F_S_TARGET=0.0;
float   g_DIDT_TARGET = 0.0;
float   g_ILIM_pt_S =0.0;
float   g_ILIM_exp_S =0.0;
float	g_ILIM_I2f_pt_S =0.0;

// For Capture and Find ILIM with digitizer
float   g_Ilim_Incr_max=0.0;
float	g_Ilim_gain =0.0, g_BUFgain=0.0;
int		g_SAMPLE_SIZE=0;

int		g_FIND_RDSON_Peak_FLAG	=0;
int		g_FIND_RDSON_Spec_FLAG	=0;
int		g_Find_ILIM_Jitter		=0;
float	g_Idmax[4000]				={-100.0};
int		g_Idmax_addr[4000]		={0};

float	gTon_1stP			=0.0;
float	gTon_2ndP			=0.0;
float	gTon_3rdP			=0.0;
float	gToff_1stP			=0.0;
float	gToff_2ndP			=0.0;
float	gToff_3rdP			=0.0;
float	g_ILIM_pct_1stP		=0.0;
float	g_ILIM_pct_2ndP		=0.0;
float	g_ILIM_pct_3rdP		=0.0;
float   gRTM_Slope			=0.0;
float   gtDelta_RTM_Slope	=0.0;
float	gtDelta_RTM_Slope_200us =0.0;
float	gi_pct_drop_RTM		=0.0;
float	g_ILIM_200us_S		=0.0;
float   g_ILIM_200us_pct_S   =0.0;
/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
float gISvth =0.0;
float MEAS_Isvth_FLAG =0;

/*=======================    VBP_Supply Function Variables    ===============================*/
float gVshunt_Init_Pr =0.0;
float gVshunt_Init_Se =0.0;
float g_BPP_IS1_nsw_P = 0.0;
float g_BPP_IS2_sw_P = 0.0;
float gISD_P = 0;
float gISD_S = 0;

/*=======================    DATT Function Variables    ===============================*/
float	gDATT_drain_current =0.0, gDATT_pulse_time =0.0;
float	gNorm_x_lim =0.0, gNorm_n_lim =0.0;

/*===========================    HandShake Variables    ===============================*/
extern float HANDSHAKE_Vd_TM=0.0,		// Set Drain pull up voltage. 
			 HANDSHAKE_Vd_NM =0.0;		// Set Drain pull up voltage. 

// ======================  Gage Digitizer Variables=============================
int		SAMPLE_RATE_Hz	= 50e6;
float	SAMPLE_RATE_s	= 20e-9;
int		g_DigitizerType		= 0;

// ============================  Gage Digitizer ================================
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_32K		// 640us
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_64K		// 1280us or 1.28ms 
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_128K		// 2560us or 2.56ms
#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_1M		// 2560us or 2.56ms
#define GAGE_WAVEFORM_BUFFER_SIZE_18kHz		GAGE_POST_256K		// 5.12ms to cover 18kHz tests. // DPG added //
#define GAGE_WAVEFORM_BUFFER_PAD	10	

signed short chan_a_16[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];
signed short chan_b_16[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];
//int Gage_pretrig_samples = 64; //must be divisible by 32
int Gage_pretrig_samples = 1024; //must be divisible by 32

//// XP ////
	//XP variables for Gage
	int		debug_gage_error	=	0;	//set to 1 to print gage errors to DOS window
	int32						i32Status = CS_SUCCESS;
	TCHAR						szFileName[MAX_PATH];
	int64						i64StartOffset = 0;
	void*						pBuffer = NULL;
	float*						pVBuffer = NULL;
	uInt32						u32Mode;
	CSHANDLE					hSystem = 0;
	IN_PARAMS_TRANSFERDATA		InData = {0};
	OUT_PARAMS_TRANSFERDATA		OutData = {0};
	CSSYSTEMINFO				CsSysInfo = {0};
	CSAPPLICATIONDATA			CsAppData = {0};
	FileHeaderStruct			stHeader = {0};
	CSACQUISITIONCONFIG			CsAcqCfg = {0};
	CSCHANNELCONFIG				CsChanCfg = {0};
	CSCHANNELCONFIG				CsChanCfg_B = {0};
	CSTRIGGERCONFIG				CsTrigCfg = {0};
	uInt32						u32ChannelIndexIncrement;
	int64						i64Padding = 64; //extra samples to capture to ensure we get what we ask for
	int64						i64SavedLength;
	int64						i64MaxLength;
	int64						i64MinSA;  
	LONGLONG current_time;
	LONGLONG initial_time;

	int debug_test_time;
	float Gage_chan_a_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//add padding 
	int16 chan_a_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//old signed short.
    float Gage_chan_b_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
	int16 chan_b_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
		//// XP ////
	float Gage_chan_aa_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//add padding 
	int16 chan_aa_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//old signed short.
	float Gage_chan_bb_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
	int16 chan_bb_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.

	// ++++++++++++++++++++++++++++++++++++++ //
	float *Gage_chan_a_voltageM = (float *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(float));
	int16 *chan_a_16_rawM = (int16 *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*2);
	float *Gage_chan_b_voltageM = (float *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(float));
	int16 *chan_b_16_rawM = (int16 *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*2);
	// ++++++++++++++++++++++++++++++++++++++ //

	int dig_ok,tbs,n;
	double trig_level;
	signed long starting_a,ending_a,trigger;
	signed long starting_b,ending_b;
	unsigned long offset_a,offset_b,timenow[10];
	BOOL data_ok,trig_ok;
#ifdef NT_
	signed long g_gage_sample_resolution_32;
#endif
	signed short	boards_in_system;
#ifdef NT_
	unsigned short /*far*/	gage_board_location[GAGE_B_L_BUFFER_SIZE];
	gage_driver_info_type   *board_info;
#endif
	//for Create_Awav 
	char			Wav_Outfile_path[100] = "e:\\DL4\\";
	char			Wav_outfile_name[100];
	STRING	Dut_serial_number;	
	STRING  lot_info_handler;
//	STRING ProgramName, Prg_Name;

	//////----------------------------------------------------------------
	//////Will need to remove in the future.  Codes left from INNOVi
	////// Declare register names and their addresses. //

	//////int g_SlaveAddress; // 7 bits only. '0011000' //
	////int g_SlaveAddress; // Broadcast address. 7 bits only. '0000000' //
	////int g_RDADDR; // WR_Word //
	////int g_FWPK_reg; // WR_Byte //
	////int g_VBEN; // WR_Byte //
	////int g_MINLD; // WR_Byte //
	////int g_VDIS; // WR_Byte //
	////int g_Self_Destruct; // WR_Byte //
	////int g_Fast_VI_Command; // WR_Byte //
	////int g_CVO_mode; // WR_Byte, Rev2 silicon //
	////int g_CV_reg; // WR_Word //
	////int g_OVA;
	////int g_UVA;
	////int g_CDC; // WR_Byte //
	////int g_CC_reg;
	////int g_VPK_reg;
	////int g_OVL; // WR_Byte //
	////int g_UVL; // WR_Byte //
	////int g_CCSCL; // WR_Byte //
	////int g_ISSC; // WR_Byte //
	////int g_UVL_Timer; // WR_Byte //
	////int g_Watchdog_Timer; // WR_Byte //
	////int g_CVO_response; // WR_Byte, Rev2 silicon //
	////int g_CVO_timer; // WR_Byte, Rev2 silicon //
	////int g_Interrupt_Mask; // WR_Byte, Rev2 silicon //
	////int g_OTP; // WR_Byte, Rev2 silicon //
	////int g_fast_cc_offset; // WR_Byte, RevC silicon //
	////int g_loop_speed_set1; // WR_Word, RevC silicon  //
	////int g_loop_speed_set2; // WR_Word, RevC silicon  //
	////int g_TM_CTRL; // WR_Word //
	////int g_TM_SEL; // WR_Word //
	////int g_TM_DAC; // WR_Byte //
	////int g_TM_ANA; // WR_Word, Rev2 silicon //
	////int g_EEP_CMD; // WR_Byte //	
	////int g_TM_EN; // WR_Word //


	//------------------------------------------------------------------------------------------------
	//Secondary Registers.
	//---------------------------------------------------------------------------------------------------
	int g_SlaveAddress_P;       //7 bits only.
	int g_SlaveAddress_S;       //7 bits only.
	int g_RDADDR;			  //WR_Word
	int g_CORE_CTRL0;         //WR_Byte
	int g_CORE_CTRL1;         //WR_Byte
	int g_CORE_CTRL2;         //WR_Byte
	int g_TM_CTRL;	          //WR_Byte
	int g_SIG_CTRL;           //WR_Byte
	int g_ANA_CTRL_0;         //WR_Word
	int g_ANA_CTRL_1;         //WR_Word
	int g_I2C_CTRL;           //WR_Byte
	int g_FAULT_CTRL;         //WR_Byte
	int g_PINSCL_CTRL;        //WR_Byte
	int g_PINSDA_CTRL;        //WR_Byte
	int g_RDPIN_FAULT;		  //WR_Byte
	int g_PIN1_CFG;           //WR_Byte
	int g_EEP_CMD;            //WR_Byte
	int g_TM_EN;			  //WR_Word
	int g_EEP_W_E0;           //WR_Word
	int g_EEP_W_E2;           //WR_Word
	int g_EEP_W_E4;           //WR_Word
	int g_EEP_W_E6;           //WR_Word
	int g_EEP_W_E8;           //WR_Word
	int g_EEP_R_C0;           //WR_Word
	int g_EEP_R_C2;           //WR_Word
	int g_EEP_R_C4;           //WR_Word
	int g_EEP_R_C6;           //WR_Word
	int g_EEP_R_C8;           //WR_Word
	int g_TEST_CTRL1;         //WR_Word
	int g_TEST_CTRL2;         //WR_Word
	int g_TEST_CTRL3;         //WR_Word
	int g_TEST_CTRL4;         //WR_Word

	int g_READ00;       //RD_Word
	int g_READ02;       //RD_Word
	int g_READ04;       //RD_Word
	int g_READ06;       //RD_Word
	int g_READ08;       //RD_Word
	int g_READ0A;       //RD_Word
	int g_READ0C;       //RD_Word
	int g_READ0E;       //RD_Word
	int g_READ10;       //RD_Word
	int g_READ12;       //RD_Word
	int g_READ14;       //RD_Word
	int g_READ16;       //RD_Word
	int g_READ40;       //RD_Word
	int g_READ42;       //RD_Word
	int g_READ44;       //RD_Word
	int g_READ46;       //RD_Word
	int g_READ48;       //RD_Word
	int g_READ4A;       //RD_Word
	int g_READ4C;       //RD_Word
	int g_READ70;       //RD_Word
	
	int g_LowerByte = 0;

// Define register names and their addresses. //
// EEPROM shadow registers //	
int g_SREG0; // WR_Word //
int g_SREG1; // WR_Word //
int g_SREG2; // WR_Word //
int g_SREG3; // WR_Word //
int g_SREG4; // WR_Word //
int g_SREG5; // WR_Word //
int g_SREG6; // WR_Word //

////// Define register names and their addresses. //
////// Read Back Registers //	
////int g_READ0; //RD_Word //
////int g_READ1; //RD_Word //
////int g_READ2; //RD_Word //
////int g_READ3; //RD_Word //
////int g_READ4; //RD_Word //
////int g_READ5; //RD_Word //
////int g_READ6; //RD_Word //
////int g_READ7; //RD_Word //
////int g_READ8; //RD_Word //
////int g_READ9; //RD_Word //
////int g_READ10; //RD_Word //
////int g_READ11; //RD_Word //
////int g_READ12; //RD_Word //
////int g_READ13; //RD_Word //
////int g_READ14; //RD_Word //
////int g_READ15; //RD_Word //
////int g_READ16; //RD_Word //
////int g_READ17; //RD_Word //
////int g_READ18; //RD_Word, Rev.1 silicon only //
////int g_READ19; //RD_Word, Rev.1 silicon only //
////int g_READ20; //RD_Word, Rev.1 silicon only //
////int g_READ21; //RD_Word, Rev.1 silicon only //
////int g_READ22; //RD_Word, Rev.1 silicon only //
////int g_READ40; // WR_Word, Rev2 silicon //
////int g_READ41; // WR_Word, Rev2 silicon //
////int g_READ42; // WR_Word, Rev2 silicon //
////int g_READ43; // WR_Word, Rev2 silicon //
////int g_READ44; // WR_Word, Rev2 silicon //
////int g_READ45; // WR_Word, Rev2 silicon //
////int g_READ46; // WR_Word, Rev2 silicon //
////int g_READ47; // WR_Word, Rev2 silicon //
////int g_READ56; // WR_Word, Rev2 silicon //
////int g_READ57; // WR_Word, Rev2 silicon //
////int g_READ58; // WR_Word, Rev2 silicon //
////int g_READ59; // WR_Word, Rev2 silicon //
////int g_READ60; // WR_Word, Rev2 silicon //
////int g_READ61; // WR_Word, Rev2 silicon //
////int g_READ62; // WR_Word, Rev2 silicon //

// Passwords and keys for entering test mode. //
// To enter test mode, for write the g_TestMode_Password followed by g_TestMode_Enter. //
// To exit test mode, for write the g_TestMode_Password followed by g_TestMode_Exit. //
int g_TestMode_Password; // Word //
int g_TestMode_Enter; // Word.  Key to enter test mode. //
int g_TestMode_Exit; // Word.  Key to exit test mode. //
int g_SR_Enable; //Word. Enable SR drive before entering scan mode.
int g_ScanMode_Enter;//Word. Key to enter Scan mode.//

// Declare Global Variables for FunctionsToExecute() function. //
int g_Fn_aFirst = 0;
int g_Fn_Continuity = 0;
int g_Fn_Leakage = 0;
int g_Fn_ScanChain = 0;
int g_Fn_BV_Vpin = 0;
int g_Fn_BV_FW = 0;
int g_Fn_BV_Drain = 0;
int g_Fn_VBP_Init = 0;
int g_Fn_BPS_STRESS = 0;
int g_Fn_BPP_STRESS = 0;
int g_Fn_IzPre = 0;
int g_Fn_Feature_Trim_P = 0;
int g_Fn_Feature_Trim_S = 0;
int g_Fn_OVT = 0;
int g_Fn_IOV_Pre_P = 0;
int g_Fn_IOV_Trim = 0;
int g_Fn_IOV_post_P = 0;
int g_Fn_Fosc_Pre_P = 0;
int g_Fn_Fosc_Trim_P = 0;
int g_Fn_Fosc_post_P = 0;
int g_Fn_tOVL_Pre_S = 0;
int g_Fn_tOVL_Trim = 0;
int g_Fn_tOVL_post_S = 0;
int g_Fn_OSC_Pt = 0;
int g_Fn_Fosc_Pre_S = 0;
int g_Fn_Fosc_Trim_S = 0;
int g_Fn_Fosc_post_S = 0;
int g_Fn_ILIM_Pre = 0;
int g_Fn_ILIM_Trim = 0;
int g_Fn_ILIM = 0;
int g_Fn_CV_Pre = 0;
int g_Fn_ISvth_Pre_S = 0;
int g_Fn_CDC_Pre = 0;
int g_Fn_nDAC_Pt = 0;
int g_Fn_pDAC_Pt = 0;
int g_Fn_DofA_Pt = 0;
int g_Fn_IsDAC_Pt = 0;
int g_Fn_Gain_Pt = 0;
int g_Fn_CCoff_Pt = 0;
int g_Fn_IsCal_Pt = 0;
int g_Fn_ADC_Pt = 0;
int g_Fn_ADC_Final = 0;
int g_Fn_EEPROM_Write = 0;
int g_Fn_IzPost = 0;
int g_SoftStart = 0;
int g_Fn_Isvth3X_AR_ISSC = 0;
int g_Fn_VBP_Supply = 0;
int g_Fn_IBP_Supply = 0;
int g_Fn_IOV_IUV_OT = 0;
int g_Fn_FOSC_Ton_ARST = 0;
int g_Fn_FWPK = 0;
int g_Fn_SR_Delay_tREQinh = 0;
int g_Fn_Vesr = 0;
int g_Fn_SOA_SDS_TW50 = 0;
int g_Fn_Iout = 0;
int g_Fn_CV_nDAC_pDAC = 0;
int g_Fn_Vovp = 0;
int g_Fn_UVP = 0;
int g_Fn_VPK = 0;
int g_Fn_CDC_Final = 0;
int g_Fn_VBD_uVCC = 0;
int g_Fn_ADC_Linearity = 0;
int g_Fn_OSC_Final = 0;
int g_Fn_DofA_Final = 0;
int g_Fn_IsDAC_Final = 0;
int g_Fn_Gain_Final = 0;
int g_Fn_Ccoff_Final = 0;
int g_Fn_IsCal_Final = 0;
int g_Fn_DATT = 0;
int g_Fn_zLast = 0;

// Declare global variables //
// ---------------------------
// HL --added-----------------
int g_TrimRegister_P[80]     = {0};
int g_S_TrimRegister[80]     = {0};
int g_TrimRegisterTemp_P[80] = {0};
int g_S_TrimRegisterTemp[80] = {0};
int g_S_EEpromTemp[80] = {0};
int g_TrimBank[5]            = {0};

int	g_E0_start_bit = 0;
int	g_E2_start_bit = 16;
int	g_E4_start_bit = 32;
int	g_E6_start_bit = 48;
int	g_E8_start_bit = 64;

//----------------------------
int g_binary_array[30] = {0};
int g_Read_HiByte_Mem[30] = {0};
int g_Read_LoByte_Mem[30] = {0};
int g_ShadowRegister[112] = {0};
const int HEX = 0;
const int BIN = 1;
float g_begintime = 0;
float g_endtime = 0;
int g_Error_Flag = 0;
float g_Fosc_Sim_S = 0;
float g_Fosc_Sim_Chg_S = 0;
float g_CCoff_Pt_S = 0;
float g_IsDAC_Pt_S = 0;
float g_IsCal_Pt_S = 0;
float g_Gain_Pt_S = 0;
float g_DofA_Pt_S = 0;
float g_pDAC_Target_S = 0;
float g_pDAC_Pt_S = 0;
float g_nDAC_Target_S = 0;
float g_nDAC_Pt_S = 0;
float g_CCoff_Target_S = 0;
float g_CV_pt_S = 0;
float g_OSC_Pt_S = 0;
float g_ISvth3X_pt_S = 0;
float g_CDC_Target_S = 0;
float g_CV_Final_S = 0;
float g_CDC_Pt_S = 0;
float g_Framework_Rev = 0;
float g_IsDAC_final = 0;
float g_Gain_Final = 0;
bool g_DDD_Load_Finished = false;
float g_IsDAC_Sim_S = 0;
CMicroTimer g_mytimer; // Class used for measuring time intervals //
int g_PartFailed = 0;
int g_Save_Awav_TextDebug_ALL		= 0;
int g_Save_Awav_TextDebug_Dtemp	= 0;

int g_xChk_P[100] = {0};
float g_ILIM_S = 0;
float g_DDD_High = 0;
float g_DDD_Low = 0;
//float g_SoftStartTime = 0;
float g_ADC_Pt = 0;
float g_ADC_Final = 0;
float g_Voffset = 0.0;
float g_tOVP_S = 0;
int g_EEpt_ShadReg0 = 0;
int g_EEpt_ShadReg1 = 0;
int g_EEpt_ShadReg2 = 0;
int g_EEpt_ShadReg3 = 0;
int g_EEpt_ShadReg4 = 0;
int g_EEpt_ShadReg5 = 0;
int g_EEpt_ShadReg6 = 0;
int g_EEpt_ShadReg7 = 0;
int g_EEpt_ShadReg8 = 0;
int g_EEpt_ShadReg9 = 0;
int g_EEpt_ShadReg10 = 0;
int g_EEpt_ShadReg11 = 0;
int g_EEpt_ShadReg12 = 0;
int g_EEpt_ShadReg13 = 0;
int g_EEpt_ShadReg14 = 0;
int g_EEpt_ShadReg15 = 0;
int g_EEpt_ShadReg16 = 0;
int g_EEpt_ShadReg17 = 0;
int g_EEpt_ShadReg18 = 0;
int g_EEpt_ShadReg19 = 0;
int g_EEpt_ShadReg20 = 0;
int g_EEpt_ShadReg21 = 0;
int g_EEpt_ShadReg22 = 0;
int g_EEpt_ShadReg23 = 0;
int g_EEpt_ShadReg24 = 0;
int g_EEpt_ShadReg25 = 0;
int g_EEpt_ShadReg26 = 0;
int g_EEpt_ShadReg27 = 0;
int g_EEpt_ShadReg28 = 0;
int g_EEpt_ShadReg29 = 0;
int g_EEpt_ShadReg30 = 0;
int g_EEpt_ShadReg31 = 0;
int g_EEpt_ShadReg32 = 0;
int g_EEpt_ShadReg33 = 0;
int g_EEpt_ShadReg34 = 0;
int g_EEpt_ShadReg35 = 0;
int g_EEpt_ShadReg36 = 0;
int g_EEpt_ShadReg37 = 0;
int g_EEpt_ShadReg38 = 0;
int g_EEpt_ShadReg39 = 0;
int g_EEpt_ShadReg40 = 0;
int g_EEpt_ShadReg41 = 0;
int g_EEpt_ShadReg42 = 0;
int g_EEpt_ShadReg43 = 0;
int g_EEpt_ShadReg44 = 0;
int g_EEpt_ShadReg45 = 0;
int g_EEpt_ShadReg46 = 0;
int g_EEpt_ShadReg47 = 0;
int g_EEpt_ShadReg48 = 0;
int g_EEpt_ShadReg49 = 0;
int g_EEpt_ShadReg50 = 0;
int g_EEpt_ShadReg51 = 0;
int g_EEpt_ShadReg52 = 0;
int g_EEpt_ShadReg53 = 0;
int g_EEpt_ShadReg54 = 0;
int g_EEpt_ShadReg55 = 0;
int g_EEpt_ShadReg56 = 0;
int g_EEpt_ShadReg57 = 0;
int g_EEpt_ShadReg58 = 0;
int g_EEpt_ShadReg59 = 0;
int g_EEpt_ShadReg60 = 0;
int g_EEpt_ShadReg61 = 0;
int g_EEpt_ShadReg62 = 0;
int g_EEpt_ShadReg63 = 0;
int g_EEpt_ShadReg64 = 0;
int g_EEpt_ShadReg65 = 0;
int g_EEpt_ShadReg66 = 0;
int g_EEpt_ShadReg67 = 0;
int g_EEpt_ShadReg68 = 0;
int g_EEpt_ShadReg69 = 0;
int g_EEpt_ShadReg70 = 0;
int g_EEpt_ShadReg71 = 0;
int g_EEpt_ShadReg72 = 0;
int g_EEpt_ShadReg73 = 0;
int g_EEpt_ShadReg74 = 0;
int g_EEpt_ShadReg75 = 0;
int g_EEpt_ShadReg76 = 0;
int g_EEpt_ShadReg77 = 0;
int g_EEpt_ShadReg78 = 0;
int g_EEpt_ShadReg79 = 0;
int g_EEpt_ShadReg80 = 0;
int g_EEpt_ShadReg81 = 0;
int g_EEpt_ShadReg82 = 0;
int g_EEpt_ShadReg83 = 0;
int g_EEpt_ShadReg84 = 0;
int g_EEpt_ShadReg85 = 0;
int g_EEpt_ShadReg86 = 0;
int g_EEpt_ShadReg87 = 0;
int g_EEpt_ShadReg88 = 0;
int g_EEpt_ShadReg89 = 0;
int g_EEpt_ShadReg90 = 0;
int g_EEpt_ShadReg91 = 0;
int g_EEpt_ShadReg92 = 0;
int g_EEpt_ShadReg93 = 0;
int g_EEpt_ShadReg94 = 0;
int g_EEpt_ShadReg95 = 0;
int g_EEpt_ShadReg96 = 0;
int g_EEpt_ShadReg97 = 0;
int g_EEpt_ShadReg98 = 0;
int g_EEpt_ShadReg99 = 0;
int g_EEpt_ShadReg100 = 0;
int g_EEpt_ShadReg101 = 0;
int g_EEpt_ShadReg102 = 0;
int g_EEpt_ShadReg103 = 0;
int g_EEpt_ShadReg104 = 0;
int g_EEpt_ShadReg105 = 0;
int g_EEpt_ShadReg106 = 0;
int g_EEpt_ShadReg107 = 0;
int g_EEpt_ShadReg108 = 0;
int g_EEpt_ShadReg109 = 0;
int g_EEpt_ShadReg110 = 0;
int g_EEpt_ShadReg111 = 0;
int g_EE_ShadReg0 = 0;
int g_EE_ShadReg1 = 0;
int g_EE_ShadReg2 = 0;
int g_EE_ShadReg3 = 0;
int g_EE_ShadReg4 = 0;
int g_EE_ShadReg5 = 0;
int g_EE_ShadReg6 = 0;
int g_EE_ShadReg7 = 0;
int g_EE_ShadReg8 = 0;
int g_EE_ShadReg9 = 0;
int g_EE_ShadReg10 = 0;
int g_EE_ShadReg11 = 0;
int g_EE_ShadReg12 = 0;
int g_EE_ShadReg13 = 0;
int g_EE_ShadReg14 = 0;
int g_EE_ShadReg15 = 0;
int g_EE_ShadReg16 = 0;
int g_EE_ShadReg17 = 0;
int g_EE_ShadReg18 = 0;
int g_EE_ShadReg19 = 0;
int g_EE_ShadReg20 = 0;
int g_EE_ShadReg21 = 0;
int g_EE_ShadReg22 = 0;
int g_EE_ShadReg23 = 0;
int g_EE_ShadReg24 = 0;
int g_EE_ShadReg25 = 0;
int g_EE_ShadReg26 = 0;
int g_EE_ShadReg27 = 0;
int g_EE_ShadReg28 = 0;
int g_EE_ShadReg29 = 0;
int g_EE_ShadReg30 = 0;
int g_EE_ShadReg31 = 0;
int g_EE_ShadReg32 = 0;
int g_EE_ShadReg33 = 0;
int g_EE_ShadReg34 = 0;
int g_EE_ShadReg35 = 0;
int g_EE_ShadReg36 = 0;
int g_EE_ShadReg37 = 0;
int g_EE_ShadReg38 = 0;
int g_EE_ShadReg39 = 0;
int g_EE_ShadReg40 = 0;
int g_EE_ShadReg41 = 0;
int g_EE_ShadReg42 = 0;
int g_EE_ShadReg43 = 0;
int g_EE_ShadReg44 = 0;
int g_EE_ShadReg45 = 0;
int g_EE_ShadReg46 = 0;
int g_EE_ShadReg47 = 0;
int g_EE_ShadReg48 = 0;
int g_EE_ShadReg49 = 0;
int g_EE_ShadReg50 = 0;
int g_EE_ShadReg51 = 0;
int g_EE_ShadReg52 = 0;
int g_EE_ShadReg53 = 0;
int g_EE_ShadReg54 = 0;
int g_EE_ShadReg55 = 0;
int g_EE_ShadReg56 = 0;
int g_EE_ShadReg57 = 0;
int g_EE_ShadReg58 = 0;
int g_EE_ShadReg59 = 0;
int g_EE_ShadReg60 = 0;
int g_EE_ShadReg61 = 0;
int g_EE_ShadReg62 = 0;
int g_EE_ShadReg63 = 0;
int g_EE_ShadReg64 = 0;
int g_EE_ShadReg65 = 0;
int g_EE_ShadReg66 = 0;
int g_EE_ShadReg67 = 0;
int g_EE_ShadReg68 = 0;
int g_EE_ShadReg69 = 0;
int g_EE_ShadReg70 = 0;
int g_EE_ShadReg71 = 0;
int g_EE_ShadReg72 = 0;
int g_EE_ShadReg73 = 0;
int g_EE_ShadReg74 = 0;
int g_EE_ShadReg75 = 0;
int g_EE_ShadReg76 = 0;
int g_EE_ShadReg77 = 0;
int g_EE_ShadReg78 = 0;
int g_EE_ShadReg79 = 0;
int g_EE_ShadReg80 = 0;
int g_EE_ShadReg81 = 0;
int g_EE_ShadReg82 = 0;
int g_EE_ShadReg83 = 0;
int g_EE_ShadReg84 = 0;
int g_EE_ShadReg85 = 0;
int g_EE_ShadReg86 = 0;
int g_EE_ShadReg87 = 0;
int g_EE_ShadReg88 = 0;
int g_EE_ShadReg89 = 0;
int g_EE_ShadReg90 = 0;
int g_EE_ShadReg91 = 0;
int g_EE_ShadReg92 = 0;
int g_EE_ShadReg93 = 0;
int g_EE_ShadReg94 = 0;
int g_EE_ShadReg95 = 0;
int g_EE_ShadReg96 = 0;
int g_EE_ShadReg97 = 0;
int g_EE_ShadReg98 = 0;
int g_EE_ShadReg99 = 0;
int g_EE_ShadReg100 = 0;
int g_EE_ShadReg101 = 0;
int g_EE_ShadReg102 = 0;
int g_EE_ShadReg103 = 0;
int g_EE_ShadReg104 = 0;
int g_EE_ShadReg105 = 0;
int g_EE_ShadReg106 = 0;
int g_EE_ShadReg107 = 0;
int g_EE_ShadReg108 = 0;
int g_EE_ShadReg109 = 0;
int g_EE_ShadReg110 = 0;
int g_EE_ShadReg111 = 0;
int g_Bit63_Change_Flag = 0;
float g_ISVTH = 0;
float g_CCoff_final = 0;
int g_FirstPartPass = 0;
int g_HP_meter_cal_done = 0;
float g_ISbuff_Gain32 = 0;
float g_ISbuff_GainMid = 0;
float g_ISbuff_GainLow = 0;
float g_IsCal_final = 0;
float g_ENG1 = 0;
float g_ENG2 = 0;
float g_ENG3 = 0;
float g_ENG4 = 0;
float g_ENG5 = 0;
float g_ENG6 = 0;
float g_ENG7 = 0;
float g_ENG8 = 0;
float g_ENG9 = 0;
float g_ENG10 = 0;
int g_LimitSetChanged = 0;
float g_I2C_Pullup = 0;
float g_VBPP_P_S_FailFlag = 0;
float g_ILL_FW = 0;
float g_ILL_FB = 0;
float g_ILH_FB = 0;
float g_ILL_VO = 0;
float g_ILL_IS = 0;
float g_ILH_VBD = 0;
float g_ILL_VBD = 0;
float g_ILH_SDA = 0;
float g_ILL_SDA = 0;
float g_ILH_SCL = 0;
float g_ILL_SCL = 0;
int g_DDDwait = 0;
int g_DDDwait_b = 0;
float SetDebugFlow = 0;
STRING g_PrgName; // .prg name //
int g_LB_type = 0;
int g_CB_type = 0;
float g_R1_ohms = 0;
int g_Site = 0;
float g_InvSyn_Fall = 0;
float g_R1_current = 0.0001;
int g_Enable_ScanChain = 1; // DEBUG ONLY!!!  Be sure to enable for production. //
float g_BPP_Stress_Volt = 0;
float g_BPP_IS1_Pre = 0;
float g_BPP_IS1_Diff = 0;
float g_BPP_IS2_Pre = 0;
float g_BPP_IS2_Diff = 0;
float g_iLeak_V_Pre = 0;
float g_iLeak_V_Post = 0;
float g_iLeak_V_Delta = 0;
float g_BPS_IS1_Pre = 0;
float g_BPS_IS2_Pre = 0;
float g_DSM_Library_Version = 0;
float g_DSM_Firmware_Version = 0;
float g_GNDRes_Se = 0;
float g_GNDRes_Pri = 0;
float g_Inv_threshold = 0;
float g_FWmeasV = 0;
//float g_Vshunt_2mA_P_Final = 0;
ofstream DSM_vector_file_write;
uint32_t g_DSM_address;
uint32_t g_Last_DSM_Address;


//////// DDD start/stop variables //
//////int g_StartBit_start = 0;
//////int g_StartBit_stop = 0;
//////int g_StartBit_start_45kHz = 0;
//////int g_StartBit_stop_45kHz  = 0;
//////int g_StartBit_start_Force_SCL = 0;
//////int g_StartBit_stop_Force_SCL = 0;
//////int g_SlaveAddress_start = 0;
//////int g_SlaveAddress_stop = 0;
//////int g_SlaveAddress_start_45kHz = 0;
//////int g_SlaveAddress_stop_45kHz = 0;
//////int g_SlaveAddress_start_Force_SCL = 0;
//////int g_SlaveAddress_stop_Force_SCL = 0;
//////int g_WriteBit_start = 0;
//////int g_WriteBit_stop = 0;
//////int g_WriteBit_start_45kHz = 0;
//////int g_WriteBit_stop_45kHz = 0;
//////int g_WriteBit_start_Force_SCL = 0;
//////int g_WriteBit_stop_Force_SCL = 0;
//////int g_ReadBit_start = 0;
//////int g_ReadBit_stop = 0;
//////int g_Read_HiByte_start = 0;
//////int g_Read_HiByte_stop = 0;
//////int g_Read_LoByte_start = 0;
//////int g_Read_LoByte_stop = 0;
//////int g_SlaveAck_start = 0;
//////int g_SlaveAck_stop = 0;
//////int g_SlaveAck_start_45kHz = 0;
//////int g_SlaveAck_stop_45kHz = 0;
//////int g_SlaveAck_start_Force_SCL = 0;
//////int g_SlaveAck_stop_Force_SCL = 0;
//////int g_MasterAck_start = 0;
//////int g_MasterAck_stop = 0;
//////int g_MasterNack_start = 0;
//////int g_MasterNack_stop = 0;
//////int g_StopBit_start = 0;
//////int g_StopBit_stop = 0;
//////int g_StopBit_start_45kHz = 0;
//////int g_StopBit_stop_45kHz = 0;
//////int g_StopBit_start_Force_SCL = 0;
//////int g_StopBit_stop_Force_SCL = 0;
//////int g_RDADDR_start = 0;
//////int g_RDADDR_stop = 0;
//////int g_FWPK_start = 0;
//////int g_FWPK_stop = 0;
//////int g_VBEN_start = 0;
//////int g_VBEN_stop = 0;
//////int g_MINLD_start = 0;
//////int g_MINLD_stop = 0;
//////int g_VDIS_start = 0;
//////int g_VDIS_stop = 0;
//////int g_Self_Destruct_start = 0;
//////int g_Self_Destruct_stop = 0;
//////int g_Fast_VI_Command_start = 0;
//////int g_Fast_VI_Command_stop = 0;
//////int g_CVO_mode_start = 0; // Rev2 silicon //
//////int g_CVO_mode_stop = 0; // Rev2 silicon //
//////int g_CV_start = 0;
//////int g_CV_stop = 0;
//////int g_OVA_start = 0;
//////int g_OVA_stop = 0;
//////int g_UVA_start = 0;
//////int g_UVA_stop = 0;
//////int g_CDC_start = 0;
//////int g_CDC_stop = 0;
//////int g_CDC_start_45kHz = 0;
//////int g_CDC_stop_45kHz  = 0;
//////int g_CC_start = 0;
//////int g_CC_stop = 0;
//////int g_VPK_start = 0;
//////int g_VPK_stop = 0;
//////int g_OVL_start = 0;
//////int g_OVL_stop = 0;
//////int g_UVL_start = 0;
//////int g_UVL_stop = 0;
//////int g_CCSCL_start = 0;
//////int g_CCSCL_stop = 0;
//////int g_ISSC_start = 0;
//////int g_ISSC_stop = 0;
//////int g_UVL_Timer_start = 0;
//////int g_UVL_Timer_stop = 0;
//////int g_Watchdog_Timer_start = 0;
//////int g_Watchdog_Timer_stop = 0;
//////int g_CVO_response_start = 0; // Rev2 silicon //
//////int g_CVO_response_stop = 0; // Rev2 silicon //
//////int g_CVO_timer_start = 0; // Rev2 silicon //
//////int g_CVO_timer_stop = 0; // Rev2 silicon //
//////int g_Interrupt_Mask_start = 0; // Rev2 silicon //
//////int g_Interrupt_Mask_stop = 0; // Rev2 silicon //
//////int g_OTP_start = 0; // Rev2 silicon //
//////int g_OTP_stop = 0; // Rev2 silicon //
//////int g_fast_cc_offset_start; // WR_Byte, RevC silicon //
//////int g_fast_cc_offset_stop; // WR_Byte, RevC silicon //
//////int g_loop_speed_set1_start; // WR_Word, RevC silicon  //
//////int g_loop_speed_set1_stop; // WR_Word, RevC silicon  //
//////int g_loop_speed_set2_start; // WR_Word, RevC silicon  //
//////int g_loop_speed_set2_stop; // WR_Word, RevC silicon  //
//////int g_TM_CTRL_start = 0;
//////int g_TM_CTRL_stop = 0;
//////int g_TM_CTRL_start_Force_SCL = 0;
//////int g_TM_CTRL_stop_Force_SCL = 0;
//////int g_TM_SEL_start = 0;
//////int g_TM_SEL_stop = 0;
//////int g_TM_DAC_start = 0;
//////int g_TM_DAC_stop = 0;
//////int g_TM_ANA_start = 0; // Rev2 silicon //
//////int g_TM_ANA_stop = 0; // Rev2 silicon //
//////int g_EEP_CMD_start = 0;
//////int g_EEP_CMD_stop = 0;
//////int g_TM_EN_start = 0;
//////int g_TM_EN_stop = 0;
//////int g_TM_EN_start_Force_SCL = 0;
//////int g_TM_EN_stop_Force_SCL = 0;
//////int g_SREG0_start = 0;
//////int g_SREG0_stop = 0;
//////int g_SREG1_start = 0;
//////int g_SREG1_stop = 0;
//////int g_SREG2_start = 0;
//////int g_SREG2_stop = 0;
//////int g_SREG3_start = 0;
//////int g_SREG3_stop = 0;
//////int g_SREG4_start = 0;
//////int g_SREG4_stop = 0;
//////int g_SREG5_start = 0;
//////int g_SREG5_stop = 0;
//////int g_SREG6_start = 0;
//////int g_SREG6_stop = 0;
//////int g_READ0_start = 0;
//////int g_READ0_stop = 0;
//////int g_READ1_start = 0;
//////int g_READ1_stop = 0;
//////int g_READ2_start = 0;
//////int g_READ2_stop = 0;
//////int g_READ3_start = 0;
//////int g_READ3_stop = 0;
//////int g_READ4_start = 0;
//////int g_READ4_stop = 0;
//////int g_READ5_start = 0;
//////int g_READ5_stop = 0;
//////int g_READ6_start = 0;
//////int g_READ6_stop = 0;
//////int g_READ7_start = 0;
//////int g_READ7_stop = 0;
//////int g_READ8_start = 0;
//////int g_READ8_stop = 0;
//////int g_READ9_start = 0;
//////int g_READ9_stop = 0;
//////int g_READ10_start = 0;
//////int g_READ10_stop = 0;
//////int g_READ11_start = 0;
//////int g_READ11_stop = 0;
//////int g_READ12_start = 0;
//////int g_READ12_stop = 0;
//////int g_READ13_start = 0;
//////int g_READ13_stop = 0;
//////int g_READ14_start = 0;
//////int g_READ14_stop = 0;
//////int g_READ15_start = 0;
//////int g_READ15_stop = 0;
//////int g_READ16_start = 0;
//////int g_READ16_stop = 0;
//////int g_READ17_start = 0;
//////int g_READ17_stop = 0;
//////int g_READ18_start = 0;
//////int g_READ18_stop = 0;
//////int g_READ19_start = 0;
//////int g_READ19_stop = 0;
//////int g_READ20_start = 0;
//////int g_READ20_stop = 0;
//////int g_READ21_start = 0;
//////int g_READ21_stop = 0;
//////int g_READ22_start = 0;
//////int g_READ22_stop = 0;
//////int g_READ40_start = 0; // Rev2 silicon //
//////int g_READ40_stop = 0; // Rev2 silicon //
//////int g_READ41_start = 0; // Rev2 silicon //
//////int g_READ41_stop = 0; // Rev2 silicon //
//////int g_READ42_start = 0; // Rev2 silicon //
//////int g_READ42_stop = 0; // Rev2 silicon //
//////int g_READ43_start = 0; // Rev2 silicon //
//////int g_READ43_stop = 0; // Rev2 silicon //
//////int g_READ44_start = 0; // Rev2 silicon //
//////int g_READ44_stop = 0; // Rev2 silicon //
//////int g_READ45_start = 0; // Rev2 silicon //
//////int g_READ45_stop = 0; // Rev2 silicon //
//////int g_READ46_start = 0; // Rev2 silicon //
//////int g_READ46_stop = 0; // Rev2 silicon //
//////int g_READ47_start = 0; // Rev2 silicon //
//////int g_READ47_stop = 0; // Rev2 silicon //
//////int g_READ56_start = 0; // Rev2 silicon //
//////int g_READ56_stop = 0; // Rev2 silicon //
//////int g_READ57_start = 0; // Rev2 silicon //
//////int g_READ57_stop = 0; // Rev2 silicon //
//////int g_READ58_start = 0; // Rev2 silicon //
//////int g_READ58_stop = 0; // Rev2 silicon //
//////int g_READ59_start = 0; // Rev2 silicon //
//////int g_READ59_stop = 0; // Rev2 silicon //
//////int g_READ60_start = 0; // Rev2 silicon //
//////int g_READ60_stop = 0; // Rev2 silicon //
//////int g_READ61_start = 0; // Rev2 silicon //
//////int g_READ61_stop = 0; // Rev2 silicon //
//////int g_READ62_start = 0; // Rev2 silicon //
//////int g_READ62_stop = 0; // Rev2 silicon //
//////int g_SDA_SCL_Low_start = 0;
//////int g_SDA_SCL_Low_stop = 0;
//////int g_SDA_hiz_SCL_low_start = 0;
//////int g_SDA_hiz_SCL_low_stop = 0;
//////int g_SDA_hiz_SCL_hiz_start = 0;
//////int g_SDA_hiz_SCL_hiz_stop = 0;
//int g_BPShigh_start = 0;
//int g_BPShigh_stop = 0;
//int g_All_HIZ_start = 0;
//int g_All_HIZ_stop = 0;
//int g_SDA_SCL_HIZ_start = 0;
//int g_SDA_SCL_HIZ_stop = 0;

// DSM start/stop variables, Word //
uint32_t g_RDADDR_READ0_start_DSM = 0;
uint32_t g_RDADDR_READ0_stop_DSM = 0;
uint32_t g_RDADDR_READ1_start_DSM = 0;
uint32_t g_RDADDR_READ1_stop_DSM = 0;
uint32_t g_RDADDR_READ2_start_DSM = 0;
uint32_t g_RDADDR_READ2_stop_DSM = 0;
uint32_t g_RDADDR_READ3_start_DSM = 0;
uint32_t g_RDADDR_READ3_stop_DSM = 0;
uint32_t g_RDADDR_READ4_start_DSM = 0;
uint32_t g_RDADDR_READ4_stop_DSM = 0;
uint32_t g_RDADDR_READ5_start_DSM = 0;
uint32_t g_RDADDR_READ5_stop_DSM = 0;
uint32_t g_RDADDR_READ6_start_DSM = 0;
uint32_t g_RDADDR_READ6_stop_DSM = 0;
uint32_t g_RDADDR_READ7_start_DSM = 0;
uint32_t g_RDADDR_READ7_stop_DSM = 0;
uint32_t g_RDADDR_READ8_start_DSM = 0;
uint32_t g_RDADDR_READ8_stop_DSM = 0;
uint32_t g_RDADDR_READ9_start_DSM = 0;
uint32_t g_RDADDR_READ9_stop_DSM = 0;
uint32_t g_RDADDR_READ10_start_DSM = 0;
uint32_t g_RDADDR_READ10_stop_DSM = 0;
uint32_t g_RDADDR_READ11_start_DSM = 0;
uint32_t g_RDADDR_READ11_stop_DSM = 0;
uint32_t g_RDADDR_READ12_start_DSM = 0;
uint32_t g_RDADDR_READ12_stop_DSM = 0;
uint32_t g_RDADDR_READ13_start_DSM = 0;
uint32_t g_RDADDR_READ13_stop_DSM = 0;
uint32_t g_RDADDR_READ14_start_DSM = 0;
uint32_t g_RDADDR_READ14_stop_DSM = 0;
uint32_t g_RDADDR_READ56_start_DSM = 0;
uint32_t g_RDADDR_READ56_stop_DSM = 0;
uint32_t g_RDADDR_READ57_start_DSM = 0;
uint32_t g_RDADDR_READ57_stop_DSM = 0;
uint32_t g_RDADDR_READ58_start_DSM = 0;
uint32_t g_RDADDR_READ58_stop_DSM = 0;
uint32_t g_RDADDR_READ59_start_DSM = 0;
uint32_t g_RDADDR_READ59_stop_DSM = 0;
uint32_t g_RDADDR_READ60_start_DSM = 0;
uint32_t g_RDADDR_READ60_stop_DSM = 0;
uint32_t g_RDADDR_READ61_start_DSM = 0;
uint32_t g_RDADDR_READ61_stop_DSM = 0;
uint32_t g_RDADDR_READ62_start_DSM = 0;
uint32_t g_RDADDR_READ62_stop_DSM = 0;
uint32_t g_TM_ANA_0x0000_start_DSM = 0;
uint32_t g_TM_ANA_0x0000_stop_DSM = 0;
uint32_t g_TM_ANA_0x0120_start_DSM = 0;
uint32_t g_TM_ANA_0x0120_stop_DSM = 0;
uint32_t g_TM_ANA_0x0130_start_DSM = 0;
uint32_t g_TM_ANA_0x0130_stop_DSM = 0;
uint32_t g_TM_ANA_0x0134_start_DSM = 0;
uint32_t g_TM_ANA_0x0134_stop_DSM = 0;
uint32_t g_TM_ANA_0x0138_start_DSM = 0;
uint32_t g_TM_ANA_0x0138_stop_DSM = 0;
uint32_t g_TM_ANA_0x013C_start_DSM = 0;
uint32_t g_TM_ANA_0x013C_stop_DSM = 0;
uint32_t g_TM_ANA_0x0934_start_DSM = 0;
uint32_t g_TM_ANA_0x0934_stop_DSM = 0;
uint32_t g_TM_ANA_SR_Enable_start_DSM = 0;
uint32_t g_TM_ANA_SR_Enable_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0000_start_DSM = 0;
uint32_t g_TM_CTRL_0x0000_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0001_start_DSM = 0;
uint32_t g_TM_CTRL_0x0001_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0004_start_DSM = 0;
uint32_t g_TM_CTRL_0x0004_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0020_start_DSM = 0;
uint32_t g_TM_CTRL_0x0020_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0820_start_DSM = 0;
uint32_t g_TM_CTRL_0x0820_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0828_start_DSM = 0;
uint32_t g_TM_CTRL_0x0828_stop_DSM = 0;
uint32_t g_TM_CTRL_0x0A22_start_DSM = 0;
uint32_t g_TM_CTRL_0x0A22_stop_DSM = 0;
uint32_t g_TM_CTRL_0x1800_start_DSM = 0;
uint32_t g_TM_CTRL_0x1800_stop_DSM = 0;
uint32_t g_TM_CTRL_ScanMode_Enter_start_DSM = 0;
uint32_t g_TM_CTRL_ScanMode_Enter_stop_DSM = 0;
uint32_t g_TM_EN_TestMode_Password_start_DSM = 0;
uint32_t g_TM_EN_TestMode_Password_stop_DSM = 0;
uint32_t g_TM_EN_TestMode_Enter_start_DSM = 0;
uint32_t g_TM_EN_TestMode_Enter_stop_DSM = 0;
uint32_t g_TM_EN_TestMode_Exit_start_DSM = 0;
uint32_t g_TM_EN_TestMode_Exit_stop_DSM = 0;
uint32_t g_TM_SEL_26_start_DSM = 0;
uint32_t g_TM_SEL_26_stop_DSM = 0;
uint32_t g_TM_SEL_29_start_DSM = 0;
uint32_t g_TM_SEL_29_stop_DSM = 0;
uint32_t g_TM_SEL_0x0000_start_DSM = 0;
uint32_t g_TM_SEL_0x0000_stop_DSM = 0;
uint32_t g_TM_SEL_0x0001_start_DSM = 0;
uint32_t g_TM_SEL_0x0001_stop_DSM = 0;
uint32_t g_TM_SEL_0x0004_start_DSM = 0;
uint32_t g_TM_SEL_0x0004_stop_DSM = 0;
uint32_t g_TM_SEL_0x0006_start_DSM = 0;
uint32_t g_TM_SEL_0x0006_stop_DSM = 0;
uint32_t g_TM_SEL_0x0008_start_DSM = 0;
uint32_t g_TM_SEL_0x0008_stop_DSM = 0;
uint32_t g_TM_SEL_0x000A_start_DSM = 0;
uint32_t g_TM_SEL_0x000A_stop_DSM = 0;
uint32_t g_TM_SEL_0x0016_start_DSM = 0;
uint32_t g_TM_SEL_0x0016_stop_DSM = 0;
uint32_t g_TM_SEL_0x0018_start_DSM = 0;
uint32_t g_TM_SEL_0x0018_stop_DSM = 0;
uint32_t g_TM_SEL_0x0020_start_DSM = 0;
uint32_t g_TM_SEL_0x0020_stop_DSM = 0;
uint32_t g_TM_SEL_0x0024_start_DSM = 0;
uint32_t g_TM_SEL_0x0024_stop_DSM = 0;
uint32_t g_TM_SEL_0x0026_start_DSM = 0;
uint32_t g_TM_SEL_0x0026_stop_DSM = 0;
uint32_t g_CC_reg_384_start_DSM = 0;
uint32_t g_CC_reg_384_stop_DSM = 0;
uint32_t g_CC_reg_32941_start_DSM = 0;
uint32_t g_CC_reg_32941_stop_DSM = 0;
uint32_t g_CV_reg_556_start_DSM = 0;
uint32_t g_CV_reg_556_stop_DSM = 0;
uint32_t g_CV_reg_756_start_DSM = 0;
uint32_t g_CV_reg_756_stop_DSM = 0;
uint32_t g_CV_reg_1032_start_DSM = 0;
uint32_t g_CV_reg_1032_stop_DSM = 0;
uint32_t g_CV_reg_1052_start_DSM = 0;
uint32_t g_CV_reg_1052_stop_DSM = 0;
uint32_t g_CV_reg_1112_start_DSM = 0;
uint32_t g_CV_reg_1112_stop_DSM = 0;
uint32_t g_CV_reg_1220_start_DSM = 0;
uint32_t g_CV_reg_1220_stop_DSM = 0;
uint32_t g_CV_reg_1796_start_DSM = 0;
uint32_t g_CV_reg_1796_stop_DSM = 0;
uint32_t g_CV_reg_1896_start_DSM = 0;
uint32_t g_CV_reg_1896_stop_DSM = 0;
uint32_t g_CV_reg_2124_start_DSM = 0;
uint32_t g_CV_reg_2124_stop_DSM = 0;
uint32_t g_CV_reg_4148_start_DSM = 0;
uint32_t g_CV_reg_4148_stop_DSM = 0;
uint32_t g_CV_reg_33552_start_DSM = 0;
uint32_t g_CV_reg_33552_stop_DSM = 0;
uint32_t g_CV_reg_33636_start_DSM = 0;
uint32_t g_CV_reg_33636_stop_DSM = 0;
uint32_t g_CV_reg_33648_start_DSM = 0;
uint32_t g_CV_reg_33648_stop_DSM = 0;
uint32_t g_CV_reg_33651_start_DSM = 0;
uint32_t g_CV_reg_33651_stop_DSM = 0;
uint32_t g_CV_reg_33772_start_DSM = 0;
uint32_t g_CV_reg_33772_stop_DSM = 0;
uint32_t g_CV_reg_33778_start_DSM = 0;
uint32_t g_CV_reg_33778_stop_DSM = 0;
uint32_t g_CV_reg_33780_start_DSM = 0;
uint32_t g_CV_reg_33780_stop_DSM = 0;
uint32_t g_CV_reg_33790_start_DSM = 0;
uint32_t g_CV_reg_33790_stop_DSM = 0;
uint32_t g_CV_reg_34196_start_DSM = 0;
uint32_t g_CV_reg_34196_stop_DSM = 0;
uint32_t g_CV_reg_34336_start_DSM = 0;
uint32_t g_CV_reg_34336_stop_DSM = 0;
uint32_t g_CV_reg_34356_start_DSM = 0;
uint32_t g_CV_reg_34356_stop_DSM = 0;
uint32_t g_CV_reg_36816_start_DSM = 0;
uint32_t g_CV_reg_36816_stop_DSM = 0;
uint32_t g_CV_reg_37600_start_DSM = 0;
uint32_t g_CV_reg_37600_stop_DSM = 0;
uint32_t g_UVA_318_start_DSM = 0;
uint32_t g_UVA_318_stop_DSM = 0;
uint32_t g_UVA_368_start_DSM = 0;
uint32_t g_UVA_368_stop_DSM = 0;
uint32_t g_UVA_396_start_DSM = 0;
uint32_t g_UVA_396_stop_DSM = 0;
uint32_t g_UVA_32838_start_DSM = 0;
uint32_t g_UVA_32838_stop_DSM = 0;
uint32_t g_UVA_32926_start_DSM = 0;
uint32_t g_UVA_32926_stop_DSM = 0;
uint32_t g_UVA_32976_start_DSM = 0;
uint32_t g_UVA_32976_stop_DSM = 0;
uint32_t g_OVA_278_start_DSM = 0;
uint32_t g_OVA_278_stop_DSM = 0;
uint32_t g_OVA_368_start_DSM = 0;
uint32_t g_OVA_368_stop_DSM = 0;
uint32_t g_OVA_378_start_DSM = 0;
uint32_t g_OVA_378_stop_DSM = 0;
uint32_t g_OVA_456_start_DSM = 0;
uint32_t g_OVA_456_stop_DSM = 0;
uint32_t g_OVA_32830_start_DSM = 0;
uint32_t g_OVA_32830_stop_DSM = 0;
uint32_t g_OVA_32868_start_DSM = 0;
uint32_t g_OVA_32868_stop_DSM = 0;
uint32_t g_OVA_32959_start_DSM = 0;
uint32_t g_OVA_32959_stop_DSM = 0;
uint32_t g_VPK_reg_278_start_DSM = 0;
uint32_t g_VPK_reg_278_stop_DSM = 0;
uint32_t g_VPK_reg_363_start_DSM = 0;
uint32_t g_VPK_reg_363_stop_DSM = 0;
uint32_t g_VPK_reg_456_start_DSM = 0;
uint32_t g_VPK_reg_456_stop_DSM = 0;
uint32_t g_VPK_reg_32868_start_DSM = 0;
uint32_t g_VPK_reg_32868_stop_DSM = 0;
uint32_t g_VPK_reg_32949_start_DSM = 0;
uint32_t g_VPK_reg_32949_stop_DSM = 0;

// DSM start/stop variables, Byte //
uint32_t g_CCSCL_0x00_start_DSM = 0;
uint32_t g_CCSCL_0x00_stop_DSM = 0;
uint32_t g_CDC_0_start_DSM = 0;
uint32_t g_CDC_0_stop_DSM = 0;
uint32_t g_CDC_1_start_DSM = 0;
uint32_t g_CDC_1_stop_DSM = 0;
uint32_t g_CDC_2_start_DSM = 0;
uint32_t g_CDC_2_stop_DSM = 0;
uint32_t g_CDC_4_start_DSM = 0;
uint32_t g_CDC_4_stop_DSM = 0;
uint32_t g_CDC_8_start_DSM = 0;
uint32_t g_CDC_8_stop_DSM = 0;
uint32_t g_CDC_11_start_DSM = 0;
uint32_t g_CDC_11_stop_DSM = 0;
uint32_t g_CDC_12_start_DSM = 0;
uint32_t g_CDC_12_stop_DSM = 0;
uint32_t g_CVO_mode_0x00_start_DSM = 0;
uint32_t g_CVO_mode_0x00_stop_DSM = 0;
uint32_t g_CVO_mode_0x01_start_DSM = 0;
uint32_t g_CVO_mode_0x01_stop_DSM = 0;
uint32_t g_EEP_CMD_0x00_start_DSM = 0;
uint32_t g_EEP_CMD_0x00_stop_DSM = 0;
uint32_t g_EEP_CMD_0x01_start_DSM = 0;
uint32_t g_EEP_CMD_0x01_stop_DSM = 0;
uint32_t g_EEP_CMD_0x03_start_DSM = 0;
uint32_t g_EEP_CMD_0x03_stop_DSM = 0;
uint32_t g_fast_cc_offset_32_start_DSM = 0;
uint32_t g_fast_cc_offset_32_stop_DSM = 0;
uint32_t g_fast_cc_offset_0x80_start_DSM = 0;
uint32_t g_fast_cc_offset_0x80_stop_DSM = 0;
uint32_t g_Fast_VI_Command_0x01_start_DSM = 0;
uint32_t g_Fast_VI_Command_0x01_stop_DSM = 0;
uint32_t g_FWPK_reg_0x00_start_DSM = 0;
uint32_t g_FWPK_reg_0x00_stop_DSM = 0;
uint32_t g_FWPK_reg_0x01_start_DSM = 0;
uint32_t g_FWPK_reg_0x01_stop_DSM = 0;
uint32_t g_Interrupt_Mask_0x00_start_DSM = 0;
uint32_t g_Interrupt_Mask_0x00_stop_DSM = 0;
uint32_t g_Interrupt_Mask_0x01_start_DSM = 0;
uint32_t g_Interrupt_Mask_0x01_stop_DSM = 0;
uint32_t g_MINLD_0x00_start_DSM = 0;
uint32_t g_MINLD_0x00_stop_DSM = 0;
uint32_t g_MINLD_0x01_start_DSM = 0;
uint32_t g_MINLD_0x01_stop_DSM = 0;
uint32_t g_OVL_0x01_start_DSM = 0;
uint32_t g_OVL_0x01_stop_DSM = 0;
uint32_t g_OVL_0x02_start_DSM = 0;
uint32_t g_OVL_0x02_stop_DSM = 0;
uint32_t g_TM_DAC_0x00_start_DSM = 0;
uint32_t g_TM_DAC_0x00_stop_DSM = 0;
uint32_t g_TM_DAC_0x40_start_DSM = 0;
uint32_t g_TM_DAC_0x40_stop_DSM = 0;
uint32_t g_TM_DAC_0x80_start_DSM = 0;
uint32_t g_TM_DAC_0x80_stop_DSM = 0;
uint32_t g_UVL_Timer_0x00_start_DSM = 0;
uint32_t g_UVL_Timer_0x00_stop_DSM = 0;
uint32_t g_UVL_Timer_0x01_start_DSM = 0;
uint32_t g_UVL_Timer_0x01_stop_DSM = 0;
uint32_t g_UVL_Timer_0x02_start_DSM = 0;
uint32_t g_UVL_Timer_0x02_stop_DSM = 0;
uint32_t g_UVL_Timer_0x03_start_DSM = 0;
uint32_t g_UVL_Timer_0x03_stop_DSM = 0;
uint32_t g_VBEN_0x80_start_DSM = 0;
uint32_t g_VBEN_0x80_stop_DSM = 0;
uint32_t g_VBEN_0x83_start_DSM = 0;
uint32_t g_VBEN_0x83_stop_DSM = 0;
uint32_t g_VDIS_131_start_DSM = 0;
uint32_t g_VDIS_131_stop_DSM = 0;
uint32_t g_VDIS_0x83_start_DSM = 0;
uint32_t g_VDIS_0x83_stop_DSM = 0;
uint32_t g_VDIS_0x8C_start_DSM = 0;
uint32_t g_VDIS_0x8C_stop_DSM = 0;
uint32_t g_Watchdog_Timer_0x00_start_DSM = 0;
uint32_t g_Watchdog_Timer_0x00_stop_DSM = 0;
uint32_t g_Watchdog_Timer_0x01_start_DSM = 0;
uint32_t g_Watchdog_Timer_0x01_stop_DSM = 0;

//DDD pattern for Scan Chain
string Scan_Pattern;
char **Store_Pattern;
char **Compare_Pattern;
bool DEBUG_Pattern_output = FALSE;
int g_Fail_address;
int g_row_load = 0;
int g_row_compare = 0;
int g_pattern_size = 0;
double row_length = 0;
bool g_Wrong_Scan_Pattern = FALSE;

// DSM MODULE CODE //
bool g_No_DSM_USB = FALSE;
bool g_DSM = TRUE;
uint32_t ScanChain_AddrStart = 0;
uint32_t ScanChain_AddrEnd = 0;
// DSM MODULE CODE //


	STRING ProgramName, Prg_Name;

void user_init(void)
{	//  As TEST.EXE loads, before program name etc.
	g_pid = _getpid();  //do not remove
	PiUserInit( );

	GetProgramName(ProgramName);
	Prg_Name = ProgramName;

	char dummy[40];
	STRING mystring;
	STRING ProgramName;

	GetLimitSetName( mystring );

	istrstream theLimitSetName( (char*)((const char*)mystring) );

	theLimitSetName >> g_DevName  >> g_OperCode >> dummy >> dummy;// >> TestTemp;

//	if ( strstr(Prg_Name,"Golden"))
	if ( strstr(g_DevName,"GU"))
		GoldenUnit = true;

	//////DSM_init(0);
	//////int ver = DSM_version(); //1.5
	//////int firmware = DSM_firmware(DSM_CONTEXT); //1.5
	//////printf("ver = %i, firmware = %i\n",ver,firmware);

	//////

	//////	
	//////DSM_set_vector_clock_freq(DSM_CONTEXT, 1200);//Freq in kHZ
	//////DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);
	//////DSM_set_drv_comp(DSM_CONTEXT,DRV_COMP_ALL,	2.5); 
	//////DSM_set_high_level(DSM_CONTEXT,		ALL_CH, 5);	//DOUT high levels						     
	//////DSM_set_low_level(DSM_CONTEXT,		ALL_CH, 0);
	//////DSM_set_voltage_ref(DSM_CONTEXT,	ALL_CH, 2.0);
	//////DSM_set_voltage_I2C(DSM_CONTEXT,			3.3);
	//////DSM_enable_outputs(DSM_CONTEXT, NONE_CH);       //Disable outputs
	//////DSM_enable_open_drain(DSM_CONTEXT, NONE_CH);    //Disable Open Drain
	//////DSM_set_no_delay(DSM_CONTEXT);                  //Set 0 second delay	

	//////RelayController relays = RelayController(5,//num drivers
	//////							500000,//hz
	//////							1/*1*/,//pinswap
	//////							1);// din edge
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_load(void)
{	//  After the user selects the program, before user_start_lot().
	g_Voffset = 0;
	GetProgramName(g_PrgName); // Returns the .prg name. //
	board_ptr_init();
	board_hardware_init();

	// Declare Variables //
	char dummy[40];
	STRING mystring;
//	STRING ProgramName;

	// Define I2C register //
	Define_I2C_Registers();

	// Decide which functions will be executed. All the little boxes in .prg should be set 
	// to green, even if they will not be executed.  This function is used to 
	// determine which functions will be run.  The purpose is to keep control of which 
	// functions are executed under source code control. //
	FunctionsToExecute();

	// Get limit set //
	GetLimitSetName( mystring );
	istrstream theLimitSetName( (char*)((const char*)mystring) );
	theLimitSetName >> Part_ID_LimitSet  >> g_OperCode >> dummy >> dummy;

	// Test Program Rev //
	PrgRev = "0.46cxL"; // This should be identical to PiSetProgramName() function call. //
	FamilyName = "LYT8"; // This should be identical to PiSetProgramName() function call. //

	// Modify AutoCorrReport file to share one golden unit for multiple devices of same family. //
	if (!strnicmp(Part_ID_LimitSet, "INN3365", 7) || 
		!strnicmp(Part_ID_LimitSet, "INN3375", 7))
	{
		if(	Pi::AutoCorrReport::Verify(FamilyName,PrgRev,"INN3375"))
		{
			printf("GU is ok  \n");
			Pi::AutoCorrReport::Modify(FamilyName, PrgRev, Part_ID_LimitSet); //Modify the "Current Test Program" field in the AutoCorrReport.txt. //
		}
		else
			printf("GU is NOT ok  \n");
	}
	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || 
		!strnicmp(Part_ID_LimitSet, "INN3376", 7))
	{
		if(	Pi::AutoCorrReport::Verify(FamilyName,PrgRev,"INN3376"))
		{
			printf("GU is ok  \n");
			Pi::AutoCorrReport::Modify(FamilyName, PrgRev, Part_ID_LimitSet); //Modify the "Current Test Program" field in the AutoCorrReport.txt. //
		}
		else
			printf("GU is NOT ok  \n");
	}
	if (!strnicmp(Part_ID_LimitSet, "INN3377", 7) || 
		!strnicmp(Part_ID_LimitSet, "SC1750", 6))
	{
		if(	Pi::AutoCorrReport::Verify(FamilyName,PrgRev,"INN3377"))
		{
			printf("GU is ok  \n");
			Pi::AutoCorrReport::Modify(FamilyName, PrgRev, Part_ID_LimitSet); //Modify the "Current Test Program" field in the AutoCorrReport.txt. //
		}
		else
			printf("GU is NOT ok  \n");
	}
	if (!strnicmp(Part_ID_LimitSet, "INN3368", 7) ||
		!strnicmp(Part_ID_LimitSet, "INN3367", 7) ||
		!strnicmp(Part_ID_LimitSet, "SC1738", 6))
	{
		if(	Pi::AutoCorrReport::Verify(FamilyName,PrgRev,"INN3368"))
		{
			printf("GU is ok  \n");
			Pi::AutoCorrReport::Modify(FamilyName, PrgRev, Part_ID_LimitSet); //Modify the "Current Test Program" field in the AutoCorrReport.txt. //
			
		}
		else
			printf("GU is NOT ok  \n");
	}


	// Enable golden units //
	PiEnableGoldenUnit();

	// Test Program Rev //
	PiSetProgramName("LYT8 0.46cxL");

	// Setup //
	PiUserLoad( );


	//Make sure both FamilyName and ProgramRev are less than or equal to 10 characters
	int FamilyName_char_count	=0,
		PrgRev_char_count		=0, 
		i						=0;

	for(i=0; FamilyName[i] !=0; i++)
		FamilyName_char_count++;

	for(i=0; PrgRev[i] !=0; i++)
		PrgRev_char_count++;

	//10 character is the maximum number of characters allow for FamilyName and ProgramRev
	if(FamilyName_char_count >10 || PrgRev_char_count>10)
		DisplayErrorMessage("ProgramName either have PrgRev > 10 character or FamilyName > 10 characters.  Not able to upload data to YMS");

	//mode_change();
	STRING load_message = "DDD load";
	SendCommStatus(load_message);
	DDD_init();


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// XP Gage digitizer Setup STARTS //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Gage Initialization
	load_message = "Gage Init start";
	SendCommStatus(load_message);
	delay(100);
	dig_ok = Gage_loadtime_setup();	//call this only once

	Gage_cal_table_setup_xp();
	Gage_init();			//can be called multiple times
	delay(1);

    // Gage Calibration (the following function call will calibrate current range)
	i32Status = CsDo(hSystem, ACTION_CALIB);	//Gage will calibrate for current range
	load_message = "Gage Init end";
	SendCommStatus(load_message);
	delay(100);

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// XP Gage digitizer Setup ENDS //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


	//HL added this section just for Binno DSM initialization.
	if(1)
	{
		load_message = "DSM init start";
		SendCommStatus(load_message);
		delay(100);

		int ret = -1;
		float dret = -1;
		cout << endl << endl << "Start DSM Loading."<<endl;                                 
		//ret = DSM_init(DSM_CONTEXT); //only call at start of lot
		//dret = DSM_version(); //1.5
		//dret = DSM_firmware(DSM_CONTEXT); //1.5


		DSM_init(0);
		int ver = DSM_version(); //1.5
		int firmware = DSM_firmware(DSM_CONTEXT); //1.5
		printf("ver = %i, firmware = %i\n",ver,firmware);

		

			
		DSM_set_vector_clock_freq(DSM_CONTEXT, 1200);//Freq in kHZ
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);
		DSM_set_drv_comp(DSM_CONTEXT,DRV_COMP_ALL,	2.5); 
		DSM_set_high_level(DSM_CONTEXT,		ALL_CH, 5);	//DOUT high levels						     
		DSM_set_low_level(DSM_CONTEXT,		ALL_CH, 0);
		DSM_set_voltage_ref(DSM_CONTEXT,	ALL_CH, 2.0);
		DSM_set_voltage_I2C(DSM_CONTEXT,			3.3);
		DSM_enable_outputs(DSM_CONTEXT, NONE_CH);       //Disable outputs
		DSM_enable_open_drain(DSM_CONTEXT, NONE_CH);    //Disable Open Drain
		DSM_set_no_delay(DSM_CONTEXT);                  //Set 0 second delay	

		RelayController relays = RelayController(5,//num drivers
									500000,//hz
									1/*1*/,//pinswap
									1);// din edge

		load_message = "DSM init end";
		SendCommStatus(load_message);
		delay(100);

	}
	//if (0)//g_Enable_ScanChain)//HL disabled for Binno.
	//{
	//	// DSM MODULE CODE //
	//	if(g_DSM)
	//	{
	//		// Declare Variables //
	//		int i = 0;
	//		//ofstream DSM_vector_file_write;
	//		ifstream DSM_vector_file_read;
	//		uint32_t ScanChainVector_Qty= 0;
	//		string File_line;
	//		
	//		// BEGIN: Code to deal with path name changing- use relative path. //
	//		char test_vector_logic_path[2048];
	//		char DSM_vector_file_path[2048];
	//		int PathLength = 0;
	//		GetModuleFileNameA(GetModuleHandle(_T("InnoVI.dll")), test_vector_logic_path, 2048);
	//		PathLength = strlen(test_vector_logic_path);
	//		test_vector_logic_path[PathLength-16] = NULL;
	//		// END: Code to deal with path name changing- use relative path. //

	//		// Create a copy of the scan chain vector file from design (test_vector_logic.vec) so 
	//		// that it remains untouched. The new file will be called DSM_vector_file.vec.  We will append all
	//		// the I2C vectors into this file, so all the DSM module vectors reside in a single file, i.e. both 
	//		// the scan chain vectors as well as the I2C vectors will be in same file. //
	//		strcpy(DSM_vector_file_path, test_vector_logic_path); // Make a copy of the path //
	//		if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	//		{
	//			strcat(test_vector_logic_path, "Vectors\\test_vector_logic_v3.vec");
	//		}
	//		if (g_SiliconRev_Sec == 5) // Rev C silicon //
	//		{
	//			strcat(test_vector_logic_path, "Vectors\\test_vector_logic.vec");
	//		}
	//		//strcat(test_vector_logic_path, "Vectors\\test_vector_logic.vec"); // Add rest of path name. This the is full path to the scan chain vector file from design. //
	//		strcat(DSM_vector_file_path, "Vectors\\DSM_vector_file.vec"); // Create new file path for DSM_vector_file.vec //
	//		//CopyFile("c:/dog.txt", "c:/dog2.txt", TRUE);
	//		CopyFile(test_vector_logic_path, DSM_vector_file_path, FALSE); // Create a copy of the original scan chain vector file from design (test_vector_logic.vec) and call it DSM_vector_file.vec. //

	//		// Find out how many vectors are in the scan chain. //
	//		DSM_vector_file_read.open(DSM_vector_file_path);
	//		ScanChainVector_Qty = 0;
	//		if(DSM_vector_file_read.is_open())
	//		{
	//			//cout << endl;
	//			while(!DSM_vector_file_read.eof())
	//			{
	//				getline(DSM_vector_file_read, File_line);
	//				//cout << File_line << endl;
	//				ScanChainVector_Qty++;
	//			}
	//		}
	//		ScanChainVector_Qty--;
	//		DSM_vector_file_read.close();


	//		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//		// LOAD DSM I2C PATTERNS //		
	//		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//		// Open vector file to write data.  Open in append mode. //
	//		//DSM_vector_file_write.open(DSM_vector_file_path);
	//		DSM_vector_file_write.open(DSM_vector_file_path, fstream::app);

	//		// Keep track of DSM memory address //
	//		// Starting address //
	//		g_DSM_address = ScanChainVector_Qty + 1;
	//		
	//		// DSM I2C patterns //
	//		// Word //
	//		g_RDADDR_READ0_start_DSM = g_DSM_address;
	//		g_RDADDR_READ0_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ0);
	//		g_RDADDR_READ1_start_DSM = g_DSM_address;
	//		g_RDADDR_READ1_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ1);
	//		g_RDADDR_READ2_start_DSM = g_DSM_address;
	//		g_RDADDR_READ2_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ2);
	//		g_RDADDR_READ3_start_DSM = g_DSM_address;
	//		g_RDADDR_READ3_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ3);
	//		g_RDADDR_READ4_start_DSM = g_DSM_address;
	//		g_RDADDR_READ4_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ4);
	//		g_RDADDR_READ5_start_DSM = g_DSM_address;
	//		g_RDADDR_READ5_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ5);
	//		g_RDADDR_READ6_start_DSM = g_DSM_address;
	//		g_RDADDR_READ6_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ6);
	//		g_RDADDR_READ7_start_DSM = g_DSM_address;
	//		g_RDADDR_READ7_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ7);
	//		g_RDADDR_READ8_start_DSM = g_DSM_address;
	//		g_RDADDR_READ8_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ8);
	//		g_RDADDR_READ9_start_DSM = g_DSM_address;
	//		g_RDADDR_READ9_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ9);
	//		g_RDADDR_READ10_start_DSM = g_DSM_address;
	//		g_RDADDR_READ10_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ10);
	//		g_RDADDR_READ11_start_DSM = g_DSM_address;
	//		g_RDADDR_READ11_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ11);
	//		g_RDADDR_READ12_start_DSM = g_DSM_address;
	//		g_RDADDR_READ12_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ12);
	//		g_RDADDR_READ13_start_DSM = g_DSM_address;
	//		g_RDADDR_READ13_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ13);
	//		g_RDADDR_READ14_start_DSM = g_DSM_address;
	//		g_RDADDR_READ14_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ14);
	//		g_RDADDR_READ56_start_DSM = g_DSM_address;
	//		g_RDADDR_READ56_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ56);
	//		g_RDADDR_READ57_start_DSM = g_DSM_address;
	//		g_RDADDR_READ57_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ57);
	//		g_RDADDR_READ58_start_DSM = g_DSM_address;
	//		g_RDADDR_READ58_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ58);
	//		g_RDADDR_READ59_start_DSM = g_DSM_address;
	//		g_RDADDR_READ59_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ59);
	//		g_RDADDR_READ60_start_DSM = g_DSM_address;
	//		g_RDADDR_READ60_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ60);
	//		g_RDADDR_READ61_start_DSM = g_DSM_address;
	//		g_RDADDR_READ61_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ61);
	//		g_RDADDR_READ62_start_DSM = g_DSM_address;
	//		g_RDADDR_READ62_stop_DSM = DSM_Load_Write_Word(g_RDADDR, g_READ62);
	//		g_TM_ANA_0x0000_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0000_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0000);
	//		g_TM_ANA_0x0120_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0120_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0120);
	//		g_TM_ANA_0x0130_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0130_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0130);
	//		g_TM_ANA_0x0134_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0134_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0134);
	//		g_TM_ANA_0x0138_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0138_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0138);
	//		g_TM_ANA_0x013C_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x013C_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x013C);
	//		g_TM_ANA_0x0934_start_DSM = g_DSM_address;
	//		g_TM_ANA_0x0934_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, 0x0934);
	//		g_TM_ANA_SR_Enable_start_DSM = g_DSM_address;
	//		g_TM_ANA_SR_Enable_stop_DSM = DSM_Load_Write_Word(g_TM_ANA, g_SR_Enable);
	//		g_TM_CTRL_0x0000_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0000_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0000);
	//		g_TM_CTRL_0x0001_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0001_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0001);
	//		g_TM_CTRL_0x0004_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0004_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0004);
	//		g_TM_CTRL_0x0020_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0020_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0020);
	//		g_TM_CTRL_0x0820_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0820_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0820);
	//		g_TM_CTRL_0x0828_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0828_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0828);
	//		g_TM_CTRL_0x0A22_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x0A22_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x0A22);
	//		g_TM_CTRL_0x1800_start_DSM = g_DSM_address;
	//		g_TM_CTRL_0x1800_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, 0x1800);
	//		g_TM_CTRL_ScanMode_Enter_start_DSM = g_DSM_address;
	//		g_TM_CTRL_ScanMode_Enter_stop_DSM = DSM_Load_Write_Word(g_TM_CTRL, g_ScanMode_Enter);
	//		g_TM_EN_TestMode_Password_start_DSM = g_DSM_address;
	//		g_TM_EN_TestMode_Password_stop_DSM = DSM_Load_Write_Word(g_TM_EN, g_TestMode_Password);
	//		g_TM_EN_TestMode_Enter_start_DSM = g_DSM_address;
	//		g_TM_EN_TestMode_Enter_stop_DSM = DSM_Load_Write_Word(g_TM_EN, g_TestMode_Enter);
	//		g_TM_EN_TestMode_Exit_start_DSM = g_DSM_address;
	//		g_TM_EN_TestMode_Exit_stop_DSM = DSM_Load_Write_Word(g_TM_EN, g_TestMode_Exit);
	//		g_TM_SEL_26_start_DSM = g_DSM_address;
	//		g_TM_SEL_26_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 26);
	//		g_TM_SEL_29_start_DSM = g_DSM_address;
	//		g_TM_SEL_29_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 29);
	//		g_TM_SEL_0x0000_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0000_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0000);
	//		g_TM_SEL_0x0001_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0001_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0001);
	//		g_TM_SEL_0x0004_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0004_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0004);
	//		g_TM_SEL_0x0006_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0006_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0006);
	//		g_TM_SEL_0x0008_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0008_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0008);
	//		g_TM_SEL_0x000A_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x000A_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x000A);
	//		g_TM_SEL_0x0016_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0016_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0016);
	//		g_TM_SEL_0x0018_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0018_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0018);
	//		g_TM_SEL_0x0020_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0020_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0020);
	//		g_TM_SEL_0x0024_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0024_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0024);
	//		g_TM_SEL_0x0026_start_DSM = g_DSM_address;
	//		g_TM_SEL_0x0026_stop_DSM = DSM_Load_Write_Word(g_TM_SEL, 0x0026);
	//		g_CC_reg_384_start_DSM = g_DSM_address;
	//		g_CC_reg_384_stop_DSM = DSM_Load_Write_Word(g_CC_reg, 384);
	//		g_CC_reg_32941_start_DSM = g_DSM_address;
	//		g_CC_reg_32941_stop_DSM = DSM_Load_Write_Word(g_CC_reg, 32941);
	//		g_CV_reg_556_start_DSM = g_DSM_address;
	//		g_CV_reg_556_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 556);
	//		g_CV_reg_756_start_DSM = g_DSM_address;
	//		g_CV_reg_756_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 756);
	//		g_CV_reg_1032_start_DSM = g_DSM_address;
	//		g_CV_reg_1032_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1032);
	//		g_CV_reg_1052_start_DSM = g_DSM_address;
	//		g_CV_reg_1052_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1052);
	//		g_CV_reg_1112_start_DSM = g_DSM_address;
	//		g_CV_reg_1112_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1112);
	//		g_CV_reg_1220_start_DSM = g_DSM_address;
	//		g_CV_reg_1220_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1220);
	//		g_CV_reg_1796_start_DSM = g_DSM_address;
	//		g_CV_reg_1796_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1796);
	//		g_CV_reg_1896_start_DSM = g_DSM_address;
	//		g_CV_reg_1896_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 1896);
	//		g_CV_reg_2124_start_DSM = g_DSM_address;
	//		g_CV_reg_2124_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 2124);
	//		g_CV_reg_4148_start_DSM = g_DSM_address;
	//		g_CV_reg_4148_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 4148);
	//		g_CV_reg_33552_start_DSM = g_DSM_address;
	//		g_CV_reg_33552_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33552);
	//		g_CV_reg_33636_start_DSM = g_DSM_address;
	//		g_CV_reg_33636_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33636);
	//		g_CV_reg_33648_start_DSM = g_DSM_address;
	//		g_CV_reg_33648_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33648);
	//		g_CV_reg_33651_start_DSM = g_DSM_address;
	//		g_CV_reg_33651_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33651);
	//		g_CV_reg_33772_start_DSM = g_DSM_address;
	//		g_CV_reg_33772_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33772);
	//		g_CV_reg_33778_start_DSM = g_DSM_address;
	//		g_CV_reg_33778_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33778);
	//		g_CV_reg_33780_start_DSM = g_DSM_address;
	//		g_CV_reg_33780_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33780);
	//		g_CV_reg_33790_start_DSM = g_DSM_address;
	//		g_CV_reg_33790_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 33790);
	//		g_CV_reg_34196_start_DSM = g_DSM_address;
	//		g_CV_reg_34196_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 34196);
	//		g_CV_reg_34336_start_DSM = g_DSM_address;
	//		g_CV_reg_34336_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 34336);
	//		g_CV_reg_34356_start_DSM = g_DSM_address;
	//		g_CV_reg_34356_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 34356);
	//		g_CV_reg_36816_start_DSM = g_DSM_address;
	//		g_CV_reg_36816_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 36816);
	//		g_CV_reg_37600_start_DSM = g_DSM_address;
	//		g_CV_reg_37600_stop_DSM = DSM_Load_Write_Word(g_CV_reg, 37600);
	//		g_UVA_318_start_DSM = g_DSM_address;
	//		g_UVA_318_stop_DSM = DSM_Load_Write_Word(g_UVA, 318);
	//		g_UVA_368_start_DSM = g_DSM_address;
	//		g_UVA_368_stop_DSM = DSM_Load_Write_Word(g_UVA, 368);
	//		g_UVA_396_start_DSM = g_DSM_address;
	//		g_UVA_396_stop_DSM = DSM_Load_Write_Word(g_UVA, 396);
	//		g_UVA_32838_start_DSM = g_DSM_address;
	//		g_UVA_32838_stop_DSM = DSM_Load_Write_Word(g_UVA, 32838);
	//		g_UVA_32926_start_DSM = g_DSM_address;
	//		g_UVA_32926_stop_DSM = DSM_Load_Write_Word(g_UVA, 32926);
	//		g_UVA_32976_start_DSM = g_DSM_address;
	//		g_UVA_32976_stop_DSM = DSM_Load_Write_Word(g_UVA, 32976);
	//		g_OVA_278_start_DSM = g_DSM_address;
	//		g_OVA_278_stop_DSM = DSM_Load_Write_Word(g_OVA, 278);
	//		g_OVA_368_start_DSM = g_DSM_address;
	//		g_OVA_368_stop_DSM = DSM_Load_Write_Word(g_OVA, 368);
	//		g_OVA_378_start_DSM = g_DSM_address;
	//		g_OVA_378_stop_DSM = DSM_Load_Write_Word(g_OVA, 378);
	//		g_OVA_456_start_DSM = g_DSM_address;
	//		g_OVA_456_stop_DSM = DSM_Load_Write_Word(g_OVA, 456);
	//		g_OVA_32830_start_DSM = g_DSM_address;
	//		g_OVA_32830_stop_DSM = DSM_Load_Write_Word(g_OVA, 32830);
	//		g_OVA_32868_start_DSM = g_DSM_address;
	//		g_OVA_32868_stop_DSM = DSM_Load_Write_Word(g_OVA, 32868);
	//		g_OVA_32959_start_DSM = g_DSM_address;
	//		g_OVA_32959_stop_DSM = DSM_Load_Write_Word(g_OVA, 32959);
	//		g_VPK_reg_278_start_DSM = g_DSM_address;
	//		g_VPK_reg_278_stop_DSM = DSM_Load_Write_Word(g_VPK_reg, 278);
	//		g_VPK_reg_363_start_DSM = g_DSM_address;
	//		g_VPK_reg_363_stop_DSM = DSM_Load_Write_Word(g_VPK_reg, 363);
	//		g_VPK_reg_456_start_DSM = g_DSM_address;
	//		g_VPK_reg_456_stop_DSM = DSM_Load_Write_Word(g_VPK_reg, 456);
	//		g_VPK_reg_32868_start_DSM = g_DSM_address;
	//		g_VPK_reg_32868_stop_DSM = DSM_Load_Write_Word(g_VPK_reg, 32868);
	//		g_VPK_reg_32949_start_DSM = g_DSM_address;
	//		g_VPK_reg_32949_stop_DSM = DSM_Load_Write_Word(g_VPK_reg, 32949);


	//		// DSM I2C patterns //
	//		// Byte //
	//		g_CCSCL_0x00_start_DSM = g_DSM_address;
	//		g_CCSCL_0x00_stop_DSM = DSM_Load_Write_Byte(g_CCSCL, 0x00);
	//		g_CDC_0_start_DSM = g_DSM_address;
	//		g_CDC_0_stop_DSM = DSM_Load_Write_Byte(g_CDC, 0);
	//		g_CDC_1_start_DSM = g_DSM_address;
	//		g_CDC_1_stop_DSM = DSM_Load_Write_Byte(g_CDC, 1);
	//		g_CDC_2_start_DSM = g_DSM_address;
	//		g_CDC_2_stop_DSM = DSM_Load_Write_Byte(g_CDC, 2);
	//		g_CDC_4_start_DSM = g_DSM_address;
	//		g_CDC_4_stop_DSM = DSM_Load_Write_Byte(g_CDC, 4);
	//		g_CDC_8_start_DSM = g_DSM_address;
	//		g_CDC_8_stop_DSM = DSM_Load_Write_Byte(g_CDC, 8);
	//		g_CDC_11_start_DSM = g_DSM_address;
	//		g_CDC_11_stop_DSM = DSM_Load_Write_Byte(g_CDC, 11);
	//		g_CDC_12_start_DSM = g_DSM_address;
	//		g_CDC_12_stop_DSM = DSM_Load_Write_Byte(g_CDC, 12);
	//		g_CVO_mode_0x00_start_DSM = g_DSM_address;
	//		g_CVO_mode_0x00_stop_DSM = DSM_Load_Write_Byte(g_CVO_mode, 0x00);
	//		g_CVO_mode_0x01_start_DSM = g_DSM_address;
	//		g_CVO_mode_0x01_stop_DSM = DSM_Load_Write_Byte(g_CVO_mode, 0x01);
	//		g_EEP_CMD_0x00_start_DSM = g_DSM_address;
	//		g_EEP_CMD_0x00_stop_DSM = DSM_Load_Write_Byte(g_EEP_CMD, 0x00);
	//		g_EEP_CMD_0x01_start_DSM = g_DSM_address;
	//		g_EEP_CMD_0x01_stop_DSM = DSM_Load_Write_Byte(g_EEP_CMD, 0x01);
	//		g_EEP_CMD_0x03_start_DSM = g_DSM_address;
	//		g_EEP_CMD_0x03_stop_DSM = DSM_Load_Write_Byte(g_EEP_CMD, 0x03);
	//		g_fast_cc_offset_32_start_DSM = g_DSM_address;
	//		g_fast_cc_offset_32_stop_DSM = DSM_Load_Write_Byte(g_fast_cc_offset, 32);
	//		g_fast_cc_offset_0x80_start_DSM = g_DSM_address;
	//		g_fast_cc_offset_0x80_stop_DSM = DSM_Load_Write_Byte(g_fast_cc_offset, 0x80);
	//		g_Fast_VI_Command_0x01_start_DSM = g_DSM_address;
	//		g_Fast_VI_Command_0x01_stop_DSM = DSM_Load_Write_Byte(g_Fast_VI_Command, 0x01);
	//		g_FWPK_reg_0x00_start_DSM = g_DSM_address;
	//		g_FWPK_reg_0x00_stop_DSM = DSM_Load_Write_Byte(g_FWPK_reg, 0x00);
	//		g_FWPK_reg_0x01_start_DSM = g_DSM_address;
	//		g_FWPK_reg_0x01_stop_DSM = DSM_Load_Write_Byte(g_FWPK_reg, 0x01);
	//		g_Interrupt_Mask_0x00_start_DSM = g_DSM_address;
	//		g_Interrupt_Mask_0x00_stop_DSM = DSM_Load_Write_Byte(g_Interrupt_Mask, 0x00);
	//		g_Interrupt_Mask_0x01_start_DSM = g_DSM_address;
	//		g_Interrupt_Mask_0x01_stop_DSM = DSM_Load_Write_Byte(g_Interrupt_Mask, 0x01);
	//		g_MINLD_0x00_start_DSM = g_DSM_address;
	//		g_MINLD_0x00_stop_DSM = DSM_Load_Write_Byte(g_MINLD, 0x00);
	//		g_MINLD_0x01_start_DSM = g_DSM_address;
	//		g_MINLD_0x01_stop_DSM = DSM_Load_Write_Byte(g_MINLD, 0x01);
	//		g_OVL_0x01_start_DSM = g_DSM_address;
	//		g_OVL_0x01_stop_DSM = DSM_Load_Write_Byte(g_OVL, 0x01);
	//		g_OVL_0x02_start_DSM = g_DSM_address;
	//		g_OVL_0x02_stop_DSM = DSM_Load_Write_Byte(g_OVL, 0x02);
	//		g_TM_DAC_0x00_start_DSM = g_DSM_address;
	//		g_TM_DAC_0x00_stop_DSM = DSM_Load_Write_Byte(g_TM_DAC, 0x00);
	//		g_TM_DAC_0x40_start_DSM = g_DSM_address;
	//		g_TM_DAC_0x40_stop_DSM = DSM_Load_Write_Byte(g_TM_DAC, 0x40);
	//		g_TM_DAC_0x80_start_DSM = g_DSM_address;
	//		g_TM_DAC_0x80_stop_DSM = DSM_Load_Write_Byte(g_TM_DAC, 0x80);
	//		g_UVL_Timer_0x00_start_DSM = g_DSM_address;
	//		g_UVL_Timer_0x00_stop_DSM = DSM_Load_Write_Byte(g_UVL_Timer, 0x00);
	//		g_UVL_Timer_0x01_start_DSM = g_DSM_address;
	//		g_UVL_Timer_0x01_stop_DSM = DSM_Load_Write_Byte(g_UVL_Timer, 0x01);
	//		g_UVL_Timer_0x02_start_DSM = g_DSM_address;
	//		g_UVL_Timer_0x02_stop_DSM = DSM_Load_Write_Byte(g_UVL_Timer, 0x02);
	//		g_UVL_Timer_0x03_start_DSM = g_DSM_address;
	//		g_UVL_Timer_0x03_stop_DSM = DSM_Load_Write_Byte(g_UVL_Timer, 0x03);
	//		g_VBEN_0x80_start_DSM = g_DSM_address;
	//		g_VBEN_0x80_stop_DSM = DSM_Load_Write_Byte(g_VBEN, 0x80);
	//		g_VBEN_0x83_start_DSM = g_DSM_address;;'/
	//		g_VBEN_0x83_stop_DSM = DSM_Load_Write_Byte(g_VBEN, 0x83);
	//		g_VDIS_131_start_DSM = g_DSM_address;
	//		g_VDIS_131_stop_DSM = DSM_Load_Write_Byte(g_VDIS, 131);
	//		g_VDIS_0x83_start_DSM = g_DSM_address;
	//		g_VDIS_0x83_stop_DSM = DSM_Load_Write_Byte(g_VDIS, 0x83);
	//		g_VDIS_0x8C_start_DSM = g_DSM_address;
	//		g_VDIS_0x8C_stop_DSM = DSM_Load_Write_Byte(g_VDIS, 0x8C);
	//		g_Watchdog_Timer_0x00_start_DSM = g_DSM_address;
	//		g_Watchdog_Timer_0x00_stop_DSM = DSM_Load_Write_Byte(g_Watchdog_Timer, 0x00);
	//		g_Watchdog_Timer_0x01_start_DSM = g_DSM_address;
	//		g_Watchdog_Timer_0x01_stop_DSM = DSM_Load_Write_Byte(g_Watchdog_Timer, 0x01);


	//		// Ending address //
	//		g_Last_DSM_Address = g_DSM_address - 1;
	//		DSM_vector_file_write.close();
	//				
	//		//+++++++++++++++++++++++DSM SW++++++++++++++++++++++++++ //
	//		int ret = -1;
	//		float dret = -1;
	//		cout << endl << endl << "Start DSM Loading."<<endl;                                 
	//		ret = DSM_init(DSM_CONTEXT); //only call at start of lot
	//		dret = DSM_version(); //1.5
	//		dret = DSM_firmware(DSM_CONTEXT); //1.5
	//		ret = DSM_set_vector_clock_freq(DSM_CONTEXT, 15000);//Freq in kHZ
	//		ret = DSM_set_drv_comp(DSM_CONTEXT,DRV_COMP_ALL, 2.5); 
	//		ret = DSM_set_high_level(DSM_CONTEXT, ALL_CH, 3.3);						     
	//		ret = DSM_set_low_level(DSM_CONTEXT, ALL_CH, 0);
	//		ret = DSM_set_voltage_ref(DSM_CONTEXT, ALL_CH, 2.5);
	//		ret = DSM_set_voltage_I2C(DSM_CONTEXT, 3.3);
	//		ret = DSM_enable_outputs(DSM_CONTEXT, NONE_CH);       //Disable outputs
	//		ret = DSM_enable_open_drain(DSM_CONTEXT, NONE_CH);    //Disable Open Drain
	//		ret = DSM_set_no_delay(DSM_CONTEXT);            //Set 0 second delay	
	//		DSM_set_file_column_position(0,2,1,3,3,4,6,7); //InnoVI File order 
	//		//ScanChain_AddrEnd = DSM_load_file(DSM_CONTEXT, "C:\\visualATE\\Asl_71\\Users\\Engineering\\InnoVI_Rev0.232_2018_0320\\InnoVI\\Programs\\test_vector_logic.txt",ScanChain_AddrStart);
	//		//if (g_SiliconRev_Sec == 4) // Rev B3 silicon //
	//		//{
	//		//	strcat ( test_vector_logic_path, "Vectors\\test_vector_logic_v3.vec" );
	//		//}
	//		//if (g_SiliconRev_Sec == 5) // Rev C silicon //
	//		//{
	//		//	strcat ( test_vector_logic_path, "Vectors\\test_vector_logic.vec" );
	//		//}
	//		//ScanChain_AddrEnd = DSM_load_file(DSM_CONTEXT, test_vector_logic_path, ScanChain_AddrStart);
	//		DSM_load_file(DSM_CONTEXT, DSM_vector_file_path, ScanChain_AddrStart);
	//		ScanChain_AddrEnd = ScanChainVector_Qty; // Found previously //
	//		if(ScanChain_AddrEnd == 0)
	//		{
	//			printf("\n ERROR! - vector file not found");
	//			g_Wrong_Scan_Pattern = TRUE;
	//		}
	//		else
	//		{
	//			ret = DSM_flash_erase(DSM_CONTEXT);
	//			//ret = DSM_commit_flash(DSM_CONTEXT, ScanChain_AddrStart, (ScanChain_AddrEnd ));
	//			ret = DSM_commit_flash(DSM_CONTEXT, ScanChain_AddrStart, g_Last_DSM_Address);
	//			cout << endl << endl << "Done DSM loading successfully."<<endl; 
	//		}
	//		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//	}
	//	// DSM MODULE CODE //
	//}

	load_message = "Load Complete";
	SendCommStatus(load_message);
	delay(100);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_start_lot(void)
{ //  After Limit selection and LotID is entered or if a New Lot is started manually.

	// Reset limit change variable here. //
	g_LimitSetChanged = 0;

	// Reset g_FirstPart variable here. //
	g_FirstPart = 1;

	// Get connection to HP meter ready.  HP meter used to calibrate the 20X buffer. //
	if (g_comm == NULL) { scan_for_meter(&g_comm, 2);} 
	g_comm->setup(COMM_PORT_2, 9600);
	g_comm->meter_reset();
	wait.delay_10_us(200);
	//g_comm->set_meter_config(METER_VOLTS_DC, METER_1_V, METER_SLOW_RATE);
	g_comm->set_meter_config(METER_VOLTS_DC, METER_100_MILLI_V, METER_SLOW_RATE);
	wait.delay_10_us(2000); //Fast CPU may need this delay

	PiUserStartLot( );
	g_Voffset = 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_wait_sot(void)
{	//  Obsolete and is not called.
	PiUserWaitSot( );
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_start_test(void)
{	//  After SOT, before 1st function.
	PiUserStartTest( );
	pv3_4->drive_off();
	delay(1);
	pv3_4->charge_on();				// Charge up PV3 capacitor bank early to save test time


	// No longer needed, spare resources //
	//ovi_3->disconnect(5);
	//ovi_1->disconnect(5);
	//ovi_1->disconnect(7);

	// Setup MUX //
	mux_14->close_relay(MUX_2_GND);
	mux_14->close_relay(MUX_BANK_1_2);
	mux_14->close_relay(MUX_BANK_3_4);
	mux_14->close_relay(MUX_4_GND);
	mux_14->close_relay(MUX_BANK_5_6);
	mux_14->close_relay(MUX_6_GND);
	mux_14->close_relay(MUX_7_GND);
	mux_14->close_relay(MUX_8_GND);

	mux_20->close_relay(MUX_2_GND);
	mux_20->close_relay(MUX_4_GND);
	mux_20->close_relay(MUX_6_GND);
	mux_20->close_relay(MUX_7_GND);
	mux_20->close_relay(MUX_8_GND);
	mux_20->close_relay(MUX_BANK_1_2);
	mux_20->close_relay(MUX_BANK_3_4);
	mux_20->close_relay(MUX_BANK_5_6);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_before_binning(void)
{	//  Before binning device.
	if (!PiGetAnyFailStatus())
	{
			int func[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69};  // define list of required test functions by number
			size_t n = sizeof(func) / sizeof(int);
			//PiSetRequiredFunctions(n, func,FALSE);
			PiSetRequiredFunctions(n, func);
			//PiSetRequiredFunctions(n, func, TRUE);
	}
	PiUserBeforeBinning();
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_end_test(void)
{	//  After binning device.
	PiUserEndTest( );

	// Delete HP meter handle.  HP meter used to calibrate the 20X buffer.
	// Delete meter handle. //

	// Only calibrate for the first passing part in the lot.  Calibration only needs to be performed once at beginning of lot. //
	if (g_PartFailed == 0)
	{
		g_FirstPartPass = 1;
	}
	if (g_FirstPartPass == 1 && g_HP_meter_cal_done == 0)
	{
		if (g_comm != NULL) 
		{
			delete g_comm;
			g_comm = NULL;
		}
		g_HP_meter_cal_done = 1;
	}
	
	// Be sure everything is powered down if no continue on fail //
	if (0)//g_PartFailed) HL disabled for Binno.
	{
		// Open all relays //
		Initialize_Relays();

		// Initialize Instruments //
		Initialize_Instruments();

		//Gage_init();

		//ddd_7->init();

		//ddd_7->ddd_connect_drivers();

		ddd_7->ddd_set_clock_period(Dclk_period);
		ddd_7->ddd_set_voltage_ref(DDD_Vref);

//		FB_ovi->connect(FB_ch);
//		VPIN_ovi->connect(VPIN_ch);

		//Open_relay(MUX_BANK_3_4);
		//Open_relay(MUX_4_GND);
		//Open_relay(MUX_BANK_5_6);
		//Open_relay(MUX_6_GND);
		//Open_relay(MUX_7_GND);
		//Open_relay(MUX_8_GND);

		/*
		ovi_1->init();
		ovi_3->init();
		pv3_4->init();
		tmu_6->init();
		ddd_7->init();
		dvi_9->init();
		dvi_11->init();
		dvi_13->init();
		mux_14->init();
		hvs_15->init();
		mux_20->init();
		dvi_21->init();
		*/

		wait.delay_10_us(300); // Wait for relays //
	}

	// DDD memory on TMT118 was getting erased periodically.  Suspect faulty DDD board.  Not a problem on any 
	// other tester. When this occurs then every part afterward will start failing.  Only solution found is to 
	// reload DDD memory. VBPP_P_S_Init-S test is the first failing test if this occurs so use this failure 
	// as a flag to reload DDD memory. //
	//if (g_VBPP_P_S_FailFlag > 0.5)
	//	DDD_init();

	// All the little boxes in .prg should be set to green, even if they will not 
	// be executed.  If the total number of functions executed is not 67 then abort 
	// all testing and provide a message box. The purpose is to keep control of 
	//which functions are executed under source code control. //
	if (g_PartFailed == 0)	// Only for passing part. //	
	{
		if (0)//gFuncNum != 69)
		{
			//AbortTest = true;
			g_Wrong_Number_Of_Functions = true;
			//DisplayErrorMessage("All the functions in the .prg must be set to green.");
			MessageBox(NULL, "All the functions in the .prg should have been green.  You must exit and restart Visual ATE.", "Error", MB_OK|MB_TOPMOST);
			//wait.delay_10_us(1000000); // 10 second delay // 
		}
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_next_device(void)
{	//  After displaying test results, before looking for SOT.
	PiUserNextDevice( );
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_end_lot(void)
{	//  After last EOT in a lot or if a New Lot is started manually.
//	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0,	RANGE_10_V);	// OVI_1_4	
	ovi_1->set_voltage(4, 0.0,	RANGE_10_V);	// OVI_1_4	
	pv3_4->charge_off();		// Discharge PV3 capacitor bank at end lot

	if (1)//g_Enable_ScanChain) //HL enabled for DSM closing for Binno.
	{
		// DSM MODULE CODE //
		DSM_close(DSM_CONTEXT); //only call at end of lot
		// DSM MODULE CODE //
	}

	PiUserEndLot( );
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_exit(void)
{	//  On program exit.

//{ASL_CREATE BEGIN USER_EXIT_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END USER_EXIT_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive changes to this code.
//ASL_CREATE END USER_EXIT_FROM_LIST_PROPERTIES}
	/* =========== XP Gage Digitizer ============= */
	PiUserExit( );
	CsFreeSystem(hSystem); 	//Free Gage software handle (prevents crash when Visual Studio debugger started)	
	free(Store_Pattern);
	free(Compare_Pattern);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_F12(void)
{	//  User hit F12.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_dut_power_off(void)
{	//  Dut power off occured.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void user_dut_power_on(void)
{	//  Dut power on occured.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//{ASL_CREATE BEGIN SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive changes to this code.
//ASL_CREATE END SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


//********************************************************************************
//***********  Start: DSM SPI for Relay Controller  ******************************
//********************************************************************************

	//******************************
	//*** DSM_SPI Control Relays ***
	//******************************
	int version;
	int firmware;

	int drivers;

	uint8_t SPI_out[8];
	uint8_t SPI_in[8];

	uint8_t* tracker = NULL;


	RelayController::RelayController(int num_modules, int hz, int pinswap, int din_edge) {
		drivers = num_modules;
		
		version = DSM_version(); 
		firmware = DSM_firmware(0); 
		
		DSM_setup_SPI2(0,
						hz, //clk rate in hz
						1, //must be in master mode
						pinswap, //
						din_edge); //Data clk'd in on rising/falling edge of clk
	}



	// Relay status will be automatically updated.
	void RelayController::track_relay_states(uint8_t* states) {
		tracker = states;
	}

	// Relay status will be written into "states" when function is called.
	void RelayController::get_relay_states(uint8_t* states) {
		for(int i = 0; i < drivers; i++) {
			states[i] = SPI_out[i];
		}
	}


	// Writes to DSM SPI2
	// Returns 0 on success.
	int RelayController::write_spi() {
		if(tracker != NULL) 
		{
			for(int i = 0; i < drivers; i++) {
				tracker[i] = SPI_out[i];
			}
		};
		return DSM_comms_SPI2(0, drivers, SPI_out, SPI_in);
	}

	int RelayController::close_relay_spi(int drv, int bit) {
		//Change specfied bit to 1.
		SPI_out[drv - 1] = SPI_out[drv - 1] | 1 << bit;
		return write_spi();
	}

	int RelayController::open_relay_spi(int drv, int bit) {
		//Change specfied bit to 0.
		SPI_out[drv - 1] = SPI_out[drv - 1] & ~(1 << bit);
		return write_spi();
	}

	int RelayController::open_all_relays_spi() {
		for(int i = 0; i < drivers; i++) {
			SPI_out[i] = 0;
		}
		return write_spi();
	}

	RelayController relays(0,0,0,0);



	////////******************************************
	////////*** Binno Control Relays using DSM_SPI ***
	////////******************************************
	///////*#include <map>

	//////using namespace std;

	//////map<int, pair<int,int> > control_map;
	//////RelayController relays(0,0,0,0);*/

	////////int BinnoRelayController::init() {
	////////	// Bank 1
	////////	control_map[K1_IS_SPI_TB]  = pair<int,int>(1, 0);//
	////////	control_map[K2_IS_SPI_IB]  = pair<int,int>(1, 1);
	////////	control_map[K3_IS_SPI_IB]  = pair<int,int>(1, 2);
	////////	control_map[K4_IS_SPI_IB]  = pair<int,int>(1, 3);
	////////	control_map[K5_IS_SPI_IB]  = pair<int,int>(1, 4);
	////////	control_map[K6_IS_SPI_IB]  = pair<int,int>(1, 5);
	////////	control_map[K1_SDA_SPI_TB] = pair<int,int>(1, 6);
	////////	control_map[K1_SCL_SPI_TB] = pair<int,int>(1, 7);

	////////	// Bank 2
	////////	control_map[K1_HBP_SPI_RB]  = pair<int,int>(2 ,0);
	////////	control_map[K1_FB_SPI_TB]   = pair<int,int>(2 ,1);
	////////	control_map[K2_FB_SPI_TB]   = pair<int,int>(2 ,2);
	////////	control_map[K1_HSG_SPI_RB]  = pair<int,int>(2 ,3);
	////////	control_map[K2_HSG_SPI_TB]  = pair<int,int>(2 ,4);
	////////	control_map[K3_HSG_SPI_TB]  = pair<int,int>(2 ,5);
	////////	control_map[K4_HSG_SPI_TB]  = pair<int,int>(2 ,6);
	////////	control_map[K5_HSG_SPI_TB]  = pair<int,int>(2 ,7);

	////////	 //Bank 3
	////////	control_map[K6_HSG_SPI_RB] = pair<int,int>(3 ,0);
	////////	control_map[K1_B_SPI_RB]   = pair<int,int>(3 ,1);
	////////	control_map[K2_B_SPI_TB]   = pair<int,int>(3 ,2);
	////////	control_map[K3_B_SPI_TB]   = pair<int,int>(3 ,3);
	////////	control_map[K4_B_SPI_TB]   = pair<int,int>(3 ,4);
	////////	control_map[K5_B_SPI_TB]   = pair<int,int>(3 ,5);
	////////	control_map[K2AB_VR_SPI_RB]= pair<int,int>(3 ,6);
	////////	control_map[K3_VR_SPI_RB]  = pair<int,int>(3 ,7);

	////////	// Bank 4
	////////	control_map[K4_VR_SPI_RB]   = pair<int,int>(4 ,0);
	////////	control_map[K5_VR_SPI_RB]   = pair<int,int>(4, 1);
	////////	control_map[K6_VR_SPI_RB]   = pair<int,int>(4 ,2);
	////////	control_map[K1_FW_SPI_TB]   = pair<int,int>(4 ,3);
	////////	control_map[K2_FW_SPI_TB]   = pair<int,int>(4 ,4);
	////////	control_map[K3_FW_SPI_TB]   = pair<int,int>(4 ,5);
	////////	control_map[K4_FW_SPI_IB]   = pair<int,int>(4 ,6);
	////////	control_map[K7_HSG_SPI_TB]  = pair<int,int>(4 ,7);

 ////////  		 //Bank 5
	////////	control_map[K_HPM_SPI_TB]   = pair<int,int>(5 ,0);
	////////	control_map[K7_VR_SPI_IB]   = pair<int,int>(5 ,1);
	////////	control_map[K_BANK5_SP1_TB] = pair<int,int>(5 ,2);
	////////	control_map[K_BANK5_SP2_TB] = pair<int,int>(5 ,3);
	////////	control_map[K_BANK5_SP3_TB] = pair<int,int>(5 ,4);
	////////	control_map[K_BANK5_SP4_TB] = pair<int,int>(5 ,5);
	////////	control_map[K_BANK5_SP5_TB] = pair<int,int>(5 ,6);
	////////	control_map[K_BANK5_SP6_TB] = pair<int,int>(5 ,7);

	////////	return 0;

	////////}

	////////BinnoRelayController::BinnoRelayController(int num_modules, int hz, int pinswap, int din_edge) {
	////////	relays = RelayController(num_modules, hz, pinswap, din_edge);
	////////	relays.track_relay_states(states);
	////////	BinnoRelayController::init(); // Causing linker failure
	////////	//BinnoRelayController::close_relay(10);// Causing linker failure
	////////}

	////////int BinnoRelayController::open_relay_spi(int rly) {
	////////	return relays.open_relay_spi(control_map[rly].first, control_map[rly].second);
	////////}

	////////int BinnoRelayController::close_relay_spi(int rly)  {
	////////	return relays.close_relay_spi(control_map[rly].first, control_map[rly].second);
	////////}

	////////int BinnoRelayController::open_all_relays_spi() {
	////////	return relays.open_all_relays_spi();
	////////}

//********************************************************************************
//***********  END: DSM SPI for Relay Controller  ********************************
//********************************************************************************








void Close_relay(int Relay)
{

	


	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//Mux14 controlled relays.
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	if(Relay == K1_DSM_TB   || //K1_DSM_TB     = MUX_1_1,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA (Vpin) of Primary.
       Relay == K2_DSM_TB   || //K2_DSM_TB     = MUX_1_2,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA of 2ndary.
	   Relay == K3_DSM_TB   || //K3_DSM_TB     = MUX_1_3,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL (TS) of Primary.
	   Relay == K4_DSM_TB   || //K4_DSM_TB     = MUX_1_4,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL of 2ndary.
	   Relay == K1_DDD_TB   || //K1_DDD_TB     = MUX_2_3,   // On Mux14.  To control relay to connect DDD7_1 to either TS or Integrator on IS pin.
	   Relay == K2_DDD_TB   || //K2_DDD_TB     = MUX_2_4,   // On Mux14.  To control relay to connect DDD7_2 to either IS or UV pin.
	   Relay == K3_DDD_TB   || //K3_DDD_TB     = MUX_3_1,   // On Mux14.  To control relay to connect DDD7_3 to VR pin.
	   Relay == K4_DDD_TB   || //K4_DDD_TB     = MUX_3_2,   // On Mux14.  To control relay to connect DDD7_4 to SDA pin.
	   Relay == K5_DDD_TB   || //K5_DDD_TB     = MUX_3_3,   // On Mux14.  To control relay to connect DDD7_5 to SCL pin or DDD7_5_FW_COMP3 pin.
       Relay == K6_DDD_TB   || //K6_DDD_TB     = MUX_3_4,   // On Mux14.  To control relay to connect DDD7_6 to FB pin or DDD7_6_FW_COMP1 pin.
	   Relay == K7_DDD_TB   || //K7_DDD_TB     = MUX_4_1,   // On Mux14.  To control relay to connect DDD7_7 to FW pin or DDD7_7_FW_COMP2 pin.
	   Relay == K1_TMU_TB   || //K1_TMU_TB     = MUX_4_2,   // On Mux14.  To control relay to connect TMU_HIZ1_D1 or TMU_HIZ1_D2.
	   Relay == K2_TMU_TB   || //K2_TMU_TB     = MUX_4_3,   // On Mux14.  To control relay to connect TMU_HIZ2/TMU_CHB_DUT2 to UV or B pin.	
	   Relay == K3_TMU_TB   || //K3_TMU_TB     = MUX_4_4,   // On Mux14.  To control relay to connect TMU_HIZ3 to HBP pin.	
	   Relay == K4_TMU_TB   || //K4_TMU_TB     = MUX_5_1,   // On Mux14.  To control relay to connect TMU_HIZ3 to VR pin.	
	   Relay == K5_TMU_TB   || //K5_TMU_TB     = MUX_5_2,   // On Mux14.  To control relay to connect TMU_HIZ3 to FW pin.	
	   Relay == K6_TMU_TB   || //K6_TMU_TB     = MUX_5_3,   // On Mux14.  To control relay to connect TMU_HIZ4/TMU_CHB_DUT1 to HSG or TS pin.	
	   Relay == K1_VR_TB    || //K1_VR_TB      = MUX_5_4,   // On Mux14.  To control relay to connect HVS to VR pin.
	   Relay == K1_D_RB     || //K1_D_RB       = MUX_6_1,   // On Mux14.  To control relay to connect DVI_11_0 to Drain or IM_Pedestal.
	   Relay == K2_D_RB     || //K2_D_RB       = MUX_6_2,   // On Mux14.  To control relay to connect DVI_11_0 as Kelvin or NonKelvin to Drain.
	   Relay == K3_D_TB     || //K3_D_TB       = MUX_6_3,   // On Mux14.  To control relay to connect/disconnect DVI_11_0 to Drain.
	   Relay == K4_D_TB     || //K4_D_TB       = MUX_6_4,   // On Mux14.  To control relay to connect/disconnect HVS to Drain.
	   Relay == K5_D_TB     || //K5_D_TB       = MUX_7_1,   // On Mux14.  To control relay to connect/disconnect PVI3 directly or via inductor to Drain
	   Relay == K6_D_TB     || //K6_D_TB       = MUX_7_2,   // On Mux14.  To control relay to connect/disconnect reg Pri SOA or pulse Pri SOA.
	   Relay == K7_D_TB     || //K7_D_TB       = MUX_7_3,   // On Mux14.  To control relay to connect/disconnect Drain to SOA circuit.
	   Relay == K8_K11_D_TB || //K8_K11_D_TB   = MUX_7_4,   // On Mux14.  To control relay to connect/disconnect Sync circuit to FW.
	   Relay == K9_D_TB     || //K9_D_TB       = MUX_8_1,   // On Mux14.  To control relay to connect/disconnect Drain to Pierson.
	   Relay == K1_IM_TB    || //K1_IM_TB	   = MUX_8_2,   // On Mux14.  To control relay to connect/disconnect IM1
	   Relay == K2_IM_TB    || //K2_IM_TB	   = MUX_8_3,   // On Mux14.  To control relay to connect/disconnect IM2
	   Relay == K3_IM_TB     ) //K3_IM_TB	   = MUX_8_4,   // On Mux14.  To control relay to connect/disconnect IM3
	{
		mux_14->close_relay(Relay-500);
	}
	else if (//Mux20 controlled relays.
			 Relay == K1_HVS_LB    || //K1_HVS_LB    = MUX_6_2,   // On Mux20.  To connect HVS_15_POS_F to LB.
             Relay == K2_HVS_LB    || //K2_HVS_LB    = MUX_6_3,   // On Mux20.  To stack   HVS_15_NEG_F on top of HVS_19_POS_F for 900V testing.
             Relay == K1_DDD_LB    || //K1_DDD_LB    = MUX_6_1,   // On Mux20.  To connect DDD7_1 to high speed comparator to generate narrow pulses.
			 Relay == K_GND_ANA_LB || //K_GND_ANA_LB = MUX_6_4,   // On Mux20.  By default, GND sense is connected to primary ground sense.  K_GND_ANA_LB is to connect to 2ndary GNDS
			 Relay == K1_GNDS_LB   || //K1_GNDS_LB   = MUX_5_1,   // On Mux20.  By default, DVI11_GNDS is connected to primary ground sense. K1_GNDS_LB is to connect to 2ndary GNDS.
			 Relay == K2_GNDS_LB   || //K2_GNDS_LB   = MUX_5_2,   // On Mux20.  By default, DVI9_GNDS is connected to primary ground sense.  K2_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K3_GNDS_LB   || //K3_GNDS_LB   = MUX_5_3,   // On Mux20.  By default, DVI13_GNDS is connected to primary ground sense. K3_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K4_GNDS_LB   || //K4_GNDS_LB   = MUX_5_4,   // On Mux20.  By default, DVI21_GNDS is connected to primary ground sense. K4_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K_OVI3_0_LB  || //K_OVI3_0_LB  = MUX_7_2,   // On Mux20.  To control OVI3_0 connect or disconnect from TS pin.
			 Relay == K_OVI3_1_LB  || //K_OVI3_1_LB  = MUX_7_3,   // On Mux20.  To control OVI3_0 connect to OVI3_1 sense to check Kelvin of OVI3_0 on TS pin.
			 Relay == K_OVI3_3_LB  || //K_OVI3_3_LB  = MUX_7_4,   // On Mux20.  To control OVI3_3 connect/disconnect to Sync ckt on TB.  K_OVI3_3_LB is also used to check Mux_20.
			 Relay == K_OVI3_4_LB  || //K_OVI3_4_LB  = MUX_8_2,   // On Mux20.  To short OVI3_4 Sense to OVI3_5 Sense for Kelvin check.   To short OVI3_6 Sense to OVI3_7 S for Kelvin Check.
			 Relay == K_OVI1_0_LB  || //K_OVI1_0_LB  = MUX_8_3,   // On Mux20.  To short OVI1_1 Sense to OVI1_0 Sense for Kelvin check.   
			 Relay == K5678_DSM_TB || //K5678_DSM_TB = MUX_4_2,   // On Mux20.  To control relay for Pri + 2ndary parallel scan.   
			 Relay == K10_D_TB     || //K10_D_TB     = MUX_1_1,   // On Mux20.  To control relay for connecting Drain to RDSON BUFF Input.
			 Relay == K12_D_TB     || //K12_D_TB     = MUX_4_1,   // On Mux20.  To control relay for shorting inductor L3 for Pri SOA testing.
			 Relay == K_UV_BUFF_TB || //K_UV_BUFF_TB = MUX_1_2,   // On Mux20.  To control relay for connecting Rdson buffer to Vpin.
			 Relay == K1_UV_RB     || //K1_UV_RB     = MUX_1_3,   // On Mux20.  To control relay NonKelvin or Kelvin On Vpin.
			 Relay == K2_UV_RB     || //K2_UV_RB     = MUX_1_4,   // On Mux20.  To control relay to select 10K or 600K pullup resistor on Vpin.
			 Relay == K3_UV_TB     || //K3_UV_TB     = MUX_2_1,   // On Mux20.  To control relay to connect/disconnect DVI21 to Vpin.
			 Relay == K1_DigA_TB   || //K1_DigA_TB   = MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K1_IS_BUFF_TB|| //K1_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K2_IS_BUFF_TB|| //K2_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K2_DigA_TB   || //K2_DigA_TB   = MUX_2_3,   // On Mux20.  To control relay to connect to either FW or IS pin.
		     Relay == K_CHANB_TB   || //K_CHANB_TB   = MUX_2_4,   // On Mux20.  To control relay to connect to either B or HSG pin.
             Relay == K1_BPP_RB    || //K1_BPP_RB    = MUX_3_1,   // On Mux20.  To control relay to connect to BPP to 4.7uF CaP on Riderboard.
             Relay == K1_TS_RB     || //K1_TS_RB     = MUX_3_2,   // On Mux20.  To control relay to select NonKelvin/Kelvin on TS pin.
	         Relay == K2_TS_TB     || //K2_TS_TB     = MUX_3_3,   // On Mux20.  To control relay to connect/disconnect OVI3_0 to TS pin.
	         Relay == K3_TS_IB     ) //K3_TS_IB     = MUX_3_4,   // On Mux20.  To control relay to connect/disconnect LT1719 comparator to TS pin.
	{
		mux_20->close_relay(Relay-200);
	}
	else if (//SPI Relay Bank 1
		     Relay == K1_IS_SPI_TB || //K1_IS_SPI_TB  = SPI1_OUT1, //SPI controlled.  To connect to IS or IS buffer ckt.
	         Relay == K2_IS_SPI_IB || //K2_IS_SPI_IB  = SPI1_OUT2, //SPI controlled.  To connect/disconnect 100K for voltage divider in IS buffer insert ckt.
			 Relay == K3_IS_SPI_IB || //K3_IS_SPI_IB  = SPI1_OUT3, //SPI controlled.  To connect/disconnect 2K for voltage divider in IS buffer insert ckt.
             Relay == K4_IS_SPI_IB || //K4_IS_SPI_IB  = SPI1_OUT4, //SPI controlled.  To connect/disconnect comparator input to GND in the IS buffer insert ckt.
			 Relay == K5_IS_SPI_IB || //K5_IS_SPI_IB  = SPI1_OUT5, //SPI controlled.  To connect/disconnect buffer output to IS pin in the IS buffer insert ckt.
	         Relay == K6_IS_SPI_IB || //K6_IS_SPI_IB  = SPI1_OUT6, //SPI controlled.  To connect/disconnect analog switch to either DDD7_2 or B in the Current Limit boost Insert ckt
			 Relay == K1_SDA_SPI_TB|| //K1_SDA_SPI_TB = SPI1_OUT7, //SPI controlled.  To connect/disconnect OVI3_5 as Kelvin/NonKelvin to SDA pin.
			 Relay == K1_SCL_SPI_TB ) //	K1_SCL_SPI_TB = SPI1_OUT8, //SPI controlled.  To connect/disconnect OVI3_6 as Kelvin/NonKelvin to SCL pin.
	{
		//relays.close_relay_spi(5, Relay);	
		if(Relay == K1_IS_SPI_TB)		relays.close_relay_spi(5, 0);
		if(Relay == K2_IS_SPI_IB)		relays.close_relay_spi(5, 1);
		if(Relay == K3_IS_SPI_IB)		relays.close_relay_spi(5, 2);
		if(Relay == K4_IS_SPI_IB)		relays.close_relay_spi(5, 3);
		if(Relay == K5_IS_SPI_IB)		relays.close_relay_spi(5, 4);
		if(Relay == K6_IS_SPI_IB)		relays.close_relay_spi(5, 5);
		if(Relay == K1_SDA_SPI_TB)		relays.close_relay_spi(5, 6);
		if(Relay == K1_SCL_SPI_TB)		relays.close_relay_spi(5, 7);
	}
	
	else if (//SPI Relay Bank 2
             Relay == K1_HBP_SPI_RB || //K1_HBP_SPI_RB = SPI2_OUT1, //SPI controlled.  To connect/disconnect HBP & FB pins.
             Relay == K1_FB_SPI_TB  || //K1_FB_SPI_TB  = SPI2_OUT2, //SPI controlled.  To connect/disconnect OVI3_7 as Kelvin/NonKelvin to FB pin.
             Relay == K2_FB_SPI_TB  || //K2_FB_SPI_TB  = SPI2_OUT3, //SPI controlled.  To select 1M pullup resistor or voltage divider to FB pin.
	         Relay == K1_HSG_SPI_RB || //K1_HSG_SPI_RB = SPI2_OUT4, //SPI controlled.  To connect/disconnect OVI1_0 as Kelvin/NonKelvin to HSG pin.
	         Relay == K2_HSG_SPI_TB || //K2_HSG_SPI_TB = SPI2_OUT5, //SPI controlled.  To connect/disconnect OVI1_0 from HSG pin.
	         Relay == K3_HSG_SPI_TB || //K3_HSG_SPI_TB = SPI2_OUT6, //SPI controlled.  To connect/disconnect HSG to 2nF cap.
			 Relay == K4_HSG_SPI_TB || //K4_HSG_SPI_TB = SPI2_OUT7, //SPI controlled.  To connect/disconnect HSG to GND.
			 Relay == K5_HSG_SPI_TB  ) //K5_HSG_SPI_TB = SPI2_OUT8, //SPI controlled.  To connect/disconnect HSG to Buffer ckt.
	{
		if(Relay == K1_HBP_SPI_RB)		relays.close_relay_spi(4, 0);
		if(Relay == K1_FB_SPI_TB)		relays.close_relay_spi(4, 1);
		if(Relay == K2_FB_SPI_TB)		relays.close_relay_spi(4, 2);
		if(Relay == K1_HSG_SPI_RB)		relays.close_relay_spi(4, 3);
		if(Relay == K2_HSG_SPI_TB)		relays.close_relay_spi(4, 4);
		if(Relay == K3_HSG_SPI_TB)		relays.close_relay_spi(4, 5);
		if(Relay == K4_HSG_SPI_TB)		relays.close_relay_spi(4, 6);
		if(Relay == K5_HSG_SPI_TB)		relays.close_relay_spi(4, 7);
	}
	else if (//SPI Relay Bank 3
             Relay == K6_HSG_SPI_RB || //K6_HSG_SPI_RB  = SPI3_OUT1, //SPI controlled. 
             Relay == K1_B_SPI_RB   || //K1_B_SPI_RB    = SPI3_OUT2, //SPI controlled.  
             Relay == K2_B_SPI_TB   || //K2_B_SPI_TB    = SPI3_OUT3, //SPI controlled.  
	         Relay == K3_B_SPI_TB   || //K3_B_SPI_TB    = SPI3_OUT4, //SPI controlled.  
	         Relay == K4_B_SPI_TB   || //K4_B_SPI_TB    = SPI3_OUT5, //SPI controlled.
	         Relay == K5_B_SPI_TB   || //K5_B_SPI_TB    = SPI3_OUT6, //SPI controlled.  
			 Relay == K2AB_VR_SPI_RB|| //K2AB_VR_SPI_RB = SPI3_OUT7, //SPI controlled. 
			 Relay == K3_VR_SPI_RB  ) //K3_VR_SPI_RB   = SPI3_OUT8, //SPI controlled.  
	{
		if(Relay == K6_HSG_SPI_RB)		relays.close_relay_spi(3, 0);
		if(Relay == K1_B_SPI_RB)		relays.close_relay_spi(3, 1);
		if(Relay == K2_B_SPI_TB)		relays.close_relay_spi(3, 2);
		if(Relay == K3_B_SPI_TB)		relays.close_relay_spi(3, 3);
		if(Relay == K4_B_SPI_TB)		relays.close_relay_spi(3, 4);
		if(Relay == K5_B_SPI_TB)		relays.close_relay_spi(3, 5);
		if(Relay == K2AB_VR_SPI_RB)		relays.close_relay_spi(3, 6);
		if(Relay == K3_VR_SPI_RB)		relays.close_relay_spi(3, 7);	
	}
	else if (//SPI Relay Bank 4
             Relay == K4_VR_SPI_RB   || //K4_VR_SPI_RB   = SPI4_OUT1, //SPI controlled. 
             Relay == K5_VR_SPI_RB   || //K5_VR_SPI_RB   = SPI4_OUT2, //SPI controlled.  
             Relay == K6_VR_SPI_RB   || //K6_VR_SPI_RB   = SPI4_OUT3, //SPI controlled.  
	         Relay == K1_FW_SPI_TB   || //K1_FW_SPI_TB   = SPI4_OUT4, //SPI controlled.   
	         Relay == K2_FW_SPI_TB   || //K2_FW_SPI_TB   = SPI4_OUT5, //SPI controlled.  
	         Relay == K3_FW_SPI_TB   || //K3_FW_SPI_TB   = SPI4_OUT6, //SPI controlled. same CBIT also controlled K4_FW_SPI_IB
			 Relay == K5_FW_SPI_IB   || //K5_FW_SPI_IB   = SPI4_OUT7, //SPI controlled.
			 Relay == K7_HSG_SPI_TB  )  //K7_HSG_SPI_TB  = SPI4_OUT8, //SPI controlled.
	{
		if(Relay == K4_VR_SPI_RB)		relays.close_relay_spi(2, 0);
		if(Relay == K5_VR_SPI_RB)		relays.close_relay_spi(2, 1);
		if(Relay == K6_VR_SPI_RB)		relays.close_relay_spi(2, 2);
		if(Relay == K1_FW_SPI_TB)		relays.close_relay_spi(2, 3);
		if(Relay == K2_FW_SPI_TB)		relays.close_relay_spi(2, 4);
		if(Relay == K3_FW_SPI_TB)		relays.close_relay_spi(2, 5);
		if(Relay == K5_FW_SPI_IB)		relays.close_relay_spi(2, 6);
		if(Relay == K7_HSG_SPI_TB)		relays.close_relay_spi(2, 7);		}
	else if (//SPI Relay Bank 5
             Relay == K_HPM_SPI_TB   || //K_HPM_SPI_TB   = SPI5_OUT1, //SPI controlled.  
             Relay == K7_VR_SPI_IB   || //K7_VR_SPI_IB   = SPI5_OUT2, //SPI controlled. 
             Relay == K_BANK5_SP1_TB || //K_BANK5_SP1_TB = SPI5_OUT3, //SPI controlled.   
	         Relay == K_BANK5_SP2_TB || //K_BANK5_SP2_TB = SPI5_OUT4, //SPI controlled.    
	         Relay == K_BANK5_SP3_TB || //K_BANK5_SP3_TB = SPI5_OUT5, //SPI controlled.   
	         Relay == K_BANK5_SP4_TB || //K_BANK5_SP4_TB = SPI5_OUT6, //SPI controlled.
			 Relay == K_BANK5_SP5_TB || //K_BANK5_SP5_TB = SPI5_OUT7, //SPI controlled. 
			 Relay == K_BANK5_SP6_TB  )  //K_BANK5_SP6_TB = SPI5_OUT8, //SPI controlled.
	{
		if(Relay == K_HPM_SPI_TB)		relays.close_relay_spi(1, 0);
		if(Relay == K7_VR_SPI_IB)		relays.close_relay_spi(1, 1);
		if(Relay == K_BANK5_SP1_TB)		relays.close_relay_spi(1, 2);
		if(Relay == K_BANK5_SP2_TB)		relays.close_relay_spi(1, 3);
		if(Relay == K_BANK5_SP3_TB)		relays.close_relay_spi(1, 4);
		if(Relay == K_BANK5_SP4_TB)		relays.close_relay_spi(1, 5);
		if(Relay == K_BANK5_SP5_TB)		relays.close_relay_spi(1, 6);
		if(Relay == K_BANK5_SP6_TB)		relays.close_relay_spi(1, 7);
	}
	else {};

}
	
//--------------------------------------------------------------------------------------------------------------------------------------
void Open_relay(int Relay)
{



	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//Mux14 controlled relays.
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	if(Relay == K1_DSM_TB   || //K1_DSM_TB     = MUX_1_1,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA (Vpin) of Primary.
       Relay == K2_DSM_TB   || //K2_DSM_TB     = MUX_1_2,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA of 2ndary.
	   Relay == K3_DSM_TB   || //K3_DSM_TB     = MUX_1_3,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL (TS) of Primary.
	   Relay == K4_DSM_TB   || //K4_DSM_TB     = MUX_1_4,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL of 2ndary.
	   Relay == K1_DDD_TB   || //K1_DDD_TB     = MUX_2_3,   // On Mux14.  To control relay to connect DDD7_1 to either TS or Integrator on IS pin.
	   Relay == K2_DDD_TB   || //K2_DDD_TB     = MUX_2_4,   // On Mux14.  To control relay to connect DDD7_2 to either IS or UV pin.
	   Relay == K3_DDD_TB   || //K3_DDD_TB     = MUX_3_1,   // On Mux14.  To control relay to connect DDD7_3 to VR pin.
	   Relay == K4_DDD_TB   || //K4_DDD_TB     = MUX_3_2,   // On Mux14.  To control relay to connect DDD7_4 to SDA pin.
	   Relay == K5_DDD_TB   || //K5_DDD_TB     = MUX_3_3,   // On Mux14.  To control relay to connect DDD7_5 to SCL pin or DDD7_5_FW_COMP3 pin.
       Relay == K6_DDD_TB   || //K6_DDD_TB     = MUX_3_4,   // On Mux14.  To control relay to connect DDD7_6 to FB pin or DDD7_6_FW_COMP1 pin.
	   Relay == K7_DDD_TB   || //K7_DDD_TB     = MUX_4_1,   // On Mux14.  To control relay to connect DDD7_7 to FW pin or DDD7_7_FW_COMP2 pin.
	   Relay == K1_TMU_TB   || //K1_TMU_TB     = MUX_4_2,   // On Mux14.  To control relay to connect TMU_HIZ1_D1 or TMU_HIZ1_D2.
	   Relay == K2_TMU_TB   || //K2_TMU_TB     = MUX_4_3,   // On Mux14.  To control relay to connect TMU_HIZ2/TMU_CHB_DUT2 to UV or B pin.	
	   Relay == K3_TMU_TB   || //K3_TMU_TB     = MUX_4_4,   // On Mux14.  To control relay to connect TMU_HIZ3 to HBP pin.	
	   Relay == K4_TMU_TB   || //K4_TMU_TB     = MUX_5_1,   // On Mux14.  To control relay to connect TMU_HIZ3 to VR pin.	
	   Relay == K5_TMU_TB   || //K5_TMU_TB     = MUX_5_2,   // On Mux14.  To control relay to connect TMU_HIZ3 to FW pin.	
	   Relay == K6_TMU_TB   || //K6_TMU_TB     = MUX_5_3,   // On Mux14.  To control relay to connect TMU_HIZ4/TMU_CHB_DUT1 to HSG or TS pin.	
	   Relay == K1_VR_TB    || //K1_VR_TB      = MUX_5_4,   // On Mux14.  To control relay to connect HVS to VR pin.
	   Relay == K1_D_RB     || //K1_D_RB       = MUX_6_1,   // On Mux14.  To control relay to connect DVI_11_0 to Drain or IM_Pedestal.
	   Relay == K2_D_RB     || //K2_D_RB       = MUX_6_2,   // On Mux14.  To control relay to connect DVI_11_0 as Kelvin or NonKelvin to Drain.
	   Relay == K3_D_TB     || //K3_D_TB       = MUX_6_3,   // On Mux14.  To control relay to connect/disconnect DVI_11_0 to Drain.
	   Relay == K4_D_TB     || //K4_D_TB       = MUX_6_4,   // On Mux14.  To control relay to connect/disconnect HVS to Drain.
	   Relay == K5_D_TB     || //K5_D_TB       = MUX_7_1,   // On Mux14.  To control relay to connect/disconnect PVI3 directly or via inductor to Drain
	   Relay == K6_D_TB     || //K6_D_TB       = MUX_7_2,   // On Mux14.  To control relay to connect/disconnect reg Pri SOA or pulse Pri SOA.
	   Relay == K7_D_TB     || //K7_D_TB       = MUX_7_3,   // On Mux14.  To control relay to connect/disconnect Drain to SOA circuit.
	   Relay == K8_K11_D_TB || //K8_K11_D_TB   = MUX_7_4,   // On Mux14.  To control relay to connect/disconnect Sync circuit to FW.
	   Relay == K9_D_TB     || //K9_D_TB       = MUX_8_1,   // On Mux14.  To control relay to connect/disconnect Drain to Pierson.
	   Relay == K1_IM_TB    || //K1_IM_TB	   = MUX_8_2,   // On Mux14.  To control relay to connect/disconnect IM1
	   Relay == K2_IM_TB    || //K2_IM_TB	   = MUX_8_3,   // On Mux14.  To control relay to connect/disconnect IM2
	   Relay == K3_IM_TB     ) //K3_IM_TB	   = MUX_8_4,   // On Mux14.  To control relay to connect/disconnect IM3
	{
		mux_14->open_relay(Relay-500);
	}
	else if (//Mux20 controlled relays.
			 Relay == K1_HVS_LB    || //K1_HVS_LB    = MUX_6_2,   // On Mux20.  To connect HVS_15_POS_F to LB.
             Relay == K2_HVS_LB    || //K2_HVS_LB    = MUX_6_3,   // On Mux20.  To stack   HVS_15_NEG_F on top of HVS_19_POS_F for 900V testing.
             Relay == K1_DDD_LB    || //K1_DDD_LB    = MUX_6_1,   // On Mux20.  To connect DDD7_1 to high speed comparator to generate narrow pulses.
			 Relay == K_GND_ANA_LB || //K_GND_ANA_LB = MUX_6_4,   // On Mux20.  By default, GND sense is connected to primary ground sense.  K_GND_ANA_LB is to connect to 2ndary GNDS
			 Relay == K1_GNDS_LB   || //K1_GNDS_LB   = MUX_5_1,   // On Mux20.  By default, DVI11_GNDS is connected to primary ground sense. K1_GNDS_LB is to connect to 2ndary GNDS.
			 Relay == K2_GNDS_LB   || //K2_GNDS_LB   = MUX_5_2,   // On Mux20.  By default, DVI9_GNDS is connected to primary ground sense.  K2_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K3_GNDS_LB   || //K3_GNDS_LB   = MUX_5_3,   // On Mux20.  By default, DVI13_GNDS is connected to primary ground sense. K3_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K4_GNDS_LB   || //K4_GNDS_LB   = MUX_5_4,   // On Mux20.  By default, DVI21_GNDS is connected to primary ground sense. K4_GNDS_LB is to connected 2ndary GNDs.                                   
			 Relay == K_OVI3_0_LB  || //K_OVI3_0_LB  = MUX_7_2,   // On Mux20.  To control OVI3_0 connect or disconnect from TS pin.
			 Relay == K_OVI3_1_LB  || //K_OVI3_1_LB  = MUX_7_3,   // On Mux20.  To control OVI3_0 connect to OVI3_1 sense to check Kelvin of OVI3_0 on TS pin.
			 Relay == K_OVI3_3_LB  || //K_OVI3_3_LB  = MUX_7_4,   // On Mux20.  To control OVI3_3 connect/disconnect to Sync ckt on TB.  K_OVI3_3_LB is also used to check Mux_20.
			 Relay == K_OVI3_4_LB  || //K_OVI3_4_LB  = MUX_8_2,   // On Mux20.  To short OVI3_4 Sense to OVI3_5 Sense for Kelvin check.   To short OVI3_6 Sense to OVI3_7 S for Kelvin Check.
			 Relay == K_OVI1_0_LB  || //K_OVI1_0_LB  = MUX_8_3,   // On Mux20.  To short OVI1_1 Sense to OVI1_0 Sense for Kelvin check.   
			 Relay == K5678_DSM_TB || //K5678_DSM_TB = MUX_4_2,   // On Mux20.  To control relay for Pri + 2ndary parallel scan.   
			 Relay == K10_D_TB     || //K10_D_TB     = MUX_1_1,   // On Mux20.  To control relay for connecting Drain to RDSON BUFF Input.
			 Relay == K12_D_TB     || //K12_D_TB     = MUX_4_1,   // On Mux20.  To control relay for shorting inductor L3 for Pri SOA testing.
			 Relay == K_UV_BUFF_TB || //K_UV_BUFF_TB = MUX_1_2,   // On Mux20.  To control relay for connecting Rdson buffer to Vpin.
			 Relay == K1_UV_RB     || //K1_UV_RB     = MUX_1_3,   // On Mux20.  To control relay NonKelvin or Kelvin On Vpin.
			 Relay == K2_UV_RB     || //K2_UV_RB     = MUX_1_4,   // On Mux20.  To control relay to select 10K or 600K pullup resistor on Vpin.
			 Relay == K3_UV_TB     || //K3_UV_TB     = MUX_2_1,   // On Mux20.  To control relay to connect/disconnect DVI21 to Vpin.
			 Relay == K1_DigA_TB   || //K1_DigA_TB   = MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K1_IS_BUFF_TB|| //K1_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K2_IS_BUFF_TB|| //K2_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
			 Relay == K2_DigA_TB   || //K2_DigA_TB   = MUX_2_3,   // On Mux20.  To control relay to connect to either FW or IS pin.
		     Relay == K_CHANB_TB   || //K_CHANB_TB   = MUX_2_4,   // On Mux20.  To control relay to connect to either B or HSG pin.
             Relay == K1_BPP_RB    || //K1_BPP_RB    = MUX_3_1,   // On Mux20.  To control relay to connect to BPP to 4.7uF CaP on Riderboard.
             Relay == K1_TS_RB     || //K1_TS_RB     = MUX_3_2,   // On Mux20.  To control relay to select NonKelvin/Kelvin on TS pin.
	         Relay == K2_TS_TB     || //K2_TS_TB     = MUX_3_3,   // On Mux20.  To control relay to connect/disconnect OVI3_0 to TS pin.
	         Relay == K3_TS_IB     ) //K3_TS_IB     = MUX_3_4,   // On Mux20.  To control relay to connect/disconnect LT1719 comparator to TS pin.
	{
		mux_20->open_relay(Relay-200);
	}
	else if (//SPI Relay Bank 1
		     Relay == K1_IS_SPI_TB || //K1_IS_SPI_TB  = SPI1_OUT1, //SPI controlled.  To connect to IS or IS buffer ckt.
	         Relay == K2_IS_SPI_IB || //K2_IS_SPI_IB  = SPI1_OUT2, //SPI controlled.  To connect/disconnect 100K for voltage divider in IS buffer insert ckt.
			 Relay == K3_IS_SPI_IB || //K3_IS_SPI_IB  = SPI1_OUT3, //SPI controlled.  To connect/disconnect 2K for voltage divider in IS buffer insert ckt.
             Relay == K4_IS_SPI_IB || //K4_IS_SPI_IB  = SPI1_OUT4, //SPI controlled.  To connect/disconnect comparator input to GND in the IS buffer insert ckt.
			 Relay == K5_IS_SPI_IB || //K5_IS_SPI_IB  = SPI1_OUT5, //SPI controlled.  To connect/disconnect buffer output to IS pin in the IS buffer insert ckt.
	         Relay == K6_IS_SPI_IB || //K6_IS_SPI_IB  = SPI1_OUT6, //SPI controlled.  To connect/disconnect analog switch to either DDD7_2 or B in the Current Limit boost Insert ckt
			 Relay == K1_SDA_SPI_TB|| //K1_SDA_SPI_TB = SPI1_OUT7, //SPI controlled.  To connect/disconnect OVI3_5 as Kelvin/NonKelvin to SDA pin.
			 Relay == K1_SCL_SPI_TB ) //	K1_SCL_SPI_TB = SPI1_OUT8, //SPI controlled.  To connect/disconnect OVI3_6 as Kelvin/NonKelvin to SCL pin.
	{
		if(Relay == K1_IS_SPI_TB)		relays.open_relay_spi(5, 0);
		if(Relay == K2_IS_SPI_IB)		relays.open_relay_spi(5, 1);
		if(Relay == K3_IS_SPI_IB)		relays.open_relay_spi(5, 2);
		if(Relay == K4_IS_SPI_IB)		relays.open_relay_spi(5, 3);
		if(Relay == K5_IS_SPI_IB)		relays.open_relay_spi(5, 4);
		if(Relay == K6_IS_SPI_IB)		relays.open_relay_spi(5, 5);
		if(Relay == K1_SDA_SPI_TB)		relays.open_relay_spi(5, 6);
		if(Relay == K1_SCL_SPI_TB)		relays.open_relay_spi(5, 7);		//relays.open_relay_spi(Relay);		
	}
	
	else if (//SPI Relay Bank 2
             Relay == K1_HBP_SPI_RB || //K1_HBP_SPI_RB = SPI2_OUT1, //SPI controlled.  To connect/disconnect HBP & FB pins.
             Relay == K1_FB_SPI_TB  || //K1_FB_SPI_TB  = SPI2_OUT2, //SPI controlled.  To connect/disconnect OVI3_7 as Kelvin/NonKelvin to FB pin.
             Relay == K2_FB_SPI_TB  || //K2_FB_SPI_TB  = SPI2_OUT3, //SPI controlled.  To select 1M pullup resistor or voltage divider to FB pin.
	         Relay == K1_HSG_SPI_RB || //K1_HSG_SPI_RB = SPI2_OUT4, //SPI controlled.  To connect/disconnect OVI1_0 as Kelvin/NonKelvin to HSG pin.
	         Relay == K2_HSG_SPI_TB || //K2_HSG_SPI_TB = SPI2_OUT5, //SPI controlled.  To connect/disconnect OVI1_0 from HSG pin.
	         Relay == K3_HSG_SPI_TB || //K3_HSG_SPI_TB = SPI2_OUT6, //SPI controlled.  To connect/disconnect HSG to 2nF cap.
			 Relay == K4_HSG_SPI_TB || //K4_HSG_SPI_TB = SPI2_OUT7, //SPI controlled.  To connect/disconnect HSG to GND.
			 Relay == K5_HSG_SPI_TB  ) //K5_HSG_SPI_TB = SPI2_OUT8, //SPI controlled.  To connect/disconnect HSG to Buffer ckt.
	{
		if(Relay == K1_HBP_SPI_RB)		relays.open_relay_spi(4, 0);
		if(Relay == K1_FB_SPI_TB)		relays.open_relay_spi(4, 1);
		if(Relay == K2_FB_SPI_TB)		relays.open_relay_spi(4, 2);
		if(Relay == K1_HSG_SPI_RB)		relays.open_relay_spi(4, 3);
		if(Relay == K2_HSG_SPI_TB)		relays.open_relay_spi(4, 4);
		if(Relay == K3_HSG_SPI_TB)		relays.open_relay_spi(4, 5);
		if(Relay == K4_HSG_SPI_TB)		relays.open_relay_spi(4, 6);
		if(Relay == K5_HSG_SPI_TB)		relays.open_relay_spi(4, 7);
	}
	else if (//SPI Relay Bank 3
             Relay == K6_HSG_SPI_RB || //K6_HSG_SPI_RB  = SPI3_OUT1, //SPI controlled. 
             Relay == K1_B_SPI_RB   || //K1_B_SPI_RB    = SPI3_OUT2, //SPI controlled.  
             Relay == K2_B_SPI_TB   || //K2_B_SPI_TB    = SPI3_OUT3, //SPI controlled.  
	         Relay == K3_B_SPI_TB   || //K3_B_SPI_TB    = SPI3_OUT4, //SPI controlled.  
	         Relay == K4_B_SPI_TB   || //K4_B_SPI_TB    = SPI3_OUT5, //SPI controlled.
	         Relay == K5_B_SPI_TB   || //K5_B_SPI_TB    = SPI3_OUT6, //SPI controlled.  
			 Relay == K2AB_VR_SPI_RB|| //K2AB_VR_SPI_RB = SPI3_OUT7, //SPI controlled. 
			 Relay == K3_VR_SPI_RB  ) //K3_VR_SPI_RB   = SPI3_OUT8, //SPI controlled.  
	{
		if(Relay == K6_HSG_SPI_RB)		relays.open_relay_spi(3, 0);
		if(Relay == K1_B_SPI_RB)		relays.open_relay_spi(3, 1);
		if(Relay == K2_B_SPI_TB)		relays.open_relay_spi(3, 2);
		if(Relay == K3_B_SPI_TB)		relays.open_relay_spi(3, 3);
		if(Relay == K4_B_SPI_TB)		relays.open_relay_spi(3, 4);
		if(Relay == K5_B_SPI_TB)		relays.open_relay_spi(3, 5);
		if(Relay == K2AB_VR_SPI_RB)		relays.open_relay_spi(3, 6);
		if(Relay == K3_VR_SPI_RB)		relays.open_relay_spi(3, 7);	}
	else if (//SPI Relay Bank 4
             Relay == K4_VR_SPI_RB   || //K4_VR_SPI_RB   = SPI4_OUT1, //SPI controlled. 
             Relay == K5_VR_SPI_RB   || //K5_VR_SPI_RB   = SPI4_OUT2, //SPI controlled.  
             Relay == K6_VR_SPI_RB   || //K6_VR_SPI_RB   = SPI4_OUT3, //SPI controlled.  
	         Relay == K1_FW_SPI_TB   || //K1_FW_SPI_TB   = SPI4_OUT4, //SPI controlled.   
	         Relay == K2_FW_SPI_TB   || //K2_FW_SPI_TB   = SPI4_OUT5, //SPI controlled.  
	         Relay == K3_FW_SPI_TB   || //K3_FW_SPI_TB   = SPI4_OUT6, //SPI controlled.
			 Relay == K5_FW_SPI_IB   || //K4_FW_SPI_IB   = SPI4_OUT7, //SPI controlled.
			 Relay == K7_HSG_SPI_TB  )  //K7_HSG_SPI_TB  = SPI4_OUT8, //SPI controlled.
	{
		if(Relay == K4_VR_SPI_RB)		relays.open_relay_spi(2, 0);
		if(Relay == K5_VR_SPI_RB)		relays.open_relay_spi(2, 1);
		if(Relay == K6_VR_SPI_RB)		relays.open_relay_spi(2, 2);
		if(Relay == K1_FW_SPI_TB)		relays.open_relay_spi(2, 3);
		if(Relay == K2_FW_SPI_TB)		relays.open_relay_spi(2, 4);
		if(Relay == K3_FW_SPI_TB)		relays.open_relay_spi(2, 5);
		if(Relay == K5_FW_SPI_IB)		relays.open_relay_spi(2, 6);
		if(Relay == K7_HSG_SPI_TB)		relays.open_relay_spi(2, 7);	}
	else if (//SPI Relay Bank 5
             Relay == K_HPM_SPI_TB   || //K_HPM_SPI_TB   = SPI5_OUT1, //SPI controlled.  
             Relay == K7_VR_SPI_IB   || //K7_VR_SPI_IB   = SPI5_OUT2, //SPI controlled. 
             Relay == K_BANK5_SP1_TB || //K_BANK5_SP1_TB = SPI5_OUT3, //SPI controlled.   
	         Relay == K_BANK5_SP2_TB || //K_BANK5_SP2_TB = SPI5_OUT4, //SPI controlled.    
	         Relay == K_BANK5_SP3_TB || //K_BANK5_SP3_TB = SPI5_OUT5, //SPI controlled.   
	         Relay == K_BANK5_SP4_TB || //K_BANK5_SP4_TB = SPI5_OUT6, //SPI controlled.
			 Relay == K_BANK5_SP5_TB || //K_BANK5_SP5_TB = SPI5_OUT7, //SPI controlled. 
			 Relay == K_BANK5_SP6_TB  )  //K_BANK5_SP6_TB = SPI5_OUT8, //SPI controlled.
	{
		if(Relay == K_HPM_SPI_TB)		relays.open_relay_spi(1, 0);
		if(Relay == K7_VR_SPI_IB)		relays.open_relay_spi(1, 1);
		if(Relay == K_BANK5_SP1_TB)		relays.open_relay_spi(1, 2);
		if(Relay == K_BANK5_SP2_TB)		relays.open_relay_spi(1, 3);
		if(Relay == K_BANK5_SP3_TB)		relays.open_relay_spi(1, 4);
		if(Relay == K_BANK5_SP4_TB)		relays.open_relay_spi(1, 5);
		if(Relay == K_BANK5_SP5_TB)		relays.open_relay_spi(1, 6);
		if(Relay == K_BANK5_SP6_TB)		relays.open_relay_spi(1, 7);	}
	else {};
	
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void CreateAwav(double * data, int arr_size, float sample_rate, char * out_file_and_path) // DPG added //
{
	// create .awav file for debug //
	int i;
	FILE * fpr = fopen(out_file_and_path, "w");
	if (! fpr)
		return;
	fprintf (fpr, "version awav 0 2 0;\n");
	fprintf (fpr, "date 07 10 2003;\n");
	fprintf (fpr, "time 14 42 47;\n");
	fprintf (fpr, "name =  \"result_data\";\n");
	fprintf (fpr, "type = rrect;\n");
	fprintf (fpr, "size = %d;\n", arr_size);
	fprintf (fpr, "sample_interval = %13.11e;\n", sample_rate);
	fprintf (fpr, "offset = 0.000000e+000;\n");
	fprintf (fpr, "x_units = \"s \";\n");
	fprintf (fpr, "y_units = \"V \";\n");
	fprintf (fpr, "pattern;\n");
	fprintf (fpr, "  !Value\n");
	double val;
	for( i = 0; i < arr_size; i++)
		{
		val = data[i];
		if (val >= 0.0) 
			fprintf (fpr, "+");
		fprintf (fpr, "%18.16e; !%d\n", val, i);
		}
	fprintf (fpr, "pattern_end;\n");
	fclose(fpr);
	return;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void mode_change(void)
{	
	// Declare Variables //
	char dummy[40];
	STRING mystring;
	//STRING ProgramName;

	// Get limit set //
	GetLimitSetName( mystring );
	istrstream theLimitSetName( (char*)((const char*)mystring) );
	theLimitSetName >> Part_ID_LimitSet  >> g_OperCode >> dummy >> dummy;

	// OpCode  //
	if (!strnicmp( g_OperCode, "4200", 4 ))
		g_OPCODE = 4200;						
	if (!strnicmp( g_OperCode, "4250", 4 ))	
		g_OPCODE = 4250;						
	if (!strnicmp( g_OperCode, "4500", 4 ))	
		g_OPCODE = 4500;						
	if (!strnicmp( g_OperCode, "4300", 4 ))
		g_OPCODE = 4300;						
	if (!strnicmp( g_OperCode, "4400", 4 ))
		g_OPCODE = 4400;						
	if (!strnicmp( g_OperCode, "2400", 4 ))
		g_OPCODE = 2400;

 //*******************************  PartID  *************************************
	char*	Part_id_name;
	int		str_cmp_result	= 99;
	int		length			= 0;
	string	str_Part_id_name;
	if(GoldenUnit==false)
	{
		if(g_Require_PartID)
		{
			Part_id_name = PiGetPartID();			// Get partID from Lot info field
			Part_id_name = strupr(Part_id_name);	// Convert to Upper case.
			str_Part_id_name = Part_id_name;
			length = str_Part_id_name.length();

			//	Delete the "-TL" at the end of the device ID if it's there.
			if (str_Part_id_name.substr(length-3,length) == "-TL")
			{
				strcpy(Part_id_name, str_Part_id_name.substr(0, length-3).c_str());	// Remove "-TL" at the end of Part ID.
			}
			//if(!(str_cmp_result = (strcmp(Part_id_name,"SC1542K"))))//Append "-HCode"
			//{
			//	strcat(Part_id_name,"-HC16");
			//}

			//Part_id_name = "SC1538"; // Debug //
			printf("\nPart ID = %s\n",Part_id_name);

			if((strcmp(Part_id_name,"NONE")) == 0)
			{
				DisplayErrorMessage("'Part ID' must be entered in 'New Lot Information' pop-up screen");
				DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
				//g_DevNum_Trimops = 0;
				return;
				//exit(0);
			}
		}
	}

	// VBP setup //
	gVshunt_BPP = 5.5; // vBPP does not want to go above 5.5V according to Lance
	gVshunt_BPS = 5.5; // vBPS does not want to go above 5.5V according to Giao

	// Primary global register trim bit locations //
	gP_Reg_Start_Bit_SiID		=	0	;
	gP_Reg_Start_Bit_fOSC		=	8	;
	gP_Reg_Start_Bit_yInter		=	12	;
	gP_Reg_Start_Bit_ILIM		=	16	;
	gP_Reg_Start_Bit_ArSkip		=	21	;
	gP_Reg_Start_Bit_ArOnT		=	22	;
	gP_Reg_Start_Bit_ArOffT		=	23	;
	gP_Reg_Start_Bit_StrFREQ	=	25	;
	gP_Reg_Start_Bit_OnTSL		=	26	;
	gP_Reg_Start_Bit_ShuntEn	=	31	;
	gP_Reg_Start_Bit_RcvTH		=	32	;
	gP_Reg_Start_Bit_GanMode	=	35	;
	gP_Reg_Start_Bit_VxTrim		=	36	;
	gP_Reg_Start_Bit_DrSize		=	41	;
	gP_Reg_Start_Bit_AROn512	=	45	;
	gP_Reg_Start_Bit_GanDLy1	=	46	;
	gP_Reg_Start_Bit_IlimTc		=	48	;
	gP_Reg_Start_Bit_SDTemp		=	52	;
	gP_Reg_Start_Bit_DOPL		=	54	;
	gP_Reg_Start_Bit_DisIlimCap	=	55	;
	gP_Reg_Start_Bit_ILIMP		=	56	;
	gP_Reg_Start_Bit_uVADC		=	57	;
	gP_Reg_Start_Bit_StrTTFB	=	61	;
	gP_Reg_Start_Bit_EndTTFB	=	64	;
	gP_Reg_Start_Bit_TsADC		=	67	;
	gP_Reg_Start_Bit_UV10pct	=	71	;
	gP_Reg_Start_Bit_IOV		=	72	;
	gP_Reg_Start_Bit_TonM		=	77	;


	gP_Total_Bits_SiID			=	8	;
	gP_Total_Bits_fOSC			=	4	;
	gP_Total_Bits_yInter		=	4	;
	gP_Total_Bits_ILIM			=	5	;
	gP_Total_Bits_ArSkip		=	1	;
	gP_Total_Bits_ArOnT			=	1	;
	gP_Total_Bits_ArOffT		=	2	;
	gP_Total_Bits_StrFREQ		=	1	;
	gP_Total_Bits_OnTSL			=	5	;
	gP_Total_Bits_ShuntEn		=	1	;
	gP_Total_Bits_RcvTH			=	3	;
	gP_Total_Bits_GanMode		=	1	;
	gP_Total_Bits_VxTrim		=	5	;
	gP_Total_Bits_DrSize		=	4	;
	gP_Total_Bits_AROn512		=	1	;
	gP_Total_Bits_GanDLy1		=	2	;
	gP_Total_Bits_IlimTc		=	4	;
	gP_Total_Bits_SDTemp		=	2	;
	gP_Total_Bits_DOPL			=	1	;
	gP_Total_Bits_DisIlimCap	=	1	;
	gP_Total_Bits_ILIMP			=	1	;
	gP_Total_Bits_uVADC			=	4	;
	gP_Total_Bits_StrTTFB		=	3	;
	gP_Total_Bits_EndTTFB		=	3	;
	gP_Total_Bits_TsADC			=	4	;
	gP_Total_Bits_UV10pct		=	1	;
	gP_Total_Bits_IOV			=	5	;
	gP_Total_Bits_TonM			=	3	;


	// Initialize global variables //
	gLoadBoard_SubType = 6205; // Loadboard Subtype for Hardware ID. //HL changed to 6205
	
	// Use the old inductor module with D1 shorted.  There is a problem 
	// with D1 installed because the drain does not discharge when the drain turns 
	// off and is around 160V at the start of the next switching cycle which causes 
	// large current spike into drain, causing SOA to be tripped. // 
	gInductorRev = 2; // Inductor Module Revision for Hardware ID. //
	gContactor_SubType = 3550; // CB ID. ATE test variable, trimops table not used. //
	gVped_Ilim = 45; // gVped_ILIM. ATE test variable, trimops table not used. //				
	gVped_Ilim_Incr = 45; // gVped_Ilim_Incr. ATE test variable, trimops table not used. //			
	g_Ilim_gain = 0.5; // Ilim_gain. ATE test variable, trimops table not used. //			
	gDATT_pulse_time = 200; // DATT_tPulse. ATE test variable, trimops table not used. //		
	gNorm_x_lim = -0.01;
	gNorm_n_lim = 0.01;
	if (!strnicmp(Part_ID_LimitSet, "INN3365", 7))
	{
		gInductor_SubType = 1200; // IM ID. ATE test variable, trimops table not used. //
		//gVind_RM = 7; // Using PVI stacked on top of +50V supply. //
		gVind_RM = 43.5;
		g_Vpedestal = 20;
		gDATT_drain_current	= 1.26; // DATT_Idrain.. ATE test variable, trimops table not used. //
		g_DIDT_TARGET = 212.5/1000.0;
		g_scaled_ifrc = 0.0008;
	}

		

	g_Part_ID_Trimops = PiGetPartID();
	if (!strnicmp( g_PrgName, "INN3375GoldenUnit", 17 ))
	{
		g_Part_ID_Trimops = "INN3375golden";
	}

	printf("\nPart ID = %s\n",g_Part_ID_Trimops);
	if((strcmp(g_Part_ID_Trimops,"NONE")) == 0)
	{
		//HL disabled for Binno prelimiary trimming test program
		//MessageBox(NULL, "'Part ID' must be entered in 'New Lot Information' pop-up screen.  Program can not run.  Please re-enter New Lot Info.", "Error", MB_OK|MB_TOPMOST);
		//g_DevNum_Trimops = -99;
		//return;
	}
	char * dll_name = "LYT8.dll";
	#define MAX_FILE_NAME				100
	char DllFullName[MAX_FILE_NAME];
	HMODULE		DllHandle;
	DllHandle = GetModuleHandle( dll_name );
	GetModuleFileName( DllHandle, DllFullName, MAX_FILE_NAME );
	printf("DllFullName= %s\n",DllFullName);
	char* csvpath;
	csvpath = GetCSVPath(DllFullName,"LYT8-TrimOptions.csv");
	printf("\r\n\r\nCSV Path: %s\r\n\r\n",csvpath);
	PITrimOptions* trimops = new PITrimOptions();
	int fields = trimops->Read(csvpath, g_Part_ID_Trimops);	//Allow to read once only
	if (fields != 66)	//LYT8 has 66 fields
	{
		MessageBox(NULL, "You've entered wrong 'Part ID'.", "Error", MB_OK|MB_TOPMOST);
		DisplayErrorMessage("You've entered 'Part ID' = ", g_Part_ID_Trimops, ". We do not have this product.  Please re-enter the correct Part ID");	
		//g_DevNum_Trimops = -99;
		return;
	}

	// Verify Trim options table revision
	Table_Rev_Trimops = trimops->GetRevision();
	if(strcmp(Table_Rev_Trimops, "0.1") ) //Only accept the correct revision table
	{
		MessageBox(NULL, "Program can not run.  Trim Option Table is not the correct Revision", "Error", MB_OK|MB_TOPMOST);
		DisplayErrorMessage("Trim Option Table Revision is '", Table_Rev_Trimops, "', Wrong Revision!\n");
		exit(0);
	}
	int trimops_num =5; //start at column 5 "BV" for LYT8 Trimops table

	//Charles temporary put targets here.  Retrieve targets from trimops table once it's available.

	// Retreive Trim option values
	// Set trim option values as Long and double
	////////g_DevFamily_Trimops = trimops->GetTrimOpAsLong(trimops_num++); // Family.  Device Family (1=CE, 2=CP, 6=EP) //
	//g_Hcode_Trimops	 = trimops->GetTrimOpAsLong(trimops_num++); // Hcode. // "Will need to differentiate HX,HC,HE code"
	//g_Hcode_Trimops									= trimops->GetTrimOpAsLong(trimops_num++); // Hcode. // "Will need to differentiate HX,HC,HE code"
	g_BV_Trimops									= trimops->GetTrimOpAsLong(trimops_num++); // BV.  (6=650V, 7=725V)
	g_FET_Size_Trimops								= trimops->GetTrimOpAsLong(trimops_num++); // FET Size.  (2 to 8) 
	gP_Reserved_Trimops								= trimops->GetTrimOpAsLong(trimops_num++); // Register Reserved bits 0 to 7
	//trimops_num++; //ignore Reserved column for now.
	gP_Trim_AR_SKIP_time_Trimops					= trimops->GetTrimOpAsLong(trimops_num++); //   "AR SKIP time"
	gP_Trim_Disable_TON_foldback_Trimops			= trimops->GetTrimOpAsLong(trimops_num++); //   "TON foldback"
	gP_Trim_AR_OFF_TIME_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //   "AR Off TIME"
	gP_Trim_START_UP_FREQ_Trimops					= trimops->GetTrimOpAsLong(trimops_num++); //   "START-UP FREQ"
	gP_Trim_Enable_Shunt_during_Cap_Select_Trimops	= trimops->GetTrimOpAsLong(trimops_num++); //   "Shunt during Cap Select"
	gP_Trim_RCV_threshold_Trimops					= trimops->GetTrimOpAsLong(trimops_num++); //	"Receiver threshold"
	gP_Trim_GaN_Mode_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"GaN Mode"
	gP_Trim_Sense_Voltage_ILIM_Trimops				= trimops->GetTrimOpAsLong(trimops_num++); //	"Sense voltage ILIM"
	gP_Trim_Driver_Size_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"Driver Size"
	gP_Trim_AR_ON_time_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"AR ON time"
	gP_Trim_GaN_On_Delay_Trimops					= trimops->GetTrimOpAsLong(trimops_num++); //	"GaN On Delay"
	gP_Trim_ILIMTC_Trimops							= trimops->GetTrimOpAsLong(trimops_num++); //	"ILIMTC"
	gP_Trim_Bandgap_TSD_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"Bandgap TSD Target @ 150C"
	gP_Trim_DOPL_mode_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"DOPL mode"
	gP_Trim_Disable_ILIM_cap_Select_Trimops			= trimops->GetTrimOpAsLong(trimops_num++); //	" ILIM cap Select"
	gP_Trim_Set_ILIMP_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"Set ILIM+ if ZTM<55> timmmed"
	gP_Trim_Junction_Start_Temp_Trimops				= trimops->GetTrimOpAsLong(trimops_num++); //	"Junction Start Temp Target @ 100C"
	gP_Trim_Junction_TSD_Trimops					= trimops->GetTrimOpAsLong(trimops_num++); //	"Junction TSD Target @ 150C"
	gP_Trim_iUV_10pct_Trimops						= trimops->GetTrimOpAsLong(trimops_num++); //	"iUV10%"
	gP_iOVp_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6; // iOV+		Target  (uA)
	gP_iOVm_TARGET_Trimops							= gP_iOVp_TARGET_Trimops - 1.7e-6;				// iOV-		Target  (uA)
	gP_Fosc_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e6;	// FoscP		Target  (MHz)
	gP_TonMin_TARGET_Trimops						= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6;	// TonMin	Target  (us)
	gP_Slope_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6;	// TonSlope	Target  (us/kHz)
	gP_Offset_TARGET_Trimops						= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6;	// TonOfset Target  (us)
	gP_ILIM_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e-3;	// ILIM		Target  (mA)
	gP_iUVp_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6;	// iUV+		Target  (us)
	gP_iUVm_TARGET_Trimops							= trimops->GetTrimOpAsDouble(trimops_num++)*1e-6;	// iUV-		Target  (us)
	gP_VTSstart_TARGET_Trimops						= trimops->GetTrimOpAsDouble(trimops_num++);		// VTSstart	Target  (V)
	gP_Dtemp_TARGET_Trimops							= gP_VTSstart_TARGET_Trimops/5.0*512;			// Dtemp	Target based on 5V, 512 FullScale code

	// Secondary Targets and Feature Trim bits


	// Initialize global variables based on Trimops //
	//gCVtgt_15pct_Higher = 2.0;	//This will prevent FB glitch result to ILIM functions
	

	// Secondary AF global paramters initialize //		
	g_Ilim_Incr_max = gP_ILIM_TARGET_Trimops + 0.275; // ILIM target + 275mA
	g_I2F_S_TARGET = gP_ILIM_TARGET_Trimops *gP_ILIM_TARGET_Trimops * gFOSC_TARGET_S_Trimops * 1e-3;	

	// Setup Hardware ID //
	//HardwareList.VerifyRequiredBoardList();
	//HardwareList.ResetRequiredBoardList();

	//////// Loadboard //
	//////g_LB_type = HardwareList.LoadBoard().CalFactor(2); // OLD(with handwiring)=0, NEW=3 //
	//////if (g_LB_type == 3) // NEW loadboard //
	//////	g_LB_rev_needed = 25;
	//////else // OLD loadboard(with handwiring) //
	//////	g_LB_rev_needed = 18;
	//////HardwareList.RegisterRequiredBoard(CHardwareList::LOADBOARD, gLoadBoard_SubType, g_LB_rev_needed, "Inno_VI LB");

	//////// Contactor board //
	//////g_CB_type = HardwareList.HandlerContactor().CalFactor(2); // OLD(with handwiring)=0, NEW=3 //
	//////if (g_CB_type == 3) // NEW contactor board //
	//////	g_CB_rev_needed = 21; // CB Rev. ATE test variable, trimops table not used. //
	//////else
	//////	g_CB_rev_needed = 11; // CB Rev. ATE test variable, trimops table not used. //
	//////HardwareList.RegisterRequiredBoard(CHardwareList::HANDLERCONTACTORBOARD, gContactor_SubType, g_CB_rev_needed, "Inno3_VI CB");
	//////
	//////// Inductor module //
	//////HardwareList.RegisterRequiredBoard(CHardwareList::INDUCTOR, gInductor_SubType, gInductorRev, "Inno3_VI Inductor");

	gLoadBoard_SubType = HardwareList.LoadBoard().HardwareSubType();
	gLoadBoardRev      = HardwareList.LoadBoard().HardwareRevision();

	gTestBlock_SubType = HardwareList.TestBlock().HardwareSubType();
	gTestBlockRev      = HardwareList.TestBlock().HardwareRevision();

	HardwareList.RegisterRequiredBoard(CHardwareList::LOADBOARD,6300,1,"96pin LYT8/BINNO LB");
	HardwareList.RegisterRequiredBoard(CHardwareList::TESTBLOCK,3600,1,"LYT8/BINNO TB for Rasco");


	if( HardwareList.VerifyRequiredBoardList() )
		g_Setup_OK = 1;
	else
		g_Setup_OK = 0;




	// Setup Digitizer //
	BINNO_Gage_ChanAB_setup(0.10); // Setup for Gage Digitizer Channels A,B trigger level
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void DDD_init()
{
	//HL modified DDD_init for Binno usage.

	Dclk_period = 1e-6; // DDD clock period
	DDD_Vref = 1.5; // DDD voltage reference 2.5V
	if (g_DDD_fast)
	{
		g_Dclk_I2C = 0.41e-6; // I2C DDD clock period. 800kHz. //
	}
	else
	{
		g_Dclk_I2C = 1e-6; // I2C DDD clock period. 330kHz. //
	}
	g_Vref_I2C = 1.5; // I2C DDD voltage reference //
	
	ddd_7->init();
	ddd_7->ddd_set_clock_period(Dclk_period);		
	ddd_7->ddd_set_no_delay();

	// DDD level //
	g_DDD_Low = 0.0; // Save current value //
	g_DDD_High = 0.0; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_connect_drivers();	
	ddd_7->ddd_set_voltage_ref(DDD_Vref);
	//DDD_Load_Patterns();
	//ddd_7->ddd_run_pattern(First_address, g_NextAddr);
	//wait.delay_1_us((int (g_NextAddr- First_address+1)*Dclk_period*1e6) + 5.51); 
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Convert_Decimal_To_Binary(float Decimal_Value, int *BitArray)
//{
//	// Function converts a decimal value into binary number stored in an array.  20 bits maximum. // 
//
//	// Declare Variables //
//	float TempVar = Decimal_Value;
//	int i = 0;
//
//	// Initialize BitArray[30] //
//	for (i=0;i<29;i++)  // Only 30 index locations! //
//	{
//		BitArray[i] = 0;
//	}
//
//	// Convert "byte_data" to array //
//	if (TempVar > 524288 || TempVar == 524288)
//	{
//		BitArray[19] = 1;
//		TempVar = TempVar - 524288;
//	}
//	if (TempVar > 262144 || TempVar == 262144)
//	{
//		BitArray[18] = 1;
//		TempVar = TempVar - 262144;
//	}
//	if (TempVar > 131072 || TempVar == 131072)
//	{
//		BitArray[17] = 1;
//		TempVar = TempVar - 131072;
//	}
//	if (TempVar > 65536 || TempVar == 65536)
//	{
//		BitArray[16] = 1;
//		TempVar = TempVar - 65536;
//	}
//	if (TempVar > 32768 || TempVar == 32768)
//	{
//		BitArray[15] = 1;
//		TempVar = TempVar - 32768;
//	}
//	if (TempVar > 16384 || TempVar == 16384)
//	{
//		BitArray[14] = 1;
//		TempVar = TempVar - 16384;
//	}
//	if (TempVar > 8192 || TempVar == 8192)
//	{
//		BitArray[13] = 1;
//		TempVar = TempVar - 8192;
//	}
//	if (TempVar > 4096 || TempVar == 4096)
//	{
//		BitArray[12] = 1;
//		TempVar = TempVar - 4096;
//	}
//	if (TempVar > 2048 || TempVar == 2048)
//	{
//		BitArray[11] = 1;
//		TempVar = TempVar - 2048;
//	}
//	if (TempVar > 1024 || TempVar == 1024)
//	{
//		BitArray[10] = 1;
//		TempVar = TempVar - 1024;
//	}
//	if (TempVar > 512 || TempVar == 512)
//	{
//		BitArray[9] = 1;
//		TempVar = TempVar - 512;
//	}
//	if (TempVar > 256 || TempVar == 256)
//	{
//		BitArray[8] = 1;
//		TempVar = TempVar - 256;
//	}
//	if (TempVar > 128 || TempVar == 128)
//	{
//		BitArray[7] = 1;
//		TempVar = TempVar - 128;
//	}
//	if (TempVar > 64 || TempVar == 64)
//	{
//		BitArray[6] = 1;
//		TempVar = TempVar - 64;
//	}
//	if (TempVar > 32 || TempVar == 32)
//	{
//		BitArray[5] = 1;
//		TempVar = TempVar - 32;
//	}
//	if (TempVar > 16 || TempVar == 16)
//	{
//		BitArray[4] = 1;
//		TempVar = TempVar - 16;
//	}
//	if (TempVar > 8 || TempVar == 8)
//	{
//		BitArray[3] = 1;
//		TempVar = TempVar - 8;
//	}
//	if (TempVar > 4 || TempVar == 4)
//	{
//		BitArray[2] = 1;
//		TempVar = TempVar - 4;
//	}
//	if (TempVar > 2 || TempVar == 2)
//	{
//		BitArray[1] = 1;
//		TempVar = TempVar - 2;
//	}
//	if (TempVar > 1 || TempVar == 1)
//	{
//		BitArray[0] = 1;
//		TempVar = TempVar - 1;
//	}
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Convert_16bitBinary_To_Decimal(int *BitArray, int &Decimal_Value)
//{
//	// Function converts 16bit binary number stored in an array to a decimal value.  16 bits maximum. //
//	
//	// Convert binary to decimal. //
//	Decimal_Value = (BitArray[15])*32768 + 
//					(BitArray[14])*16384 + 
//					(BitArray[13])*8192 + 
//					(BitArray[12])*4096 + 
//					(BitArray[11])*2048 + 
//					(BitArray[10])*1024 + 
//					(BitArray[9])*512 + 
//					(BitArray[8])*256 + 
//					(BitArray[7])*128 + 
//					(BitArray[6])*64 + 
//					(BitArray[5])*32 + 
//					(BitArray[4])*16 + 
//					(BitArray[3])*8 + 
//					(BitArray[2])*4 + 
//					(BitArray[1])*2 + 
//					(BitArray[0])*1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Convert_8bitBinary_To_Decimal(int *BitArray, int &Decimal_Value)
//{
//	// Function converts 8bit binary number stored in an array to a decimal value.  8 bits maximum. //
//	
//	// Convert binary to decimal. //
//	Decimal_Value = (BitArray[7])*128 + 
//					(BitArray[6])*64 + 
//					(BitArray[5])*32 + 
//					(BitArray[4])*16 + 
//					(BitArray[3])*8 + 
//					(BitArray[2])*4 + 
//					(BitArray[1])*2 + 
//					(BitArray[0])*1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_7_Bit_Pattern(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//
//	DDD_start = g_NextAddr;
//	for (j=6;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_7_Bit_Pattern_45kHz(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//
//	DDD_start = g_NextAddr;
//	for (j=6;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_7_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//
//	DDD_start = g_NextAddr;
//	for (j=6;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_8_Bit_Pattern(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//	
//	DDD_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_8_Bit_Pattern_45kHz(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//	
//	DDD_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_8_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_start, int &DDD_stop)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//	
//	DDD_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_16_Bit_Pattern(int *BitArray, int &DDD_hi_start, int &DDD_hi_stop, int &DDD_lo_start, int &DDD_lo_stop)
//{
//	// This function loads 16 bit pattern to DDD memory. The 16 bit word is split into two 8bit bytes (hi and lo) 
//	// because I2C commands are written 8bits at a time, so a 16bit word is written as two 8bit bytes consecutively. //
//
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//	
//	// Load high byte to DDD memory. //
//	DDD_hi_start = g_NextAddr;
//	for (j=15;j>7;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_hi_stop = g_NextAddr-1;
//
//	// Load low byte to DDD memory. //
//	DDD_lo_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_lo_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Load_16_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_hi_start, int &DDD_hi_stop, int &DDD_lo_start, int &DDD_lo_stop)
//{
//	// This function loads 16 bit pattern to DDD memory. The 16 bit word is split into two 8bit bytes (hi and lo) 
//	// because I2C commands are written 8bits at a time, so a 16bit word is written as two 8bit bytes consecutively. //
//
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//
//	// In "void user_load(void)" function all the pre-loaded ("fixed") DDD 
//	// patterns are loaded to DDD memory. Then, during test program execution, any additional 
//	// DDD patterns are loaded "real-time" as the program is executing, and those 
//	// patterns will always start from the next available DDD address after 
//	// the "fixed" (pre-load) patterns. //
//	if (g_DDD_Load_Finished)
//		g_NextAddr = g_NextAddrFixed;
//	
//	// Load high byte to DDD memory. //
//	DDD_hi_start = g_NextAddr;
//	for (j=15;j>7;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_hi_stop = g_NextAddr-1;
//
//	// Load low byte to DDD memory. //
//	DDD_lo_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==1)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//					g_NextAddr++;
//				}
//			}
//			if(k==2)
//			{
//				if(BitArray[j]==0)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//					g_NextAddr++;
//				}
//				if(BitArray[j]==1)
//				{
//					ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//					g_NextAddr++;
//				}
//			}		
//		}
//	}
//	DDD_lo_stop = g_NextAddr-1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void DDD_Load_Patterns()
//{	
//	int	start_vec=0, stop_vec=0, pulses=0;
//	int t_hi=0, t_lo=0, t_hi_1=0, t_lo_1=0, t_hi_2=0, t_lo_2=0, vec_hi=0, vec_lo=0;
//	int t_lo1p5 = 0;
//	int t_lo2p5 = 0;
//	int t_lo3p5 = 0;
//	int t_hi3p5 = 0;
//	int t_lo3 =0;
//	int t_hi3 = 0;
//	int t_hi3p8 = 0;
//	int t_hi3p6 = 0;
//	int t_hi3p7 = 0;
//	int t_hi3p9 = 0;
//	int t_hi4 = 0;
//	int t_hi_FW =0, t_lo_FW=0, t_hi_FB=0, t_lo_FB=0, FB_vec=0, FW_vec=0;
//	int i=0, j=0, k=0, m=0, n=0, FB_cycle_vec=0, FW_cycle_vec=0, n_FB_cycles=0, n_FW_cycles=0;
//	float t_high=0, t_low=0;
//	float Mclk_in_Mhz=0;
//	int t_hi_Vpin = 0; 
//	int t_lo_Vpin = 0;
//	int t_hi_Vout = 0;
//	int t_lo_Vout = 0;
//	int Vpin_cycle_vec = 0;
//	int Vout_cycle_vec = 0;
//	int n_Vpin_cycles = 0;
//	int n_Vout_cycles = 0;
//	int p = 0;
//	int Vpin_vec = 0;
//	int Vout_vec = 0;
//
//	// FWPK Switching 
//	float t_hi_300kHz =0;
//	float t_hi_1MHz	=0;
//	float t_hi_4us =0;
//	float t_hi_x = 0;
//	float t_hi_MaxHz = 0;
//	float t_hi_MinHz = 0;
//
//	if(Dclk_period !=0) 
//		Mclk_in_Mhz = 1/(Dclk_period*1e6);
//	else Mclk_in_Mhz =0.0;
//
//	// Assign starting address //
//	First_address = 0;
//
//	//-------------------------------------------------------------------
//	//	FW negative pulses   - Loop pulses
//	//  FB 100kHz clk pulses - Loop pulses
//	//-------------------------------------------------------------------
//	//t_hi_FW = 31*Mclk_in_Mhz; t_lo_FW = 4*Mclk_in_Mhz;		// FW   Hi,Low = 31us,4us for Secondary FW looping pulses
//	t_hi_FW		= 6*Mclk_in_Mhz; t_lo_FW   = 6*Mclk_in_Mhz;		// FW   Hi,Low = 31us,4us for Secondary FW looping pulses
//	t_hi_FB		= 9*Mclk_in_Mhz; t_lo_FB   = 1*Mclk_in_Mhz;		// FB   Hi,Low =  9us,1us for Secondary FB looping pulses
//	//t_hi_Vpin	= 1*Mclk_in_Mhz; t_lo_Vpin = 29*Mclk_in_Mhz;	// Vpin Hi,Low =  1us,29us for Secondary Vpin looping pulses
//	//HL made changes due to too narrow pulse (1us) on RS & Turret setup.
//	t_hi_Vpin	= 5*Mclk_in_Mhz; t_lo_Vpin = 25*Mclk_in_Mhz;	// Vpin Hi,Low =  5us,25us for Secondary Vpin looping pulses
//	t_hi_Vout	= 9*Mclk_in_Mhz; t_lo_Vout = 1*Mclk_in_Mhz;		// Vout Hi,Low =  9us,1us for Secondary FB looping pulses
//
//	Vpin_cycle_vec	= t_hi_Vpin + t_lo_Vpin;	//120 vectors for 30us, 1us Lo and 29us High
//	FB_cycle_vec	= t_hi_FB	+ t_lo_FB;		// 40 vectors for 100kHz with 0.25us per vector
//	FW_cycle_vec	= t_hi_FW	+ t_lo_FW;		//140 vectors for 34us,1us Hi/Lo
//	Vout_cycle_vec  = t_hi_Vout + t_lo_Vout;	// 40 vectors for 100kHz with 0.25us per vector
//
//	i =0;
////	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	start_vec	= i; 
//	stop_vec	= 2*Vpin_cycle_vec;	// 2 cycles of Hi/Lo 
//
//	FW_Neg_loop_pulse_start		= start_vec;
//	Vpin_loop_pulse_start		= start_vec;
//	FB_100kHz_loop_pulse_start	= start_vec;
//
//	n_FB_cycles		= stop_vec / FB_cycle_vec;
//	n_Vpin_cycles	= stop_vec / Vpin_cycle_vec;
//	n_FW_cycles		= stop_vec / FW_cycle_vec;
//	n_Vout_cycles   = stop_vec / Vout_cycle_vec;
//
//	for (i= start_vec; i< stop_vec; i++)	// Load FW and FB looping pulses at the same time
//	{
//		n = i/FB_cycle_vec;
//		k = i/Vpin_cycle_vec;
//		m = i/FW_cycle_vec;
//		p = i/Vout_cycle_vec;
//
//		// Define FB, Vpin and FW Hi/Lo
//		if( i <= (n*FB_cycle_vec + t_hi_FB/2 - 1	  )																	)	FB_vec = 1;
//		if( i >= (n*FB_cycle_vec + t_hi_FB/2		  )		  && i <= (n*FB_cycle_vec + t_hi_FB/2 + t_lo_FB-1		)	)	FB_vec = 0;
//		if( i >= (n*FB_cycle_vec + t_hi_FB/2 + t_lo_FB)		  && i <= (n*FB_cycle_vec	+ t_hi_FB-1					)	)	FB_vec = 1;
//		if( i <= (k*Vpin_cycle_vec + t_hi_Vpin/2 - 1		)															)	Vpin_vec = 1;
//		if( i >= (k*Vpin_cycle_vec + t_hi_Vpin/2			) && i <= (k*Vpin_cycle_vec + t_hi_Vpin/2 + t_lo_Vpin-1 )	)	Vpin_vec = 0;
//		if( i >= (k*Vpin_cycle_vec + t_hi_Vpin/2 + t_lo_Vpin) && i <= (k*Vpin_cycle_vec	+ t_hi_Vpin-1				)	)	Vpin_vec = 1;
//		if( i <= (m*FW_cycle_vec + t_hi_FW/2 - 1	  )																	)	FW_vec = 1;
//		if( i >= (m*FW_cycle_vec + t_hi_FW/2		  )		  && i <= (m*FW_cycle_vec + t_hi_FW/2 + t_lo_FW			)	)	FW_vec = 0;
//		if( i >= (m*FW_cycle_vec + t_hi_FW/2 + t_lo_FW)		  && i <= (m*FW_cycle_vec + t_hi_FW-1					)	)	FW_vec = 1;
//		if( i <= (p*Vout_cycle_vec + t_hi_Vout/2 - 1	  )																)	Vout_vec = 1;
//		if( i >= (p*Vout_cycle_vec + t_hi_Vout/2		  )	  && i <= (p*Vout_cycle_vec + t_hi_Vout/2 + t_lo_Vout-1	)	)	Vout_vec = 0;
//		if( i >= (p*Vout_cycle_vec + t_hi_Vout/2 + t_lo_Vout) && i <= (p*Vout_cycle_vec	+ t_hi_Vout-1				)	)	Vout_vec = 1;
//
//		//Making Vout to be the same as FB so only FW,FB,Vpin should be care about below.
//		if( FW_vec==0 && FB_vec==0 && Vpin_vec==0 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0000");
//		if( FW_vec==0 && FB_vec==0 && Vpin_vec==1 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0001");
//		if( FW_vec==0 && FB_vec==1 && Vpin_vec==0 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1010");
//		if( FW_vec==0 && FB_vec==1 && Vpin_vec==1 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1011");
//		if( FW_vec==1 && FB_vec==0 && Vpin_vec==0 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0100");
//		if( FW_vec==1 && FB_vec==0 && Vpin_vec==1 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0101");
//		if( FW_vec==1 && FB_vec==1 && Vpin_vec==0 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1110");
//		if( FW_vec==1 && FB_vec==1 && Vpin_vec==1 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1111");
//	}
//	FW_Neg_loop_pulse_stop		= i-1;
//	FB_100kHz_loop_pulse_stop	= i-1;
//	Vpin_loop_pulse_stop		= i-1;
//	Vout_loop_pulse_stop		= i-1;
//	
//	// ++++++++++++++++++++++++++++++++++++ //
//	// ++++++++++++++++++++++++++++++++++++ //
//	FB_100kHz_100_pulses_start  = i;
//	for(k=0; k<106; k++)
//	{
//		start_vec = i;
//		stop_vec= i + 1*(t_hi_FB+t_lo_FB);
//		for(i=start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi_FB/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo_FB ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi_FB/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			i--;
//		}
//	}
//	
//	FB_100kHz_100_pulses_stop = i-1;
//
//	/*
//	//-------------------------------------------------------------------
//	//	FB 100kHz pulse + RTM pulse for ILIM_NORM test 
//	//  (18 pulses of 100kHz and stop for 30us, then 1 pulse of 100kHz, then stop for >200us, then 3 pulses of 100kHz)
//	//-------------------------------------------------------------------
//	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 9us High, 1us Low
//	i +=50;
//	FB_100kHz_ILIM_pulse_start= i;
//
//	// 18 pulses of 100kHz
//	pulses = 1;
//	while(pulses<=18)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	FB_100kHz_ILIM_18_pulse_stop = i-1;
//
//	// ILIM OFF (FB High) for 30us (including the t_hi/2 from pulse of previous & next, the rest require for FB High would be 30us-9us = 21us)
//	for(j=0; j<((30-9)*Mclk_in_Mhz); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//	
//	// 5 pulse of 100kHz
//	pulses = 1;
//	while(pulses<=5)
//	{
//		start_vec = i; stop_vec= i + 1*(t_hi+t_lo);
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			i--;
//		}
//		pulses++;
//	}
//
//	// ILIM OFF (FB High) for >200us
//	for(j=0; j<(203*t_lo); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//	
//	// 3 pulses of 100kHz
//	pulses = 1;
//	while(pulses<=3)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	FB_100kHz_ILIM_pulse_stop = i-1;
//	*/
//
//	//-------------------------------------------------------------------
//	//	Vpin 100kHz pulse + RTM pulse for ILIM_NORM test 
//	//  (18 pulses of 100kHz and stop for 30us, then 5 pulses of 100kHz, then stop for 200us, then 5 pulses of 100kHz)
//	//-------------------------------------------------------------------
//	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 9us High, 1us Low
//	//i +=50;
//	Vpin_100kHz_ILIM_pulse_start= i;
//
//	// 18 pulses of 100kHz
//	pulses = 1;
//	while(pulses<=18)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//
//	// ILIM OFF (Vpin low) for 30us (including the t_hi/2 from pulse of previous & next, the rest require for Vpin low would be 30us-9us = 21us)
//	for(j=0; j<((30-9)*Mclk_in_Mhz); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//	
//	// 5 pulse of 100kHz
//	pulses = 1;
//	while(pulses<=5)
//	{
//		start_vec = i; stop_vec= i + 1*(t_hi+t_lo);
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			i--;
//		}
//		pulses++;
//	}
//
//	// ILIM OFF (Vpin low) for 200us //
//	for(j=0; j<(195*t_lo); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//	
//	// 5 pulse of 100kHz
//	pulses = 1;
//	while(pulses<=5)
//	{
//		start_vec = i; stop_vec= i + 1*(t_hi+t_lo);
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_100kHz_ILIM_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FB 18kHz pulse. 300 pulses of 18kHz. 
//	//-------------------------------------------------------------------
//	t_hi= 55*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 55us High, 1us Low
//	FB_18kHz_pulse_start= i;
//
//	// 300 pulses of 18kHz
//	pulses = 1;
//	while(pulses<=300)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	FB_18kHz_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FB 125kHz pulses. 250 pulses of 125kHz. 
//	//-------------------------------------------------------------------
//	t_hi= 7*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 7us High, 1us Low
//	FB_125kHz_pulse_start= i;
//
//	// 250 pulses of 125kHz
//	pulses = 1;
//	while(pulses<=250)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	FB_125kHz_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 125kHz pulses. 63 pulses of 125kHz. 
//	//-------------------------------------------------------------------
//	t_hi= 7*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 7us High, 1us Low
//	//i +=50;
//	Vpin_125kHz_pulse_start_X= i;
//
//	// 63 pulses of 125kHz
//	pulses = 1;
//	while(pulses<=63)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX10");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX01");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX10");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_125kHz_pulse_stop_X = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 100kHz pulses. 35 pulses of 100kHz. 
//	//-------------------------------------------------------------------
//	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 9us High, 1us Low
//	Vpin_100kHz_ILIM_pulse_start_X= i;
//
//	// 35 pulses of 100kHz
//	pulses = 1;
//	while(pulses<=35)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_100kHz_ILIM_pulse_stop_X = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 6 clocks. //
//	//-------------------------------------------------------------------
//	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 1us High, 1us Low
//	//i +=50;
//	Vpin_6clocks_start = i;
//
//	// 6 pulses //
//	pulses = 1;
//	while(pulses<=6)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
//			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_6clocks_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 4 clocks. //
//	//-------------------------------------------------------------------
//	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 1us High, 1us Low
//	//i +=50;
//	Vpin_4clocks_start = i;
//
//	// 4 pulses //
//	pulses = 1;
//	while(pulses<=4)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
//			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_4clocks_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 2 clocks. //
//	//-------------------------------------------------------------------
//	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 1us High, 1us Low
//	//i +=50;
//	Vpin_2clocks_start = i;
//
//	// 2 pulses //
//	pulses = 1;
//	while(pulses<=2)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
//			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_2clocks_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 3 negative clocks. //
//	//-------------------------------------------------------------------
//	t_hi= 50*Mclk_in_Mhz; t_lo= 50*Mclk_in_Mhz;	// 50us High, 50us Low
//	//i +=50;
//	Vpin_3NegClocks_start = i;
//
//	// 3 pulses //
//	pulses = 1;
//	while(pulses<=3)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_3NegClocks_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 2 clocks 30usec apart. //
//	//-------------------------------------------------------------------
//	t_hi= 1*Mclk_in_Mhz; t_lo= 29*Mclk_in_Mhz; // 1us High, 29us Low
//	//i +=50;
//	Vpin_30usec_start = i;
//
//	// 2 pulses //
//	pulses = 1;
//	while(pulses<=2)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
//			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_30usec_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 1 clock.  30usec pulse width. //
//	//-------------------------------------------------------------------
//	t_hi= 30*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 30us High //
//	//i +=50;
//	Vpin_one_30us_clock_start = i;
//
//	// 1 pulse //
//	pulses = 1;
//	while(pulses<=1)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
//			i--;
//		}
//		pulses++;
//	}
//	Vpin_one_30us_clock_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FB 100kHz pulses. 5 pulses of 100kHz. 
//	//-------------------------------------------------------------------
//	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz; // 9us High, 1us Low
//	//i +=50;
//	FB_100kHz_pulse_start_5X= i;
//
//	// 5 pulses of 100kHz //
//	pulses = 1;
//	while(pulses<=5)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//			for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//			for(j=0;j<t_hi/2;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//			i--;
//		}
//		pulses++;
//	}
//	FB_100kHz_pulse_stop_5X = i-1;
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// FW peak switch patterns //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	t_hi = 2.0*Mclk_in_Mhz; // 2.0us High //
//	t_lo = 2.0*Mclk_in_Mhz; // 2.00us Low //
//	t_hi3p5 = 3.5*Mclk_in_Mhz; // 3.5us High //
//	t_lo1p5 = 1.5*Mclk_in_Mhz; // 1.5us Low //
//	t_lo2p5 = 2.5*Mclk_in_Mhz; // 2.5us Low //
//	t_lo3p5 = 3.5*Mclk_in_Mhz; // 3.5us Low //
//	t_hi3 = 3.0*Mclk_in_Mhz; // 3.0us High //
//	t_lo3 = 3.0*Mclk_in_Mhz; // 3.0us Low //
//	t_hi_x = 40*Mclk_in_Mhz; // 40us High //
//	t_hi_4us = 4.0*Mclk_in_Mhz; // 4.00us High
//	t_hi3p6 = 3.6*Mclk_in_Mhz; // 3.6us High
//	t_hi3p7 = 3.7*Mclk_in_Mhz; // 3.7us High
//	t_hi3p8 = 3.8*Mclk_in_Mhz; // 3.8us High
//	t_hi3p9 = 3.9*Mclk_in_Mhz; // 3.9us High
//	t_hi4 = 4.0*Mclk_in_Mhz; // 4.0us High
//	t_hi_300kHz	= 1.67*Mclk_in_Mhz; // 1.67us High for 300kHz //
//	t_hi_1MHz = 0.50*Mclk_in_Mhz; // 0.50us High for 1MegaHz //
//	t_hi_MaxHz = 0.25*Mclk_in_Mhz; // 0.25us High for 2MegaHz //
//	t_hi_MinHz = 2.7*Mclk_in_Mhz; // 2.5us High for 200kHz //
//
//	FWPK_300kHz_Ring_start= i;
//	for(j=0;j<t_hi_300kHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 1.67us high //
//	for(j=0;j<t_hi_300kHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 1.67us Low //
//	for(j=0;j<t_hi_300kHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 1.67us high //
//	for(j=0;j<t_hi_300kHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 1.67us Low //
//	for(j=0;j<t_hi_300kHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 1.67us high //
//	for(j=0;j<t_hi_300kHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 1.67us Low //
//	FWPK_300kHz_Ring_stop = i-1;
//
//	// ++++++++++++++++++++++++++++ //
//	// ++++++++++++++++++++++++++++ //
//		
//	FWPK_test_pulses_start1_single= i;
//	for(j=0;j<t_lo1p5 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 1.5us Low //
//	for(j=0;j<t_hi4 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 4us high //
//	FWPK_test_pulses_stop1_single = i-1;
//
//	FWPK_test_pulses_start2_single= i;
//	for(j=0;j<t_lo ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.0us Low //
//	for(j=0;j<t_hi4 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 4us high //
//	FWPK_test_pulses_stop2_single = i-1;
//
//	FWPK_test_pulses_start3_single= i;
//	for(j=0;j<t_lo2p5 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.5us Low //
//	for(j=0;j<t_hi4 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 4us high //
//	FWPK_test_pulses_stop3_single = i-1;
//
//	FWPK_test_pulses_start4_single= i;
//	for(j=0;j<t_lo3 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 3.0us Low //
//	for(j=0;j<t_hi4 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 4us high //
//	FWPK_test_pulses_stop4_single = i-1;
//
//	FWPK_test_pulses_start5_single= i;
//	for(j=0;j<t_lo3p5 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 3.5us Low //
//	for(j=0;j<t_hi4 ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 4us high //
//	FWPK_test_pulses_stop5_single = i-1;
//
//	FWPK_1MHz_Ring_start= i;
//	for(j=0;j<t_hi_1MHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_1MHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_1MHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_1MHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_1MHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_1MHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	FWPK_1MHz_Ring_stop = i-1;
//
//	FWPK_Max_Ring_start= i;
//	for(j=0;j<t_hi_MaxHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MaxHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_MaxHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MaxHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_MaxHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MaxHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	FWPK_Max_Ring_stop = i-1;
//
//	FWPK_Min_Ring_start= i;
//	for(j=0;j<t_hi_MinHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MinHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_MinHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MinHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	for(j=0;j<t_hi_MinHz;j++) {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;} // 2us high //
//	for(j=0;j<t_hi_MinHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} // 2.00us Low //
//	FWPK_Min_Ring_stop = i-1;
//
//	HIZallChannels_start= i;
//	for(j=0;j<t_hi_1MHz ;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXXX");i++;} // HIZ //
//	HIZallChannels_stop = i-1;
//	
//
//	//-------------------------------------------------------------------
//	//	Low, High, TriState Start/Stop patterns
//	//-------------------------------------------------------------------
//	//i +=50;
//
//	Low_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"00XX0000");i++;}
//	Low_pat_stop = i-1;
//
//	Low_XXX_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
//	//i--;
//	Low_XXX_pat_stop = i-1;
//
//	High_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"00XX1111");i++;}
//	High_pat_stop = i-1;
//
//	High_pat_FB_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"00X00010");i++;}
//	//i--;
//	High_pat_FB_stop = i-1;
//
//	//High_pat_FW_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	//for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0100");i++;}
//	//High_pat_FW_stop = i-1;
//
//	HIZ_SDA_SCL_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XX000000");i++;}
//	HIZ_SDA_SCL_stop = i-1;
//
//	SDA_SCL_HIZ_FW_High_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XX000100");i++;}
//	SDA_SCL_HIZ_FW_High_stop = i-1;
//
//	//FWhi_FBhi_Vlow_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	//for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XX000110");i++;}
//	//FWhi_FBhi_Vlow_stop = i-1;
//
//	/*
//	FWhi_FBlow_Vhi_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<10;j++) 
//	{
//		ddd_7->ddd_load_pattern(i,"XX000111");i++;
//	}
//	for(j=0;j<5;j++) 
//	{
//		ddd_7->ddd_load_pattern(i,"XX000101");i++;
//	}
//	FWhi_FBlow_Vhi_stop = i-1;
//	*/
//
//	//-------------------------------------------------------------------
//	//	FB (Low 1us, High X care or > 40us)
//	//-------------------------------------------------------------------
//	t_hi= 35*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;//+++++++++++++++++++++++++
//	//i +=50;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FB_tOVL_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
//
//		i--;
//	}
//	FB_tOVL_stop = i-1;
//
//
//	//Note that the vectors "FW Negative 1st, 2nd, 3rd, and Negative Edge" are in series 
//	//2nd,3rd and Negative in series will be used for VBPS_Reset_Threshold purpose
//
//	//-------------------------------------------------------------------
//	//	FW negative 1st pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	//i +=50;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FW_Neg_1st_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//
//		i--;
//	}
//	FW_Neg_1st_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FW negative 2nd pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FW_Neg_2nd_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//
//		i--;
//	}
//	FW_Neg_2nd_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FW negative 3rd pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FW_Neg_3rd_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
//
//		i--;
//	}
//	FW_Neg_3rd_pulse_stop = i-1;
//
//	//Note that the vectors "FWneg_FBhi_Vlo_1st, 2nd, 3rd, and Negative Edge" are in series //
//	//-------------------------------------------------------------------
//	//	FW negative 1st pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	//i +=50;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FWneg_FBhi_Vlo_1st_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX010");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//
//		i--;
//	}
//	FWneg_FBhi_Vlo_1st_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FW negative 2nd pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FWneg_FBhi_Vlo_2nd_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX010");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//
//		i--;
//	}
//	FWneg_FBhi_Vlo_2nd_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	FW negative 3rd pulse - Single pulse 
//	//-------------------------------------------------------------------
//	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//	FWneg_FBhi_Vlo_3rd_pulse_start= start_vec;
//
//	for (i= start_vec; i< stop_vec; i++)
//	{
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX010");i++;} 
//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX110");i++;}
//
//		i--;
//	}
//	FWneg_FBhi_Vlo_3rd_pulse_stop = i-1;
//
//	//--------------------------------------------------------------------------
//	//	Inno4 Primary - Vpin Clk(Long) pulse: 1us Lo - 10us Hi  - 1us Lo
//	//												 ___________	
//	//										Vpin ___|			|____
//	//--------------------------------------------------------------------------
//	t_high	= 10e-6;
//	t_low	= 2e-6; //1us Low before and after 1us High
//	//t_high	= 11e-6;
//	//t_low	= 3e-6; //1us Low before and after 1us High
//	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
//	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
//	i +=50;
//	start_vec= i; stop_vec= i + vec_hi + vec_lo;	
//
//	AF_Vpin_Clk_pulse_start= start_vec;
//	for (i= start_vec; i< stop_vec; i++)
//	{	
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
//		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
//		i--;
//	}
//	AF_Vpin_Clk_pulse_stop = i-1;
//
//	//-------------------------------------------------------------------
//	//	Vpin 5 clocks for 132kHz 
//	//-------------------------------------------------------------------
//	//												 ___________	
//	//										Vpin ___|			|____
//	//--------------------------------------------------------------------------
//	t_hi= 5.5*Mclk_in_Mhz; 
//	t_lo= 2*Mclk_in_Mhz;	
//	i +=50;
//	start_vec= i; 
//	AF_Vpin_Clk_pulse_start_132kHz= start_vec;
//	pulses = 1;
//	while(pulses<=5)
//	{
//		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
//		for (i= start_vec; i< stop_vec; i++)
//		{
//			for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"00XX0000");i++;}
//			for(j=0;j<t_hi ;j++)   {ddd_7->ddd_load_pattern(i,"00XX0001");i++;} 
//			for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"00XX0000");i++;}
//			i--;
//		}
//		pulses++;
//	}
//	AF_Vpin_Clk_pulse_stop_132kHz = i-1;
//
//	//--------------------------------------------------------------------------
//	//	Inno4 Primary - Vpin Data(Short) pulse: 1us Lo  - 1us Hi - 1us Lo
//	//													________	
//	//										Vpin    ___|		|__
//	//--------------------------------------------------------------------------
//	t_high	= 1e-6;	
//	t_low	= 2e-6; //1us Low before and after 10us High
//	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
//	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
//	i +=50;
//	start_vec= i; stop_vec= i + vec_hi + vec_lo;	
//
//	AF_Vpin_Data_pulse_start= start_vec;
//	for (i= start_vec; i< stop_vec; i++)
//	{	
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
//		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
//		i--;
//	}
//	AF_Vpin_Data_pulse_stop = i-1;
//
//	//--------------------------------------------------------------------------
//	//	Inno3X Secondary - Vout Single pulse: 1us Lo - 10us Hi - 1us Lo
//	//											   _____________	
//	//									Vout   ___|				|__
//	//--------------------------------------------------------------------------
//	t_high	= 10e-6;	
//	t_low	= 2e-6; //1us Low before and after 10us High
//	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
//	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
//	i +=50;
//	start_vec= i; stop_vec= i + vec_hi + vec_lo;	
//
//	/*
//	AF_Vout_pulse_start= start_vec;
//	for (i= start_vec; i< stop_vec; i++)
//	{	
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
//		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX11XX");i++;} 
//		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
//		i--;
//	}
//	AF_Vout_pulse_stop = i-1;
//	*/
//
//	// From here on g_NextAddr will be used to store the next available DDD address, it is a global variable. //
//	g_NextAddr = i;
//
//	// DDD channels //
//	// ddd_7->ddd_load_pattern(i,"ch8,ch7,ch6,ch5,ch4,ch3,ch2,ch1"); //
//	// ch1 = V //
//	// ch2 = FB //
//	// ch3 = FW //
//	// ch4 = Vout //
//	// ch5 = SR //
//	// ch6 = BPS //
//	// ch7 = SDA //
//	// ch8 = SCL //
//	// ddd_7->ddd_load_pattern(g_NextAddr,"SCL,SDA,BPS,SR,Vout,FW,FB,V"); //
//
//	// I2C Start Bit //
//	g_StartBit_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_StartBit_stop = g_NextAddr-1;
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// I2C Start Bit, 45kHz //
//	g_StartBit_start_45kHz = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//
//	g_StartBit_stop_45kHz = g_NextAddr-1;
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	
//	// I2C Start Bit, Force SCL //
//	g_StartBit_start_Force_SCL = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_StartBit_stop_Force_SCL = g_NextAddr-1;
//
//	// I2C Slave Address //
//	Convert_Decimal_To_Binary(g_SlaveAddress, g_binary_array);  // Convert slave address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_7_Bit_Pattern(g_binary_array, g_SlaveAddress_start, g_SlaveAddress_stop); // Load 7 bit pattern to DDD. //
//	Load_7_Bit_Pattern_45kHz(g_binary_array, g_SlaveAddress_start_45kHz, g_SlaveAddress_stop_45kHz); // Load 7 bit pattern to DDD. //
//	Load_7_Bit_Pattern_Force_SCL(g_binary_array, g_SlaveAddress_start_Force_SCL, g_SlaveAddress_stop_Force_SCL); // Load 7 bit pattern to DDD. //
//
//	// I2C Write Bit //
//	g_WriteBit_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_WriteBit_stop = g_NextAddr-1;
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// I2C Write Bit, 45kHz //
//	g_WriteBit_start_45kHz = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_WriteBit_stop_45kHz = g_NextAddr-1;
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//
//	// I2C Write Bit, Force SCL //
//	g_WriteBit_start_Force_SCL = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_WriteBit_stop_Force_SCL = g_NextAddr-1;
//	
//	// I2C Read Bit //
//	g_ReadBit_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	g_ReadBit_stop = g_NextAddr-1;
//
//	// I2C Read HiByte //
//	g_Read_HiByte_start = g_NextAddr;
//	for (j=15;j>7;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//			}
//			if(k==1)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				//g_Read_HiByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				g_Read_HiByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				//g_Read_HiByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//			}
//			if(k==2)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//			}		
//		}
//	}
//	g_Read_HiByte_stop = g_NextAddr-1;
//
//	// I2C Read LoByte //
//	g_Read_LoByte_start = g_NextAddr;
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<3;k++)
//		{
//			if(k==0)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//			}
//			if(k==1)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				//g_Read_LoByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				g_Read_LoByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//				//g_Read_LoByte_Mem[j] = g_NextAddr;
//				g_NextAddr++;
//			}
//			if(k==2)
//			{
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//				ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//				g_NextAddr++;
//			}		
//		}
//	}
//	g_Read_LoByte_stop = g_NextAddr-1;
//
//	// I2C Slave Ack Bit //
//	g_SlaveAck_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	g_SlaveAck_stop = g_NextAddr-1;
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// I2C Slave Ack Bit, 45kHz //
//	g_SlaveAck_start_45kHz = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	g_SlaveAck_stop_45kHz = g_NextAddr-1;
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//
//	// I2C Slave Ack Bit, Force SCL //
//	g_SlaveAck_start_Force_SCL = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"1X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	g_SlaveAck_stop_Force_SCL = g_NextAddr-1;
//
//	// I2C Master Ack Bit //
//	g_MasterAck_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_MasterAck_stop = g_NextAddr-1;
//
//	// I2C Master Nack Bit //
//	g_MasterNack_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	g_MasterNack_stop = g_NextAddr-1;
//
//	// I2C Stop Bit //
//	g_StopBit_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	g_StopBit_stop = g_NextAddr-1;
//
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// I2C Stop Bit, 45kHz //
//	g_StopBit_start_45kHz = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	g_StopBit_stop_45kHz = g_NextAddr-1;
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//
//	// I2C Stop Bit, Force SCL //
//	g_StopBit_start_Force_SCL = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"10000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"11000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"01000000");
//	g_NextAddr++;
//	g_StopBit_stop_Force_SCL = g_NextAddr-1;
//
//	// RDADDR //
//	Convert_Decimal_To_Binary(g_RDADDR, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_RDADDR_start, g_RDADDR_stop); // Load 8 bit pattern to DDD. //
//
//	// FWPK //
//	Convert_Decimal_To_Binary(g_FWPK_reg, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_FWPK_start, g_FWPK_stop); // Load 8 bit pattern to DDD. //
//	
//	// VBEN //
//	Convert_Decimal_To_Binary(g_VBEN, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_VBEN_start, g_VBEN_stop); // Load 8 bit pattern to DDD. //
//	
//	// MINLD //
//	Convert_Decimal_To_Binary(g_MINLD, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_MINLD_start, g_MINLD_stop); // Load 8 bit pattern to DDD. //
//	
//	// VDIS //
//	Convert_Decimal_To_Binary(g_VDIS, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_VDIS_start, g_VDIS_stop); // Load 8 bit pattern to DDD. //
//
//	// Self_Destruct //
//	Convert_Decimal_To_Binary(g_Self_Destruct, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_Self_Destruct_start, g_Self_Destruct_stop); // Load 8 bit pattern to DDD. //
//
//	// Fast_VI_Command //
//	Convert_Decimal_To_Binary(g_Fast_VI_Command, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_Fast_VI_Command_start, g_Fast_VI_Command_stop); // Load 8 bit pattern to DDD. //
//
//	// CVO_mode //
//	Convert_Decimal_To_Binary(g_CVO_mode, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CVO_mode_start, g_CVO_mode_stop); // Load 8 bit pattern to DDD. //
//
//	// CV_reg //
//	Convert_Decimal_To_Binary(g_CV_reg, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CV_start, g_CV_stop); // Load 8 bit pattern to DDD. //
//
//	// OVA //
//	Convert_Decimal_To_Binary(g_OVA, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_OVA_start, g_OVA_stop); // Load 8 bit pattern to DDD. //
//
//	// UVA //
//	Convert_Decimal_To_Binary(g_UVA, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_UVA_start, g_UVA_stop); // Load 8 bit pattern to DDD. //
//	
//	// CDC //
//	Convert_Decimal_To_Binary(g_CDC, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CDC_start, g_CDC_stop); // Load 8 bit pattern to DDD. //
//	Load_8_Bit_Pattern_45kHz(g_binary_array, g_CDC_start_45kHz, g_CDC_stop_45kHz); // Load 8 bit pattern to DDD. //
//
//	// CC_reg //
//	Convert_Decimal_To_Binary(g_CC_reg, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CC_start, g_CC_stop); // Load 8 bit pattern to DDD. //
//	Load_8_Bit_Pattern(g_binary_array, g_CC_start, g_CC_stop); // Load 8 bit pattern to DDD. //
//
//	// VPK_reg //
//	Convert_Decimal_To_Binary(g_VPK_reg, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_VPK_start, g_VPK_stop); // Load 8 bit pattern to DDD. //
//	
//	// OVL //
//	Convert_Decimal_To_Binary(g_OVL, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_OVL_start, g_OVL_stop); // Load 8 bit pattern to DDD. //
//	
//	// UVL //
//	Convert_Decimal_To_Binary(g_UVL, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_UVL_start, g_UVL_stop); // Load 8 bit pattern to DDD. //
//	
//	// CCSCL //
//	Convert_Decimal_To_Binary(g_CCSCL, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CCSCL_start, g_CCSCL_stop); // Load 8 bit pattern to DDD. //
//	
//	// ISSC //
//	Convert_Decimal_To_Binary(g_ISSC, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_ISSC_start, g_ISSC_stop); // Load 8 bit pattern to DDD. //
//	
//	// UVL_Timer //
//	Convert_Decimal_To_Binary(g_UVL_Timer, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_UVL_Timer_start, g_UVL_Timer_stop); // Load 8 bit pattern to DDD. //
//	
//	// Watchdog_Timer //
//	Convert_Decimal_To_Binary(g_Watchdog_Timer, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_Watchdog_Timer_start, g_Watchdog_Timer_stop); // Load 8 bit pattern to DDD. //
//	
//	// g_CVO_response //
//	Convert_Decimal_To_Binary(g_CVO_response, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CVO_response_start, g_CVO_response_stop); // Load 8 bit pattern to DDD. //
//
//	// g_CVO_timer //
//	Convert_Decimal_To_Binary(g_CVO_timer, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_CVO_timer_start, g_CVO_timer_stop); // Load 8 bit pattern to DDD. //
//
//	// g_Interrupt_Mask //
//	Convert_Decimal_To_Binary(g_Interrupt_Mask, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_Interrupt_Mask_start, g_Interrupt_Mask_stop); // Load 8 bit pattern to DDD. //
//
//	// g_OTP //
//	Convert_Decimal_To_Binary(g_OTP, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_OTP_start, g_OTP_stop); // Load 8 bit pattern to DDD. //
//
//	// g_fast_cc_offset //
//	Convert_Decimal_To_Binary(g_fast_cc_offset, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_fast_cc_offset_start, g_fast_cc_offset_stop); // Load 8 bit pattern to DDD. //
//
//	// g_loop_speed_set1 //
//	Convert_Decimal_To_Binary(g_loop_speed_set1, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_loop_speed_set1_start, g_loop_speed_set1_stop); // Load 8 bit pattern to DDD. //
//
//	// g_loop_speed_set2 //
//	Convert_Decimal_To_Binary(g_loop_speed_set2, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_loop_speed_set2_start, g_loop_speed_set2_stop); // Load 8 bit pattern to DDD. //
//
//	// TM_CTRL //
//	Convert_Decimal_To_Binary(g_TM_CTRL, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_TM_CTRL_start, g_TM_CTRL_stop); // Load 8 bit pattern to DDD. //
//	Load_8_Bit_Pattern_Force_SCL(g_binary_array, g_TM_CTRL_start_Force_SCL, g_TM_CTRL_stop_Force_SCL); // Load 8 bit pattern to DDD. //
//
//	// TM_SEL //
//	Convert_Decimal_To_Binary(g_TM_SEL, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_TM_SEL_start, g_TM_SEL_stop); // Load 8 bit pattern to DDD. //
//	
//	// TM_DAC //
//	Convert_Decimal_To_Binary(g_TM_DAC, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_TM_DAC_start, g_TM_DAC_stop); // Load 8 bit pattern to DDD. //	
//
//	// TM_ANA //
//	Convert_Decimal_To_Binary(g_TM_ANA, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_TM_ANA_start, g_TM_ANA_stop); // Load 8 bit pattern to DDD. //
//
//	// EEP_CMD //
//	Convert_Decimal_To_Binary(g_EEP_CMD, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_EEP_CMD_start, g_EEP_CMD_stop); // Load 8 bit pattern to DDD. //
//	
//	// TM_EN //
//	Convert_Decimal_To_Binary(g_TM_EN, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_TM_EN_start, g_TM_EN_stop); // Load 8 bit pattern to DDD. //	
//	Load_8_Bit_Pattern_Force_SCL(g_binary_array, g_TM_EN_start_Force_SCL, g_TM_EN_stop_Force_SCL); // Load 8 bit pattern to DDD. //
//			
//	// EEPROM shadow registers //	
//	// SREG0 //
//	Convert_Decimal_To_Binary(g_SREG0, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG0_start, g_SREG0_stop); // Load 8 bit pattern to DDD. //
//	
//	// SREG1 //
//	Convert_Decimal_To_Binary(g_SREG1, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG1_start, g_SREG1_stop); // Load 8 bit pattern to DDD. //
//	
//	// SREG2 //
//	Convert_Decimal_To_Binary(g_SREG2, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG2_start, g_SREG2_stop); // Load 8 bit pattern to DDD. //
//
//	// SREG3 //
//	Convert_Decimal_To_Binary(g_SREG3, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG3_start, g_SREG3_stop); // Load 8 bit pattern to DDD. //
//
//	// SREG4 //
//	Convert_Decimal_To_Binary(g_SREG4, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG4_start, g_SREG4_stop); // Load 8 bit pattern to DDD. //
//	
//	// SREG5 //
//	Convert_Decimal_To_Binary(g_SREG5, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG5_start, g_SREG5_stop); // Load 8 bit pattern to DDD. //
//
//	// SREG6 //
//	Convert_Decimal_To_Binary(g_SREG6, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_SREG6_start, g_SREG6_stop); // Load 8 bit pattern to DDD. //
//		
//	// Read Back Registers //	
//	// READ0 //
//	Convert_Decimal_To_Binary(g_READ0, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ0_start, g_READ0_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ1 //
//	Convert_Decimal_To_Binary(g_READ1, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ1_start, g_READ1_stop); // Load 8 bit pattern to DDD. //
//
//	// READ2 //
//	Convert_Decimal_To_Binary(g_READ2, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ2_start, g_READ2_stop); // Load 8 bit pattern to DDD. //
//
//	// READ3 //
//	Convert_Decimal_To_Binary(g_READ3, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ3_start, g_READ3_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ4 //
//	Convert_Decimal_To_Binary(g_READ4, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ4_start, g_READ4_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ5 //
//	Convert_Decimal_To_Binary(g_READ5, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ5_start, g_READ5_stop); // Load 8 bit pattern to DDD. //
//
//	// READ6 //
//	Convert_Decimal_To_Binary(g_READ6, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ6_start, g_READ6_stop); // Load 8 bit pattern to DDD. //
//
//	// READ7 //
//	Convert_Decimal_To_Binary(g_READ7, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ7_start, g_READ7_stop); // Load 8 bit pattern to DDD. //
//
//	// READ8 //
//	Convert_Decimal_To_Binary(g_READ8, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ8_start, g_READ8_stop); // Load 8 bit pattern to DDD. //
//
//	// READ9 //
//	Convert_Decimal_To_Binary(g_READ9, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ9_start, g_READ9_stop); // Load 8 bit pattern to DDD. //
//
//	// READ10 //
//	Convert_Decimal_To_Binary(g_READ10, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ10_start, g_READ10_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ11 //
//	Convert_Decimal_To_Binary(g_READ11, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ11_start, g_READ11_stop); // Load 8 bit pattern to DDD. //
//
//	// READ12 //
//	Convert_Decimal_To_Binary(g_READ12, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ12_start, g_READ12_stop); // Load 8 bit pattern to DDD. //
//
//	// READ13 //
//	Convert_Decimal_To_Binary(g_READ13, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ13_start, g_READ13_stop); // Load 8 bit pattern to DDD. //
//
//	// READ14 //
//	Convert_Decimal_To_Binary(g_READ14, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ14_start, g_READ14_stop); // Load 8 bit pattern to DDD. //
//
//	// READ15 //
//	Convert_Decimal_To_Binary(g_READ15, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ15_start, g_READ15_stop); // Load 8 bit pattern to DDD. //
//
//	// READ16 //
//	Convert_Decimal_To_Binary(g_READ16, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ16_start, g_READ16_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ17 //
//	Convert_Decimal_To_Binary(g_READ17, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ17_start, g_READ17_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ18 //
//	Convert_Decimal_To_Binary(g_READ18, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ18_start, g_READ18_stop); // Load 8 bit pattern to DDD. //
//
//	// READ19 //
//	Convert_Decimal_To_Binary(g_READ19, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ19_start, g_READ19_stop); // Load 8 bit pattern to DDD. //
//
//	// READ20 //
//	Convert_Decimal_To_Binary(g_READ20, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ20_start, g_READ20_stop); // Load 8 bit pattern to DDD. //
//
//	// READ21 //
//	Convert_Decimal_To_Binary(g_READ21, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ21_start, g_READ21_stop); // Load 8 bit pattern to DDD. //
//
//	// READ22 //
//	Convert_Decimal_To_Binary(g_READ22, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ22_start, g_READ22_stop); // Load 8 bit pattern to DDD. //
//	
//	// READ40 //
//	Convert_Decimal_To_Binary(g_READ40, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ40_start, g_READ40_stop); // Load 8 bit pattern to DDD. //
//
//	// READ41 //
//	Convert_Decimal_To_Binary(g_READ41, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ41_start, g_READ41_stop); // Load 8 bit pattern to DDD. //
//
//	// READ42 //
//	Convert_Decimal_To_Binary(g_READ42, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ42_start, g_READ42_stop); // Load 8 bit pattern to DDD. //
//
//	// READ43 //
//	Convert_Decimal_To_Binary(g_READ43, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ43_start, g_READ43_stop); // Load 8 bit pattern to DDD. //
//
//	// READ44 //
//	Convert_Decimal_To_Binary(g_READ44, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ44_start, g_READ44_stop); // Load 8 bit pattern to DDD. //
//
//	// READ45 //
//	Convert_Decimal_To_Binary(g_READ45, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ45_start, g_READ45_stop); // Load 8 bit pattern to DDD. //
//
//	// READ46 //
//	Convert_Decimal_To_Binary(g_READ46, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ46_start, g_READ46_stop); // Load 8 bit pattern to DDD. //
//
//	// READ47 //
//	Convert_Decimal_To_Binary(g_READ47, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ47_start, g_READ47_stop); // Load 8 bit pattern to DDD. //
//
//	// READ56 //
//	Convert_Decimal_To_Binary(g_READ56, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ56_start, g_READ56_stop); // Load 8 bit pattern to DDD. //
//
//	// READ57 //
//	Convert_Decimal_To_Binary(g_READ57, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ57_start, g_READ57_stop); // Load 8 bit pattern to DDD. //
//
//	// READ58 //
//	Convert_Decimal_To_Binary(g_READ58, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ58_start, g_READ58_stop); // Load 8 bit pattern to DDD. //
//
//	// READ59 //
//	Convert_Decimal_To_Binary(g_READ59, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ59_start, g_READ59_stop); // Load 8 bit pattern to DDD. //
//
//	// READ60 //
//	Convert_Decimal_To_Binary(g_READ60, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ60_start, g_READ60_stop); // Load 8 bit pattern to DDD. //
//
//	// READ61 //
//	Convert_Decimal_To_Binary(g_READ61, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ61_start, g_READ61_stop); // Load 8 bit pattern to DDD. //
//
//	// READ62 //
//	Convert_Decimal_To_Binary(g_READ62, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	Load_8_Bit_Pattern(g_binary_array, g_READ62_start, g_READ62_stop); // Load 8 bit pattern to DDD. //
//
//	// SDA and SCL low.  All other DDD channels also low. //
//	g_SDA_SCL_Low_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"00000000");
//	g_NextAddr++;
//	g_SDA_SCL_Low_stop = g_NextAddr-1;
//
//	// SDA and SCL HIZ.  All other DDD channels low. //
//	g_SDA_hiz_SCL_low_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"0X000000");
//	g_NextAddr++;
//	g_SDA_hiz_SCL_low_stop = g_NextAddr-1;
//
//	// SDA and SCL HIZ.  All other DDD channels low. //
//	g_SDA_hiz_SCL_hiz_start = g_NextAddr;
//	ddd_7->ddd_load_pattern(g_NextAddr,"XX000000");
//	g_NextAddr++;
//	ddd_7->ddd_load_pattern(g_NextAddr,"XX000000");
//	g_NextAddr++;
//	g_SDA_hiz_SCL_hiz_stop = g_NextAddr-1;
//
//	// Next available DDD address is g_NextAddr. //
//	// After the DDD_Load_Patterns() function is finished, then all the 
//	// fixed DDD patterns have been loaded.  All additional patterns are loaded "real-time" per device.
//	// The g_NextAddrFixed variable is the starting address for all "real-time" patterns. //
//	g_NextAddrFixed = g_NextAddr;
//
//	g_DDD_Load_Finished = true;
//}
//
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//
//void DDD_load_scan_pattern(int Start_Address, int Stop_Address)
//{
//	
//    string Scan_Pattern_DDD;
//
//	int i ;//
//
//
//	
//	for( i = Start_Address;i<=Stop_Address;i++)
//	{
//		const char Bit0 = Store_Pattern[g_row_load][0];
//		const char Bit1 = Store_Pattern[g_row_load][1];
//		const char Bit2 = Store_Pattern[g_row_load][2];
//		const char Bit3 = Store_Pattern[g_row_load][3];
//		const char Bit4 = Store_Pattern[g_row_load][4];
//		const char Bit5 = Store_Pattern[g_row_load][5];
//		const char Bit6 = Store_Pattern[g_row_load][6];
//		const char Bit7 = Store_Pattern[g_row_load][7];
//		g_row_load++;
//		Scan_Pattern_DDD = Scan_Pattern_DDD + 
//											   Bit0 +
//											   Bit1 +
//											   Bit2 +
//											   Bit3 +
//											   Bit4 +
//											   Bit5 +
//											   Bit6 +
//											   Bit7;
///*		
//		cout << row<<" "<<Bit0<<Bit1<<Bit2<<Bit3<<Bit4<<Bit5<<Bit6<<Bit7<<endl;
//		cout<<"Scan_Pattern_DDD is"<<Scan_Pattern_DDD<<endl;
//		cout<<Store_Pattern[row]<<endl;
//*/
//
//		char *input = new char[9]; 
//		strcpy(input,Scan_Pattern_DDD.c_str());
////		cout<<"input = "<<input;
//		ddd_7->ddd_load_pattern(i,input);		
//		Scan_Pattern_DDD.clear();
//		delete input;
//		
//	}
//}
//
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void DDD_Run_Scan_Pattern(int Start_Address, int Stop_Address)
//{
//	ddd_7->ddd_run_pattern(Start_Address,Stop_Address);
//}
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void DDD_Compare_Pattern(int *g_Fail_address,int Start_Address,int Stop_Address)
//{
//	int Hex_return ;//This is actually a decimal number
//	int remainder,
//		i = 1,
//		count =1;
//	long long binary_return = 0;
//	bool Fail_Pattern = FALSE;
//	bool debug_scan = FALSE;
//	ofstream PatternOut;
//	PatternOut.open("e:\\dl4\\InnoVI_Pattern_output.txt");	
//	PatternOut<<"DDD"<<"    "<<"Vector#"<<"     "<<"O/P DDD"<<"    "<<"DUT O/P"<<"  "<<"Exp O/P"<<"  "<<"DUT I/P" << endl;
//	ofstream ErrorOut;
//	ErrorOut.open("e:\\dl4\\InnoVI_Error_Out.txt");
//	for(int address = Start_Address;address <= Stop_Address; address++)
//	{
//		//Read back the data and then do a compare
//		Hex_return = ddd_7->ddd_read_pattern(address+2);//Readback is always off by one add
//		//convert to binary
//		if(Hex_return != 0)
//		{
//			while(Hex_return!=0)
//			{
//				remainder = Hex_return%2;
//				Hex_return /= 2;
//				binary_return += remainder*i;
//				i *= 10;
//				count++;
//			}
//			count-=1;
//		}else count = 1;//One decimal digit is already 0.
//
//		
//		string Result;
//		ostringstream convert;
//		convert<<binary_return;
//		Result = convert.str();	
//	
//
//
//		if(count < 8)//Need all 8 bits
//		{
//			count = 8 - count;
//			string Zeroes = "0";
//			while(count-1)
//			{
//				Zeroes = Zeroes + "0";
//				count--;
//
//			}
//			Result = Zeroes + Result;
//			if(debug_scan)
//			{
//				PatternOut << address << "   " << (g_row_compare+2)/3 <<"       "<<Result << "        " << Result[3]<<"        "<< Compare_Pattern[g_row_compare][3]<<"        " << Compare_Pattern[g_row_compare][1] <<  endl;
//			}
//
//			if(g_row_compare != 0)//skip very 1st compare
//			{
//				if((Compare_Pattern[g_row_compare][3]!= 'X'))//There are patterns when O/P(SR) is "X" - ignore it.
//				{
//					//Compare
//					if(Result[3] != Compare_Pattern[g_row_compare][3])
//					{
//						Fail_Pattern = TRUE;
//						ErrorOut << address << " " << g_row_compare <<" "<< (g_row_compare+2)/3 << " " << Result << " " << Compare_Pattern[g_row_compare]<<endl;
//						break;					
//					}
//				}
//				g_row_compare = g_row_compare + 2;//only check every 3rd pattern.
//				address = address + 2;//address incremented by one in for loop.
//			}
//		}else
//		{
//			if(debug_scan)
//			{
//				PatternOut << address << "   " << (g_row_compare+2)/3 <<"       "<<Result << "        " << Result[3]<<"        "<< Compare_Pattern[g_row_compare][3]<<"        " << Compare_Pattern[g_row_compare][1] <<  endl;
//			}
//			if(g_row_compare != 0)//skip very 1st compare
//			{
//				if((Compare_Pattern[g_row_compare][3]!= 'X'))//There are patterns when O/P(SR) is "X" - ignore it.
//				{
//					//Compare
//					if(Result[3] != Compare_Pattern[g_row_compare][3])// && (g_row_compare%2 != 0))
//					{
//						Fail_Pattern = TRUE;
//						ErrorOut << address << " " << g_row_compare <<" "<< (g_row_compare+2)/3 << " " << Result << " " << Compare_Pattern[g_row_compare]<<endl;
//						break;					
//					}
//				}
//				g_row_compare = g_row_compare + 2;//only check every 3rd pattern.
//				address = address + 2;//address incremented by one in for loop.
//			}
//		}
//		i = 1;
//		count = 1;
//		binary_return = 0;
//		g_row_compare++;
//	}
//	if(Fail_Pattern)
//	*g_Fail_address = (g_row_compare+2)/3;
//	else *g_Fail_address = 0;
//	PatternOut.close();
//	ErrorOut.close();
//
//}
//
//// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Powerup_to_trim_primary()
{


	////float j = 0;

	////// Initialize DDD
	////// DDD level //
	////g_DDD_Low = 0.1; // Save current value //
	////g_DDD_High = 5.0; // Save current value //
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	////ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	////wait.delay_10_us(100);
	///////VPIN_ovi->disconnect(1); // Disconnect OVI from UV
	////Close_relay(K2); // Primary:	Connect DVI11_0 to Drain pin
	////Close_relay(K12); // Primary:	Connect DDD7_1  to UV pin
	////wait.delay_10_us(400); // 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	////// Drain set to 0V
	//////D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	//////D_dvi->set_current(D_ch, 300.0e-3, RANGE_300_MA);
	//////D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT); // Meas mode only work with autorange

	////// Bpp set 5V for 100us
	//////VBPP_ramp_up(0.0, 5.0, 200e-3); // BPP ramp up from 0 to 5V with 200mV step
	////wait.delay_10_us(50);

	////// Enter write mode, Vpin clock 3 pulses (10us positive) 
	////Force_Vpin_Pulses_nTimes(3);
	////wait.delay_10_us(50);

	////// Drain setup to be able to see AF links and ready for trimming
	////j = 0;
	////while(j<gTrim_Voltage)
	////{
	////	D_dvi->set_voltage(D_ch, j, VOLT_50_RANGE);		//AF Trimming vDrain
	////	wait.delay_10_us(5);
	////	j++;

	////}
	////D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE); // AF Trimming vDrain
	////wait.delay_10_us(200);

	////// Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	////VBPP_ramp_up(5.0, 5.5, 50e-3);		
	////VBPP_ramp_down(5.5, 5, 50e-3);
	////wait.delay_10_us(100);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Powerdown_from_trim_primary()
{
	////D_dvi->set_voltage(D_ch, 0.5, VOLT_10_RANGE); // DVI_11_0
	////wait.delay_10_us(20);
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	////VBPP_ramp_down(3, 0.0, 0.05);
	////wait.delay_10_us(10);
	////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	////wait.delay_10_us(2);
	////VPIN_ovi->connect(1);
	////Open_relay(K2);
	////Open_relay(K12);
	////wait.delay_10_us(200);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Down_Primary()
{
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	////D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0
	////BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	////VBPP_ramp_down(3, 0.0, 0.05);
	////VPIN_ovi->connect(1); // Connect OVI from UV (Also reset to 0V/100uA)
	////VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	////VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void DDD_Clock_UV_Antifuse(int pulse_num)
{
	for(int i=0; i<pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start,AF_Vpin_Clk_pulse_stop);	
		wait.delay_10_us(5);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Trim_Anti_fuse_primary(float *iAF)
{	
	////wait.delay_10_us(50);
	////// Note that vTrim should be already setup from Powerup_to_trim_primary() function
	////// Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
	////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop); // Assert data pulse 
	////wait.delay_10_us(g_trimTime_p);		
	////*iAF = D_dvi->measure_average(5);
	////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop); // Deassert data pulse 
	////wait.delay_10_us(50);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Force_Neg_Pulses_FW_DDD (float High_lev, float Low_lev)
{
	int i=0;
//	int pulse_num = 3;	// If the pulse_num is changed, BPS:Reset-S search will be affected and won't work properly. 
//	From 1.6-9G silicon forward, FW pin will use 3 pulses to  trigger test mode. The first pulse 
//  is to get out of test mode in order to read anti-fuses, 
//	the 2nd and 3rd poulses are to provide the two negative edges to switch the secondary 
//  For normal mode  
//NOTE:   For most power up, the first pulse is applied during BPS power up in Power_Up_Secondary_Normal_Mode
//		  or Power_up_Secondary_Test_Mode functions. This function only applies the two pulses to turn on secondary
//		  to mimic two handshake pulses.

	int start_vec=0, stop_vec=0;	
	int dly=0;

	// DDD level //
	g_DDD_Low = Low_lev; // Save current value //
	g_DDD_High = High_lev; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

	start_vec = FW_Neg_1st_pulse_start;
	stop_vec  = FW_Neg_3rd_pulse_stop-1;

	ddd_7->ddd_run_pattern(start_vec,stop_vec);
	wait.delay_10_us(10);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Force_Neg_Pulses_FW_DDD_x (float High_lev, float Low_lev)
{
	int i=0;
//	int pulse_num = 3;	// If the pulse_num is changed, BPS:Reset-S search will be affected and won't work properly. 
//	From 1.6-9G silicon forward, FW pin will use 3 pulses to  trigger test mode. The first pulse 
//  is to get out of test mode in order to read anti-fuses, 
//	the 2nd and 3rd poulses are to provide the two negative edges to switch the secondary 
//  For normal mode  
//NOTE:   For most power up, the first pulse is applied during BPS power up in Power_Up_Secondary_Normal_Mode
//		  or Power_up_Secondary_Test_Mode functions. This function only applies the two pulses to turn on secondary
//		  to mimic two handshake pulses.

	int start_vec=0, stop_vec=0;	
	int dly=0;

	// DDD level //
	g_DDD_Low = Low_lev; // Save current value //
	g_DDD_High = High_lev; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

	start_vec = FWneg_FBhi_Vlo_1st_pulse_start;
	stop_vec  = FWneg_FBhi_Vlo_3rd_pulse_stop-1;

	ddd_7->ddd_run_pattern(start_vec,stop_vec);
	wait.delay_10_us(10);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Force_Vpin_Pulses_nTimes (int pulse_num)
{
	int i=0;

	int start_vec=0, stop_vec=0;	
	int dly=0;

	start_vec = AF_Vpin_Clk_pulse_start;
	stop_vec  = AF_Vpin_Clk_pulse_stop;
	for( i = 0; i< pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(start_vec,stop_vec);
		wait.delay_10_us(5);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Force_Vpin_Pulses_5_Times (float High_lev, float Low_lev)
{

	int start_vec=0, stop_vec=0;	
	int dly=0;

	// DDD level //
	g_DDD_Low = Low_lev; // Save current value //
	g_DDD_High = High_lev; // Save current value //
	wait.delay_10_us(g_DDDwait);
	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	wait.delay_10_us(g_DDDwait);

	start_vec = AF_Vpin_Clk_pulse_start_132kHz;
	stop_vec  = AF_Vpin_Clk_pulse_stop_132kHz;
	ddd_7->ddd_run_pattern(start_vec,stop_vec);
	wait.delay_10_us(50);	//Need to wait at least 3*35us for DDD to finish running the pattern
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
float Rdson_Buffer_Cal(float res_div_ratio)
{
	float	buf_gain=0.0;
	float	Vbuf_in =0.0;
	float	vsample =0.0;
	float	ChB_vrng=0.0;
	int		vrng_b	=0.0;
	int		iaddr	=0;
	int		lcnt	=0;
	int		vrng_a=0;
	float	ChA_vrng =0.0;
	float	Idmax_exp=0.0, Vdmax_exp=0.0;
	float	ilim_trig_lev=0;
	int i = 0;
////
////	vrng_b = GAGE_PM_5_V;
////	ChB_vrng = 5.0;
////
////	Close_relay(K2);	
////	Close_relay(K10);		// Connect Rdson Buffer to DVI_11_0
////	wait.delay_10_us(300);
////
////	Vbuf_in = 4.875 * res_div_ratio;		// 97.5% of 5V range
////
////	// Stop Primary from switching
////	VBPP_ramp_down(3, 0.0, 0.05);
////	BPP_ovi->set_current(BPP_ch, 30e-3,RANGE_30_MA);
////
////	D_dvi->set_current(D_ch, 30e-3,	RANGE_30_MA);	
////	D_dvi->set_voltage(D_ch, Vbuf_in);			// Auto range
////	//	Set up Buffer Clamp
////	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
////	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop
//////	delay(1);
////
////	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,g_SAMPLE_SIZE); 
//////	delay(2);
////
////	gage_input_control_xp (GAGE_CHAN_B,		// channel
////			GAGE_INPUT_ENABLE,					// enable / disable
////			GAGE_DC,							// coupling
////			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance
//////	delay(2);
////	
////	gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
////			GAGE_DC,							// coupling for ext trig
////			vrng_b,								// range for CHA trigger
////			GAGE_POSITIVE,						// slope
////			1.0,								// 1.0V trigger level 
////	   		g_SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
////	delay(3);
////	
////	Gage_Start_Capture( );
////	delay(2);
////
////	i32Status = CsDo(hSystem, ACTION_FORCE);
////	delay(2);
////
////	Gage_Wait_For_Capture_Complete( );
////	delay(2);
////
////	// Transfer data
////	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
////	delay(2);
////
////	// Save captured data as .awav file. //
////	if (g_Save_Awav_TextDebug_ALL)
////	{
////			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
////			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
////			{	
////				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
////			}
////			CreateAwav(	capture_data_B, // Data array //
////							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
////							20.0e-9, // Sampling period //				 
////							"e:\\dl4\\RdsonBufGain.awav"); // Output file and path //
////			free (capture_data_B);
////	}
////	
////	if (!trig_ok || !data_ok)
////	{
////		buf_gain =0.0;
////		return buf_gain;
////	}
////
////	lcnt =0;
////	vsample =0.0;
////	for (iaddr = 100 ; iaddr<g_SAMPLE_SIZE; iaddr+=25)
////	{
////		vsample += Gage_chan_b_voltage[iaddr];
////		lcnt ++;
////	}
////
////	if (vsample>0.1 && lcnt >0)
////	{
////		vsample /= lcnt;
////		buf_gain = Vbuf_in/vsample;
////	}
////	else
////		buf_gain =0.0;
////
////	//Power down
////	D_dvi->set_voltage(D_ch, 0.0);	// Auto range
////	wait.delay_10_us(10);
////	Open_relay(K10);
////	Open_relay(K2);
////	delay(1);
////
////	Idmax_exp = g_Ilim_Incr_max*g_ILIM_gain *1.2;// Increase 20% to cover the highest ILIM pretrim
////	ilim_trig_lev = 0.10;	// Set a higher trigger level to have a consistency point of capture. HQL 07/08/14
////
////	if(Idmax_exp < 0.5)	
////	{	
////		vrng_a = GAGE_PM_500_MV;
////		ChA_vrng =0.5;
////	}
////	else if(Idmax_exp >= 0.5 && Idmax_exp < 1.0)
////	{		
////		vrng_a = GAGE_PM_1_V;
////		ChA_vrng = 1.0; 
////	}
////	else if(Idmax_exp >= 1.0 && Idmax_exp < 2.0)	
////	{	
////		vrng_a = GAGE_PM_2_V;
////		ChA_vrng = 2.0; 
////	}
////	else if(Idmax_exp >= 2.0)
////	{	
////		vrng_a = GAGE_PM_5_V;
////		ChA_vrng = 5.0;
////	}
////
////	/*
////	//Reset Trigger level for the rest of the program so it won't need to be called again
////	gage_trigger_control_xp (GAGE_CHAN_A,		// trigger source
////			GAGE_DC,							// coupling for ext trig
////			vrng_a,								// range for CHA trigger
////			GAGE_NEGATIVE,						// slope
////			0.1,								// Tigger level in Volt (100mV)
////	   		g_SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
////	*/
	return buf_gain;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_VBPP_th( float* vBPP_pV, float* vBPP_m, float* vBPP_p, float* vBPP_p_iHVoff, float* vBPP_vshuntPUseq, float LowerLimit)
{	
/********************************************************************************************************************************
 *		Priamry: vBPP_PV (1.4mA) --> vBPP_M (-5mA) --> vBPP_P (-1.2mA) --> vBPP_P_iHVoff (200uA) --> vBPP_ShuntPUseq			*
 *																																*
 * 1. Drain=0, BPP=5.0, IBPP=220uA, increase BPP until IBPP jumps to 1.4mA														*
 *    (this is around BPP=5.4V the first level when first powering up.  This is not the VBPP-P, a Vpin threshold for Testmodes)	*
 * 2. Bring BPP down to 5V, turn on Drain=50V through 1K load, IBPP is still positive around 1.2mA,								*
 *    decrease BPP down until IBPP flip sign from 0.6mA to -5mA (this is around 4.5V the first level when BPP goes down VBPP-M)	*
 * 3. Increase BPP to around 5V VBPP-P to see device starts switching															*
 *    (this is the level after 2nd time raise BPP up) IBPP around -1.2mA														*
 * 4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
 * 5. Increase BPP to around 5.4V VBPP-shunt when the device stops switching and IBPP = 11.3mA > 10mA (DE don't need this)		*
 ********************************************************************************************************************************/

////	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
////	float vstart=0, vstop=0, vBPP_P_Expect=0;
////	float ich_th=0;
////	int   lcnt1=0, lcnt2=0, rcnt =0;
////
////	int		dly_BPP_p47uF, dly_BPP_4p7uF;
////	Pulse pulse;
////
////	dly_BPP_p47uF = 1; //ms
////	dly_BPP_4p7uF = 3; //ms
////
////	//vBPP_P_Expect = 5.5;
////	vBPP_P_Expect = LowerLimit;
////
////	//VBPP_ramp_down(3, 0.0, 0.05);
////	//BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);   
////	//BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
////	//wait.delay_10_us(30);
////
////	// ** VBPP_PV
////	lcnt1 =0;
////	lcnt2 =0;
////	ich_th = 1.3e-3;			// threshold to decide if device is switching or not
////
////	VBPP_ramp_up(0.0, 5.0, 100e-3);    //BPP ramp up from 0V to 4.5V in 100mV step    (Needed for -40C)
////	if(BPP_4p7uF) delay(3);
////	if(BPP_p47uF) delay(1);
////	wait.delay_10_us(10);
////	imeas = BPP_ovi->measure_average(5);
////
////	if (imeas >ich_th)
////	{	
////		*vBPP_pV = 0.0;	
////		return;
////	}
////	vstep = 0.1;	// used to be 0.2
////	vfrc = 4.5;
////	while (vstep >=0.1)
////	{
////		if (imeas < ich_th)
////		{	
////			vfrc+=vstep;
////			if (vfrc > 5.6) // Prevent overvoltage on BPP pin //
////			{
////				*vBPP_pV = 0;
////				BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////				return;
////			}
////			BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V); // Starting search point
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////			wait.delay_10_us(10);
////			imeas = BPP_ovi->measure_average(5);
////		}
////		else			
////		{	
////			// Reset device and reduce searching step
////			vfrc -=  1.25* vstep;	// Back down 1.25 step
////			vstep = 0.0025;			// Fine search, used to be 0.01
////			// Reset device
////			VBPP_ramp_down(3, 0.0, 0.05);
////			wait.delay_10_us(10);
////			VBPP_ramp_up(0.0, vfrc, 50e-3);	//BPP ramp up from 0V to vfrc in 50mV step
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////			wait.delay_10_us(10);
////			imeas = BPP_ovi->measure_average(5);				//expect device not switching here.
////			if (imeas >ich_th)
////			{	
////				*vBPP_p = -1.0;	
////				return;
////			}
////			while (imeas < ich_th)
////			{	
////				vfrc+=vstep;
////				if (vfrc > 5.6) // Prevent overvoltage on BPP pin //
////				{
////					*vBPP_pV = 0;
////					BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////					return;
////				}
////				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////				if(BPP_4p7uF) delay(3);
////				if(BPP_p47uF) delay(dly_BPP_p47uF);
////				wait.delay_10_us(10);
////				imeas = BPP_ovi->measure_average(5);
////			}
////		} 
////	}
////
////	*vBPP_pV = vfrc;
////
////
////	// VBPP_M
////
////	D_dvi->set_voltage(D_ch, 45, VOLT_50_RANGE);  
////
////	lcnt1 =0;	
////	lcnt2 =0;
////	ich_th = 0.9e-3;
////
////	BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////	wait.delay_10_us(15);	// JD was 5, tester correlation
////	if(BPP_4p7uF) delay(3);
////	if(BPP_p47uF) delay(dly_BPP_p47uF);
////	imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
////	if (imeas <ich_th)
////	{	
////		*vBPP_m = 0.0;	
////		return;
////	}
////
////	vstep = 0.1;
////	while ((vstep >=0.1) && (vfrc > 2))
////	{
////		if (imeas >ich_th)
////		{	
////			vfrc-=vstep;
////			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////			wait.delay_10_us(10);
////			imeas = BPP_ovi->measure_average(5);	
////		}
////		else			
////		{	
////			vstep = 0.0025;			// Fine search
////			ich_th = 0;
////			while ((imeas > ich_th) && (vfrc > 2))
////			{	
////				vfrc-=vstep;
////				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////				if(BPP_4p7uF) delay(3);
////				if(BPP_p47uF) delay(dly_BPP_p47uF);
////				wait.delay_10_us(15);	// JD was 5, tester correlation
////				imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
////			}
////		} 
////	}
////	*vBPP_m = vfrc;
////
////if (*vBPP_m < 0.0) 
////	*vBPP_m =0.0;
////
////
////// ** VBPP_P
////	lcnt1 =0;
////	lcnt2 =0;
////	ich_th = -2e-3;			// threshold to decide if device is switching or not
////	vstep = 0.1;	// used to be 0.2
////
////	BPP_ovi->set_voltage(BPP_ch, vfrc-10e-3,	RANGE_10_V);
////	wait.delay_10_us(5);
////	imeas = BPP_ovi->measure_average(5);
////
////	while (vstep >=0.1)
////	{
////		if ( imeas<ich_th && vfrc<(vBPP_P_Expect-150e-3) )
////		{	
////			vfrc+=vstep;
////			if (vfrc > 5.6) // Prevent overvoltage on BPP pin //
////			{
////				*vBPP_p = 0;
////				BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////				return;
////			}
////			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////			wait.delay_10_us(10);
////			imeas = BPP_ovi->measure_average(5);
////		}
////		else			
////		{	
////			vstep = 0.0025;			// Fine search, used to be 0.01
////			while (imeas < ich_th)
////			{	
////				vfrc+=vstep;
////				if (vfrc > 5.6) // Prevent overvoltage on BPP pin //
////				{
////					*vBPP_p = 0;
////					BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////					return;
////				}
////				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////				if(BPP_4p7uF) delay(3);
////				if(BPP_p47uF) delay(dly_BPP_p47uF);
////				wait.delay_10_us(10);
////				imeas = BPP_ovi->measure_average(5);
////			}
////		} 
////	}
////
////	*vBPP_p = vfrc;
////
////	// Take anothe measurement to get more accurate value //
////	wait.delay_10_us(100);
////	imeas = BPP_ovi->measure_average(5);
////
//////4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
////// ** VBPP_P_iHVoff
////	lcnt1 =0;
////	lcnt2 =0;
////	ich_th = 170e-6;	//change from -1.2mA to 200uA.  170uA set as threshold
////
////	vstep = 2.5e-3;		
////	while (imeas < ich_th )
////	{	
////		vfrc+=vstep;
////		if (vfrc > 5.6) // Prevent overvoltage on BPP pin //
////		{
////			*vBPP_p_iHVoff = 0;
////			BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
////			return;
////		}
////		BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////		if(BPP_4p7uF) delay(3);
////		if(BPP_p47uF) delay(dly_BPP_p47uF);
////		wait.delay_10_us(15);	// JD was 5, tester correlation
////		imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
////	}
////
////	*vBPP_p_iHVoff = vfrc;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_VBPS_P_th( float* vBPS_p, int Measure_BPS_IS1_nsw_s)
{	
/**************************************************************************************
 *					Secondary: VBPS_P_Init, VBPS_M_Init, VBPS_HYS_Init				  *
 *							 : VBPS_P,      VBPS_M,      VBPS_HYS					  *
 *VBPS_Init_P:																		  *
 * Chip consumption is the same at different states for secondary when device is not  *
 * switching. Power up FW pin to see state transition by checking charge current. 	  *
 * NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  *
 *                           +200uA													  *			
 *				 -20mA /----------------											  *
 *					  /											            		  *	
 *	BPS Pin			 /	                                                              *
 *	FW =9.5V   	    /                                                                 *
 **************************************************************************************/
	////float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	////float ich_th=0, IBPS_nsw=0;
	////int lcnt1=0, lcnt2=0;
	////Pulse pulse;


	////lcnt1 =0;
	////lcnt2 =0;
	////vramp_pt =3.5;
	////vfrc = vramp_pt;
	////ich_th = 0.0; // threshold 0mA  From neg to positive at transtion pt
	////BPS_dvi->set_voltage(BPS_ch, vfrc, VOLT_10_RANGE); // Starting search point
	////BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT);
	////wait.delay_10_us(30);

	////imeas = BPS_dvi->measure();

	////if (imeas >ich_th)
	////{	
	////	*vBPS_p = 0.0;	
	////	return;
	////}

	////vstep = 0.2;
	////while ((vstep >0.1) && (vfrc < 5.4) && (lcnt1< 200))
	////{
	////	if (imeas <ich_th)		// imeas is negative 
	////	{	vfrc+=vstep;
	////		BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
	////		wait.delay_10_us(60);
	////		imeas = BPS_dvi->measure_average(5);
	////	}
	////	else			
	////	{	// Reset device and reduce searching step
	////		vfrc -= 2.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
	////		vstep = 0.01;			// Fine search

	////		// Don't need to reset device
	////		// But make sure only ramp one way to avoid comparator Hyst[about 0.2V](Not VBPS Hyst [about 0.5V])
	////		BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	
	////		wait.delay_10_us(60);
	////		imeas = BPS_dvi->measure();				// Should be negative
	////		if (imeas >ich_th)
	////		{	
	////			*vBPS_p = -1.0;	
	////			return;
	////		}
	////		while ((imeas < ich_th) && (vfrc <5.4) && (lcnt2<200) )
	////		{	vfrc+=vstep;
	////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
	////			wait.delay_10_us(10);
	////			imeas = BPS_dvi->measure_average(5);		
	////			lcnt2++;
	////		}
	////	} 
	////	lcnt1 ++;
	////}

	////*vBPS_p = vfrc;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_VBPS_M_th_Inno4( float* vBPS_m)
{
/****************************************************************************************
 *					Secondary: VBPS_M_Init, VBPS_M										*
 * VBPS_Init:																			*
 *	- Continue from VBPS_P (BPS no longer have current sink from FW)					*
 *	- Set Vout to 5V																	*
 *	- Reduce VBPS until FW current source current again to BPS							*
 ****************************************************************************************/
	////float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	////float iFW_th=0, iFW=0;
	////int   lcnt1=0, lcnt2=0;

	//////VO set to 5V
	////VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA); // DVI_9_0 //
	////wait.delay_10_us(10);
	////VO_dvi->set_voltage(VO_ch, 5, VOLT_50_RANGE); // DVI_9_0 //
	////wait.delay_10_us(20);

	////// Add load to uVCC to prevent uVCC pin breaking into oscillation. //
	////uVCC_ovi->set_voltage(uVCC_ch, 1.0, RANGE_10_V); // OVI_3_2 //
	////uVCC_ovi->set_current(uVCC_ch, 1e-3, RANGE_30_MA); // OVI_3_2 //

	//////Setup to measure FW current 
	////FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
	////wait.delay_10_us(10);
	////iFW = FW_dvi->measure_average(5);	   // expect FW not sourcing any current to BPS (less than 50uA)

	////lcnt1 =0;
	////lcnt2 =0;

	//////VBPS_M typical = 3.8V
	////vramp_pt = gVBPS_P_Init - 100e-3;
	////vfrc = vramp_pt;
	////iFW_th = 5e-3; // 5mA threshold to determine switching or not (request from DE)


	////BPS_dvi->set_voltage(BPS_ch, vfrc, VOLT_10_RANGE); // Starting search point
	////wait.delay_10_us(30);

	////imeas = FW_dvi->measure_average(5);

	////if (imeas >iFW_th) // Jump out of search loop if FW is sourcing (Device not switching)
	////{	
	////	*vBPS_m = 0.0;	
	////	return;
	////}

	////vstep = 0.2;
	////while ((vstep >0.1) && (vfrc > 3.0) && (lcnt1< 200))
	////{
	////	if (imeas <iFW_th)		// imeas is positive
	////	{	
	////		vfrc-=vstep;
	////		BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
	////		wait.delay_10_us(50);
	////		imeas = FW_dvi->measure_average(5);
	////	}
	////	else			
	////	{	
	////		// Reset device and reduce searching step
	////		//FW set 0V (Need to take out sourcing supply when BPS at low voltage, else BPS go down too slowly to 0V)
	////		FW_dvi->set_voltage(FW_ch, 0.0, VOLT_10_RANGE);	 
	////		wait.delay_10_us(10);
	////		VBPS_ramp_down(vfrc, 0, 200e-3);
	////		VBPS_ramp_up(0, gVBPS_P_Init+300e-3, 100e-3);
	////	//	imeas = FW_dvi->measure_average(5); // FW should NOT be sourcing more than 50mA 

	////		// FW set 6V (sourcing BPS before it reach VBPS-P)
	////		FW_dvi->set_voltage(FW_ch, 6.0, VOLT_10_RANGE);	 
	////		wait.delay_10_us(10);

	////		// Setup search //
	////		vfrc += 1.5* vstep; // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
	////		vstep = 0.01; // Fine search

	////		// Set BPS to start search //
	////		VBPS_ramp_down(gVBPS_P_Init+100e-3, vfrc, 50e-3);
	////		wait.delay_10_us(100);
	////		imeas = FW_dvi->measure_average(5); // FW should NOT be sourcing more than 50mA 

	////		if (imeas >iFW_th) // True if device is not switching
	////		{	
	////			*vBPS_m = -1.0;	
	////			return;
	////		}
	////		while ((imeas < iFW_th) && (vfrc >3.0) && (lcnt2<200) )
	////		{	
	////			vfrc-=vstep;
	////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
	////			wait.delay_10_us(10);
	////			imeas = FW_dvi->measure_average(5);
	////			lcnt2++;
	////		}
	////	} 
	////	lcnt1 ++;
	////}
	////*vBPS_m = vfrc;	
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_VBPS_Reset(float *VBPS_Reset)
{
	////// Declare variables //
	////float vfrc =0.0, vstep =0.0;
	////float imeas =0.0, imeas_BPS=0.0;
	////float IBPS_sw=0;
	////int i=0, lcnt=0;
	////float vfrc_lo=0, tmeas=0;
	////Pulse pulse;

	////vfrc = gVBPS_M_Init-.01;
	////vstep = 20e-3;
	////
	////// Make sure that have not tripped the reset threshold yet. //
	////VBPS_ramp_down(gVBPS_final, vfrc, 10e-3); // Needs to ramp down to prevent undershoot //
	////wait.delay_10_us(20);
	////BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1 //
	////wait.delay_10_us(100);
	////ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_2nd_pulse_stop-1);
	////wait.delay_10_us(20);
	////tmu_6->arm();						
	////wait.delay_10_us(30);				
	////tmeas = tmu_6->read();
	////if (tmeas < 1e-6)
	////{
	////	*VBPS_Reset = 0.0;
	////	return;
	////}

	////// VBP_P drops when secondary has control //
	////BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final+0.1, RANGE_10_V); // prevent undershoot //
	////wait.delay_10_us(8);
	////BPP_ovi->set_voltage(BPP_ch, g_VBPP_P_s_final, RANGE_10_V);
	////wait.delay_10_us(10);

	////lcnt=0;
	////while (tmeas>1e-6 && lcnt<300 && vfrc>1)
	////{
	////	vfrc -= vstep;
	////	VBPS_ramp_down(gVBPS_final, vfrc, 10e-3); // Needs to ramp down to prevent undershoot
	////	wait.delay_10_us(20);
	////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE); // DVI_9_1  (8" EPSON require higher)
	////	wait.delay_10_us(80);
	////	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_2nd_pulse_stop);
	////	wait.delay_10_us(20);
	////	tmu_6->arm();						
	////	wait.delay_10_us(30);				
	////	tmeas = tmu_6->read();
	////	lcnt++;
	////}
	////*VBPS_Reset = vfrc;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_VBPP_Reset(float *VBPP_Reset)
{
	////float vforce =0.0, vramp =0.0, vstep =0.0;
	////float imeas =0.0;
	////int FINE_SEARCH=0;
	////int	lcnt =0;
	////float imeasure = 0;
	////float tmeasure = 0;

	////VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	////wait.delay_10_us(30);
	////imeasure = VPIN_ovi->measure_average(15);
	////wait.delay_10_us(1);

	////if (imeasure < 1.0e-6)		// Device should be switching here. Doing auto restart
	////{	lcnt = 999;	
	////	*VBPP_Reset = 999.0;
	////}
	////else
	////	lcnt =0;
	////vforce = gVBPP_M_Init - 1.0;	// ~3.3V starting point, threshold is ~3.0V
	////vstep = 0.01;
	////FINE_SEARCH = 1;
	////lcnt = 0;

	////while (imeasure > 1.0e-6 && vforce > 2.0 && lcnt<200 )
	////{
	////	lcnt += 1;
	////	vforce -= vstep;

	////	// JD ramp BPP down and look for a change in Vpin current
	////	BPP_ovi->set_voltage(BPP_ch, vforce, 	RANGE_10_V);	// OVI_1_0
	////	wait.delay_10_us(20);
	////	imeasure = VPIN_ovi->measure_average(15);	
	////}

	////*VBPP_Reset = vforce;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_SR_th(float *SR_th, float LowerLimit)
{
////	// Declare Variables // 
////	float vSR =0.0;
////	float vfrc=0.0;
////	float vstep=0.0;
////	Pulse pulse;
////
////	// Set FW low to start //
////	FW_dvi->set_voltage(FW_ch, -200e-3, VOLT_1_RANGE); 
////	wait.delay_10_us(50);
////	vSR = SR_dvi2k->measure(); // Should be low //
////
////	if (vSR > 2.5)
////	{
////		*SR_th = 999.0;
////		return;
////	}
////
////	// FW set closer to threshold smoothly //
////	vfrc = LowerLimit - 50e-3;
////	while(vfrc < LowerLimit)
////	{
////		FW_dvi->set_voltage(FW_ch, vfrc, VOLT_1_RANGE); 
////		wait.delay_10_us(2);
////		vfrc += 1e-3;
////	}
////	vfrc = LowerLimit;
////	vstep = 0.1e-3;
//////float V_FW_force = vfrc;
////	while( vSR < 2.5 && vfrc < 25e-3)
////	{
////		
//////		
//////while(V_FW_force < vfrc)
//////{
//////	FW_dvi->set_voltage(FW_ch, V_FW_force, VOLT_1_RANGE);
//////	wait.delay_10_us(30);
//////	V_FW_force += .01e-3;
//////}
////		
//////		
////		
////		FW_dvi->set_voltage(FW_ch, vfrc, VOLT_1_RANGE);
////		wait.delay_10_us(30);
////		vSR = SR_dvi2k->measure();
////		vfrc+=vstep;
////	}
////	*SR_th = vfrc - vstep;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPP_ramp_up(float vstart, float vstop, float vstep)
{	
	while( vstart < (vstop-vstep) ) // Ramp up VBPP to reduce overshoot
	{	
		vstart +=vstep;
		BPP_dvi->set_voltage(BPP_ch, vstart, RANGE_10_V); // OVI_1_0
		wait.delay_10_us(5);
	}	
	BPP_dvi->set_voltage(BPP_ch, vstop,	RANGE_10_V);	
	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPP_ramp_down(float vstart, float vstop, float vstep)
{
	while( vstart > (vstop+vstep) ) // Ramp down VBPP to reduce undershoot
	{	
		vstart -=vstep;
		BPP_dvi->set_voltage(BPP_ch, vstart, RANGE_10_V); // OVI_1_0
		wait.delay_10_us(5);
	}	
		BPP_dvi->set_voltage(BPP_ch, vstop,	RANGE_10_V); // OVI_1_0
		wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPP_DVI_ramp_down(float vstart, float vstop, float vstep)
{
	////while( vstart > (vstop+vstep) ) // Ramp down VBPP to reduce undershoot
	////{	
	////	vstart -=vstep;
	////	BPP_DVI->set_voltage(BPP_ch, vstart, VOLT_10_RANGE); // DVI_11_0 
	////	wait.delay_10_us(5);
	////}	
	////	BPP_DVI->set_voltage(BPP_ch, vstop, VOLT_10_RANGE); // DVI_11_0 
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPS_ramp_up(float vstart, float vstop, float vstep)
{
	////while( vstart < (vstop-vstep) ) // Ramp up VBPS
	////{	
	////	vstart +=vstep;
	////	BPS_dvi->set_voltage(BPS_ch, vstart, VOLT_10_RANGE);			
	////	wait.delay_10_us(1);
	////}	
	////	BPS_dvi->set_voltage(BPS_ch, vstop,	VOLT_10_RANGE);			
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPS_ramp_down(float vstart, float vstop, float vstep)
{
	////while( vstart > (vstop+vstep) ) // Ramp down VBPS to reduce undershoot
	////{	
	////	vstart -=vstep;
	////	BPS_dvi->set_voltage(BPS_ch, vstart, VOLT_10_RANGE);			
	////	wait.delay_10_us(2);
	////}	
	////	BPS_dvi->set_voltage(BPS_ch, vstop,	VOLT_10_RANGE);			
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBD_ramp_up(float vstart, float vstop, float vstep)
{
	////while( vstart < (vstop-vstep) ) // Ramp up VBPS
	////{	
	////	vstart +=vstep;
	////	VBD_dvi->set_voltage(VBD_ch, vstart, VOLT_50_RANGE); // DVI_21_0 //		
	////	wait.delay_10_us(1);
	////}	
	////	VBD_dvi->set_voltage(VBD_ch, vstop, VOLT_50_RANGE); // DVI_21_0 //		
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBD_ramp_down(float vstart, float vstop, float vstep)
{
	////while( vstart > (vstop+vstep) ) // Ramp down VBPS to reduce undershoot
	////{	
	////	vstart -=vstep;
	////	VBD_dvi->set_voltage(VBD_ch, vstart, VOLT_50_RANGE); // DVI_21_0 //	
	////	wait.delay_10_us(2);
	////}	
	////	VBD_dvi->set_voltage(VBD_ch, vstop, VOLT_50_RANGE); // DVI_21_0 //
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FW_ramp_up(float vstart, float vstop, float vstep)
{
	////while( vstart < (vstop-vstep) ) // Ramp up VBPS
	////{	
	////	vstart +=vstep;
	////	FW_dvi->set_voltage(FW_ch, vstart, VOLT_10_RANGE); // DVI_11_1
	////	wait.delay_10_us(1);
	////}	
	////	FW_dvi->set_voltage(FW_ch, vstop, VOLT_10_RANGE); // DVI_11_1
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void uVCC_ramp_down(float vstart, float vstop, float vstep)
{
	////while( vstart > (vstop+vstep) ) // Ramp down VBPS to reduce undershoot
	////{	
	////	vstart -=vstep;
	////	uVCC_ovi->set_voltage(uVCC_ch, vstart, RANGE_10_V); // OVI_3_2 //		
	////	wait.delay_10_us(10);
	////}	
	////	uVCC_ovi->set_voltage(uVCC_ch, vstop, RANGE_10_V); // OVI_3_2 //		
	////	wait.delay_10_us(5);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void uVCCrampDown(float Vstart, float Vstop, float Vstep)
{
	////float uVCC_volt = 0;
	////uVCC_volt = Vstart;
	////while(uVCC_volt > Vstop)
	////{
	////	uVCC_ovi->set_voltage(uVCC_ch, uVCC_volt, RANGE_5_V); // OVI_3_2 //
	////	uVCC_volt -= Vstep;
	////	wait.delay_10_us(20);
	////}
	////uVCC_ovi->set_voltage(uVCC_ch, Vstop, RANGE_5_V); // OVI_3_2 //
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void uVCCrampUp(float Vstart, float Vstop, float Vstep)
{
	////float uVCC_volt = 0;
	////uVCC_volt = Vstart;
	////while(uVCC_volt < Vstop)
	////{
	////	uVCC_ovi->set_voltage(uVCC_ch, uVCC_volt, RANGE_10_V); // OVI_3_2 //
	////	uVCC_volt += Vstep;
	////	wait.delay_10_us(20);
	////}
	////uVCC_ovi->set_voltage(uVCC_ch, Vstop, RANGE_10_V); // OVI_3_2 //
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void HVS_ramp_down(float vstart, float vstop, float vstep)
{
	////while( vstart > (vstop+vstep) ) // Ramp down VBPS to reduce undershoot
	////{	
	////	vstart -=vstep;
	////	hvs_15->set_voltage(vstart, RANGE_1_KV);
	////	wait.delay_10_us(10);
	////}	
	////	hvs_15->set_voltage(vstop, RANGE_1_KV);
	////	wait.delay_10_us(5);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPS_Power_Up(float vfinal)
{
	////// For regular handshake involving primary, FW pin is usually switching before VBPS is powered all the way
	////// up to VBPS_P. FW will see the first negative edge before BPS pin power up and reading anti-fuse for post 
	////// trim parameters won't be a problem. Compare this to VBPS_Power_Up_TestModeSelect();
	////BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init-0.1, 	VOLT_10_RANGE);		// DVI_9_1
	////wait.delay_10_us(10);
	////BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);				// DVI_9_1
	////wait.delay_10_us(10);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Secondary(int Mode, double vfinal)	//FB(1V), BPS(0V,vPlus-200mV then vPlus+50mV), FW(continuous clk 1us/34us Low/High)
{
	//////BPS (VBPS_M - 200mV) "Allow bandgap to start up and avoid large charge current from Vout to heat up the device"
	////BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	 
	////BPS_dvi->set_voltage(BPS_ch, 0.0001,	VOLT_10_RANGE);				// DVI_9_1
	////wait.delay_10_us(5);
	//////BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init-0.2, 		VOLT_10_RANGE);				// DVI_9_1
	////BPS_dvi->set_voltage(BPS_ch, 3.56, 		VOLT_10_RANGE);				// DVI_9_1
	////wait.delay_10_us(10);

	//////FW clocking spec is critical with respect to reaching VBPS_Plus.  Once vPlus reached, first negative pulse has to 
	//////happen within 40us, then 2 more negative pulses for Secondary to take in control.  Then the following negative pulses
	//////has to happen after 30us otherwise Secondary will give up control.
	////IS_dvi2k->set_voltage(IS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	////IS_dvi2k->set_current(IS_ch, 20.0e-3,	RANGE_20_MA);
	////FB_ovi->set_current(FB_ch, 30e-3,		RANGE_30_MA);
	////FB_ovi->set_voltage(FB_ch, 1.0, 		RANGE_2_V);				// OVI_1_2
	////wait.delay_10_us(5);

	////if(Mode == Normal_Mode_S)
	////{
	////	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	////	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	////	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	////	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	////	
	////	dvi_13->close_relay(BUS_SENSE1);
	////	dvi_13->close_relay(BUS_FORCE1);
	////	mux_14->close_relay(MUX_3_BUS3);
	////}

	//////Vout (5V)
	////VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	////VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"

	////if(Mode==Normal_Mode_with_FW || Mode==Test_Mode)
	////{
	////	// DDD level //
	////	g_DDD_High = 0.0; // Save current value //
	////	wait.delay_10_us(g_DDDwait);
	////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	////	wait.delay_10_us(g_DDDwait);
	////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
	////	wait.delay_10_us(10);

	////	Close_relay(K21);										// Connect FW pin to DDD, DDD is at 0V
	////	Open_relay(K18);										// Disconnect FW pin from DVI
	////	delay(5);

	////	ddd_7->ddd_stop_pattern();			// stop FW continuous clks
	////	wait.delay_10_us(10);


	////	// DDD level //
	////	g_DDD_Low = -0.5; // Save current value //
	////	g_DDD_High = 0.5; // Save current value //
	////	wait.delay_10_us(g_DDDwait);
	////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	////	ddd_7->ddd_set_hi_level(g_DDD_High); // Will immediately change to this level upon execution
	////	wait.delay_10_us(g_DDDwait);
	////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//FW will start with High
	////	wait.delay_10_us(10);
	////}

	////if(Mode==Normal_Mode_with_FW)
	////{
	////	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
	////	ddd_7->ddd_run_pattern();
	////}

	////if(Mode==Normal_Mode_with_Vout)
	////{
	////	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
	////	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	////}
	////BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);				// DVI_9_1
	////wait.delay_10_us(50);
	////wait.delay_10_us(500);
	////
	////if(Mode==Test_Mode)			//Enter Test_Mode or Write_Mode if FW does not switch within 40us after reaching vPlus
	////{
	////	wait.delay_10_us(10);
	////	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
	////	ddd_7->ddd_run_pattern();
	////	wait.delay_10_us(10);
	////}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Connect_InvSyn_IM(int Vd_Input_Mode)
{	
	/********************************************************************************************
	 * When HV device turns off, Drain always overshoot above pullup level, which caused        *
	 * FW pin to go more negative than desired level, and clamped by the ESD diode. But this    *
	 * does affect the handshake.															    *
	 * Important NOTE: Make sure the rising edge of Drain or falling edge of FW are not longer  *
	 * than 0.5us. That will be at the margin of the communication window.						*
	 * 1.5us after device sees the rising edge of drain, secondary will send communication pulse*
	 * Primary will start looking for the the communication pulse from secondary from 1us to 2us*
	 * window.																					*
	 *			   _																			*
	 *			  / |																			*
	 *			 /  |																			*
	 *	Drain	/   |																			*
	 *----------    ------------------------													*
	 *----------	------------------------													*
	 *	FW		\___|__FW -100mV lev															*
	 *			|\	|				Secondary send												*
	 *			| \_|	       /|Communication pulses /|										*
	 *		    |   -1.5us-	 |/ |	internally		 / |										*
	 *			|------------|  |--------------------| |------									*
	 *          |																				*
	 *          | Primary Window to look for communication signal.								*
     *	    	|--------|       |-------------													*
	 *					1us     2us																*
	 ********************************************************************************************/


////	ovi_1->set_voltage(OVI_CHANNEL_6, 0, VOLT_5_RANGE); 
////	ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
////
////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0, VOLT_20_RANGE); // OVI_1_4
////	InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3, RANGE_30_MA);	
////	wait.delay_10_us(20);
////
////	Close_relay(K8); //Connect InvSyn_IM_IN  to Drain
//////	wait.delay_10_us(220);
////	Close_relay(K19); // Connect InvSyn_IM_OUT to FW pin
////	wait.delay_10_us(300);
////
////	if(Vd_Input_Mode == High_Vd_Input)
////		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0, VOLT_20_RANGE); // OVI_1_4	"Size x8 Vref max = 5V/2 (2.5V), so 3/2 = 1.5V (good margin)"
////	if(Vd_Input_Mode == Low_Vd_Input)
////	{
////		if(g_FET_Size_Trimops==8)
////			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5, VOLT_20_RANGE);	// OVI_1_4	
////		if(g_FET_Size_Trimops==5)
////			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0, VOLT_20_RANGE);	// OVI_1_4	
////		else
////			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5, VOLT_20_RANGE);	// OVI_1_4	
////	}
////	if(Vd_Input_Mode == Low_Load_Vd_Input)
////		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.0, VOLT_20_RANGE); // OVI_1_4	
////
////	if(Vd_Input_Mode == High_Temp_Vd_Input)
////		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4.5,		VOLT_20_RANGE);	// Higher for hot test
////
////	wait.delay_10_us(50);
////	
////	//LT1016 LT/GND pin setup to be below GND so Comparator output can go below GND
////	//ovi_1->set_voltage(OVI_CHANNEL_6, -2, VOLT_5_RANGE); //revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
////	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.2, VOLT_5_RANGE); //revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
////	//ovi_1->set_voltage(OVI_CHANNEL_6, -2.3, VOLT_5_RANGE); //revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
////	ovi_1->set_voltage(OVI_CHANNEL_6, -3, VOLT_5_RANGE);
////
////	wait.delay_10_us(50);
////	
////	//HANDSHAKE_Vref is the reference voltage set for comparator's (+)input terminal.
////	//If Vin(-) > Vin(+), then output goes low to FW pin.  Vin(-) is coming from Drain to MESH FET.
////	//MESH FET is gating at ~11V.  Hence, doesn't matter what Vdrain is, MESH FET's highest output < 11V.
////	//High_Vd is for Drain switching at Hot   temperature with 2x of  Rdson_Rm.	(High_Vd > Rdson_hot*ILIM)
////	//Low_Vd  is for Drain switching at Rooom temperature with normal Rdson_Rm. (Low_Vd  > Rdson_Rm *ILIM)
////	//Note: When Vin(+) set to 8.4V, Vin(-) automatically goes to ~1V.  Maybe it's the comparator itself.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Disconnect_InvSyn_IM()
{	
	////// !!! Make sure Drain voltage is less than +/-12V to avoid damaging InvSyn_IM
	////Open_relay(K19); //Disconnect InvSyn_IM_OUT from FW pin
	////Open_relay(K8); // Disconnect InvSyn_IM_IN from drain		
	////wait.delay_10_us(20);

	////InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0, RANGE_20_V); // OVI_1_4	
	////InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3, RANGE_30_MA);	
	////
	////ovi_1->set_voltage(OVI_CHANNEL_6, 0.0, VOLT_5_RANGE);
	////ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
	////wait.delay_10_us(20);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//=================== INNOSW XP gage digitizer functions ===================
void BINNO_Gage_ChanAB_setup(float ilim_trig_lev)
{
	// Split this setup portion out from Gage_Capture_Ilim() function due to 4ms excution time on each input control
	// and trig control statement. Only excute this once for the whole test program.
	// 03/15/13 - As of today, Gage Razor changing range still takes 34ms. Therefore, only one range is used for the entire program
	//			  for now. In the future, when the new Gage Razor driver without long delay is available,
	//			  this can be modified to adjust ranges for different ILIM. 
	int vrng_a=0, vrng_b=0;
	float ChA_vrng =0.0, ChB_vrng =0.0;
	float Idmax_exp=0.0, Vdmax_exp=0.0;

	if(g_SAMPLE_SIZE > GAGE_WAVEFORM_BUFFER_SIZE)
	{ 
		return;
	}

	Idmax_exp = g_Ilim_Incr_max*g_Ilim_gain *1.2;// Increase 20% to cover the highest ILIM pretrim
	//ilim_trig_lev = 0.10;	// Set a higher trigger level to have a consistency point of capture. HQL 07/08/14

	if(Idmax_exp < 0.5)	
	{	
		vrng_a = GAGE_PM_500_MV;
		ChA_vrng =0.5;
	}
	else if(Idmax_exp >= 0.5 && Idmax_exp < 1.0)
	{		
		vrng_a = GAGE_PM_1_V;
		ChA_vrng = 1.0; 
	}
	else if(Idmax_exp >= 1.0 && Idmax_exp < 2.0)	
	{	
		vrng_a = GAGE_PM_2_V;
		ChA_vrng = 2.0; 
	}
	else if(Idmax_exp >= 2.0)
	{	
		vrng_a = GAGE_PM_5_V;
		ChA_vrng = 5.0;
	}

	vrng_b = GAGE_PM_5_V;
	ChB_vrng = 5.0;

//	Set up Buffer Clamp
	BUFCLMP_ovi->set_current(BUFCLMP_ch, 30e-3,			RANGE_30_MA);
	BUFCLMP_ovi->set_voltage(BUFCLMP_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop

	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,g_SAMPLE_SIZE); 

	gage_input_control_xp (GAGE_CHAN_A,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_a|GAGE_1_MOHM_INPUT);		// range, impedance

	gage_input_control_xp (GAGE_CHAN_B,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance

	gage_trigger_control_xp (GAGE_CHAN_A,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_a,								// range for CHA trigger
			GAGE_NEGATIVE,						// slope
			ilim_trig_lev,						// Tigger level in Volt
	   		g_SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_Ilim(float *Idmax_ave, float *DiDt_ave, float *Ton_ave, float *Rdson_peak_ave, float *Rdson_spec_ave)
{
	*Idmax_ave =0.0;
	*DiDt_ave  =0.0;
	*Ton_ave   =0.0;
	*Rdson_peak_ave =0.0;
	*Rdson_spec_ave =0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*DiDt_ave		=999.0;
		*Ton_ave		=999.0;
		*Rdson_peak_ave =999.0;
		*Rdson_spec_ave =999.0;
		g_ILIM_pct_1stP	= 0.0;
		g_ILIM_pct_2ndP	= 0.0;
		g_ILIM_pct_3rdP	= 0.0;
		return;
	}

	int	PULSE_NUM_NEED  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	float Vdson_peak_ave =0.0;
	float Vped_threshold =0.0;
	
	// Variables for ILIM peak tests
	float ACgnd[400]      ={0.0};
	float ACgnd_Ave[400]  ={0.0};
	float Id05us_Ave[400] ={0.0};
	float pulse_width[400]={0.0};
	float Ton[400]		 ={0.0};
	float Toff[400]		 ={0.0};
	float DiDt[400]		 ={0.0};
	int Id05us_Addr[400]  ={0};
	int ACgnd_addr[400]   ={1000};				// GND is taken before device turns on
	int gnd_addr_offset	= 0;

	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec =0.0;
	float Vdson_spec[400] ={0.0};
	float Idson_spec[400] ={0.0};
	float Rdson_spec[400] ={0.0};
	float Vdson_spec_ave =0.0;
	float Idson_spec_ave =0.0;
	int Id_spec_addr[400] ={0};
	float istep_downdelta = 0.0;

	float Id_temp =0.0;
	float Id_one_data_pts =0.0;
	int	  lcnt =0, i=0;
	int	  ave_start_pulse =0;
	int	  ave_pulses	  =0;
	int	  ave_end_pulse	  =0;

	float Period=0.0;
	int	  Sample_per_cycle=0;
	int   FIND_ILIM_LO_FLAG=0;

	float Off_Time=0.0;
	float RTM_High_Id=0.0,
		  RTM_Low_Id=0.0;

	char wave_name_Id[150] ="/0"; 
	char wave_name_Vd[150] ="/0"; 
	char debug_file_name[150] ="/0"; 



	//if(gFind_ILIM_Jitter)		PULSE_NUM_NEED  =100;	//If fosc = 100kHz, every pulse would take 10us.  100 pulses would take 1ms
	//else						PULSE_NUM_NEED  =26;	//If fosc = 100kHz, every pulse would take 10us.  27  pulses would take 270us

	PULSE_NUM_NEED		= 26;

	Period				= 1/(100e3-10e3);		//Takes care of device with Jitter up to 10kHz from 100kHz
	SAMPLE_RATE_s		= 20e-9;
	Sample_per_cycle	= Period/SAMPLE_RATE_s;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		g_Idmax[icnt]		= -100;
		g_Idmax_addr[icnt]	= 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	if(g_FIND_RDSON_Peak_FLAG || g_FIND_RDSON_Spec_FLAG)
		Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
//	start_addr = 300;					// Skip 6us from negative trigger edge
//	start_addr = 1300;					// Skip the first 3 initial pulses (all 3 of them lower than ILIM)
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < g_SAMPLE_SIZE)
		start_addr+=1;					// Fast forward by 1 samples at rate of 20ns/sample

	start_addr += 8;	//Fast forward by 8 samples (This also jump over the FET turn-on spike)

	// Error check
	if ((start_addr + Sample_per_cycle + 125) > g_SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	{
		*Idmax_ave  = 999.0;
		return;
	}

	FIND_ILIM_LO_FLAG = 1;

	// Search for the peak
	while ((pulse_cnt<= PULSE_NUM_NEED)&& (start_addr < g_SAMPLE_SIZE))
	{
		// Find Idmax
//		for(icnt = start_addr; icnt< start_addr + Sample_per_cycle + 125 ; icnt++)		
		for(icnt = start_addr; icnt< start_addr + 300 ; icnt++)	// To avoid intermittence failure for RDSON reading. HQL 07/08/14	
		{// Searching window = Period + 2.5us(from next pulse). 
			if((Gage_chan_a_voltage[icnt] > g_Idmax[pulse_cnt])&& Gage_chan_a_voltage[icnt]>50e-3)
			{
				g_Idmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
				g_Idmax_addr[pulse_cnt] = icnt;
			}
			//if (MOSFET_SIZE==8 && g_ILIM_TARGET_S > 2.2)
			if(1)
			{
				//First pulse breaks out of loop if Gage_chan_a_voltage starts dropping and greater than 50mV
				if(  FIND_ILIM_LO_FLAG == 1												&&
					(Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -20e-3	&&   //10/16/17. HL problem here to cause wrong ILIM Peak
					 Gage_chan_a_voltage[icnt] > 50e-3										)
				{
					FIND_ILIM_LO_FLAG = 0;
					break;
				}				
			}
			////else
			////{
			////	//First pulse breaks out of loop if Gage_chan_a_voltage starts dropping and greater than 50mV
			////	if(  FIND_ILIM_LO_FLAG == 1												&&
			////		(Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -5e-3	&& 
			////		 Gage_chan_a_voltage[icnt] > 50e-3										)
			////	{
			////		FIND_ILIM_LO_FLAG = 0;
			////		break;
			////	}
			////}

			//break out of loop if Gage_chan_a_voltage starts dropping by 20mA (and greater than 50mV)
			if( ((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -20e-3)	&& 
				 (Gage_chan_a_voltage[icnt] > 50e-3)					)
			{
				break;
			}
		}

		//if(DEBUG==1)
		//	printf("\ngIDmax[%i] = %.1fmA, gIdmax_addr[%i] = %i, ", pulse_cnt, g_Idmax[pulse_cnt]*1000, pulse_cnt, g_Idmax_addr[pulse_cnt]);

		//if(MOSFET_SIZE==2)			Vped_threshold = 0.025;
		//else if(MOSFET_SIZE==5)		Vped_threshold = 0.005;	//Hiep 1/25/2017
		//else						Vped_threshold = 0.05;
		Vped_threshold = 0.005;		//Size 3 with 50mV fail.  Since size5 released to PROD and no complain, make it the same as PROD
		// Find AC Ground level before turn on, count backward from pulse peak until sample less than threshold
		ACgnd[pulse_cnt] = 1000;
		for(icnt = g_Idmax_addr[pulse_cnt]; (icnt> 0) && (Gage_chan_a_voltage[icnt]>=Vped_threshold); icnt--)	//Primary in control
		{
			 ACgnd[pulse_cnt] = Gage_chan_a_voltage[icnt-1];
			 ACgnd_addr[pulse_cnt] = icnt;
		}
		

		gnd_addr_offset = 100;

		ACgnd_Ave[pulse_cnt] = (Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(15+gnd_addr_offset)]+	// 15 samples away from First data point
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(16+gnd_addr_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(17+gnd_addr_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(18+gnd_addr_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(19+gnd_addr_offset)])/5.0;

		// Find 0.5us location from Idmax, pulse width is time from peak back to sample threshold
		pulse_width[pulse_cnt] = g_Idmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt];

		if (pulse_width[pulse_cnt]> 25)		// Pulse > 0.5us
			Id05us_Addr[pulse_cnt] = g_Idmax_addr[pulse_cnt]- 25;	// 0.5us away from Idmax
		else 
			Id05us_Addr[pulse_cnt] = g_Idmax_addr[pulse_cnt] - int(pulse_width[pulse_cnt]/2);

		Id05us_Ave[pulse_cnt] = (Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+2]+	
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]  ]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-2])/5.0;

	
		// Individual Peak result
		Id05us_Ave[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		Id05us_Ave[pulse_cnt]/= g_Ilim_gain;

		g_Idmax[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		g_Idmax[pulse_cnt] /= g_Ilim_gain;

		// A/us
		DiDt[pulse_cnt]	= (g_Idmax[pulse_cnt] - Id05us_Ave[pulse_cnt])/((g_Idmax_addr[pulse_cnt] - Id05us_Addr[pulse_cnt])*SAMPLE_RATE_s*1e6);

		// Ton
			Ton[pulse_cnt]	= pulse_width[pulse_cnt] * SAMPLE_RATE_s;
		// Toff		
		if(pulse_cnt > 3)	//Primary in control (Discount pulses 0,1,2,3)
		{
			Toff[pulse_cnt-1]	= (ACgnd_addr[pulse_cnt] - g_Idmax_addr[pulse_cnt-1])* SAMPLE_RATE_s;

			//Store RTM_Slope information
			if(g_WAVE_NAME == "ILIM_NORM")
			{
				Off_Time = Toff[pulse_cnt-1];
				if( Off_Time > 30e-6 && Off_Time < 50e-6 )	//Expect 40us RTM_Slope drop time or Off_Time
				{
					gRTM_Slope  = 0;	//Should only come into this if condition once
					RTM_High_Id = g_Idmax[pulse_cnt-1];
					RTM_Low_Id	= g_Idmax[pulse_cnt];
					gRTM_Slope  = (RTM_Low_Id - RTM_High_Id)/RTM_High_Id*100/(Off_Time*1e6);
				}
			}
		}

		// Locate Id_spec, Vd_spec location and calculate Rdson_spec
		if(g_FIND_RDSON_Spec_FLAG && DiDt[pulse_cnt] !=0.0 && pulse_cnt > 3)
		{
			Ilim_spec = 0.25 * gP_ILIM_TARGET_Trimops;	

			Id_spec_addr[pulse_cnt] = int(g_Idmax_addr[pulse_cnt] - (g_Idmax[pulse_cnt]- Ilim_spec)/(DiDt[pulse_cnt] *SAMPLE_RATE_s *1e6));
			Id_temp = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/g_Ilim_gain;	//Id_temp must be > 0 since it's 25-30% of ILIM_target
			Id_one_data_pts = DiDt[pulse_cnt] * SAMPLE_RATE_s *1e6; // Amps
			while ((Ilim_spec - Id_temp)> Id_one_data_pts && lcnt < 100)
			{
				Id_spec_addr[pulse_cnt]++;
				Id_temp= Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/g_Ilim_gain;
			}
				Id_spec_addr[pulse_cnt]+=2;	// Move away from ringing

			if ((g_Idmax_addr[pulse_cnt]-Id_spec_addr[pulse_cnt])< pulse_width[pulse_cnt])
			{
				Vdson_spec[pulse_cnt] = Gage_chan_b_voltage[Id_spec_addr[pulse_cnt]]*g_BUFgain;
				Idson_spec[pulse_cnt] = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/g_Ilim_gain;
				if (Idson_spec[pulse_cnt] !=0.0)
					Rdson_spec[pulse_cnt]=Vdson_spec[pulse_cnt]/(Idson_spec[pulse_cnt]);
				else
					Rdson_spec[pulse_cnt] = 0.0;
			}
			else 
				Rdson_spec[pulse_cnt] = 0.0;
		}

		//Reset gIdmax
		if(g_Idmax[pulse_cnt] < -100)
			g_Idmax[pulse_cnt] = -100;

		// Reset start address after find a peak.
		if(g_Idmax[pulse_cnt] > 0)	//only do additional count if it's a true Idmax
		{
			start_addr = g_Idmax_addr[pulse_cnt] + 100;	//Fast forward 100 samples (2us) for the next loop to start 
			PULSE_NUM_PROCESSED ++;
			pulse_cnt ++;
		}

		while (Gage_chan_a_voltage[start_addr]< 35e-3 && start_addr < g_SAMPLE_SIZE)	
			start_addr+=1;					// Fast forward by 200ns/step
//			start_addr+=25;					// Fast forward by 0.5us/step
		start_addr+=9;	// Fast forward 9 samples of 20ns

		if ((icnt< start_addr + Sample_per_cycle + 125) > g_SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse). 
			break;
	}

	// Average Peak results
	if(( PULSE_NUM_PROCESSED>= 16)) //Sometimes the first pulse miss-trigger.  Expect 22 if no missing trigger
	{
		// Number of pulses used for ILIM_ave, Ton_ave, Didt_ave, Vdson_peak_ave, Rdson_spec_ave
		//ave_start_pulse	= 4;	//good for size x8 but not size x5
		ave_start_pulse	= 6;	//good for both size x8 and x5
		ave_pulses		= 10;
		ave_end_pulse	= ave_start_pulse + ave_pulses;
		// Taking average Needed pulses peak values (Must skip the first 3 pulses since they are not at ILIM)
		for (pulse_cnt =ave_start_pulse; pulse_cnt< ave_end_pulse; pulse_cnt++)
		{
			*Idmax_ave+=g_Idmax[pulse_cnt];
			*Ton_ave  +=Ton[pulse_cnt];
			*DiDt_ave +=DiDt[pulse_cnt];

			//PEAK Rdson
			if(g_FIND_RDSON_Peak_FLAG)
				Vdson_peak_ave+=Gage_chan_b_voltage[g_Idmax_addr[pulse_cnt]]*g_BUFgain;

			//SPEC Rdson
			if(g_FIND_RDSON_Spec_FLAG)
				*Rdson_spec_ave+=Rdson_spec[pulse_cnt];
		}

		//PEAK Rdson
		if(g_FIND_RDSON_Peak_FLAG && *Idmax_ave !=0.0)	*Rdson_peak_ave =Vdson_peak_ave/(*Idmax_ave);
		else											*Rdson_peak_ave =999.0;

		//SPEC Rdson
		if(g_FIND_RDSON_Spec_FLAG)	*Rdson_spec_ave /=(ave_pulses+1e-23);
		else						*Rdson_spec_ave =999.0;

		*Idmax_ave /=ave_pulses;
		*Ton_ave   /=ave_pulses;
		*DiDt_ave  /=ave_pulses;
	}
	//return Idmax=999, Ton=999, didt=999
	else	
	{
			*Idmax_ave =999.0;
			*Ton_ave   =999.0;
			*DiDt_ave  =999.0;
			if(DEBUG==1)
				MessageBox(NULL, "Error: PULSE_NUM_PROCESSED is less than PULSE_NUM_NEED",g_Func_name, MB_OK);

	}


	//DEBUG text File
	if(DEBUG==1 && g_Debug)
	{
		int i=0;
		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_");
		strcat (debug_file_name, g_WAVE_NAME);
		strcat (debug_file_name, "_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf(fpr,"WAVE_NAME= %s \n\n",g_WAVE_NAME);

		//measured values
		fprintf(fpr,"ILIM(Idmax_ave) = %.3f A,  *DiDt_ave = %.2f A/us,  *Ton_ave= %.2f us\n",*Idmax_ave,  *DiDt_ave,  *Ton_ave*1e6);

		//RDSon
		if(g_FIND_RDSON_Peak_FLAG)
			fprintf(fpr,"Rdson_peak_ave = %.3f ohms (Vdson_peak_ave=%.3f V , Idmax_ave=%.3f A)\n",
				*Rdson_peak_ave,Vdson_peak_ave/ave_pulses,	*Idmax_ave);

		//pulses
		fprintf(fpr,"\n  PULSE_NUM_PROCESSED=%i\n",PULSE_NUM_PROCESSED);
		if(g_WAVE_NAME == "ILIM_NORM")
		{
			fprintf(fpr,"  ILIM, Ton, didt averaged from pulse %i to pulse %i\n\n", ave_start_pulse,ave_end_pulse);
			fprintf(fpr,"  ILIM_Lo taken from pulse %i\n", PULSE_NUM_PROCESSED-3);
			fprintf(fpr,"  ILIM_Med taken from pulse %i\n", PULSE_NUM_PROCESSED-2);
			fprintf(fpr,"  ILIM_Hi taken from pulse %i\n", PULSE_NUM_PROCESSED-1);
		}

		fprintf(fpr,"\nPeak Data: \n",g_WAVE_NAME);
		//Peak data
		for(i=0; i<PULSE_NUM_PROCESSED; i++)
		{
			if(g_Idmax[i] > 0)
			fprintf(fpr,"ILIM_Pulse %i = %.1fmA, Ton_Pulse = %.1fus, Toff_Pulse = %.1fus, Freq = %.1fkHz, Ton_addr=%i, pk_addr=%i\n", 
				i, g_Idmax[i]*1000, Ton[i]*1e6, Toff[i]*1e6, 1/(Ton[i]+Toff[i])/1000,ACgnd_addr[i],g_Idmax_addr[i]);

			if(g_FIND_RDSON_Peak_FLAG)
			{
				fprintf(fpr,"  Vdson_peak %i = %.3f V \n",i,Gage_chan_b_voltage[g_Idmax_addr[i]]*g_BUFgain);
				fprintf(fpr,"  Rdson_peak %i = %.3f ohm \n",i,(Gage_chan_b_voltage[g_Idmax_addr[i]]*g_BUFgain)/g_Idmax[i]);
			}
		}
		fprintf (fpr, "End of Peaks\n");
		fclose(fpr);

	}


	//DEBUG AWAV Files
	if(DEBUG==1 && g_Debug)
	//if(DEBUG==1)
	{
		strcpy (wave_name_Id, g_WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, g_SAMPLE_SIZE-1, SAMPLE_RATE_s);

		if(g_FIND_RDSON_Peak_FLAG || g_FIND_RDSON_Spec_FLAG)
		{
			strcpy (wave_name_Vd, g_WAVE_NAME);
			strcat (wave_name_Vd, "_Vd"); 
			Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, g_SAMPLE_SIZE-1, SAMPLE_RATE_s);
		}
		g_WAVE_NAME = "NoWaveName";
	}


	// Reset Flags
	g_FIND_RDSON_Peak_FLAG	=0;
	g_FIND_RDSON_Spec_FLAG	=0;
	g_Find_ILIM_Jitter		=0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_Ilim_SSS(float *Idmax_ave, float *tsoft, float *tHandshake, float *fosc_s_min, float *fosc_s_max, float *ilim_min, float *ilim_max, float *fModulation_P, float *Fosc_Sss_P, float UppLimFoscMin, float LowLimFoscMin)
{
	////*Idmax_ave =0.0;
	////*tsoft  =0.0;
	////*tHandshake   =0.0;
	////*fosc_s_min =0.0;
	////*fosc_s_max =0.0;
	////*ilim_min =0.0;
	////*ilim_max =0.0;
	////*fModulation_P=0.0;
	////*Fosc_Sss_P=0.0;

	////// Declare Variables //
	////float Data_max = 0;
	////float Data_min = 0;
	////int QtySamples = 125;
	////float DataValue = 0;
	////float Data_range = 0;
	////float NoiseLevel = 0;
	////float DataNext = 0;
	////int TurnOnAddress = 0;
	////int QtyNext = 10;
	////float Data_sum = 0;
	////int GND_addr = 0;
	////int GND_count = 10;
	////int NoTurnOn = 0;
	////float MultFactor = 0;
	////int OnCount = 0;
	////int OnCount2 = 0;
	////int k = 0;
	////float GND_delta[10] = {0};
	////int GND_delta_min = 0;
	////int Look_Ahead_Qty = 10;
	////int Look_Back_Qty = 10;
	////float GND_value = 0;
	////Pulse pulse;

	////// Set  MultFactor per device //
	////MultFactor = 2.5;
	////if (!strnicmp(Part_ID_LimitSet, "INN3365", 7))
	////{
	////	MultFactor = 18.4;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3375", 7))
	////{
	////	MultFactor = 18.4;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3366", 7))
	////{
	////	MultFactor = 15;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3376", 7))
	////{
	////	MultFactor = 15;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3367", 7))
	////{
	////	MultFactor = 3.5;
	////	NoiseLevel = 0.011;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3377", 7))
	////{
	////	MultFactor = 11.7;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "SC1750", 6))
	////{
	////	MultFactor = 11.7;
	////	NoiseLevel = 0.002;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "INN3368", 7))
	////{
	////	MultFactor = 2.5;
	////	NoiseLevel = 0.0114;
	////}
	////if (!strnicmp(Part_ID_LimitSet, "SC1738", 6))
	////{
	////	MultFactor = 2.5;
	////	NoiseLevel = 0.0114;
	////}

	////if (!trig_ok || !data_ok)
	////{
	////	//Bad acquisition
	////	*Idmax_ave		=999.0;
	////	*tsoft		=999.0;
	////	*tHandshake		=999.0;
	////	*fosc_s_min =999.0;
	////	*fosc_s_max =999.0;
	////	*ilim_min =999.0;
	////	*ilim_max =999.0;
	////	*fModulation_P=999.0;
	////	*Fosc_Sss_P=999.0;
	////	return;
	////}

	////int	a  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	////int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	////int start_addr=0;
	////int tsoft_start=0, tsoft_end=0;
	////int pulse_cnt =0;
	////int icnt =0, cnt=0; 
	////float Vdson_peak_ave =0.0;
	////float Vped_threshold =0.0;
	////
	////// Variables for ILIM peak tests
	////float ACgnd[4000]      ={0.0};
	////float ACgnd_Ave[4000]  ={0.0};
	////float Id05us_Ave[4000] ={0.0};
	////float pulse_width[4000]={0.0};
	////float Ton[4000]		 ={0.0};
	////float Toff[4000]		 ={0.0};
	////float DiDt[4000]		 ={0.0};
	////int Id05us_Addr[4000]  ={0};
	////int ACgnd_addr[4000]   ={1000};				// GND is taken before device turns on
	////float pulse_period[4000]	={0.0};
	////float freq[4000]	={0.0};
	////int TurnOnAddr[4000] = {0};

	////float FirstPeak_ILIM =0.0;
	////float FirstPeak_addr =0.0;
	////int   FirstPeak_cnt	 =0;
	////float SecondPeak_ILIM =0.0;
	////float SecondPeak_addr =0.0;
	////int   SecondPeak_cnt  =0;
	////float min=0, max=0;
	////float start=0.0, start2=0.0;
	////float dummy_array[200]={0.0};


	////// Variables for Rdson_spec tests at 10% ILIM_NORM level
	////float Ilim_spec =0.0;
	////float Vdson_spec[4000] ={0.0};
	////float Idson_spec[4000] ={0.0};
	////float Rdson_spec[4000] ={0.0};
	////float Vdson_spec_ave =0.0;
	////float Idson_spec_ave =0.0;
	////int Id_spec_addr[4000] ={0};

	////float Id_temp =0.0;
	////float Id_one_data_pts =0.0;
	////int	  lcnt =0, i=0;
	////int   loop_cnt=0;
	////int	  ave_start_pulse =0;
	////int	  ave_pulses	  =0;
	////int	  ave_end_pulse	  =0;

	////float Period=0.0;
	////int	  Sample_per_cycle=0;
	////int   FIND_ILIM_LO_FLAG=0;

	////float Off_Time=0.0;
	////float RTM_High_Id=0.0,
	////	  RTM_Low_Id=0.0;
	////int ILIM_min_address = 0;
	////int ILIM_max_address = 0;
	////char wave_name_Id[150] ="/0"; 
	////char wave_name_Vd[150] ="/0"; 


	////Period = 1/(gFOSC_TARGET_P_Trimops-10e3);		//Takes care of device with Jitter up to 10kHz
	////SAMPLE_RATE_s = 20e-9;
	////Sample_per_cycle = Period/SAMPLE_RATE_s;

	//////transfer data to PC (XP)
	////Gage_Transfer_Data (GAGE_CHAN_A); //transfer data to Gage_chan_a_voltage array

	////// Save captured data as .awav file. //
	////if (g_Save_Awav_TextDebug_ALL)
	////{
	////	//double *capture_data = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
	////	double *capture_data = (double *)malloc((g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
	////	//for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
	////	for( i = 0; i < (g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10); i++)
	////	{	
	////		capture_data[i] = (double)(Gage_chan_a_voltage[i]); // XP //	
	////	}
	////	CreateAwav(	capture_data, // Data array //
	////				g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10, // Size of array //
	////				20.0e-9, // Sampling period //				 
	////				"e:\\dl4\\ILIM_tSoftRamp.awav"); // Output file and path //
	////	free (capture_data);
	////}

	////for (icnt=0; icnt<4000; icnt++)
	////{
	////	g_Idmax[icnt] = -100;
	////	g_Idmax_addr[icnt]  = 0;
	////}

	////pulse_cnt =0;
	////PULSE_NUM_PROCESSED =0;
	////
	////// Find the noise level. //
	//////Data_max = -99999;
	//////Data_min = 99999;
	//////for (i=1;i<(QtySamples+1);i++)
	//////{
	//////	DataValue = Gage_chan_a_voltage[i];
	//////	if(DataValue < Data_min)
	//////		Data_min = DataValue;
	//////	if(DataValue > Data_max)
	//////		Data_max = DataValue;
	//////}
	//////Data_range = Data_max - Data_min;
	//////NoiseLevel = Data_range;

	////start_addr = QtyNext + 10;

	////// Look for part turn on. //
	////TurnOnAddress = 1;
	////for(i=start_addr; i < (start_addr+(5*Period/20e-9)); i++)
	////{
	////	DataValue = Gage_chan_a_voltage[i];
	////	DataNext = Gage_chan_a_voltage[i + QtyNext];
	////	Data_range = DataNext - DataValue;
	////	if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
	////	{
	////		// Look at ten samples after turn-on edge to make sure part is really on and not just a noise spike //
	////		OnCount = 0;
	////		for (k=1; k < (Look_Ahead_Qty+1); k++)
	////		{
	////			DataValue = Gage_chan_a_voltage[i];
	////			DataNext = Gage_chan_a_voltage[i + QtyNext+k];
	////			Data_range = DataNext - DataValue;
	////			if (Data_range > MultFactor*NoiseLevel)
	////				OnCount++;
	////		}

	////		// Look at 10 samples prior to turn-on to make sure part is really on and not a noise spike.  
	////		// The samples just prior to the turn-on edge should all be near the same level. //
	////		OnCount2 = 0;
	////		for (k=1; k < (Look_Back_Qty+1); k++)
	////		{
	////			DataValue = Gage_chan_a_voltage[i];
	////			DataNext = Gage_chan_a_voltage[i - k];
	////			Data_range = DataNext - DataValue;
	////			if (Data_range<0) // Remove negative //
	////				Data_range *= -1;
	////			if (Data_range < MultFactor*NoiseLevel/2)
	////				OnCount2++;
	////		}
	////		if (OnCount > (Look_Ahead_Qty-1) && OnCount2 > (Look_Back_Qty-1)) // Real turn-on found //
	////		{
	////			TurnOnAddress = i + QtyNext;
	////			break; // Out of for loop. //
	////		}
	////	}
	////}
	////TurnOnAddr[pulse_cnt] = TurnOnAddress;
	////start_addr = TurnOnAddress + 25; // Jump ahead 500nsec to avoid leading edge spike. //

	////// Error check
	////if ((start_addr + Sample_per_cycle + 125) > g_SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	////{
	////	*Idmax_ave  = 999.0;
	////	return;
	////}
	////// Search for the peaks //
	////while (start_addr < g_SAMPLE_SIZE-10)
	////{
	////	// Find Idmax
	////	for(icnt = start_addr; icnt< start_addr + 400 ; icnt++)
	////	{
	////		if(Gage_chan_a_voltage[icnt] > g_Idmax[pulse_cnt] /*&& Gage_chan_a_voltage[icnt]>50e-3*/)
	////		{
	////			g_Idmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
	////			g_Idmax_addr[pulse_cnt] = icnt;
	////		}
	////		if((g_Idmax[pulse_cnt] - Gage_chan_a_voltage[icnt]) > 35*NoiseLevel /*&& g_Idmax[pulse_cnt] > 50e-3*/)
	////		{
	////			break;
	////		}
	////	}

	////	// Look for next part turn on. //
	////	start_addr = g_Idmax_addr[pulse_cnt] + 125;	// Fast forward 125 samples (2.5us) //
	////	NoTurnOn = 1;
	////	for(i=start_addr; i < (g_SAMPLE_SIZE - Sample_per_cycle - 125); i++)
	////	{
	////		DataValue = Gage_chan_a_voltage[i];
	////		DataNext = Gage_chan_a_voltage[i + QtyNext];
	////		Data_range = DataNext - DataValue;
	////		if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
	////		{
	////			// Look at ten samples after turn-on edge to make sure part is really on and not just a noise spike //
	////			OnCount = 0;
	////			for (k=1; k < (Look_Ahead_Qty+1); k++)
	////			{
	////				DataValue = Gage_chan_a_voltage[i];
	////				DataNext = Gage_chan_a_voltage[i + QtyNext+k];
	////				Data_range = DataNext - DataValue;
	////				if (Data_range > MultFactor*NoiseLevel)
	////					OnCount++;
	////			}

	////			// Look at 10 samples prior to turn-on to make sure part is really on and not a noise spike.  
	////			// The samples just prior to the turn-on edge should all be near the same level. //
	////			OnCount2 = 0;
	////			for (k=1; k < (Look_Back_Qty+1); k++)
	////			{
	////				DataValue = Gage_chan_a_voltage[i];
	////				DataNext = Gage_chan_a_voltage[i - k];
	////				Data_range = DataNext - DataValue;
	////				if (Data_range<0) // Remove negative //
	////					Data_range *= -1;
	////				if (Data_range < MultFactor*NoiseLevel/2)
	////					OnCount2++;
	////			}
	////			if (OnCount > (Look_Ahead_Qty-1) && OnCount2 > (Look_Back_Qty-1)) // Real turn-on found //
	////			{
	////				NoTurnOn = 0; // Turn-on found //
	////				TurnOnAddress = i + QtyNext;
	////				break; // Out of for loop. //
	////			}
	////		}
	////	}
	////	start_addr = TurnOnAddress + 25; // Jump ahead 500nsec to avoid leading edge spike. //
	////	
	////	// Check if turn-on found //
	////	if (NoTurnOn)
	////	{
	////		start_addr = g_SAMPLE_SIZE + 999; // Force out of while loop //
	////	}
	////	else
	////	{
	////		PULSE_NUM_PROCESSED ++;
	////		pulse_cnt ++;
	////	}
	////	TurnOnAddr[pulse_cnt] = TurnOnAddress;
	////	if ( (icnt> (g_SAMPLE_SIZE-400)) || PULSE_NUM_PROCESSED > 3000) 	
	////		break;
	////}
	////
	////// Subract GND level for all peaks //
	////for(pulse_cnt=0; pulse_cnt<PULSE_NUM_PROCESSED; pulse_cnt++)
	////{
	////	// For the first two pulses, use the flat just prior to turn-on to get GND.  For 3rd 
	////	// and later pulses look at the GND levels for the current pulse and two previous pulses 
	////	// and compare all three GND levels to make sure none of them are significantly different 
	////	// from each other; if one GND level is significantly different from the other two it 
	////	// will not be used.  Ocassionally, there is noise on the flat just prior to turn-on 
	////	// that causes a measurement error. //

	////	// Look at samples just before part turn-on to find GND. //
	////	GND_addr = 	TurnOnAddr[pulse_cnt] - QtyNext - 2;
	////	Data_sum = 0;
	////	for (i=0; i<GND_count; i++)
	////	{
	////		DataValue = Gage_chan_a_voltage[GND_addr-i];
	////		Data_sum += DataValue;
	////	}
	////	ACgnd_Ave[pulse_cnt] = Data_sum / GND_count;
	////	GND_value = ACgnd_Ave[pulse_cnt];

	////	// Choose a different ground level if needed //
	////	// Look at the GND levels for the current pulse and two previous pulses to remove bad GND level //
	////	if (pulse_cnt > 1) 
	////	{
	////		GND_delta[1] = ACgnd_Ave[pulse_cnt-2] - ACgnd_Ave[pulse_cnt-1];
	////		GND_delta[2] = ACgnd_Ave[pulse_cnt] - ACgnd_Ave[pulse_cnt-2];
	////		GND_delta[3] = ACgnd_Ave[pulse_cnt] - ACgnd_Ave[pulse_cnt-1];

	////		// Take absolute value //
	////		for (k=1; k<4; k++)
	////		{
	////			if (GND_delta[k] < 0)
	////			GND_delta[k] *= -1;
	////		}
	////		
	////		// Pick the smallest //
	////		Data_min = 99999;
	////		for (k=1; k<4; k++)
	////		{
	////			if (GND_delta[k] < Data_min )
	////			{
	////				Data_min = GND_delta[k];
	////				GND_delta_min = k;
	////			}
	////		}

	////		// Set the new GND level //
	////		if (GND_delta_min == 1)
	////			GND_value = ACgnd_Ave[pulse_cnt-2];
	////		if (GND_delta_min == 2)
	////			GND_value = ACgnd_Ave[pulse_cnt]; // No change //
	////		if (GND_delta_min == 3)
	////			GND_value = ACgnd_Ave[pulse_cnt]; // No change //
	////	}
	////	//g_Idmax[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
	////	g_Idmax[pulse_cnt] -= GND_value;
	////}

	////// Get frequency and period of every pulse //
	////for(pulse_cnt = 1; pulse_cnt < PULSE_NUM_PROCESSED; pulse_cnt++)
	////{	
	////	pulse_period[pulse_cnt] = (g_Idmax_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1])*SAMPLE_RATE_s;
	////	freq[pulse_cnt] = 1/pulse_period[pulse_cnt];
	////}
	////*Fosc_Sss_P = freq[1];
	////*tHandshake = pulse_period[2];
	////*fosc_s_min = freq[3];
	////if(*fosc_s_min < LowLimFoscMin || *fosc_s_min > UppLimFoscMin) // Sometimes three pulses for handshake. Not well understood yet. //
	////{
	////	*tHandshake = pulse_period[3];
	////	*fosc_s_min = freq[4];
	////}
	////
	////
	////// After the ramp reaches full frequency, the frequency modulation begins (~1.25kHz).  Take 
	////// an average of at least one full modulation cycle to get the approximate final maximum 
	////// frequency; approximately 1.5 modulation cycles worth of pulses ( ((1/1250)*1.5)*130000 ~150pulses).
	////// Then, when the ramp gets to within 100Hz of this final frequency, the ramp 
	////// is complete and jump out of the loop. //
	////int AvgQty = 150;
	////float FreqSum = 0;
	////float FreqAvg = 0;
	////for(i=1;i<AvgQty+1;i++)
	////{
	////	FreqSum = FreqSum + freq[PULSE_NUM_PROCESSED-i];
	////}
	////FreqAvg = FreqSum / AvgQty;
	////for(pulse_cnt=3; pulse_cnt<PULSE_NUM_PROCESSED; pulse_cnt++)
	////{
	////	if(FreqAvg -freq[pulse_cnt] < 100)
	////	{
	////		tsoft_end = pulse_cnt;
	////		break;
	////	}
	////	
	////}


	/////*
	////for(pulse_cnt=3; pulse_cnt<PULSE_NUM_PROCESSED; pulse_cnt++)
	////{
	////	if(abs(freq[pulse_cnt]-freq[PULSE_NUM_PROCESSED-10])<1000)
	////	{
	////		tsoft_end = pulse_cnt;
	////		break;
	////	}
	////	
	////}
	////*/

	////*fosc_s_max = freq[tsoft_end];
	////*tsoft = (gIdmax_addr[tsoft_end] - gIdmax_addr[2])*SAMPLE_RATE_s;

	////// Average ILIM 70pct from first two pulses //
	//////*Idmax_ave = (gIdmax[0] + gIdmax[1]) / 2;
	//////*Idmax_ave /= g_ILIM_gain;

	////// Average ILIM 70pct from first two pulses after secondary has control //
	////*Idmax_ave = (gIdmax[2] + gIdmax[3]) / 2;
	////*Idmax_ave /= g_ILIM_gain;


	////// Find ILIM Jitter at 132kHz //
	//// // 250 pulses cover ~2ms of data. Exclude the last 5 points  of capture. //
	////*ilim_min = 9999;
	////*ilim_max = -9999;
	////for(cnt = tsoft_end; (cnt < tsoft_end+250) && cnt<(PULSE_NUM_PROCESSED-5); cnt++)
	////{
	////	if (gIdmax[cnt] < *ilim_min)
	////	{
	////		*ilim_min = gIdmax[cnt];
	////		ILIM_min_address = gIdmax_addr[cnt];
	////	}
	////	if (gIdmax[cnt] > *ilim_max)
	////	{
	////		*ilim_max = gIdmax[cnt];
	////		ILIM_max_address = gIdmax_addr[cnt];
	////	}
	////}
	////*ilim_min /= g_ILIM_gain;
	////*ilim_max /= g_ILIM_gain;

	///////////////////////////////////
	//////F_Modulation
	///////////////////////////////////
 ////	start=tsoft_end+50;
	////start2=tsoft_end+150;

	////FirstPeak_ILIM =0;
	////FirstPeak_addr =0;
	////SecondPeak_ILIM =0;
	////SecondPeak_addr =0;
	////// Looking for 1st Peak
	////for(cnt=start;(cnt < start+100);cnt++) // 100 pulses should cover 1ms of data
	////{
	////	if (gIdmax[cnt]>FirstPeak_ILIM) 
	////	{
	////		FirstPeak_ILIM = gIdmax[cnt];	
	////		FirstPeak_addr = gIdmax_addr[cnt];	
	////		FirstPeak_cnt  = cnt;
	////		start2 = cnt+50;	// Start the 2nd Peak search 50 pulses after the 1st Peak is found.
	////	}
	////}
	////// Looking for 2nd Peak
	////for(cnt=start2;(cnt < start2+100);cnt++) // 100 pulses should cover 1ms of data
	////{
	////	if (gIdmax[cnt]>SecondPeak_ILIM) 
	////	{
	////		SecondPeak_ILIM = gIdmax[cnt];	
	////		SecondPeak_addr = gIdmax_addr[cnt];	
	////		SecondPeak_cnt  = cnt;
	////	}
	////}
	////
	////*fModulation_P = 1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE_s);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_Ilim_18kHz(float *ILIM_Jit18K_S, float *ILIMhi_Jit18K_S, float *ILIMLo_Jit18K_S, float *Fosc_Mod_18K_S) // DPG added //
{
	// Declare Variables //
	long int i = 0;
	//int j = 0;
	int tbs = 0;
	float period = 0;
	float vmax[500];
	//float voffs[500];
	long int vmax_addr[500];
	float Ilim_rslt[500];
	int pulse_cnt =0;
	int TurnOnAddr[500] = {0};
	int GND_addr = 0;
	float Data_sum = 0;
	float ACgnd_Ave[500]  ={0.0};
	float GND_delta[10] = {0};
	int GND_delta_min = 0;
	long int StartAddress = 0;
	float DataValueMin = 0;
	float DataValueMax = 0;
	int FoundFlat = 0;
	long int FirstAddress = 0;
	long int i_count = 0;
	long int j_count = 0;
	int NumPoints = 4250; // 85us //
	int QtyPoints = 100;
	float DataValue = 0;
	float DataRange = 0;
	long int TurnOnAddress = 0;
	int QtyNext = 10;
	float DataNext = 0;
	//float VoltageRange = 0;
	long int TempAddr = 0;
	float delta_I = 0;
	float DataPrevious = 0;
	float DataPrevious2 = 0;
	float DataPrevious3 = 0;
	float DataPrevious4 = 0;
	float ScaleFactor = 0;
	float Data_range = 0;
	int QtySamples = 0;
	long int AddrMin = 0;
	float Data_Sum = 0;
	int Num_samples = 0;
	long int DataAddr = 0;
	int Num_ILIM_Peaks = 255;
	float Data_max = 0;
	float Data_min = 0;
	float temp_1 = 0;
	float MaxDelta = 0; // Set MaxDelta. Used in ILIM search algorithm. //
	int OnCount = 0;
	int OnCount2 = 0;
	int k = 0;
	int GND_count = 10;
	int Look_Ahead_Qty = 10;
	int Look_Back_Qty = 10;
	float GND_value = 0;

	ScaleFactor = 17;
	MaxDelta = .015;

	// Initialize //
	*ILIM_Jit18K_S = 0;
	*ILIMhi_Jit18K_S = 0;
	*ILIMLo_Jit18K_S = 0;
	*Fosc_Mod_18K_S = 0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*ILIM_Jit18K_S = -999;
		*ILIMhi_Jit18K_S = -999;
		*ILIMLo_Jit18K_S = -999;
		*Fosc_Mod_18K_S = -999;
		return;
	}

	// Clear Gage array //
	for(i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD); i++)	
	{
		chan_a_16_raw[i] = 0; // XP //
		chan_b_16_raw[i] = 0; // XP //
	}

	//Check to see if trigger occured //
	tbs = 20; // 20ns/sample //
	
	// Transfer data to PC (XP) //
	Gage_Transfer_Data (GAGE_CHAN_A); // XP //

	// Save captured data as .awav file. //
	if (g_Save_Awav_TextDebug_ALL)
	{
		double *capture_data = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
		{	
			capture_data[i] = (double)(Gage_chan_a_voltage[i]); // XP //	
		}
		CreateAwav(	capture_data, // Data array //
					GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
					20.0e-9, // Sampling period //				 
					"e:\\dl4\\Inno_IlimJitter18kHz.awav"); // Output file and path //
		free (capture_data);
	}

	// Set switching period //
	period = 1/18e3; // 18kHz frequency // 

	// Initialize array //
	for (pulse_cnt=0;pulse_cnt<500;pulse_cnt++)
	{
		vmax_addr[pulse_cnt] = 0;
		vmax[pulse_cnt] = 0;
	}

	// Search the data to find ILIM. //
	StartAddress = 12500;  // Skip about first 5 pulses to make sure at full ILIM. //
	for (pulse_cnt=0;pulse_cnt<Num_ILIM_Peaks;pulse_cnt++) // Find 65 ILIM peaks.  40x(1/18kHz) = 2.22 msec of data. //
	{
		// Look for flat spot.
		// Look in the first NumPoints samples. //
		DataValueMin = 9999;
		DataValueMax = -9999;
		FoundFlat = 0;
		FirstAddress = 0;
		i_count = 0;
		for (i_count = StartAddress; i_count < (StartAddress+NumPoints) && !FoundFlat; i_count++)
		{
			// Look at QtyPoints samples.  If the difference between max and 
			// min is < MaxDelta, then we've found a flat spot within the QtyPoints samples.  If the difference 
			// between max and min is > MaxDelta, then we have not found a flat spot in the QtyPoints 
			// samples, so shift over by 1 sample (20ns) and look at another QtyPoints samples for a flat spot. //
			DataValueMin = 9999;
			DataValueMax = -9999;
			for (j_count = 0; j_count < QtyPoints; j_count++)
			{
				DataValue = Gage_chan_a_voltage[i_count+j_count];
				if (DataValue < DataValueMin)
					DataValueMin = 	DataValue;
				if (DataValue > DataValueMax)
					DataValueMax = 	DataValue;
			}
			DataRange = DataValueMax - DataValueMin;
			if(DataRange < 0)
				DataRange *= -1; // Take absolute value. //
			if (DataRange < MaxDelta)
			{
				FoundFlat = 1;
				FirstAddress = i_count;
			}
		}

		// Error if could not find flat. //
		if ( i_count > (StartAddress+NumPoints-1) )
		{
			*ILIM_Jit18K_S = -999;
			*ILIMhi_Jit18K_S = -999;
			*ILIMLo_Jit18K_S = -999;
			*Fosc_Mod_18K_S = -999;
			return;
		}

		// Starting address for search. //
		StartAddress = FirstAddress;
	
		// Look for part turn on. //
		TurnOnAddress = 1;
		for(i=StartAddress; i < (StartAddress+(3*period/20e-9)); i++)
		{
			DataValue = Gage_chan_a_voltage[i];
			DataNext = Gage_chan_a_voltage[i + QtyNext];
			Data_range = DataNext - DataValue;
			if (Data_range > 2*MaxDelta) // Turn-on found //
			{
				// Look at ten samples after turn-on edge to make sure part is really on and not just a noise spike //
				OnCount = 0;
				for (k=1; k < (Look_Ahead_Qty + 1) ;k++)
				{
					DataValue = Gage_chan_a_voltage[i];
					DataNext = Gage_chan_a_voltage[i + QtyNext+k];
					Data_range = DataNext - DataValue;
					if (Data_range > 2*MaxDelta)
						OnCount++;
				}

				// Look at 10 samples prior to turn-on to make sure part is really on and not a noise spike.  
				// The samples just prior to the turn-on edge should all be near the same level. //
				OnCount2 = 0;
				for (k=1; k < (Look_Back_Qty + 1); k++)
				{
					DataValue = Gage_chan_a_voltage[i];
					DataNext = Gage_chan_a_voltage[i - k];
					Data_range = DataNext - DataValue;
					if (Data_range<0) // Remove negative //
						Data_range *= -1;
					if (Data_range < MaxDelta)
						OnCount2++;
				}
				if (OnCount > (Look_Ahead_Qty-1) && OnCount2 > (Look_Back_Qty-1)) // Real turn-on found //
				{
					TurnOnAddress = i + QtyNext;
					TurnOnAddr[pulse_cnt] = TurnOnAddress;
					break; // Out of for loop. //
				}
			}
		}
		TempAddr = TurnOnAddress + 13; // Jump ahead 260nsec to avoid leading edge spike. //
		
		// Get average change in current per 20nsec sample step.  Take average of 12 samples. //
		DataValue = Gage_chan_a_voltage[TempAddr];
		DataNext = Gage_chan_a_voltage[TempAddr + 15];
		delta_I = (DataNext-DataValue) / 15;

		// Search for peak. //
		vmax[pulse_cnt] = -999; // Give vmax a small value to start. //
		for(i = TempAddr; i < (TempAddr+(period/20e-9)); i++)
		{
			DataValue = Gage_chan_a_voltage[i];
			if (DataValue > vmax[pulse_cnt])
			{
				vmax[pulse_cnt] = DataValue;
				vmax_addr[pulse_cnt] = i; // Address of max value //
			}
			if ( (vmax[pulse_cnt] - DataValue) > (ScaleFactor*delta_I) )
				break;		
		}

		/*
		// The current probe coupling will cause the current to tend to 
		// drift negative. The "zero" value must be found in order to get an 
		// accurate reading.  Therefore the current limit will be vmax minus 
		// voffs.  To find the voffs value, look at the flat just before the start of the ramp.  
		// Average 300ns(15 samples) to find an acceptable offset value. //
		FoundFlat = 0;
		Data_range = 0;
		QtySamples = 40;
		AddrMin = 0;
		Data_Sum = 0;
		Num_samples = 30;
		DataAddr = vmax_addr[pulse_cnt];
		AddrMin = DataAddr - QtySamples;
		while ( (vmax_addr[pulse_cnt]-AddrMin)*20e-9 < period && AddrMin > 5 && FoundFlat < 1)
		{
			Data_max = -99999;
			Data_min = 99999;
			for (i=0;i<QtySamples;i++)
			{
				temp_1 = Gage_chan_a_voltage[DataAddr-i];
				if(temp_1 < Data_min)
					Data_min = temp_1;
				if(temp_1 > Data_max)
					Data_max = temp_1;
			}
			Data_range = Data_max - Data_min;
			if (Data_range < 0) // Make positive. //
				Data_range *= -1;
			if (Data_range < MaxDelta) // Found flat. Take average. //
			{
				Data_Sum = 0;
				for (i=2;i<(Num_samples+2);i++)
				{
					temp_1 = Gage_chan_a_voltage[DataAddr-i];
					Data_Sum += temp_1;
				}
				voffs[pulse_cnt] = Data_Sum / Num_samples;
				FoundFlat = 1;
			}
			DataAddr--;
			AddrMin = DataAddr - (QtySamples - 1);
		}

		if (FoundFlat < 1) // Did not find flat.  Error. //
		{
			g_Error_Flag = -100;
		}
		*/
				
		// Calculate current limit //
		//Ilim_rslt[pulse_cnt] = vmax[pulse_cnt] - voffs[pulse_cnt];
		StartAddress = vmax_addr[pulse_cnt];

		// The peak value must be at least .065 otherwise it's just noise. //
		//if (Ilim_rslt[pulse_cnt] < 0.065)
		//	pulse_cnt--; // Reset the pulse_cnt value, this peak is not valid //
	}

	// Subract GND level for all peaks //
	for (pulse_cnt=0;pulse_cnt<Num_ILIM_Peaks;pulse_cnt++)
	{
		// For the first two pulses, use the flat just prior to turn-on to get GND.  For 3rd 
		// and later pulses look at the GND levels for the current pulse and two previous pulses 
		// and compare all three GND levels to make sure none of them are significantly different 
		// from each other; if one GND level is significantly different from the other two it 
		// will not be used.  Ocassionally, there is noise on the flat just prior to turn-on 
		// that causes a measurement error. //

		// Look at samples just before part turn-on to find GND. //
		GND_addr = 	TurnOnAddr[pulse_cnt] - QtyNext - 2;
		Data_sum = 0;
		for (i=0; i<GND_count; i++)
		{
			DataValue = Gage_chan_a_voltage[GND_addr-i];
			Data_sum += DataValue;
		}
		ACgnd_Ave[pulse_cnt] = Data_sum / GND_count;
		GND_value = ACgnd_Ave[pulse_cnt];

		// Choose a different ground level if needed //
		// Look at the GND levels for the current pulse and two previous pulses to remove bad GND level //
		if (pulse_cnt > 1) 
		{
			GND_delta[1] = ACgnd_Ave[pulse_cnt-2] - ACgnd_Ave[pulse_cnt-1];
			GND_delta[2] = ACgnd_Ave[pulse_cnt] - ACgnd_Ave[pulse_cnt-2];
			GND_delta[3] = ACgnd_Ave[pulse_cnt] - ACgnd_Ave[pulse_cnt-1];

			// Take absolute value //
			for (k=1; k<4; k++)
			{
				if (GND_delta[k] < 0)
				GND_delta[k] *= -1;
			}
			
			// Pick the smallest //
			Data_min = 99999;
			for (k=1; k<4; k++)
			{
				if (GND_delta[k] < Data_min )
				{
					Data_min = GND_delta[k];
					GND_delta_min = k;
				}
			}

			// Set the new GND level //
			if (GND_delta_min == 1)
				GND_value = ACgnd_Ave[pulse_cnt-2];
			if (GND_delta_min == 2)
				GND_value = ACgnd_Ave[pulse_cnt]; // No change //
			if (GND_delta_min == 3)
				GND_value = ACgnd_Ave[pulse_cnt]; // No change //
		}
		//Ilim_rslt[pulse_cnt] = vmax[pulse_cnt] - ACgnd_Ave[pulse_cnt];
		Ilim_rslt[pulse_cnt] = vmax[pulse_cnt] - GND_value;
	}

	if (g_Error_Flag == -100)
	{
		*ILIM_Jit18K_S = -999;
		*ILIMhi_Jit18K_S = -999;
		*ILIMLo_Jit18K_S = -999;
		*Fosc_Mod_18K_S = -999;
		return;
	}

	// Pearson current probe output is 1/2. //
	for (pulse_cnt=0; pulse_cnt<Num_ILIM_Peaks; pulse_cnt++)
	{
		Ilim_rslt[pulse_cnt] *= 2;
	}

	int MaxAddress = 0;
	int MinAddress = 0;
	int SecondMaxAddress = 0;
	int SecondMinAddress = 0;
	float DataPt1 = 0;
	float DataPt2 = 0;
	float DataPt3 = 0;
	int FirstFallingAddr = 0;
	int FirstRisingAddr = 0;
	int SecondFallingAddr = 0;
	float Midpoint = 0;

	// Find max and min ilim values //
	// Skip first 50 peaks to make sure ILIM is settled.//
	Data_max = -9999;
	Data_min = 9999;
	for (pulse_cnt=50; pulse_cnt<150; pulse_cnt++)
	{
		if (Ilim_rslt[pulse_cnt] > Data_max)
		{
			Data_max = Ilim_rslt[pulse_cnt];
			MaxAddress = pulse_cnt;
		}
		if (Ilim_rslt[pulse_cnt] < Data_min)
		{
			Data_min = Ilim_rslt[pulse_cnt];
			MinAddress = pulse_cnt;
		}
	}
	*ILIMhi_Jit18K_S = Data_max;
	*ILIMLo_Jit18K_S = Data_min;
	*ILIM_Jit18K_S = (*ILIMLo_Jit18K_S / *ILIMhi_Jit18K_S) * 100;
	Midpoint = (Data_max + Data_min) / 2;

	// Look for Ilim level going below Midpoint //
	// Check for 3 consecutive below Midpoint //
	pulse_cnt = MaxAddress; 
	while( (pulse_cnt+2) < Num_ILIM_Peaks)
	{
		DataPt1 = Ilim_rslt[pulse_cnt];
		DataPt2 = Ilim_rslt[pulse_cnt+1];
		DataPt3 = Ilim_rslt[pulse_cnt+2];
		if ( (DataPt1 < Midpoint) && (DataPt2 < Midpoint) && (DataPt3 < Midpoint) ) // Falling below midpoint found //
		{	
			FirstFallingAddr = pulse_cnt+2;
			break;
		}
		pulse_cnt++;
	}

	// Look for Ilim level going above Midpoint //
	// Check for 3 consecutive above Midpoint //
	pulse_cnt = FirstFallingAddr; 
	while( (pulse_cnt+2) < Num_ILIM_Peaks)
	{
		DataPt1 = Ilim_rslt[pulse_cnt];
		DataPt2 = Ilim_rslt[pulse_cnt+1];
		DataPt3 = Ilim_rslt[pulse_cnt+2];
		if ( (DataPt1 > Midpoint) && (DataPt2 > Midpoint) && (DataPt3 > Midpoint) ) // Falling below midpoint found //
		{	
			FirstRisingAddr = pulse_cnt+2;
			break;
		}
		pulse_cnt++;
	}

	// Look for Ilim level going below Midpoint again //
	// Check for 3 consecutive below Midpoint //
	pulse_cnt = FirstRisingAddr; 
	while( (pulse_cnt+2) < Num_ILIM_Peaks)
	{
		DataPt1 = Ilim_rslt[pulse_cnt];
		DataPt2 = Ilim_rslt[pulse_cnt+1];
		DataPt3 = Ilim_rslt[pulse_cnt+2];
		if ( (DataPt1 < Midpoint) && (DataPt2 < Midpoint) && (DataPt3 < Midpoint) ) // Falling below midpoint found //
		{	
			SecondFallingAddr = pulse_cnt+2;
			break;
		}
		pulse_cnt++;
	}

	// Find max value between FirstFallingAddr and SecondFallingAddr. This will be
	// the next peak ilim in the modulation. //
	Data_max = -9999;
	Data_min = 9999;
	for (pulse_cnt=FirstFallingAddr+1; pulse_cnt<SecondFallingAddr+1; pulse_cnt++)
	{
		if (Ilim_rslt[pulse_cnt] > Data_max)
		{
			Data_max = Ilim_rslt[pulse_cnt];
			SecondMaxAddress = pulse_cnt;
		}
		if (Ilim_rslt[pulse_cnt] < Data_min)
		{
			Data_min = Ilim_rslt[pulse_cnt];
			SecondMinAddress = pulse_cnt;
		}
	}
	*Fosc_Mod_18K_S = 1 / ( 20e-9 * (vmax_addr[SecondMaxAddress] - vmax_addr[MaxAddress]) );
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_SOA(float *SOA, float *TW_50)
{
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int i = 0;
	float On_addr[200] ={0}, Off_addr[200] ={0};
	float ILIM_On_addr[200] ={0}, ILIM_Off_addr[200] ={0};
	float On_Time[200] ={0}, Off_Time[200] ={0};
	float SOA_On_addr[200] ={0}, SOA_Off_addr[200] ={0}, SOA_On_Time[200] ={0}, SOA_Cycle_Time[200] ={0};
	int SOA_cnt=0;
	char wave_name_Id[50] ="/0";
	float Data_max = 0;
	float Data_min = 0;
	int QtySamples = 175; // 3.5us //
	float DataValue = 0;
	float Data_range = 0;
	float NoiseLevel = 0;
	int TurnOnAddress = 0;
	float Period=0.0;
	float DataNext = 0;
	int QtyNext = 4;
	float MultFactor = 2.5;
	float Data0 = 0;
	float Data1 = 0;
	float Data2 = 0;
	float DataSum = 0;
	float GND_level = 0;
	int Turn_On_Found = 0;
	int Turn_Off_Address = 0;
	float PeakValue = 0;

	*SOA =0.0;
	*TW_50 =0.0;

	//Initialize all variables
	i			=0;
	start_addr	=0;
	pulse_cnt	=0;
	icnt		=0; 

	for (i=0; i<GAGE_WAVEFORM_BUFFER_SIZE; i++)
		Gage_chan_a_voltage[i] = 0;	// Initialize array before data transfer

	for (i=0; i<200; i++)
	{
		On_addr[i]			=0; 
		Off_addr[i]			=0;
		ILIM_On_addr[i]		=0; 
		ILIM_Off_addr[i]	=0;
		On_Time[i]			=0; 
		Off_Time[i]			=0;

		SOA_On_addr[i]		=0; 
		SOA_Off_addr[i]		=0;
		SOA_On_Time[i]		=0; 
		SOA_Cycle_Time[i]	=0;
	}

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*SOA  = 999.0;
		*TW_50 =999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array

	// Save captured data as .awav file. //
	if (g_Save_Awav_TextDebug_ALL)
	{
		double *capture_data = (double *)malloc((g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		for( i = 0; i < (g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10); i++)
		{	
			capture_data[i] = (double)(Gage_chan_a_voltage[i]); // XP //	
		}
		CreateAwav(	capture_data, // Data array //
					g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10, // Size of array //
					20.0e-9, // Sampling period //				 
					"e:\\dl4\\SOA_P_TW50_P.awav"); // Output file and path //
		free (capture_data);
	}

	// Initialize //
	SOA_cnt = 0;
	pulse_cnt = 0;

	// Find the noise level. //
	//Data_max = -99999;
	//Data_min = 99999;
	//for (i=1;i<(QtySamples+1);i++)
	//{
	//	DataValue = Gage_chan_a_voltage[i];
	//	if(DataValue < Data_min)
	//		Data_min = DataValue;
	//	if(DataValue > Data_max)
	//		Data_max = DataValue;
	//}
	//Data_range = Data_max - Data_min;
	//NoiseLevel = Data_range;
	NoiseLevel = 0.012;

	// Find the GND level //
	DataSum = 0;
	for (i=1;i<(QtySamples+1);i++)
	{
		DataValue = Gage_chan_a_voltage[i];
		DataSum += DataValue;
	}
	GND_level = DataSum / QtySamples;


	// Look for part turn on. //
	start_addr = 0;
	Turn_On_Found = 0;
	TurnOnAddress = 1;
	for(i=start_addr; i < (start_addr+5000); i++)
	{
		DataValue = Gage_chan_a_voltage[i];
		DataNext = Gage_chan_a_voltage[i + QtyNext];
		Data_range = DataNext - DataValue;
		if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
		{
			TurnOnAddress = i + (QtyNext-1);
			Turn_On_Found = 1;
			break; // Out of for loop. //
		}
	}
	
	// Error check
	if (TurnOnAddress > (g_SAMPLE_SIZE - 15001) || Turn_On_Found < 1  ) // 300us to cover two pulses //
	{
		*SOA  = 999.0;
		*TW_50 =999.0;
		return;
	}

	while (TurnOnAddress < (g_SAMPLE_SIZE - 15000) && pulse_cnt < 10 && Turn_On_Found > 0 ) // Process captured data //
	{
		// Find OFF address //
		Turn_Off_Address = 0;
		start_addr = TurnOnAddress + 2; // Jump ahead a couple samples to avoid any noise. //
		i = start_addr;
		while (i < (g_SAMPLE_SIZE-15000) && (i-start_addr) < 100) // Stop searching after 2us //
		{
			Data0 = Gage_chan_a_voltage[i];
			Data1 = Gage_chan_a_voltage[i+1];
			Data2 = Gage_chan_a_voltage[i+2];
			if(Data0 > Data1 && Data0 > Data2) // Turn off found //
			{
				//Off_addr[pulse_cnt] = start_addr;
				//ILIM_Off_addr[pulse_cnt] = Gage_chan_a_voltage[start_addr];
				Turn_Off_Address = i;
				break;
			}
			i +=1;
		}
			
		// It's only a real pulse if the peak value is greater than 200m, otherwise it's just noise. //
		PeakValue = Gage_chan_a_voltage[Turn_Off_Address] - GND_level;
		if (PeakValue > 0.2)
		{
			pulse_cnt++;

			// ON address of pulse // 
			On_addr[pulse_cnt] = TurnOnAddress;
			ILIM_On_addr[pulse_cnt]	= Gage_chan_a_voltage[TurnOnAddress];

			// OFF address of pulse // 
			Off_addr[pulse_cnt] = Turn_Off_Address;
			ILIM_Off_addr[pulse_cnt] = Gage_chan_a_voltage[Turn_Off_Address];

			// PULSE WIDTH of pulse //
			On_Time[pulse_cnt] = (Off_addr[pulse_cnt] - On_addr[pulse_cnt])*SAMPLE_RATE_s;
		}

		// Look for next part turn on. //
		start_addr = i + 150;	// fast forward by 3us after finding Off_addr
		TurnOnAddress = 1;
		Turn_On_Found = 0;
		for(i=start_addr; i < (g_SAMPLE_SIZE-15000); i++)
		{
			DataValue = Gage_chan_a_voltage[i];
			DataNext = Gage_chan_a_voltage[i + QtyNext];
			Data_range = DataNext - DataValue;
			if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
			{
				TurnOnAddress = i + (QtyNext-1);
				Turn_On_Found = 1;
				break; // Out of for loop. //
			}
		}
	}

	// Analyze the pulses //
	SOA_cnt = 1;
	for (i=1; i < pulse_cnt+1; i++)
	{
		// Store pulses with On_Time less than 1us //
		if(On_Time[i] < 1e-6 && On_Time[i] > 5e-9)
		{
			SOA_On_addr[SOA_cnt] = On_addr[i];
			SOA_Off_addr[SOA_cnt] = Off_addr[i];
			SOA_On_Time[SOA_cnt] = On_Time[i];

			// Store cycle time //
			if(SOA_cnt > 1)
			{
				SOA_Cycle_Time[SOA_cnt] = (SOA_Off_addr[SOA_cnt] - SOA_Off_addr[SOA_cnt-1])*SAMPLE_RATE_s;

				//Store SOA_P
				if(SOA_Cycle_Time[SOA_cnt] > (10e-6))	
				{
					*SOA = SOA_Cycle_Time[SOA_cnt];
					*TW_50 = SOA_On_Time[SOA_cnt];

					//Break out of function after the second SOA pulse found
					if(SOA_cnt > 1)
						break; //Found SOA and TW50...  DONE	cx 11/10/16
				}
			}
			SOA_cnt++;
		}
	}

		/*
		// Store pulses with On_Time less than 1us
		if(On_Time[pulse_cnt] < 1e-6 && On_Time[pulse_cnt] > 1e-9)
		{
			SOA_On_addr[SOA_cnt] = On_addr[pulse_cnt];
			SOA_Off_addr[SOA_cnt] = Off_addr[pulse_cnt];
			SOA_On_Time[SOA_cnt] = On_Time[pulse_cnt];

			//Store cycle time
			if(SOA_cnt > 0)
			{
				SOA_Cycle_Time[SOA_cnt] = (SOA_Off_addr[SOA_cnt] - SOA_Off_addr[SOA_cnt-1])*SAMPLE_RATE_s;

				//Store SOA_P
				if(SOA_Cycle_Time[SOA_cnt] > (10e-6))	
				{
					*SOA = SOA_Cycle_Time[SOA_cnt];
					*TW_50 = SOA_On_Time[SOA_cnt];

					//Break out of function after the second SOA pulse found
					if(SOA_cnt > 2)
						break; //Found SOA and TW50...  DONE	cx 11/10/16
				}
			}
			SOA_cnt++;
		}
		pulse_cnt++;
		*/	

		// Look for next part turn on. //
		//start_addr += 150;	//fast forward by 3us after finding Off_addr
		//TurnOnAddress = 1;
		//for(i=start_addr; i < (g_SAMPLE_SIZE-10); i++)
		//{
		//	DataValue = Gage_chan_a_voltage[i];
		//	DataNext = Gage_chan_a_voltage[i + QtyNext];
		//	Data_range = DataNext - DataValue;
		//	if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
		//	{
		//		TurnOnAddress = i + (QtyNext-1);
		//		break; // Out of for loop. //
		//	}
		//}
	
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_SDS(float *SDS, float *SDS_TW_50, float *SDS_P_nsw)
{
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int PULSES_NEEDED = 2;
	float On_addr[200] ={0}, Off_addr[200] ={0};
	float ILIM_On_addr[200] ={0}, ILIM_Off_addr[200] ={0};
	float On_Time[200] ={0}, Off_Time[200] ={0};
	float SDS_On_addr[200] ={0}, SDS_Off_addr[200] ={0}, SDS_On_Time[200] ={0}, SDS_Cycle_Time[200] ={0};
	int	  SDS_cnt=0;
	char wave_name_Id[50] ="/0";
	float Data_max = 0;
	float Data_min = 0;
	float DataSum = 0;
	int QtySamples = 175; // 3.5us //
	float DataValue = 0;
	float Data_range = 0;
	float NoiseLevel = 0;
	float GND_level = 0;
	int TurnOnAddress = 0;
	int Turn_Off_Address = 0;
	int Turn_On_Found = 0;
	float DataNext = 0;
	int QtyNext = 4;
	float MultFactor = 2.5;
	float Data0 = 0;
	float Data1 = 0;
	float Data2 = 0;
	float PeakValue = 0;
	*SDS_P_nsw = -99;

	*SDS =0.0;
	*SDS_TW_50 =0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*SDS  = 999.0;
		*SDS_TW_50 =999.0;
		*SDS_P_nsw = 99.0;
		return;
	}

	int i = 0;
	for (i=0; i<GAGE_WAVEFORM_BUFFER_SIZE; i++)
		Gage_chan_a_voltage[i] = 0;	// Initialize array before data transfer

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array

	// Save captured data as .awav file. //
	if (g_Save_Awav_TextDebug_ALL)
	{
		double *capture_data = (double *)malloc((g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		for( i = 0; i < (g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10); i++)
		{	
			capture_data[i] = (double)(Gage_chan_a_voltage[i]); // XP //	
		}
		CreateAwav(	capture_data, // Data array //
					g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10, // Size of array //
					20.0e-9, // Sampling period //				 
					"e:\\dl4\\SDS_P_TW50_SDS_P.awav"); // Output file and path //
		free (capture_data);
	}

	// Initialize //
	SDS_cnt = 0;
	pulse_cnt = 0;

	// Find the noise level. //
	//Data_max = -99999;
	//Data_min = 99999;
	//for (i=1;i<(QtySamples+1);i++)
	//{
	//	DataValue = Gage_chan_a_voltage[i];
	//	if(DataValue < Data_min)
	//		Data_min = DataValue;
	//	if(DataValue > Data_max)
	//		Data_max = DataValue;
	//}
	//Data_range = Data_max - Data_min;
	//NoiseLevel = Data_range;
	NoiseLevel = 0.012;

	// Find the GND level //
	DataSum = 0;
	for (i=1;i<(QtySamples+1);i++)
	{
		DataValue = Gage_chan_a_voltage[i];
		DataSum += DataValue;
	}
	GND_level = DataSum / QtySamples;

	// Look for part turn on. //
	start_addr = 0;
	Turn_On_Found = 0;
	TurnOnAddress = 1;
	for(i=start_addr; i < (start_addr+15000); i++)
	{
		DataValue = Gage_chan_a_voltage[i];
		DataNext = Gage_chan_a_voltage[i + QtyNext];
		Data_range = DataNext - DataValue;
		if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
		{
			TurnOnAddress = i + QtyNext;
			Turn_On_Found = 1;
			break; // Out of for loop. //
		}
	}

	// Error check //
	if ( TurnOnAddress > (g_SAMPLE_SIZE-501) || Turn_On_Found < 1 )
	{
		*SDS  = 999.0;
		*SDS_TW_50 = 999.0;
		return;
	}

	while (TurnOnAddress < (g_SAMPLE_SIZE-500) && Turn_On_Found > 0) // Process captured data //
	{
		// Find OFF address //
		Turn_Off_Address = 0;
		start_addr = TurnOnAddress + 2; // Jump ahead a couple samples to avoid any noise. //
		i = start_addr;
		while (i < (g_SAMPLE_SIZE-500) && (i-start_addr) < 100) // Stop searching after 2us //
		{
			Data0 = Gage_chan_a_voltage[i];
			Data1 = Gage_chan_a_voltage[i+1];
			Data2 = Gage_chan_a_voltage[i+2];
			if(Data0 > Data1 && Data0 > Data2) // Turn off found //
			{
				Turn_Off_Address = i;
				break;
			}
			i +=1;
		}

		// It's only a real pulse if the peak value is greater than 200m, otherwise it's just noise. //
		PeakValue = Gage_chan_a_voltage[Turn_Off_Address] - GND_level;
		if (PeakValue > 0.2)
		{
			pulse_cnt++;

			// ON address of pulse // 
			On_addr[pulse_cnt] = TurnOnAddress;
			ILIM_On_addr[pulse_cnt]	= Gage_chan_a_voltage[TurnOnAddress];

			// OFF address of pulse // 
			Off_addr[pulse_cnt] = Turn_Off_Address;
			ILIM_Off_addr[pulse_cnt] = Gage_chan_a_voltage[Turn_Off_Address];

			// PULSE WIDTH of pulse //
			On_Time[pulse_cnt] = (Off_addr[pulse_cnt] - On_addr[pulse_cnt])*SAMPLE_RATE_s;
		}

		// Look for next part turn on. //
		start_addr = i + 150;	// fast forward by 3us after finding Off_addr
		TurnOnAddress = 1;
		Turn_On_Found = 0;
		for(i=start_addr; i < (g_SAMPLE_SIZE-500); i++)
		{
			DataValue = Gage_chan_a_voltage[i];
			DataNext = Gage_chan_a_voltage[i + QtyNext];
			Data_range = DataNext - DataValue;
			if (Data_range > MultFactor*NoiseLevel) // Turn-on found //
			{
				TurnOnAddress = i + QtyNext;
				Turn_On_Found = 1;
				break; // Out of for loop. //
			}
		}
	}

	// Analyze the pulses //
	SDS_cnt = 1;
	for (i=1; i < pulse_cnt+1; i++)
	{
		// Store pulses with On_Time less than 1us //
		if(On_Time[i] < 1e-6 && On_Time[i] > 5e-9)
		{
			SDS_On_addr[SDS_cnt] = On_addr[i];
			SDS_Off_addr[SDS_cnt] = Off_addr[i];
			SDS_On_Time[SDS_cnt] = On_Time[i];

			// Store cycle time //
			if(SDS_cnt > 1)
			{
				SDS_Cycle_Time[SDS_cnt] = (SDS_Off_addr[SDS_cnt] - SDS_Off_addr[SDS_cnt-1])*SAMPLE_RATE_s;
				*SDS = SDS_Cycle_Time[SDS_cnt];
				*SDS_TW_50 = SDS_On_Time[SDS_cnt-1];	//The 1st Pulse should be the real TW50
			}
			SDS_cnt++;
		}
	}

	// Functional Check to make sure device is in ARST off after 2 SDS pulses. //
	// Look at the last SDS pulse and make sure there were no more pulses aftwards //
	if (Off_addr[pulse_cnt] == SDS_Off_addr[SDS_cnt-1] && Off_addr[pulse_cnt] < (g_SAMPLE_SIZE-10000) )
		*SDS_P_nsw = 0;
	else
		*SDS_P_nsw = 99;
	

	//if (start_addr==(g_SAMPLE_SIZE-10) && pulse_cnt==2)
	//	*SDS_P_nsw = 0;
	//else
	//	*SDS_P_nsw = 99;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Count_Cycles_CHB(float *Cycle_Count)
{
	int	PULSE_NUM_NEED  =110;	// Define min # of pulses need to be caputred
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	long int i = 0;
	Pulse pulse;

	float On_addr[200] ={0}, Off_addr[200] ={0};
	float curr_lev[200]={0}, next_lev[200]={0};
	float comp_lev=0.0;
	float Vdata =0.0;
	char wave_name_Id[200] ="/0"; 

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Cycle_Count  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	//if(g_WAVE_NAME == "ILIM_P1")
	if (g_Save_Awav_TextDebug_ALL)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\RxTx_HRcv.awav"); // Output file and path //
			free (capture_data_B);
	}

	start_addr = 100;		
	//pulse_cnt = 0;
	pulse_cnt = -1;
	for ( icnt = start_addr; icnt < (g_SAMPLE_SIZE-20);  icnt++ )
	{
		// Look for drain turn off. //
		Vdata = Gage_chan_b_voltage[icnt];
		if (Vdata > 1.2) // Found drain turn off. //
		{
			pulse_cnt++;
			
			//Jump ahead 5 usec to look for drain turn-on. //
			icnt = icnt + 250;
			while (Vdata > 1.0)
			{
				if (icnt >(g_SAMPLE_SIZE-20))
					break;
				icnt++;
				Vdata = Gage_chan_b_voltage[icnt];
			}

			// Drain turn-on found //
			// Jump ahead 100nsec to be sure past turn on edge. //
			icnt = icnt + 5;
		}
		if (icnt >(g_SAMPLE_SIZE-20))
			break;
	}
	*Cycle_Count = pulse_cnt;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void DChUp_Gage_Find(float *DChUp_Result)
{
	int start_addr=0;
	int stop_addr=0;
	int icnt =0; 
	int j_cnt = 0;
	long int i = 0;
	float DataValue =0.0;
	float DataValueMax = 0;
	float DataValueMin = 0;
	float DataRange = 0;
	float VmaxAddress = 0;
	int QtyPoints = 20;
	int FoundRampStart = 0;
	int RampStartAddr = 0;
	float MaxDelta = .024;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*DChUp_Result  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	if (g_Save_Awav_TextDebug_ALL)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\DChUp.awav"); // Output file and path //
			free (capture_data_B);
	}

	// Look for max value. //
	start_addr = 1750;		
	stop_addr = 4250;
	DataValueMax = -9999;
	for ( icnt = start_addr; icnt < stop_addr;  icnt++ )
	{
		DataValue = Gage_chan_b_voltage[icnt];
		if (DataValue > DataValueMax)
		{
			DataValueMax = 	DataValue;
			VmaxAddress = icnt;
		}
	}

	// Look for ramp start. //
	icnt = VmaxAddress;
	FoundRampStart = 0;
	while (icnt > (VmaxAddress-1250) && FoundRampStart < 1)
	{
		DataValueMin = 9999;
		DataValueMax = -9999;
		for (j_cnt = 0; j_cnt < QtyPoints; j_cnt++)
		{
			DataValue = Gage_chan_b_voltage[icnt-j_cnt];
			if (DataValue < DataValueMin)
				DataValueMin = 	DataValue;
			if (DataValue > DataValueMax)
				DataValueMax = 	DataValue;
		}
		DataRange = DataValueMax - DataValueMin;
		if(DataRange < 0)
			DataRange *= -1; // Take absolute value. //
		if (DataRange < MaxDelta)
		{
			FoundRampStart = 1;
			RampStartAddr = icnt;
		}
		icnt--;
	}
	*DChUp_Result = (VmaxAddress - RampStartAddr)*20e-9;
	*DChUp_Result += 80e-9;  // Always measures about 80nsec too small. //
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_tOVL(float *tOVL)
{
	int start_addr=0;
	//int stop_addr=0;
	int start_trig_addr=0;
	int stop_trig_addr=0;
	int icnt =0; 
	//int j_cnt = 0;
	long int i = 0;
	//float Start_Value = 0;
	//float Stop_Value = 0;
	//float Start_Trig = 4.7;
	//float Stop_Trig = 4.2;
	float StartVoltage = 0;
	int NumPoints = 500;
	float DataValue = 0;
	float DataValueMin = 99999;
	float DataValueMax = -99999;
	float DataValueSum = 0;
	float NoiseRange = 0;
	float DeltaV = 0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tOVL  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	if (g_Save_Awav_TextDebug_ALL)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\tOVL.awav"); // Output file and path //
			free (capture_data_B);
	}
	
	// Look at 500 points to find noise level and average. //
	DataValueMin = 99999;
	DataValueMax = -99999;
	icnt = 0;
	DataValueSum = 0;
	start_addr = 10;
	for (icnt = start_addr; icnt < (start_addr+NumPoints); icnt++)
	{
		// Look at 500 samples.  The differnce between max and min is the noise. //
		DataValue = Gage_chan_b_voltage[icnt];
		if (DataValue < DataValueMin)
			DataValueMin = 	DataValue;
		if (DataValue > DataValueMax)
			DataValueMax = 	DataValue;
		DataValueSum += DataValue;
	}
	NoiseRange = DataValueMax - DataValueMin;
	if(NoiseRange < 0)
		NoiseRange *= -1; // Take absolute value. //
	StartVoltage = DataValueSum / NumPoints; // Take average //
	
	// The start voltage should be close to 5V, otherwise there is an error. //
	if(StartVoltage < 4.9 || StartVoltage > 5.1)
	{
		g_Error_Flag = -128;
	}

	// Look for falling edge //
	start_addr = 10;		
	for ( icnt = start_addr; icnt < g_SAMPLE_SIZE - 100;  icnt++ )
	{
		DataValue = Gage_chan_b_voltage[icnt];
		DeltaV = StartVoltage - DataValue;
		if (DeltaV > (3*NoiseRange) ) // Found falling edge //
		{
			start_trig_addr = icnt;
			break;
		}
	}

	// Look for rising edge //
	start_addr = start_trig_addr + 200; // Jump ahead 4us //
	DataValueMin = 99999;
	for ( icnt = start_addr; icnt < g_SAMPLE_SIZE - 100;  icnt++ )
	{
		DataValue = Gage_chan_b_voltage[icnt];
		if (DataValue < DataValueMin)
		{
			DataValueMin = 	DataValue;
			stop_trig_addr = icnt;
		}
		DeltaV = DataValue - DataValueMin;
		if (DeltaV > (3*NoiseRange) ) // Found rising edge //
		{
			//stop_trig_addr = icnt;
			break;
		}
	}
	*tOVL = (stop_trig_addr - start_trig_addr)*20e-9;

	// Check for error //
	if (g_Error_Flag == -128)
		*tOVL = -999;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_tDableOn(float *tDableON, float *FWPK_tVOxDble, float *FWPK_Timer, int Freq1Mhz)
{
	if (!trig_ok || !data_ok)
	{
		// Bad acquisition
		*tDableON =999;
		return;
	}

	// Declare Variables //
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int i=0;
	int j=0; 
	bool Find_Negative_Edge = false;
	bool Find_Positive_Edge = false;
	int NegEdge_Found_cnt = 0; 
	int PosEdge_Found_cnt = 0;
	float NegEdge_value[25] = {0.0};
	float PosEdge_value[25] = {0.0};
	int NegEdge_addr[25] = {0};
	int PosEdge_addr[25] = {0};
	float PulseWidth = 0;
	float tLow[25] = {0.0};
	float tHigh[25] = {0.0};
	int FlagSkipFirst = 0;

	// Transfer Gage data //
	Gage_Transfer_Data (GAGE_CHAN_B); // Transfer data to Gage_chan_b_voltage array

	if (g_Save_Awav_TextDebug_ALL)
	{
		//double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		double *capture_data_B = (double *)malloc((g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		//for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
		for( i = 0; i < (g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10); i++)
		{	
			capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
		}
		CreateAwav(	capture_data_B, // Data array //
						g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10, // Size of array //
						20.0e-9, // Sampling period //				 
						"e:\\dl4\\tDableOn.awav"); // Output file and path //
		free (capture_data_B);
	}

	Find_Negative_Edge	= true;
	Find_Positive_Edge	= false;
	pulse_cnt =0;
	NegEdge_Found_cnt =0;
	PosEdge_Found_cnt =0;
	start_addr =0;	
	for(icnt =start_addr; icnt< g_SAMPLE_SIZE-10 ; icnt++)	
	{
		// Find Negative edge //
		if(Gage_chan_b_voltage[icnt] < 0.9 && Find_Negative_Edge ==true)
		{
			if (Freq1Mhz == 1) // 1Mhz //
			{
				NegEdge_value[pulse_cnt] = Gage_chan_b_voltage[icnt];
				NegEdge_addr[pulse_cnt] = icnt;
			}
			else // 300kHz //
			{
				// Go back to find actual turn-on point more exactly, use 3V as turn-on threshold. //
				i = 1;
				while (Gage_chan_b_voltage[icnt-i] < 3.0 && i<21) // Look back 20 points max //
				{	
					i++;
				}
				i=i-1;
				
				// Save result //
				NegEdge_value[pulse_cnt] = Gage_chan_b_voltage[icnt-i];
				NegEdge_addr[pulse_cnt] = icnt-i;
			}
			Find_Positive_Edge = true;
			Find_Negative_Edge = false;
			NegEdge_Found_cnt += 1;
			pulse_cnt++;
		}
		// Find Positive edge //
		else if(Gage_chan_b_voltage[icnt] > 1.75 && Find_Positive_Edge ==true)
		{
			PosEdge_value[pulse_cnt] = Gage_chan_b_voltage[icnt];
			PosEdge_addr[pulse_cnt] = icnt;
			Find_Positive_Edge = false;
			Find_Negative_Edge = true;
			PosEdge_Found_cnt += 1;
		}
	}

	// Analyze Results //
	*tDableON = -999;


	*tDableON = ( NegEdge_addr[1] - PosEdge_addr[1] ) * SAMPLE_RATE_s;
	*FWPK_tVOxDble = ( PosEdge_addr[1] - NegEdge_addr[0]) * SAMPLE_RATE_s;
	*FWPK_Timer = (PosEdge_addr[2] - NegEdge_addr[0]) * SAMPLE_RATE_s;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Find_Dtemp_code(int *Dtemp_code_Decimal, float *tLong_Dtemp, int *Dtemp_HighByte, float *tShort_Dtemp, int *Dtemp_LowByte)
{
	*Dtemp_code_Decimal	=0;
	*tLong_Dtemp			=0;
	*Dtemp_HighByte		=0;
	*tShort_Dtemp			=0;
	*Dtemp_LowByte		=0;

	if (!trig_ok || !data_ok)
	{
		// Bad acquisition //
		*Dtemp_code_Decimal	= -999;
		*tLong_Dtemp			= -999;
		*Dtemp_HighByte		= -999;
		*tShort_Dtemp			= -999;
		*Dtemp_LowByte		= -999;
		return;
	}

	// Declare Variables //
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int i=0, j=0;
	bool Find_Negative_Edge = false;
	bool Find_Positive_Edge = false;
	int NegEdge_Found_cnt = 0; 
	int PosEdge_Found_cnt = 0;
	float NegEdge_value[150] = {0.0};
	float PosEdge_value[150] = {0.0};
	int	  NegEdge_addr[150]	 = {0};
	int   PosEdge_addr[150]  = {0};
	float tHigh[150]		 = {0.0};
	float tLow[150]			 = {0.0};

	float	tLong_Pulse		= 0,
			tShort_Pulse	= 0,
			tBit_xx[150]	= {0};

	int		tLong_Pulse_start  = 0,
			tShort_Pulse_start = 0;

	int		Dtemp_code[150]	= {0};
			//Dtemp_code_Decimal= 0;
	
	char debug_file_name[150] ="/0"; 


	//Initialize array variables
	//for(i=0; i<16; i++)
	//{
	//	tBit_xx[i]  = 0;
	//	Dtemp_code[i] = 0;
	//}

	for(i=0; i<150; i++)
	{
		NegEdge_value[i]	= 0;
		PosEdge_value[i]	= 0;
		NegEdge_addr[i]		= 0;
		PosEdge_addr[i]		= 0;
		tHigh[i]			= 0;
		tLow[i]				= 0;
		tBit_xx[i]  = 0;
		Dtemp_code[i] = 0;
	}

	// Transfer Gage data //
	Gage_Transfer_Data (GAGE_CHAN_B); // Transfer data to Gage_chan_b_voltage array

	if (g_Save_Awav_TextDebug_ALL || g_Save_Awav_TextDebug_Dtemp)
	{
		char awav_file_name[150] ="/0"; 

		strcpy (awav_file_name, "e:\\DL4\\"); 
		strcat (awav_file_name, g_DevName); 
		strcat (awav_file_name, "_");
		strcat (awav_file_name, g_WAVE_NAME);
		strcat (awav_file_name, ".awav");

		//double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		double *capture_data_B = (double *)malloc((g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
		//for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
		for( i = 0; i < (g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10); i++)
		{	
			capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
		}
		CreateAwav(	capture_data_B, // Data array //
						g_SAMPLE_SIZE + GAGE_WAVEFORM_BUFFER_PAD - 10, // Size of array //
						20.0e-9, // Sampling period //		
						awav_file_name);
						//"e:\\dl4\\TREQ_INH.awav"); // Output file and path //
		free (capture_data_B);
	}

	Find_Negative_Edge	= true;
	Find_Positive_Edge	= false;
	pulse_cnt =0;
	NegEdge_Found_cnt =0;
	PosEdge_Found_cnt =0;
	start_addr =0;	
	for(icnt =start_addr; icnt< g_SAMPLE_SIZE-150 ; icnt++)	
	{
		// Find Negative edge //
		if(Gage_chan_b_voltage[icnt] < 0.2 && Find_Negative_Edge ==true)
		{
			NegEdge_value[pulse_cnt] = Gage_chan_b_voltage[icnt];
			NegEdge_addr[pulse_cnt] = icnt;
			Find_Positive_Edge = true;
			Find_Negative_Edge = false;
			NegEdge_Found_cnt += 1;
			pulse_cnt++;

			////// Skip ahead 2.5us if negative edge found to avoid ringing //
			////icnt += 125; // 2.5usec //
		}
		// Find Positive edge //
		else if(Gage_chan_b_voltage[icnt] > 0.25 && Find_Positive_Edge ==true)
		{
			PosEdge_value[pulse_cnt] = Gage_chan_b_voltage[icnt];
			PosEdge_addr[pulse_cnt] = icnt;
			Find_Positive_Edge = false;
			Find_Negative_Edge = true;
			PosEdge_Found_cnt += 1;
		}
		//Break out of for loop
		if(pulse_cnt > 70) 
			icnt=g_SAMPLE_SIZE;	//Break out of for loop 
	}
	pulse_cnt = pulse_cnt - 1; // To get total number of pulses //

	//Sort out all of the pulse width
	tLong_Pulse_start  = 0;
	tShort_Pulse_start = 0;
	for(i=1; i<=70; i++)	//Search within the 70 pulses
	{
		//ignore first pulse since you don't know if you will start from Positive or Negative edge of the waveform
		tHigh[i]	= NegEdge_addr[i]	- PosEdge_addr[i];
		tLow[i]		= PosEdge_addr[i+1] - NegEdge_addr[i];

		if(tHigh[i] > 400 && tLong_Pulse_start==0)		
		{
			tLong_Pulse			= tHigh[i];
			tLong_Pulse_start	= i;
		}
		if(tLong_Pulse_start > 0 && tShort_Pulse_start==0)	//found tLong_Pulse.  Now find tShort_Pulse
		{
			if(tHigh[i] > 160 && tHigh[i] < 400)	
			{
				tShort_Pulse		= tHigh[i];
				tShort_Pulse_start	= i;
			}
		}		
		//Break out of for loop if both Long/Short pulses and the 8 bits after Short Pulses are found
		if(tLong_Pulse_start != 0 && tShort_Pulse_start != 0 && i>(tShort_Pulse_start+8) )
			i = 71;
	}

	//Find Long Pulse and Short pulse
	j=15;
	i=tLong_Pulse_start;
	while( i <= (tShort_Pulse_start+8) && j>=0)
	//for(i=tLong_Pulse_start; i<=(tShort_Pulse_start+8); i++)
	{
		tBit_xx[j] = tLow[i];					//MSB --> LSB
		if(tBit_xx[j] > 75)		Dtemp_code[j] = 1;
		else					Dtemp_code[j] = 0;
		j--;
		i++;
	}

	*Dtemp_code_Decimal = 0;
	*Dtemp_LowByte	  = 0;
	*Dtemp_HighByte	  = 0;
	//Convert low 9 bits tBit_xx[0_to_8] to Decimal for Dtemp code
	for(j=0; j<=15; j++)
	{
		if(j<=8)
			*Dtemp_code_Decimal	+= Dtemp_code[j] * pow(2.0,j);
		if(j<=7)
			*Dtemp_LowByte		+= Dtemp_code[j] * pow(2.0,j);		//bits 7:0
		if(j>=8)
			*Dtemp_HighByte		+= Dtemp_code[j] * pow(2.0,(j-8));	//bits 15:8
	}

	*tLong_Dtemp  = tLong_Pulse;
	*tShort_Dtemp = tShort_Pulse;
	if(tShort_Pulse < 1e-6)	
		*Dtemp_code_Decimal = -999;

	//DEBUG text File
	if(g_Save_Awav_TextDebug_Dtemp || g_Save_Awav_TextDebug_ALL)
	{
		int i=0;
		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_");
		strcat (debug_file_name, g_WAVE_NAME);
		strcat (debug_file_name, "_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf(fpr,"WAVE_NAME= %s \n\n",g_WAVE_NAME);

		//measured values
		fprintf(fpr,"Dtemp_code_Decimal \t= %i  \t\tDtemp_LowByte = %i ,  \tDtemp_HighByte = %i \n",*Dtemp_code_Decimal,  *Dtemp_LowByte,  *Dtemp_HighByte);
		fprintf(fpr,"tLong_Dtemp \t\t= %.1f us  \ttShort_Dtemp = %.1f us \n",*tLong_Dtemp*20e-9*1e6,  *tShort_Dtemp*20e-9*1e6);
		fprintf(fpr,"tLong_Pulse_start \t= %i   \t\ttShort_Pulse_start = %i \n",tLong_Pulse_start,  tShort_Pulse_start);


		fprintf(fpr,"\nData: \n\n",g_WAVE_NAME);
		//Peak data
		fprintf(fpr,"Pulse \tNegEdge_addr \tNegEdge_val(V) \tPosEdge_addr \tPosEdge_val(V) \ttHigh(us), \ttLow(us) \n"); 
		fprintf(fpr,"-----------------------------------------------------------------------------------------------------\n"); 
		for(i=0; i<=70; i++)
		{
			fprintf(fpr,"%i \t%i \t\t%.2f \t\t%i \t\t%.2f \t\t%.2f \t\t%.2f \n", 
						  i, NegEdge_addr[i], NegEdge_value[i], PosEdge_addr[i], PosEdge_value[i], tHigh[i], tLow[i] );

		}
		fprintf (fpr, "End of Data\n");
		fclose(fpr);

	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Create_Awav_xp (	char	*wave_name,
						float   *v_data,
						int		arr_size,
						float	samp_rate )
{
	//GetSerialNum(Dut_serial_number);

//		strcpy (Wav_outfile_name, Wav_Outfile_path); 
		strcpy (Wav_outfile_name, "e:\\DL4\\"); 
		strcat (Wav_outfile_name, Part_ID_LimitSet); 
		//strcat (Wav_outfile_name, "_#"); strcat (Wav_outfile_name, Dut_serial_number); 
		strcat (Wav_outfile_name, "_"); 
		strcat (Wav_outfile_name, g_WAVE_NAME);
		//strcat (Wav_outfile_name, "_"); strcat (Wav_outfile_name, Hdwr_id); 
		strcat (Wav_outfile_name, ".awav"); 

		FILE * fpr_1 = fopen (Wav_outfile_name, "w"); 
		if (!fpr_1) return;

		fprintf (fpr_1, "version awav 0 2 0;\n");
		fprintf (fpr_1, "date 07 10 2003;\n");
		fprintf (fpr_1, "time 14 42 47;\n");
		fprintf (fpr_1, "name =  \"result_data\";\n");
		fprintf (fpr_1, "type = rrect;\n");
		fprintf (fpr_1, "size = %d;\n", arr_size);
		fprintf (fpr_1, "sample_interval = %13.11e;\n", samp_rate);
		fprintf (fpr_1, "offset = 0.000000e+000;\n");
		fprintf (fpr_1, "x_units = \"s \";\n");
		fprintf (fpr_1, "y_units = \"V \";\n");
		fprintf (fpr_1, "pattern;\n");
		fprintf (fpr_1, "  !Value\n");

		for (int i = 0; i < arr_size; i++)	
		{
			if ( v_data[i] >= 0.0) fprintf (fpr_1, "+");
			fprintf (fpr_1, "%18.16e; !%d\n", v_data[i] * 2.0, i);
		}

		fprintf (fpr_1, "pattern_end;\n"); fclose (fpr_1);
	return;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//=================== XP gage digitizer Setup Codes STARTS here ===================
void Gage_init() {	
	
	//	CsFreeSystem(hSystem);	//Call only once at end of program
	//	InitBoard();	//Call only once at program load

	float gain = 1.00;		// start with 1.00 56X
	trig_ok = true;
	data_ok = true;

	CsAcqCfg.i64TriggerHoldoff=Gage_pretrig_samples;

	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg;
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate = 50000000;    //50Mhz
	CsAcqCfg.i64Depth = 8192-CsAcqCfg.i64TriggerHoldoff;             //8K  4K
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount = 1;
	CsAcqCfg.i64TriggerTimeout = 100; //Definition: 100ns units.
	CsAcqCfg.u32ExtClk = 0;

	CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);


//Set CHANA to 200mV Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = CS_GAIN_400_MV	;     //400<==>200mVp-p, 4000==>2V
	CsChanCfg.u32Impedance = CS_REAL_IMP_1M_OHM	;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);


	//Set CHANB to 5V Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;      //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 10000;     //5Vp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);


	//CSTRIGGERCONFIG CsTrigCfg;
	CsTrigCfg.u32Size = sizeof(CSTRIGGERCONFIG);
	CsTrigCfg.u32TriggerIndex		= 1;	//should always be 1
	CsTrigCfg.i32Source = CS_TRIG_SOURCE_CHAN_1;     //Channel A
	CsTrigCfg.u32ExtCoupling = CS_COUPLING_DC;		//GAGE_DC
	CsTrigCfg.u32ExtTriggerRange = 400; //2000;             //GAGE_PM_1_V
    CsTrigCfg.u32Condition = CS_TRIG_COND_NEG_SLOPE; //GAGE_NEGATIVE
	CsTrigCfg.i32Level = 0;							//Trigger Level 0V
	CsTrigCfg.u32ExtImpedance = 10000000;           //Impedance = 10Mhz;
	CsSet(hSystem, CS_TRIGGER, &CsTrigCfg);

	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.

	//Get the current sample size, resolution and offset parameters from the driver
	//by calling CsGet for the ACQUISTIONCONFIG structure. These values are used
	//when saving the file.

	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	if (CS_FAILED(i32Status))
	{
		
		CsFreeSystem(hSystem);
		
	}

    CsAppData.i64TransferLength = GAGE_WAVEFORM_BUFFER_SIZE;
	CsAppData.u32TransferSegmentCount = 1;
	CsAppData.u32TransferSegmentStart = 1;
	CsAppData.u32PageSize = 32768;
	CsAppData.i32SaveFormat = 2;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Setup_Acquisition_xp ( int sample_rate_in_Hz, int g_SAMPLE_SIZE )
{
	//Setup gage acquisition using XP driver
	//must be followed by ACTION_COMMIT to send settings to Hardware.
	CsAcqCfg.u32Size             = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode             = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate       = sample_rate_in_Hz ;    //example:50000000
	CsAcqCfg.i64Depth            = g_SAMPLE_SIZE-CsAcqCfg.i64TriggerHoldoff; 
	CsAcqCfg.i64SegmentSize		 = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount	 = 1;
	CsAcqCfg.i64TriggerTimeout   = 100; //Definition: 100ns units.
	CsAcqCfg.u32ExtClk           = 0;
	CsAcqCfg.i64TriggerTimeout   = CS_TIMEOUT_DISABLE;

	i32Status = CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);
	//must be followed by ACTION_COMMIT to send settings to Hardware.
//	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.
/*	char *lpBuffer;
	int  nBufferMax = 100;
	CsGetErrorString( i32Status,lpBuffer, nBufferMax);*/

	if (CS_FAILED(i32Status))
	{
//		MessageBox(NULL,"Error while setting Gage_Setup_Acquisition_xp.","Error", MB_OK);
	}

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Setup_Chan_A ( int pk_pk_range_in_mV )
{
	//Setup Gage CHAN_A
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size         = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;                   //Channel A
	CsChanCfg.u32Term         = CS_COUPLING_DC;      //GAGE_DC
	CsChanCfg.u32InputRange   = pk_pk_range_in_mV ;  //mVp-p (example:400 -> 400mV pk-pk -> +/-200mV)
	CsChanCfg.u32Impedance    = 1000000;             //1 MOhm impedance
	CsChanCfg.i32DcOffset     = 0;                   //no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Setup_Chan_B ( int pk_pk_range_in_mV )
{
	//Setup Gage CHAN_B
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;                //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC;           //GAGE_DC
	CsChanCfg.u32InputRange = pk_pk_range_in_mV ; //Example: 10000 = 5Vp-p
	CsChanCfg.u32Impedance = 1000000;             //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;                    //no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
	//must be followed by ACTION_COMMIT to send settings to Hardware.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int gage_input_control_xp (int16 channel, int16 enable, int16 coupling, int16 gain)
{
	//Setup Gage CHAN_B
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	if (channel==GAGE_CHAN_A)
		CsChanCfg.u32ChannelIndex = 1;                //Channel A
	else
		CsChanCfg.u32ChannelIndex = 2;                //Channel B
	////Fixed DC coupling
	CsChanCfg.u32Term = CS_COUPLING_DC;           //GAGE_DC
	//Set range
	if (gain == GAGE_PM_5_V)
		CsChanCfg.u32InputRange = 10000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_2_V)
		CsChanCfg.u32InputRange = 4000 ; //Example: 4000 = 2Vp-p
	if (gain == GAGE_PM_1_V)
		CsChanCfg.u32InputRange = 2000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_500_MV)
		CsChanCfg.u32InputRange = 1000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_200_MV)
		CsChanCfg.u32InputRange = 400 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_100_MV)
		CsChanCfg.u32InputRange = 200 ; //Example: 10000 = 5Vp-p
	
	CsChanCfg.u32Impedance = 1000000;			//Fixed 1 MOhm impedance        
	CsChanCfg.i32DcOffset = 0;					//no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);		//must be followed by ACTION_COMMIT to send settings to Hardware.
	i32Status = CsDo(hSystem, ACTION_COMMIT);	//Send settings to Hardware.

	if (i32Status>0)
		return 1;	//success
	else
		return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//** gage_trigger_control_xp **
//int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, int16 level_in_volts, int32 depth)
int gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, float level_in_volts, int32 depth)
{
	//CSTRIGGERCONFIG CsTrigCfg;
	CsTrigCfg.u32Size				= sizeof(CSTRIGGERCONFIG);
	CsTrigCfg.u32TriggerIndex		= 1;	//should always be 1
	//source
	if ( source == GAGE_EXTERNAL )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_EXT;  //Channel A
	else if ( source == GAGE_CHAN_A )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_CHAN_1;  //Channel A
	else if ( source == GAGE_CHAN_B )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_CHAN_2;  //Channel B

	//coupling
	if ( ext_coupling == GAGE_DC )
		CsTrigCfg.u32ExtCoupling     = CS_COUPLING_DC;	       //GAGE_DC

	//ext trig range
	if ( ext_gain == GAGE_PM_10_V )
		CsTrigCfg.u32ExtTriggerRange = 20000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_5_V )
		CsTrigCfg.u32ExtTriggerRange = 10000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_2_V )
		CsTrigCfg.u32ExtTriggerRange = 4000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_1_V )
		CsTrigCfg.u32ExtTriggerRange = 2000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_500_MV )
		CsTrigCfg.u32ExtTriggerRange = 1000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_200_MV )
		CsTrigCfg.u32ExtTriggerRange = 400;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_100_MV )
		CsTrigCfg.u32ExtTriggerRange = 200;  //pk_pk_range_in_mV 

	//slope
	if ( slope == GAGE_POSITIVE )
    	CsTrigCfg.u32Condition       = CS_TRIG_COND_POS_SLOPE; //GAGE_POSITIVE
	else
    	CsTrigCfg.u32Condition       = CS_TRIG_COND_NEG_SLOPE; //GAGE_NEGATIVE

	//Trigger level as a percentage of the trigger source input range, 0% is 0V, 100% is full scale positive
	//source
	if ( source == GAGE_EXTERNAL )
		//Set external trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsTrigCfg.u32ExtTriggerRange/2);	
	else if ( source == GAGE_CHAN_A )
	{
		//Find Chan A range
		CsChanCfg.u32ChannelIndex = 1;                //Channel A
		CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		//Set Chan A trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsChanCfg.u32InputRange/2);	
	}
	else if ( source == GAGE_CHAN_B )
	{
		//Find Chan B range
		CsChanCfg.u32ChannelIndex = 2;                //Channel B
		CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		//Set Chan B trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsChanCfg.u32InputRange/2);	
	}

	//Set trigger values
	CsSet(hSystem, CS_TRIGGER, &CsTrigCfg);

	//Set Acquisition depth
	CsAcqCfg.i64Depth       = depth-CsAcqCfg.i64TriggerHoldoff;             
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);

	
	//Note: must be followed by ACTION_COMMIT to send settings to Hardware.
	i32Status = CsDo(hSystem, ACTION_COMMIT);

	Gage_print_error("gage_trigger_control_xp");

	if (i32Status>0)
		return 1;	//success
	else
		return 0;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Commit ( void )	//Send to hardware
{
	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Start_Capture( void )
{	//Begin Data Capture
	i32Status = CsDo(hSystem, ACTION_START);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Wait_For_Capture_Complete( void )
{	//capture wait loop after capture has been started, Gage_trig_ok,Gage_data_ok status is set
	int gageStatus=-1,icnt;

	//Get starting time stamp
	timenow[2] = mytimer.GetElapsedTime();
	starttime = timenow[2];

	//Retrieve initial Capture Status.
	i32Status = CsGetStatus(hSystem);
	Sleep(0);
	//if (i32Status==0)printf("initial i32Status=0\n");

   	//Wait until ACQ_STATUS_READY is true

	int  while_flag = 1; //To prevent infinite loop.
	while (while_flag && (i32Status != ACQ_STATUS_READY))
	{
		stoptime = mytimer.GetElapsedTime();
		i32Status = CsGetStatus(hSystem);
		Sleep(0);
		if((float)(stoptime-starttime) >=30000)	//30000=30ms
		{
			CsDo(hSystem, ACTION_FORCE);	//Force capture.
			printf("\nGage Forced capture\n");
			for (icnt=0;icnt<=150;icnt++)
			{	
				wait.delay_10_us(10);			//wait for forced capture to end
				gageStatus = CsGetStatus(hSystem);
				if (gageStatus == ACQ_STATUS_READY)
					break;
			}
			while_flag = 0; //condition to exit loop.
		}
	}

	//calculate capture time
	stoptime = mytimer.GetElapsedTime();
	float temp_1 = float(stoptime-starttime);
	int debug_capture=0;
	if (debug_capture){
		printf("acquisition time= %8.3f ms, Status=%i \n",temp_1/1000.0,i32Status);
	}

	if (i32Status == ACQ_STATUS_READY) {	//0=ACQ_STATUS_READY, 1=ACQ_STATUS_WAIT_TRIGGER
		//change variable here to match rest of program
		trig_ok = TRUE;
		//Gage_trig_ok = TRUE;
		//Gage_data_ok = TRUE;
	}
	else {
		//capture was forced
		//change variable here to match rest of program
		trig_ok = FALSE;
		//Gage_trig_ok = FALSE;
		//Gage_data_ok = FALSE;
	}

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Transfer_Data ( int channel_num )
{	
	int i;
	int icnt; 
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_a_16_raw;
	else
		InData.pDataBuffer = chan_b_16_raw;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_a_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_b_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));

	// QMc 02-21-13
	// Initialize Gage_chan_a and Gage_chan_b, so the data from the previous unit can't be used for current testing unit
	if (channel_num == GAGE_CHAN_A)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_a_voltage[icnt] =0.0;
		}
	}
	else if (channel_num == GAGE_CHAN_B)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_b_voltage[icnt] =0.0;
		}
	}


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);

		return;
	}

	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_a_16_raw, Gage_chan_a_voltage);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_b_16_raw, Gage_chan_b_voltage);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data()

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Transfer_DataM ( int channel_num )
{	
	int i;
	int icnt; 
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_a_16_rawM;
	else
		InData.pDataBuffer = chan_b_16_rawM;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_a_16_rawM,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_b_16_rawM,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD));

	// QMc 02-21-13
	// Initialize Gage_chan_a and Gage_chan_b, so the data from the previous unit can't be used for current testing unit
	if (channel_num == GAGE_CHAN_A)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_a_voltageM[icnt] =0.0;
		}
	}
	else if (channel_num == GAGE_CHAN_B)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_b_voltageM[icnt] =0.0;
		}
	}


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);

		return;
	}

	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_a_16_rawM, Gage_chan_a_voltageM);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_b_16_rawM, Gage_chan_b_voltageM);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data()

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_Transfer_Data_ilim_states ( int channel_num )
{
	int i;
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_aa_16_raw;
	else
		InData.pDataBuffer = chan_bb_16_raw;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_aa_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_bb_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);
		return;
	}


	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_aa_16_raw, Gage_chan_aa_voltage);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_bb_16_raw, Gage_chan_bb_voltage);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data_ilim_states()

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_print_error(string text_str)
{
	//Print the Gage error status to the console (DOS) window
	//use if return value <0 for CsDo,CsFreeSystem,CsGet,CsGetStatus,CsGetSystem,CsInitialize,CsSet,CsTransfer
	if ((debug_gage_error) && (i32Status<0)){
		char return_string2[40]=" ";
		CsGetErrorString(i32Status,return_string2,40);
		printf("Gage Error Status (%s): %s\n",text_str.c_str(),return_string2);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_print_setup(string text_str)
{
	//Print the Gage settings to the Console (DOS) Window
	printf("Gage Status (%s):\n",text_str.c_str());
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	printf("  Sample Size= %i \n",CsAcqCfg.i64Depth		);
	printf("  Sample Rate= %i Msa/sec\n",CsAcqCfg.i64SampleRate /1000000		);
	
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	printf("  Chan A Input Range (mV,pk-pk)= %i\n",CsChanCfg.u32InputRange 		);
	int chan_a_rng=CsChanCfg.u32InputRange;
	CsChanCfg.u32ChannelIndex=2;//chan b
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	printf("  Chan B Input Range (mV,pk-pk)= %i\n",CsChanCfg.u32InputRange 		);
	int chan_b_rng=CsChanCfg.u32InputRange;


	i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);
	if (CsTrigCfg.i32Source == 1)
	{
		printf("  Trigger source= CHAN_1\n"	);
		printf("  Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)chan_a_rng/2) 	);
	}
	if (CsTrigCfg.i32Source == 2)
	{
		printf("  Trigger source= CHAN_2\n");
		printf("  Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)chan_b_rng/2) 	);
	}
	if (CsTrigCfg.i32Source == -1)
	{
		printf("  Trigger source= EXTERNAL\n"	);
		printf("  Ext Trig Full Scale Range (mV)= %i\n",CsTrigCfg.u32ExtTriggerRange 		);
		printf("  Ext Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Ext Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)CsTrigCfg.u32ExtTriggerRange/2) 	);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int	Gage_loadtime_setup (void)
{
/*	Initializes all the CompuScope boards found in the system.  The routine
	attempts to read the GAGESCOP.INC configuration file to find out the memory
	segment and I/O addresses of the boards. The routine also updates several tables
	and structures depending upon the board type that is found.
*/
//Call InitBoard only once


//	uInt32					i;
	//LPCTSTR					szIniFile = _T("Acquire.ini");	
	int64					i64Padding = 64; //extra samples to capture to ensure we get what we ask for



/*
	Initializes the CompuScope boards found in the system. If the
	system is not found a message with the error code will appear.
	Otherwise i32Status will contain the number of systems found.
*/
	i32Status = CsInitialize();

	if (CS_FAILED(i32Status))
	{
		//MessageBox(NULL, str, "Razor Digitizer Fails to Initialize", MB_OK);
		MessageBox(NULL,"RAZOR FAILS TO INITIATE!","Error", MB_OK);
		
	}

	//Obtain the handle to the first Compuscope in the system
	i32Status = CsGetSystem(&hSystem, 0, 0, 0, 0);


	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to Obtain Razor Handle!","Error", MB_OK);		
	}

/*
	Get System information. The u32Size field must be filled in
	 prior to calling CsGetSystemInfo
*/
	CsSysInfo.u32Size = sizeof(CSSYSTEMINFO);
	i32Status = CsGetSystemInfo(hSystem, &CsSysInfo);


/*
	Display the system name from the driver
*/
	_ftprintf(stdout, _T("\nBoard Name: %s"), CsSysInfo.strBoardName);  //Display Razor Model


	//Set CHANA, CHANB, Trigger for Razor
	
	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg

	CsAcqCfg.u32Size = sizeof(CsAcqCfg);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);

	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg;
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate = 50000000;    //50Mhz
	CsAcqCfg.i64Depth = 8192-CsAcqCfg.i64TriggerHoldoff;             //8K
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount = 1;
	CsAcqCfg.i64TriggerTimeout = 10000000;
	CsAcqCfg.u32ExtClk = 0;


	i32Status = CsDo(hSystem, ACTION_COMMIT);

	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting Dual Mode.","Error", MB_OK);
		CsFreeSystem(hSystem);
	}
/*
	Get the current sample size, resolution and offset parameters from the driver
	by calling CsGet for the ACQUISTIONCONFIG structure. These values are used
	when saving the file.
*/
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured Dual Mode parameters from driver!","Error", MB_OK);
		CsFreeSystem(hSystem);
	}


	//Set CHANA to 200mV Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg_B.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 400;      //200mVp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);

	i32Status = CsDo(hSystem, ACTION_COMMIT);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting CHAN A Input Control.","Error", MB_OK);
		CsFreeSystem(hSystem);
	}

	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured CHAN A parameters from driver!","Error", MB_OK);
		CsFreeSystem(hSystem);
	}


		//Set CHANB to 5V Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;      //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 10000;      //5Vp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
	
	i32Status = CsDo(hSystem, ACTION_COMMIT);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting CHB Input Control.","Error", MB_OK);
		CsFreeSystem(hSystem);
	}

	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured CHAN B      parameters from driver!","Error", MB_OK);
		CsFreeSystem(hSystem);
	}


/*
	We need to allocate a buffer
	for transferring the data
*/

	CsAppData.i64TransferLength = GAGE_WAVEFORM_BUFFER_SIZE;

	pBuffer  = VirtualAlloc(NULL, (size_t)((CsAppData.i64TransferLength + i64Padding) * CsAcqCfg.u32SampleSize), MEM_COMMIT, PAGE_READWRITE);

  
	if (NULL == pBuffer)
	{
		//_ftprintf (stderr, _T("\nUnable to allocate memory\n"));
		MessageBox(NULL,"Unable to allocate memory!","Error", MB_OK);
		CsFreeSystem(hSystem);
	}

	if (TYPE_FLOAT == CsAppData.i32SaveFormat)
	{
/*
		Allocate another buffer to pass the data that is going to be converted
		into voltages
*/
		pVBuffer  = (float *)VirtualAlloc(NULL, (size_t)(CsAppData.i64TransferLength * sizeof(float)), MEM_COMMIT, PAGE_READWRITE);

		if (NULL == pVBuffer)
		{
			//_ftprintf (stderr, _T("\nUnable to allocate memory\n"));
			MessageBox(NULL,"Unable to allocate memory!","Error", MB_OK);
			CsFreeSystem(hSystem);
			VirtualFree(pBuffer, 0, MEM_RELEASE);
			
		}
	}

  return (0);

}       /*  End of Gage_loadtime_setup ().  */

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Gage_cal_table_setup_xp()
{
	//Force Gage Calibration
	//This routine calibrates Chan A at 4 settings and Chan B at 4 settings
	//The user can comment out the unescessary ranges
	//run this routine at program load time
	//Note: Gage will automatically run calibration at EVERY input change for the first 20 minutes after system boot-up

	//Set input voltage range, +/-500mV
	Gage_Setup_Chan_A (1000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-1V
	Gage_Setup_Chan_A (2000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-2V
	Gage_Setup_Chan_A (4000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-5V
	Gage_Setup_Chan_A (10000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//B input settings
	//Set input voltage range, +/-500mV
	Gage_Setup_Chan_B (1000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-1V
	Gage_Setup_Chan_B (2000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-2V
	Gage_Setup_Chan_B (4000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-5V
	Gage_Setup_Chan_B (10000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	debug_test_time=0;
	if (debug_test_time)
	{
		initial_time = mytimer.GetElapsedTime();	// start trimming
		Gage_Setup_Chan_A(2000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_A complete");
		Gage_Setup_Chan_B(1000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_B complete");
		Gage_Setup_Chan_A(10000); 	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_A complete");
		Gage_Setup_Chan_B(10000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_B complete");
		debug_test_time=0;
	}

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void PrintCaptureTime(string text_str)
{
	double elapsed_time;
	if (!debug_test_time)
		return;
	current_time = mytimer.GetElapsedTime();	// start trimming
	elapsed_time = (double)(current_time-initial_time)/1e6;// elapsed time
	printf("Elapsed Capture Time, %s: %6.0f msec\n",text_str.c_str(),	elapsed_time*1e3);

	return;
}

//=================== XP gage digitizer Setup Codes ENDS here ===================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
char* GetCSVPath (const char* dllpath, const char* csvname)
{
  size_t len = strlen(dllpath) + strlen(csvname) + 1;  // little more space than should need
  char* csvpath = (char*) calloc((len + 1), sizeof(char));
  strncpy(csvpath, dllpath, len);
  char* bs1 = strrchr(csvpath,'\\');
  *bs1 = '\0';  // replace right most backslash with string terminator
  char* bs2 = strrchr(csvpath,'\\');
  *bs2 = '\0';  // replace 2nd from right backslash with string terminator
  strncat(csvpath, "\\Programs\\",(len - strlen(csvpath)));
  strncat(csvpath, csvname, (len - strlen(csvpath)));
  return(csvpath);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool PIPulse::do_pulse(void)
{
	//do_pulse() provides a debug pulse on J1B9
	Dvi *Pulse_dvi = dvi_9;
	//Read initial data
	unsigned short regData = Pulse_dvi->card.adc_val;

	if ( pulse_width_in_seconds < 10e-6)
		pulse_width_in_seconds=10e-6;
	
	if ( pulse_width_in_seconds > 10e-3)
		pulse_width_in_seconds=10e-3;
	
	// Set Ext Clock Low
	regData &= ~DUT_NVRAM_CK;

	//Output low
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;

	// Set Ext Clock High
	regData |= DUT_NVRAM_CK;

	//Output high
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;

	//Pulse width
	wait.delay_10_us((unsigned long) (pulse_width_in_seconds*1e5));

	// Set Ext Clock Low
	regData &= ~DUT_NVRAM_CK;

	//Output low
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;
	
	return true;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPP_Power_Up_w_Test_Mode(int TestModeSelect, int ILIM_Mode)
{
	// TestMode1 selected //
	//	- Speed up everything by 32x.  Expect ~2.5ms/~65ms  ON_Time/OFF_Time
////	if (TestModeSelect == gTM1_p ||
////		TestModeSelect == gTM_OverTemp ||
////		TestModeSelect == gTM_Fast_Counter_32x ||
////		TestModeSelect == gTM_TonMax1us ||
////		TestModeSelect == gTM_Receiver_Threshold ||
////		TestModeSelect == gTM1_UVOV_NoDelay)
////	{
////			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);	// DVI_11_0	//
////			wait.delay_10_us(5);
////	}
////	// TestMode2 selected //
////	else if (TestModeSelect == gTM2_p ||
////			TestModeSelect == gTM_Trim_Readable ||
////			TestModeSelect == gTM_Jitter_to_Vpin ||
////			TestModeSelect == gTM_MaxF_to_Vpin ||
////			TestModeSelect == gTM_ILIM ||
////			TestModeSelect == gTM2_UVOV_NoDelay)
////	{
////			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////			D_dvi->set_voltage(D_ch, 15.0, VOLT_50_RANGE);	// DVI_11_0	//
////			wait.delay_10_us(20);
////	}
////	if (TestModeSelect == gTM_Jitter_to_Vpin ||
////	    TestModeSelect == gTM2_UVOV_NoDelay )	// 45V from Lance //
////	{
////			D_dvi->set_voltage(D_ch, 45.0, VOLT_50_RANGE); // DVI_11_0	
////			wait.delay_10_us(20);
////	}
////	if (TestModeSelect == gTM2_UVOV_NoDelay || 
////	    TestModeSelect == gTM1_UVOV_NoDelay    ) 
////	{
////		// UV pin (Vpin) set to 6V/80uA before PU //
////		VPIN_ovi->set_voltage(VPIN_ch, 6.0, RANGE_10_V);  
////		VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);	
////	}
////	else
////	{
////		// UV pin (Vpin) set to 0V before PU //
////		VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);  
////		VPIN_ovi->set_current(VPIN_ch, 20e-3, RANGE_30_MA);	
////	}
////	
////	//BPP set 0V
////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
////	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V); // OVI_1_0 //
////	wait.delay_10_us(5);
////
////	// BPP ramp up to VBPP_PV  (Note: DO NOT GO ABOVE 5.5V ON BPP, Above 5.5V might cause damage to device) //
////	VBPP_ramp_up(3.5, gVBPP_PV_final, 0.2);
////	wait.delay_10_us(5);			
////
////// B2 //
//////	if(BPP_4p7uF) delay(3);
//////	if(BPP_p47uF) delay(1);
////
////// B3 //
//////	if(BPP_4p7uF) delay(3);
//////	if(BPP_p47uF) delay(1);
////
////	// TestModeSelect2 //
////	if (TestModeSelect == gTM2_p ||
////	    TestModeSelect == gTM_Trim_Readable ||
////	    TestModeSelect == gTM_Jitter_to_Vpin ||
////	    TestModeSelect == gTM_MaxF_to_Vpin ||
////	    TestModeSelect == gTM_ILIM ||
////	    TestModeSelect == gTM2_UVOV_NoDelay )
////	{
////			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0 //	
////			wait.delay_10_us(5);
////	}
////
////	// Additional delay for UVOV testmode //
////	if(TestModeSelect == gTM2_UVOV_NoDelay ||
////	   TestModeSelect == gTM1_UVOV_NoDelay    		) 
////		wait.delay_10_us(30);
////
////	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // 15mA here so iBPP_minus won't clamp at 2mA from above for B3 silicon
////	
////	// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION) //
////	if     (ILIM_Mode == ILIM_NORM) wait.delay_10_us(3); //1.0uF (ILIM) 30us //
////	else if(ILIM_Mode == ILIM_INCR) wait.delay_10_us(150); //10uF (ILIM+1) 1.2ms //
////	wait.delay_10_us(1); // Delay is critical for 1.8A device.  w/o 10us, ILIM read 70mA lower and not as repeatable.
////
////	//TestModeSelect2
////	if (TestModeSelect == gTM2_p ||
////		TestModeSelect == gTM_Trim_Readable ||
////		TestModeSelect == gTM_Jitter_to_Vpin ||
////		TestModeSelect == gTM_MaxF_to_Vpin ||
////		TestModeSelect == gTM_ILIM ||
////		TestModeSelect == gTM2_UVOV_NoDelay ||
////		TestModeSelect == gTM1_UVOV_NoDelay)
////	{
////			//Drain = 0V
////			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0 //
////	}
////
////	VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.25, 0.1); // vstart, vstop, vstep //	
////	wait.delay_10_us(10);
////// B2 //
//////	if(BPP_4p7uF) delay(3);
//////	if(BPP_p47uF) delay(1);
////
////// B3 //
//////	if(BPP_4p7uF) delay(3);
//////	if(BPP_p47uF) delay(1);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material
////	VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
////	
////	wait.delay_10_us(10);
////
////	//TestModeSelect2
////	if (TestModeSelect == gTM2_p ||
////		TestModeSelect == gTM_Trim_Readable ||
////		TestModeSelect == gTM_Jitter_to_Vpin ||
////		TestModeSelect == gTM_MaxF_to_Vpin ||
////		TestModeSelect == gTM_ILIM)
////	{
////			//Drain = 7V	(6V not enough to read the fuse links)
////			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
////			D_dvi->set_voltage(D_ch, 10.0, 		VOLT_50_RANGE);	// DVI_11_0	
////			wait.delay_10_us(50);
////	}
////	else
////	{
////			//Drain = 2.5V (in DR doc, but 1V would be better for noise)
////			D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, 	VOLT_5_RANGE);	// DVI_11_0	
////	}
////
////	if (TestModeSelect == gTM2_UVOV_NoDelay	||
////	    TestModeSelect == gTM1_UVOV_NoDelay		)
////	{
////			D_dvi->set_voltage(D_ch, 2.0, 	VOLT_50_RANGE);	// DVI_11_0	
////			wait.delay_10_us(5);
////	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Powerup_Primary_in_Testmode(int Testmodes)
{
	////float vDrainPowerup =0;

	//////Drain_P set to 0V
	////D_dvi->set_voltage(D_ch, 0.0,  VOLT_10_RANGE); // DVI_11_0
	////D_dvi->set_current(D_ch, 30.0e-3, RANGE_30_MA);
	////wait.delay_10_us(10);
	////
	//////Bpp set 5V for 100us
	////VBPP_ramp_up(0.0, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 200mV step

	////if(Testmodes == gOT_Mode)	
	////	Force_Vpin_Pulses_nTimes(4);	//Vpin clock 4 pulses (10us positive) to enter OT mode
	////else
	////{
	////	Force_Vpin_Pulses_nTimes(3);	//Vpin clock 3 pulses (10us positive) to enter write mode
	////	//Drain setup to be able to see AF links
	////	vDrainPowerup = 40;
	////	dvi_11->set_voltage(DVI_CHANNEL_0, vDrainPowerup, VOLT_50_RANGE);
	////	wait.delay_10_us(50);
	////}

	//////Bpp ramp from 5V -> gVBPP_PV_final -> 5V with 50mV step
	////VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);		
	////VBPP_ramp_down(gVBPP_PV_final, 5, 50e-3);	

	////switch (Testmodes)
	////{
	////	case gWrite_Mode_ReadAF:
	////		D_dvi->set_voltage(D_ch, gVread_AF_primary, VOLT_50_RANGE);	//AF Reading vDrain
	////		break;

	////	case gWrite_Mode_TrimAF:
	////		D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE);		//AF Trimming vDrain
	////		break;

	////	case gOT_Mode:
	////		BPP_ovi->set_voltage(BPP_ch, 4.1, RANGE_10_V); // OVI_1_0 //
	////		wait.delay_10_us(50);
	////		//Drain set to 2V so device will switch at a low voltage
	////		D_dvi->set_voltage(D_ch, 2.0, VOLT_5_RANGE);
	////		wait.delay_10_us(30);
	////		BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	////		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V); // OVI_1_0 //
	////		wait.delay_10_us(10);
	////		break;

	////	default:
	////		break;
	////}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_Observe_Mode(int ObsMode_xx) 
{
////	int num_pulses_Vpin = 0;
////	int i = 0;
////	
////	//Drain (0V/3mA)
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
////	wait.delay_10_us(20);
////
////	//BPP set 0V
//////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
//////	VBPP_ramp_down(3, 0.0, 0.05);
//////	wait.delay_10_us(5);
////
////	//BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
////	VBPP_ramp_up(0.0, 5.0, 0.2);	// vstart, vstop, vstep	
////	
////	//Vpin clock 3 pulses (10us positive) to enter write mode	
////	Force_Vpin_Pulses_nTimes(3);	
////
////	D_dvi->set_voltage(D_ch, 40.0, VOLT_50_RANGE); // DVI_11_0 // //be able to see AF links properly
////	wait.delay_10_us(50);
////
////	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
////	VBPP_ramp_up(5.0, 5.5, 50e-3);		
////	VBPP_ramp_down(5.5, 5, 50e-3);	
////
////	//Drain stays at 0V so BPP signal will be cleaner
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);
////	wait.delay_10_us(20);
////
////	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
////	VBPP_ramp_down(5, gVBPP_M_Init-200e-3, 50e-3);	
////	wait.delay_10_us(50);
////
////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////	
////	wait.delay_10_us(30);
////
////	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
//////	BPP_ovi->set_voltage(BPP_ch, 4.2, RANGE_10_V); // OVI_1_0 //
//////	wait.delay_10_us(50);
//////	BPP_ovi->set_voltage(BPP_ch, 5.2, RANGE_10_V); // OVI_1_0 //
//////	wait.delay_10_us(30);
////
////	if		(ObsMode_xx == gObserve_Mode_Xcontrol_sec)	num_pulses_Vpin = 0;
////	else if	(ObsMode_xx == gObserve_Mode_Xlisten)		num_pulses_Vpin = 1;
////	else if (ObsMode_xx == gObserve_Mode_XVTurnOn)		num_pulses_Vpin = 2;
////	else if (ObsMode_xx == gObserve_Mode_XRestart)		num_pulses_Vpin = 3;
////	else if (ObsMode_xx == gObserve_Mode_rcv)			num_pulses_Vpin = 4;
////	else if (ObsMode_xx == gObserve_Mode_Pause)			num_pulses_Vpin = 5;
////	else if (ObsMode_xx == gObserve_Mode_DSDS)			num_pulses_Vpin = 6;
////	else if (ObsMode_xx == gObserve_Mode_OT)			num_pulses_Vpin = 7;
////	else if (ObsMode_xx == gObserve_Mode_LatchOff)		num_pulses_Vpin = 8;
////	else if (ObsMode_xx == gObserve_Mode_Xoc)			num_pulses_Vpin = 9;
////	else if (ObsMode_xx == gObserve_Mode_DZwindow)		num_pulses_Vpin = 10;
////	else if (ObsMode_xx == gObserve_Mode_XZfQ)			num_pulses_Vpin = 11;
////	else if (ObsMode_xx == gObserve_Mode_Xtest2)		num_pulses_Vpin = 12;
////	else if (ObsMode_xx == gObserve_Mode_iplus)			num_pulses_Vpin = 13;
////	else												num_pulses_Vpin = 0;
////
////	for(i=0; i<num_pulses_Vpin; i++)
////	{
////		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start,AF_Vpin_Clk_pulse_stop);
////		wait.delay_10_us(5);	
////	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_BypassWL_TM5(int ILIM_Select) 
{
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Rev B silicon implemented new test mode to bypass wait and listen.
	// To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	// on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	// be used to bypass wait and listen time when applicable.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	// Drain (0V/3mA)
	////D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
	////D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
	////wait.delay_10_us(20);

	////// BPP set 0V
	////BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	////wait.delay_10_us(5);

	////// BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	////VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep

	////// Vpin clock 5 pulses (10us positive) to enter write mode
	////Force_Vpin_Pulses_5_Times(5.0, 0.0);	
	////wait.delay_10_us(5);
	////D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0. Be able to see AF links properly //
	////wait.delay_10_us(10);

	////// BPP ramp from 5V -> 5.5V -> 5V with 50mV step
	////VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);

	////// Drain stays at 0V so BPP signal will be cleaner
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	////wait.delay_10_us(10);

	////VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	

	////// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	////if (ILIM_Select == ILIM_NORM)
	////	wait.delay_10_us(3); // 1.0uF, ILIM, 30us
	////else if(ILIM_Select == ILIM_INCR)
	////	wait.delay_10_us(150); // 10uF, ILIM+1, 1.2ms

	////// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	////BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
	////wait.delay_10_us(20);

	////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
	////
	////wait.delay_10_us(10);

	////// Drain set to 5V for switching
	////D_dvi->set_voltage(D_ch, 5.0, VOLT_50_RANGE); // DVI_11_0 //
	////wait.delay_10_us(10);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_BypassWL_TM5_New(int ILIM_Select) 
{
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Rev B silicon implemented new test mode to bypass wait and listen.
	// To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	// on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	// be used to bypass wait and listen time when applicable.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	// Drain (0V/3mA)
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
////	wait.delay_10_us(20);
////
////	// BPP set 0V
////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
////	wait.delay_10_us(5);
////
////	// BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
////	VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep
////
////	// Vpin clock 5 pulses (10us positive) to enter write mode
////	Force_Vpin_Pulses_5_Times(5.0, 0.0);	
////	wait.delay_10_us(5);
////	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0. Be able to see AF links properly //
////	wait.delay_10_us(10);
////
////	// BPP ramp from 5V -> 5.5V -> 5V with 50mV step
////	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
////
////	// Drain stays at 0V so BPP signal will be cleaner
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////	wait.delay_10_us(10);
////
////	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
////
////	// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
////	if (ILIM_Select == ILIM_NORM)
////		wait.delay_10_us(3); // 1.0uF, ILIM, 30us
////	else if(ILIM_Select == ILIM_INCR)
////		wait.delay_10_us(150); // 10uF, ILIM+1, 1.2ms
////
////	// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
////	wait.delay_10_us(20);
////
//////	BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
//////	VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
////	
//////	wait.delay_10_us(10);
////wait.delay_10_us(40);
////
////	// Drain set to 5V for switching
////	D_dvi->set_voltage(D_ch, 5.0, VOLT_50_RANGE); // DVI_11_0 //
////	wait.delay_10_us(10);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_BypassWL_TM5_SoftStart(int ILIM_Select) 
{
	/******************************************************************************************************
	Rev B silicon implemented new test mode to bypass wait and listen.
	To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	be used to bypass wait and listen time when applicable.
	*******************************************************************************************************/
	Pulse pulse;
////	float PedestalVoltage = 0;
////	float InductorVoltage = 0;
////
////	//Drain (0V/3mA)
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
////	wait.delay_10_us(20);
////
////	//BPP set 0V
////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
////	wait.delay_10_us(5);
////
////	//BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
////	VBPP_ramp_up(0.0, 5.0, 0.2);	// vstart, vstop, vstep	
////	//Vpin clock 5 pulses (10us positive) to enter write mode
////	Force_Vpin_Pulses_5_Times(5.0, 0.0);	
////	wait.delay_10_us(5);
////	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0. Be able to see AF links properly //
////	wait.delay_10_us(10);
////
////	// BPP ramp from 5V -> 5.5V -> 5V with 50mV step
////	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
////
////	// Drain stays at 0V so BPP signal will be cleaner
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////	wait.delay_10_us(10);
////
////	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
////
////	// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
////	if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
////	else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms
////
////	// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
////	wait.delay_10_us(20);
////
////	// Connect Inductor to Drain
////	Open_relay(K3); // Drain to RL pullup
////
////	Close_relay(KIM1); // Connect Vind to CT2+ to CT2-
////
////	Close_relay(K9); // Connect CT2- to Drain
////
////	Close_relay(K1); // Connect Iped to CT2+ to CT2-
////
////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
////	{
////		Close_relay(KIM3); // ILIM Pedestal Use resistor Rpd2
////	}
////	else
////		Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1
////
////	// Open K12.  Reconect OVI to Vpin. //
////	Open_relay(K12);
////	VPIN_ovi->connect(1);
////	wait.delay_10_us(300);
////
////	// Setup pedestal and inductor voltage to be sure getting full frequency //
////	if (!strnicmp(Part_ID_LimitSet, "INN3365", 7))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 46;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3375", 7))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 46;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7))
////	{
////		PedestalVoltage = 45;
////		InductorVoltage = 40;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3376", 7))
////	{
////		PedestalVoltage = 45;
////		InductorVoltage = 40;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3367", 7))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 42;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3377", 7))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 42;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "SC1750", 6))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 42;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "INN3368", 7))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 50;
////	}
////	if (!strnicmp(Part_ID_LimitSet, "SC1738", 6))
////	{
////		PedestalVoltage = 50;
////		InductorVoltage = 50;
////	}
////
////	// Setup Pedestal
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////	D_dvi->set_voltage(D_ch, PedestalVoltage, VOLT_50_RANGE); // DVI_11_0
////
////	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
////	wait.delay_10_us(50);
////
////	// Connect PVI //
////	PV3_Connect_Drain_and_DriveON(InductorVoltage); // Drive Voltage
////
//////wait.delay_10_us(300);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_BypassWL_TM5_18kHz(int ILIM_Select) 
{
	/******************************************************************************************************
	Rev B silicon implemented new test mode to bypass wait and listen.
	To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	be used to bypass wait and listen time when applicable.
	*******************************************************************************************************/
	Pulse pulse;
////	float PedestalVoltage = 0;
////	float InductorVoltage = 0;
////
////	//Drain (0V/3mA)
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
////	wait.delay_10_us(20);
////
////	//BPP set 0V
////	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
////	wait.delay_10_us(5);
////
////	//BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
////	VBPP_ramp_up(0.0, 5.0, 0.2);	// vstart, vstop, vstep	
////	//Vpin clock 5 pulses (10us positive) to enter write mode
////	Force_Vpin_Pulses_5_Times(5.0, 0.0);	
////	wait.delay_10_us(5);
////	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0. Be able to see AF links properly //
////	wait.delay_10_us(10);
////
////	// BPP ramp from 5V -> 5.5V -> 5V with 50mV step
////	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
////
////	// Drain stays at 0V so BPP signal will be cleaner
////	D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
////	wait.delay_10_us(10);
////
////	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
////
////	// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
////	if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
////	else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms
////
////	// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
////	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
////	wait.delay_10_us(20);
////
////	// Connect Inductor to Drain
////	Open_relay(K3); // Drain to RL pullup
////
////	Close_relay(KIM1); // Connect Vind to CT2+ to CT2-
////
////	Close_relay(K9); // Connect CT2- to Drain
////
////	Close_relay(K1); // Connect Iped to CT2+ to CT2-
////
//////	if (!strnicmp(Part_ID_LimitSet, "INN3366", 7) || !strnicmp(Part_ID_LimitSet, "INN3376", 7))
//////	{
//////		Close_relay(KIM3); // ILIM Pedestal Use resistor Rpd2
//////	}
//////	else
////		Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1
////
////	// Open K12.  Reconect OVI to Vpin. //
////	Open_relay(K12);
////	VPIN_ovi->connect(1);
////	wait.delay_10_us(300);
////
////	// Setup Pedestal
////	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
////	D_dvi->set_voltage(D_ch, g_Vpedestal, VOLT_50_RANGE); // DVI_11_0
////
////	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
////	wait.delay_10_us(50);
////
////	// Connect PVI //
////	PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage
////
//////wait.delay_10_us(300);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_BypassWL_TM5_Partial(int ILIM_Select) 
{
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Rev B silicon implemented new test mode to bypass wait and listen.
	// To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	// on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	// be used to bypass wait and listen time when applicable.
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Pulse pulse;

	//////Drain (0V/3mA)
	////D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
	////D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0	
	////wait.delay_10_us(20);

	//////BPP set 0V
	////BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	////wait.delay_10_us(5);

	//////BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	////VBPP_ramp_up(0.0, 5.0, 0.2);	// vstart, vstop, vstep	
	//////Vpin clock 5 pulses (10us positive) to enter write mode
	////Force_Vpin_Pulses_5_Times(5.0, 0.0);	
	////wait.delay_10_us(5);
	////D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE); // DVI_11_0. Be able to see AF links properly //
	////wait.delay_10_us(10);

	////// BPP ramp from 5V -> 5.5V -> 5V with 50mV step
	////VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);

	////// Drain stays at 0V so BPP signal will be cleaner
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); // DVI_11_0
	////wait.delay_10_us(10);

	////VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	

	////// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	////if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
	////else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms

	////// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	////BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V); // OVI_1_0 //
	////wait.delay_10_us(20);

	////// Connect Inductor to Drain
	//////Open_relay(K3); // Drain to RL pullup

	//////Close_relay(KIM1); // Connect Vind to CT2+ to CT2-

	//////Close_relay(K9); // Connect CT2- to Drain

	//////Close_relay(K1); // Connect Iped to CT2+ to CT2-
	//////Open_relay(KIM3); // ILIM Pedestal Use resistor Rpd1

	////// Open K12.  Reconect OVI to Vpin. //
	////Open_relay(K12);
	////VPIN_ovi->connect(1);
	////wait.delay_10_us(300);


	// Setup Pedestal
	//D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	//D_dvi->set_voltage(D_ch, g_Vpedestal, VOLT_50_RANGE); // DVI_11_0

	//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
	//wait.delay_10_us(50);

	// Connect PVI //
	//PV3_Connect_Drain_and_DriveON(gVind_RM); // Drive Voltage

//wait.delay_10_us(300);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Up_Primary_Normal_Mode(int ILIM_PU_Select) 
{
	//////Drain (>15V read anti-fuses)
	////D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);		
	////D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE);	// DVI_11_0	
	////wait.delay_10_us(300);

	//////Vpin setup
	////if (gIOV)
	////{
	////	//Vpin current to control switching or not (Below iOV+)
	////	VPIN_ovi->set_voltage(VPIN_ch, 6.0, RANGE_10_V);  
	////	VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);	
	////}
	////else
	////{
	////	//Vpin set to 0V before PU (Low Jitter for ILIM_NORM if Primary in control)
	////	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);  
	////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	////}

	//////BPP set 0V
	////BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	////BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V);	// OVI_1_0
	////wait.delay_10_us(5);

	////VBPP_ramp_up(0.0, gVBPP_PV_final, 0.2);	// vstart, vstop, vstep	
	////wait.delay_10_us(20);

	////VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	////
	//////Determine what ILIM PowerUp mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	////if (ILIM_PU_Select == ILIM_NORM)
	////	wait.delay_10_us(3); // 1.0 uF, (ILIM), 30us
	////else if(ILIM_PU_Select == ILIM_INCR)
	////	wait.delay_10_us(150); // 10uF, (ILIM+1), 1.2ms

	////VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.2, 0.1);	// vstart, vstop, vstep	
	////wait.delay_10_us(50);

	////BPP_ovi->set_current(BPP_ch, 2e-3, RANGE_30_MA);
	////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_final, 10e-3);
	////
	////wait.delay_10_us(50);
	////D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_NM, VOLT_10_RANGE); // DVI_11_0	
	////wait.delay_10_us(20);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void PV3_CHARGE_ON(int Vrange)
{
	float PV3_Charge = 0;
	
	pv3_4->normal_comp();
	pv3_4->set_voltage(0, Vrange);
	pv3_4->set_current(0, RANGE_10_A);
	pv3_4->set_meas_mode(PV3_CHARGE_S);	
	pv3_4->drive_off();
	pv3_4->charge_on();
	PV3_Charge = pv3_4->measure();
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void PV3_Check_Charge(int Vrange)
{
	float PV3_Charge = 0;
	int	  lcnt		 = 0;
	float Vcharge_th = 0;
	float iCharge	 = 0;

	if(Vrange == RANGE_3_V)
		Vcharge_th = 2.5;
	else
		Vcharge_th = 60;
	while ((PV3_Charge < Vcharge_th) && (lcnt < 2000)) // 60V is enough	
	{
		delay(1);
		lcnt++;
		PV3_Charge = pv3_4->measure();
		if(PV3_Charge > Vcharge_th)
		{
			pv3_4->set_meas_mode(PV3_MEASURE_CURRENT);
			delay(1);
			iCharge = pv3_4->measure();
		}
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void PV3_Connect_Drain_and_DriveON(float Vdrive)
{
	float Vpv3_meas	 = 0;
	int	  lcnt		 = 0;
	Pulse pulse;

	//	connect PV3 to drain ILIM
	pv3_4->close_switch(PV3_LOW_FORCE_2);
	pv3_4->close_switch(PV3_LOW_SENSE_2);
	pv3_4->close_switch(PV3_HIGH_FORCE_1);
	pv3_4->close_switch(PV3_HIGH_SENSE_1);
	wait.delay_10_us(200);

	pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
	pv3_4->set_current(10.0, RANGE_10_A);			// Time=1e3*7e-3*(Vcap-(userV+5V))/userI; max C*U/I = 369mS
	//pv3_4->set_current(0.3, RANGE_10_A);			// Time=1e3*7e-3*(Vcap-(userV+5V))/userI; max C*U/I = 369mS
	
	pv3_4->set_voltage(Vdrive, RANGE_100_V);
	wait.delay_10_us(20);

	// turn on PV3
	pv3_4->drive_on(); 

	Vpv3_meas = pv3_4->measure();
	lcnt = 0;
	while ( Vpv3_meas < Vdrive*0.98 && lcnt < 100 )	
	{
		lcnt++;
		Vpv3_meas = pv3_4->measure();
		wait.delay_10_us(100);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Observe_Vpin_Internal_Signals()
{
	// Description: Also new in Inno4 is a way to bring out some internal logic signals to be observed on the VPIN.  
	// The way this mode is entered is by ending either Write or Program Mode.  We do this by bringing the BP voltage 
	// below UV- (4.5V) and then bringing it back above UV+(5.1V).  The chip goes into normal operation at this point, 
	// but VPIN continues to serve as a clock input and at the same time is being driven by a current sink 
	// controlled by the observation signal. //

	// Declare Variables //
	////int i = 0;
	////float vVpin[16] = {0};
	////float iVpin[16] = {0};

	////// Drain stays at 0V so BPP signal will be cleaner

	////// BPP set 4.5V for 100us and 5.1V to bring chip back to normal operation
	////BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-0.3, RANGE_10_V); // OVI_1_0 //
	////wait.delay_10_us(10);
	//////BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init+0.2, RANGE_10_V); // OVI_1_0 //
	////BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V); // OVI_1_0 //
	////wait.delay_10_us(10);
	////VPIN_ovi->connect(VPIN_ch);

	////// Setup to connect 5kohm between Vpin and DDD
	////Open_relay(K16); // 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
	////Open_relay(K12); // Vpin (UV) to DDD-7-1
	////Close_relay(KC5C); //Vpin to 5kohm to OVI-1-1
	////delay(4);

	////// Vpin continues to serve as clock input and being drive by current sink controlled by observed signal.
	////// note: if Vpin continue negative edge clocking after the 15th address, it will go back to addr 0 and start over.
	////for(i=0; i<16; i++)
	////{
	////	VPIN_ovi->set_voltage(VPIN_ch, 5.0, RANGE_10_V); // OVI_1_1 //
	////	VPIN_ovi->set_current(VPIN_ch, 1.0e-3, RANGE_30_MA); // OVI_1_1 //
	////	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_VOLTAGE, RANGE_5_V); // OVI_1_1 //
	////	wait.delay_10_us(5);
	////	vVpin[i] = VPIN_ovi->measure_average(5);

	////	// Require disconnecting from Vpin for clean digitial signal from DDD
	////	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT); // OVI_1_1 //
	////	wait.delay_10_us(5);
	////	iVpin[i] = VPIN_ovi->measure_average(5);
	////	VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V); // OVI_1_1 //
	////	wait.delay_10_us(10);
	////	if(iVpin[i] < 0)	
	////		gVpin_Internal_Signal[i]=1;
	////	else				
	////		gVpin_Internal_Signal[i]=0;
	////}
	////VPIN_ovi->disconnect(VPIN_ch);

	////// Disconnect //
	////Open_relay(K16); // 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
	////Open_relay(KC5C); // Vpin to 5kohm to OVI-1-1
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Skip_Wait_and_Listen()
{
	//Before calling this function, Primary is already "ON" and Secondary is already "ON"
	//This function is purely created to skip the "Wait and Listen" time also known as "tWL" ~85ms

	//If Primary power-up by itself, it will go through tWL first and then switch for ~85ms and do ARST for ~2second
	//We do not want to have tWL added to test time everytime we do a power-up.  To avoid tWL, secondary to have 
	//trick primary thinking that secondary is already in control by supplying 3 FW negative pulses so Primary will
	//give up control and bypass tWL.

	//Setup FW to connect to DDD
	////Open_relay(K18);  //disconnect FW from dvi-11-1
	////Close_relay(K21); //FW to DDD (once DDD connected, it will then be set to DDD's vLow)
	////delay(5);

	////ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//Vpin set to vHigh

	////// Secondary send 3 negative FW pulses to cause Primary to see request so Primary will be switching
	////Force_Neg_Pulses_FW_DDD(5, -0.5);
	////wait.delay_10_us(10);  //more than 30us quiet time on FW signal

	////D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	////wait.delay_10_us(5);
	////
	////FB_ovi->set_voltage(FB_ch, gCVtgt_15pct_Higher, 		VOLT_5_RANGE);	// OVI_1_2
	////wait.delay_10_us(40);

	////Connect_InvSyn_IM(Low_Vd_Input);		
	////Open_relay(K21);		// FW		to	DDD
	////wait.delay_10_us(10);
	////D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
	////wait.delay_10_us(140);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_IOVp_Binary(float *iOVp, float LowerLimit, float UpperLimit)
{
	//IOV+ binary search to find threshold where switching stops
	//Notes:
	//	- Device will stop switching immediately if goes above IOV+
	//	- Going from non-switching to switching requires minimum 100us tOV to see device start switching.
	//	- iHys_OV is ~10uA
	//	- Going from IOV- to IUV+ will not change switching status.  Device will stay switching
	//	- Going from IUV+ to below IUV- will require a wait time of tUV ~35ms to see device go from switching to OFF
	//	- iHys_UV is ~5uA
	//	- Going from IUV- to above IUV+ also requires ~100us min to see device go from non-switch to switch.

////	float	ifrc_hi		=0,
////			ifrc_lo		=0,
////			i_mid		=0,
////			ifrc		=0,
////			iHys		=0,
////			istep		=0,
////			tmeas		=0,
////			tmeas_th	=0,
////			t_hi		=0,
////			t_lo		=0;
////
////	float VcurrMeas = 0;
////
////	int		switching_status	=0,
////			lcnt				=0,
////			i					=0;
////
////
////	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
////
////	//ifrc_hi		= 150e-6;
////	//ifrc_lo		= 75e-6;
////	ifrc_hi		= UpperLimit;
////	ifrc_lo		= LowerLimit;
////	iHys		= 30e-6;
////	istep		= 0.1e-6;
////	tmeas_th	= 10e-6;	//use 10us Period threshold to determine switching or not.
////	t_hi		= 80e-6;
////	t_lo		= 2e-6;
////	//iHys		= 15e-6;
//////	t_hi		= 60e-6;
//////	t_lo		= 10e-6;
////
////	tmu_6->arm(); 
////	wait.delay_10_us(10);
////	tmeas = tmu_6->read(100e-6); //expect to see device switching after power-up with 80uA iVpin
////	if(tmeas < 10e-6)
////	{
////		*iOVp = -999e-6;
////		switching_status = 0;
////		return;
////	}
////
////	VPIN_ovi->set_current(VPIN_ch, ifrc_hi, RANGE_300_UA); //expect stop switching
////	wait.delay_10_us(15);
////	tmu_6->arm(); 
////	wait.delay_10_us(10);
////	tmeas = tmu_6->read(100e-6); 
////	if(tmeas > t_lo && tmeas < t_hi)
////	{
////		*iOVp = 999e-6;
////		switching_status = 1;
////		return;
////	}
////
////	delay(10); // What is this delay? Maybe remove for test time reduction //
////
////	switching_status = 0;
////	while ( ((ifrc_hi-ifrc_lo) > 0.125e-6) && (lcnt < 20) )
////	{
////		i_mid = (ifrc_hi+ifrc_lo)/2;	
////
////		if(switching_status == 0)	//Only require if previous status is OFF
////		{
////			//Bring device back to switching with subtraction to Hysteresis
////			VPIN_ovi->set_current(VPIN_ch, i_mid-iHys, RANGE_300_UA);	
////			wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw
////			if(gTrim_Loff_AR_P_Trimops)
////			{
////				VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
////				wait.delay_10_us(10);
////				VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
////				wait.delay_10_us(50);
////				//delay(1);
////			}
////		}
////		//Now set the current in between New High and New Low
////		VPIN_ovi->set_current(VPIN_ch, i_mid, RANGE_300_UA);	
////		wait.delay_10_us(15);
////		tmu_6->arm();						
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read(100e-6);
////
////		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
////		{
////			ifrc_hi = i_mid;
////			switching_status = 0;
////		}
////		else
////		{
////			ifrc_lo = i_mid;
////			switching_status = 1;
////		}
////			
////		lcnt++;
////	}
////
////
////	//Fine Tune in 10 steps of 100nA
////	//Bring device back to switching with subtraction to Hysteresis
////	VPIN_ovi->set_current(VPIN_ch, i_mid-iHys, RANGE_300_UA);	
////	wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw
////	if(gTrim_Loff_AR_P_Trimops)
////	{
////		VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
////		wait.delay_10_us(10);
////		VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
////		wait.delay_10_us(50);
////		//delay(1);
////	}
////
////	//Ramp up from "i_mid-iHys" to 2uA below "i_mid"
////	ifrc	= i_mid - iHys;
////	istep	= 0.5e-6;
////	while(ifrc < (i_mid-2e-6))
////	{
////		VPIN_ovi->set_current(VPIN_ch, ifrc, RANGE_300_UA);	
////		wait.delay_10_us(5);
////		ifrc += istep;
////	}
////	//Now set the current in between New High and New Low
////	ifrc = i_mid - 1e-6;
////	istep	= 0.1e-6;
////	for(i=1; i<40; i++)
////	{
////		ifrc = (i_mid - 1e-6) + i*istep;
////		VPIN_ovi->set_current(VPIN_ch, ifrc, RANGE_300_UA);	
////		wait.delay_10_us(10);
////		if(gLoadBoardRev > 24)
////		{
////			VcurrMeas = VPIN_ovi->measure_average(25);
////		}
////		tmu_6->arm();						
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read(100e-6);
////		if (tmeas < t_lo || tmeas > t_hi) //TRUE if device is not switching
////			break;
////	}
////	*iOVp = ifrc;	
////	if(gLoadBoardRev > 24)
////	{
////		*iOVp = VcurrMeas;
////	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void search_IOVp_Binary_TurretCB(float *iOVp)
{
////	//IOV+ binary search to find threshold where switching stops
////	//Notes:
////	//	- Device will stop switching immediately if goes above IOV+
////	//	- Going from non-switching to switching requires minimum 100us tOV to see device start switching.
////	//	- iHys_OV is ~10uA
////	//	- Going from IOV- to IUV+ will not change switching status.  Device will stay switching
////	//	- Going from IUV+ to below IUV- will require a wait time of tUV ~35ms to see device go from switching to OFF
////	//	- iHys_UV is ~5uA
////	//	- Going from IUV- to above IUV+ also requires ~100us min to see device go from non-switch to switch.
////
////	float	ifrc_hi		=0,
////			ifrc_lo		=0,
////			i_mid		=0,
////			ifrc		=0,
////			iHys		=0,
////			istep		=0,
////			tmeas		=0,
////			tmeas_th	=0,
////			t_hi		=0,
////			t_lo		=0,
////			j           =0;
////
////
////	int		switching_status	=0,
////			lcnt				=0,
////			i					=0;
////
////
////	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
////
////	ifrc_hi		= 150e-6;
////	ifrc_lo		= 75e-6;
////	iHys		= 30e-6;
////	istep		= 0.1e-6;
////	tmeas_th	= 10e-6;	//use 10us Period threshold to determine switching or not.
////	t_hi		= 80e-6;
////	t_lo		= 2e-6;
////	//iHys		= 15e-6;
//////	t_hi		= 60e-6;
//////	t_lo		= 10e-6;
////
////	tmu_6->arm(); 
////	wait.delay_10_us(10);
////	tmeas = tmu_6->read(100e-6); //expect to see device switching after power-up with 80uA iVpin
////	if(tmeas < 10e-6)
////	{
////		*iOVp = -999e-6;
////		switching_status = 0;
////		return;
////	}
////
////	VPIN_ovi->set_current(VPIN_ch, ifrc_hi,		RANGE_300_UA);	//expect stop switching
////	wait.delay_10_us(30);
////	tmu_6->arm(); 
////	wait.delay_10_us(10);
////	tmeas = tmu_6->read(100e-6); 
////	if(tmeas > t_lo && tmeas < t_hi)
////	{
////		*iOVp = 999e-6;
////		switching_status = 1;
////		return;
////	}
////
////	delay(10); //WTF is this delay?  Why do we need it for iOV final only??
////
////	switching_status = 0;
////	while ( ((ifrc_hi-ifrc_lo) > 0.125e-6) && (lcnt < 20) )
////	{
////		i_mid = (ifrc_hi+ifrc_lo)/2;	
////
////		j = 0;
////		while(j < i_mid)
////		{
////			VPIN_ovi->set_current(VPIN_ch, j,		RANGE_300_UA);	
////			j = j + 0.5e-6;
////		}
////		//Now set the current in between New High and New Low
////		VPIN_ovi->set_current(VPIN_ch, i_mid,		RANGE_300_UA);	
////		wait.delay_10_us(15);
////		tmu_6->arm();						
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read(100e-6);
////
////		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
////		{
////			ifrc_hi = i_mid;
////			switching_status = 0;
////		}
////		else
////		{
////			ifrc_lo = i_mid;
////			switching_status = 1;
////		}
////			
////		lcnt++;
////	}
////
////
////	//Fine Tune in 10 steps of 100nA
////	//Bring device back to switching with subtraction to Hysteresis
////	VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
////	wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw
////
////	//Ramp up from "i_mid-iHys" to 2uA below "i_mid"
////	ifrc	= i_mid - iHys;
////	istep	= 0.5e-6;
////	while(ifrc < (i_mid-2e-6))
////	{
////		VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
////		wait.delay_10_us(5);
////		ifrc += istep;
////	}
////	//Now set the current in between New High and New Low
////	//VPIN_ovi->set_current(VPIN_ch, i_mid - 2e-6,		RANGE_300_UA);
////	//wait.delay_10_us(5);
////	//VPIN_ovi->set_current(VPIN_ch, i_mid - 1e-6,		RANGE_300_UA);
////	//wait.delay_10_us(5);
////	ifrc = i_mid - 1e-6;
////	istep	= 0.1e-6;
////	for(i=1; i<40; i++)
////	{
////		ifrc = (i_mid - 1e-6) + i*istep;
////		VPIN_ovi->set_current(VPIN_ch, ifrc,		RANGE_300_UA);	
////		wait.delay_10_us(10);
////		tmu_6->arm();						
////		wait.delay_10_us(10);
////		tmeas = tmu_6->read(100e-6);
////		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
////			break;
////	}
////
////	*iOVp = ifrc;	
////	wait.delay_10_us(20);

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Open_All_Relays()
{
	////////Open All Relays //
	//////Open_relay(K1);
	//////Open_relay(K2);
	//////Open_relay(K3);
	//////Open_relay(K4);
	//////Open_relay(K5);
	//////Open_relay(K6);
	//////Open_relay(K7);
	//////Open_relay(K8);
	//////Open_relay(K9);
	//////Open_relay(K10);
	//////Open_relay(K11);
	//////Open_relay(K12);
	//////Open_relay(K13);
	//////Open_relay(K14);
	//////Open_relay(K15);
	//////Open_relay(K16);
	//////Open_relay(K17);
	//////Open_relay(K18);
	//////Open_relay(K19);
	//////Open_relay(K20);
	//////Open_relay(K21);
	//////Open_relay(K22);
	//////Open_relay(K23);
	//////Open_relay(K24);
	//////Open_relay(K71);
	//////Open_relay(K26);
	//////Open_relay(K27);
	//////Open_relay(KC5C);
	//////Open_relay(KC6C);
	//////Open_relay(KIM1);
	//////Open_relay(KIM2);
	//////Open_relay(KIM3);

	////////tmu_6->open_relay(TMU_HIZ_DUT1);			
	////////tmu_6->open_relay(TMU_HIZ_DUT2);			
	////////tmu_6->open_relay(TMU_HIZ_DUT3);			
	////////tmu_6->open_relay(TMU_HIZ_DUT4);			
	////////tmu_6->open_relay(TMU_CHAN_A_DUT1);			
	////////tmu_6->open_relay(TMU_CHAN_A_DUT2);			
	////////tmu_6->open_relay(TMU_CHAN_B_DUT1);			
	////////tmu_6->open_relay(TMU_CHAN_B_DUT2);			
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Down_Everything()
{
	////D_dvi->set_current(D_ch, 30e-3, 		RANGE_30_MA);	// DVI_11_0
	////D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	////BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	////BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
	//////Vpin
	////ovi_1->connect(OVI_CHANNEL_1);
	////VPIN_ovi->set_current(VPIN_ch, 30e-3,	RANGE_30_MA);
	////VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);

	////ddd_7->ddd_stop_pattern();								// Stop the DDD loop pattern

	////// DDD level //
	////g_DDD_Low = 0.0; // Save current value //
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	////wait.delay_10_us(5);

	////VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);	
	////VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	////FB_ovi->set_current(FB_ch, 30e-3,		RANGE_30_MA);
	////FB_ovi->set_voltage(FB_ch, 0.0, 		RANGE_2_V);	// OVI_1_2

	////IS_dvi2k->set_current(IS_ch, 0.1,		RANGE_2_A);
	////IS_dvi2k->set_voltage(IS_ch, 0.0,		VOLT_2_RANGE);	// DVI-13-0

	////IS_dvi2k->set_voltage(IS_ch, 0.0,		VOLT_2_RANGE);	// DVI-13-0
	////BPS_dvi->set_current(BPS_ch, 300.0e-3,	RANGE_300_MA);				//NEED TO BE 300mA to pull down to GND faster.
	////BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_1
	////FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	
	////FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1
	////SR_dvi2k->open_relay(BUS_SENSE1);
	////SR_dvi2k->open_relay(BUS_FORCE1);
	////mux_14->open_relay(MUX_3_BUS3);
	////wait.delay_10_us(5);
	////SR_dvi2k->close_relay(CONN_FORCE1);
	////SR_dvi2k->close_relay(CONN_SENSE1);
	////SR_dvi2k->set_current(SR_ch, 0.1,		RANGE_2_A);
	////SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);
	////wait.delay_10_us(5);

	//////IS
	////mux_14->open_relay(MUX_2_GND);

	//////BUF Clamp
	////ovi_1->set_current(OVI_CHANNEL_3, 30e-3, RANGE_30_MA);
	////ovi_1->set_voltage(OVI_CHANNEL_3, 0.0,	 RANGE_2_V);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Power_Down_Everything_Except_Buf_Clamp()
{
	////D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0
	////D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	////BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	////BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 
	////ovi_1->connect(OVI_CHANNEL_1);
	////VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	////VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
	////ddd_7->ddd_stop_pattern();

	////// DDD level //
	////g_DDD_Low = 0.0; // Save current value //
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
	////wait.delay_10_us(g_DDDwait);
	////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	////wait.delay_10_us(5);
	////VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA);	
	////VO_dvi->set_voltage(VO_ch, 0.0, VOLT_5_RANGE); // DVI_9_0
	////FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA);
	////FB_ovi->set_voltage(FB_ch, 0.0, RANGE_2_V); // OVI_1_2
	////IS_dvi2k->set_current(IS_ch, 0.1, RANGE_2_A);
	////IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI-13-0
	////BPS_dvi->set_current(BPS_ch, 300.0e-3, RANGE_300_MA); // NEED TO BE 300mA to pull down to GND faster.
	////BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); // DVI_9_1
	////FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA);	
	////FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE); // DVI11-1
	////SR_dvi2k->open_relay(BUS_SENSE1);
	////SR_dvi2k->open_relay(BUS_FORCE1);
	////mux_14->open_relay(MUX_3_BUS3);
	////wait.delay_10_us(5);
	////SR_dvi2k->close_relay(CONN_FORCE1);
	////SR_dvi2k->close_relay(CONN_SENSE1);
	////SR_dvi2k->set_current(SR_ch, 0.1,		RANGE_2_A);
	////SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
	////wait.delay_10_us(5);

	////// IS
	////mux_14->open_relay(MUX_2_GND);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void VBPP_Negative_Cycle()
{
//	BPP_ovi->set_current(BPP_ch, 3e-3,		RANGE_3_MA);
//	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
//	wait.delay_10_us(5);
//	BPP_ovi->set_voltage(BPP_ch, -1.0, 		RANGE_10_V);	// OVI_1_0 
//	delay(1);	
//	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
//	wait.delay_10_us(10);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void Write_Byte(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN)
{
	// RegisterName = name of the register we are writing to. //
	// DataHex = the data we are writing, in either hex or decimal format. //
	// DataBinaryArray = the data we are writing, in binary format, stored in DataBinaryArray[] array. //
	// HEXorBIN = indicates whether we are writing with hex or binary format.  Possible values are HEX or BIN. //

	// Declare Variables //
	////int Reg_Address_start = 0;
	////int Reg_Address_stop = 0;
	////int Data_Byte_start = 0;
	////int Data_Byte_stop = 0;
	////int i = 0;
	////
	////// Load Data to DDD pattern memory. //
	////if (HEXorBIN == HEX) // Convert Hex data into binary. //
	////{
	////	Convert_Decimal_To_Binary(DataHex, g_binary_array);  // Convert DataHex into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
	////}
	////if (HEXorBIN == BIN) // Load array g_binary_array[], for loading into DDD pattern memory. //
	////{
	////	for (i=0;i<8;i++)
	////	{
	////		g_binary_array[i] = DataBinaryArray[i];
	////	}
	////}	
	////Load_8_Bit_Pattern(g_binary_array, Data_Byte_start, Data_Byte_stop ); // Load 8 bit pattern to DDD. //

	////// Get DDD start and stop for register address. //
	////if (RegisterName == g_FWPK_reg)
	////{
	////	Reg_Address_start = g_FWPK_start;
	////	Reg_Address_stop = g_FWPK_stop;
	////}
	////if (RegisterName == g_VBEN)
	////{
	////	Reg_Address_start = g_VBEN_start;
	////	Reg_Address_stop = g_VBEN_stop;
	////}
	////if (RegisterName == g_MINLD)
	////{
	////	Reg_Address_start = g_MINLD_start;
	////	Reg_Address_stop = g_MINLD_stop;
	////}
	////if (RegisterName == g_VDIS)
	////{
	////	Reg_Address_start = g_VDIS_start;
	////	Reg_Address_stop = g_VDIS_stop;
	////}
	////if (RegisterName == g_Self_Destruct)
	////{
	////	Reg_Address_start = g_Self_Destruct_start;
	////	Reg_Address_stop = g_Self_Destruct_stop;
	////}
	////if (RegisterName == g_Fast_VI_Command)
	////{
	////	Reg_Address_start = g_Fast_VI_Command_start;
	////	Reg_Address_stop = g_Fast_VI_Command_stop;
	////}
	////if (RegisterName == g_CVO_mode)
	////{
	////	Reg_Address_start = g_CVO_mode_start;
	////	Reg_Address_stop = g_CVO_mode_stop;
	////}
	////if (RegisterName == g_CDC)
	////{
	////	Reg_Address_start = g_CDC_start;
	////	Reg_Address_stop = g_CDC_stop;
	////}
	////if (RegisterName == g_OVL)
	////{
	////	Reg_Address_start = g_OVL_start;
	////	Reg_Address_stop = g_OVL_stop;
	////}
	////if (RegisterName == g_UVL)
	////{
	////	Reg_Address_start = g_UVL_start;
	////	Reg_Address_stop = g_UVL_stop;
	////}
	////if (RegisterName == g_CCSCL)
	////{
	////	Reg_Address_start = g_CCSCL_start;
	////	Reg_Address_stop = g_CCSCL_stop;
	////}
	////if (RegisterName == g_ISSC)
	////{
	////	Reg_Address_start = g_ISSC_start;
	////	Reg_Address_stop = g_ISSC_stop;
	////}
	////if (RegisterName == g_UVL_Timer)
	////{
	////	Reg_Address_start = g_UVL_Timer_start;
	////	Reg_Address_stop = g_UVL_Timer_stop;
	////}
	////if (RegisterName == g_Watchdog_Timer)
	////{
	////	Reg_Address_start = g_Watchdog_Timer_start;
	////	Reg_Address_stop = g_Watchdog_Timer_stop;
	////}
	////if (RegisterName == g_CVO_response)
	////{
	////	Reg_Address_start = g_CVO_response_start;
	////	Reg_Address_stop = g_CVO_response_stop;
	////}
	////if (RegisterName == g_CVO_timer)
	////{
	////	Reg_Address_start = g_CVO_timer_start;
	////	Reg_Address_stop = g_CVO_timer_stop;
	////}
	////if (RegisterName == g_Interrupt_Mask)
	////{
	////	Reg_Address_start = g_Interrupt_Mask_start;
	////	Reg_Address_stop = g_Interrupt_Mask_stop;
	////}
	////if (RegisterName == g_OTP)
	////{
	////	Reg_Address_start = g_OTP_start;
	////	Reg_Address_stop = g_OTP_stop;
	////}
	////if (RegisterName == g_fast_cc_offset)
	////{
	////	Reg_Address_start = g_fast_cc_offset_start;
	////	Reg_Address_stop = g_fast_cc_offset_stop;
	////}
	////if (RegisterName == g_TM_DAC)
	////{
	////	Reg_Address_start = g_TM_DAC_start;
	////	Reg_Address_stop = g_TM_DAC_stop;
	////}
	////if (RegisterName == g_EEP_CMD)
	////{
	////	Reg_Address_start = g_EEP_CMD_start;
	////	Reg_Address_stop = g_EEP_CMD_stop;
	////}

	////// Write byte to slave //
	////ddd_7->ddd_run_pattern(g_StartBit_start, g_StartBit_stop);  // Master sends start bit. One bit. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_SlaveAddress_start, g_SlaveAddress_stop);  // Master sends slave address. 7 bits. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_WriteBit_start, g_WriteBit_stop);  // Master sends bit to indicate a write. One bit. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be written to. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(Data_Byte_start, Data_Byte_stop); // Master sends data byte.  8 bits. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
	////wait.delay_10_us(20);
	////ddd_7->ddd_run_pattern(g_StopBit_start, g_StopBit_stop);  // Master sends stop bit. One bit. //
	////wait.delay_10_us(20);
}

//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Write_Byte_45kHz(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN)
//{
//	// RegisterName = name of the register we are writing to. //
//	// DataHex = the data we are writing, in either hex or decimal format. //
//	// DataBinaryArray = the data we are writing, in binary format, stored in DataBinaryArray[] array. //
//	// HEXorBIN = indicates whether we are writing with hex or binary format.  Possible values are HEX or BIN. //
//
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Data_Byte_start = 0;
//	int Data_Byte_stop = 0;
//	int i = 0;
//	
//	// Load Data to DDD pattern memory. //
//	if (HEXorBIN == HEX) // Convert Hex data into binary. //
//	{
//		Convert_Decimal_To_Binary(DataHex, g_binary_array);  // Convert DataHex into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	}
//	if (HEXorBIN == BIN) // Load array g_binary_array[], for loading into DDD pattern memory. //
//	{
//		for (i=0;i<8;i++)
//		{
//			g_binary_array[i] = DataBinaryArray[i];
//		}
//	}	
//	Load_8_Bit_Pattern_45kHz(g_binary_array, Data_Byte_start, Data_Byte_stop ); // Load 8 bit pattern to DDD. //
//
//	// Get DDD start and stop for register address. //
//	if (RegisterName == g_CDC)
//	{
//		Reg_Address_start = g_CDC_start_45kHz;
//		Reg_Address_stop = g_CDC_stop_45kHz;
//	}
//	
//	// Write byte to slave //
//	ddd_7->ddd_run_pattern(g_StartBit_start_45kHz, g_StartBit_stop_45kHz);  // Master sends start bit. One bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start_45kHz, g_SlaveAddress_stop_45kHz);  // Master sends slave address. 7 bits. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_WriteBit_start_45kHz, g_WriteBit_stop_45kHz);  // Master sends bit to indicate a write. One bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_45kHz, g_SlaveAck_stop_45kHz); // Slave sends acknowlege bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be written to. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_45kHz, g_SlaveAck_stop_45kHz); // Slave sends acknowlege bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(Data_Byte_start, Data_Byte_stop); // Master sends data byte.  8 bits. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_45kHz, g_SlaveAck_stop_45kHz); // Slave sends acknowlege bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_StopBit_start_45kHz, g_StopBit_stop_45kHz);  // Master sends stop bit. One bit. //
//	wait.delay_10_us(20);
//	wait.delay_10_us(20);
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Write_Byte_Part_Pulls_SDA_low(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN)
//{
//	// RegisterName = name of the register we are writing to. //
//	// DataHex = the data we are writing, in either hex or decimal format. //
//	// DataBinaryArray = the data we are writing, in binary format, stored in DataBinaryArray[] array. //
//	// HEXorBIN = indicates whether we are writing with hex or binary format.  Possible values are HEX or BIN. //
//
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Data_Byte_start = 0;
//	int Data_Byte_stop = 0;
//	int i = 0;
//	
//	// Load Data to DDD pattern memory. //
//	if (HEXorBIN == HEX) // Convert Hex data into binary. //
//	{
//		Convert_Decimal_To_Binary(DataHex, g_binary_array);  // Convert DataHex into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	}
//	if (HEXorBIN == BIN) // Load array g_binary_array[], for loading into DDD pattern memory. //
//	{
//		for (i=0;i<8;i++)
//		{
//			g_binary_array[i] = DataBinaryArray[i];
//		}
//	}	
//	Load_8_Bit_Pattern(g_binary_array, Data_Byte_start, Data_Byte_stop ); // Load 8 bit pattern to DDD. //
//
//	// Get DDD start and stop for register address. //
//	if (RegisterName == g_FWPK_reg)
//	{
//		Reg_Address_start = g_FWPK_start;
//		Reg_Address_stop = g_FWPK_stop;
//	}
//	if (RegisterName == g_VBEN)
//	{
//		Reg_Address_start = g_VBEN_start;
//		Reg_Address_stop = g_VBEN_stop;
//	}
//	if (RegisterName == g_MINLD)
//	{
//		Reg_Address_start = g_MINLD_start;
//		Reg_Address_stop = g_MINLD_stop;
//	}
//	if (RegisterName == g_VDIS)
//	{
//		Reg_Address_start = g_VDIS_start;
//		Reg_Address_stop = g_VDIS_stop;
//	}
//	if (RegisterName == g_Self_Destruct)
//	{
//		Reg_Address_start = g_Self_Destruct_start;
//		Reg_Address_stop = g_Self_Destruct_stop;
//	}
//	if (RegisterName == g_Fast_VI_Command)
//	{
//		Reg_Address_start = g_Fast_VI_Command_start;
//		Reg_Address_stop = g_Fast_VI_Command_stop;
//	}
//	if (RegisterName == g_CVO_mode)
//	{
//		Reg_Address_start = g_CVO_mode_start;
//		Reg_Address_stop = g_CVO_mode_stop;
//	}
//	if (RegisterName == g_CDC)
//	{
//		Reg_Address_start = g_CDC_start;
//		Reg_Address_stop = g_CDC_stop;
//	}
//	if (RegisterName == g_OVL)
//	{
//		Reg_Address_start = g_OVL_start;
//		Reg_Address_stop = g_OVL_stop;
//	}
//	if (RegisterName == g_UVL)
//	{
//		Reg_Address_start = g_UVL_start;
//		Reg_Address_stop = g_UVL_stop;
//	}
//	if (RegisterName == g_CCSCL)
//	{
//		Reg_Address_start = g_CCSCL_start;
//		Reg_Address_stop = g_CCSCL_stop;
//	}
//	if (RegisterName == g_ISSC)
//	{
//		Reg_Address_start = g_ISSC_start;
//		Reg_Address_stop = g_ISSC_stop;
//	}
//	if (RegisterName == g_UVL_Timer)
//	{
//		Reg_Address_start = g_UVL_Timer_start;
//		Reg_Address_stop = g_UVL_Timer_stop;
//	}
//	if (RegisterName == g_Watchdog_Timer)
//	{
//		Reg_Address_start = g_Watchdog_Timer_start;
//		Reg_Address_stop = g_Watchdog_Timer_stop;
//	}
//	if (RegisterName == g_CVO_response)
//	{
//		Reg_Address_start = g_CVO_response_start;
//		Reg_Address_stop = g_CVO_response_stop;
//	}
//	if (RegisterName == g_CVO_timer)
//	{
//		Reg_Address_start = g_CVO_timer_start;
//		Reg_Address_stop = g_CVO_timer_stop;
//	}
//	if (RegisterName == g_Interrupt_Mask)
//	{
//		Reg_Address_start = g_Interrupt_Mask_start;
//		Reg_Address_stop = g_Interrupt_Mask_stop;
//	}
//	if (RegisterName == g_OTP)
//	{
//		Reg_Address_start = g_OTP_start;
//		Reg_Address_stop = g_OTP_stop;
//	}
//	if (RegisterName == g_fast_cc_offset)
//	{
//		Reg_Address_start = g_fast_cc_offset_start;
//		Reg_Address_stop = g_fast_cc_offset_stop;
//	}
//	if (RegisterName == g_TM_DAC)
//	{
//		Reg_Address_start = g_TM_DAC_start;
//		Reg_Address_stop = g_TM_DAC_stop;
//	}
//	if (RegisterName == g_EEP_CMD)
//	{
//		Reg_Address_start = g_EEP_CMD_start;
//		Reg_Address_stop = g_EEP_CMD_stop;
//	}
//
//	// Write byte to slave //
//	ddd_7->ddd_run_pattern(g_StartBit_start, g_StartBit_stop);  // Master sends start bit. One bit. //
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start, g_SlaveAddress_stop);  // Master sends slave address. 7 bits. //
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_WriteBit_start, g_WriteBit_stop);  // Master sends bit to indicate a write. One bit. //
//	wait.delay_10_us(20);
//	ddd_7->ddd_run_pattern(g_SDA_hiz_SCL_low_start, g_SDA_hiz_SCL_low_stop);  // Let SDA float to allow part to pull SDA down.  Keep SCL low. //
//	wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be written to. //
//	//wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(Data_Byte_start, Data_Byte_stop); // Master sends data byte.  8 bits. //
//	//wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(20);
//	//ddd_7->ddd_run_pattern(g_StopBit_start, g_StopBit_stop);  // Master sends stop bit. One bit. //
//	//wait.delay_10_us(20);
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void DSM_Write_Byte(int RegisterName, float RegisterData)
//{
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Found_Name_Data = 0;
//
//	// Get DSM start and stop address. //
//	if (RegisterName == g_FWPK_reg)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_FWPK_reg_0x00_start_DSM; Reg_Address_stop = g_FWPK_reg_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_FWPK_reg_0x01_start_DSM; Reg_Address_stop = g_FWPK_reg_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_VBEN)
//	{
//		if (RegisterData == 0x80) {Reg_Address_start = g_VBEN_0x80_start_DSM; Reg_Address_stop = g_VBEN_0x80_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x83) {Reg_Address_start = g_VBEN_0x83_start_DSM; Reg_Address_stop = g_VBEN_0x83_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_MINLD)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_MINLD_0x00_start_DSM; Reg_Address_stop = g_MINLD_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_MINLD_0x01_start_DSM; Reg_Address_stop = g_MINLD_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_VDIS)
//	{
//		if (RegisterData == 131) {Reg_Address_start = g_VDIS_131_start_DSM; Reg_Address_stop = g_VDIS_131_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x83) {Reg_Address_start = g_VDIS_0x83_start_DSM; Reg_Address_stop = g_VDIS_0x83_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x8C) {Reg_Address_start = g_VDIS_0x8C_start_DSM; Reg_Address_stop = g_VDIS_0x8C_stop_DSM; Found_Name_Data = 1;}
//	}
//	//if (RegisterName == g_Self_Destruct)
//	//{
//	//	
//	//}
//	if (RegisterName == g_Fast_VI_Command)
//	{
//		if (RegisterData == 0x01) {Reg_Address_start = g_Fast_VI_Command_0x01_start_DSM; Reg_Address_stop = g_Fast_VI_Command_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_CVO_mode)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_CVO_mode_0x00_start_DSM; Reg_Address_stop = g_CVO_mode_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_CVO_mode_0x01_start_DSM; Reg_Address_stop = g_CVO_mode_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_CDC)
//	{
//		if (RegisterData == 0) {Reg_Address_start = g_CDC_0_start_DSM; Reg_Address_stop = g_CDC_0_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1) {Reg_Address_start = g_CDC_1_start_DSM; Reg_Address_stop = g_CDC_1_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 2) {Reg_Address_start = g_CDC_2_start_DSM; Reg_Address_stop = g_CDC_2_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 4) {Reg_Address_start = g_CDC_4_start_DSM; Reg_Address_stop = g_CDC_4_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 8) {Reg_Address_start = g_CDC_8_start_DSM; Reg_Address_stop = g_CDC_8_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 11) {Reg_Address_start = g_CDC_11_start_DSM; Reg_Address_stop = g_CDC_11_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 12) {Reg_Address_start = g_CDC_12_start_DSM; Reg_Address_stop = g_CDC_12_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_OVL)
//	{
//		if (RegisterData == 0x01) {Reg_Address_start = g_OVL_0x01_start_DSM; Reg_Address_stop = g_OVL_0x01_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x02) {Reg_Address_start = g_OVL_0x02_start_DSM; Reg_Address_stop = g_OVL_0x02_stop_DSM; Found_Name_Data = 1;}
//	}
//	//if (RegisterName == g_UVL)
//	//{
//	//	
//	//}
//	if (RegisterName == g_CCSCL)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_CCSCL_0x00_start_DSM; Reg_Address_stop = g_CCSCL_0x00_stop_DSM; Found_Name_Data = 1;}
//	}
//	//if (RegisterName == g_ISSC)
//	//{
//	//	
//	//}
//	if (RegisterName == g_UVL_Timer)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_UVL_Timer_0x00_start_DSM; Reg_Address_stop = g_UVL_Timer_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_UVL_Timer_0x01_start_DSM; Reg_Address_stop = g_UVL_Timer_0x01_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x02) {Reg_Address_start = g_UVL_Timer_0x02_start_DSM; Reg_Address_stop = g_UVL_Timer_0x02_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x03) {Reg_Address_start = g_UVL_Timer_0x03_start_DSM; Reg_Address_stop = g_UVL_Timer_0x03_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_Watchdog_Timer)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_Watchdog_Timer_0x00_start_DSM; Reg_Address_stop = g_Watchdog_Timer_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_Watchdog_Timer_0x01_start_DSM; Reg_Address_stop = g_Watchdog_Timer_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	//if (RegisterName == g_CVO_response)
//	//{
//	//	
//	//}
//	//if (RegisterName == g_CVO_timer)
//	//{
//	//	
//	//}
//	if (RegisterName == g_Interrupt_Mask)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_Interrupt_Mask_0x00_start_DSM; Reg_Address_stop = g_Interrupt_Mask_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_Interrupt_Mask_0x01_start_DSM; Reg_Address_stop = g_Interrupt_Mask_0x01_stop_DSM; Found_Name_Data = 1;}
//	}
//	//if (RegisterName == g_OTP)
//	//{
//	//	
//	//}
//	if (RegisterName == g_fast_cc_offset)
//	{
//		if (RegisterData == 32) {Reg_Address_start = g_fast_cc_offset_32_start_DSM; Reg_Address_stop = g_fast_cc_offset_32_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x80) {Reg_Address_start = g_fast_cc_offset_0x80_start_DSM; Reg_Address_stop = g_fast_cc_offset_0x80_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_TM_DAC)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_TM_DAC_0x00_start_DSM; Reg_Address_stop = g_TM_DAC_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x40) {Reg_Address_start = g_TM_DAC_0x40_start_DSM; Reg_Address_stop = g_TM_DAC_0x40_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x80) {Reg_Address_start = g_TM_DAC_0x80_start_DSM; Reg_Address_stop = g_TM_DAC_0x80_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_EEP_CMD)
//	{
//		if (RegisterData == 0x00) {Reg_Address_start = g_EEP_CMD_0x00_start_DSM; Reg_Address_stop = g_EEP_CMD_0x00_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x01) {Reg_Address_start = g_EEP_CMD_0x01_start_DSM; Reg_Address_stop = g_EEP_CMD_0x01_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x03) {Reg_Address_start = g_EEP_CMD_0x03_start_DSM; Reg_Address_stop = g_EEP_CMD_0x03_stop_DSM; Found_Name_Data = 1;}
//	}
//
//	// Run pattern //
//	DSM_run_pattern(DSM_CONTEXT, Reg_Address_start, Reg_Address_stop);
//
//	// Error check //
//	if (Found_Name_Data == 0)
//	{
//		g_Error_Flag = -231;
//		MessageBox(NULL, "The register name and/or data were not found in DSM_Write_Byte function.", "Error", MB_OK|MB_TOPMOST);
//	}
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Write_Word(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN)
//{
//	// RegisterName = name of the register we are writing to. //
//	// DataHex = the data we are writing, in either hex or decimal format. //
//	// DataBinaryArray = the data we are writing, in binary format, stored in DataBinaryArray[] array. //
//	// HEXorBIN = indicates whether we are writing with hex or binary format.  Possible values are HEX or BIN. //
//
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Data_Byte_Hi_start = 0;
//	int Data_Byte_Hi_stop = 0;
//	int Data_Byte_Lo_start = 0;
//	int Data_Byte_Lo_stop = 0;
//	int i = 0;
//
//	// Load Data to DDD pattern memory. //
//	if (HEXorBIN == HEX) // Convert Hex data into binary. //
//	{
//		Convert_Decimal_To_Binary(DataHex, g_binary_array);  // Convert DataHex into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	}
//	if (HEXorBIN == BIN) // Load array g_binary_array[], for loading into DDD pattern memory. //
//	{
//		for (i=0;i<16;i++)
//		{
//			g_binary_array[i] = DataBinaryArray[i];
//		}
//	}
//	Load_16_Bit_Pattern(g_binary_array, Data_Byte_Hi_start, Data_Byte_Hi_stop, Data_Byte_Lo_start, Data_Byte_Lo_stop); // Load 16 bit pattern to DDD. //
//		
//	// Get DDD start and stop for register address. //
//	if (RegisterName == g_RDADDR)
//	{
//		Reg_Address_start = g_RDADDR_start;
//		Reg_Address_stop = g_RDADDR_stop;
//	}
//	if (RegisterName == g_CV_reg)
//	{
//		Reg_Address_start = g_CV_start;
//		Reg_Address_stop = g_CV_stop;
//	}
//	if (RegisterName == g_OVA)
//	{
//		Reg_Address_start = g_OVA_start;
//		Reg_Address_stop = g_OVA_stop;
//	}
//	if (RegisterName == g_UVA)
//	{
//		Reg_Address_start = g_UVA_start;
//		Reg_Address_stop = g_UVA_stop;
//	}
//	if (RegisterName == g_CC_reg)
//	{
//		Reg_Address_start = g_CC_start;
//		Reg_Address_stop = g_CC_stop;
//	}
//	if (RegisterName == g_VPK_reg)
//	{
//		Reg_Address_start = g_VPK_start;
//		Reg_Address_stop = g_VPK_stop;
//	}
//	if (RegisterName == g_loop_speed_set1)
//	{
//		Reg_Address_start = g_loop_speed_set1_start;
//		Reg_Address_stop = g_loop_speed_set1_stop;
//	}
//	if (RegisterName == g_loop_speed_set2)
//	{
//		Reg_Address_start = g_loop_speed_set2_start;
//		Reg_Address_stop = g_loop_speed_set2_stop;
//	}
//	if (RegisterName == g_TM_CTRL)
//	{
//		Reg_Address_start = g_TM_CTRL_start;
//		Reg_Address_stop = g_TM_CTRL_stop;
//	}
//	if (RegisterName == g_TM_SEL)
//	{
//		Reg_Address_start = g_TM_SEL_start;
//		Reg_Address_stop = g_TM_SEL_stop;
//	}
//	if (RegisterName == g_TM_ANA)
//	{
//		Reg_Address_start = g_TM_ANA_start;
//		Reg_Address_stop = g_TM_ANA_stop;
//	}
//	if (RegisterName == g_TM_EN)
//	{
//		Reg_Address_start = g_TM_EN_start;
//		Reg_Address_stop = g_TM_EN_stop;
//	}
//	if (RegisterName == g_SREG0)
//	{
//		Reg_Address_start = g_SREG0_start;
//		Reg_Address_stop = g_SREG0_stop;
//	}
//	if (RegisterName == g_SREG1)
//	{
//		Reg_Address_start = g_SREG1_start;
//		Reg_Address_stop = g_SREG1_stop;
//	}
//	if (RegisterName == g_SREG2)
//	{
//		Reg_Address_start = g_SREG2_start;
//		Reg_Address_stop = g_SREG2_stop;
//	}
//	if (RegisterName == g_SREG3)
//	{
//		Reg_Address_start = g_SREG3_start;
//		Reg_Address_stop = g_SREG3_stop;
//	}
//	if (RegisterName == g_SREG4)
//	{
//		Reg_Address_start = g_SREG4_start;
//		Reg_Address_stop = g_SREG4_stop;
//	}
//	if (RegisterName == g_SREG5)
//	{
//		Reg_Address_start = g_SREG5_start;
//		Reg_Address_stop = g_SREG5_stop;
//	}
//	if (RegisterName == g_SREG6)
//	{
//		Reg_Address_start = g_SREG6_start;
//		Reg_Address_stop = g_SREG6_stop;
//	}
//
//	// Write word to slave //
//	ddd_7->ddd_run_pattern(g_StartBit_start, g_StartBit_stop);  // Master sends start bit. One bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start, g_SlaveAddress_stop);  // Master sends slave address. 7 bits. //
//	wait.delay_10_us(5);
//
//	ddd_7->ddd_run_pattern(g_WriteBit_start, g_WriteBit_stop);  // Master sends bit to indicate a write. One bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be written to. //
//	wait.delay_10_us(5);
//
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(Data_Byte_Lo_start, Data_Byte_Lo_stop); // Master sends the first 8 bits of the 16 bit word, low byte.  8 bits. //
//	wait.delay_10_us(5);
//
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(Data_Byte_Hi_start, Data_Byte_Hi_stop); // Master sends the second 8 bits of the 16 bit word, high byte.  8 bits. //
//	wait.delay_10_us(5);
//
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	wait.delay_10_us(2);
//
//	ddd_7->ddd_run_pattern(g_StopBit_start, g_StopBit_stop);  // Master sends stop bit. One bit. //
//	wait.delay_10_us(2);
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Write_Word_Force_SCL(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN)
//{
//	// This function forces SCL high directly with DDD pin instead of letting is get pulled
//	// by pullup resist. This is to speed up the clocking edge to run at a higher frequency (800kHz). //
//	
//	// RegisterName = name of the register we are writing to. //
//	// DataHex = the data we are writing, in either hex or decimal format. //
//	// DataBinaryArray = the data we are writing, in binary format, stored in DataBinaryArray[] array. //
//	// HEXorBIN = indicates whether we are writing with hex or binary format.  Possible values are HEX or BIN. //
//
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Data_Byte_Hi_start = 0;
//	int Data_Byte_Hi_stop = 0;
//	int Data_Byte_Lo_start = 0;
//	int Data_Byte_Lo_stop = 0;
//	int i = 0;
//
//	// Load Data to DDD pattern memory. //
//	if (HEXorBIN == HEX) // Convert Hex data into binary. //
//	{
//		Convert_Decimal_To_Binary(DataHex, g_binary_array);  // Convert DataHex into binary number stored in an array, g_binary_array[], for loading into DDD pattern memory. //
//	}
//	if (HEXorBIN == BIN) // Load array g_binary_array[], for loading into DDD pattern memory. //
//	{
//		for (i=0;i<16;i++)
//		{
//			g_binary_array[i] = DataBinaryArray[i];
//		}
//	}
//	Load_16_Bit_Pattern_Force_SCL(g_binary_array, Data_Byte_Hi_start, Data_Byte_Hi_stop, Data_Byte_Lo_start, Data_Byte_Lo_stop); // Load 16 bit pattern to DDD. //
//		
//	// Get DDD start and stop for register address. //
////	if (RegisterName == g_RDADDR)
////	{
////		Reg_Address_start = g_RDADDR_start;
////		Reg_Address_stop = g_RDADDR_stop;
////	}
////	if (RegisterName == g_CV_reg)
////	{
////		Reg_Address_start = g_CV_start;
////		Reg_Address_stop = g_CV_stop;
////	}
//
////		if (RegisterName == g_OVA)
////		{
////			Reg_Address_start = g_OVA_start;
////			Reg_Address_stop = g_OVA_stop;
////		}
////		if (RegisterName == g_UVA)
////		{
////			Reg_Address_start = g_UVA_start;
////			Reg_Address_stop = g_UVA_stop;
////		}
////		if (RegisterName == g_CC_reg)
////		{
////			Reg_Address_start = g_CC_start;
////			Reg_Address_stop = g_CC_stop;
////		}
////		if (RegisterName == g_VPK_reg)
////		{
////			Reg_Address_start = g_VPK_start;
////			Reg_Address_stop = g_VPK_stop;
////		}
//	if (RegisterName == g_loop_speed_set1)
//	{
//		Reg_Address_start = g_loop_speed_set1_start;
//		Reg_Address_stop = g_loop_speed_set1_stop;
//	}
//	if (RegisterName == g_loop_speed_set2)
//	{
//		Reg_Address_start = g_loop_speed_set2_start;
//		Reg_Address_stop = g_loop_speed_set2_stop;
//	}
//	if (RegisterName == g_TM_CTRL)
//	{
//		Reg_Address_start = g_TM_CTRL_start_Force_SCL;
//		Reg_Address_stop = g_TM_CTRL_stop_Force_SCL;
//	}
////	if (RegisterName == g_TM_SEL)
////	{
////		Reg_Address_start = g_TM_SEL_start;
////		Reg_Address_stop = g_TM_SEL_stop;
////	}
////	if (RegisterName == g_TM_ANA)
////	{
////		Reg_Address_start = g_TM_ANA_start;
////		Reg_Address_stop = g_TM_ANA_stop;
////	}
//	if (RegisterName == g_TM_EN)
//	{
//		Reg_Address_start = g_TM_EN_start_Force_SCL;
//		Reg_Address_stop = g_TM_EN_stop_Force_SCL;
//	}		
////	if (RegisterName == g_SREG0)
////	{
////		Reg_Address_start = g_SREG0_start;
////		Reg_Address_stop = g_SREG0_stop;
////	}
////	if (RegisterName == g_SREG1)
////	{
////		Reg_Address_start = g_SREG1_start;
////		Reg_Address_stop = g_SREG1_stop;
////	}
////	if (RegisterName == g_SREG2)
////	{
////		Reg_Address_start = g_SREG2_start;
////		Reg_Address_stop = g_SREG2_stop;
////	}
////	if (RegisterName == g_SREG3)
////	{
////		Reg_Address_start = g_SREG3_start;
////		Reg_Address_stop = g_SREG3_stop;
////	}
////	if (RegisterName == g_SREG4)
////	{
////		Reg_Address_start = g_SREG4_start;
////		Reg_Address_stop = g_SREG4_stop;
////	}
////	if (RegisterName == g_SREG5)
////	{
////		Reg_Address_start = g_SREG5_start;
////		Reg_Address_stop = g_SREG5_stop;
////	}
////	if (RegisterName == g_SREG6)
////	{
////		Reg_Address_start = g_SREG6_start;
////		Reg_Address_stop = g_SREG6_stop;
////	}
//
//	// Write word to slave //
//	ddd_7->ddd_run_pattern(g_StartBit_start_Force_SCL, g_StartBit_stop_Force_SCL);  // Master sends start bit. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start_Force_SCL, g_SlaveAddress_stop_Force_SCL);  // Master sends slave address. 7 bits. //
//	//wait.delay_10_us(10);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_WriteBit_start_Force_SCL, g_WriteBit_stop_Force_SCL);  // Master sends bit to indicate a write. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_Force_SCL, g_SlaveAck_stop_Force_SCL); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be written to. //
//	//wait.delay_10_us(15);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_Force_SCL, g_SlaveAck_stop_Force_SCL); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(Data_Byte_Lo_start, Data_Byte_Lo_stop); // Master sends the first 8 bits of the 16 bit word, low byte.  8 bits. //
//	//wait.delay_10_us(15);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_Force_SCL, g_SlaveAck_stop_Force_SCL); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(Data_Byte_Hi_start, Data_Byte_Hi_stop); // Master sends the second 8 bits of the 16 bit word, high byte.  8 bits. //
//	//wait.delay_10_us(15);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start_Force_SCL, g_SlaveAck_stop_Force_SCL); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_StopBit_start_Force_SCL, g_StopBit_stop_Force_SCL);  // Master sends stop bit. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void DSM_Write_Word(int RegisterName, float RegisterData)
//{
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int Found_Name_Data = 0;
//
//	// Get DSM start and stop address. //
//	if (RegisterName == g_RDADDR)
//	{
//		if (RegisterData == g_READ0) {Reg_Address_start = g_RDADDR_READ0_start_DSM; Reg_Address_stop = g_RDADDR_READ0_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ1) {Reg_Address_start = g_RDADDR_READ1_start_DSM; Reg_Address_stop = g_RDADDR_READ1_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ2) {Reg_Address_start = g_RDADDR_READ2_start_DSM; Reg_Address_stop = g_RDADDR_READ2_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ3) {Reg_Address_start = g_RDADDR_READ3_start_DSM; Reg_Address_stop = g_RDADDR_READ3_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ4) {Reg_Address_start = g_RDADDR_READ4_start_DSM; Reg_Address_stop = g_RDADDR_READ4_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ5) {Reg_Address_start = g_RDADDR_READ5_start_DSM; Reg_Address_stop = g_RDADDR_READ5_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ6) {Reg_Address_start = g_RDADDR_READ6_start_DSM; Reg_Address_stop = g_RDADDR_READ6_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ7) {Reg_Address_start = g_RDADDR_READ7_start_DSM; Reg_Address_stop = g_RDADDR_READ7_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ8) {Reg_Address_start = g_RDADDR_READ8_start_DSM; Reg_Address_stop = g_RDADDR_READ8_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ9) {Reg_Address_start = g_RDADDR_READ9_start_DSM; Reg_Address_stop = g_RDADDR_READ9_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ10) {Reg_Address_start = g_RDADDR_READ10_start_DSM; Reg_Address_stop = g_RDADDR_READ10_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ11) {Reg_Address_start = g_RDADDR_READ11_start_DSM; Reg_Address_stop = g_RDADDR_READ11_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ12) {Reg_Address_start = g_RDADDR_READ12_start_DSM; Reg_Address_stop = g_RDADDR_READ12_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ13) {Reg_Address_start = g_RDADDR_READ13_start_DSM; Reg_Address_stop = g_RDADDR_READ13_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ14) {Reg_Address_start = g_RDADDR_READ14_start_DSM; Reg_Address_stop = g_RDADDR_READ14_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ56) {Reg_Address_start = g_RDADDR_READ56_start_DSM; Reg_Address_stop = g_RDADDR_READ56_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ57) {Reg_Address_start = g_RDADDR_READ57_start_DSM; Reg_Address_stop = g_RDADDR_READ57_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ58) {Reg_Address_start = g_RDADDR_READ58_start_DSM; Reg_Address_stop = g_RDADDR_READ58_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ59) {Reg_Address_start = g_RDADDR_READ59_start_DSM; Reg_Address_stop = g_RDADDR_READ59_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ60) {Reg_Address_start = g_RDADDR_READ60_start_DSM; Reg_Address_stop = g_RDADDR_READ60_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ61) {Reg_Address_start = g_RDADDR_READ61_start_DSM; Reg_Address_stop = g_RDADDR_READ61_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_READ62) {Reg_Address_start = g_RDADDR_READ62_start_DSM; Reg_Address_stop = g_RDADDR_READ62_stop_DSM; Found_Name_Data = 1;}		
//	}
//	if (RegisterName == g_CV_reg)
//	{
//		if (RegisterData == 556) {Reg_Address_start = g_CV_reg_556_start_DSM; Reg_Address_stop = g_CV_reg_556_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 756) {Reg_Address_start = g_CV_reg_756_start_DSM; Reg_Address_stop = g_CV_reg_756_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1032) {Reg_Address_start = g_CV_reg_1032_start_DSM; Reg_Address_stop = g_CV_reg_1032_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1052) {Reg_Address_start = g_CV_reg_1052_start_DSM; Reg_Address_stop = g_CV_reg_1052_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1112) {Reg_Address_start = g_CV_reg_1112_start_DSM; Reg_Address_stop = g_CV_reg_1112_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1220) {Reg_Address_start = g_CV_reg_1220_start_DSM; Reg_Address_stop = g_CV_reg_1220_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1796) {Reg_Address_start = g_CV_reg_1796_start_DSM; Reg_Address_stop = g_CV_reg_1796_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 1896) {Reg_Address_start = g_CV_reg_1896_start_DSM; Reg_Address_stop = g_CV_reg_1896_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 2124) {Reg_Address_start = g_CV_reg_2124_start_DSM; Reg_Address_stop = g_CV_reg_2124_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 4148) {Reg_Address_start = g_CV_reg_4148_start_DSM; Reg_Address_stop = g_CV_reg_4148_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33552) {Reg_Address_start = g_CV_reg_33552_start_DSM; Reg_Address_stop = g_CV_reg_33552_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33636) {Reg_Address_start = g_CV_reg_33636_start_DSM; Reg_Address_stop = g_CV_reg_33636_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33648) {Reg_Address_start = g_CV_reg_33648_start_DSM; Reg_Address_stop = g_CV_reg_33648_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33651) {Reg_Address_start = g_CV_reg_33651_start_DSM; Reg_Address_stop = g_CV_reg_33651_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33772) {Reg_Address_start = g_CV_reg_33772_start_DSM; Reg_Address_stop = g_CV_reg_33772_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33778) {Reg_Address_start = g_CV_reg_33778_start_DSM; Reg_Address_stop = g_CV_reg_33778_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33780) {Reg_Address_start = g_CV_reg_33780_start_DSM; Reg_Address_stop = g_CV_reg_33780_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 33790) {Reg_Address_start = g_CV_reg_33790_start_DSM; Reg_Address_stop = g_CV_reg_33790_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 34196) {Reg_Address_start = g_CV_reg_34196_start_DSM; Reg_Address_stop = g_CV_reg_34196_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 34336) {Reg_Address_start = g_CV_reg_34336_start_DSM; Reg_Address_stop = g_CV_reg_34336_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 34356) {Reg_Address_start = g_CV_reg_34356_start_DSM; Reg_Address_stop = g_CV_reg_34356_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 36816) {Reg_Address_start = g_CV_reg_36816_start_DSM; Reg_Address_stop = g_CV_reg_36816_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 37600) {Reg_Address_start = g_CV_reg_37600_start_DSM; Reg_Address_stop = g_CV_reg_37600_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_OVA)
//	{
//		if (RegisterData == 278) {Reg_Address_start = g_OVA_278_start_DSM; Reg_Address_stop = g_OVA_278_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 368) {Reg_Address_start = g_OVA_368_start_DSM; Reg_Address_stop = g_OVA_368_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 378) {Reg_Address_start = g_OVA_378_start_DSM; Reg_Address_stop = g_OVA_378_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 456) {Reg_Address_start = g_OVA_456_start_DSM; Reg_Address_stop = g_OVA_456_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32830) {Reg_Address_start = g_OVA_32830_start_DSM; Reg_Address_stop = g_OVA_32830_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32868) {Reg_Address_start = g_OVA_32868_start_DSM; Reg_Address_stop = g_OVA_32868_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32959) {Reg_Address_start = g_OVA_32959_start_DSM; Reg_Address_stop = g_OVA_32959_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_UVA)
//	{
//		if (RegisterData == 318) {Reg_Address_start = g_UVA_318_start_DSM; Reg_Address_stop = g_UVA_318_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 368) {Reg_Address_start = g_UVA_368_start_DSM; Reg_Address_stop = g_UVA_368_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 396) {Reg_Address_start = g_UVA_396_start_DSM; Reg_Address_stop = g_UVA_396_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32838) {Reg_Address_start = g_UVA_32838_start_DSM; Reg_Address_stop = g_UVA_32838_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32926) {Reg_Address_start = g_UVA_32926_start_DSM; Reg_Address_stop = g_UVA_32926_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32976) {Reg_Address_start = g_UVA_32976_start_DSM; Reg_Address_stop = g_UVA_32976_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_CC_reg)
//	{
//		if (RegisterData == 384) {Reg_Address_start = g_CC_reg_384_start_DSM; Reg_Address_stop = g_CC_reg_384_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32941) {Reg_Address_start = g_CC_reg_32941_start_DSM; Reg_Address_stop = g_CC_reg_32941_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_VPK_reg)
//	{
//		if (RegisterData == 278) {Reg_Address_start = g_VPK_reg_278_start_DSM; Reg_Address_stop = g_VPK_reg_278_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 363) {Reg_Address_start = g_VPK_reg_363_start_DSM; Reg_Address_stop = g_VPK_reg_363_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 456) {Reg_Address_start = g_VPK_reg_456_start_DSM; Reg_Address_stop = g_VPK_reg_456_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32868) {Reg_Address_start = g_VPK_reg_32868_start_DSM; Reg_Address_stop = g_VPK_reg_32868_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 32949) {Reg_Address_start = g_VPK_reg_32949_start_DSM; Reg_Address_stop = g_VPK_reg_32949_stop_DSM; Found_Name_Data = 1;}
//	}
////	if (RegisterName == g_loop_speed_set1)
////	{
////
////	}
////	if (RegisterName == g_loop_speed_set2)
////	{
////
////	}
//	if (RegisterName == g_TM_CTRL)
//	{
//		if (RegisterData == 0x0000) {Reg_Address_start = g_TM_CTRL_0x0000_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0000_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0001) {Reg_Address_start = g_TM_CTRL_0x0001_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0001_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0004) {Reg_Address_start = g_TM_CTRL_0x0004_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0004_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0020) {Reg_Address_start = g_TM_CTRL_0x0020_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0020_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0820) {Reg_Address_start = g_TM_CTRL_0x0820_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0820_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0828) {Reg_Address_start = g_TM_CTRL_0x0828_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0828_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0A22) {Reg_Address_start = g_TM_CTRL_0x0A22_start_DSM; Reg_Address_stop = g_TM_CTRL_0x0A22_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x1800) {Reg_Address_start = g_TM_CTRL_0x1800_start_DSM; Reg_Address_stop = g_TM_CTRL_0x1800_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_ScanMode_Enter) {Reg_Address_start = g_TM_CTRL_ScanMode_Enter_start_DSM; Reg_Address_stop = g_TM_CTRL_ScanMode_Enter_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_TM_SEL)
//	{
//		if (RegisterData == 26) {Reg_Address_start = g_TM_SEL_26_start_DSM; Reg_Address_stop = g_TM_SEL_26_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 29) {Reg_Address_start = g_TM_SEL_29_start_DSM; Reg_Address_stop = g_TM_SEL_29_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0000) {Reg_Address_start = g_TM_SEL_0x0000_start_DSM; Reg_Address_stop = g_TM_SEL_0x0000_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0001) {Reg_Address_start = g_TM_SEL_0x0001_start_DSM; Reg_Address_stop = g_TM_SEL_0x0001_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0004) {Reg_Address_start = g_TM_SEL_0x0004_start_DSM; Reg_Address_stop = g_TM_SEL_0x0004_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0006) {Reg_Address_start = g_TM_SEL_0x0006_start_DSM; Reg_Address_stop = g_TM_SEL_0x0006_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0008) {Reg_Address_start = g_TM_SEL_0x0008_start_DSM; Reg_Address_stop = g_TM_SEL_0x0008_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x000A) {Reg_Address_start = g_TM_SEL_0x000A_start_DSM; Reg_Address_stop = g_TM_SEL_0x000A_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0016) {Reg_Address_start = g_TM_SEL_0x0016_start_DSM; Reg_Address_stop = g_TM_SEL_0x0016_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0018) {Reg_Address_start = g_TM_SEL_0x0018_start_DSM; Reg_Address_stop = g_TM_SEL_0x0018_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0020) {Reg_Address_start = g_TM_SEL_0x0020_start_DSM; Reg_Address_stop = g_TM_SEL_0x0020_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0024) {Reg_Address_start = g_TM_SEL_0x0024_start_DSM; Reg_Address_stop = g_TM_SEL_0x0024_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0026) {Reg_Address_start = g_TM_SEL_0x0026_start_DSM; Reg_Address_stop = g_TM_SEL_0x0026_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_TM_ANA)
//	{
//		if (RegisterData == 0x0000) {Reg_Address_start = g_TM_ANA_0x0000_start_DSM; Reg_Address_stop = g_TM_ANA_0x0000_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0120) {Reg_Address_start = g_TM_ANA_0x0120_start_DSM; Reg_Address_stop = g_TM_ANA_0x0120_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0130) {Reg_Address_start = g_TM_ANA_0x0130_start_DSM; Reg_Address_stop = g_TM_ANA_0x0130_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0134) {Reg_Address_start = g_TM_ANA_0x0134_start_DSM; Reg_Address_stop = g_TM_ANA_0x0134_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0138) {Reg_Address_start = g_TM_ANA_0x0138_start_DSM; Reg_Address_stop = g_TM_ANA_0x0138_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x013C) {Reg_Address_start = g_TM_ANA_0x013C_start_DSM; Reg_Address_stop = g_TM_ANA_0x013C_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == 0x0934) {Reg_Address_start = g_TM_ANA_0x0934_start_DSM; Reg_Address_stop = g_TM_ANA_0x0934_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_SR_Enable) {Reg_Address_start = g_TM_ANA_SR_Enable_start_DSM; Reg_Address_stop = g_TM_ANA_SR_Enable_stop_DSM; Found_Name_Data = 1;}
//	}
//	if (RegisterName == g_TM_EN)
//	{
//		if (RegisterData == g_TestMode_Password) {Reg_Address_start = g_TM_EN_TestMode_Password_start_DSM; Reg_Address_stop = g_TM_EN_TestMode_Password_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_TestMode_Enter) {Reg_Address_start = g_TM_EN_TestMode_Enter_start_DSM; Reg_Address_stop = g_TM_EN_TestMode_Enter_stop_DSM; Found_Name_Data = 1;}
//		if (RegisterData == g_TestMode_Exit) {Reg_Address_start = g_TM_EN_TestMode_Exit_start_DSM; Reg_Address_stop = g_TM_EN_TestMode_Exit_stop_DSM; Found_Name_Data = 1;}
//	}
////	if (RegisterName == g_SREG0)
////	{
////		
////	}
////	if (RegisterName == g_SREG1)
////	{
////		
////	}
////	if (RegisterName == g_SREG2)
////	{
////		
////	}
////	if (RegisterName == g_SREG3)
////	{
////		
////	}
////	if (RegisterName == g_SREG4)
////	{
////		
////	}
////	if (RegisterName == g_SREG5)
////	{
////		
////	}
////	if (RegisterName == g_SREG6)
////	{
////		
////	}
//
//	// Run pattern //
//	DSM_run_pattern(DSM_CONTEXT, Reg_Address_start, Reg_Address_stop);
//
//	// Error check //
//	if (Found_Name_Data == 0)
//	{
//		g_Error_Flag = -232;
//		MessageBox(NULL, "The register name and/or data were not found in DSM_Write_Word function.", "Error", MB_OK|MB_TOPMOST);
//	}
//}
//
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Read_Word(int RegisterName, int *BitArray)
//{
//	// RegisterName = register to read from. //
//	// BitArray[] = array to store the read. //
//	
//	// Declare Variables //
//	int Reg_Address_start = 0;
//	int Reg_Address_stop = 0;
//	int j=0;
//	int HexValue = 0x0;
//	Pulse pulse;
//		
//	// Get DDD start and stop for register address. //
//	if (RegisterName == g_RDADDR)
//	{
//		Reg_Address_start = g_RDADDR_start;
//		Reg_Address_stop = g_RDADDR_stop;
//	}
//	if (RegisterName == g_READ0)
//	{
//		Reg_Address_start = g_READ0_start;
//		Reg_Address_stop = g_READ0_stop;
//	}
//	if (RegisterName == g_READ1)
//	{
//		Reg_Address_start = g_READ1_start;
//		Reg_Address_stop = g_READ1_stop;
//	}
//	if (RegisterName == g_READ2)
//	{
//		Reg_Address_start = g_READ2_start;
//		Reg_Address_stop = g_READ2_stop;
//	}
//	if (RegisterName == g_READ3)
//	{
//		Reg_Address_start = g_READ3_start;
//		Reg_Address_stop = g_READ3_stop;
//	}
//	if (RegisterName == g_READ4)
//	{
//		Reg_Address_start = g_READ4_start;
//		Reg_Address_stop = g_READ4_stop;
//	}
//	if (RegisterName == g_READ5)
//	{
//		Reg_Address_start = g_READ5_start;
//		Reg_Address_stop = g_READ5_stop;
//	}
//	if (RegisterName == g_READ6)
//	{
//		Reg_Address_start = g_READ6_start;
//		Reg_Address_stop = g_READ6_stop;
//	}
//	if (RegisterName == g_READ7)
//	{
//		Reg_Address_start = g_READ7_start;
//		Reg_Address_stop = g_READ7_stop;
//	}
//	if (RegisterName == g_READ8)
//	{
//		Reg_Address_start = g_READ8_start;
//		Reg_Address_stop = g_READ8_stop;
//	}
//	if (RegisterName == g_READ9)
//	{
//		Reg_Address_start = g_READ9_start;
//		Reg_Address_stop = g_READ9_stop;
//	}
//	if (RegisterName == g_READ10)
//	{
//		Reg_Address_start = g_READ10_start;
//		Reg_Address_stop = g_READ10_stop;
//	}
//	if (RegisterName == g_READ11)
//	{
//		Reg_Address_start = g_READ11_start;
//		Reg_Address_stop = g_READ11_stop;
//	}
//	if (RegisterName == g_READ12)
//	{
//		Reg_Address_start = g_READ12_start;
//		Reg_Address_stop = g_READ12_stop;
//	}
//	if (RegisterName == g_READ13)
//	{
//		Reg_Address_start = g_READ13_start;
//		Reg_Address_stop = g_READ13_stop;
//	}
//	if (RegisterName == g_READ14)
//	{
//		Reg_Address_start = g_READ14_start;
//		Reg_Address_stop = g_READ14_stop;
//	}
//	if (RegisterName == g_READ15)
//	{
//		Reg_Address_start = g_READ15_start;
//		Reg_Address_stop = g_READ15_stop;
//	}
//	if (RegisterName == g_READ16)
//	{
//		Reg_Address_start = g_READ16_start;
//		Reg_Address_stop = g_READ16_stop;
//	}
//	if (RegisterName == g_READ17)
//	{
//		Reg_Address_start = g_READ17_start;
//		Reg_Address_stop = g_READ17_stop;
//	}
//	if (RegisterName == g_READ18)
//	{
//		Reg_Address_start = g_READ18_start;
//		Reg_Address_stop = g_READ18_stop;
//	}
//	if (RegisterName == g_READ19)
//	{
//		Reg_Address_start = g_READ19_start;
//		Reg_Address_stop = g_READ19_stop;
//	}
//	if (RegisterName == g_READ20)
//	{
//		Reg_Address_start = g_READ20_start;
//		Reg_Address_stop = g_READ20_stop;
//	}
//	if (RegisterName == g_READ21)
//	{
//		Reg_Address_start = g_READ21_start;
//		Reg_Address_stop = g_READ21_stop;
//	}
//	if (RegisterName == g_READ22)
//	{
//		Reg_Address_start = g_READ22_start;
//		Reg_Address_stop = g_READ22_stop;
//	}
//	if (RegisterName == g_READ40)
//	{
//		Reg_Address_start = g_READ40_start;
//		Reg_Address_stop = g_READ40_stop;
//	}
//	if (RegisterName == g_READ41)
//	{
//		Reg_Address_start = g_READ41_start;
//		Reg_Address_stop = g_READ41_stop;
//	}
//	if (RegisterName == g_READ42)
//	{
//		Reg_Address_start = g_READ42_start;
//		Reg_Address_stop = g_READ42_stop;
//	}
//	if (RegisterName == g_READ43)
//	{
//		Reg_Address_start = g_READ43_start;
//		Reg_Address_stop = g_READ43_stop;
//	}
//	if (RegisterName == g_READ44)
//	{
//		Reg_Address_start = g_READ44_start;
//		Reg_Address_stop = g_READ44_stop;
//	}
//	if (RegisterName == g_READ45)
//	{
//		Reg_Address_start = g_READ45_start;
//		Reg_Address_stop = g_READ45_stop;
//	}
//	if (RegisterName == g_READ46)
//	{
//		Reg_Address_start = g_READ46_start;
//		Reg_Address_stop = g_READ46_stop;
//	}
//	if (RegisterName == g_READ47)
//	{
//		Reg_Address_start = g_READ47_start;
//		Reg_Address_stop = g_READ47_stop;
//	}
//	if (RegisterName == g_READ56)
//	{
//		Reg_Address_start = g_READ56_start;
//		Reg_Address_stop = g_READ56_stop;
//	}
//	if (RegisterName == g_READ57)
//	{
//		Reg_Address_start = g_READ57_start;
//		Reg_Address_stop = g_READ57_stop;
//	}
//	if (RegisterName == g_READ58)
//	{
//		Reg_Address_start = g_READ58_start;
//		Reg_Address_stop = g_READ58_stop;
//	}
//	if (RegisterName == g_READ59)
//	{
//		Reg_Address_start = g_READ59_start;
//		Reg_Address_stop = g_READ59_stop;
//	}
//	if (RegisterName == g_READ60)
//	{
//		Reg_Address_start = g_READ60_start;
//		Reg_Address_stop = g_READ60_stop;
//	}
//	if (RegisterName == g_READ61)
//	{
//		Reg_Address_start = g_READ61_start;
//		Reg_Address_stop = g_READ61_stop;
//	}
//	if (RegisterName == g_READ62)
//	{
//		Reg_Address_start = g_READ62_start;
//		Reg_Address_stop = g_READ62_stop;
//	}
//
//	// Read word from slave //
//	ddd_7->ddd_run_pattern(g_StartBit_start, g_StartBit_stop);  // Master sends start bit. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start, g_SlaveAddress_stop);  // Master sends slave address. 7 bits. //
//	//wait.delay_10_us(10);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_WriteBit_start, g_WriteBit_stop);  // Master sends bit to indicate a write. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(Reg_Address_start, Reg_Address_stop); // Master sends address of register to be read from. //
//	//wait.delay_10_us(15);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_StartBit_start, g_StartBit_stop);  // Master sends repeated start bit. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAddress_start, g_SlaveAddress_stop); // Master sends slave address. 7 bits. //
//	//wait.delay_10_us(10);
//	wait.delay_10_us(5);
//	ddd_7->ddd_run_pattern(g_ReadBit_start, g_ReadBit_stop); // Master sends bit to indicate a read. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_SlaveAck_start, g_SlaveAck_stop); // Slave sends acknowlege bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_Read_LoByte_start, g_Read_LoByte_stop); // Master reads low byte from slave. //
//	//wait.delay_10_us(40);
//	wait.delay_10_us(10);
//	ddd_7->ddd_run_pattern(g_MasterAck_start, g_MasterAck_stop); // Master sends Ack bit to slave. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_Read_HiByte_start, g_Read_HiByte_stop); // Master reads high byte from slave. //
//	//wait.delay_10_us(40);
//	wait.delay_10_us(10);
//	ddd_7->ddd_run_pattern(g_MasterNack_start, g_MasterNack_stop); // Master sends Nack bit to slave. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//	ddd_7->ddd_run_pattern(g_StopBit_start, g_StopBit_stop);  // Master sends stop bit. One bit. //
//	//wait.delay_10_us(5);
//	wait.delay_10_us(2);
//
//	// Pull read data from DDD memory //
//	// The return value from the ddd_read_pattern function is a 2 digit hexidecimal number 
//	// where each digit represents 4 of the ddd channels. //
//	
//	// Read g_Read_HiByte_Mem[] DDD memory. //
//	for (j=15;j>7;j--)
//	{
//		HexValue = ddd_7->ddd_read_pattern(g_Read_HiByte_Mem[j]+1); // +1 because the DDD always returns data two address values below what is called for in the function. //
//		//ResultVal = ddd_7->ddd_compare_pattern("X1XXXXXX",g_Read_HiByte_Mem[j]); // This function call will also work.  Can use either this or the ddd_read_pattern function. //
//		HexValue = HexValue & 0x40;
//		if (HexValue == 0x00)
//		{
//			BitArray[j] = 0;
//		}
//		if (HexValue == 0x40)
//		{
//			BitArray[j] = 1;
//		}
//	}
//
//	// Read g_Read_LoByte_Mem[] DDD memory. //
//	for (j=7;j>-1;j--)
//	{
//		HexValue = ddd_7->ddd_read_pattern(g_Read_LoByte_Mem[j]+1); // +1 because the DDD always returns data two address values below what is called for in the function. //
//		//ResultVal = ddd_7->ddd_compare_pattern("X1XXXXXX",g_Read_HiByte_Mem[j]); // This function call will also work.  Can use either this or the ddd_read_pattern function. //
//		HexValue = HexValue & 0x40;
//		if (HexValue == 0x00)
//		{
//			BitArray[j] = 0;
//		}
//		if (HexValue == 0x40)
//		{
//			BitArray[j] = 1;
//		}
//	}
//}
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int Get_Inductor_ID()
{
	int i = 0;
	int Inductor_ID = 0;
	int tenThousands = 0;
	int thousands = 0;
	int hundreds = 0;
	int tens = 0;
	int ones = 0;
	TCHAR Inductor_Num[80] = "\0";
	Inductor_Num[2]  =	HardwareList.m_Inductor->m_strName[2];
	Inductor_Num[3]  =	HardwareList.m_Inductor->m_strName[3];
	Inductor_Num[4]  =	HardwareList.m_Inductor->m_strName[4];
	Inductor_Num[5]  =	HardwareList.m_Inductor->m_strName[5];
	Inductor_Num[6]  =	HardwareList.m_Inductor->m_strName[6];
	for(i=2;i<7;i++)
	{
		if(i==2)
		{
			if (Inductor_Num[i] == '1')
				tenThousands = 1;
			if (Inductor_Num[i] == '2')
				tenThousands = 2;
			if (Inductor_Num[i] == '3')
				tenThousands = 3;
			if (Inductor_Num[i] == '4')
				tenThousands = 4;
			if (Inductor_Num[i] == '5')
				tenThousands = 5;
			if (Inductor_Num[i] == '6')
				tenThousands = 6;
			if (Inductor_Num[i] == '7')
				tenThousands = 7;
			if (Inductor_Num[i] == '8')
				tenThousands = 8;
			if (Inductor_Num[i] == '9')
				tenThousands = 9;
		}
		if(i==3)
		{
			if (Inductor_Num[i] == '1')
				thousands = 1;
			if (Inductor_Num[i] == '2')
				thousands = 2;
			if (Inductor_Num[i] == '3')
				thousands = 3;
			if (Inductor_Num[i] == '4')
				thousands = 4;
			if (Inductor_Num[i] == '5')
				thousands = 5;
			if (Inductor_Num[i] == '6')
				thousands = 6;
			if (Inductor_Num[i] == '7')
				thousands = 7;
			if (Inductor_Num[i] == '8')
				thousands = 8;
			if (Inductor_Num[i] == '9')
				thousands = 9;
		}
		if(i==4)
		{
			if (Inductor_Num[i] == '1')
				hundreds = 1;
			if (Inductor_Num[i] == '2')
				hundreds = 2;
			if (Inductor_Num[i] == '3')
				hundreds = 3;
			if (Inductor_Num[i] == '4')
				hundreds = 4;
			if (Inductor_Num[i] == '5')
				hundreds = 5;
			if (Inductor_Num[i] == '6')
				hundreds = 6;
			if (Inductor_Num[i] == '7')
				hundreds = 7;
			if (Inductor_Num[i] == '8')
				hundreds = 8;
			if (Inductor_Num[i] == '9')
				hundreds = 9;
		}
		if(i==5)
		{
			if (Inductor_Num[i] == '1')
				tens = 1;
			if (Inductor_Num[i] == '2')
				tens = 2;
			if (Inductor_Num[i] == '3')
				tens = 3;
			if (Inductor_Num[i] == '4')
				tens = 4;
			if (Inductor_Num[i] == '5')
				tens = 5;
			if (Inductor_Num[i] == '6')
				tens = 6;
			if (Inductor_Num[i] == '7')
				tens = 7;
			if (Inductor_Num[i] == '8')
				tens = 8;
			if (Inductor_Num[i] == '9')
				tens = 9;
		}
		if(i==6)
		{
			if (Inductor_Num[i] == '1')
				ones = 1;
			if (Inductor_Num[i] == '2')
				ones = 2;
			if (Inductor_Num[i] == '3')
				ones = 3;
			if (Inductor_Num[i] == '4')
				ones = 4;
			if (Inductor_Num[i] == '5')
				ones = 5;
			if (Inductor_Num[i] == '6')
				ones = 6;
			if (Inductor_Num[i] == '7')
				ones = 7;
			if (Inductor_Num[i] == '8')
				ones = 8;
			if (Inductor_Num[i] == '9')
				ones = 9;
		}
	}
	Inductor_ID = tenThousands*10000 + thousands*1000 + hundreds*100 + tens*10 + ones;
	return Inductor_ID;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int Get_Loadboard_ID()
{
	int i = 0;
	int Loadboard_ID = 0;
	int tenThousands = 0;
	int thousands = 0;
	int hundreds = 0;
	int tens = 0;
	int ones = 0;
	TCHAR Loadboard_Num[80] = "\0";
	Loadboard_Num[2]  =	HardwareList.m_LoadBoard->m_strName[2];
	Loadboard_Num[3]  =	HardwareList.m_LoadBoard->m_strName[3];
	Loadboard_Num[4]  =	HardwareList.m_LoadBoard->m_strName[4];
	Loadboard_Num[5]  =	HardwareList.m_LoadBoard->m_strName[5];
	Loadboard_Num[6]  =	HardwareList.m_LoadBoard->m_strName[6];
	for(i=2;i<7;i++)
	{
		if(i==2)
		{
			if (Loadboard_Num[i] == '1')
				tenThousands = 1;
			if (Loadboard_Num[i] == '2')
				tenThousands = 2;
			if (Loadboard_Num[i] == '3')
				tenThousands = 3;
			if (Loadboard_Num[i] == '4')
				tenThousands = 4;
			if (Loadboard_Num[i] == '5')
				tenThousands = 5;
			if (Loadboard_Num[i] == '6')
				tenThousands = 6;
			if (Loadboard_Num[i] == '7')
				tenThousands = 7;
			if (Loadboard_Num[i] == '8')
				tenThousands = 8;
			if (Loadboard_Num[i] == '9')
				tenThousands = 9;
		}
		if(i==3)
		{
			if (Loadboard_Num[i] == '1')
				thousands = 1;
			if (Loadboard_Num[i] == '2')
				thousands = 2;
			if (Loadboard_Num[i] == '3')
				thousands = 3;
			if (Loadboard_Num[i] == '4')
				thousands = 4;
			if (Loadboard_Num[i] == '5')
				thousands = 5;
			if (Loadboard_Num[i] == '6')
				thousands = 6;
			if (Loadboard_Num[i] == '7')
				thousands = 7;
			if (Loadboard_Num[i] == '8')
				thousands = 8;
			if (Loadboard_Num[i] == '9')
				thousands = 9;
		}
		if(i==4)
		{
			if (Loadboard_Num[i] == '1')
				hundreds = 1;
			if (Loadboard_Num[i] == '2')
				hundreds = 2;
			if (Loadboard_Num[i] == '3')
				hundreds = 3;
			if (Loadboard_Num[i] == '4')
				hundreds = 4;
			if (Loadboard_Num[i] == '5')
				hundreds = 5;
			if (Loadboard_Num[i] == '6')
				hundreds = 6;
			if (Loadboard_Num[i] == '7')
				hundreds = 7;
			if (Loadboard_Num[i] == '8')
				hundreds = 8;
			if (Loadboard_Num[i] == '9')
				hundreds = 9;
		}
		if(i==5)
		{
			if (Loadboard_Num[i] == '1')
				tens = 1;
			if (Loadboard_Num[i] == '2')
				tens = 2;
			if (Loadboard_Num[i] == '3')
				tens = 3;
			if (Loadboard_Num[i] == '4')
				tens = 4;
			if (Loadboard_Num[i] == '5')
				tens = 5;
			if (Loadboard_Num[i] == '6')
				tens = 6;
			if (Loadboard_Num[i] == '7')
				tens = 7;
			if (Loadboard_Num[i] == '8')
				tens = 8;
			if (Loadboard_Num[i] == '9')
				tens = 9;
		}
		if(i==6)
		{
			if (Loadboard_Num[i] == '1')
				ones = 1;
			if (Loadboard_Num[i] == '2')
				ones = 2;
			if (Loadboard_Num[i] == '3')
				ones = 3;
			if (Loadboard_Num[i] == '4')
				ones = 4;
			if (Loadboard_Num[i] == '5')
				ones = 5;
			if (Loadboard_Num[i] == '6')
				ones = 6;
			if (Loadboard_Num[i] == '7')
				ones = 7;
			if (Loadboard_Num[i] == '8')
				ones = 8;
			if (Loadboard_Num[i] == '9')
				ones = 9;
		}
	}
	Loadboard_ID = tenThousands*10000 + thousands*1000 + hundreds*100 + tens*10 + ones;
	return Loadboard_ID;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int Get_Contactor_ID()
{
	int i = 0;
	int Contactor_ID = 0;
	int tenThousands = 0;
	int thousands = 0;
	int hundreds = 0;
	int tens = 0;
	int ones = 0;
	TCHAR Contactor_Num[80] = "\0";
	Contactor_Num[2]  =	HardwareList.m_HandlerContactor->m_strName[2];
	Contactor_Num[3]  =	HardwareList.m_HandlerContactor->m_strName[3];
	Contactor_Num[4]  =	HardwareList.m_HandlerContactor->m_strName[4];
	Contactor_Num[5]  =	HardwareList.m_HandlerContactor->m_strName[5];
	Contactor_Num[6]  =	HardwareList.m_HandlerContactor->m_strName[6];
	for(i=2;i<7;i++)
	{
		if(i==2)
		{
			if (Contactor_Num[i] == '1')
				tenThousands = 1;
			if (Contactor_Num[i] == '2')
				tenThousands = 2;
			if (Contactor_Num[i] == '3')
				tenThousands = 3;
			if (Contactor_Num[i] == '4')
				tenThousands = 4;
			if (Contactor_Num[i] == '5')
				tenThousands = 5;
			if (Contactor_Num[i] == '6')
				tenThousands = 6;
			if (Contactor_Num[i] == '7')
				tenThousands = 7;
			if (Contactor_Num[i] == '8')
				tenThousands = 8;
			if (Contactor_Num[i] == '9')
				tenThousands = 9;
		}
		if(i==3)
		{
			if (Contactor_Num[i] == '1')
				thousands = 1;
			if (Contactor_Num[i] == '2')
				thousands = 2;
			if (Contactor_Num[i] == '3')
				thousands = 3;
			if (Contactor_Num[i] == '4')
				thousands = 4;
			if (Contactor_Num[i] == '5')
				thousands = 5;
			if (Contactor_Num[i] == '6')
				thousands = 6;
			if (Contactor_Num[i] == '7')
				thousands = 7;
			if (Contactor_Num[i] == '8')
				thousands = 8;
			if (Contactor_Num[i] == '9')
				thousands = 9;
		}
		if(i==4)
		{
			if (Contactor_Num[i] == '1')
				hundreds = 1;
			if (Contactor_Num[i] == '2')
				hundreds = 2;
			if (Contactor_Num[i] == '3')
				hundreds = 3;
			if (Contactor_Num[i] == '4')
				hundreds = 4;
			if (Contactor_Num[i] == '5')
				hundreds = 5;
			if (Contactor_Num[i] == '6')
				hundreds = 6;
			if (Contactor_Num[i] == '7')
				hundreds = 7;
			if (Contactor_Num[i] == '8')
				hundreds = 8;
			if (Contactor_Num[i] == '9')
				hundreds = 9;
		}
		if(i==5)
		{
			if (Contactor_Num[i] == '1')
				tens = 1;
			if (Contactor_Num[i] == '2')
				tens = 2;
			if (Contactor_Num[i] == '3')
				tens = 3;
			if (Contactor_Num[i] == '4')
				tens = 4;
			if (Contactor_Num[i] == '5')
				tens = 5;
			if (Contactor_Num[i] == '6')
				tens = 6;
			if (Contactor_Num[i] == '7')
				tens = 7;
			if (Contactor_Num[i] == '8')
				tens = 8;
			if (Contactor_Num[i] == '9')
				tens = 9;
		}
		if(i==6)
		{
			if (Contactor_Num[i] == '1')
				ones = 1;
			if (Contactor_Num[i] == '2')
				ones = 2;
			if (Contactor_Num[i] == '3')
				ones = 3;
			if (Contactor_Num[i] == '4')
				ones = 4;
			if (Contactor_Num[i] == '5')
				ones = 5;
			if (Contactor_Num[i] == '6')
				ones = 6;
			if (Contactor_Num[i] == '7')
				ones = 7;
			if (Contactor_Num[i] == '8')
				ones = 8;
			if (Contactor_Num[i] == '9')
				ones = 9;
		}
	}
	Contactor_ID = tenThousands*10000 + thousands*1000 + hundreds*100 + tens*10 + ones;
	return Contactor_ID;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void Initialize_Relays()
{
	    int i = 0;
	    ////// This function opens all relays. //
	   //---------------------------------------------------------------------------------------------------------------------------------------------------------
	   //Mux14 controlled relays.
	   //----------------------------------------------------------------------------------------------------------------------------------------------------------
	   mux_14->open_relay(K1_DSM_TB);    //K1_DSM_TB     = MUX_1_1,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA (Vpin) of Primary.
	   mux_14->open_relay(K2_DSM_TB);    //K2_DSM_TB     = MUX_1_2,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA of 2ndary.
	   mux_14->open_relay(K3_DSM_TB);    //K3_DSM_TB     = MUX_1_3,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL (TS) of Primary.
	   mux_14->open_relay(K4_DSM_TB);    //K4_DSM_TB     = MUX_1_4,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL of 2ndary.
	   mux_14->open_relay(K1_DDD_TB);    //K1_DDD_TB     = MUX_2_3,   // On Mux14.  To control relay to connect DDD7_1 to either TS or Integrator on IS pin.
	   mux_14->open_relay(K2_DDD_TB);    //K2_DDD_TB     = MUX_2_4,   // On Mux14.  To control relay to connect DDD7_2 to either IS or UV pin.
	   mux_14->open_relay(K3_DDD_TB);    //K3_DDD_TB     = MUX_3_1,   // On Mux14.  To control relay to connect DDD7_3 to VR pin.
	   mux_14->open_relay(K4_DDD_TB);    //K4_DDD_TB     = MUX_3_2,   // On Mux14.  To control relay to connect DDD7_4 to SDA pin.
	   mux_14->open_relay(K5_DDD_TB);    //K5_DDD_TB     = MUX_3_3,   // On Mux14.  To control relay to connect DDD7_5 to SCL pin or DDD7_5_FW_COMP3 pin.
       mux_14->open_relay(K6_DDD_TB);    //K6_DDD_TB     = MUX_3_4,   // On Mux14.  To control relay to connect DDD7_6 to FB pin or DDD7_6_FW_COMP1 pin.
	   mux_14->open_relay(K7_DDD_TB);    //K7_DDD_TB     = MUX_4_1,   // On Mux14.  To control relay to connect DDD7_7 to FW pin or DDD7_7_FW_COMP2 pin.
	   mux_14->open_relay(K1_TMU_TB);    //K1_TMU_TB     = MUX_4_2,   // On Mux14.  To control relay to connect TMU_HIZ1_D1 or TMU_HIZ1_D2.
	   mux_14->open_relay(K2_TMU_TB);    //K2_TMU_TB     = MUX_4_3,   // On Mux14.  To control relay to connect TMU_HIZ2/TMU_CHB_DUT2 to UV or B pin.	
	   mux_14->open_relay(K3_TMU_TB);    //K3_TMU_TB     = MUX_4_4,   // On Mux14.  To control relay to connect TMU_HIZ3 to HBP pin.	
	   mux_14->open_relay(K4_TMU_TB);    //K4_TMU_TB     = MUX_5_1,   // On Mux14.  To control relay to connect TMU_HIZ3 to VR pin.	
	   mux_14->open_relay(K5_TMU_TB);    //K5_TMU_TB     = MUX_5_2,   // On Mux14.  To control relay to connect TMU_HIZ3 to FW pin.	
	   mux_14->open_relay(K6_TMU_TB);    //K6_TMU_TB     = MUX_5_3,   // On Mux14.  To control relay to connect TMU_HIZ4/TMU_CHB_DUT1 to HSG or TS pin.	
	   mux_14->open_relay(K1_VR_TB);     //K1_VR_TB      = MUX_5_4,   // On Mux14.  To control relay to connect HVS to VR pin.
	   mux_14->open_relay(K1_D_RB);      //K1_D_RB       = MUX_6_1,   // On Mux14.  To control relay to connect DVI_11_0 to Drain or IM_Pedestal.
	   mux_14->open_relay(K2_D_RB);      //K2_D_RB       = MUX_6_2,   // On Mux14.  To control relay to connect DVI_11_0 as Kelvin or NonKelvin to Drain.
	   mux_14->open_relay(K3_D_TB);      //K3_D_TB       = MUX_6_3,   // On Mux14.  To control relay to connect/disconnect DVI_11_0 to Drain.
	   mux_14->open_relay(K4_D_TB);      //K4_D_TB       = MUX_6_4,   // On Mux14.  To control relay to connect/disconnect HVS to Drain.
	   mux_14->open_relay(K5_D_TB );     //K5_D_TB       = MUX_7_1,   // On Mux14.  To control relay to connect/disconnect PVI3 directly or via inductor to Drain
	   mux_14->open_relay(K6_D_TB);      //K6_D_TB       = MUX_7_2,   // On Mux14.  To control relay to connect/disconnect reg Pri SOA or pulse Pri SOA.
	   mux_14->open_relay(K7_D_TB );     //K7_D_TB       = MUX_7_3,   // On Mux14.  To control relay to connect/disconnect Drain to SOA circuit.
	   mux_14->open_relay(K8_K11_D_TB);  //K8_K11_D_TB   = MUX_7_4,   // On Mux14.  To control relay to connect/disconnect Sync circuit to FW.
	   mux_14->open_relay(K9_D_TB);      //K9_D_TB       = MUX_8_1,   // On Mux14.  To control relay to connect/disconnect Drain to Pierson.
	   mux_14->open_relay(K1_IM_TB);      //K1_IM_TB	 = MUX_8_2,   // On Mux14.  To control relay to connect/disconnect IM1
	   mux_14->open_relay(K2_IM_TB);      //K2_IM_TB	 = MUX_8_3,   // On Mux14.  To control relay to connect/disconnect IM2
	   mux_14->open_relay(K3_IM_TB );     //K3_IM_TB	 = MUX_8_4,   // On Mux14.  To control relay to connect/disconnect IM3
	
	   //Mux20 controlled relays.
	   mux_20->open_relay(K1_HVS_LB);     //K1_HVS_LB    = MUX_6_2,   // On Mux20.  To connect HVS_15_POS_F to LB.
       mux_20->open_relay(K2_HVS_LB);     //K2_HVS_LB    = MUX_6_3,   // On Mux20.  To stack   HVS_15_NEG_F on top of HVS_19_POS_F for 900V testing.
       mux_20->open_relay(K1_DDD_LB);     //K1_DDD_LB    = MUX_6_1,   // On Mux20.  To connect DDD7_1 to high speed comparator to generate narrow pulses.
	   mux_20->open_relay(K_GND_ANA_LB);  //K_GND_ANA_LB = MUX_6_4,   // On Mux20.  By default, GND sense is connected to primary ground sense.  K_GND_ANA_LB is to connect to 2ndary GNDS
	   mux_20->open_relay(K1_GNDS_LB);    //K1_GNDS_LB   = MUX_5_1,   // On Mux20.  By default, DVI11_GNDS is connected to primary ground sense. K1_GNDS_LB is to connect to 2ndary GNDS.
	   mux_20->open_relay(K2_GNDS_LB);    //K2_GNDS_LB   = MUX_5_2,   // On Mux20.  By default, DVI9_GNDS is connected to primary ground sense.  K2_GNDS_LB is to connected 2ndary GNDs.                                   
	   mux_20->open_relay(K3_GNDS_LB);    //K3_GNDS_LB   = MUX_5_3,   // On Mux20.  By default, DVI13_GNDS is connected to primary ground sense. K3_GNDS_LB is to connected 2ndary GNDs.                                   
	   mux_20->open_relay(K4_GNDS_LB);    //K4_GNDS_LB   = MUX_5_4,   // On Mux20.  By default, DVI21_GNDS is connected to primary ground sense. K4_GNDS_LB is to connected 2ndary GNDs.                                   
	   mux_20->open_relay(K_OVI3_0_LB);   //K_OVI3_0_LB  = MUX_7_2,   // On Mux20.  To control OVI3_0 connect or disconnect from TS pin.
	   mux_20->open_relay(K_OVI3_1_LB);   //K_OVI3_1_LB  = MUX_7_3,   // On Mux20.  To control OVI3_0 connect to OVI3_1 sense to check Kelvin of OVI3_0 on TS pin.
	   mux_20->open_relay(K_OVI3_3_LB);   //K_OVI3_3_LB  = MUX_7_4,   // On Mux20.  To control OVI3_3 connect/disconnect to Sync ckt on TB.  K_OVI3_3_LB is also used to check Mux_20.
	   mux_20->open_relay(K_OVI3_4_LB );  //K_OVI3_4_LB  = MUX_8_2,   // On Mux20.  To short OVI3_4 Sense to OVI3_5 Sense for Kelvin check.   To short OVI3_6 Sense to OVI3_7 S for Kelvin Check.
	   mux_20->open_relay(K_OVI1_0_LB );  //K_OVI1_0_LB  = MUX_8_3,   // On Mux20.  To short OVI1_1 Sense to OVI1_0 Sense for Kelvin check.   
	   mux_20->open_relay(K5678_DSM_TB);  //K5678_DSM_TB = MUX_4_2,   // On Mux20.  To control relay for Pri + 2ndary parallel scan.   
	   mux_20->open_relay(K10_D_TB);      //K10_D_TB     = MUX_1_1,   // On Mux20.  To control relay for connecting Drain to RDSON BUFF Input.
	   mux_20->open_relay(K12_D_TB );     //K12_D_TB     = MUX_4_1,   // On Mux20.  To control relay for shorting inductor L3 for Pri SOA testing.
	   mux_20->open_relay(K_UV_BUFF_TB);  //K_UV_BUFF_TB = MUX_1_2,   // On Mux20.  To control relay for connecting Rdson buffer to Vpin.
	   mux_20->open_relay(K1_UV_RB);      //K1_UV_RB     = MUX_1_3,   // On Mux20.  To control relay NonKelvin or Kelvin On Vpin.
	   mux_20->open_relay(K2_UV_RB);      //K2_UV_RB     = MUX_1_4,   // On Mux20.  To control relay to select 10K or 600K pullup resistor on Vpin.
	   mux_20->open_relay(K3_UV_TB);      //K3_UV_TB     = MUX_2_1,   // On Mux20.  To control relay to connect/disconnect DVI21 to Vpin.
	   mux_20->open_relay(K1_DigA_TB);    //K1_DigA_TB   = MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	   mux_20->open_relay(K1_IS_BUFF_TB); //K1_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	   mux_20->open_relay(K2_IS_BUFF_TB); //K2_IS_BUFF_TB= MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	   mux_20->open_relay(K2_DigA_TB );   //K2_DigA_TB   = MUX_2_3,   // On Mux20.  To control relay to connect to either FW or IS pin.
	   mux_20->open_relay(K_CHANB_TB);    //K_CHANB_TB   = MUX_2_4,   // On Mux20.  To control relay to connect to either B or HSG pin.
       mux_20->open_relay(K1_BPP_RB);     //K1_BPP_RB    = MUX_3_1,   // On Mux20.  To control relay to connect to BPP to 4.7uF CaP on Riderboard.
       mux_20->open_relay(K1_TS_RB);      //K1_TS_RB     = MUX_3_2,   // On Mux20.  To control relay to select NonKelvin/Kelvin on TS pin.
	   mux_20->open_relay(K2_TS_TB );     //K2_TS_TB     = MUX_3_3,   // On Mux20.  To control relay to connect/disconnect OVI3_0 to TS pin.
	   mux_20->open_relay(K3_TS_IB );     //K3_TS_IB     = MUX_3_4,   // On Mux20.  To control relay to connect/disconnect LT1719 comparator to TS pin.
	
	  
		for(i = 0; i < 8; i++) 
		{
			relays.open_relay_spi(1,i);
			relays.open_relay_spi(2,i);
			relays.open_relay_spi(3,i);
			relays.open_relay_spi(4,i);
			relays.open_relay_spi(5,i);
		}
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void FWrampDown(float Vstart, float Vstop, float Vstep)
{
	///*float FW_volt = 0;
	//FW_volt = Vstart;
	//while(FW_volt > Vstop)
	//{
	//	FW_dvi->set_voltage(FW_ch, FW_volt, VOLT_50_RANGE);
	//	FW_volt -= Vstep;
	//	wait.delay_10_us(20);
	//}
	//FW_dvi->set_voltage(FW_ch, Vstop, VOLT_50_RANGE);*/
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void VOUTrampDown(float Vstart, float Vstop, float Vstep)
{
	////float VOUT_volt = 0;
	////VOUT_volt = Vstart;
	////while(VOUT_volt > Vstop)
	////{
	////	VO_dvi->set_voltage(VO_ch, VOUT_volt, VOLT_20_RANGE); // DVI_9_0
	////	VOUT_volt -= Vstep;
	////	wait.delay_10_us(20);
	////}
	////VO_dvi->set_voltage(VO_ch, Vstop, VOLT_20_RANGE); // DVI_9_0
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void VOUTrampDown_Range10V(float Vstart, float Vstop, float Vstep)
{
	////float VOUT_volt = 0;
	////VOUT_volt = Vstart;
	////while(VOUT_volt > Vstop)
	////{
	////	VO_dvi->set_voltage(VO_ch, VOUT_volt, VOLT_10_RANGE); // DVI_9_0
	////	VOUT_volt -= Vstep;
	////	wait.delay_10_us(20);
	////}
	////VO_dvi->set_voltage(VO_ch, Vstop, VOLT_10_RANGE); // DVI_9_0
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Define_I2C_Registers()
{
	// All resister addresses use odd parity in bit[7]. //
	
	//g_Pri_SlaveAddress = 0x18;    //7 bits only. '0011000' //
	//g_Pri_RDADDR       = 0x00;    //WR_Word.
	//g_Pri_CORE_CTRL0   = 0x10;    //WR_Byte.
	//g_Pri_CORE_CTRL1   = 0x12;    //WR_Byte.
	//g_Pri_CORE_CTRL2   = 0X14;    //WR_Byte.
	//g_Pri_TM_CTRL      = 0x40;    //WR_Byte.
	//g_Pri_SIG_CRTL     = 0x42;    //WR_Byte.
	//g_Pri_ANA_CTRL_0   = 0x44;    //WR_Word.
	//g_Pri_ANA_CTRL_1   = 0X46;    //WR_Word.

	//Secondary Registers.
	g_SlaveAddress_P = 0x1C;       //7 bits only. '0001110w/r'
	g_SlaveAddress_S = 0x14;       //7 bits only. '0001010w/r'
	g_RDADDR       = 0x00;       //WR_Word
	g_CORE_CTRL0   = 0x10;       //WR_Byte
	g_CORE_CTRL1   = 0x12;       //WR_Byte
	g_CORE_CTRL2   = 0x14;       //WR_Byte
	g_TM_CTRL      = 0x40;	     //WR_Byte
	g_SIG_CTRL     = 0x42;       //WR_Byte
	g_ANA_CTRL_0   = 0x44;       //WR_Word
	g_ANA_CTRL_1   = 0x46;       //WR_Word
	g_I2C_CTRL     = 0x48;       //WR_Byte
	g_FAULT_CTRL   = 0x4A;       //WR_Byte
	g_PINSCL_CTRL  = 0x4C;       //WR_Byte
	g_PINSDA_CTRL  = 0x4E;       //WR_Byte
	g_RDPIN_FAULT  = 0x50;       //WR_Byte (add by charles from I2CregisterMap of Primary)
	g_PIN1_CFG     = 0x52;       //WR_Byte
	g_EEP_CMD      = 0x5C;       //WR_Byte
	g_TM_EN        = 0x5E;       //WR_Word
	g_EEP_W_E0     = 0xE0;       //WR_Word
	g_EEP_W_E2     = 0xE2;       //WR_Word
	g_EEP_W_E4     = 0xE4;       //WR_Word
	g_EEP_W_E6     = 0xE6;       //WR_Word
	g_EEP_W_E8     = 0xE8;       //WR_Word
	g_EEP_R_C0     = 0xC0;       //WR_Word
	g_EEP_R_C2     = 0xC2;       //WR_Word
	g_EEP_R_C4     = 0xC4;       //WR_Word
	g_EEP_R_C6     = 0xC6;       //WR_Word
	g_EEP_R_C8     = 0xC8;       //WR_Word
	g_TEST_CTRL1   = 0x60;       //WR_Word
	g_TEST_CTRL2   = 0x62;       //WR_Word
	g_TEST_CTRL3   = 0x64;       //WR_Word
	g_TEST_CTRL4   = 0x66;       //WR_Word

	//ReadBack Registers.
	g_READ00       = 0x00;       //RD_Word
	g_READ02       = 0x02;       //RD_Word
	g_READ04       = 0x04;       //RD_Word
	g_READ06       = 0x06;       //RD_Word
	g_READ08       = 0x08;       //RD_Word
	g_READ0A       = 0x0A;       //RD_Word
	g_READ0C       = 0x0C;       //RD_Word
	g_READ0E       = 0x0E;       //RD_Word
	g_READ10       = 0x10;       //RD_Word
	g_READ12       = 0x12;       //RD_Word
	g_READ14       = 0x14;       //RD_Word
	g_READ16       = 0x16;       //RD_Word
	g_READ40       = 0x40;       //RD_Word
	g_READ42       = 0x42;       //RD_Word
	g_READ44       = 0x44;       //RD_Word
	g_READ46       = 0x46;       //RD_Word
	g_READ48       = 0x48;       //RD_Word
	g_READ4A       = 0x4A;       //RD_Word
	g_READ4C       = 0x4A;       //RD_Word
	g_READ70       = 0x70;       //RD_Word


////INNOPRO Register.
//////////	// Define register names and their addresses. //
//////////	g_SlaveAddress = 0x98; // Without parity:0x18; // 7 bits only. '0011000' //
////////////	g_SlaveAddress = 0x00; // Broadcast address. 7 bits only. '0000000' //
//////////	g_RDADDR = 0x80; // Without parity: 0x00, // WR_Word //
//////////	g_FWPK_reg = 0x02; // WR_Byte //
//////////	g_VBEN = 0x04; // WR_Byte //
//////////	g_MINLD = 0x86; // Without parity: 0x06, // WR_Byte //
//////////	g_VDIS = 0x08; // WR_Byte //
//////////	g_Self_Destruct = 0x8A; // Without parity: 0x0A, // WR_Byte //
//////////	g_Fast_VI_Command = 0x8C; // Without parity: 0x0C, // WR_Byte //
//////////	g_CVO_mode = 0x0E; // WR_Byte, Rev2 silicon //
//////////	g_CV_reg = 0x10; // WR_Word //
//////////	g_OVA = 0x92; // Without parity:0x12, // WR_Word //
//////////	g_UVA = 0x94; // Without parity:0x14, // WR_Word //
//////////	g_CDC = 0x16; // WR_Byte //
//////////	g_CC_reg = 0x98; // Without parity:0x18, // WR_Word //
//////////	g_VPK_reg = 0x1A; // WR_Word //
//////////	g_OVL = 0x1C; // WR_Byte //
//////////	g_UVL = 0x9E; // Without parity:0x1E, // WR_Byte //
//////////	g_CCSCL = 0x20; // WR_Byte //
//////////	g_ISSC = 0xA2; // Without parity:0x22; // WR_Byte //
//////////	g_UVL_Timer = 0xA4; // Without parity: 0x24; // WR_Byte //
//////////	g_Watchdog_Timer = 0x26; // WR_Byte //
//////////	g_CVO_response = 0xA8; // Without parity: 0x28; // WR_Byte, Rev2 silicon //
//////////	g_CVO_timer = 0x2A; // WR_Byte, Rev2 silicon //
//////////	g_Interrupt_Mask = 0x2C; // WR_Byte, Rev2 silicon //
//////////	g_OTP = 0xAE; // Without parity: 0x2E; // WR_Byte, Rev2 silicon //
//////////	g_fast_cc_offset = 0xB0; // Without parity: 0x30; // WR_Byte, RevC silicon //
//////////	g_loop_speed_set1 = 0x32; // Without parity: 0x32; // WR_Word, RevC silicon  //
//////////	g_loop_speed_set2 = 0x34; // Without parity: 0x34; // WR_Word, RevC silicon  //
//////////	g_TM_CTRL = 0xD0; // Without parity: 0x50; // WR_Word //
//////////	g_TM_SEL = 0x52; // WR_Word //
//////////	g_TM_DAC = 0x54; // WR_Byte //
//////////	g_TM_ANA = 0xD6; // Without parity: 0x56; // WR_Word, Rev2 silicon //
//////////	g_EEP_CMD = 0xDC; // Without parity: 0x5C; // WR_Byte //	
//////////	g_TM_EN = 0x5E; // WR_Word //
//////////
//////////	// Define register names and their addresses. //
//////////	// EEPROM shadow registers //	
//////////	g_SREG0 = 0x70; // WR_Word //
//////////	g_SREG1 = 0xF2; // Without parity: 0x72; // WR_Word //
//////////	g_SREG2 = 0xF4; // Without parity: 0x74; // WR_Word //
//////////	g_SREG3 = 0x76; // WR_Word //
//////////	g_SREG4 = 0xF8; // Without parity: 0x78; // WR_Word //
//////////	g_SREG5 = 0x7A; // WR_Word //
//////////	g_SREG6 = 0x7C; // WR_Word //
//////////
//////////	// Define register names and their addresses. //
//////////	// Read Back Registers //	
//////////	g_READ0 = 0x0000; // RD_Word //
//////////	g_READ1 = 0x0202; // RD_Word //
//////////	g_READ2 = 0x0404; // RD_Word //
//////////	g_READ3 = 0x0606; // RD_Word //
//////////	g_READ4 = 0x0808; // RD_Word //
//////////	g_READ5 = 0x0A0A; // RD_Word //
//////////	g_READ6 = 0x0C0C; // RD_Word //
//////////	g_READ7 = 0x0E0E; // RD_Word //
//////////	g_READ8 = 0x1010; // RD_Word //
//////////	g_READ9 = 0x1212; // RD_Word //
//////////	g_READ10 = 0x1414; // RD_Word //
//////////	g_READ11 = 0x1616; // RD_Word //
//////////	g_READ12 = 0x1818; // RD_Word //
//////////	g_READ13 = 0x1A1A; // RD_Word, test die //
//////////	g_READ14 = 0x1C1C; // RD_Word, test die //
//////////	g_READ15 = 0x1E1E; // RD_Word //
//////////	g_READ16 = 0x2020; // RD_Word //
//////////	g_READ17 = 0x2222; // RD_Word //
//////////	//g_READ18 = 0x2424; // RD_Word, Rev.1 silicon only //
//////////	//g_READ19 = 0x2626; // RD_Word, Rev.1 silicon only //
//////////	//g_READ20 = 0x2828; // RD_Word, Rev.1 silicon only //
//////////	//g_READ21 = 0x2A2A; // RD_Word, Rev.1 silicon only //
//////////	//g_READ22 = 0x2C2C; // RD_Word, Rev.1 silicon only //
//////////	g_READ40 = 0x5050; // WR_Word, Rev2 silicon //
//////////	g_READ41 = 0x5252; // WR_Word, Rev2 silicon //
//////////	g_READ42 = 0x5454; // WR_Word, Rev2 silicon //
//////////	g_READ43 = 0x5656; // WR_Word, Rev2 silicon //
//////////	g_READ44 = 0x5858; // WR_Word, Rev2 silicon //
//////////	g_READ45 = 0x5A5A; // WR_Word, Rev2 silicon //
//////////	g_READ46 = 0x5C5C; // WR_Word, Rev2 silicon //
//////////	g_READ47 = 0x5E5E; // WR_Word, Rev2 silicon //
//////////	g_READ56 = 0x7070; // WR_Word, Rev2 silicon //
//////////	g_READ57 = 0x7272; // WR_Word, Rev2 silicon //
//////////	g_READ58 = 0x7474; // WR_Word, Rev2 silicon //
//////////	g_READ59 = 0x7676; // WR_Word, Rev2 silicon //
//////////	g_READ60 = 0x7878; // WR_Word, Rev2 silicon //
//////////	g_READ61 = 0x7A7A; // WR_Word, Rev2 silicon //
//////////	g_READ62 = 0x7C7C; // WR_Word, Rev2 silicon //
//////////
//////////	// Passwords and keys for entering test mode. //
//////////	// To enter test mode, write the g_TestMode_Password followed by g_TestMode_Enter. //
//////////	// To exit test mode, write the g_TestMode_Password followed by g_TestMode_Exit. //
//////////	g_TestMode_Password = 0x2016; // Word //
//////////	g_TestMode_Enter = 0x1234; // Word.  Key to enter test mode. //
//////////	g_TestMode_Exit = 0xABCD; // Word.  Key to exit test mode. //
//////////	g_SR_Enable = 0x0004;//Word. Enable SR drive before entering scan mode.
//////////	g_ScanMode_Enter = 0x8000;//Word. Key to enter Scan mode.//
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//uint32_t DSM_Load_Write_Byte(int RegisterName, float RegisterData)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//	
//	// Start bit //
//	DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//
//	// Slave address (7 bits) //
//	Convert_Decimal_To_Binary(g_SlaveAddress, g_binary_array);  // Convert slave address into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=6;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Write bit //
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Register address (8 bits) //
//	Convert_Decimal_To_Binary(RegisterName, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Data byte //
//	Convert_Decimal_To_Binary(RegisterData, g_binary_array);  // Convert data into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Stop bit //
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//
//	return g_DSM_address - 1;
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//uint32_t DSM_Load_Write_Word(int RegisterName, float RegisterData)
//{
//	// Declare Variables //
//	int j = 0;
//	int k = 0;
//	
//	// Start bit //
//	DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//
//	// Slave address (7 bits) //
//	Convert_Decimal_To_Binary(g_SlaveAddress, g_binary_array);  // Convert slave address into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=6;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Write bit //
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Register address (8 bits) //
//	Convert_Decimal_To_Binary(RegisterName, g_binary_array);  // Convert register address into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Data word, low byte first //
//	Convert_Decimal_To_Binary(RegisterData, g_binary_array);  // Convert data into binary number stored in an array, g_binary_array[], for loading into DSM pattern memory. //
//	for (j=7;j>-1;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Data word, high byte //
//	for (j=15;j>7;j--)
//	{
//		for (k=0;k<4;k++)
//		{
//			if(k==0)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==1)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==2)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//				}
//			}
//			if(k==3)
//			{
//				if(g_binary_array[j]==0)
//				{
//					DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//				}
//				if(g_binary_array[j]==1)
//				{
//					DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//				}
//			}	
//		}
//	}
//
//	// Ack bit //
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "11XX" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "01XX" << "\n"; g_DSM_address++;
//
//	// Stop bit //
//	DSM_vector_file_write << "010X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "110X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "111X" << "\n"; g_DSM_address++;
//	DSM_vector_file_write << "011X" << "\n"; g_DSM_address++;
//
//	return g_DSM_address - 1;
//}
//
/*
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void MUX20_Test()
{
	// Declare Variables //
	float I_meas = 0;
	float V_meas = 0;
	int MUX20_error = 0;

	// Open all MUX20 relays to start //
	mux_20->open_relay(MUX_1_1);
	mux_20->open_relay(MUX_1_2);
	Open_relay(K1_UV_RB);
	mux_20->open_relay(MUX_1_4);
	mux_20->open_relay(MUX_1_BUS9);

	mux_20->open_relay(MUX_BANK_1_2);

	mux_20->open_relay(MUX_2_1);
	mux_20->open_relay(MUX_2_2);
	mux_20->open_relay(MUX_2_3);
	mux_20->open_relay(MUX_2_4);
	mux_20->open_relay(MUX_2_BUS2);
	mux_20->open_relay(MUX_2_GND);

	mux_20->open_relay(MUX_BANK_2_3);

	mux_20->open_relay(MUX_3_1);
	Open_relay(K1_TS_RB);
	mux_20->open_relay(MUX_3_3);
	mux_20->open_relay(MUX_3_4);
	mux_20->open_relay(MUX_3_BUS3);

	mux_20->open_relay(MUX_BANK_3_4);

	mux_20->open_relay(MUX_4_1);
	mux_20->open_relay(MUX_4_2);
	mux_20->open_relay(MUX_4_3);
	mux_20->open_relay(MUX_4_4);
	mux_20->open_relay(MUX_4_BUS4);
	mux_20->open_relay(MUX_4_GND);

	mux_20->open_relay(MUX_BANK_4_5);

	mux_20->open_relay(MUX_5_1);
	mux_20->open_relay(MUX_5_2);
	mux_20->open_relay(MUX_5_3);
	mux_20->open_relay(MUX_5_4);
	mux_20->open_relay(MUX_5_BUS10); // //
	mux_20->open_relay(MUX_5_BUS5); // //

	mux_20->open_relay(MUX_BANK_5_6);

	mux_20->open_relay(MUX_6_1);
	mux_20->open_relay(MUX_6_2);
	mux_20->open_relay(MUX_6_3);
	mux_20->open_relay(MUX_6_4);
	mux_20->open_relay(MUX_6_GND);
	mux_20->open_relay(MUX_6_BUS6);

	mux_20->open_relay(MUX_BANK_6_7);

	mux_20->open_relay(MUX_7_1);
	mux_20->open_relay(MUX_7_2);
	mux_20->open_relay(MUX_7_3);
	mux_20->open_relay(MUX_7_4);
	mux_20->open_relay(MUX_7_GND);
	mux_20->open_relay(MUX_7_BUS7);

	mux_20->open_relay(MUX_BANK_7_8);

	mux_20->open_relay(MUX_8_1);
	mux_20->open_relay(MUX_8_2);
	mux_20->open_relay(MUX_8_3);
	mux_20->open_relay(MUX_8_4);
	mux_20->open_relay(MUX_8_GND);
	mux_20->open_relay(MUX_8_BUS8);

	mux_20->open_relay(MUX_BANK_8_1);

	// Setup OVI3 CH3 //
	ovi_3->connect(3);
	ovi_3->set_voltage(OVI_CHANNEL_3, 0.0, RANGE_20_V); // OVI_3_3 //
	ovi_3->set_current(OVI_CHANNEL_3, 30e-6, RANGE_30_UA); // OVI_3_3 //
	Mux20_Close_relay(K61); // Connect OVI3 CH3 to MUX20_7_3 //
	wait.delay_10_us(300);

	// Make sure all MUX20 relays are open, check for leakage //
	ovi_3->set_meas_mode(OVI_CHANNEL_3, OVI_MEASURE_CURRENT); // OVI_3_3 //
	wait.delay_10_us(30);
	I_meas = ovi_3->measure();
	if (I_meas < -20e-6 || I_meas > 20e-6)
	{
		MUX20_error = -99;
	}


	// Check MUX_1_1 //
	//ovi_3->set_meas_mode(OVI_CHANNEL_3, OVI_MEASURE_VOLTAGE); // OVI_3_3 //
	mux_20->close_relay(MUX_7_3);
	mux_20->close_relay(MUX_BANK_7_8);
	mux_20->close_relay(MUX_BANK_8_1);
	wait.delay_10_us(300);
	I_meas = ovi_3->measure();
	//if (V_meas > 0.5) // +12V should not be connected yet //
	//	MUX20_error = -99;
	mux_20->close_relay(MUX_1_1);
	wait.delay_10_us(300);
	I_meas = ovi_3->measure();
	//if (V_meas < 11.5) // +12V should be connected //
	//	MUX20_error = -99;

	mux_20->open_relay(MUX_1_1);

	// Power down //
	Mux20_Open_relay(K61); // Connect OVI3 CH3 to MUX20_7_3 //

	// Reset relays //
	Mux20_Close_relay(MUX_2_GND);
	Mux20_Close_relay(MUX_4_GND);
	Mux20_Close_relay(MUX_6_GND);
	Mux20_Close_relay(MUX_7_GND);
	Mux20_Close_relay(MUX_8_GND);
	Mux20_Close_relay(MUX_BANK_1_2);
	Mux20_Close_relay(MUX_BANK_3_4);
	Mux20_Close_relay(MUX_BANK_5_6);
	wait.delay_10_us(300);
}
*/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Initialize_Instruments()
{
////	// This function sets instruments to a known state. //
////
////	VO_dvi->set_voltage(VO_ch, 0, VOLT_50_RANGE); // DVI_9_0 //
////	VO_dvi->set_current(VO_ch, 30e-3, RANGE_30_MA); // DVI_9_0 //
////	//VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE); // DVI_9_0 //
////
////	BPS_dvi->set_voltage(BPS_ch, 0, VOLT_50_RANGE); // DVI_9_1 //
////	BPS_dvi->set_current(BPS_ch, 30e-3, RANGE_30_MA); // DVI_9_1 //
////	//BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_VOLTAGE); // DVI_9_1 //
////
////	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////	//D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE); // DVI_11_0 //
////
////	BPP_DVI->set_voltage(BPP_ch, 0, VOLT_50_RANGE); // DVI_11_0 //
////	BPP_DVI->set_current(BPP_ch, 30e-3, RANGE_30_MA); // DVI_11_0 //
////	//BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE); // DVI_11_0 //
////
////	FW_dvi->set_voltage(FW_ch, 0, VOLT_50_RANGE); // DVI_11_1 //
////	FW_dvi->set_current(FW_ch, 30e-3, RANGE_30_MA); // DVI_11_1 //
////	//FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_VOLTAGE); // DVI_11_1 //
////
////	VBD_dvi->set_voltage(VBD_ch, 0, VOLT_50_RANGE); // DVI_21_0 //
////	VBD_dvi->set_current(VBD_ch, 30e-3, RANGE_30_MA); // DVI_21_0 //
////	//VBD_dvi->set_meas_mode(VBD_ch, DVI_MEASURE_VOLTAGE); // DVI_21_0 //
////
////	//dvi_17->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
////	//dvi_17->set_current(DVI_CHANNEL_1, 30e-3, RANGE_30_MA);
////	//dvi_17->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////
////	dvi_21->set_voltage(DVI_CHANNEL_1, 0, VOLT_50_RANGE);
////	dvi_21->set_current(DVI_CHANNEL_1, 30e-3, RANGE_30_MA);
////	//dvi_21->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
////
////	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_2_RANGE); // DVI_13_0, dvi2k //
////	IS_dvi2k->set_current(IS_ch, 20.0e-3, RANGE_20_MA); // DVI_13_0, dvi2k //
////	//IS_dvi2k->set_meas_mode(IS_ch, DVI_MEASURE_VOLTAGE); // DVI_13_0, dvi2k // 
////
////	SR_dvi2k->close_relay(CONN_FORCE1);
////	SR_dvi2k->close_relay(CONN_SENSE1);
////	SR_dvi2k->open_relay(BUS_SENSE1);
////	SR_dvi2k->open_relay(BUS_FORCE1);
////	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE); // DVI_13_1, dvi2k //
////	SR_dvi2k->set_current(SR_ch, 20.0e-3, RANGE_20_MA); // DVI_13_1, dvi2k //
////	//SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE); // DVI_13_1, dvi2k //
////
////	tmu_6->start_holdoff(0,FALSE);
////	tmu_6->stop_holdoff(0,FALSE);
////	tmu_6->open_relay(TMU_HIZ_DUT1);
////	tmu_6->open_relay(TMU_HIZ_DUT2);
////	tmu_6->open_relay(TMU_HIZ_DUT3);
////	tmu_6->open_relay(TMU_HIZ_DUT4);
////	tmu_6->open_relay(TMU_CHAN_A_DUT1);
////	tmu_6->open_relay(TMU_CHAN_A_DUT2);
////	tmu_6->open_relay(TMU_CHAN_B_DUT1);
////	tmu_6->open_relay(TMU_CHAN_B_DUT2);
////	
////	//hvs_15->set_voltage(0.0, RANGE_1_KV);
////	//hvs_15->set_current(100e-9, RANGE_1_MA);
////	//hvs_15->open_relay(HVS_NEG_FORCE);
////	//hvs_15->open_relay(HVS_SHORT_NEG_FS);	
////	//hvs_15->open_relay(HVS_GND_NEG_SENSE);	
////	//hvs_15->open_relay(HVS_SHORT_POS_FS);
////	//hvs_15->open_relay(HVS_FORCE_POS);
////
////	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
////	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
////	//BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE); // OVI_1_0 //
////
////	//VPIN_ovi->connect(VPIN_ch);
////	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V); // OVI_1_1 //
////	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA); // OVI_1_1 //
////	//VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_VOLTAGE); // OVI_1_1 //
////
////	//FB_ovi->connect(FB_ch);
////	FB_ovi->set_voltage(FB_ch, 0.0, RANGE_10_V); // OVI_1_2 //
////	FB_ovi->set_current(FB_ch, 30e-3, RANGE_30_MA); // OVI_1_2 //
////	//FB_ovi->set_meas_mode(FB_ch, OVI_MEASURE_VOLTAGE); // OVI_1_2 //
////
////	//BC_ovi->connect(BC_ch);
////	BC_ovi->set_voltage(BC_ch, 0.0, RANGE_10_V); // OVI_1_3 //
////	BC_ovi->set_current(BC_ch, 30e-3, RANGE_30_MA); // OVI_1_3 //
////	//BC_ovi->set_meas_mode(BC_ch, OVI_MEASURE_VOLTAGE); // OVI_1_3 //
////
////	//InvSyn_REF_ovi->connect(InvSyn_ch);
////	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0, RANGE_10_V); // OVI_1_4 //
////	InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3, RANGE_30_MA); // OVI_1_4 //
////	//InvSyn_REF_ovi->set_meas_mode(InvSyn_ch, OVI_MEASURE_VOLTAGE); // OVI_1_4 //
////
////	ovi_1->disconnect(5);
////	ovi_1->disconnect(7);
////
////	//ovi_1->connect(OVI_CHANNEL_5);
////	ovi_1->set_voltage(OVI_CHANNEL_5, 0.0, RANGE_10_V); // OVI_1_5 //
////	ovi_1->set_current(OVI_CHANNEL_5, 30e-3, RANGE_30_MA); // OVI_1_5 //
////	//ovi_1->set_meas_mode(OVI_CHANNEL_5, OVI_MEASURE_VOLTAGE); // OVI_1_5 //
////
////	//ovi_1->connect(OVI_CHANNEL_6);
////	ovi_1->set_voltage(OVI_CHANNEL_6, 0.0, RANGE_10_V); // OVI_1_6 //
////	ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_1_6 //
////	//ovi_1->set_meas_mode(OVI_CHANNEL_6, OVI_MEASURE_VOLTAGE); // OVI_1_6 //
////
////	//ovi_1->connect(OVI_CHANNEL_7);
////	ovi_1->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_1_7 //
////	ovi_1->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_1_7 //
////	//ovi_1->set_meas_mode(OVI_CHANNEL_7, OVI_MEASURE_VOLTAGE); // OVI_1_7 //
////
////	//SDA_ovi->connect(SDA_ch);
////	SDA_ovi->set_voltage(SDA_ch, 0.0, RANGE_10_V); // OVI_3_0 //
////	SDA_ovi->set_current(SDA_ch, 30e-3, RANGE_30_MA); // OVI_3_0 //
////	//SDA_ovi->set_meas_mode(SDA_ch, OVI_MEASURE_VOLTAGE); // OVI_3_0 //
////
////	//SCL_ovi->connect(SCL_ch);
////	SCL_ovi->set_voltage(SCL_ch, 0.0, RANGE_10_V); // OVI_3_1 //
////	SCL_ovi->set_current(SCL_ch, 30e-3, RANGE_30_MA); // OVI_3_1 //
////	//SCL_ovi->set_meas_mode(SCL_ch, OVI_MEASURE_VOLTAGE); // OVI_3_1 //
////
////	//uVCC_ovi->connect(uVCC_ch);
////	uVCC_ovi->set_voltage(uVCC_ch, 0.0, RANGE_10_V); // OVI_3_2 //
////	uVCC_ovi->set_current(uVCC_ch, 30e-3, RANGE_30_MA); // OVI_3_2 //
////	//uVCC_ovi->set_meas_mode(uVCC_ch, OVI_MEASURE_VOLTAGE); // OVI_3_2 //
////
////	ovi_3->disconnect(3);
////	//ovi_3->set_voltage(OVI_CHANNEL_3, 0.0, RANGE_10_V); // OVI_3_3 //
////	//ovi_3->set_current(OVI_CHANNEL_3, 30e-3, RANGE_30_MA); // OVI_3_3 //
////	//ovi_3->set_meas_mode(OVI_CHANNEL_3, OVI_MEASURE_VOLTAGE); // OVI_3_3 //
////
////	//IS_ovi->connect(IS_ovi_ch);
////	IS_ovi->set_voltage(IS_ovi_ch, 0.0, RANGE_10_V); // OVI_3_4 //
////	IS_ovi->set_current(IS_ovi_ch, 30e-3, RANGE_30_MA); // OVI_3_4 //
////	//IS_ovi->set_meas_mode(IS_ovi_ch, OVI_MEASURE_VOLTAGE); // OVI_3_4 //
////
////	ovi_3->disconnect(5);
////	//ovi_3->connect(OVI_CHANNEL_5);
////	//ovi_3->set_voltage(OVI_CHANNEL_5, 0.0, RANGE_10_V); // OVI_3_5 //
////	//ovi_3->set_current(OVI_CHANNEL_5, 30e-3, RANGE_30_MA); // OVI_3_5 //
////	//ovi_3->set_meas_mode(OVI_CHANNEL_5, OVI_MEASURE_VOLTAGE); // OVI_3_5 //
////
////	//ovi_3->connect(OVI_CHANNEL_6);
////	ovi_3->set_voltage(OVI_CHANNEL_6, 0.0, RANGE_10_V); // OVI_3_6 //
////	ovi_3->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA); // OVI_3_6 //
////	//ovi_3->set_meas_mode(OVI_CHANNEL_6, OVI_MEASURE_VOLTAGE); // OVI_3_6 //
////
////	//ovi_3->connect(OVI_CHANNEL_7);
////	ovi_3->set_voltage(OVI_CHANNEL_7, 0.0, RANGE_10_V); // OVI_3_7 //
////	ovi_3->set_current(OVI_CHANNEL_7, 30e-3, RANGE_30_MA); // OVI_3_7 //
////	//ovi_3->set_meas_mode(OVI_CHANNEL_7, OVI_MEASURE_VOLTAGE); // OVI_3_7 //
////
//////	ddd_7->ddd_stop_pattern(); // Stop DDD loop pattern //
////	
////	// DDD level //
////	g_DDD_Low = 0.0; // Save current value //
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_set_lo_level(g_DDD_Low); // Will immediately change to this level upon execution 
////	wait.delay_10_us(g_DDDwait);
////	ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
////	wait.delay_10_us(5);
////
////	//ddd_7->ddd_disconnect_drivers();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void LoadShadowRegister()
//{
//	// This function uses I2C to load the g_ShadowRegister[] array to the DUTs shadow register. // 
//
//	// Declare Variables //
//	int NObin[1] = {0}; // Place holder //
//	int NOhex = 0; // Place holder //
//	int WordArray[16] = {0};
//
//	// SREG0 //
//	WordArray[0] = g_ShadowRegister[0];
//	WordArray[1] = g_ShadowRegister[1];
//	WordArray[2] = g_ShadowRegister[2];
//	WordArray[3] = g_ShadowRegister[3];
//	WordArray[4] = g_ShadowRegister[4];
//	WordArray[5] = g_ShadowRegister[5];
//	WordArray[6] = g_ShadowRegister[6];
//	WordArray[7] = g_ShadowRegister[7];
//	WordArray[8] = g_ShadowRegister[8];
//	WordArray[9] = g_ShadowRegister[9];
//	WordArray[10] = g_ShadowRegister[10];
//	WordArray[11] = g_ShadowRegister[11];
//	WordArray[12] = g_ShadowRegister[12];
//	WordArray[13] = g_ShadowRegister[13];
//	WordArray[14] = g_ShadowRegister[14];
//	WordArray[15] = g_ShadowRegister[15];
//	Write_Word(g_SREG0, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG1 //
//	WordArray[0] = g_ShadowRegister[16];
//	WordArray[1] = g_ShadowRegister[17];
//	WordArray[2] = g_ShadowRegister[18];
//	WordArray[3] = g_ShadowRegister[19];
//	WordArray[4] = g_ShadowRegister[20];
//	WordArray[5] = g_ShadowRegister[21];
//	WordArray[6] = g_ShadowRegister[22];
//	WordArray[7] = g_ShadowRegister[23];
//	WordArray[8] = g_ShadowRegister[24];
//	WordArray[9] = g_ShadowRegister[25];
//	WordArray[10] = g_ShadowRegister[26];
//	WordArray[11] = g_ShadowRegister[27];
//	WordArray[12] = g_ShadowRegister[28];
//	WordArray[13] = g_ShadowRegister[29];
//	WordArray[14] = g_ShadowRegister[30];
//	WordArray[15] = g_ShadowRegister[31];
//	Write_Word(g_SREG1, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG2 //
//	WordArray[0] = g_ShadowRegister[32];
//	WordArray[1] = g_ShadowRegister[33];
//	WordArray[2] = g_ShadowRegister[34];
//	WordArray[3] = g_ShadowRegister[35];
//	WordArray[4] = g_ShadowRegister[36];
//	WordArray[5] = g_ShadowRegister[37];
//	WordArray[6] = g_ShadowRegister[38];
//	WordArray[7] = g_ShadowRegister[39];
//	WordArray[8] = g_ShadowRegister[40];
//	WordArray[9] = g_ShadowRegister[41];
//	WordArray[10] = g_ShadowRegister[42];
//	WordArray[11] = g_ShadowRegister[43];
//	WordArray[12] = g_ShadowRegister[44];
//	WordArray[13] = g_ShadowRegister[45];
//	WordArray[14] = g_ShadowRegister[46];
//	WordArray[15] = g_ShadowRegister[47];
//	Write_Word(g_SREG2, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG3 //
//	WordArray[0] = g_ShadowRegister[48];
//	WordArray[1] = g_ShadowRegister[49];
//	WordArray[2] = g_ShadowRegister[50];
//	WordArray[3] = g_ShadowRegister[51];
//	WordArray[4] = g_ShadowRegister[52];
//	WordArray[5] = g_ShadowRegister[53];
//	WordArray[6] = g_ShadowRegister[54];
//	WordArray[7] = g_ShadowRegister[55];
//	WordArray[8] = g_ShadowRegister[56];
//	WordArray[9] = g_ShadowRegister[57];
//	WordArray[10] = g_ShadowRegister[58];
//	WordArray[11] = g_ShadowRegister[59];
//	WordArray[12] = g_ShadowRegister[60];
//	WordArray[13] = g_ShadowRegister[61];
//	WordArray[14] = g_ShadowRegister[62];
//	WordArray[15] = g_ShadowRegister[63];
//	Write_Word(g_SREG3, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG4 //
//	WordArray[0] = g_ShadowRegister[64];
//	WordArray[1] = g_ShadowRegister[65];
//	WordArray[2] = g_ShadowRegister[66];
//	WordArray[3] = g_ShadowRegister[67];
//	WordArray[4] = g_ShadowRegister[68];
//	WordArray[5] = g_ShadowRegister[69];
//	WordArray[6] = g_ShadowRegister[70];
//	WordArray[7] = g_ShadowRegister[71];
//	WordArray[8] = g_ShadowRegister[72];
//	WordArray[9] = g_ShadowRegister[73];
//	WordArray[10] = g_ShadowRegister[74];
//	WordArray[11] = g_ShadowRegister[75];
//	WordArray[12] = g_ShadowRegister[76];
//	WordArray[13] = g_ShadowRegister[77];
//	WordArray[14] = g_ShadowRegister[78];
//	WordArray[15] = g_ShadowRegister[79];
//	Write_Word(g_SREG4, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG5 //
//	WordArray[0] = g_ShadowRegister[80];
//	WordArray[1] = g_ShadowRegister[81];
//	WordArray[2] = g_ShadowRegister[82];
//	WordArray[3] = g_ShadowRegister[83];
//	WordArray[4] = g_ShadowRegister[84];
//	WordArray[5] = g_ShadowRegister[85];
//	WordArray[6] = g_ShadowRegister[86];
//	WordArray[7] = g_ShadowRegister[87];
//	WordArray[8] = g_ShadowRegister[88];
//	WordArray[9] = g_ShadowRegister[89];
//	WordArray[10] = g_ShadowRegister[90];
//	WordArray[11] = g_ShadowRegister[91];
//	WordArray[12] = g_ShadowRegister[92];
//	WordArray[13] = g_ShadowRegister[93];
//	WordArray[14] = g_ShadowRegister[94];
//	WordArray[15] = g_ShadowRegister[95];
//	Write_Word(g_SREG5, NOhex, WordArray, BIN); // Write to shadow register. //
//
//	// SREG6 //
//	WordArray[0] = g_ShadowRegister[96];
//	WordArray[1] = g_ShadowRegister[97];
//	WordArray[2] = g_ShadowRegister[98];
//	WordArray[3] = g_ShadowRegister[99];
//	WordArray[4] = g_ShadowRegister[100];
//	WordArray[5] = g_ShadowRegister[101];
//	WordArray[6] = g_ShadowRegister[102];
//	WordArray[7] = g_ShadowRegister[103];
//	WordArray[8] = g_ShadowRegister[104];
//	WordArray[9] = g_ShadowRegister[105];
//	WordArray[10] = g_ShadowRegister[106];
//	WordArray[11] = g_ShadowRegister[107];
//	WordArray[12] = g_ShadowRegister[108];
//	WordArray[13] = g_ShadowRegister[109];
//	WordArray[14] = g_ShadowRegister[110];
//	WordArray[15] = g_ShadowRegister[111];
//	Write_Word(g_SREG6, NOhex, WordArray, BIN); // Write to shadow register. //
//}
//
//------------------------------------------------------------------
//HL added to burn EEprom for either primary or secondary.
//------------------------------------------------------------------

void Program_Trim_Register(int *Trim_Register)
{
	// This function uses I2C to load the TrimRegister[] array (either g_Pri_TrimRegister[] or 
	// g_Sec_TrimRegister[] array to the DUTs shadow register. // 

	// Declare Variables //
	int WordArray[16] = {0};
	uint16_t BIN_2_Dec_Num = 0;

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	// E0 //
	WordArray[0]  = Trim_Register[0];
	WordArray[1]  = Trim_Register[1];
	WordArray[2]  = Trim_Register[2];
	WordArray[3]  = Trim_Register[3];
	WordArray[4]  = Trim_Register[4];
	WordArray[5]  = Trim_Register[5];
	WordArray[6]  = Trim_Register[6];
	WordArray[7]  = Trim_Register[7];
	WordArray[8]  = Trim_Register[8];
	WordArray[9]  = Trim_Register[9];
	WordArray[10] = Trim_Register[10];
	WordArray[11] = Trim_Register[11];
	WordArray[12] = Trim_Register[12];
	WordArray[13] = Trim_Register[13];
	WordArray[14] = Trim_Register[14];
	WordArray[15] = Trim_Register[15];

	BIN_2_Dec_Num = Convert_BIN_2_Dec(WordArray);
	if(BIN_2_Dec_Num != 0)
	{
		DSM_I2C_Write('w', g_EEP_W_E0, BIN_2_Dec_Num);
	}
	
	// E2 //
	WordArray[0]  = Trim_Register[16];
	WordArray[1]  = Trim_Register[17];
	WordArray[2]  = Trim_Register[18];
	WordArray[3]  = Trim_Register[19];
	WordArray[4]  = Trim_Register[20];
	WordArray[5]  = Trim_Register[21];
	WordArray[6]  = Trim_Register[22];
	WordArray[7]  = Trim_Register[23];
	WordArray[8]  = Trim_Register[24];
	WordArray[9]  = Trim_Register[25];
	WordArray[10] = Trim_Register[26];
	WordArray[11] = Trim_Register[27];
	WordArray[12] = Trim_Register[28];
	WordArray[13] = Trim_Register[29];
	WordArray[14] = Trim_Register[30];
	WordArray[15] = Trim_Register[31];

	BIN_2_Dec_Num = Convert_BIN_2_Dec(WordArray);
	if(BIN_2_Dec_Num != 0)
	{
		DSM_I2C_Write('w', g_EEP_W_E2, BIN_2_Dec_Num);
	}
	
	// E4 //
	WordArray[0]  = Trim_Register[32];
	WordArray[1]  = Trim_Register[33];
	WordArray[2]  = Trim_Register[34];
	WordArray[3]  = Trim_Register[35];
	WordArray[4]  = Trim_Register[36];
	WordArray[5]  = Trim_Register[37];
	WordArray[6]  = Trim_Register[38];
	WordArray[7]  = Trim_Register[39];
	WordArray[8]  = Trim_Register[40];
	WordArray[9]  = Trim_Register[41];
	WordArray[10] = Trim_Register[42];
	WordArray[11] = Trim_Register[43];
	WordArray[12] = Trim_Register[44];
	WordArray[13] = Trim_Register[45];
	WordArray[14] = Trim_Register[46];
	WordArray[15] = Trim_Register[47];

	BIN_2_Dec_Num = Convert_BIN_2_Dec(WordArray);

	if(BIN_2_Dec_Num != 0)
	{
		DSM_I2C_Write('w', g_EEP_W_E4, BIN_2_Dec_Num);
	}
	
	// E6 //
	WordArray[0]  = Trim_Register[48];
	WordArray[1]  = Trim_Register[49];
	WordArray[2]  = Trim_Register[50];
	WordArray[3]  = Trim_Register[51];
	WordArray[4]  = Trim_Register[52];
	WordArray[5]  = Trim_Register[53];
	WordArray[6]  = Trim_Register[54];
	WordArray[7]  = Trim_Register[55];
	WordArray[8]  = Trim_Register[56];
	WordArray[9]  = Trim_Register[57];
	WordArray[10] = Trim_Register[58];
	WordArray[11] = Trim_Register[59];
	WordArray[12] = Trim_Register[60];
	WordArray[13] = Trim_Register[61];
	WordArray[14] = Trim_Register[62];
	WordArray[15] = Trim_Register[63];

	BIN_2_Dec_Num = Convert_BIN_2_Dec(WordArray);
	if(BIN_2_Dec_Num != 0)
	{
		DSM_I2C_Write('w', g_EEP_W_E6, BIN_2_Dec_Num);
	}
	
	// E8 //
	WordArray[0]  = Trim_Register[64];
	WordArray[1]  = Trim_Register[65];
	WordArray[2]  = Trim_Register[66];
	WordArray[3]  = Trim_Register[67];
	WordArray[4]  = Trim_Register[68];
	WordArray[5]  = Trim_Register[69];
	WordArray[6]  = Trim_Register[70];
	WordArray[7]  = Trim_Register[71];
	WordArray[8]  = Trim_Register[72];
	WordArray[9]  = Trim_Register[73];
	WordArray[10] = Trim_Register[74];
	WordArray[11] = Trim_Register[75];
	WordArray[12] = Trim_Register[76];
	WordArray[13] = Trim_Register[77];
	WordArray[14] = Trim_Register[78];
	WordArray[15] = Trim_Register[79];

	BIN_2_Dec_Num = Convert_BIN_2_Dec(WordArray);
	if(BIN_2_Dec_Num != 0)
	{
		DSM_I2C_Write('w', g_EEP_W_E8, BIN_2_Dec_Num);
	}
	

}

void Program_All_TrimRegister()
{
	// This function uses I2C to load the TrimRegister[] array (either g_Pri_TrimRegister[] or 
	// g_Sec_TrimRegister[] array to the DUTs shadow register. // 
	int i = 0;
	int g_EEP_W_Array[] = {g_EEP_W_E0, g_EEP_W_E2, g_EEP_W_E4, g_EEP_W_E6, g_EEP_W_E8};

	for(i=0;i<5;i++)
	{
		DSM_I2C_Write('w', g_EEP_W_Array[i], EEpr_Bank_P[i]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
}

void Program_All_TrimRegister_P()
{
	// This function uses I2C to load the TrimRegister[] array (either g_Pri_TrimRegister[] or 
	// g_Sec_TrimRegister[] array to the DUTs shadow register. // 
	int i = 0;
	int g_EEP_W_Array[] = {g_EEP_W_E0, g_EEP_W_E2, g_EEP_W_E4, g_EEP_W_E6, g_EEP_W_E8};

	for(i=0;i<5;i++)
	{
		DSM_I2C_Write('w', g_EEP_W_Array[i], EEpr_Bank_P[i]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
}

void Program_Single_TrimRegister(int TrimLocation)
{
	////g_EEP_W_E0     = 0xE0;       //WR_Word
	////g_EEP_W_E2     = 0xE2;       //WR_Word
	////g_EEP_W_E4     = 0xE4;       //WR_Word
	////g_EEP_W_E6     = 0xE6;       //WR_Word
	////g_EEP_W_E8     = 0xE8;       //WR_Word
	if(TrimLocation == 0xE0)
	{
		DSM_I2C_Write('w', g_EEP_W_E0, EEpr_Bank_P[0]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
	if(TrimLocation == 0xE2)
	{
		DSM_I2C_Write('w', g_EEP_W_E2, EEpr_Bank_P[1]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
	if(TrimLocation == 0xE4)
	{
		DSM_I2C_Write('w', g_EEP_W_E4, EEpr_Bank_P[2]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
	if(TrimLocation == 0xE6)
	{
		DSM_I2C_Write('w', g_EEP_W_E6, EEpr_Bank_P[3]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
	if(TrimLocation == 0xE8)
	{
		DSM_I2C_Write('w', g_EEP_W_E8, EEpr_Bank_P[4]);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);
	}
}

//------------------------------------------------------------------
//HL added to read EEprom register for either primary or secondary.
//------------------------------------------------------------------

void Read_Trim_Register(int *TrimBank)
{
		DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
		//g_Debug = 1;
		TrimBank[0] = DSM_I2C_Read(0xC0);	//Read back data of Register addr 0xE0 from 0xC0 register address through READ_ADDR 0x00
		TrimBank[1] = DSM_I2C_Read(0xC2);	//Read back data of Register addr 0xE2 from 0xC2 register address through READ_ADDR 0x00
		TrimBank[2] = DSM_I2C_Read(0xC4);	//Read back data of Register addr 0xE4 from 0xC4 register address through READ_ADDR 0x00
		TrimBank[3] = DSM_I2C_Read(0xC6);	//Read back data of Register addr 0xE6 from 0xC6 register address through READ_ADDR 0x00
		TrimBank[4] = DSM_I2C_Read(0xC8);	//Read back data of Register addr 0xE8 from 0xC8 register address through READ_ADDR 0x00
		//g_Debug = 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void ReadShadowRegister()
//{
//	// This function uses I2C to load the DUTs shadow register to the g_ShadowRegister[] array.  // 
//
//	// Declare Variables //
//	int NObin[1] = {0}; // Place holder //
//	int READ13_word[16] = {0};
//	int READ14_word[16] = {0};
//	int READ15_word[16] = {0};
//	int READ16_word[16] = {0};
//	int READ17_word[16] = {0};
//	int READ18_word[16] = {0};
//	int READ19_word[16] = {0};
//	int READ56_word[16] = {0};
//	int READ57_word[16] = {0};
//	int READ58_word[16] = {0};
//	int READ59_word[16] = {0};
//	int READ60_word[16] = {0};
//	int READ61_word[16] = {0};
//	int READ62_word[16] = {0};
//
//	Write_Word(g_RDADDR, g_READ56, NObin, HEX);// SREG0.  Shadow register. //
//	Read_Word(g_RDADDR, READ56_word);// SREG0.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ57, NObin, HEX);// SREG1.  Shadow register. //
//	Read_Word(g_RDADDR, READ57_word);// SREG1.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ58, NObin, HEX);// SREG2.  Shadow register. //
//	Read_Word(g_RDADDR, READ58_word);// SREG2.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ59, NObin, HEX);// SREG3.  Shadow register. //
//	Read_Word(g_RDADDR, READ59_word);// SREG3.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ60, NObin, HEX); // SREG4.  Shadow register. //
//	Read_Word(g_RDADDR, READ60_word);// SREG4.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ61, NObin, HEX); // SREG5.  Shadow register. //
//	Read_Word(g_RDADDR, READ61_word); // SREG5.  Shadow register. //
//
//	Write_Word(g_RDADDR, g_READ62, NObin, HEX); // SREG6.  Shadow register. //
//	Read_Word(g_RDADDR, READ62_word); // SREG6.  Shadow register. //
//
//	// Load Shadow Register //
//	g_ShadowRegister[0] = READ56_word[0];
//	g_ShadowRegister[1] = READ56_word[1];
//	g_ShadowRegister[2] = READ56_word[2];
//	g_ShadowRegister[3] = READ56_word[3];
//	g_ShadowRegister[4] = READ56_word[4];
//	g_ShadowRegister[5] = READ56_word[5];
//	g_ShadowRegister[6] = READ56_word[6];
//	g_ShadowRegister[7] = READ56_word[7];
//	g_ShadowRegister[8] = READ56_word[8];
//	g_ShadowRegister[9] = READ56_word[9];
//	g_ShadowRegister[10] = READ56_word[10];
//	g_ShadowRegister[11] = READ56_word[11];
//	g_ShadowRegister[12] = READ56_word[12];
//	g_ShadowRegister[13] = READ56_word[13];
//	g_ShadowRegister[14] = READ56_word[14];
//	g_ShadowRegister[15] = READ56_word[15];
//	g_ShadowRegister[16] = READ57_word[0];
//	g_ShadowRegister[17] = READ57_word[1];
//	g_ShadowRegister[18] = READ57_word[2];
//	g_ShadowRegister[19] = READ57_word[3];
//	g_ShadowRegister[20] = READ57_word[4];
//	g_ShadowRegister[21] = READ57_word[5];
//	g_ShadowRegister[22] = READ57_word[6];
//	g_ShadowRegister[23] = READ57_word[7];
//	g_ShadowRegister[24] = READ57_word[8];
//	g_ShadowRegister[25] = READ57_word[9];
//	g_ShadowRegister[26] = READ57_word[10];
//	g_ShadowRegister[27] = READ57_word[11];
//	g_ShadowRegister[28] = READ57_word[12];
//	g_ShadowRegister[29] = READ57_word[13];
//	g_ShadowRegister[30] = READ57_word[14];
//	g_ShadowRegister[31] = READ57_word[15];
//	g_ShadowRegister[32] = READ58_word[0];
//	g_ShadowRegister[33] = READ58_word[1];
//	g_ShadowRegister[34] = READ58_word[2];
//	g_ShadowRegister[35] = READ58_word[3];
//	g_ShadowRegister[36] = READ58_word[4];
//	g_ShadowRegister[37] = READ58_word[5];
//	g_ShadowRegister[38] = READ58_word[6];
//	g_ShadowRegister[39] = READ58_word[7];
//	g_ShadowRegister[40] = READ58_word[8];
//	g_ShadowRegister[41] = READ58_word[9];
//	g_ShadowRegister[42] = READ58_word[10];
//	g_ShadowRegister[43] = READ58_word[11];
//	g_ShadowRegister[44] = READ58_word[12];
//	g_ShadowRegister[45] = READ58_word[13];
//	g_ShadowRegister[46] = READ58_word[14];
//	g_ShadowRegister[47] = READ58_word[15];
//	g_ShadowRegister[48] = READ59_word[0];
//	g_ShadowRegister[49] = READ59_word[1];
//	g_ShadowRegister[50] = READ59_word[2];
//	g_ShadowRegister[51] = READ59_word[3];
//	g_ShadowRegister[52] = READ59_word[4];
//	g_ShadowRegister[53] = READ59_word[5];
//	g_ShadowRegister[54] = READ59_word[6];
//	g_ShadowRegister[55] = READ59_word[7];
//	g_ShadowRegister[56] = READ59_word[8];
//	g_ShadowRegister[57] = READ59_word[9];
//	g_ShadowRegister[58] = READ59_word[10];
//	g_ShadowRegister[59] = READ59_word[11];
//	g_ShadowRegister[60] = READ59_word[12];
//	g_ShadowRegister[61] = READ59_word[13];
//	g_ShadowRegister[62] = READ59_word[14];
//	g_ShadowRegister[63] = READ59_word[15];
//	g_ShadowRegister[64] = READ60_word[0];
//	g_ShadowRegister[65] = READ60_word[1];
//	g_ShadowRegister[66] = READ60_word[2];
//	g_ShadowRegister[67] = READ60_word[3];
//	g_ShadowRegister[68] = READ60_word[4];
//	g_ShadowRegister[69] = READ60_word[5];
//	g_ShadowRegister[70] = READ60_word[6];
//	g_ShadowRegister[71] = READ60_word[7];
//	g_ShadowRegister[72] = READ60_word[8];
//	g_ShadowRegister[73] = READ60_word[9];
//	g_ShadowRegister[74] = READ60_word[10];
//	g_ShadowRegister[75] = READ60_word[11];
//	g_ShadowRegister[76] = READ60_word[12];
//	g_ShadowRegister[77] = READ60_word[13];
//	g_ShadowRegister[78] = READ60_word[14];
//	g_ShadowRegister[79] = READ60_word[15];
//	g_ShadowRegister[80] = READ61_word[0];
//	g_ShadowRegister[81] = READ61_word[1];
//	g_ShadowRegister[82] = READ61_word[2];
//	g_ShadowRegister[83] = READ61_word[3];
//	g_ShadowRegister[84] = READ61_word[4];
//	g_ShadowRegister[85] = READ61_word[5];
//	g_ShadowRegister[86] = READ61_word[6];
//	g_ShadowRegister[87] = READ61_word[7];
//	g_ShadowRegister[88] = READ61_word[8];
//	g_ShadowRegister[89] = READ61_word[9];
//	g_ShadowRegister[90] = READ61_word[10];
//	g_ShadowRegister[91] = READ61_word[11];
//	g_ShadowRegister[92] = READ61_word[12];
//	g_ShadowRegister[93] = READ61_word[13];
//	g_ShadowRegister[94] = READ61_word[14];
//	g_ShadowRegister[95] = READ61_word[15];
//	g_ShadowRegister[96] = READ62_word[0];
//	g_ShadowRegister[97] = READ62_word[1];
//	g_ShadowRegister[98] = READ62_word[2];
//	g_ShadowRegister[99] = READ62_word[3];
//	g_ShadowRegister[100] = READ62_word[4];
//	g_ShadowRegister[101] = READ62_word[5];
//	g_ShadowRegister[102] = READ62_word[6];
//	g_ShadowRegister[103] = READ62_word[7];
//	g_ShadowRegister[104] = READ62_word[8];
//	g_ShadowRegister[105] = READ62_word[9];
//	g_ShadowRegister[106] = READ62_word[10];
//	g_ShadowRegister[107] = READ62_word[11];
//	g_ShadowRegister[108] = READ62_word[12];
//	g_ShadowRegister[109] = READ62_word[13];
//	g_ShadowRegister[110] = READ62_word[14];
//	g_ShadowRegister[111] = READ62_word[15];
//}
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Data_To_Text_File(int ArraySize, char FileName[], char Arr1_Label[], float Arr1_Data[], char Arr2_Label[], float Arr2_Data[], char Arr3_Label[], float Arr3_Data[], char Arr4_Label[], float Arr4_Data[], char Arr5_Label[], float Arr5_Data[])
{
	// Example function call //
	//float Arr1[xx] = {0};
	//float Arr2[xx] = {0};
	//float Arr3[xx] = {0};
	//float Arr4[xx] = {0};
	//float Arr5[xx] = {0};
	//Data_To_Text_File(ArraySize, "MyLYT3Data", "First", Arr1, "ColumnLabel2", Arr2, "ColumnLabel3", Arr3, "ColumnLabel4", Arr4, "ColumnLabel5", Arr5);

	// Declare Variables //
	int i = 0;
	ofstream dumparray;
	char DirectoryPath[100] = "e:\\dl4\\";

	//int Arr1_Data_size = sizeof(Arr1_Data);
	//int Arr2_Data_size = sizeof(float);
	//int Arr3_Data_size = sizeof(Arr3_Data)/sizeof(float);
	//int Arr4_Data_size = sizeof(Arr4_Data)/sizeof(float);
	//int Arr5_Data_size = sizeof(Arr5_Data)/sizeof(float);

	// Get LoopSize --> equal to smallest array size.  Use smallest array size to prevent exceeding array bound in the for loop when the data is written out. //
	//int LoopSize = 999999;
	//if (Arr1_Data_size < LoopSize)
	//	LoopSize = Arr1_Data_size;
	//if(Arr2_Data_size < LoopSize)
	//	LoopSize = Arr2_Data_size;
	//if(Arr3_Data_size < LoopSize)
	//	LoopSize = Arr3_Data_size;
	//if(Arr4_Data_size < LoopSize)
	//	LoopSize = Arr4_Data_size;
	//if(Arr5_Data_size < LoopSize)
	//	LoopSize = Arr5_Data_size;

	// Write the data to a .txt file. //
	//dumparray.open( "e:\\dl4\\FOSCDutyVsCode.txt", dumparray.app);  // The extra parameter dumparray.app will just append to the existing .txt file.  Otherwise, it creates a new file. //
	strcat(DirectoryPath,FileName);
	strcat(DirectoryPath,".txt");
	dumparray.open(DirectoryPath);
	dumparray << Arr1_Label << "\t" << "\t" << "\t"
		<< Arr2_Label << "\t" << "\t" << "\t"
		<< Arr3_Label << "\t" << "\t" << "\t"
		<< Arr4_Label << "\t" << "\t" << "\t"
		<< Arr5_Label << "\n";
	for (i=0; i<ArraySize; i++)
		dumparray << Arr1_Data[i] << "\t" << "\t" << "\t" 
		<< Arr2_Data[i] << "\t" << "\t" << "\t" 
		<< Arr3_Data[i] << "\t" << "\t" << "\t" 
		<< Arr4_Data[i] << "\t" << "\t" << "\t" 
		<< Arr5_Data[i] << "\n";
	dumparray<< endl;
	dumparray.close();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void FunctionsToExecute()
{
	// Decide which functions will be executed. All the little boxes in .prg should be set 
	// to green, even if they will not be executed.  This function is used to 
	// determine which functions will be run.  The purpose is to keep control of which 
	// functions are executed under source code control. //
	g_Fn_aFirst =				1; // x, 1 
	g_Fn_Continuity =			1; // x, 2
	g_Fn_Leakage =				1; // x, 3
	g_Fn_BV_Vpin =				0; // x, 4
	g_Fn_BV_FW =				0; // x, 5
	g_Fn_BV_Drain =				0; // x, 6
	g_Fn_VBP_Init =				0; // x, 7
	g_Fn_ScanChain =			0; // x, 8
	g_Fn_IzPre =				0; // x, 9
	g_Fn_Feature_Trim_P =		0; // x, 10, Disable for secondary retrim //
	g_Fn_Feature_Trim_S =		0; // x, 11
	g_Fn_BPS_STRESS =			0; // x, 12
	g_Fn_BPP_STRESS =			0; // x, 13
	g_Fn_OVT =					0; // x, 14
	g_Fn_IOV_Pre_P =			0; // x, 15
	g_Fn_IOV_Trim =				0; // x, 16, Disable for secondary retrim //
	g_Fn_IOV_post_P =			0; // 0, 17
	g_Fn_Fosc_Pre_P =			0; // x, 18
	g_Fn_Fosc_Trim_P =			0; // x, 19, Disable for secondary retrim //
	g_Fn_Fosc_post_P =			0; // x, 20
	g_Fn_tOVL_Pre_S =			0; // x, 21
	g_Fn_tOVL_Trim =			0; // x, 22, Disable for secondary retrim //
	g_Fn_tOVL_post_S=			0; // x, 23
	g_Fn_Fosc_Pre_S =			0; // x, 24
	g_Fn_Fosc_Trim_S =			0; // x, 25
	g_Fn_Fosc_post_S =			0; // x, 26
	g_Fn_OSC_Pt =				0; // x, 27
	g_Fn_ILIM_Pre =				0; // x, 28
	g_Fn_ILIM_Trim =			0; // x, 29, Disable for secondary retrim //
	g_Fn_ILIM =					0; // x, 30
	g_Fn_CV_Pre =				0; // x, 31
	g_Fn_ISvth_Pre_S =			0; // x, 32
	g_Fn_nDAC_Pt =				0; // x, 33
	g_Fn_pDAC_Pt =				0; // x, 34
	g_Fn_DofA_Pt =				0; // x, 35
	g_Fn_IsDAC_Pt =				0; // x, 36
	g_Fn_Gain_Pt =				0; // x, 37
	g_Fn_CDC_Pre =				0; // x, 38
	g_Fn_CCoff_Pt =				0; // 0, 39
	g_Fn_IsCal_Pt =				0; // x, 40
	g_Fn_ADC_Pt =				0; // x, 41
	g_Fn_EEPROM_Write =			0; // 1, 42
	g_Fn_IzPost =				0; // x, 43
	g_SoftStart =				0; // x, 44
	g_Fn_VBP_Supply =			0; // x, 45
	g_Fn_IBP_Supply =			0; // x, 46
	g_Fn_IOV_IUV_OT =			0; // x, 47
	g_Fn_FOSC_Ton_ARST =		0; // x, 48
	g_Fn_FWPK =					0; // x, 49
	g_Fn_SR_Delay_tREQinh =		0; // x, 50	
	g_Fn_SOA_SDS_TW50 =			0; // x, 51
	g_Fn_IsCal_Final =			0; // x, 52
	g_Fn_Iout =					0; // x, 53
	g_Fn_CV_nDAC_pDAC =			0; // x, 54
	g_Fn_Vesr =					0; // x, 55
	g_Fn_Isvth3X_AR_ISSC =		0; // x, 56
	g_Fn_Vovp =					0; // x, 57
	g_Fn_UVP =					0; // x, 58
	g_Fn_VBD_uVCC =				0; // x, 59
	g_Fn_OSC_Final =			0; // x, 60
	g_Fn_DofA_Final =			0; // x, 61
	g_Fn_IsDAC_Final =			0; // x, 62
	g_Fn_Gain_Final =			0; // x, 63
	g_Fn_CDC_Final =			0; // x, 64
	g_Fn_Ccoff_Final =			0; // x, 65	
	g_Fn_VPK =					0; // x, 66
	g_Fn_ADC_Final =			0; // x, 67
	g_Fn_DATT =					0; // x, 68
	g_Fn_zLast =				0; // x, 69
}


////////////int _my_DSM_read_I2C_buffer	(int DSM_context, 
////////////							 uint16_t address,
////////////							 uint8_t num_read_bytes,
////////////							 uint8_t * readDataBuffer )
////////////{
////////////	int i;
////////////	int ret_code = DSM_read_I2C_buffer ( DSM_context, 
////////////										 address,
////////////										 num_read_bytes,
////////////										 readDataBuffer );
////////////
////////////	if (1)//ret_code)
////////////	{
////////////		__dsm_read_fail_count++;
////////////
////////////		if (DSM_halt_exec_on_error)
////////////		{
////////////			printf("###DSM_ERROR### - calling DSM_read_I2C_buffer\n");
////////////			printf("return value : %d\n",ret_code);
////////////			printf("params : \n");
////////////			printf("\t\t DSM_context : %d\n",DSM_context);
////////////			printf("\t\t address : 0x%04X\n",address);
////////////			printf("\t\t num_read_bytes : %d\n",num_read_bytes);
////////////			printf("\t\t readDataBuffer :\n");
////////////			for(i=0; i<num_read_bytes; i++)
////////////				printf("\t\t\t%d\t0x%02X\n",i,readDataBuffer[i]);
////////////		}
////////////	}
////////////	else
////////////	{
////////////		__dsm_read_pass_count++;
////////////	}
////////////
////////////	return(ret_code);
////////////}
////////HL new added I2C Write function.
//////void DSM_I2C_Write2(uint8_t reg_addr, uint8_t lower_byte, uint8_t upper_byte,  int is_it_word)
//////{
//////
//////	uint16_t address = 0x00;	
//////	uint8_t num_read_bytes = 2;
//////	uint8_t readDataBuffer[20];
//////	uint8_t writeDataBuffer[20];
//////	int i = 0, ret_code = 0;
//////
//////	for(i=0;i<20;i++)
//////	{
//////		readDataBuffer[i] = 0x00;
//////		writeDataBuffer[i] = 0x00;
//////	}
//////
//////		if(is_it_word == 0)
//////		{		
//////			address = 0x00;
//////			writeDataBuffer[0] = reg_addr;  
//////			writeDataBuffer[1] = lower_byte;
//////			num_read_bytes = 2;
//////	
//////		}
//////		else
//////		{		
//////			writeDataBuffer[0] = reg_addr;	
//////			writeDataBuffer[1] = lower_byte;	
//////			writeDataBuffer[2] = upper_byte; 
//////			num_read_bytes = 3;
//////		
//////		}
//////
//////		ret_code = DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );
//////
//////		//Sometimes, DSM doesn't write correctly the first time.  Not sure why!
//////		if(ret_code)
//////		{
//////			DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );
//////		}
//////
//////}

void DSM_I2C_Pri_SREG0_0x7070()
{
		//Get ready for any data to move to read address 0x00
		DSM_I2C_Pri_Write('w', 0x00, 0x7070);
}

void DSM_I2C_SREG0_0x7070()
{
		//Get ready for any data to move to read address 0x00
		DSM_I2C_Write('w', 0x00, 0x7070);
}

uint16_t DSM_I2C_Read(uint8_t reg_addr)
{
	/*Procedure:
		DSM_I2C_Write('w', reg_addr, 0x0000);	//write register address
	*/
	
	uint16_t address = 0x00;	
	uint8_t num_read_bytes = 2;
	uint8_t readDataBuffer[20];
	uint8_t writeDataBuffer[20];
	uint16_t ret_value = 0;
	int i = 0, ret_code = 0;

	for(i=0;i<20;i++)
	{
		readDataBuffer[i] = 0x00;
		writeDataBuffer[i] = 0x00;
	}

	//Loading content of desired reading reg to temporarily holding reg.
	DSM_I2C_Write('w', reg_addr, 0x0000);

	address = 0x00;

	readDataBuffer[0] = 0x00;		//Reg Address
	readDataBuffer[1] = 0x00;		//Hi Byte of the Register address
	readDataBuffer[2] = 0x00;		//Lo Byte of the Register address
	num_read_bytes = 3;
	DSM_read_I2C_buffer(0, address, num_read_bytes, readDataBuffer);

	//Ignore Buffer[0], treat Buffer[2] as Low Byte and Buffer[1] as upper Byte
	//Need to discuss with Dale later.
	if(g_Debug)
		{
			//printf("\t\t DSM_context : %d\n",						DSM_CONTEXT);
			printf("\t\t Read ID Address \t: 0x%04X\n",   address);
			//printf("\t\t Read Address : 0x%04X\n",		reg_addr);
			//printf("\t\t Read Num_read_bytes : %d\n",	num_read_bytes);
			printf("\t\t Read DataBuffer :\n");
			for(i=0; i<num_read_bytes; i++)
			{
				//if(i==0)	printf("\t\t\tBuffer[%d]\t0x%02X\tSlave Data\n",i,readDataBuffer[i]);
				if(i==1)	printf("\t\t\tBuffer[%d]\t0x%02X\tHi Byte Data\n",i,readDataBuffer[i]);
				if(i==2)	printf("\t\t\tBuffer[%d]\t0x%02X\tLo Byte Data\n",i,readDataBuffer[i]);
				//if(i==3)	printf("\t\t\tBuffer[%d]\t0x%02X\tHi Byte Data\n",i,readDataBuffer[i]);
			}
			printf("\n");
		}


	ret_value = (uint16_t)readDataBuffer[1];
	ret_value = ret_value << 8;
	ret_value = ret_value + readDataBuffer[2];

	g_LowerByte = readDataBuffer[2];

	return (ret_value);

}

void DSM_I2C_Pri_Read(uint8_t reg_addr)
{

	uint16_t address = 0x00;	
	uint8_t num_read_bytes = 2;
	uint8_t readDataBuffer[20];
	uint8_t writeDataBuffer[20];
	int i = 0, ret_code = 0;

	for(i=0;i<20;i++)
	{
		readDataBuffer[i] = 0x00;
		writeDataBuffer[i] = 0x00;
	}

	//Loading content of desired reading reg to temporarily holding reg.
	DSM_I2C_Pri_Write('w', reg_addr, 0x0000);


	//address = 0x1D;
	address = 0x00;

	//readDataBuffer[0] = 0x00;	//Reg Address
	readDataBuffer[0] = 0x00;		//Lo Byte of the Register address
	readDataBuffer[1] = 0x00;		//Hi Byte of the Register address
	num_read_bytes = 2;
	DSM_read_I2C_buffer(0, address, num_read_bytes, readDataBuffer);

	//Ignore Buffer[0], treat Buffer[2] as Low Byte and Buffer[1] as upper Byte
	//Need to discuss with Dale later.
	if(g_Debug)
		{
			//printf("\t\t DSM_context : %d\n",						DSM_CONTEXT);
			printf("\t\t Read ID Address \t: 0x%04X\n",   address);
			//printf("\t\t Read Address : 0x%04X\n",		reg_addr);
			//printf("\t\t Read Num_read_bytes : %d\n",	num_read_bytes);
			printf("\t\t Read DataBuffer :\n");
			for(i=0; i<num_read_bytes; i++)
			{
				if(i==0)	printf("\t\t\tBuffer[%d]\t0x%02X\tLo Byte Data\n",i,readDataBuffer[i]);
				if(i==1)	printf("\t\t\tBuffer[%d]\t0x%02X\tHi Byte Data\n",i,readDataBuffer[i]);
			}
			printf("\n");
		}

}


//HL new added I2C Write function.
void DSM_I2C_Write(char byte_or_word, uint8_t reg_addr, uint16_t word_entered)
{
	/*Procedure
		- Determine if you want to write 'b' Byte or 'w' Word.  If 'b' come in, set num_read_bytes = 2 else 3.
		- DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );
			* address			= reg_addr coming in
			* writeDataBuffer	= word_entered
	*/
	uint16_t address = 0x00;	
	uint8_t num_read_bytes = 2;
	uint8_t writeDataBuffer[20];
	int i = 0, ret_code = 0;



	for(i=0;i<20;i++)
	{
		writeDataBuffer[i] = 0x00;
	}


	
		if(byte_or_word == 'b')
		{		
			address = 0x00;
			writeDataBuffer[0] = reg_addr;  
			writeDataBuffer[1] = (uint8_t) (word_entered & 0x00FF);
			num_read_bytes = 2;
	
		}
		else
		{		
			writeDataBuffer[0] = reg_addr;	
			writeDataBuffer[1] = (uint8_t) (word_entered & 0x00FF);	
			writeDataBuffer[2] = (uint8_t) ((word_entered>>8) & 0x00FF);
			num_read_bytes = 3;
		
		}

		ret_code = DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );

		//Sometimes, DSM doesn't write correctly the first time.  Not sure why!
		if(ret_code)
		{
			DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );
			printf("ret_code active.  DSM write again\n");
		}



		if(g_Debug)
		{
			//printf("\t\t DSM_context : %d\n",   DSM_CONTEXT);
			printf("\t\t Write ID Address \t: 0x%04X\n",       address);
			//printf("\t\t Write Reg Address \t: 0x%04X\n",   reg_addr);
			//printf("\t\t Write Num_read_bytes \t: %d\n",    num_read_bytes);
			//printf("\t\t WriteDataBuffer0:\t%d\t0x%02X\tRegister Address\n",0,writeDataBuffer[0]);
			//printf("\t\t WriteDataBuffer1:\t%d\t0x%02X\tLo Byte Data\n",1,writeDataBuffer[1]);
			//printf("\t\t WriteDataBuffer2:\t%d\t0x%02X\tHi Byte Data\n",2,writeDataBuffer[2]);
			printf("\t\t WriteDataBuffer :\n");
			for(i=0; i<num_read_bytes; i++)
			{
				if(i==0)	printf("\t\t\tBuffer[%d]\t0x%02X\tRegister Address\n",i,writeDataBuffer[i]);
				if(i==1)	printf("\t\t\tBuffer[%d]\t0x%02X\tLo Byte Data\n",i,writeDataBuffer[i]);
				if(i==2)	printf("\t\t\tBuffer[%d]\t0x%02X\tHi Byte Data\n",i,writeDataBuffer[i]);
			}
			printf("\n");
		}

}

void DSM_I2C_Pri_Write(char byte_or_word, uint8_t reg_addr, uint16_t word_entered)
{

	uint16_t address = 0x1C;	
	uint8_t num_read_bytes = 2;
	uint8_t writeDataBuffer[20];
	int i = 0, ret_code = 0;



	for(i=0;i<20;i++)
	{
		writeDataBuffer[i] = 0x00;
	}


	
		if(byte_or_word == 'b')
		{		
			writeDataBuffer[0] = reg_addr;  
			writeDataBuffer[1] = (uint8_t) (word_entered & 0x00FF);
			num_read_bytes = 2;
	
		}
		else
		{		
			writeDataBuffer[0] = reg_addr;	
			writeDataBuffer[1] = (uint8_t) (word_entered & 0x00FF);	
			writeDataBuffer[2] = (uint8_t) ((word_entered>>8) & 0x00FF);
			num_read_bytes = 3;
		
		}

		ret_code = DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );

		//Sometimes, DSM doesn't write correctly the first time.  Not sure why!
		if(ret_code)
		{
			DSM_write_I2C_buffer(DSM_CONTEXT, address, num_read_bytes, writeDataBuffer );
			printf("ret_code active.  DSM write again\n");
		}



		if(g_Debug)
		{
			//printf("\t\t DSM_context : %d\n",   DSM_CONTEXT);
			printf("\t\t Write ID Address \t: 0x%04X\n",       address);
			//printf("\t\t Write Reg Address \t: 0x%04X\n",   reg_addr);
			//printf("\t\t Write Num_read_bytes \t: %d\n",    num_read_bytes);
			//printf("\t\t WriteDataBuffer0:\t%d\t0x%02X\tRegister Address\n",0,writeDataBuffer[0]);
			//printf("\t\t WriteDataBuffer1:\t%d\t0x%02X\tLo Byte Data\n",1,writeDataBuffer[1]);
			//printf("\t\t WriteDataBuffer2:\t%d\t0x%02X\tHi Byte Data\n",2,writeDataBuffer[2]);
			printf("\t\t WriteDataBuffer :\n");
			for(i=0; i<num_read_bytes; i++)
			{
				if(i==0)	printf("\t\t\tBuffer[%d]\t0x%02X\tRegister Address\n",i,writeDataBuffer[i]);
				if(i==1)	printf("\t\t\tBuffer[%d]\t0x%02X\tLo Byte Data\n",i,writeDataBuffer[i]);
				if(i==2)	printf("\t\t\tBuffer[%d]\t0x%02X\tHi Byte Data\n",i,writeDataBuffer[i]);
			}
			printf("\n");
		}

}

void End_EEprom_Erase_Secondary()
{
	//	i.	 0x00 0x5C write 0x00
	//	ii.	 VR set to 15V (optional)
	//	iii. 0x00 0x44 write 0x00 0x00 --> bring internal supply back to 5V from 7V
		DSM_I2C_Write('b', g_EEP_CMD, 0x00);					
		VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE);	
		delay(5);
		DSM_I2C_Write('w', g_ANA_CTRL_0, 0x0000);					
}

void Analog_TM_Enable_Primary()
{
	//0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
	//DSM_I2C_Pri_Write('b', 0x40, 0x02);	//0x1C Slave Address
	DSM_I2C_Write('b', 0x40, 0x02);		//0x00 Slave Address
}

void Analog_TM_Enable_Secondary()
{
	//0x00 0x5E write 0x16 0x20
	DSM_I2C_Write('w', g_TM_EN, 0x2016);
	//0x00 0x5E write 0x34 0x12
	DSM_I2C_Write('w', g_TM_EN, 0x1234);	
}


void Hardware_Check_Binno()
{
	/*
		Checking if Mux20 is working properly
			1. Init Mux20 so all relays are open
			2. Close relay K_OVI3_3 to R_Mux(1k) to MUX20_8_1
			3. Close relay MUX_8_GND
			4. Force 1V/2mA from ovi-3-3
			5. Measure and expect 1mA
			6. Open relay MUX_8_1 and measure/expect 0A since MUX_8_1 is open
			7. Open relay MUX_8_GND and Close relay MUX_8_1.  Ovi-3-3 measure/expect 0A.
			8. Close all of the MUX banks to check all MUX GNDs one at a time.
			9. Close relay MUX_2_GND measure and expect 1mA
			10. Open relay MUX_2_GND measure and expect 0A
			11. Close relay MUX_4_GND measure and expect 1mA
			12. Open relay MUX_4_GND measure and expect 0A
			13. Close relay MUX_6_GND measure and expect 1mA
			14. Open relay MUX_6_GND measure and expect 0A
			15. Close relay MUX_7_GND measure and expect 1mA
			16. Open relay MUX_7_GND measure and expect 0A
			17. Check all 4 relays from all 8 banks
			18. Force 10V/3mA on ovi-3-3
			19. Close mux relays 1 at a time and measure current from OVI to see how much current there is.  
			20. Expect -2mA when close.
			21. Expect 0A when open.
			22. Pop-up error messages per failure and indicate the failure.
	*/

	float	iMeas_Hi=0,
			iMeas_Lo=0;

	//1. Init Mux20 so all relays are open
	mux_20->init();		
	delay(1);
	//2. Close relay K_OVI3_3 to R_Mux(1k) to MUX20_8_1
	mux_20->close_relay(MUX_7_GND);	
	delay(5);
	Close_relay(K_OVI3_3_LB);		
	mux_20->close_relay(MUX_8_1);
	//3. Close relay MUX_8_GND
	mux_20->close_relay(MUX_8_GND);	
	delay(5);
	//4. Force 1V/2mA from ovi-3-3
	ovi_3->set_current(OVI_CHANNEL_3, 2e-3, RANGE_3_MA);
	ovi_3->set_voltage(OVI_CHANNEL_3, 1.0, RANGE_10_V);	
	ovi_3->set_meas_mode(OVI_CHANNEL_3, OVI_MEASURE_CURRENT);
	delay(1);
	//5. Measure and expect 1mA
	iMeas_Hi = ovi_3->measure_average(5);
	//6. Open relay MUX_8_1 and measure/expect 0A since MUX_8_1 is open
	mux_20->open_relay(MUX_8_1);
	delay(5);
	iMeas_Lo = ovi_3->measure_average(5); 
	//7. Open relay MUX_8_GND and Close relay MUX_8_1.  Ovi-3-3 measure/expect 0A.
	mux_20->open_relay(MUX_8_GND);
	mux_20->close_relay(MUX_8_1);
	delay(5);
	iMeas_Lo = ovi_3->measure_average(5); 
	//8. Close all of the MUX banks to check all MUX GNDs one at a time.
		mux_20->close_relay(MUX_BANK_1_2);
		mux_20->close_relay(MUX_BANK_2_3);
		mux_20->close_relay(MUX_BANK_3_4);
		mux_20->close_relay(MUX_BANK_4_5);
		mux_20->close_relay(MUX_BANK_5_6);
		//mux_20->close_relay(MUX_BANK_6_7);
		//mux_20->close_relay(MUX_BANK_7_8);
		mux_20->close_relay(MUX_BANK_8_1);	//This is not really needed if BANK_7_8 is closed.

	mux_20->open_relay(MUX_7_GND);	//Need to open 7_GND here because all Banks are connected.
	//Keep in mind that the below MUX_GNDs close K_OVI3_3 as well to check out all of the MUX_GND relays.

		//9. Close relay MUX_2_GND measure and expect 1mA
		mux_20->close_relay(MUX_2_GND);
		delay(5);
		iMeas_Hi = ovi_3->measure_average(5); 
		//10. Open relay MUX_2_GND measure and expect 0A
		mux_20->open_relay(MUX_2_GND);
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 
		//11. Close relay MUX_4_GND measure and expect 1mA
		mux_20->close_relay(MUX_4_GND);
		delay(5);
		iMeas_Hi = ovi_3->measure_average(5); 
		//12. Open relay MUX_4_GND measure and expect 0A
		mux_20->open_relay(MUX_4_GND);
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 
		//13. Close relay MUX_6_GND measure and expect 1mA
		mux_20->close_relay(MUX_6_GND);
		delay(5);
		iMeas_Hi = ovi_3->measure_average(5); 
		//14. Open relay MUX_6_GND measure and expect 0A
		mux_20->open_relay(MUX_6_GND);
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 
		//15. Close relay MUX_7_GND measure and expect 1mA
		mux_20->close_relay(MUX_7_GND);
		delay(5);
		iMeas_Hi = ovi_3->measure_average(5); 
		//16. Open relay MUX_7_GND measure and expect 0A
		mux_20->open_relay(MUX_7_GND);
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

	mux_20->close_relay(MUX_7_GND);	//Bring back the K_OVI3_3 by 7_GND since we are done with the MUX_GND checks.
	delay(5);

	//17. Check all 4 relays from all 8 banks
	//18. Force 10V/3mA on ovi-3-3
	//19. Close mux relays 1 at a time and measure current from OVI to see how much current there is.  
	//20. Expect -0.9mA when close.  Current travel from 12V to K_LED,K_R,Kmux,mux-8-1,Rmux,ovi-3-3
	//21. Expect 0A when open.
	ovi_3->set_current(OVI_CHANNEL_3, 3e-3, RANGE_3_MA);	
	ovi_3->set_voltage(OVI_CHANNEL_3, 10.0, RANGE_10_V);	
	
		//Mux relays for LB (MUX_8_2/3/4, 7_2/3/4, 6_1/2/3/4, 5_1/2/3/4)
		mux_20->close_relay(MUX_8_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_8_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_8_3);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_8_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_8_4);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_8_4);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 



		mux_20->close_relay(MUX_7_2);	//Expect 0mA since MUX_7_4 for K_OVI3_3
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_7_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_7_3);	//Expect 0mA since MUX_7_4 for K_OVI3_3
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_7_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		//NO NEED TO CHECK MUX_7_4
		////mux_20->close_relay(MUX_7_4);	//Expect 0mA since MUX_7_4 for K_OVI3_3
		////delay(5);
		////iMeas_Hi = -ovi_3->measure_average(5); 
		////mux_20->open_relay(MUX_7_4);	//Expect 0A
		////delay(5);
		////iMeas_Lo = ovi_3->measure_average(5); 



		mux_20->close_relay(MUX_6_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_6_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_6_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_6_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_6_3);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_6_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_6_4);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_6_4);	//Expect 0A		
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 
		


		mux_20->close_relay(MUX_5_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_5_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_5_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_5_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_5_3);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_5_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_5_4);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_5_4);	//Expect 0A		
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 


		//K_LED AND K_R ARE NOT IN PLACE LIKE THE LOAD-BOARD FOR RIDDER-BOARD AND TEST-BLOCK
		//Set lower than 5V (4V/3mA).  Current will travel from +5V to relay inductance to Rmux to ovi-3-3
		ovi_3->set_current(OVI_CHANNEL_3, 3e-3, RANGE_3_MA);	
		ovi_3->set_voltage(OVI_CHANNEL_3, 4.0, RANGE_10_V);	
		delay(5);

		//Mux relays for RIDDER-BOARD (MUX_1_3/4, 3_1/2/4)
		Close_relay(K1_UV_RB);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		Open_relay(K1_UV_RB);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_1_4);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_1_4);	//Expect 0A		
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_3_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_3_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		Close_relay(K1_TS_RB);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		Open_relay(K1_TS_RB);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 



		//Mux relays for TB (MUX_1_1/2, 2_1/2/3/4, 3_3/4, 4_1/2)
		mux_20->close_relay(MUX_1_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_1_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_1_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_1_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_2_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_2_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_2_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_2_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_2_3);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_2_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_2_4);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_2_4);	//Expect 0A		
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_3_3);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_3_3);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_3_4);	//Expect -0.9mA		//Connects to TB_J39.pin3 and +5V to J39.pin10 for TS_COMP_INSERT_BOARD.  4th IB from IM
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5);				//I AM NOT GETTING HIGH CURRENT HERE BECAUSE THERE'S NO TS_COMP_INSERT_BOARD
		mux_20->open_relay(MUX_3_4);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 


		mux_20->close_relay(MUX_4_1);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_4_1);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

		mux_20->close_relay(MUX_4_2);	//Expect -0.9mA
		delay(5);
		iMeas_Hi = -ovi_3->measure_average(5); 
		mux_20->open_relay(MUX_4_2);	//Expect 0A
		delay(5);
		iMeas_Lo = ovi_3->measure_average(5); 

	//Open all mux-banks
		mux_20->open_relay(MUX_BANK_1_2);
		mux_20->open_relay(MUX_BANK_2_3);
		mux_20->open_relay(MUX_BANK_3_4);
		mux_20->open_relay(MUX_BANK_4_5);
		mux_20->open_relay(MUX_BANK_5_6);
		mux_20->open_relay(MUX_BANK_6_7);
		mux_20->open_relay(MUX_BANK_7_8);
		mux_20->open_relay(MUX_BANK_8_1);	
		mux_20->open_relay(MUX_8_1);	
		mux_20->open_relay(MUX_7_4);	
		delay(5);

	//OVI-3-3 set to 0V/0A
	ovi_3->set_current(OVI_CHANNEL_3, 0.0, RANGE_300_UA);	
	ovi_3->set_voltage(OVI_CHANNEL_3, 0.0, RANGE_10_V);	
	delay(5);

	//22. Pop-up error messages per failure and indicate the failure.
	


}
//HL added to convert from binary to decimal.

uint16_t Convert_BIN_2_Dec(int *WordArray)
{
	int i = 0;
	uint16_t cal_value = 0;
	float temp = 0;

	for(i=0;i<16;i++)
	{
		temp = pow(2.0, i);
		cal_value = cal_value + (WordArray[i]* temp);
	}

	return(cal_value);
}



void EEprcode_2_EEprArray(int TrimCode, int *EEpr, int Startbit)
{
	int k;
	int TrimCode_Binary;
	int TrimRange;
	int NumberTrimBits = 16;

	TrimRange = 1;
	for (k = 0; k < NumberTrimBits; k++)
		TrimRange *= 2;

	TrimCode_Binary = TrimCode;	

	int weight = 0;
	int TRIM_IT= 0;
	weight = 1;
	for (k =0; k < NumberTrimBits; k++)
	{			
		TRIM_IT = TrimCode_Binary & weight;
		weight *= 2;
		
		if (TRIM_IT > 0)		
		{
			g_S_EEpromTemp[k] = 1;
		}	
		else
		{
			g_S_EEpromTemp[k] = 0;
		}		
	}
	
	for(k=0;k<NumberTrimBits;k++)
	{
		EEpr[k+Startbit] = g_S_EEpromTemp[k];
	}

}

void TrimCode_To_TrimBit(short TrimCode, char TrimParam[30], char p_or_s)
{
	//This function updates the trimcode to the correct global register bits and store it for use through out entire program.

	int k;
	short TrimCode_Binary;
	int   TrimRange;
	
	int   StartingBit = 0;
	int   NumberTrimBits = 0;
	float ITRIM = 0;

	if(p_or_s == 's')
	{
			//Trim Program
			if(!strnicmp("SI_ID_S", TrimParam, 99 )) 		
			{
				StartingBit    = 0;
				NumberTrimBits = 7;
			}
			else if(!strnicmp( "tsstart_S", TrimParam, 99 )) 	
			{
				StartingBit    = 8;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "tfbOptions_S", TrimParam, 99 )) 	
			{
				StartingBit    = 10;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "Bfreq_S", TrimParam, 99 )) 	
			{
				StartingBit    = 12;
				NumberTrimBits = 3;
			}
			else if(!strnicmp( "DOPL_S", TrimParam, 99 )) 	
			{
				StartingBit    = 15;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "TvrOption_S", TrimParam, 99 )) 	
			{
				StartingBit    = 16;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "TenCP_S", TrimParam, 99 )) 	
			{
				StartingBit    = 18;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ZffOption_S", TrimParam, 99 )) 	
			{
				StartingBit    = 19;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "DsblJitDim_S", TrimParam, 99 )) 	
			{
				StartingBit    = 21;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "JitterOff_S", TrimParam, 99 )) 	
			{	
				StartingBit    = 22;
				NumberTrimBits = 1;			
			}
			else if(!strnicmp( "CP_S", TrimParam, 99 ))
			{
				StartingBit    = 23;
				NumberTrimBits = 4;			
			}
			else if(!strnicmp( "VDDA_S", TrimParam, 99 )) 	
			{
						
				StartingBit    = 27;
				NumberTrimBits = 2;		
				
			}
			else if(!strnicmp( "ZTMBstr_0_S", TrimParam, 99 )) 	
			{
				StartingBit    = 29;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ZTMBstr_1_S", TrimParam, 99 )) 	
			{
				StartingBit    = 30;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "DsblFlBck_S", TrimParam, 99 )) 	
			{
				StartingBit    = 31;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "CCOffset_S", TrimParam, 99 )) 	
			{
				StartingBit    = 32;
				NumberTrimBits = 3;
			}
			else if(!strnicmp( "ccPFOFF_S", TrimParam, 99 )) 	
			{
				StartingBit    = 35;
				NumberTrimBits = 3;
			}
			else if(!strnicmp( "CV_S", TrimParam, 99 )) 	
			{
				StartingBit    = 38;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "VbILimit_S", TrimParam, 99 )) 	
			{
				StartingBit    = 42;
				NumberTrimBits = 5;
			}
			else if(!strnicmp( "DimTH_S", TrimParam, 99 )) 	
			{
				StartingBit    = 47;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "VADC_S", TrimParam, 99 )) 	
			{
				StartingBit    = 48;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "VccRef_S", TrimParam, 99 )) 	
			{
				StartingBit    = 52;
				NumberTrimBits = 5;
			}
			else if(!strnicmp( "ZTtime_S", TrimParam, 99 )) 	
			{
				StartingBit    = 57;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "tHrBtOpt_S", TrimParam, 99 )) 	
			{
				StartingBit    = 61;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "CP_NonI2C_S", TrimParam, 99 )) 	
			{
				StartingBit    = 62;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ZEE_50KStr_S", TrimParam, 99 )) 	
			{
				StartingBit    = 63;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "Fosc_S", TrimParam, 99 )) 	
			{
				StartingBit    = 64;
				NumberTrimBits = 6;
			}
			else if(!strnicmp( "Clock1M_S", TrimParam, 99 )) 	
			{
				StartingBit    = 70;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "FlBck_Ccopt_S", TrimParam, 99 )) 	
			{
				StartingBit    = 74;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "FlBck_Sel_S", TrimParam, 99 )) 	
			{
				StartingBit    = 75;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "IRSET_S", TrimParam, 99 )) 	
			{
				StartingBit    = 76;
				NumberTrimBits = 4;
			}

			TrimRange = 1;
			for (k = 0; k < NumberTrimBits; k++)
				TrimRange *= 2;

			if (TrimCode < 0)
				TrimCode_Binary = TrimCode + TrimRange;
			else
				TrimCode_Binary = TrimCode;	

			short weight;
			short TRIM_IT;
			weight = 1;
			for (k =0; k < NumberTrimBits; k++)
			{		
				ITRIM = 0;
				TRIM_IT = TrimCode_Binary & weight;
				weight *= 2;
				
				if (TRIM_IT > 0)		
				{
					g_S_TrimRegisterTemp[StartingBit+k] = 1;
				}	
				else
				{
					g_S_TrimRegisterTemp[StartingBit+k] = 0;
				}		
			}
	}
	else
	{

			//Primary conversion 
			if(!strnicmp("SI_ID_P", TrimParam, 99 )) 		
			{
				StartingBit    = 0;
				NumberTrimBits = 7;
			}
			else if(!strnicmp( "fOSC_P", TrimParam, 99 )) 	
			{
				StartingBit    = 8;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "yInter_P", TrimParam, 99 )) 	
			{
				StartingBit    = 12;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "ILIM_P", TrimParam, 99 )) 	
			{
				StartingBit    = 16;
				NumberTrimBits = 5;
			}
			else if(!strnicmp( "ArSkip_P", TrimParam, 99 )) 	
			{
				StartingBit    = 21;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ArOnT_P", TrimParam, 99 )) 	
			{
				StartingBit    = 22;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ArOffT_P", TrimParam, 99 )) 	
			{
				StartingBit    = 23;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "StrtFREQ_P", TrimParam, 99 )) 	
			{
				StartingBit    = 25;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "OnTSL_P", TrimParam, 99 )) 	
			{
				StartingBit    = 26;
				NumberTrimBits = 5;
			}
			else if(!strnicmp( "ShuntEn_P", TrimParam, 99 )) 	
			{	
				StartingBit    = 31;
				NumberTrimBits = 1;			
			}
			else if(!strnicmp( "RcvTH_P", TrimParam, 99 ))
			{
				StartingBit    = 32;
				NumberTrimBits = 3;			
			}
			else if(!strnicmp( "GanMode_P", TrimParam, 99 )) 	
			{
				StartingBit    = 35;
				NumberTrimBits = 1;		
			}
			else if(!strnicmp( "VxTrim_P", TrimParam, 99 )) 	
			{
				StartingBit    = 36;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "DrSize_P", TrimParam, 99 )) 	
			{
				StartingBit    = 41;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "AROn512_P", TrimParam, 99 )) 	
			{
				StartingBit    = 45;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "GanDLy1_P", TrimParam, 99 )) 	
			{
				StartingBit    = 46;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "IlimTc_P", TrimParam, 99 )) 	
			{
				StartingBit    = 48;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "SDTemp_P", TrimParam, 99 )) 	
			{
				StartingBit    = 52;
				NumberTrimBits = 2;
			}
			else if(!strnicmp( "DOPL_P", TrimParam, 99 )) 	
			{
				StartingBit    = 54;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "DisIlimCap_P", TrimParam, 99 )) 	
			{
				StartingBit    = 55;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "ILIMP_P", TrimParam, 99 )) 	
			{
				StartingBit    = 56;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "uVADC_P", TrimParam, 99 )) 	
			{
				StartingBit    = 57;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "StrTTFB_P", TrimParam, 99 )) 	
			{
				StartingBit    = 61;
				NumberTrimBits = 3;
			}
			else if(!strnicmp( "EndTTFB_P", TrimParam, 99 )) 	
			{
				StartingBit    = 64;
				NumberTrimBits = 3;
			}
			else if(!strnicmp( "TsADC_P", TrimParam, 99 )) 	
			{
				StartingBit    = 67;
				NumberTrimBits = 4;
			}
			else if(!strnicmp( "UV10pct_P", TrimParam, 99 )) 	
			{
				StartingBit    = 71;
				NumberTrimBits = 1;
			}
			else if(!strnicmp( "IOV_P", TrimParam, 99 )) 	
			{
				StartingBit    = 72;
				NumberTrimBits = 5;
			}
			else if(!strnicmp( "TonM_P", TrimParam, 99 )) 	
			{
				StartingBit    = 77;
				NumberTrimBits = 3;
			}

			TrimRange = 1;
			for (k = 0; k < NumberTrimBits; k++)
				TrimRange *= 2;

			if (TrimCode < 0)
				TrimCode_Binary = TrimCode + TrimRange;
			else
				TrimCode_Binary = TrimCode;	

			short weight;
			short TRIM_IT;
			weight = 1;
			for (k =0; k < NumberTrimBits; k++)
			{		
				ITRIM = 0;
				TRIM_IT = TrimCode_Binary & weight;
				weight *= 2;
				
				if (TRIM_IT > 0)		
				{
					g_TrimRegisterTemp_P[StartingBit+k] = 1;
				}	
				else
				{
					g_TrimRegisterTemp_P[StartingBit+k] = 0;
				}		
			}
	}

}


void CV_Search(float &CV_minus1p5pct, float &CV_th, float &CV_plus1p5pct, float vStart, float Step_size)
{
	float vFB_Start = vStart;
	float vstep = Step_size;
	float i_HSG = 0.0;
	int exit_loop = 0;
	int loop_1 = 0;
	int loop_2 = 0;
	
	FB_ovi3->set_voltage(FB_ch, vFB_Start, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(100);
	i_HSG = HSG_ovi->measure_average(5);

	while(vFB_Start < 1.4 && exit_loop < 1)
	{
		FB_ovi3->set_voltage(FB_ch, vFB_Start, VOLT_5_RANGE);
		wait.delay_10_us(5);
		i_HSG= HSG_ovi->measure_average(5);
		if(i_HSG < 0.1e-3 && loop_1 <1)
		{
			CV_minus1p5pct = vFB_Start;
			loop_1++;
		}
		if(loop_1 > 0 && i_HSG > 2.5e-3 && loop_2 < 1)
		{
			CV_th = vFB_Start;
			loop_2++;
		}
		if(loop_2 > 0 && i_HSG < 0.1e-3)
		{
			CV_plus1p5pct = vFB_Start;
			exit_loop++;
		}
		vFB_Start = vFB_Start + vstep;
	}

}


void Load_10Khz_Pulses()
{

	Dclk_period = 1e-6;
	g_DDD_Low = 0.1; 
	g_DDD_High = 2.5; 
	
	//ddd_7->init();

	//ddd_7->ddd_set_clock_period(Dclk_period);		
	

	ddd_7->ddd_set_lo_level(g_DDD_Low);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(100);
	//ddd_7->ddd_connect_drivers();	
	//ddd_7->ddd_set_voltage_ref(1.5);
	//ddd_7->ddd_set_no_delay();


	int i, ddd_addr_start;
	float ddd_addr_length;

	//DDD_7_7 is on FW pin ==> Load 10Khz signal. 
	
	//Setup LOW for 10kHz signal (50us)//
	//50us to be low//
	//50us to be high//
	//DDD clock is set to 1us period//
	
	//Number of address required for 50us time (15% duty cycle).
	ddd_addr_length = 50e-6/g_DDD_Period;  //==>50us/1us => 50

	//Signal Low first. 
	//Start from address 0 to address 39 
	ddd_addr_start = 0;
	for(i = ddd_addr_start; i < ddd_addr_length; i++)	
	{
		ddd_7->ddd_load_pattern(i, "X0XXXXXX");		
	}

	//Signal High follows. 
	//Start from address 51 to address 100.
	ddd_addr_start = i;

	//Setup HIGH for 10kHz signal///////
	for(i = ddd_addr_start; i < ddd_addr_start+ddd_addr_length;i++)		
	{													
		ddd_7->ddd_load_pattern(i, "X1XXXXXX");
	}

	//Update start address to be used for stopping the pattern.
	ddd_addr_start = i;
	
	//g_DDD_125_Pulses_StopAddr = ddd_addr_start -1; //Not sure why subtracting by 1 in orginal code.  
	g_DDD_10Khz_Pulses_StopAddr = ddd_addr_start;  


}

void Load_100Khz_Pulses()
{

	Dclk_period = 0.1e-6;
	g_DDD_Low = 0.01; 
	g_DDD_High = 2.0; 
	
	ddd_7->init();

	ddd_7->ddd_set_clock_period(Dclk_period);		
	

	ddd_7->ddd_set_lo_level(g_DDD_Low);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(100);
	ddd_7->ddd_connect_drivers();	
	ddd_7->ddd_set_voltage_ref(1.0);
	ddd_7->ddd_set_no_delay();


	int i, ddd_addr_start;
	float ddd_addr_length;

	//DDD_7_7 is on FW pin ==> Load 10Khz signal. 
	
	//Setup LOW for 10kHz signal (50us)//
	//50us to be low//
	//50us to be high//
	//DDD clock is set to 1us period//
	
	//Number of address required for 50us time (50% duty cycle).
	ddd_addr_length = 5e-6/Dclk_period;  //==>5us/0.1us => 50

	//Signal Low first. 
	//Start from address 0 to address 50
	ddd_addr_start = 0;
	for(i = ddd_addr_start; i < ddd_addr_length; i++)	
	{
		//ddd_7->ddd_load_pattern(i, "X0XXXXXX");		
		ddd_7->ddd_load_pattern(i, "X0XXXXX0");		//cx add channel 1 for TS 100kHz
	}

	//Signal High follows. 
	//Start from address 51 to address 100.
	ddd_addr_start = i;

	//Setup HIGH for 10kHz signal///////
	for(i = ddd_addr_start; i < ddd_addr_start+ddd_addr_length;i++)		
	{													
		//ddd_7->ddd_load_pattern(i, "X1XXXXXX");
		ddd_7->ddd_load_pattern(i, "X1XXXXX1");		//cx add channel 1 for TS 100kHz
	}

	//Update start address to be used for stopping the pattern.
	ddd_addr_start = i;
	
	//g_DDD_125_Pulses_StopAddr = ddd_addr_start -1; //Not sure why subtracting by 1 in orginal code.  
	g_DDD_100Khz_Pulses_StopAddr = ddd_addr_start;  


}

void Load_30Khz_Pulses_TS()
{

	Dclk_period = 0.1e-6;
	g_DDD_Low = 0.01; 
	g_DDD_High = 2.0; 
	
	ddd_7->init();

	ddd_7->ddd_set_clock_period(Dclk_period);		
	

	ddd_7->ddd_set_lo_level(g_DDD_Low);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(100);
	ddd_7->ddd_connect_drivers();	
	ddd_7->ddd_set_voltage_ref(1.0);
	ddd_7->ddd_set_no_delay();


	int i, ddd_addr_start;
	float ddd_addr_length;

	//DDD_7_7 is on FW pin ==> Load 10Khz signal. 
	
	//Setup LOW for 10kHz signal (50us)//
	//50us to be low//
	//50us to be high//
	//DDD clock is set to 1us period//
	
	//Number of address required for 50us time (50% duty cycle).
	ddd_addr_length = 16.66e-6/Dclk_period;  //==>5us/0.1us => 50

	ddd_addr_length = (ddd_addr_length*2)*0.98;
	//Signal Low first. 
	//Start from address 0 to address 95
	ddd_addr_start = 0;
	for(i = ddd_addr_start; i < ddd_addr_length; i++)	
	{
		//ddd_7->ddd_load_pattern(i, "X0XXXXXX");		
		ddd_7->ddd_load_pattern(i, "X0XXXXX0");		//cx add channel 1 for TS 100kHz
	}

	//Signal High follows. 
	//Start from address 96 to address 100.
	ddd_addr_start = i;
	ddd_addr_length = ddd_addr_length*0.02;

	//Setup HIGH for 10kHz signal///////
	for(i = ddd_addr_start; i < ddd_addr_start+ddd_addr_length;i++)		
	{													
		//ddd_7->ddd_load_pattern(i, "X1XXXXXX");
		ddd_7->ddd_load_pattern(i, "X1XXXXX1");		//cx add channel 1 for TS 100kHz
	}

	//Update start address to be used for stopping the pattern.
	ddd_addr_start = i;
	
	//g_DDD_125_Pulses_StopAddr = ddd_addr_start -1; //Not sure why subtracting by 1 in orginal code.  
	g_DDD_100Khz_Pulses_StopAddr = ddd_addr_start;  


}

void Load_80Khz_Pulses_TS()
{

	Dclk_period = 0.1e-6;
	g_DDD_Low = 0.01; 
	g_DDD_High = 2.0; 
	
	ddd_7->init();

	ddd_7->ddd_set_clock_period(Dclk_period);		
	

	ddd_7->ddd_set_lo_level(g_DDD_Low);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(100);
	ddd_7->ddd_connect_drivers();	
	ddd_7->ddd_set_voltage_ref(1.0);
	ddd_7->ddd_set_no_delay();


	int i, ddd_addr_start;
	float ddd_addr_length;

	//DDD_7_7 is on FW pin ==> Load 10Khz signal. 
	
	//Setup LOW for 10kHz signal (50us)//
	//50us to be low//
	//50us to be high//
	//DDD clock is set to 1us period//
	
	//Number of address required for 50us time (50% duty cycle).
	ddd_addr_length = 6.25e-6/Dclk_period;  //==>5us/0.1us => 50

	ddd_addr_length = (ddd_addr_length*2)*0.98;
	//Signal Low first. 
	//Start from address 0 to address 95
	ddd_addr_start = 0;
	for(i = ddd_addr_start; i < ddd_addr_length; i++)	
	{
		//ddd_7->ddd_load_pattern(i, "X0XXXXXX");		
		ddd_7->ddd_load_pattern(i, "X0XXXXX0");		//cx add channel 1 for TS 100kHz
	}

	//Signal High follows. 
	//Start from address 96 to address 100.
	ddd_addr_start = i;
	ddd_addr_length = ddd_addr_length*0.02;

	//Setup HIGH for 10kHz signal///////
	for(i = ddd_addr_start; i < ddd_addr_start+ddd_addr_length;i++)		
	{													
		//ddd_7->ddd_load_pattern(i, "X1XXXXXX");
		ddd_7->ddd_load_pattern(i, "X1XXXXX1");		//cx add channel 1 for TS 100kHz
	}

	//Update start address to be used for stopping the pattern.
	ddd_addr_start = i;
	
	//g_DDD_125_Pulses_StopAddr = ddd_addr_start -1; //Not sure why subtracting by 1 in orginal code.  
	g_DDD_100Khz_Pulses_StopAddr = ddd_addr_start;  


}

void Load_100Khz_Pulses_TS()
{

	Dclk_period = 0.1e-6;
	g_DDD_Low = 0.01; 
	g_DDD_High = 2.0; 
	
	ddd_7->init();

	ddd_7->ddd_set_clock_period(Dclk_period);		
	

	ddd_7->ddd_set_lo_level(g_DDD_Low);
	ddd_7->ddd_set_hi_level(g_DDD_High);	
	wait.delay_10_us(100);
	ddd_7->ddd_connect_drivers();	
	ddd_7->ddd_set_voltage_ref(1.0);
	ddd_7->ddd_set_no_delay();


	int i, ddd_addr_start;
	float ddd_addr_length;

	//DDD_7_7 is on FW pin ==> Load 10Khz signal. 
	
	//Setup LOW for 10kHz signal (50us)//
	//50us to be low//
	//50us to be high//
	//DDD clock is set to 1us period//
	
	//Number of address required for 50us time (50% duty cycle).
	ddd_addr_length = 5e-6/Dclk_period;  //==>5us/0.1us => 50

	ddd_addr_length = (ddd_addr_length*2)*0.98;
	//Signal Low first. 
	//Start from address 0 to address 95
	ddd_addr_start = 0;
	for(i = ddd_addr_start; i < ddd_addr_length; i++)	
	{
		//ddd_7->ddd_load_pattern(i, "X0XXXXXX");		
		ddd_7->ddd_load_pattern(i, "X0XXXXX0");		//cx add channel 1 for TS 100kHz
	}

	//Signal High follows. 
	//Start from address 96 to address 100.
	ddd_addr_start = i;
	ddd_addr_length = ddd_addr_length*0.02;

	//Setup HIGH for 10kHz signal///////
	for(i = ddd_addr_start; i < ddd_addr_start+ddd_addr_length;i++)		
	{													
		//ddd_7->ddd_load_pattern(i, "X1XXXXXX");
		ddd_7->ddd_load_pattern(i, "X1XXXXX1");		//cx add channel 1 for TS 100kHz
	}

	//Update start address to be used for stopping the pattern.
	ddd_addr_start = i;
	
	//g_DDD_125_Pulses_StopAddr = ddd_addr_start -1; //Not sure why subtracting by 1 in orginal code.  
	g_DDD_100Khz_Pulses_StopAddr = ddd_addr_start;  


}

void Stop_10Khz_Pulses()
{
	ddd_7->ddd_stop_pattern();
}

void Stop_100Khz_Pulses()
{
	ddd_7->ddd_stop_pattern();
}
void Stop_100Khz_Pulses_TS()
{
	ddd_7->ddd_stop_pattern();
}

void Run_10Khz_Pulses()
{

	ddd_7->ddd_end_pattern(g_DDD_10Khz_Pulses_StopAddr);//Basically where the low pattern ends
	wait.delay_10_us(100);
	ddd_7->ddd_run_pattern();  //Start the 10kHz signal on FW pin.
	wait.delay_10_us(50);

}
void Run_100Khz_Pulses()
{

	ddd_7->ddd_end_pattern(g_DDD_100Khz_Pulses_StopAddr);//Basically where the low pattern ends
	wait.delay_10_us(100);
	ddd_7->ddd_run_pattern();  //Start the 10kHz signal on FW pin.
	wait.delay_10_us(50);

}

void Run_30Khz_Pulses_TS()
{

	ddd_7->ddd_end_pattern(g_DDD_100Khz_Pulses_StopAddr);//Basically where the low pattern ends
	wait.delay_10_us(100);
	ddd_7->ddd_run_pattern();  //Start the 10kHz signal on FW pin.
	wait.delay_10_us(50);

}
void Run_80Khz_Pulses_TS()
{

	ddd_7->ddd_end_pattern(g_DDD_100Khz_Pulses_StopAddr);//Basically where the low pattern ends
	wait.delay_10_us(100);
	ddd_7->ddd_run_pattern();  //Start the 10kHz signal on FW pin.
	wait.delay_10_us(50);

}void Run_100Khz_Pulses_TS()
{

	ddd_7->ddd_end_pattern(g_DDD_100Khz_Pulses_StopAddr);//Basically where the low pattern ends
	wait.delay_10_us(100);
	ddd_7->ddd_run_pattern();  //Start the 10kHz signal on FW pin.
	wait.delay_10_us(50);

}
void EEPROM_ERASE_P(float *vErase_th_P)
{
		/* Refer to TestPlan from Design "EEPROMWriteErase"

			ERASE Primary EEprom Procedure:
			----------------------------------------------------------------------------------------------------------------------
			1.  Start up I2C: Drain(0V) BPP(5V)
			2.  Analog Test Mode Enable					--> 0x00 0x40 write 0x02
			3.  Set EE comparator voltage on CFG14		--> 0x00 0x44 write 0x00 0xC0	(for ERASE)
			4.  Observe EE comparator on Vpin			--> 0x00 0x46 write 0x44 0xF8
			5.  Write EEprom Erase command				--> 0x00 0x5C write 0x03		(for ERASE)
			6.  release Vpin(SDA) for observation		--> 0x00 0x4E write 0x01
			7.  set vBPP=7V, vDrain > 24V for Erase.  Ramp vDrain > 24V until Vpin go from Low to High.  Set Drain(0V) BPP(5V)
			8.  regain I2C control by taking TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
			9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
		*/
		
		Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
		DSM_I2C_Write('w', 0x44, 0xC000);	//3.  write CFG14 (ANA_CTRL0) enable EE comparator erase voltage
		DSM_I2C_Write('w', 0x46, 0xF844);	//4.  write to ANA_CTRL0 to enable CFGs for VPIN observe, select EE comparator signal, and set I2C password
		DSM_I2C_Write('b', 0x5C, 0x03);	//5.  Write EEprom Erase command			
		DSM_I2C_Write('b', 0x4E, 0x01);	//6.  release Vpin(SDA) for observation	--> 0x00 0x4E write 0x01
			//TEST to observe Vpin here (cx observed Vpin drop to 1V at ATE.  drop to <0.5V at Bench)

		//////7. set vBPP=7V, vDrain > 24V for Erase.  Ramp vDrain > 24V until Vpin go from Low to High.  Set Drain(0V) BPP(5V)
			BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
			BPP_dvi->set_voltage(BPP_ch, 7.0, VOLT_10_RANGE); 
			wait.delay_10_us(10);
			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
			D_dvi->set_voltage(D_ch, 22.0, VOLT_50_RANGE); 
			wait.delay_10_us(10);

			UV_dvi->set_current(UV_ch, 1e-9, RANGE_300_UA);	//set really low current for Vmeas
			UV_dvi->set_voltage(UV_ch, g_vDSM_pullup_P, VOLT_5_RANGE); 
			UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_VOLTAGE);
			wait.delay_10_us(20);

			float vD_set, vVpin;
			vD_set	= 22;
			vVpin	= 0;
			while (vD_set < 28)
			{
				vD_set += 0.1;
				D_dvi->set_voltage(D_ch, vD_set, VOLT_50_RANGE); 
				wait.delay_10_us(10);
				vVpin = UV_dvi->measure_average(5);
//				if(vVpin > 1.5) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V with Vpullup_P=3.3V)
				if(vVpin > 2.0) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V with Vpullup_P=3.3V)
				{
					g_vDrain_Erase_th_P = vD_set+1;  //cx observed that with Vpullup_P = 4.0V, it does not work.
					D_dvi->set_voltage(D_ch, g_vDrain_Erase_th_P, VOLT_50_RANGE); 
					delay(5);
					break;                       //HL added 1V to the vDrain_Erase voltage.
				}
			}
			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); 
			wait.delay_10_us(10);
			BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
			wait.delay_10_us(10);

			//Disable DSM I2C (Any I2C write command will bring back I2C)
			DSM_set_I2C_timeout(0, 1);
			DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

		//8.  regain I2C control by taking TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
			TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE); 
			delay(1);
			TS_ovi3->set_voltage(TSovi3_ch, g_vDSM_pullup_P, VOLT_5_RANGE); 
			wait.delay_10_us(10);
			UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
			wait.delay_10_us(10);


		//9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
		DSM_I2C_Write('b', 0x5C, 0x00);	//Vpin stays low until the "READ EEPROM" command issue.  I2C regain control

		//BPP cycle has to happen in order for ERASE to reflect
		BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 
		delay(1);
		BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
		delay(1);
}

void EEPROM_BURN_P(float *vBurn_th_P)
{
	DSM_I2C_Write('b', 0x5C, 0x01);	//8.  write "WRITE EEPROM"
	DSM_I2C_Write('b', 0x4E, 0x01);	//9.  release Vpin(SDA) for observation	

	//10. set vBPP=7V, vDrain > 18V for Erase.  Ramp vDrain > 18V until Vpin go from Low to High.  Set BPP(5V) Drain(0V)
		BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
		BPP_dvi->set_voltage(BPP_ch, 7.0, VOLT_10_RANGE); 
		wait.delay_10_us(10);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 16.0, VOLT_50_RANGE); 
		wait.delay_10_us(10);

		UV_dvi->set_current(UV_ch, 1e-9, RANGE_300_UA);	//set really low current for Vmeas
		UV_dvi->set_voltage(UV_ch, g_vDSM_pullup_P, VOLT_5_RANGE); 
		UV_dvi->set_meas_mode(UV_ch, DVI_MEASURE_VOLTAGE);
		wait.delay_10_us(20);

		float vD_set, vVpin;
		vD_set	= 16;
		vVpin	= 0;
		while (vD_set < 21)
		{
			vD_set += 0.1;
			D_dvi->set_voltage(D_ch, vD_set, VOLT_50_RANGE); 
			wait.delay_10_us(10);
			vVpin = UV_dvi->measure_average(5);
			//if(vVpin > 1.5) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V)
			if(vVpin > 2.0) //exit while loop  (cx observed Vpin change state from ~1V to 2.3V)
			{
				g_vDrain_Burn_th_P = vD_set+0.2;
				*vBurn_th_P = g_vDrain_Burn_th_P;
				D_dvi->set_voltage(D_ch, g_vDrain_Burn_th_P, VOLT_50_RANGE);
				delay(5);
				break;
			}
			else
			{
				g_vDrain_Burn_th_P = -99;
				*vBurn_th_P = g_vDrain_Burn_th_P;
			}
		}

		D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE); 
		wait.delay_10_us(10);
		BPP_dvi->set_voltage(BPP_ch, 5.0, VOLT_10_RANGE); 
		wait.delay_10_us(10);

		//Disable DSM I2C (Any I2C write command will bring back I2C)
		//DSM_set_I2C_timeout(0, 1);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	//11. regain I2C control by bringing TSPIN to 0V and set TSPIN back to 3.3V after regain I2C control
		TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_5_RANGE); 
		delay(1);
		TS_ovi3->set_voltage(TSovi3_ch, g_vDSM_pullup_P, VOLT_5_RANGE); 
		wait.delay_10_us(10);
		UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
		wait.delay_10_us(10);


	//9.  write "READ EEPROM" to end ERASE		--> 0x00 0x5C write 0x00
	//    HL needed.  Or the 1st readback is invalid.
	DSM_I2C_Write('b', 0x5C, 0x00);	//Vpin stays low until the "READ EEPROM" command issue.  I2C regain control
}

void EEPROM_Write_Enable_P()
{
	//HL-PowerDown.  This is observed from design bench.  
	//SDA(Vpin), SCLK(TS) & reset TS & Vpin current.
	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
	UV_dvi->set_voltage(UV_ch,		0.0, VOLT_10_RANGE); // DVI_21_1
	delay(1);

	TS_ovi3->set_voltage(TSovi3_ch, g_vDSM_pullup_P, VOLT_10_RANGE); // OVI_3_0
	UV_dvi->set_voltage(UV_ch,		g_vDSM_pullup_P, VOLT_10_RANGE); // DVI_21_1
	delay(1);

	DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

	Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
	DSM_I2C_Write('w', 0x44, 0x4000);	//3.  Set EE comparator voltage on CFG14
	DSM_I2C_Write('w', 0x46, 0xF844);	//4.  write to ANA_CTRL0 to enable CFGs for VPIN observe, select EE comparator signal, and set I2C password

	//HL. Do not execute Write EEProm before sending in the pattern or will reading all 0 instead. 
	//DSM_I2C_Write2('b', 0x5C, 0x01);	//8.  write "WRITE EEPROM"  <<===== DONT DO IT!!!!! It won't write.
}

void EEPROM_Read_Enable_P()
{
	Analog_TM_Enable_Primary();			//2.  Analog Test Mode Enable	-->	0x00 0x40 write 0x02 --> TM_CTRL, enable analog mode
	//DSM_I2C_Write('w', 0x46, 0x2804);	//write I2C password.  After zigzag and stay in I2C
	//DSM_I2C_Write('w', 0x44, 0x4000);	//3.  Set EE comparator voltage on CFG14	//per DE

	DSM_I2C_SREG0_0x7070();	//Get ready for any data to move to read address 0x00
}

void PowerUp_I2C_P()
{
	//BPP to 5.0V first.
	float j = 0.0;
	while(j<=g_vDSM_pullup_P)
	{
		BPP_dvi->set_voltage(BPP_ch, j, VOLT_10_RANGE); // DVI_11_1
		if(j >=g_vDSM_pullup_P)
		{
			TS_ovi3->set_voltage(TSovi3_ch, g_vDSM_pullup_P, VOLT_10_RANGE); // OVI_3_0
			UV_dvi->set_voltage(UV_ch,		g_vDSM_pullup_P, VOLT_10_RANGE); // DVI_21_1
		}
		j=j+1;
	}
	BPP_dvi->set_voltage(BPP_ch, 5, VOLT_10_RANGE); // DVI_11_1
	wait.delay_10_us(10);

	//Set pullup voltage at TS @ UV pins.
	TS_ovi3->set_voltage(TSovi3_ch, g_vDSM_pullup_P, VOLT_10_RANGE); // OVI_3_0

	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_voltage(UV_ch, g_vDSM_pullup_P, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(5);
}

void DSM_init_LYT8()
{
	DSM_init(DSM_CONTEXT); //only call at start of lot
	DSM_version(); //1.5
	DSM_firmware(DSM_CONTEXT); //1.5
	//DSM_set_vector_clock_freq(DSM_CONTEXT, 1200);//Freq in kHZ
	DSM_set_I2C_clock_freq(DSM_CONTEXT, 100);
	DSM_set_drv_comp(DSM_CONTEXT,DRV_COMP_ALL,	2.5); 
	DSM_set_high_level(DSM_CONTEXT,		ALL_CH, 5);	//DOUT high levels						     
	DSM_set_low_level(DSM_CONTEXT,		ALL_CH, 0);
	DSM_set_voltage_ref(DSM_CONTEXT,	ALL_CH, 2.0);
	DSM_set_voltage_I2C(DSM_CONTEXT,			g_vDSM_pullup_P);
	DSM_enable_outputs(DSM_CONTEXT, NONE_CH);       //Disable outputs
	DSM_enable_open_drain(DSM_CONTEXT, NONE_CH);    //Disable Open Drain
	DSM_set_no_delay(DSM_CONTEXT);            //Set 0 second delay	
}

float Average_Value(float *Meas_Array)
{
	int i = 0;
	float tmeas = 0;

	//Eliminate invalid measurements (less than 1e-6 due to noise or greater 2e-6 due missing second positive edge)
	for(i=0; i<15;i++)
	{
		if(Meas_Array[i] < 1e-6 || Meas_Array[i] > 2e-6)
		{
			Meas_Array[i] = 0;
		}
	}

	//Calculate average from valid data points.
	for(i=0;i<15;i++)
	{
		if(Meas_Array[i] > 0)
		{
			tmeas = 0.5*(tmeas + Meas_Array[i]);
		}
	}

	return(tmeas);
	
}

void Setup_Resources_for_I2C_P()
{
	//Drain = 0V
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
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
	Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
	Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
	//Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
	//Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
	//Connect DSM CLK & Data to primary pins: TS & UV
	Close_relay(K1_DSM_TB);	
	Close_relay(K3_DSM_TB);	
	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	//Close_relay(K1_DSM_TB);	
	//Close_relay(K3_DSM_TB);
	//Open_relay(K2_DSM_TB);
	//Open_relay(K4_DSM_TB);
	delay(5);
	////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void Power_Down_I2C_P()
{
	//SDA = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_10_RANGE); // OVI_3_0

	//SCL = 3.3V via pullup resistor. Ready for I2C.
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(20);
	dvi_9->set_current(DVI_CHANNEL_1, 30e-3, RANGE_300_MA);
	dvi_9->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE); // DVI_11_1
	wait.delay_10_us(20);

	Open_relay(K2_DSM_TB);
	Open_relay(K4_DSM_TB);
	delay(4);

	//Set pullup voltage at TS @ UV pins.
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); // OVI_3_0
	//UV = 0V via pullup resistor. Ready for I2C.
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(10);

	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); // DVI_11_1
	wait.delay_10_us(10);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE); // DVI_11_0
	wait.delay_10_us(20);

	Open_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
	Open_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
	
	//Disconnect DSM from Primary.
	Open_relay(K1_DSM_TB);	
	Open_relay(K3_DSM_TB);	
	delay(1);
}


void PowerUp_I2C_S()
{
	//Drain = 0V
	D_dvi->set_current(D_ch, 100e-3, RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, VOLT_2_RANGE); 
	//BPP = 0V
	BPP_dvi->set_current(BPP_ch, 300e-3, RANGE_300_MA);
	BPP_dvi->set_voltage(BPP_ch, 0.0, VOLT_10_RANGE); 

	//TS = 0V 
	TS_ovi3->set_current(TSovi3_ch, 30e-3, RANGE_30_MA);
	TS_ovi3->set_voltage(TSovi3_ch, 0.0, VOLT_10_RANGE); 
	//UV = 0V 
	UV_dvi->set_current(UV_ch, 300e-3, RANGE_300_MA);
	UV_dvi->set_voltage(UV_ch, 0.0, VOLT_10_RANGE);

	//-----------------------------------------------------------------------------------------------------------------
	//Setup Resource pins on Secondary.
	//------------------------------------------------------------------------------------------------------------------
	HSG_ovi->set_current(HSG_ch, 30e-3, RANGE_30_MA);
	HSG_ovi->set_voltage(HSG_ch, 0, VOLT_20_RANGE); 
	B_ovi3->set_current(B_ch1, 30e-3, RANGE_30_MA);
	B_ovi3->set_voltage(B_ch1, 0.0, VOLT_10_RANGE);
	FW_ovi3->set_current(FW_ch, 3e-3, RANGE_30_MA);
	FW_ovi3->set_voltage(FW_ch, 0.0, VOLT_2_RANGE); 
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 0.0, VOLT_5_RANGE); 
	IS_dvi2k->set_voltage(IS_ch, 0.0, VOLT_5_RANGE);				
	IS_dvi2k->set_current(IS_ch, 200e-3, RANGE_200_MA);
	SDA_ovi3->set_current(SDA_ch, 30e-3, RANGE_30_MA);	        
	SDA_ovi3->set_voltage(SDA_ch, 0.0, VOLT_5_RANGE); 
	SCL_ovi3->set_current(SCL_ch, 30e-3, RANGE_30_MA);				
	SCL_ovi3->set_voltage(SCL_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_5_RANGE); 
	BPS_dvi->set_current(BPS_ch, 0.0e-3, RANGE_300_MA);
	HBP_dvi2k->set_current(HBP_ch, 0.0e-6, RANGE_200_MA);
	HBP_dvi2k->set_voltage(HBP_ch, 0.0, VOLT_20_RANGE);
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	
	VR_dvi->set_voltage(VR_ch, 0.0, VOLT_5_RANGE); 
	wait.delay_10_us(50);

	//Disonnect Pullup R from TS and UV pins
	Open_relay(K1_TS_RB);
	Open_relay(K1_UV_RB);	
	//Connect Pullup R to SCL & SDA
	Close_relay(K1_SDA_SPI_TB);
	Close_relay(K1_SCL_SPI_TB);
	//Disconnect DSM CLK & Data from primary pins: TS & UV
	//Connect DSM CLK & Data to secondary:         SCL & SDA
	Open_relay(K1_DSM_TB);
	Open_relay(K3_DSM_TB);
	Close_relay(K2_DSM_TB);
	Close_relay(K4_DSM_TB);
	wait.delay_10_us(250);


	//Step 1.	vFB = 1.25V
	FB_ovi3->set_current(FB_ch, 30e-3, RANGE_30_MA);
	FB_ovi3->set_voltage(FB_ch, 1.25, VOLT_5_RANGE); // DVI_11_0
	wait.delay_10_us(10);

	//Step 2.	VR = 15V 
	VR_dvi->set_current(VR_ch, 300e-3, RANGE_300_MA);	//Require >30mA else VR -> 10V, droop, then start rising with weird ramps
	VR_dvi->set_voltage(VR_ch, 15.0, VOLT_50_RANGE); // DVI_11_1
	wait.delay_10_us(200);

	//SDA,SCL = 3.3V via pullup resistor. Ready for I2C.
	SDA_ovi3->set_voltage(SDA_ch, 3.3, VOLT_10_RANGE); // OVI_3_0
	SCL_ovi3->set_voltage(SCL_ch, 3.3, VOLT_10_RANGE); // DVI_21_1
	wait.delay_10_us(50);
}

void Search_iOVp_P(float *iOVp_th_P)
{
	//Ramp up to find iOV+ until vDrain toggle from high to low (virgin parts ~53uA)
	float	iStep,
			iSet,
			iOVp_target,
			iStart,
			iRamp[1000]={0},
			vMeas[1000]={0},
			vSet,
			vStep,
			vStart,
			vRamp[1000]={0},
			vR_600K=0;

	int		i=0,
			iOVp_count=0,
			tStep=0,
			t_us_Step=0;
	
	if(g_USE_VR_600K==true) //Using vForce indirectly control iVpin
	{
		//prevent falling into infinite loop
		iOVp_target = gP_iOVp_TARGET_Trimops;
		if(gP_iOVp_TARGET_Trimops > 100e-6)
			iOVp_target = 60e-6;

		vStep		= 62.5e-3;
		vSet		= 0.0;
		vStart		= 30;
		vMeas[0]	= 0.0;
		*iOVp_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 50;	//x10us delay per step

		UV_dvi->set_current(UV_ch, 70e-6, RANGE_300_UA);	

		//Ramp vVpin with 0.5V step from 0V to 30V
		while (vSet < vStart)	
		{
			vSet += 0.5;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			wait.delay_10_us(1);
		}

		vRamp[0] = vSet;
		i=0;
		//Ramp iVpin with vStep to find iOVp threshold until vDrain toggle from High to Low
		while (vSet < 50)
		{
			iOVp_count=i;
			vSet += vStep;
			vRamp[i] = vSet;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(50);
			if(vMeas[i] < 2.0) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				break;
			}
			i++;
		}

		//Measure using UV resouce
		*iOVp_th_P = UV_dvi->measure_average(50);

		//////Force lines could not be connected  (will cause Vpin to go low if connected)
		//dvi_9->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_DIFF);
		//dvi_9->set_diff_range(RANGE_100_V);
		//dvi_9->open_relay(CONN_FORCE0);
		//dvi_9->open_relay(CONN_FORCE1);
		//dvi_9->open_relay(CONN_SENSE0);
		//dvi_9->open_relay(CONN_SENSE1);
		//delay(1);
		//Close_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(4);

		//vR_600K = dvi_9->measure_average(5);	//diff mode measurement between 600Kohm
		//*iOVp_th_P = vR_600K/600000;

		//dvi_9->close_relay(CONN_FORCE0);
		//dvi_9->close_relay(CONN_FORCE1);
		//delay(1);
		//Open_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(1);
	}


	//iVpin Ramp observe voltage change
	if(g_USE_VR_600K==false)	
	{
		//prevent falling into infinite loop
		iOVp_target = gP_iOVp_TARGET_Trimops;
		if(gP_iOVp_TARGET_Trimops > 100e-6)
			iOVp_target = 60e-6;

		iStep		= 0.05e-6;
		iSet		= 0.0;
		iStart		= 45e-6;
		vMeas[0]	= 0.0;
		*iOVp_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 1;	//x10us delay per step

		//Ramp iVpin with 1uA step from 0A to 45uA
		while (iSet < iStart)	
		{
			iSet += 1e-6;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			wait.delay_10_us(1);
		}

		iRamp[0] = iSet;
		i=0;
		//Ramp iVpin with iStep to find iOVp threshold until vDrain toggle from High to Low
		while (iSet < iOVp_target*1.25)	//max trim up range is +20% and trim dn range is -15%
		{
			iOVp_count=i;
			iSet += iStep;
			iRamp[i] = iSet;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(25);
			if(vMeas[i] < 2.0) //exit while loop  (observed vDrain change state from 5V to 0V)
			//if(vMeas[i] > 0.5e-3) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				*iOVp_th_P = iSet;
				break;
			}
			i++;
		}
	}

	if(g_Char_iOVp_XYplot)
	{
		int j=0;
		char debug_file_name[150] ="/0"; 

		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_iOVp_iv_plot.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print iForce and vMeas
		fprintf(fpr,"iOVp vs. vDrain  tStep=%ims iStep=0.1uA\n", tStep);
		for (j=0; j<=iOVp_count;j++)
		{
			//fprintf(fpr,"iVpin = %.4f uA, vDrain = %.3f V\n",iRamp[i]*1e6,vMeas[i]);
			fprintf(fpr,"%.4f	\t%.7f \n",iRamp[j]*1e6,vMeas[j]);
		}
		fprintf(fpr,"\n");
		fclose(fpr);
	}
}

void Search_iOVm_P(float *iOVm_th_P)
{
	//Ramp up to find iOV+ until vDrain toggle from high to low (virgin parts ~53uA)
	float	iStep,
			iSet,
			iOVm_target,
			iStart,
			iRamp[1000]={0},
			vMeas[1000]={0},
			vSet,
			vStep,
			vStart,
			vRamp[1000]={0},
			vR_600K=0;

	int		i=0,
			iOVm_count=0,
			tStep=0,
			t_us_Step=0;
	
	if(g_USE_VR_600K==true) //Using vForce indirectly control iVpin
	{
		//prevent falling into infinite loop
		iOVm_target = gP_iOVm_TARGET_Trimops;
		if(gP_iOVm_TARGET_Trimops > 100e-6)
			iOVm_target = 60e-6;

		vStep		= 62.5e-3;
		vSet		= 0.0;
		vStart		= 30;
		vMeas[0]	= 0.0;
		*iOVm_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 50;	//x10us delay per step

		UV_dvi->set_current(UV_ch, 70e-6, RANGE_300_UA);	

		//Ramp vVpin with 0.5V step from 0V to 30V
		while (vSet < vStart)	
		{
			vSet += 0.5;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			wait.delay_10_us(1);
		}

		vRamp[0] = vSet;
		i=0;
		//Ramp iVpin with vStep to find iOVm threshold until vDrain toggle from High to Low
		while (vSet < 50)
		{
			iOVm_count=i;
			vSet += vStep;
			vRamp[i] = vSet;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(50);
			if(vMeas[i] < 2.0) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				break;
			}
			i++;
		}

		//Measure using UV resouce
		*iOVm_th_P = UV_dvi->measure_average(50);

		//////Force lines could not be connected  (will cause Vpin to go low if connected)
		//dvi_9->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_DIFF);
		//dvi_9->set_diff_range(RANGE_100_V);
		//dvi_9->open_relay(CONN_FORCE0);
		//dvi_9->open_relay(CONN_FORCE1);
		//dvi_9->open_relay(CONN_SENSE0);
		//dvi_9->open_relay(CONN_SENSE1);
		//delay(1);
		//Close_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(4);

		//vR_600K = dvi_9->measure_average(5);	//diff mode measurement between 600Kohm
		//*iOVm_th_P = vR_600K/600000;

		//dvi_9->close_relay(CONN_FORCE0);
		//dvi_9->close_relay(CONN_FORCE1);
		//delay(1);
		//Open_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(1);
	}


	//iVpin Ramp observe voltage change
	if(g_USE_VR_600K==false)	
	{
		iStep		= 0.05e-6;
		iSet		= 0.0;
		iStart		= g_iOVp_pt_P + 2e-6;  //start with iOVp+2uA ramp down
		vMeas[0]	= 0.0;
		*iOVm_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 1;	//x10us delay per step

		iSet		= iStart;
		iRamp[0]	= iSet;		//for XY plot variable
		i=0;
		//Ramp iVpin with iStep to find iOVm threshold until vDrain toggle from High to Low
		while( iSet > (gP_iOVm_TARGET_Trimops - 10e-6) )
		{
			iOVm_count=i;
			iSet -= iStep;
			iRamp[i] = iSet;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(25);
			if(vMeas[i] > 2.0) //exit while loop  (observed vDrain change state from 0V to 5V)
			//if(vMeas[i] > 0.5e-3) //exit while loop  (observed vDrain change state from 0V to 5V)
			{
				*iOVm_th_P = iSet;
				break;
			}
			i++;
		}
	}

	if(g_Char_iOVm_XYplot)
	{
		int j=0;
		char debug_file_name[150] ="/0"; 

		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_iOVm_iv_plot.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print iForce and vMeas
		fprintf(fpr,"iOVm vs. vDrain  tStep=%ims iStep=0.1uA\n", tStep);
		for (j=0; j<=iOVm_count;j++)
		{
			//fprintf(fpr,"iVpin = %.4f uA, vDrain = %.3f V\n",iRamp[i]*1e6,vMeas[i]);
			fprintf(fpr,"%.4f	\t%.7f \n",iRamp[j]*1e6,vMeas[j]);
		}
		fprintf(fpr,"\n");
		fclose(fpr);
	}
}

void Search_iUVp_P(float *iUVp_th_P)
{
	//Ramp up to find iUV+ until vDrain toggle from high to low (virgin parts ~53uA)
	float	iStep,
			iSet,
			iUVp_target,
			iStart,
			iRamp[500]={0},
			vMeas[500]={0},
			vSet,
			vStep,
			vStart,
			vRamp[500]={0},
			vR_600K=0;

	int		i=0,
			iUVp_count=0,
			tStep=0,
			t_us_Step=0;
	
	if(g_USE_VR_600K==true) //Using vForce indirectly control iVpin
	{
		//prevent falling into infinite loop
		iUVp_target = gP_iUVp_TARGET_Trimops;
		if(gP_iUVp_TARGET_Trimops > 100e-6)
			iUVp_target = 60e-6;

		vStep		= 62.5e-3;
		vSet		= 0.0;
		vStart		= 5;
		vMeas[0]	= 0.0;
		*iUVp_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 400;	//x10us delay per step

		UV_dvi->set_current(UV_ch, 20e-6, RANGE_300_UA);	

		//Ramp vVpin with 0.5V step from 0V to 30V
		while (vSet < vStart)	
		{
			vSet += 0.5;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			wait.delay_10_us(1);
		}

		vRamp[0] = vSet;
		i=0;
		//Ramp iVpin with vStep to find iUVp threshold until vDrain toggle from High to Low
		while (vSet < 50)
		{
			iUVp_count=i;
			vSet += vStep;
			vRamp[i] = vSet;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(50);
			if(vMeas[i] > 2.0) //exit while loop  (observed vDrain change state from 0V to 5V)
			{
				break;
			}
			i++;
		}

		//Measure using UV resouce
		*iUVp_th_P = UV_dvi->measure_average(50);

		//////Force lines could not be connected  (will cause Vpin to go low if connected)
		//dvi_9->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_DIFF);
		//dvi_9->set_diff_range(RANGE_100_V);
		//dvi_9->open_relay(CONN_FORCE0);
		//dvi_9->open_relay(CONN_FORCE1);
		//dvi_9->open_relay(CONN_SENSE0);
		//dvi_9->open_relay(CONN_SENSE1);
		//delay(1);
		//Close_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(4);

		//vR_600K = dvi_9->measure_average(5);	//diff mode measurement between 600Kohm
		//*iUVp_th_P = vR_600K/600000;

		//dvi_9->close_relay(CONN_FORCE0);
		//dvi_9->close_relay(CONN_FORCE1);
		//delay(1);
		//Open_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(1);
	}


	//iVpin Ramp observe voltage change
	if(g_USE_VR_600K==false)	
	{
		//prevent falling into infinite loop
		iUVp_target = gP_iUVp_TARGET_Trimops;
		if(gP_iUVp_TARGET_Trimops > 20e-6)
			iUVp_target = 20e-6;

		iStep		= 0.05e-6;
		iSet		= 0.0;
		iStart		= 5e-6;
		vMeas[0]	= 0.0;
		*iUVp_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 500;	//x10us delay per step

		//Ramp iVpin with 1uA step from 0A to 45uA
		while (iSet < iStart)	
		{
			iSet += 1e-6;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			wait.delay_10_us(1);
		}

		iRamp[0] = iSet;
		i=0;
		//Ramp iVpin with iStep to find iUVp threshold until vDrain toggle from Low to High
		while (iSet < iUVp_target*1.15)	//max trim range is +/-10% 
		{
			iUVp_count=i;
			iSet += iStep;
			iRamp[i] = iSet;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(30);
			if(vMeas[i] > 2.0) //exit while loop  (observed vDrain change state from Low to High)
			//if(vMeas[i] > 0.5e-3) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				*iUVp_th_P = iSet;
				break;
			}
			i++;
		}
	}

	if(g_Char_iUVp_XYplot)
	{
		int j=0;
		char debug_file_name[150] ="/0"; 

		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_iUVp_iv_plot.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print iForce and vMeas
		fprintf(fpr,"iUVp vs. vDrain  tStep=%ims iStep=0.1uA\n", tStep);
		for (j=0; j<=iUVp_count;j++)
		{
			//fprintf(fpr,"iVpin = %.4f uA, vDrain = %.3f V\n",iRamp[i]*1e6,vMeas[i]);
			fprintf(fpr,"%.4f	\t%.7f \n",iRamp[j]*1e6,vMeas[j]);
		}
		fprintf(fpr,"\n");
		fclose(fpr);
	}
}
void Search_iUVm_P(float *iUVm_th_P)
{
	//Ramp up to find iOV+ until vDrain toggle from high to low (virgin parts ~53uA)
	float	iStep,
			iSet,
			iUVm_target,
			iStart,
			iRamp[500]={0},
			vMeas[500]={0},
			vSet,
			vStep,
			vStart,
			vRamp[500]={0},
			vR_600K=0;

	int		i=0,
			iUVm_count=0,
			tStep=0,
			t_us_Step=0;
	
	if(g_USE_VR_600K==true) //Using vForce indirectly control iVpin
	{
		//prevent falling into infinite loop
		iUVm_target = gP_iUVm_TARGET_Trimops;
		if(gP_iUVm_TARGET_Trimops > 100e-6)
			iUVm_target = 60e-6;

		vStep		= 62.5e-3;
		vSet		= 0.0;
		vStart		= 30;
		vMeas[0]	= 0.0;
		*iUVm_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 50;	//x10us delay per step

		UV_dvi->set_current(UV_ch, 70e-6, RANGE_300_UA);	

		//Ramp vVpin with 0.5V step from 0V to 30V
		while (vSet < vStart)	
		{
			vSet += 0.5;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			wait.delay_10_us(1);
		}

		vRamp[0] = vSet;
		i=0;
		//Ramp iVpin with vStep to find iUVm threshold until vDrain toggle from High to Low
		while (vSet < 50)
		{
			iUVm_count=i;
			vSet += vStep;
			vRamp[i] = vSet;
			UV_dvi->set_voltage(UV_ch, vSet, VOLT_50_RANGE);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(50);
			if(vMeas[i] < 2.0) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				break;
			}
			i++;
		}

		//Measure using UV resouce
		*iUVm_th_P = UV_dvi->measure_average(50);

		//////Force lines could not be connected  (will cause Vpin to go low if connected)
		//dvi_9->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_DIFF);
		//dvi_9->set_diff_range(RANGE_100_V);
		//dvi_9->open_relay(CONN_FORCE0);
		//dvi_9->open_relay(CONN_FORCE1);
		//dvi_9->open_relay(CONN_SENSE0);
		//dvi_9->open_relay(CONN_SENSE1);
		//delay(1);
		//Close_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(4);

		//vR_600K = dvi_9->measure_average(5);	//diff mode measurement between 600Kohm
		//*iUVm_th_P = vR_600K/600000;

		//dvi_9->close_relay(CONN_FORCE0);
		//dvi_9->close_relay(CONN_FORCE1);
		//delay(1);
		//Open_relay(K2AB_VR_SPI_RB); //dvi-9-0 S "VR_600K_1" & dvi-9-1 S "VR_600K_2"
		//delay(1);
	}


	//iVpin Ramp observe voltage change
	if(g_USE_VR_600K==false)	
	{
		iStep		= 0.05e-6;
		iSet		= 0.0;
		iStart		= g_iUVp_pt_P + 2e-6;  //start with iUVp+2uA ramp down
		vMeas[0]	= 0.0;
		*iUVm_th_P	= 99.0;
		tStep		= 1;	//ms
		t_us_Step	= 1;	//x10us delay per step

		iSet		= iStart;
		iRamp[0]	= iSet;		//for XY plot variable
		i=0;
		//Ramp iVpin with iStep to find iUVm threshold until vDrain toggle from High to Low
		while( iSet > (gP_iUVm_TARGET_Trimops - 10e-6) )
		{
			iUVm_count=i;
			iSet -= iStep;
			iRamp[i] = iSet;
			UV_dvi->set_current(UV_ch, iSet, RANGE_300_UA);
			//delay(tStep);
			wait.delay_10_us(t_us_Step);
			vMeas[i] = D_dvi->measure_average(25);
			if(vMeas[i] < 2.0) //exit while loop  (observed vDrain change state from 5V to 0V)
			//if(vMeas[i] > 0.5e-3) //exit while loop  (observed vDrain change state from 5V to 0V)
			{
				*iUVm_th_P = iSet;
				break;
			}
			i++;
		}
	}

	if(g_Char_iUVm_XYplot)
	{
		int j=0;
		char debug_file_name[150] ="/0"; 

		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, g_DevName); 
		strcat (debug_file_name, "_iUVm_iv_plot.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print iForce and vMeas
		fprintf(fpr,"iUVm vs. vDrain  tStep=%ims iStep=0.1uA\n", tStep);
		for (j=0; j<=iUVm_count;j++)
		{
			//fprintf(fpr,"iVpin = %.4f uA, vDrain = %.3f V\n",iRamp[i]*1e6,vMeas[i]);
			fprintf(fpr,"%.4f	\t%.7f \n",iRamp[j]*1e6,vMeas[j]);
		}
		fprintf(fpr,"\n");
		fclose(fpr);
	}
}

void BPP_zigzag(float vBPP1, float vBPP2, float vBPP3)
{
	//vBPP1 = 5.5;
	//vBPP2 = 4.3;
	//vBPP3 = 5.4;

	//BPP zig zag (5V to 5.5V to 4.3V to 5.4V below OV threshold)
	BPP_dvi->set_voltage(BPP_ch, vBPP1, VOLT_10_RANGE); // DVI_11_1
	delay(1);
	BPP_dvi->set_voltage(BPP_ch, vBPP2, VOLT_10_RANGE); // DVI_11_1
	delay(1);
	BPP_dvi->set_voltage(BPP_ch, vBPP3, VOLT_10_RANGE); // DVI_11_1
	delay(1);
}

void Regain_I2C_P(int regain_I2C_mode)
{
	if(regain_I2C_mode == g_Vpin_Low_to_High)
	{
		UV_dvi->set_voltage(UV_ch,		0.0,	VOLT_10_RANGE); // DVI_21_1
		UV_dvi->set_current(UV_ch,		30e-3,	RANGE_300_MA);	//set really low current for Vmeas
		wait.delay_10_us(10);
		UV_dvi->set_voltage(UV_ch,		3.3,	VOLT_10_RANGE); // DVI_21_1
		wait.delay_10_us(10);
		TS_ovi3->set_voltage(TSovi3_ch, 3.3,	VOLT_10_RANGE); // OVI_3_0
		wait.delay_10_us(10);
	}
	else if(regain_I2C_mode == g_TSpin_Low_to_High)
	{
		TS_ovi3->set_voltage(TSovi3_ch, 0.0,	VOLT_10_RANGE); // OVI_3_0
		TS_ovi3->set_current(TSovi3_ch, 30e-3,	RANGE_30_MA);
		wait.delay_10_us(10);
		TS_ovi3->set_voltage(TSovi3_ch, 3.3,	VOLT_10_RANGE); // OVI_3_0
		wait.delay_10_us(10);
		UV_dvi->set_voltage(UV_ch,		3.3,	VOLT_10_RANGE); // DVI_21_1
		wait.delay_10_us(10);
	}
	//Connect relays for I2C use
		Close_relay(K1_TS_RB);	//Connect Pullup R to TS pin.
		Close_relay(K1_UV_RB);	//Connect Pullup R to UV pin.
		//Connect DSM from Primary after releasing VPIN or TS pins
		Close_relay(K1_DSM_TB);	
		Close_relay(K3_DSM_TB);	
}

void Disable_n_Disconnect_DSMI2C_via(int release_pin)
{
	if(release_pin == g_release_TSpin)
	{
		//Disable DSM I2C (Any I2C write command will bring back I2C)
		DSM_set_I2C_timeout(0, 1);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

		Open_relay(K1_TS_RB);	//disConnect Pullup R to TS pin.
		Open_relay(K1_UV_RB);	//disConnect Pullup R to UV pin.

		////Setup TSpin to directly connect to ovi-3-0 instead of pullup for vForce
		//Open_relay(K1_TS_RB);
		delay(1);
	}
	else if(release_pin == g_release_Vpin)
	{
		//Disable DSM I2C (Any I2C write command will bring back I2C)
		DSM_set_I2C_timeout(0, 1);
		DSM_set_I2C_clock_freq(DSM_CONTEXT, 300);

		//Disconnect DSM from Primary after releasing VPIN or TS pins
		Open_relay(K1_DSM_TB);	
		Open_relay(K3_DSM_TB);	
		delay(1);

		Open_relay(K1_TS_RB);	//disConnect Pullup R to TS pin.
		Open_relay(K1_UV_RB);	//disConnect Pullup R to UV pin.

		//////Setup TSpin to directly connect to ovi-3-0 instead of pullup for vForce
		////Open_relay(K1_TS_RB);
		delay(1);
	}
}