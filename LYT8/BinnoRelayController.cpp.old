////////
////////
////////
////////
#include "asl.h"
////////
////////
////////#pragma warning (disable : 4244)
////////#pragma warning (disable : 4305)
////////
////////#include "BinnoRelayController.h"
//////////#include "RelayController.h"
//////////#include "digital_scan_module.h"
////////#include <map>
////////
////////
////////enum RelayNames
////////{
////////	K1 = 0,  //
////////	K2, 
////////	K3,
////////	K4,
////////	K5,
////////	K6,
////////	K7,
////////	K8,      // 
////////	K9,		 // 
////////	K10,
////////	K11,
////////	K12,
////////	K13,
////////	K14,
////////	K15,
////////	K16,	// 
////////};
////////
////////using namespace std;
////////
////////map<int, pair<int,int> > control_map;
////////RelayController relays(0,0,0,0);
////////
////////int BinnoRelayController::init() {
////////	// Bank 1
////////	control_map[K1]  = pair<int,int>(1 ,1);//
////////	control_map[K2]  = pair<int,int>(1 ,2);
////////	control_map[K3]  = pair<int,int>(1 ,3);
////////	control_map[K4]  = pair<int,int>(1 ,4);
////////	control_map[K5]  = pair<int,int>(1 ,5);
////////	control_map[K6]  = pair<int,int>(1 ,6);
////////	control_map[K7]  = pair<int,int>(1 ,7);
////////	control_map[K8]  = pair<int,int>(1 ,8);
////////	// Bank 2
////////	control_map[K9]  = pair<int,int>(2 ,1);
////////	control_map[K10] = pair<int,int>(2 ,2);
////////	control_map[K11] = pair<int,int>(2 ,3);
////////	control_map[K12] = pair<int,int>(2 ,4);
////////	control_map[K13] = pair<int,int>(2 ,5);
////////	control_map[K14] = pair<int,int>(2 ,6);
////////	control_map[K15] = pair<int,int>(2 ,7);
////////	control_map[K16] = pair<int,int>(2 ,8);//*/
////////
////////	return 0;
////////
////////}
////////
////////
////////BinnoRelayController::BinnoRelayController(int num_modules, int hz, int pinswap, int din_edge) {
////////	relays = RelayController(num_modules, hz, pinswap, din_edge);
////////	relays.track_relay_states(states);
////////	BinnoRelayController::init(); // Causing linker failure
////////	//BinnoRelayController::close_relay(10);// Causing linker failure
////////}
////////
////////
////////
////////int BinnoRelayController::open_relay(int rly) {
////////	return relays.open_relay(control_map[rly].first, control_map[rly].second);
////////}
////////
////////int BinnoRelayController::close_relay(int rly)  {
////////	return relays.close_relay(control_map[rly].first, control_map[rly].second);
////////}
////////
////////int BinnoRelayController::open_all_relays() {
////////	return relays.open_all_relays();
////////}