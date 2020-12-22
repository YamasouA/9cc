#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

//
// tokenize.c
//

typedef enum {
  TK_IDENT, // Indentifiers(変数名)
  TK_PUNCT, // punctuators
  TK_KEYWORD, // keyword(while, return, intなど)
  TK_NUM,   // Numeric literals
  TK_EOF,   // End-of-file markers
} TokenKind;

// Token type
typedef struct Token Token;
struct Token {
  TokenKind kind; // Token kind
  Token *next;    // Next token
  int val;        // If kind is TK_NUM, its value
  char *loc;      // Token location
  int len;        // Token length
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
void error_tok(Token *tok, char *fmt, ...);
bool equal(Token *tok, char *op);
Token *skip(Token *tok, char *op);
Token *tokenize(char *input);

//
// parse.c
//

typedef struct Obj Obj;
struct Obj {
  Obj *next;
  char *name; // Variable name
  int offset; // offset from RBP
};

// Function
typedef struct Function Function;
struct Function {
  Node *body;
  Obj *locals;
  int stack_size;
};

// AST node
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NEG, // unary -
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_ASSIGN, // =
  ND_RETURN, //"return"
  ND_BLOCK, // {...}
  ND_IF, // "if"
  ND_EXPR_STMT, // Expression statement
  ND_VAR, // Valiable
  ND_NUM, // Integer
} NodeKind;

// AST node type
struct Node {
  NodeKind kind; // Node kind
  Node *next;    // Next node
  Node *lhs;     // Left-hand side
  Node *rhs;     // Right-hand side

  // "if"
  Node *cond;
  Node *then;
  Node *els;
  
  Node *body;    // Block
  Obj *var;      // Used if kind == ND_VAR
  int val;       // Used if kind == ND_NUM
};

Function *parse(Token *tok);

//
// codegen.c
//

void codegen(Function *prog);