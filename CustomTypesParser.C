/**** This code is based on the BNFC-Generated Visitor Design Pattern Skeleton. ***/

// The purpose of this code is to create a list of all custom types declared in the Franca AST, as well as in any files
// declared as imports in the original file. This list can then be consulted to find the currect D-Bus signature for
// any custom type found in the AST.

// At the moment, the following custom types are supported:
//
// - Typedefs
// - Enums (including extending other enums as well as assigning values to enum members)
//

#include "CustomTypesParser.H"
#include <sstream> 
#include <iostream>
#include <stdio.h>


CustomTypesParser::CustomTypesParser(void)
{
}


CustomTypesParser::~CustomTypesParser(void)
{
}



std::vector<CustomType> CustomTypesParser::findCustomTypes(Visitable *v, std::string s) {
    pathToImportFile = s;
    v->accept(this);    
    
    return parseUnfinishedList(unfinished);
}


std::vector<CustomType> CustomTypesParser::findUnfinishedTypes(Visitable *v, std::string s) {
    // This has the same functionality as findCustomTypes, but does not try to parse the found types.
    // Used to import type collections in other Franca files.
    pathToImportFile = s;
    v->accept(this); 
     
    return unfinished;

}

std::vector<CustomType> CustomTypesParser::parseUnfinishedList(std::vector<CustomType> unfinished) {
    std::vector<CustomType> finished;
    
    int oldsize = 0;
    
    // Iterate through the list of unfinished types as long as there are any left and the last iteration actually managed to remove one
    while(unfinished.size() > 0 && oldsize != unfinished.size()) {
        oldsize = unfinished.size();
        //std::cout << "DEBUG: In beginning of while loop. Size of unfinished: " << unfinished.size() << ". Size of finished: " << finished.size() << std::endl;

        std::vector<CustomType>::iterator it = unfinished.begin();
        while (it != unfinished.end()) {
            // Iterate over each unfinished type, checking if it contains any unfinished types in its definition.
            // If not, add it to finished types and remove it from unfinished types.
            
            bool isFinished = false;
            
            if (it->getType() == FRANCA_ENUM) {
                // For enums, check if they extend any unknown enum. If they do not extend any enum, or extends an already finished enum, they are safe to add to finished list.
                if (it->getEnumExtends().compare("") == 0) {
                    isFinished = true;
                } else {
                    for (std::vector<CustomType>::iterator f_it = finished.begin(); f_it != finished.end(); ++f_it) {
                        if (f_it->getName().compare(it->getEnumExtends()) == 0) {
                            isFinished = true;
                        }
                    }
                }
            } else if (it->getType() == FRANCA_TYPEDEF) {
                // For typedefs, check if data is a custom type in finished, or if D-bus signature already has been set.
                if (it->getDBusSign().compare("") != 0) {
                    isFinished = true;
                } else {
                    for (std::vector<CustomType>::iterator f_it = finished.begin(); f_it != finished.end(); ++f_it) {
                        if (f_it->getName().compare(it->getData()) == 0) {
                            isFinished = true;
                        }
                    }
                }
            }
            // other types go here TODO
            
            
            
            if (isFinished) {
            
                if (it->getType() == FRANCA_ENUM) {
                // if enum, set value/dbussignature to u.
                    it->setDBusSign("u");
                // Also, add any enum members of the extended enum.    
                    for (std::vector<CustomType>::iterator f_it = finished.begin(); f_it != finished.end(); ++f_it) {
                        if (f_it->getName().compare(it->getEnumExtends()) == 0) {
                            for (int i = 0; i < f_it->getNbrOfEnumMembers(); i++) {
                                it->addEnum(f_it->getEnumMember(i), f_it->getEnumValue(i));   
                            }
                        }
                    }

                } else if (it->getType() == FRANCA_TYPEDEF) {
                // if typedef, check if d-bus signature already has been set. If not, set value/dbussignature to same signature as the typedef'd type
                    if (it->getDBusSign().compare("") == 0) {
                        for (std::vector<CustomType>::iterator f_it = finished.begin(); f_it != finished.end(); ++f_it) {
                            if (f_it->getName().compare(it->getData()) == 0) {
                                //we need to check if it's an enum we typedef. If so, we need to copy its members as well.
                                // NOTE: Since the target already is in finished, we know that all enum extentions are already handled.
                                if (f_it->getType() == FRANCA_ENUM) {
                                    it->setType(FRANCA_ENUM);
                                    it->setEnumExtends(f_it->getEnumExtends());
                                    for (int i = 0; i < f_it->getNbrOfEnumMembers(); i++) {
                                        it->addEnum(f_it->getEnumMember(i), f_it->getEnumValue(i));   
                                        it->setDBusSign(f_it->getDBusSign());
                                    } 
                                } else {
                                    it->setDBusSign(f_it->getDBusSign());
                                }
                            }
                        }
                    }
                }
            
                // Add element to finished, and remove it from unfinished, thus incrementing iterator.
                finished.push_back(*it);
                it = unfinished.erase(it);
             
          
    
        
            } else {
                // Increment iterator since no element was removed from unfinished
                ++it;
            }
        }
    }
    
    // If there are any unfinished types left, print an error message and exit.
    if (unfinished.size() > 0) {
        std::cout << "ERROR: Custom Franca types cannot be resolved: " << std::endl;
        for (std::vector<CustomType>::iterator it = unfinished.begin(); it != unfinished.end(); ++it) {
            std::cout << "NAME: " << it->getName() << std::endl << "TYPE: " << it->getTypeString() << std::endl << "D-BUS SIGNATURE: " << it->getDBusSign() << std::endl;
            if (it->getType() == FRANCA_ENUM) {
                std::cout << "EXTENDS: " << it->getEnumExtends() << std::endl;
                for (int i = 0; i != it->getNbrOfEnumMembers(); i++) {
                    std::cout << "ENUM MEMBER: " << it->getEnumMember(i) << " = " << it->getEnumValue(i) << std::endl;
                }        
            } else {
                std::cout << "VALUE: " << it->getData() << std::endl;
            }
            std::cout << std::endl;
        } 
        std::cout << "Aborting code generation." << std::endl;
        exit(1);
     }
       
   
    // Print finished for DEBUG purposes
    std::cout << "DEBUG: FINISHED TYPES:" << std::endl;
    for (std::vector<CustomType>::iterator it = finished.begin(); it != finished.end(); ++it) {
        std::cout << "NAME: " << it->getName() << std::endl << "TYPE: " << it->getTypeString() << std::endl << "D-BUS SIGNATURE: " << it->getDBusSign() << std::endl;
        if (it->getType() == FRANCA_ENUM) {
           std::cout << "EXTENDS: " << it->getEnumExtends() << std::endl;
           for (int i = 0; i != it->getNbrOfEnumMembers(); i++) {
              std::cout << "ENUM MEMBER: " << it->getEnumMember(i) << " = " << it->getEnumValue(i) << std::endl;
           }        
        } else {
            std::cout << "VALUE: " << it->getData() << std::endl;
        }
        std::cout << std::endl;
    } 


    // Postprocess enums, setting a value to each member not already having one.
    // TODO this should really take into account not only the values of the enum members in the currently processed enum,
    // but also the values of any members in enums extending that one.
    // Right now, the same enum member might be assigned different values in "subclasses" of this enum.
    for (std::vector<CustomType>::iterator it = finished.begin(); it != finished.end(); ++it) {
        if (it->getType() == FRANCA_ENUM) {
            int currentFreeValue = 0;
            std::string currentFreeValueString = "0";
                      
            for (int i = 0; i != it->getNbrOfEnumMembers(); i++) {
                while (it->getEnumValue(i) == "") {
                    // Enum member has no value yet.
                    // Assign string representation of lowest possible integer. Take care to avoid clashes.
                    bool valueIsFree = true;
                    for (int j = 0; j != it->getNbrOfEnumMembers(); j++) {
                        if (it->getEnumValue(j).compare(currentFreeValueString) == 0) {
                            valueIsFree = false;
                        }
                    }
                    if (valueIsFree) {
                        std::ostringstream convert;
                        convert << currentFreeValue;
                        it->setEnumValue(i, convert.str());
                    } else {
                        currentFreeValue++;
                        std::ostringstream convert;
                        convert << currentFreeValue;
                        currentFreeValueString = convert.str();
                    }                   
                }
            }
        }    
    }   
    
    return finished;
}

