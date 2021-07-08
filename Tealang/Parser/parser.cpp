#include <iostream>
#include "parser.h"

using namespace parser;

Parser::Parser(lexer::Lexer* lexeme) : l1(lexeme){
        current = lexeme->getNextToken();
        next = lexeme->getNextToken();
}

Parser::Parser(lexer::Lexer *lexeme, unsigned int tok) : l1(lexeme){
    next = lexeme->getNextToken();
    for(unsigned int temp; temp < tok; temp++){
        pop_token();
    }
}

void Parser::pop_token(){
    current = next;
    next = l1->getNextToken();
}

ASTProgramNode* Parser::parse(){
    switch(current.type){
        case lexer::TOK_Var:
            return parsedec();
        case lexer::TOK_Let:
            return parseass();
        case lexer::TOK_Print:
            return parseprint();
        case lexer::TOK_If:
            return parseif();
        case lexer::TOK_While:
            return parsewhile();
        case lexer::TOK_Return:
            return parseret();
        case lexer::TOK_Def:
            return parsefunction();
        case lexer::TOK_OpenScope:
            return parseblock();

        default:
            std::cout << "Invalid Statement" << std::endl;
    }
}

ASTAssignmentNode* Parser::parseass(){
    std::string id;
    ASTExprNode* argc;

    unsigned int number = current.number;
    pop_token();

    if(current.type != lexer::TOK_Identifier){
        std::cout << "Expected Var Name after 'let'" << std::endl;
    }
    id = current.lexeme;
    pop_token();
    
    if(current.type != lexer::TOK_Equals){
        std::cout << "Expected Assignment Operator" << std::endl;
    }
    argc = parsexpr();
    pop_token();

    if(current.type != lexer::TOK_Semicolon){
        std::cout << "Expected ;" << std::endl;
    }

    return new ASTAssignmentNode(id, argc, number);
}

ASTPrintNode* Parser::parseprint(){
    unsigned int number = current.number;
    ASTExprNode* argc = parsexpr();
    pop_token();

    if(current.type != lexer::TOK_Semicolon){
        std::cout << "Expected ;" << std::endl;
    }

    return new ASTPrintNode(argc, number);
}

ASTReturnNode* Parser::parseret(){
    unsigned int number = current.number;
    ASTExprNode* argc = parsexpr();
    pop_token();

    if(current.type != lexer::TOK_Semicolon){
        std::cout << "Expected ;" << std::endl;
    }

    return new ASTReturnNode(argc, number);
}

ASTBlockNode* Parser::parseblock(){
    auto stat = new std::vector<ASTStatementNode*>;
    unsigned int number = current.number;
    pop_token();

    //Not End of Block
    while(current.type != lexer::TOK_CloseScope && current.type != lexer::TOK_Error && current.type != lexer::TOK_EOF){
        stat->push_back(parsestate());
        pop_token();
    }

    if(current.type == lexer::TOK_CloseScope){
        return new ASTBlockNode(*stat, number);
    }
    else{
        std::cout << "Reached EOF While Parsing" << std::endl;
    }
}

ASTDeclarationNode* Parser::parsedec(){
    VAR_TYPE type;
    std::string id;
    ASTExprNode* argc;
    unsigned int number;

    number = current.number;
    pop_token();

    if(current.type != lexer::TOK_Identifier){
        std::cout << "Expected Variable Name" << std::endl;
    }
    id = current.lexeme;

    pop_token();

    if(current.type != lexer::TOK_Colon){
        std::cout << "Expected : " << std::endl;
    }

    pop_token();
    type = parsetype(id);
    pop_token();

    if(current.type != lexer::TOK_Equals){
        std::cout << "Expected = " << std::endl;
    }

    argc = parsexpr();
    pop_token();

    if(current.type != lexer::TOK_Semicolon){
        std::cout << "Expected ; " << std::endl;
    }

    return new ASTDeclarationNode(type, id, argc, number);


}

ASTIfNode* Parser::parseif(){
    parser::ASTExprNode* compare;
    parser::ASTBlockNode* block;
    unsigned int number = current.number;

    //Pop (
    pop_token();
    if(current.type != lexer::TOK_OpenParenthesis){
        std::cout << "Expected (" << std::endl;
    }

    compare = parsexpr();

    // Pop )
    pop_token();
    if(current.type != lexer::TOK_CloseParenthesis){
        std::cout << "Expected )" << std::endl;
    }

    //Pop {
    pop_token();
    if(current.type != lexer::TOK_OpenScope){
        std::cout << "Expected { for IF Block" << std::endl;
    }

    block = parseblock();

    //Check if If has an Else
    if(next.type != lexer::TOK_Else){
        return new ASTIfNode(compare, block, number);
    }
    else{
        pop_token();
        pop_token();

        if(current.type != lexer::TOK_OpenScope){
            std::cout << "Expected {" << std::endl;
        }
    
        ASTBlockNode* elseblock = parseblock();

        return new ASTIfNode(compare, block, number, elseblock);
    }
}

ASTWhileNode* Parser::parsewhile(){
    ASTExprNode* condition;
    ASTBlockNode* whileblock;
    unsigned int number = current.number;

    pop_token();
    if(current.type != lexer::TOK_OpenParenthesis){
        std::cout << "Expected (" << std::endl;
    }

    condition = parsexpr();

    pop_token();
    if(current.type != lexer::TOK_CloseParenthesis){
        std::cout << "Expected )" << std::endl;
    }

    pop_token();
    if(current.type != lexer::TOK_OpenScope){
        std::cout << "Expected {" << std::endl;
    }

    whileblock = parseblock();

    return new ASTWhileNode(condition, whileblock, number);

}

