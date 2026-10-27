#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

void lexer_init(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->start = 0;
    lexer->current = 0;
    lexer->line = 1;
    lexer->column = 1;
}

static bool is_at_end(Lexer *lexer) {
    return lexer->source[lexer->current] == '\0';
}

static char advance(Lexer *lexer) {
    char c = lexer->source[lexer->current++];
    if (c == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    return c;
}

static char peek(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->source[lexer->current];
}

static char peek_next(Lexer *lexer) {
    if (lexer->current + 1 >= (int)strlen(lexer->source)) return '\0';
    return lexer->source[lexer->current + 1];
}

static void skip_whitespace(Lexer *lexer) {
    while (true) {
        char c = peek(lexer);
        if (c == ' ' || c == '\r' || c == '\t') {
            advance(lexer);
        } else if (c == '\n') {
            advance(lexer);
        } else if (c == '/' && peek_next(lexer) == '/') {
            // Single line comment
            while (peek(lexer) != '\n' && !is_at_end(lexer)) {
                advance(lexer);
            }
        } else if (c == '/' && peek_next(lexer) == '*') {
            // Multi-line comment
            advance(lexer); // /
            advance(lexer); // *
            while (!(peek(lexer) == '*' && peek_next(lexer) == '/') && !is_at_end(lexer)) {
                advance(lexer);
            }
            if (!is_at_end(lexer)) {
                advance(lexer); // *
                advance(lexer); // /
            }
        } else {
            break;
        }
    }
}

static Token make_token(Lexer *lexer, TokenType type) {
    Token token;
    token.type = type;
    int length = lexer->current - lexer->start;
    if (length >= MAX_TOKEN_LENGTH) length = MAX_TOKEN_LENGTH - 1;
    memcpy(token.lexeme, lexer->source + lexer->start, length);
    token.lexeme[length] = '\0';
    token.line = lexer->line;
    // Column is approximate
    token.column = lexer->column - length;
    token.length = length;
    return token;
}

static Token error_token(Lexer *lexer, const char *message) {
    Token token;
    token.type = TOKEN_ERROR;
    strncpy(token.lexeme, message, MAX_TOKEN_LENGTH - 1);
    token.lexeme[MAX_TOKEN_LENGTH - 1] = '\0';
    token.line = lexer->line;
    token.column = lexer->column;
    token.length = (int)strlen(message);
    return token;
}

static TokenType check_keyword(Lexer *lexer, int start, int length, const char *rest, TokenType type) {
    if (lexer->current - lexer->start == start + length &&
        memcmp(lexer->source + lexer->start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type(Lexer *lexer) {
    int len = lexer->current - lexer->start;
    // Check keywords
    if (len == 3) {
        if (memcmp(lexer->source + lexer->start, "imp", 3) == 0) return TOKEN_IMP;
        if (memcmp(lexer->source + lexer->start, "map", 3) == 0) return TOKEN_MAP;
        if (memcmp(lexer->source + lexer->start, "gib", 3) == 0) return TOKEN_GIB;
    }
    if (len == 4) {
        if (memcmp(lexer->source + lexer->start, "frag", 4) == 0) return TOKEN_FRAG;
        if (memcmp(lexer->source + lexer->start, "fist", 4) == 0) return TOKEN_FIST;
        if (memcmp(lexer->source + lexer->start, "true", 4) == 0) return TOKEN_TRUE;
        if (memcmp(lexer->source + lexer->start, "wave", 4) == 0) return TOKEN_WAVE;
        if (memcmp(lexer->source + lexer->start, "hell", 4) == 0) return TOKEN_HELL;
        if (memcmp(lexer->source + lexer->start, "none", 4) == 0) return TOKEN_NONE;
        if (memcmp(lexer->source + lexer->start, "from", 4) == 0) return TOKEN_FROM;
        if (memcmp(lexer->source + lexer->start, "hunt", 4) == 0) return TOKEN_HUNT;
        if (memcmp(lexer->source + lexer->start, "rage", 4) == 0) return TOKEN_RAGE;
    }
    if (len == 5) {
        if (memcmp(lexer->source + lexer->start, "eject", 5) == 0) return TOKEN_EJECT;
        if (memcmp(lexer->source + lexer->start, "spawn", 5) == 0) return TOKEN_SPAWN;
        if (memcmp(lexer->source + lexer->start, "false", 5) == 0) return TOKEN_FALSE;
        if (memcmp(lexer->source + lexer->start, "plasma", 6) == 0) return TOKEN_PLASMA; // will fix below
    }
    if (len == 6) {
        if (memcmp(lexer->source + lexer->start, "import", 6) == 0) return TOKEN_IMPORT;
        if (memcmp(lexer->source + lexer->start, "export", 6) == 0) return TOKEN_EXPORT;
        if (memcmp(lexer->source + lexer->start, "slayer", 6) == 0) return TOKEN_SLAYER;
        if (memcmp(lexer->source + lexer->start, "avatar", 6) == 0) return TOKEN_AVATAR;
        if (memcmp(lexer->source + lexer->start, "chamber", 7) == 0) return TOKEN_CHAMBER;
        if (memcmp(lexer->source + lexer->start, "sector", 6) == 0) return TOKEN_SECTOR;
        if (memcmp(lexer->source + lexer->start, "patrol", 6) == 0) return TOKEN_PATROL;
        if (memcmp(lexer->source + lexer->start, "plasma", 6) == 0) return TOKEN_PLASMA;
    }
    if (len == 7) {
        if (memcmp(lexer->source + lexer->start, "arsenal", 7) == 0) return TOKEN_ARSENAL;
        if (memcmp(lexer->source + lexer->start, "berserk", 7) == 0) return TOKEN_BERSERK;
        if (memcmp(lexer->source + lexer->start, "bruiser", 7) == 0) return TOKEN_BRUISER;
        if (memcmp(lexer->source + lexer->start, "loadout", 7) == 0) return TOKEN_LOADOUT;
        if (memcmp(lexer->source + lexer->start, "redcard", 7) == 0) return TOKEN_REDCARD;
        if (memcmp(lexer->source + lexer->start, "respawn", 7) == 0) return TOKEN_RESPAWN;
        if (memcmp(lexer->source + lexer->start, "bfg9000", 7) == 0) return TOKEN_BFG9000;
        if (memcmp(lexer->source + lexer->start, "skullkey", 8) == 0) return TOKEN_SKULLKEY;
    }
    if (len == 8) {
        if (memcmp(lexer->source + lexer->start, "chainsaw", 8) == 0) return TOKEN_CHAINSAW;
        if (memcmp(lexer->source + lexer->start, "bluecard", 8) == 0) return TOKEN_BLUECARD;
        if (memcmp(lexer->source + lexer->start, "hellfire", 8) == 0) return TOKEN_HELLFIRE;
        if (memcmp(lexer->source + lexer->start, "revenant", 8) == 0) return TOKEN_REVENANT;
        if (memcmp(lexer->source + lexer->start, "skullkey", 8) == 0) return TOKEN_SKULLKEY;
        if (memcmp(lexer->source + lexer->start, "archvile", 8) == 0) return TOKEN_ARCHVILE;
    }
    if (len == 9) {
        if (memcmp(lexer->source + lexer->start, "purgatory", 9) == 0) return TOKEN_PURGATORY;
    }
    if (len == 10) {
        if (memcmp(lexer->source + lexer->start, "cacodemon", 10) == 0) return TOKEN_CACODEMON;
        if (memcmp(lexer->source + lexer->start, "cyberdemon", 11) == 0) return TOKEN_CYBERDEMON;
        if (memcmp(lexer->source + lexer->start, "soulsphere", 10) == 0) return TOKEN_SOULSPHERE;
        if (memcmp(lexer->source + lexer->start, "yellowcard", 10) == 0) return TOKEN_YELLOWCARD;
    }
    if (len == 11) {
        if (memcmp(lexer->source + lexer->start, "cyberdemon", 11) == 0) return TOKEN_CYBERDEMON;
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier(Lexer *lexer) {
    while (isalnum(peek(lexer)) || peek(lexer) == '_') {
        advance(lexer);
    }
    return make_token(lexer, identifier_type(lexer));
}

static Token number(Lexer *lexer) {
    while (isdigit(peek(lexer))) {
        advance(lexer);
    }
    
    if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
        advance(lexer); // consume .
        while (isdigit(peek(lexer))) {
            advance(lexer);
        }
        return make_token(lexer, TOKEN_FLOAT_LITERAL);
    }
    
    return make_token(lexer, TOKEN_INT_LITERAL);
}

static Token string(Lexer *lexer) {
    advance(lexer); // consume opening "
    while (peek(lexer) != '"' && !is_at_end(lexer)) {
        if (peek(lexer) == '\n') {
            return error_token(lexer, "Unterminated string");
        }
        if (peek(lexer) == '\\') {
            advance(lexer);
            if (!is_at_end(lexer)) advance(lexer);
        } else {
            advance(lexer);
        }
    }
    if (is_at_end(lexer)) {
        return error_token(lexer, "Unterminated string");
    }
    advance(lexer); // consume closing "
    return make_token(lexer, TOKEN_STRING_LITERAL);
}

static Token character(Lexer *lexer) {
    advance(lexer); // consume opening '
    if (peek(lexer) == '\\') {
        advance(lexer);
        if (!is_at_end(lexer)) advance(lexer);
    } else if (!is_at_end(lexer)) {
        advance(lexer);
    }
    if (peek(lexer) != '\'') {
        return error_token(lexer, "Unterminated character");
    }
    advance(lexer); // consume closing '
    return make_token(lexer, TOKEN_CHAR_LITERAL);
}

Token lexer_next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    
    lexer->start = lexer->current;
    
    if (is_at_end(lexer)) {
        return make_token(lexer, TOKEN_EOF);
    }
    
    char c = advance(lexer);
    
    if (isalpha(c) || c == '_') return identifier(lexer);
    if (isdigit(c)) return number(lexer);
    
    switch (c) {
        case '"': return string(lexer);
        case '\'': return character(lexer);
        case '(': return make_token(lexer, TOKEN_LPAREN);
        case ')': return make_token(lexer, TOKEN_RPAREN);
        case '{': return make_token(lexer, TOKEN_LBRACE);
        case '}': return make_token(lexer, TOKEN_RBRACE);
        case '[': return make_token(lexer, TOKEN_LBRACKET);
        case ']': return make_token(lexer, TOKEN_RBRACKET);
        case ',': return make_token(lexer, TOKEN_COMMA);
        case ';': return make_token(lexer, TOKEN_SEMICOLON);
        case ':': 
            if (peek(lexer) == ':') { advance(lexer); return make_token(lexer, TOKEN_DOUBLE_COLON); }
            return make_token(lexer, TOKEN_COLON);
        case '.': return make_token(lexer, TOKEN_DOT);
        case '~': return make_token(lexer, TOKEN_TILDE);
        
        case '+': 
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_PLUS_ASSIGN); }
            return make_token(lexer, TOKEN_PLUS);
        case '-':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_MINUS_ASSIGN); }
            if (peek(lexer) == '>') { advance(lexer); return make_token(lexer, TOKEN_ARROW_RETURN); }
            return make_token(lexer, TOKEN_MINUS);
        case '*':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_STAR_ASSIGN); }
            if (peek(lexer) == '*') { advance(lexer); return make_token(lexer, TOKEN_POWER); }
            return make_token(lexer, TOKEN_STAR);
        case '/':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_SLASH_ASSIGN); }
            return make_token(lexer, TOKEN_SLASH);
        case '%':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_PERCENT_ASSIGN); }
            return make_token(lexer, TOKEN_PERCENT);
        
        case '=':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_EQ); }
            return make_token(lexer, TOKEN_ASSIGN);
        case '!':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_NE); }
            return make_token(lexer, TOKEN_NOT);
        case '<':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_LE); }
            if (peek(lexer) == '<') { advance(lexer); return make_token(lexer, TOKEN_LSHIFT); }
            return make_token(lexer, TOKEN_LT);
        case '>':
            if (peek(lexer) == '=') { advance(lexer); return make_token(lexer, TOKEN_GE); }
            if (peek(lexer) == '>') { advance(lexer); return make_token(lexer, TOKEN_RSHIFT); }
            return make_token(lexer, TOKEN_GT);
        case '&':
            if (peek(lexer) == '&') { advance(lexer); return make_token(lexer, TOKEN_AND); }
            return make_token(lexer, TOKEN_AMP);
        case '|':
            if (peek(lexer) == '|') { advance(lexer); return make_token(lexer, TOKEN_OR); }
            return make_token(lexer, TOKEN_PIPE);
        case '^': return make_token(lexer, TOKEN_CARET);
    }
    
    return error_token(lexer, "Unexpected character");
}

const char *token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_MAP: return "MAP";
        case TOKEN_IMPORT: return "IMPORT";
        case TOKEN_LOADOUT: return "LOADOUT";
        case TOKEN_FRAG: return "FRAG";
        case TOKEN_EJECT: return "EJECT";
        case TOKEN_SLAYER: return "SLAYER";
        case TOKEN_SOULSPHERE: return "SOULSPHERE";
        case TOKEN_CHAINSAW: return "CHAINSAW";
        case TOKEN_GIB: return "GIB";
        case TOKEN_UAC: return "UAC"; // We'll add
        default: return "UNKNOWN";
    }
}