void CustomTypesParser::visitProgram(Program* t) {} //abstract class
void CustomTypesParser::visitDef(Def* t) {} //abstract class
void CustomTypesParser::visitPackageName(PackageName* t) {} //abstract class
void CustomTypesParser::visitFileName(FileName* t) {} //abstract class
void CustomTypesParser::visitFileEnding(FileEnding* t) {} //abstract class
void CustomTypesParser::visitNamespace(Namespace* t) {} //abstract class
void CustomTypesParser::visitNamespaceID(NamespaceID* t) {} //abstract class
void CustomTypesParser::visitIBody(IBody* t) {} //abstract class
void CustomTypesParser::visitIBodyItem(IBodyItem* t) {} //abstract class
void CustomTypesParser::visitInVari(InVari* t) {} //abstract class
void CustomTypesParser::visitOutVari(OutVari* t) {} //abstract class
void CustomTypesParser::visitVari(Vari* t) {} //abstract class
void CustomTypesParser::visitEnumId(EnumId* t) {} //abstract class
void CustomTypesParser::visitEnumList(EnumList* t) {} //abstract class
void CustomTypesParser::visitEnum(Enum* t) {} //abstract class
void CustomTypesParser::visitTypeDefId(TypeDefId* t) {} //abstract class
void CustomTypesParser::visitType(Type* t) {} //abstract class

