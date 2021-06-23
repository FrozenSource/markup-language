#include <XmlLanguage.h>

cXmlNode::cXmlNode(const std::string& sTagName, const cMarkupNodeType& eNodeType) {
    this->SetTagName(sTagName);
    this->SetNodeType(eNodeType);
}

cXmlNode::cXmlNode(const cXmlNode& oNode) {
    *this = oNode;
}

cXmlNode& cXmlNode::operator=(const cXmlNode& oNode) {
    cMarkupNode::operator=(oNode);
    return *this;
}

cXmlContainer::cXmlContainer(const cXmlContainer& oContainer) {
    *this = oContainer;
}

cXmlContainer& cXmlContainer::operator=(const cXmlContainer& oContainer) {
    cStringBuilder::operator=(oContainer);
    this->paNodes = oContainer.paNodes;
    return *this;
}

void cXmlContainer::AddNode(const cXmlNode& oNode) {
    this->paNodes.push_back(oNode);
}

cXmlNode& cXmlContainer::GetNode(size_t uiIndex) {
    return this->paNodes[uiIndex];
}

bool cXmlContainer::RemoveNode(size_t uiIndex) {
    if (uiIndex >= this->paNodes.size()) return false;
    this->paNodes.erase(this->paNodes.begin() + uiIndex);
    return true;
}

std::string cXmlContainer::ToString() {
    cXmlNode oDocType {"xml", cMarkupNodeType::NO_CLOSE};
    oDocType.SetNodePrefix("?");
    oDocType.SetNodePostfix("?");
    oDocType.AddAttribute("version", "1.0");
    Append(oDocType.ToString());
    for (int i = 0; i < this->paNodes.size(); i++)
        Append(this->paNodes[i].ToString());
    return cStringBuilder::ToString();
}