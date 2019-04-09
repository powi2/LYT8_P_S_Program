#if !defined(USER_H)
#define USER_H
//==============================================================================
// USER.H
//==============================================================================
#define STRING(x) #x
#define LINE_STRING(line_number) STRING(line_number)
#define LOCATION __FILE__"("LINE_STRING(__LINE__)")"
//Include from PI START
#include "piclasses.h"
#include "qcsample.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream> 
#include "gage_drv.h"
#include <process.h>
#include "CsStruct.h"
#include "CsPrototypes.h"
#include "CsAppSupport.h"
#include "CsTchar.h"
#include "CsSdkMisc.h"
#include "CsTypes.h"

// DSM MODULE CODE //
#include "digital_scan_module.h"
// DSM MODULE CODE //

#include "ModalDialogDescription.h"
#include "ui.h"
#include "NPMSupport.h"

using namespace std;
#ifdef NT_
#include <strstrea.h>
#include <fstream.h>
#include "M310.h"
#else
// XP //
#include <strstream>
#include <fstream>
#endif
//Include from PI END

// Include from Credence START
#include "vType.h"
#include "vVector.h"
#include "vAnyTypeSharedData.h"
#include "vISetSharedData.h"
#include "ISiteMgrPub.h"
#include "sc_status.h"
// Include from Credence END

#define CSC_SITEBASE (1)	// value must be 0 or 1
#define Pulse PIPulse

// DSM MODULE CODE //
#define DSM_CONTEXT 0
// DSM MODULE CODE //

#define Pulse PIPulse

extern ModalDialogDescription mdb;		// External class object, allocate memory. Credence function
extern int g_pid;  //Not really a global, but watch sheets need this exact name.

//{ASL_CREATE BEGIN BOARDS_FROM_LIST_PROPERTIES
// Regenerating source code will change code between here and ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive the changes to this code.
 
void board_ptr_init(void);
void board_hardware_init(void);
 
extern Ovi * ovi_1;
extern Ovi * ovi_3;
extern Pv3 * pv3_4;
extern Tmu * tmu_6;
extern Ddd * ddd_7;
extern Dvi * dvi_9;
extern Dvi * dvi_11;
extern Dvi * dvi_13;
extern Mux * mux_14;
extern Hvs * hvs_15;
extern Mux * mux_20;
extern Dvi * dvi_21;
//ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// This file must be present even if no user code is placed below

#endif

enum release_pin_mode
{
	g_release_Vpin  = 1,
	g_release_TSpin = 2,
};

enum I2C_regain_mode
{
	g_Vpin_Low_to_High  = 1,
	g_TSpin_Low_to_High = 2,
};

enum Reg_Bank
{
		E0 = 0,
		E2 = 1,
		E4 = 2,
		E6 = 3,
		E8 = 4,
};

enum relay{

	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//SPI controlled relays.
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//Bank 1
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	K1_IS_SPI_TB  = 100, //SPI1_OUT1, //SPI controlled.  To connect to IS or IS buffer ckt.
	K2_IS_SPI_IB  = 101, //SPI1_OUT2, //SPI controlled.  To connect/disconnect 100K for voltage divider in IS buffer insert ckt.
	K3_IS_SPI_IB  = 102, //SPI1_OUT3, //SPI controlled.  To connect/disconnect 2K for voltage divider in IS buffer insert ckt.
	K4_IS_SPI_IB  = 103, //SPI1_OUT4, //SPI controlled.  To connect/disconnect comparator input to GND in the IS buffer insert ckt.
	K5_IS_SPI_IB  = 104, //SPI1_OUT5, //SPI controlled.  To connect/disconnect buffer output to IS pin in the IS buffer insert ckt.
	K6_IS_SPI_IB  = 105, //SPI1_OUT6, //SPI controlled.  To connect/disconnect analog switch to either DDD7_2 or B in the Current Limit boost Insert ckt
	K1_SDA_SPI_TB = 106, //SPI1_OUT7, //SPI controlled.  To connect/disconnect OVI3_5 as Kelvin/NonKelvin to SDA pin.
	K1_SCL_SPI_TB = 107, //SPI1_OUT8, //SPI controlled.  To connect/disconnect OVI3_6 as Kelvin/NonKelvin to SCL pin.

	//--------------------------------------------------------------------------------------------------------------------------------------------------
	//Bank 2
	//--------------------------------------------------------------------------------------------------------------------------------------------------

	K1_HBP_SPI_RB = 108, //SPI2_OUT1, //SPI controlled.  To connect/disconnect HBP & FB pins.
	K1_FB_SPI_TB  = 109, //SPI2_OUT2, //SPI controlled.  To connect/disconnect OVI3_7 as Kelvin/NonKelvin to FB pin.
	K2_FB_SPI_TB  = 110,//SPI2_OUT3, //SPI controlled.  To select 1M pullup resistor or voltage divider to FB pin.
	K1_HSG_SPI_RB = 111,//SPI2_OUT4, //SPI controlled.  To connect/disconnect OVI1_0 as Kelvin/NonKelvin to HSG pin.
	K2_HSG_SPI_TB = 112,//SPI2_OUT5, //SPI controlled.  To connect/disconnect OVI1_0 from HSG pin.
	K3_HSG_SPI_TB = 113,//SPI2_OUT6, //SPI controlled.  To connect/disconnect HSG to 2nF cap.
	K4_HSG_SPI_TB = 114,//SPI2_OUT7, //SPI controlled.  To connect/disconnect HSG to GND.
	K5_HSG_SPI_TB = 115,//SPI2_OUT8, //SPI controlled.  To connect/disconnect HSG to Buffer ckt.

	//--------------------------------------------------------------------------------------------------------------------------------------------------
	//Bank 3
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	K6_HSG_SPI_RB  = 116,//SPI3_OUT1, //SPI controlled.  
	K1_B_SPI_RB    = 117,//SPI3_OUT2, //SPI controlled.  
	K2_B_SPI_TB    = 118,//SPI3_OUT3, //SPI controlled.  
	K3_B_SPI_TB    = 119,//SPI3_OUT4, //SPI controlled.  
	K4_B_SPI_TB    = 120,//SPI3_OUT5, //SPI controlled.  
	K5_B_SPI_TB    = 121,//SPI3_OUT6, //SPI controlled.  
	K2AB_VR_SPI_RB = 122,//SPI3_OUT7, //SPI controlled.  
	K3_VR_SPI_RB   = 123,//SPI3_OUT8, //SPI controlled.  

	//--------------------------------------------------------------------------------------------------------------------------------------------------
	//Bank 4
	//--------------------------------------------------------------------------------------------------------------------------------------------------

	K4_VR_SPI_RB   = 124,//SPI4_OUT1, //SPI controlled.  
	K5_VR_SPI_RB   = 125,//SPI4_OUT2, //SPI controlled.  
	K6_VR_SPI_RB   = 126,//SPI4_OUT3, //SPI controlled.  
	K1_FW_SPI_TB   = 127,//SPI4_OUT4, //SPI controlled.  
	K2_FW_SPI_TB   = 128,//SPI4_OUT5, //SPI controlled.  
	K3_FW_SPI_TB   = 129,//SPI4_OUT6, //SPI controlled.  
	K5_FW_SPI_IB   = 130,//SPI4_OUT7, //SPI controlled.  
	K7_HSG_SPI_TB  = 131,//SPI4_OUT8, //SPI controlled. 

	//--------------------------------------------------------------------------------------------------------------------------------------------------
	//Bank 5
	//--------------------------------------------------------------------------------------------------------------------------------------------------

	K_HPM_SPI_TB   = 132,//SPI5_OUT1, //SPI controlled.  
	K7_VR_SPI_IB   = 133,//SPI5_OUT2, //SPI controlled.  
	K7_IS_SPI_TB   = 134,//SPI5_OUT3, //SPI controlled. //02/13/19.  HL added to connect 1K from IS to GND.
	K_BANK5_SP2_TB = 135,//SPI5_OUT4, //SPI controlled. 
	K_BANK5_SP3_TB = 136,//SPI5_OUT5, //SPI controlled. 
	K_BANK5_SP4_TB = 137,//SPI5_OUT6, //SPI controlled. 
	K_BANK5_SP5_TB = 138,//SPI5_OUT7, //SPI controlled. 
	K_BANK5_SP6_TB = 139,//SPI5_OUT8, //SPI controlled. 


	//---------------------------------------------------------------------------------------------------------------------------------------------------
	//Mux20 controlled relays.
	//---------------------------------------------------------------------------------------------------------------------------------------------------
	K1_HVS_LB    = 200+MUX_6_2,   // On Mux20.  To connect HVS_15_POS_F to LB.
	K2_HVS_LB    = 200+MUX_6_3,   // On Mux20.  To stack   HVS_15_NEG_F on top of HVS_19_POS_F for 900V testing.
	K1_DDD_LB    = 200+MUX_6_1,   // On Mux20.  To connect DDD7_1 to high speed comparator to generate narrow pulses.
	K_GND_ANA_LB = 200+MUX_6_4,   // On Mux20.  By default, GND sense is connected to primary ground sense.  K_GND_ANA_LB is to connect to 2ndary GNDS
	K1_GNDS_LB   = 300+MUX_5_1,   // On Mux20.  By default, DVI11_GNDS is connected to primary ground sense. K1_GNDS_LB is to connect to 2ndary GNDS.
	K2_GNDS_LB   = 200+MUX_5_2,   // On Mux20.  By default, DVI9_GNDS is connected to primary ground sense.  K2_GNDS_LB is to connected 2ndary GNDs.                                   
	K3_GNDS_LB   = 200+MUX_5_3,   // On Mux20.  By default, DVI13_GNDS is connected to primary ground sense. K3_GNDS_LB is to connected 2ndary GNDs.                                   
	K4_GNDS_LB   = 200+MUX_5_4,   // On Mux20.  By default, DVI21_GNDS is connected to primary ground sense. K4_GNDS_LB is to connected 2ndary GNDs.                                   
	K_OVI3_0_LB  = 200+MUX_7_2,   // On Mux20.  To control OVI3_0 connect or disconnect from TS pin.
	K_OVI3_1_LB  = 200+MUX_7_3,   // On Mux20.  To control OVI3_0 connect to OVI3_1 sense to check Kelvin of OVI3_0 on TS pin.
	K_OVI3_3_LB  = 200+MUX_7_4,   // On Mux20.  To control OVI3_3 connect/disconnect to Sync ckt on TB.  K_OVI3_3_LB is also used to check Mux_20.
	K_OVI3_4_LB  = 200+MUX_8_2,   // On Mux20.  To short OVI3_4 Sense to OVI3_5 Sense for Kelvin check.   To short OVI3_6 Sense to OVI3_7 S for Kelvin Check.
	K_OVI1_0_LB  = 200+MUX_8_3,   // On Mux20.  To short OVI1_1 Sense to OVI1_0 Sense for Kelvin check.   
	K5678_DSM_TB = 200+MUX_4_2,   // On Mux20.  To control relay for Pri + 2ndary parallel scan.   
	K10_D_TB     = 200+MUX_1_1,   // On Mux20.  To control relay for connecting Drain to RDSON BUFF Input.
	K12_D_TB     = 200+MUX_4_1,   // On Mux20.  To control relay for shorting inductor L3 for Pri SOA testing.
	K_UV_BUFF_TB = 200+MUX_1_2,   // On Mux20.  To control relay for connecting Rdson buffer to Vpin.
	K1_UV_RB     = 200+MUX_1_3,   // On Mux20.  To control relay NonKelvin or Kelvin On Vpin.
	K2_UV_RB     = 200+MUX_1_4,   // On Mux20.  To control relay to select 10K or 600K pullup resistor on Vpin.
	K3_UV_TB     = 200+MUX_2_1,   // On Mux20.  To control relay to connect/disconnect DVI21 to Vpin.
	K1_DigA_TB   = 200+MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	K1_IS_BUFF_TB= 200+MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	K2_IS_BUFF_TB= 200+MUX_2_2,   // On Mux20.  To control relay to connect to either Drain or FW/IS pin.
	K2_DigA_TB   = 200+MUX_2_3,   // On Mux20.  To control relay to connect to either FW or IS pin.
	K_CHANB_TB   = 200+MUX_2_4,   // On Mux20.  To control relay to connect to either B or HSG pin.
	K1_BPP_RB    = 200+MUX_3_1,   // On Mux20.  To control relay to connect to BPP to 4.7uF CaP on Riderboard.
	K1_TS_RB     = 200+MUX_3_2,   // On Mux20.  To control relay to select NonKelvin/Kelvin on TS pin.
	K2_TS_TB     = 200+MUX_3_3,   // On Mux20.  To control relay to connect/disconnect OVI3_0 to TS pin.
	K3_TS_IB     = 200+MUX_3_4,   // On Mux20.  To control relay to connect/disconnect LT1719 comparator to TS pin.
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//Mux14 controlled relays.
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	K1_DSM_TB     = 500+MUX_1_1,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA (Vpin) of Primary.
	K2_DSM_TB     = 500+MUX_1_2,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SDA of 2ndary.
	K3_DSM_TB     = 500+MUX_1_3,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL (TS) of Primary.
	K4_DSM_TB     = 500+MUX_1_4,   // On Mux14.  To control relay to connect/disconnect DSM I2C to SCL of 2ndary.
	K1_DDD_TB     = 500+MUX_2_3,   // On Mux14.  To control relay to connect DDD7_1 to either TS or Integrator on IS pin.
	K2_DDD_TB     = 500+MUX_2_4,   // On Mux14.  To control relay to connect DDD7_2 to either IS or UV pin.
	K3_DDD_TB     = 500+MUX_3_1,   // On Mux14.  To control relay to connect DDD7_3 to VR pin.
	K4_DDD_TB     = 500+MUX_3_2,   // On Mux14.  To control relay to connect DDD7_4 to SDA pin.
	K5_DDD_TB     = 500+MUX_3_3,   // On Mux14.  To control relay to connect DDD7_5 to SCL pin or DDD7_5_FW_COMP3 pin.
	K6_DDD_TB     = 500+MUX_3_4,   // On Mux14.  To control relay to connect DDD7_6 to FB pin or DDD7_6_FW_COMP1 pin.
	K7_DDD_TB     = 500+MUX_4_1,   // On Mux14.  To control relay to connect DDD7_7 to FW pin or DDD7_7_FW_COMP2 pin.	
	K1_TMU_TB     = 500+MUX_4_2,   // On Mux14.  To control relay to connect TMU_HIZ1_D1 or TMU_HIZ1_D2.	
	K2_TMU_TB     = 500+MUX_4_3,   // On Mux14.  To control relay to connect TMU_HIZ2/TMU_CHB_DUT2 to UV or B pin.	
	K3_TMU_TB     = 500+MUX_4_4,   // On Mux14.  To control relay to connect TMU_HIZ3 to HBP pin.	
	K4_TMU_TB     = 500+MUX_5_1,   // On Mux14.  To control relay to connect TMU_HIZ3 to VR pin.	
	K5_TMU_TB     = 500+MUX_5_2,   // On Mux14.  To control relay to connect TMU_HIZ3 to FW pin.	
	K6_TMU_TB     = 500+MUX_5_3,   // On Mux14.  To control relay to connect TMU_HIZ4/TMU_CHB_DUT1 to HSG or TS pin.	
	K1_VR_TB      = 500+MUX_5_4,   // On Mux14.  To control relay to connect HVS to VR pin.
	K1_D_RB       = 500+MUX_6_1,   // On Mux14.  To control relay to connect DVI_11_0 to Drain or IM_Pedestal.
	K2_D_RB       = 500+MUX_6_2,   // On Mux14.  To control relay to connect DVI_11_0 as Kelvin or NonKelvin to Drain.
	K3_D_TB       = 500+MUX_6_3,   // On Mux14.  To control relay to connect/disconnect DVI_11_0 to Drain.
	K4_D_TB       = 500+MUX_6_4,   // On Mux14.  To control relay to connect/disconnect HVS to Drain.
	K5_D_TB       = 500+MUX_7_1,   // On Mux14.  To control relay to connect/disconnect PVI3 directly or via inductor to Drain
	K6_D_TB       = 500+MUX_7_2,   // On Mux14.  To control relay to connect/disconnect reg Pri SOA or pulse Pri SOA.
	K7_D_TB       = 500+MUX_7_3,   // On Mux14.  To control relay to connect/disconnect Drain to SOA circuit.
	K8_K11_D_TB   = 500+MUX_7_4,   // On Mux14.  To control relay to connect/disconnect Sync circuit to FW.
	K9_D_TB       = 500+MUX_8_1,   // On Mux14.  To control relay to connect/disconnect Drain to Pierson.
	K1_IM_TB	  = 500+MUX_8_2,   // On Mux14.  To control relay to connect/disconnect IM1
	K2_IM_TB	  = 500+MUX_8_3,   // On Mux14.  To control relay to connect/disconnect IM2
	K3_IM_TB	  = 500+MUX_8_4,   // On Mux14.  To control relay to connect/disconnect IM3

};

