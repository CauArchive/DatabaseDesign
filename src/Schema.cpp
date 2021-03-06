//
// Created by woodi on 2022/06/01.
//

#include "Schema.h"

#include <stdexcept>
#include <sstream>

static std::string type(const Schema::Relation::Attribute &attr) {
    Types::Tag type = attr.type;
    switch (type) {
        case Types::Tag::Integer:
            return "Integer";
            /*case Types::Tag::Numeric: {
               std::stringstream ss;
               ss << "Numeric(" << attr.len1 << ", " << attr.len2 << ")";
               return ss.str();
            }*/
        case Types::Tag::Char: {
            std::stringstream ss;
            ss << "Char(" << attr.len << ")";
            return ss.str();
        }
        default:
            throw std::logic_error("Unknown type");
    }
}

std::string Schema::toString() const {
    std::stringstream out;
    for (const Schema::Relation &rel: relations) {
        out << rel.name << std::endl;
        out << "\tPrimary Key:";
        for (unsigned keyId: rel.primaryKey)
            out << ' ' << rel.attributes[keyId].name;
        out << std::endl;
        for (const auto &attr: rel.attributes)
            out << '\t' << attr.name << '\t' << type(attr) << (attr.notNull ? " not null" : "") << std::endl;
    }
    return out.str();
}
