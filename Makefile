CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
all: RunFCCG

clean:
	rm -f *.o franca.dvi franca.aux franca.log 
	rm -f franca.pdf RunFCCG

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H franca.l franca.y franca.tex franca.dvi franca.aux franca.log franca.ps RunFCCG 

RunFCCG: Absyn.o Lexer.o Parser.o Printer.o XMLGenerator.o GenerateXML.o
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

XMLGenerator.o: XMLGenerator.C XMLGenerator.H Absyn.H
	${CC} ${CCFLAGS} -c XMLGenerator.C

GenerateXML.o: GenerateXML.C Parser.H Printer.H Absyn.H XMLGenerator.H
	${CC} ${CCFLAGS} -c GenerateXML.C