// Resource Mapping //
extern  Dvi	*VR_dvi;       //DVI_9_1
extern	Dvi *D_dvi;        //DVI_11_0
extern	Dvi *BPP_dvi;      //DVI_11_1
extern	Dvi *HBP_dvi2k;    //DVI_13_0
extern	Dvi *IS_dvi2k;     //DVI_13_1
extern  Dvi *BPS_dvi;      //DVI_21_0
extern  Dvi *UV_dvi;       //DVI_21_1

extern  Ovi *HSG_ovi;      //OVI_1_0
extern  Ovi *BUFCLMP_ovi;    //OVI_1_1
extern  Ovi	*IS_ovi;       //OVI_1_2,OVI_1_4
extern  Ovi *NC_ovi;       //OVI_1_3
extern  Ovi	*TS_ovi;	   //OVI_1_5
extern  Ovi	*Site_ovi;     //OVI_1_7
	
extern  Ovi	*TS_ovi3;	   //OVI_3_0
extern	Ovi *B_ovi3;       //OVI_3_1,OVI_3_2
extern  Ovi	*SYNC_ovi3;    //OVI_3_3
extern	Ovi *FW_ovi3;      //OVI_3_4
extern	Ovi *SDA_ovi3;     //OVI_3_5
extern	Ovi *SCL_ovi3;     //OVI_3_6
extern	Ovi *FB_ovi3;      //OVI_3_7


// Gage Digitizer
extern 	CSSYSTEMINFO	CsSysInfo ;
extern  int				g_DigitizerType;


// Resource Channels //
extern int	VR_ch;         //DVI_9_1.
extern int  VRstep_ch;     //DVI_9_0.
extern int	D_ch;          //DVI_11_0
extern int	BPP_ch;        //DVI_11_1
extern int	HBP_ch;        //DVI_13_0
extern int	IS_ch;         //DVI_13_1
extern int	BPS_ch;        //DVI_21_0
extern int	UV_ch;         //DVI_21_1

extern int	HSG_ch;        //OVI_1_0
extern int	BUFCLMP_ch;    //OVI_1_1
extern int	IS_ch2;        //OVI_1_2
extern int  IS_ch4;        //OVI_1_4
extern int	NC_ch;		   //OVI_1_3
extern int	TSovi1_ch;     //OVI_1_5
extern int  TSovi3_ch;	   //OVI_3_0
extern int	Site_ch;       //OVI_1_7
	
extern int	B_ch1;         //OVI_3_1
extern int  B_ch2;         //OVI_3_2
extern int	SYNC_ch;       //OVI_3_3
extern int	FW_ch;         //OVI_3_4
extern int	SDA_ch;        //OVI_3_5
extern int	SCL_ch;        //OVI_3_6
extern int	FB_ch;         //OVI_3_7

extern uint16_t EEpr_Bank_P[5];
extern uint16_t EEpr_Bank_S_S[5];	//replace EEpr_Bank_S with additional _S for secondary  --> to do later by HL
extern uint16_t EEpr_Bank_S[5];

extern uint16_t EEpr_E0;   
extern uint16_t EEpr_E2;
extern uint16_t EEpr_E4;   
extern uint16_t EEpr_E6;
extern uint16_t EEpr_E8;

extern int	g_Pre_E0_data_P;
extern int	g_Pre_E2_data_P;
extern int	g_Pre_E4_data_P;
extern int  g_Pre_E6_data_P;
extern int  g_Pre_E8_data_P;
		
extern int	g_Pre_E0_data_S;
extern int  g_Pre_E2_data_S;
extern int	g_Pre_E4_data_S;
extern int  g_Pre_E6_data_S;
extern int	g_Pre_E8_data_S;

// Program Name
//extern STRING ProgramName;

/* ======================  Test Hardware ID Parameters  ============================*/
extern int gLoadBoard_SubType;					// Loadboard type for hardware ID
extern int gLoadBoardRev;
extern int g_LB_rev_needed;
//HL added.
extern int gTestBlock_SubType;
extern int gTestBlockRev;
extern int g_TB_rev_needed;
extern int gInductor_SubType;				// Inductor type for hardware ID
extern int gInductorRev;
extern int gContactor_SubType;				// Contactor type for hardware ID
extern int gContactorRev;
extern int g_CB_rev_needed;


/* ======================  Die Parameters  =========================================*/
extern int g_DevFamily_Trimops;
//extern int g_DevNum_Trimops;
extern int	g_BV_Trimops									,
			g_FET_Size_Trimops								,
			gP_Reserved_Trimops								, //bit 0 to 7
			gP_Trim_AR_SKIP_time_Trimops					,	//bit 21
			gP_Trim_Disable_TON_foldback_Trimops			,	//bit 22
			gP_Trim_AR_OFF_TIME_Trimops						,	//bit 23,24
			gP_Trim_START_UP_FREQ_Trimops					, //bit 25
			gP_Trim_Enable_Shunt_during_Cap_Select_Trimops	, //bit31
			gP_Trim_RCV_threshold_Trimops					, //bit 32,33,34
			gP_Trim_GaN_Mode_Trimops						, //bit 35
			gP_Trim_Sense_Voltage_ILIM_Trimops				, //bit 36,37,38,39,40
			gP_Trim_Driver_Size_Trimops						, //bit 41,42,43,44
			gP_Trim_AR_ON_time_Trimops						, //bit 45
			gP_Trim_GaN_On_Delay_Trimops					, //bit 46,47
			gP_Trim_ILIMTC_Trimops							, //bit 48,49,50,51
			gP_Trim_Bandgap_TSD_Trimops						, //bit 52,53
			gP_Trim_DOPL_mode_Trimops						, //bit 54
			gP_Trim_Disable_ILIM_cap_Select_Trimops			, //bit 55
			gP_Trim_Set_ILIMP_Trimops						, //bit 56
			gP_Trim_Junction_Start_Temp_Trimops				, //bit 61,62,63
			gP_Trim_Junction_TSD_Trimops					, //bit 64,65,66
			gP_Trim_iUV_10pct_Trimops						; //but 71

//to do later for HL  "move secondary to here for trimops global variables"

/* ======================  Test Flow Control Parameter  ============================*/
//extern int  g_First_Time_Run;
extern bool g_Require_PartID;
extern int	AbortTest; 
extern int	g_Sim_Enable_P;
extern int  g_Burn_Enable_P;
extern int  g_Burn_Enable_S;
extern int	g_Erase_Enable_P;
extern int  g_Erase_Enable_S;
extern int  g_TstTime_Enble_P;
extern char* g_Part_ID_Trimops;
extern char *PrgRev;
extern char *FamilyName;
extern char *gDev_Family;
extern char g_OperCode[];
extern char g_DevName[];
extern char Part_ID_LimitSet[];
extern int  g_OPCODE;	
extern int  g_OPCODE_RTR;
extern int  g_Rel_Enable_P;
//extern int  Golden_Unit_Prg;
extern int g_Char_Enable_P;
extern int g_Char_Enable_S;
extern int g_Debug;
extern int g_LowerByte;
extern int g_FeedFoward;
extern int g_Device_ID_S;

extern float g_B2_MaxSate;
extern float g_B1_FastUpdate;
extern float g_A3_Target_VR;
extern float g_A2_FastUpdate;
extern float g_A1_MinState;
extern float g_A_Skipping;
//extern int   g_DOPL_Primary;


// DSM I2C error counters
//extern uint32_t __dsm_write_fail_count;
//extern uint32_t __dsm_write_retry_count;
//extern uint32_t __dsm_write_pass_count;
//extern uint32_t __dsm_read_fail_count;
//extern uint32_t __dsm_read_pass_count;

//extern bool DSM_halt_exec_on_error;

/* ======================  Debug Parameters ============================*/
extern char *g_Func_name;
extern char *g_WAVE_NAME; 

enum SiliconRev_S{ revA_S, revB_S, revB2_S};
enum Capture_Mode {ILIM_NORM, ILIM_INCR};
enum Power_Up_Modes {	Normal_Mode_P, 
						Normal_Mode_S,
						Normal_Mode_with_FW, 
						Normal_Mode_with_Vout, 
						gNM_SkipWaitNListen_S,
						Test_Mode, 
						gTM1_p, 
						gTM2_p,
						gTM5_BypassWL_p,
						gTM_OverTemp, 
						gTM_Fast_Counter_32x, 
						gTM_TonMax1us, 
						gTM_Receiver_Threshold, 
						gTM1_UVOV_NoDelay,
						gTM2_UVOV_NoDelay,
						gTM_Trim_Readable, 
						gTM_Jitter_to_Vpin, 
						gTM_MaxF_to_Vpin, 
						gTM_ILIM,
						gWrite_Mode_ReadAF, 
						gWrite_Mode_TrimAF, 
						gObserve_Mode, 
						gOT_Mode, 
						gProgRead_S,
						gProgRead_SkipWaitNListen_S,
						gProgSim,
						gObserve_Mode_Xcontrol_sec,
						gObserve_Mode_Xlisten,
						gObserve_Mode_XVTurnOn,
						gObserve_Mode_XRestart,
						gObserve_Mode_rcv,
						gObserve_Mode_Pause,
						gObserve_Mode_DSDS,
						gObserve_Mode_OT,
						gObserve_Mode_LatchOff,
						gObserve_Mode_Xoc,
						gObserve_Mode_DZwindow,
						gObserve_Mode_XZfQ,
						gObserve_Mode_Xtest2,
						gObserve_Mode_iplus,
						gProgReadTestMode1_FB_S,		//Shorten AR timer by 10x.  Shorten SC timer by 256x
						gProgReadTestMode1_Vout_S,		//Shorten AR timer by 10x.  Shorten SC timer by 256x
						gProgReadTestMode2_S,			//DableOn from FW pin Peak Switch
						gProgReadTestMode3_S,			//Pulse Request
						gProgReadTestMode4_S,			//FW pin Peak Switch FAult
						gProgReadTestMode5_S,			//SR pullup
						gProgReadTestMode6_S,			//verify secondary is in control
						gProgReadTestModeTFB1_S,			//normal SR signal
						gProgReadTestModeTFB2_S,			//normal SR signal
						gProgReadTestMode11_S,			//SR comparator output
						gProgReadTestMode12_S,			//FW min 1us negative pulse indication
						gProgReadTestMode13_S,			//9V20V comparator signal
						gProgReadTestMode14_S,			//12V comparator signal
						gProgReadTestMode18_S,			//CV comparator signal
						gProgReadTestMode19_S,			//CC comparator signal
						gProgReadTestMode20_S,			//AR_3V comparator signal
						gProgReadTestMode21_S,			//SC comparator signal
					};

enum Vd_Input_Mode {High_Vd_Input, Low_Vd_Input, High_Temp_Vd_Input, Low_Load_Vd_Input};

/* ======================    Trimming Variable  ============================*/
extern float gTrim_Voltage;

/* ======================  Setup Variable  ============================*/
extern STRING CURRENT_SERIAL_NUM; 
extern int g_SERIAL_NUM;
extern int g_FirstPart;
extern int gFuncNum;
extern int gDisplay_FuncNum;
extern bool g_Wrong_Number_Of_Functions;
extern int g_Setup_OK;  //HL added.

/*=======================   Test Debug Variables ===============================*/
extern CMicroTimer mytimer;					
extern LONGLONG starttime;
extern LONGLONG stoptime;
extern int DEBUG;
//extern char *WAVE_NAME; 

/*=======================   Golden Unit Variables    ===============================*/
extern bool GoldenUnit;

extern float g_vDSM_pullup_P;
extern float g_vDSM_pullup_S;

//Global Characterization variables
extern bool	g_Char_iOVp_XYplot;
extern bool	g_Char_iOVm_XYplot;
extern bool	g_Char_iUVp_XYplot;
extern bool	g_Char_iUVm_XYplot;
extern bool g_Char_vBPPth;

//iOV function global variables
extern bool g_USE_VR_600K;

//Global Delay variables
extern int	g_Erase_dly_P,
			g_Burn_dly_P,
			g_Erase_dly_S,
			g_Burn_dly_S;

//CX added for Primary variables
extern float	g_vDrain_Erase_th_P;
extern float	g_vDrain_Burn_th_P;
extern bool		g_Load_previous_RegBits;

//HL---------------------------------------------------------------------------------
//Secondary Variables.
//-----------------------------------------------------------------------------------
extern float g_HBP_Pre_S;
extern float g_CV_Prg;
extern int   g_TrimBank[5];
extern int	 g_E0_start_bit;
extern int	 g_E2_start_bit;
extern int	 g_E4_start_bit;
extern int	 g_E6_start_bit;
extern int	 g_E8_start_bit;

extern float g_DDDhiLevel;
extern float g_DDDLoLevel;
extern float g_DDD_Period;
extern int   g_DDD_10Khz_Pulses_StopAddr;
extern int   g_DDD_100Khz_Pulses_StopAddr;
extern int   g_VbIlim_Pulses_StopAddr;
extern int   g_DDD_FW_1_Pulse_StartAddr;
extern int   g_DDD_FW_1_Pulse_StopAddr;

/*=======================		DDD Variables		 ===============================*/
extern float Dclk_period;		// DDD clock period
extern float DDD_Vref;			// DDD voltage reference 2.5V
extern float g_Dclk_I2C; // I2C DDD clock period //
extern float g_Vref_I2C; // I2C DDD voltage reference //
extern int g_DDD_fast;

