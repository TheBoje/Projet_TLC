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
	main.cc

#	clurtle_drawer/src/clurtle.cc \

SRCH=clurtle_drawer/include/affectation.hh \
	clurtle_drawer/include/change_color.hh \
	clurtle_drawer/include/color.hh \
	clurtle_drawer/include/conditional.hh \
	clurtle_drawer/include/constant.hh \
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
CXXFLAGS=-lfl -Wall -Wpedantic -Iclurtle_drawer/include -Iclurtle_drawer/src

clurtle: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

lex.yy.c: lexer.ll parser.tab.cc
	flex $<

parser.tab.cc: parser.yy
	bison -vd $<

clean:
	rm -fr $(OBJ) *~ lex.yy.c parser.tab.cc parser.tab.hh clurtle

.PHONY: clean
