CC = gcc
CCFLAGS = -Wall -g $(shell pkg-config --cflags glib-2.0 gio-2.0)
LIBS = $(shell pkg-config --libs glib-2.0 gio-2.0)

all: 	ProxyImplementation StubImplementation

clean:
	rm -f *.o MediaIndexer_customStubImplementation MediaIndexer_customProxyImplementation

distclean: clean

ProxyImplementation:
	${CC} ${CCFLAGS} MediaIndexer_customProxyImplementation.c MediaIndexer_proxy.c ${LIBS} -o MediaIndexer_customProxyImplementation
	
StubImplementation: 
	${CC} ${CCFLAGS} MediaIndexer_customStubImplementation.c MediaIndexer_stub.c ${LIBS} -o MediaIndexer_customStubImplementation
