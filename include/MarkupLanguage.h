#pragma once
#include <Core.hpp>
#include <StringBuilder.h>

MAKE_ENUM(cMarkupNodeType,
    NO_CLOSE,
    SINGLE_CLOSE,
    SECONDARY_CLOSE
);

class cMarkupNode : protected cStringBuilder {
public:
    cMarkupNode(const string& sTagName, const cMarkupNodeType& eType);
    cMarkupNode(const cMarkupNode& oNode);
    cMarkupNode() = default;

    cMarkupNode& operator=(const cMarkupNode& oNode);

    void SetTagName(const string& sTagName);
    string GetTagName();

    void SetNodeType(const cMarkupNodeType& eType);
    cMarkupNodeType GetNodeType();

    void SetValue(const string& sValue);
    string GetValue();

    void SetNodePrefix(const string& sPrefix);
    string GetNodePrefix();

    void SetNodePostfix(const string& sPostfix);
    string GetNodePostfix();

    void SetPrependValue(const bool& bPrepend);
    bool GetPrependValue();

    void SetPrependAdditionalChildren(const bool& bPrepend);
    bool GetPrependAdditionalChildren();

    bool AddAttribute(const string& sKey, const string& sValue);
    bool AddAttribute(const string& sKey);
    string GetAttribute(const string& sKey);
    bool SetAttributeValue(const string& sKey, const string& sValue);
    bool RemoveAttribute(const string& sKey);

    size_t AddChild(const cMarkupNode& oNode);
    bool RemoveChild(cMarkupNode* pNode);
    bool RemoveChild(size_t uiIndex);
    cMarkupNode& GetChild(size_t uiIndex);

    virtual string ToString(std::vector<cMarkupNode> aAdditionalChildNodes = {});
protected:
    std::unordered_map<string, string> paAttributes;
    std::vector<cMarkupNode> paChildren;
    
    cMarkupNodeType peType = cMarkupNodeType::NO_CLOSE;

    string psTagName = "";

    string psValue = "";
    bool pbPrependValue = false;
    bool pbPrependAdditionalChildren = false;

    string psNodePrefix = "";
    string psNodePostfix = "";
};