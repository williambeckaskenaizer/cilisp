all: cilisp

cilisp.tab.c cilisp.tab.h:	cilisp.y
	bison -d cilisp.y

lex.yy.c: cilisp.l cilisp.tab.h
	flex cilisp.l

cilisp: lex.yy.c cilisp.tab.c cilisp.tab.h
	gcc -o cilisp cilisp.c cilisp.tab.c lex.yy.c -g -lm

clean:
	rm -R cilisp cilisp.tab.c lex.yy.c cilisp.tab.h cilisp.dSYM
