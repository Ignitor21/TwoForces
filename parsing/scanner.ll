%{
  #include <string>
  #include <limits>
  #include "driver.hxx"
  #include "parser.hxx"
%}

%option noyywrap nounput noinput batch debug

%{
  yy::parser::symbol_type make_NUMBER(const std::string &s, const yy::parser::location_type& loc);
%}

WS      [ \f\r\t\v]
ID      [a-zA-Z][a-zA-Z_0-9]*
NUMBER  (0|[1-9][0-9]*)
COMMENT [/][/].*

%{
  #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
  loc.step();
%}

{WS}+      loc.step();
\n+        loc.lines(yyleng); loc.step(); 
{COMMENT}  loc.step();  

"-"        return yy::parser::make_MINUS(loc);
"+"        return yy::parser::make_PLUS(loc);
"*"        return yy::parser::make_MUL(loc);
"/"        return yy::parser::make_DIV(loc);
"%"        return yy::parser::make_MOD(loc);
"("        return yy::parser::make_LPAREN(loc);
")"        return yy::parser::make_RPAREN(loc);
"{"        return yy::parser::make_LBRACE(loc);
"}"        return yy::parser::make_RBRACE(loc);
";"        return yy::parser::make_SCOLON(loc);
"="        return yy::parser::make_ASGN(loc);
"print"    return yy::parser::make_PRINT(loc);
"?"        return yy::parser::make_INPUT(loc);
"if"       return yy::parser::make_IF(loc);
"else"     return yy::parser::make_ELSE(loc);
"while"    return yy::parser::make_WHILE(loc);

"<"        return yy::parser::make_LESS(loc);
">"        return yy::parser::make_GREATER(loc);
"=="       return yy::parser::make_EQ(loc);
"!="       return yy::parser::make_NEQ(loc);
"<="       return yy::parser::make_LESSEQ(loc);
">="       return yy::parser::make_GREATEREQ(loc);

"&&"       return yy::parser::make_AND(loc);
"||"       return yy::parser::make_OR(loc);
"!"        return yy::parser::make_NOT(loc);

{NUMBER}   return make_NUMBER(yytext, loc);
{ID}       return yy::parser::make_ID(yytext, loc);
<<EOF>>    return yy::parser::make_END(loc);
.          throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));

%%

yy::parser::symbol_type make_NUMBER(const std::string &s, const yy::parser::location_type& loc)
{
  long n = std::stol(s);

  if (!(std::numeric_limits<int>::min() <= n && n <= std::numeric_limits<int>::max()))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);

  return yy::parser::make_NUMBER(static_cast<int>(n), loc);
}
