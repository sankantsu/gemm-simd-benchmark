#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dgemm.h"

typedef void (*mm) (int, int, int, double*, double*, double*);

double random_double() {
  return (double)rand() / RAND_MAX;
}

void init_random(int size, double *data) {
  for (int i = 0; i < size; i++) {
    data[i] = random_double();
  }
}

double run(int n, mm f) {
  double *A = (double *)aligned_alloc(64, n * n * sizeof(double));
  double *B = (double *)aligned_alloc(64, n * n * sizeof(double));
  double *C = (double *)aligned_alloc(64, n * n * sizeof(double));

  init_random(n * n, A);
  init_random(n * n, B);

  clock_t start = clock();
  f(n, n, n, A, B, C);
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

  free(A);
  free(B);
  free(C);

  return elapsed;
}

void print_header() {
  printf("label,n,iter,sec\n");
}

void benchmark(char *label, mm f) {
  int n_min = 8;
  int n_max = 1024;
  for (int n = n_min; n <= n_max; n <<= 1) {
    fprintf(stderr, "Running %s for size %d ...\n", label, n);
    int n_iter = 20;
    for (int i = 0; i < n_iter; i++) {
      double elapsed = run(n, f);
      printf("%s,%d,%d,%.9f\n", label, n, i, elapsed);
    }
  }
}

int main() {
  setbuf(stdout, NULL);  // disable buffer for printf

  print_header();
  benchmark("dgemm", dgemm);
  benchmark("dgemm_simd", dgemm_simd);
}
