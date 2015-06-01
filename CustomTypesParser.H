#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream> 
#include <iostream>
#include "Parser.H"
#include "Printer.H"

enum FRANCA_DATATYPE {NO_TYPE, FRANCA_ENUM, FRANCA_TYPEDEF} ;

class CustomType {

protected:
    String name; // Name of custom type
    FRANCA_DATATYPE type; // Type. Mainly used to separate enums from others.
    String data; // the franca signature of the type
    String dbussign;
    String emum_extends; // Only for enums. Name of enumeration to extend.
    std::vector<String> enum_members; // Only for enums. List of enum members.
    std::vector<String> enum_values; // Only for enums. List of enum values.

public:

    String getName();
    FRANCA_DATATYPE getType();
    String getTypeString();
    String getEnumExtends();
    String getData();
    String getDBusSign();
    String getEnumMember(int i);
    String getEnumValue(int i);
    int getNbrOfEnumMembers();
    
    void setName(String name);
    void setType(FRANCA_DATATYPE type);
    void setData(String data);
    void setEnumExtends(String enum_extends);
    void addEnum(String name, String value);
    void setEnumValue(int i, String value);
    void setDBusSign(String sign);

    CustomType(void);
    ~CustomType(void);    
    CustomType(String name, FRANCA_DATATYPE type, String data);

};




class CustomTypesParser : public Visitor
{

protected:
  String importedFileName;
  String importedNameSpace;
  String pathToImportFile;
  String tempString;
  CustomType* currentCT;
  std::vector<CustomType> unfinished;
  std::vector<CustomType> finished;

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