void CustomTypesParser::visitProg(Prog *prog)
{
  /* Code For Prog Goes Here */

  prog->listdef_->accept(this);

}

void CustomTypesParser::visitDPackage(DPackage *dpackage)
{
  /* Code For DPackage Goes Here */

  dpackage->packagename_->accept(this);

}

void CustomTypesParser::visitDInterface(DInterface *dinterface)
{
  /* Code For DInterface Goes Here */

  visitId(dinterface->id_);
  dinterface->ibody_->accept(this);

}

void CustomTypesParser::visitDTypeCollection(DTypeCollection *dtypecollection)
{
  /* Code For DTypeCollection Goes Here */

  visitId(dtypecollection->id_);
  dtypecollection->ibody_->accept(this);

}

void CustomTypesParser::visitDImport(DImport *dimport)
{
 
  
  // Note that my solution for saving namespace and file name is rather ugly.
  // Might need to implement a nicer solution (TODO) or at least make some error checking.

  importedNameSpace = "";
  importedFileName = "";
  
  
  // Save namespace. 
  tempString = "";
  dimport->namespace_->accept(this);
  importedNameSpace = tempString;
  
  // Save file name.
  tempString = "";
  dimport->filename_->accept(this);
  importedFileName = tempString;
  
  // std::cout << "DEBUG: importedNameSpace: " << importedNameSpace << std::endl; 
  // std::cout << "DEBUG: importedFileName: " << importedFileName << std::endl; 
  
  // Remove last character of namespace if it's a dot ('.')
  if (importedNameSpace.at(importedNameSpace.length() -1) == '.' ) {
    importedNameSpace = importedNameSpace.substr(0, importedNameSpace.length()-1);
  }
  
  // std::cout << "DEBUG: importedNameSpace: " << importedNameSpace << std::endl; 
  // Now namespace and file name are saved, and we can open the file.
  
 
  FILE *importedFile;
  
  if (pathToImportFile == "") {
    importedFile = fopen(importedFileName.c_str(), "r");
  } else {
    importedFile = fopen((pathToImportFile + "/" + importedFileName).c_str(), "r");
  }
  
  if (!importedFile)
  {
    std::cout << "Error importing fidl file from import statement: " << importedFileName << std::endl;
    exit(1);
  }
  
  // do stuff with file...
  // ... but what?
  // Import and render entire type collection for now.
  // Should only import the specified namespace! TODO
  
  
  Program *imported_parse_tree = pProgram(importedFile);
  if (imported_parse_tree)
  {
    CustomTypesParser *parser = new CustomTypesParser();
    std::vector<CustomType> newUnfinishedTypes = parser->findUnfinishedTypes(imported_parse_tree, pathToImportFile);
    
    unfinished.insert(unfinished.end(), newUnfinishedTypes.begin(), newUnfinishedTypes.end());
    

  } else {
    std::cout << "Error parsing imported fidl file: " << importedFileName << std::endl;
  }
  
  fclose(importedFile);
  
}

