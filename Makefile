CC=gcc
CFLAGS=-Wall -g

SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(OBJ)/main.o $(OBJ)/esclient.o
BINNAME=elasticc
BIN=bin/$(BINNAME)

TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTBIN=$(patsubst $(TEST)/%.c, $(TEST)/bin%, $(TESTS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(TEST)/bin:
	mkdir $@

clean:
	rm -r $(BIN) $(OBJ)/*.o
