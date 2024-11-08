// Define the grammar name
grammar MiniLang;

// Define the main parser rules

program : statement+ EOF;

statement
    : assignment
    | output
    | input
    | ifStatement
    | whileLoop
    | COMMENT
    ;

assignment
    : IDENTIFIER '=' expression ';'
    ;

output
    : 'p' '(' STRING ')' ';'
    ;

input
    : IDENTIFIER '=' 'r' '(' STRING ')' ';'
    ;

ifStatement
    : 'if' condition '{' statement* '}' ('else' '{' statement* '}')?
    ;

whileLoop
    : 'while' condition '{' statement* '}'
    ;

// Expressions

expression
    : expression op=('*' | '/') expression   # MulDivExpr
    | expression op=('+' | '-') expression   # AddSubExpr
    | expression '**' expression             # ExpExpr
    | '(' expression ')'                     # ParenExpr
    | IDENTIFIER                             # VarExpr
    | INT                                    # IntExpr
    | DOUBLE                                 # DoubleExpr
    ;

// Conditions

condition
    : expression relop expression
    | '!' condition
    | condition '&&' condition
    | condition '||' condition
    ;

relop
    : '>' | '<' | '>=' | '<=' | '==' | '!='
    ;

// Define lexer rules

IDENTIFIER : [a-zA-Z_] [a-zA-Z_0-9]* ;

INT : [0-9]+ ;

DOUBLE : [0-9]+ '.' [0-9]+ ;

STRING : '"' (~["])* '"' ;

COMMENT : '#' ~[\r\n]* -> skip ;

WS : [ \t\r\n]+ -> skip ;

// Operators
ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';
EXP : '**';

// Separators and delimiters
SEPARATOR : ';';
LPAREN : '(';
RPAREN : ')';
LBRACE : '{';
RBRACE : '}';