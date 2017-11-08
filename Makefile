SOURCES := $(wildcard src/*)
TARGET := ./bin/t2

# Default value
NP ?= 4

.PHONY: all
all: bin/ output/ $(TARGET) ;

%/:
	mkdir -p $@

bin/%: $(SOURCES)
	mpicc -fopenmp -I src/ -Wall -o $@ $^


.PHONY: clean
clean:
	rm -rf bin/*

.PHONY: run
run: all
	mpirun -np $(NP) $(TARGET)
