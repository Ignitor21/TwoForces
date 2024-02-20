#include "Node.hxx"

namespace frontend
{

int output_statement::calc()
{
    std::cout << expression_->calc();
    return 0;
}

void output_statement::dump() const
{
    std::cout << "Output statement: " << location_ << "\n";
    return;
}


int scope::calc()
{
    for (auto it = statements_.rbegin(), ite = statements_.rend(); it != ite; ++it)
        (*it)->calc();

    return 0;
}

void scope::dump() const
{
    std::cout << "Scope: " << "\n";

    for (auto& statement: statements_)
        statement->dump();
    
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
    return value_;
}

void identificator_expression::dump() const
{
    std::cout << "Identificator: " << location_ << "\n";
    return;
}

int binary_op_expression::calc()
{
    //DEBUG THIS:
    return 1488;
}

void binary_op_expression::dump() const
{
    std::cout << "Binary expression: " << location_ << "\n";
    return;
}

}
