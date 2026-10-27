# Doom-Script Compiler Architecture

## 1. Overview

Doom-Script is implemented as a multi-pass compiler written in C, generating C code as its backend. This design prioritizes portability, debuggability, and seamless integration with HellKernel and the C ecosystem.

## 2. Compilation Pipeline

```
Source (.ds) → Lexer → Parser → AST → Semantic Analysis → Code Generator → C Code → gcc/cc → Executable
```

### Stage Details

| Stage | Component | Purpose |
|-------|-----------|---------|
| 1. Source Loading | `src/loader.c` | Read `.ds` files, handle includes/imports |
| 2. Lexical Analysis | `src/lexer/lexer.c` | Tokenize source into tokens with location info |
| 3. Parsing | `src/parser/parser.c` | Build Abstract Syntax Tree from tokens |
| 4. Semantic Analysis | `src/semantic/analyzer.c` | Name resolution, type checking, scope validation |
| 5. Code Generation | `src/codegen/cgen.c` | Generate equivalent C code |
| 6. Compilation/Linking | Driver/`doomcc` | Invoke C compiler, link runtime |

## 3. Backend Selection Rationale

**Chosen Backend: C Code Generation**

| Backend | Pros | Cons | Decision |
|---------|------|------|----------|
| **C Codegen** | Portable, debuggable, easy to integrate with OS/kernel, no extra deps, familiar toolchain | Slightly less control, generated code verbose | ✓ **Selected** |
| **LLVM** | Powerful optimizations, native code, great tooling | Heavy dependency, complex API, harder to debug, overkill | Rejected |
| **Custom VM/Bytecode** | Full control, custom optimizations, educational | Must implement VM, GC, no native perf, more code to maintain | Rejected for v1.0 |

C codegen strikes the best balance for HellKernel integration and maintainability.

## 4. Directory Structure

```
DoomOS/
├── include/           # Public headers
│   ├── doomcc.h      # Main compiler API
│   ├── lexer.h       # Lexer definitions
│   ├── parser.h      # Parser definitions
│   ├── ast.h         # AST node definitions
│   ├── semantic.h    # Semantic analyzer
│   ├── codegen.h     # Code generator
│   └── runtime.h     # Runtime interface
├── src/              # Implementation
│   ├── main.c        # Compiler driver (doomcc)
│   ├── lexer/        # Tokenizer
│   ├── parser/       # Parser & grammar
│   ├── ast/          # AST construction/printing
│   ├── semantic/     # Name resolution & type checking
│   ├── codegen/      # C code generation
│   └── runtime/      # Runtime library (libdoom.a)
├── tests/            # Test suite
├── examples/         # Example .ds programs
├── server/           # LSP server implementation
├── sublime/          # Sublime Text package
├── docs/             # Additional documentation
└── build/            # Build artifacts
```

## 5. Core Data Structures

### Token
```c
typedef struct {
    TokenType type;
    char *lexeme;
    int line;
    int column;
    int length;
} Token;
```

### AST Nodes
Hierarchical structure with node types: Program, FunctionDecl, VarDecl, IfStmt, WhileStmt, etc.

### Symbol Table
Multi-scope symbol table tracking variables, functions, types, and modules.

### Type System
Type representation with primitives, arrays, structs, pointers, and user-defined types.

## 6. Language Server Architecture

The LSP server (`doom-lsp`) shares components with the compiler:
- Uses same lexer and parser for accuracy
- Uses same semantic analyzer for diagnostics
- Implements LSP protocol over stdin/stdout
- Supports: diagnostics, completion, hover, goto-definition, references, symbols, signature-help

## 7. Sublime Text Integration

Package structure:
```
DoomScript.sublime-package/
├── DoomScript.sublime-syntax
├── DoomScript.sublime-settings
├── Comments.tmPreferences
├── Indentation Rules.tmPreferences
├── Symbol List.tmPreferences
├── Default.sublime-keymap (optional)
├── LSP.sublime-settings
├── Snippets/
└── README.md
```

## 8. Build System

Uses Make for portability:
- `make` - Build compiler and runtime
- `make test` - Run test suite
- `make install` - Install to system
- `make package` - Build Sublime package
- `make clean` - Clean artifacts

## 9. Error Handling Strategy

All compiler errors include:
- File name
- Line and column numbers
- Thematic DOOM message
- Source line excerpt with caret indicator
- Helpful suggestions when possible

## 10. Memory Management

- Compiler uses manual memory management (malloc/free) with clear ownership
- Runtime uses standard C malloc/free
- No garbage collector in v1.0 for simplicity
- Future versions may add GC

## 11. Testing Strategy

- Unit tests for lexer, parser, semantic analyzer
- Integration tests compile and run full programs
- LSP protocol tests
- Regression test suite
- All tests must pass for acceptance
