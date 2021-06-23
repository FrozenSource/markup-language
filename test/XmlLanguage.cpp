#include <gtest/gtest.h>

#include <XmlLanguage.h>

TEST(XmlGenerator, Doctype) {
    cXmlContainer oContainer;
    std::string sRoot = oContainer.ToString();
    std::string sShouldResult = "<?xml version=\"1.0\"?>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}