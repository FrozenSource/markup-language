#include <MarkupLanguage.h>

cMarkupNode::cMarkupNode(const std::string& sTagName, const cMarkupNodeType& eType) {
    this->SetTagName(sTagName);
    this->SetNodeType(eType);
}

cMarkupNode::cMarkupNode(const cMarkupNode& oNode) {
    *this = oNode;
}

cMarkupNode& cMarkupNode::operator=(const cMarkupNode& oNode) {
    cStringBuilder::operator=(oNode);
    this->paAttributes = oNode.paAttributes;
    this->paChildren = oNode.paChildren;
    this->psTagName = oNode.psTagName;
    this->peType = oNode.peType;
    this->psValue = oNode.psValue;
    this->psNodePrefix = oNode.psNodePrefix;
    this->psNodePostfix = oNode.psNodePostfix;
    this->pbPrependValue = oNode.pbPrependValue;
    return *this;
}

void cMarkupNode::SetTagName(const std::string& sTagName) {
    this->psTagName = sTagName;
}

std::string cMarkupNode::GetTagName() {
    return this->psTagName;
}

void cMarkupNode::SetNodeType(const cMarkupNodeType& eType) {
    this->peType = eType;
}

cMarkupNodeType cMarkupNode::GetNodeType() {
    return this->peType;
}

void cMarkupNode::SetValue(const std::string& sValue) {
    if (this->peType == cMarkupNodeType::NO_CLOSE ||
        this->peType == cMarkupNodeType::SINGLE_CLOSE)
        throw std::runtime_error("Node needs to have a secundary closing node.");
    this->psValue = sValue;
}

std::string cMarkupNode::GetValue() {
    return this->psValue;
}

void cMarkupNode::SetNodePrefix(const std::string& sPrefix) {
    if (this->peType != cMarkupNodeType::NO_CLOSE &&
        this->peType != cMarkupNodeType::SINGLE_CLOSE)
        throw std::runtime_error("prefixes and postfixes should not be used in a secundary node closing style.");
    this->psNodePrefix = sPrefix;
}

std::string cMarkupNode::GetNodePrefix() {
    return this->psNodePrefix;
}

void cMarkupNode::SetNodePostfix(const std::string& sPostfix) {
    this->psNodePostfix = sPostfix;
}

std::string cMarkupNode::GetNodePostfix() {
    return this->psNodePostfix;
}

void cMarkupNode::SetPrependValue(const bool& bPrepend) {
    this->pbPrependValue = bPrepend;
}

bool cMarkupNode::GetPrependValue() {
    return this->pbPrependValue;
}

void cMarkupNode::SetPrependAdditionalChildren(const bool& bPrepend) {
    this->pbPrependAdditionalChildren = bPrepend;
}

bool cMarkupNode::GetPrependAdditionalChildren() {
    return this->pbPrependAdditionalChildren;
}

bool cMarkupNode::AddAttribute(const std::string& sKey, const std::string& sValue) {
    if (this->paAttributes.find(sKey) != this->paAttributes.end()) return false;
    this->paAttributes.insert({sKey, sValue});
    return true;
}

bool cMarkupNode::AddAttribute(const std::string& sKey) {
    if (this->paAttributes.find(sKey) != this->paAttributes.end()) return false;
    this->paAttributes.insert({sKey, ""});
    return true;
}

std::string cMarkupNode::GetAttribute(const std::string& sKey) {
    if (this->paAttributes.find(sKey) == this->paAttributes.end()) return "";
    return this->paAttributes[sKey];
}

bool cMarkupNode::SetAttributeValue(const std::string& sKey, const std::string& sValue) {
    auto oAttribute = this->paAttributes.find(sKey);
    if (oAttribute == this->paAttributes.end()) return false;
    this->paAttributes[sKey] = sValue;
    return true;
}

bool cMarkupNode::RemoveAttribute(const std::string& sKey) {
    auto oAttribute = this->paAttributes.find(sKey);
    if (oAttribute == this->paAttributes.end()) return false;
    this->paAttributes.erase(sKey);
    return true;
}

size_t cMarkupNode::AddChild(const cMarkupNode& oNode) {
    if (this->peType == cMarkupNodeType::NO_CLOSE ||
        this->peType == cMarkupNodeType::SINGLE_CLOSE)
        throw std::runtime_error("Node needs to have a secundary closing node.");
    this->paChildren.push_back(oNode);
    return this->paChildren.size() - 1;
}

bool cMarkupNode::RemoveChild(cMarkupNode* pNode) {
    for (size_t i = 0; i < this->paChildren.size(); i++)
        if ((void*)&this->paChildren[i] == (void*)pNode) {
            this->paChildren.erase(this->paChildren.begin() + i);
            return true;
        }
    return false;
}

bool cMarkupNode::RemoveChild(size_t uiIndex) {
    if (uiIndex >= this->paChildren.size()) return false;
    this->paChildren.erase(this->paChildren.begin() + uiIndex);
    return true;
}

cMarkupNode& cMarkupNode::GetChild(size_t uiIndex) {
    if (uiIndex >= this->paChildren.size()) throw std::runtime_error("index out of bounds.");
    return this->paChildren[uiIndex];
}

std::string cMarkupNode::ToString(std::vector<cMarkupNode> aAdditionalChildNodes) {
    Append("<");
    if (this->psNodePrefix.size() > 0) Append(this->psNodePrefix);
    Append(this->psTagName);

    // Loop attributes if nessecary.
    for (auto& [sAttributeName, sAttributeValue] : this->paAttributes) {
        Append(" ");
        Append(sAttributeName);
        if (sAttributeValue.size() > 0) {
            Append("=\"");
            Append(sAttributeValue);
            Append("\"");
        }
    }

    if (this->peType == cMarkupNodeType::SINGLE_CLOSE) {
        Append("/>\n");
        return this->poBuffer.str();
    }
    else {
        if (this->psNodePostfix.size() > 0) Append(this->psNodePostfix);
        if (this->paChildren.size() > 0 || this->psValue.size() > 0)
            Append(">\n");
        else
            Append(">");
    }

    if (this->peType == cMarkupNodeType::NO_CLOSE) {
        Append("\n");
        return this->poBuffer.str();
    }

    if (this->psValue.size() > 0 && this->peType != cMarkupNodeType::SECONDARY_CLOSE)
        throw std::runtime_error("Cannot add a value to a singular node type.");

    if (this->psValue.size() > 0 && this->pbPrependValue) {
        Append(this->psValue);
        Append("\n");
    }

    if (this->pbPrependAdditionalChildren && aAdditionalChildNodes.size() > 0) {
        for (cMarkupNode& oChild : aAdditionalChildNodes)
            Append(oChild.ToString());
    }
    for (cMarkupNode& oChild : this->paChildren)
        Append(oChild.ToString());
    if (!this->pbPrependAdditionalChildren && aAdditionalChildNodes.size() > 0) {
        for (cMarkupNode& oChild : aAdditionalChildNodes)
            Append(oChild.ToString());
    }
    
    if (this->psValue.size() > 0 && !this->pbPrependValue)  {
        Append(this->psValue);
        Append("\n");
    }

    if (this->peType == cMarkupNodeType::SECONDARY_CLOSE) {
        Append("</");
        Append(this->psTagName);
        Append(">\n");
    }

    return cStringBuilder::ToString();
}