/* XML Generator from Franca IDL abstract syntax tree
 * Based on BNFC-generated pretty printer
 ***/

#include "XMLGenerator.h"

#include <iostream>




////////////////////////////////////////////////////////////
// Functions handling the buffer
////////////////////////////////////////////////////////////

void GenerateDBusXML::newIndLine() {
    bufAppend('\n');
    indent();
}

void GenerateDBusXML::increaseIndent() {
    _n_ = _n_ + 3;
}

void GenerateDBusXML::decreaseIndent() {
    _n_ = _n_ - 3;
    if (_n_ < 0) {
        _n_ = 0;
    }
}

void GenerateDBusXML::render(Char c) {
    bufAppend(c);
}

void GenerateDBusXML::render(std::string s_) {
    const char *s = s_.c_str() ;
    if(strlen(s) > 0) {
        bufAppend(s);
    }
}

void GenerateDBusXML::indent() {
    int n = _n_;
    while (n > 0) {
        bufAppend(' ');
        n--;
    }
}

void GenerateDBusXML::removeLastDot() {
    while (buf_[cur_ - 1] == '.') {
        buf_[cur_ - 1] = 0;
        cur_--;
    }
}

void GenerateDBusXML::removeLastComma() {
    while ((buf_[cur_ - 1] == ' ') && (buf_[cur_ - 2] == ',')) {
        buf_[cur_ - 1] = 0;
        buf_[cur_ - 2] = 0;
        cur_--;
        cur_--;
    }
}

void GenerateDBusXML::removeLine() {
    while ((buf_[cur_ - 1] == '\n') || (buf_[cur_ - 1] == ' ')) {
        buf_[cur_ - 1] = 0;
        cur_--;
    }
}










////////////////////////////////////////////////////////////
// Constructors and 'main' functions
////////////////////////////////////////////////////////////

GenerateDBusXML::GenerateDBusXML(void) {
    _n_ = 0;
    buf_ = 0;
    bufReset();
}


GenerateDBusXML::~GenerateDBusXML(void) {
}


char* GenerateDBusXML::generate(Visitable *v, std::string s) {
    _n_ = 0;
    packageName = "";
    pathToImportFile = s;
    bufReset();
  
    //createCustomTypesList(v, s);  

    v->accept(this);
    return buf_;
}


void GenerateDBusXML::createCustomTypesList(Visitable *v, std::string s) {
    CustomTypesParser *parser = new CustomTypesParser();
    finishedTypes = parser->findCustomTypes(v, s, "*"); // "*" to import entire namespace
    // finishedTypes now contain a list of all custom types in fidl file, together with their d-bus signature
}


std::string GenerateDBusXML::getCustomTypeSig(std::string name) {
    for (std::vector<CustomType>::iterator it = finishedTypes.begin(); it != finishedTypes.end(); ++it) {
        if (it->getName().compare(name) == 0) {
            return it->getDBusSign();
        }
    }
    // If name of custom type is not found, it has not been defined. Exit code generation.
    std::cerr << "ERROR: Custom Franca type '" << name << "' has not been defined." << std::endl << "Aborting code generation." << std::endl;
    exit(1);
    return "";
}

void GenerateDBusXML::setNameOfEnum(std::string name) {
    for (std::vector<CustomType>::iterator it = finishedTypes.begin(); it != finishedTypes.end(); ++it) {
        if (it->getName().compare(name) == 0) {
            if (it->getType() == FRANCA_ENUM) {
                // If the custom type found is an enum, set nameOfEnum to its name.
                nameOfEnum = name;
            }
        }
    }
}

void GenerateDBusXML::renderEnumMembersIfNeeded() {
    if (nameOfEnum.compare("") != 0) {
        // nameOfEnum has been set, render all members of that enum    
        for (std::vector<CustomType>::iterator it = finishedTypes.begin(); it != finishedTypes.end(); ++it) {
            if (it->getName().compare(nameOfEnum) == 0) {
                for (int i = 0; i != it->getNbrOfEnumMembers(); i++) {
                    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.Enum." + it->getName() + "." + it->getEnumMember(i) + "\" value=\"" + it->getEnumValue(i) + "\"/>");
                    newIndLine();
                }     
            }
        }
    }
    nameOfEnum = "";
}


////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////


