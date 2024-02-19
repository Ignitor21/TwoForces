#pragma once

#include <string>
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

class output_statement final: public statement
{
private:
    INode* expression_;
public:
    int calc() override;
    void dump() const override;

    output_statement(yy::location loc, INode* expr) : statement(loc), expression_(expr) {}
};

class scope final : public INode
{
private:
    std::vector<INode*> statements_;
    std::unordered_map<std::string, int> symtab_;
    scope *prev_;
public:
    int calc() override;
    void dump() const override;
    
    scope() = default;
    scope(scope* other) : statements_{}, symtab_(other->symtab_), prev_(other) {}

    void add_action(INode* node)
    {
        statements_.push_back(node);
    }
};

class expression : public INode
{
protected:
    yy::location location_;
    int value_;
public:
    expression(yy::location loc, int val = 0) : location_(loc), value_(val) {}
};

class number_expression final: public expression
{
public:
    int calc() override;
    void dump() const override;

    number_expression(yy::location loc, int val) : expression(loc, val) {}
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
public:
    int calc() override;
    void dump() const override;

    identificator_expression(yy::location loc, const std::string& name) : expression(loc), name_(name) {}
};

class binary_op_expression final : public expression
{
private:
    INode* lhs_;
    BinOps operator_;
    INode* rhs_;
public:
    int calc() override;
    void dump() const override;

    binary_op_expression(yy::location loc, INode* lhs, BinOps oper, INode* rhs) : expression(loc), 
        lhs_(lhs), operator_(oper), rhs_(rhs) {}
};

}
