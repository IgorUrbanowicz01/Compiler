# Compiler
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

 My compiler is written in C using Flex (Fast Lexical Analyzer Generator) and Bison for code analysis and parsing. I based it on the theory from the book ["Introduction to Compilers and Language Design"](https://www3.nd.edu/~dthain/compilerbook/) by Douglas Thain. At first, it uses Flex to remove white spaces and separate code into tokens. Afterwards, Bison parses those tokens using a context-free grammar and creates an AST (abstract syntax tree), which is a very handy way to keep our program organized and allows us easy access and manipulation of the code. The AST is made up of four different nodes: decl (declaration), expr (expression), stmt (statement), and type. The last one is somewhat redundant because this language is simple, and there are only two different types (int and procedure), and we could easily get by without it. However, following the advice of the book mentioned above, if I ever needed to expand my compiler, it might come in handy, and it's generally good practice to include it. Declarations always lie at the top of the tree and contain both variables and entire procedures. Statements hold sections of code, like if statements and while loops. Expressions are single operations, although they can point to other expressions. The general trend of the tree is decl → stmt → expr.
    
## Optimisation

One of the most common way for optimisation is "constant folding". I's basicly what it sounds like. We look thru the tree and if we ever encunter an expresion that has no varibles we can "fold it" e.g. 3+2-x -> expr(expr(3+2)-x) -> expr(5-x). Other whay to make your code faster is dividing by half when we see /2^x apropriet aount of time. It's significatly quicker then call the div procedure. Speeking of wich calling another way of optimisation. There are gennerly two schools of thought when it comes to basic funcions. You can either paste the entire code when you see any operations or you can initialize them at the beginning of the virtual machine code and then call them this method is slightly as we still need to paste the call phrase and make the operations but only ads a contant number of commands to the time of each opertion and it significantly decres the amount of commands with represents saving memory.

## Quick overview of files and folders structure

## Source Folder

This folder contains all the code for the compiler, including the following:

- Nodes for the Abstract Syntax Tree (AST)
- `labor4.pdf`, which is the full task assigned by Dr. Maciej Gębala
- Bison code for the parser
- Flex code for the scanner
- `test.sh`, which is a Bash script that I used to run some tests
- A `Makefile` for compiling the code

### operation

This folder contains pre-written, efficient basic operations for addition, subtraction, multiplication, and division, as well as their corresponding function calls.

### codeGen
Folder containing implementations that generate code for each node in the Abstract Syntax Tree (AST).

### virtual-machine
Folder with virtual-machine files and code.

## Contributors
* [Igor Urbanowicz](https://github.com/IgorUrbanowicz01) - compiler code
* [Dr Maciej Gębala](https://cs.pwr.edu.pl/gebala/) - virtual machine and assignment