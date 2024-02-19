%language "c++"
%skeleton "lalr1.cc" 
%require "3.5.2"
%defines

%define api.token.constructor
%define api.value.type variant
%define api.token.raw
%define parse.assert

%code requires
{
    #include <string>
    #include <unordered_map>
    #include "ast.hxx"
    namespace frontend { class ast; }
    
    using namespace frontend;
}

%parse-param { ast& abs_syntax_tree }
%param { yy::location& loc}
%locations

%define parse.trace
%define parse.error verbose

%code 
{
    #include "driver.hxx"
}   

%token
  END  0  "end of file"
  ASGN    "="
  PLUS    "+"
  MINUS   "-"
  MUL     "*"
  DIV     "/"
  LPAREN  "("
  RPAREN  ")"
  LBRACE  "{"
  RBRACE  "}"
  SCOLON  ";"
  IF      "if"
  WHILE   "while" 
  PRINT   "print"
  INPUT   "?"
;

%token <std::string> ID
%token <int> NUMBER
%nterm program
%nterm <scope*> stmts
%nterm <scope*> scope
%nterm <INode*> stmt
%nterm <binary_op_expression*> assignment 
%nterm <output_statement*> output
%nterm <expression*> lval
%nterm <expression*> expr term fact
%nterm <expression*> if
%nterm <expression*> while

%right "=";
%left "+" "-";
%left "*" "/";

%printer { yyo << $$;} <*>;

%%

program: stmts { abs_syntax_tree.execute(); } 

stmts: 
  %empty      {}  
| stmts stmt  { abs_syntax_tree.add_action($2); }
| stmts scope { std::cout << "New scope!\n" << "\n"; }
;

stmt:
  assignment ";" { $$ = $1; }
| output     ";" { $$ = $1; }
| if             {}
| while
;

assignment:
  lval "=" expr { $$ = new binary_op_expression(@2, $1, BinOps::ASGN, $3); }
;

lval:
    ID {$$ = new identificator_expression{@1, $1}; } 
;

output:
  "print" expr { $$ = new output_statement{@1, $2}; };

expr:
  expr "+" term { /* $$ = $1 + $3;*/ }
| expr "-" term { /* $$ = $1 - $3;*/ }
| term          { /*$$ = $1;    */  }
;

term:
  term "*" fact { /* $$ = $1 * $3; */}
| term "/" fact {/* $$ = $1 / $3; */}
| fact          {/* $$ = $1;    */  }
;

fact:
  NUMBER       { $$ = new number_expression{loc, $1};       }
| ID           { $$ = new identificator_expression{@1, $1}; }
| "?"         
  {
  /*
    int n;
    std::cin >> n;
    $$ = n; */
  }
| "(" expr ")" { $$ = $2; }
;

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
