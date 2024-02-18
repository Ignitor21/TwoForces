#pragma once

#include <string>
#include <unordered_map>
#include "parser.hxx"
#include "Node.hxx"

#define YY_DECL yy::parser::symbol_type yylex(yy::location& loc)

YY_DECL;

namespace yy 
{
  
class driver
{
private:
  std::unordered_map<std::string, int> symtab_;
  std::vector<Node*> statements;
  location location_;
  std::string file_;
  bool trace_scanning_;
  bool trace_parsing_;

  void scan_begin();
  void scan_end();
public:
  driver();
  void set_parse_debug_level(bool level);
  void set_scan_debug_level(bool level);
  int parse (const std::string& f);

};

}

