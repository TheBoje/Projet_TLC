OUT_DIR=build
CXX=g++
SRC_DIR=clurtle_drawer/src
CXXFLAGS=-g -Wpedantic -Wall -Wextra -pthread -I${OUT_DIR} -I${SRC_DIR} -Iclurtle_drawer/include -lm -lfl
IN_FILE=exemples/quadrilataire.cl

SRC=${wildcard ${SRC_DIR}/*.cc}
OBJ=${patsubst %.cc,${OUT_DIR}/%.o,${SRC}}
OBJ_B=${patsubst %, build/%, ${notdir ${OBJ}}}


default: clurtle

clurtle_cpp: clurtle ${IN_FILE} clurtle_drawer/clurtle_cpp.header clurtle_drawer/clurtle_cpp.footer
	${OUT_DIR}/$< ${OUT_DIR}/${basename ${notdir ${IN_FILE}}} < ${IN_FILE}
	${CXX} ${OUT_DIR}/${basename ${notdir ${IN_FILE}}}.cpp -o ${OUT_DIR}/${basename ${notdir ${IN_FILE}}} -Iclurtle_drawer/include -pthread -lX11

clurtle: ${OBJ} lex.yy.c ${OUT_DIR}/parser.tab.o ${IN_FILE}
	${CXX} -o ${OUT_DIR}/$@ ${CXXFLAGS} ${OUT_DIR}/lex.yy.c ${OUT_DIR}/parser.tab.o ${OBJ_B} -lX11

mkdir:
	@mkdir -p ${OUT_DIR}

${OUT_DIR}/%.o : %.cc mkdir lex.yy.c
	${CXX} ${CXXFLAGS} -o ${OUT_DIR}/${notdir $@} $< -c

lex.yy.c: clurtle_drawer/lexer.ll parser.tab.cc
	flex -o ${OUT_DIR}/$@ $<

parser.tab.cc: clurtle_drawer/parser.yy mkdir
	bison -d $< -o ${OUT_DIR}/$@

${OUT_DIR}/parser.tab.o: parser.tab.cc
	${CXX} ${CXXFLAGS} -o $@ ${OUT_DIR}/$< -c


clean:
	rm -fr ${OBJ} *~ lex.yy.c parser.tab.cc parser.tab.hh clurtle parser.output *.png *.bmp clurtle_cpp.cpp clurtle_cpp build

.PHONY: clean
