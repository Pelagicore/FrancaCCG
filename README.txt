TEMP README

Use ./run.sh to generate stub and proxy for simpleFranca/simpleFranca.fidl.
Not usable with other Franca files at the moment (will get C compile errors with other files due to debug code)

Use ./cleanup.sh to return to pre-"run.sh" state.







Old readme for just Franca IDL -> D-Bus XML Introspection code generator:



README v0.2
Written by Jesper Lundkvist
jesperlundkvist@gmail.com

Part of Master Thesis conducted at Pelagicore


---Prerequisities---

BNFC 2.7.1 (older probably works as well)
GCC (latest version)
Bison 1.75 (version important! Newer not compatible with BNFC)
Flex 2.5.4 (version probably important)



---File list---

franca.cf		BNF grammar definitions for Franca IDL.
GenerateXML.C		Contains main function.
Makefile		Makefile. Don't generate a new one!
README.txt		This file.
XMLGenerator.C		Code for the actual XML generator.
XMLGenerator.H		Header file for XML generator.



---Compiling---

make



---Usage---

./RunFCCG francaTestFile.fidl

Output will be francaTestFile.xml.