void CustomTypesParser::visitDPackageName(DPackageName *dpackagename)
{
  /* Code For DPackageName Goes Here */

  dpackagename->listnamespaceid_->accept(this);

}

void CustomTypesParser::visitDFileName(DFileName *dfilename)
{

  // Save the file name

  visitId(dfilename->id_);
  tempString.append(".");
  dfilename->fileending_->accept(this);
}
  

void CustomTypesParser::visitDFileNameNoEnd(DFileNameNoEnd *dfilenamenoend)
{
  visitId(dfilenamenoend->id_);
  
}

void CustomTypesParser::visitDFileEnding(DFileEnding *dfileending)
{
  /* Code For DFileEnding Goes Here */

  visitId(dfileending->id_);

}

void CustomTypesParser::visitDNamespace(DNamespace *dnamespace)
{
  /* Code For DNamespace Goes Here */

  dnamespace->listnamespaceid_->accept(this);

}

void CustomTypesParser::visitDNamespaceID(DNamespaceID *dnamespaceid)
{
  /* Code For DNamespaceID Goes Here */

  visitId(dnamespaceid->id_);

}

void CustomTypesParser::visitDIBody(DIBody *dibody)
{
  /* Code For DIBody Goes Here */

  dibody->listibodyitem_->accept(this);

}

void CustomTypesParser::visitDMethod(DMethod *dmethod)
{
  /* Code For DMethod Goes Here */

  visitId(dmethod->id_);

}

void CustomTypesParser::visitDInMethod(DInMethod *dinmethod)
{
  /* Code For DInMethod Goes Here */

  visitId(dinmethod->id_);
  dinmethod->listinvari_->accept(this);

}

void CustomTypesParser::visitDOutMethod(DOutMethod *doutmethod)
{
  /* Code For DOutMethod Goes Here */

  visitId(doutmethod->id_);
  doutmethod->listoutvari_->accept(this);

}

void CustomTypesParser::visitDInOutMethod(DInOutMethod *dinoutmethod)
{
  /* Code For DInOutMethod Goes Here */

  visitId(dinoutmethod->id_);
  dinoutmethod->listinvari_->accept(this);
  dinoutmethod->listoutvari_->accept(this);

}

void CustomTypesParser::visitDVersion(DVersion *dversion)
{
  /* Code For DVersion Goes Here */

  visitInteger(dversion->integer_1);
  visitInteger(dversion->integer_2);

}

void CustomTypesParser::visitDAttrib(DAttrib *dattrib)
{
  /* Code For DAttrib Goes Here */

  dattrib->type_->accept(this);
  visitId(dattrib->id_);

}

void CustomTypesParser::visitDAttribReadOnly(DAttribReadOnly *dattribreadonly)
{
  /* Code For DAttribReadOnly Goes Here */

  dattribreadonly->type_->accept(this);
  visitId(dattribreadonly->id_);

}

void CustomTypesParser::visitDAttribNoSub(DAttribNoSub *dattribnosub)
{
  /* Code For DAttribNoSub Goes Here */

  dattribnosub->type_->accept(this);
  visitId(dattribnosub->id_);

}

