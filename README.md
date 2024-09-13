# GEMM SIMD Benchmark

Benchmark for GEMM (General Matrix Multiplication) with AVX-512 SIMD acceleration.

## Build

- Build shared libraries

```
make lib
```

This build step compiles `libdgemm.so` in `lib/` directory, which contains two functions:

```c
// Double-precision general matrix multiplication
void dgemm(int m, int n, int k, double *A, double *B, double *C);
void dgemm_simd(int m, int n, int k, double *A, double *B, double *C);
```

`dgemm()` computes matrix multiplication of `A` (`m` x `k`) and `B` (`k` x `n`) into `C` (`m` x `n`).
`dgemm_simd()` is AVX-512 accelerated version of `dgemm()`.

## Test

```
make test
```

runs small matrix multiplication tests in `testcases/` directories.

This test only checks `dgemm()` implementation (not `dgemm_simd()`) implementation, because `dgemm_simd()` currently only support matrices with 64-byte alignment at the start of each row.

```
make validate
```

runs validation which checks the difference of `dgemm()` and `dgemm_simd()` are negligible (probably no difference).

This test runs `N` x `N` matrix multiplications for `N` = 8, 16, 32, ..., 1024 using both `dgemm()` and `dgemm_simd()` and checks difference between two results.

## Benchmark

```
make benchmark
```

runs benchmark for `dgemm()` and `dgemm_simd()` for square matrices with random double values `[0, 1)`.
