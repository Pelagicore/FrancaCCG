#!/bin/bash
cd FIDLtoXML
make distclean
cd ..
cd XMLtoC
rm *.pyc
cd ..
rm -f fidl/simpleFranca/simpleFranca.xml
rm -f fidl/simpleFranca/simpleFranca_proxyImplementation
rm -f fidl/simpleFranca/simpleFranca_proxyImplementation.c
rm -f fidl/simpleFranca/simpleFranca_proxy.c
rm -f fidl/simpleFranca/simpleFranca_proxy.h
rm -f fidl/simpleFranca/simpleFranca_stubImplementation
rm -f fidl/simpleFranca/simpleFranca_stubImplementation.c
rm -f fidl/simpleFranca/simpleFranca_stub.c
rm -f fidl/simpleFranca/simpleFranca_stub.h
rm -f fidl/simpleFranca/simpleFranca_common.h


