#pragma once

#include "Node.hxx"
#include <utility>
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
        auto ptr = std::make_unique<T>(std::forward<T>(node));
        T* ret = ptr.get();
        nodes_.emplace_back(std::move(ptr));
        return ret;
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
