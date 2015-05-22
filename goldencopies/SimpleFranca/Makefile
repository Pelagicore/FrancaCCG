CC = gcc
CCFLAGS = -Wall -g $(shell pkg-config --cflags glib-2.0 gio-2.0)
LIBS = $(shell pkg-config --libs glib-2.0 gio-2.0)

all: 	ProxyImplementation StubImplementation

clean:
	rm -f *.o simpleFranca_stubImplementation simpleFranca_proxyImplementation

distclean: clean

ProxyImplementation:
	${CC} ${CCFLAGS} simpleFranca_proxyImplementation.c simpleFranca_proxy.c ${LIBS} -o simpleFranca_proxyImplementation
	
StubImplementation: 
	${CC} ${CCFLAGS} simpleFranca_stubImplementation.c simpleFranca_stub.c ${LIBS} -o simpleFranca_stubImplementation
