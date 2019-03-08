//********************************************************************
//********************************************************************
//
//	DIGITAL_SCAN_MODULE.h
//
//	Liam Wall, Test Engineer, Power Integrations UK
//	13th May 2017
//
//	The aim of DIGITAL_SCAN_MODULE is to provide an easy alternative to the DDD module on the ASL.
//	The main feature of the DSM is the ability to perform scan live (4 data outputs & 4 data inputs)
//	The DSM provides 4MByte of flash for vectors to be stored.
//	The DSM also provides I2C / SPI resources.
//
//	DIGITAL_SCAN_MODULE uses the cross platform library simplusb - developed by PIUK, the DLLs provided by simplusb are required to function
//
//********************************************************************
//********************************************************************

#ifndef __DIGITAL_SCAN_MODULE_H__
#define __DIGITAL_SCAN_MODULE_H__

#include <windows.h>

// Use static library
#define DSM_LIB_EXPORT

//********************************************************************
//	DIGITAL_SCAN_MODULE Definitions
//********************************************************************

//////////////////////////////////////////////////////////////////////
//	DLL Error Codes
//////////////////////////////////////////////////////////////////////
#define DSM_SUCCESS					0x0000
#define DSM_ERROR					0xFFFF
#define DSM_ARG_INVALID				0xFFFE
#define DSM_USB_INVALID				0xFFFD
#define DSM_FLASH_VERIFY_FAIL		0xFFFC
#define DSM_INCOMPATIBLE_FIRMWARE	0xFFFB
//--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
//	DLL Definitions
//////////////////////////////////////////////////////////////////////
#define DSM_FLASH_MAX_ADDR			0x3FFFFF // 32Mb = 4MB 
#define MAX_VECTOR_ADDRESS			0x7FFFFF //  4MB -> 8M vectors

#ifdef _MSC_VER
	/* on MS environments, the inline keyword is available in C++ only */
	#define inline __inline
	/* ssize_t is also not available (copy/paste from MinGW) */
	#ifndef _SSIZE_T_DEFINED
		#define _SSIZE_T_DEFINED
		#undef ssize_t
		#ifdef _WIN64
			typedef __int64 ssize_t;
		#else
			typedef int ssize_t;
		#endif /* _WIN64 */
	#endif /* _SSIZE_T_DEFINED */
#endif /* _MSC_VER */

/* stdint.h is also not usually available on MS */
#if defined(_MSC_VER) && (_MSC_VER < 1600) && (!defined(_STDINT)) && (!defined(_STDINT_H))
	typedef unsigned __int8   uint8_t;
	typedef unsigned __int16  uint16_t;
	typedef unsigned __int32  uint32_t;
#else
	#include <stdint.h> 
#endif

#ifdef DEPRECATED
//do nothing
#else
#ifdef _MSC_VER
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif	//ifdef _MSC_VER
#endif	//ifdef DEPRACATED

//--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
//	DLL Export Constants
//////////////////////////////////////////////////////////////////////

#if defined DSM_DLL_EXPORT
#define DSM_EXPORT __declspec(dllexport)
#else 
#if defined DSM_LIB_EXPORT
	#define DSM_EXPORT
#else
	#define DSM_EXPORT __declspec(dllimport)
#endif
#endif

//--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
//	Digital Scan Module type definitions and structures
//////////////////////////////////////////////////////////////////////
typedef enum
{
	NONE_CH	 = 0,
	DOUT1_CH = 1,
	DOUT2_CH = 1 << 1,
	DOUT3_CH = 1 << 2,
	DOUT4_CH = 1 << 3,
	ALL_CH	 = 0x0F
} DSM_channel_t;

#define DOUT_PULSE_CONTINUOUS 16 

typedef enum
{
	NONE_DRV_COMP	= 0,
	DRV_COMP_DATA	= 1,
	DRV_COMP_EN		= 1 << 1,
	DRV_COMP_ALL	= 0x03
} DSM_drv_comp_t;

typedef enum
{
	NONE_DAC	= 0,
	DAC_1		= 1,
	DAC_2		= 1 << 1,
	DAC_3		= 1 << 2,
	DAC_4		= 1 << 3,
	DAC_5		= 1 << 4,
	DAC_ALL		= 0x0F
} DSM_DAC_t;

typedef enum
{
	VOUT_A		= 0,
	VOUT_B		= 1,
	VOUT_C		= 2,
	VOUT_D		= 3,
	VOUT_ALL	= 4
} DSM_DAC_channel_t;

typedef enum
{
	RANGE_5V       = 0,
	RANGE_10V      = 1,
	RANGE_10V8     = 2,
	RANGE_PN_5V    = 3,
	RANGE_PN_10V   = 4,
	RANGE_PN_10V8  = 5
} DSM_DAC_range_t;

typedef struct
{
	float VOUTA_5V_gain;
	float VOUTA_5V_offset;
	float VOUTB_5V_gain;
	float VOUTB_5V_offset;
	float VOUTC_5V_gain;
	float VOUTC_5V_offset;
	float VOUTD_5V_gain;
	float VOUTD_5V_offset;

	float VOUTA_10V_gain;
	float VOUTA_10V_offset;
	float VOUTB_10V_gain;
	float VOUTB_10V_offset;
	float VOUTC_10V_gain;
	float VOUTC_10V_offset;
	float VOUTD_10V_gain;
	float VOUTD_10V_offset;

	float VOUTA_10V8_gain;
	float VOUTA_10V8_offset;
	float VOUTB_10V8_gain;
	float VOUTB_10V8_offset;
	float VOUTC_10V8_gain;
	float VOUTC_10V8_offset;
	float VOUTD_10V8_gain;
	float VOUTD_10V8_offset;

	float VOUTA_PN_5V_gain;
	float VOUTA_PN_5V_offset;
	float VOUTB_PN_5V_gain;
	float VOUTB_PN_5V_offset;
	float VOUTC_PN_5V_gain;
	float VOUTC_PN_5V_offset;
	float VOUTD_PN_5V_gain;
	float VOUTD_PN_5V_offset;

	float VOUTA_PN_10V_gain;
	float VOUTA_PN_10V_offset;
	float VOUTB_PN_10V_gain;
	float VOUTB_PN_10V_offset;
	float VOUTC_PN_10V_gain;
	float VOUTC_PN_10V_offset;
	float VOUTD_PN_10V_gain;
	float VOUTD_PN_10V_offset;

	float VOUTA_PN_10V8_gain;
	float VOUTA_PN_10V8_offset;
	float VOUTB_PN_10V8_gain;
	float VOUTB_PN_10V8_offset;
	float VOUTC_PN_10V8_gain;
	float VOUTC_PN_10V8_offset;
	float VOUTD_PN_10V8_gain;
	float VOUTD_PN_10V8_offset;

} DSM_DAC_CAL_RANGE_s; //48 members of 4 bytes each (192 bytes total)


/* DSM DAC Calibration Factors */
//	uses shared memory so that a = b = c in the following:
//	DSM_DAC_CAL_DATA_t data;
//	a = data.DAC_1.VOUTD_PN_10V8_gain;
//	b = data.DAC_array[0].DAC.VOUTD_PN_10V8_offset
//	c = data.DAC_array[0].DAC_range_array[47];
typedef struct
{
	union
	{
		struct 
		{
			DSM_DAC_CAL_RANGE_s DAC_1;
			DSM_DAC_CAL_RANGE_s DAC_2;
			DSM_DAC_CAL_RANGE_s DAC_3;
			DSM_DAC_CAL_RANGE_s DAC_4;
			DSM_DAC_CAL_RANGE_s DAC_5;
		};
		union
		{ 
			DSM_DAC_CAL_RANGE_s DAC; 
			float DAC_range_array[(sizeof(DSM_DAC_CAL_RANGE_s)/sizeof(((DSM_DAC_CAL_RANGE_s *)0)->VOUTA_5V_gain))];
		}DAC_array[5];
	};
} DSM_DAC_CAL_DATA_t; //240 members of 4 bytes each (960 bytes total)


