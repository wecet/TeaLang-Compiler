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

/*
    Semantic Analysis from Visitor
                                    */

//Constructor
Analysis::Analysis(){
    scopes.push_back(new SScope());
}

//Overloaded Constructor
Analysis::Analysis(SScope* global){
    scopes.push_back(global);
}

//Deconstructor
Analysis::~Analysis() = default;

/*
    Visitors
              */

void Analysis::visit(parser::ASTProgramNode *program_node){
    for(auto &argc : program_node -> argc){
        argc -> accept(this);
    }
}

void Analysis::visit(parser::ASTDeclarationNode *declaration_node){
    SScope *scope = scopes.back();

    if(scope->already_referenced(declaration_node->id)){
        std::cout << "Variable was already Declared" << std::endl;
    }

    declaration_node ->node -> accept(this);

    if(declaration_node->type == parser::FLOAT && types == parser::INT){
        scope->declare(declaration_node->id, parser::FLOAT, declaration_node->number);
    }
    else if(declaration_node->type == types){
        scope->declare(declaration_node->id, declaration_node->type, declaration_node->number);
    }
    else{
        std::cout << "Types don't Match" << std::endl;
    }
}

void Analysis::visit(parser::ASTAssignmentNode *assignment_node){
    unsigned long temp;
    for(temp = scopes.size() -1; !scopes[temp] -> already_referenced(assignment_node->id); temp--)
        if(temp <= 0)
            std::cout << "[ERR] Variable aready Assigned" << std::endl;
        
    parser::VAR_TYPE type = scopes[temp]->type_check(assignment_node->id);
    assignment_node->argc->accept(this);

    if(type == parser::FLOAT && types == parser::INT){

    }
    else if(types != type){
        std::cout << "Mismatched Type" << std::endl;
    }

}

void Analysis::visit(parser::ASTPrintNode *print_node){
    print_node -> argc -> accept(this);

}

void Analysis::visit(parser::ASTReturnNode *return_node){
    return_node -> argc -> accept(this);
    if(!funcs.empty() && types != funcs.top()){
        std::cout << "Invalid Return Type" << std::endl;
    }
}

void Analysis::visit(parser::ASTBlockNode *block_node){
    scopes.push_back(new SScope());

    for(auto p : params){
        scopes.back() -> declare(p.first, p.second, block_node->number);
    }
    params.clear();

    for(auto &s : block_node->argc){
        s -> accept(this);
    }

    scopes.pop_back();
}

void Analysis::visit(parser::ASTIfNode *if_node){
    if_node -> comparison -> accept(this);

    if(types != parser::BOOL){
        std::cout << "Invalid If-Condition" << std::endl;
    }

    if_node -> ifblock -> accept(this);

    if(if_node -> elseblock){
        if_node -> elseblock -> accept(this);
    }
}

void Analysis::visit(parser::ASTWhileNode *while_node){
    while_node -> condition -> accept(this);

    if(types != parser::BOOL){
        std::cout << "Invalid While Condition" << std::endl;
    }

    while_node -> whileblock -> accept(this);
}

void Analysis::visit(parser::ASTFunctionNode *func_def_node){
    for(auto &s : scopes){
        if(s->already_referenced(func_def_node->type, func_def_node->signature)){
            int dec_line = s->check_line(func_def_node->type, func_def_node->signature);
            std::string sig = "(";
            bool params = false;

            for(auto p : func_def_node -> signature){
                params = true;
                sig += stringtype(p) + ",";
            }
            sig.pop_back();
            sig.pop_back();
            sig += ")";

            std::cout << "Function already defined" << std::endl;
        }
    }

    scopes.back() -> declare(func_def_node->type, func_def_node->functype, func_def_node->signature, func_def_node->number);
    funcs.push(func_def_node->functype);

    params.clear();
    params = func_def_node->params;

    func_def_node->funcblock->accept(this);

    if(!ret(func_def_node->funcblock) = false){
        std::cout << "Does Not Guarantee Output" << std::endl;
    }

    funcs.pop();
}

void Analysis::visit(parser::ASTLiteralNode<int>*) {
    types = parser::INT;
}

void Analysis::visit(parser::ASTLiteralNode<float>*) {
    types = parser::FLOAT;
}

void Analysis::visit(parser::ASTLiteralNode<bool>*) {
    types = parser::BOOL;
}

