#ifndef _yy_defines_h_
#define _yy_defines_h_

#define OP_AND 257
#define OP_OR 258
#define OP_NOT 259
#define OP_EQ 260
#define OP_GT 261
#define KW_NIL 262
#define OP_SET 263
#define DEFV 264
#define DEFF 265
#define KW_WHILE 266
#define KW_IF 267
#define KW_EXIT 268
#define KW_LOAD 269
#define KW_DISP 270
#define KW_TRUE 271
#define KW_FALSE 272
#define OP_PLUS 273
#define OP_MINUS 274
#define OP_DIV 275
#define OP_MULT 276
#define OP_OP 277
#define OP_CP 278
#define OP_OC 279
#define OP_CC 280
#define OP_COMMA 281
#define COMMENT 282
#define VALUE 283
#define IDENTIFIER 284
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE{
    int operand;
    int *operands;
    char expr[30];
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
