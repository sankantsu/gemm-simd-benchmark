#!/usr/bin/env python

import os
import pandas as pd
import matplotlib.pyplot as plt


def init():
    os.makedirs("./img", exist_ok=True)


def load_benchmark_result():
    df = pd.read_csv("./out/bench_out.csv")
    df = df.drop(df.index[df.iter < 5])
    df = df.groupby(by=["label", "n"]).sec.median().reset_index()
    df = df.pivot_table(index="n", columns="label", values="sec")
    return df


def plot(df):
    # linear scale
    df.plot(ylabel="sec", marker="x")
    plt.savefig("./img/benchmark_result_linear.png")

    # log scale
    df.plot(ylabel="sec", loglog=True, marker="x")
    plt.savefig("./img/benchmark_result_loglog.png")


def show_speedup(df):
    speedup = df.dgemm / df.dgemm_simd
    print("Speedup:")
    print(speedup)


def main():
    init()
    df = load_benchmark_result()
    plot(df)
    show_speedup(df)


if __name__ == "__main__":
    main()
