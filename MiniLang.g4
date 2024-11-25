// Define the grammar name
grammar MiniLang;

// Define the main parser rules
program : statement+ EOF;

statement 
    : ifStatement 
    | whileLoop 
    | printStmt 
    | typeDeclaration 
    | assignment 
    | inputStmt 
    | block
    ;

block : '{' statement* '}';

typeDeclaration 
    : type IDENTIFIER ('=' (expression | inputStmt))? ';'
    ;

type : TYPE_INT | TYPE_DOUBLE | TYPE_STRING | TYPE_BOOL;

assignment : IDENTIFIER '=' (expression | inputStmt) ';';

printStmt : 'p' '(' expression ')' ';';

inputStmt : 'r' '(' STRING ')' ';';

ifStatement 
    : 'if' '(' comparison ')' (statement | block) 
      ('else' (statement | block))?
    ;

whileLoop 
    : 'while' '(' comparison ')' (statement | block)
    ;

// Expressions with precedence
expression 
    : term ((PLUS | MINUS) term)*
    ;

term 
    : factor ((MULTIPLY | DIVIDE) factor)*
    ;

factor 
    : primary 
    | LPAREN expression RPAREN
    ;

primary 
    : IDENTIFIER 
    | INTEGER 
    | DOUBLE 
    | STRING 
    | BOOLEAN
    ;

// Conditions
comparison 
    : expression relop expression
    | NOT comparison
    | comparison AND comparison
    | comparison OR comparison
    ;

relop 
    : '>' | '<' | '>=' | '<=' | '==' | '!='
    ;

// Lexer rules
IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]*;
INTEGER : [0-9]+;
DOUBLE : [0-9]+ '.' [0-9]+;
STRING : '"' (~["\r\n])* '"';
BOOLEAN : 'true' | 'false';

// Keywords
TYPE_INT : 'int';
TYPE_DOUBLE : 'double';
TYPE_STRING : 'string';
TYPE_BOOL : 'bool';

// Operators
PLUS : '+';
MINUS : '-';
MULTIPLY : '*';
DIVIDE : '/';
POWER : '**';
ASSIGN : '=';

// Comparison operators
GREATER : '>';
LESS : '<';
GREATER_EQUAL : '>=';
LESS_EQUAL : '<=';
EQUAL_EQUAL : '==';
NOT_EQUAL : '!=';

// Logical operators
AND : '&&';
OR : '||';
NOT : '!';

// Separators
LPAREN : '(';
RPAREN : ')';
LBRACE : '{';
RBRACE : '}';
SEMICOLON : ';';

// Skip whitespace and comments
WS : [ \t\r\n]+ -> skip;