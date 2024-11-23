// Define the grammar name
grammar MiniLang;

// Define the main parser rules
program : statement+ EOF;

statement : typeDeclaration | assignment | output | input | ifStatement | whileLoop | COMMENT;

typeDeclaration : type IDENTIFIER ('=' (expression | input))? ';';

type : 'int' | 'double' | 'string' | 'bool';

assignment : IDENTIFIER '=' expression ';';

output : 'p' '(' expression ')' ';';

input : IDENTIFIER '=' 'r' '(' STRING ')' ';' | type IDENTIFIERp '=' 'r' '(' STRING ')' ';';

ifStatement : 'if' '(' condition ')' statement ('else' statement)?;

whileLoop : 'while' '(' condition ')' statement;

// Expressions
expression : term (('+' | '-') term)*;

term : factor (('*' | '/') factor)*;

factor : primary | '(' expression ')';

primary : IDENTIFIER | INTEGER | DOUBLE | STRING | BOOLEAN;

// Conditions
condition : expression relop expression | '!' condition | condition '&&' condition | condition '||' condition;

relop : '>' | '<' | '>=' | '<=' | '==' | '!=';

// Define lexer rules
IDENTIFIER : [a-zA-Z_] [a-zA-Z_0-9]*;
INTEGER : [0-9]+;
DOUBLE : [0-9]+ '.' [0-9]+;
STRING : '"' (~["])* '"';
BOOLEAN : 'true' | 'false';

COMMENT : '#' ~[\r\n]* -> skip;
WS : [ \t\r\n]+ -> skip;

// Keywords
IF : 'if';
ELSE : 'else';
WHILE : 'while';
TYPE_INT : 'int';
TYPE_DOUBLE : 'double';
TYPE_STRING : 'string';
TYPE_BOOL : 'bool';

// Operators
PLUS : '+';
MINUS : '-';
MULTIPLY : '*';
DIVIDE : '/';
ASSIGN : '=';
EQUAL : '==';
NOT_EQUAL : '!=';
GREATER : '>';
LESS : '<';
GREATER_EQUAL : '>=';
LESS_EQUAL : '<=';
AND : '&&';
OR : '||';
NOT : '!';

// Separators
LPAREN : '(';
RPAREN : ')';
LBRACE : '{';
RBRACE : '}';
SEMICOLON : ';';