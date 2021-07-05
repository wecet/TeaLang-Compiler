#include <iostream>

#include "interpreter.h"

using namespace visitor;

/*
    Checking if variable or function 
    is already defined
                                     */

bool IScope::already_referenced(std::string id){
    return vartable.find(id) != vartable.end();
}

bool IScope::already_referenced(std::string id, std::vector<parser::VAR_TYPE> signature){
    auto function = functable.equal_range(id);

    if(std::distance(function.first, function.second) == 0){
        std::cout << "[ERR] Key not found in Multimap" << std::endl;
        return false;
    }

    for(auto x = function.first; x != function.second; x++){
        if(std::get<0>(x->second) == signature){
            return true;
        }
    }
    
    std::cout << "[ERR] Function with specified signature not found " << std::endl;
    return false;

}

/*
    Declaring Variables
                        */

void IScope::declare(std::string id, int argc){
    variable var;
    var.i = argc;
    vartable[id] = std::make_pair(parser::INT, var);
}

void IScope::declare(std::string id, float argc){
    variable var;
    var.f = argc;
    vartable[id] = std::make_pair(parser::FLOAT, var);
}

void IScope::declare(std::string id, bool argc){
    variable var;
    var.b = argc;
    vartable[id] = std::make_pair(parser::BOOL, var);
}

void IScope::declare(std::string id, std::string argc){
    variable var;
    var.s = argc;
    vartable[id] = std::make_pair(parser::STRING, var);
}

void IScope::declare(std::string id, std::vector<parser::VAR_TYPE> signature, std::vector<std::string> names, parser::ASTBlockNode *funcblock){
    functable.insert(std::make_pair(id, std::make_tuple(signature, names, funcblock)));
}

/*
    TYPE OF
            */

parser::VAR_TYPE IScope::vartype_of(std::string id){
    return vartable[id].first;
}

/*
    Content in Type
                    */

variable IScope::content(std::string id){
    return vartable[id].second;
}

/*
    Names of Variables
                        */

std::vector<std::string> IScope::names(std::string id, std::vector<parser::VAR_TYPE> signature){
    auto function = functable.equal_range(id);

    for(auto x = function.first; x!=function.second; x++){
        if(std::get<0>(x->second) == signature){
            return std::get<1>(x->second);
        }
    }
}

/*
    Finding Which Block
                        */

parser::ASTBlockNode* IScope::block(std::string id, std::vector<parser::VAR_TYPE> signature){
    auto function = functable.equal_range(id);

    for(auto x = function.first; x != function.second; x++){
        if(std::get<0>(x->second) == signature){
            return std::get<2>(x->second);
        }
    }

    return nullptr;
}

/*
    List of Variables
                        */

std::vector<std::tuple<std::string, std::string, std::string>> IScope::varlist(){
    std::vector<std::tuple<std::string, std::string, std::string>> templist;

    for(auto const &x : vartable){
        switch(x.second.first){
            case parser::INT:
                templist.emplace_back(std::make_tuple("let", x.first, ": int", std::to_string(x.second.second.i)));
                break;

            case parser::FLOAT:
                templist.emplace_back(std::make_tuple("let", x.first, ": float", std::to_string(x.second.second.f)));
                break;

            case parser::BOOL:
                templist.emplace_back(std::make_tuple("let", x.first, ": bool", std::to_string(x.second.second.b)));
                break;

            case parser::STRING:
                templist.emplace_back(std::make_tuple("let", x.first, ": string", x.second.second.s));
                break;

            default:
                std::cout << "Unknown Type" << std::endl;
        }

        return std::move(templist);
    }
}

/*
    Constructor, Overloaded Constructor and Deconstructor for Interpreter
                                                                            */

Interpreter::Interpreter(){
    scopes.push_back(new IScope());
}

Interpreter::Interpreter(IScope *global){
    scopes.push_back(global);
}

Interpreter::~Interpreter() = default;







