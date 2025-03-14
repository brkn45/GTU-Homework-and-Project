%{
/*definitions*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
FILE *p_inputFile,*p_stringStream;
FILE *output;
extern FILE *yyin;
void writeList(int *list);
%}

%union{
    int operand;
    int *operands;
    char expr[30];
}
 /*tokens of operators*/
%token	OP_AND OP_OR OP_NOT OP_EQ OP_GT KW_NIL OP_SET DEFV
		DEFF KW_WHILE KW_IF KW_EXIT KW_LOAD KW_DISP KW_TRUE KW_FALSE
		OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_OC OP_CC OP_COMMA 
        
		COMMENT
/*token for value*/
%token <operand> VALUE
/* token for identifier*/
%token <expr> IDENTIFIER

/*Types*/
%type <operand> EXPI
%type <operand> EXPB
%type <operands> VALUES
%type <operands> EXPLIST
%type <operands> ELEMENTS

%start START
%%
/*gpp Concrete Syntax*/
/*START -> INPUT*/
/*INPUT -> EXPI | EXPLISTI*/
START:
    EXPI {fprintf(output,"SYNTAX OK. \nResult: %d\n", $1);}
    |
    EXPLIST {fprintf(output,"SYNTAX OK. \nResult: ");writeList($1);}
    /*|error { yyerrok; yyclearin;}*/
    ;

START:
    EXPB {fprintf(output,"SYNTAX OK. \nResult: %s\n", $1 == 1 ? "T" : "NIL");}
    |
    START EXPI {fprintf(output,"SYNTAX OK. \nResult: %d\n", $2);}
    |
    START EXPLIST {fprintf(output,"SYNTAX OK. \nResult:"); writeList($2); }
    |
    START EXPB {fprintf(output,"SYNTAX OK. \nResult: %s\n", $2 == 1 ? "T" : "NIL");}
    |
    COMMENT {}
    |
    START COMMENT {}
    |
    OP_OP KW_EXIT OP_CP { printf("File has created!\n"); exit(-1);}
    |
    START OP_OP KW_EXIT OP_CP { printf("File has created!\n"); exit(-1); }
    ;
EXPI:
    /* (+ EXPI EXPI) G++ Syntax*/
    OP_OP OP_PLUS EXPI EXPI OP_CP  {$$=$3+$4;}
    |
    /* (- EXPI EXPI) */
    OP_OP OP_MINUS EXPI EXPI OP_CP {$$=$3-$4;}
    |
    /* (* EXPI EXPI) */
    OP_OP OP_MULT EXPI EXPI OP_CP  {$$=$3*$4;}
    |
    /* (/ EXPI EXPI) */
    OP_OP OP_DIV EXPI EXPI OP_CP   {$$=$3/$4;}
    |
    IDENTIFIER {$$ = getDataOfVariable($1);}
    |
    VALUE {$$ = $1;}
    |
    OP_OP OP_SET IDENTIFIER EXPI OP_CP {$$ = $4; addNewVariable($3, $4);}
    |
    OP_OP KW_IF EXPB EXPI OP_CP {$$ = (1 == $3) ? $4: 0;}
    |
    OP_OP KW_WHILE EXPB EXPI OP_CP { $$ = (1 == $3) ? $4 : 0; }
    |
    OP_OP KW_IF EXPB EXPI EXPI OP_CP {$$ = (1 == $3) ? $4: $5;}
    |
    OP_OP KW_DISP EXPI OP_CP { $$ = $3; fprintf(output,"Display : %d\n", $3);}
    ;

EXPB:
    OP_OP OP_AND EXPB EXPB OP_CP {$$ = $3 && $4;}
    |
    OP_OP OP_OR EXPB EXPB OP_CP  {$$ = $3 || $4;}
    |
    OP_OP OP_NOT EXPB OP_CP  {$$ = ! ($3);}
    |
    OP_OP OP_EQ EXPB EXPB OP_CP {$$ = ($3 == $4);}
    |
    OP_OP OP_EQ EXPI EXPI OP_CP {$$ = ($3 == $4);}
    |
    OP_OP OP_GT EXPI EXPI OP_CP { $$ = $3 > $4; }
    |
    KW_TRUE  { $$ = 1; }
    |
    KW_FALSE   { $$ = 0; }
    |
    OP_OP KW_DISP EXPB OP_CP { $$ = $3; fprintf(output,"Display : %s\n", ($3 ? "T":"NIL"));}
    ;

EXPLIST:
    ELEMENTS  {$$ = $1;}
    |
    OP_OP KW_DISP ELEMENTS OP_CP { $$ = $3; fprintf(output,"Display : "); writeList($3);}
    ;


ELEMENTS:
    OP_OP VALUES OP_CP {$$ = $2;}
    |
    OP_OP OP_CP { $$= NULL; }
    |
    KW_NIL { $$ = NULL;}
    ;
VALUES:
    VALUES VALUE  {$$ = appendElementToList($1, $2);}
    |
    VALUE {$$ = NULL; $$ = appendElementToList($$, $1);}
    ;

%%

int yyerror(char *error) {
    fprintf(output, "SYNTAX ERROR \n");
}

void writeList(int *list){
    fprintf(output, "(");
    for(int i=0;list[i]!=-999; ++i){
      if(list[i+1]!=-999){
        fprintf(output,"%d ", list[i]);
      }
      else{
        fprintf(output,"%d", list[i]);
      }

    }
    fprintf(output, ")\n");
}
int main(int argc, char **argv){
  output = fopen("parsed_cpp.txt","w");
  printf("1\n");
  if(output == NULL)
  {
    printf("Error parsed_cpp.txt doesn't exist!\n");
    exit(1);
  }
  printf("2\n");
  if(argc > 1){
    //read input from file
    p_inputFile = fopen(argv[1],"r");
    if(p_inputFile == NULL)
    {
      printf("Error File doesn't exist!\n");
      exit(1);
    }
    printf("3\n");
    yyin = p_inputFile;
    yyparse();
    printf("File has created!\n");
    
  }
  else{
    //read input from terminal in repl mode
    printf("Welcome to G++ shell made by Akif with Flex and Yacc, to exit enter empty string\n> ");
    char* newLine = NULL;
    char* line = (char*)malloc(20*sizeof(char));;
    int is_empty_string;
    size_t size = 0;
    //read until empty string and store them
    do{
      is_empty_string = getline(&newLine, &size, stdin);
      if(is_empty_string != 1){
        line = (char *) realloc(line, (strlen(line)+size+2)*sizeof(char));
        strcat(line,newLine);
      }
    }while(is_empty_string != 1);
    //after reading, tokenize by using string stream fuction fmemopen
    p_stringStream = fmemopen (line, strlen (line) - 1, "r");
    printf("4\n");
    yyin = p_stringStream;
    printf("5\n");
    yyparse();
    printf("File has created!\n");
  }
  printf("6\n");
  exit(-1);
}