extern int First_address;
extern int g_NextAddrFixed;
extern int g_NextAddr;
//////////extern int Low_pat_start, Low_pat_stop,
//////////		Low_XXX_pat_start, Low_XXX_pat_stop,
//////////		High_pat_start, High_pat_stop,
//////////		High_pat_FB_start, High_pat_FB_stop,
//////////		//High_pat_FW_start, High_pat_FW_stop,
//////////		HIZ_SDA_SCL_start,HIZ_SDA_SCL_stop,
//////////		SDA_SCL_HIZ_FW_High_start, SDA_SCL_HIZ_FW_High_stop,
//////////		//FWhi_FBhi_Vlow_start, FWhi_FBhi_Vlow_stop,
//////////		//FWhi_FBlow_Vhi_start, FWhi_FBlow_Vhi_stop,
//////////		FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop,
//////////		FW_Neg_2nd_pulse_start, FW_Neg_2nd_pulse_stop,
//////////		FW_Neg_3rd_pulse_start, FW_Neg_3rd_pulse_stop,
//////////		//FW_Neg_4th_pulse_start, FW_Neg_4th_pulse_stop,
//////////		//FW_Neg_5th_pulse_start, FW_Neg_5th_pulse_stop,
//////////		FWneg_FBhi_Vlo_1st_pulse_start, FWneg_FBhi_Vlo_1st_pulse_stop,
//////////		FWneg_FBhi_Vlo_2nd_pulse_start, FWneg_FBhi_Vlo_2nd_pulse_stop,
//////////		FWneg_FBhi_Vlo_3rd_pulse_start, FWneg_FBhi_Vlo_3rd_pulse_stop,
//////////		FWPK_300kHz_Ring_start, FWPK_300kHz_Ring_stop,
//////////		FWPK_1MHz_Ring_start, FWPK_1MHz_Ring_stop,
//////////		FWPK_Max_Ring_start, FWPK_Max_Ring_stop,
//////////		FWPK_Min_Ring_start, FWPK_Min_Ring_stop,
//////////		FWPK_test_pulses_start1, FWPK_test_pulses_stop1,
//////////		FWPK_test_pulses_start1_single, FWPK_test_pulses_stop1_single,
//////////		FWPK_test_pulses_start2_single, FWPK_test_pulses_stop2_single,
//////////		FWPK_test_pulses_start3_single, FWPK_test_pulses_stop3_single,
//////////		FWPK_test_pulses_start4_single, FWPK_test_pulses_stop4_single,
//////////		FWPK_test_pulses_start5_single, FWPK_test_pulses_stop5_single,
//////////		//FWPK_test_pulses_start2, FWPK_test_pulses_stop2,
//////////		//FWPK_test_pulses_start3, FWPK_test_pulses_stop3,
//////////		//FWPK_test_pulses_start4, FWPK_test_pulses_stop4,
//////////		//FWPK_test_pulses_start5, FWPK_test_pulses_stop5,
//////////		//FWPK_test_pulses_start6, FWPK_test_pulses_stop6,
//////////		//FWPK_test_pulses_start7, FWPK_test_pulses_stop7,
//////////		//FWPK_test_pulses_start8, FWPK_test_pulses_stop8,
//////////		//FWPK_test_pulses_start9, FWPK_test_pulses_stop9,
//////////		//FWPK_test_pulses_start10, FWPK_test_pulses_stop10,
//////////		//FWPK_test_pulses_start11, FWPK_test_pulses_stop11,
//////////		//FWPK_test_pulses_start12, FWPK_test_pulses_stop12,
//////////		//FWPK_test_pulses_start13, FWPK_test_pulses_stop13,
//////////		//FWPK_test_pulses_start14, FWPK_test_pulses_stop14,
//////////		//FWPK_test_pulses_start15, FWPK_test_pulses_stop15,
//////////		HIZallChannels_start, HIZallChannels_stop, 
//////////		FW_Neg_loop_pulse_start, FW_Neg_loop_pulse_stop,
//////////		FB_100kHz_loop_pulse_start, FB_100kHz_loop_pulse_stop, 
//////////		Vpin_loop_pulse_start, Vpin_loop_pulse_stop,
//////////		FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop,
//////////		FB_100kHz_ILIM_pulse_start, FB_100kHz_ILIM_pulse_stop, 
//////////		FB_100kHz_ILIM_18_pulse_stop,
//////////		FB_tOVL_start, FB_tOVL_stop,
//////////		AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop,
//////////		AF_Vpin_Clk_pulse_start_132kHz, AF_Vpin_Clk_pulse_stop_132kHz,
//////////		AF_Vpin_Data_pulse_start,AF_Vpin_Data_pulse_stop;
//////////		//AF_Vout_pulse_start, AF_Vout_pulse_stop;
//////////
//////////extern int Vpin_100kHz_ILIM_pulse_start;
//////////extern int Vpin_100kHz_ILIM_pulse_stop;
//////////
//////////extern int FB_18kHz_pulse_start;
//////////extern int FB_18kHz_pulse_stop;
//////////extern int FB_125kHz_pulse_start;
//////////extern int FB_125kHz_pulse_stop;
//////////
//////////extern int Vpin_125kHz_pulse_start_X;
//////////extern int Vpin_125kHz_pulse_stop_X;
//////////
//////////extern int Vout_125kHz_pulse_start_X;
//////////extern int Vout_125kHz_pulse_stop_X;
//////////
//////////extern int Vout_100kHz_ILIM_pulse_start_X;
//////////extern int Vout_100kHz_ILIM_pulse_stop_X;
//////////
//////////extern int Vpin_100kHz_ILIM_pulse_start_X;
//////////extern int Vpin_100kHz_ILIM_pulse_stop_X;
//////////extern int Vpin_6clocks_start;
//////////extern int Vpin_6clocks_stop;
//////////extern int Vpin_4clocks_start;
//////////extern int Vpin_4clocks_stop;
//////////extern int Vpin_2clocks_start;
//////////extern int Vpin_2clocks_stop;
//////////extern int Vpin_3NegClocks_start;
//////////extern int Vpin_3NegClocks_stop;
//////////extern int Vpin_30usec_start;
//////////extern int Vpin_30usec_stop;
//////////extern int Vpin_one_30us_clock_start;
//////////extern int Vpin_one_30us_clock_stop;
//////////extern int FB_100kHz_pulse_start_5X;
//////////extern int FB_100kHz_pulse_stop_5X;


/*=======================    Internal Registers   ===============================*/
extern int gVpin_Internal_Signal[16];	//Primary Internal Registers
extern float gIZ_AF_post_P[100];

/*=======================    BVD Function Variables    =============================*/
extern float g_scaled_ifrc;
extern float	gBVD_Room_Trimops;
extern float	gBVD_Hot_Trimops;

/*============================    VBP Variables    =================================*/
extern float gVshunt_BPP, gVshunt_BPS;
extern float gVBPS_P_Init, gVBPP_P_Init, gVBPP_P_final, gVBPS_final, gVBPP_M_Init, gVBPS_M_Init, gVBPP_PV_Init, gVBPP_PV_final; 
extern float g_VBPP_P_S_Init_S;
extern float g_VBPP_P_s_final;
extern float gVBPP_VCEN;
extern float gIBPS_nsw;
extern float gIBPS_nswHF;

/*============================    Timing Global Variables   ===============================*/
extern float gDly_Wait_and_Listen_Normal_Mode;
extern float gDly_Wait_and_Listen_Test_Mode;
extern float g_readTime_p;
extern float g_readTime_s;
extern float g_trimTime_p;
extern float g_trimTime_s;
extern float g_StartTime;
extern float g_StopTime;
extern int   g_ILIM_dly;
extern int   g_REL_dly;
extern int   g_tHandshake_SSS;


//#define Secondary_I2C_ADDR			0x3B	// 7-bit slave address
//#define Secondary_I2C_ADDR_R		0x77	// r_wb = 1
//#define Secondary_I2C_ADDR_W		0x76	// r_wb = 0

/*============================    FB Global Variables   ===============================*/
/*============================    Anti-Fuse Variables   ===============================*/
//Primary
extern int  gP_Reg_Start_Bit_SiID		,
			gP_Reg_Start_Bit_fOSC		,
			gP_Reg_Start_Bit_yInter		,
			gP_Reg_Start_Bit_ILIM		,
			gP_Reg_Start_Bit_ArSkip		,
			gP_Reg_Start_Bit_ArOnT		,
			gP_Reg_Start_Bit_ArOffT		,
			gP_Reg_Start_Bit_StrFREQ	,	
			gP_Reg_Start_Bit_OnTSL		,
			gP_Reg_Start_Bit_ShuntEn	,	
			gP_Reg_Start_Bit_RcvTH		,
			gP_Reg_Start_Bit_GanMode	,	
			gP_Reg_Start_Bit_VxTrim		,
			gP_Reg_Start_Bit_DrSize		,
			gP_Reg_Start_Bit_AROn512	,	
			gP_Reg_Start_Bit_GanDLy1	,	
			gP_Reg_Start_Bit_IlimTc		,
			gP_Reg_Start_Bit_SDTemp		,
			gP_Reg_Start_Bit_DOPL		,
			gP_Reg_Start_Bit_DisIlimCap	,	
			gP_Reg_Start_Bit_ILIMP		,
			gP_Reg_Start_Bit_uVADC		,
			gP_Reg_Start_Bit_StrTTFB	,	
			gP_Reg_Start_Bit_EndTTFB	,	
			gP_Reg_Start_Bit_TsADC		,
			gP_Reg_Start_Bit_UV10pct	,	
			gP_Reg_Start_Bit_IOV		,
			gP_Reg_Start_Bit_TonM		;

extern int  gP_Total_Bits_SiID		,
			gP_Total_Bits_fOSC		,
			gP_Total_Bits_yInter		,
			gP_Total_Bits_ILIM		,
			gP_Total_Bits_ArSkip		,
			gP_Total_Bits_ArOnT		,
			gP_Total_Bits_ArOffT		,
			gP_Total_Bits_StrFREQ	,	
			gP_Total_Bits_OnTSL		,
			gP_Total_Bits_ShuntEn	,	
			gP_Total_Bits_RcvTH		,
			gP_Total_Bits_GanMode	,	
			gP_Total_Bits_VxTrim		,
			gP_Total_Bits_DrSize		,
			gP_Total_Bits_AROn512	,	
			gP_Total_Bits_GanDLy1	,	
			gP_Total_Bits_IlimTc		,
			gP_Total_Bits_SDTemp		,
			gP_Total_Bits_DOPL		,
			gP_Total_Bits_DisIlimCap	,	
			gP_Total_Bits_ILIMP		,
			gP_Total_Bits_uVADC		,
			gP_Total_Bits_StrTTFB	,	
			gP_Total_Bits_EndTTFB	,	
			gP_Total_Bits_TsADC		,
			gP_Total_Bits_UV10pct	,	
			gP_Total_Bits_IOV		,
			gP_Total_Bits_TonM		;

//Secondary
extern int	gPK_AF_Addr_Start,							
			gCV_AF_Addr_Start, 
			gSpare_Addr_Start,
			gZF_S_Addr;

/*============================    Feature Trim Variables   ===============================*/
extern double	g_Hcode_Trimops,
				gTrim_code_Trimops;

extern int	g_Trim_iov_Off_P_Trimops		,
			g_Trim_iuvMinus_P_Trimops	,
			g_Trim_uvDelay_P_Trimops		,
			g_Trim_Loff_AR_P_Trimops		,
			g_Trim_DisablAR_P_Trimops	,
			g_Trim_didtComp_P_Trimops	,
			g_Trim_OT_Hys_P		,
			g_Trim_LoffwOT_P_Trimops		,
			g_Trim_iLselOff_P_Trimops	,
			g_Trim_iLStdIcr_P_Trimops	,
			g_Trim_iL20dn_P_Trimops		,
			g_Trim_iL20up_P_Trimops		,
			g_Trim_SAM_P_Trimops			,
			g_Trim_OTP_P_Trimops			, //3 bits
			g_Trim_SDSoff_P_Trimops	,
			g_Trim_Rcv_P_Trimops				, //3 bits
			g_Trim_drvSize_P_Trimops			, //4 bits
			g_Trim_RsenseUp_P_Trimops		,
			g_Trim_vxAdj_P_Trimops			, //5 bits
			g_Trim_iLRatio_P_Trimops			, //4 bits
			g_Trim_iLTC_P_Trimops			, //4 bits
			gTrim_AR_req_Trimops			;



extern int gTrim_SdwReg0_Trimops;
extern int gTrim_SdwReg1_Trimops;
extern int gTrim_SdwReg2_Trimops;
extern int gTrim_SdwReg3_Trimops;
extern int gTrim_SdwReg4_Trimops;
extern int gTrim_SdwReg5_Trimops;
extern int gTrim_SdwReg6_Trimops;
extern int gTrim_SdwReg7_Trimops;
extern int gTrim_SdwReg8_Trimops;
extern int gTrim_SdwReg9_Trimops;
extern int gTrim_SdwReg10_Trimops;
extern int gTrim_SdwReg11_Trimops;
extern int gTrim_SdwReg12_Trimops;
extern int gTrim_SdwReg13_Trimops;
extern int gTrim_SdwReg14_Trimops;
extern int gTrim_SdwReg15_Trimops;
extern int gTrim_SdwReg16_Trimops;
extern int gTrim_SdwReg17_Trimops;
extern int gTrim_SdwReg18_Trimops;
extern int gTrim_SdwReg19_Trimops;
extern int gTrim_SdwReg20_Trimops;
extern int gTrim_SdwReg21_Trimops;
extern int gTrim_SdwReg22_Trimops;
extern int gTrim_SdwReg23_Trimops;
extern int gTrim_SdwReg24_Trimops;
extern int gTrim_SdwReg25_Trimops;
extern int gTrim_SdwReg26_Trimops;
extern int gTrim_SdwReg27_Trimops;
extern int gTrim_SdwReg28_Trimops;
extern int gTrim_SdwReg29_Trimops;
extern int gTrim_SdwReg30_Trimops;
extern int gTrim_SdwReg31_Trimops;
extern int gTrim_SdwReg32_Trimops;
extern int gTrim_SdwReg33_Trimops;
extern int gTrim_SdwReg34_Trimops;
extern int gTrim_SdwReg35_Trimops;
extern int gTrim_SdwReg36_Trimops;
extern int gTrim_SdwReg37_Trimops;
extern int gTrim_SdwReg38_Trimops;
extern int gTrim_SdwReg39_Trimops;
extern int gTrim_SdwReg40_Trimops;
extern int gTrim_SdwReg41_Trimops;
extern int gTrim_SdwReg42_Trimops;
extern int gTrim_SdwReg43_Trimops;
extern int gTrim_SdwReg44_Trimops;
extern int gTrim_SdwReg45_Trimops;
extern int gTrim_SdwReg46_Trimops;
extern int gTrim_SdwReg47_Trimops;
extern int gTrim_SdwReg48_Trimops;
extern int gTrim_SdwReg49_Trimops;
extern int gTrim_SdwReg50_Trimops;
extern int gTrim_SdwReg51_Trimops;
extern int gTrim_SdwReg52_Trimops;
extern int gTrim_SdwReg53_Trimops;
extern int gTrim_SdwReg54_Trimops;
extern int gTrim_SdwReg55_Trimops;
extern int gTrim_SdwReg56_Trimops;
extern int gTrim_SdwReg57_Trimops;
extern int gTrim_SdwReg58_Trimops;
extern int gTrim_SdwReg59_Trimops;
extern int gTrim_SdwReg60_Trimops;
extern int gTrim_SdwReg61_Trimops;
extern int gTrim_SdwReg62_Trimops;
extern int gTrim_SdwReg63_Trimops;
extern int gTrim_SdwReg64_Trimops;
extern int gTrim_SdwReg65_Trimops;
extern int gTrim_SdwReg66_Trimops;
extern int gTrim_SdwReg67_Trimops;
extern int gTrim_SdwReg68_Trimops;
extern int gTrim_SdwReg69_Trimops;
extern int gTrim_SdwReg70_Trimops;
extern int gTrim_SdwReg71_Trimops;
extern int gTrim_SdwReg72_Trimops;
extern int gTrim_SdwReg73_Trimops;
extern int gTrim_SdwReg74_Trimops;
extern int gTrim_SdwReg75_Trimops;
extern int gTrim_SdwReg76_Trimops;
extern int gTrim_SdwReg77_Trimops;
extern int gTrim_SdwReg78_Trimops;
extern int gTrim_SdwReg79_Trimops;
extern int gTrim_SdwReg80_Trimops;
extern int gTrim_SdwReg81_Trimops;
extern int gTrim_SdwReg82_Trimops;
extern int gTrim_SdwReg83_Trimops;
extern int gTrim_SdwReg84_Trimops;
extern int gTrim_SdwReg85_Trimops;
extern int gTrim_SdwReg86_Trimops;
extern int gTrim_SdwReg87_Trimops;
extern int gTrim_SdwReg88_Trimops;
extern int gTrim_SdwReg89_Trimops;
extern int gTrim_SdwReg90_Trimops;
extern int gTrim_SdwReg91_Trimops;
extern int gTrim_SdwReg92_Trimops;
extern int gTrim_SdwReg93_Trimops;
extern int gTrim_SdwReg94_Trimops;
extern int gTrim_SdwReg95_Trimops;
extern int gTrim_SdwReg96_Trimops;
extern int gTrim_SdwReg97_Trimops;
extern int gTrim_SdwReg98_Trimops;
extern int gTrim_SdwReg99_Trimops;
extern int gTrim_SdwReg100_Trimops;
extern int gTrim_SdwReg101_Trimops;
extern int gTrim_SdwReg102_Trimops;
extern int gTrim_SdwReg103_Trimops;
extern int gTrim_SdwReg104_Trimops;
extern int gTrim_SdwReg105_Trimops;
extern int gTrim_SdwReg106_Trimops;
extern int gTrim_SdwReg107_Trimops;
extern int gTrim_SdwReg108_Trimops;
extern int gTrim_SdwReg109_Trimops;
extern int gTrim_SdwReg110_Trimops;
extern int gTrim_SdwReg111_Trimops;