void GenerateDBusXML::visitProgram(Program*p) {} //abstract class
void GenerateDBusXML::visitEnum(Enum* t) {} //abstract class
void GenerateDBusXML::visitEnumList(EnumList* t) {} //abstract class
void GenerateDBusXML::visitEnumId(EnumId* t) {} //abstract class
void GenerateDBusXML::visitTypeDefId(TypeDefId* t) {} //abstract class
void GenerateDBusXML::visitFileName(FileName* t) {} //abstract class
void GenerateDBusXML::visitFileEnding(FileEnding* t) {} //abstract class
void GenerateDBusXML::visitNamespace(Namespace* t) {} //abstract class
void GenerateDBusXML::visitNamespaceID(NamespaceID* t) {} //abstract class
void GenerateDBusXML::visitPackageName(PackageName* t) {} //abstract class
void GenerateDBusXML::visitDef(Def*p) {} //abstract class
void GenerateDBusXML::visitIBodyItem(IBodyItem*p) {} //abstract class
void GenerateDBusXML::visitIBody(IBody*p) {} //abstract class
void GenerateDBusXML::visitVari(Vari*p) {} //abstract class
void GenerateDBusXML::visitInVari(InVari*p) {} //abstract class
void GenerateDBusXML::visitOutVari(OutVari*p) {} //abstract class
void GenerateDBusXML::visitType(Type*p) {} //abstract class












////////////////////////////////////////////////////////////
// PROGRAM - visitor functions
////////////////////////////////////////////////////////////


