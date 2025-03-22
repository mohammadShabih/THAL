#include "dcmi.h"

dcmi_init(struct dcmi *dcmi, int sync_mode) {
	// set  8 bits, continous mode, embedded sync
	if (sync_mode == EMBEDDED_SYNC) {
		
		dcmi->cr |= 0x00000030;
	} else if (sync_mode == HARDWARE_SYNC) {
		// i need to check pixel clock polarity --- it should be the same
		// I need to check the vertical syn and horiziatonal sync polarity
		// on the both ov7670 and my dcmi interface. 
		dcmi->cr |= 0x00000020;
	}
	
	
	// dcmi enable
	dcmi->cr |= BIT(14);
	// capture enable, setting this to will stop camera
	dcmi->cr |= BIT(0);
}
