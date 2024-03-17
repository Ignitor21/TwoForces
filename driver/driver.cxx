#include "parser.hxx"
#include "lexer.hxx"
#include "driver.hxx"

int yy::driver::scan_begin()
{
    yyset_debug(trace_scanning_);
    
    if (!(yyin = fopen(file_.c_str(), "r")))
    {
        std::cerr << "Cannot open " << file_ << "\n";
        return 1;
    }

    return 0;
}

void yy::driver::scan_end()
{
    fclose(yyin);
    yylex_destroy();
}

int yy::driver::parse(const std::string& f)
{
    file_ = f;
    location_.initialize(&file_);
    if (scan_begin())
        return 1;
    parser parser_obj(ast_, location_);
    parser_obj.set_debug_level(trace_parsing_);
    int res = parser_obj.parse();
    scan_end();
    return res;
}

void yy::driver::set_scan_debug_level(bool level) noexcept
{
    trace_scanning_ = true;
}

void yy::driver::set_parse_debug_level(bool level) noexcept
{
    trace_parsing_ = true;
}
