gpp_lexer.out : gpp_lexer.c
	 yacc -d test.y
	 lex gpp_lexer.l
	gcc -g lex.yy.c y.tab.c -ll -o test.out
	./test.out
	
clean :
	rm *.o gpp_lexer.out
