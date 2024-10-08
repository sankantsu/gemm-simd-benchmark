CC=gcc
CFLAGS=-std=c11 -O2 -mavx512f

BIN_DIR=./bin/
LIB_DIR=./lib/
OUT_DIR=./out/

SOURCES=dgemm.c dgemm_simd.c
TEST_SOURCES=test.c
BENCH_SOURCES=bench.c
VALIDATE_SOURCES=validate.c
DGEMM_LIB=$(LIB_DIR)libdgemm.so
TEST_EXECUTABLE=$(BIN_DIR)test
BENCH_EXECUTABLE=$(BIN_DIR)bench
VALIDATE_EXECUTABLE=$(BIN_DIR)validate
SO_CFLAGS=-fPIC -rdynamic -shared

all: $(TEST_EXECUTABLE) lib

$(DGEMM_LIB): $(SOURCES)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) $(SO_CFLAGS) -o $@ $(SOURCES)

$(TEST_EXECUTABLE): $(TEST_SOURCES) $(DGEMM_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -o $@ $(TEST_SOURCES) -ldgemm -lm

$(BENCH_EXECUTABLE): $(BENCH_SOURCES) $(DGEMM_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -o $@ $(BENCH_SOURCES) -ldgemm

$(VALIDATE_EXECUTABLE): $(VALIDATE_SOURCES) $(DGEMM_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -o $@ $(VALIDATE_SOURCES) -ldgemm -lm

.PHONY: bench test clean

bench: $(BENCH_EXECUTABLE)
	@mkdir -p $(OUT_DIR)
	@LD_LIBRARY_PATH=$(LIB_DIR) $(BENCH_EXECUTABLE) >$(OUT_DIR)bench_out.csv

validate: $(VALIDATE_EXECUTABLE)
	@LD_LIBRARY_PATH=$(LIB_DIR) $(VALIDATE_EXECUTABLE)

test: $(TEST_EXECUTABLE)
	@sh test.sh

clean:
	rm -f $(DGEMM_LIB) $(TEST_EXECUTABLE) $(BENCH_EXECUTABLE)
