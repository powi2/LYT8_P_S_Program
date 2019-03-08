//==============================================================================
// Continuity.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Continuity_user_init(test_function& func);

// ***********************************************************

void initialize_Continuity(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Continuity_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Continuity(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}



// ***********************************************************
enum enum_continuity{
	A_Func_Num_Continuity,
	A_VcontD,
	A_VcontD_p,
	A_VcontD_1mA,
	A_VcontD_Rat,
	A_IcontD,
	A_VcontBPP,
	A_VcontBPP_p,
	A_VcontBPP_1mA,
	A_VcontBPP_Rat,
	A_IcontBPP,
	A_VcontUV,
	A_VcontUV_p,
	A_VcontUV_1mA,
	A_VcontUV_Rat,
	A_IcontUV,
	A_VcontTS,
	A_VcontTS_p,
	A_VcontTS_1mA,
	A_VcontTS_Rat,
	A_IcontTS,
	A_VcontFW,
	A_VcontFW_p,
	A_VcontFW_1mA,
	A_VcontFW_Rat,
	A_IcontFW,
	A_VcontVR,
	A_VcontVR_p,
	A_VcontVR_1mA,
	A_VcontVR_Rat,
	A_IcontVR,
	A_VcontHSG,
	A_VcontHSG_p,
	A_VcontHSG_1mA,
	A_VcontHSG_Rat,
	A_IcontHSG,
	A_VcontB,
	A_VcontB_p,
	A_VcontB_1mA,
	A_VcontB_Rat,
	A_IcontB,
	A_VcontHBP,
	A_VcontHBP_p,
	A_VcontHBP_1mA,
	A_VcontHBP_Rat,
	A_IcontHBP,
	A_VcontFB,
	A_VcontFB_p,
	A_VcontFB_1mA,
	A_VcontFB_Rat,
	A_IcontFB,
	A_VcontBPS,
	A_VcontBPS_p,
	A_VcontBPS_1mA,
	A_VcontBPS_Rat,
	A_IcontBPS,
	A_VcontIS,
	A_VcontIS_p,
	A_VcontIS_1mA,
	A_VcontIS_Rat,
	A_IcontIS,
	A_VcontSDA,
	A_VcontSDA_1mA,
	A_VcontSDA_Rat,
	A_IcontSDA,
	A_VcontSCL,
	A_VcontSCL_1mA,
	A_Vcont_SCL_Rat,
	A_IcontSCL,
	A_GNDRes_Se,
	A_GNDRes_Pri,
A_VcontBPP_cap,
A_VcontBPP_capGNG,
	A_Continuity_TT
};