#!/bin/bash
make
./RunFCCG simpleFranca/simpleFranca.fidl
python -m codegen_francac.codegen_main --generate-c-code simpleFranca/simpleFranca simpleFranca/simpleFranca.xml 
cd simpleFranca
make

