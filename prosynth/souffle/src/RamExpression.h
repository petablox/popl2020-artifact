/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file RamExpression.h
 *
 * Defines a class for evaluating values in the Relational Algebra Machine
 *
 ************************************************************************/

#pragma once

#include "FunctorOps.h"
#include "RamNode.h"
#include "RamRelation.h"
#include "SymbolTable.h"
#include "Util.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <string>

#include <cstdlib>
#include <utility>

namespace souffle {

/**
 * @class RamExpression
 * @brief Abstract class for describing scalar values in RAM
 */
class RamExpression : public RamNode {
public:
    RamExpression* clone() const override = 0;
};

/**
 * @class RamAbstractOperator
 * @brief Abstract class for an operator/functor
 */
class RamAbstractOperator : public RamExpression {
public:
    RamAbstractOperator(std::vector<std::unique_ptr<RamExpression>> args) : arguments(std::move(args)) {}

    /** @brief Get argument values */
    std::vector<RamExpression*> getArguments() const {
        return toPtrVector(arguments);
    }

    /** @brief Get i-th argument value */
    const RamExpression& getArgument(size_t i) const {
        assert(i >= 0 && i < arguments.size() && "argument index out of bounds");
        return *arguments[i];
    }

    /** @brief Get number of arguments */
    size_t getArgCount() const {
        return arguments.size();
    }

    std::vector<const RamNode*> getChildNodes() const override {
        std::vector<const RamNode*> res;
        for (const auto& cur : arguments) {
            res.push_back(cur.get());
        }
        return res;
    }

    void apply(const RamNodeMapper& map) override {
        for (auto& arg : arguments) {
            arg = map(std::move(arg));
        }
    }

protected:
    /** Arguments of user defined operator */
    std::vector<std::unique_ptr<RamExpression>> arguments;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamAbstractOperator*>(&node));
        const auto& other = static_cast<const RamAbstractOperator&>(node);
        return equal_targets(arguments, other.arguments);
    }
};

/**
 * @class RamIntrinsicOperator
 * @brief Operator that represents an intrinsic (built-in) functor
 */
class RamIntrinsicOperator : public RamAbstractOperator {
public:
    template <typename... Args>
    RamIntrinsicOperator(FunctorOp op, Args... args)
            : RamAbstractOperator({std::move(args)...}), operation(op) {}

    RamIntrinsicOperator(FunctorOp op, std::vector<std::unique_ptr<RamExpression>> args)
            : RamAbstractOperator(std::move(args)), operation(op) {}

    void print(std::ostream& os) const override {
        if (isInfixFunctorOp(operation)) {
            os << "(";
            os << join(arguments, getSymbolForFunctorOp(operation),
                    print_deref<std::unique_ptr<RamExpression>>());
            os << ")";
        } else {
            os << getSymbolForFunctorOp(operation);
            os << "(";
            os << join(arguments, ",", print_deref<std::unique_ptr<RamExpression>>());
            os << ")";
        }
    }

    /** @brief Get operator symbol */
    FunctorOp getOperator() const {
        return operation;
    }

    RamIntrinsicOperator* clone() const override {
        std::vector<std::unique_ptr<RamExpression>> argsCopy;
        for (auto& arg : arguments) {
            argsCopy.emplace_back(arg->clone());
        }
        return new RamIntrinsicOperator(operation, std::move(argsCopy));
    }

protected:
    /** Operation symbol */
    const FunctorOp operation;

    bool equal(const RamNode& node) const override {
        const auto& other = static_cast<const RamIntrinsicOperator&>(node);
        return RamAbstractOperator::equal(node) && getOperator() == other.getOperator();
    }
};

/**
 * @class RamUserDefinedOperator
 * @brief Operator that represents an extrinsic (user-defined) functor
 */
class RamUserDefinedOperator : public RamAbstractOperator {
public:
    RamUserDefinedOperator(std::string n, std::string t, std::vector<std::unique_ptr<RamExpression>> args)
            : RamAbstractOperator(std::move(args)), name(std::move(n)), type(std::move(t)) {}

    void print(std::ostream& os) const override {
        os << "@" << name << "_" << type << "(";
        os << join(arguments, ",",
                [](std::ostream& out, const std::unique_ptr<RamExpression>& arg) { out << *arg; });
        os << ")";
    }

    /** @brief Get operator name */
    const std::string& getName() const {
        return name;
    }

    /** @brief Get types of arguments */
    const std::string& getType() const {
        return type;
    }

    RamUserDefinedOperator* clone() const override {
        auto* res = new RamUserDefinedOperator(name, type, {});
        for (auto& cur : arguments) {
            RamExpression* arg = cur->clone();
            res->arguments.emplace_back(arg);
        }
        return res;
    }

protected:
    /** Name of user-defined operator */
    const std::string name;

    /** Argument types */
    const std::string type;

