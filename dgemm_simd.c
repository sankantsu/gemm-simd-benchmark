#include <math.h>
#include <assert.h>
#include <immintrin.h>

// Double-precision general matrix multiplication
// C (m*n) = A(m*k) * B(k*n)
void dgemm_simd(int m, int n, int k, double *A, double *B, double *C) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j += 8) {
      __m512d c0 = _mm512_load_pd(C + n*i + j);
      for (int l = 0; l < k; l++) {
        __m512d bv = _mm512_load_pd(B + n*l + j);
        __m512d aa = _mm512_broadcastsd_pd(_mm_load_sd(A + k*i + l));
        c0 = _mm512_fmadd_pd(aa, bv, c0);
      }
      _mm512_store_pd(C + n*i + j, c0);
    }
  }
}
