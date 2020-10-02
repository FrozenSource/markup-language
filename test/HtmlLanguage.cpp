#include <Core.hpp>
#include <gtest/gtest.h>
#include <HtmlLanguage.h>

TEST(cHtmlNode, is_operator) {
    cHtmlNode oNode1 {cHtmlNodeType::BODY}, oNode2;
    ASSERT_TRUE(oNode2.GetHtmlNodeType() == cHtmlNodeType::NONE);
    oNode2 = oNode1;
    ASSERT_TRUE(oNode2.GetHtmlNodeType() == cHtmlNodeType::BODY);
}

TEST(cHtmlNode, PrintBase) {
    cHtmlNode oRootNode { cHtmlNodeType::HTML };
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<html></html>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, Attribute1) {
    cHtmlNode oRootNode { cHtmlNodeType::DIV };
    oRootNode.AddAttribute("class", "HtmlGenerator");
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<div class=\"HtmlGenerator\"></div>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, Attribute2) {
    cHtmlNode oRootNode { cHtmlNodeType::DIV };
    oRootNode.AddAttribute("class", "HtmlGenerator");
    oRootNode.AddAttribute("id", "HtmlGenerator");
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<div class=\"HtmlGenerator\" id=\"HtmlGenerator\"></div>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, ChildNode1) {
    cHtmlNode oRootNode { cHtmlNodeType::DIV };
    oRootNode.AddChild(cHtmlNode(cHtmlNodeType::DIV));
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<div>\n"
                           "<div></div>\n"
                           "</div>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, ChildNode2) {
    cHtmlNode oRootNode { cHtmlNodeType::DIV };
    oRootNode.AddChild(cHtmlNode(cHtmlNodeType::META));
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<div>\n"
                           "<meta>\n"
                           "</div>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, Value) {
    cHtmlNode oRootNode { cHtmlNodeType::DIV };
    oRootNode.SetValue("hello world!");
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<div>\nhello world!\n</div>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(cHtmlNode, Prefix) {
    cHtmlNode oRootNode { cHtmlNodeType::DOCTYPE };
    oRootNode.SetNodePrefix("!");
    oRootNode.AddAttribute("html");
    string sRoot = oRootNode.ToString();
    string sShouldResult = "<!doctype html>\n";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(HtmlGeneration, BasicHtmlPage) {
    cHtmlContainer oContainer;
    string sRoot = oContainer.ToString();
    string sShouldResult = "<!doctype html>\n<html><head></head>\n<body></body>\n</html>";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(HtmlGeneration, Title) {
    cHtmlContainer oContainer;
    oContainer.SetTitle("hello world!");
    string sRoot = oContainer.ToString();
    string sShouldResult = "<!doctype html>\n<html><head><title>\nhello world!\n</title>\n</head>\n<body></body>\n</html>";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}

TEST(HtmlGeneration, Icon) {
    cHtmlContainer oContainer;
    oContainer.SetIcon("favicon.ico", 48, 48);
    string sRoot = oContainer.ToString();
    string sShouldResult = "<!doctype html>\n<html><head><link rel=\"shortcut icon\" href=\"favicon.ico\" sizes=\"48x48\"/>\n</head>\n<body></body>\n</html>";
    ASSERT_STREQ(sShouldResult.c_str(), sRoot.c_str());
}