void GenerateDBusXML::visitProg(Prog* p) {
    render("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"\n");
    render(" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
    increaseIndent();
    newIndLine();
    if(p->listdef_) {p->listdef_->accept(this);}

    removeLine();
    decreaseIndent();
    newIndLine();
    render("</node>");
}









////////////////////////////////////////////////////////////
// FILE IMPORT - visitor functions
////////////////////////////////////////////////////////////
  
    ///// HANDLED IN CustomTypesParser FOR NOW!
    ///// Should be able to import other e.g. interfaces here.
    ///// TODO



void GenerateDBusXML::visitDImport(DImport *dimport) {
    /* 
    importedNameSpace = "";
    importedFileName = "";
  
  
    // Save namespace
    int old_cur = cur_;
    dimport->namespace_->accept(this);
    removeLastDot();
    for (int i = old_cur; i< cur_; i++) {
  	    importedNameSpace.push_back(buf_[i]);
    }
    // Reset buffer, we don't want to print namespace
    cur_ = old_cur;
  
    // File name is saved in its function, not done here. TODO change?
    dimport->filename_->accept(this);
  
    //std::cout << "DEBUG: importedNameSpace: " << importedNameSpace << std::endl; 
    //std::cout << "DEBUG: importedFileName: " << importedFileName << std::endl; 
  
    if (importedNameSpace.at(importedNameSpace.length() -1) == '.' ) {
        importedNameSpace = importedNameSpace.substr(0, importedNameSpace.length()-1);
    }
  
    //std::cout << "DEBUG: importedNameSpace: " << importedNameSpace << std::endl; 
    // Now namespace and file name are saved, and we can open the file.
  
 
    FILE *importedFile;
  
    if (pathToImportFile == "") {
        importedFile = fopen(importedFileName.c_str(), "r");
    } else {
        importedFile = fopen((pathToImportFile + "/" + importedFileName).c_str(), "r");
    }
  
    if (!importedFile) {
        std::cout << "Error importing fidl file from import statement: " << importedFileName << std::endl;
        exit(1);
    }
  
    // do stuff with file...
    // ... but what?
    // Import and render entire type collection for now. Should probably be saved and rendered later on.
    // Also, more importantly: Should only import the specific namespace! TODO
  
  
    Program *imported_parse_tree = pProgram(importedFile);
    if (imported_parse_tree) {
        GenerateDBusXML *imported_g = new GenerateDBusXML();   
        std::string xmlFromImport;
        xmlFromImport = imported_g->generate(imported_parse_tree, pathToImportFile);

        // Some unneccecary XML code has been generated. Eliminate it.
        std::string tmp_packageName = importedNameSpace.substr(0, importedNameSpace.find_last_of("."));
        std::string startString = "<node name=\"" + tmp_packageName + "\">";
        size_t startPos = xmlFromImport.find(startString, 0) + startString.length() + 4; //TODO this nasty 4 should be removed
        size_t endPos = xmlFromImport.find("</node>", startPos);
        std::string strippedXMLImport = xmlFromImport.substr(startPos, endPos-startPos);
    
        //Finally render the stripped string.
        render(strippedXMLImport);

    } else {
        std::cout << "Error parsing imported fidl file: " << importedFileName << std::endl;
    }
  
    fclose(importedFile);
  
    */
}

void GenerateDBusXML::visitDFileName(DFileName *dfilename) {
    /*

    // Save the file name but don't print it (visitId will append it to buffer)
    int old_cur = cur_;
    visitId(dfilename->id_);
    render(".");
    dfilename->fileending_->accept(this);
  
    for (int i = old_cur; i< cur_; i++) {
  	    importedFileName.push_back(buf_[i]);
    }
  
    cur_ = old_cur;
    // Buffer is now reset to before filename was processed,
    // and file name is saved to importedFileName.

    */
}

void GenerateDBusXML::visitDFileNameNoEnd(DFileNameNoEnd *dfilenamenoend) {
    /*
    // Save the file name but don't print it (visitId will append it to buffer)
    int old_cur = cur_;
    visitId(dfilenamenoend->id_);
    for (int i = old_cur; i< cur_; i++) {
  	    importedFileName.push_back(buf_[i]);
    }
  
    cur_ = old_cur;
    // Buffer is now reset to before filename was processed,
    // and file name is saved to importedFileName.
    */
}

void GenerateDBusXML::visitDFileEnding(DFileEnding *dfileending) {
    /*
    visitId(dfileending->id_);
    */
}



















////////////////////////////////////////////////////////////
// NAMESPACES AND PACKAGES - visitor functions
////////////////////////////////////////////////////////////



void GenerateDBusXML::visitDNamespace(DNamespace *dnamespace) {
    dnamespace->listnamespaceid_->accept(this);
}

void GenerateDBusXML::visitDNamespaceID(DNamespaceID *dnamespaceid) {
    visitId(dnamespaceid->id_);
}


void GenerateDBusXML::visitListNamespaceID(ListNamespaceID* listnamespaceid) {
    for (ListNamespaceID::iterator i = listnamespaceid->begin() ; i != listnamespaceid->end() ; ++i) {
        (*i)->accept(this);
        render(".");
    }
}


void GenerateDBusXML::visitDNamespaceIDAll(DNamespaceIDAll *dnamespaceidall) {
  /* Code For DNamespaceIDAll Goes Here */
}



void GenerateDBusXML::visitDPackage(DPackage* p) {
    // Should be one indent to the left
    removeLine();
    decreaseIndent();
    newIndLine();

    render("<node name=\"");
    p->packagename_->accept(this);
    render("\">");

    increaseIndent();
    newIndLine();
}

void GenerateDBusXML::visitDPackageName(DPackageName *dpackagename) {
  
    // Save the package name 
    int old_cur = cur_;
    
    dpackagename->listnamespaceid_->accept(this);
    removeLastDot();
    for (int i = old_cur; i< cur_; i++) {
  	    packageName.push_back(buf_[i]);
    }
  
    //cur_ = old_cur;
}















////////////////////////////////////////////////////////////
// ENUMS - visitor functions
////////////////////////////////////////////////////////////

void GenerateDBusXML::visitDEnumDef(DEnumDef *denumdef) {
    /*
    enum_empty = true;

    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.Enum\" value=\"name=");
    visitId(denumdef->id_);
    render(", members={");
  
    denumdef->enumlist_->accept(this);
  
    if(!enum_empty) {
 	    removeLastComma();
    }
  
    render("}\"/>");
    newIndLine();
    */
}

void GenerateDBusXML::visitDExtendedEnumDef(DExtendedEnumDef *dextendedenumdef) {
    /*
  
    enum_empty = true;
 

    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.Enum\" value=\"name=");

    dextendedenumdef->enumid_->accept(this);
  
    render(", extends=");
  
    visitId(dextendedenumdef->id_);
  
    render(", members={");
  
    dextendedenumdef->enumlist_->accept(this);
  
    if(!enum_empty) {
 	    removeLastComma();
    }
  
    render("}\"/>");
    newIndLine();
    */
}

void GenerateDBusXML::visitDEnum(DEnum *denum) {
    /*
    enum_empty = false;
    visitId(denum->id_);
    render(", ");
    */
}

void GenerateDBusXML::visitDEnumValue(DEnumValue *denumvalue) {
    /*
    enum_empty = false;
    visitId(denumvalue->id_);
    render("=");
    visitInteger(denumvalue->integer_);
    render(", ");
    */
}


void GenerateDBusXML::visitDEnumList(DEnumList *denumlist) {
    /*

    denumlist->listenum_->accept(this);
  
    */
}

void GenerateDBusXML::visitDEnumIdent(DEnumIdent *denumident) {
    /*

    visitId(denumident->id_);
    */
}


void GenerateDBusXML::visitListEnum(ListEnum* listenum) {
    /*
    for (ListEnum::iterator i = listenum->begin() ; i != listenum->end() ; ++i) {
        (*i)->accept(this);
    }
    */
}


















////////////////////////////////////////////////////////////
// INTERFACES- visitor functions
////////////////////////////////////////////////////////////



void GenerateDBusXML::visitDInterface(DInterface* p) {

    render("<interface name=\"");

    render(packageName);

    render(".");
    visitIdent(p->id_);
    render("\">");
    increaseIndent();
    newIndLine();
 
    p->ibody_->accept(this);
 
    removeLine();
    decreaseIndent();
    newIndLine();
    render("</interface>");
    newIndLine();
}


void GenerateDBusXML::visitDIBody(DIBody* p) {
    if(p->listibodyitem_) {
        p->listibodyitem_->accept(this);
    }
}


void GenerateDBusXML::visitListIBodyItem(ListIBodyItem *listibodyitem) {
    for (ListIBodyItem::const_iterator i = listibodyitem->begin() ; i != listibodyitem->end() ; ++i) {
        (*i)->accept(this);
    }
}

void GenerateDBusXML::visitDVersion(DVersion* p) {
  // TODO what to do with version? <version> tag or ignore?
}




void GenerateDBusXML::visitDTypeCollection(DTypeCollection *dtypecollection) {
    //visitId(dtypecollection->id_);
    dtypecollection->ibody_->accept(this);
}



void GenerateDBusXML::visitListDef(ListDef *listdef) {
    for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i) {
        (*i)->accept(this);
    }
}










////////////////////////////////////////////////////////////
// TYPE DEFINITIONS - visitor functions
////////////////////////////////////////////////////////////

void GenerateDBusXML::visitDTypeDef(DTypeDef *dtypedef) {
/*
    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.Typedef\" value=\"{");
    dtypedef->typedefid_->accept(this);
    render(", ");

    dtypedef->type_->accept(this);
    render("}\"/>");
    newIndLine();
*/
}

void GenerateDBusXML::visitDTypeDefCustom(DTypeDefCustom *dtypedefcustom) {
/*
    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.Typedef\" value=\"{");
    dtypedefcustom->typedefid_->accept(this);
    render(", ");

    visitId(dtypedefcustom->id_);
    render("}\"/>");
    newIndLine();
*/
}

void GenerateDBusXML::visitDTypeDefIdent(DTypeDefIdent *dtypedefident) {
  /*
    visitId(dtypedefident->id_);
*/
}










////////////////////////////////////////////////////////////
// METHODS AND METHOD PARAMETERS - visitor functions
////////////////////////////////////////////////////////////

void GenerateDBusXML::visitDMethod(DMethod* p) {
    render("<method name=\"");
    visitIdent(p->id_);
    render("\">");
    newIndLine();
    render("</method>");
    newIndLine();
}


void GenerateDBusXML::visitDInMethod(DInMethod* p) {
    render("<method name=\"");
    visitIdent(p->id_);
    render("\">");
    increaseIndent();
    newIndLine();

    if (p->listinvari_) {
        p->listinvari_->accept(this);
    }

    removeLine();
    decreaseIndent();
    newIndLine();
    render("</method>");
    newIndLine();
}


void GenerateDBusXML::visitDOutMethod(DOutMethod* p) {
    render("<method name=\"");
    visitIdent(p->id_);
    render("\">");
    increaseIndent();
    newIndLine();

    if (p->listoutvari_) {
        p->listoutvari_->accept(this);
    }

    removeLine();
    decreaseIndent();
    newIndLine();
    render("</method>");
    newIndLine();
}

void GenerateDBusXML::visitDInOutMethod(DInOutMethod* p) {
    render("<method name=\"");
    visitIdent(p->id_);
    render("\">");
    increaseIndent();
    newIndLine();

    if (p->listinvari_) {
        p->listinvari_->accept(this);
    }

    if (p->listoutvari_) {
        p->listoutvari_->accept(this);
    }

    removeLine();
    decreaseIndent();
    newIndLine();
    render("</method>");
    newIndLine();
}


void GenerateDBusXML::visitDInVar(DInVar* p) {
    render("<arg direction=\"in\" name=\"");
    visitIdent(p->id_);
    render("\" type=\"");
    p->type_->accept(this);
    render("\">");
  
    //TODO documentation/annotations
    increaseIndent();
    newIndLine();
    renderEnumMembersIfNeeded();
    removeLine();
    decreaseIndent();
    newIndLine();
  
    render("</arg>");

    newIndLine();
}



void GenerateDBusXML::visitDOutVar(DOutVar* p) {
    render("<arg direction=\"out\" name=\"");
    visitIdent(p->id_);
    render("\" type=\"");
    p->type_->accept(this);
    render("\">");

    //TODO documentation/annotations
    increaseIndent();
    newIndLine();
    renderEnumMembersIfNeeded();
    removeLine();
    decreaseIndent();
    newIndLine();
  
    render("</arg>");
    newIndLine();
}


void GenerateDBusXML::visitDVar(DVar* p) {
    p->type_->accept(this);
    visitIdent(p->id_);
}


void GenerateDBusXML::visitListVari(ListVari *listvari) {
    for (ListVari::const_iterator i = listvari->begin() ; i != listvari->end() ; ++i) {
        (*i)->accept(this);
    }
}



void GenerateDBusXML::visitListInVari(ListInVari *listinvari) {
    for (ListInVari::const_iterator i = listinvari->begin() ; i != listinvari->end() ; ++i) {
        (*i)->accept(this);
    }
}


void GenerateDBusXML::visitListOutVari(ListOutVari *listoutvari) {
    for (ListOutVari::const_iterator i = listoutvari->begin() ; i != listoutvari->end() ; ++i) {
        (*i)->accept(this);
    }
}











////////////////////////////////////////////////////////////
// ATTRIBUTES / PROPERTIES - visitor functions
////////////////////////////////////////////////////////////

void GenerateDBusXML::visitDAttrib(DAttrib *dattrib) {

    render("<property access=\"readwrite\" name=\"");
    visitIdent(dattrib->id_);
    render("\" type=\"");
    dattrib->type_->accept(this);
    render("\">");
  
    increaseIndent();
    newIndLine();
    renderEnumMembersIfNeeded();
    removeLine();
    decreaseIndent();
    newIndLine();

    render("</property>");
    newIndLine();
}

void GenerateDBusXML::visitDAttribReadOnly(DAttribReadOnly *dattribreadonly) {

    render("<property access=\"read\" name=\"");
    visitIdent(dattribreadonly->id_);
    render("\" type=\"");
    dattribreadonly->type_->accept(this);
    render("\">");

    increaseIndent();
    newIndLine();
    renderEnumMembersIfNeeded();
    removeLine();
    decreaseIndent();
    newIndLine();

    render("</property>");
    newIndLine();
}

void GenerateDBusXML::visitDAttribNoSub(DAttribNoSub *dattribnosub) {

    render("<property access=\"readwrite\" name=\"");
    visitIdent(dattribnosub->id_);
    render("\" type=\"");
    dattribnosub->type_->accept(this);
    render("\">");
  
    increaseIndent();
    newIndLine();

    renderEnumMembersIfNeeded();
    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.NoSubscriptions\" value=\"True\"/>");
  
    removeLine();
    decreaseIndent();
    newIndLine();

    render("</property>");
    newIndLine();
}

