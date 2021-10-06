CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile
ifeq ($(OS), Windows_NT)
	MKDIR_P = mkdir
else
	MKDIR_P = mkdir -p
endif

all: directories bin/edit_distance_main bin/edit_distance_tests

tests: bin/edit_distance_tests
	bin/edit_distance_tests

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_distance_main: build/hash_utility.o build/edit_distance.o build/edit_distance_main.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_main build/edit_distance_main.o build/hash_utility.o build/edit_distance.o -lm

bin/edit_distance_tests: build/edit_distance_tests.o build/hash_utility.o build/edit_distance.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_tests build/edit_distance_tests.o build/hash_utility.o build/edit_distance.o build/unity.o -lm

clean:
	$(RM) build/*
	$(RM) bin/edit_distance_main
	$(RM) bin/edit_distance_tests

directories:
	${MKDIR_P} bin
	${MKDIR_P} build

run:
ifndef cor
	@echo "Missing file declaration (cor)"
else ifndef dic
	@echo "Missing file declaration (dic)"
else
	cd bin/;./edit_distance_main $(cor) $(dic)
endif