/* DSM Delay Calibration factors*/
typedef struct
{
	float vectorClock_gain;
	float vectorClock_offset;
	unsigned int dout1_delay_offset; 
	unsigned int dout2_delay_offset;
	unsigned int dout3_delay_offset;
	unsigned int dout4_delay_offset;
	unsigned int latch_delay_offset;
} DSM_DLY_CAL_DATA_t;

#define DEFAULT_DSM_DAC_CAL_DATA \
	/* 5V	 */ 1,0,1,0,1,0,1,0,\
	/*10V	 */ 1,0,1,0,1,0,1,0,\
	/*10V8	 */ 1,0,1,0,1,0,1,0,\
	/*PN 5V	 */ 1,0,1,0,1,0,1,0,\
	/*PN10V	 */ 1,0,1,0,1,0,1,0,\
	/*PN10V8 */ 1,0,1,0,1,0,1,0

#define DEFAULT_DSM_CAL_DATA {{{\
	/* DSM DAC Cal Factors */\
	/* DAC_1 */	{DEFAULT_DSM_DAC_CAL_DATA},\
	/* DAC_2 */	{DEFAULT_DSM_DAC_CAL_DATA},\
	/* DAC_3 */	{DEFAULT_DSM_DAC_CAL_DATA},\
	/* DAC_4 */	{DEFAULT_DSM_DAC_CAL_DATA},\
	/* DAC_5 */	{DEFAULT_DSM_DAC_CAL_DATA}}}}


#define DEFAULT_DSM_DLY_CAL_DATA \
	/* vectorClock_gain		*/	1,\
	/* vectorClock_offset	*/	0,\
	/* dout1_delay_offset	*/	0,\
	/* dout2_delay_offset	*/	0,\
	/* dout3_delay_offset	*/	0,\
	/* dout4_delay_offset	*/	0,\
	/* latch_delay_offset	*/	0



//#define DEFAULT_DSM_CAL_DATA {{{\
//	/* DSM DAC Cal Factors */\
//	/* DAC_1 */	{DEFAULT_DSM_DAC_CAL_DATA},\
//	/* DAC_2 */	{DEFAULT_DSM_DAC_CAL_DATA},\
//	/* DAC_3 */	{DEFAULT_DSM_DAC_CAL_DATA},\
//	/* DAC_4 */	{DEFAULT_DSM_DAC_CAL_DATA},\
//	/* DAC_5 */	{DEFAULT_DSM_DAC_CAL_DATA}}},\
//	/* DSM Delay Cal Factors */\
//	DEFAULT_DSM_DLY_CAL_DATA}
//--------------------------------------------------------------------

