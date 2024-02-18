#pragma once

#include "Node.hxx"

namespace ast
{

class ast
{
private:
    scope* global_scope_;
    scope* current_scope;
public:

    ast(scope* glob_scope) : global_scope_(glob_scope), current_scope_(global_scope) {}

    void execute()
    {
        global_scope_.calc();
    }
};


}
