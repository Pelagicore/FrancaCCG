#!/bin/bash
make distclean
cd codegen_francac
rm *.pyc
cd ..
rm -f simpleFranca/simpleFranca.xml
rm -f simpleFranca/simpleFranca_proxyImplementation
rm -f simpleFranca/simpleFranca_proxyImplementation.c
rm -f simpleFranca/simpleFranca_proxy.c
rm -f simpleFranca/simpleFranca_proxy.h
rm -f simpleFranca/simpleFranca_stubImplementation
rm -f simpleFranca/simpleFranca_stubImplementation.c
rm -f simpleFranca/simpleFranca_stub.c
rm -f simpleFranca/simpleFranca_stub.h


