README v0.1
Written by Jesper Lundkvist
jesperlundkvist@gmail.com

Part of Master Thesis conducted at Pelagicore


---Prerequisities---

BNFC 2.7.1 (older probably works as well)
GCC (latest version)
Bison 1.75 (version important! Newer not compatible with BNFC)
Flex 2.5.4 (version probably important)



---File list---

franca.cf		Franca BNF grammar definitions.
francaTest1.fidl	Example Franca interface file.
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
