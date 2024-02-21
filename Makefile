CC=gcc
CFLAGS=-Wall -g

SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINNAME=elasticc
BIN=bin/$(BINNAME)

TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

LIBNAME=esclient.a
LIB=lib/$(LIBNAME)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c
	echo $@
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(TEST)/bin:
	mkdir $@


$(LIB): $(OBJS)
	ar rcs $@ $^

all: $(LIB)

test: $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -r $(BIN) $(OBJ)/*.o
	rm -r $(TEST)/bin/*
