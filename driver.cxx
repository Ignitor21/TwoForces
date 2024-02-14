#include "parser.hxx"
#include "lexer.hxx"
#include "driver.hxx"

yy::driver::driver() : trace_parsing_ (false), trace_scanning_ (false) {}

void yy::driver::scan_begin()
{
  yyset_debug(trace_scanning_);
  if (file_.empty () || file_ == "-")
        yyin = stdin;
  else if (!(yyin = fopen (file_.c_str (), "r")))
    {
        std::cerr << "cannot open " << file_ << ": " << strerror(errno) << '\n';
        exit (EXIT_FAILURE);
    }
}

void yy::driver::scan_end()
{
    fclose(yyin);
    yylex_destroy();
}

int yy::driver::parse (const std::string &f)
{
    file_ = f;
    location_.initialize(&file_);
    scan_begin();
    yy::parser parser_obj(symtab_, location_);
    parser_obj.set_debug_level(trace_parsing_);
    int res = parser_obj.parse();
    scan_end();
    return res;
}
