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

 My compiler is written in C with Flex (Fast Lexical Analyzer Generator) and Bison for code analysys and parsing. I bassed it on theory from the book ["Introduction to Compilers and Language Design"](https://www3.nd.edu/~dthain/compilerbook/) by Douglas Thain. At first is usses Flex to remove white spaces and sparate code into token. Afterwords Bison parsses those tokens using Contextfree Gramar and creats AST (abstract syntax tree) wich is a verry handy way to keep our prgram. It allas us eassy acces and manipulation (...). AST is made out of four difrent nodes: decl(decleration), expr(expresion), stmt(statment) and type. The last in somewhat redundant as this language is simple that there are only two diffrent types (int and procedure) and we cuould easly get by without it, but followin the advice of the book matnioned above if I ever needed to expand my compiler it might come in handy and it's generaly a good practice to include it. declere allways lise at the top of the tree and it contains both veribles and entire procdures. statments hoold  
    
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