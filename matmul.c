// See LICENSE for license details.

#include "dataset.h"
#include "util.h"
#include <stddef.h>

void matmul(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[])
{
  size_t i, j, k;

  for (i = 0; i < lda; i++) {
    for (j = coreid; j < lda; j += ncores) {
      data_t sum = 0;
      for (k = 0; k < lda; k++)
        sum += A[j*lda + k] * B[k*lda + i];
      C[i + j*lda] = sum;
    }
  }
}

void matmul_opt(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[])
{
	size_t im, jm, km, i, j;
	data_t sum;

	for (im = 8*coreid; im < lda; im += 16) {
		for (jm = 0; jm < lda; jm += 8) {
			for (km = 0; km < lda; km += 8) {
				for (i = im; i < im + 8 && i < lda; i++) {
					for (j = jm; j < jm + 8 && j < lda; j++) {
						sum =	A[j*lda + km] * B[km*lda + i] +		A[j*lda + km+1] * B[(km+1)*lda + i];
						sum +=	A[j*lda + km+2] * B[(km+2)*lda + i] +	A[j*lda + km+3] * B[(km+3)*lda + i];
						sum +=	A[j*lda + km+4] * B[(km+4)*lda + i] +	A[j*lda + km+5] * B[(km+5)*lda + i];
						sum +=	A[j*lda + km+6] * B[(km+6)*lda + i] +	A[j*lda + km+7] * B[(km+7)*lda + i];
						C[i + j*lda] += sum;
					}
				}
			}
		}
	}
}

