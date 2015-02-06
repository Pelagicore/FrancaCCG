/* XML Generator from Franca IDL abstract syntax tree
 * Based on BNFC-generated pretty printer
 ***/

#include <string>
#include "XMLGenerator.H"


void GenerateDBusXML::newIndLine()
{
  bufAppend('\n');
  indent();
}

void GenerateDBusXML::increaseIndent()
{
  _n_ = _n_ + 3;
}

void GenerateDBusXML::decreaseIndent()
{
  _n_ = _n_ - 3;
  if (_n_ < 0) {
    _n_ = 0;
  }
}


void GenerateDBusXML::render(Char c)
{
  bufAppend(c);
}

void GenerateDBusXML::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
  }
}


void GenerateDBusXML::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}


//void GenerateDBusXML::backup()
//{
//  if (buf_[cur_ - 1] == ' ')
//  {
//    buf_[cur_ - 1] = 0;
//    cur_--;
//  }
//}



void GenerateDBusXML::removeLine()
{
  while ((buf_[cur_ - 1] == '\n') || (buf_[cur_ - 1] == ' '))
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}

GenerateDBusXML::GenerateDBusXML(void)
{
  _n_ = 0;
  buf_ = 0;
  bufReset();
}


GenerateDBusXML::~GenerateDBusXML(void)
{
}


