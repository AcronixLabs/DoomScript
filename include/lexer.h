#ifndef LEXER_H
#define LEXER_H

#include "doomcc.h"

typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,
    
    // Keywords - Module/Import
    TOKEN_MAP,
    TOKEN_IMPORT,
    TOKEN_FROM,
    TOKEN_EXPORT,
    
    // Keywords - Types
    TOKEN_SLAYER,
    TOKEN_IMP,
    TOKEN_CYBERDEMON,
    TOKEN_CACODEMON,
    TOKEN_ARCHVILE,
    TOKEN_HELLFIRE,
    TOKEN_BFG9000,
    TOKEN_SOULSPHERE,
    TOKEN_CHAINSAW,
    TOKEN_FIST,
    TOKEN_BRUISER,
    TOKEN_REVENANT,
    TOKEN_GIB,
    TOKEN_NONE,
    
    // Keywords - Declarations
    TOKEN_SPAWN,
    TOKEN_ARSENAL,
    TOKEN_LOADOUT,
    TOKEN_AVATAR,
    TOKEN_PLASMA,
    
    // Keywords - Control Flow
    TOKEN_FRAG,
    TOKEN_WAVE,
    TOKEN_PATROL,
    TOKEN_HUNT,
    TOKEN_BERSERK,
    TOKEN_RAGE,
    TOKEN_EJECT,
    TOKEN_RESPAWN,
    
    // Keywords - Scope/Access
    TOKEN_SECTOR,
    TOKEN_CHAMBER,
    TOKEN_HELL,
    TOKEN_PURGATORY,
    TOKEN_REDCARD,
    TOKEN_BLUECARD,
    TOKEN_YELLOWCARD,
    TOKEN_SKULLKEY,
    TOKEN_UAC, // standard library namespace
    
    // Literals
    TOKEN_INT_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_CHAR_LITERAL,
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Identifiers
    TOKEN_IDENTIFIER,
    
    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_POWER,
    
    TOKEN_EQ,
    TOKEN_NE,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LE,
    TOKEN_GE,
    
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    
    TOKEN_ASSIGN,
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,
    TOKEN_STAR_ASSIGN,
    TOKEN_SLASH_ASSIGN,
    TOKEN_PERCENT_ASSIGN,
    
    TOKEN_AMP,
    TOKEN_PIPE,
    TOKEN_CARET,
    TOKEN_LSHIFT,
    TOKEN_RSHIFT,
    TOKEN_TILDE,
    
    TOKEN_DOT,
    TOKEN_ARROW,
    
    // Punctuation
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_DOUBLE_COLON,
    TOKEN_ARROW_RETURN, // ->
    
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
    int line;
    int column;
    int length;
} Token;

typedef struct {
    const char *source;
    int start;
    int current;
    int line;
    int column;
} Lexer;

void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);
const char *token_type_to_string(TokenType type);

#endif
