%language "c++"
%skeleton "lalr1.cc" 
%require "3.5.2"
%defines

%define api.token.constructor
%define api.value.type variant
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
  ASGN "="
  MINUS   "-"
  PLUS    "+"
  MUL    "*"
  DIV   "/"
  LPAREN  "("
  RPAREN  ")"
;

%token <std::string> ID
%token <int> NUMBER 
%nterm <int> expr

%printer { yyo << $$; } <*>;

%%

unit: assignments expr  { drv.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  ID "=" expr { drv.variables[$1] = $3; };

%right "=";
%left "+" "-";
%left "*" "/";

expr:
  NUMBER
| ID  { $$ = drv.variables[$1]; }
| expr "+" expr   { $$ = $1 + $3; }
| expr "-" expr   { $$ = $1 - $3; }
| expr "*" expr   { $$ = $1 * $3; }
| expr "/" expr   { $$ = $1 / $3; }
| "(" expr ")"    { $$ = $2; }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