void GenerateDBusXML::visitDAttribReadOnlyNoSub(DAttribReadOnlyNoSub *dattribreadonlynosub) {
    render("<property access=\"read\" name=\"");
    visitIdent(dattribreadonlynosub->id_);
    render("\" type=\"");
    dattribreadonlynosub->type_->accept(this);
    render("\">");
  
    increaseIndent();
    newIndLine();

    renderEnumMembersIfNeeded();
    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.NoSubscriptions\" value=\"True\"/>");
  
    removeLine();
    decreaseIndent();
    newIndLine();

    render("</property>");
    newIndLine();
}

void GenerateDBusXML::visitDAttribReadOnlyNoSub2(DAttribReadOnlyNoSub2 *dattribreadonlynosub2) {

  // TODO Franca does not allow readOnly to be after noSubscriptions. Produce error instead of code!
    render("<property access=\"read\" name=\"");
    visitIdent(dattribreadonlynosub2->id_);
    render("\" type=\"");
    dattribreadonlynosub2->type_->accept(this);
    render("\">");
  
    increaseIndent();
    newIndLine();

    renderEnumMembersIfNeeded();
    render("<annotation name=\"com.pelagicore.FrancaCCodeGen.NoSubscriptions\" value=\"True\"/>");
  
    removeLine();
    decreaseIndent();
    newIndLine();

    render("</property>");
    newIndLine();
}













