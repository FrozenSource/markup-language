#pragma once
#include <string>
#include <sstream>

class cStringBuilder {
public:
    cStringBuilder() = default;
    cStringBuilder(const cStringBuilder& oBuilder) = delete;
    
    cStringBuilder& operator=(const cStringBuilder& oBuilder);

    void Append(const std::string& sValue);
    void AppendLine(const std::string& sValue);
    void AppendIndented(unsigned char iIndents, const std::string& sValue);
    void AppendIndentedLine(unsigned char iIndents, const std::string& sValue);
    std::string ToString();

protected:

    // Variables
    std::stringstream poBuffer;
};