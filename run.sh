#!/bin/bash

# Usage: ./run.sh <path to fidl file> <optional output folder, if not given uses folder from first argument>
# e.g.   ./run.sh fidl/simpleFranca/simpleFranca.fidl fidl/simpleFranca/output


file_path=`dirname $1`
file_name=`basename $1`
file_extension="${file_name##*.}"
file_name="${file_name%.*}"

echo ""
cd FIDLtoXML
./RunFCCG ../$1
OUT1=$?

if [ $OUT1 != 0 ];then
   echo "ERROR: FIDLtoXML code generator failed. Code generation aborted." >&2
   exit 1
fi


outputfolder=$2
if [ -n "$2" ]; then
    outputfolder=$2
else
    outputfolder=$file_path
fi


   
cd ..
python -m XMLtoC.codegen_main --generate-c-code $outputfolder/$file_name $file_path/$file_name.xml 
OUT2=$?
if [ $OUT2 != 0 ];then
   echo "ERROR: XMLtoC code generator failed. Code generation aborted." >&2
   exit 1
fi

echo "XMLtoC successfully finished generating C server proxy and stub for D-Bus XML file $file_path/$file_name.xml"
echo "Code generation for Franca IDL file $1 was successful."
echo ""




