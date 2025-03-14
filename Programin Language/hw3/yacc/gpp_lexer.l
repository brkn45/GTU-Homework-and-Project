%{
  /*definitions*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
//FILE *p_inputFile,*p_stringStream;
//FILE *output;
char *bg_substr(const char *src, int m, int n);
%}
 /*Rule and DFA part of lexer*/
%%

 /*rules of operators*/
\+ { return OP_PLUS; }
\- { return OP_MINUS; }
\/ { return OP_DIV; }
\* { return OP_MULT; }
\( { return OP_OP; }
\) { return OP_CP;  }
, { return OP_COMMA; }

 /*rules for keywords in g++ language*/
and { return OP_AND; }
or { return OP_OR; }
not { return OP_NOT; }
equal { return OP_EQ; }
gt { return OP_GT; }
nil { return KW_NIL; }
set { return OP_SET; }
defvar { return DEFV; }
deffun { return DEFF; }
while { return KW_WHILE; }
if { return KW_IF; }
exit {return KW_EXIT; }
load {return KW_LOAD; }
disp {return KW_DISP; }
true {return KW_TRUE; }
false {return KW_FALSE; }





 /*rule for comment*/
;;(.*) { return COMMENT; }
 /*rule for value*/
(0)|([1-9][0-9]*) { yylval.operand = atoi(yytext); return VALUE;  }


 /* rule for identifier*/
[a-zA-Z][0-9a-zA-Z]* {strcpy(yylval.expr, yytext); return IDENTIFIER;}
[\n\f\r\t ] {} /*ignorable tokens*/
   

%%
 /*C code part*/
int yywrap(){} 
/*int main(int argc, char **argv){
  output = fopen("parsed_cpp.txt","w");
  if(output == NULL)
  {
    printf("Error parsed_cpp.txt doesn't exist!\n");   
    exit(1);             
  }
  if(argc > 1){
    //read input from file
    p_inputFile = fopen(argv[1],"r");
    if(p_inputFile == NULL)
    {
      printf("Error File doesn't exist!\n");   
      exit(1);             
    }
    yyin = p_inputFile;
    yylex();
    printf("File has created!\n");  
  }
  else{
    //read input from terminal in repl mode
    printf("Welcome to G++ shell with Flex, to exit enter empty string\n> ");
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
    yyin = p_stringStream;
    yylex();
    printf("File has created!\n");
  }
  return 0;
}

char *bg_substr(const char *src, int m, int n)
{
  // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}*/