#pragma once

#include "Node.hxx"
#include <memory>

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
    
    template <typename T>
    T* create_node(T&& node)
    {
        auto ptr = std::make_unique<T>(node);
        T* ret = ptr.get();
        nodes_.emplace_back(std::move(ptr));
        return ret;
    }
    
    identificator_expression* create_node(identificator_expression&& node)
    {
        std::string name = node.get_name(); 
        identificator_expression* tmp = current_scope_->contains(name); 

        if (tmp)
            return tmp;
        
        auto ptr = std::make_unique<identificator_expression>(node);
        identificator_expression* ret = ptr.get();
        current_scope_->add_id(name, ret);
        nodes_.emplace_back(std::move(ptr));
        return ret;
    }

    void add_action(INode* node)
    {
        if (node)
            current_scope_->add_action(node);
    }

    identificator_expression* get_access(const yy::location& loc, const std::string& name) const
    {
        return current_scope_->get_access(loc, name);
    }
    
    void reset_scope()
    {
        current_scope_ = current_scope_->reset_scope();
    }

};

}
