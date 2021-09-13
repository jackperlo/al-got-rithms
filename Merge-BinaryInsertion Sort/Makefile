CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile
ifeq ($(OS),Windows_NT)
	MKDIR_P = mkdir
else
	MKDIR_P = mkdir -p
endif

all: directories bin/merge_binary_insertion_sort_main bin/merge_binary_insertion_sort_tests

tests: bin/merge_binary_insertion_sort_tests
	bin/merge_binary_insertion_sort_tests

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/merge_binary_insertion_sort_main: build/merge_binary_insertion_sort.o build/merge_binary_insertion_sort_main.o $(COMMON_DEPS)
	$(CC) -o bin/merge_binary_insertion_sort_main build/merge_binary_insertion_sort_main.o build/merge_binary_insertion_sort.o

bin/merge_binary_insertion_sort_tests: build/merge_binary_insertion_sort_tests.o build/merge_binary_insertion_sort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/merge_binary_insertion_sort_tests build/merge_binary_insertion_sort_tests.o build/merge_binary_insertion_sort.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/merge_binary_insertion_sort_main
	$(RM) bin/merge_binary_insertion_sort_tests

directories:
	${MKDIR_P} bin
	${MKDIR_P} build

run:
ifndef src 
	@echo "Non hai definito src_file"
else ifndef reverse
	@echo "Non hai definito reverse"
else
	cd bin/;merge_binary_insertion_sort_main $(src) $(reverse)
endif
