.PHONY=all

all: calc run

lex.yy.c: calc.l
	flex calc.l

calc.tab.c: calc.y
	bison -d calc.y

calc: calc.tab.c lex.yy.c
	g++ -o calc calc.tab.c lex.yy.c -lm

run: calc
	./calc
