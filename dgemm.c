#include <math.h>
#include <assert.h>

// Double-precision general matrix multiplication
// C (m*n) = A(m*k) * B(k*n)
void dgemm(int m, int n, int k, double *A, double *B, double *C) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      C[n*i + j] = 0;
      for (int l = 0; l < k; l++) {
        C[n*i + j] += A[k*i + l] * B[n*l + j];
      }
    }
  }
}
