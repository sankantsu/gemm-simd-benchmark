// Double-precision general matrix multiplication
// C (m*n) = A(m*k) * B(k*n)
void dgemm(int m, int n, int k, double *A, double *B, double *C);
void dgemm_simd(int m, int n, int k, double *A, double *B, double *C);
