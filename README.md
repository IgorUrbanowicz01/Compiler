# Compiler of a simple imperative language
## Description

A compiler is a type of software that converts source code written in one programming language (the "source language") into machine code or another form of executable code (the "target language"). The process of compilation involves several stages, including lexical analysis (breaking the code down into individual "tokens"), syntax analysis (checking that the code follows the rules of the programming language), and code generation (creating the target code based on the input source code). In our example, we convert from a very simple language with some similarities to C to a virtual machine code. For the full specification, please refer to labor4.pdf.

## Language specification

Quick tour through language specification:
- arithmetic operations are performed on natural numbers. The result of subtracting a larger number from a smaller one is 0. In addition, dividing by zero should give a result 0 and the remainder is also 0,
- language includes implementation of procedures: procedures cannot contain recursive calls, formal parameters are passed through references (IN-OUT), variables used in a procedure must be it's formal parameters or be declared inside the procedure, only procedures defined earlier in the program code can be called in a procedure, other procedures can be called only with variables defined in the current procedure,
- you can use IF and IF ELSE conditions, WHILE and REPEAT UNTIL loops, 
- REPEAT UNTIL breaks when the condition iset and the loop will execute at least once,
- instruction READ takes the input from the user and assigns it to the specified variable and WRITE command prints out variable or constant value,
- variables and procedures identifiers are described by the regular expression [_a-z]+,
- lowercase and uppercase letters are distinguished,
- you can use [comments] in the code, which cannot be nested,
More on the grammar of the language in the labor4.pdf file.

Example code:
```
PROCEDURE s(n,m) IS
VAR i,o
BEGIN
    m:=1;
    i:=n;
    WHILE i>0 DO
        o:=i%2;
        IF o=1 THEN
            m:=m*i;
        ELSE
            m:=i*m;
        ENDIF
        i:=i-1;
    ENDWHILE
END

PROCEDURE bc(n,k,m) IS
VAR p,a,b,c
BEGIN
   s(n,a);
   p:=n-k;
   s(p,b);
   s(k,c);
   m:=a/b;
   m:=m/c;
END

PROGRAM IS
VAR n,k,w
BEGIN
    READ n;
    READ k;
    bc(n,k,w);
    WRITE w;
END
```

## Specifications and Details

 My compiler is written in C using Flex (Fast Lexical Analyzer Generator) and Bison for code analysis and parsing. I based it on the theory from the book ["Introduction to Compilers and Language Design"](https://www3.nd.edu/~dthain/compilerbook/) by Douglas Thain. At first, it uses Flex to remove white spaces and separate code into tokens. Afterwards, Bison parses those tokens using a context-free grammar and creates an AST (abstract syntax tree), which is a very handy way to keep our program organized and allows us easy access and manipulation of the code. The AST is made up of four different nodes: decl (declaration), expr (expression), stmt (statement), and type. The last one is somewhat redundant because this language is simple, and there are only two different types (int and procedure), and we could easily get by without it. However, following the advice of the book mentioned above, if I ever needed to expand my compiler, it might come in handy, and it's generally good practice to include it. Declarations always lie at the top of the tree and contain both variables and entire procedures. Statements hold secions of code like if statments and while loops. Expresions are sigle operations altho they can point to other expresion. The general trend of the tree is delc -> stmt -> expr.
    
## Optimisation

I added unit tests for Memory class which creates Memory mockup, perform some operations on it (adds many variables and procedures), then checks if returned values of chosen variables and procedures are correct. Second test is written in bash and involves running three test programs through the process of compiling and running it on the virtual machine, then checks if the output is correct (correct output is defined in ie. {test_program_name}_correct.out).

## Quick overview of files and folders structure

### src

Source folder contains compiler code:
- codeGenerator (contains machine code generator),
- memory (code for virtual machine memory mockup with some extensions like procedures and more complex variables),
- parser (Flex and Bison code),
- variables (code for variable implementation).

### tests
Folder that contains example code for testing, code that should give errors and correct output files.

### tools
Folder with Flex and Bison version used in the compiler.

### virtual-machine
Folder with virtual-machine files and code.

## Contributors
* [Mateusz Gancarz](https://github.com/magancarz) - compiler code
* [Dr Maciej Gębala](https://cs.pwr.edu.pl/gebala/) - virtual machine and assignment