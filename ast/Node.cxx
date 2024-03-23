#include "parser.hxx"


namespace frontend
{

yy::location expression::get_location() const
{
    return location_;
}

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

identificator_expression* scope::get(const std::string& name) const
{
    auto it = symtab_.find(name);

    if (it != symtab_.end())
        return (*it).second;
    else
        return nullptr;

}

void scope::add_id(const std::string& name, identificator_expression* node)
{
    symtab_[name] = node;
}

void scope::set_value(const std::string& name, int value)
{
    symtab_[name]->set_value(value);
    return;
}

identificator_expression* scope::get_access(const yy::location& loc, const std::string& name)
{
    if (!symtab_.contains(name))
        throw yy::parser::syntax_error(loc, name + " is undeclared!");
    return symtab_[name];
}

void scope::add_action(INode* node)
{
    actions_.push_back(node);
    return;
}

scope* scope::reset_scope()
{
    return prev_;
}

int if_statement::calc()
{
    if(condition_->calc())
        true_body_->calc();
    else if (false_body_)
        false_body_->calc();

    return 0;
}

void if_statement::dump() const
{
    std::cout << "If statement: " << location_ << "\n";
    return;
}

int while_statement::calc()
{
    while(condition_->calc())
        body_->calc();
 
    return 0;
}

void while_statement::dump() const
{
    std::cout << "While statement: " << location_ << "\n";
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

int assignment_expression::calc()
{
    int ret = rhs_->calc();
    lhs_->set_value(ret);
    return ret;
}

void assignment_expression::dump() const
{
    std::cout << "Assignment: " << location_ << "\n";

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

const std::string& identificator_expression::get_name() const
{
    return name_;
}

void identificator_expression::set_value(int val) noexcept
{
    value_ = val;
}

int binary_op_expression::calc()
{
    int l_res = lhs_->calc();
    int r_res = rhs_->calc();

    switch(operator_)
    {

    case BinOps::PLUS:
        return l_res + r_res;

    case BinOps::MINUS:
        return l_res - r_res;

    case BinOps::MUL:
        return l_res * r_res;

    case BinOps::DIV:
        if (!r_res)
            throw yy::parser::syntax_error(location_, "Division by zero");
        return l_res / r_res;

    case BinOps::MOD:
        if (!r_res)
            throw yy::parser::syntax_error(location_, "Division by zero");
        return l_res % r_res;

    case BinOps::LESS:
        return l_res < r_res;

    case BinOps::GREATER:
        return l_res > r_res;

    case BinOps::EQ:
        return l_res == r_res;

    case BinOps::NEQ:
        return l_res != r_res;

    case BinOps::LESSEQ:
        return l_res <= r_res;

    case BinOps::GREATEREQ:
        return l_res >= r_res;

    case BinOps::AND:
        return l_res && r_res;

    case BinOps::OR:
        return l_res || r_res;

    default:
        throw yy::parser::syntax_error(location_, "Unknown binary operator");
        break;
    }

    return 0;
}

void binary_op_expression::dump() const
{
    std::cout << "Binary expression: " << location_ << "\n";
    return;
}

int unary_op_expression::calc()
{
        
    int res = expression_->calc();

    switch(operator_)
    {

    case UnOps::NOT:
        return !res;

    case UnOps::UPLUS:
        return +res;

    case UnOps::UMINUS:
        return -res;

    default:
        throw yy::parser::syntax_error(location_, "Unknown unary operator");
        break;
    }

    return 0;
}

void unary_op_expression::dump() const
{
    std::cout << "Unary expression: " << location_ << "\n";
    return;
}

}
