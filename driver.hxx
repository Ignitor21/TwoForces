#pragma once

#include <string>
#include <unordered_map>

#include "parser.hxx"
#include "location.hh"
#include "Node.hxx"
#include "ast.hxx"

#define YY_DECL yy::parser::symbol_type yylex(yy::location& loc)
YY_DECL;


namespace yy 
{
  
class driver
{
private:
  frontend::ast ast_;
  location location_;
  std::string file_;
  bool trace_scanning_ = false;
  bool trace_parsing_ = false;

  void scan_begin();
  void scan_end();
public:
  driver() = default;
  int parse (const std::string& f);
  void set_parse_debug_level(bool level);
  void set_scan_debug_level(bool level);
};

}

