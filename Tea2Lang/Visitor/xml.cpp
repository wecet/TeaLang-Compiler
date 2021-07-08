#include "xml.h"

using namespace visitor;

XML::XML() : indent(0){
    xml.open("program.xml");
}

XML::~XML(){
    xml.close();
}

std::string XML::indenter(){
    std::string tab;

    for(int x = 0; x < indent; x++){
        tab += TAB;
    }

    return tab;
}

/*  
    Visitor Functions
                        */

//Program Node
void::XML::visit(parser::ASTProgramNode *program_node){
    xml << indenter() << "<Program>" << std::endl;;
    indent++;

    for(auto stmnt : program_node -> argc){
        stmnt -> accept(this);
    }

    indent--;

    xml << indenter() << " </Program>" << std::endl;
}

void XML::visit(parser::ASTDeclarationNode *declartion_node){
    xml << indenter() << "<Decl>" << std::endl;
    indent++;

    xml << indenter() << "<Var Type = \"" + string_var(declartion_node->type) + "\">" << declartion_node -> id << "/Id" << std::endl;
    declartion_node -> node -> accept(this);
    indent--;

    xml << indenter() << "</Decl>" << std::endl;
}

void XML::visit(parser::ASTAssignmentNode *assignment_node){
    xml << indenter() << "<Assigner>" << std::endl;
    indent++;

    xml << indenter() << "<Id>" << assignment_node->id << "</Id>" << std::endl;
    assignment_node -> argc -> accept(this);
    indent--;

    xml << indenter() << "</Assigner>" << std::endl;
}

void XML::visit(parser::ASTPrintNode *print_node){
    xml << indenter() << "<Print>" << std::endl;
    indent++;

    print_node -> argc -> accept(this);
    indent--;

    xml << indenter() << "</Print>" << std::endl;
}

void XML::visit(parser::ASTReturnNode *return_node){
    xml << indenter() << "<Return>" << std::endl;
    indent++;

    return_node -> argc -> accept(this);
    indent--;

    xml << indenter() << "</Return>" << std::endl;
}

void XML::visit(parser::ASTBlockNode *block_node){
    xml << indenter() << "<Block>" << std::endl;
    indent++;

    for(auto &blocks : block_node -> argc){
        blocks -> accept(this);
    }

    indent--;

    xml << indenter() << "</Block>" << std::endl;
}

void XML::visit(parser::ASTIfNode *if_node){
    xml << indenter() << "<If>" << std::endl;
    indent++;
    //Adding Condition
    xml << indenter() << "<Condition>" << std::endl;
    indent++;

    if_node -> comparison -> accept(this);
    indent--;

    xml << indenter() << "</Condition>" << std::endl;
    xml << indenter() << "<Block>" << std::endl;
    indent++;

    if_node -> ifblock -> accept(this);
    indent--;

    xml << indenter() << "</Block>" << std::endl;
    indent--;

    //Checking for Else
    if(if_node->elseblock){
        xml << indenter() << "<Block>" << std::endl;
        indent++;

        if_node -> elseblock -> accept(this);
        indent--;

        xml << indenter() << "</Block>" << std::endl;
    }
    xml << indenter() << "</If>" << std::endl;
}

void XML::visit(parser::ASTWhileNode *while_node){
    xml << indenter() << "<While>" << std::endl;
    indent++;

    //Condition
    xml << indenter() << "<Condition>" << std::endl;
    indent++;

    while_node -> condition -> accept(this);
    indent--;

    xml << indenter() << "</Condition>" << std::endl;
    while_node -> whileblock -> accept(this);
    indent--;
    xml << indenter() << "</While>" << std::endl;
}

void XML::visit(parser::ASTFunctionNode *function_node){
    xml << indenter() << "<Function Type = \"" + string_var(function_node->functype) + "\">" << std::endl;
    indent++;

    xml << indenter() << "<Id>" + function_node->type + "</Id>" << std::endl;

    for(auto &argc : function_node->params){
        xml << indenter() << "Parameter Type = \"" + string_var(argc.second) + "\">" + argc.first + "</Parameter>" << std::endl;
    }

    function_node->funcblock->accept(this);
    indent--;

    xml << indenter() << "</Function Definition>" << std::endl;

}

void XML::visit(parser::ASTLiteralNode<int> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'int'>" << std::endl;
    xml << indenter() << "<Int Const>" << std::endl;
    xml << "</Int Const>" << std::endl;
}

void XML::visit(parser::ASTLiteralNode<int> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'float'>" << std::endl;
    xml << indenter() << "<Float Const>" << std::endl;
    xml << "</Float Const>" << std::endl;
}

void XML::visit(parser::ASTLiteralNode<bool> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'bool'>" << std::endl;
    xml << indenter() << "<Bool Const>" << std::endl;
    xml << "</Bool Const>" << std::endl;
}

void XML::visit(parser::ASTLiteralNode<std::string> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'string'>" << std::endl;
    xml << indenter() << "<String Const>" << std::endl;
    xml << "</String Const>" << std::endl;
}

void XML::visit(parser::ASTLiteralNode<char> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'char'>" << std::endl;
    xml << indenter() << "<String Const>" << std::endl;
    xml << "</char Const>" << std::endl;
}

void XML::visit(parser::ASTLiteralNode<std::vector<typename std::iterator_traits<auto>>> *literal_node){
    xml << indenter() << "<Var Type = \"\" 'auto'>" << std::endl;
    xml << indenter() << "<String Const>" << std::endl;
    xml << "</Auto Const>" << std::endl;
}

void XML::visit(parser::ASTBinaryNode *binary_node){
    xml << indenter() << "<BinExprNode Op=\"" + xmloperator(binary_node->op) + "\">" << std::endl;
    indent++;

    binary_node -> left -> accept(this);
    binary_node -> right -> accept(this);

    indent--;
    xml << indenter() << "</BinExprNode>" << std::endl;
}

void XML::visit(parser::ASTIdentifierNode *identifier_node){
    xml << indenter() << "<Id>" << std::endl;
    xml << identifier_node->id;
    xml << "</Id>" << std::endl;
}

void XML::visit(parser::ASTUnaryNode *unary_node){
    xml << indenter() << "<UnExprNode Op=\"" + unary_node->op + "\">" << std::endl;
    indent++;

    unary_node->expression->accept(this);
    indent--;

    xml << indenter() << "</UnExprNode>" << std::endl;
}

void XML::visit(parser::ASTFunctionCallNode *function_call_node){
    xml << indenter() << "<Function Call>" << std::endl;
    indent++;

    xml << indenter() << "<Id>" + function_call_node->functype + "</Id>" << std::endl;

    for(auto &p : function_call_node -> signature){
        xml << indenter() << "<Parameter>" << std::endl;
        indent++;
        p->accept(this);
        indent++;
        xml << indenter << "</Parameter>" << std::endl;
    }

    indent--;
    xml << indenter << "</Function Call>" << std::endl;
}

std::string XML::string_var(parser::VAR_TYPE type){
    switch(type){
        case parser::INT:
            return "int";
        case parser::FLOAT:
            return "float";
        case parser::BOOL:
            return "bool";
        case parser::STRING:
            return "string";
        case parser::CHAR:
            return "char";
        case parser::AUTO:
            return "auto";
        
    }
}

std::string XML::xmloperator(std::string oper){
    if(oper == "<"){
        return "&lst;";
    }
    else if(oper == ">"){
        return "&grt;";
    }
    else if(oper == "<="){
        return "&lst;=";
    }
    else if(oper == ">="){
        return "&grt;=";
    }

}









