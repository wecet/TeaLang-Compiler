#include "semantic.h"

#include <iostream>
#include <utility>

using namespace visitor;

/*
    Finding if the Signature or Variable has already 
    been declared or not
                            */

//Variable
bool SScope::already_referenced(std::string id){
    return vartable.find(id) != vartable.end();
}

//Overloaded Function to check Definition of Function Signature
bool SScope::already_referenced(std::string id, std::vector<parser::VAR_TYPE> signature){

    auto function = funtable.equal_range(id);

    if(std::distance(function.first, function.second) == 0){
        return false;
    }

    for(auto x = function.first; x != function.second; x++){
        if(std::get<1>(x->second) == signature){
            std::cout << ("Signature Found\n") << std::endl;
            return true;
        }
    }

    std::cout << ("Signature Not Found\n") << std::endl;
    return false;
}

/* 
    Declaring Variables and Functions
                                        */

//Variable
void SScope::declare(std::string id, parser::VAR_TYPE type, unsigned int number){
    vartable[id] = std::make_pair(type, number);
}

//Function


