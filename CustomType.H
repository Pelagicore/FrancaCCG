#ifndef CUSTOMTYPE_HEADER
#define CUSTOMTYPE_HEADER

#include <vector>
#include <stdlib.h>
#include <string>

enum FRANCA_DATATYPE {NO_TYPE, FRANCA_ENUM, FRANCA_TYPEDEF} ;

class CustomType {

protected:
    std::string name; // Name of custom type
    FRANCA_DATATYPE type; // Type. Mainly used to separate enums from others.
    std::string data; // the franca signature of the type
    std::string dbussign;
    std::string emum_extends; // Only for enums. Name of enumeration to extend.
    std::vector<std::string> enum_members; // Only for enums. List of enum members.
    std::vector<std::string> enum_values; // Only for enums. List of enum values.

public:

    std::string getName();
    FRANCA_DATATYPE getType();
    std::string getTypeString();
    std::string getEnumExtends();
    std::string getData();
    std::string getDBusSign();
    std::string getEnumMember(int i);
    std::string getEnumValue(int i);
    int getNbrOfEnumMembers();
    
    void setName(std::string name);
    void setType(FRANCA_DATATYPE type);
    void setData(std::string data);
    void setEnumExtends(std::string enum_extends);
    void addEnum(std::string name, std::string value);
    void setEnumValue(int i, std::string value);
    void setDBusSign(std::string sign);

    CustomType(void);
    ~CustomType(void);    
    CustomType(std::string name, FRANCA_DATATYPE type, std::string data);

};

#endif
