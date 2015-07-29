#!/bin/bash

# Usage: ./run.sh <path to fidl file>
# e.g.   ./run.sh fidl/simpleFranca/simpleFranca.fidl


file_path=`dirname $1`
file_name=`basename $1`
file_extension="${file_name##*.}"
file_name="${file_name%.*}"


cd FIDLtoXML
make
./RunFCCG ../$1
cd ..
python -m XMLtoC.codegen_main --generate-c-code $file_path/$file_name $file_path/$file_name.xml 
cd $file_path
make
cd ..