char* GenerateDBusXML::generate(Visitable *v)
{
  _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitProgram(Program*p) {} //abstract class


//TODO fix this method
void GenerateDBusXML::visitProg(Prog* p)
{
  render("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"\n");
  render(" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
  render("<node name=\"TODO NODE NAME HERE\">");
  increaseIndent();
  newIndLine();
  if(p->listdef_) {p->listdef_->accept(this);}

  removeLine();
  decreaseIndent();
  newIndLine();
  render("</node>");

}

//TODO fix this method. Needed?
void GenerateDBusXML::visitDef(Def*p) {} //abstract class


//TODO fix this method
void GenerateDBusXML::visitDInterface(DInterface* p)
{

  render("<interface name=\"TODO_PATH.");
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


void GenerateDBusXML::visitListDef(ListDef *listdef)
{
  for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitIBody(IBody*p) {} //abstract class

//TODO fix this method
void GenerateDBusXML::visitDIBody(DIBody* p)
{
  if(p->listibodyitem_) {p->listibodyitem_->accept(this);}

}

//TODO fix this method
void GenerateDBusXML::visitListIBodyItem(ListIBodyItem *listibodyitem)
{
  for (ListIBodyItem::const_iterator i = listibodyitem->begin() ; i != listibodyitem->end() ; ++i)
  {
    (*i)->accept(this);

  }
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitIBodyItem(IBodyItem*p) {} //abstract class


void GenerateDBusXML::visitDInMethod(DInMethod* p)
{
  render("<method name=\"");
  visitIdent(p->id_);
  render("\">");
  increaseIndent();
  newIndLine();

  if(p->listdinvari_) {p->listdinvari_->accept(this);}

  removeLine();
  decreaseIndent();
  newIndLine();
  render("</method>");
  newIndLine();
}


void GenerateDBusXML::visitDOutMethod(DOutMethod* p)
{
  render("<method name=\"");
  visitIdent(p->id_);
  render("\">");
  increaseIndent();
  newIndLine();

  if(p->listdoutvari_) {p->listdoutvari_->accept(this);}

  removeLine();
  decreaseIndent();
  newIndLine();
  render("</method>");
  newIndLine();
}



void GenerateDBusXML::visitDInOutMethod(DInOutMethod* p)
{
  render("<method name=\"");
  visitIdent(p->id_);
  render("\">");
  increaseIndent();
  newIndLine();

  if(p->listdinvari_) {p->listdinvari_->accept(this);}

  if(p->listdoutvari_) {p->listdoutvari_->accept(this);}

  removeLine();
  decreaseIndent();
  newIndLine();
  render("</method>");
  newIndLine();
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitDInVari(DInVari*p) {} //abstract class

//TODO fix this method
void GenerateDBusXML::visitDInVar(DInVar* p)
{
  render("<arg direction=\"in\" name=\"");
  visitIdent(p->id_);
  render("\" type=\"");
  p->type_->accept(this);
  render("\">");
  
  //TODO documentation/annotations
  newIndLine();

  render("</arg>");

  newIndLine();
}


//TODO fix this method. Needed?
void GenerateDBusXML::visitDOutVari(DOutVari*p) {} //abstract class

//TODO fix this method
void GenerateDBusXML::visitDOutVar(DOutVar* p)
{
  render("<arg direction=\"out\" name=\"");
  visitIdent(p->id_);
  render("\" type=\"");
  p->type_->accept(this);
  render("\">");

  //TODO documentation/annotations
  newIndLine();

  render("</arg>");
  newIndLine();
}


//TODO fix this method. Needed?
void GenerateDBusXML::visitDVari(DVari*p) {} //abstract class


void GenerateDBusXML::visitDVar(DVar* p)
{
  p->type_->accept(this);
  visitIdent(p->id_);
}



void GenerateDBusXML::visitListDVari(ListDVari *listdvari)
{
  for (ListDVari::const_iterator i = listdvari->begin() ; i != listdvari->end() ; ++i)
  {
    (*i)->accept(this);
  }
}



void GenerateDBusXML::visitListDInVari(ListDInVari *listdinvari)
{
  for (ListDInVari::const_iterator i = listdinvari->begin() ; i != listdinvari->end() ; ++i)
  {
    (*i)->accept(this);

  }
}


void GenerateDBusXML::visitListDOutVari(ListDOutVari *listdoutvari)
{
  for (ListDOutVari::const_iterator i = listdoutvari->begin() ; i != listdoutvari->end() ; ++i)
  {
    (*i)->accept(this);

  }
}


//TODO fix this method. Needed?
void GenerateDBusXML::visitType(Type*p) {} //abstract class



void GenerateDBusXML::visitDUIntEight(DUIntEight* p)
{
  render("y");
}


void GenerateDBusXML::visitDIntEight(DIntEight* p)
{
  //TODO Not in D-Bus?
  render("Int8 (ERROR: Not in D-Bus?)");

}


void GenerateDBusXML::visitDUIntSixteen(DUIntSixteen* p)
{
  render("q");
}


void GenerateDBusXML::visitDIntSixteen(DIntSixteen* p)
{
  render("n");
}


void GenerateDBusXML::visitDUIntThirtyTwo(DUIntThirtyTwo* p)
{
  render("u");
}


void GenerateDBusXML::visitDIntThirtyTwo(DIntThirtyTwo* p)
{
  render("i");
}


void GenerateDBusXML::visitDUIntSixtyFour(DUIntSixtyFour* p)
{
  render("t");
}


void GenerateDBusXML::visitDIntSixtyFour(DIntSixtyFour* p)
{
  render("x");
}


void GenerateDBusXML::visitDBoolean(DBoolean* p)
{
  render("b");
}

//TODO fix this method
void GenerateDBusXML::visitDFloat(DFloat* p)
{
  render("Float (ERROR: Not in D-Bus?)");
}


void GenerateDBusXML::visitDDouble(DDouble* p)
{
  render("d");
}


void GenerateDBusXML::visitDString(DString* p)
{
  render("s");
}

//TODO fix this method
void GenerateDBusXML::visitDByteBuffer(DByteBuffer* p)
{
  render("ByteBuffer (ERROR: Not in D-Bus?)");
}



//TODO fix this method. Needed?
void GenerateDBusXML::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitString(String s_)
{
  const char *s = s_.c_str() ;
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

//TODO fix this method. Needed?
void GenerateDBusXML::visitIdent(String s_)
{
  const char *s = s_.c_str() ;
  render(s);
}



void GenerateDBusXML::visitId(String s_)
{
  const char *s = s_.c_str() ;
  render(s);
}






