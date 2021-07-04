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
            std::cout << ("[ERR] Signature Found\n") << std::endl;
            return true;
        }
    }

    std::cout << ("[ERR] Signature Not Found\n") << std::endl;
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
void SScope::declare(std::string id, parser::VAR_TYPE type, std::vector<parser::VAR_TYPE> signature, unsigned int number){
    funtable.insert(std::make_pair(id, std::make_tuple(type, signature, number)));
}


/* 
    Checking Types of Variable or Function Calls
                                                    */

parser::VAR_TYPE SScope::type_check(std::string id){
    if(already_referenced(id)){
        return vartable[id].first;
    }
    else{
        std::cout << "[ERR] Unknown Type" << id << std::endl;
    }
}

parser::VAR_TYPE SScope::type_check(std::string id, std::vector<parser::VAR_TYPE> signature){
    auto function = funtable.equal_range(id);

    if(std::distance(function.first, function.second) == 0){
        std::cout << "[ERR] Unknown Type" << id << std::endl;
    }

    //Checking Signature for All Variables 
    for(auto x = function.first; x!= function.second; x++){
        if(std::get<1>(x->second) == signature){
            return std::get<0>(x->second);
        }
    }

    std::cout << "[ERR] Unknown Type in Signature" << std::endl;

}

/* 
    Checking Declaration Line of Variable or Function 
                                                       */

unsigned int SScope::check_line(std::string id){
    if(already_referenced(id)){
        return vartable[std::move(id)].second;
    }
    else{
        std::cout << "[ERR] Error When Determining Line for " << id << std::endl;
    }
}

unsigned int SScope::check_line(std::string id, std::vector<parser::VAR_TYPE> signature){
    auto function = funtable.equal_range(id);

    if(std::distance(function.first, function.second) == 0){
        std::cout << "[ERR] Error when Determining Line for" << id << std::endl;
    }

    //Checking Signature for All Variables 
    for(auto x = function.first; x!= function.second; x++){
        if(std::get<1>(x->second) == signature){
            return std::get<0>(x->second);
        }
    }

    std::cout << "[ERR] Error when Determining Line for" << id << std::endl;
}

/*
    Function List
                    */

std::vector<std::pair<std::string, std::string>> SScope::list(){

    std::vector<std::pair<std::string, std::string>> argc;

    auto function = funtable.begin();
    auto last_func = funtable.end();

    for(function, last_func; function != last_func; function = funtable.upper_bound(function->first)){
   
        std::string name = function -> first + "(";
        bool params = false;

        for(auto p : std::get<1>(function -> second)){
            params = true;
            name += stringtype(p) + ", ";

        }

        name.pop_back();
        name.pop_back();
        name += ")";

        argc.emplace_back(std::make_pair(name, stringtype(std::get<0>(function->second))));
    }

    return std::move(argc);
}




