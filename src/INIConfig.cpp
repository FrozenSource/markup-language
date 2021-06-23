#include <INIConfig.h>

#include <algorithm>

cINIGroup::cINIGroup(const std::string& sGroupName) {
    this->SetGroupName(sGroupName);
}

cINIGroup::cINIGroup::cINIGroup(const cINIGroup& oGroup) {
    *this = oGroup;
}

cINIGroup& cINIGroup::operator=(const cINIGroup& oNode) {
    cStringBuilder::operator=(oNode);
    this->paProperties = oNode.paProperties;
    this->SetGroupName(oNode.psGroupName);
    return *this;
}

bool cINIGroup::AddProperty(const std::string& sKey, const std::string& sValue) {
    if (this->papProperties.find(sKey) != this->papProperties.end()) return false;
    this->paProperties.push_back({sKey, sValue});
    this->papProperties.try_emplace(sKey, this->paProperties.size() - 1);
    return true;
}

std::string cINIGroup::GetProperty(const std::string& sKey) const {
    if (this->papProperties.find(sKey) == this->papProperties.end()) return "";
    return this->paProperties.at(this->papProperties.at(sKey)).second;
}

bool cINIGroup::RemoveProperty(const std::string& sKey) {
    if (this->papProperties.find(sKey) == this->papProperties.end()) return false;
    this->paProperties.erase(this->paProperties.begin() + this->papProperties.at(sKey));
    this->papProperties.erase(sKey);
    return true;
}

void cINIGroup::SetGroupName(const std::string& sValue) {
    this->psGroupName = sValue;
}

std::string cINIGroup::GetGroupName() const {
    return this->psGroupName;
}

std::string cINIGroup::ToString() {
    Append("[");
    Append(this->GetGroupName());
    Append("]\n");
    for (auto& [sKey, sValue] : this->paProperties) {
        Append(sKey);
        Append("=");
        Append(sValue);
        Append("\n");
    }
    return cStringBuilder::ToString();
}

std::vector<std::pair<std::string, std::string>>& cINIGroup::GetProperties() {
    return this->paProperties;
}

std::unordered_map<std::string, size_t>& cINIGroup::GetPropertiesIndex() {
    return this->papProperties;
}

bool cINIGroup::HasProperty(const std::string& sKey) {
    return this->papProperties.find(sKey) != this->papProperties.end();
}

cINIContainer::cINIContainer(const cINIContainer& oContainer) {
    *this = oContainer;
}

cINIContainer& cINIContainer::operator=(const cINIContainer& oContainer) {
    cStringBuilder::operator=(oContainer);
    this->paGroups = oContainer.paGroups;
    return *this;
}

bool cINIContainer::CreateGroup(const std::string& sGroupName, cINIGroup** pGroupOut) {
    if (!AddGroup({sGroupName})) return false;
    *pGroupOut = &GetGroup(sGroupName);
    return true;
}

bool cINIContainer::AddGroup(const cINIGroup& oGroup) {
    std::string sGroupName = oGroup.GetGroupName();
    if (this->paGroups.find(sGroupName) != this->paGroups.end()) return false;
    this->paGroups.insert({sGroupName, oGroup});
    return true;
}

cINIGroup& cINIContainer::GetGroup(const std::string& sGroupName) {
    if (this->paGroups.find(sGroupName) == this->paGroups.end()) throw std::runtime_error("no group with that name.");
    return this->paGroups.at(sGroupName);
}

bool cINIContainer::RemoveGroup(const std::string& sGroupName) {
    if (this->paGroups.find(sGroupName) == this->paGroups.end()) return false;
    this->paGroups.erase(sGroupName);
    return true;
}

std::string cINIContainer::ToString() {
    for (auto& [sName, oGroup] : this->paGroups)
        Append(oGroup.ToString());
    return cStringBuilder::ToString();
}

void cINIContainer::Clear() {
    this->paGroups.clear();
    this->poBuffer.clear();
}

void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}
std::vector<std::string> Split(std::string str, const std::string& delim) noexcept {
    std::vector<std::string> result;
    while (str.size()) {
        size_t index = str.find(delim);
        if (index != std::string::npos) {
            result.emplace_back(str.substr(0, index));
            str = str.substr(index + delim.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(str);
            str.clear();
        }
    }
    return result;
}

bool cINIContainer::FromString(const std::string& sStr) {
    Clear();
    bool bWindowsStyle = (sStr.find("\r\n") != std::string::npos);
    auto aLines = Split(sStr, bWindowsStyle ? "\r\n" : "\n");

    cINIGroup* pGroup = nullptr;
    for (auto& sLine : aLines) {
        if (sLine.size() == 0 || sLine == (bWindowsStyle ? "\r\n" : "\n")) continue;
        size_t uiOpenBracket = sLine.find("[");
        size_t uiCloseBracket = sLine.find("]");
        size_t uiEqual = sLine.find("=");
        if (uiOpenBracket == 0) {
            if (uiCloseBracket == std::string::npos) {
                Clear();
                return false;
            }
            std::string sName = sLine.substr(1, uiCloseBracket - 1);
            if (this->paGroups.find(sName) != this->paGroups.end()) {
                Clear();
                return false;
            }
            this->paGroups.insert({sName, {sName}});
            pGroup = &(this->paGroups[sName]);
        } else if (uiEqual != std::string::npos) {
            if (!pGroup) {
                Clear();
                return false;
            }
            std::string sKey = sLine.substr(0, uiEqual);
            std::string sValue = sLine.substr(uiEqual + 1, sLine.size() - uiEqual - 1);
            trim(sKey);
            trim(sValue);
            pGroup->AddProperty(sKey, sValue);
        } else {
            Clear();
            return false;
        }
    }
    return true;
}

std::unordered_map<std::string, cINIGroup>& cINIContainer::GetGroups() {
    return this->paGroups;
}

bool cINIContainer::HasGroup(const std::string& sKey) {
    return this->paGroups.find(sKey) != this->paGroups.end();
}