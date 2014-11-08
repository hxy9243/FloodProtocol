CC := gcc
SRC := src

CFLAGS := -c
LDFLAGS := -lpthread

BIN := query_flood
SRCS := *.cc
OBJ := *.o

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD)/%.o: %.c %.h
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm -rf $(OBJ) $(BIN)

