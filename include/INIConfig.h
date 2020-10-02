#pragma once
#include <Core.hpp>
#include <StringBuilder.h>

class cINIGroup : protected cStringBuilder {
public:
    cINIGroup(const string& sGroupName);
    cINIGroup(const cINIGroup& oGroup);
    cINIGroup() = default;

    cINIGroup& operator =(const cINIGroup& oNode);

    bool HasProperty(const string& sKey);
    bool AddProperty(const string& sKey, const string& sValue);
    string GetProperty(const string& sKey) const;
    bool RemoveProperty(const string& sKey);

    void SetGroupName(const string& sValue);
    string GetGroupName() const;
    std::vector<std::pair<string, string>>& GetProperties();
    std::unordered_map<string, size_t>& GetPropertiesIndex();

    string ToString();
private:
    std::unordered_map<string, size_t> papProperties;
    std::vector<std::pair<string, string>> paProperties;
    string psGroupName = "";
};

class cINIContainer : protected cStringBuilder {
public:
    cINIContainer(const cINIContainer& oContainer);
    cINIContainer() = default;

    cINIContainer& operator =(const cINIContainer& oContainer);

    bool CreateGroup(const string& sGroupName, cINIGroup** pGroupOut);
    bool HasGroup(const string& sKey);
    bool AddGroup(const cINIGroup& oGroup);
    cINIGroup& GetGroup(const string& sGroupName);
    bool RemoveGroup(const string& psGroupName);
    std::unordered_map<string, cINIGroup>& GetGroups();

    void Clear();
    
    string ToString();
    bool FromString(const string& sStr);
private:
    std::unordered_map<string, cINIGroup> paGroups;
};