
SRC=lex.yy.c parser.tab.cc main.cc
SRCH=
OBJ=$(SRC:.cc=.o)
CXXFLAGS=-lfl -Wall -Wpedantic

prog: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

lex.yy.c: lexer.ll parser.tab.cc
	flex $<

parser.tab.cc: parser.yy
	bison -d $<

clean:
	rm -fr $(OBJ) *~ lex.yy.c parser.tab.cc parser.tab.hh prog

.PHONY: clean
