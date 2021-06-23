#pragma once
#include <vector>
#include <unordered_map>
#include <StringBuilder.h>

class cINIGroup : protected cStringBuilder {
public:
    cINIGroup(const std::string& sGroupName);
    cINIGroup(const cINIGroup& oGroup);
    cINIGroup() = default;

    cINIGroup& operator =(const cINIGroup& oNode);

    bool HasProperty(const std::string& sKey);
    bool AddProperty(const std::string& sKey, const std::string& sValue);
    std::string GetProperty(const std::string& sKey) const;
    bool RemoveProperty(const std::string& sKey);

    void SetGroupName(const std::string& sValue);
    std::string GetGroupName() const;
    std::vector<std::pair<std::string, std::string>>& GetProperties();
    std::unordered_map<std::string, size_t>& GetPropertiesIndex();

    std::string ToString();
private:
    std::unordered_map<std::string, size_t> papProperties;
    std::vector<std::pair<std::string, std::string>> paProperties;
    std::string psGroupName;
};

class cINIContainer : protected cStringBuilder {
public:
    cINIContainer(const cINIContainer& oContainer);
    cINIContainer() = default;

    cINIContainer& operator =(const cINIContainer& oContainer);

    bool CreateGroup(const std::string& sGroupName, cINIGroup** pGroupOut);
    bool HasGroup(const std::string& sKey);
    bool AddGroup(const cINIGroup& oGroup);
    cINIGroup& GetGroup(const std::string& sGroupName);
    bool RemoveGroup(const std::string& psGroupName);
    std::unordered_map<std::string, cINIGroup>& GetGroups();

    void Clear();
    
    std::string ToString();
    bool FromString(const std::string& sStr);
private:
    std::unordered_map<std::string, cINIGroup> paGroups;
};