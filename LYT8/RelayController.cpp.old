//
//   RelayController.cpp
//
//



#include "asl.h"

////#pragma warning (disable : 4244)
////#pragma warning (disable : 4305)
////
////#include "RelayController.h"
////#include "digital_scan_module.h"
////
////
////#include <windows.h>

////int version;
////int firmware;
////
////int drivers;
////
////uint8_t SPI_out[8];
////uint8_t SPI_in[8];
////
////uint8_t* tracker = NULL;
////
////
////RelayController::RelayController(int num_modules, int hz, int pinswap, int din_edge) {
////	drivers = num_modules;
////	
////	version = DSM_version(); 
////	firmware = DSM_firmware(0); 
////	
////	DSM_setup_SPI2(0,
////					hz, //clk rate in hz
////					1, //must be in master mode
////					pinswap, //
////					din_edge); //Data clk'd in on rising/falling edge of clk
////}
////
////
////
////// Relay status will be automatically updated.
////void RelayController::track_relay_states(uint8_t* states) {
////	tracker = states;
////}
////
////// Relay status will be written into "states" when function is called.
////void RelayController::get_relay_states(uint8_t* states) {
////	for(int i = 0; i < drivers; i++) {
////		states[i] = SPI_out[i];
////	}
////}
////
////
////// Writes to DSM SPI2
////// Returns 0 on success.
////int RelayController::write_spi() {
////	if(tracker != NULL) 
////	{
////		for(int i = 0; i < drivers; i++) {
////			tracker[i] = SPI_out[i];
////		}
////	};
////	return DSM_comms_SPI2(0, drivers, SPI_out, SPI_in);
////}
////
////int RelayController::close_relay(int drv, int bit) {
////	//Change specfied bit to 1.
////	SPI_out[drv - 1] = SPI_out[drv - 1] | 1 << bit;
////	return write_spi();
////}
////
////int RelayController::open_relay(int drv, int bit) {
////	//Change specfied bit to 0.
////	SPI_out[drv - 1] = SPI_out[drv - 1] & ~(1 << bit);
////	return write_spi();
////}
////
////int RelayController::open_all_relays() {
////	for(int i = 0; i < drivers; i++) {
////		SPI_out[i] = 0;
////	}
////	return write_spi();
////}

