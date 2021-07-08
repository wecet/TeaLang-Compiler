# TeaLang
The goal of this project is to create a working compiler, lexer and interpreter for the TeaLang language whilst also considering the semantics of the code. A snippet of TeaLang code can be found below.

# Tea2Lang 

Found in its corresponding directory is an improvement than the below defined TeaLang. The differences include an addition of acceptance of 'char' and 'auto' variables. Alongside the new opportunity to create structs, arrays and overloaded functions.

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
    
    