ASTFunctionNode* Parser::parsefunction(){
    std::string id;
    std::vector<std::pair<std::string, VAR_TYPE>> params;
    VAR_TYPE type;
    ASTBlockNode *funcblock;
    unsigned int number = current.number;

    pop_token();

    if(current.type != lexer::TOK_Identifier){
        std::cout << "Expected Identifier" << std::endl;
    }

    id = current.lexeme;
    pop_token();

    if(current.type != lexer::TOK_OpenParenthesis){
        std::cout << "Expected ( after Identifier" << std::endl;;
    }

    pop_token();

    if(current.type != lexer::TOK_CloseParenthesis){
        params.push_back(*parsefparam());
        pop_token();

        while(current.type == lexer::TOK_Comma){
            pop_token();
            params.push_back(*parsefparam());
            pop_token();
        }

        if(current.type != lexer::TOK_CloseParenthesis){
            std::cout << "Expected (" << std::endl;
        }
    }

    pop_token();

    type = parsetype(id);
    if(current.type != lexer::TOK_OpenScope){
        std::cout << "Expected {" << std::endl;
    }

    funcblock = parseblock();

    return new ASTFunctionNode(id, params, type, funcblock, number);

}

std::pair<std::string, VAR_TYPE>* Parser::parsefparam(){
    std::string id;
    VAR_TYPE type;

    if(current.type != lexer::TOK_Identifier){
        std::cout << "Expected Variable Name" << std::endl;
    }
    id = current.lexeme;

    pop_token();

    if(current.type != lexer::TOK_Colon){
        std::cout << "Expected : After Identifier" << std::endl;
    }

    pop_token();
    type = parsetype(id);

    return new std::pair<std::string, VAR_TYPE>(id, type);
}

ASTExprNode* Parser::parsexpr(){
    ASTExprNode *argc = parse_sing_expr();
    unsigned int number = current.number;

    if(next.type == lexer::TOK_RelOp){
        pop_token();
        return new ASTBinaryNode(current.lexeme, argc, parsexpr(), number);
    }

    return argc;
}

ASTExprNode* Parser::parse_sing_expr(){
    ASTExprNode *term = parseterm();
    unsigned int number = current.number;

    if(next.type == lexer::TOK_AdditiveOp){
        pop_token();
        return new ASTBinaryNode(current.lexeme, term, parse_sing_expr(), number);
    }

    return term;
}

ASTExprNode* Parser::parseterm(){
    ASTExprNode *f = parsefactor();
    unsigned int number = current.number;

    if(next.type == lexer::TOK_MultiplicativeOp){
        pop_token();
        return new ASTBinaryNode(current.lexeme, f, parseterm(), number);
    }

    return f;
}

ASTExprNode *Parser::parsefactor(){
    pop_token();

    unsigned int number = current.number;
    switch(current.type){
        //Variable Literals
        case lexer::TOK_IntLiteral:
            return new ASTLiteralNode<int>(std::stoi(current.lexeme), number);
        case lexer::TOK_FloatLiteral:
            return new ASTLiteralNode<float>(std::stoi(current.lexeme), number);
        case lexer::TOK_Boolean:
            return new ASTLiteralNode<bool>(std::stoi(current.lexeme), number);

        case lexer::TOK_String:{
            std::string argc = current.lexeme.substr(1, current.lexeme.size() - 2);
            size_t pointer = argc.find("\\\"");

            while(pointer != std::string::npos){
                argc.replace(pointer, 2, "\"");
                pointer = argc.find("\\\"", pointer + 2);
            }

            //Setting /s as New Line 
            pointer = argc.find("\\n");
            while(pointer != std::string::npos){
                argc.replace(pointer, 2, "\n");
                pointer = argc.find("\\n", pointer + 2);
            }

            //Setting /t as Tab
            pointer = argc.find("\\t");
            while(pointer != std::string::npos){
                argc.replace(pointer, 2, "\t");
                pointer = argc.find("\\t", pointer + 2);
            }

            return new ASTLiteralNode<std::string>(std::move(argc), number);
        }

        case lexer::TOK_Identifier:
            if(next.type == lexer::TOK_OpenParenthesis){
                return parsefunc();
            }
            else return new ASTIdentifierNode(current.lexeme, number);

        case lexer::TOK_AdditiveOp:
        case lexer::TOK_Not:
            return new ASTUnaryNode(current.lexeme, parsexpr(), number);

        default:
            std::cout << "Expected Expression" << std::endl;
            break;
    }
}

ASTFunctionCallNode* Parser::parsefunc(){
    std::string id = current.lexeme;
    auto *params = new std::vector<ASTExprNode*>;
    unsigned int number = current.number;

    pop_token();
    if(current.type != lexer::TOK_OpenParenthesis){
        std::cout << "Expected (" << std::endl;
    }

    if(next.type != lexer::TOK_CloseParenthesis){
        params = parseparams();
    }
    else{
        pop_token();
    }

    if(current.type != lexer::TOK_CloseParenthesis){
        std::cout << "Expected )" << std::endl;
    }

    return new ASTFunctionCallNode(id, *params, number);
}

std::vector<ASTExprNode*>* Parser::parseparams(){
    auto params = new std::vector<ASTExprNode*>;
    params->push_back(parsexpr());

    pop_token();

    while(current.type == lexer::TOK_Comma){
        params->push_back(parsexpr());
        pop_token();
    }

    return params;
}

VAR_TYPE Parser::parsetype(std::string& id){
    switch(current.type){
        case lexer::TOK_IntLiteral:
            return INT;
        case lexer::TOK_FloatLiteral:
            return FLOAT;
        case lexer::TOK_Boolean:
            return BOOL;
        case lexer::TOK_String:
            return STRING;

        default:
            std::cout << "Unknown Type " << std::endl;
    }
}