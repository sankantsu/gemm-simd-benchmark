#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "dgemm.h"

double random_double() {
  return (double)rand() / RAND_MAX;
}

void init_random(int size, double *data) {
  for (int i = 0; i < size; i++) {
    data[i] = random_double();
  }
}

double max_diff(int m, int n, int k, double *A, double *B) {
  double *C1 = (double *)aligned_alloc(64, m*n*sizeof(double));
  double *C2 = (double *)aligned_alloc(64, m*n*sizeof(double));
  dgemm(m, n, k, A, B, C1);
  dgemm_simd(m, n, k, A, B, C2);
  double diff = 0;
  for (int i = 0; i < m*n; i++) {
    diff = fmax(diff, fabs(C1[i] - C2[i]));
  }
  free(C1);
  free(C2);
  return diff;
}

void validate(int m, int n, int k) {
  double *A = (double *)aligned_alloc(64, m*k*sizeof(double));
  double *B = (double *)aligned_alloc(64, k*n*sizeof(double));
  init_random(m*k, A);
  init_random(k*n, B);
  double diff = max_diff(m, n, k, A, B);
  printf("(m = %d, n = %d, k = %d) max diff: %.10f\n", m, n, k, diff);
  free(A);
  free(B);
}

int main() {
  srand(time(NULL));
  for (int n = 8; n <= 1024; n <<= 1) {
    validate(n, n, n);
  }
}
