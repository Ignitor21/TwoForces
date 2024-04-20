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
        return static_cast<T*>(nodes_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)).get());
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
