CC=gcc
CFLAGS=-Wunused -Wall -g

SRC=src
SRCS=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/lib/%, $(TESTS))

LIBNAME=esclient.a
LIB=lib/$(LIBNAME)

all: setup $(BIN) $(LIB) 

setup: 
	mkdir -p obj
	mkdir -p lib

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/lib/%: $(TEST)/%.c
	echo $@
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(TEST)/lib:
	mkdir $@

$(LIB): $(OBJS)
	ar rcs $@ $^

test: $(TEST)/lib $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -r $(LIB) $(OBJ)/*.o
	rm -rf $(TEST)/lib
	rm -rf lib/ obj/

.PHONY: all test clean
