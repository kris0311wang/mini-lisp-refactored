//
// Created by 王愉博 on 24-5-23.
//

#ifndef MINI_LISP_VALUE_H
#define MINI_LISP_VALUE_H

#include<iostream>
#include<memory>
#include<string>
#include <utility>
#include<vector>
#include<optional>

class Value : public std::enable_shared_from_this<Value> {
public:

    virtual std::string internalToString() const;

    virtual std::string toString() const = 0;

    virtual ~Value() = default;

    bool isNil() const;

    bool isSymbol() const;

    virtual std::optional<std::string> asSymbol() const;

    bool isNum() const;

    bool isBool() const;

    bool isString() const;

    bool isPair() const;

    bool isSelfEvaluating() const;

    virtual std::vector<std::shared_ptr<Value>> toVector();

    virtual std::shared_ptr<Value> toQuote();

    virtual std::optional<double> asNumber() const;
};

using ValuePtr = std::shared_ptr<Value>;

class BooleanValue : public Value {
    bool value;
public:
    explicit BooleanValue(const bool &value) : value(value) {}

    std::string toString() const override;
};

class NumericValue : public Value {
    double value;
public:
    explicit NumericValue(const double &value) : value(value) {}

    bool isInt() const;

    std::string toString() const override;

    double getValue() const;
};

class NilValue : public Value {
public:
    std::string internalToString() const override;

    std::string toString() const override;

    std::shared_ptr<Value> toQuote () override;
};

class PairValue : public Value {
    ValuePtr car;
    ValuePtr cdr;
public:
    explicit PairValue(const ValuePtr &car, const ValuePtr &cdr) : car(car->shared_from_this()),
                                                                   cdr(cdr->shared_from_this()) {}

    std::string internalToString() const override;

    std::string toString() const override;

    ValuePtr getCar() const;

    ValuePtr getCdr() const;

    std::vector<ValuePtr> toVector() override;

    std::shared_ptr<Value> toQuote() override;
};

class SymbolValue : public Value {
    std::string value;
public:
    explicit SymbolValue(std::string value) : value(std::move(value)) {}

    std::string toString() const override;
};

class StringValue : public Value {
    std::string value;
public:
    explicit StringValue(std::string value) : value(std::move(value)) {}

    std::string toString() const override;

    std::string internalToString() const override;
};

using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr> &);//内建函数的函数指针类型
class BuiltinProcValue : public Value {
public:
    std::string name;
    BuiltinFuncType *func;//函数指针
    BuiltinProcValue(std::string name, BuiltinFuncType func) : name(std::move(name)), func(func) {}//构造函数
    std::shared_ptr<Value> toQuote() override;

    std::string toString() const override;
};

#endif //MINI_LISP_VALUE_H