////////////////////////////////////////////////////////////
// TYPES AND IDENTIFIERS - visitor functions
////////////////////////////////////////////////////////////


void GenerateDBusXML::visitDUIntEight(DUIntEight* p) {
    render("y");
}


void GenerateDBusXML::visitDIntEight(DIntEight* p) {

    std::cerr << "ERROR: Franca type 'Int8' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
    exit(1);
}


void GenerateDBusXML::visitDUIntSixteen(DUIntSixteen* p) {
    render("q");
}


void GenerateDBusXML::visitDIntSixteen(DIntSixteen* p) {
    render("n");
}


void GenerateDBusXML::visitDUIntThirtyTwo(DUIntThirtyTwo* p) {
    render("u");
}


void GenerateDBusXML::visitDIntThirtyTwo(DIntThirtyTwo* p) {
    render("i");
}


void GenerateDBusXML::visitDUIntSixtyFour(DUIntSixtyFour* p) {
    render("t");
}


void GenerateDBusXML::visitDIntSixtyFour(DIntSixtyFour* p) {
    render("x");
}


void GenerateDBusXML::visitDBoolean(DBoolean* p) {
    render("b");
}


void GenerateDBusXML::visitDFloat(DFloat* p) {
    std::cerr << "ERROR: Franca type 'Float' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
    exit(1);
}