//********************************************************************
//********************************************************************
//	External Functions
//********************************************************************
//********************************************************************
#ifdef __cplusplus	//if c++ make sure functions are exported undecorated in c formatting
	extern "C" {
#endif

//********************************************************************
//	Digital Scan Module Functions
//********************************************************************
//////////////////////////////////////////////////////////////////////
//	DSM_init
//
//	This function initialises the DIGITAL_SCAN_MODULE library, USB libraries and the DSM firmware
//
//	Notes
//		-	This function is required for communication to the connected DSM
//		-	This function only initialises the first connected DSM.
//			DIGITAL_SCAN_MODULE library does not support multiple DSMs.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		
//	Returns 0x00 on success / error code on fail.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_init(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_init(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_close
//
//	This function deinitialises the USB libraries and closes the connection to the DSM
//
//	Notes
//		-	This function should be called when communication with the DSM has ceased
//		-	This function should be called even if the attached DSM has been disconnected.
//			This leaves the USB Handles in a defined state
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	Returns 0x00 on success / error code on fail.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_close(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_close(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_version
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	Returns the version of this DIGITAL_SCAN_MODULE library
//////////////////////////////////////////////////////////////////////
DSM_EXPORT float __cdecl DSM_version(void);

DSM_EXPORT float __stdcall s_DSM_version(void);


//////////////////////////////////////////////////////////////////////
//	DSM_firmware
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	Returns the firmware version of attached Digital Scan Module
//	DSM_ERROR on error.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT float __cdecl DSM_firmware(int DSM_context);

DSM_EXPORT float __stdcall s_DSM_firmware(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_toggle_leds
//
//	Led1 & Led2 are toggled. 
//
//	Notes
//		- This function's purpose is to supply a visual cue to aid in debugging
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_toggle_leds(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_toggle_leds(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_write_I2C_buffer
//	Writes 0-250 bytes to the address & i2c_register specified. 
//
//	Notes
//		-	I2C voltage must be set for operation
//			Default is 0 volts.
//			call DSM_set_voltage_I2C()
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		address			-	the I2C address of the device that is to be communicated with. 
//							the write bit is applied at DSM firmware layer
//							auto 7-bit, 10-bit address detection.
//		i2c_register	-	the I2C register of the device that is to be communicated with.
//		num_write_bytes	-	this is the number of bytes of writeDataBuffer to be sent.
//							must not exceed the size of writeDataBuffer else undefined behaviour may occur.
//		writeDataBuffer	-	this is the pointer to the data to be sent; least significant byte first: |7-0|->|15-8|->...->|1999-1991|
//							a valid pointer is required else undefined behaviour may occur unless num_write_bytes equals 0x00.							
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_write_I2C_buffer(int DSM_context, 
											uint16_t address, 
											uint8_t num_write_bytes , uint8_t * writeDataBuffer );

DSM_EXPORT int __stdcall s_DSM_write_I2C_buffer(int DSM_context,
												uint16_t address,
												uint8_t num_write_bytes , uint8_t * writeDataBuffer );


//////////////////////////////////////////////////////////////////////
//	DSM_read_I2C_buffer
//
//	Reads 0-250 bytes from the address specified.
//
//	Notes
//		-	I2C voltage must be set for operation
//			Default is 0 volts.
//			call DSM_set_voltage_I2C()
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		address			-	the I2C address of the device that is to be communicated with. 
//							the read bit is applied at DSM firmware layer
//							auto 7-bit, 10-bit address detection.
//		num_read_bytes	-	this is the number of bytes to be read and stored in readDataBuffer.
//							must not exceed the size of readDataBuffer else undefined behaviour may occur.
//		readDataBuffer	-	this is the pointer for the data to be stored; least significant byte first: |7-0|->|15-8|->...->|1999-1991|
//							a valid pointer is required else undefined behaviour may occur unless num_read_bytes equals 0x00.
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_read_I2C_buffer(int DSM_context, 
										   uint16_t address,
										   uint8_t num_read_bytes , uint8_t * readDataBuffer );

DSM_EXPORT int __stdcall s_DSM_read_I2C_buffer(int DSM_context,
											   uint16_t address,
											   uint8_t num_read_bytes , uint8_t * readDataBuffer );


//////////////////////////////////////////////////////////////////////
//	DSM_set_I2C_clock_freq
//
//	Sets the clock frequency for I2C communications
//
//	Notes
//		-	Default I2C clock frequency is set at 50 kHz
//		-	Sending lots of data through the I2C at high frequency has bugs associated with it.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		freq_kHz		-	the frequency in kHz to be set on the I2C clock
//
//	returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_I2C_clock_freq(int DSM_context, 
											  uint16_t freq_kHz);

DSM_EXPORT int __stdcall s_DSM_set_I2C_clock_freq(int DSM_context,
												  uint16_t freq_kHz);


//////////////////////////////////////////////////////////////////////
//	DSM_set_I2C_timeout
//
//	Sets the timeout for I2C communications
//
//	Notes
//		-	Default I2C timeout is at least 35 milliseconds
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		timeout_ms		-	the minimum timeout in milliseconds for the I2C data communications
//
//	returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_I2C_timeout(int DSM_context,
										   uint16_t timeout_ms);

DSM_EXPORT int __stdcall s_DSM_set_I2C_timeout(int DSM_context,
											   uint16_t timeout_ms);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_I2C
//
//	Sets the voltage level for I2C communications
//
//	Notes
//		-	Default I2C voltage is set at 0 volts
//		-	I2C read & write will not work unless this function has been called
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		volts			-	the voltage in volts to be set for I2C clock & data.
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_I2C(int DSM_context, 
										   double volts);

DSM_EXPORT int __stdcall s_DSM_set_voltage_I2C(int DSM_context,
											   double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_range_I2C
//
//	Sets the voltage range level for I2C 
//
//	Notes
//		-	Default I2C range is set at RANGE_5V
//		-	sets the I2C voltage to 0V before changing range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		range			-	the range be set on the I2C DAC
//							Use DSM_DAC_range_t to select the different ranges
//
//	return DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_range_I2C(int DSM_context, 
										 DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_range_I2C(int DSM_context,
											 DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_I2C_SDA_Hold_Time
//
//	Sets the SDA hold time for I2C communications
//
//	Notes
//		-	The SDA hold time setting dictates the minimum hold time on SDA after the falling edge of SCL.
//		-	There are two SDA hold time settings, 0x00 and 0x01:
//			0x00 results in a minimum of 100 nanoseconds hold time
//			0x01 results in a minimum of 300 nanoseconds hold time
//			
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		hold_time		-	Selects the hold time for I2C communications to follow.
//							Valid only if 0x00 or 0x01. Other values may result in undesired behaviour
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_I2C_SDA_hold_time(int DSM_context, 
												 uint8_t hold_time);

DSM_EXPORT int __stdcall s_DSM_set_I2C_SDA_hold_time(int DSM_context,
													 uint8_t hold_time);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_ref
//
//	set the voltage reference for the input comparators.
//
//	Notes
//		-	Default voltage is set at 0 volts.
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the input comparator level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set for the input comparators.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_ref(int DSM_context, 
										   DSM_channel_t channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_voltage_ref(int DSM_context,
											   DSM_channel_t channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_ref_range
//
//	sets the voltage reference range for the input comparator(s)
//
//	Notes
//		-	Default range is RANGE_5V
//		-	Use the typedef DSM_channel_t to set the same range across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	Sets the specified channel(s) voltage to 0 volts
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level range is to be set
//							only the channel(s) selected will be modified
//		range			-	the range be set on the selected channel(s)
//							Use DSM_DAC_range_t to select the different ranges
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_ref_range(int DSM_context,
												 DSM_channel_t channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_voltage_ref_range(int DSM_context,
													 DSM_channel_t channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_ref_secondary
//
//	set the voltage reference for the secondary input comparators.
//
//	Notes
//		-	Default voltage is set at 0 volts.
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the input comparator level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set for the input comparators.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_ref_secondary(int DSM_context,
													 DSM_channel_t channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_voltage_ref_secondary(int DSM_context,
														 DSM_channel_t channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_ref_secondary_range
//
//	sets the voltage reference range for the secondary input comparator(s)
//
//	Notes
//		-	Default range is RANGE_5V
//		-	Use the typedef DSM_channel_t to set the same range across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	Sets the specified channel(s) voltage to 0 volts
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level range is to be set
//							only the channel(s) selected will be modified
//		range			-	the range be set on the selected channel(s)
//							Use DSM_DAC_range_t to select the different ranges
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_ref_secondary_range(int DSM_context,
														   DSM_channel_t channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_voltage_ref_secondary_range(int DSM_context,
															   DSM_channel_t channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_high_level
//
//	sets the output high level in volts for the selected channel(s)
//
//	Notes
//		-	Default voltage is set at 0 volts.
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	if the voltage is greater than the DAC Range can allow, the outputted voltage will be equal 
//			to the maximum allowable of the range
//		-	MUST be greater than or equal to the equivalent output low level
//			If DOUTx_CH high level < DOUTx_CH low level, DOUTx_CH low level will be set as per "volts" first ( DOES NOT CHECK RANGE )		
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output high level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set on the specified channel(s)
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_high_level(int DSM_context, 
										  DSM_channel_t channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_high_level(int DSM_context,
											  DSM_channel_t channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_high_level_range
//
//	sets the output high level range for the selected channel(s)
//
//	Notes
//		-	Default range is RANGE_5V
//		-	Use the typedef DSM_channel_t to set the same range across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	Sets the specified channel(s) voltage to 0 volts
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output high level range is to be set
//							only the channel(s) selected will be modified
//		range			-	the range be set on the selected channel(s)
//							Use DSM_DAC_range_t to select the different ranges
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_high_level_range(int DSM_context,
												DSM_channel_t channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_high_level_range(int DSM_context,
													DSM_channel_t channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_low_level
//
//	sets the output low level in volts for the specified channels
//
//	Notes
//		-	Default voltage is set at 0 volts.
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	if the voltage is greater than the DAC Range can allow, the outputted voltage will be equal 
//			to the maximum allowable of the range
//		-	MUST be less than or equal to the equivalent output high level
//			If DOUTx_CH low level > DOUTx_CH high level, DOUTx_CH high level will be set as per "volts" first ( DOES NOT CHECK RANGE )
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set on the specified channel(s)
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_low_level(int DSM_context, 
										 DSM_channel_t channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_low_level(int DSM_context,
											 DSM_channel_t channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_low_level_range
//
//	sets the output low level range for the selected channel(s)
//
//	Notes
//		-	Default range is RANGE_5V
//		-	Use the typedef DSM_channel_t to set the same range across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	Sets the specified channel(s) voltage to 0 volts
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level range is to be set
//							only the channel(s) selected will be modified
//		range			-	the range be set on the selected channel(s)
//							Use DSM_DAC_range_t to select the different ranges
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_low_level_range(int DSM_context,
											   DSM_channel_t channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_low_level_range(int DSM_context,
												   DSM_channel_t channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_drv_comp
//
//	sets the drive comparator volts
//
//	Notes
//		-	Default voltage is set at 0 volts.
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	if the voltage is greater than the DAC Range can allow, the outputted voltage will be equal 
//			to the maximum allowable of the range
//		-	the following is called as part of DSM_init():
//					DSM_set_drv_comp(DSM_context, DRV_COMP_ALL, 2.5);
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set on the specified channel(s)
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_drv_comp(int DSM_context,
										DSM_drv_comp_t channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_drv_comp(int DSM_context,
											DSM_drv_comp_t channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_drv_comp_range
//
//	sets the drive comparator range
//
//	Notes
//		-	Default range is set to RANGE_5V
//		-	Use the typedef DSM_channel_t to set the same voltage across multiple channels at once.
//			"Bitwise Or" the channel values together
//		-	if the voltage is greater than the DAC Range can allow, the outputted voltage will be equal 
//			to the maximum allowable of the range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel(s) for which the output low level is to be set
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set on the specified channel(s)
//
//	Returns DSM_SUCCESS on success
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_drv_comp_range(int DSM_context,
											  DSM_drv_comp_t channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_drv_comp_range(int DSM_context,
												  DSM_drv_comp_t channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_set_vector_clock_freq
//	
//	Sets the vector clock frequency for DSM_run_pattern
//
//	Notes
//		-	High speeds may require vector pattern and or signal delay adjustments.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		freq_kHz		-	the frequency in kHz to be set on the vector clock
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_vector_clock_freq(int DSM_context, 
												 uint16_t freq_kHz);

DSM_EXPORT int __stdcall s_DSM_set_vector_clock_freq(int DSM_context,
													 uint16_t freq_kHz);


//////////////////////////////////////////////////////////////////////
//	DSM_set_no_delay
//
//	Sets a delay of 0 seconds on each channel
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_no_delay(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_set_no_delay(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_set_delay
//
//	Sets the delay length for each channel in nanoseconds
//
//	Notes
//		-	Delays in the range of 0-510 nanoseconds are possible in 2 nanosecond steps.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		dout1_delay_ns	-	delay to set on the dout1 channel
//		dout2_delay_ns	-	delay to set on the dout2 channel
//		dout3_delay_ns	-	delay to set on the dout3 channel
//		dout4_delay_ns	-	delay to set on the dout4 channel
//		latch_delay_ns	-	delay to set on the latch. 
//							This is used to control when SCAN_ERROR is recorded.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_delay(int DSM_context,
									 uint16_t dout1_delay_ns, uint16_t dout2_delay_ns,
									 uint16_t dout3_delay_ns, uint16_t dout4_delay_ns,
									 uint16_t latch_delay_ns);

DSM_EXPORT int __stdcall s_DSM_set_delay(int DSM_context,
										 uint16_t dout1_delay_ns, uint16_t dout2_delay_ns,
										 uint16_t dout3_delay_ns, uint16_t dout4_delay_ns,
										 uint16_t latch_delay_ns);


//////////////////////////////////////////////////////////////////////
//	DSM_enable_outputs
//
//	This function is used to enable & disable the output channels
//
//	Notes
//		-	Use the typedef DSM_output_enable_t to set all channels.
//			"Bitwise Or" the channels values together to get the correct 
//		-	a "masked" version of this function is available: DSM_enable_outputs_masked
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel  -	"Bitwise Or" the channels to enable, otherwise they will be disabled
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_enable_outputs(int DSM_context, 
										  DSM_channel_t channel);

DSM_EXPORT int __stdcall s_DSM_enable_outputs(int DSM_context,
											  DSM_channel_t channel);

//////////////////////////////////////////////////////////////////////
//	DSM_enable_outputs_masked
//
//	This function is used to enable & disable the output channels
//
//	Notes
//		-	Use the typedef DSM_output_enable_t to set all channels.
//			"Bitwise Or" the channels values together to get the correct
//		-	a "non-masked" version of this function is available: DSM_enable_outputs
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	"Bitwise Or" the channels to enable
//		mask			- 	"Bitwise Or" the channels to be changed.
//							only those channel(s) selected will be modified
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_enable_outputs_masked(int DSM_context,
												 DSM_channel_t channel, DSM_channel_t mask);

DSM_EXPORT int __stdcall s_DSM_enable_outputs_masked(int DSM_context,
												   DSM_channel_t channel, DSM_channel_t mask);


//////////////////////////////////////////////////////////////////////
//	DSM_enable_open_drain
//
//	This function is used to enable & disable the open drain mode for each channel
//
//	Notes
//		-	This function does not enable the outputs.
//			Use in conjunction with DSM_enable_outputs
//		-	Use the typedef DSM_output_enable_t to set all channels.
//			"Bitwise Or" the channels values together to get the correct 
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel	-	The output channels to enable/disable.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_enable_open_drain(int DSM_context,
											 DSM_channel_t channel);

DSM_EXPORT int __stdcall s_DSM_enable_open_drain(int DSM_context,
												 DSM_channel_t channel);


//////////////////////////////////////////////////////////////////////
//	DSM_enable_loopback
//
//	This function is used to enable & disable the loopback function for each channel
//	This is part of the self-test functionality of the DSM
//
//	Notes
//		-	Use the typedef DSM_output_enable_t to set all channels.
//			"Bitwise Or" the channels values together to get the correct 
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel	-	The output channels to enable/disable.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_enable_loopback(int DSM_context,
										   DSM_channel_t channel);

DSM_EXPORT int __stdcall s_DSM_enable_loopback(int DSM_context,
											   DSM_channel_t channel);


//////////////////////////////////////////////////////////////////////
//	DSM_run_pattern
//	This function runs the vector pattern from flash of the attached Digital Scan Module
//
//	Notes 
//		-	The compare is performed by this function "live"
//		-	The vector patterns must have been committed to the flash for this function to work
//			Loading the cache with Data is not good enough.
//		-	The error address returned is relative to vectorAddrStart
//			i.e.	if vectorAddrStart ==  0 , and an error occured at vector 25 , the returned value will be 25.
//					if vectorAddrStart == 10 , and an error occured at vector 25 , the returned value will be 15.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	This is the first vector of the pattern to be run.
//							This vector must be even else undefined behaviour may occur. 
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > VECTOR_MAX_ADDR
//							An error is returned if vectorAddrEnd < vectorAddrStart
//
//	returns 0x00 on success, vectorAddrOffset, (vectorAddrError - vectorAddrStart) on fail.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT uint32_t __cdecl DSM_run_pattern(int DSM_context, 
											uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT uint32_t __stdcall s_DSM_run_pattern(int DSM_context,
												uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_get_error_address
//
//	This function returns the error address from the last DSM_run_pattern call.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	returns vectorErrorAddress on success ( 0x00 indicates previous DSM_run_pattern was successful )
//	returns ( 0xFFFFFFFF - ERROR CODE ) on fail.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT uint32_t __cdecl DSM_get_error_address(int DSM_context);

DSM_EXPORT uint32_t __stdcall s_DSM_get_error_address(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_set_file_column_order
//	This function is used to set the data channel positions for DSM_load_file
//
//	Notes 
//		-	The columns are taken to be 0 indexed. 
//			The leftmost character is considered column 0
//		-	Channels may share the same data column if required
//		-	If the vector file does not store data for a particular data channel set the 
//			data channel positon to be greater than the number of columns in the vector file
//
//	Argument description
//		DOut1_Pos		-	the position in the file where DOut1 data is stored
//							default is column 0.
//		DOut2_Pos		-	the position in the file where DOut2 data is stored
//							default is column 1.
//		DOut3_Pos		-	the position in the file where DOut3 data is stored
//							default is column 2.
//		DOut4_Pos		-	the position in the file where DOut4 data is stored
//							default is column 3.
//		DIn1_Pos		-	the position in the file where DIn1 data is stored
//							default is column 4.
//		DIn2_Pos		-	the position in the file where DIn2 data is stored
//							default is column 5.
//		DIn3_Pos		-	the position in the file where DIn3 data is stored
//							default is column 6.
//		DIn4_Pos		-	the position in the file where DIn4 data is stored
//							default is column 7.
//
//////////////////////////////////////////////////////////////////////
DSM_EXPORT void __cdecl DSM_set_file_column_position(uint8_t DOut1_Pos, uint8_t DOut2_Pos,
													 uint8_t DOut3_Pos, uint8_t DOut4_Pos,
													 uint8_t DIn1_Pos, uint8_t DIn2_Pos,
													 uint8_t DIn3_Pos, uint8_t DIn4_Pos);

DSM_EXPORT void __stdcall s_DSM_set_file_column_position(uint8_t DOut1_Pos, uint8_t DOut2_Pos,
														 uint8_t DOut3_Pos, uint8_t DOut4_Pos,
														 uint8_t DIn1_Pos, uint8_t DIn2_Pos,
														 uint8_t DIn3_Pos, uint8_t DIn4_Pos);


//////////////////////////////////////////////////////////////////////
//	DSM_load_file	
//	This function parses a vector file, contents are cached.
//
//	Notes 
//		-	This function loads a file into cache only. 
//			Call DSM_commit_flash after loading the vector cache
//		-	This functions loads each column into the cache as defined by DSM_set_file_column_order			
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		filename		-	the path to the vector file to be tested.
//							Ensure no escape characters are present by formating: DRIVE:\\PATH\\TO\\FILE
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vector_file_length + vectorAddrStart > MAX_VECTOR_ADDRESS
//
//	returns the last vector address on success, 0 on error.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT uint32_t __cdecl DSM_load_file(int DSM_context, 
										  const char* filename, uint32_t vectorAddrStart);

DSM_EXPORT uint32_t __stdcall s_DSM_load_file(int DSM_context,
											  const char* filename, uint32_t vectorAddrStart);


//////////////////////////////////////////////////////////////////////
//	DSM_load_array
//	This function parses a vector array, contents are cached.
//
//	Notes 
//		-	This function loads a vector array into cache only. 
//			Call DSM_commit_flash after loading the vector cache
//		-	This functions loads each column into the cache as defined by DSM_set_file_column_order
//		-	Uses ASCII codes.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorArray		-	A pointer to the vector array to be tested.
//							The pointer must be valid else undefined behaviour may occur
//		arrayLength		-	The size of vectorArray.
//							Must be smaller or equal to size of vectorArray else undefined behaviour may occur
//		vectorLength	-	The number of elements that make up a vector:
//							For example if 8, elements 0-7 will make up the first vector; taking element 0 to be the leftmost column
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vector_file_length + vectorAddrStart > MAX_VECTOR_ADDRESS
//
//	returns the last vector address on success, 0 on error.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT uint32_t __stdcall s_DSM_load_array(int DSM_context,
											   uint8_t* vectorArray, uint32_t arrayLength, uint32_t vectorLength, uint32_t vectorAddrStart);

DSM_EXPORT uint32_t __cdecl DSM_load_array(int DSM_context,
										   uint8_t* vectorArray, uint32_t arrayLength, uint32_t vectorLength, uint32_t vectorAddrStart);

//////////////////////////////////////////////////////////////////////
//	DSM_load_array_auto
//
//	Automatically generate random scan data for use with loopback self-test//
//
//	Notes 
//		-	This function loads a vector array into cache only. 
//			Call DSM_commit_flash after loading the vector cache
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorErrAddr	-	Address to inject error.
//		arrayLength		-	The size of vectorArray.
//							Must be smaller or equal to size of vectorArray else undefined behaviour may occur
//		vectorLength	-	The number of elements that make up a vector:
//							For example if 8, elements 0-7 will make up the first vector; taking element 0 to be the leftmost column
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vector_file_length + vectorAddrStart > MAX_VECTOR_ADDRESS
//
//	returns the last vector address on success, 0 on error.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT uint32_t __stdcall s_DSM_load_array_auto(int DSM_context,
											   uint32_t vectorErrAddr, uint32_t arrayLength, uint32_t vectorLength, uint32_t vectorAddrStart);

DSM_EXPORT uint32_t __cdecl DSM_load_array_auto(int DSM_context,
										   uint32_t vectorErrAddr, uint32_t arrayLength, uint32_t vectorLength, uint32_t vectorAddrStart);


//////////////////////////////////////////////////////////////////////
//	DSM_set_output
//
//	writes dataPattern to the output cache.
//
//	Notes 
//		-	dataPattern should be 4 bytes long: 
//			e.g. uint32_t dataPatternPoint or uint8_t dataPatternPoint[4]
//			byte 0 -> dout1
//			byte 1 -> dout2
//			byte 2 -> dout3
//			byte 3 -> dout4;
//		-	dataPattern should formatted: 
//			'1' = high, '0' = low, 'x' or 'X' = don't care
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddr		-	this is the vector address of the output cache to write to
//		dataPattern		-	this is a pointer to the data to write to the output cache
//							The pointer must be valid else undefined behaviour may occur							
//////////////////////////////////////////////////////////////////////
DSM_EXPORT void __cdecl DSM_set_output(int DSM_context, 
									   uint32_t vectorAddr, uint8_t * dataPattern);

DSM_EXPORT void __stdcall s_DSM_set_output(int DSM_context,
										   uint32_t vectorAddr, uint8_t * dataPattern);


//////////////////////////////////////////////////////////////////////
//	DSM_set_compare
//
//	writes compPattern to the output cache.
//	decodes compPattern to write to the mask cache.
//
//	Notes 
//		-	compPattern should be 4 bytes long: 
//			e.g. uint32_t dataPatternPoint or uint8_t dataPatternPoint[4]
//			byte 0 -> din1
//			byte 1 -> din2
//			byte 2 -> din3
//			byte 3 -> din4;
//		-	compPattern should formatted: 
//			'1' = high, '0' = low, 'x' or 'X' = don't care
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddr		-	this is the vector address of the compare/mask cache to write to
//		compPattern		-	this is a pointer to the data to write to the compare/mask cache
//							The pointer must be valid else undefined behaviour may occur							
//////////////////////////////////////////////////////////////////////
DSM_EXPORT void __cdecl DSM_set_compare(int DSM_context, 
										uint32_t vectorAddr, uint8_t * compPattern);

DSM_EXPORT void __stdcall s_DSM_set_compare(int DSM_context,
											uint32_t vectorAddr, uint8_t * compPattern);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_flash
//	
//	commits output/mask/compare vector caches into the attached Digital Scan Module's flash
//
//	Notes
//		- This function should only be used for debug
//		- Use DSM_commit_flash_CKSM() for production
//	
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrStart > vectorAddrEnd
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > MAX_VECTOR_ADDRESS
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_commit_flash(int DSM_context, 
										uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT int __stdcall s_DSM_commit_flash(int DSM_context,
											uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_flash_CKSM
//
//	commits output/mask/compare vector caches into the attached Digital Scan Module's flash
//
//	Notes
//		-	This function checks the existing contents of each flash sector and skips the write if the
//			contents already match the data to be written. Comparison is done via MD5 checksum.
//		-	After an erase and write the contents of each flash sector are verified using MD5 chekcsum.
//		-	Sector size is  8192 (0x2000) vectors. 
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrStart > vectorAddrEnd
//							Must be an integer multiple of 0x2000. e.g. 0x0000, 0x2000, 0x4000, ...
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > MAX_VECTOR_ADDRESS
//							Sector size is 0x2000. All of the sector containing vectorAddrEnd will be erased.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __stdcall s_DSM_commit_flash_CKSM(int DSM_context,
												 uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT int __cdecl DSM_commit_flash_CKSM(int DSM_context,
											 uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_output
//
//	commits output vector cache into the attached Digital Scan Modules flash
//	
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrStart > vectorAddrEnd
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > MAX_VECTOR_ADDRESS
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_commit_output(int DSM_context, 
										 uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT int __stdcall s_DSM_commit_output(int DSM_context,
											 uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_mask
//
//	commits mask vector cache into the attached Digital Scan Modules flash
//	
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrStart > vectorAddrEnd
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > MAX_VECTOR_ADDRESS
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_commit_mask(int DSM_context, 
									   uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT int __stdcall s_DSM_commit_mask(int DSM_context,
										   uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_compare
//
//	commits compare vector cache into the attached Digital Scan Modules flash
//	
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrStart > vectorAddrEnd
//		vectorAddrEnd	-	this is the vector address where the first line of filename will be stored.
//							An error is returned if vectorAddrEnd > MAX_VECTOR_ADDRESS
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_commit_compare(int DSM_context, 
										  uint32_t vectorAddrStart, uint32_t vectorAddrEnd);

DSM_EXPORT int __stdcall s_DSM_commit_compare(int DSM_context,
											  uint32_t vectorAddrStart, uint32_t vectorAddrEnd);


//////////////////////////////////////////////////////////////////////
//	DSM_flash_erase
//
//	TODO: REMOVE
//
//	completely erases the flash of the attached Digital Scan Module
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DEPRECATED(DSM_EXPORT int __cdecl DSM_flash_erase(int DSM_context));

DEPRECATED(DSM_EXPORT int __stdcall s_DSM_flash_erase(int DSM_context));


//////////////////////////////////////////////////////////////////////
//	DSM_flash_erase_sector
//
//	Completely erases the flash sector containing vectorAddrStart for the specified flash memory.
//
//	Notes
//		-	Low level function. Do not use.
//		-	This is called by DSM_commit_xxx functions as needed.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		
//	vectorAddrStart		-	start address of sector to erase
//	flashDev			-	Flash chip to erase. One of DSM_FLASH_DATA,DSM_FLASH_MASK or DSM_FLASH_COMPARE.
//
//	Returns DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_flash_erase_sector(int DSM_context, uint32_t vectorAddrStart, uint8_t flashDev);


//////////////////////////////////////////////////////////////////////
//	DSM_init_DAC
//
//	Puts the specified DAC(s) channel(s) into the Powered Up State
//
//	Notes
//		-	Resets the specified DAC(s) and channel(s) to default voltage
//		-	Resets the specified DAC(s) and channel(s) to default range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC				-	the DAC(s) to be powered up
//							only the DAC(s) selected will be modified
//		DAC_channel		-	the channel(s) to be powered up
//							only the channel(s) selected will be modified
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_init_DAC(int DSM_context,
									DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel);

DSM_EXPORT int __stdcall s_DSM_init_DAC(int DSM_context,
										DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel);


//////////////////////////////////////////////////////////////////////
//	DSM_close_DAC
//
//	Puts the specified DAC(s) channel(s) into the Powered Down State
//
//	Notes
//		- Resets the specified DAC(s) and channel(s) to default voltage
//		- Resets the specified DAC(s) and channel(s) to default range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC				-	the DAC(s) to be powered down
//							only the DAC(s) selected will be modified
//		DAC_channel		-	the channel(s) to be powered down
//							only the channel(s) selected will be modified
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_close_DAC(int DSM_context,
									 DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel);

DSM_EXPORT int __stdcall s_DSM_close_DAC(int DSM_context,
										 DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel);


//////////////////////////////////////////////////////////////////////
//	DSM_set_voltage_DAC
//
//	Sets the voltage level for each DAC channel
//
//	Notes
//		-	Use the typedef DSM_DAC_t to set the same level across multiple DACs at once.
//			"Bitwise Or" the DAC values together
//		-	DAC_channel cannot be "Bitwise Or'd" together
//			DAC_channel can only be as per DSM_DAC_channel_t
//		-	VOUTx1 must always be greater or equal to VOUTx2
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC				-	the DAC(s) to set the voltage on
//							only the DAC(s) selected will be modified
//		DAC_channel		-	the channel(s) to set the voltage on
//							only the channel(s) selected will be modified
//		volts			-	the voltage in volts to be set on the specified DAC_channel of the specified DAC(s)
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_voltage_DAC(int DSM_context,
										   DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel, double volts);

DSM_EXPORT int __stdcall s_DSM_set_voltage_DAC(int DSM_context,
											   DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel, double volts);


//////////////////////////////////////////////////////////////////////
//	DSM_set_range_DAC
//
//	Sets the range level for each DAC channel
//
//	Notes
//		-	Use the typedef DSM_DAC_t to set the same level across multiple DACs at once.
//			"Bitwise Or" the DAC values together
//		-	DAC_channel cannot be "Bitwise Or'd" together
//			DAC_channel can only be as per DSM_DAC_channel_t
//		-	Sets the specified DAC_channel voltage to 0 volts.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC				-	the DAC(s) to set the range on
//							only the DAC(s) selected will be modified
//		DAC_channel		-	the channel(s) to set the range on
//							only the channel(s) selected will be modified
//		range			-	the range to be set on the specified DAC_channel of the specified DAC(s)
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_set_range_DAC(int DSM_context,
										 DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel, DSM_DAC_range_t range);

DSM_EXPORT int __stdcall s_DSM_set_range_DAC(int DSM_context,
											 DSM_DAC_t DAC, DSM_DAC_channel_t DAC_channel, DSM_DAC_range_t range);


//////////////////////////////////////////////////////////////////////
//	DSM_write
//
//	Low level routine for sending commands to DSM.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DSM_command		-	see list of commands starting at line 55 of digital_can_module.c
//		writeData		-	pointer to DSM_BUF_SIZE (512) byte data array

DSM_EXPORT int __cdecl DSM_write(int DSM_context,
								 uint8_t DSM_command, uint8_t * writeData);

DSM_EXPORT int __stdcall s_DSM_write(int DSM_context,
									 uint8_t DSM_command, uint8_t * writeData);


//////////////////////////////////////////////////////////////////////
//	DSM_read
//
//	Low level routine for reading data from DSM.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DSM_command		-	see list of commands starting at line 55 of digital_can_module.c
//		readData		-	pointer to DSM_BUF_SIZE (512) byte data array

DSM_EXPORT int __cdecl DSM_read(int DSM_context,
								uint8_t DSM_command, uint8_t * readData);

DSM_EXPORT int __stdcall s_DSM_read(int DSM_context,
									uint8_t DSM_command, uint8_t * readData);


//////////////////////////////////////////////////////////////////////
//	DSM_write_read
//
//	Low level routine for reading/writing data from DSM.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DSM_command		-	see list of commands starting at line 55 of digital_can_module.c
//		writeData		-	pointer to DSM_BUF_SIZE (512) byte data array
//		readData		-	pointer to DSM_BUF_SIZE (512) byte data array


DSM_EXPORT int __cdecl DSM_write_read(int DSM_context,
									  uint8_t DSM_command, uint8_t * writeData, uint8_t * readData);

DSM_EXPORT int __stdcall s_DSM_write_read(int DSM_context,
										  uint8_t DSM_command, uint8_t * writeData, uint8_t * readData);


//////////////////////////////////////////////////////////////////////
//	DSM_set_cal_data
//
//	Low level routine for writing cal data to PIC RAM.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC_calData		-	Calibration data

DSM_EXPORT int __cdecl DSM_set_cal_data(int DSM_context,
										DSM_DAC_CAL_DATA_t* DAC_calData);

DSM_EXPORT int __stdcall s_DSM_set_cal_data(int DSM_context,
											DSM_DAC_CAL_DATA_t* DAC_calData);


//////////////////////////////////////////////////////////////////////
//	DSM_get_cal_data
//
//	Low level routine for reading cal data from PIC RAM.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		DAC_calData		-	Calibration data
DSM_EXPORT int __cdecl DSM_get_cal_data(int DSM_context,
										DSM_DAC_CAL_DATA_t* calData);

DSM_EXPORT int __stdcall s_DSM_get_cal_data(int DSM_context,
											DSM_DAC_CAL_DATA_t* calData);


//////////////////////////////////////////////////////////////////////
//	DSM_commit_cal_data
//
//	Low level routine for writing cal data from PIC RAM to PIC FLASH.
//
//	Notes
//		-	Low level function. Do not use.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
DSM_EXPORT int __cdecl DSM_commit_cal_data(int DSM_context);


DSM_EXPORT int __stdcall s_DSM_commit_cal_data(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_enable_DOut_pulse
//
//	Connect all the DOut pulse outputs to the delay lines. 
//
//	Notes
//		-	Ensures FLASH memory outputs are inactive.
//		-	running vector_patterns whilst DOut_pulse is enable may result in undefined behaviour
//		-	You will also need to use DSM_set_delay, DSM_set_high_level, DSM_set_low_level and DSM_enable_outputs to set up the outputs.
//		-	Use XXXX to set up pulse timing and triggering
//		- 	Use DSM_write_DOut_pulse to directly control the DC output states.
//		- 	Use DSM_MINNO_spi_byte to run SPI comms to MINNO Master.
//		-	Use DSM_SPI4_transaction to run SPI4 comms.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_enable_DOut_pulse(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_enable_DOut_pulse(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_disable_DOut_pulse
//
//	Disconnects all the DOut pulse outputs from the delay lines.
//
//	Notes
//		-	running vector patterns whilst DOut_pulse is enabled may result in undefined behaviour
//			disabling DOut_pulse ensures that the FLASH memory has control of delay line inputs
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////										  
DSM_EXPORT int __cdecl DSM_disable_DOut_pulse(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_disable_DOut_pulse(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_write_DOut_pulse
//
//  Set or Clear all digital outputs to DC value 
//
//	Notes
//		-	pulse output must be enabled with DSM_enable_DOut_pulse
//
//	Argument description
//		DSM_context		-	this is to support multisite
//		writePattern	-	OR of channels to set (others are cleared). e.g. DOUT1_CH || DOUT3_CH

DSM_EXPORT int __cdecl DSM_write_DOut_pulse(int DSM_context,
											DSM_channel_t writePattern);

DSM_EXPORT int __stdcall s_DSM_write_DOut_pulse(int DSM_context,
												DSM_channel_t writePattern);


//////////////////////////////////////////////////////////////////////
//	DSM_write_DOut_pulse_masked
//
//  Set or Clear selected digital outputs to DC value 
//
//	Notes
//		-	pulse output must be enabled with DSM_enable_DOut_pulse
//
//	Argument description
//		DSM_context		-	this is to support multisite
//		writePattern	-	OR of channels to set (others are cleared). e.g. DOUT1_CH || DOUT3_CH
//		writeMask		-	OR of channels to change. e.g. DOUT1_CH || DOUT3_CH || DOUT4_CH

DSM_EXPORT int __cdecl DSM_write_DOut_pulse_masked(int DSM_context,
												   DSM_channel_t writePattern, DSM_channel_t writeMask);

DSM_EXPORT int __stdcall s_DSM_write_DOut_pulse_masked(int DSM_context,
													   DSM_channel_t writePattern, DSM_channel_t writeMask);


//////////////////////////////////////////////////////////////////////
//	DSM_read_DIn_PIC
//
//  Read digital inputs 
//
//	Notes
//		-	pulse output must be enabled with DSM_enable_DOut_pulse
//		-	comparator inputs must be set-up with DSM_set_drv_comp and DSM_set_drv_comp_range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//		readPattern		-	input OR of channel read states e.g. DOUT1_CH || DOUT3_CH

DSM_EXPORT int __cdecl DSM_read_DIn_PIC(int DSM_context,
										uint8_t * readPattern);

DSM_EXPORT int __stdcall s_DSM_read_DIn_PIC(int DSM_context,
											uint8_t * readPattern);


//////////////////////////////////////////////////////////////////////
//	DSM_nvm_write
//
//	writes the non-volatile memory stored in the PIC
//
//	Notes
//		-	Do not use
//		-	PIC needs to be power cycled before a write can be read
//		-	currently address and size to write is defined in the firmware
//			the buffer must be at least size of ( DSM_BUF_SIZE - 4 )
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		writeBuffer		-	this is the pointer to the data to be written
//							a valid pointer is required else undefined behaviour may occur
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_nvm_write(int DSM_context,
									 uint8_t* writeBuffer);

DSM_EXPORT int __stdcall s_DSM_nvm_write(int DSM_context,
										 uint8_t* writeBuffer);


//////////////////////////////////////////////////////////////////////
//	DSM_nvm_read
//
//	reads the non-volatile memory stored in the PIC
//
//	Notes
//		-	Do not use
//		-	PIC needs to be power cycled before a write can be read
//		-	currently address and size to read is defined in the firmware
//			the buffer must be at least size of ( DSM_BUF_SIZE - 4 )
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		readBuffer		-	this is the pointer to the data to be received
//							a valid pointer is required else undefined behaviour may occur
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_nvm_read(int DSM_context,
									uint8_t* readBuffer);

DSM_EXPORT int __stdcall s_DSM_nvm_read(int DSM_context,
										uint8_t* readBuffer);


//////////////////////////////////////////////////////////////////////
//	DSM_nvm_erase
//
//	erases the non-volatile memory stored in the PIC
//
//	Notes
//		-	do not use
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_nvm_erase(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_nvm_erase(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_get_freq
//
//	Measures the frequency of a signal on the selected DIn channel
//
//	Notes
//		-	frequency can only be measured on the DIN channels
//		-	32 bit counter clocked at 10ns period
//		-	averaged over 4 cycles
//		-	comparator inputs must be set-up with DSM_set_drv_comp and DSM_set_drv_comp_range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	channel to be measured e.g. DOUT1_CH
//		freq_out		-	pointer to float frequency measurement
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_get_freq(int DSM_context,
									DSM_channel_t channel, float * freq_out);

DSM_EXPORT int __stdcall s_DSM_get_freq(int DSM_context,
										DSM_channel_t channel, float * freq_out);


//////////////////////////////////////////////////////////////////////
//	DSM_get_duty_cycle
//
//	Measures the duty cycle of a signal on the selected DIn channel
//
//	Notes
//		-	duty cycle can only be measured on the DIN channels
//		-	32 bit counter clocked at 10ns period
//		-	comparator inputs must be set-up with DSM_set_drv_comp and DSM_set_drv_comp_range
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		channel			-	the channel for which the frequency is to be measured from
//		duty_out		-	pointer to float duty cycle measurement
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_get_duty_cycle(int DSM_context,
										  DSM_channel_t channel, float * duty_out);

DSM_EXPORT int __stdcall s_DSM_get_duty_cycle(int DSM_context,
											  DSM_channel_t channel, float * duty_out);



//////////////////////////////////////////////////////////////////////
//	DSM_MINNO_spi_byte
//
//	send/receive SPI byte to MINNO devices only. 
//
//	Notes
//		-	this is a special product function because of the SPI implementation in MINNO
//			do not use this function.
//		-	this function can only send and receive 1 byte at a time
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		byte_slave_in	-	this is the pointer to the data to be sent
//							a valid pointer is required else undefined behaviour may occur							
//		byte_slave_out	-	this is the pointer to the data to be received
//							a valid pointer is required else undefined behaviour may occur
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_MINNO_spi_byte(int DSM_context,
										  uint8_t * byte_slave_in, uint8_t * byte_slave_out);

DSM_EXPORT int __stdcall s_DSM_MINNO_spi_byte(int DSM_context,
											  uint8_t * byte_slave_in, uint8_t * byte_slave_out);


//////////////////////////////////////////////////////////////////////
//	DSM_MINNO_spi_comms
//
//	send/receive SPI message to MINNO devices only. 
//
//	Notes
//		-	this is a special product function because of the SPI implementation in MINNO
//			do not use this function.
//		-	this function can send up to 255 bytes at a time
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		byte_slave_in	-	this is the pointer to the data to be sent
//							a valid pointer is required else undefined behaviour may occur							
//		byte_slave_out	-	this is the pointer to the data to be received
//							a valid pointer is required else undefined behaviour may occur
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_MINNO_spi_comms(int DSM_context,
										   uint8_t dataLength, uint8_t * byte_slave_in, uint8_t * byte_slave_out);

DSM_EXPORT int __stdcall s_DSM_MINNO_spi_comms(int DSM_context,
											   uint8_t dataLength, uint8_t * byte_slave_in, uint8_t * byte_slave_out);


//////////////////////////////////////////////////////////////////////
//	DSM_setup_pulse
//
//	Set-up triggered pulse outputs. Trigger on Din_x, output on Dout_x. 
//
//	Notes
//		-	All outputs share the same timer. When any input is triggered the timer is reset. 
//      -   output is low for delay time, high for on-time
//		-	timer values are multiplied by 10ns.
//		-	multiple outputs can be triggered from single input
//		-	multiple inputs can trigger single output
//		-	there is a minimum delay offset of xxus.
//		-	timer period is automatically set to max of (doutx_delay + doutx_on_time)
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		doutx_triggers	-	bitwise OR of trigger channels as DSM_channel_t
//							Default is single pulse per trigger. Add DOUT_PULSE_CONTINUOUS for continuous pulsing after single trigger.
//							if doutx_triggers = DOUT_PULSE_CONTINUOUS then no trigger is required.
//		doutx_delay		-	output starts low, goes high (delay * 10ns) after trigger.
//		doutx_on_time	-	output stays high for on_time.
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_setup_pulse(int DSM_context,
									   uint8_t dout1_triggers, uint16_t  dout1_delay, uint16_t  dout1_on_time,
									   uint8_t dout2_triggers, uint16_t  dout2_delay, uint16_t  dout2_on_time,
									   uint8_t dout3_triggers, uint16_t  dout3_delay, uint16_t  dout3_on_time,
									   uint8_t dout4_triggers, uint16_t  dout4_delay, uint16_t  dout4_on_time);

DSM_EXPORT int __stdcall s_DSM_setup_pulse(int DSM_context,
										   uint8_t dout1_triggers, uint16_t  dout1_delay, uint16_t  dout1_on_time,
										   uint8_t dout2_triggers, uint16_t  dout2_delay, uint16_t  dout2_on_time,
										   uint8_t dout3_triggers, uint16_t  dout3_delay, uint16_t  dout3_on_time,
										   uint8_t dout4_triggers, uint16_t  dout4_delay, uint16_t  dout4_on_time);


//////////////////////////////////////////////////////////////////////
//	DSM_disable_pulse
//
//	Disables the triggered pulse outputs.
//
//	Notes
//		-	Alternatively call DSM_setup_pulse with no triggers, for example:
//				DSM_setup_pulse(DSM_context, 0, 0, 0,
//											 0, 0, 0,
//											 0, 0, 0,
//											 0, 0, 0);
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_disable_pulse(int DSM_context);

DSM_EXPORT int __stdcall s_DSM_disable_pulse(int DSM_context);


//////////////////////////////////////////////////////////////////////
//	DSM_setup_SPI2
//
//	Set-up SPI2 serial interface. 
//
//	Notes
//		-	SPI2 can be accessed on CON3 (10-way IDC) of DSM.
//		-	Schematic is labelled assuming that DSM is SPI SLAVE with pin_swap = 0.
//		-	DSM firmware does not currently support SLAVE operation.
//		-	For SPI MASTER operation with the default pin configuration you need to swap MISO2/MOSI2 compared to schematic.
//		-	For SPI MASTER operation with the pin_swap set to 1, then only MOSI2 is supported. Schematic is correct.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		clock			-	SPI clock in Hz
//		master			-	1 = MASTER; 0 = SLAVE.
//		pin_swap		-	0 = CON3_pin4 -> SDI2, CON3_pin6 -> SDO2; 1 = CON3_pin4 -> SDO2, CON3_pin6 -> Not Used; 
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_setup_SPI2(int DSM_context,
									  uint32_t clock, uint8_t master, uint8_t pin_swap, uint8_t din_edge);

DSM_EXPORT int __stdcall s_DSM_setup_SPI2(int DSM_context,
										  uint32_t clock, uint8_t master, uint8_t pin_swap, uint8_t din_edge);


//////////////////////////////////////////////////////////////////////
//	DSM_comms_SPI2
//
//	send/receive SPI message over SPI2 serial interface. 
//
//	Notes
//		-	SPI2 can be accessed on CON3 (10-way IDC) of DSM.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		data_length		-	this is the number of bytes to be sent and received.
//							must not exceed the size of data_in or data_out else undefined behaviour may occur.
//		data_slave_in	-	this is the pointer to the data to be sent; least significant byte first: |7-0|->|15-8|->...->|1999-1991|
//							a valid pointer is required else undefined behaviour may occur
//		data_slave_out	-	this is the pointer to the data to be received; least significant byte first: |7-0|->|15-8|->...->|1999-1991|
//							a valid pointer is required else undefined behaviour may occur
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
DSM_EXPORT int __cdecl DSM_comms_SPI2(int DSM_context,
									  uint8_t data_length, uint8_t * data_slave_in, uint8_t * data_slave_out);

DSM_EXPORT int __stdcall s_DSM_comms_SPI2(int DSM_context,
										  uint8_t data_length, uint8_t * data_slave_in, uint8_t * data_slave_out);


//--------------------------------------------------------------------

DSM_EXPORT int DSM_self_test_pattern(int DSM_context);
DSM_EXPORT int DSM_freq_test(int DSM_context);
DSM_EXPORT int DSM_dout_test(int DSM_context);
DSM_EXPORT int DSM_duty_cycle_test(int DSM_context);
DSM_EXPORT int DSM_delay_sync(int DSM_context);
DSM_EXPORT int __cdecl DSM_LODRUN_pattern_array(int DSM_context,
												uint8_t* vectorArr, uint32_t vectorArrLen, uint32_t vectorAddrStart, uint32_t vectorErrAddr);
DSM_EXPORT int __cdecl DSM_LODRUN_pattern_auto(int DSM_context,
									  uint32_t vectorArrLen, uint32_t vectorAddrStart, uint32_t vectorErrAddr);
DSM_EXPORT int __cdecl DSM_calculate_cache_checksum(uint8_t* MD5_Result, uint32_t vectorAddrStart, uint32_t vectorAddrEnd, uint8_t flashDev);
DSM_EXPORT int __cdecl DSM_calculate_flash_checksum(int DSM_context, uint8_t* MD5_Result, uint32_t vectorAddrStart, uint32_t vectorAddrEnd, uint8_t flashDev);

//////////////////////////////////////////////////////////////////////
//	DSM_read_pattern
//
//	Read back one sector of pattern data from DSM flash.
//
//	Notes 
//		-	Do not use
//		-	The vector patterns must have been committed to the flash for this function to work
//			Loading the cache with Data is not good enough.
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		vectorAddrStart	-	This is the first vector of the pattern.
//							This vector must be even else undefined behaviour may occur. 
//		flashDev		-	Flash chip to erase. One of DSM_FLASH_DATA,DSM_FLASH_MASK or DSM_FLASH_COMPARE.
//		flashData		-	Incoming data destination - pointer to byte array
//	
//////////////////////////////////////////////////////////////////////
DSM_EXPORT int __cdecl DSM_read_pattern(int DSM_context, uint32_t vectorAddr, uint8_t flashDev, uint8_t* flashData);


//////////////////////////////////////////////////////////////////////
//	DSM_MINNO_ACK_pulse_IC_PWM_edge
//
//	Special function for MINNO test. Pulses out on ACK. IC on PWM measure number of pulses upto edge on PWM. 
//
//	Notes
//		-	
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//		period			-	ACK pulse period in us.						
//		timeout			-	timeout in ms.					
//		count_out	   -	pointer to float to receive pulse count out
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	

DSM_EXPORT int __cdecl DSM_MINNO_ACK_pulse_IC_PWM_edge(int DSM_context,
									int period, int timeout, float * count_out);

DSM_EXPORT int __stdcall s_DSM_MINNO_ACK_pulse_IC_PWM_edge(int DSM_context,
										int period, int timeout, float * count_out);

#ifdef __cplusplus	//if c++ make sure functions are exported undecorated in c formatting
	}
#endif

#endif //__DIGITAL_SCAN_MODULE_H__

//********************************************************************
//********************************************************************
//DIGITAL_SCAN_MODULE.lib example
//********************************************************************
//********************************************************************
/*


*/
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//	DSM_
//	Description
//
//	Notes
//		-
//
//	Argument description
//		DSM_context		-	this is to support multisite
//							not currently implemented
//
//	return DSM_SUCCESS on success.
//////////////////////////////////////////////////////////////////////	
