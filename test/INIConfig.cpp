#include <INIConfig.h>
#include <gtest/gtest.h>

TEST(cINIGroup, Basic) {
    cINIGroup oGroup{"Settings"};
    ASSERT_TRUE(oGroup.GetGroupName() == "Settings");
    oGroup.AddProperty("name", "hello world!");
    ASSERT_TRUE(oGroup.GetProperty("name") == "hello world!");
    std::string sGroup = oGroup.ToString();
    std::string sShouldResult =
        "[Settings]\n"
        "name=hello world!\n";
    ASSERT_STREQ(sShouldResult.c_str(), sGroup.c_str());
}

TEST(cINIContainer, Basic) {
    cINIGroup oGroup1{"Settings1"}, oGroup2{"Settings2"};
    ASSERT_TRUE(oGroup1.GetGroupName() == "Settings1");
    ASSERT_TRUE(oGroup2.GetGroupName() == "Settings2");
    oGroup1.AddProperty("name", "hello world1!");
    oGroup2.AddProperty("name", "hello world2!");
    ASSERT_TRUE(oGroup1.GetProperty("name") == "hello world1!");
    ASSERT_TRUE(oGroup2.GetProperty("name") == "hello world2!");
    cINIContainer oContainer;
    oContainer.AddGroup(oGroup1);
    oContainer.AddGroup(oGroup2);
    std::string sINISettings = oContainer.ToString();
    std::string sShouldResult =
        "[Settings1]\n"
        "name=hello world1!\n"
        "[Settings2]\n"
        "name=hello world2!\n";
    ASSERT_STREQ(sShouldResult.c_str(), sINISettings.c_str());
}

TEST(cINIContainer, FromString) {
    const std::string sStr =
        "[test1]\n"
        "test = kaas\n"
        "[test2]\n"
        " kaas = test";
    cINIContainer oContainer;
    EXPECT_TRUE(oContainer.FromString(sStr));
}