Developed by Jesper Lundkvist
jesperlundkvist@gmail.com

Developed as part of Master Thesis conducted at Pelagicore during spring 2015


---PREREQUISITIES---

BNFC 2.7.1 (older probably works as well)
GCC (latest version)
Bison 1.75 (version important! Newer not compatible with BNFC)
Flex 2.5.4 (version probably important)



---USAGE---

Compile the code generators with ./compile.sh 

Use ./run.sh <path to fidl file> <optional path to output folder> to generate stub and proxy fidl file given.
If no output folder is given, C files will be generated in the folder of the *.fidl file.

Use ./cleanup.sh to return to pre-compilation state.



---FRANCA IDL SUBSET SUPPORTED---
(to be continued)



---KNOWN BUGS---
(to be continued)

- XMLtoC does not handle multiple methods with the same name very well.
