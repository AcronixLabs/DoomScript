# Contributing to Doom-Script

*"Rip and tear, until it is done."*

We welcome contributions to Doom-Script! This guide will help you get started.

## Getting Started

### Development Environment

1. Fork and clone the repository
2. Install dependencies: GCC/Clang, Make
3. Build the project: `make`
4. Run tests: `make test`

### Code Style

- **C Standard:** C11
- **Style:** K&R or similar, consistent indentation (4 spaces)
- **Comments:** Only when necessary - let the code speak
- **Warnings:** Compile with `-Wall -Wextra -Werror`
- **Naming:** snake_case for functions/variables, PascalCase for types
- **DOOM Theming:** Use appropriate terminology in errors/messages where it fits

### Project Structure Guidelines

- `include/` - Public headers only
- `src/` - Implementation files, organized by module
- `tests/` - Tests mirror source structure
- `examples/` - Working example programs
- Keep modules focused and loosely coupled

## Development Workflow

1. **Pick a task** - Check issues or implement from the checklist
2. **Write tests first** - TDD encouraged for compiler components
3. **Implement** - Follow existing patterns
4. **Test** - `make test` must pass
5. **Lint/Check** - Ensure clean compilation with warnings enabled
6. **Commit** - Clear, descriptive commit messages
7. **PR** - Submit pull request with description

## Adding Language Features

When adding a new language feature:

1. Update `LANGUAGE_SPEC.md` with syntax and semantics
2. Add token(s) to lexer if needed
3. Update grammar in parser
4. Add AST nodes if needed
5. Implement semantic analysis
6. Add code generation
7. Write tests (lexer, parser, semantic, integration)
8. Add example if appropriate

## Testing

```bash
# Run all tests
make test

# Run specific test suite
make test-lexer
make test-parser
make test-semantic
make test-integration
make test-lsp
```

Tests should be in `tests/` directory with clear naming.

## Bug Reports

When reporting bugs, include:
- Doom-Script version/commit
- Minimal reproducing example (`.ds` file)
- Expected behavior
- Actual behavior
- Compiler output/errors
- Platform (OS, compiler version)

## Feature Requests

Feature requests should align with Doom-Script's vision of a DOOM-themed general-purpose language. Explain the use case and how it fits the theme.

## Code of Conduct

- Be respectful and constructive
- Focus on technical merit
- Keep the DOOM spirit fun but professional
- Help others learn

## Questions?

Open an issue or discussion in the repository.

**Rip and tear!**
