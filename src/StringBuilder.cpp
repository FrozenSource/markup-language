#include <StringBuilder.h>

cStringBuilder& cStringBuilder::operator=(const cStringBuilder& oBuilder) {
    this->poBuffer << oBuilder.poBuffer.str();
    return *this;
}

void cStringBuilder::Append(const string& sValue) {
    this->poBuffer << sValue;
}

void cStringBuilder::AppendLine(const string& sValue) {
    this->poBuffer << sValue << "\n";
}

void cStringBuilder::AppendIndented(byte iIndents, const string& sValue) {
    for (byte i = 0; i < iIndents; i++) this->poBuffer << "\t";
    this->Append(sValue);
}

void cStringBuilder::AppendIndentedLine(byte iIndents, const string& sValue) {
    for (byte i = 0; i < iIndents; i++) this->poBuffer << "\t";
    this->AppendLine(sValue);
}

string cStringBuilder::ToString() {
    string sTotal = this->poBuffer.str();
    this->poBuffer.clear();
    return sTotal;
}