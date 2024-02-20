#pragma once

#include "Node.hxx"

/*TO-DO:
 -rewrite with unique pointers
*/

namespace frontend
{
class INode;

class ast
{
private:
    scope global_scope_;
    scope* current_scope_;
    std::vector<INode> nodes_;
public:
    ast() : global_scope_{}, current_scope_(&global_scope_), nodes_{} {}
    
    void execute()
    {
        global_scope_.calc();
        return;
    }

    INode* create_node(INode&& node)
    {
         return &(nodes_.emplace_back(node));
    }

    void add_action(INode* node)
    {
        current_scope_->add_action(node);
        return;
    }
};


}