void CustomTypesParser::visitDAttribReadOnlyNoSub(DAttribReadOnlyNoSub *dattribreadonlynosub)
{
  /* Code For DAttribReadOnlyNoSub Goes Here */

  dattribreadonlynosub->type_->accept(this);
  visitId(dattribreadonlynosub->id_);

}

void CustomTypesParser::visitDAttribReadOnlyNoSub2(DAttribReadOnlyNoSub2 *dattribreadonlynosub2)
{
  /* Code For DAttribReadOnlyNoSub2 Goes Here */

  dattribreadonlynosub2->type_->accept(this);
  visitId(dattribreadonlynosub2->id_);

}

void CustomTypesParser::visitDEnumDef(DEnumDef *denumdef)
{

  CustomType *ct = new CustomType();
  ct->setType(FRANCA_ENUM);

  tempString = "";
  visitId(denumdef->id_);
  ct->setName(tempString);
  
  currentCT = ct;
  denumdef->enumlist_->accept(this);
  
  unfinished.push_back(*ct);
}

void CustomTypesParser::visitDExtendedEnumDef(DExtendedEnumDef *dextendedenumdef)
{ 

  CustomType *ct = new CustomType();
  ct->setType(FRANCA_ENUM);

  tempString = "";
  dextendedenumdef->enumid_->accept(this);
  ct->setName(tempString);
  
  tempString = "";
  visitId(dextendedenumdef->id_);
  ct->setEnumExtends(tempString);
  
  currentCT = ct;
  dextendedenumdef->enumlist_->accept(this);
  
  unfinished.push_back(*ct);
}

void CustomTypesParser::visitDTypeDef(DTypeDef *dtypedef)
{

  CustomType *ct = new CustomType();
  ct->setType(FRANCA_TYPEDEF);
  
  tempString = "";  
  dtypedef->typedefid_->accept(this);
  ct->setName(tempString);
  
  tempString = "";  
  dtypedef->type_->accept(this);
  ct->setDBusSign(tempString);
  
  unfinished.push_back(*ct);
}

void CustomTypesParser::visitDTypeDefCustom(DTypeDefCustom *dtypedefcustom)
{

  CustomType *ct = new CustomType();
  ct->setType(FRANCA_TYPEDEF);
  
  tempString = "";  
  dtypedefcustom->typedefid_->accept(this);
  ct->setName(tempString);
  
  tempString = "";  
  visitId(dtypedefcustom->id_);
  ct->setData(tempString);
  
  unfinished.push_back(*ct);
}

void CustomTypesParser::visitDInVar(DInVar *dinvar)
{
  /* Code For DInVar Goes Here */

  dinvar->type_->accept(this);
  visitId(dinvar->id_);

}

void CustomTypesParser::visitDOutVar(DOutVar *doutvar)
{
  /* Code For DOutVar Goes Here */

  doutvar->type_->accept(this);
  visitId(doutvar->id_);

}

void CustomTypesParser::visitDVar(DVar *dvar)
{
  /* Code For DVar Goes Here */

  dvar->type_->accept(this);
  visitId(dvar->id_);

}

void CustomTypesParser::visitDEnumIdent(DEnumIdent *denumident)
{
  /* Code For DEnumIdent Goes Here */

  visitId(denumident->id_);

}

void CustomTypesParser::visitDEnumList(DEnumList *denumlist)
{
  /* Code For DEnumList Goes Here */
    
  denumlist->listenum_->accept(this);

}

void CustomTypesParser::visitDEnum(DEnum *denum)
{

  tempString = "";
  visitId(denum->id_);
  currentCT->addEnum(tempString, "");
}

void CustomTypesParser::visitDEnumValue(DEnumValue *denumvalue)
{
  tempString = "";
  visitId(denumvalue->id_);
  std::string tempEnumMemberName = tempString;

  tempString = "";
  visitInteger(denumvalue->integer_);
  
  currentCT->addEnum(tempEnumMemberName, tempString);
}

