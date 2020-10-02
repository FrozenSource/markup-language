#pragma once
#include <Core.hpp>
#include <MarkupLanguage.h>

class cXmlNode : public cMarkupNode {
public:
    cXmlNode(const string& sTagName, const cMarkupNodeType& eNodeType);
    cXmlNode(const cXmlNode& oNode);

    cXmlNode& operator=(const cXmlNode& oNode);
protected:
};

class cXmlContainer : public cStringBuilder {
public:
    cXmlContainer(const cXmlContainer& oContainer);
    cXmlContainer() = default;
    
    cXmlContainer& operator=(const cXmlContainer& oContainer);

    void AddNode(const cXmlNode& oNode);
    cXmlNode& GetNode(size_t uiIndex);
    bool RemoveNode(size_t uiIndex);

    string ToString();
protected:
    std::vector<cXmlNode> paNodes;
};