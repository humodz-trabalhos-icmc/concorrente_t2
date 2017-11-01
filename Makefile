SOURCES := $(wildcard src/*)
TARGET := ./bin/t2

.PHONY: all
all: bin/ $(TARGET) ;

%/:
	mkdir -p $@

bin/%: $(SOURCES)
	mpicc -I src/ -Wall -o $@ $^


.PHONY: clean
clean:
	rm -rf bin/*

.PHONY: run
run:
	mpirun -np $(NP) $(TARGET)
