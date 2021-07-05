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

/*
    Visitor Functions
                        */

void visitor::Interpreter::visit(parser::ASTProgramNode *program_node){

    for(auto &argv : program_node -> argc){
        argv -> accept(this);
    }
}

void visitor::Interpreter::visit(parser::ASTDeclarationNode *declaration_node){

    declaration_node -> node -> accept(this);

    switch(declaration_node -> type){
        case parser::INT:
            scopes.back()->declare(declaration_node->id, expression_content.i);
            break;
        
        case parser::FLOAT:
            if(expression_type == parser::INT){
                scopes.back()->declare(declaration_node->id,(float)expression_content.f);
            }
            else{
                scopes.back()->declare(declaration_node->id, expression_content.f);
            }
            break;

        case parser::BOOL:
            scopes.back()->declare(declaration_node->id, expression_content.b);
            break;

        case parser::STRING:
            scopes.back()->declare(declaration_node->id, expression_content.s);
            break;

    }
}

void visitor::Interpreter::visit(parser::ASTAssignmentNode *assignment_node){

    unsigned long temp;
    for(temp = scopes.size() - 1; !scopes[temp] -> already_referenced(assignment_node->id); temp--);

    assignment_node -> argc -> accept(this);

    switch(scopes[temp]->vartype_of(assignment_node->id)){
        case parser::INT:
            scopes[temp]->declare(assignment_node->id, expression_content.i);
            break;
        
        case parser::FLOAT:
            scopes[temp]->declare(assignment_node->id, (float)expression_content.f);
            break;

        case parser::BOOL:
            scopes[temp]->declare(assignment_node->id, expression_content.b);
            break;

        case parser::STRING:
            scopes[temp]->declare(assignment_node->id, expression_content.s);
            break;
    }
}

void visitor::Interpreter::visit(parser::ASTPrintNode *print_node){

    print_node -> argc -> accept(this);

    switch(expression_type){
        case parser::INT:
            std::cout << expression_content.i;  
            break;

        case parser::FLOAT:
            std::cout << expression_content.f;
            break;

        case parser::BOOL:
            std::cout << expression_content.f;
            break;

        case parser::STRING:
            std::cout << expression_content.s;
            break; 
    }
}

void visitor::Interpreter::visit(parser::ASTReturnNode *return_node){
    return_node -> argc -> accept(this);
}

void visitor::Interpreter::visit(parser::ASTBlockNode *block_node){

}

void visitor::Interpreter::visit(parser::ASTIfNode *if_node){
    if_node -> comparison -> accept(this);

    if(expression_content.b){
        if_node -> ifblock -> accept(this);
    }
    else{
        if(if_node -> elseblock){
            if_node -> elseblock -> accept(this);
        }
    }
}

void visitor::Interpreter::visit(parser::ASTWhileNode *while_node){
    while_node -> condition -> accept(this);

    while(expression_content.b){
        while_node -> whileblock -> accept(this);

        while_node -> condition -> accept(this);
    }
}

void visitor::Interpreter::visit(parser::ASTFunctionNode *function_node){
    scopes.back()->declare(function_node->type, function_node->signature, function_node->funcblock);
}

void visitor::Interpreter::visit(parser::ASTLiteralNode<int> *literal_node){
    variable var;
    var.i = literal_node->vartype;
    expression_type = parser::INT;
    expression_content = std::move(var);
}

void visitor::Interpreter::visit(parser::ASTLiteralNode<float> *literal_node){
    variable var;
    var.f = literal_node->vartype;
    expression_type = parser::FLOAT;
    expression_content = std::move(var);
}

void visitor::Interpreter::visit(parser::ASTLiteralNode<bool> *literal_node){
    variable var;
    var.b = literal_node->vartype;
    expression_type = parser::BOOL;
    expression_content = std::move(var);
}

void visitor::Interpreter::visit(parser::ASTLiteralNode<std::string> *literal_node){
    variable var;
    var.s = literal_node->vartype;
    expression_type = parser::STRING;
    expression_content = std::move(var);
}

void visitor::Interpreter::visit(parser::ASTBinaryNode *binary_node){

}

void visitor::Interpreter::visit(parser::ASTIdentifierNode *identifier_node){

    unsigned long temp;
    for(temp = scopes.size() - 1; !scopes[temp] -> already_referenced(identifier_node->id); temp--){
        expression_type = scopes[temp] -> vartype_of(identifier_node->id);
        expression_content = scopes[temp] -> content(identifier_node->id);
    }
}

void visitor::Interpreter::visit(parser::ASTUnaryNode *unary_node){
    unary_node -> expression -> accept(this);

    switch(expression_type){
        case parser::INT:
            if(unary_node->op == "-"){
                expression_content.i *= -1;
                break;
            }

        case parser::FLOAT:
            if(unary_node->op == "-"){
                expression_content.f *= -1;
                break;
            }

        case parser::BOOL:
            expression_content.b ^= 1;
    }
}

void visitor::Interpreter::visit(parser::ASTFunctionCallNode *function_call_node){

}

std::pair<parser::VAR_TYPE, variable> Interpreter::expr(){
    return std::move(std::make_pair(expression_type, expression_content));
};


std::string visitor::stringtype(parser::VAR_TYPE type){
    switch(type){
        case parser::INT:
            return "int";
        case parser::FLOAT:
            return "float";
        case parser::BOOL:
            return "bool";
        case parser::STRING:
            return "string";
        default:
            std::cout << "[ERR] Unknown Type" << std::endl;
    }
}

