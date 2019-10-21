/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2017, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstPragma.h
 *
 * Define the class AstPragma to update global options based on parameter.
 *
 ***********************************************************************/

#pragma once

#include "AstNode.h"
#include "AstTransformer.h"
#include <cassert>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace souffle {

class AstTranslationUnit;

/**
 * @class AstPragma
 * @brief Representation of a global option
 */
class AstPragma : public AstNode {
public:
    ~AstPragma() override = default;

    AstPragma() = default;

    AstPragma(std::string k, std::string v) : key(std::move(k)), value(std::move(v)) {}

    /** Obtains a list of all embedded child nodes */
    std::vector<const AstNode*> getChildNodes() const override {
        // type is just cached, not essential
        return std::vector<const AstNode*>();
    }

    /** Creates a clone of this AST sub-structure */
    AstPragma* clone() const override {
        auto res = new AstPragma();
        res->key = key;
        res->value = value;
        res->setSrcLoc(getSrcLoc());
        return res;
    }

    /** No nested nodes to apply to */
    void apply(const AstNodeMapper& mapper) override {}

    /** Output to a given output stream */
    void print(std::ostream& os) const override {
        os << ".pragma " << key << " " << value << "\n";
    }

    std::pair<std::string, std::string> getkvp() const {
        return std::pair<std::string, std::string>(key, value);
    }

    friend std::ostream& operator<<(std::ostream& out, const AstPragma& arg) {
        out << arg.key << " \"" << arg.value << "\"";
        return out;
    }

    /** Name of the key */
    std::string key;

    /** Value */
    std::string value;

protected:
    /** An internal function to determine equality to another node */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstPragma*>(&node));
        const auto& other = static_cast<const AstPragma&>(node);
        return other.key == key && other.value == value;
    }
};

class AstPragmaChecker : public AstTransformer {
public:
    std::string getName() const override {
        return "AstPragmaChecker";
    }

private:
    bool transform(AstTranslationUnit&) override;
};

}  // end of namespace souffle
