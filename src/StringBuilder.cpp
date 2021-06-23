#include <StringBuilder.h>

cStringBuilder& cStringBuilder::operator=(const cStringBuilder& oBuilder) {
    this->poBuffer << oBuilder.poBuffer.str();
    return *this;
}

void cStringBuilder::Append(const std::string& sValue) {
    this->poBuffer << sValue;
}

void cStringBuilder::AppendLine(const std::string& sValue) {
    this->poBuffer << sValue << "\n";
}

void cStringBuilder::AppendIndented(unsigned char iIndents, const std::string& sValue) {
    for (unsigned char i = 0; i < iIndents; i++) this->poBuffer << "\t";
    this->Append(sValue);
}

void cStringBuilder::AppendIndentedLine(unsigned char iIndents, const std::string& sValue) {
    for (unsigned char i = 0; i < iIndents; i++) this->poBuffer << "\t";
    this->AppendLine(sValue);
}

std::string cStringBuilder::ToString() {
    std::string sTotal = this->poBuffer.str();
    this->poBuffer.clear();
    return sTotal;
}