void CustomTypesParser::visitDTypeDefIdent(DTypeDefIdent *dtypedefident)
{
  visitId(dtypedefident->id_);
}

void CustomTypesParser::visitDUIntEight(DUIntEight *duinteight)
{
  tempString.append("y");
}

void CustomTypesParser::visitDIntEight(DIntEight *dinteight)
{
  std::cout << "ERROR: Franca type 'Int8' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
  exit(1);
}

void CustomTypesParser::visitDUIntSixteen(DUIntSixteen *duintsixteen)
{
  tempString.append("q");
}

void CustomTypesParser::visitDIntSixteen(DIntSixteen *dintsixteen)
{
  tempString.append("n");
}

void CustomTypesParser::visitDUIntThirtyTwo(DUIntThirtyTwo *duintthirtytwo)
{
  tempString.append("u");
}

void CustomTypesParser::visitDIntThirtyTwo(DIntThirtyTwo *dintthirtytwo)
{
  tempString.append("i");
}

void CustomTypesParser::visitDUIntSixtyFour(DUIntSixtyFour *duintsixtyfour)
{
  tempString.append("t");
}

void CustomTypesParser::visitDIntSixtyFour(DIntSixtyFour *dintsixtyfour)
{
  tempString.append("x");
}

void CustomTypesParser::visitDBoolean(DBoolean *dboolean)
{
  tempString.append("b");
}

void CustomTypesParser::visitDFloat(DFloat *dfloat)
{
  std::cout << "ERROR: Franca type 'Float' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
  exit(1);
}

void CustomTypesParser::visitDDouble(DDouble *ddouble)
{
  tempString.append("d");
}

void CustomTypesParser::visitDString(DString *dstring)
{
  tempString.append("s");
}

void CustomTypesParser::visitDByteBuffer(DByteBuffer *dbytebuffer)
{
  std::cout << "ERROR: Franca type 'ByteBuffer' is not defined in D-Bus." << std::endl << "Aborting code generation." << std::endl;
  exit(1);
}

void CustomTypesParser::visitDCustomType(DCustomType *dcustomtype)
{
  visitId(dcustomtype->id_);
}


void CustomTypesParser::visitListDef(ListDef* listdef)
{
  for (ListDef::iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CustomTypesParser::visitListNamespaceID(ListNamespaceID* listnamespaceid)
{
  for (ListNamespaceID::iterator i = listnamespaceid->begin() ; i != listnamespaceid->end() ; ++i)
  {
    (*i)->accept(this);
    tempString.append(".");
  }
}

void CustomTypesParser::visitListIBodyItem(ListIBodyItem* listibodyitem)
{
  for (ListIBodyItem::iterator i = listibodyitem->begin() ; i != listibodyitem->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CustomTypesParser::visitListVari(ListVari* listvari)
{
  for (ListVari::iterator i = listvari->begin() ; i != listvari->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CustomTypesParser::visitListInVari(ListInVari* listinvari)
{
  for (ListInVari::iterator i = listinvari->begin() ; i != listinvari->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CustomTypesParser::visitListOutVari(ListOutVari* listoutvari)
{
  for (ListOutVari::iterator i = listoutvari->begin() ; i != listoutvari->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CustomTypesParser::visitListEnum(ListEnum* listenum)
{
  for (ListEnum::iterator i = listenum->begin() ; i != listenum->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void CustomTypesParser::visitId(Id x)
{
  tempString.append(x);
}

void CustomTypesParser::visitInteger(Integer x)
{
  std::ostringstream convert;
  convert << x;
  tempString.append(convert.str());
}

void CustomTypesParser::visitChar(Char x)
{
  std::ostringstream convert;
  convert << x;
  tempString.append(convert.str());
}

void CustomTypesParser::visitDouble(Double x)
{
  std::ostringstream convert;
  convert << x;
  tempString.append(convert.str());
}

void CustomTypesParser::visitString(String x)
{
  tempString.append(x);
}

void CustomTypesParser::visitIdent(Ident x)
{
  tempString.append(x);
}
