#ifndef CUSTOMTYPESPARSER_HEADER
#define CUSTOMTYPESPARSER_HEADER

#include "Absyn.H"
#include "Parser.H"

#include "CustomType.H"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>


class CustomTypesParser : public Visitor
{

protected:
  std::string importedFileName;
  std::string importedNameSpace;
  std::string pathToImportFile;
  std::string tempString;
  CustomType* currentCT;
  std::vector<CustomType> unfinished;

  std::vector<CustomType> parseUnfinishedList(std::vector<CustomType> unfinished);
  
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
  
  std::vector<CustomType> findCustomTypes(Visitable *v, String s);
  std::vector<CustomType> findUnfinishedTypes(Visitable *v, String s);

  CustomTypesParser(void);
  ~CustomTypesParser(void);
};

#endif
