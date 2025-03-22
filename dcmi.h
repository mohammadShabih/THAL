#include "macros.h"
#include "dma.h"

struct dcmi {
	uint32_t cr, sr, ris, ier, mis, icr, escr, esur, cwstr, cwsiz, dr;
}

enum eSync_mode {
	EMBEDDED_SYNC, HARDWARE_SYNC
};

deinit()
