#include "driver.hxx"
#include "parser.hxx"

yy::driver::driver() : trace_parsing (false), trace_scanning (false) {}

int yy::driver::parse (const std::string &f)
{
  file = f;
  location.initialize(&file);
  scan_begin();
  yy::parser parse(*this);
  parse.set_debug_level(trace_parsing);
  int res = parse();
  scan_end();
  return res;
}
