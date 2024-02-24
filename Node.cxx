#include "parser.hxx"
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
    if (prev_)
        symtab_ = prev_->symtab_;

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

int if_statement::calc()
{
    if(condition_->calc())
        body_->calc();
        
    return 0;
}

void if_statement::dump() const
{
    std::cout << "If statement: " << location_ << "\n";
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

int input_expression::calc()
{
    int tmp{};
    std::cin >> tmp;
    return tmp;
}

void input_expression::dump() const
{
    std::cout << "Input: " << location_ << "\n";

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

    case BinOps::PLUS:
    {
        int l_res = lhs_->calc();
        int r_res = rhs_->calc();
        return l_res + r_res;
    }

    case BinOps::MINUS:
    {
        int l_res = lhs_->calc();
        int r_res = rhs_->calc();
        return l_res - r_res;
    }

    case BinOps::MUL:
    {
        int l_res = lhs_->calc();
        int r_res = rhs_->calc();
        return l_res * r_res;
    }

    case BinOps::DIV:
    {
        int l_res = lhs_->calc();
        int r_res = rhs_->calc();

        if (!r_res)
        {
            throw yy::parser::syntax_error(location_, "Division by zero");
        }

        return l_res / r_res;
    }

    default:
        throw yy::parser::syntax_error(location_, "Unknown binary operator");
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
