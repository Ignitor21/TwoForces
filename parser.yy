%language "c++"
%skeleton "lalr1.cc" 
%require "3.5.2"
%defines

%define api.token.constructor
%define api.value.type variant
%define api.token.raw
%define parse.assert

%code requires {
  #include <string>
  namespace yy { class driver; }
}

%param { yy::driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hxx"
}

%token
  END  0  "end of file"
  ASGN    "="
  MINUS   "-"
  PLUS    "+"
  MUL     "*"
  DIV     "/"
  LPAREN  "("
  RPAREN  ")"
  LBRACE  "{"
  RBRACE  "}"
  IF      "if"
  WHILE   "while" 
  PRINT   "print"
  INPUT   "?"
;

%token <std::string> ID
%token <int> NUMBER
%nterm stmts 
%nterm stmt
%nterm assignment output
%nterm <int> expr term fact

%right "=";
%left "+" "-";
%left "*" "/";

%printer { yyo << $$; } <*>;

%%

stmts: 
  %empty  
| stmts stmt {};

stmt:
  assignment {}
| output     {}
;

assignment:
  ID "=" expr { drv.variables[$1] = $3; };

output:
  "print" expr { std::cout << $2 << "\n"; };

expr:
  expr "+" term { $$ = $1 + $3; }
| expr "-" term { $$ = $1 - $3; }
| term
;

term:
  term "*" fact { $$ = $1 * $3; }
| term "/" fact { $$ = $1 / $3; }
| fact
;

fact:
  NUMBER       
| ID           { $$ = drv.variables[$1]; }
| "?"         
  { 
    int n;
    std::cin >> n;
    $$ = n;
  }
| "(" expr ")" { $$ = $2; }
;

%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
