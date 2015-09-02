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


#include "CustomType.h"
#include <stdlib.h>
#include <iostream>

std::string CustomType::getName() {
    return this->name;
}

FRANCA_DATATYPE CustomType::getType() {
    return this->type;
}

std::string CustomType::getTypeString() {
    if (this->type == FRANCA_ENUM) {
        return "ENUMERATION";
    } else if (this->type == FRANCA_TYPEDEF) {
        return "TYPEDEF";
    }
    else
    return "";
}

std::string CustomType::getEnumExtends() {
    return this->emum_extends;
}

std::string CustomType::getData() {
    return this->data;
}

std::string CustomType::getDBusSign() {
    return this->dbussign;
}

std::string CustomType::getEnumMember(int i) {
    if (i <= enum_members.size()) {
        return this->enum_members.at(i);
    } else {
        std::cerr << "RUNTIME ERROR: Code generator couldn't fetch enum member #" << i << " from enum type "<< this->name << std::endl << "Aborting code generation." << std::endl;
        exit(1);      
    }
}

std::string CustomType::getEnumValue(int i) {
    if (i <= enum_values.size()) {
        return this->enum_values.at(i);
    } else {
        std::cerr << "RUNTIME ERROR: Code generator couldn't fetch enum value #" << i << " from enum type "<< this->name << std::endl << "Aborting code generation." << std::endl;
        exit(1);
    }
}

int CustomType::getNbrOfEnumMembers() {
    return this->enum_members.size();
}
    
void CustomType::setName(std::string name) {
    this->name = name;
}

void CustomType::setType(FRANCA_DATATYPE type) {
    this->type = type;
}

void CustomType::setData(std::string data) {
    this->data = data;
}

void CustomType::setEnumExtends(std::string enum_extends) {
    this->emum_extends = enum_extends;
}

void CustomType::addEnum(std::string name, std::string value) {
    // TODO make threadsafe
    this->enum_members.push_back(name);
    this->enum_values.push_back(value);
}

void CustomType::setEnumValue(int i, std::string value) {
    if (i <= this->enum_members.size()) {
        this->enum_values.at(i) = value;   
    }
}

void CustomType::setDBusSign(std::string sign) {
    this->dbussign = sign;
}

CustomType::CustomType(std::string name, FRANCA_DATATYPE type, std::string data) {
    this->name = name;
    this->type = type;
    this->data = data;
}

CustomType::CustomType(void) {
    this->name = "";
    this->type = NO_TYPE;
    this->data = "";
    this->emum_extends = "";
}

CustomType::~CustomType(void) {
}
