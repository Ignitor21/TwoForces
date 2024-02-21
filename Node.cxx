#include "Node.hxx"

namespace frontend
{

int output_statement::calc()
{
    std::cout << expression_->calc() << "\n";
    return 0;
}

void output_statement::dump() const
{
    std::cout << "Output statement: " << location_ << "\n";
    return;
}


int scope::calc()
{
    for (auto& action: actions_)
        action->calc();

    return 0;
}

void scope::dump() const
{
    std::cout << "Scope: " << "\n";

    for (auto& action: actions_)
        action->dump();
    
    return;
}

int expression::calc()
{
    return value_;
}

void expression::dump() const
{
    std::cout << "Expression: " << location_ << "\n";

    return;
}

int number_expression::calc()
{
    return value_;
}

void number_expression::dump() const
{
    std::cout << "Number: " << location_ << "\n";

    return;
}

int identificator_expression::calc()
{
    return scope_->get_value(name_);
}

void identificator_expression::dump() const
{
    std::cout << "Identificator: " << location_ << "\n";
    return;
}

int binary_op_expression::calc()
{
    switch(operator_)
    {

    case BinOps::ASGN:
    {
        int ret = rhs_->calc();
        identificator_expression* tmp = static_cast<identificator_expression*>(lhs_);
        tmp->set_value(ret);
        return ret;
        break;
    }

    default:
        std::cerr << "Unknown operator" << "\n";
        return 0;
        break;
    }

    return 0;
}

void binary_op_expression::dump() const
{
    std::cout << "Binary expression: " << location_ << "\n";
    return;
}

}
