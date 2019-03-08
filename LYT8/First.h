//==============================================================================
// First.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void First_user_init(test_function& func);

// ***********************************************************

void initialize_First(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	First_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_First(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_aFirst{

	A_fNum_First,				//00
	A_Setup,					//01
	A_Site,						//02
	A_Opcode,					//03
	A_Framework_Rev,			//04
	A_ProcessorType,			//05
	A_Loadboard_ID,				//06
	A_Loadboard_Rev,			//07
	A_Inductor_ID,				//08
	A_Inductor_Rev,				//09
	A_Contactor_ID,				//10
	A_Contactor_Rev,			//11
	A_Handsockt_ID,				//12
	A_Handsockt_Rev,			//13
	A_p_Loop_wait,				//14
	A_p_Char_Enable,			//15
	A_p_Rel_Enable,				//16
	A_p_IOV_Code_P,				//17
	A_p_FOSC_Code_P,			//18
	A_p_TonMin_Code_P,			//19
	A_p_Slope_Code_P,			//20
	A_p_Offset_Code_P,			//21
	A_p_ILIM_Code_P,			//22
	A_p_UV_Code_P,				//23
    A_p_NTC_Code_P,				//24
	A_p_VDDA_Code_S,			//25
	A_p_VREF_Code_S,			//26
	A_p_IRSET_Code_S,			//27
	A_p_nDAC_Code_S,			//28
	A_p_ZTime_Code_S,			//29
	A_p_VADC_Code_S,			//30
	A_p_Clock1M_Code_S,			//31
	A_p_CCoffset_Code_S,		//32
	A_p_VccRef_Code_S,			//33
    A_p_CCPFOFF_Code_S,			//34
	//A_p_FOSC_Code_S,			//35
	//A_p_BFreq_Code_S,			//36
	//A_p_CP_Code_S,				//37
	//A_p_VbILimit_Code_S,		//38
	A_p_Trim_Enable,			//39
	A_p_TstTime_Enble,			//40
	A_Rewrite_EPROM,			//41
	A_ExtraParam1,				//42
	A_ExtraParam2,				//43
	A_BUFgain,					//44
	A_iPV3_Cal_CC90,			//45
	A_iPV3_Cal_CC80,			//46
	A_iPV3_Cal_CC65,			//47
	A_iPV3_Cal_CC55,			//48
	A_DVI2K_ch0_Temp,			//49
	A_DVI2K_ch1_Temp,			//50
	A_Dig_Type,					//51
	A_First_TT					//52
};