CFLAGS = -Wall -Wextra -O3
LDFLAGS =
LDLIBS = -lm

NAME = main
SRC = src
OBJ = obj
BIN = bin

EXE = $(BIN)/$(NAME)

BIN_SRCS = $(wildcard $(SRC)/*.c)
LIB_SRCS = $(wildcard $(SRC)/*/*.c)
ALL_SRCS = $(BIN_SRCS) $(LIB_SRCS)

LIB_OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(LIB_SRCS))
BINS = $(patsubst $(SRC)/%.c,$(BIN)/%,$(BIN_SRCS))
DEPS = $(patsubst $(SRC)/%.c,$(OBJ)/%.d,$(ALL_SRCS))

all: $(BINS)

run: $(EXE)
	@$(EXE)

hot:
	@find $(SRC) -type f | entr -c make run

image.ppm: $(BIN)/rng_image
	@time $<

open: image.ppm
	@open $<

benchmark: $(BIN)/benchmark
	@$<

$(BIN)/%: $(OBJ)/%.o $(LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -MMD -o $@

clean:
	@rm -rf $(BIN) $(OBJ)

-include $(DEPS)

.PHONY: all run hot clean
