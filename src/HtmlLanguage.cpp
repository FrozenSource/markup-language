#include <HtmlLanguage.h>

MAKE_ENUM_CPP(cHtmlNodeType,
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

cHtmlNode::cHtmlNode(const cHtmlNodeType& eType) {
    this->SetHtmlNodeType(eType);
}

cHtmlNode::cHtmlNode(const cHtmlNode& oNode) {
    *this = oNode;
}

cHtmlNode::cHtmlNode() {
    this->SetHtmlNodeType(cHtmlNodeType::NONE);
}

void cHtmlNode::SetHtmlNodeType(const cHtmlNodeType& eType) {
    this->SetTagName(ToLowercaseCP(EnumToString(eType)));
    this->SetNodeType(C_HTML_USES_NODE_CLOSE.at(eType));
    this->peHtmlType = eType;
}

cHtmlNodeType cHtmlNode::GetHtmlNodeType() const {
    return this->peHtmlType;
}

cHtmlNode& cHtmlNode::operator=(const cHtmlNode& oNode) {
    this->SetHtmlNodeType(oNode.GetHtmlNodeType());
    cMarkupNode::operator=(oNode);
    return *this;
}

cHtmlContainer::cHtmlContainer(const cHtmlContainer& oContainer) {
    *this = oContainer;
}

cHtmlContainer& cHtmlContainer::operator=(const cHtmlContainer& oContainer) {
    cStringBuilder::operator=(oContainer);
    this->poBody = oContainer.poBody;
    this->poHead = oContainer.poHead;
    this->psTitle = oContainer.psTitle;
    this->psIconPath = oContainer.psIconPath;
    this->puiIconHeight = oContainer.puiIconHeight;
    this->puiIconWidth = oContainer.puiIconWidth;
    return *this;
}

void cHtmlContainer::SetTitle(const string& sTitle) {
    this->psTitle = sTitle;
}

string cHtmlContainer::GetTitle() {
    return this->psTitle;
}

void cHtmlContainer::SetIcon(const string& sPath, uint uiWidth, uint uiHeight) {
    this->psIconPath = sPath;
    this->puiIconWidth = uiWidth;
    this->puiIconHeight = uiHeight;
}

void cHtmlContainer::RemoveIcon() {
    this->psIconPath = "%none%";
    this->puiIconWidth = 0;
    this->puiIconHeight = 0;
}

cHtmlNode& cHtmlContainer::GetHead() {
    return this->poHead;
}

void cHtmlContainer::AddNodeToHead(const cHtmlNode& oNode) {
    this->poHead.AddChild(oNode);
}

cHtmlNode& cHtmlContainer::GetNodeOfHead(size_t uiIndex) {
    return (cHtmlNode&) this->poHead.GetChild(uiIndex);
}

bool cHtmlContainer::RemoveNodeFromHead(size_t uiIndex) {
    return this->poHead.RemoveChild(uiIndex);
}

cHtmlNode& cHtmlContainer::GetBody() {
    return this->poBody;
}

void cHtmlContainer::AddNodeToBody(const cHtmlNode& oNode) {
    this->poBody.AddChild(oNode);
}

cHtmlNode& cHtmlContainer::GetNodeOfBody(size_t uiIndex) {
    return (cHtmlNode&) this->poBody.GetChild(uiIndex);
}

bool cHtmlContainer::RemoveNodeFromBody(size_t uiIndex) {
    return this->poBody.RemoveChild(uiIndex);
}

cHtmlNode cHtmlContainer::CreateComment(const string& sText) {
    cHtmlNode oComment {};
    oComment.SetNodeType(cMarkupNodeType::NO_CLOSE);
    oComment.SetNodePrefix("!--");
    oComment.SetTagName("");
    oComment.SetNodePostfix("--");
    oComment.AddAttribute(sText + " ", "");
    return oComment;    
}

cHtmlNode cHtmlContainer::CreateJSInclude(const string& sPath) {
    cHtmlNode oIncludeJS {cHtmlNodeType::SCRIPT};
    oIncludeJS.AddAttribute("src", sPath);
    return oIncludeJS;
}

cHtmlNode cHtmlContainer::CreateCSSInclude(const string& sPath) {
    cHtmlNode oIncludeCSS {cHtmlNodeType::LINK};
    oIncludeCSS.AddAttribute("href", sPath);
    oIncludeCSS.AddAttribute("rel", "stylesheet");
    oIncludeCSS.AddAttribute("type", "text/css");
    return oIncludeCSS;
}

string cHtmlContainer::ToString() {
    cHtmlNode oDoctype {cHtmlNodeType::DOCTYPE};
    oDoctype.SetNodePrefix("!");
    oDoctype.AddAttribute("html");
    Append(oDoctype.ToString());
    Append("<html>");
    std::vector<cMarkupNode> aAdditionals;
    cHtmlNode oTitle {cHtmlNodeType::TITLE}, oIcon {cHtmlNodeType::LINK};
    if (this->psTitle != "%none%") {
        oTitle.SetValue(this->psTitle);
        cMarkupNode* pNode = &oTitle;
        aAdditionals.push_back(*pNode);
    } 
    if (this->psIconPath.size() > 0) {
        //<link rel="shortcut icon" href="favicon.ico" sizes="48x48" />
        oIcon.AddAttribute("rel", "shortcut icon");
        oIcon.AddAttribute("href", this->psIconPath);
        oIcon.AddAttribute("sizes", (std::to_string(this->puiIconWidth) + "x" + std::to_string(this->puiIconHeight)));
        cMarkupNode* pNode = &oIcon;
        aAdditionals.push_back(*pNode);
    }
    this->poHead.SetPrependAdditionalChildren(true);
    Append(this->poHead.ToString(aAdditionals));
    Append(this->poBody.ToString());
    Append("</html>");

    return cStringBuilder::ToString();
}