//-------------------------------------------------------------------------------------
extern int g_SiliconRev_Pri; // Primary silicon revision //
extern int g_SiliconRev_Sec; // Secondary silicon revision //

//HL
// Secondary Trim Options.
extern int g_Trim_tsstart_B8_9_S_Trimops;			//Softstart time    
extern int g_Trim_tfbOption_B10_11_S_Trimops;		//Boost Frequency Options
extern int g_Trim_DOPL_B15_S_Trimops;				//DOPL Option Bit
extern int g_Trim_TvrOption_B16_17_S_Trimops;		//VR Option Selection.
extern int g_Trim_TenCP_B18_S_Trimops;				//Enable CP in Non I2C Mode
extern int g_Trim_ZffOption_B19_20_S_Trimops;		//Feedforward Option.
extern int g_Trim_DsblJitDim_B21_S_Trimops;			//Disable Jitter in Dimming.
extern int g_Trim_JitterOff_B22_S_Trimops;			//Turn off Jitter.
extern int g_Trim_ZTMBStr_B29_30_S_Trimops;			//Enable 1 segment Boost Driver.
extern int g_Trim_DsblFlBck_B31_S_Trimops;			//Disable Foldback.
extern int g_Trim_Dimth_B47_S_Trimops;				//Select Deep Dim Threshold
extern int g_Trim_tHrtBtOpt_B61_S_Trimops;			//Heat beat time option.
extern int g_Trim_CPNonI2C_B62_S_Trimops;			//Disable CP
extern int g_Trim_ZEE_50KStr_B63_S_Trimops;			//Set softstart start up freq
extern int g_Trim_FlBck_Ccopt_B74_S_Trimops;			//To change rate of change in CC reference.
extern int g_Trim_FlBck_Sel_B75_S_Trimops;			//Trim to disable thermal foldback and line induced foldback.
extern int g_SID_Trimops;							//Si ID

extern float g_BFreq_Target_S_Trimops;
extern float g_ccPFOFF_Target_S_Trimops;
extern float g_Fosc_Target_S_Trimops;
extern float g_CLK1M_Target_S_Trimops;
extern float g_VDDA_Target_S_Trimops;
extern float g_CV_Target_S_Trimops;
extern float g_VbIlim_Target_S_Trimops;
extern float g_VADC_Target_S_Trimops;
extern float g_ZTtimer_Target_S_Trimops;
extern float g_VccRef_Target_S_Trimops;
extern float g_CCOffset_Target_S_Trimops;
extern float g_CP_IS_Target_S_Trimops;
extern float g_IRSET_Target_S_Trimops;

extern int   g_GRR_Enable;
extern float g_HBP_P_S;
extern float g_CV_Pre;
extern float g_VDDA_Pre;
extern float g_IRSET_Pre;
extern float g_ZTtimer_Pre;
extern float g_VADC_Pre;
extern float g_CLK1M_Pre;
extern float g_CCOffset_Pre;
extern float g_VccRef_Pre;
extern float g_ccPFOFF_Pre;
extern float g_Fosc_Pre;
extern float g_BFreq_Pre;
extern float g_CP_IS_Pre;
extern float g_VbIlim_Pre;
//-------------------------------------------------------------------------------------------------

/*=======================    IzPre Function Variables    ===============================*/
extern float	gIzpt_NoZ_s, gIZ_NoZ_s;
extern float    gVread_AF_primary, gVread_AF_secondary;
extern float    gSec_tr1_ZapTime;
extern float    gSec_tr2_AFtrhd;
extern int		gSiOption_s;

/*====================    Fosc Function Variables    ===============================*/
extern float	g_Fosc_pt_P,    g_FOSC_pt_S;
extern float    g_FOSC_S;
extern float	gP_Fosc_TARGET_Trimops, gFOSC_TARGET_S_Trimops;
extern float    g_FOSC_exp_P,   g_FOSC_exp_S;
//extern float    gFOSC_post_S;

/*======================    TonMin Variables    ====================================*/
extern float   gP_TonMin_TARGET_Trimops;

/*======================    Ton Slope & Offset Variables    ====================================*/
extern float	gP_Slope_TARGET_Trimops;
extern float	gP_Offset_TARGET_Trimops;

//extern float   g_TonMax_Pt, g_TonMax_S;
//extern float   g_ToffMin_s;
//extern float   g_TonMax_exp;
//extern float   g_tOVL_TARGET_Trimops;
//extern float   g_tOVL_Pt;
//extern float   g_tOVL_exp;
//extern int	   g_HandShake_PASS;

/*======================    iOV- Variables    ====================================*/
extern float	gP_iOVp_TARGET_Trimops;
extern float	gP_iOVm_TARGET_Trimops;
extern float	g_iOVp_meas_P;
extern float	g_iOVp_exp;

/*======================    iUV+ Variables    ====================================*/
extern float	gP_iUVp_TARGET_Trimops;
extern float    gP_iUVm_TARGET_Trimops;
extern float	g_iUVp_pt_P;
extern float	g_iUVp_exp;

/*======================    CV Variables    ====================================*/
extern float 	gCV_FB_Init_pt_S;
//extern float	gCV_FB_pt_S;
extern float	gCV_VO_pt_S;
//extern float    gCVtgt_15pct_Higher; //gCV_FB_Pre;
extern float gCV_Vout_TARGET_Trimops;
extern float	gCV_S,		gCV_post_S;
extern float	gCV_FB_S,	gCV_FB_post_S;
extern float	gCV_VO_S,	gCV_VO_post_S;

extern float    gVclamp_2pct_S, gVclamp_10pct_S;

/*======================    CC Variables    ====================================*/
extern float 	gCC_pt_S;
extern float 	gKP_pt_S;
extern float 	gSL_pt_S;
//extern float	gCC_Amp_pt_S;
extern float	gISvth_pt_S;
extern float    gISvth_TARGET_Trimops;

extern float	gCC_KPpt_S;
extern float	gCV_NM_KPpt_S;
extern float	gCB_KPpt_S;
extern float	gSL_pt_S;
extern float	gCC_Amp_SLpt_S;
extern float	gCC_ISvth_SLpt_S;
extern float	gVknee_actual_SLpt_S;
extern float	gCC_Amp_S;
extern float	gVknee_actual_S;

extern float	gCC_S_9V_TARGET;
extern float	gCC_S_12V_TARGET;
extern float	gCC_S_20V_TARGET;
extern float	gCC_exp_S;
extern float	gISvth_S_9V_TARGET;
extern float	gISvth_S_12V_TARGET;
extern float	gISvth_S_20V_TARGET;
extern float	gKP_exp_S;
extern float	gSL_exp_S;

extern float    iPV3_Cal_CC90;
extern float    iPV3_Cal_CC80;
extern float    iPV3_Cal_CC65;
extern float    iPV3_Cal_CC55;
extern float	iPV3_CC90;
extern float	iPV3_CC80;
extern float	iPV3_CC65;
extern float	iPV3_CC55;

/*======================    CB Variables    ====================================*/
extern int		gCB_CODE;
extern float    gCB_exp_S;
extern float    iPV3_Load, iDVI2K_Load;	// For CB vs load experiment
extern float	gCB_NoLoad_Pct_pt;
extern float	gvCB_pre_TM_S;

/*======================    IFB Variables    ====================================*/
extern float	gIFB_TH_Target_S;
extern float	gIFB_250mA_pt_S;
extern float	gIFB_130mA_pt_S;
extern float	gIFB_TH_pt_S;
extern float	gIFB_exp_S;

/*======================    Dtemp Variables    ====================================*/
extern float	gP_Dtemp_TARGET_Trimops;
extern float	gP_VTSstart_TARGET_Trimops;

/*======================    ILIM Variables    ====================================*/
extern float	gVped_Ilim, gVped_Ilim_Incr;
extern float	gVind_RM;
extern float	g_Vpedestal;

extern float	gP_ILIM_TARGET_Trimops;
extern float	g_ILIM_LO_TARGET;
extern float	g_ILIM_LO_Med_TARGET;
extern float	g_ILIM_UP_Med_TARGET;
extern float	g_I2F_S_TARGET;
extern float	g_DIDT_TARGET;
extern float    g_ILIM_pt_S;
extern float    g_ILIM_exp_S;
extern float	g_ILIM_I2f_pt_S;
// For Capture and Find ILIM with digitizer
extern float    g_Ilim_Incr_max;
extern float	g_Ilim_gain, g_BUFgain;
extern int		g_SAMPLE_SIZE;

extern int		g_FIND_RDSON_Peak_FLAG;
extern int		g_FIND_RDSON_Spec_FLAG;
extern int		g_Find_ILIM_Jitter;
extern float	g_Idmax[4000];
extern int		g_Idmax_addr[4000];

/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
extern float gISvth;
extern float MEAS_Isvth_FLAG;

/*=======================    VBP_Supply Function Variables    ===============================*/
extern float gVshunt_Init_Pr;
extern float gVshunt_Init_Se;
extern float g_BPP_IS1_nsw_P;
extern float g_BPP_IS2_sw_P;
extern float gISD_P;
extern float gISD_S;
extern float gVBPS_P;	//JD  redundunt variables

/*=======================    IOV/UV Function Variables    ===============================*/
extern bool gIOV;

/*=======================    DATT Function Variables    ===============================*/
extern float	gDATT_drain_current, gDATT_pulse_time;
extern float	gNorm_x_lim, gNorm_n_lim;

extern int	Gage_pretrig_samples;

/*===========================    HandShake Variables    ===============================*/
extern float HANDSHAKE_Vd_TM,	// Set Drain pull up voltage. 
			 HANDSHAKE_Vd_NM;	// Set Drain pull up voltage. 

// ======================  Gage Digitizer Variables=============================
extern int SAMPLE_RATE_Hz;
extern float SAMPLE_RATE_s;


//================== Omniswitch User Functions Headers START here ===============
void Close_relay(int);
void Open_relay(int);
void Open_All_Relays();

void mode_change(void);
void DDD_init();
void DDD_Load_Patterns();

void Powerup_to_trim_primary();
void Powerdown_from_trim_primary();
void Trim_Anti_fuse_primary(float*);
void DDD_Clock_UV_Antifuse(int);
void VBPP_Power_Up_w_Test_Mode(int, int);
void Powerup_Primary_in_Testmode(int);
void Observe_Vpin_Internal_Signals();

void Power_Up_Primary_Observe_Mode(int);
void Power_Up_Primary_BypassWL_TM5(int);
void Power_Up_Primary_BypassWL_TM5_New(int ILIM_Select);
void Power_Up_Primary_BypassWL_TM5_SoftStart(int);
void Power_Up_Primary_BypassWL_TM5_18kHz(int ILIM_Select);
void Power_Up_Primary_BypassWL_TM5_Partial(int ILIM_Select);
void Power_Up_Primary_Normal_Mode(int);
void Power_Down_Primary();
void Power_Down_Everything();
void Power_Down_Everything_Except_Buf_Clamp();
void Force_Neg_Pulses_FW_DDD (float, float);
void Force_Neg_Pulses_FW_DDD_x (float High_lev, float Low_lev);
void Force_Vpin_Pulses_nTimes (int);
void Force_Vpin_Pulses_5_Times (float, float);

void Skip_Wait_and_Listen();
float Rdson_Buffer_Cal(float);

