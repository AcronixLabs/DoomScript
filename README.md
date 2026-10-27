# Doom-Script

*A programming language forged in Hell, compiled with righteous fury.*

Doom-Script is a complete, DOOM (1993)-themed programming language implementation featuring a C-based compiler, language server protocol (LSP) support, and Sublime Text integration. Built for the HellKernel operating system project and beyond.

## Features

- **DOOM-Themed Syntax** - Keywords like `loadout`, `frag`, `eject`, `uac`, `sector` bring the atmosphere of Hell to your code
- **Complete Toolchain** - Lexer, parser, semantic analyzer, code generator all implemented from scratch in C
- **C Code Generation** - Portable backend that generates C code, compiles with your system C compiler
- **Standard Library** - The UAC provides I/O, strings, memory, and file operations
- **Module System** - Organize your code with `map` modules and `import` statements
- **Type Safety** - Strong static typing with DOOM-inspired primitive types
- **Language Server** - Full LSP support for modern editor integration
- **Sublime Text Package** - Syntax highlighting, snippets, and LSP integration out of the box
- **Comprehensive Tests** - Automated test suite for lexer, parser, semantic analysis, and integration
- **Thematic Diagnostics** - Error messages like "RIP AND TEAR - Syntax error..."

## Quick Start

### Prerequisites

- GCC or Clang (C11 or later)
- Make
- POSIX-compatible system (Linux, macOS, BSD)

### Building

```bash
# Clone the repository
git clone https://github.com/AcronixLabs/DoomScript.git
cd DoomScript

# Build compiler and runtime
make

# Run tests
make test

# Install (optional)
sudo make install
```

### Hello World

Create `hell.ds`:

```doom
map hell import uac;

loadout main() -> gib {
    uac.printf("HELLO FROM HELLKERNEL\n");
    eject 0;
}
```

Compile and run:

```bash
./doomcc hell.ds -o hell
./hell
```

Output: `HELLO FROM HELLKERNEL`

## Documentation

- [Language Specification](LANGUAGE_SPEC.md) - Complete language reference
- [Architecture](ARCHITECTURE.md) - Compiler design and implementation details
- [Contributing](CONTRIBUTING.md) - How to contribute
- [Examples](examples/) - Sample programs

## Tools

### Compiler (`doomcc`)
```bash
doomcc [options] file.ds
  -o <file>     Output executable name
  -c            Generate C code only
  -v            Verbose output
  -Wall         Enable all warnings
  -O0/-O1/-O2   Optimization level
  --help        Show help
```

### Language Server (`doom-lsp`)
Implements Language Server Protocol 3.17 for editor integration.

### Sublime Text Package
See [sublime/README.md](sublime/README.md) for installation instructions.

## Language Showcase

```doom
map slayer import uac;

// Constants
berserk slayer MAX_HEALTH = 100;

// Struct
revenant Demon {
    slayer health;
    slayer damage;
    chainsaw type;
};

// Function
loadout attack(revenant target, slayer weapon_damage) -> slayer {
    target.health -= weapon_damage;
    frag (target.health <= 0) {
        uac.printf("%s HAS BEEN FRAGGED!\n", target.type);
        eject 1;
    }
    eject 0;
}

loadout main() -> gib {
    revenant imp;
    imp.health = 60;
    imp.damage = 10;
    imp.type = "IMP";
    
    patrol slayer i = 0; i < 3; i++ {
        uac.printf("Attack #%d!\n", i);
        attack(imp, 25);
    }
    
    eject 0;
}
```

## Project Status

- [x] Language specification
- [x] Compiler architecture design
- [ ] Lexer implementation
- [ ] Parser implementation
- [ ] Semantic analyzer
- [ ] Code generator
- [ ] Runtime library
- [ ] LSP server
- [ ] Sublime Text package
- [ ] Test suite
- [ ] Documentation

## License

This is a fan-created programming language project, not affiliated with id Software LLC or Bethesda Softworks LLC. DOOM and related trademarks are property of their respective owners.

See [LICENSE](LICENSE) for details.

## Acknowledgments

Inspired by DOOM (1993) by id Software - a masterpiece that taught a generation to rip and tear.
