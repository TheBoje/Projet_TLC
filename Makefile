SRC=lex.yy.c parser.tab.cc \
	clurtle_drawer/src/affectation.cc \
	clurtle_drawer/src/change_color.cc \
	clurtle_drawer/src/color.cc \
	clurtle_drawer/src/conditional.cc \
	clurtle_drawer/src/constant.cc \
	clurtle_drawer/src/for_loop.cc \
	clurtle_drawer/src/forward.cc \
	clurtle_drawer/src/line.cc \
	clurtle_drawer/src/ope.cc \
	clurtle_drawer/src/rectangle.cc \
	clurtle_drawer/src/rotate.cc \
	clurtle_drawer/src/seq.cc \
	clurtle_drawer/src/variable.cc \
	clurtle_drawer/src/while_loop.cc \
	clurtle_drawer/src/clurtle_cpp.cc \
	clurtle_drawer/src/clurtle.cc \
	main.cc

SRCH=clurtle_drawer/include/affectation.hh \
	clurtle_drawer/include/change_color.hh \
	clurtle_drawer/include/color.hh \
	clurtle_drawer/include/conditional.hh \
	clurtle_drawer/include/constant.hh \
	clurtle_drawer/include/CImg.h \
	clurtle_drawer/include/down.hh \
	clurtle_drawer/include/expr.hh \
	clurtle_drawer/include/for_loop.hh \
	clurtle_drawer/include/forward.hh \
	clurtle_drawer/include/instr.hh \
	clurtle_drawer/include/line.hh \
	clurtle_drawer/include/ope.hh \
	clurtle_drawer/include/rectangle.hh \
	clurtle_drawer/include/rotate.hh \
	clurtle_drawer/include/seq.hh \
	clurtle_drawer/include/term.hh \
	clurtle_drawer/include/up.hh \
	clurtle_drawer/include/variable.hh \
	clurtle_drawer/include/visitor.hh \
	clurtle_drawer/include/while_loop.hh \
	clurtle_drawer/include/clurle_cpp.hh \
	clurtle_drawer/include/clurtle.hh
OBJ=$(SRC:.cc=.o)
CXX=g++
CXXFLAGS=-g -Wpedantic -Wall -Wextra -pthread -Iclurtle_drawer/include -Iclurtle_drawer/src -lm -lpthread -lfl

IN_FILE=exemples/quadrilataire.cl

default: clurtle

clurtle_cpp: clurtle $(IN_FILE) clurtle_cpp.header clurtle_cpp.footer
	./clurtle < $(IN_FILE)
	$(CXX) $@.cpp -o $@ -Iclurtle_drawer/include -L/usr/include -pthread -lX11

clurtle: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -lX11

lex.yy.c: lexer.ll parser.tab.cc
	flex $<

parser.tab.cc: parser.yy
	bison -vd $<

clean:
	rm -fr $(OBJ) *~ lex.yy.c parser.tab.cc parser.tab.hh clurtle parser.output *.png clurle_cpp.cpp 

.PHONY: clean