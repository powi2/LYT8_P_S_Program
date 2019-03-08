////////#if defined(_MSC_VER) && (_MSC_VER < 1600) && (!defined(_STDINT)) && (!defined(_STDINT_H))
////////	typedef unsigned __int8   uint8_t;
////////	typedef unsigned __int16  uint16_t;
////////	typedef unsigned __int32  uint32_t;
////////#else
////////	#include <stdint.h> 
////////#endif
////////
////////#include "RelayController.h"
////////
////////class BinnoRelayController
////////{
////////	public:
////////		BinnoRelayController(int num_modules, int hz, int pinswap, int din_edge);
////////		~BinnoRelayController() {};
////////		uint8_t states[8];
////////			
////////		int open_relay(int rly);
////////		int close_relay(int rly);
////////		int open_all_relays();
////////
////////
////////		
////////	private:
////////		int init();
////////		//RelayController relays(0,0,0,0);
////////		
////////	
////////};