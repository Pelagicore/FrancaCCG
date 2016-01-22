Originally developed by Jesper Lundkvist <jesperlundkvist@gmail.com>
Part of Master Thesis conducted at Pelagicore AB during spring 2015

Currently supports subset of Franca IDL only!
See fidl/MediaIndexer/ for example of supported features.



# PREREQUISITIES

BNFC 2.7.1 (older probably works as well)
GCC (latest version)
Bison 1.75 (version important! Newer not compatible with BNFC)
Flex 2.5.4 (version probably important)


# USAGE

Compile the code generators with ./compile.sh 

Use ./run.sh <path to fidl file> <optional path to output folder> to generate stub and proxy fidl file given.
If no output folder is given, C files will be generated in the folder of the *.fidl file.

Use ./cleanup.sh to return to pre-compilation state.


## FRANCA IDL SUBSET SUPPORTED
(to be continued)


## KNOWN BUGS
- XMLtoC does not handle multiple methods with the same name very well.
