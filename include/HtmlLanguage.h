#pragma once
#include <Core.hpp>
#include <MarkupLanguage.h>

MAKE_ENUM_H(cHtmlNodeType,
    NONE,
    HTML,
    DOCTYPE,
    META,
    HEAD,
    BODY,
    TITLE,
    LINK,
    SCRIPT,
    STYLE,
    DIV,
    P,
    INPUT,
    OBJECT
);

const std::unordered_map<cHtmlNodeType, cMarkupNodeType> C_HTML_USES_NODE_CLOSE = {
    { cHtmlNodeType::NONE, cMarkupNodeType::NO_CLOSE },
    { cHtmlNodeType::HTML, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::DOCTYPE, cMarkupNodeType::NO_CLOSE },
    { cHtmlNodeType::META, cMarkupNodeType::NO_CLOSE },
    { cHtmlNodeType::HEAD, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::BODY, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::TITLE, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::LINK, cMarkupNodeType::SINGLE_CLOSE },
    { cHtmlNodeType::SCRIPT, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::STYLE, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::DIV, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::P, cMarkupNodeType::SECONDARY_CLOSE },
    { cHtmlNodeType::INPUT, cMarkupNodeType::NO_CLOSE },
    { cHtmlNodeType::OBJECT, cMarkupNodeType::SECONDARY_CLOSE }
};

class cHtmlNode : public cMarkupNode {
public:
    cHtmlNode(const cHtmlNodeType& eType);
    cHtmlNode(const cHtmlNode& oNode);
    cHtmlNode();

    cHtmlNode& operator=(const cHtmlNode& oNode);

    void SetHtmlNodeType(const cHtmlNodeType& eType);
    cHtmlNodeType GetHtmlNodeType() const;
protected:
    cHtmlNodeType peHtmlType = cHtmlNodeType::NONE;
};

class cHtmlContainer : public cStringBuilder {
public:
    cHtmlContainer(const cHtmlContainer& oContainer);
    cHtmlContainer() = default;

    cHtmlContainer& operator=(const cHtmlContainer& oContainer);

    void SetTitle(const string& sTitle);
    string GetTitle();

    void SetIcon(const string& sPath, uint uiWidth, uint uiHeight);
    void RemoveIcon();

    cHtmlNode& GetHead();
    void AddNodeToHead(const cHtmlNode& oNode);
    cHtmlNode& GetNodeOfHead(size_t uiIndex);
    bool RemoveNodeFromHead(size_t uiIndex);

    cHtmlNode& GetBody();
    void AddNodeToBody(const cHtmlNode& oNode);
    cHtmlNode& GetNodeOfBody(size_t uiIndex);
    bool RemoveNodeFromBody(size_t uiIndex);

    cHtmlNode CreateComment(const string& sText);
    cHtmlNode CreateJSInclude(const string& sPath);
    cHtmlNode CreateCSSInclude(const string& sPath);
    
    string ToString();
protected:
    cHtmlNode poHead = {cHtmlNodeType::HEAD};
    cHtmlNode poBody = {cHtmlNodeType::BODY};

    string psTitle = "%none%";

    string psIconPath = "";
    uint puiIconWidth = 0, puiIconHeight = 0;

    friend class cHtmlNode;
};