CC = gcc
CCFLAGS = -Wall -g $(shell pkg-config --cflags glib-2.0 gio-2.0)
LIBS = $(shell pkg-config --libs glib-2.0 gio-2.0)

all: 	ProxyImplementation StubImplementation

clean:
	rm -f *.o MediaIndexer_stubImplementation MediaIndexer_proxyImplementation

distclean: clean

ProxyImplementation:
	${CC} ${CCFLAGS} MediaIndexer_proxyImplementation.c MediaIndexer_proxy.c ${LIBS} -o MediaIndexer_proxyImplementation
	
StubImplementation: 
	${CC} ${CCFLAGS} MediaIndexer_stubImplementation.c MediaIndexer_stub.c ${LIBS} -o MediaIndexer_stubImplementation
