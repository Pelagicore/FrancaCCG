CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
all: 	RunFCCG

clean:
	rm -f *.o franca.dvi franca.aux franca.log 
	rm -f franca.pdf RunFCCG

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H franca.l franca.y franca.tex franca.dvi franca.aux franca.log franca.ps RunFCCG 
	 rm -f *.bak

bnfc:	
	bnfc -cpp_stl franca.cf

RunFCCG: bnfc Absyn.o Lexer.o Parser.o Printer.o XMLGenerator.o GenerateXML.o CustomTypesParser.o CustomType.o
	@echo "Linking RunFCCG..."
	${CC} ${CCFLAGS} *.o -o RunFCCG

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: franca.l
	${FLEX} -oLexer.C franca.l

Parser.C: franca.y
	${BISON} franca.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C
	
CustomTypesParser.o: CustomTypesParser.cpp CustomType.h Absyn.H
	${CC} ${CCFLAGS} -c CustomTypesParser.cpp
	
CustomType.o: CustomType.cpp
	${CC} ${CCFLAGS} -c CustomType.cpp

XMLGenerator.o: XMLGenerator.cpp XMLGenerator.h Absyn.H CustomTypesParser.h CustomType.h
	${CC} ${CCFLAGS} -c XMLGenerator.cpp

GenerateXML.o: GenerateXML.cpp Parser.H Printer.H Absyn.H XMLGenerator.h
	${CC} ${CCFLAGS} -c GenerateXML.cpp

