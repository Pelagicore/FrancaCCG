# About

FrancaCCG (Franca C Code Generator) is a code generator suite for the Franca Interface Definition Language, runnable from the command line and producing C server stubs and proxies using the GDBus library. Originally developed by Jesper Lundkvist <jesperlundkvist@gmail.com> as part of Master Thesis conducted at Pelagicore AB during spring 2015

#### Currently supports subset of Franca IDL only!
See fidl/MediaIndexer/ for example of supported features.


# Prerequisites (software requirements)

BNFC 2.7.1 (older probably works as well)
GCC (latest version)
Bison 1.75 (version important! Newer versions incompatible with BNFC)
Flex 2.5.4 (version probably important)


# Usage

Compile the code generators with ./compile.sh 

Use ./run.sh <path to fidl file> <optional path to output folder> to generate stub and proxy fidl file given.
If no output folder is given, C files will be generated in the folder of the *.fidl file.

Use ./cleanup.sh to return to pre-compilation state.


## FRANCA IDL SUBSET SUPPORTED
(to be continued)


## KNOWN BUGS
- XMLtoC does not handle multiple methods with the same name very well.
