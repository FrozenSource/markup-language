#pragma once
#include <Core.hpp>

class cStringBuilder {
public:
    cStringBuilder() = default;
    cStringBuilder(const cStringBuilder& oBuilder) = delete;
    
    cStringBuilder& operator=(const cStringBuilder& oBuilder);

    void Append(const string& sValue);
    void AppendLine(const string& sValue);
    void AppendIndented(byte iIndents, const string& sValue);
    void AppendIndentedLine(byte iIndents, const string& sValue);
    string ToString();

protected:

    // Variables
    std::stringstream poBuffer;
};