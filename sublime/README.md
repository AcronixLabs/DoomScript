# Doom-Script Sublime Text Package

## Installation

### Method 1: Manual Installation
1. Build the package: `./build_package.sh`
2. Copy `DoomScript.sublime-package` to your Sublime Text Installed Packages directory:
   - Linux: `~/.config/sublime-text/Installed Packages/`
   - macOS: `~/Library/Application Support/Sublime Text/Installed Packages/`
   - Windows: `%APPDATA%\Sublime Text\Installed Packages\`

### Method 2: Development Installation
1. Copy the `sublime/` directory contents to:
   - Linux: `~/.config/sublime-text/Packages/DoomScript/`

## Requirements

- Sublime Text 4
- LSP package installed via Package Control
- `doom-lsp` in your PATH (from Doom-Script compiler installation)

## Features

- Syntax highlighting for `.ds` files
- DOOM-themed color scheme friendly
- Comment toggling (`Ctrl+/` or `Cmd+/`)
- LSP integration for diagnostics, completions, go-to-definition
- Auto-indentation

## Troubleshooting

If LSP isn't working:
1. Ensure `doom-lsp` is installed and in PATH
2. Check LSP package is installed
3. Open LSP logs: `LSP: Toggle Log Panel`

## Rip and Tear!