//void search_VBPP_th( float*, float*, float*, float*, float* );
void search_VBPP_th( float* vBPP_pV, float* vBPP_m, float* vBPP_p, float* vBPP_p_iHVoff, float* vBPP_vshuntPUseq, float LowerLimit);
void search_VBPS_P_th( float* vBPS_p, int Measure_BPS_IS1_nsw_s);
void search_VBPS_M_th_Inno4( float* );
void search_VBPS_Reset(float *);
void search_VBPP_Reset(float *);
void VBPP_Negative_Cycle();
void VBPP_ramp_up(float, float, float);
void VBPP_ramp_down(float, float, float);
void VBPP_DVI_ramp_down(float vstart, float vstop, float vstep);
void VBPS_ramp_up(float, float, float);
void VBPS_ramp_down(float, float, float);
void VBD_ramp_up(float vstart, float vstop, float vstep);
void VBD_ramp_down(float vstart, float vstop, float vstep);
void FW_ramp_up(float vstart, float vstop, float vstep);
void uVCC_ramp_down(float vstart, float vstop, float vstep);
void uVCCrampDown(float Vstart, float Vstop, float Vstep);
void uVCCrampUp(float Vstart, float Vstop, float Vstep);
void HVS_ramp_down(float vstart, float vstop, float vstep);
void VBPS_Power_Up(float);
void Power_Up_Secondary(int, double);
void search_SR_th(float *SR_th, float LowerLimit);
//void search_IOVp_Binary(float*);
void search_IOVp_Binary(float *iOVp, float LowerLimit, float UpperLimit);
void search_IOVp_Binary_TurretCB(float*);
void Connect_InvSyn_IM(int);
void Disconnect_InvSyn_IM();
void Create_Awav_xp ( char *, float *,int arr_size, float  samp_rate);
void PV3_CHARGE_ON(int);
void PV3_Check_Charge(int);
void PV3_Connect_Drain_and_DriveON(float Vdrive);
void Convert_Decimal_To_Binary(float Decimal_Value, int *BitArray);
void Convert_16bitBinary_To_Decimal(int *BitArray, int &Decimal_Value);
void Convert_8bitBinary_To_Decimal(int *BitArray, int &Decimal_Value);
void Load_7_Bit_Pattern(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_7_Bit_Pattern_45kHz(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_7_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_8_Bit_Pattern(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_8_Bit_Pattern_45kHz(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_8_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_start, int &DDD_stop);
void Load_16_Bit_Pattern(int *BitArray, int &DDD_hi_start, int &DDD_hi_stop, int &DDD_lo_start, int &DDD_lo_stop);
void Load_16_Bit_Pattern_Force_SCL(int *BitArray, int &DDD_hi_start, int &DDD_hi_stop, int &DDD_lo_start, int &DDD_lo_stop);
void Write_Byte(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN);
void Write_Byte_45kHz(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN);
void Write_Byte_Part_Pulls_SDA_low(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN);
void DSM_Write_Byte(int RegisterName, float RegisterData);
void Write_Word(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN);
void Write_Word_Force_SCL(int RegisterName, float DataHex, int *DataBinaryArray, int HEXorBIN);
void DSM_Write_Word(int RegisterName, float RegisterData);
void Read_Word(int RegisterName, int *BitArray);
int Get_Inductor_ID();
int Get_Loadboard_ID();
int Get_Contactor_ID();
void Initialize_Relays();
void FWrampDown(float Vstart, float Vstop, float Vstep);
void VOUTrampDown(float Vstart, float Vstop, float Vstep);
void VOUTrampDown_Range10V(float Vstart, float Vstop, float Vstep);
void Define_I2C_Registers();
uint32_t DSM_Load_Write_Byte(int RegisterName, float RegisterData);
uint32_t DSM_Load_Write_Word(int RegisterName, float RegisterData);
void MUX20_Test();
void Initialize_Instruments();
//-------------------------------
//HL added ----------------------
void Program_Trim_Register(int *Trim_Register);
void Read_Trim_Register(int *TrimBank);
void Program_All_TrimRegister();
void Program_All_TrimRegister_P();
void Program_Single_TrimRegister(int TrimLocation);
void Program_Single_TrimRegister_P(int TrimLocation);

//-------------------------------
void LoadShadowRegister();
void ReadShadowRegister();
void Data_To_Text_File(int ArraySize, char FileName[], char Arr1_Label[], float Arr1_Data[], char Arr2_Label[], float Arr2_Data[], char Arr3_Label[], float Arr3_Data[], char Arr4_Label[], float Arr4_Data[], char Arr5_Label[], float Arr5_Data[]);
void FunctionsToExecute();

//=================== INNOVI Scan Test functions===========================

void DDD_load_scan_pattern(int Start_Address, int Stop_Address);
void DDD_Run_Scan_Pattern(int Start_Address, int Stop_Address);
void DDD_Compare_Pattern(int *g_Fail_Address,int Start_Address, int Stop_Address);

//=================== INNOSW XP gage digitizer Headers ===================
void BINNO_Gage_ChanAB_setup(float);
void Gage_Find_Ilim(float *, float *, float *, float *, float *);
void Gage_Find_Ilim_18kHz(float *, float *, float *, float *);
//void Gage_Find_Ilim_SSS(float *, float *, float *, float *, float *, float *, float *, float *, float *);
void Gage_Find_Ilim_SSS(float *Idmax_ave, float *tsoft, float *tHandshake, float *fosc_s_min, float *fosc_s_max, float *ilim_min, float *ilim_max, float *fModulation_P, float *Fosc_Sss_P, float UppLimFoscMin, float LowLimFoscMin);
void Gage_Find_SOA(float *, float *);
void Gage_Find_SDS(float *, float *, float *);
//void Gage_Find_tDableOn(float *tDableON, float *FWPK_tVOxDble, float *FWPK_Timer);
void Gage_Find_tDableOn(float *tDableON, float *FWPK_tVOxDble, float *FWPK_Timer, int Freq1Mhz);
void Gage_Find_Dtemp_code(int *Dtemp_code_Decimal, float *tLong_Dtemp, int *Dtemp_HighByte, float *tShort_Dtemp, int *Dtemp_LowByte);
void Gage_Count_Cycles_CHB(float *);
void DChUp_Gage_Find(float *);
void Gage_Find_tOVL(float *);
char* GetCSVPath (const char* dllpath, const char* csvname);

//HL added.
void Gage_Find_ccPFOFF(double *ccPassFEToff_TH, double *ccBoostOff_TH, double *Dcc_TH);
void Gage_Find_CP(double *CP_IS_TH, double *CP_BOFF_TH, double *CP_PFOFF_TH);
void Gage_Find_VbIlim_TH(double *VbIlim_TH);
void Gage_ChanAB_Setup_S(float pin_trig_level, int16 chanA_gain, int chanB_gain);
void Gage_ChanAB_Setup_S2(float pin_trig_level, int16 chanA_gain, int chanB_gain, int sample_rate_in_Hz);

//=================== XP gage PIPULSE Definition STARTS here ===================

//PIPulse class to replace Pulse class removed by LTXC for VATE 7.0 release
enum
{
	PULSE_RISING_EDGE,
	PULSE_FALLING_EDGE,
};
class PIPulse
{
	private:
		int logic ;
		double pulse_width_in_seconds;
	public:
		PIPulse(int logic_ = 0, double pulse_width_ = 10e-6 )
		{	
			logic=0;
			pulse_width_in_seconds=pulse_width_;
		}
		~PIPulse(){};
		bool	do_pulse(void);
};
//=================== XP gage PIPULSE Definition ENDS here ===================
extern	CSHANDLE	hSystem;

//=================== XP gage digitizer func Header STARTS here ===================
void	Gage_init();
void	Gage_Setup_Acquisition_xp ( int sample_rate_in_Hz, int g_SAMPLE_SIZE );
void	Gage_Capture_Data( );
void	Gage_Setup_Chan_A ( int pk_pk_range_in_mV );
void	Gage_Setup_Chan_B ( int pk_pk_range_in_mV );
int		gage_input_control_xp (int16 channel, int16 enable, int16 coupling, int16 gain);
//int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, int16 level, int32 depth);
int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, float level, int32 depth);
void	Gage_Commit ( void );
void	Gage_Start_Capture( int force_capture);
void	Gage_Wait_For_Capture_Complete( void );
void	Gage_Transfer_Data ( int channel_num );
void	Gage_Transfer_DataM ( int channel_num );
void	Gage_Transfer_Data_ilim_states ( int channel_num );
void	Gage_print_error(string text_str);
void	Gage_print_setup(string text_str);
int     Gage_loadtime_setup(void);
void	Gage_cal_table_setup_xp();
void	PrintCaptureTime(string text_str);

void Gage_init_S();
//=================== XP gage digitizer func Header ENDS here ===================

// Declare register names and their addresses. //
	//Primary Registers will be declared later.

	//Registers Addresses
extern int	g_SlaveAddress_P;			//7 bits only. '0001110w/r'  0x1C
extern int	g_SlaveAddress_S;			//7 bits only. '0001101w/r'  0x14
extern int	g_RDADDR;				//WR_Word
extern int	g_CORE_CTRL0;           //WR_Byte
extern int	g_CORE_CTRL1;			//WR_Byte
extern int	g_CORE_CTRL2;			//WR_Byte
extern int	g_TM_CTRL;				//WR_Byte
extern int	g_SIG_CTRL;				//WR_Byte
extern int	g_ANA_CTRL_0;			//WR_Word
extern int	g_ANA_CTRL_1;			//WR_Word
extern int	g_I2C_CTRL;				//WR_Byte
extern int	g_FAULT_CTRL;			//WR_Byte
extern int	g_PINSCL_CTRL;			//WR_Byte
extern int	g_PINSDA_CTRL;			//WR_Byte
extern int  g_RDPIN_FAULT;			//WR_Byte (add by charles from I2CregisterMap of Primary)
extern int	g_PIN1_CFG;				//WR_Byte
extern int	g_EEP_CMD;				//WR_Byte
extern int	g_TM_EN ;				//WR_Word
extern int	g_EEP_W_E0;				//WR_Word
extern int	g_EEP_W_E2;				//WR_Word
extern int	g_EEP_W_E4;				//WR_Word
extern int	g_EEP_W_E6;				//WR_Word
extern int	g_EEP_W_E8;				//WR_Word
extern int	g_EEP_R_C0;				//WR_Word
extern int	g_EEP_R_C2;				//WR_Word
extern int	g_EEP_R_C4;				//WR_Word
extern int	g_EEP_R_C6;				//WR_Word
extern int	g_EEP_R_C8;				//WR_Word
extern int	g_TEST_CTRL1;			//WR_Word
extern int	g_TEST_CTRL2;			//WR_Word
extern int	g_TEST_CTRL3;			//WR_Word
extern int	g_TEST_CTRL4;			//WR_Word

//ReadBack Registers.
extern int	g_READ00;       //RD_Word
extern int	g_READ02;       //RD_Word
extern int	g_READ04;       //RD_Word
extern int	g_READ06;       //RD_Word
extern int	g_READ08;       //RD_Word
extern int	g_READ0A;       //RD_Word
extern int  g_READ0C;       //RD_Word
extern int	g_READ0E;       //RD_Word
extern int	g_READ10;       //RD_Word
extern int	g_READ12;       //RD_Word
extern int	g_READ16;       //RD_Word
extern int	g_READ40;       //RD_Word
extern int	g_READ42;       //RD_Word
extern int	g_READ44;       //RD_Word
extern int	g_READ46;       //RD_Word
extern int	g_READ48;       //RD_Word
extern int	g_READ4A;       //RD_Word
extern int	g_READ4C;       //RD_Word
extern int	g_READ70;       //RD_Word

//////
////////---------------------------------------------------------------------------------------
////////Old codes from INNOVI.  Will need to remove in the future.
////////--------------------------------------------------------------------------------------------
//////extern int g_SlaveAddress; // 7 bits only. '0011000' //
//////extern int g_SlaveAddress; // Broadcast address. 7 bits only. '0000000' //
//////extern int g_RDADDR; // WR_Word //
//////extern int g_FWPK_reg; // WR_Byte //
//////extern int g_VBEN; // WR_Byte //
//////extern int g_MINLD; // WR_Byte //
//////extern int g_VDIS; // WR_Byte //
//////extern int g_Self_Destruct; // WR_Byte //
//////extern int g_Fast_VI_Command; // WR_Byte //
//////extern int g_CVO_mode; // WR_Byte, Rev2 silicon //
//////extern int g_CV_reg; // WR_Word //
//////extern int g_OVA;
//////extern int g_UVA;
//////extern int g_CDC; // WR_Byte //
//////extern int g_CC_reg;
//////extern int g_VPK_reg;
//////extern int g_OVL; // WR_Byte //
//////extern int g_UVL; // WR_Byte //
//////extern int g_CCSCL; // WR_Byte //
//////extern int g_ISSC; // WR_Byte //
//////extern int g_UVL_Timer; // WR_Byte //
//////extern int g_Watchdog_Timer; // WR_Byte //
//////extern int g_CVO_response; // WR_Byte, Rev2 silicon //
//////extern int g_CVO_timer; // WR_Byte, Rev2 silicon //
//////extern int g_Interrupt_Mask; // WR_Byte, Rev2 silicon //
//////extern int g_OTP; // WR_Byte, Rev2 silicon //
//////extern int g_fast_cc_offset; // WR_Byte //
//////extern int g_loop_speed_set1; // WR_Word //
//////extern int g_loop_speed_set2; // WR_Word //
//////extern int g_TM_CTRL; // WR_Word //
//////extern int g_TM_SEL; // WR_Word //
//////extern int g_TM_DAC; // WR_Byte //
//////extern int g_TM_ANA; // WR_Word, Rev2 silicon //
//////extern int g_EEP_CMD; // WR_Byte //	
//////extern int g_TM_EN; // WR_Word //
//////
//////// Define register names and their addresses. //
//////// EEPROM shadow registers //	
//////extern int g_SREG0; // WR_Word //
//////extern int g_SREG1; // WR_Word //
//////extern int g_SREG2; // WR_Word //
//////extern int g_SREG3; // WR_Word //
//////extern int g_SREG4; // WR_Word //
//////extern int g_SREG5; // WR_Word //
//////extern int g_SREG6; // WR_Word //
//////
//////// Define register names and their addresses. //
//////// Read Back Registers //	
//////extern int g_READ0; //RD_Word //
//////extern int g_READ1; //RD_Word //
//////extern int g_READ2; //RD_Word //
//////extern int g_READ3; //RD_Word //
//////extern int g_READ4; //RD_Word //
//////extern int g_READ5; //RD_Word //
//////extern int g_READ6; //RD_Word //
//////extern int g_READ7; //RD_Word //
//////extern int g_READ8; //RD_Word //
//////extern int g_READ9; //RD_Word //
//////extern int g_READ10; //RD_Word //
//////extern int g_READ11; //RD_Word //
//////extern int g_READ12; //RD_Word //
//////extern int g_READ13; //RD_Word //
//////extern int g_READ14; //RD_Word //
//////extern int g_READ15; //RD_Word //
//////extern int g_READ16; //RD_Word //
//////extern int g_READ17; //RD_Word //
//////extern int g_READ18; //RD_Word, Rev.1 silicon only //
//////extern int g_READ19; //RD_Word, Rev.1 silicon only //
//////extern int g_READ20; //RD_Word, Rev.1 silicon only //
//////extern int g_READ21; //RD_Word, Rev.1 silicon only //
//////extern int g_READ22; //RD_Word, Rev.1 silicon only //
//////extern int g_READ40; // WR_Word, Rev2 silicon //
//////extern int g_READ41; // WR_Word, Rev2 silicon //
//////extern int g_READ42; // WR_Word, Rev2 silicon //
//////extern int g_READ43; // WR_Word, Rev2 silicon //
//////extern int g_READ44; // WR_Word, Rev2 silicon //
//////extern int g_READ45; // WR_Word, Rev2 silicon //
//////extern int g_READ46; // WR_Word, Rev2 silicon //
//////extern int g_READ47; // WR_Word, Rev2 silicon //
//////extern int g_READ56; // WR_Word, Rev2 silicon //
//////extern int g_READ57; // WR_Word, Rev2 silicon //
//////extern int g_READ58; // WR_Word, Rev2 silicon //
//////extern int g_READ59; // WR_Word, Rev2 silicon //
//////extern int g_READ60; // WR_Word, Rev2 silicon //
//////extern int g_READ61; // WR_Word, Rev2 silicon //
//////extern int g_READ62; // WR_Word, Rev2 silicon //
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// Passwords and keys for entering test mode. //
// To enter test mode, for write the g_TestMode_Password followed by g_TestMode_Enter. //
// To exit test mode, for write the g_TestMode_Password followed by g_TestMode_Exit. //
extern int g_TestMode_Password; // Word //
extern int g_TestMode_Enter; // Word.  Key to enter test mode. //
extern int g_TestMode_Exit; // Word.  Key to exit test mode. //
extern int g_SR_Enable; //Word. Enable SR drive before entering scan mode.
extern int g_ScanMode_Enter;//Word. Key to enter Scan mode.//

// Declare Global Variables for FunctionsToExecute() function. //
extern int g_Fn_aFirst;
extern int g_Fn_Continuity;
extern int g_Fn_Leakage;
extern int g_Fn_ScanChain;
extern int g_Fn_BV_Vpin;
extern int g_Fn_BV_FW;
extern int g_Fn_BV_Drain;
extern int g_Fn_VBP_Init;
extern int g_Fn_BPS_STRESS;
extern int g_Fn_BPP_STRESS;
extern int g_Fn_IzPre;
extern int g_Fn_Feature_Trim_P;
extern int g_Fn_Feature_Trim_S;
extern int g_Fn_OVT;
extern int g_Fn_IOV_Pre_P;
extern int g_Fn_IOV_Trim;
extern int g_Fn_IOV_post_P;
extern int g_Fn_Fosc_Pre_P;
extern int g_Fn_Fosc_Trim_P;
extern int g_Fn_Fosc_post_P;
extern int g_Fn_tOVL_Pre_S;
extern int g_Fn_tOVL_Trim;
extern int g_Fn_tOVL_post_S;
extern int g_Fn_OSC_Pt;
extern int g_Fn_Fosc_Pre_S;
extern int g_Fn_Fosc_Trim_S;
extern int g_Fn_Fosc_post_S;
extern int g_Fn_ILIM_Pre;
extern int g_Fn_ILIM_Trim;
extern int g_Fn_ILIM;
extern int g_Fn_CV_Pre;
extern int g_Fn_ISvth_Pre_S;
extern int g_Fn_CDC_Pre;
extern int g_Fn_nDAC_Pt;
extern int g_Fn_pDAC_Pt;
extern int g_Fn_DofA_Pt;
extern int g_Fn_IsDAC_Pt;
extern int g_Fn_Gain_Pt;
extern int g_Fn_CCoff_Pt;
extern int g_Fn_IsCal_Pt;
extern int g_Fn_ADC_Pt;
extern int g_Fn_ADC_Final;
extern int g_Fn_EEPROM_Write;
extern int g_Fn_IzPost;
extern int g_SoftStart;
extern int g_Fn_Isvth3X_AR_ISSC;
extern int g_Fn_VBP_Supply;
extern int g_Fn_IBP_Supply;
extern int g_Fn_IOV_IUV_OT;
extern int g_Fn_FOSC_Ton_ARST;
extern int g_Fn_FWPK;
extern int g_Fn_SR_Delay_tREQinh;
extern int g_Fn_Vesr;
extern int g_Fn_SOA_SDS_TW50;
extern int g_Fn_Iout;
extern int g_Fn_CV_nDAC_pDAC;
extern int g_Fn_Vovp;
extern int g_Fn_UVP;
extern int g_Fn_VPK;
extern int g_Fn_CDC_Final;
extern int g_Fn_VBD_uVCC;
extern int g_Fn_ADC_Linearity;
extern int g_Fn_OSC_Final;
extern int g_Fn_DofA_Final;
extern int g_Fn_IsDAC_Final;
extern int g_Fn_Gain_Final;
extern int g_Fn_Ccoff_Final;
extern int g_Fn_IsCal_Final;
extern int g_Fn_DATT;
extern int g_Fn_zLast;

// Declare global variables //
// ---------------------------
// HL --added-----------------
extern int g_TrimRegister_P[80];
extern int g_S_TrimRegister[80];
extern int g_TrimRegisterTemp_P[80];
extern int g_S_TrimRegisterTemp[80];
extern int g_S_EEpromTemp[80];
//----------------------------
extern int g_binary_array[30];
extern int g_Read_HiByte_Mem[30];
extern int g_Read_LoByte_Mem[30];
extern int g_ShadowRegister[112];
extern const int HEX;
extern const int BIN;
extern float g_begintime;
extern float g_endtime;
extern int g_Error_Flag;
extern float g_Fosc_Sim_S;
extern float g_Fosc_Sim_Chg_S;
extern float g_CCoff_Pt_S;
extern float g_IsDAC_Pt_S;
extern float g_IsCal_Pt_S;
extern float g_Gain_Pt_S;
extern float g_DofA_Pt_S;
extern float g_pDAC_Target_S;
extern float g_pDAC_Pt_S;
extern float g_nDAC_Target_S;
extern float g_nDAC_Pt_S;
extern float g_CCoff_Target_S;
extern float g_CV_pt_S;
extern float g_OSC_Pt_S;
extern float g_ISvth3X_pt_S;
extern float g_CDC_Target_S;
extern float g_CV_Final_S;
extern float g_CDC_Pt_S;
extern float g_Framework_Rev;
extern float g_IsDAC_final;
extern float g_Gain_Final;
extern bool g_DDD_Load_Finished;
extern float g_IsDAC_Sim_S;
extern CMicroTimer g_mytimer; // Class used for measuring time intervals //
extern int g_PartFailed;
extern int g_Save_Awav_TextDebug_ALL;
extern int g_Save_Awav_TextDebug_Dtemp;
extern int g_xChk_P[100];
extern float g_ILIM_S;
extern float g_DDD_High;
extern float g_DDD_Low;
//extern float g_SoftStartTime;
extern float g_ADC_Pt;
extern float g_ADC_Final;
extern float g_Voffset;
extern float g_tOVP_S;
extern int g_EEpt_ShadReg0;
extern int g_EEpt_ShadReg1;
extern int g_EEpt_ShadReg2;
extern int g_EEpt_ShadReg3;
extern int g_EEpt_ShadReg4;
extern int g_EEpt_ShadReg5;
extern int g_EEpt_ShadReg6;
extern int g_EEpt_ShadReg7;
extern int g_EEpt_ShadReg8;
extern int g_EEpt_ShadReg9;
extern int g_EEpt_ShadReg10;
extern int g_EEpt_ShadReg11;
extern int g_EEpt_ShadReg12;
extern int g_EEpt_ShadReg13;
extern int g_EEpt_ShadReg14;
extern int g_EEpt_ShadReg15;
extern int g_EEpt_ShadReg16;
extern int g_EEpt_ShadReg17;
extern int g_EEpt_ShadReg18;
extern int g_EEpt_ShadReg19;
extern int g_EEpt_ShadReg20;
extern int g_EEpt_ShadReg21;
extern int g_EEpt_ShadReg22;
extern int g_EEpt_ShadReg23;
extern int g_EEpt_ShadReg24;
extern int g_EEpt_ShadReg25;
extern int g_EEpt_ShadReg26;
extern int g_EEpt_ShadReg27;
extern int g_EEpt_ShadReg28;
extern int g_EEpt_ShadReg29;
extern int g_EEpt_ShadReg30;
extern int g_EEpt_ShadReg31;
extern int g_EEpt_ShadReg32;
extern int g_EEpt_ShadReg33;
extern int g_EEpt_ShadReg34;
extern int g_EEpt_ShadReg35;
extern int g_EEpt_ShadReg36;
extern int g_EEpt_ShadReg37;
extern int g_EEpt_ShadReg38;
extern int g_EEpt_ShadReg39;
extern int g_EEpt_ShadReg40;
extern int g_EEpt_ShadReg41;
extern int g_EEpt_ShadReg42;
extern int g_EEpt_ShadReg43;
extern int g_EEpt_ShadReg44;
extern int g_EEpt_ShadReg45;
extern int g_EEpt_ShadReg46;
extern int g_EEpt_ShadReg47;
extern int g_EEpt_ShadReg48;
extern int g_EEpt_ShadReg49;
extern int g_EEpt_ShadReg50;
extern int g_EEpt_ShadReg51;
extern int g_EEpt_ShadReg52;
extern int g_EEpt_ShadReg53;
extern int g_EEpt_ShadReg54;
extern int g_EEpt_ShadReg55;
extern int g_EEpt_ShadReg56;
extern int g_EEpt_ShadReg57;
extern int g_EEpt_ShadReg58;
extern int g_EEpt_ShadReg59;
extern int g_EEpt_ShadReg60;
extern int g_EEpt_ShadReg61;
extern int g_EEpt_ShadReg62;
extern int g_EEpt_ShadReg63;
extern int g_EEpt_ShadReg64;
extern int g_EEpt_ShadReg65;
extern int g_EEpt_ShadReg66;
extern int g_EEpt_ShadReg67;
extern int g_EEpt_ShadReg68;
extern int g_EEpt_ShadReg69;
extern int g_EEpt_ShadReg70;
extern int g_EEpt_ShadReg71;
extern int g_EEpt_ShadReg72;
extern int g_EEpt_ShadReg73;
extern int g_EEpt_ShadReg74;
extern int g_EEpt_ShadReg75;
extern int g_EEpt_ShadReg76;
extern int g_EEpt_ShadReg77;
extern int g_EEpt_ShadReg78;
extern int g_EEpt_ShadReg79;
extern int g_EEpt_ShadReg80;
extern int g_EEpt_ShadReg81;
extern int g_EEpt_ShadReg82;
extern int g_EEpt_ShadReg83;
extern int g_EEpt_ShadReg84;
extern int g_EEpt_ShadReg85;
extern int g_EEpt_ShadReg86;
extern int g_EEpt_ShadReg87;
extern int g_EEpt_ShadReg88;
extern int g_EEpt_ShadReg89;
extern int g_EEpt_ShadReg90;
extern int g_EEpt_ShadReg91;
extern int g_EEpt_ShadReg92;
extern int g_EEpt_ShadReg93;
extern int g_EEpt_ShadReg94;
extern int g_EEpt_ShadReg95;
extern int g_EEpt_ShadReg96;
extern int g_EEpt_ShadReg97;
extern int g_EEpt_ShadReg98;
extern int g_EEpt_ShadReg99;
extern int g_EEpt_ShadReg100;
extern int g_EEpt_ShadReg101;
extern int g_EEpt_ShadReg102;
extern int g_EEpt_ShadReg103;
extern int g_EEpt_ShadReg104;
extern int g_EEpt_ShadReg105;
extern int g_EEpt_ShadReg106;
extern int g_EEpt_ShadReg107;
extern int g_EEpt_ShadReg108;
extern int g_EEpt_ShadReg109;
extern int g_EEpt_ShadReg110;
extern int g_EEpt_ShadReg111;
extern int g_EE_ShadReg0;
extern int g_EE_ShadReg1;
extern int g_EE_ShadReg2;
extern int g_EE_ShadReg3;
extern int g_EE_ShadReg4;
extern int g_EE_ShadReg5;
extern int g_EE_ShadReg6;
extern int g_EE_ShadReg7;
extern int g_EE_ShadReg8;
extern int g_EE_ShadReg9;
extern int g_EE_ShadReg10;
extern int g_EE_ShadReg11;
extern int g_EE_ShadReg12;
extern int g_EE_ShadReg13;
extern int g_EE_ShadReg14;
extern int g_EE_ShadReg15;
extern int g_EE_ShadReg16;
extern int g_EE_ShadReg17;
extern int g_EE_ShadReg18;
extern int g_EE_ShadReg19;
extern int g_EE_ShadReg20;
extern int g_EE_ShadReg21;
extern int g_EE_ShadReg22;
extern int g_EE_ShadReg23;
extern int g_EE_ShadReg24;
extern int g_EE_ShadReg25;
extern int g_EE_ShadReg26;
extern int g_EE_ShadReg27;
extern int g_EE_ShadReg28;
extern int g_EE_ShadReg29;
extern int g_EE_ShadReg30;
extern int g_EE_ShadReg31;
extern int g_EE_ShadReg32;
extern int g_EE_ShadReg33;
extern int g_EE_ShadReg34;
extern int g_EE_ShadReg35;
extern int g_EE_ShadReg36;
extern int g_EE_ShadReg37;
extern int g_EE_ShadReg38;
extern int g_EE_ShadReg39;
extern int g_EE_ShadReg40;
extern int g_EE_ShadReg41;
extern int g_EE_ShadReg42;
extern int g_EE_ShadReg43;
extern int g_EE_ShadReg44;
extern int g_EE_ShadReg45;
extern int g_EE_ShadReg46;
extern int g_EE_ShadReg47;
extern int g_EE_ShadReg48;
extern int g_EE_ShadReg49;
extern int g_EE_ShadReg50;
extern int g_EE_ShadReg51;
extern int g_EE_ShadReg52;
extern int g_EE_ShadReg53;
extern int g_EE_ShadReg54;
extern int g_EE_ShadReg55;
extern int g_EE_ShadReg56;
extern int g_EE_ShadReg57;
extern int g_EE_ShadReg58;
extern int g_EE_ShadReg59;
extern int g_EE_ShadReg60;
extern int g_EE_ShadReg61;
extern int g_EE_ShadReg62;
extern int g_EE_ShadReg63;
extern int g_EE_ShadReg64;
extern int g_EE_ShadReg65;
extern int g_EE_ShadReg66;
extern int g_EE_ShadReg67;
extern int g_EE_ShadReg68;
extern int g_EE_ShadReg69;
extern int g_EE_ShadReg70;
extern int g_EE_ShadReg71;
extern int g_EE_ShadReg72;
extern int g_EE_ShadReg73;
extern int g_EE_ShadReg74;
extern int g_EE_ShadReg75;
extern int g_EE_ShadReg76;
extern int g_EE_ShadReg77;
extern int g_EE_ShadReg78;
extern int g_EE_ShadReg79;
extern int g_EE_ShadReg80;
extern int g_EE_ShadReg81;
extern int g_EE_ShadReg82;
extern int g_EE_ShadReg83;
extern int g_EE_ShadReg84;
extern int g_EE_ShadReg85;
extern int g_EE_ShadReg86;
extern int g_EE_ShadReg87;
extern int g_EE_ShadReg88;
extern int g_EE_ShadReg89;
extern int g_EE_ShadReg90;
extern int g_EE_ShadReg91;
extern int g_EE_ShadReg92;
extern int g_EE_ShadReg93;
extern int g_EE_ShadReg94;
extern int g_EE_ShadReg95;
extern int g_EE_ShadReg96;
extern int g_EE_ShadReg97;
extern int g_EE_ShadReg98;
extern int g_EE_ShadReg99;
extern int g_EE_ShadReg100;
extern int g_EE_ShadReg101;
extern int g_EE_ShadReg102;
extern int g_EE_ShadReg103;
extern int g_EE_ShadReg104;
extern int g_EE_ShadReg105;
extern int g_EE_ShadReg106;
extern int g_EE_ShadReg107;
extern int g_EE_ShadReg108;
extern int g_EE_ShadReg109;
extern int g_EE_ShadReg110;
extern int g_EE_ShadReg111;
extern int g_Bit63_Change_Flag;
extern float g_ISVTH;
extern float g_CCoff_final;
extern int g_FirstPartPass;
extern int g_HP_meter_cal_done;
extern float g_ISbuff_Gain32;
extern float g_ISbuff_GainMid;
extern float g_ISbuff_GainLow;
extern float g_IsCal_final;
extern float g_ENG1;
extern float g_ENG2;
extern float g_ENG3;
extern float g_ENG4;
extern float g_ENG5;
extern float g_ENG6;
extern float g_ENG7;
extern float g_ENG8;
extern float g_ENG9;
extern float g_ENG10;
extern int g_LimitSetChanged;
extern float g_I2C_Pullup;
extern float g_VBPP_P_S_FailFlag;

extern float g_ILL_FW;
extern float g_ILL_FB;
extern float g_ILH_FB;
extern float g_ILL_VO;
extern float g_ILL_IS;
extern float g_ILH_VBD;
extern float g_ILL_VBD;
extern float g_ILH_SDA;
extern float g_ILL_SDA;
extern float g_ILH_SCL;
extern float g_ILL_SCL;
extern int g_DDDwait;
extern int g_DDDwait_b;
extern float SetDebugFlow;
extern STRING g_PrgName; // .prg name //
extern int g_LB_type;
extern int g_CB_type;
extern float g_R1_ohms;
extern int g_Site;
extern float g_InvSyn_Fall;
extern float g_R1_current;
extern int g_Enable_ScanChain;
extern float g_BPP_Stress_Volt;
extern float g_BPP_IS1_Pre;
extern float g_BPP_IS1_Diff;
extern float g_BPP_IS2_Pre;
extern float g_BPP_IS2_Diff;
extern float g_iLeak_V_Pre;
extern float g_iLeak_V_Post;
extern float g_iLeak_V_Delta;
extern float g_BPS_IS1_Pre;
extern float g_BPS_IS2_Pre;
extern float g_DSM_Library_Version;
extern float g_DSM_Firmware_Version;
extern float g_GNDRes_Se;
extern float g_GNDRes_Pri;
extern float g_Inv_threshold;
extern float g_FWmeasV;
//extern float g_Vshunt_2mA_P_Final;
extern uint32_t g_DSM_address;
extern uint32_t g_Last_DSM_Address;


// DDD start/stop variables //
extern int g_StartBit_start;
extern int g_StartBit_stop;
extern int g_StartBit_start_45kHz;
extern int g_StartBit_stop_45kHz;
extern int g_StartBit_start_Force_SCL;
extern int g_StartBit_stop_Force_SCL;
extern int g_SlaveAddress_start;
extern int g_SlaveAddress_stop;
extern int g_SlaveAddress_start_45kHz;
extern int g_SlaveAddress_stop_45kHz;
extern int g_SlaveAddress_start_Force_SCL;
extern int g_SlaveAddress_stop_Force_SCL;
extern int g_WriteBit_start;
extern int g_WriteBit_stop;
extern int g_WriteBit_start_45kHz;
extern int g_WriteBit_stop_45kHz;
extern int g_WriteBit_start_Force_SCL;
extern int g_WriteBit_stop_Force_SCL;
extern int g_ReadBit_start;
extern int g_ReadBit_stop;
extern int g_Read_HiByte_start;
extern int g_Read_HiByte_stop;
extern int g_Read_LoByte_start;
extern int g_Read_LoByte_stop;
extern int g_SlaveAck_start;
extern int g_SlaveAck_stop;
extern int g_SlaveAck_start_45kHz;
extern int g_SlaveAck_stop_45kHz;
extern int g_SlaveAck_start_Force_SCL;
extern int g_SlaveAck_stop_Force_SCL;
extern int g_MasterAck_start;
extern int g_MasterAck_stop;
extern int g_MasterNack_start;
extern int g_MasterNack_stop;
extern int g_StopBit_start;
extern int g_StopBit_stop;
extern int g_StopBit_start_45kHz;
extern int g_StopBit_stop_45kHz;
extern int g_StopBit_start_Force_SCL;
extern int g_StopBit_stop_Force_SCL;
extern int g_RDADDR_start;
extern int g_RDADDR_stop;
extern int g_FWPK_start;
extern int g_FWPK_stop;
extern int g_VBEN_start;
extern int g_VBEN_stop;
extern int g_MINLD_start;
extern int g_MINLD_stop;
extern int g_VDIS_start;
extern int g_VDIS_stop;
extern int g_Self_Destruct_start;
extern int g_Self_Destruct_stop;
extern int g_Fast_VI_Command_start;
extern int g_Fast_VI_Command_stop;
extern int g_CVO_mode_start;
extern int g_CVO_mode_stop;
extern int g_CV_start;
extern int g_CV_stop;
extern int g_OVA_start;
extern int g_OVA_stop;
extern int g_UVA_start;
extern int g_UVA_stop;
extern int g_CDC_start;
extern int g_CDC_stop;
extern int g_CDC_start_45kHz;
extern int g_CDC_stop_45kHz;
extern int g_CC_start;
extern int g_CC_stop;
extern int g_VPK_start;
extern int g_VPK_stop;
extern int g_OVL_start;
extern int g_OVL_stop;
extern int g_UVL_start;
extern int g_UVL_stop;
extern int g_CCSCL_start;
extern int g_CCSCL_stop;
extern int g_ISSC_start;
extern int g_ISSC_stop;
extern int g_UVL_Timer_start;
extern int g_UVL_Timer_stop;
extern int g_Watchdog_Timer_start;
extern int g_Watchdog_Timer_stop;
extern int g_CVO_response_start;
extern int g_CVO_response_stop;
extern int g_CVO_timer_start;
extern int g_CVO_timer_stop;
extern int g_Interrupt_Mask_start;
extern int g_Interrupt_Mask_stop;
extern int g_OTP_start;
extern int g_OTP_stop;
extern int g_fast_cc_offset_start;
extern int g_fast_cc_offset_stop;
extern int g_loop_speed_set1_start;
extern int g_loop_speed_set1_stop;
extern int g_loop_speed_set2_start;
extern int g_loop_speed_set2_stop;
extern int g_TM_CTRL_start;
extern int g_TM_CTRL_stop;
extern int g_TM_CTRL_start_Force_SCL;
extern int g_TM_CTRL_stop_Force_SCL;
extern int g_TM_SEL_start;
extern int g_TM_SEL_stop;
extern int g_TM_DAC_start;
extern int g_TM_DAC_stop;
extern int g_TM_ANA_start;
extern int g_TM_ANA_stop;
extern int g_EEP_CMD_start;
extern int g_EEP_CMD_stop;
extern int g_TM_EN_start;
extern int g_TM_EN_stop;
extern int g_TM_EN_start_Force_SCL;
extern int g_TM_EN_stop_Force_SCL;
extern int g_SREG0_start;
extern int g_SREG0_stop;
extern int g_SREG1_start;
extern int g_SREG1_stop;
extern int g_SREG2_start;
extern int g_SREG2_stop;
extern int g_SREG3_start;
extern int g_SREG3_stop;
extern int g_SREG4_start;
extern int g_SREG4_stop;
extern int g_SREG5_start;
extern int g_SREG5_stop;
extern int g_SREG6_start;
extern int g_SREG6_stop;
extern int g_READ0_start;
extern int g_READ0_stop;
extern int g_READ1_start;
extern int g_READ1_stop;
extern int g_READ2_start;
extern int g_READ2_stop;
extern int g_READ3_start;
extern int g_READ3_stop;
extern int g_READ4_start;
extern int g_READ4_stop;
extern int g_READ5_start;
extern int g_READ5_stop;
extern int g_READ6_start;
extern int g_READ6_stop;
extern int g_READ7_start;
extern int g_READ7_stop;
extern int g_READ8_start;
extern int g_READ8_stop;
extern int g_READ9_start;
extern int g_READ9_stop;
extern int g_READ10_start;
extern int g_READ10_stop;
extern int g_READ11_start;
extern int g_READ11_stop;
extern int g_READ12_start;
extern int g_READ12_stop;
extern int g_READ13_start;
extern int g_READ13_stop;
extern int g_READ14_start;
extern int g_READ14_stop;
extern int g_READ15_start;
extern int g_READ15_stop;
extern int g_READ16_start;
extern int g_READ16_stop;
extern int g_READ17_start;
extern int g_READ17_stop;
extern int g_READ18_start;
extern int g_READ18_stop;
extern int g_READ19_start;
extern int g_READ19_stop;
extern int g_READ20_start;
extern int g_READ20_stop;
extern int g_READ21_start;
extern int g_READ21_stop;
extern int g_READ22_start;
extern int g_READ22_stop;
extern int g_READ40_start;
extern int g_READ40_stop;
extern int g_READ41_start;
extern int g_READ41_stop;
extern int g_READ42_start;
extern int g_READ42_stop;
extern int g_READ43_start;
extern int g_READ43_stop;
extern int g_READ44_start;
extern int g_READ44_stop;
extern int g_READ45_start;
extern int g_READ45_stop;
extern int g_READ46_start;
extern int g_READ46_stop;
extern int g_READ47_start;
extern int g_READ47_stop;
extern int g_READ56_start;
extern int g_READ56_stop;
extern int g_READ57_start;
extern int g_READ57_stop;
extern int g_READ58_start;
extern int g_READ58_stop;
extern int g_READ59_start;
extern int g_READ59_stop;
extern int g_READ60_start;
extern int g_READ60_stop;
extern int g_READ61_start;
extern int g_READ61_stop;
extern int g_READ62_start;
extern int g_READ62_stop;
extern int g_SDA_SCL_Low_start;
extern int g_SDA_SCL_Low_stop;
extern int g_SDA_hiz_SCL_low_start;
extern int g_SDA_hiz_SCL_low_stop;
extern int g_SDA_hiz_SCL_hiz_start;
extern int g_SDA_hiz_SCL_hiz_stop;
//extern int g_BPShigh_start;
//extern int g_BPShigh_stop;
//extern int g_All_HIZ_start;
//extern int g_All_HIZ_stop;
//extern int g_SDA_SCL_HIZ_start;
//extern int g_SDA_SCL_HIZ_stop;

// DSM start/stop variables, Word //
extern uint32_t g_RDADDR_READ0_start_DSM;
extern uint32_t g_RDADDR_READ0_stop_DSM;
extern uint32_t g_RDADDR_READ1_start_DSM;
extern uint32_t g_RDADDR_READ1_stop_DSM;
extern uint32_t g_RDADDR_READ2_start_DSM;
extern uint32_t g_RDADDR_READ2_stop_DSM;
extern uint32_t g_RDADDR_READ3_start_DSM;
extern uint32_t g_RDADDR_READ3_stop_DSM;
extern uint32_t g_RDADDR_READ4_start_DSM;
extern uint32_t g_RDADDR_READ4_stop_DSM;
extern uint32_t g_RDADDR_READ5_start_DSM;
extern uint32_t g_RDADDR_READ5_stop_DSM;
extern uint32_t g_RDADDR_READ6_start_DSM;
extern uint32_t g_RDADDR_READ6_stop_DSM;
extern uint32_t g_RDADDR_READ7_start_DSM;
extern uint32_t g_RDADDR_READ7_stop_DSM;
extern uint32_t g_RDADDR_READ8_start_DSM;
extern uint32_t g_RDADDR_READ8_stop_DSM;
extern uint32_t g_RDADDR_READ9_start_DSM;
extern uint32_t g_RDADDR_READ9_stop_DSM;
extern uint32_t g_RDADDR_READ10_start_DSM;
extern uint32_t g_RDADDR_READ10_stop_DSM;
extern uint32_t g_RDADDR_READ11_start_DSM;
extern uint32_t g_RDADDR_READ11_stop_DSM;
extern uint32_t g_RDADDR_READ12_start_DSM;
extern uint32_t g_RDADDR_READ12_stop_DSM;
extern uint32_t g_RDADDR_READ13_start_DSM;
extern uint32_t g_RDADDR_READ13_stop_DSM;
extern uint32_t g_RDADDR_READ14_start_DSM;
extern uint32_t g_RDADDR_READ14_stop_DSM;
extern uint32_t g_RDADDR_READ56_start_DSM;
extern uint32_t g_RDADDR_READ56_stop_DSM;
extern uint32_t g_RDADDR_READ57_start_DSM;
extern uint32_t g_RDADDR_READ57_stop_DSM;
extern uint32_t g_RDADDR_READ58_start_DSM;
extern uint32_t g_RDADDR_READ58_stop_DSM;
extern uint32_t g_RDADDR_READ59_start_DSM;
extern uint32_t g_RDADDR_READ59_stop_DSM;
extern uint32_t g_RDADDR_READ60_start_DSM;
extern uint32_t g_RDADDR_READ60_stop_DSM;
extern uint32_t g_RDADDR_READ61_start_DSM;
extern uint32_t g_RDADDR_READ61_stop_DSM;
extern uint32_t g_RDADDR_READ62_start_DSM;
extern uint32_t g_RDADDR_READ62_stop_DSM;
extern uint32_t g_TM_ANA_0x0000_start_DSM;
extern uint32_t g_TM_ANA_0x0000_stop_DSM;
extern uint32_t g_TM_ANA_0x0120_start_DSM;
extern uint32_t g_TM_ANA_0x0120_stop_DSM;
extern uint32_t g_TM_ANA_0x0130_start_DSM;
extern uint32_t g_TM_ANA_0x0130_stop_DSM;
extern uint32_t g_TM_ANA_0x0134_start_DSM;
extern uint32_t g_TM_ANA_0x0134_stop_DSM;
extern uint32_t g_TM_ANA_0x0138_start_DSM;
extern uint32_t g_TM_ANA_0x0138_stop_DSM;
extern uint32_t g_TM_ANA_0x013C_start_DSM;
extern uint32_t g_TM_ANA_0x013C_stop_DSM;
extern uint32_t g_TM_ANA_0x0934_start_DSM;
extern uint32_t g_TM_ANA_0x0934_stop_DSM;
extern uint32_t g_TM_ANA_SR_Enable_start_DSM;
extern uint32_t g_TM_ANA_SR_Enable_stop_DSM;
extern uint32_t g_TM_CTRL_0x0000_start_DSM;
extern uint32_t g_TM_CTRL_0x0000_stop_DSM;
extern uint32_t g_TM_CTRL_0x0001_start_DSM;
extern uint32_t g_TM_CTRL_0x0001_stop_DSM;
extern uint32_t g_TM_CTRL_0x0004_start_DSM;
extern uint32_t g_TM_CTRL_0x0004_stop_DSM;
extern uint32_t g_TM_CTRL_0x0020_start_DSM;
extern uint32_t g_TM_CTRL_0x0020_stop_DSM;
extern uint32_t g_TM_CTRL_0x0820_start_DSM;
extern uint32_t g_TM_CTRL_0x0820_stop_DSM;
extern uint32_t g_TM_CTRL_0x0828_start_DSM;
extern uint32_t g_TM_CTRL_0x0828_stop_DSM;
extern uint32_t g_TM_CTRL_0x0A22_start_DSM;
extern uint32_t g_TM_CTRL_0x0A22_stop_DSM;
extern uint32_t g_TM_CTRL_0x1800_start_DSM;
extern uint32_t g_TM_CTRL_0x1800_stop_DSM;
extern uint32_t g_TM_CTRL_ScanMode_Enter_start_DSM;
extern uint32_t g_TM_CTRL_ScanMode_Enter_stop_DSM;
extern uint32_t g_TM_EN_TestMode_Password_start_DSM;
extern uint32_t g_TM_EN_TestMode_Password_stop_DSM;
extern uint32_t g_TM_EN_TestMode_Enter_start_DSM;
extern uint32_t g_TM_EN_TestMode_Enter_stop_DSM;
extern uint32_t g_TM_EN_TestMode_Exit_start_DSM;
extern uint32_t g_TM_EN_TestMode_Exit_stop_DSM;
extern uint32_t g_TM_SEL_26_start_DSM;
extern uint32_t g_TM_SEL_26_stop_DSM;
extern uint32_t g_TM_SEL_29_start_DSM;
extern uint32_t g_TM_SEL_29_stop_DSM;
extern uint32_t g_TM_SEL_0x0000_start_DSM;
extern uint32_t g_TM_SEL_0x0000_stop_DSM;
extern uint32_t g_TM_SEL_0x0001_start_DSM;
extern uint32_t g_TM_SEL_0x0001_stop_DSM;
extern uint32_t g_TM_SEL_0x0004_start_DSM;
extern uint32_t g_TM_SEL_0x0004_stop_DSM;
extern uint32_t g_TM_SEL_0x0006_start_DSM;
extern uint32_t g_TM_SEL_0x0006_stop_DSM;
extern uint32_t g_TM_SEL_0x0008_start_DSM;
extern uint32_t g_TM_SEL_0x0008_stop_DSM;
extern uint32_t g_TM_SEL_0x000A_start_DSM;
extern uint32_t g_TM_SEL_0x000A_stop_DSM;
extern uint32_t g_TM_SEL_0x0016_start_DSM;
extern uint32_t g_TM_SEL_0x0016_stop_DSM;
extern uint32_t g_TM_SEL_0x0018_start_DSM;
extern uint32_t g_TM_SEL_0x0018_stop_DSM;
extern uint32_t g_TM_SEL_0x0020_start_DSM;
extern uint32_t g_TM_SEL_0x0020_stop_DSM;
extern uint32_t g_TM_SEL_0x0024_start_DSM;
extern uint32_t g_TM_SEL_0x0024_stop_DSM;
extern uint32_t g_TM_SEL_0x0026_start_DSM;
extern uint32_t g_TM_SEL_0x0026_stop_DSM;
extern uint32_t g_CC_reg_384_start_DSM;
extern uint32_t g_CC_reg_384_stop_DSM;
extern uint32_t g_CC_reg_32941_start_DSM;
extern uint32_t g_CC_reg_32941_stop_DSM;
extern uint32_t g_CV_reg_556_start_DSM;
extern uint32_t g_CV_reg_556_stop_DSM;
extern uint32_t g_CV_reg_756_start_DSM;
extern uint32_t g_CV_reg_756_stop_DSM;
extern uint32_t g_CV_reg_1032_start_DSM;
extern uint32_t g_CV_reg_1032_stop_DSM;
extern uint32_t g_CV_reg_1052_start_DSM;
extern uint32_t g_CV_reg_1052_stop_DSM;
extern uint32_t g_CV_reg_1112_start_DSM;
extern uint32_t g_CV_reg_1112_stop_DSM;
extern uint32_t g_CV_reg_1220_start_DSM;
extern uint32_t g_CV_reg_1220_stop_DSM;
extern uint32_t g_CV_reg_1796_start_DSM;
extern uint32_t g_CV_reg_1796_stop_DSM;
extern uint32_t g_CV_reg_1896_start_DSM;
extern uint32_t g_CV_reg_1896_stop_DSM;
extern uint32_t g_CV_reg_2124_start_DSM;
extern uint32_t g_CV_reg_2124_stop_DSM;
extern uint32_t g_CV_reg_4148_start_DSM;
extern uint32_t g_CV_reg_4148_stop_DSM;
extern uint32_t g_CV_reg_33552_start_DSM;
extern uint32_t g_CV_reg_33552_stop_DSM;
extern uint32_t g_CV_reg_33636_start_DSM;
extern uint32_t g_CV_reg_33636_stop_DSM;
extern uint32_t g_CV_reg_33648_start_DSM;
extern uint32_t g_CV_reg_33648_stop_DSM;
extern uint32_t g_CV_reg_33651_start_DSM;
extern uint32_t g_CV_reg_33651_stop_DSM;
extern uint32_t g_CV_reg_33772_start_DSM;
extern uint32_t g_CV_reg_33772_stop_DSM;
extern uint32_t g_CV_reg_33778_start_DSM;
extern uint32_t g_CV_reg_33778_stop_DSM;
extern uint32_t g_CV_reg_33780_start_DSM;
extern uint32_t g_CV_reg_33780_stop_DSM;
extern uint32_t g_CV_reg_33790_start_DSM;
extern uint32_t g_CV_reg_33790_stop_DSM;
extern uint32_t g_CV_reg_34196_start_DSM;
extern uint32_t g_CV_reg_34196_stop_DSM;
extern uint32_t g_CV_reg_34336_start_DSM;
extern uint32_t g_CV_reg_34336_stop_DSM;
extern uint32_t g_CV_reg_34356_start_DSM;
extern uint32_t g_CV_reg_34356_stop_DSM;
extern uint32_t g_CV_reg_36816_start_DSM;
extern uint32_t g_CV_reg_36816_stop_DSM;
extern uint32_t g_CV_reg_37600_start_DSM;
extern uint32_t g_CV_reg_37600_stop_DSM;
extern uint32_t g_UVA_318_start_DSM;
extern uint32_t g_UVA_318_stop_DSM;
extern uint32_t g_UVA_368_start_DSM;
extern uint32_t g_UVA_368_stop_DSM;
extern uint32_t g_UVA_396_start_DSM;
extern uint32_t g_UVA_396_stop_DSM;
extern uint32_t g_UVA_32838_start_DSM;
extern uint32_t g_UVA_32838_stop_DSM;
extern uint32_t g_UVA_32926_start_DSM;
extern uint32_t g_UVA_32926_stop_DSM;
extern uint32_t g_UVA_32976_start_DSM;
extern uint32_t g_UVA_32976_stop_DSM;
extern uint32_t g_OVA_278_start_DSM;
extern uint32_t g_OVA_278_stop_DSM;
extern uint32_t g_OVA_368_start_DSM;
extern uint32_t g_OVA_368_stop_DSM;
extern uint32_t g_OVA_378_start_DSM;
extern uint32_t g_OVA_378_stop_DSM;
extern uint32_t g_OVA_456_start_DSM;
extern uint32_t g_OVA_456_stop_DSM;
extern uint32_t g_OVA_32830_start_DSM;
extern uint32_t g_OVA_32830_stop_DSM;
extern uint32_t g_OVA_32868_start_DSM;
extern uint32_t g_OVA_32868_stop_DSM;
extern uint32_t g_OVA_32959_start_DSM;
extern uint32_t g_OVA_32959_stop_DSM;
extern uint32_t g_VPK_reg_278_start_DSM;
extern uint32_t g_VPK_reg_278_stop_DSM;
extern uint32_t g_VPK_reg_363_start_DSM;
extern uint32_t g_VPK_reg_363_stop_DSM;
extern uint32_t g_VPK_reg_456_start_DSM;
extern uint32_t g_VPK_reg_456_stop_DSM;
extern uint32_t g_VPK_reg_32868_start_DSM;
extern uint32_t g_VPK_reg_32868_stop_DSM;
extern uint32_t g_VPK_reg_32949_start_DSM;
extern uint32_t g_VPK_reg_32949_stop_DSM;

// DSM start/stop variables, Byte //
extern uint32_t g_CCSCL_0x00_start_DSM;
extern uint32_t g_CCSCL_0x00_stop_DSM;
extern uint32_t g_CDC_0_start_DSM;
extern uint32_t g_CDC_0_stop_DSM;
extern uint32_t g_CDC_1_start_DSM;
extern uint32_t g_CDC_1_stop_DSM;
extern uint32_t g_CDC_2_start_DSM;
extern uint32_t g_CDC_2_stop_DSM;
extern uint32_t g_CDC_4_start_DSM;
extern uint32_t g_CDC_4_stop_DSM;
extern uint32_t g_CDC_8_start_DSM;
extern uint32_t g_CDC_8_stop_DSM;
extern uint32_t g_CDC_11_start_DSM;
extern uint32_t g_CDC_11_stop_DSM;
extern uint32_t g_CDC_12_start_DSM;
extern uint32_t g_CDC_12_stop_DSM;
extern uint32_t g_CVO_mode_0x00_start_DSM;
extern uint32_t g_CVO_mode_0x00_stop_DSM;
extern uint32_t g_CVO_mode_0x01_start_DSM;
extern uint32_t g_CVO_mode_0x01_stop_DSM;
extern uint32_t g_EEP_CMD_0x00_start_DSM;
extern uint32_t g_EEP_CMD_0x00_stop_DSM;
extern uint32_t g_EEP_CMD_0x01_start_DSM;
extern uint32_t g_EEP_CMD_0x01_stop_DSM;
extern uint32_t g_EEP_CMD_0x03_start_DSM;
extern uint32_t g_EEP_CMD_0x03_stop_DSM;
extern uint32_t g_fast_cc_offset_32_start_DSM;
extern uint32_t g_fast_cc_offset_32_stop_DSM;
extern uint32_t g_fast_cc_offset_0x80_start_DSM;
extern uint32_t g_fast_cc_offset_0x80_stop_DSM;
extern uint32_t g_Fast_VI_Command_0x01_start_DSM;
extern uint32_t g_Fast_VI_Command_0x01_stop_DSM;
extern uint32_t g_FWPK_reg_0x00_start_DSM;
extern uint32_t g_FWPK_reg_0x00_stop_DSM;
extern uint32_t g_FWPK_reg_0x01_start_DSM;
extern uint32_t g_FWPK_reg_0x01_stop_DSM;
extern uint32_t g_Interrupt_Mask_0x00_start_DSM;
extern uint32_t g_Interrupt_Mask_0x00_stop_DSM;
extern uint32_t g_Interrupt_Mask_0x01_start_DSM;
extern uint32_t g_Interrupt_Mask_0x01_stop_DSM;
extern uint32_t g_MINLD_0x00_start_DSM;
extern uint32_t g_MINLD_0x00_stop_DSM;
extern uint32_t g_MINLD_0x01_start_DSM;
extern uint32_t g_MINLD_0x01_stop_DSM;
extern uint32_t g_OVL_0x01_start_DSM;
extern uint32_t g_OVL_0x01_stop_DSM;
extern uint32_t g_OVL_0x02_start_DSM;
extern uint32_t g_OVL_0x02_stop_DSM;
extern uint32_t g_TM_DAC_0x00_start_DSM;
extern uint32_t g_TM_DAC_0x00_stop_DSM;
extern uint32_t g_TM_DAC_0x40_start_DSM;
extern uint32_t g_TM_DAC_0x40_stop_DSM;
extern uint32_t g_TM_DAC_0x80_start_DSM;
extern uint32_t g_TM_DAC_0x80_stop_DSM;
extern uint32_t g_UVL_Timer_0x00_start_DSM;
extern uint32_t g_UVL_Timer_0x00_stop_DSM;
extern uint32_t g_UVL_Timer_0x01_start_DSM;
extern uint32_t g_UVL_Timer_0x01_stop_DSM;
extern uint32_t g_UVL_Timer_0x02_start_DSM;
extern uint32_t g_UVL_Timer_0x02_stop_DSM;
extern uint32_t g_UVL_Timer_0x03_start_DSM;
extern uint32_t g_UVL_Timer_0x03_stop_DSM;
extern uint32_t g_VBEN_0x80_start_DSM;
extern uint32_t g_VBEN_0x80_stop_DSM;
extern uint32_t g_VBEN_0x83_start_DSM;
extern uint32_t g_VBEN_0x83_stop_DSM;
extern uint32_t g_VDIS_131_start_DSM;
extern uint32_t g_VDIS_131_stop_DSM;
extern uint32_t g_VDIS_0x83_start_DSM;
extern uint32_t g_VDIS_0x83_stop_DSM;
extern uint32_t g_VDIS_0x8C_start_DSM;
extern uint32_t g_VDIS_0x8C_stop_DSM;
extern uint32_t g_Watchdog_Timer_0x00_start_DSM;
extern uint32_t g_Watchdog_Timer_0x00_stop_DSM;
extern uint32_t g_Watchdog_Timer_0x01_start_DSM;
extern uint32_t g_Watchdog_Timer_0x01_stop_DSM;

//DDD Scan Test Variables
extern int g_Fail_address;
extern int g_row_load;
extern int g_row_compare;
extern int g_pattern_size;
extern double row_length;
extern bool g_Wrong_Scan_Pattern;


// DSM MODULE CODE //
extern bool g_DSM;
extern bool g_No_DSM_USB;
extern uint32_t ScanChain_AddrStart;
extern uint32_t ScanChain_AddrEnd;
// DSM MODULE CODE //







//********************************************************************************
//***********  Start: DSM SPI for Relay Controller  ******************************
//********************************************************************************

	#if defined(_MSC_VER) && (_MSC_VER < 1600) && (!defined(_STDINT)) && (!defined(_STDINT_H))
		typedef unsigned __int8   uint8_t;
		typedef unsigned __int16  uint16_t;
		typedef unsigned __int32  uint32_t;
	#endif

	//////Already defined above.
	//////enum RelayNames
	//////{
	//////	K1x = 0,  //
	//////	K2x, 
	//////	K3x,
	//////	K4x,
	//////	K5x,
	//////	K6x,
	//////	K7x,
	//////	K8x,      // 
	//////	K9x,		 // 
	//////	K10x,
	//////	K11x,
	//////	K12x,
	//////	K13x,
	//////	K14x,
	//////	K15x,
	//////	K16x,	// 
	//////};

	class RelayController
	{
		public:
			RelayController(int num_modules, int hz, int pinswap, int din_edge);
			~RelayController() {};
			void track_relay_states(uint8_t* states);
			void get_relay_states(uint8_t* states);
				
			int open_relay_spi(int drv, int bit);
			int close_relay_spi(int drv, int bit);
			int open_all_relays_spi();
			
		private:
			int write_spi();
		
	};

	////////class BinnoRelayController
	////////{
	////////	public:
	////////		BinnoRelayController(int num_modules, int hz, int pinswap, int din_edge);
	////////		~BinnoRelayController() {};
	////////		uint8_t states[8];
	////////			
	////////		int open_relay_spi(int rly);
	////////		int close_relay_spi(int rly);
	////////		int open_all_relays_spi();


	////////		
	////////	private:
	////////		int init();
	////////		//RelayController relays(0,0,0,0);
	////////		
	////////	
	////////};

//********************************************************************************
//***********  End: DSM SPI for Relay Controller  ********************************
//********************************************************************************
uint16_t	Binno_I2C_read ( uint8_t read_addr );

//void DSM_I2C_Write2(uint8_t reg_addr, uint8_t lower_byte, uint8_t upper_byte = 0x00, int is_it_word = 0);
void DSM_I2C_SREG0_0x7070();
uint16_t DSM_I2C_Read(uint8_t reg_addr);
void DSM_I2C_Write(char byte_or_word, uint8_t reg_addr, uint16_t word_entered);
void End_EEprom_Erase_Secondary();
void Analog_TM_Enable_Primary();
void Analog_TM_Enable_Secondary();

//01/10/19 HL added for Primary Debugging.
void DSM_I2C_Pri_SREG0_0x7070();
void DSM_I2C_Pri_Read(uint8_t reg_addr);
void DSM_I2C_Pri_Write(char byte_or_word, uint8_t reg_addr, uint16_t word_entered);

void Hardware_Check_Binno();

uint16_t Convert_BIN_2_Dec(int *WordArray);

void TrimCode_To_TrimBit(int TrimCode, char TrimParam[99], char p_or_s);
void EEprcode_2_EEprArray(int TrimCode, int *EEpr, int Startbit);
void CV_Search(float &CV_minus1p5pct, float &CV_th, float &CV_plus1p5pct, float vStart, float Step_size);
void Load_10Khz_Pulses();
void Stop_10Khz_Pulses();
void Run_10Khz_Pulses();
void Load_100Khz_Pulses();
void Stop_100Khz_Pulses();
void Run_100Khz_Pulses();
void Load_VbIlim_Pattern();
void Run_VbIlim_Pattern();
void Stop_VbIlim_Pattern();
void Load_FW_DDD_1_Pulse(int StartAddr);
void Run_FW_DDD_1_Pulse(int StartAddr);
void Load_VR_DDD_Step_Pulse(int StartAddr);
void Run_VR_DDD_Step_Pulse(int StartAddr);
float Average_Value(float *Meas_Array, float min_lim, float max_lim);

void Load_30Khz_Pulses_TS();
void Load_80Khz_Pulses_TS();
void Load_100Khz_Pulses_TS();
void Run_30Khz_Pulses_TS();
void Run_80Khz_Pulses_TS();
void Run_100Khz_Pulses_TS();
void Stop_100Khz_Pulses_TS();

//Primary functions
void EEPROM_Write_Enable_P();
void EEPROM_Read_Enable_P();
void PowerUp_I2C_P();
void PowerUp_I2C_S();
void DSM_init_LYT8();
void Setup_Resources_for_I2C_P();
void Power_Down_I2C_P();
void Characterize_vBPPth();


void EEPROM_ERASE_P(float *vErase_th_P);
void EEPROM_BURN_P(float *vBurn_th_P);
void Search_iOVp_P(float *iOVp_th_P);
void Search_iOVm_P(float *iOVm_th_P);
void Search_iUVp_P(float *iUVp_th_P);
void Search_iUVm_P(float *iUVm_th_P);
void BPP_zigzag(float vBPP1, float vBPP2, float vBPP3);
void Regain_I2C_P(int regain_I2C_mode);
void Disable_n_Disconnect_DSMI2C_via(int release_pin);
float search_direction(int up);
void WordArray_Assigned(int *WordArray, int startbit);
float tmu_meas(int hold_off, int arm_delay, float timeout_delay);
void min_value(float *meas_value, int &array_index, int num_loop);
void max_value(float *meas_value, int &array_index, int num_loop);
float BFreq_Meas(int num_loop);
void Set_EEprBit(uint16_t &EEpr_Bank, int bit, int bit_state);
void TestMode_Check(int TM_Chk);
void VR_Detect_B_Search(float &VB, float &VBSkip, float &VStart, float &Vstop, float &Vstep, char B_or_HSG, char Up_or_Dn);
void VR_Detect_A_Search(float &VB1, float &VB2, float &VA0, float &VA1, float &VA2, float &VA3, float &VStart, float &Vstop, float &Vstep);