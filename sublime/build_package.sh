#!/bin/bash
echo "RIP AND TEAR - Building Doom-Script Sublime Text Package..."

PACKAGE_NAME="DoomScript.sublime-package"
cd "$(dirname "$0")"

# Create package
zip -r "$PACKAGE_NAME" \
    DoomScript.sublime-syntax \
    DoomScript.sublime-settings \
    LSP.sublime-settings \
    Comments.tmPreferences \
    Snippets/ \
    README.md 2>/dev/null

echo "Package created: $PACKAGE_NAME"
echo "Install by copying to Sublime Text Packages directory"
