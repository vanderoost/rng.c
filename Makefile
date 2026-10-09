CFLAGS = -Wall -Wextra -O3
LDFLAGS =
LDLIBS = -lm

NAME = main
SRC = src
OBJ = obj
BIN = bin

GEN_SRCS = $(SRC)/rng/rng_zig_layers.c

EXE = $(BIN)/$(NAME)

BIN_SRCS = $(wildcard $(SRC)/*.c)
LIB_SRCS = $(wildcard $(SRC)/*/*.c) $(GEN_SRCS)
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

$(SRC)/rng/rng_zig_layers.c: $(BIN)/rng_zig_layers_gen
	$< > $@

$(BIN)/rng_zig_layers_gen: $(SRC)/rng_zig_layers_gen.c $(SRC)/rng/rng.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BIN)/%: $(OBJ)/%.o $(LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -MMD -o $@

clean:
	@rm -rf $(BIN) $(OBJ) *.ppm

clean-gen: clean
	@rm -f $(GEN_SRCS)

-include $(DEPS)

.PHONY: all run hot open benchmark clean