    bool equal(const RamNode& node) const override {
        const auto& other = static_cast<const RamUserDefinedOperator&>(node);
        return RamAbstractOperator::equal(node) && name == other.name && type == other.type;
    }
};

/**
 * @class RamTupleElement
 * @brief Access element from the current tuple in a tuple environment
 *
 * In the following example, the tuple element t0.1 is accessed:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * IF t0.1 in A
 * 	...
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class RamTupleElement : public RamExpression {
public:
    RamTupleElement(size_t ident, size_t elem, std::unique_ptr<RamRelationReference> relRef = nullptr)
            : identifier(ident), element(elem) {}

    void print(std::ostream& os) const override {
        os << "t" << identifier << "." << element;
    }

    /** @brief Get identifier */
    int getTupleId() const {
        return identifier;
    }

    /** @brief Get element */
    size_t getElement() const {
        return element;
    }

    RamTupleElement* clone() const override {
        return new RamTupleElement(identifier, element);
    }

protected:
    /** Identifier for the tuple */
    const size_t identifier;

    /** Element number */
    const size_t element;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamTupleElement*>(&node));
        const auto& other = static_cast<const RamTupleElement&>(node);
        return getTupleId() == other.getTupleId() && getElement() == other.getElement();
    }
};

/**
 * @class RamNumber
 * @brief Represents a number constant
 *
 * For example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * number(5)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class RamNumber : public RamExpression {
public:
    RamNumber(RamDomain c) : constant(c) {}

    /** @brief Get constant */
    RamDomain getConstant() const {
        return constant;
    }

    void print(std::ostream& os) const override {
        os << "number(" << constant << ")";
    }

    /** Create clone */
    RamNumber* clone() const override {
        return new RamNumber(constant);
    }

protected:
    /** Constant value */
    const RamDomain constant;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamNumber*>(&node));
        const auto& other = static_cast<const RamNumber&>(node);
        return getConstant() == other.getConstant();
    }
};

/**
 * @class RamAutoIncrement
 * @brief Increment a counter and return its value.
 *
 * Note that there exists a single counter only.
 */
class RamAutoIncrement : public RamExpression {
public:
    void print(std::ostream& os) const override {
        os << "autoinc()";
    }

    RamAutoIncrement* clone() const override {
        return new RamAutoIncrement();
    }
};

/**
 * @class RamUndefValue
 * @brief An undefined expression
 *
 * Output is ⊥
 */
class RamUndefValue : public RamExpression {
public:
    void print(std::ostream& os) const override {
        os << "⊥";
    }

    RamUndefValue* clone() const override {
        return new RamUndefValue();
    }
};

/** @brief Determines if an expression is undefined */
inline bool isRamUndefValue(const RamExpression* expr) {
    return nullptr != dynamic_cast<const RamUndefValue*>(expr);
}

/**
 * @class RamPackRecord
 * @brief Packs a record's arguments into a reference
 */
class RamPackRecord : public RamExpression {
public:
    RamPackRecord(std::vector<std::unique_ptr<RamExpression>> args) : arguments(std::move(args)) {}

    /** @brief Get record arguments */
    std::vector<RamExpression*> getArguments() const {
        return toPtrVector(arguments);
    }

    void print(std::ostream& os) const override {
        os << "[" << join(arguments, ",", [](std::ostream& out, const std::unique_ptr<RamExpression>& arg) {
            out << *arg;
        }) << "]";
    }

    std::vector<const RamNode*> getChildNodes() const override {
        std::vector<const RamNode*> res;
        for (const auto& cur : arguments) {
            res.push_back(cur.get());
        }
        return res;
    }

    RamPackRecord* clone() const override {
        auto* res = new RamPackRecord({});
        for (auto& cur : arguments) {
            res->arguments.emplace_back(cur->clone());
        }
        return res;
    }

    void apply(const RamNodeMapper& map) override {
        for (auto& arg : arguments) {
            arg = map(std::move(arg));
        }
    }

protected:
    /** Arguments */
    std::vector<std::unique_ptr<RamExpression>> arguments;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamPackRecord*>(&node));
        const auto& other = static_cast<const RamPackRecord&>(node);
        return equal_targets(arguments, other.arguments);
    }
};

/**
 * @class RamSubroutineArgument
 * @brief Access argument of a subroutine
 *
 * Arguments are number from zero 0 to n-1
 * where n is the number of arguments of the
 * subroutine.
 */
class RamSubroutineArgument : public RamExpression {
public:
    RamSubroutineArgument(size_t number) : number(number) {}

    /** @brief Get argument */
    size_t getArgument() const {
        return number;
    }

    void print(std::ostream& os) const override {
        os << "argument(" << number << ")";
    }

    RamSubroutineArgument* clone() const override {
        return new RamSubroutineArgument(number);
    }

protected:
    /** Argument number */
    const size_t number;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamSubroutineArgument*>(&node));
        const auto& other = static_cast<const RamSubroutineArgument&>(node);
        return getArgument() == other.getArgument();
    }
};

}  // end of namespace souffle
