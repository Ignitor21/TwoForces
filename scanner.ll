%{
  #include <cerrno>
  #include <climits>
  #include <cstdlib>
  #include <cstring>
  #include <string>
  #include "driver.hxx"
  #include "parser.hxx"
%}

%option noyywrap nounput noinput batch debug

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type
  make_NUMBER (const std::string &s, const yy::parser::location_type& loc);
%}

WS       [ \f\r\t\v]
ID       [a-zA-Z][a-zA-Z_0-9]*
NUMBER   (0|[1-9][0-9]*)

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  loc.step();
%}

{WS}+      loc.step();
\n+        loc.lines(yyleng); loc.step();

"-"        return yy::parser::make_MINUS(loc);
"+"        return yy::parser::make_PLUS(loc);
"*"        return yy::parser::make_MUL(loc);
"/"        return yy::parser::make_DIV(loc);
"("        return yy::parser::make_LPAREN(loc);
")"        return yy::parser::make_RPAREN(loc);
";"        return yy::parser::make_SCOLON(loc);
"="        return yy::parser::make_ASGN(loc);
"print"    return yy::parser::make_PRINT(loc);
"?"        return yy::parser::make_INPUT(loc);

{NUMBER}   return make_NUMBER(yytext, loc);
{ID}       return yy::parser::make_ID(yytext, loc);
.          {
             throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));
}
<<EOF>>    return yy::parser::make_END(loc);

%%

yy::parser::symbol_type make_NUMBER (const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER ((int) n, loc);
}


