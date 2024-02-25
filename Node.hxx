#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "location.hh"
/* TO-DO:
- move methods implementation to cxx file
- add logical operations
- add template specialisation for binary operations
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

class expression : public INode
{
protected:
    yy::location location_;
public:
    expression(yy::location loc) : location_(loc) {}
    yy::location get_location() const;
};

class identificator_expression final : public expression
{
private:
    std::string name_;
    int value_;
public:
    int calc() override;
    void dump() const override;

    identificator_expression(yy::location loc, const std::string& name, int val = 0) : expression(loc), name_(name), value_(val) {}
    const std::string& get_name() const;
    void set_value(int val) noexcept;
};

class scope final : public INode
{
private:
    std::vector<INode*> actions_;
    std::unordered_map<std::string, identificator_expression*> symtab_;
    scope *prev_;
public:
    int calc() override;
    void dump() const override;
    
    scope() = default;
    scope(scope* other) : actions_{}, symtab_{other->symtab_}, prev_{other} {}
    
    void add_id(const std::string& name, identificator_expression* node);
    identificator_expression* contains(const std::string& name);
    void set_value(const std::string& name, int value); 
    identificator_expression* get_access(const yy::location& loc, const std::string& name);
    void add_action(INode* node);
    scope* reset_scope();
};

class if_statement final : public statement
{
private:
    expression* condition_;
    scope* body_;
public:
    int calc() override;
    void dump() const override;

    if_statement(yy::location loc, expression* cond, scope* body) : statement(loc), condition_(cond), body_(body) {}
};

class while_statement final : public statement
{
private:
    expression* condition_;
    scope* body_;
public:
    int calc() override;
    void dump() const override;

    while_statement(yy::location loc, expression* cond, scope* body) : statement(loc), condition_(cond), body_(body) {}
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
