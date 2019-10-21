/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstIO.h
 *
 * Define the classes representing IO operations.
 *
 ***********************************************************************/

#pragma once

#include "AstNode.h"
#include "AstRelationIdentifier.h"

#include <map>
#include <string>

namespace souffle {

/**
 * @class AstIO
 * @brief Intermediate representation of IO operations.
 */
class AstIO : public AstNode {
public:
    AstIO() = default;
    ~AstIO() override = default;

    /** Obtains a list of all embedded child nodes */
    std::vector<const AstNode*> getChildNodes() const override {
        // type is just cached, not essential
        return std::vector<const AstNode*>();
    }

    /** Creates a clone of this AST sub-structure */
    AstIO* clone() const override {
        auto res = new AstIO();
        res->names = names;
        res->kvps = kvps;
        res->setSrcLoc(getSrcLoc());
        return res;
    }

    /** No nested nodes to apply to */
    void apply(const AstNodeMapper& /*mapper*/) override {}

    /** Output to a given output stream */
    void print(std::ostream& os) const override {
        bool first = true;
        for (auto& relationName : getNames()) {
            if (first) {
                first = false;
            } else {
                os << ',';
            }
            os << relationName;
        }
        if (kvps.empty()) {
            return;
        }
        os << "(";
        first = true;
        for (auto& pair : kvps) {
            if (first) {
                first = false;
            } else {
                os << ',';
            }
            os << pair.first << "=\"" << pair.second << "\"";
        }
        os << ')';
    }

    /** Return the name of this kvp map */
    const AstRelationIdentifier& getName() const {
        return *names.begin();
    }

    /** Return the names of this kvp map */
    const std::set<AstRelationIdentifier>& getNames() const {
        return names;
    }

    /** Set kvp map name */
    void addName(const AstRelationIdentifier& name) {
        names.insert(name);
    }
    /** Set kvp map name */
    void setName(const AstRelationIdentifier& name) {
        names.clear();
        names.insert(name);
    }

    void addKVP(const std::string& key, const std::string& value) {
        kvps[key] = unescape(value);
    }

    const std::map<std::string, std::string>& getIODirectiveMap() const {
        return kvps;
    }

protected:
    AstIO(const AstIO& io) : names(io.names), kvps(io.kvps) {}

    /** An internal function to determine equality to another node */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstIO*>(&node));
        const auto& other = static_cast<const AstIO&>(node);
        return other.names == names && other.kvps == kvps;
    }

    std::string unescape(const std::string& inputString) const {
        std::string unescaped = unescape(inputString, "\\\"", "\"");
        unescaped = unescape(unescaped, "\\t", "\t");
        unescaped = unescape(unescaped, "\\r", "\r");
        unescaped = unescape(unescaped, "\\n", "\n");
        return unescaped;
    }

    std::string unescape(
            const std::string& inputString, const std::string& needle, const std::string& replacement) const {
        std::string result = inputString;
        size_t pos = 0;
        while ((pos = result.find(needle, pos)) != std::string::npos) {
            result = result.replace(pos, needle.length(), replacement);
            pos += replacement.length();
        }
        return result;
    }
    /** Name of the kvp */
    std::set<AstRelationIdentifier> names;

    /** kvp map */
    std::map<std::string, std::string> kvps;
};

/**
 * @class AstStore
 * @brief Intermediate representation of a store operation.
 */
class AstStore : public AstIO {
public:
    AstStore(const AstIO& io) : AstIO(io) {
        setSrcLoc(io.getSrcLoc());
    }
    AstStore() = default;
    ~AstStore() override = default;

    /** Output to a given output stream */
    void print(std::ostream& os) const override {
        os << ".output ";
        AstIO::print(os);
    }

    /** An internal function to determine equality to another node */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstStore*>(&node));
        const auto& other = static_cast<const AstStore&>(node);
        return other.names == names && other.kvps == kvps;
    }

    /** Creates a clone of this AST sub-structure */
    AstStore* clone() const override {
        auto res = new AstStore();
        res->names = names;
        res->kvps = kvps;
        res->setSrcLoc(getSrcLoc());
        return res;
    }
};

/**
 * @class AstLoad
 * @brief Intermediate representation of a store operation.
 */
class AstLoad : public AstIO {
public:
    AstLoad(const AstIO& io) : AstIO(io) {
        setSrcLoc(io.getSrcLoc());
    }
    AstLoad() = default;
    ~AstLoad() override = default;

    /** Output to a given output stream */
    void print(std::ostream& os) const override {
        os << ".output ";
        AstIO::print(os);
    }

    /** An internal function to determine equality to another node */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstLoad*>(&node));
        const auto& other = static_cast<const AstLoad&>(node);
        return other.names == names && other.kvps == kvps;
    }

    /** Creates a clone of this AST sub-structure */
    AstLoad* clone() const override {
        auto res = new AstLoad();
        res->names = names;
        res->kvps = kvps;
        res->setSrcLoc(getSrcLoc());
        return res;
    }
};

/**
 * @class AstPrintSize
 * @brief Intermediate representation of a summary store operation.
 */
class AstPrintSize : public AstStore {
public:
    AstPrintSize(const AstIO& io) : AstStore(io) {
        addKVP("IO", "stdoutprintsize");
    }
    AstPrintSize() {
        addKVP("IO", "stdoutprintsize");
    }
    ~AstPrintSize() override = default;

    /** Output to a given output stream */
    void print(std::ostream& os) const override {
        os << ".printsize ";
        AstIO::print(os);
    }

    /** An internal function to determine equality to another node */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstPrintSize*>(&node));
        const auto& other = static_cast<const AstPrintSize&>(node);
        return other.names == names;
    }

    /** Creates a clone of this AST sub-structure */
    AstPrintSize* clone() const override {
        auto res = new AstPrintSize();
        res->names = names;
        res->kvps = kvps;
        res->setSrcLoc(getSrcLoc());
        return res;
    }
};

}  // end of namespace souffle
