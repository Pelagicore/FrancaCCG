/*
    Copyright (c) 2015, Pelagicore AB.
    All rights reserved.
    
    This software was orgininally developed as part of the Master's Thesis
    "Franca IDL C Code Generator - Development and Evaluation of New
    Tools for Franca IDL" conducted at Chalmers University of Technology
    2015 by Jesper Lundkvist (jesperlundkvist@gmail.com).
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/



#ifndef CUSTOMTYPESPARSER_HEADER
#define CUSTOMTYPESPARSER_HEADER

#include "Absyn.H"
#include "Parser.H"

#include "CustomType.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>


class CustomTypesParser : public Visitor {

protected:
    std::string pathToImportFile;
    std::string currentFQN;    
    std::string tempString;
    CustomType* currentCT;
    std::vector<CustomType> unfinished;
    std::string namespaceToImport;

    std::vector<CustomType> parseUnfinishedList(std::vector<CustomType> unfinished);
    bool isInNamespaceToImport(std::string fqn, std::string ns);
    
    void visitProgram(Program* p);
    void visitDef(Def* p);
    void visitPackageName(PackageName* p);
    void visitFileName(FileName* p);
    void visitFileEnding(FileEnding* p);
    void visitNamespace(Namespace* p);
    void visitNamespaceID(NamespaceID* p);
    void visitIBody(IBody* p);
    void visitIBodyItem(IBodyItem* p);
    void visitInVari(InVari* p);
    void visitOutVari(OutVari* p);
    void visitVari(Vari* p);
    void visitEnumId(EnumId* p);
    void visitEnumList(EnumList* p);
    void visitEnum(Enum* p);
    void visitTypeDefId(TypeDefId* p);
    void visitType(Type* p);
    void visitProg(Prog* p);
    void visitDPackage(DPackage* p);
    void visitDPackageName(DPackageName* p);
    void visitDInterface(DInterface* p);
    void visitDTypeCollection(DTypeCollection* p);
    void visitDImport(DImport* p);
    void visitDFileName(DFileName* p);
    void visitDFileNameNoEnd(DFileNameNoEnd* p);
    void visitDFileEnding(DFileEnding* p);
    void visitDNamespace(DNamespace* p);
    void visitDNamespaceID(DNamespaceID* p);
    void visitDNamespaceIDAll(DNamespaceIDAll* p);    
    void visitDIBody(DIBody* p);
    void visitDMethod(DMethod* p);
    void visitDInMethod(DInMethod* p);
    void visitDOutMethod(DOutMethod* p);
    void visitDInOutMethod(DInOutMethod* p);
    void visitDVersion(DVersion* p);
    void visitDAttrib(DAttrib* p);
    void visitDAttribReadOnly(DAttribReadOnly* p);
    void visitDAttribNoSub(DAttribNoSub* p);
    void visitDAttribReadOnlyNoSub(DAttribReadOnlyNoSub* p);
    void visitDAttribReadOnlyNoSub2(DAttribReadOnlyNoSub2* p);
    void visitDInVar(DInVar* p);
    void visitDOutVar(DOutVar* p);
    void visitDVar(DVar* p);
    void visitDEnumDef(DEnumDef* p);
    void visitDExtendedEnumDef(DExtendedEnumDef* p);
    void visitDEnumIdent(DEnumIdent* p);
    void visitDEnumList(DEnumList* p);
    void visitDEnum(DEnum* p);
    void visitDEnumValue(DEnumValue* p);
    void visitDTypeDef(DTypeDef* p);
    void visitDTypeDefCustom(DTypeDefCustom* p);
    void visitDTypeDefIdent(DTypeDefIdent* p);
    void visitDUIntEight(DUIntEight* p);
    void visitDIntEight(DIntEight* p);
    void visitDUIntSixteen(DUIntSixteen* p);
    void visitDIntSixteen(DIntSixteen* p);
    void visitDUIntThirtyTwo(DUIntThirtyTwo* p);
    void visitDIntThirtyTwo(DIntThirtyTwo* p);
    void visitDUIntSixtyFour(DUIntSixtyFour* p);
    void visitDIntSixtyFour(DIntSixtyFour* p);
    void visitDBoolean(DBoolean* p);
    void visitDFloat(DFloat* p);
    void visitDDouble(DDouble* p);
    void visitDString(DString* p);
    void visitDByteBuffer(DByteBuffer* p);
    void visitDCustomType(DCustomType* p);
    void visitListDef(ListDef* p);
    void visitListNamespaceID(ListNamespaceID* p);
    void visitListIBodyItem(ListIBodyItem* p);
    void visitListVari(ListVari* p);
    void visitListInVari(ListInVari* p);
    void visitListOutVari(ListOutVari* p);
    void visitListEnum(ListEnum* p);

    void visitId(Id x);
    void visitInteger(Integer x);
    void visitChar(Char x);
    void visitDouble(Double x);
    void visitString(String x);
    void visitIdent(Ident x);

public:
  
    std::vector<CustomType> findCustomTypes(Visitable *v, std::string s, std::string ns);
    std::vector<CustomType> findUnfinishedTypes(Visitable *v, std::string s, std::string ns);

    CustomTypesParser(void);
    ~CustomTypesParser(void);
};

#endif