void GenerateDBusXML::visitDDouble(DDouble* p) {
    render("d");
}


void GenerateDBusXML::visitDString(DString* p) {
    render("s");
}


void GenerateDBusXML::visitDByteBuffer(DByteBuffer* p) {
    std::cerr << "ERROR: Franca type 'ByteBuffer' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
    exit(1);
}

void GenerateDBusXML::visitInteger(Integer i) {
    char tmp[16];
    sprintf(tmp, "%d", i);
    bufAppend(tmp);
}

void GenerateDBusXML::visitDouble(Double d) {
    char tmp[16];
    sprintf(tmp, "%g", d);
    bufAppend(tmp);
}

void GenerateDBusXML::visitChar(Char c) {
    bufAppend('\'');
    bufAppend(c);
    bufAppend('\'');
}

void GenerateDBusXML::visitString(String s_) {
    const char *s = s_.c_str() ;
    bufAppend('\"');
    bufAppend(s);
    bufAppend('\"');
}

void GenerateDBusXML::visitIdent(String s_) {
    const char *s = s_.c_str() ;
    render(s);
}

void GenerateDBusXML::visitId(String s_) {
    const char *s = s_.c_str() ;
    render(s);
}

void GenerateDBusXML::visitDCustomType(DCustomType *dcustomtype) {

    //TODO
    // Custom type can (at the moment) either be a typedef, or an enumeration
    // could also be a struct, union, map, array - but not supported atm
  
    // Don't render custom type name, render it's dbus signature instead
  
    // Save the file name but don't print it (visitId will append it to buffer)
    std::string nameOfCustomType;
    int old_cur = cur_;
    visitId(dcustomtype->id_);  
    for (int i = old_cur; i< cur_; i++) {
  	    nameOfCustomType.push_back(buf_[i]);
    }
    cur_ = old_cur;
    render(getCustomTypeSig(nameOfCustomType));
    setNameOfEnum(nameOfCustomType);
}
