#include "dma.h";
 
struct dma_stream {
	uint32_t cr, num_data, per_addr, mem_0, mem_1, fifo_cntrl;
}

struct dma {
	uint32_t lisr, hisr, lifcr, hifcr;
	struct dma_stream stream0, stream1, stream2, stream3, stream4, stream5, stream6, stream7; 
};



void dma_init(struct *dma, ) {}

deinit()
