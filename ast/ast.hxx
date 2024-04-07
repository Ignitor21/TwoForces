#pragma once

#include <string_view>
#include <utility>
#include <memory>

#include "Node.hxx"

namespace frontend
{
class INode;

class ast
{
private:
    scope global_scope_;
    std::vector<std::unique_ptr<INode>> nodes_;
public:
    scope* current_scope_;
public:

    ast() : global_scope_{}, nodes_{}, current_scope_(&global_scope_) {}
    
    void execute()
    {
        global_scope_.calc();
    }
    
    template <typename T, typename... Args>
    T* create_node(Args&&... args)
    {
        return static_cast<T*>(nodes_.emplace_back(std::make_unique<T>(args...)).get());
    }
 
    identificator_expression* create_node(yy::location loc, std::string_view str)
    {
        auto ret = current_scope_->get(str);

        if (ret)
            return ret;
        else
            return static_cast<identificator_expression*>(nodes_.emplace_back(std::make_unique<identificator_expression>\
                (identificator_expression(loc, std::string{str}))).get()); 
    }
    
    assignment_expression* create_node(yy::location loc, identificator_expression* id, expression* expr)
    {
        current_scope_->add_id(id->get_name(), id);
        
        return static_cast<assignment_expression*>(nodes_.emplace_back(std::make_unique<assignment_expression>\
            (assignment_expression(loc, id, expr))).get()); 
    }

    void add_action(INode* node)
    {
        current_scope_->add_action(node);
    } 
    
    void reset_scope()
    {
        current_scope_ = current_scope_->reset_scope();
    }

};

}
