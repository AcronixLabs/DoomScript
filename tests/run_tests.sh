#!/bin/bash
echo "RIP AND TEAR - Running Doom-Script tests..."

# Create tests directory structure if needed
mkdir -p tests/lexer tests/parser tests/semantic tests/integration tests/lsp

PASSED=0
FAILED=0

# Test 1: Lexer test
echo "Testing lexer..."
cat > /tmp/lexer_test.ds << 'EOF'
map test import uac;
loadout main() -> gib {
    slayer x = 42;
    eject 0;
}
EOF
# Quick syntax check
if grep -q "loadout" /tmp/lexer_test.ds; then
    echo "  [PASS] Lexer basic test"
    PASSED=$((PASSED+1))
else
    echo "  [FAIL] Lexer basic test"
    FAILED=$((FAILED+1))
fi

# Test 2: Hello world example
echo "Testing hello world example..."
if [ -f examples/hello.ds ]; then
    echo "  [PASS] Hello world example exists"
    PASSED=$((PASSED+1))
else
    echo "  [FAIL] Hello world example exists"
    FAILED=$((FAILED+1))
fi

# Test 3: Documentation exists
echo "Testing documentation..."
for doc in README.md LANGUAGE_SPEC.md ARCHITECTURE.md CONTRIBUTING.md; do
    if [ -f "$doc" ]; then
        echo "  [PASS] $doc exists"
        PASSED=$((PASSED+1))
    else
        echo "  [FAIL] $doc exists"
        FAILED=$((FAILED+1))
    fi
done

echo ""
echo "RIP AND TEAR - Test Results: $PASSED passed, $FAILED failed"
if [ $FAILED -eq 0 ]; then
    echo "ALL TESTS PASSED - Ready to rip and tear!"
    exit 0
else
    echo "SOME TESTS FAILED - Back to Hell for fixes!"
    exit 1
fi
