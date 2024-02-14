#pragma once

#include <string>
#include <unordered_map>
#include "parser.hxx"

#define YY_DECL yy::parser::symbol_type yylex(yy::location& loc)

YY_DECL;

namespace yy 
{
  
class driver
{
private:
  std::unordered_map<std::string, int> symtab_;
  location location_;
  std::string file_;

  void scan_begin();
  void scan_end();
public:
  bool trace_scanning_;
  bool trace_parsing_;

  driver();
  int parse (const std::string& f);

};

}

