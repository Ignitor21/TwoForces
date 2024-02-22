#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "location.hh"

/* TO-DO:
- move methods implementation to cxx file
- implement scopes, if and while
- add logical operations
- add id checking
*/

namespace frontend
{

enum class BinOps
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    ASGN
};

struct INode
{
    virtual int calc() = 0;
    virtual void dump() const = 0;
    virtual ~INode() {}
};

class statement : public INode
{
protected:
    yy::location location_;
public:
    statement(yy::location loc) : location_(loc) {}

};

class expression;

class output_statement final: public statement
{
private:
    expression* expression_;
public:
    int calc() override;
    void dump() const override;

    output_statement(yy::location loc, expression* expr) : statement(loc), expression_(expr) {}
};

class scope final : public INode
{
private:
    std::vector<INode*> actions_;
    std::unordered_map<std::string, int> symtab_;
    scope *prev_;
public:
    int calc() override;
    void dump() const override;
    
    scope() = default;
    scope(scope* other) : actions_{}, symtab_(other->symtab_), prev_(other) {}

    void set_value(const std::string& name, int value)
    {
        symtab_[name] = value;
        return;
    }

    int get_value(const std::string& name)
    {
        return symtab_[name];
    }

    void add_action(INode* node)
    {
        actions_.push_back(node);
    }
};

class expression : public INode
{
protected:
    yy::location location_;
public:
    expression(yy::location loc) : location_(loc) {}
};

class number_expression final: public expression
{
private:
    int value_;
public:
    int calc() override;
    void dump() const override;

    number_expression(yy::location loc, int val) : expression(loc), value_(val) {}
};

class input_expression final : public expression
{
public:
    int calc() override;
    void dump() const override;

    input_expression(yy::location loc) : expression(loc) {}
};

class identificator_expression final : public expression
{
private:
    std::string name_;
    scope* scope_;
public:
    int calc() override;
    void dump() const override;

    identificator_expression(yy::location loc, const std::string& name, scope* scope) : expression(loc), name_(name), scope_(scope) {}

    const std::string& get_name() const noexcept
    {
        return name_;
    }

    void set_value(int val) noexcept
    {
        scope_->set_value(name_, val);
    }
};

class binary_op_expression final : public expression
{
private:
    expression* lhs_;
    BinOps operator_;
    expression* rhs_;
public:
    int calc() override;
    void dump() const override;

    binary_op_expression(yy::location loc, expression* lhs, BinOps oper, expression* rhs) : expression(loc), 
        lhs_(lhs), operator_(oper), rhs_(rhs) {}
};

}
