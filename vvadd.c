// See LICENSE for license details.

#include "stdlib.h"
#include "dataset.h"

//--------------------------------------------------------------------------
// vvadd function

void __attribute__((noinline)) vvadd(int coreid, int ncores, size_t n, const data_t* x, const data_t* y, data_t* z)
{
   size_t i;

   // interleave accesses
   for (i = coreid; i < n; i+=ncores)
   {
      z[i] = x[i] + y[i];
   }
}

void __attribute__((noinline)) vvadd_opt(int coreid, int ncores, size_t n, const data_t* x, const data_t* y, data_t* z)
{
	size_t i;

	/* Each core does 16 units of work at a time = 2 cache lines.
	 * This ensures no false sharing and also functions as loop unrolling. */
	for (i = 16*coreid; i < (n/32)*32; i += 32) {
		z[i] = x[i] + y[i];
		z[i+1] = x[i+1] + y[i+1];
		z[i+2] = x[i+2] + y[i+2];
		z[i+3] = x[i+3] + y[i+3];
		z[i+4] = x[i+4] + y[i+4];
		z[i+5] = x[i+5] + y[i+5];
		z[i+6] = x[i+6] + y[i+6];
		z[i+7] = x[i+7] + y[i+7];
		z[i+8] = x[i+8] + y[i+8];
		z[i+9] = x[i+9] + y[i+9];
		z[i+10] = x[i+10] + y[i+10];
		z[i+11] = x[i+11] + y[i+11];
		z[i+12] = x[i+12] + y[i+12];
		z[i+13] = x[i+13] + y[i+13];
		z[i+14] = x[i+14] + y[i+14];
		z[i+15] = x[i+15] + y[i+15];
	}

	/* Tail case */
	if (coreid == 0) {
		for (i = (n/32)*32; i < n; i++) {
			z[i] = x[i] + y[i];
		}
	}
}

