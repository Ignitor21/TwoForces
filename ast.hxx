#pragma once

#include "Node.hxx"

namespace frontend
{

class ast
{
private:
    scope* global_scope_;
    scope* current_scope_;
public:

    ast(scope* glob_scope) : global_scope_(glob_scope), current_scope_(global_scope_) {}
    
    ast() : global_scope_( new scope{} ), current_scope_(global_scope_) {}

    void execute()
    {
        global_scope_->calc();
    }

    void add_action(INode* node)
    {
        current_scope_->add_action(node);
    }
};


}
