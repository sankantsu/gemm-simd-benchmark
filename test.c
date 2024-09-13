#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dgemm.h"

double* input_double_array(FILE* fp, int size) {
  double *res = (double *)malloc(size * sizeof(double));
  for (int i = 0; i < size; i++) {
    double x;
    int check = fscanf(fp, "%lf", &x);
    if (check != 1) {
      fprintf(stderr, "Invalid testcase input.");
      exit(1);
    }
    res[i] = x;
  }
  return res;
}

void input(FILE *fp, int *mp, int *np, int *kp, double **A, double **B, double **C) {
  int m, n, k;
  int check = fscanf(fp, "%d %d %d", &m, &n, &k);
  if (check != 3) {
    fprintf(stderr, "Invalid testcase input.");
    exit(1);
  }
  *mp = m;
  *np = n;
  *kp = k;
  *A = input_double_array(fp, m * k);
  *B = input_double_array(fp, k * n);
  *C = input_double_array(fp, m * n);
}

int check_result(int size, double *m, double *expect, double eps) {
  int ok = 1;
  for (int i = 0; i < size; i++) {
    if (fabs(m[i] - expect[i]) > eps) {
      ok = 0;
      break;
    }
  }
  return ok;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <testcase>\n", argv[0]);
    exit(1);
  }

  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  int m, n, k;
  double *A, *B, *C, *expect;
  input(fp, &m, &n, &k, &A, &B, &expect);
  
  C = (double *)malloc(m * n * sizeof(double));
  dgemm(m, n, k, A, B, C);

  double eps = 1e-6;
  assert(check_result(m*n, C, expect, eps));

  free(A);
  free(B);
  free(C);
  free(expect);
}
