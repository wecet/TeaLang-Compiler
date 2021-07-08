# TeaLang

The goal of this project is to create a working compiler, lexer and interpreter for the TeaLang language whilst also considering the semantics of the code. A snippet of TeaLang code can be found below. The EBNF which defines the expressions and nodes in TeaLang can also be viewed below.

### EBNF 

        <Letter> ::= [A-Za-z]

        <Digit> ::= [0-9]

        <Printable> ::= [\textbackslash x20-\textbackslash x7E]

        <Type> ::= `float' | `int' | `bool' | `string'

        <BooleanLiteral> ::= `true' | `false'

        <IntegerLiteral> ::= <Digit> \{ <Digit> \}

        <FloatLiteral> ::= <Digit> \{ <Digit> \} `.' <Digit> \{ <Digit> \}

        <StringLiteral> ::= `"' \{ <Printable> \} `"'

        <Literal> ::= <BooleanLiteral> |
                      <IntegerLiteral> |
                      <FloatLiteral>   |
                      <StringLiteral>

        <Identifier> ::= ( `\_' | <Letter> )  \{ `\_' | <Letter> | <Digit> \}

        <MultiplicativeOp> ::= `*' | `/' | `and' 

        <AdditiveOp> ::= `+' | `-' | `or' 

        <RelationalOp> ::= `<' | `>' | `==' | `!=' | `<=' | `>=' 

        <ActualParams> ::= <Expression> \{ `,' <Expression> \}

        <FunctionCall> ::= <Identifier> `(' [ <ActualParams> ] `)' 

        <SubExpression> ::= `(' <Expression> `)' 

        <Unary> ::= ( `-' | `not' ) <Expression>

        <Factor> ::=  <Literal>       |
                      <Identifier>    |
                      <FunctionCall>  |
                      <SubExpression> |
                      <Unary>         

        <Term> ::= <Factor> \{ <MultiplicativeOp> <Factor> \}

        <SimpleExpression> ::= <Term> \{ <AdditiveOp> <Term> \}

        <Expression> ::= <SimpleExpression> \{ <RelationalOp> <SimpleExpression> \}

        <Assignment> ::= <Identifier> `=' <Expression>

        <VariableDecl> ::= `let' <Identifier> `:' <Type> `=' <Expression>

        <PrintStatement> ::= `print' <Expression>

        <RtrnStatement> ::= `return' <Expression>

        <IfStatement> ::= `if' `(' <Expression> `)' <Block> [ `else' <Block> ]

        <ForStatement> ::= `for' `(' [ <VariableDecl> ] ';' <Expression> ';' [ <Assignment> ] `)' <Block>

        <WhileStatement> ::= `while' `(' <Expression> `)' <Block> 

        <FormalParam> ::= <Identifier> `:' <Type>

        <FormalParams> ::= <FormalParam> \{ `,' <FormalParam> \}

        <FunctionDecl> ::= <type> <Identifier> `(' [ <FormalParams> ] `)' <Block>

        <Statement> ::=	<VariableDecl> `;'   |
                        <Assignment> `;'     |
                        <PrintStatement> `;' |
                        <IfStatement>        |
                        <ForStatement>       |
                        <WhileStatement>     |
                        <RtrnStatement> `;'  |
                        <FunctionDecl>       |
                        <Block>              

        <Block> ::= `{' \{ <Statement> \} `}' 

        <Program> ::= \{ <Statement> \}


### Code

   float Square(x:float){
        return x*x;
    }

    bool XGreaterThanY(x:float, y:float){
        let ans:bool = true;
        if (y>x) { ans = false; }
        return ans; 
    }

    bool XGreaterThanYv2(x:float, y:float){
        return x > y;
    }

    float AverageOfThree(x:float, y:float, z:float){
        let total:float = x + y + z;
        return total/3;
    }

    string JoinStr(s1:string, s2:string){
        let s3:string = s1 + s2;
        return s3;
    }

    let x:float = 2.4;
    let y:float = Square(2.5);
    print y;
    print XGreaterThanY(x, 2.3);
    print XGreaterThanYv2(Square(1.5), y);
    print AverageOfThree(x, y, 1.2);
    print JoinStr("Hello", "World");
    


# Tea2Lang 

Found in its corresponding directory is an improvement than the below defined TeaLang. The differences include an addition of acceptance of 'char' and 'auto' variables. Alongside the new opportunity to create structs, arrays and overloaded functions.

 
    
