CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I./include
LDFLAGS = 

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = tests

# Compiler sources
COMPILER_SRCS = $(SRC_DIR)/main.c \
                $(SRC_DIR)/lexer/lexer.c \
                $(SRC_DIR)/parser/parser.c \
                $(SRC_DIR)/ast/ast.c \
                $(SRC_DIR)/semantic/analyzer.c \
                $(SRC_DIR)/codegen/cgen.c

# Runtime sources
RUNTIME_SRCS = $(SRC_DIR)/runtime/runtime.c

# LSP sources
LSP_SRCS = $(SRC_DIR)/lsp/main.c \
          $(SRC_DIR)/lsp/server.c

COMPILER_OBJS = $(COMPILER_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
RUNTIME_OBJS = $(RUNTIME_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LSP_OBJS = $(LSP_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = doomcc
RUNTIME_LIB = libdoom.a
LSP_TARGET = doom-lsp

all: $(BUILD_DIR) $(TARGET) $(RUNTIME_LIB) $(LSP_TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/lexer $(BUILD_DIR)/parser $(BUILD_DIR)/ast $(BUILD_DIR)/semantic $(BUILD_DIR)/codegen $(BUILD_DIR)/runtime $(BUILD_DIR)/lsp

$(TARGET): $(COMPILER_OBJS)
	$(CC) $(COMPILER_OBJS) -o $(TARGET) $(LDFLAGS)

$(RUNTIME_LIB): $(RUNTIME_OBJS)
	ar rcs $(RUNTIME_LIB) $(RUNTIME_OBJS)

$(LSP_TARGET): $(LSP_OBJS) $(COMPILER_OBJS)
	$(CC) $(LSP_OBJS) $(COMPILER_OBJS) -o $(LSP_TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	@echo "RIP AND TEAR - Running tests..."
	@./tests/run_tests.sh

test-lexer:
	@echo "Testing lexer..."
	@cd tests/lexer && $(CC) -I../../include ../../src/lexer/lexer.c lexer_test.c -o lexer_test && ./lexer_test

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(RUNTIME_LIB) $(LSP_TARGET) *.o
	rm -rf tests/*/*_test tests/*/*.out

install: all
	install -m 755 $(TARGET) /usr/local/bin/
	install -m 644 $(RUNTIME_LIB) /usr/local/lib/
	install -m 755 $(LSP_TARGET) /usr/local/bin/

package: all
	@echo "Building Sublime Text package..."
	@cd sublime && ./build_package.sh

.PHONY: all test test-lexer clean install package
