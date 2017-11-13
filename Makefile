SOURCES := $(wildcard src/*)
TARGET := ./bin/gauss_jordan
SOURCES_SEQ := $(wildcard src_seq/*)
TARGET_SEQ := ./bin/gauss_jordan_seq


# Default value
NP ?= 4

.PHONY: all
all: bin/ output/ $(TARGET) ;

.PHONY: all_seq
all_seq: bin/ output/ $(TARGET_SEQ) ;

%/:
	mkdir -p $@

bin/%: $(SOURCES)
	mpicc -fopenmp -I src/ -Wall -o $@ $^

bin/%: $(SOURCES_SEQ)
	gcc -I src_seq/ -Wall -o $@ $^

.PHONY: clean
clean:
	rm -rf bin/*

.PHONY: run
run: all
	mpirun -np $(NP) $(TARGET)

.PHONY: run_seq
run_seq: all_seq
	$(TARGET)