void Analysis::visit(parser::ASTLiteralNode<std::string>*) {
    types = parser::STRING;
}

void Analysis::visit(parser::ASTBinaryNode *binary_node){
    std::string ope = binary_node -> op;

    binary_node -> left -> accept(this);
    parser::VAR_TYPE lvartype = type;

    binary_node -> right -> accept(this);
    parser::VAR_TYPE rvartype = type;

    if(ope == "*" || ope == "/" || ope == "-"){
        if(lvartype != parser::INT && lvartype != parser::FLOAT || rvartype != parser::INT && rvartype != parser::FLOAT){
            std::cout << "Incompatible Numerical Operands" << std::endl;
        }
        type = (lvartype == parser::INT && rvartype  == parser::INT) ? parser::INT : parser::FLOAT;
    }
    else if(op == "+"){
        if(lvartype == parser::BOOL || rvartype == parser::BOOL){
            std::cout << "Invalid Operand for BOOL" << std::endl;
        }
        else if(lvartype == parser::STRING || rvartype == parser::STRING){
            std::cout << "Mismatched Operands" << std::endl;
        }
        else if(lvartype == parser::STRING && rvartype == parser::STRING){
            type = parser::STRING;
        }
        else{
            type = (lvartype == parser::INT && rvartype == parser::INT) ? parser::INT : parser::FLOAT;
        }
    }

    else if(ope == "and" || op == "or"){
        if(lvartype == parser::BOOL && rvartype == parser::BOOL){
            type = parser::BOOL;
        }
        else{
            std::cout << "Expected Two Boolean Operands" << std::endl;
        }
    }

    else if(ope == "<"  || ope == ">" || ope == "<=" || ope == ">="){
        if((lvartype != parser::FLOAT && lvartype != parser::INT) || (rvartype != parser::FLOAT && rvartype != parser::INT)){
            std::cout << "Expected Two Numerical Operands" << std::endl;
        }
        type = parser::BOOL;
    }

    else if(ope == "==" || ope == "!="){
        if(lvartype != rvartype && (lvartype != parser::FLOAT || rvartype != parser::INT) && (lvartype != parser::INT || rvartype != parser::FLOAT)){
            std::cout << "Expected Arguments of Same Type" << std::endl;
        }
        type = parser::BOOL
    }

    else{
        std::cout << "Unknown Operator" << std::endl;
    }
}

void Analysis::visit(parser::ASTIdentifierNode *identifier_node){
    unsigned long temp;
    for(temp = scopes.size() -1; !scopes[temp] -> already_referenced(identifier_node->id); temp--){
        if(temp <= 0){
            std::cout << "Identifier was never Declared" << std::endl;
        }
    }

    types = scopes[temp]->type_check(identifier_node->id);
    
}

void Analysis::visit(parser::ASTUnaryNode *unary_node){
    unary_node -> expression -> accept(this);

    switch(types){
        case parser::INT:
            break;
        case parser::FLOAT:
            if(unary_node->op != "+" && unary_node->op != "-"){
                std::cout << "Operator incorrectly placed" << std::endl;
            }
            break;
        case parser::BOOL:
            if(unary_node->op != "not"){
                    std::cout << "Operator incorrectly placed" << std::endl;
            }
            break;
        default:
            std::cout << "Incompatible Unary Operator" << std::endl;
        
    }
}

void Analysis::visit(parser::ASTFunctionCallNode *func_call_node){
    std::vector<parser::VAR_TYPE> signature;

    for(auto p : func_call_node -> signature){
        p -> accept(this);
        signature.push_back(types);
    }

    unsigned long temp;
    for(temp = scopes.size()- 1; !scopes[temp]->already_referenced(func_call_node->functype, signature); temp--){
        if(temp <= 0){
            std::string name = func_call_node->functype + "(";
            bool params = false;
            for(auto p : signature){
                params = true;
                name += stringtype(p) + ",";
            }
            name.pop_back();
            name.pop_back();
            name += ")";
            std::cout << "Function was never declared" << std::endl;
        }
    types = scopes[temp]->type_check(func_call_node->functype, std::move(signature));
    }
}

std::string stringtype(parser::VAR_TYPE type){
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
            std::cout << "Invalid Type" << type << std::endl;
    }
}

bool Analysis::ret(parser::ASTStatementNode *statement_node){
    
}



