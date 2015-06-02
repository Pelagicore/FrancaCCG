#ifndef XMLGENERATOR_HEADER
#define XMLGENERATOR_HEADER

#include "Absyn.H"
#include "CustomTypesParser.H"
#include "CustomType.H"

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000

class GenerateDBusXML : public Visitor
{
 public:
  GenerateDBusXML(void);
  ~GenerateDBusXML(void);
  char* generate(Visitable* v, std::string s);
  void createCustomTypesList(Visitable *v, std::string s);

 protected:
  int _n_, _i_;
  std::string packageName;
  std::string nameOfEnum;
  std::vector<CustomType> finishedTypes;
  std::string pathToImportFile;

  void newIndLine(void);
  void increaseIndent(void);
  void decreaseIndent(void);
  void render(Char c);
  void render(std::string s);
  void indent(void);
  void removeLastDot(void);
  void removeLastComma(void);
  void removeLine(void);
 
 
 std::string getCustomTypeSig(std::string name);
  void setNameOfEnum(std::string name);
  void renderEnumMembersIfNeeded();
  void saveNamespaceId(std::string s);
  
  void visitPackageName(std::string s_);
  void visitProgram(Program *p); /* abstract class */
  void visitProg(Prog *p);
  void visitDef(Def *p); /* abstract class */
  void visitEnum(Enum* p);
  void visitEnumList(EnumList* p);
  void visitEnumId(EnumId* p);
  void visitDPackage(DPackage *p);
  void visitDInterface(DInterface *p);
  void visitListDef(ListDef* p);
  void visitIBody(IBody *p); /* abstract class */
  void visitDIBody(DIBody *p);
  void visitListIBodyItem(ListIBodyItem* p);
  void visitIBodyItem(IBodyItem *p); /* abstract class */
  void visitDEnumDef(DEnumDef* p);
  void visitDEnum(DEnum* p);
  void visitDEnumValue(DEnumValue* p);
  void visitDEnumList(DEnumList* p);
  void visitDExtendedEnumDef(DExtendedEnumDef* p);
  void visitDEnumIdent(DEnumIdent* p);
  void visitDVersion(DVersion *p);
  void visitDMethod(DMethod *p);
  void visitDInMethod(DInMethod *p);
  void visitDOutMethod(DOutMethod *p);
  void visitDInOutMethod(DInOutMethod *p);  
  void visitDAttrib(DAttrib* p);
  void visitDAttribReadOnly(DAttribReadOnly* p);
  void visitDAttribNoSub(DAttribNoSub* p);
  void visitDAttribReadOnlyNoSub(DAttribReadOnlyNoSub* p);
  void visitDAttribReadOnlyNoSub2(DAttribReadOnlyNoSub2* p);
  void visitVari(Vari *p); /* abstract class */
  void visitDVar(DVar *p);
  void visitInVari(InVari *p); /* abstract class */
  void visitDInVar(DInVar *p);
  void visitOutVari(OutVari *p); /* abstract class */
  void visitDOutVar(DOutVar *p);
  void visitListVari(ListVari* p);
  void visitListInVari(ListInVari* p);
  void visitListOutVari(ListOutVari* p);
  void visitDTypeDef(DTypeDef* p);
  void visitType(Type *p); /* abstract class */
  void visitDUIntEight(DUIntEight *p);
  void visitDIntEight(DIntEight *p);
  void visitDUIntSixteen(DUIntSixteen *p);
  void visitDIntSixteen(DIntSixteen *p);
  void visitDUIntThirtyTwo(DUIntThirtyTwo *p);
  void visitDIntThirtyTwo(DIntThirtyTwo *p);
  void visitDUIntSixtyFour(DUIntSixtyFour *p);
  void visitDIntSixtyFour(DIntSixtyFour *p);
  void visitDBoolean(DBoolean *p);
  void visitDFloat(DFloat *p);
  void visitDDouble(DDouble *p);
  void visitDString(DString *p);
  void visitDByteBuffer(DByteBuffer *p);
  void visitListEnum(ListEnum* p);
  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
  void visitId(String s);
  void visitDTypeDefIdent(DTypeDefIdent* p);
  void visitTypeDefId(TypeDefId* p);
  void visitDTypeDefCustom(DTypeDefCustom* p);
  void visitDTypeCollection(DTypeCollection* p);
  void visitFileName(FileName* p);
  void visitFileEnding(FileEnding* p);
  void visitDImport(DImport* p);
  void visitDFileName(DFileName* p);
  void visitDFileNameNoEnd(DFileNameNoEnd* p);
  void visitDFileEnding(DFileEnding* p);
  void visitDNamespace(DNamespace* p);
  void visitDNamespaceID(DNamespaceID* p);
  void visitNamespace(Namespace* p);
  void visitNamespaceID(NamespaceID* p);
  void visitListNamespaceID(ListNamespaceID* p);
  void visitPackageName(PackageName* p);
  void visitDPackageName(DPackageName* p);  
  void visitDCustomType(DCustomType* p);
 
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;

};

#endif

