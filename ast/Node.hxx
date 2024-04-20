#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include "location.hh"

namespace frontend
{

enum class BinOps
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,

    LESS,
    GREATER,
    EQ,
    NEQ,
    LESSEQ,
    GREATEREQ,
    AND,
    OR
};

enum class UnOps
{
    UPLUS,
    UMINUS,
    NOT
};

struct INode
{
    virtual int calc() = 0;
    virtual void dump() const = 0;
    virtual ~INode() {}
};

class node_with_location : public INode
{
protected:
    yy::location location_;
public:
    node_with_location(yy::location loc) : location_(loc) {}
};

class statement : public node_with_location
{
public:
    statement(yy::location loc) : node_with_location(loc) {}
};

class expression : public node_with_location
{
public:
    expression(yy::location loc) : node_with_location(loc) {}
    yy::location get_location() const;
};

class output_statement final: public statement
{
private:
    expression* expression_;
public:
    int calc() override;
    void dump() const override;

    output_statement(yy::location loc, expression* expr) : statement(loc), expression_(expr) {}
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
    std::string_view get_name() const;
    void set_value(int val) noexcept;
};

class scope final : public INode
{
private:
    std::vector<INode*> actions_;
    std::unordered_map<std::string_view, identificator_expression*> symtab_;
    scope *prev_;
public:
    int calc() override;
    void dump() const override;
    
    scope() = default;
    scope(scope* other) : actions_{}, symtab_{other->symtab_}, prev_{other} {}
    
    void add_id(std::string_view name, identificator_expression* node);
    identificator_expression* get(std::string_view name) const;
    void set_value(std::string_view name, int value); 
    identificator_expression* get_variable(const yy::location& loc, std::string_view name);
    void add_action(INode* node);
    scope* reset_scope();
};

class if_statement final : public statement
{
private:
    expression* condition_;
    INode* true_body_;
    INode* false_body_;
public:
    int calc() override;
    void dump() const override;

    if_statement(yy::location loc, expression* cond, INode* tbody, INode* fbody = nullptr) : statement(loc), condition_(cond), true_body_(tbody), false_body_(fbody) {}
};

class while_statement final : public statement
{
private:
    expression* condition_;
    INode* body_;
public:
    int calc() override;
    void dump() const override;

    while_statement(yy::location loc, expression* cond, INode* body) : statement(loc), condition_(cond), body_(body) {}
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

class assignment_expression final : public expression
{
private:
    identificator_expression* lhs_;
    expression* rhs_;
public:
    int calc() override;
    void dump() const override;

    assignment_expression(yy::location loc, identificator_expression* lhs, expression* rhs, scope* cur_scope);
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

class unary_op_expression final : public expression
{
private:
    UnOps operator_;
    expression* expression_;
public:
    int calc() override;
    void dump() const override;

    unary_op_expression(yy::location loc, UnOps oper, expression* expr) : expression(loc), 
        operator_(oper), expression_(expr) {}
};

}
